# Miscellaneous / Unknown Types

## Scope and policy

This partition records high-value unclassified FUN/DAT/vtable/allocation/container/record patterns that remain type-open in the pinned SporeApp.exe 3.1.0.22 corpus. It is research-only: no implementation, triage rewrite, binary/Ghidra mutation, SPORE change, or runtime launch was performed.

- Binary: `SporeApp.exe`, x86-LE 32-bit, image base `0x00400000`
- Binary SHA-256: `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`
- Triage snapshot: `f0e310e0`; canonical universe: 58,757 VAs
- Xref snapshot: `2540f2ca`; deduplicated edges: 223,704
- Classifier provenance: triage-v6 artifact; row metadata still says triage-v5
- Ghidra: read-only only; no program was open, so no new Ghidra query or mutation was made

Evidence uses the repository scale `UNKNOWN < APPROXIMATION < INFERRED < SUPPORTED < CONFIRMED < OBSERVED < VERIFIED`. Current source is comparison-only. A `FUN_*` name, a `DAT_*` address, vtable proximity, fan-in, a source purpose label, or a current OpenSpore struct does not establish original type identity or ownership.

## Method and source register

1. Partition the unresolved corpus by cluster and package ownership.
2. Rank candidates by distinct fan-in, repeated layout/slot structure, cross-cluster consumers, and vtable leverage.
3. Recover only directly supported offsets, fields, slots, forwarding mechanics, and lifecycle edges.
4. Attach evidence level, confidence, provenance, contradictions, and a next evidence gate to each candidate.
5. Exclude known domain-owned types and current source projections from ownership claims.

| ID | Source | Use |
|---|---|---|
| `P01` | `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl` | VA identity, categories, clusters, names, priorities, vtable associations |
| `P02` | `knowledgegraph/triage/xrefs-2540f2ca.tsv` | Canonical caller, callee, data, and vtable-reference topology |
| `P03` | `knowledgegraph/research/global-campaign-2026/track-j-dependency-graph.json` | Fan forests, bridges, cross-cluster dependencies, unlock order |
| `P04` | `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json` | Map lower-bound mechanics and offsets |
| `P05` | `docs/analysis/vtables.json` | Vtable candidates, slots, scores, pair clusters, chains |
| `P06` | `docs/analysis/dossiers/unknown-high/space-event-record-pair.md` | Paired record construction and unresolved layout |
| `P07` | `knowledgegraph/research/decomp-gap/` | Targeted static records and consumer call-site observations |
| `P08` | `docs/analysis/semantic-atlas.md` | Canonical inventory, contract ceiling, package ownership, contradictions |
| `P09` | `src/` | Comparison-only clean-room projections |

## Inventory

| Population | Count | Relevance |
|---|---:|---|
| Canonical functions | 58,757 | Address-keyed universe |
| `UNKNOWN` triage rows | 39,716 | Category count, not a semantic partition |
| `unknown-fun-mass` | 44,978 | Long-tail non-vtable pool |
| `unknown-vtable-impl` | 4,384 | SDK-less vtable implementation pool |
| Debt-map UNKNOWN rows | 48,296 | Different population from triage category |
| Genuinely unknown debt ownership | 35,771 | Ownership projection, not semantic resolution |
| Vtable candidates | 3,081 | Candidate bases, not classes |
| Vtable references | 11,898 | Data references, not direct calls |
| Vtable pair clusters | 300 | Similarity clusters, not class identities |
| Vtable inheritance chains | 12 | Structural chains, not RTTI identities |
| Persisted bodies in `unknown-fun-mass` | 1 | Persisted body coverage is not live Ghidra capacity |
| Persisted bodies in `unknown-vtable-impl` | 0 | No persisted body in the canonical projection |

The dominant unknown-vtable and unknown-function populations are deliberately not bulk-read. The selected patterns are ranked by fan-in, cross-cluster reuse, structural regularity, and the amount of independently bounded evidence.

## Candidate patterns

| ID | Neutral pattern label | Primary VAs/data | High-value evidence | Evidence level | Confidence | Ownership |
|---|---|---|---|---|---|---|
| `MISC-AT-001` | Four-byte forwarding boundary pair | `00f47380`, `00f473a0`; targets `009276c0`, `009289f0` | 6,527 and 2,901 callers; one callee each; cross-domain call sites | `SUPPORTED` mechanics | High mechanics / low identity | Candidate unowned boundary |
| `MISC-BUF-001` | Opaque buffer/handle family | `009289f0`, `00928a30` | 20 and 35 callers; one callee each; WIN32 dependency hints | `INFERRED` | Low identity | Candidate unowned boundary |
| `MISC-STR-001` | Opaque string/localized-value wrapper family | `006b55c0`, `006b5770` | 263 and 93 callers; 5 and 2 callees; SEH-heavy source evidence | `SUPPORTED` mechanics | Low identity | Candidate unowned boundary |
| `MISC-MAP-001` | Map-like lower-bound container | `00e5c780`; related mutation helper `00ba8420` | 239 callers, 49 gameplay callers; offsets at `+0x04`, `+0x0c`, `+0x10`, `+0x14` | `SUPPORTED` mechanics | High mechanics / medium identity | Shared container; no domain owner |
| `MISC-VT-001` | Unattributed 40-slot vtable base | `0x013f1a30` | 40 slots, score 11, long-run candidate, no namespace | `SUPPORTED` structure | High structure / unknown identity | Candidate unowned vtable |
| `MISC-REC-001` | Paired 27/24-field record builder | `00e39ab0`; `DAT_0168de78`; `cTribe+0x504/508/50c` | 16 callers; record writes at `+0x64/+0x68`; pair of records | `INFERRED` | Medium mechanics / low identity | Contested overlap; no ownership assigned |

## Candidate layouts and slots

### `MISC-AT-001`: four-byte forwarding boundary

The stable observation is a pair of 32-bit forwarding roots, not an allocator type:

- `00f47380`: a nonzero argument is forwarded to `009276c0`; 6,527 distinct callers and 3,910 leafish callers are recorded by the dependency projection.
- `00f473a0`: six arguments are forwarded to `009289f0`; 2,901 distinct callers are recorded.
- Concrete object size, argument meanings, return type, null behavior, ownership, and allocation/destruction side effects remain unknown.
- The source purpose labels “free” and “alloc” are retained as provenance only and are not used as type names.

### `MISC-BUF-001`: opaque buffer/handle family

`009289f0` and `00928a30` are neighboring unknown functions with one internal callee each and WIN32 external-dependency hints. The source adjudication calls the region thread-safe buffer operations, but no buffer, lock, element, or owner layout is committed. This remains a low-identity targeting family only.

### `MISC-STR-001`: opaque string/localized-value wrapper family

`006b55c0` and `006b5770` are high-fan-in `ENGINE_IMPLEMENTATION` rows in the `Unknown` subsystem. Their source purpose is SEH-heavy cString/LocalizedString handling, but no stable field offsets, object size, return contract, or ownership is recovered. The family is not renamed as a string type.

### `MISC-MAP-001`: map-like lower-bound container

| Offset | Structural observation | Status |
|---|---|---|
| `container+0x04` | map end storage/sentinel candidate | `SUPPORTED` |
| `container+0x0c` | map root pointer candidate | `SUPPORTED` |
| `node+0x10` | node key candidate | `SUPPORTED` |
| `node+0x14` | node payload candidate | `SUPPORTED` |

`00e5c780` performs unsigned lower-bound, not exact find. It has no direct internal callee and no observed mutation. Related consumers may materialize or insert through separate helpers, including `00ba8420` and `00b21340`; that does not move mutation into the lower-bound helper. The exact EASTL type, key/value domains, iterator encoding, and owner remain unresolved.

The old message-handler-registration interpretation is preserved as a contradiction and is not selected over the later map/vector mechanics.

### `MISC-VT-001`: unattributed vtable base

The vtable artifact records `0x013f1a30` as an unattributed, 40-slot, long-run candidate with score 11. The candidate is recorded structurally as:

```text
object+0x00 -> opaque vtable pointer
vtable+4*n   -> method slot candidate, n = 0..39
```

Committed vtable archaeology further reports 38 implemented slots, 0 inherited slots, 0 overridden slots, and 2 unknown slot indices (`0` and `10`). It records 17 method-address entries and 71 unique consumer VAs, including representative consumers `0x00410cc0`, `0x00418870`, `0x0041a980`, `0x004301e0`, `0x004329e0`, `0x004346b0`, `0x004575d0`, `0x00469590`, `0x0046a750`, `0x0047d6a0`, `0x004b24c0`, and `0x004bab30`.

The recorded method-address entries are `FUN_00402ab0`, `FUN_00461290`, `FUN_00472970`, `FUN_004cc320`, `FUN_00516da0`, `FUN_00516e10`, `FUN_00517160`, `FUN_005172c0`, `FUN_00517400`, `FUN_005182f0`, `FUN_0051a900`, `FUN_0051d090`, `FUN_0051e340`, `FUN_0051e380`, `FUN_0056f2b0`, `FUN_007f9b80`, and `purecall`. These are structural method addresses, not semantic names. No class identity, construction site, slot meaning, or ownership is promoted. The artifact’s 3,081 candidate bases, 300 pair clusters, and 12 inheritance chains are structural evidence only. The binary has no MSVC RTTI, and vtable proximity is not class proof.

### `MISC-REC-001`: paired record builder

`00e39ab0` builds a pair of records described by the dossier as 27-field and 24-field records. The observed record content includes:

- an object reference;
- cell/object IDs obtained through `00e39450` and `00e39420`;
- a millisecond timestamp derived from `00b316c0/1000`;
- a default slot value whose observed constant is `0x53dbcf2` (`-10` as reported by the dossier);
- additional IDs and float3 positions;
- writes at `record+0x64` and `record+0x68`.

Positions come from arguments or from a 6,624-byte `cTribe` candidate at `+0x504`, `+0x508`, and `+0x50c`. The global `DAT_0168de78` is read but has no recovered meaning. Record field order and byte sizes remain unknown because the two layouts are absent from the SDK TSV.

The record is included only as an unresolved record ABI reused by multiple event/tool paths. Its Simulator/Space consumer overlap is not treated as ownership of the type.

## Hot offsets and data patterns

| Candidate | Offset/address | Meaning | Status |
|---|---|---|---|
| `MISC-AT-001` | argument/return words | opaque 32-bit forwarding values | `INFERRED` |
| `MISC-MAP-001` | `container+0x04` | map end storage/sentinel candidate | `SUPPORTED` |
| `MISC-MAP-001` | `container+0x0c` | map root pointer candidate | `SUPPORTED` |
| `MISC-MAP-001` | `node+0x10` | node key candidate | `SUPPORTED` |
| `MISC-MAP-001` | `node+0x14` | node payload candidate | `SUPPORTED` |
| `MISC-VT-001` | `vtable+4*n`, `n=0..39` | structural method-slot range | `STRUCTURAL_ONLY` |
| `MISC-REC-001` | `record+0x64` | observed record write | `INFERRED` |
| `MISC-REC-001` | `record+0x68` | observed record write | `INFERRED` |
| `MISC-REC-001` | `cTribe+0x504/508/50c` | three position-source components | `INFERRED` |
| `MISC-REC-001` | `0x0168de78` | read global, meaning unknown | `UNKNOWN` |

No slot or offset is marked hot by execution frequency. “Hot” here means repeatedly touched or high-value structural evidence, not runtime hotness.

## Lifecycle and consumer clusters

| Candidate | Observed lifecycle boundary | Consumer clusters | Unresolved lifecycle facts |
|---|---|---|---|
| `MISC-AT-001` | caller -> 32-bit forwarder -> one internal target | editor-core, editor-support, sim-core-systems, sim-space, terrain-world, ui-shell | allocation/release, ownership, null behavior, return type |
| `MISC-BUF-001` | caller -> unknown region family -> one internal target; WIN32 hint | unknown-fun-mass | buffer lifetime, lock, storage owner |
| `MISC-STR-001` | caller -> SEH-heavy wrapper -> string/localized helpers | editor-core, editor-support, sim-core-systems, ui-shell | temporary ownership, exception boundary, output contract |
| `MISC-MAP-001` | owner map -> lower-bound result -> lookup/materialization consumer | gameglobal-misc, sim-core-systems, sim-space consumer paths | key/value types, iterator, insertion ownership, event meaning |
| `MISC-VT-001` | unattributed base -> 40 structural slots -> unknown implementations | unknown-vtable-impl; vtable-ref only | class, object construction, slot meaning, virtual ownership |
| `MISC-REC-001` | inputs/global DAT -> two records -> downstream event/tool consumers | sim-core-systems, sim-space consumer paths | allocation mechanism, field order, consumer ownership, serialization |

Consumer-cluster membership is structural evidence. It is not a runtime call trace and does not establish domain ownership.

## Ownership boundaries

The following are explicitly excluded from this partition because they already have bounded package or domain ownership:

- `00b3d300`, `00b3d2a0`, `00b5b800`, `01021260`, `00b1fdb0`, `00b21340`, `01021300`, `01021080`, `00b25fb0`, and `00ba9370`: existing PKG-01/shared-state interface material. This report does not rewrite it.
- `00e780a0`: Cell object-pool lifecycle owned by the Cell state package; `src/sim/CellPool.hpp` is comparison only.
- SDK-associated UI/editor construction, message, and load records such as `005bfd40`, `005c0100`, `005c0380`, `00603650`, `00834fa0`, `00962950`, `0106e3e0`, and `01073700`: UI/editor/application domains.
- DBPF, QFS, GMDL, RW4, raster/DXT5, and CellResource records: asset/content packages.
- The 4,075-row runtime/CRT/STL cluster: explicitly out of scope.

No candidate in this file is renamed, added to triage, assigned a package owner, or promoted to `READY`.

## Current source comparison

Current source was used only to prevent category confusion:

- `src/sim/CellPool.hpp:1-16,23-56,66-162` models a clean-room 28-byte seven-field free-list pool, a 0x398-byte Cell object comparison, and 4,096 capacity. It does not establish the type of `00f47380` or `00f473a0`.
- `src/sim/CellQuery.hpp:1-18,27-82` models a clean-room 28-byte query entry and linked/arena projection. It is Cell-domain comparison, not evidence for the unknown vtable or map candidates.
- `src/sim/Advect.hpp:1-21,29-43` models a 24-byte owned Cell table record. It is not evidence for the unclassified 27/24-field record pair.
- `src/assets/Dbpf.hpp:16-46` and `src/assets/Stream.hpp:13-109` model package rows and a bounds-checked byte cursor. They are asset/source comparison only.
- `src/assets/Rw4.hpp:1-22,35-43,67-79` models a 24-byte RW4 section record and explicitly leaves unknown type codes informational. It is asset-domain comparison only.

## Contradictions and integrity

1. `unknown-fun-mass` has 44,978 v6 cluster rows while the debt map has 48,296 UNKNOWN debt rows. These are different populations and are not merged.
2. `unknown-vtable-impl` has 4,384 canonical rows, while one vtable-pool category projection contains 5,758 `ENGINE_IMPLEMENTATION` rows. The current canonical Track B count is retained and the discrepancy is preserved.
3. `vtables.json` reports 58,756 functions, while the canonical triage/xref universe is 58,757. Snapshot/scope drift is retained.
4. The vtable pool has 3,081 candidate bases, 11,898 vtable references, 300 pair clusters, and 12 inheritance chains; these are not a one-to-one class or slot inventory.
5. The triage-v6 filename/summary and triage-v5 row metadata remain a provenance discrepancy. VA-keyed fields are used without historical triage rewriting.
6. The semantic atlas keeps all 58,757 canonical function contracts unknown. Static decompilation, SDK names, vtable proximity, current source, and package candidates are not runtime truth.
7. Runtime evidence remains negative for the original Cell path; no function here is `OBSERVED` or `VERIFIED`.

## Next actions

1. **P1 — allocation boundary:** read-only decompile/disassemble `00f47380`, `00f473a0`, `009276c0`, and `009289f0`; record exact register/stack ABI, return behavior, and null paths before assigning allocator terms.
2. **P1 — generic map:** correlate `00e5c780`, `00ba8420`, and `00b21340`; identify owner, key/value widths, mutation boundary, and iterator encoding. Keep the old message-handler interpretation excluded unless re-established.
3. **P1 — vtable carving:** correlate `0x013f1a30` with the 300 pair clusters and 12 chains; use stable slot-vector and construction/caller evidence only, never RTTI or namespace proximity.
4. **P2 — record ABI:** recover the `00e39ab0` 27/24-field layouts from the constructor and at least two independent consumers, including all offsets, sentinel handling, and ownership.
5. **P2 — wrapper family:** decompile `006b55c0` and `006b5770` together and compare exception paths, temporaries, outputs, and consumer shapes; do not call the family a string type yet.

## Provenance

- `docs/analysis/semantic-atlas.md:1-324`
- `knowledgegraph/research/track-b-function-accounting.json:92-100,101-266,268-282,823-879`
- `knowledgegraph/research/global-campaign-2026/track-j-dependency-graph.json:677-697,724-760,762-884`
- `knowledgegraph/triage/clusters-f0e310e0-v6.json:1-4,690-829`
- `knowledgegraph/triage/unknown-high-investigation-f0e310e0.json:12343-12421,16327-16402,31805-31877`
- `knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json:234-281,287-295`
- `docs/analysis/dossiers/unknown-high/space-event-record-pair.md:18-40,77-83`
- `docs/analysis/dossiers/unknown-high/space-event-record-pair.json:32-58,88-120`
- `docs/analysis/vtables.json:2-9`
- `knowledgegraph/research/global-campaign-2026/track-o-packages-testability.json:463-493,526-531`
- `knowledgegraph/triage/debtmap-f0e310e0.json:2820-2834,6213-6228,61964-62001`
- `knowledgegraph/research/global-campaign-2026/track-p-coverage.json:237-247`
- `docs/analysis/unknown-high-resolution.md:72-92`
- `src/sim/CellPool.hpp:1-16,23-56,66-162`
- `src/sim/CellQuery.hpp:1-18,27-82`
- `src/sim/Advect.hpp:1-21,29-43`
- `src/assets/Dbpf.hpp:16-46`
- `src/assets/Rw4.hpp:1-22,35-43,67-79`
- `src/assets/Stream.hpp:13-109`

## Integrity

- Only `knowledgegraph/research/types/16-misc-unknown.json` and `.md` were written by this partition.
- No implementation, SPORE, triage, database, binary, symbol, or Ghidra mutation occurred.
- No proprietary EA source, model, texture, sound, script, or asset payload was reproduced.
- No timestamp or generated-at field is present.

## Determinism

- JSON arrays use stable candidate ID, VA, path, or cluster ordering.
- No timestamps are present.
- No implementation, SPORE, triage, database, binary, symbol, or Ghidra mutation occurred.
