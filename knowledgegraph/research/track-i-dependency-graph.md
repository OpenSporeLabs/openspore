# Track I — Global call-graph and dependency archaeology

> Read-only deterministic analysis over triage-v6 and the canonical xref TSV. No graph DB or Ghidra access; no runtime claim is promoted.

## 1. Inputs and reproducibility

| role | path | records | sha256 |
|---|---|---|---|
| triage_v6_functions | `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl` | 58757 | 5fd07ad16b85… |
| canonical_xrefs | `knowledgegraph/triage/xrefs-2540f2ca.tsv` | 223704 | 89e74b8a03c4… |
| canonical_external_allowlist | `knowledgegraph/triage/xrefs-2540f2ca.externals.tsv` | 362 | 23a96399a638… |
| triage_v6_summary | `knowledgegraph/triage/summary-f0e310e0.triage-v6.json` | — | 3901eb6984cf… |
| triage_v6_cluster_inventory | `knowledgegraph/triage/clusters-f0e310e0-v6.json` | 20 | 7b9cbc9a584d… |
| xref_export_summary | `knowledgegraph/triage/xrefs-2540f2ca.summary.json` | — | 83f7762426b2… |
| vtable_candidate_inventory | `docs/analysis/vtables.json` | 3081 | f4161d3d9944… |
| cluster_partition_rule | `tools/triage/rules-v4.json` | — | 94a71ce75066… |
| prior_reconstruction_dependency_audit | `knowledgegraph/triage/reconstruction-readiness-f0e310e0.json` | 2149 | 44e89b29c4dc… |

Machine-readable output: `knowledgegraph/research/track-i-dependency-graph.json`. Every emitted function edge includes source caller, target, canonical reference type(s), and real callsite(s).

## 2. Global graph shape

- **Universe:** 58,757 functions; 140,810 distinct internal call pairs; 2,389 distinct caller→external pairs.
- **Canonical rows:** 223,704 total = 207,757 call references + 15,947 vtable/data references.
- **Connectivity:** 9,719 weak components; largest 46,313; 294 nontrivial. 58,654 SCCs; largest 1; 76 nontrivial.
- **Coverage:** 33,643 functions have an internal caller; 40,641 have an internal callee; 1,599 call an import.
- **Evidence debt:** 477/58,757 decomp-backed; 4,092 named; 5,948 in at least one vtable candidate; 39,716 still UNKNOWN.

### Largest global structures

| # | size | named | decomp | dominant subsystem | representative |
|---|---|---|---|---|---|
| 1 | 46313 | 3572 | 376 | Anim | FUN_00f47380, FUN_00f473a0 |
| 2 | 194 | 0 | 0 | App | FUN_004013f0, FUN_0121b1c0 |
| 3 | 194 | 0 | 0 | App | FUN_00401850, FUN_0121b170 |
| 4 | 129 | 0 | 0 | App | FUN_00401160, FUN_0121aee0 |
| 5 | 129 | 0 | 0 | App | FUN_00401190, FUN_0121af10 |
| 6 | 129 | 0 | 0 | App | FUN_004011c0, FUN_0121af40 |
| 7 | 129 | 0 | 0 | App | FUN_00401200, FUN_0121af80 |
| 8 | 129 | 0 | 0 | App | FUN_00401240, FUN_0121afc0 |
| 9 | 129 | 0 | 0 | App | FUN_00401280, FUN_0121b000 |
| 10 | 129 | 0 | 0 | App | FUN_004012c0, FUN_0121b040 |

## 3. Ranked roots and central managers

Named singleton rows are explicit name/struct candidates. Unnamed low-out rows are graph-only hypotheses; their shared-state meaning is **not** asserted without body/global evidence.

| rank | class | va | name | fan_in | fan_out | category | evidence | decomp |
|---|---|---|---|---|---|---|---|---|
| 1 | named_singleton_accessor | 00b3d350 | Simulator::cGameInputManager::Get | 614 | 0 | GAMEPLAY_SUPPORT | CONFIRMED | yes |
| 2 | named_singleton_accessor | 00401090 | Editors::cSpeciesManager::Get | 162 | 0 | GAMEPLAY_SUPPORT | CONFIRMED | yes |
| 3 | named_singleton_accessor | 00b3d4d0 | Simulator::cSpaceTrading::Get | 156 | 0 | GAMEPLAY_SUPPORT | CONFIRMED | yes |
| 4 | named_singleton_accessor | 006a25a0 | Prop_GetPropValueBool | 99 | 3 | GAMEPLAY_SUPPORT | SUPPORTED | no |
| 5 | named_singleton_accessor | 00401010 | Editors::IBakeManager::Get | 90 | 0 | GAMEPLAY_SUPPORT | CONFIRMED | yes |
| 6 | named_singleton_accessor | 00401030 | Sporepedia::cAssetViewManager::Get | 71 | 0 | GAMEPLAY_SUPPORT | CONFIRMED | yes |
| 7 | named_singleton_accessor | 00b3d480 | Simulator::cGameTimeManager::Get | 61 | 0 | GAMEPLAY_SUPPORT | CONFIRMED | yes |
| 8 | named_singleton_accessor | 00b3d520 | Simulator::cPlantSpeciesManager::Get | 56 | 1 | GAMEPLAY_SUPPORT | CONFIRMED | yes |
| 9 | named_singleton_accessor | 00b3d3c0 | Simulator::cRelationshipManager::Get | 53 | 0 | GAMEPLAY_SUPPORT | CONFIRMED | yes |
| 10 | named_singleton_accessor | 00b3d420 | Simulator::cGameModeManager::Get | 47 | 0 | GAMEPLAY_SUPPORT | CONFIRMED | yes |
| 11 | named_singleton_accessor | 00b3d400 | Simulator::cGameNounManager::Get | 43 | 0 | GAMEPLAY_SUPPORT | CONFIRMED | yes |
| 12 | named_singleton_accessor | 00401020 | Palettes::cSwatchManager::Get | 42 | 0 | GAMEPLAY_SUPPORT | CONFIRMED | yes |
| 13 | unnamed_low_out_fanin | 00b3d300 | FUN_00b3d300 | 1097 | 0 | GAMEPLAY_SUPPORT | SUPPORTED | no |
| 14 | unnamed_low_out_fanin | 00b5b800 | FUN_00b5b800 | 459 | 2 | GAMEPLAY_LOGIC | SUPPORTED | no |
| 15 | unnamed_low_out_fanin | 00b3d2a0 | FUN_00b3d2a0 | 314 | 0 | GAMEPLAY_SUPPORT | SUPPORTED | no |
| 16 | unnamed_low_out_fanin | 00b1fdb0 | FUN_00b1fdb0 | 303 | 0 | GAMEPLAY_LOGIC | SUPPORTED | no |
| 17 | unnamed_low_out_fanin | 01021260 | FUN_01021260 | 262 | 0 | GAMEPLAY_SUPPORT | SUPPORTED | no |
| 18 | unnamed_low_out_fanin | 00b21340 | FUN_00b21340 | 254 | 2 | GAMEPLAY_LOGIC | SUPPORTED | no |
| 19 | unnamed_low_out_fanin | 00c2e4e0 | FUN_00c2e4e0 | 198 | 0 | GAMEPLAY_LOGIC | INFERRED | no |
| 20 | unnamed_low_out_fanin | 01021300 | FUN_01021300 | 182 | 2 | GAMEPLAY_SUPPORT | SUPPORTED | no |
| 21 | unnamed_low_out_fanin | 01021080 | FUN_01021080 | 175 | 0 | GAMEPLAY_SUPPORT | SUPPORTED | no |
| 22 | unnamed_low_out_fanin | 00b3d380 | FUN_00b3d380 | 165 | 0 | GAMEPLAY_SUPPORT | SUPPORTED | no |
| 23 | unnamed_low_out_fanin | 00b3d240 | FUN_00b3d240 | 158 | 0 | GAMEPLAY_SUPPORT | SUPPORTED | no |
| 24 | unnamed_low_out_fanin | 00b225d0 | FUN_00b225d0 | 157 | 3 | GAMEPLAY_LOGIC | SUPPORTED | no |

### Chokepoint proxy

| rank | va | name | score | fan_in | fan_out | category |
|---|---|---|---|---|---|---|
| 1 | 00f47380 | FUN_00f47380 | 80.79 | 6527 | 1 | ENGINE_IMPLEMENTATION |
| 2 | 00f473a0 | FUN_00f473a0 | 53.861 | 2901 | 1 | ENGINE_IMPLEMENTATION |
| 3 | 00dd8640 | FUN_00dd8640 | 38.536 | 55 | 27 | GAMEPLAY_LOGIC |
| 4 | 006b55c0 | FUN_006b55c0 | 36.263 | 263 | 5 | ENGINE_IMPLEMENTATION |
| 5 | 00423650 | FUN_00423650 | 31.984 | 341 | 3 | ENGINE_IMPLEMENTATION |
| 6 | 00b5b800 | FUN_00b5b800 | 30.299 | 459 | 2 | GAMEPLAY_LOGIC |
| 7 | 006b5240 | FUN_006b5240 | 30.05 | 301 | 3 | ENGINE_IMPLEMENTATION |
| 8 | 008105b0 | FUN_008105b0 | 25.923 | 672 | 1 | ENGINE_IMPLEMENTATION |
| 9 | 01180d50 | FUN_01180d50 | 25.729 | 331 | 2 | ENGINE_IMPLEMENTATION |
| 10 | 00454cb0 | FUN_00454cb0 | 25.278 | 213 | 3 | ENGINE_IMPLEMENTATION |
| 11 | 008f3d90 | FUN_008f3d90 | 25.239 | 49 | 13 | ENGINE_IMPLEMENTATION |
| 12 | 0093c5a0 | FUN_0093c5a0 | 24.187 | 117 | 5 | ENGINE_IMPLEMENTATION |
| 13 | 0044ae00 | FUN_0044ae00 | 23.917 | 52 | 11 | GAMEPLAY_LOGIC |
| 14 | 00441440 | FUN_00441440 | 23.812 | 7 | 81 | ENGINE_INTERFACE |
| 15 | 00b21340 | FUN_00b21340 | 22.539 | 254 | 2 | GAMEPLAY_LOGIC |
| 16 | 00fec590 | FUN_00fec590 | 22.249 | 15 | 33 | ENGINE_IMPLEMENTATION |
| 17 | 00aebe90 | FUN_00aebe90 | 21.977 | 7 | 69 | ENGINE_IMPLEMENTATION |
| 18 | 0042dee0 | FUN_0042dee0 | 21.817 | 238 | 2 | ENGINE_IMPLEMENTATION |
| 19 | 00c099e0 | FUN_00c099e0 | 21.817 | 14 | 34 | GAMEPLAY_LOGIC |
| 20 | 009a9600 | FUN_009a9600 | 21.772 | 237 | 2 | ENGINE_IMPLEMENTATION |
| 21 | 00b225d0 | FUN_00b225d0 | 21.703 | 157 | 3 | GAMEPLAY_LOGIC |
| 22 | 00b20c60 | FUN_00b20c60 | 21.541 | 116 | 4 | ENGINE_IMPLEMENTATION |
| 23 | 009221b0 | FUN_009221b0 | 21.401 | 229 | 2 | ENGINE_IMPLEMENTATION |
| 24 | 00c32cd0 | FUN_00c32cd0 | 20.785 | 24 | 18 | GAMEPLAY_LOGIC |
| 25 | 00aea5d0 | FUN_00aea5d0 | 20.494 | 105 | 4 | ENGINE_IMPLEMENTATION |
| 26 | 0083bcd0 | FUN_0083bcd0 | 20.199 | 24 | 17 | UNKNOWN |
| 27 | 006b54b0 | FUN_006b54b0 | 20.1 | 101 | 4 | ENGINE_INTERFACE |
| 28 | 00e3e350 | FUN_00e3e350 | 19.975 | 19 | 21 | ENGINE_IMPLEMENTATION |
| 29 | 00895810 | FUN_00895810 | 19.774 | 23 | 17 | UNKNOWN |
| 30 | 004558a0 | FUN_004558a0 | 19.748 | 130 | 3 | ENGINE_IMPLEMENTATION |

The score is `sqrt(caller degree × callee degree)`, not betweenness. Central-manager candidates, their evidence edges, and all other rankings are in the JSON.

## 4. High fan-in gameplay functions

| rank | va | name | fan_in | gameplay_fan_in | fan_out | subsystem | decomp |
|---|---|---|---|---|---|---|---|
| 1 | 00b3d300 | FUN_00b3d300 | 1097 | 252 | 0 | Simulator | no |
| 2 | 00b3d350 | Simulator::cGameInputManager::Get | 614 | 80 | 0 | Simulator | yes |
| 3 | 00b5b800 | FUN_00b5b800 | 459 | 80 | 2 | Simulator | no |
| 4 | 00b3d2a0 | FUN_00b3d2a0 | 314 | 101 | 0 | Simulator | no |
| 5 | 00b1fdb0 | FUN_00b1fdb0 | 303 | 68 | 0 | Simulator | no |
| 6 | 01021260 | FUN_01021260 | 262 | 68 | 0 | Simulator | no |
| 7 | 00b21340 | FUN_00b21340 | 254 | 50 | 2 | Simulator | no |
| 8 | 00e5c780 | map_int_whatever_find | 239 | 49 | 0 | GameGlobal | no |
| 9 | 00c2e4e0 | FUN_00c2e4e0 | 198 | 16 | 0 | Sporepedia | no |
| 10 | 01021300 | FUN_01021300 | 182 | 47 | 2 | Simulator | no |
| 11 | 01021080 | FUN_01021080 | 175 | 38 | 0 | Simulator | no |
| 12 | 00b3d380 | FUN_00b3d380 | 165 | 19 | 0 | Simulator | no |
| 13 | 00401090 | Editors::cSpeciesManager::Get | 162 | 17 | 0 | Editor | yes |
| 14 | 00b3d240 | FUN_00b3d240 | 158 | 28 | 0 | Simulator | no |
| 15 | 00b225d0 | FUN_00b225d0 | 157 | 31 | 3 | Simulator | no |
| 16 | 00b3d4d0 | Simulator::cSpaceTrading::Get | 156 | 22 | 0 | Simulator | yes |
| 17 | 005c65e0 | FUN_005c65e0 | 140 | 32 | 0 | Simulator | no |
| 18 | 00ba9370 | FUN_00ba9370 | 136 | 35 | 1 | Simulator | no |
| 19 | 00b3d2c0 | FUN_00b3d2c0 | 127 | 21 | 3 | Simulator | no |
| 20 | 00743b50 | FUN_00743b50 | 125 | 35 | 0 | Simulator | no |
| 21 | 01021090 | FUN_01021090 | 119 | 31 | 0 | Simulator | no |
| 22 | 00b8de30 | FUN_00b8de30 | 116 | 28 | 3 | Simulator | no |
| 23 | 0059c190 | QuaternionToMatrix | 113 | 12 | 1 | GameGlobal | no |
| 24 | 00ce6950 | FUN_00ce6950 | 112 | 33 | 0 | Simulator | no |
| 25 | 010212a0 | FUN_010212a0 | 103 | 22 | 0 | Simulator | no |

## 5. High fan-out orchestrators (gameplay)

| rank | va | name | fan_in | fan_out | external | vtable_slots | category |
|---|---|---|---|---|---|---|---|
| 1 | 00591fa0 | Editors::cEditor::HandleMessage | 0 | 111 | 0 | 1 | GAMEPLAY_LOGIC |
| 2 | 0102df20 | FUN_0102df20 | 1 | 104 | 0 | 0 | GAMEPLAY_LOGIC |
| 3 | 0058be50 | Editors::cEditor::Update | 0 | 96 | 0 | 1 | GAMEPLAY_LOGIC |
| 4 | 00588570 | Editors::cEditor::OnMouseDown | 0 | 92 | 0 | 1 | GAMEPLAY_LOGIC |
| 5 | 010593e0 | FUN_010593e0 | 2 | 85 | 0 | 2 | GAMEPLAY_LOGIC |
| 6 | 004c73f0 | FUN_004c73f0 | 2 | 67 | 0 | 0 | GAMEPLAY_LOGIC |
| 7 | 00bb8b20 | FUN_00bb8b20 | 3 | 62 | 2 | 0 | GAMEPLAY_LOGIC |
| 8 | 0058ac10 | Editors::cEditor::OnKeyDown | 0 | 56 | 0 | 1 | GAMEPLAY_LOGIC |
| 9 | 00587a20 | Editors::cEditor::OnExit | 0 | 54 | 0 | 1 | GAMEPLAY_LOGIC |
| 10 | 0102d1b0 | FUN_0102d1b0 | 1 | 53 | 0 | 0 | GAMEPLAY_SUPPORT |
| 11 | 01003690 | FUN_01003690 | 6 | 52 | 0 | 0 | GAMEPLAY_SUPPORT |
| 12 | 01073700 | FUN_01073700 | 4 | 51 | 0 | 0 | GAMEPLAY_LOGIC |
| 13 | 0105a110 | FUN_0105a110 | 0 | 50 | 0 | 1 | GAMEPLAY_LOGIC |
| 14 | 00586b00 | Editors::cEditor::SetEditorModel | 5 | 49 | 0 | 0 | GAMEPLAY_SUPPORT |
| 15 | 00587270 | Editors::cEditor::SetActiveMode | 4 | 43 | 0 | 0 | GAMEPLAY_SUPPORT |
| 16 | 00b28ec0 | FUN_00b28ec0 | 1 | 40 | 2 | 0 | GAMEPLAY_SUPPORT |
| 17 | 01056160 | FUN_01056160 | 2 | 41 | 0 | 5 | GAMEPLAY_LOGIC |
| 18 | 00582fe0 | Editors::cEditor::AddCreature | 8 | 40 | 0 | 0 | GAMEPLAY_LOGIC |
| 19 | 00b32b20 | FUN_00b32b20 | 1 | 39 | 0 | 0 | GAMEPLAY_SUPPORT |
| 20 | 00b33350 | FUN_00b33350 | 1 | 39 | 0 | 0 | GAMEPLAY_SUPPORT |
| 21 | 00c20230 | FUN_00c20230 | 1 | 38 | 0 | 0 | GAMEPLAY_LOGIC |
| 22 | 00582250 | Editors::cEditor::sub_581F70 | 1 | 36 | 0 | 0 | GAMEPLAY_LOGIC |
| 23 | 00dabdf0 | FUN_00dabdf0 | 0 | 36 | 0 | 0 | GAMEPLAY_LOGIC |
| 24 | 00c099e0 | FUN_00c099e0 | 14 | 34 | 0 | 0 | GAMEPLAY_LOGIC |
| 25 | 00b32ce0 | FUN_00b32ce0 | 1 | 33 | 0 | 0 | GAMEPLAY_SUPPORT |

## 6. Semantic components

The 20 components are the exhaustive `_row_cluster` partition recomputed from triage-v6. They are semantic labels, not runtime sequences.

| component | functions | gameplay | decomp | weak | largest | cross_pairs |
|---|---|---|---|---|---|---|
| unknown-fun-mass | 44978 | 0 | 0 | 12857 | 30531 | 49313 |
| unknown-vtable-impl | 4384 | 0 | 0 | 3888 | 58 | 16222 |
| runtime-crt-stl | 4075 | 0 | 2 | 1491 | 403 | 6163 |
| sim-core-systems | 1628 | 1523 | 54 | 270 | 1334 | 14435 |
| app-lifecycle | 1104 | 0 | 147 | 356 | 679 | 13018 |
| utfwin-framework | 1093 | 0 | 66 | 571 | 333 | 4338 |
| resource-io | 523 | 0 | 50 | 174 | 280 | 2780 |
| editor-core | 314 | 265 | 39 | 84 | 214 | 2477 |
| terrain-world | 112 | 102 | 5 | 42 | 45 | 702 |
| sporepedia-online | 100 | 83 | 14 | 70 | 12 | 830 |
| editor-support | 99 | 84 | 18 | 23 | 51 | 607 |
| graphics-render | 86 | 0 | 20 | 25 | 58 | 1343 |
| scripting-content | 84 | 0 | 10 | 43 | 17 | 681 |
| swarm-anim | 70 | 0 | 4 | 8 | 63 | 1384 |
| gameglobal-misc | 39 | 35 | 0 | 19 | 18 | 871 |
| sim-cell | 26 | 26 | 26 | 16 | 8 | 252 |
| ui-shell | 13 | 13 | 3 | 10 | 4 | 135 |
| audio-input | 11 | 0 | 6 | 7 | 3 | 102 |
| sim-creature-tribeciv | 11 | 11 | 11 | 10 | 2 | 79 |
| sim-space | 7 | 7 | 2 | 6 | 2 | 232 |

Top vtable families and SDK struct associations, plus representative members, are in `semantic_components` support sections of the JSON.

## 7. Isolated functions

- **9,306** functions have no internal caller, internal callee, or external call target.
- **8,553** are also isolated after retaining vtable/data references; **505** have outgoing reference-only edges and **259** have incoming data-reference-only edges.
- The isolated set contains **45 gameplay**, **111 named**, and **88 decomp-backed** functions.

Full membership and a deterministic top-100 ranking are in `isolated_functions`; reference-only isolation is not called a runtime leaf.

## 8. Wrapper forests

- **143** triage rows carry the explicit `v5-crt-wrapper` rationale; **390** functions have zero internal callees and at least one external call target.
- Target fan-forest detection identifies shared targets with leaf-ish caller fans; the top 30 include actual callsite evidence.
- Vtable-backed high-fan-out dispatch surfaces and thin gameplay→import bridges are reported separately to avoid conflating wrappers, dispatch, and runtime leaf calls.

## 9. Gameplay ↔ engine/runtime bridges

| direction | pairs | rows |
|---|---|---|
| gameplay_to_engine | 3375 | 5070 |
| engine_to_gameplay | 3380 | 4928 |
| gameplay_to_runtime | 137 | 181 |
| engine_to_runtime | 1250 | 2005 |

The JSON contains the top 40 bridge functions, top 250 category-crossing edges, top 250 cross-component edges, and top 100 external edges. Aggregate counts above cover every canonical edge. Vtable references are not counted as gameplay↔engine calls.

## 10. First-understanding order

| rank | unit | entries | objective |
|---|---|---|---|
| 1 | named_singleton_roots | 12 | Establish exact singleton/global-return contracts before reading callers. |
| 2 | unnamed_low_out_roots | 12 | Characterize the unnamed high-fan-in contracts; do not yet assign singleton meanings without body/global evidence. |
| 3 | central_manager_contracts | 12 | Map manager getters, setters, and update/continuation functions before subsystem bodies. |
| 4 | gameplay_engine_bridges | 12 | Freeze cross-category contracts used by the most bridge-heavy functions. |
| 5 | orchestrator_and_dispatch_surfaces | 20 | Separate dispatch/control flow from leaf algorithms by reading top orchestrators and vtable-backed handlers. |
| 6 | semantic_components | 20 | Study clusters only after root, manager, and bridge contracts; prioritize coherent clusters with decomp coverage and gameplay content. |
| 7 | isolated_function_packages | 40 | Parallelize call-isolated functions, prioritizing gameplay, named, decomp-backed rows. |

This is a dependency-first reading order, not an implementation plan: contracts and dispatch surfaces precede large semantic bodies; isolated functions are parallel work packages.

## 11. Unresolved limitations

1. **vtable-ref granularity:** A vtable-ref row points to the containing vtable base, not the exact selected slot method. No caller-to-slot virtual-call edge is invented.
2. **vtable discovery incompleteness/no RTTI:** The binary has no MSVC RTTI; the candidate inventory has 3,081 candidates but only 20 labels. Vtable families can merge or misattribute.
3. **no global/data-state xref export:** The exporter retains data refs only when the target is itself a pinned function or a known vtable range. Shared-state candidates cannot be proven from reads/writes to globals in this artifact.
4. **call reference is not execution proof:** A call xref proves a reference, not that a route is runtime-reachable on every execution. Tail calls, thunks, and computed-call semantics are not fully resolved here.
5. **external boundary is import-only:** External edges identify imported functions, not the third-party implementation or its complete dependency graph.
6. **category uncertainty:** 39,716 functions remain UNKNOWN; v6 region/caller propagation is static inference. Bridges and semantic components inherit those category assignments.
7. **body coverage:** Only 1,667 functions have exported SDK decompilation; most high-fan-in unnamed roots have no body artifact. Root semantics beyond names/contracts remain unresolved.
8. **no runtime evidence:** The triage projection has zero OBSERVED and zero VERIFIED functions. First-understanding order is structural, not a runtime call sequence.
9. **snapshot pair:** Xrefs are frozen at snapshot 2540f2ca and triage at f0e310e0. They share the canonical binary and 58,757-function pinned universe, but names/categories were classified later.
10. **no exact betweenness/path ranking:** Chokepoints use a transparent degree proxy. A full Brandes betweenness computation is not included because it would be expensive and still graph-theoretic rather than semantic.

## 12. Determinism contract

- No wall-clock fields, random choices, live Ghidra queries, or SQLite reads/writes.
- Counts are recomputed from the two frozen source datasets; all JSON keys and records are sorted before serialization.
- Re-running the same inputs must produce byte-identical JSON and Markdown; verify with SHA-256 after two runs.
