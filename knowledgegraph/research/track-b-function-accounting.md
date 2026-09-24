# Track B Function Accounting

Deterministic, read-only accounting for the canonical 58,757-function universe. The complete per-function record is the ascending-VA JSONL sidecar; this document records its schema, stable counts, reconciliation checks, and unresolved-evidence policy.

## Scope and invariants

- Canonical universe: **58,757** unique VA rows from `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl`.
- VA format: 8-digit lowercase hexadecimal; sidecar ordering: ascending lexical VA.
- JSONL sidecar: `knowledgegraph/research/track-b-function-accounting.jsonl`; one row per canonical VA; JSON keys and arrays are stable-sorted by the generator.
- This track reads committed artifacts only. It does not write the knowledge-graph DB, alter triage/xrefs, or create implementation/final documentation.
- Unknown remains unknown. Name evidence, vtable evidence, graph edges, and decompiler output are recorded as evidence, not promoted to semantic truth.

## Source artifacts

- `knowledgegraph/research/21-decompilation-coverage.json` — 49,709,906 bytes; SHA-256 `16ac8cb10f0f0300964ab1655b20706d8c3a87104be0b8b30aee77b185e11784`
- `knowledgegraph/triage/attribution-f0e310e0.json` — 5,288 bytes; SHA-256 `b8974afaeff9e38cf4d5810b645a06b993c6dca7d4f5d287ba2556ffa54ac061`
- `knowledgegraph/triage/clusters-f0e310e0-v6.json` — 70,217 bytes; SHA-256 `7b9cbc9a584dbfadc32f9abeab273b8754cbae1e8caee1690455bab3608c017e`
- `knowledgegraph/triage/debtmap-f0e310e0.json` — 13,404,955 bytes; SHA-256 `b5b98edee96e230eea41136d7cc93d1694ca0f101380d8d2cffaa7c8ac0968fa`
- `knowledgegraph/triage/reconstruction-readiness-f0e310e0.json` — 382,264 bytes; SHA-256 `44e89b29c4dc1c1ca3a135d2dfdfef3d276a3a7eea95e313e59d7271a7b351eb`
- `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl` — 34,392,005 bytes; SHA-256 `5fd07ad16b85da68716e7e7fe2c1fcbc78e397888b532c0c09783b4480b6321e`
- `knowledgegraph/triage/xrefs-2540f2ca.summary.json` — 1,726 bytes; SHA-256 `83f7762426b23d9195dfd232fc2666abe01e84004e2856911363d3813b088c2f`
- `knowledgegraph/triage/xrefs-2540f2ca.tsv` — 27,823,658 bytes; SHA-256 `89e74b8a03c4db38a1927f8c95c38db507bf99cb8a11de6b6eb6a9484d8c79cb`

## Stable summary counts

### Identity and accounting

| check | value |
|---|---:|
| canonical rows | 58,757 |
| canonical unique VA | 58,757 |
| sidecar rows | 58,757 |
| sidecar unique VA | 58,757 |
| category sum | 58,757 |
| cluster sum | 58,757 |
| subsystem sum | 58,757 |
| all exact-universe checks | True |

### Category

| value | count |
|---|---:|
| `ENGINE_IMPLEMENTATION` | 11,585 |
| `ENGINE_INTERFACE` | 1,227 |
| `GAMEPLAY_LOGIC` | 1,656 |
| `GAMEPLAY_SUPPORT` | 493 |
| `THIRD_PARTY_OR_RUNTIME` | 4,080 |
| `UNKNOWN` | 39,716 |

### Name evidence

| value | count |
|---|---:|
| `APPROX` | 1,500 |
| `CONFIRMED` | 1,167 |
| `INFERRED` | 12,371 |
| `SUPPORTED` | 3,836 |
| `UNKNOWN` | 39,883 |

### Priority

| value | count |
|---|---:|
| `IGNORE` | 178 |
| `P0` | 159 |
| `P1` | 6,261 |
| `P2` | 19 |
| `P3` | 52,140 |

### Gameplay affinity

| value | count |
|---|---:|
| `gameplay` | 2,149 |
| `non_gameplay` | 56,608 |

### Decompilation state

| value | count |
|---|---:|
| `annotated_decompiler_capture` | 1 |
| `decompiler_export` | 477 |
| `snapshot_only` | 2 |
| `unavailable` | 58,277 |

### Decompilation quality

| value | count |
|---|---:|
| `annotated_decompiler_capture` | 1 |
| `decompiler_pseudocode_with_warnings` | 477 |
| `snapshot_role_only` | 1 |
| `snapshot_snippet_only` | 1 |
| `unavailable` | 58,277 |

### Infrastructure/third-party indicator

| value | count |
|---|---:|
| `likely_infrastructure` | 8,619 |
| `none_evidenced` | 44,647 |
| `third_party_or_runtime` | 5,491 |

### Debtmap ownership

| value | count |
|---|---:|
| `engine_runtime` | 8,789 |
| `gameplay_affinity` | 2,950 |
| `genuinely_unknown` | 35,771 |
| `third_party_hint` | 786 |
| `unknown` | 10,461 |

### Reconstruction relevance

| value | count |
|---|---:|
| `gameplay_population_not_in_readiness_queue` | 1,913 |
| `not_in_reconstruction_scope_evidence` | 56,479 |
| `queue_scoped` | 365 |

### Readiness

| value | count |
|---|---:|
| `DEPENDENCY_FIRST` | 24 |
| `ENGINE_BOUNDARY` | 23 |
| `LIKELY_INFRASTRUCTURE` | 182 |
| `NEEDS_RE` | 101 |
| `READY` | 6 |
| `READY_WITH_LOCAL_CONTEXT` | 29 |
| `not_assessed` | 58,392 |

### Contract status

| value | count |
|---|---:|
| `unknown` | 58,757 |

### Unresolved reason codes

Codes are non-exclusive across rows; each code is emitted only when its evidence is present or its absence is explicitly known.

| code | rows |
|---|---:|
| `callee_dependencies_unresolved` | 24 |
| `decompilation_not_persisted` | 58,279 |
| `engine_interface_boundary` | 23 |
| `excluded_from_reconstruction_scope` | 182 |
| `identity_or_semantics_unknown` | 39,853 |
| `local_type_context_required` | 29 |
| `needs_reverse_engineering` | 101 |
| `not_in_reconstruction_queue` | 1,913 |
| `outside_reconstruction_scope` | 182 |
| `readiness_not_assessed_queue_scoped` | 58,392 |
| `reverse_engineering_required` | 101 |
| `semantic_understanding_not_established` | 58,757 |
| `snapshot_evidence_is_not_full_body` | 2 |

## Xref accounting

- Canonical call-type edge rows: **207,757**; artifact unique rows: **223,704**.
- Functions with at least one evidenced internal caller: **33,643**; artifact: **33,643**.
- Functions with at least one evidenced call-type callee destination, including external tokens: **41,031**; artifact: **41,031**.
- Per-function `caller_count` counts distinct pinned callers. `callee_count` counts distinct call-type destinations, including external allowlisted destinations, matching the canonicalizer/ingest definition. Data and vtable references remain in the artifact but are not included in these call counts.

## Cluster accounting

The cluster partition is recomputed from the canonical triage row fields using the exhaustive 20-cluster rule and checked against the v6 cluster inventory. The artifact reports 58,757; all 20 per-cluster counts match.

| cluster | accounted | artifact | match | artifact readiness |
|---|---:|---:|---|---|
| `utfwin-framework` | 1,093 | 1,093 | True | `ready` |
| `app-lifecycle` | 1,104 | 1,104 | True | `ready` |
| `resource-io` | 523 | 523 | True | `ready` |
| `sim-cell` | 26 | 26 | True | `near-ready` |
| `sim-space` | 7 | 7 | True | `near-ready` |
| `sim-creature-tribeciv` | 11 | 11 | True | `near-ready` |
| `sim-core-systems` | 1,628 | 1,628 | True | `ready` |
| `editor-core` | 314 | 314 | True | `ready` |
| `editor-support` | 99 | 99 | True | `near-ready` |
| `sporepedia-online` | 100 | 100 | True | `ready` |
| `terrain-world` | 112 | 112 | True | `near-ready` |
| `graphics-render` | 86 | 86 | True | `near-ready` |
| `ui-shell` | 13 | 13 | True | `near-ready` |
| `scripting-content` | 84 | 84 | True | `ready` |
| `swarm-anim` | 70 | 70 | True | `blocked-on-identification` |
| `audio-input` | 11 | 11 | True | `blocked-on-identification` |
| `gameglobal-misc` | 39 | 39 | True | `blocked-on-identification` |
| `runtime-crt-stl` | 4,075 | 4,075 | True | `out-of-scope` |
| `unknown-vtable-impl` | 4,384 | 4,384 | True | `blocked-on-identification` |
| `unknown-fun-mass` | 44,978 | 44,978 | True | `blocked-on-identification` |

## Attribution, decompilation, and readiness

- Attribution artifact: 5,600 FUN-vtable-pool rows; triage rows with a vtable family: 1,501; rows with an SDK name: 1,171.
- Decompilation ledger: 478 persisted bodies and 58,279 unavailable bodies across the canonical universe; the gameplay population is 2,149, with 172 persisted bodies.
- Readiness: queue-scoped artifact contains 368 rows; 365 are canonical and 3 are outside the canonical universe. The sidecar accounts only the canonical 365 and preserves the three excluded rows in the JSON summary.
- Contract status: all 58,757 canonical rows remain `unknown`; the supplied artifacts contain no function-level contract plus runtime validation, and decompilation is explicitly evidence-only.

## Per-function schema

Each JSONL row contains:

- `va`, `name`, `category`, `subsystem`, and deterministic `cluster`.
- `caller_count` and `callee_count`, plus `xref` counts and call-reference type counts.
- `sdk_vtable`: SDK name, structs, vtable addresses/family, relationship, and attribution namespace.
- `decomp`: persisted-body availability, state, quality, path, size, and blockers; no semantic upgrade.
- `evidence`: name-level, decompilation, xref, and SDK/vtable evidence labels.
- `gameplay_affinity`, `infrastructure_or_third_party`, `reconstruction_relevance`, `readiness`, `contract_status`, `unresolved_reason`, and source-preserving triage/debtmap detail.

## Reconciliation and limitations

- The triage JSONL rows carry classifier metadata `triage-v5` although the artifact filename and cluster inventory identify the v6 projection; row fields, not the metadata label, are used for accounting. This is recorded in the decompilation artifact reconciliation and not corrected here.
- The triage snapshot is `f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b`; the canonical xref export is `2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8`. The xref closure is nevertheless explicitly pinned to 58,757 and all pinned endpoints are validated, so the two hashes remain separately identified rather than silently merged.
- The readiness artifact is queue-scoped, not a full 58,757-row readiness classification. Non-queued rows receive `not_assessed` with the reason that no readiness row exists.
- Debtmap ownership is available only for its 48,296-row unknown population. Other rows retain `null` ownership with `not_in_debtmap_unknown_population`; no ownership is inferred.
- The three readiness queue VAs outside the canonical universe are preserved in the JSON summary and excluded from the per-function sidecar, as required by exact-universe closure.
- Decompiler output, names, vtable relationships, and graph connectivity are not treated as verified behavior contracts.

## Reproduction checks

The sidecar is deterministic when regenerated from the listed frozen artifacts. Required checks are:

1. `len(sidecar_rows) == 58757`; 2. `len(unique VA) == 58757`; 3. category, cluster, and subsystem sums each equal `58757`; 4. every sidecar VA belongs to the canonical triage universe; 5. every sidecar VA is unique; 6. all cluster artifact counts match; 7. xref coverage recomputes to the canonical summary; 8. the three non-canonical readiness rows remain excluded.
