# Knowledge Graph (engineering loop)

`knowledgegraph/spore.db` (SQLite, git-ignored) is shared cross-tool memory.
Ghidra holds binary structure; this DB holds what tools *concluded*.
No graph UI: every question below is answered by `kg.py`.

## Schema usage

Tables (`schema.sql`): `node(label,name,attrs_json,confidence,origin,note,evidence_level,updated_at,binary_sha256)`,
`edge(src,dst,rel)`, `test_result(...)`, `field(struct_id,offset,role,offset_evidence,meaning_evidence,value,source,binary_sha256)`,
`trace_run(binary_sha256,probes_sha256,wine_version,display_env,xdotool,captured_at,events_total,jsonl_path,screenshots_*,outcome,replayable)`,
`investigations(id,kind,va,name,subsystem,mode,stage,status,block_reason,prerequisites,attempts,checkpoint,evidence_refs,implementer_id,adjudicator_id,binary_sha256, ...)`.
`kg.py` migrates the old schema on every command (additive, idempotent; `user_version` 0→1).
Node names are globally unique (`kg.py neighbors` resolves by name alone).
`binary_sha256` NULL = build-agnostic; rows from another build stay parked (stale = `binary_sha256 != current`), never dropped.

Node kinds: `Function`, `Structure`, `Renderer` (pre-existing RenderWare research);
`Observation` (one planted-probe trace summary per probe; `missed` = defined but 0 events);
`AssetRecord` (chosen real asset by `(type,group,instance)` identity + measured decode facts);
`Implementation` (OpenSpore source files in-tree); `Subsystem` (18 entries imported from
`docs/replacement-status.json`); `Test` (4 ctest names; outcomes in `test_result`);
`Analysis` (one static-analysis PASS summary, never per-candidate rows); plus S1 labels
`Class`, `Hypothesis`, `Adjudication` (closed enum for NEW records; legacy names survive forward-only).
Edge rels: `observes/missed/observedVia` (runtime), `storedIn/decodesWith/walksAs`
(format), `readBy/parsedBy/renderedBy/testedBy/verifies` (asset path),
`implementedBy/boundedBy/verifiedBy/gatedBy` (replacement).

Evidence scale — ONE source of truth, `knowledgegraph/scale.py` (7 levels):
`UNKNOWN 0.0 < APPROXIMATION 0.3 < INFERRED 0.5 < SUPPORTED 0.75 < OBSERVED 0.85 < CONFIRMED 0.9 < VERIFIED 1.0`
(node `evidence_level` column is canonical; `confidence` is derived display; free prose in
`attrs_json.evidence` is context, not scale). Status mapping (all 9 statuses, `scale.STATUS2EV`):
unknown→UNKNOWN, hypothesis→INFERRED, inferred→INFERRED, supported→SUPPORTED, verified→VERIFIED,
approximated→APPROXIMATION, replaced-stub→SUPPORTED (code + in-tree substitutability, gate open),
replaced-approx→APPROXIMATION, replaced-verified→VERIFIED (gate tests green).
The legacy 5-level values (incl. HYPOTHESIS 0.25) translate via the read-only `scale.LEGACY_EV`
compat map only. Measured bytes / green tests / planted-breakpoint traces = evidence; decompiler
guesses never exceed INFERRED; AI inference is never VERIFIED.

## Seed / rebuild

```sh
python3 knowledgegraph/kg.py init
python3 knowledgegraph/seed.py [--binary-sha256 <64-hex> | --build-agnostic]
# Canonical generator: deterministic (sorted emit), idempotent, bare-clone-safe.
# Inputs (committed): seed-literals.json (96/115/14 verbatim), replacement-status.json
# (18 subsystems + investigations rows), dossiers, vtables, REPLACEMENT-ABI fields,
# committed trace manifests. Optional machine inputs (SDK XML, binaries) are flags,
# gracefully skipped when absent. Re-run => identical logical state; re-seed under a
# new --binary-sha256 preserves old rows as stale (never deleted).
# => 96 nodes, 115 edges, 14 test rows, 18 Subsystem nodes.
```
`seed_sprint.py` is a DEPRECATED shim (forwards to `seed.py`); do not add data to it.

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

When an objective finishes: (1) record its nodes/edges in the committed seed inputs
(`seed-literals.json` / the relevant committed JSON) with stable names + measured
evidence; (2) re-run `seed.py`, confirm counts grew only as intended;
(3) record test outcomes from a real run; (4) update the queries above if kinds
changed; (5) never hand-edit `spore.db` (rebuild from seed instead).
