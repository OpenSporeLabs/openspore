# Source Corpus Inventory

## Scope

Read-only inventory for the global RE campaign in `/home/juanr/Proyectos/OpenSpore`.

Only these files were written:

- `knowledgegraph/research/types/00-corpus-inventory.json`
- `knowledgegraph/research/types/00-corpus-inventory.md`

No OpenSpore implementation, `SPORE/`, binary, Ghidra database, SQLite database, SDK tree, or historical triage artifact was modified. No Ghidra program was open, so no live Ghidra query was attempted.

The JSON companion is the complete machine-readable record: sorted artifact records, hashes, provenance, evidence, confidence, limitations, conflicts, and research leads.

## Evidence authority

Use the following precedence:

1. Pinned binary bytes and replayable runtime traces.
2. Pinned Ghidra exports, raw xrefs, and raw decompiler captures.
3. Pinned Spore-ModAPI Ghidra XML names and layouts.
4. `f0e310e0` triage-v6 projections, Track B, readiness, debtmap, attribution, and xref closure.
5. Global-campaign tracks, decomp-gap partitions, dossiers, and analysis reports.
6. Current OpenSpore source, contracts, tests, and fixtures.
7. SQLite knowledge graph and sidecar tooling.
8. Historical project status and narrative documentation.

Decompilation, SDK names, vtable candidates, triage categories, current source, and SQLite edges are evidence inputs. They do not independently establish original runtime behavior.

## Pinned identity

| Item | Identity |
|---|---|
| Binary | `SPORE/SporeBin/SporeApp.exe` |
| Version | `3.1.0.22` |
| Architecture | `x86:LE:32` |
| Image base | `0x00400000` |
| Binary SHA-256 | `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e` |
| Canonical triage snapshot | `f0e310e0` |
| Canonical triage SHA-256 | `5fd07ad16b85da68716e7e7fe2c1fcbc78e397888b532c0c09783b4480b6321e` |
| Xref snapshot | `2540f2ca` |
| Xref edge SHA-256 | `89e74b8a03c4db38a1927f8c95c38db507bf99cb8a11de6b6eb6a9484d8c79cb` |
| SDK XML | `/home/juanr/apps/Spore-ModAPI/SDKtoGhidra/SporeGhidra_march2017.xml` |
| SDK XML SHA-256 | `5d894677c1835082da0392e8b794f3c93a0251733898c3c5b81cf7945f458f09` |
| SDK repository HEAD | `cbf9206b9a823f0911cd9be0217104a49d72380b` |
| Repository HEAD | `260c7cefc409465c755731a03418fd360530b07c` |

The SDK is GPL-3.0 reference-only material. It is reverse-engineered community metadata, not EA source.

## Corpus inventory

### Semantic atlas

- `knowledgegraph/research/semantic-atlas.json`
- `docs/analysis/semantic-atlas.md`
- SHA-256: `fc6365ecf2bff17b5aec5d74bcbed034139cbfc231163ac03b332f98f35eb85a`
- Schema: `openspore-semantic-atlas-1`
- Status: `MACHINE_READABLE_RESEARCH_ATLAS`

Declared counts:

| Measure | Count |
|---|---:|
| Canonical functions / unique VAs | 58,757 |
| Ghidra manager entries | 59,245 |
| Ghidra-only external functions | 488 |
| Reference edges | 223,704 |
| Ghidra structures | 2,035 |
| Structure fields | 25,546 |
| SDK-associated structure names | 264 |
| Reconstruction packages | 23 |
| Readiness queue rows | 368 |
| Queue rows inside canonical universe | 365 |
| Queue rows outside canonical universe | 3 |
| Runtime-validated functions | 0 |
| Canonical contracts unknown | 58,757 |
| Contradictions | 29 |
| Unresolved questions | 92 |

The atlas is a synthesis. Its source manifest, counts, and contradiction records must be retained; it is not a replacement for raw Ghidra, SDK, xref, or runtime evidence.

### Global campaign

Directory: `knowledgegraph/research/global-campaign-2026`

- 27 JSON files
- 10 primary track JSONs
- 2 source/integration JSONs
- 15 verification/validation JSONs

Primary tracks:

- Track A: architecture and implementation surface
- Track B: function accounting
- Track C: gameplay contract ledger, 2,149 records
- Track D: Simulator Cell
- Track F: empire, civilization, progression, economy, resources, and modes
- Track G: editor, UI, input, and animation
- Track J: dependency graph and unlock order
- Track K: engine boundaries
- Track O: packages and testability
- Track P: coverage and live decompilation probes

Verification outputs are historical machine checks. Their PASS/FINDINGS status does not promote static evidence to runtime truth. Track P records 478 persisted canonical bodies, 172 persisted gameplay bodies, 996/996 sampled unavailable functions returning nonempty live decompilation, 99/99 sampled unavailable gameplay functions returning nonempty live decompilation, and zero runtime-validated functions.

The complete 27-file hash and status inventory is in the JSON companion.

### Decomp-gap artifacts

Directory: `knowledgegraph/research/decomp-gap`

- 16 JSON artifacts
- 1,901 active decomp-gap target records
- 76 held characterization-only records
- 1,977 total records
- 8 `sim-core` shards, 175 records each

| Cluster or class | Artifact | Records |
|---|---|---:|
| editor-core | `editor-core-00.json` | 223 |
| editor-support | `editor-support-00.json` | 66 |
| gameglobal-misc | `gameglobal-misc-00.json` | 35 |
| held infrastructure | `hold-infrastructure.json` | 76 |
| sim-core-systems | `sim-core-00.json` through `sim-core-07.json` | 1,400 |
| sim-space | `sim-space-00.json` | 5 |
| sporepedia-online | `sporepedia-online-00.json` | 69 |
| terrain-world | `terrain-world-00.json` | 93 |
| ui-shell | `ui-shell-00.json` | 10 |

The partitions are targeted read-only recovery queues, not the full missing-body population. Some contain targeted live Ghidra observations, but bodies and readiness promotions are not persisted. Missing persisted bodies are uncaptured evidence, not proof that Ghidra cannot decompile.

### Dossiers

Directory: `docs/analysis/dossiers`

- 16 JSON dossiers
- 16 paired Markdown dossiers
- Schema: `re-dossier-1`
- 24 dossier function records total

Topics:

- `cell-movement`
- `cell-object-pool-lifecycle`
- `empire-idcolor-pick`
- `gamemode-state-player-id`
- `message-handler-registration`
- `pdtk-text-widget`
- `sim-object-lookup-strategy`
- `sim-singleton-accessors`
- `sim-singleton-accessors-2`
- `sim-singleton-accessors-3`
- `sim-singleton-accessors-4`
- `space-event-record-pair`
- `space-player-data-accessors`
- `space-player-data-accessors-2`
- `space-player-data-accessors-3`
- `star-system-regen`

Dossiers are bounded synthesis. They are useful for function, caller, callee, vtable, struct, source, and known-unknown pointers, but they do not replace raw Ghidra, SDK, xref, or runtime evidence. Unknown-high dossiers have no runtime trace. Most field meanings remain inferred even when offsets are observed.

### SDK import corpus

Pinned XML counts:

| Element | Count |
|---|---:|
| FUNCTION rows | 1,670 |
| Unique function addresses | 1,663 |
| Duplicate address instances | 7 across 5 addresses |
| STRUCTURE | 1,895 |
| UNION | 15 |
| ENUM | 286 |
| ENUM_ENTRY | 2,937 |
| TYPE_DEF | 197 |
| FUNCTION_DEF | 4,280 |
| MEMBER | 22,056 |
| PARAMETER | 9,362 |
| DEFINED_DATA | 76 |
| SYMBOL | 314 |

The defensive importer is `tools/ghidra/ImportSporeSDK.java`, SHA-256 `dfa759aa80b3d862fdc27fabb0e5ff65fade87957ca20425f155d03a06af1a29`.

Keep these SDK populations separate:

- Raw XML: 1,670 function rows, 1,663 unique addresses
- Campaign import reports: 1,666 rows
- Narrative reports: 1,670/1,671 named functions
- Older missing-entry reports: 1,188
- Repaired adjudication: 1,186

A name match is name-level provenance only. Duplicate SDK addresses can alias multiple declarations.

### Function triage

Directory: `knowledgegraph/triage`

The current directory contains 26 files. The authoritative function ledger is:

- `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl`
- 58,757 rows
- 58,757 unique VAs
- Artifact version: `triage-v6`
- Row `classifier_version`: `triage-v5`
- SHA-256: `5fd07ad16b85da68716e7e7fe2c1fcbc78e397888b532c0c09783b4480b6321e`

Important triage counts:

- 20 clusters
- 1,171 SDK-name associations
- 1,501 vtable-family associations
- 6,261 P1 rows
- 159 P0 rows
- 39,716 UNKNOWN category rows
- 368 readiness rows, of which 3 are outside the canonical universe

The file name/summary version and row classifier metadata are intentionally not normalized.

### Xrefs

- `knowledgegraph/triage/xrefs-2540f2ca.tsv`
- 223,704 unique edges from 223,760 raw rows
- 56 duplicate triples removed
- SHA-256: `89e74b8a03c4db38a1927f8c95c38db507bf99cb8a11de6b6eb6a9484d8c79cb`
- `knowledgegraph/triage/xrefs-2540f2ca.externals.tsv`
- 362 external allowlist destinations
- `knowledgegraph/triage/xrefs-2540f2ca.summary.json`
- `tools/ghidra/ExportXrefs.java` is the exporter

Reference types:

| Type | Count |
|---|---:|
| direct-call | 197,461 |
| computed-call | 741 |
| thunk | 4,074 |
| external | 5,481 |
| vtable-ref | 11,898 |
| data-ref | 4,049 |

Closure claims all callers pinned and callees pinned or allowlisted. Data and vtable references are not call-type edges. Dest-less indirect calls are skipped rather than fabricated.

### Vtables

- Export: `docs/analysis/vtables.json`
- SHA-256: `f4161d3d99441ca4e84a2dcae6de2f4d83b3d9d2df2872e45bee8ee8f8d7f96f`
- Detector: `tools/ghidra/VtableDetect.java`
- Detector SHA-256: `a26a88607542e40891c5e54a4b855380d13405a5b375579b22e5c5622d82e9d2`

| Measure | Count |
|---|---:|
| Candidates | 3,081 |
| High confidence | 369 |
| Medium confidence | 871 |
| Low confidence | 1,841 |
| Labels | 20 |
| Shared-slot clusters | 16,107 |
| Prefix inheritance chains | 12 |
| Words scanned | 778,058 |
| Instructions scanned | 4,618,029 |
| Distinct vcall displacements | 74 |

The detector scans `.rdata` and `.data` for executable-pointer runs, cross-checks virtual-call displacements and SDK slot names, clusters shared slots, and detects prefix chains. The export reports 58,756 functions while the canonical ledger reports 58,757. There is no MSVC RTTI, and only 20 labels are written. These are structural candidates, not a complete class hierarchy.

### SQLite and knowledge-graph tools

Schema: `knowledgegraph/schema.sql`, SHA-256 `f9bb0bdc7d2095e523eb1610baa606541c7a957f1fb8362500d4f4618d6ecef8`

CLI: `knowledgegraph/kg.py`, SHA-256 `9c7e1d5d61e039c8907e80a34bac1d6d92c6cb607d9c804f4e1ce69579753ec8`

Current read-only database query:

- Database: `knowledgegraph/spore.db`
- SHA-256: `9612697643ebe6d5a20b61f941622b129cfa277937c843cb3fd1a79dab3843f8`
- `PRAGMA user_version`: 4
- `PRAGMA integrity_check`: `ok`
- 9 tables
- 65,661 nodes
- 26,508 edges
- 25,561 fields
- 1,704 investigations
- 28 test results
- 2 trace runs
- 58,757 triage rows
- 223,704 xref rows

The database is generated, WAL-enabled, and mutable. The query above used a read-only SQLite URI. `kg.py` itself opens a normal connection and can migrate or write; the viewer is read-only, but the KG CLI is not.

Relevant tooling:

- `knowledgegraph/seed.py`
- `knowledgegraph/seed_sprint.py`
- `knowledgegraph/seed-literals.json`
- `knowledgegraph/scale.py`
- `tools/kg_ingest.py`
- `tools/triage/classify.py`
- `tools/triage/debt_map.py`
- `tools/triage/export_xrefs.py`
- `tools/triage/repair_sdk_boundaries.py`
- `tools/mcp/kg_tools.py`
- `tools/viewer/query.py`
- `tools/viewer/server.py`

## Current `src/` comparison points

The current source tree has 92 files and 598,072 bytes:

| Directory | Files |
|---|---:|
| `src/` root | 1 |
| `src/apps` | 24 |
| `src/assets` | 32 |
| `src/compat` | 2 |
| `src/renderer` | 8 |
| `src/replace` | 6 |
| `src/sim` | 19 |

### Cell static and contract components

- `src/sim/CellGame.cpp`, `src/sim/CellGame.hpp`
- `src/sim/CellPool.hpp`
- `src/sim/CellQuery.hpp`
- `src/sim/Advect.hpp`
- `src/sim/Combat.hpp`
- `src/sim/Sim.cpp`, `src/sim/Sim.hpp`

These are clean-room Cell state, pool, query, advect, combat, and deterministic simulation components. They are current implementation facts and bounded static reconstructions, not a complete original runtime state machine.

### Replacement memory views

- `src/replace/CellGameView.hpp`
- `src/replace/Reference.cpp`
- `src/replace/Replace.cpp`
- `tools/re/data/decompiled/MovePlayerToMousePosition.c`

`CellGameView.hpp` explicitly aliases selected offsets and states that it is not the true class layout. Offsets are the strongest comparison point; meanings remain inferred and plane values remain approximate. The 64/64 differential is against decompilation evidence, not a live original trace.

### Cell mode, vtable, input, and UI

- `src/apps/IGameMode.hpp`
- `src/apps/CellModeStrategy.hpp`, `src/apps/CellModeStrategy.cpp`
- `src/apps/CellGfx.hpp`, `src/apps/CellGfx.cpp`
- `src/apps/CellInput.hpp`, `src/apps/CellInput.cpp`
- `src/apps/CellUI.hpp`, `src/apps/CellUI.cpp`
- `src/apps/CellAnim.hpp`, `src/apps/CellAnim.cpp`

These are reusable clean-room mode and presentation seams. They do not prove the original AppSystem, editor, message-dispatch, or runtime transition behavior.

### Typed asset records

- `src/assets/CellResource.hpp`, `src/assets/CellResource.cpp`
- `src/assets/Stream.hpp`
- `src/assets/WorldObject.hpp`, `src/assets/WorldObject.cpp`

These provide typed clean-room readers and value objects. Asset record structs are not automatically original runtime object layouts; WorldObject field order and placement semantics remain unresolved.

### Compatibility and renderer seams

- `src/compat/ResourceProvider.hpp`
- `src/compat/MeshSource.hpp`
- `src/renderer/Renderer.hpp`

These are narrow host-side boundaries. They do not reproduce the original ResourceManager, RenderWare, D3D, or complete graphics-device contracts.

## Main conflicts and limitations

1. The frozen canonical universe is 58,757 VAs; historical/live Ghidra manager counts report 59,245. The 488-entry difference is scope/snapshot drift until row-level reconciliation is available.
2. The vtable export reports 58,756 functions, one fewer than the canonical ledger.
3. SDK counts differ across raw XML, import reports, narratives, and repaired boundary adjudications. Preserve each population.
4. The v6 artifact name conflicts with v5 row classifier metadata.
5. The canonical body set has 478 addresses, while the file manifest has 477 decompiler exports plus one annotated capture; VA `0093b630` has two filenames.
6. Three readiness rows, `00e3a400`, `00e7b6c0`, and `00e7d2c0`, are outside the canonical universe.
7. Older structure counts report 1,895; current analysis reports 2,035 Ghidra structures. The current KG reports 25,561 fields, while the semantic atlas reports 25,546.
8. Older global KG counts report 65,461 nodes and 20,397 edges; the current read-only database reports 65,661 nodes and 26,508 edges.
9. Track O's 48,296 debt rows, triage-v6's 39,716 UNKNOWN category rows, and the debtmap's 35,771 genuinely unknown ownership rows are different populations.
10. The prior baseline hash for `docs/analysis/dossiers/cell-movement.json` differs from the current file hash. The current hash is recorded in the JSON companion; the baseline hash remains historical provenance.
11. There is no MSVC RTTI. Class and inheritance identity must remain bounded to vtable data, SDK structures, xrefs, and decompilation.
12. There is no positive original Cell runtime trace and zero function-level runtime validation in the atlas.
13. No build, test, Wine, game, or Ghidra execution was performed because this task was restricted to read-only inventory research.

## Recovery leads

1. Reconcile the 59,245-entry live manager against the 58,757 canonical ledger and resolve the vtable export's 58,756-function count.
2. Characterize the shared-state roots in this order: `00b3d300`, `00b3d2a0`, `00b5b800`, `00b3d350`, `01021260`, `00b1fdb0`, `00b21340`, `00e5c780`, `01021300`, `01021080`, `00ba9370`.
3. Resolve the 15-member accessor block at global `0x167eac0`; observed offsets include `+0x04`, `+0x20`, `+0x24`, and `+0x44`, but member identities are unresolved.
4. Cross-check the supported `SpacePlayerData` 0x34-byte layout, `cEmpire` 0x158-byte `mPoliticalID` at `+0x84`, and `cStarManager` 0x22c-byte map/empire fields.
5. Use the SDK-backed `cGameInputManager` 0x114-byte layout and 0x6c/27-slot vtable as an anchor, then match field offsets and virtual-call displacements to vtable candidates.
6. Map the `cCellModeStrategy` candidate vtable at `0x1485550` and SDK `IGameMode`/`IGameModeManager` relations without inferring RTTI.
7. Reconcile `cCellObjectData` 920 bytes and `cCellGame` 20,964 bytes with `mAvatarCellIndex` at `+0x411c`, the current selected CellGame view, and pool lifecycle callees.
8. Carve the 4,384-row `unknown-vtable-impl` cluster using 11,898 vtable-reference edges, 3,081 candidate bases, 369 high-confidence candidates, 16,107 shared-slot clusters, and 12 prefix chains.
9. Audit 1,186 SDK boundary adjudications before class inference: 848 contained repairs, 193 dead addresses, 141 tail aliases, 2 data/vtable-slot-not-code cases, and 2 prologue-recoverable cases.
10. Work the 1,901 active decomp-gap records as bounded queues, beginning with the 1,400 sim-core records, then editor, Sporepedia, terrain, UI, gameglobal, and space. Keep the 76 held records characterization-only.
11. Acquire a positive boot control and hash-pinned original Cell trace before promoting any class, field, callback, or gameplay meaning beyond static evidence.

## Verification of this inventory

The JSON was parsed successfully after writing. All referenced path/hash records were checked against current files, all SHA-256 fields are lowercase 64-hex strings, dossier JSON/Markdown pairs were checked, decomp-gap records sum to 1,977, and the listed triage files sum to the current 26-file directory inventory.
