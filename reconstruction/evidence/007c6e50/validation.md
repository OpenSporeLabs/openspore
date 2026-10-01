# Validation 0x007c6e50

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_camera_wave7/camera_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 22-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 1 distinct address(es) for 0x007c6e50; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 22-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | 11 source field-offset declaration(s) (field active_index_0a8, field begin_000, field bucket_count_008, field buckets_004) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 2 source constant(s) are absent from the machine listing: 0xf62def, 0xffffd8f1 |
| CONTROL FLOW | `WARN` | `partial` | 1 of 1 conditional branch target(s) fall outside the recovered body span 0x007c6e50..0x007c6e81, so the listing is a slice and flow continues past it; the source span declares for, if |
| VIRTUAL DISPATCH | `FAIL` | `partial` | the complete 22-instruction body contains no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, but the source span declares a virtual-slot boundary |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 3 passed, 0 had no evidence to evaluate; 9 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 9 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `20c09fa6a9d48322d2459ca6d8a92c4a71d7afe8bc30a9fe84e88a497155566e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e5c557aec2c834a34e28a863967a8eef687f9067c67e0c8b31ab391966a03209`
- Pack digest quoted by the briefing: `20c09fa6a9d48322d2459ca6d8a92c4a71d7afe8bc30a9fe84e88a497155566e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Original application camera-manager teardown trace is not available; no runtime promotion is claimed.`, `runtime observation required`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Original application camera-manager teardown trace is not available; no runtime promotion is claimed.
- concrete runtime owners and values remain unresolved
- runtime observation required
