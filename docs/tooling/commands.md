# Commands

All commands accept `--json` after the command and return one JSON document on stdout. Errors retain a nonzero exit code and a machine-readable error envelope.

## `frontier`

```bash
python3 tools/openspore.py frontier --json --limit 20
python3 tools/openspore.py frontier --unclaimed --dependency ready --runtime none
```

Filters: `--package`, `--subsystem`, `--status`, `--semantic`, `--dependency`, `--runtime`, `--claimed/--no-claimed`, `--unclaimed`, `--gameplay`, `--limit`, and `--offset`.

Each target contains score components, dependency endpoints, disposition, claim state, evidence references, and reason codes.

## `evidence`

```bash
python3 tools/openspore.py evidence 0x00e5b790
python3 tools/openspore.py evidence 0x00576c50 --json --no-write
python3 tools/openspore.py evidence 0x00e5b790 --live --json
```

Default output writes `reconstruction/evidence/<va8>/evidence.json` and `evidence.md`. `--no-write` keeps the operation ephemeral. Live failures are recorded as live attempts and do not become live evidence.

## `context`

```bash
python3 tools/openspore.py context 0x00e5b790 --json
```

The command writes `context.json` and `context.md` in the same evidence directory. The brief always includes all 15 sections, including explicit missing/conflicted states.

## `recover`

```bash
python3 tools/openspore.py recover 0x00576c50 --json
```

Recover is evidence → context → validation. It does not claim a target, alter source, or update replacement status. Rerunning replaces only deterministic generated artifacts for the same target.

## `validate`

```bash
python3 tools/openspore.py validate 0x00e5b790 --json
```

Validation reports `ABI`, `CALLS`, `GLOBALS`, `FIELDS/OFFSETS`, `CONSTANTS`, `CONTROL FLOW`, `VIRTUAL DISPATCH`, `RETURN SEMANTICS`, coverage, and unresolved questions. `EVIDENCE COVERAGE` is a measurement rather than a per-target verdict: it is reported outside the check table and contributes only its `NOT_AVAILABLE` floor to the aggregate. The two axes are independent — a static warning is not runtime validation, and `runtime: GATED` is an open capability gate, not a runtime failure. What each status means, and what evidence a `PASS` requires, is specified in [validation-dimensions.md](validation-dimensions.md).

## `integrate`

```bash
python3 tools/openspore.py integrate status --json
python3 tools/openspore.py integrate check --json
python3 tools/openspore.py integrate apply --json
```

`check` regenerates in memory and compares generated projections. `apply` writes through the existing atomic writer and is the only integrating command.

## `promote`

```bash
python3 tools/openspore.py promote plan pkg-property-remove-006a2ef0
python3 tools/openspore.py promote plan pkg_property_remove_006a2ef0 --json
python3 tools/openspore.py promote apply pkg-property-remove-006a2ef0 --json
python3 tools/openspore.py promote apply pkg-argscript-formatparser-setflag --va 0x0067e6f0 --overwrite
python3 tools/openspore.py promote apply pkg-direct-property-copyfrom-wave14 --no-build --no-ctest
python3 tools/openspore.py promote apply pkg-argscript-createdefsafe-00841440 --rebuild --json
```

`plan` is read-only and reports, per target, the staged files, the two validation statuses, whether the installed tree is already exactly this promotion, and every blocker code. `apply` promotes a package only when `static == "PASS"` and `runtime == "GATED"` compose, and installs all-or-nothing per package: the exact bytes are built and ctest-ed in a scratch tree that no discovery path can see, and only a green gate moves them into `src/reconstruction/<pkg>/`. A red configure, compile or test leaves `src/` untouched. The provenance side, `reconstruction/evidence/<va8>/promotion.json`, records the build verdict that `satisfy` later reads.

`--va` restricts the run to named targets, `--overwrite` applies over a drifted installed package, `--rebuild` re-gates a package that is already promoted and byte-identical (by default it is left alone and its recorded verdict is returned), and `--no-build` / `--no-ctest` skip a step of the gate. `apply` has no dry-run mode: `--no-write` is refused with exit code 2 and `plan` is the verb that does not write. A refused package does not block an admissible sibling, and the command still exits 0 with a `apply_ok_with_refusals` warning — every named target was adjudicated, and `result.refused` says why each refusal happened.

## `satisfy`

```bash
python3 tools/openspore.py satisfy plan 0x01021370
python3 tools/openspore.py satisfy plan --json
python3 tools/openspore.py satisfy apply 0x00b3d400 0x00b3d600 --json
python3 tools/openspore.py satisfy apply 0x00b3d400 --reason "model test green" --dry-run
python3 tools/openspore.py satisfy apply 0x00b3d400 --verify-build --json
```

`satisfy` is the only sanctioned way for a promoted VA to stop being an open callee. `plan` reports, per VA, the `src` package that promotes it, the two validation statuses, the current derived status, whether the scheduler still needs it satisfied, the dependents that are deferred on it, and every blocker code. `apply` writes `body_status` and `integration_status` to `integrated` in the canonical manifest, extends `source_files` with the promoted sources, and appends one `change_log` entry holding the prior statuses — nothing else. It then calls `integrate apply` to regenerate the projection and drops this root from the in-process index cache.

A VA is refused, and its manifest entry left untouched, unless all of these hold: a `src/reconstruction/<pkg>/promotion.json` exists whose target is `static_status == "PASS"` and `runtime_status == "GATED"`; that target lists a test translation unit; `reconstruction/evidence/<va8>/promotion.json` exists; the build verdict recorded there is `ok: true` **and** carries at least one step (a skipped gate is not a green gate, and the absence of a recorded failure is never a pass); and the manifest has a `functions[]` entry for the VA. `--verify-build` additionally re-runs the build gate on the installed package instead of trusting the recorded verdict.

The runtime axis cannot leak: the write touches no runtime key, `status_for` returns `reconstructed` rather than a runtime state, and the VA stays runtime-`GATED` by the absence of `runtime.validated` in the projection. A re-run over an already satisfied VA writes nothing (`changed: false`, `idempotent: true`), and the manifest is written through the canonical atomic writer, so an interrupted run leaves a valid manifest that can be re-run.

## `swarm`

```bash
python3 tools/openspore.py swarm --json --limit 5
python3 tools/openspore.py swarm --json --limit 5 --out /tmp/openspore-plan.json
```

Swarm emits only eligible targets with dependencies, evidence readiness, claimability, and reason codes. It does not launch OpenCode or acquire claims.

## `orchestrate`

```bash
python3 tools/openspore.py orchestrate plan --limit 5 --json
python3 tools/openspore.py orchestrate brief 0x008db310 --json --worker-id worker-7
python3 tools/openspore.py orchestrate run --limit 20 --worker "opencode run --print-logs" --worker-id orch-main
python3 tools/openspore.py orchestrate run --limit 20 --worker "opencode run --print-logs" --worker-id orch-main --dry-run
python3 tools/openspore.py orchestrate run --limit 20 --worker "opencode run --print-logs" --worker-channel argv --worker-id orch-main
python3 tools/openspore.py orchestrate reap --json
python3 tools/openspore.py orchestrate reclaim 0x008db310 --worker-id recovery-1 --allow-stale
```

`plan` is read-only and returns the dispatch plan: every classified target with its scheduling role, and the dependency waves. `brief` assembles the worker package for one target without claiming it. `run` executes the pipeline, dispatching one worker per dispatchable unit, concurrently within a wave and in wave order across waves. `reap` lists active leases and decides nothing. `reclaim` takes over one named row whose lease has gone stale, and only with `--allow-stale`.

`--worker` is the worker command, split once with `shlex` and spawned without a shell; the briefing arrives on stdin and the result is read from stdout. `--worker-id` is the lease holder identity and is required for `run`. `--max-workers`, `--ttl`, `--timeout` and `--allow-stale` bound the run. `--dry-run` returns the plan without taking a lease.

### Child sessions (the primary transport)

A reconstruction worker is a **native child session of the orchestrating agent session**. The orchestrating session spawns the children and hands their replies back; the tooling hands out a plan, hands out one brief per target, and reads the children's final messages back as if they were a subprocess's stdout. The `opencode run` subprocess path above is the escape hatch for a worker that is a command you spawn.

```bash
# 1. which targets, and what static evidence each one has -- claims nothing
python3 tools/openspore.py orchestrate session-plan --limit 8 --json --out /tmp/plan.json
# 2. one document per target, for one child session each -- claims nothing
python3 tools/openspore.py orchestrate session-task 0x008db310 --worker-id orch-main --json --out /tmp/task.json
# 3. (outside this repo) spawn the child sessions; write each child's FINAL
#    message verbatim to <replies>/008db310.txt
# 4. the whole lifecycle over those replies -- this is where the claim happens
python3 tools/openspore.py orchestrate session-run --replies /tmp/openspore-replies --worker-id orch-main --limit 8 --json
```

`session-plan` reports, per target: `va`, `queue_id`, `name`, `package`, `subsystem`, `cluster`, `role`, `reason`, `dispatchable`, `priority`/`score`, `open_callees`, `claim_state`, `scc`, `evidence_level` and `expected_static_evidence` — whether an evidence pack is persisted and verifies, whether a complete untruncated listing exists, and whether a source span resolves. It reports **evidence availability, never a predicted verdict**: whether the checks then agree is a question for `validate`, against a candidate that does not exist yet. The plan is byte-identical for a given root and claims nothing; `--va` narrows the batch and `--include-deferred` also schedules frontier-deferred targets, which is what makes a later wave visible.

`session-task` is the whole brief for one child session: the full `briefing` package, the `prompt_markdown` digest, the `result_contract`, a contract-valid `result_template` to fill in, `write_under` / `metadata_sidecar`, and `reply_format`. It claims nothing and writes nothing.

`reply_format` is the transport contract: the child's FINAL message is the authoritative answer and must end with the result object in a single fenced ` ```json ` block with **nothing after the closing fence**. The parser reads the **final** text block when a reply carries several. A reply with **no** result object is discarded and retried. The reply text reaches `parse_result` unchanged — the same strict contract a subprocess worker answers, with no added leniency.

Reply files are named `<va8>.txt` (the bare 8-hex queue spelling of the VA) and are read **lazily at call time**, so a reply may land after the plan that named the target. A consumed reply is **popped**: a second call for the same VA reports `absent` and produces the existing `worker produced no output` refusal, because **a retry is a new child session, not a re-read of the last one**. Producing a further reply means spawning another child session and writing another `<va8>.txt`.

`session-run` is `run()` with the child-session adapter in place of a launcher — the same disposition loop, the same bounds, the same compare-and-set. `summary.worker_channel` is `native-session` and every `launch` event carries `channel: "native-session"`, `transport: "child_session"` and `source` (`reply_dir`, `reply_map` or `absent`), so a run's own output proves which transport produced it.

### The two validation axes in a run summary

Alongside `complete` / `review_required` / `blocked` / `skipped` / `partial` / `error`:

| Key | Meaning |
|---|---|
| `static_validated` | closed on a **STATIC** `PASS` of a terminal outcome — the reconstruction was accepted against the binary |
| `runtime_validated` | the **RUNTIME** axis is `PASS` — the original process was observed. This is `0` |
| `runtime_gated` | the RUNTIME axis is `GATED`: a gate is open, nothing was attempted, nothing failed |

`runtime_validated` is `0` because `RUNTIME: PASS` requires the canonical record to report `runtime.validated > 0`, which no record in this repository does. **A static `PASS` never contributes to it** — a closure is a claim about the reconstruction, not an observation of the original process. Each record carries the same pair as `static_validation` and `runtime_status`, and the runtime axis whole under `runtime` (`status`, `validated`, `gated`, `gates`) so the `0` can be checked rather than taken on trust.

A `blocked` target inside a successful batch is a per-target disposition, not a failed command: `session-run` reports the batch outcome at the top level, adds a `batch_ok_with_blocked_targets` warning, and leaves every per-target status exactly as the lifecycle produced it. A batch with an `error` or `partial` target is `ok: false` with `code: batch_not_adjudicated`; a run that dispatched nothing is `code: no_dispatchable_targets`.

The human (`--format human`) rendering of `orchestrate` reads the document's own `$schema` to decide what to print, so `plan`, `brief`, `reap` and `reclaim` still print the full JSON document exactly as before, `session-plan` prints one line per target with its evidence availability, `session-task` prints the briefing digest plus the reply format, and a run prints the counters with the two validation axes and the transport. A `--dry-run` prints `dry_run: planned=N (no lease was taken)` instead of the full document.

### Worker channels (the subprocess escape hatch)

A `--worker` that names `opencode` is **not** run verbatim. It is routed through the deterministic JSONL channel, so the command that actually runs is:

```bash
opencode run "<briefing digest>" --print-logs --format json
```

`--format json` is the contract, not a preference: with `--format default`, OpenCode concatenates every assistant text block into stdout, so a worker that narrates before it uses a tool answers with a blob that is not a JSON document. The routing rule, in full:

| `argv[0]` | `--format` present | route |
|---|---|---|
| `opencode` / `opencode.exe` (any path) | no | `opencode_worker`, forced `--format json` |
| `opencode` | yes | `command_line`, verbatim — the operator already chose |
| anything else | no | `command_line`, verbatim |
| anything else | yes | `command_line`, verbatim |

`--worker-channel` overrides the table, and `OPENSPORE_WORKER_CHANNEL` does the same for a fleet that cannot pass a flag:

| value | effect |
|---|---|
| `auto` (default) | the table above |
| `jsonl` | the deterministic adapter is required; a `--worker` that is not `opencode` is an error (`worker_channel_unsupported`) |
| `argv` | always verbatim argv, the escape hatch for an arbitrary worker |

Any other value fails with `worker_channel_invalid` rather than silently disabling the structured channel. Whatever was chosen is reported in the run: `summary.worker_channel` (`native-session` for a child session, or `opencode-jsonl`, `argv-passthrough` or `custom`), `summary.worker_route` with the reason, `summary.worker_transport` where the worker names one, and `failure`/`channel`/`transport` on every `launch` event.

## `claim`

```bash
python3 tools/openspore.py claim 0x008db310 --json --worker-id worker-7
python3 tools/openspore.py claim 0x008db310 --json --worker-id recovery-1 --ttl 1800 --allow-stale --allow-blocked
```

`claim` inserts the investigation row if the target has none, then takes an atomic lease through the canonical `queue_op`. The lease is `implementer_id` plus `updated_at`; the TTL is 1800 seconds by default with a floor of 60. A claim held by another worker is refused with `already_claimed` unless the lease is stale and `--allow-stale` was passed.

## `release`

```bash
python3 tools/openspore.py release 0x008db310 --json --worker-id worker-7
python3 tools/openspore.py release 0x008db310 --json --worker-id worker-7 --to blocked --reason validation_warn
```

`release` ends a lease without ending the investigation: the row returns to `queued`, or to `blocked` with the recorded reason. It is refused with `not_owner` when the caller is not the lease holder, because a lease is never taken by releasing it. Releasing a row that is not `active` is a success no-op, so a retried sequence converges.

## `worker-template`

```bash
python3 tools/openspore.py worker-template 0x008db310
```

Prints the `openspore-worker-result-1` skeleton with the six outcomes, the five validation verdicts, and the worker rules, so a worker never has to guess the field names. A natural-language final message is not parsed; the worker must emit exactly one JSON document on stdout — for a subprocess worker, on stdout; for a child session, in the final fenced block of its FINAL message. `orchestrate session-task` embeds the same template per target, already filled with that target's `va`, `implementer_id` and `queue_id`.
