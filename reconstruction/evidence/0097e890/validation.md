# Validation 0x0097e890

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_utfwin_effects_wave6/utfwin_effects_wave6.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `FAIL` | `partial` | unresolved ABI conflict derived_vs_persisted; the validator will not pick a winner |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x0097e890; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `WARN` | `partial` | the complete 2-instruction listing names 1 data address(es) (0x14436b0) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 2-instruction listing names no memory operand through any register at all and it was consumed in full by the machine parse (declared_count=2, degraded=false, unparsed=0), which is the evidence that this function performs no field access; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 1 source constant(s) are absent from the machine listing: 0x1436b0 |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `4ea93845d21d58f65814dc1f36c76def65cfb172f1e89c3f4412f05cb89f88ab`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e9012abdffe9372fdcaae9bda011ee490d26aa0f07cc43e064dba9c9260b1868`
- Pack digest quoted by the briefing: `4ea93845d21d58f65814dc1f36c76def65cfb172f1e89c3f4412f05cb89f88ab`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `constant interpretation and runtime vtable ownership remain gated`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- constant interpretation and runtime vtable ownership remain gated
- runtime validation not run
