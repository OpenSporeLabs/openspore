# Reconstruction knowledge index

`index.json` is a generated, read-only projection for reconstruction agents. It joins the authoritative source-reconstruction manifest with the committed triage queue, xref export, semantic-decomp records, per-function metadata, integrated handoffs, type records, and conflict ledgers.

`bootstrap.json` is the small first-read bundle. It contains the current frontier, ABI convention index, known types/globals/vtables, counts, and the query command to use next.

## Source of truth

`knowledgegraph/research/source-reconstruction-manifest.json` remains authoritative for reconstruction ownership and status. The index does not promote runtime evidence, replace the manifest, or write ownership. `investigations` in `knowledgegraph/spore.db` remains the coordination queue for active claims; its rows are read opportunistically by the MCP context helpers and are never copied into the committed index.

## Generation

From the repository root:

```sh
python3 -m tools.reconstruction_knowledge build
```

The command atomically replaces `reconstruction/knowledge/index.json` and `reconstruction/knowledge/bootstrap.json`. Regenerate after changing the manifest, triage queue, xref export, semantic-decomp corpus, reconstruction metadata, handoffs, or conflict ledgers. The generator records source hashes in `source_of_truth` and `input_hashes`.

## Query surface

The CLI avoids requiring a database or a full corpus read:

```sh
python3 -m tools.reconstruction_knowledge status --va 0x00e5b790
python3 -m tools.reconstruction_knowledge function --va 0x00e5b790
python3 -m tools.reconstruction_knowledge related --va 0x00e5b790
python3 -m tools.reconstruction_knowledge type Transform
python3 -m tools.reconstruction_knowledge package PKG-CAMERA-WAVE7
python3 -m tools.reconstruction_knowledge frontier --limit 20
```

The MCP server exposes the same focused paths as `function_context`, `frontier_context`, and `reconstruction_status`. Results are bounded and deterministic. Dependency counts remain exact while caller/callee and edge lists are capped; the response reports truncation rather than silently implying completeness.

## Index contents

- `records`: manifest functions plus triage, metadata, handoff, and semantic records keyed by canonical VA.
- `packages`, `types`, `globals`, `vtables`, and `services`: reverse lookup indexes.
- `abi_conventions`: established calling-convention groups and examples.
- `frontier`: current non-reconstructed, non-blocked triage rows in committed queue rank order.
- `dependency_signals`: high fan-in, high fan-out, and non-trivial strongly connected components.
- `contradictions`: explicit semantic and conflict-ledger rejections/unresolved claims with VA anchors.
- `analogues`: reconstructed functions ranked only by explicit shared package, subsystem, class, type, vtable, ABI, semantic-family, or direct-xref signals.
- `codegraph`: availability and the `codegraph explore` command for source-level follow-up after the VA context is selected.

## Duplicate prevention

Use the existing SQLite coordination queue for claims. The `queue_op` operation `claim` is an atomic, lease-aware transition:

```json
{"op":"claim","id":"fn:VA:label","implementer_id":"agent-id","binary_sha256":"..."}
```

The operation refuses active claims owned by another agent, terminal `done`/`dropped` rows, stale binary identities, and blocked rows unless explicitly allowed. A stale active claim can be reclaimed only with `allow_stale=true` and `stale_after_seconds`; this is an explicit lease decision, not an automatic ownership change. Existing `insert` deduplication on `(kind, va, binary_sha256)` remains unchanged.

## Consumers

Agents should read `bootstrap.json` first, select a bounded frontier target, then call `function_context` or the CLI `function` query. `related_functions` supplies same-package/subsystem/class/type/vtable/ABI analogues and direct xref neighbours. The source files, metadata, handoff, and decomp paths in the response are the exact inspection starting points. Use the `codegraph` entry in the bootstrap bundle to navigate the selected source symbol and its callers after the binary context is known.
