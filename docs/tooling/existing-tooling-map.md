# Existing tooling map

The repository already had the following reusable layers:

| Area | Existing entry points | Reuse decision |
|---|---|---|
| Reconstruction projection | `tools/reconstruction_knowledge.py` | authoritative adapter for manifest/triage/metadata/handoff/xref joins |
| MCP reconstruction tools | `tools/mcp/reconstruction_tools.py` | status/context contracts remain unchanged |
| Ghidra transport | `tools/mcp/ghidra_client.py`, `tools/mcp/ghidra_tools.py` | live/snapshot/offline provenance reused |
| KG sidecar | `knowledgegraph/kg.py`, `tools/mcp/kg_tools.py` | SQLite remains canonical; no new DB |
| Claims | `investigations` plus existing `queue_op` | read-only overlay in frontier; no duplicate claim table |
| Runtime | `tools/observatory`, `tools/mcp/runtime_tools.py` | runtime remains separately gated |
| Graph Observatory | `tools/viewer/query.py`, `tools/viewer/server.py` | existing read-only projections reused conceptually |
| Triage/xrefs | `tools/triage/`, `knowledgegraph/triage/` | candidate pool and dependency evidence reused |
| Integration projection | `reconstruction/knowledge/` | generated, not a new authority |

## Duplication risks avoided

- no second manifest or frontier database;
- no second claim protocol;
- no copied Ghidra cache;
- no generated context index;
- no runtime evidence promotion from static validation;
- no MCP protocol or registry changes.

## Known gaps retained explicitly

Most reconstruction packages are not registered in the root CMake graph. The current generated index and many metadata/handoff files are untracked concurrent work. The frontier therefore reports source availability and provenance instead of assuming a clean checkout.
