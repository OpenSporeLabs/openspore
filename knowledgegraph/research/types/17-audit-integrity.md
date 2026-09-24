# 17 — Research Type Artifact Integrity Audit

## Scope

This read-only audit covers the 17 worker partitions `00` through `16` in `knowledgegraph/research/types/`, including each JSON file and matching Markdown file. It does not modify worker artifacts, source, Ghidra state, `SPORE/`, the knowledge-graph database, or historical files.

The audit checks parsing and pairing, deterministic ordering, source references and locators, identifiers, evidence/status/confidence vocabularies, declared counts, section coverage, and isolated-output compliance.

## Result

**Status: audit complete; normalization required.**

All 17 JSON files parse and all 17 Markdown counterparts exist. The artifacts consistently describe static, clean-room research and generally declare no implementation, binary, Ghidra, database, historical-artifact, or `SPORE/` mutation. The corpus is not yet suitable for lossless automated synthesis without normalization.

| Check | Result | Main finding |
|---|---|---|
| JSON parsing | Pass | 17/17 parse |
| JSON/Markdown pairing | Pass | 17/17 pairs present |
| Source references | Fail | Two stale exact paths |
| Identifiers | Fail | Three ambiguous identity namespaces |
| Vocabularies | Fail | Mixed scales, qualifiers, confidence forms, and statuses |
| Counts | Fail | Two reconciliation issues |
| Determinism | Partial | Stable per artifact, but no common ordering contract |
| Section coverage | Partial | Topic-specific and heterogeneous schemas |
| Isolation | Pass with finding | Static-only declarations are consistent; `generated_at` policy is not |

## Findings

### AUD-001 — Pair and parse integrity: pass

All 17 JSON files parse, and every expected Markdown counterpart is present.

### AUD-002 — Stale source paths: medium

Two exact repository paths are absent:

- `00-corpus-inventory.json:595` references `docs/analysis/global-campaign-2026/track-f-empire-economy.json`; the present path is `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json`.
- `14-class-families.json:93464,93482,93500,126840` references `knowledgegraph/triage/track-b-function-accounting.json`; the present path is `knowledgegraph/research/track-b-function-accounting.json`.

These should be corrected or explicitly retained as historical aliases. Logical locators such as JSON fragments, line ranges, compound `file.hpp/.cpp` aliases, and extensionless self-references were not counted as broken filesystem paths. SQLite WAL/shared-memory references in `00` are environment-dependent sidecars, not missing research source files.

### AUD-003 — Identifier ambiguity: medium

Most repeated identifiers are valid foreign keys. Three cases need explicit normalization:

- `02-gameplay-entity.json:173` reuses snapshot ID `f0e310e0` for triage and semantic-atlas records; the semantic-atlas record also omits `sha256`.
- `09-asset-content.json:53,64` gives both RW4 and RW4 section-class records `type_id` `0x2F4E681B`. A unique record identity should be separate from the shared resource type key if both records remain.
- `15-reconstruction-relevance.json` reuses `unknown-vtable-corpus` in both `assessments` and `unknown_unlockers` without an explicit namespace or foreign-key marker.

The repeated `type_id` values in `02`/`03`, `candidate_id` values in `16`, and scoring `method_id` values in `15` are valid relationship references and are not collisions.

### AUD-004 — Vocabulary drift: medium

The partitions use incompatible or overlapping vocabularies:

- `01` and `08` use `UNKNOWN < INFERRED < SUPPORTED < OBSERVED`.
- `00`, `09`, and `13` use a seven-level scale.
- `16` uses a seven-level scale with `CONFIRMED` before `OBSERVED`, unlike the other seven-level partitions.
- `07` adds `CONFIRMED_NAME_ONLY`; `09` uses `CONFIRMED_NAME` in nested records.
- `02` defines `SUPPORTED` twice in its Markdown vocabulary and JSON policy labels.
- Numeric confidence appears in `12` and some structured records, while other artifacts use `low`, `medium`, and `high`.
- `15` uses uncertainty as `low`, `medium`, and `high`; this is not equivalent to an evidence level.

The normalization target is one evidence scale plus separate qualifiers for name-only, structural-only, approximation, and confidence basis.

### AUD-005 — Count reconciliation: medium

Two explicit issues remain:

- `08-persistence-serialization.json:341` names persistence-manager callsite `0x00B32BC8`, while the detailed callsite ledger at `:817-844` lists `0x00C7F109` and omits `0x00B32BC8`. The Markdown at `08-persistence-serialization.md:64` lists four callsites including both. Reconcile claim, ledger, and prose from one canonical callsite list.
- `16-misc-unknown.json` declares 24 `required_sections`, but its `complete_sections` list has 23 entries and omits `complete_sections` itself.

The `15-reconstruction-relevance.json` domain summary correctly sums to 71 assessments, matching the assessment array.

### AUD-006 — Ordering policy: low

Each artifact is stable as authored, but the set has no common ordering contract. Top-level key order varies, and several scalar arrays are narrative or source-group ordered rather than lexical, including unresolved-question and source-index arrays. The lexical-order claims in `03` and `15` do not fully describe actual object order.

### AUD-007 — Section schema heterogeneity: low

The artifacts use topic-specific schemas. Some combine fields, methods, vtables, lifecycle, consumers, and provenance under names such as `vtables_and_inheritance`, `ownership_lifecycle`, or `callers_callees`; cross-cutting artifacts such as `12`, `14`, `15`, and `16` are projections rather than full type catalogs. A common section index is needed before automated completeness checks.

### AUD-008 — Timestamp policy: low

`08-persistence-serialization.json:8` contains `generated_at: null`. Other artifacts use omitted fields or explicit timestamp-free declarations. The field should be removed in favor of an omitted-field policy; semantic timestamp claims in event records should remain separate from artifact-generation metadata.

### AUD-009 — Historical address alias: informational

`10-managers-registries.json:554` preserves the historical `0x00B321340` message-registration label, while `07`, `12`, `13`, `15`, and `16` use `0x00B21340` for the map/list bridge. The artifacts correctly treat the former as withdrawn or historical. Preserve the alias and do not silently rewrite historical evidence.

## Normalization requirements

1. Adopt one canonical evidence scale, preferably `UNKNOWN < APPROXIMATION < INFERRED < SUPPORTED < OBSERVED < CONFIRMED < VERIFIED`, with name-only and structural-only limitations as qualifiers.
2. Choose one confidence representation. Preserve raw numeric values only under an explicitly named numeric field and expose a separately defined ordinal band or basis.
3. Remove `generated_at` and all artifact-generation wall-clock fields; use an explicit `timestamp_policy` value such as `omitted`.
4. Separate source `path` from source `locator`; correct stale paths and split compound aliases.
5. Separate unique `record_id` from shared `resource_type_id`; namespace cross-collection IDs and mark foreign keys explicitly.
6. Add a common section index or coverage map with `present`, `combined`, `omitted`, and `out_of_scope` states.
7. Generate declared counts from canonical record arrays; reconcile the `08` callsite list and `16` section inventory.
8. Define one serialization policy: lexical top-level keys and scalar arrays, or explicitly recorded authored ordering.
9. Preserve historical address aliases while making `0x00B21340` the canonical current address.
10. Keep semantic event timestamps separate from artifact-generation metadata.

## Per-artifact observations

| Artifact | Result | Key observations |
|---|---|---|
| `00` | Findings | One stale global-campaign path; SQLite sidecars are environment-dependent; inventory schema is not a type catalog. |
| `01` | Findings | Conventional type, field, vtable, inheritance, lifecycle, method, consumer, evidence, provenance, and question sections are present; ordering and confidence forms are not globally normalized. |
| `02` | Findings | Duplicate `SUPPORTED` label; reused `f0e310e0` snapshot ID; type references are otherwise valid. |
| `03` | Findings | Strong conventional type/field/method/provenance coverage; determinism claim does not fully match actual top-level order. |
| `04` | Findings | Topic-specific combined sections; no standalone fields or methods section. |
| `05` | Findings | Type, vtable, ownership/lifecycle, serialization, consumer, transition, and disagreement coverage; questions are narrative ordered. |
| `06` | Findings | Broad combined editor/UI schema; source index is source-group ordered and uses compound aliases. |
| `07` | Findings | Broad event/message structure; `CONFIRMED_NAME_ONLY` is a partition-specific qualifier. |
| `08` | Findings | `generated_at: null`; persistence callsite claim/ledger/Markdown mismatch; four-level evidence scale. |
| `09` | Findings | Shared `0x2F4E681B` type key; `CONFIRMED_NAME` differs from `CONFIRMED_NAME_ONLY`; semantic-atlas locators are valid. |
| `10` | Findings | Historical address alias is explicitly preserved; evidence scale differs from neighboring artifacts. |
| `11` | Findings | Extensive vtable/provenance coverage; fragment locators are valid; questions are narrative ordered. |
| `12` | Findings | Field-offset projection is explicit; numeric confidence needs a declared conversion policy. |
| `13` | Findings | Broad lifecycle/ownership/factory/registration coverage; seven-level evidence scale. |
| `14` | Findings | Large class-family synthesis; four stale triage paths; questions are narrative ordered. |
| `15` | Findings | Assessment/domain counts reconcile at 71; ordering claim is not fully accurate; `unknown-vtable-corpus` crosses collections. |
| `16` | Findings | Required/completed section count mismatch; evidence scale order differs; candidate references are valid. |

## Isolation statement

This audit is read-only. It did not modify worker artifacts, implementation source, the binary, Ghidra state, the knowledge-graph database, historical artifacts, or `SPORE/`. The only created outputs are:

- `knowledgegraph/research/types/17-audit-integrity.json`
- `knowledgegraph/research/types/17-audit-integrity.md`
