# ORCHESTRATOR — Sequential RE investigation workflow as a queue + state machine (Subagent 4)

Dense spec for how opencode (the orchestrator) drives the 7-stage pipeline
(`docs/RE-WORKFLOW.md`) over the Subagent-3 MCP surface (`docs/analysis/MCP-DESIGN.md`,
20 tools) with exactly ONE worker subagent at a time. Grounding:
`docs/analysis/SCALABILITY.md` state-persistence table, `docs/replacement-boundaries.md`
§3/§5, `docs/STATE.md` §4–§6. Every mechanism maps to an existing file/tool/MCP tool;
the four genuine gaps are marked **NEW** (§13).

---

## 1. Task queue

**Home: a table `investigations` inside the existing `knowledgegraph/spore.db`**
(git-ignored, `*.db` in `.gitignore`, rebuilt by `knowledgegraph/seed_sprint.py` per
SCALABILITY Q4.5 / state row #2: "Table in `spore.db` (label `Investigation`), seeded
from the 1670 SDK functions"). A dedicated table (not `nodes` with `label='Investigation'`)
because `schema.sql` has no timestamps and one REAL `confidence` (SCALABILITY Q4.3/Q4.5),
and the queue needs per-stage attempt counters + a checkpoint blob. `kg.py` owns the
schema; `schema.sql` gains the table below (**NEW** item 1, in scope of SCALABILITY row #2).

```sql
CREATE TABLE IF NOT EXISTS investigations (
  id             TEXT PRIMARY KEY,   -- 'fn:0x00e5b790:MovePlayerToMousePosition' | 'sub:resource-manager-full'
  kind           TEXT NOT NULL,      -- 'function' | 'subsystem'
  va             TEXT,               -- hex, image-base-relative for functions; NULL for subsystem
  name           TEXT,
  subsystem      TEXT,              -- 'sub:cell-movement' style (replacement-status.json key)
  mode           TEXT NOT NULL,     -- 'replace' | 'understand'
  why_interesting TEXT NOT NULL,
  stage          TEXT NOT NULL,     -- vocabulary of §2; QUEUED when status='queued'
  status         TEXT NOT NULL,     -- 'queued' | 'active' | 'blocked' | 'done' | 'dropped'
  block_reason   TEXT,              -- 'approval_required:<tool>' | 'escalated' | 'ghidra_offline' | 'no_spo' | 'machine_locked'
  prerequisites  TEXT,              -- JSON: [task ids or gate keys from replacement-status.json]
  attempts       TEXT,              -- JSON: {stage: count}
  checkpoint     TEXT,              -- JSON, §11
  evidence_refs  TEXT,              -- JSON: [artifact paths + KG node names], §5
  implementer_id TEXT,              -- worker id that last did REPLACE/STATIC work
  adjudicator_id TEXT,              -- worker id that authored the adjudication record (§4)
  created_at TEXT, updated_at TEXT,
  binary_sha256 TEXT NOT NULL      -- the build this record applies to
);
CREATE UNIQUE INDEX IF NOT EXISTS ix_inv_dedup
  ON investigations (kind, va, binary_sha256);   -- the dedup key, §3
```

Seed: generated section in `seed_sprint.py` from the 1670 SDK function addresses
(`ImportSporeSDK.java` output) + the 18 `replacement-status.json` subsystems; the one
completed case (cell-movement) is seeded `status='done'`, `stage='RECORDED'` — that row
IS the permanent "already investigated" record.

**Invariants**
1. `UNIQUE(kind, va, binary_sha256)` — one record per function per build.
2. At most ONE row `status='active'` (enforced by the orchestrator; re-checked at
   startup, §11).
3. A row is inserted only by the orchestrator (dedup check, §3); workers may propose
   insertions (§6), the orchestrator executes them.
4. `binary_sha256` ≠ current build hash (from `pipeline_state`) ⇒ row is **stale**:
   not dropped, parked `queued` with flag; dossier/snapshot for it must be
   `dossier_regenerate`d / `ghidra_snapshot_save`d against the new build first
   (caches miss automatically, MCP-DESIGN §D).
5. `done`/`dropped` rows are never deleted — they are the dedup memory.

## 2. Stage state machine (one target)

Stages: `QUEUED → SELECTED → DOSSIER → STATIC → [RUNTIME] → ASSETS → CONTRACT →
REPLACE → VALIDATE → RECORDED`, plus orthogonal `BLOCKED` and terminal `DROPPED`.

Per stage: entry condition / actions (MCP tool #) / exit condition / artifact written
on exit (the stage is "done" only when the artifact exists AND is in `evidence_refs`,
§5).

| Stage | Entry | Actions | Exit → artifact |
|---|---|---|---|
| SELECTED | picked by orchestrator (§10) | build function card (`ghidra_function` #9, `dossier_read` #6, `vtable_lookup` #14, `trace_status` #17) | card in task record |
| DOSSIER | card built | `ghidra_snapshot_save` #11 (if none), `dossier_regenerate` #7 | `docs/analysis/dossiers/<topic>.{json,md}` with readiness |
| STATIC | dossier exists | `ghidra_decompile` #8 for target + needed callees (into snapshot fn list), byte-verify at `file_off = linked − 0x400C00` (RE-WORKFLOW §2) | `tools/re/data/ghidra_snapshot_<topic>.json` + `tools/re/data/decompiled/<Name>.c` (EVIDENCE-NOT-TRUTH headers) |
| RUNTIME | runtime gate present for the subsystem (gate table §10) | `trace_run` #15 (approval-gated) → `trace_analyze` #16 → `kg_record` #5 Observation (incl. negative result, §8) | run manifest `{binary_sha256, probes_file_sha256, wine_version, xdotool, captured_at, events_total, jsonl_path}` + JSONL (+ committed example if representative) |
| ASSETS | runtime done or skipped | `asset_resolve` #12 / `asset_scan` #13 → `kg_record` #5 AssetRecord (rejection is a legal outcome — building stand-in precedent, STATE.md Obj34) | dossier asset section updated (regenerated) + KG records |
| CONTRACT | assets resolved/rejected | write contract doc (`docs/<TOPIC>-CONTRACT.md` pattern of `docs/CELL-CONTRACT.md`), `fixture_check` #20 (identity) | contract doc + `tests/fixtures/<topic>/fixtures.json` |
| REPLACE | **guard: dossier + snapshot + contract all in `evidence_refs`** | implement `src/replace/*` + Reference transcription + diff test (`src/replace/tests/diff_test.cpp` pattern) | replacement code + `docs/<TOPIC>-ABI.md` + `docs/<TOPIC>-DIFF.md` (table with evidence boundary stated up front) |
| VALIDATE | diff doc exists | **adjudication**: fresh worker id runs `test_run` #18 + `fixture_check` #20 (+ `trace_analyze` where the gate needs live evidence); writes KG `Adjudication` node `origin=adjudicator_id` | adjudication record `{verdict, test names, evidence_refs, origin}` |
| RECORDED | adjudication passes | `status_update` #19 (HUMAN approval) → `kg_record` #5 → `docs/STATE.md` + devlog chapter | `docs/replacement-status.json` entry (evidence-labeled, 9-level vocab) |

**Branch (understand-only).** `mode='understand'` tasks may exit at DOSSIER (if the
dossier fully answers the question) or after STATIC (if decompilation was needed);
both are legal → RECORDED via `kg_record` only (no status_update — nothing is replaced).
A `replace` task may NOT terminate before VALIDATE.

**RUNTIME skip rule.** `STATIC → ASSETS` is legal only if the gate table shows no
runtime `missing_evidence` for the target's subsystem **and** `trace_status` #17
shows no existing trace already covers the target's probes. A trace run that FAILED
(stall / 0 events) does NOT leave RUNTIME open: the negative result is recorded as
evidence (the 9-run precedent, `docs/analysis/CELL-RUNTIME-OBSERVATION.md`) and the
stage is done. Only `approval_required` parks the task (→ BLOCKED, §8).

**Legal transitions (the ONLY edges)**

```
QUEUED→SELECTED          orchestrator pick; guard: deps done, binary match, not stale
SELECTED→DOSSIER         dedup re-check passed
DOSSIER→STATIC           dossier artifact written; guard: mode=replace ∨ needs_static
DOSSIER→RECORDED        guard: mode=understand ∧ findings in KG
STATIC→RUNTIME          snapshot+decompiled committed; guard: runtime gate present
STATIC→ASSETS           guard: no runtime gate ∨ existing trace covers probes
RUNTIME→ASSETS          manifest + analysis + Observation recorded (negative ok)
RUNTIME→BLOCKED         approval_required on trace_run
ASSETS→CONTRACT         asset section resolved/rejected
CONTRACT→REPLACE        contract+fixtures; guard: dossier ∧ snapshot in evidence_refs
REPLACE→VALIDATE        diff doc + impl + reference committed
VALIDATE→RECORDED       adjudication by different worker + status_update executed
VALIDATE→BLOCKED        status_update awaiting human approval (park, no attempt burn)
<stage>→BLOCKED         approval_required / attempt cap (§9) / machine_locked / no_spo / ghidra_offline
BLOCKED→<stage>         human resolved / server back / lock free; attempt counter reset only on human resolution of an escalation
<stage>→DROPPED         explicit user decision; record kept (dedup memory)
RECORDED→(terminal)
```

Any edge not listed is forbidden. In particular: no path reaches REPLACE without
DOSSIER+STATIC+CONTRACT artifacts, and no path reaches RECORDED (replace mode) without
VALIDATE with an independent adjudication (§4).

## 3. Duplicate-work prevention

Dedup key: `(kind, va, binary_sha256)` — VA, not name (names drift across SDK import
versions; VA + build is the stable identity; subsystems key on their
`replacement-status.json` name). A function is re-investigated under a NEW build (EP1)
as a new row; the old row stays `done`.

Three enforcement points:
1. **`target_select` #2 refuses**: never returns a target with an existing row
   (`done`/`blocked` with a dossier) — MCP-DESIGN §C#2 built-in.
2. **Queue insert refuses**: `INSERT OR IGNORE` on `ix_inv_dedup`; a collision returns
   the existing record instead of inserting.
3. **Dossier topic naming**: topic = slugified subsystem name (one dossier per
   subsystem; `dossier_read` #6 on a missing topic returns the available topics).

Machine check ("this function was already investigated — here's its record"):

```
row = queue_op get kind=function va=<VA> binary_sha256=<current>
if row: emit {id, stage, status, evidence_refs, block_reason}   # do not re-investigate;
           # if more is needed, that is a NEW question → new subsystem-level row, never a duplicate fn row
```

## 4. No self-verification (hard invariant I4)

> **I4.** No worker marks its own hypothesis VERIFIED and no agent sets a replacement
> status. The worker PROPOSES (evidence + hypothesis + contract + diff table); an
> INDEPENDENT adjudication (separate subagent invocation, `origin` ≠ implementer)
> adjudicates via `test_run` #18 + `fixture_check` #20 (+ `trace_analyze` #16 where
> the gate demands live evidence); `status_update` #19 — human-approval-gated, the
> only writer of `docs/replacement-status.json` — is the only promotion path, and it
> enforces the evidence cap (decompilation reference ⇒ at most `replaced-approx`,
> per `docs/replacement-boundaries.md` §5.7; no trace manifest ⇒ never
> `replaced-verified`).

Mechanical enforcement (three locks, all existing machinery):
1. **Identity lock (state machine):** the queue row carries `implementer_id` (the
   worker that did REPLACE) and `adjudicator_id`. The orchestrator refuses
   `VALIDATE→RECORDED` unless `adjudicator_id ≠ implementer_id` AND the KG
   `Adjudication` node's `origin` attribute equals `adjudicator_id` (`kg_record` #5
   carries `origin` by design). Orchestrator assigns ids at spawn (`worker-7`,
   `worker-8`, …) and puts the id in the briefing; workers stamp artifacts with it.
2. **Approval lock (tool):** workers are never issued `approve=true` re-calls. Only the
   orchestrator re-calls a gated tool after explicit user sign-off, and only under
   `OPENSPORE_MCP_TRUSTED=1` (MCP-DESIGN §E — a misconfigured session cannot
   self-approve).
3. **Evidence lock (tool):** `status_update` #19 validates the `evidence` pointer
   against the 9-level vocab + evidence rule server-side.

Corollary: a worker's return message claiming "VERIFIED" is treated as a *proposition
for adjudication*, never as state.

## 5. Evidence-loss prevention

Every stage exit writes its artifact to the durable store listed in §2 BEFORE the
transition, and appends the ref to `evidence_refs` (queue row) + KG (`kg_record` #5).
A stage is done iff its artifact is readable from disk/KG with the right
`binary_sha256` pin. Committed artifacts: dossiers, snapshots, `decompiled/*.c`,
contract + fixtures, ABI + DIFF docs, `replacement-status.json`, trace manifests (+
committed example JSONLs per SCALABILITY row #10). `tools/mcp/cache/` decompilation
caches are git-ignored but binary-pinned, so a lost cache is a cost, not evidence loss.

**Briefing rule (no fresh guesses).** Workers are stateless subagent invocations; ALL
state flows through the briefing the orchestrator builds at spawn:

```
briefing = {
  task: full queue row (why, mode, stage, block_reason, attempts),
  function card: MCP-DESIGN §F shape (va, name, callers, callees, dispatch, subsystem,
                 gate, next_action),
  evidence_refs: ALL prior artifacts — the worker MUST dossier_read #6 / read snapshot /
                 read DIFF doc first and act from them,
  stage instructions: §2 row for the current stage only (entry/exit/artifact),
  worker id, machine-lock status, mode (supervised|unattended §12),
  rules: I4, §6 spawn bound, no status claims
}
```

Re-entering any stage (resume, retry, re-attempt) re-sends the same briefing — the
worker never "remembers"; the artifacts are the memory.

## 6. Uncontrolled-recursion prevention

**Spawn rule.** While investigating A, a worker that discovers B (callee/struct):
may (a) call `ghidra_function` #9 on B — metadata only, one call (name, size,
namespace, dispatch, callers/callees; memoized, ~0.5 s) — and (b) ENQUEUE B:
`queue_op` insert (`kind='function', va=B, why='discovered while investigating A'`,
`prerequisites=[A]`) + `kg_record` #5 edge `A —depends_on→ B`. The worker may NOT
advance B's stages: no `ghidra_decompile` #8 for B as *B's* stage work, no queue
`stage` update on B. (B's body may still be captured inside A's snapshot function
list — that is A's artifact, documented in the snapshot's list; B's *record* stays
queued.) Depth bound: one metadata level; discoveries-of-discoveries ride the queue.

**Concurrency: exactly ONE active task** — by construction (the orchestrator spawns
workers strictly one at a time) and by queue invariant 2.

**Higher-priority discovery mid-task.** The worker records it in `checkpoint.new_findings`
+ enqueues it; it completes the CURRENT stage to its artifact (no mid-stage abandonment);
the queue re-ranks at the next SELECTED (§10), so the priority shift takes effect at
the next stage boundary.

## 7. Machine lock (X display + GPU)

One lock, `flock` on `/tmp/openspore-machine.lock` (**NEW** item 4: file outside the
repo; `flock` in `observe.py`, in the `cell_stage --interactive` path, and around
GPU-bound ctest; kernel-released on process death, so there is no stale lock).

- **Acquirers:** `trace_run` #15 (observe.py), `cell_stage --interactive` smoke,
  GPU ctests (`triangle_smoke`, `asset_render`, `material_smoke`,
  `cell_stage_interactive_smoke`). Offscreen Vulkan takes the same lock — it is the
  same GPU; serialization costs nothing under the sequential model.
- **Protocol:** non-blocking `flock` + poll every 5 s for up to 90 s; on timeout the
  tool returns `{"ok":false,"error":"machine_locked","hint":"holder: <pid/label/ts from lock file>"}`
  (**NEW** error code) and the orchestrator parks the task `block_reason='machine_locked'`
  (no attempt burn — it is environmental, like `ghidra_offline`).
- **Human protection:** the documented human commands (STATE.md §4) are prefixed
  `flock /tmp/openspore-machine.lock -c "…"` so a human at the keyboard cannot
  desync a running trace or smoke run. Lock file body: `{pid, label, ts, task_id}`
  for diagnostics only.

## 8. Failure & blocking transitions

| Failure (error code) | Transition | Attempts |
|---|---|---|
| `ghidra_offline` | stage stays; task → `queued` (parked, `block_reason='ghidra_offline'`); orchestrator probes `pipeline_state` next loop and resumes | NOT incremented (infrastructure) |
| `no_spo` | degrade: `dossier_regenerate` #7 emits explicit `NOT OBTAINED` sections (its contract — never a failure, never a fabrication); stages that strictly need `SPORE/` (`asset_scan`, `trace_run`) → BLOCKED `no_spo` | not incremented for the degraded path |
| `approval_required` | → BLOCKED `approval_required:<tool>`; orchestrator surfaces `{what, cost, requires}` to the user; re-call `approve=true` (trusted env) on sign-off | NOT incremented |
| trace run FAILED (stall / 0 events) | the failure IS evidence: manifest + JSONL recorded, `kg_record` #5 Observation (negative, 9-run precedent), dossier regenerated with the runtime gap, RUNTIME → done → next stage. The *gate* stays open in `replacement-status.json` (that is the honest state: `replaced-approx`, pending trace) | incremented (a real attempt was spent) |
| worker crash mid-stage | resume from checkpoint (§11); checkpoint absent/incomplete → reset to last COMPLETED stage, fresh re-entry | the crashed attempt is counted only if its partial work left no artifact |
| `machine_locked` | park `block_reason='machine_locked'` | NOT incremented |

## 9. Retry & escalation

Per-stage attempt cap: **3** (counted in `attempts[stage]`). On cap: task → BLOCKED
`escalated` with a written escalation note `docs/analysis/escalations/<task-id>.md`
(**NEW** item 3, committed; trivial docs/ addition):

```
{task, stage, what_was_tried: [attempt summary ×3, evidence_refs of each failure],
 failure evidence (error codes / negative manifests), what_would_unblock: <one human action>,
 cost class: cheap|medium|operator-blocked}
```

Escalation is first-class: the orchestrator prints the `blocked` list (escalations
first) at the top of every loop. On user resolution, the orchestrator archives the note,
resets `attempts[stage]=0`, and re-enters the stage with a fresh briefing.

## 10. The orchestrator loop

```
startup (once):
  ps = pipeline_state()                      # #1 — binary_sha256, server liveness
  mark stale rows (invariant 4)
  for t in queue where status='active':      # §11 recovery — exactly one
      if t.checkpoint complete: resume from t.checkpoint.next_action
      else: reset to last completed stage; fresh briefing
  if machine lock held by non-orchestrator pid: note it (we will park, not fight)

loop:
  blocked = queue where status='blocked'
  if blocked: surface summary to user (approvals first: what/cost/requires; then escalations)
  if user signed off on any: re-call with approve=true (trusted env); unblock on ok
  cands = queue where status='queued' and not stale
  if cands empty:
      picks = target_select()                # #2 — dedup built in
      for p in picks: queue insert (dedup §3)   # only with a real why; cap intake at 5/loop
  t = rank(cands):
      1. fan-out: #subsystems whose gate lists this target's unlock_artifact
         (gate table = machine-readable {gate, unlock_artifact, cost, depends_on[]}
         inside docs/replacement-status.json — SCALABILITY row #7; read via pipeline_state #1;
         the cell-mode trace unlocks ≥4 — the known max)
      2. cost: cheap < medium < operator-blocked (same table)
      3. dependency-ready (prerequisites done); tie-break: oldest created_at
  set t active (invariant 2); briefing per §5
  spawn ONE worker subagent (worker-N)
  worker returns {stage_result, artifacts, evidence_refs, new_findings, approvals_needed?}
  verify: every claimed artifact exists on disk/KG with matching binary_sha256  # not the worker's word
  if worker requested a gated tool (approvals_needed):
      park t BLOCKED approval_required:<tool>; surface; continue loop
  elif artifact verified:
      advance t.stage per §2 table; write checkpoint; clear active
      if stage == RECORDED: t.status='done'
  on worker crash: §8 recovery
  repeat
```

**The orchestrator NEVER:** investigates (no `ghidra_decompile`/`dossier_regenerate`
for analysis — it only *verifies* artifact existence), marks anything VERIFIED or
promotes status (it executes `status_update` re-calls only as the human's decision,
§4 lock 2), skips a stage (the §2 table is the only path), runs two workers, or
advances a stage on a worker's unverified claim.

## 11. Checkpointing & crash recovery

Checkpoint (queue row `checkpoint`, JSON), written at every stage boundary:

```
{stage, stage_attempt, evidence_refs, last_action, next_action,
 new_findings[], worker_id, ts}
```

Stored in the queue row itself (spore.db — durable across opencode sessions; the
committed artifacts it points to are the real memory). Resume procedure (startup, §10):
for the one `active` task — `checkpoint.next_action` present AND `last_action`'s
artifact verified → resume mid-stage from `next_action` (re-briefed, §5); otherwise
reset `stage` to the last stage whose §2 artifact verifies, re-enter fresh. Never both.
Invariant re-asserted: at most one `active` after recovery.

## 12. Overnight-autonomy boundary

| Segment | Unattended-safe? | Why |
|---|---|---|
| SELECTED → DOSSIER → STATIC | **yes** | deterministic tools, no gates, no GPU (`dossier_regenerate` #7, `ghidra_snapshot_save` #11, `ghidra_decompile` #8 cached) |
| RUNTIME | **no** — human present | `trace_run` #15: approval + real X display + `wineserver -k` + menu navigation; ~30 s+; machine lock |
| ASSETS → CONTRACT | **yes** | metadata-only + `fixture_check` #20 identity mode (rebuild is the gated variant) |
| REPLACE → VALIDATE | **yes** | ctest `test_run` #18 (takes machine lock, serializes) + identity `fixture_check` + adjudication by second worker |
| RECORDED | **no** — human present | `status_update` #19 approval-gated |

**Supervised mode:** human at keyboard; every `approval_required` is surfaced
immediately; the human's sign-off is the `approve=true` re-call (trusted env).
**Unattended mode:** the same loop; at each approval gate the orchestrator writes the
park state (queue row BLOCKED + a `docs/STATE.md` §6 note "parked on <gate>, resume by
<one action>"), flushes everything (KG, checkpoints, artifacts committed), and idles —
the queue is resumable from cold start by §10 startup. An overnight run therefore
completes full dossiers/static/contract/replace/diff for every runtime-gate-free target
and stops cleanly at the trace and status gates.

## 13. NEW items (gaps in the Subagent-2/3 surface — all minimal)

1. `investigations` table in `knowledgegraph/spore.db` (schema via `kg.py`, §1) — SCALABILITY row #2 requires it; `kg_record` #5 covers KG nodes/edges/tests, not a queue.
2. **MCP tool #21 `queue_op`** `{op: list|get|insert|update|close}` over that table (kg.py pattern; git-ignored DB ⇒ no approval gate needed). The 20-tool surface has no queue writer; without it the orchestrator would shell out, and one tool keeps it on the MCP contract.
3. `docs/analysis/escalations/` — committed notes directory.
4. `flock /tmp/openspore-machine.lock` acquisition in `observe.py` + interactive/GPU test paths + documented human wrapper; `machine_locked` error code.

Everything else — queue reads via `pipeline_state` #1, intake via `target_select` #2,
artifacts via #5–#16/#18/#20, promotion via #19 — is exactly the Subagent-3 surface.
