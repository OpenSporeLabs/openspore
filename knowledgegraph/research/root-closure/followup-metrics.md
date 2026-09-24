# Phase-0 Root Closure Follow-up Metrics

Metrics-only static audit over the pinned `2540f2ca` xrefs, `f0e310e0` triage-v6 projection, six root-closure tracks, and `cross-root-relationships.json`. No source, `SPORE/`, historical artifact, or Phase-0 interface was modified.

## Aggregate metrics

| Metric | Exact value |
|---|---:|
| Roots | 11 |
| Distinct direct-caller union | 2,303 |
| Direct-call edge total | 6,077 |
| Gameplay-caller union | 516 |
| Direct callers with at least 2 of the 11 roots | 948 |
| Multi-root callers classified as gameplay | 231 |
| Curated high-information shared callers | 7 |
| Mechanical shared callers with at least 3 roots | 390 |
| Mechanical shared callers with at least 4 roots | 153 |
| Mechanical shared callers with at least 5 roots | 62 |
| Mechanical shared callers with at least 6 roots | 31 |
| Mechanical shared callers with at least 7 roots | 7 |
| Mechanically constrained downstream functions | 2,303 |
| Evidence-selected semantic downstream subset | 40 |
| Semantic subset classified as gameplay | 33 |
| Semantic subset not classified as gameplay | 7 |

The per-root direct-caller memberships sum to 3,896, while the deduplicated union is 2,303. The per-root gameplay memberships sum to 855, while the deduplicated union is 516.

## Per-root metrics

| Root | Direct callers | Direct-call edges | Gameplay callers | Multi-root callers | Semantic subset |
|---|---:|---:|---:|---:|---:|
| `00b3d300` | 1,097 | 1,941 | 252 | 698 | 23 |
| `00b3d2a0` | 314 | 510 | 101 | 205 | 12 |
| `00b5b800` | 459 | 701 | 80 | 213 | 10 |
| `00b3d350` | 614 | 958 | 80 | 227 | 10 |
| `01021260` | 262 | 357 | 68 | 189 | 11 |
| `00b1fdb0` | 303 | 432 | 68 | 293 | 11 |
| `00b21340` | 254 | 318 | 50 | 232 | 9 |
| `01021300` | 182 | 246 | 47 | 126 | 12 |
| `01021080` | 175 | 230 | 38 | 122 | 9 |
| `00b25fb0` | 100 | 193 | 36 | 100 | 7 |
| `00ba9370` | 136 | 191 | 35 | 136 | 9 |

## Baseline reconciliation

All 11 roots match the committed baseline exactly for direct callers, direct-call edges, and gameplay callers. The requested examples reconcile as:

- `00b3d300`: `1097/252`, plus `1941` direct-call edges.
- `00b3d2a0`: `314/101`, plus `510` direct-call edges.
- `00b5b800`: `459/80`, plus `701` direct-call edges.
- `00b3d350`: `614/80`, plus `958` direct-call edges.
- `01021260`: `262/68`, plus `357` direct-call edges.
- `00b1fdb0`: `303/68`, plus `432` direct-call edges.
- `00b21340`: `254/50`, plus `318` direct-call edges.
- `01021300`: `182/47`, plus `246` direct-call edges.
- `01021080`: `175/38`, plus `230` direct-call edges.
- `00b25fb0`: `100/36`, plus `193` direct-call edges.
- `00ba9370`: `136/35`, plus `191` direct-call edges.

## Counting rules

1. Use exactly the 11 roots in the cross-root artifact, normalized to lowercase hexadecimal.
2. Count only `reference_type=direct-call` rows whose callee is one of those roots. Computed calls, thunks, data refs, vtable refs, externals, and root-to-helper calls are excluded.
3. A direct caller is a distinct normalized `caller_va`; repeated callsites count once for caller and gameplay metrics.
4. A direct-call edge is an individual selected TSV row; repeated callsites count separately.
5. The direct-caller union deduplicates callers across all 11 roots. The direct-call edge total sums per-root row counts.
6. A multi-root caller is a distinct caller with direct-call edges to at least two roots.
7. A gameplay caller is a caller whose triage-v6 category is `GAMEPLAY_LOGIC` or `GAMEPLAY_SUPPORT`, regardless of subsystem. This reproduces every committed per-root gameplay baseline.
8. The high-information count has two meanings: 7 explicitly curated callers from the cross-root artifact, and the reproducible mechanical threshold of callers reaching at least 3 roots. The curated list is not exhaustive.
9. Mechanical downstream constraints cover every direct caller in the 2,303-function union because each has a statically established root calling/return contract. This does not claim a universal semantic use.
10. The 40-function semantic subset is the unique union of `direct_semantic_subset` entries in the cross-root artifact. It is evidence-selected and conservative; triage category and co-calling alone do not add a function to it.

## Curated high-information callers

The cross-root artifact curates these seven functions: `00aebe90` (6 roots), `00bff2d0` (7), `00c099e0` (3), `00cfbc10` (7), `010027b0` (7), `010225d0` (2), and `010593e0` (6). Six are in the mechanical `>=3` threshold; `010225d0` is the one curated two-root example.

## Inputs

- `knowledgegraph/triage/xrefs-2540f2ca.tsv`
- `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl`
- `knowledgegraph/research/root-closure/track-a-service-identity.json`
- `knowledgegraph/research/root-closure/track-b-strategy-handle.json`
- `knowledgegraph/research/root-closure/track-c-opaque-owner.json`
- `knowledgegraph/research/root-closure/track-d-noun-registry.json`
- `knowledgegraph/research/root-closure/track-e-empire-chain.json`
- `knowledgegraph/research/root-closure/track-f-space-context.json`
- `knowledgegraph/research/root-closure/cross-root-relationships.json`

Direct-call metrics are static-reference measures only; they do not establish runtime reachability, execution order, dataflow, or object identity.
