# Validation 0x007e6080

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 1-instruction listing name the same 1 direct transfer target(s), including a target reached only by a jump; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x007e6080; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 1-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 1-instruction listing names no memory operand through any register at all and it was consumed in full by the machine parse (declared_count=1, degraded=false, unparsed=0), which is the evidence that this function performs no field access; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (1 of 1 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 1-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 1-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `WARN` | `partial` | return type differs or is semantically renamed; review required |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 9 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 9 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `212fb23380f69db34f35e883b4edfa432fd9cfe8b3a448f779724c00bc1bc6f2`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3bf9f2b111fd88d9bab67b1e225da4f723959ae8268c88d645a3c44b1c173bb6`
- Pack digest quoted by the briefing: `212fb23380f69db34f35e883b4edfa432fd9cfe8b3a448f779724c00bc1bc6f2`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Observe the original global object at 0x01668eec, its vtable +0x04 implementation, and the concrete hook receiver before promoting ownership or platform semantics.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Concrete global object and vtable owner at 0x01668eec
- Concrete implementation selected by the vtable +0x04 slot
- Observe the original global object at 0x01668eec, its vtable +0x04 implementation, and the concrete hook receiver before promoting ownership or platform semantics.
- Runtime receiver and call reachability
