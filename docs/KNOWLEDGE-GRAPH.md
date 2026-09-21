# Knowledge Graph (engineering loop)

`knowledgegraph/spore.db` (SQLite, git-ignored) is shared cross-tool memory.
Ghidra holds binary structure; this DB holds what tools *concluded*.
No graph UI: every question below is answered by `kg.py`.

## Schema usage

Tables unchanged (`schema.sql`): `node(label,name,attrs_json,confidence,origin,note)`,
`edge(src,dst,rel)`, `test_result(...)`. Node names are globally unique
(`kg.py neighbors` resolves by name alone).

Node kinds: `Function`, `Structure`, `Renderer` (pre-existing RenderWare research);
`Observation` (one planted-probe trace summary per probe; `missed` = defined but 0 events);
`AssetRecord` (chosen real asset by `(type,group,instance)` identity + measured decode facts);
`Implementation` (OpenSpore source files in-tree); `Subsystem` (14 entries imported from
`docs/replacement-status.json`); `Test` (4 ctest names; outcomes in `test_result`);
`Analysis` (one static-analysis PASS summary, never per-candidate rows).
Edge rels: `observes/missed/observedVia` (runtime), `storedIn/decodesWith/walksAs`
(format), `readBy/parsedBy/renderedBy/testedBy/verifies` (asset path),
`implementedBy/boundedBy/verifiedBy/gatedBy` (replacement).

Evidence vocabulary: `UNKNOWN 0.0 < HYPOTHESIS 0.25 < INFERRED 0.5 < SUPPORTED 0.75 < VERIFIED 1.0`
(stored in `attrs_json.evidence`, mirrored in `confidence`).
Status mapping (`replacement-status.json` → graph): unknown→UNKNOWN, hypothesis→HYPOTHESIS,
inferred→INFERRED, supported→SUPPORTED, verified→VERIFIED, replaced-stub→SUPPORTED
(code + in-tree substitutability, gate open), replaced-verified→VERIFIED (gate tests green).
Measured bytes / green tests / planted-breakpoint traces = evidence; decompiler guesses never
exceed INFERRED; AI inference is never VERIFIED.

## Seed / rebuild

```sh
python3 knowledgegraph/kg.py init && python3 knowledgegraph/seed_sprint.py init
# re-runnable: nodes upsert by (label,name), edges INSERT OR IGNORE,
# legacy RenderWare rows DO NOTHING, seed test rows delete+re-insert.
# => 60 nodes, 68 edges, 7 test rows (re-run yields identical counts).
```

## Worked queries

1. Which behavior touches asset path X?
   `python3 knowledgegraph/kg.py neighbors --name "asset:gmdl:00E6BCE5:40637E03:067A07F0"`
   → storedIn DBPFv3, decodesWith QFS, walksAs GameModelResource, read/parsed/rendered by
   Dbpf/Gmdl/Mesh/VulkanRenderer impls, verified by assets_real + asset_render.
2. Which observations support interface Y?
   `python3 knowledgegraph/kg.py neighbors --name "sub:bootstrap-appsystem-lifecycle"`
   → 5 observedVia edges (entry/InitPlugins/Init/Startup/Get×1000, all VERIFIED);
   `neighbors --name "App::cAppSystem::Init"` traces back to `obs:main_menu:Init`.
3. Which implementation replaced behavior Z?
   `python3 knowledgegraph/kg.py neighbors --name "sub:dbpf-index"`
   → implementedBy Dbpf.cpp, boundedBy B1 ResourceProvider.hpp,
   verifiedBy assets_synthetic + assets_real.
4. Which subsystems remain unknown?
   `python3 knowledgegraph/kg.py query --label Subsystem` (+ filter `UNKNOWN`)
   → `sub:audio-havok-input`, `sub:pollinator-online`. Open gates hang off
   `gatedBy` (e.g. resource-manager-full → `obs:menu_transition`, never traced).

## NOT in the graph (and why)

- Vtable candidates (3081): only the PASS summary node `analysis:vtable_pass`
  (3081/369 high/20 labeled → `docs/analysis/vtables.json`); per-candidate rows are noise
  until hierarchy claims need them. Non-replaced subsystem gates pointing at untraced
  docs have no edge (no invented semantics). No VERIFIED without measurement.

## Maintenance

When an objective finishes: (1) add its nodes/edges to `seed_sprint.py` with stable
names + measured evidence; (2) re-run seed, confirm counts grew only as intended;
(3) record test outcomes in `TEST_ROWS` from a real run; (4) update the 4 queries
above if kinds changed; (5) never hand-edit `spore.db` (rebuild from seed instead).
