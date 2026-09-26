# Orchestration

`orchestrate` is the claim-aware half of the tooling layer. `frontier`, `swarm`, `evidence`, `context` and `validate` answer questions about targets. The orchestrator answers the question "who is working on this target right now, and what happens to it when they finish". It owns no analysis of its own: every fact it hands a worker was already produced by one of the read-side tools, and every state transition it performs goes through the existing canonical queue.

Read this alongside [architecture.md](architecture.md) (module boundaries), [concurrency.md](concurrency.md) (who may write what), [commands.md](commands.md) (the CLI surface), [evidence-model.md](evidence-model.md) (what a worker is shown) and [frontier-scoring.md](frontier-scoring.md) (how a target earns priority). The queue stage machine this layer implements is specified separately in [../analysis/ORCHESTRATOR.md](../analysis/ORCHESTRATOR.md).

## What this is

| Layer | Commands / modules | Owns |
|---|---|---|
| Planning, evidence, validation | `openspore frontier`, `swarm`, `evidence`, `context`, `validate`, `recover`, `integrate` | target ranking, evidence packs, context briefs, validator verdicts |
| Worker lifecycle | `openspore orchestrate`, `claim`, `release`, `worker-template`; `orchestrate.py` | claim, brief, launch, ingest, validate, reconcile, checkpoint, release |
| Ownership and leases | `queue_op` over `investigations` in `knowledgegraph/spore.db` | `status`, `implementer_id`, `stage`, `attempts`, `checkpoint`, `block_reason` |
| Knowledge source of truth | `reconstruction_knowledge` / `spore.db` | the canonical projection, xrefs, node/edge graph |

Three things this layer deliberately does not have:

- **No second scheduler database.** The plan is derived from the frontier on every call and discarded. The only durable orchestration state is the `investigations` row.
- **No second claim system.** `tools/reconstruction_tooling/queue.py` owns no claim logic. It delegates every call to `kg_tools.queue_op`, which is the only writer of the `investigations` table.
- **No second manifest.** Candidate membership comes from the canonical triage queue and the generated index, as it does for `frontier`.

`plan()` writes nothing. It opens the database through a read-only URI and builds the projection ephemerally. `orchestrate plan` is safe to run against a database other agents are holding leases in.

## The pipeline

Per target, in order:

```text
frontier survey            plan()            read-only   rank + claim overlay
  ↓
projection + SCC + roles   schedule.py       read-only   group, classify, wave
  ↓                                                   (waves() is pure)
ensure queue row           _resolve_row()    write       queue_op insert, only if absent
  ↓
take the lease             queue.claim       write       queue_op claim
  ↓
collect inputs             collect_inputs()  read-only   evidence + context + validate
  ↓
build the briefing         brief()           read-only   reuses the collected inputs
  ↓
run the worker             launch()          write       child process, cwd-scoped
  ↓
parse the reply            ingest()          read-only   strict, never guesses
  ↓
validate the candidate     validate()        read-only
  ↓
decide the disposition     reconcile()       pure        decision table
  ↓
record the evidence        queue.checkpoint  write       writes evidence_refs, renews the lease
  ↓
close or release           close()/release() write       queue_op close / release
  ↓
frontier refresh           next plan()       read-only   nothing is cached between runs
```

Two properties fall out of this order. The evidence a worker produced is written before the lease ends, so a crash between the two leaves an `active` row whose `checkpoint` explains itself. And the lease is only ever ended by an explicit `close` or `release`, so a target is never silently returned to the pool by an exception.

## Planning and the dependency scheduler

### Making a frontier target claimable

`frontier` and `swarm` speak `0x%08x`; the `investigations` table stores bare 8-character hex. `swarm.decorate()` projects a frontier target into a queue-addressable entry with three extra fields:

| Field | Meaning |
|---|---|
| `queue_va` | bare 8-hex, exactly as `investigations.va` stores it |
| `queue_id` | the canonical row id, or `null` when no row exists yet |
| `queue_row` | `true` when a row already exists for the current build |

`orchestrate.plan()` calls `swarm.decorate()` rather than re-projecting, so a target is described identically whether it arrived through `openspore swarm` or straight from `plan()`. That is the only place the format translation happens: `queue.queue_va()` and `kg_tools.normalize_queue_va()` are the two boundaries, and `ensure_row()` normalizes before inserting. Skipping that normalization misses the unique dedup key `(kind, va, binary_sha256)` and duplicates a row that already exists.

A real entry from `orchestrate plan --limit 5 --json`:

```json
{
  "va": "0x008db310",
  "queue_va": "008db310",
  "queue_id": "fun:008db310:Resource::PFIndexModifiable::Write",
  "queue_row": true,
  "claim_state": "queued_same_sha",
  "claimable": true,
  "role": "independent",
  "reason": "no_open_internal_callees",
  "dispatchable": true,
  "score": 91
}
```

`dispatchable` is the distinction that matters operationally: the plan contains the targets this run will dispatch (`dispatchable: true`) and the deferred targets that explain why the wave boundaries exist. Targets whose claim state is `claimed`, `active_unowned`, `stale_binary`, `coordination_missing`, `completed` or `blocked` are filtered out before classification, so only `dispatchable` entries are ever claimed.

### Roles

`schedule.classify()` assigns one mutually exclusive role per target. Precedence is top-down; a target that is claimed, blocked or finished is not available work regardless of anything else true about it.

| Order | Role | Assigned when | Effect |
|---|---|---|---|
| 1 | `blocked` | `block_reason` is set, or `claim_state == "blocked"` | never scheduled |
| 2 | `claimed` | `claim_state` in `claimed`, `active_unowned`, `stale_binary`, `coordination_missing` | never scheduled |
| 3 | `completed` | a queue row exists and `claim_state == "completed"`, or the projection already records it reconstructed | never scheduled |
| 4 | `coordinated` | more than one plan member shares a scheduling component | one dispatch slot for the whole component |
| 5 | `dependent` | calls another plan member that is not reconstructed yet | waits for the wave containing that callee |
| 6 | `uncertain` | `dependency_uncertain` | scheduled, with the uncertainty in the briefing |
| 7 | `independent` | no open internal callee | scheduled in the first ready wave |

Roles 1 to 3 are the availability ladder. Roles 4 to 7 are scheduling decisions. A `dependent` target is held back only for a callee that is *in this plan*; a callee outside the plan is context, because it will not be done by this run and deferring on it would stall the frontier permanently.

### Waves

`schedule.waves()` emits a list of waves. A wave is a maximally parallel set: by construction there is no ordering constraint between its members. The only serialization the dependency graph justifies is that a `dependent` target lands in a later wave than the wave containing its open callees. `run()` dispatches the members of one wave concurrently under a fixed thread pool, then moves to the next wave.

A wave that cannot be scheduled is emitted explicitly rather than dropped:

```json
{
  "index": 4,
  "reason": "no_progress",
  "targets": [],
  "waiting_on": ["0x0044ae00"]
}
```

`no_progress` means every remaining target waits on another remaining target, which is either a cycle the call-edge SCC pass could not see or a prerequisite outside the plan. It is a report, not a loop. From the real `plan --limit 5` output.

### What is not a scheduling key

Three fields that look like grouping keys are explicitly not used, each for a different reason:

- **`package`.** It is null for 232 of the 368 frontier targets today, and all 136 targets that do carry one are currently ineligible. Grouping by it would collapse the frontier into a few buckets that happen to line up with work that is already integrated, and would serialize unrelated targets against each other.
- **`cluster`.** Co-membership of a product or subsystem cluster is a similarity hint, not a dependency. It affects the frontier score and nothing else. Two functions in the same cluster routinely have nothing to do with each other.
- **`analogues`.** Analogues are shared-signal context computed by `reconstruction_knowledge.analogue_record` (shared types, same calling convention, same package). They are attached to the briefing as context and never gate dispatch, because "these two functions look alike" is not an ordering constraint.

### Two notions of SCC

`schedule.scc_partition()` reports two different components and conflating them is a bug:

| Field | Scope | Used for |
|---|---|---|
| `scc.members`, `scc.size` | only the VAs in this plan | the scheduling unit: two plan members in one component go to one worker, because mutual recursion cannot be ordered between them |
| `scc.cycle_members`, `cycle_size` | every member in the whole binary, from the full `xref` table | telling the worker that a cycle exists even when the siblings are not in this run |

A real example from `plan --limit 5`, where the two disagree:

```json
{
  "va": "0x00d00a10",
  "role": "uncertain",
  "scc": {
    "id": "scc-0064",
    "size": 1,
    "members": ["0x00d00a10"],
    "cycle_size": 4,
    "cycle_plan_members": 2,
    "cycle_members": ["0x00d00a10", "0x00d00a70", "0x00d00ee0", "0x00d05a20"]
  }
}
```

This target is its own scheduling unit, so it is dispatched alone, and it sits inside a four-function cycle of which one sibling is in the same plan. The briefing hands the worker the full cycle so it can report the mutual recursion even though it cannot resolve it.

Only call-shaped xrefs create edges. `CALL_REFERENCE_TYPES` is `direct-call`, `thunk`, `computed-call`. `vtable-ref` and `data-ref` are excluded because they describe dispatch candidates, not an ordering between two reconstructions; including them would manufacture a cycle out of every shared vtable.

### `dependency_degraded`

`summary.dependency_degraded` is `true` when the call-edge pass found zero usable edges between plan members. You get it when the `xref` table has no call rows for these VAs, when the database cannot be opened, or when the query fails. In that case every target is reported as its own singleton component rather than as a guess, and the plan says so. Singletons are the honest answer: they maximize parallelism and they are visibly wrong if the evidence was actually missing. A degraded plan is still dispatchable, but the wave boundaries in it carry no information.

## Claims, leases and ownership

### The claim shape

`queue_op claim` is the only way to take ownership, and it is a compare-and-set inside `BEGIN IMMEDIATE`:

1. open the row,
2. refuse if `binary_sha256` was supplied and does not match the row,
3. refuse if the row is terminal (`done`, `dropped`),
4. if the row is `active` and the owner matches, return success with `idempotent: true` and change nothing,
5. if the row is `active` under another owner, compute staleness; refuse with `already_claimed` unless the caller passed `allow_stale` *and* the lease really is stale,
6. refuse if the row is `blocked` unless `allow_blocked` was passed,
7. `UPDATE ... WHERE id=? AND status=? AND COALESCE(implementer_id,'')=?`, clearing `block_reason` and stamping `updated_at`,
8. require `rowcount == 1`; anything else rolls back with `already_claimed`.

Step 8 is what makes a claim race produce exactly one winner. Two orchestrators that pick the same target produce one owner and one `already_claimed`, not two active rows. A stale takeover additionally merges the displaced holder into `checkpoint.lease_history` before overwriting `implementer_id`, because a silent displacement is unauditable afterwards.

### Lease fields and clock

There are no dedicated lease columns. The lease is `implementer_id` plus `updated_at`:

| Field | Role |
|---|---|
| `status` | lifecycle: `queued`, `active`, `blocked`, `done`, `dropped` |
| `implementer_id` | the lease token. `NULL` whenever the row is not `active` |
| `updated_at` | the lease clock, written by SQLite `datetime('now')` on every accepted write |
| `stale_after_seconds` | the TTL, passed per claim and not stored |

`stale_after_seconds` defaults to 3600 inside `queue_op`, and the orchestrator passes `LEASE_TTL` (1800) explicitly. The floor is 60 seconds (`_MIN_STALE_AFTER_SECONDS`); anything shorter is refused, because a zero-length lease would make every held claim instantly stealable and turn one racing worker into a double-ownership bug. The adapter applies the same floor (`queue.MIN_TTL`) before the call.

Three clock formats are readable (`_LEASE_TIME_FORMATS`): SQLite's `datetime('now')` output `%Y-%m-%d %H:%M:%S`, and the ISO-8601 forms with and without a trailing `Z` that rows seeded outside `queue_op` carry. The clock fails closed: a `NULL` or unparseable `updated_at` is **never** stale, so the row stays locked until a human releases it explicitly. That is deliberate. A misread clock in the other direction would hand a live worker's target to somebody else.

### A checkpoint write is the heartbeat

There is no heartbeat verb. `queue_op update` stamps `updated_at` on every accepted write, and the update is guarded by the same lease token as everything else, so a checkpoint is simultaneously the progress record and the lease renewal. `HEARTBEAT_SECONDS` is 600: a worker that is doing real work for longer than ten minutes should write a checkpoint. The value is also shipped to the worker as `lease.heartbeat_every_seconds`.

`stale_after_seconds` therefore has to exceed the longest gap between checkpoints, not the total worker runtime. With a 1800-second TTL and a 600-second cadence, three consecutive missed heartbeats are needed before a lease looks stale.

### Three verbs, not one

| Verb | What it does | Replay contract | Use when |
|---|---|---|---|
| `queue_op update` | writes any `_QUEUE_WRITABLE` column except `status` and `implementer_id`: `stage`, `attempts`, `checkpoint`, `evidence_refs`, `adjudicator_id`, `name`, `subsystem`, `mode`, `why_interesting`, `prerequisites`, `block_reason`, `va` | not idempotent across owners: a write to an `active` row requires a matching `implementer_id` | recording progress |
| `queue_op release` | clears the lease, moves to `queued` or `blocked` | idempotent: releasing an unheld row is a success no-op | the target continues |
| `queue_op close` | moves to a terminal `done` or `dropped` | idempotent: re-closing a terminal row returns `closed: false` and does nothing | the target is finished |

They are three verbs rather than `update{status: ...}` for three reasons. Each has a different compare-and-set predicate (`update` matches the observed status and owner, `release` requires `status='active' AND owner=?`, `close` matches the observed status and owner but demands a terminal disposition). They have different replay contracts, which matters because the orchestrator retries `release` after a crash. And only `release` clears `implementer_id`, which is what makes `active` with no owner inexpressible.

`queue_op update` refuses to write `status` or `implementer_id` at all. Ownership and status transitions have their own verbs, and the error message says so.

### What is idempotent, what is refused

| Operation | Behaviour |
|---|---|
| `claim` on a row you already hold | success, `claimed: false`, `idempotent: true`, no write |
| `claim` on a terminal row | refused: `already_completed` |
| `claim` on a `blocked` row without `allow_blocked` | refused: `blocked`, with the existing `block_reason` |
| `claim` on another worker's live lease | refused: `already_claimed`, with `stale` and `stale_after_seconds` |
| `claim` on another worker's *stale* lease without `allow_stale` | refused: `already_claimed`, with `stale: true` |
| `claim` with `stale_after_seconds < 60` | refused: `invalid_params` |
| `insert` on an existing `(kind, va, binary_sha256)` | not an error: `inserted: false` plus the surviving row |
| `insert` with no `binary_sha256` | refused: `missing_param` |
| `release` on a row that is not `active` | success no-op, `released: false`, `idempotent: true` |
| `release` on a terminal row | refused: `already_completed` |
| `release` by a non-owner | refused: `not_owner`. A lease is never taken by releasing it |
| `close` on a terminal row | success, `closed: false`, `previous_status` reported |
| `close` by a non-owner on an `active` row | refused: `not_owner` |
| `close` with a non-terminal disposition | refused: `invalid_params` |
| `update` on a terminal row | refused: `already_completed`. Terminal rows are never resurrected |
| `update` on an `active` row by a non-owner | refused: `not_owner`, with `next_action` telling you to re-read and re-plan |
| `update` writing `status` or `implementer_id` | refused: `invalid_params` |
| `update` with no writable field, or an unknown field | refused: `nothing_to_update` / `invalid_params` |

### `binary_sha256` pinning

Every investigation row is pinned to the build it describes, and the unique key is `(kind, va, binary_sha256)`. A function re-investigated under a new build is a new row; the old one is never overwritten. The orchestrator passes the plan's `binary_sha256` on every claim and close, so a claim against a row belonging to a different build is refused with `stale_binary` and both hashes are reported.

Two different conditions share that name, and they are not the same thing. `queue_op` returning `stale_binary` means the row you named belongs to another build. The frontier claim state `stale_binary` means every claim row for that VA belongs to another build, so the target has no current-build row at all. The first is a caller error, the second is a build transition; both leave the target unclaimed and both require a `dossier_regenerate` / `ghidra_snapshot_save` against the new build before work resumes.

### `block_reason` prefixes

`block_reason` is free text, but these prefixes are the machine-readable classes the orchestrator routes on. They are advisory and enforced nowhere; a human can write anything.

| Prefix | Meaning |
|---|---|
| `validation_fail` | the validator rejected the candidate and the retry budget is spent |
| `validation_warn` | the validator warned. A review request, not a failure |
| `validation_unknown` | the validator could not reach a verdict |
| `validation_not_available` | the validator had no evidence to run against |
| `malformed_worker_output` | the worker's reply did not satisfy the result contract, twice |
| `dependency_blocked` | a prerequisite cannot be reconstructed |
| `no_evidence` | no decompilation, disassembly or ABI projection exists |
| `ghidra_offline` | the binary-analysis bridge is unavailable |
| `machine_locked` | the GPU or display lock is held elsewhere |
| `no_spo` | `SPORE/` is not present |
| `approval_required` | a gated tool needs human sign-off |
| `escalated:<reason>` | a bound tripped; the suffix is the stop reason |
| `obsolete` | the target stopped being worth reconstructing |

Of these, the orchestrator itself writes only five: `validation_warn`, `validation_unknown`, `validation_not_available` and `blocked` on a `review` or `block` decision, and `escalated:<stop>` when a bound trips. Everything else is either set by another tool or by a human, and is classified only so that a triage script can group them. The reason recorded is the disposition, not the diagnosis: a `validation_not_available` row needs the underlying cause read off the `checkpoint` and the evidence `missing_sections`, not guessed from the prefix.

## The worker contract

`worker_contract.py` has two halves, both machine-readable and both deterministic.

### The briefing

`briefing()` assembles a package with schema `openspore-worker-briefing-1`. It reuses the evidence pack and the context brief that already exist rather than re-deriving them, and everything passes through the same `compact()` bound the evidence pack uses, so a 6 MB decompilation cannot swamp the prompt. The sections:

| Section | Content |
|---|---|
| `target` | VA, `queue_va`, `queue_id`, name, package, subsystem, cluster, category, evidence level |
| `lease` | `implementer_id`, `binary_sha256`, attempt number, `max_attempts`, heartbeat cadence |
| `objective` | one sentence naming the VA and the symbol |
| `current_status` | the context brief's status section |
| `frontier_reason` | score, score components, reason codes, claim state, runtime gate, evidence readiness |
| `decompilation`, `disassembly`, `ghidra_function` | the bounded evidence values |
| `callers`, `callees`, `xrefs` | call edges and edge rows |
| `abi`, `types`, `fields_offsets`, `globals`, `vtables`, `services` | the structural projection |
| `state_event_links`, `semantic_findings`, `contradictions` | derived semantics and known conflicts |
| `analogues` | shared-signal context, not a dependency |
| `dependencies` | open dependencies, the scheduling component, the whole-binary cycle, external callees, truncation flags |
| `existing_reconstruction` | what already exists for this VA |
| `reconstruction_constraints` | architecture, the VA the symbol must embed, where to write, what not to touch, the rules, the outcomes |
| `validation_requirements` | required categories, the baseline verdict, the baseline checks, the gate |
| `evidence` | evidence state, the pack and context digests, provenance refs, missing sections |
| `rules` | `WORKER_RULES`, verbatim |
| `result_contract` | the result schema, required and optional fields, outcomes, verdicts |
| `retry` | only on attempt 2 and later: the previous outcome, the previous summary, the validator findings, and the instruction to address them or return `STILL_UNKNOWN` |

What a worker must **not** be asked to do, and is not told to do:

- not claim or release anything. Ownership is the orchestrator's; the worker only ever reads the lease block it was handed,
- not run the validator on itself. The briefing states the gate ("only a PASS may complete the target"); the orchestrator runs `openspore validate` on the candidate,
- not decide its own promotion. `reconcile()` maps outcome and verdict to a disposition with no worker input,
- not touch `src/`, another worker's staging package, another worker's metadata sidecar, `tools/mcp/**`, or the manifest. Those are in `WORKER_RULES` and in `reconstruction_constraints`.

### The result

Schema `openspore-worker-result-1`. Required fields: `schema`, `va`, `outcome`, `summary`, `source_files`, `observed_mechanics`, `unresolved_questions`, `evidence_refs`. Optional: `normalized_symbol`, `reconstructed_symbol`, `package`, `subsystem`, `types`, `observed_original_abi`, `layout`, `globals`, `vtables`, `services`, `state_events`, `semantic_findings`, `confidence`, `runtime_gates`, `blockers`, `validation`, `attempts_used`, `notes`.

The six outcomes and what each does to the target:

| Outcome | Meaning | Effect |
|---|---|---|
| `IMPLEMENTED` | candidate source exists and was produced | may complete on a validator `PASS` |
| `PARTIAL` | some claims modelled, material uncertainty remains | may complete on `PASS` |
| `STRUCTURAL_ONLY` | signature, layout and ABI only; no body semantics claimed | may complete on `PASS` |
| `STILL_UNKNOWN` | the evidence does not support any semantic claim | costs an attempt, never completes |
| `BLOCKED` | the worker cannot proceed; it needs a gate or an answer | costs an attempt, routes to a blocked row |
| `FAILED_VALIDATION` | the worker ran and the candidate was rejected | costs an attempt, routes to a retry |

`STILL_UNKNOWN` is a correct answer, and the briefing says so twice: in `WORKER_RULES` ("that is a correct answer, not a failure") and in the retry instruction. A worker that guesses to avoid it has produced worse evidence than one that admits the gap.

`parse_result()` is deliberately unforgiving. It refuses empty output, non-JSON, non-object payloads, a missing required field, the wrong `schema`, an unknown outcome, a `va` that does not match the assigned target, a non-list where a list is required, an unknown self-reported verdict, and anything over 4 MiB. Each refusal is a typed `{"accepted": false, "code": "malformed_worker_output", "reason": ...}` with the SHA-256 of the raw bytes, so the orchestrator routes on it and nothing is guessed. The recorded `va` is always the orchestrator's own, never the payload's, so a confused worker cannot be recorded against the wrong function.

**A natural-language final message is not parsed.** The briefing states it and the parser requires it: prose around the JSON document is ignored, and if the prose is the only output the reply is malformed.

### Digest tracking

The briefing ends with `content_sha256` over the whole package, computed before the field is populated. It carries the evidence pack's own `content_sha256` and the context brief's `content_content_sha256` in `evidence`. On completion the orchestrator writes `briefing_content_sha256` into the `VALIDATE` checkpoint, so a stored result is always traceable to the exact briefing the worker was handed. Separately, the parsed reply keeps the SHA-256 of the raw stdout as `raw_sha256`.

## Validation and the retry loop

`reconcile()` is a pure decision table over the worker's outcome and the validator's verdict. The ordering is the whole safety argument: a target is only completed on a validator `PASS` of a candidate the worker actually produced.

### Two dimensions, not one verdict

`validate()` returns **two independent dimensions**, and only the first one can complete a target.

| Dimension | Field | Question it answers | Resting state |
|---|---|---|---|
| `STATIC` | `report["static"]`, aliased as `report["status"]` | does the reconstruction agree with the binary? | `PASS` / `WARN` / `FAIL` / `UNKNOWN` / `NOT_AVAILABLE` |
| `RUNTIME` | `report["runtime"]` | was the original process observed? | `GATED` / `PASS` |

A static `PASS` says the reconstruction was accepted against the binary. It is never a runtime claim, and completion never clears a runtime gate: the completion result and the `VALIDATE` checkpoint both carry `runtime: {status, gated, gates}` so a closed row still shows the gate is open.

`RUNTIME` is `GATED` rather than `NOT_AVAILABLE` on purpose. `NOT_AVAILABLE` means "a verdict could not be reached" and is indistinguishable from a category that was searched and found empty, which would report a permanent capability gap as a per-target finding. Nothing in this repository has run the original process, so a gate is open: nothing was attempted and nothing failed. A runtime `FAIL` is not representable, because no experiment exists that could fail.

`EVIDENCE COVERAGE` is reported in full but is **not** a verdict. It counts available evidence categories over the *static* categories only — the reserved `runtime` category is excluded, since a capability gap on the original process must not be able to veto a static verdict. Its one remaining power is a floor: if no static evidence category is available at all, the static verdict is `NOT_AVAILABLE` and a reconstruction cannot be validated against nothing.

Every report also carries `static.evidence_basis`, which states how many of the eight static checks were actually evaluated. A static `PASS` means every check that could be evaluated agreed; the basis makes a thin pass legible as thin.

### Verdicts

| Verdict | Outcome | Action | Burns an attempt |
|---|---|---|---|
| `PASS` | `IMPLEMENTED` / `PARTIAL` / `STRUCTURAL_ONLY` | `complete`, code `validated` | yes |
| `FAIL` | any | `retry`, code `validation_fail` | yes |
| `WARN` | any | `review`, code `validation_warn` | no, recorded in the checkpoint |
| `UNKNOWN` | any | `review`, code `validation_unknown` | no |
| `NOT_AVAILABLE` | any | `review`, code `validation_not_available` | no |
| `PASS` | `STILL_UNKNOWN` / `BLOCKED` / `FAILED_VALIDATION` | `retry`, code is the lowercased outcome | yes |
| any | `BLOCKED` | `block`, code `blocked` | yes |
| any | anything else | `review`, code `unclassified_outcome` | yes |

`review` releases to `blocked`, never to `queued`, and never closes. A target is not completed on a warning.

`NOT_AVAILABLE` on a check is an absence of evidence, never evidence of failure, and it is neutral: it neither passes nor poisons the aggregate. A check reaches `PASS` only where an oracle **independent of the reconstruction** exists and agreement is provable — today that is `CALLS` against the Ghidra xref export, and `CONSTANTS` / `VIRTUAL DISPATCH` against a collected disassembly. `GLOBALS`, `FIELDS/OFFSETS` and `CONTROL FLOW` have no `PASS` branch at all, because the repository holds no independent global-reference or struct-layout evidence and the bridge never populates the `dispatch` field.

### Bounds

| Constant | Value | What it bounds |
|---|---|---|
| `MAX_ATTEMPTS` | 3 | the `max_attempts` advertised in the briefing |
| `MAX_VALIDATION_RETRIES` | 2 | retries after the first `validation_fail`, so three `FAIL`s in total |
| `MAX_MALFORMED` | 2 | malformed worker replies, in ingest and again in the retry guard |
| `MAX_TOTAL_ATTEMPTS` | 12 | the `_total` counter, across every outcome |
| `MAX_ITERATIONS` | 64 | the per-target loop, and the wave loop in `run()` |
| `HEARTBEAT_SECONDS` | 600 | the checkpoint cadence a worker should hold |
| `LEASE_TTL` | 1800 | `stale_after_seconds` passed to every claim |

`MAX_ATTEMPTS` is what the worker is told; it is not the enforcement number. Enforcement is `MAX_VALIDATION_RETRIES` for a `FAIL` loop, `MAX_MALFORMED` for a malformed loop, and `MAX_TOTAL_ATTEMPTS` for everything else. Note the consequence: the retry guard after a non-`FAIL` retry decision reads the `_malformed` counter, which only a malformed reply increments, so a worker that keeps answering `STILL_UNKNOWN` is bounded by `MAX_TOTAL_ATTEMPTS` and not by `MAX_MALFORMED`. That is deliberate. Repeating a correct negative answer is a different failure from emitting garbage, and it should not exhaust the same budget.

The `_total` counter is incremented by every counter bump, so one accepted worker reply costs 2 and one malformed reply costs 1. `MAX_TOTAL_ATTEMPTS = 12` is therefore roughly six worker attempts, not twelve. When a bound trips, `process_target()` bumps `_total` once more, writes a checkpoint with `next_action: human_review` and the `stop_reason`, releases to `blocked` with `reason = "escalated:<stop>"`, and returns. The stop reason is one of `attempt_budget`, `malformed_worker_output`, `validation_fail`, `still_unknown`, `blocked`, `failed_validation`.

`run()` additionally raises `OrchestrationBoundExceeded` if the wave loop reaches 64 iterations, so a scheduling regression fails loudly instead of hanging.

### Evidence first, lease second

The checkpoint that records `evidence_refs`, the outcome, the verdict, the failed checks and the next action is written **before** `close` or `release`. This is not cosmetic. SQLite gives no transaction spanning two separate `queue_op` calls, so the only question is which failure mode is recoverable:

- crash after the checkpoint, before the release: the row is still `active` under a lease that will go stale, and the `checkpoint` says exactly what happened and what to do next. The target is recoverable.
- crash after the release, before the checkpoint: the row is back in `queued` with no record of the work. A later run would redo it, or worse, treat it as fresh.

The same ordering appears on the malformed path, where the checkpoint records the failure reason, the raw reply digest, and `next_action: respawn_worker` before the release to `queued`.

## Failure recovery

| Failure | State transition | Ops issued | Recovery |
|---|---|---|---|
| Worker crash, lease still fresh | stays `active` | none | wait for the TTL. The target is `claimed` in the plan and will not be dispatched |
| Worker crash, lease stale | `active` → `active` under a new owner | `claim(allow_stale=true)` | the displaced holder is recorded in `checkpoint.lease_history` with its stage and TTL. Re-brief from the new owner's checkpoint |
| Malformed worker reply | `active` → checkpoint → `queued` | `checkpoint(stage=REPLACE)`, `release(to=queued)` | `_malformed` is bumped. Two in a row stops the loop with `escalated:malformed_worker_output` |
| Worker times out | same as malformed, with `code: worker_timeout` | same | the timeout is enforced by `launch()`, and the reply is discarded rather than half-parsed |
| Validator `FAIL` | `active` → checkpoint → `queued` | `checkpoint(stage=VALIDATE)`, `release(to=queued)` | the next iteration re-claims with the same worker identity, so the retry is a continuation of the same lease. Three `FAIL`s stop the loop |
| Validator `WARN` | `active` → checkpoint → `blocked` | `checkpoint(stage=VALIDATE)`, `release(to=blocked, reason=validation_warn)` | human review. No attempt is burned and the row is never closed on a warning |
| Validator `UNKNOWN` / `NOT_AVAILABLE` | as `WARN` | same, with the matching reason | the reason records the verdict, not the cause. The cause (missing evidence, an offline bridge) is read off the `checkpoint` and the briefing's `missing_sections` |
| Lease expires during a live run | the next write is refused | `checkpoint` returns `not_owner` | the displaced worker's writes stop landing immediately. It should re-read the row and re-plan, not retry the write. Its artifacts stay on disk for the new owner to judge |
| Stale claim from a dead agent | the row stays `active` under an `implementer_id` nobody is using | `orchestrate reap` to list and read the clock, then `orchestrate reclaim --allow-stale` or `claim --allow-stale` | `reap` is report-only and never auto-steals. Naming the row is a deliberate act, and the takeover is recorded |
| Missing evidence (no decompilation) | never reaches a claim | none | the briefing carries `missing_sections` and the worker is expected to return `STILL_UNKNOWN` or `STRUCTURAL_ONLY` |
| Concurrent conflicting writes | exactly one wins | `rowcount != 1` → `conflict`, or `already_claimed` on the claim and activation paths | no silent last-write-wins anywhere in the queue path |
| A dependency becomes blocked | its dependents stay `dependent` | none | they remain visible in later waves and are never dispatched until the prerequisite is reconstructed. `waves()` emits `no_progress` rather than spinning |
| A target becomes obsolete mid-run | the worker returns `BLOCKED` | `release(to=blocked, reason=blocked)` | the human decides whether to `close(status=dropped)`. The row is never deleted: it is the dedup memory |
| Bound trips | `active` → checkpoint → `blocked` | `checkpoint(next_action=human_review)`, `release(to=blocked, reason=escalated:<stop>)` | escalation is a first-class state, not a crash. Reset the counter by hand after resolving it |

Two rules follow from the table. A lease is never taken by releasing it: a non-owner `release` is refused with `not_owner`, and a takeover needs `allow_stale`. And a terminal row is never rewritten, so a target that was closed wrongly is corrected by a human with an explicit new row or disposition, not by a racing write.

## CLI recipes

Every command accepts `--json` and returns one envelope:

```json
{
  "$schema": "openspore-cli-result-1",
  "command": "orchestrate",
  "status": "ok",
  "ok": true,
  "source": { "requested": "persisted", "live": false, "mode": "persisted" },
  "result": {},
  "warnings": [],
  "changed": false,
  "idempotent": true
}
```

Errors keep the same envelope with `status: "error"`, `ok: false`, `code`, `message`, `exit_code`, and a nonzero process exit.

### `orchestrate plan`

Read-only. Safe to run while other agents hold leases.

```bash
python3 tools/openspore.py orchestrate plan --limit 5 --json
```

Real summary from that run:

```json
{
  "targets": 81,
  "dispatchable": 5,
  "by_role": { "dependent": 25, "independent": 12, "uncertain": 44 },
  "queue_addressable": 18,
  "queue_missing": 63,
  "waves": 5,
  "wave_widths": [56, 15, 3, 4, 0],
  "coordinated_units": 0,
  "in_cycle": 3,
  "largest_cycle": 6,
  "dependency_degraded": false,
  "scc_evidence_edges": 71,
  "universe_call_edges": 202276
}
```

The document also carries `status`, `binary_sha256`, the `database` path, the full `waves` list, and every classified `targets` entry. The plan is deterministic: the same frontier and the same queue state give byte-identical output, which is what makes two plans comparable.

The command takes about a second because it rebuilds the canonical projection every call rather than reading a cached index. That cost buys the guarantee that a concurrent agent's edit to the manifest shows up in the very next plan.

### `orchestrate brief`

Builds the worker package for one target without claiming it. Read-only for evidence, context and validation; it inserts the queue row only if the target has none, so run it on a target that is already in the queue to keep it fully read-only.

```bash
python3 tools/openspore.py orchestrate brief 0x008db310 --json --worker-id doc-example
```

Real fragments from that run:

```json
{
  "target": {
    "va": "0x008db310",
    "queue_va": "008db310",
    "queue_id": "fun:008db310:Resource::PFIndexModifiable::Write",
    "name": "Resource::PFIndexModifiable::Write",
    "subsystem": "Resource",
    "cluster": "resource-io"
  },
  "lease": {
    "implementer_id": "doc-example",
    "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
    "attempt": 1,
    "max_attempts": 3,
    "heartbeat_every_seconds": 600
  },
  "validation_requirements": {
    "baseline_status": "WARN",
    "required_categories": [
      "ABI", "CALLS", "GLOBALS", "FIELDS/OFFSETS", "CONSTANTS",
      "CONTROL FLOW", "VIRTUAL DISPATCH", "RETURN SEMANTICS", "EVIDENCE COVERAGE"
    ],
    "gate": "the orchestrator runs `openspore validate` on your candidate; only a static PASS may complete the target, and it never clears a runtime gate"
  },
  "evidence": {
    "state": "PERSISTED",
    "content_sha256": "ad44d0300541c6af575c53c7dbcb775f72d89f458543d8f7c1d40851f3c55fb4",
    "context_content_sha256": "c395f44308dca99a46c4db06a1e687ce9a8d6a9775c6881e2b62b47cb976a8aa",
    "missing_sections": [
      "DECOMPILATION",
      "DISASSEMBLY",
      "no persisted or live decompilation for this target"
    ]
  }
}
```

`--out PATH` writes the same document atomically and adds `path` to the result.

Note one honest gap: on the orchestrated path `frontier_reason.score` and `frontier_reason.reason_codes` are `null` and `[]`. The briefing reads `priority` and `reason_codes`, which live on the `swarm.decorate()` entry, while `plan()` hands `brief()` the classified record, which renamed them to `score` and dropped the reason codes. `frontier_reason.claim_state`, `runtime_gated` and `evidence_ready` are populated. A worker must not rely on the score being present.

### `orchestrate run`

```bash
python3 tools/openspore.py orchestrate run --limit 20 \
  --worker "opencode run --print-logs" \
  --worker-id orch-main \
  --max-workers 4 \
  --ttl 1800 \
  --timeout 3600
```

`--worker` is split with `shlex`, so it is a command plus its own flags; the worker is spawned once per target with no shell in between. The run output is `$schema: openspore-orchestration-run-1` with `status`, the full `plan` it executed, a `results` array sorted by VA, and a `summary`:

| `summary` key | Meaning |
|---|---|
| `targets` | results produced |
| `complete` | closed with `disposition: done` |
| `review_required` | released to `blocked` for a human |
| `blocked` | stopped on a bound, or the worker returned `BLOCKED` |
| `skipped` | the claim was lost to another orchestrator |
| `partial` | released to `queued` after a malformed or timed-out reply |
| `error` | an exception escaped `process_target` |
| `waves` | waves actually dispatched |
| `seconds`, `implementer_id`, `errors` | run metadata and any per-unit thread failures |

Each entry in `results` carries `va`, `queue_id`, `status`, `code`, `outcome`, `validation`, `attempts`, and an ordered `events` list recording every `claim`, `brief`, `launch`, `ingest`, `validate`, `checkpoint`, `close` and `release` the run performed on that target. The event list is the audit trail; read it first when a run surprises you.

`--dry-run` returns the plan with `dry_run: true`, an empty `results` array, and `summary.planned` set. It takes no lease, so it is the safe way to see what a run would dispatch.

Two flags matter for safety. `--allow-stale` is the only way to take a lease from a holder who has gone away, and it is per run, so use it deliberately. `--worker-id` is the lease holder identity; the orchestrator appends the scheduling unit to it, so one run holds `orch-main/scc-0064` rather than `orch-main` for a coordinated unit.

### `orchestrate reap`

Read-only. Lists the active leases so you can decide, and refuses to decide for you.

```bash
python3 tools/openspore.py orchestrate reap --json
```

Real output:

```json
{
  "$schema": "openspore-cli-result-1",
  "command": "orchestrate",
  "status": "ok",
  "ok": true,
  "source": { "requested": "persisted", "live": false, "mode": "persisted" },
  "result": {
    "active_leases": 0,
    "leases": [],
    "note": "report only; releasing a lease requires naming the holder with `orchestrate reclaim --allow-stale` or `release`",
    "status": "ok"
  },
  "warnings": [],
  "changed": false,
  "idempotent": true
}
```

With leases present, each entry has `id`, `va`, `implementer_id`, `updated_at`, `stage` and `attempts`. `updated_at` is the lease clock: compare it against the TTL yourself before deciding a lease is dead.

### `orchestrate reclaim`

Takes over one named row whose lease is stale.

```bash
python3 tools/openspore.py orchestrate reclaim 0x008db310 --worker-id recovery-1 --ttl 1800 --allow-stale
```

Without `--allow-stale` this is exactly `claim`, and it will be refused with `already_claimed` if the lease is still live. With it, the takeover succeeds only if the clock really is past the TTL, and the displaced holder is written into `checkpoint.lease_history`. The result is the `queue_op claim` document: `claimed`, `idempotent`, `id`, `investigation`, and `displaced_owner` when a takeover happened.

### `claim` and `release`

```bash
python3 tools/openspore.py claim 0x008db310 --worker-id worker-7 --ttl 1800
python3 tools/openspore.py claim 0x008db310 --worker-id worker-7 --ttl 1800 --allow-stale --allow-blocked
python3 tools/openspore.py release 0x008db310 --worker-id worker-7
python3 tools/openspore.py release 0x008db310 --worker-id worker-7 --to blocked --reason validation_warn
```

`claim` inserts the row first if the target has none, then claims it. Flags: `--ttl` (default 1800), `--allow-stale`, `--allow-blocked`. `release` flags: `--to {queued,blocked}` (default `queued`) and `--reason`, which is recorded only when releasing to `blocked`.

The results are the `queue_op` documents described above: `claimed` / `idempotent` / `id` / `investigation` for `claim`, and `released` / `idempotent` / `to` / `previous_status` for `release`. On refusal the CLI raises, so you get the error envelope with `code` (`already_claimed`, `not_owner`, `already_completed`, `blocked`, `stale_binary`, `invalid_params`) and a nonzero exit rather than a success document.

Do not run these against the shared database while another agent owns the queue. They are the same operations the orchestrator performs, and taking a lease by hand is indistinguishable from a worker that went rogue.

### `worker-template`

```bash
python3 tools/openspore.py worker-template 0x008db310
```

Real output:

```json
{
  "$schema": "openspore-worker-template-1",
  "status": "ok",
  "result": {
    "schema": "openspore-worker-result-1",
    "va": "0x008db310",
    "outcome": "STILL_UNKNOWN",
    "summary": "",
    "normalized_symbol": "opaque_008db310",
    "reconstructed_symbol": "reconstruct_008db310",
    "source_files": [],
    "types": [],
    "observed_mechanics": [],
    "semantic_findings": [],
    "unresolved_questions": [],
    "evidence_refs": [],
    "implementer_id": null,
    "queue_id": null
  },
  "outcomes": ["IMPLEMENTED", "PARTIAL", "STRUCTURAL_ONLY", "STILL_UNKNOWN", "BLOCKED", "FAILED_VALIDATION"],
  "verdicts": ["PASS", "WARN", "FAIL", "UNKNOWN", "NOT_AVAILABLE"],
  "rules": [
    "Evidence only. Never invent a constant, offset, vtable slot, or name.",
    "If the evidence does not support a claim, report STILL_UNKNOWN; that is a correct answer, not a failure.",
    "Do not commit, do not modify tools/mcp/**, and never touch another worker's staging package or metadata record.",
    "x86-32 only. The reconstructed symbol must embed the 8-hex target VA so the validator can locate the span.",
    "Write candidate source under reconstruction/staging/<your-package>/; the integrator promotes it to src/ after review.",
    "Emit exactly one JSON document matching openspore-worker-result-1 on stdout. The document is the result; prose around it is ignored."
  ]
}
```

## Writing a real worker

### The stdin/stdout contract

An external worker command is an argv list. It gets exactly one JSON document on stdin (the canonical briefing) and must write exactly one JSON document on stdout (the result). No shell, no interpolation, no positional arguments, no environment contract other than `OPENSPORE_WORKER_BRIEFING=1`, which `launch()` sets as a default. The child's working directory is the one the caller passed, and its stderr is captured and truncated to the last 2000 bytes for diagnostics.

A minimal working worker:

```python
#!/usr/bin/env python3
"""Minimal external worker: read the briefing on stdin, emit one result document."""
import json
import sys

briefing = json.load(sys.stdin)
va = briefing["target"]["va"]
sys.stdout.write(json.dumps({
    "schema": "openspore-worker-result-1",
    "va": va,
    "outcome": "STILL_UNKNOWN",
    "summary": "no persisted decompilation; nothing claimable",
    "source_files": [],
    "observed_mechanics": [],
    "unresolved_questions": ["where is the persisted decompilation for %s?" % va],
    "evidence_refs": briefing["evidence"]["refs"][:1],
}, sort_keys=True))
```

Its real reply, and the real ingest result, for the `0x008db310` briefing above:

```json
{"evidence_refs": [".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c"], "observed_mechanics": [], "outcome": "STILL_UNKNOWN", "schema": "openspore-worker-result-1", "source_files": [], "summary": "no persisted decompilation; nothing claimable", "unresolved_questions": ["where is the persisted decompilation for 0x008db310?"], "va": "0x008db310"}
```

```json
{
  "accepted": true,
  "outcome": "STILL_UNKNOWN",
  "raw_sha256": "613d0e72b7225a3d0c33b55c941f5abcfebbebb6cacfd5fd6cb82e8f98b81a8d"
}
```

The recorded `va` is `0x008db310` and the recorded `queue_id` is `fun:008db310:Resource::PFIndexModifiable::Write`, both taken from the orchestrator's claim, not from the payload.

### Wiring an agent launcher: the two gates

`orchestrate.agent_argv(briefing, command="opencode", model=None)` is the reference launcher shape. It is a pure function, which is what makes the launch path testable without asserting anything about model output. Two gates:

1. **argv is always a list, never a shell string.** `launch()` calls `subprocess.run(argv, ..., check=False)` with no `shell=True`. If you build a command line, split it once with `shlex.split` at the boundary and pass the list down. Nothing downstream is allowed to re-join it. A worker id, a package name or a briefing field that reaches a command line is a shell-injection risk the moment somebody re-joins it.

2. **The briefing travels as data, not as a prompt fragment.** The authoritative channel is stdin: `launch()` writes `canonical_json(briefing)` to the child. `agent_argv()` additionally appends a human-readable Markdown rendering of the same package as the final argv element, and the rendering is deliberately not the only channel. Because that rendering is inlined into argv, it is subject to the single-argument length limit; if a briefing can exceed it, have the worker read the stdin JSON, or write the briefing to a file and pass the path as a flag. Do not truncate the data channel to fit a convenience one.

Wire it like this:

```python
from tools.reconstruction_tooling import orchestrate as orch

worker = orch.command_line(
    None,                                   # unused; the argv is fixed per run
    ["opencode", "run", "--print-logs"],    # argv list, never a string
    implementer_id, cwd=ROOT, timeout=3600)
```

or, for a launcher that builds argv per briefing:

```python
worker = orch.subprocess_worker(
    argv_builder=lambda package: orch.agent_argv(package, command="opencode"),
    cwd=ROOT, timeout=3600)
```

In-process workers are also supported and are the fastest way to test a lifecycle: `orch.callable_worker(fn)` wraps any `package -> dict` function, and `orch.run(worker=..., dry_run=True)` shows you the plan without taking a lease.

## Operational cautions

- **The lease TTL is not the worker timeout.** `LEASE_TTL` is 1800 and the worker timeout is 3600. A worker that runs for longer than the TTL without a checkpoint writes will have its target stolen by anything that claims with `allow_stale`. A worker that legitimately needs more than 1800 seconds must checkpoint at least every 600. For a genuinely long job, raise `--ttl` rather than lowering the heartbeat interval.
- **Do not hand-release another worker's lease.** `release` is refused with `not_owner`, which is the correct outcome, but the reflex response should be `orchestrate reap` to see the clock, not `release --worker-id` with a borrowed identity. Borrowing an identity defeats the entire lease design and makes the `lease_history` displacement record wrong.
- **Do not run `orchestrate run` against the shared database while another orchestrator is active.** The claim CAS makes it safe: you will never double-own a row, and the loser of a race gets `skipped`. What you will not avoid is contention. Two orchestrators will compete for the same top-scoring targets, and the wave boundaries do not stop both from picking the same one. For a second run against a live queue, prefer a distinct `--worker-id` and accept a lower hit rate, or run against an isolated database via `OPENSPORE_DB`.
- **`plan()` costs about a second.** It rebuilds the canonical projection on every call instead of reading the generated index, so the plan is always current and never stale. Do not call it in a tight loop; call it once per run, and cache the document.
- **The frontier is repository-derived.** `frontier`, and therefore `plan()`, reads the manifest, the triage queue, the xref export and the SQLite claims. A concurrent agent editing the manifest or the triage queue changes the plan between two calls, so a plan you printed five minutes ago is not the plan you will execute. Re-read it, and treat a `queue_id` from an old plan as a hint rather than a guarantee. The plan does re-verify the row before claiming, so a stale id fails cleanly rather than corrupting a row.
- **`orchestrate brief` can insert a queue row.** Use it on a target that is already in the queue, or via `swarm` / `plan` output, if you want a strictly read-only inspection.
- **Terminal rows are permanent.** `done` and `dropped` are never deleted and never rewritten. They are the dedup memory that stops a function being reconstructed twice for the same build. A target closed by mistake is corrected with an explicit new row under a new `binary_sha256`, not by editing the closed one.
- **The Python version matters for subprocess workers.** `launch()` hands `subprocess.run` the canonical briefing as a `str`. Python 3.13 and newer require `bytes` there, and a `str` raises `TypeError` before the child is spawned. That `TypeError` is not one of the exception types `process_target` catches, so it escapes to the per-unit thread handler and the target simply produces no result. If you are wiring a subprocess worker, confirm `launch` round-trips on your interpreter before relying on it; passing the briefing to `launch` as encoded bytes works.
