# Track 03 — Mode State Axes

## Resolution

**Classification:** `preferred_claim_with_limit`

OpenSpore should not model App mode, Simulator mode, input mode, SpaceContext, scenario mode, and Cell lifecycle as one enum or one state machine. The minimum safe architecture is:

1. An explicit App mode registry with validated index/name requests and ordered lifecycle callbacks.
2. A separate Simulator strategy bridge with last/current committed IDs and one pending slot whose first request wins.
3. A command/request boundary between selection and lifecycle effects.
4. An explicit transition boundary for mode notifications; send order is known, listener timing is not.
5. Independent input, SpaceContext, scenario, and Cell axes.

This resolves the architecture-level conflict without claiming original ABI or runtime fidelity.

## Taxonomy

Allowed resolution values are `unresolved`, `preserved_alternatives`, `preferred_claim_with_limit`, and `same_observation_different_scope`. This report uses `preferred_claim_with_limit`: the axis separation and clean-room semantics are preferred, while original transport timing, payload semantics, and ABI details remain bounded.

## Evidence boundary

The direct-evidence sections record what the recovered binary does: helper-local call order, guards, field writes, constructor stores, raw table addresses, slot names, and observed message/request paths. The clean-room requirements section records only the minimum behavior OpenSpore should retain. Raw Cell vptr addresses, primary/secondary vtable addresses, vtable ordering, table size, and original slot numbers are not required in OpenSpore.

## Nine-step method

1. Enumerated single-global-state, App+Simulator-bridge, synchronous-transition, pending/commit, ABI-dimension, and orthogonal-axis hypotheses.
2. Stated owner, field, callback, request, timing, and ABI predictions.
3. Queried read-only Ghidra decompilation, disassembly, memory, vtable, constructor, xref, and call-graph surfaces.
4. Read committed historical reports for independent corroboration and limitations.
5. Marked direct, structural, contradictory, and repetitive evidence separately.
6. Tested whether each conflict changes subsystem boundaries, dispatch, ownership, or event semantics.
7. Used the smallest distinguishing static observations: Cell/editor constructors, manager helper, strategy constructor/predicate, listener, and SpaceContext writer.
8. Recorded no new runtime trace; historical runtime is startup-only with negative Cell-stage reachability.
9. Froze only minimum semantics and deferred unresolved payload/timing/ABI details.

## Direct evidence

### App mode manager

- `0x01412598` is the concrete App `cGameModeManager` table used by the manager.
- `0x007d8c80` range-checks the requested index and delegates to `0x007d85b0`.
- `0x007d85b0` is the activation helper. For a different valid index, its direct order is:
  `old OnExit → write +0x28 → send 0x0212d3e7 → new OnEnter → send 0x022d1adc`.
- A same-index request is a no-op. Invalid negative/out-of-range indices return failure.
- `0x007d8360` scans 24-byte mode entries, compares names case-insensitively, and calls the indexed request path.
- `0x007d8d40` is a teardown/vtable-clearing body despite the stale SDK label; it is not the concrete activation body.

### App-to-Simulator bridge

- `0x00b63510` recognizes `0x0212d3e7` and `0x022d1adc`.
- It reads payload words at `+0x08/+0x10`, normalizes them through `0x00b5c9d0`, and suppresses equal normalized IDs.
- It selects exit/enter-specific transition bodies. The direct calls to `0x00b5f040` and `0x00b5dbb0` are broader transition/effect bodies; exact field ownership of every commit write remains bounded.
- The bridge is separate from the App registry and does not replace its active index.

### Strategy pending/commit

- `0x00b5b960` initializes last/current/pending mode slots to `-1` and pending path to `0`.
- The first-request-wins guards are visible at `0x00b5b880` and `0x00b5b8a0`.
- Historical exact disassembly identifies `0x00b5b8c0` as commit-last and `0x00b5b8e0` as commit-current: each copies pending, clears pending, and resets the path.
- `0x00b5b840` returns stable only when both committed IDs match the candidate and no request is pending.
- The base/derived strategy table evidence is at `0x01461580` and `0x0145d7f0`; it is not the App mode table.

### Interface and concrete tables

- The SDK `App::IGameMode` contract is 16 slots: Initialize, Dispose, OnEnter, OnExit, six input callbacks, and Update, with lifecycle/update at slots 4/5/6/7/15.
- `0x00e616c0` constructs a 12-byte Cell mode object and installs primary vptr `0x01485558` at object `+0` and secondary vptr `0x01485550` at `+4`, then registers `Game_Cell`.
- The Cell tables contain named concrete lifecycle/input/update methods plus unknown/additional slots. They are not a universal 16-slot IGameMode ABI.
- `0x0057ce80` installs `0x013f57f8` as the editor's first vptr. Its first 16 entries have the IGameMode shape; later entries are editor-specific candidates.

### Input and orthogonal axes

- `0x00b3d350` returns the independent `cGameInputManager` pointer in `DAT_0167eaf8`.
- The input manager has independent last/current mode fields at `+0x18/+0x1c`, mouse fields, input-region records, and six input callback slots. Its concrete router body and priority/order algorithm remain unresolved.
- `0x01021960` writes `SpacePlayerData+0x10` only when the context changes; Galaxy has a conditional follow-up. `0x01021d40` initializes the context to `-1`, and `0x01022580` is an independent writer that can force `0`.
- Historical layout evidence places `cScenarioMode::mMode` at `+0xcc` with UnkMode/EditMode/PlayMode values. It is distinct from SpaceContext, input mode, and App active mode.
- Numerical `Galaxy=2` and `PlayMode=2` are coincidental, not aliases.

## Message ordering

The App helper's local order is confirmed. The send/request calls are confirmed; listener execution is not.

| Boundary | Confirmed | Not confirmed |
|---|---|---|
| App helper | Old exit, index write, exit send, new enter, enter send | Whether listeners execute immediately or later |
| Strategy listener | Exit/enter ID recognition, payload-word read, normalization, equal-ID suppression, branch selection | Full payload schema and exact commit/effect suborder |
| Message manager | Post-style wrappers package records and enqueue through `0x00885710`; queue processing is separate at `0x008841f0/0x00847f0` | Concrete `MessageSend` body, priority/tie order, consume result, reentrancy, release timing |
| Pending/commit | First pending ID preserved; commit clears pending | Which external producer issues the first request and how queued messages map to it |

Therefore OpenSpore may implement deterministic synchronous internal callbacks plus explicit sent/requested notifications, but it must not claim that the original listener ran synchronously merely because the helper calls a send/request slot.

## Minimum OpenSpore semantics

| Semantic | Decision | Scope |
|---|---|---|
| Explicit state machine | **Required** | App registry and Simulator strategy separately; not one global enum |
| Command/request layer | **Required** | Validated index/name requests, invalid handling, same-request no-op, explicit transition phases |
| Synchronous/deferred/event-driven | **Explicit boundary required** | Preserve callback order; do not assume original message timing |
| First-request-wins | **Required for strategy** | One pending slot; distinct from App same-index no-op |
| Orthogonal axes | **Required** | App, strategy, input, SpaceContext, scenario, Cell lifecycle |
| Original 27-slot ABI | **Not required** | Preserve semantic lifecycle/input/update, not concrete vtable size |
| Raw Cell vptr/table addresses and ordering | **Not required** | Binary evidence only; OpenSpore uses its own clean-room interfaces |
| Original concrete slot numbers | **Not required** | The semantic callback surface is retained; original slot layout is not |
| Original opaque mode IDs | **Not required** | Use typed semantic IDs while retaining transition evidence separately |

## Safe to freeze

- App active-index ownership and index/name request boundaries.
- The recovered helper-local order as evidence: old exit → index commit → exit send/request → new enter → enter send/request. Do not freeze the original transport or ABI.
- Separate App registry and Simulator strategy pending/committed state.
- First-request-wins for the Simulator pending slot.
- IGameMode lifecycle/input/update semantics: Initialize, Dispose, OnEnter, OnExit, input callbacks, Update, without freezing original slot numbers.
- Independent SpaceContext, scenario, input, and Cell axes.
- Explicit request/transition events without requiring the original payload ABI, vptr addresses, table order, or slot numbers.

## Defer

- Original message send timing, priority, tie order, consume-result, reentrancy, and release semantics.
- Exact mode-announcement payload words and mode-ID normalization meanings.
- Concrete `cGameInputManager` vtable base and input-region routing.
- Complete scenario native transition body and producer/consumer graph.
- Unknown Cell/editor slots and complete C++ inheritance.
- Duplicate mode names, active-entry removal, and the first gameplay-mode producer.
- Runtime reachability of App, Cell, editor, and space transitions.
- Original fixed-step semantics; the SDK name alone does not establish them.

## Architecture dependency

The conflict is architecture-changing. Collapsing the axes or treating the concrete Cell table as the universal interface would change dispatch, input ownership, world/scenario state, or lifecycle behavior. Exact original message timing and vtable ABI are not required for a clean-room implementation, but the separation of owners and transition phases is.

## Limitations and sources

No implementation, Ghidra mutation, `SPORE/` access, or `spore.db` access was performed. Historical runtime evidence is startup-only; the recorded Cell probes were negative because the game never reached Cell.

Primary historical sources:

- `docs/analysis/gameplay-transition-map.md`
- `docs/analysis/gameplay-state-machines.md`
- `docs/analysis/event-message-map.md`
- `docs/analysis/conflict-adjudication.md`
- `docs/analysis/simulator-root-closure.md`
- `docs/analysis/CELL-RUNTIME-OBSERVATION.md`
- `knowledgegraph/research/conflict-adjudication.json`
- `knowledgegraph/research/conflicts/00-corpus-inventory.json`
- `knowledgegraph/research/conflicts/track-b-vtable-fields.json`
- `knowledgegraph/research/state-machines/simulator-core.json`
- `knowledgegraph/research/state-machines/ui-gameplay.json`
- `knowledgegraph/research/state-machines/global-events.json`
- `knowledgegraph/research/types/01-simulator-core.md`
- `knowledgegraph/research/types/04-world-planet.md`
- `knowledgegraph/research/types/06-editor-ui.md`
- `knowledgegraph/research/types/11-vtable-archaeology.md`
- `knowledgegraph/research/root-closure/followup-space-lifecycle.md`
