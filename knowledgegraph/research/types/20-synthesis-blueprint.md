# Type Archaeology Synthesis Blueprint

## Purpose

`20-synthesis-blueprint.json` defines the deterministic normalization and merge plan for a future `type-archaeology.json`. It is a blueprint, not a second set of type claims. The final artifact must remain grounded in the pinned Spore binary, explicit source evidence, and preserved worker disagreements.

The blueprint uses the baseline from worker `00`:

- Binary: `SporeApp.exe`, version `3.1.0.22`, `x86:LE:32`.
- Image base: `0x00400000`.
- Binary SHA-256: `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`.
- Triage snapshot: `f0e310e0`.
- Xref snapshot: `2540f2ca`.
- Baseline inventory: 58,757 functions and 223,704 xrefs.
- No MSVC RTTI: identity must be derived from SDK names, bytes, vtables, layouts, and xrefs without claiming compiler-emitted RTTI.

## Final Artifact Shape

The final artifact must contain these top-level sections, in this order:

1. `$schema`
2. `metadata`
3. `provenance`
4. `limitations`
5. `types`
6. `aliases`
7. `fields`
8. `vtables`
9. `slots`
10. `inheritance`
11. `lifecycle`
12. `methods`
13. `evidence`
14. `semantic_subsystems`
15. `reconstruction_relevance`
16. `unresolved_questions`
17. `conflicts`
18. `metrics`

Every substantive record carries stable IDs, source-record references, evidence IDs, unresolved-question IDs where applicable, and conflict IDs where applicable. Worker prose is preserved as evidence; it is not silently promoted to primary binary or runtime evidence.

## Evidence Model

`EvidenceRecord` retains the source artifact, source hash, JSON pointer or stable record reference, source-native level, observation scope, confidence wording, and the narrow raw claim.

The controlled source-level vocabulary is `UNKNOWN`, `INFERRED`, `SUPPORTED`, `OBSERVED`, `CONFIRMED`, and `VERIFIED`. Source-only terms such as `APPROXIMATION` and naming-only statuses remain verbatim in `source_level`.

Normalized support is separate from source wording and from observation scope. In particular:

- Only explicit original-runtime evidence can set `runtime_observed: true`.
- A decompiled body is static evidence, not runtime behavior.
- SDK names, names-only families, and current OpenSpore source comparisons do not prove original runtime identity.
- A shared vtable prefix or shared field layout is structural evidence, not automatically language-level inheritance.
- A manager, pool, factory, or accessor does not prove exclusive ownership by itself.

## Record Contracts

### Types and aliases

`TypeRecord` is the identity hub. It records canonical name, qualified name, namespace, kind, `origin_class`, `identity_status`, layout claims, semantic claims, and references to aliases, fields, vtables, inheritance, lifecycle, methods, subsystems, reconstruction relevance, questions, and conflicts.

`origin_class` is one of:

- `original_binary`
- `sdk_reference`
- `current_comparison`
- `worker_candidate`
- `shared_layout`
- `synthetic_global`

`identity_status` is one of `confirmed`, `supported`, `observed`, `inferred`, `naming_only`, `candidate`, or `unknown`. A current comparison remains separate from an original type unless an explicit source establishes equivalence.

`AliasRecord` stores SDK names, SDK paths, short names, numeric resource IDs, binary labels, function labels, naming-only labels, and current comparisons. Alias equivalence is one of `exact`, `qualified`, `contextual`, `address_alias_only`, `comparison_only`, or `ambiguous`. A name match never merges two types when namespace, owner, origin, or scope differs.

### Fields

`FieldRecord` is an identity cluster with alternative `offset_claims`, `type_claims`, access claims, and semantic role claims. Conflicting offsets, sizes, owners, and field types are preserved and create a `ConflictRecord`; they are not overwritten.

A range or multi-offset source group is not split into arbitrary fields without disjoint exact boundaries. A global offset without an owner remains a shared-layout or synthetic-global field and is not assigned to a nearby type by proximity.

### Vtables and slots

`VtableRecord` separates `structure_status`, `boundary_status`, and `identity_status`. A vtable can be structurally observed while its concrete type identity remains only a candidate.

`SlotRecord` is keyed by vtable and zero-based index. Exact pointer-width arithmetic must agree with the reported offset. Conflicting target addresses or names remain target and name alternatives. The global 3,081-vtable inventory is a metric; only selected or explicitly persisted worker vtable records become vtable rows.

### Relations, lifecycle, and methods

`InheritanceRecord` distinguishes SDK declarations, binary shared prefixes, address-bearing family relations, header containment, composition, embedding, and candidate shared bases. Only an explicit `language_level` value may say language-level inheritance.

`LifecycleRecord` preserves source step order, triggers, operations, preconditions, postconditions, allocation, ownership, cleanup, factories, and managers. A list of stages is not promoted into a complete lifecycle without sequence evidence.

`MethodRecord` indexes by exact program entry address when available and otherwise by source identity. Multiple names for one address are name claims on one method, while source address aliases remain explicit. A method may have a partial or absent body and still retain a source association.

### Semantics, reconstruction, unknowns, and conflicts

`SemanticSubsystemRecord` uses controlled domains from worker `15` and links roots, owners, managers, methods, and global state. `ReconstructionRelevanceRecord` stores `preserve`, `replace`, `defer`, `gate`, `investigate`, or `unknown` classifications separately from original-binary confidence.

`UnresolvedQuestionRecord` clusters semantically identical questions while retaining every source wording. `ConflictRecord` stores observations, authority class, source scope, source level, evidence, and the merge decision. The default decision for a genuine disagreement is `do_not_collapse`.

### Metrics

`MetricsRecord` contains final counts, coverage, merge diagnostics, metric definitions, and source metric references. Baseline function and xref counts remain separate from canonical method and call-edge counts. Unknown populations are `null` or `unknown`, never zero.

## Worker Mapping

The JSON provenance manifest contains the complete top-level section map and both hashes for each worker.

| Worker | Main source material | Final destination |
|---|---|---|
| `00` | Corpus identity, authority, inventory, coverage, leads | metadata, provenance, limitations, conflicts |
| `01` | Simulator/core normalized records | types, aliases, fields, vtables, slots, relations, lifecycle, methods |
| `02` | Gameplay entity and Cell families | same direct record families as `01` |
| `03` | Creature and data types | same direct record families as `01` |
| `04` | World/planet taxonomy, layout, serialization, consumers | types, fields, lifecycle, semantics, reconstruction |
| `05` | Empire/space registry, vtables, player state, ownership | types, aliases, vtables, lifecycle, methods, conflicts |
| `06` | Editor/UI catalog, factories, ownership, replaceability | types, vtables, inheritance, lifecycle, methods, reconstruction |
| `07` | Events, functions, dispatch, producer/consumer, serialization | types, methods, vtables, lifecycle, semantics, evidence |
| `08` | Persistence layouts, primitives, function map, dispatch | types, fields, methods, vtables, lifecycle, serialization claims |
| `09` | Content types, containers, descriptors, handles, consumers | types, fields, vtables, lifecycle, methods, semantics |
| `10` | Managers, accessors, service slots, registries, pools | types, fields, slots, methods, lifecycle, reconstruction |
| `11` | Selected vtables, slots, field consumers, constructor patterns | vtables, slots, fields, inheritance, lifecycle, methods |
| `12` | High-value offsets and shared layouts | fields, shared-layout types, reconstruction comparison |
| `13` | Object lifecycle, ownership, factories, pools, cleanup | lifecycle, types, methods, ownership, relations |
| `14` | Families, aliases, trees, binary relations, call patterns | types, aliases, fields, vtables, inheritance, methods |
| `15` | Assessments, domains, interfaces, unknown unlockers | semantic subsystems, reconstruction relevance, questions |
| `16` | Candidate layouts, patterns, offsets, consumers, boundaries | candidate types, fields, vtables, lifecycle, questions |

All 1,250 worker-14 families and all 1,199 naming-only families must be represented as qualified type/alias records or explicit dispositions. The 33 selected vtable records in worker 11 must be retained, while the global vtable inventory remains a metric.

## Deterministic Merge Order

1. Verify JSON and Markdown hashes and parse every worker artifact.
2. Create source-native evidence records before merging.
3. Normalize names, addresses, offsets, paths, and IDs.
4. Build alias indexes by owner, kind, namespace, and exact value.
5. Build identity-separated types, including SDK-only, candidate, naming-only, shared-layout, and global records.
6. Build field clusters and preserve all offset/type alternatives.
7. Build selected vtables and validate pointer-width slot arithmetic.
8. Build inheritance, lifecycle, and method records from explicit evidence.
9. Build semantic subsystem and reconstruction relevance records.
10. Cluster questions and conflicts without discarding source wording.
11. Compute post-merge metrics and coverage.
12. Validate references, hashes, ordering, determinism, and prohibited fields.

Exact canonical identity keys may merge records when origin and semantic scope match. Ambiguous names, different owners, different origins, and current-source comparisons remain separate. A source conflict is resolved only by preserving alternatives and marking a preferred claim when authority precedence genuinely applies; an unresolved tie remains unresolved.

## Required Validation

- Top-level keys exactly match the declared order.
- IDs are unique and references resolve to the correct record kind.
- Every substantive record has at least one evidence ID and source pointer.
- Every source pointer resolves to the pinned worker bytes.
- Arrays are deterministically sorted.
- Addresses and offsets are canonicalized.
- Source wording and source confidence are preserved.
- No timestamps, generated-at fields, random UUIDs, machine paths, or process IDs exist.
- No current-source comparison confirms original identity or runtime behavior.
- No shared prefix, field overlap, pool, or accessor is automatically promoted to inheritance or ownership.
- All worker top-level sections have a target and coverage disposition.
- Final counts are separate from source inventory counts and selected-record counts.

The extraction must stop on a hash, parse, or reference failure. Contradictions may continue only when all alternatives are retained and a conflict record is emitted.

## Quality Gate

Before accepting the final `type-archaeology.json`, run the repository's parser, structural validation, and any available JSON lint/format checks. Then inspect the generated diff to ensure only the two approved blueprint files changed and no Ghidra project, binary, knowledge graph, or source implementation was modified.
