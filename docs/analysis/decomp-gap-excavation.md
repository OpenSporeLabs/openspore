# Decompilation Gap Excavation

Deterministic read-only synthesis of 16 repaired worker artifacts available in the worktree, joined to the authoritative Track-B, Triage, Readiness, Xref, and Track-I inputs. All sixteen expected worker partitions are present; no authoritative backfill was needed.

## Executive summary

- **Function records:** exactly 1,977 unique VA records; 1,977 repaired worker records and 0 authoritative backfill records.
- **Partition accounting:** 16/16 partitions accounted; 16 repaired artifacts are present and 0 expected partitions are explicitly backfilled from pinned inputs.
- **Coverage:** baseline gameplay is 2,149, previous usable decompilation is 172 (8.004%), and the authoritative gap is exactly 1,977; new persisted usable decompilation is 0.
- **Current worker evidence:** 184 worker-recorded live static body observations, explicitly distinguished from persisted decompilation; 796 partial/bounded contract claims; 76 held-infrastructure records; 796 static claims still requiring runtime evidence.
- **Readiness:** 145 static-upgrade evidence claims, 0 explicit canonical readiness changes; recommendations are not promoted to readiness truth.
- **Residual queue:** 1,977 records, 4,143 explicit unknown observations, 1,524 retained contradiction observations, 3,215 component claims, and 10,489 structure claims.

## Coverage and integrity

| Metric | Value |
|---|---:|
| Baseline gameplay population | 2,149 |
| Previous usable decompilation | 172 |
| Previous usable coverage | 8.004% |
| Authoritative gap population | 1,977 |
| Unique investigated function records | 1,977 |
| Repaired worker records | 1977 |
| Authoritative backfill records | 0 |
| Expected worker partitions accounted | 16/16 |
| Repaired worker artifacts present | 16 |
| New persisted usable decompilation | 0 |
| Current worker live static body observations | 184 |
| Partial/bounded contract claims | 796 |
| Held infrastructure | 76 |
| Runtime-required static claims | 796 |
| Explicit canonical readiness changes | 0 |
| Static-upgrade evidence claims | 145 |
| Explicit unknowns | 4143 |
| Retained contradictions | 1524 |
| Residual queue | 1977 |

Authoritative inputs: `knowledgegraph/research/track-b-function-accounting.jsonl`, `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl`, `knowledgegraph/triage/reconstruction-readiness-f0e310e0.json`, `knowledgegraph/triage/xrefs-2540f2ca.tsv`, and `knowledgegraph/research/track-i-dependency-graph.json`.

Integrity checks: exact unique function count is 1,977; all 16 expected partitions account for their expected counts; all 1,977 repaired worker records are represented; every function has authoritative Track-B and xref inputs; no duplicate function records, timestamp keys, KG writes, or implementation writes are present.

## Partition accounting

| Partition | Expected | Actual | Artifact | Source status |
|---|---:|---:|---|---|
| `editor-core-00` | 223 | 223 | `knowledgegraph/research/decomp-gap/editor-core-00.json` | repaired worker artifact |
| `editor-support-00` | 66 | 66 | `knowledgegraph/research/decomp-gap/editor-support-00.json` | repaired worker artifact |
| `gameglobal-misc-00` | 35 | 35 | `knowledgegraph/research/decomp-gap/gameglobal-misc-00.json` | repaired worker artifact |
| `hold-infrastructure` | 76 | 76 | `knowledgegraph/research/decomp-gap/hold-infrastructure.json` | repaired worker artifact |
| `sim-core-00` | 175 | 175 | `knowledgegraph/research/decomp-gap/sim-core-00.json` | repaired worker artifact |
| `sim-core-01` | 175 | 175 | `knowledgegraph/research/decomp-gap/sim-core-01.json` | repaired worker artifact |
| `sim-core-02` | 175 | 175 | `knowledgegraph/research/decomp-gap/sim-core-02.json` | repaired worker artifact |
| `sim-core-03` | 175 | 175 | `knowledgegraph/research/decomp-gap/sim-core-03.json` | repaired worker artifact |
| `sim-core-04` | 175 | 175 | `knowledgegraph/research/decomp-gap/sim-core-04.json` | repaired worker artifact |
| `sim-core-05` | 175 | 175 | `knowledgegraph/research/decomp-gap/sim-core-05.json` | repaired worker artifact |
| `sim-core-06` | 175 | 175 | `knowledgegraph/research/decomp-gap/sim-core-06.json` | repaired worker artifact |
| `sim-core-07` | 175 | 175 | `knowledgegraph/research/decomp-gap/sim-core-07.json` | repaired worker artifact |
| `sim-space-00` | 5 | 5 | `knowledgegraph/research/decomp-gap/sim-space-00.json` | repaired worker artifact |
| `sporepedia-online-00` | 69 | 69 | `knowledgegraph/research/decomp-gap/sporepedia-online-00.json` | repaired worker artifact |
| `terrain-world-00` | 93 | 93 | `knowledgegraph/research/decomp-gap/terrain-world-00.json` | repaired worker artifact |
| `ui-shell-00` | 10 | 10 | `knowledgegraph/research/decomp-gap/ui-shell-00.json` | repaired worker artifact |

## Repaired worker artifacts

| Artifact | Schema | Records | SHA-256 |
|---|---|---:|---|
| `knowledgegraph/research/decomp-gap/editor-core-00.json` | `openspore-decomp-gap-partition-1` | 223 | `5afae1aa9b2316d0a184320fd5208103a4075feafdc99a70824a5ec204a5f19f` |
| `knowledgegraph/research/decomp-gap/editor-support-00.json` | `openspore-decomp-gap-partition-1` | 66 | `5e906d79fb4a2628a521c2e6f576f4398832a4a30aaad3ad56fd53095853876e` |
| `knowledgegraph/research/decomp-gap/gameglobal-misc-00.json` | `openspore-decomp-gap-partition-1` | 35 | `0dd9e8d18552e56db3f5ecefe699955610a412d8fa1713eae228b0e8e0f24d2f` |
| `knowledgegraph/research/decomp-gap/hold-infrastructure.json` | `openspore-decomp-gap-hold-infrastructure-1` | 76 | `1123756369bb1cc5a3690fa5127602ae08114e47f47cbe50bdb2f13acdbe62fc` |
| `knowledgegraph/research/decomp-gap/sim-core-00.json` | `openspore-decomp-gap-partition-1` | 175 | `a5892e112707c7e8eecc2b78a072b5dae5789fe7598f8355b5c942a0fcdcc84a` |
| `knowledgegraph/research/decomp-gap/sim-core-01.json` | `openspore-decomp-gap-partition-1` | 175 | `a9222174905c6c38941c519467512f3bb99588a1aa89f3c7533ef7eba14a91b4` |
| `knowledgegraph/research/decomp-gap/sim-core-02.json` | `openspore-decomp-gap-partition-1` | 175 | `aee99d2f9add4dd7043a6b88769bc846c590c0bc444cd3d4de387255980cb93d` |
| `knowledgegraph/research/decomp-gap/sim-core-03.json` | `openspore-decomp-gap-partition-1` | 175 | `49e72d8c4795eabb2aa395247319f479aaca7b5fb7425b087758cd1896033e50` |
| `knowledgegraph/research/decomp-gap/sim-core-04.json` | `decomp-gap-partition-1` | 175 | `45241de23bdc1c93decf0e3a6eeaccfa6b65578a53a282d53232f8c3e7298d94` |
| `knowledgegraph/research/decomp-gap/sim-core-05.json` | `openspore-decomp-gap-partition-1` | 175 | `ef334601f412fb37e60558b1e9e6c04474efd2cb158ce205bd4e7db1afcb093e` |
| `knowledgegraph/research/decomp-gap/sim-core-06.json` | `openspore-decomp-gap-partition-1` | 175 | `c16471dd04b7633551d0a3cb9bbc6093a7cd78e8db98831a5372eea00ff8aa19` |
| `knowledgegraph/research/decomp-gap/sim-core-07.json` | `openspore-decomp-gap-partition-1` | 175 | `776b74108b7b2ebb9e35bc87648b53487b8796e58ec22cb2fbc183ce78fbc797` |
| `knowledgegraph/research/decomp-gap/sim-space-00.json` | `decomp-gap-partition-1` | 5 | `f5a4c0d5cf351f17c259ae48205b61ef7eb3b7df2ff6c85e2b9e9d9045e8abf2` |
| `knowledgegraph/research/decomp-gap/sporepedia-online-00.json` | `decomp-gap-partition-1` | 69 | `6ffca7d41f2ce49c5c44be51412b6bd2a93b56c9359b28db8d69ce056882e15c` |
| `knowledgegraph/research/decomp-gap/terrain-world-00.json` | `openspore-decomp-gap-partition-1` | 93 | `eb813be58bc9df10061f44e1d734e82a4cc0f1d64297626911dfabdf9fa35261` |
| `knowledgegraph/research/decomp-gap/ui-shell-00.json` | `openspore-decomp-gap-partition-1` | 10 | `54362497e74b3bcb21621af8f5be339d5631fe31dc4db5dbd169159e80e348e3` |

All sixteen expected worker partitions are present; no authoritative backfill was needed.

## Contradictions and unknowns

The machine output retains 1,524 source-attributed contradictions and 4,143 explicit unknowns. Contradiction sources include worker accounting-versus-live-body claims, stored-signature-versus-decompiler shapes, SDK-name-versus-body conflicts, readiness scope/status differences, infrastructure holds, and xref-count/endpoint differences. No disagreement is silently discarded.

| Source | Count |
|---|---:|
| `knowledgegraph/research/decomp-gap/editor-core-00.json` | 223 |
| `knowledgegraph/research/decomp-gap/editor-support-00.json` | 66 |
| `knowledgegraph/research/decomp-gap/gameglobal-misc-00.json` | 35 |
| `knowledgegraph/research/decomp-gap/hold-infrastructure.json` | 76 |
| `knowledgegraph/research/decomp-gap/sim-core-00.json` | 175 |
| `knowledgegraph/research/decomp-gap/sim-core-01.json` | 175 |
| `knowledgegraph/research/decomp-gap/sim-core-03.json` | 175 |
| `knowledgegraph/research/decomp-gap/sim-core-04.json` | 176 |
| `knowledgegraph/research/decomp-gap/sim-core-05.json` | 1 |
| `knowledgegraph/research/decomp-gap/sim-core-06.json` | 176 |
| `knowledgegraph/research/decomp-gap/sim-space-00.json` | 5 |
| `knowledgegraph/research/decomp-gap/sporepedia-online-00.json` | 1 |
| `knowledgegraph/research/decomp-gap/terrain-world-00.json` | 93 |
| `knowledgegraph/research/decomp-gap/ui-shell-00.json` | 10 |
| `knowledgegraph/research/track-b-function-accounting.json` | 6 |
| `knowledgegraph/triage/xrefs-2540f2ca.tsv` | 131 |

## Components, structures, and unlock metrics

The output retains 3,215 worker component claims and 10,489 worker structure/field claims. The authoritative component summary reports a 1,761-function dominant connected component, 21 small components covering 58 functions, and 330 isolated functions; 35 queue rows are READY or READY_WITH_LOCAL_CONTEXT. These are structural/readiness unlocks, not runtime-unlocked semantics.

## Residual queue

All 1,977 final records have source-attributed repaired-worker residual actions. No action authorizes implementation, KG mutation, or runtime claims.

## Interpretation boundary

Live static body observations are worker evidence, not persisted decompilation exports. Contracts, readiness recommendations, component claims, and structure observations remain bounded static evidence. The synthesis does not claim runtime truth or original semantic equivalence.
