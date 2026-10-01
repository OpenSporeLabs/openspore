# Validation 0x0041dc10

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 37-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x0041dc10; 156 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the complete 37-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | 3 source field-offset declaration(s) (field x, field y, field z) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (37 of 37 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 37-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 37-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is SRET_SUSPECTED and the source span declares return type 'OpaqueVector3*': the ABI envelope records a hidden-pointer return hypothesis (suspected), so the return register holds an address rather than the value and no width read off it would be a claim about the wrong value. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 5 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `fcd14989b746a88aa6da3387078a4f6ff87ce6ddda1149b3b31a8226a0a9c6db`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `917e85aa0a25ba154828267b38b381a208267facbf84ef1daf2e430246170c51`
- Pack digest quoted by the briefing: `fcd14989b746a88aa6da3387078a4f6ff87ce6ddda1149b3b31a8226a0a9c6db`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Aliasing between destination and either source is not guarded and is covered only by the model test.`, `Floating point addition follows the default SSE rounding mode; no rounding-mode manipulation is observed.`, `No original-process invocation was captured.`, `The modelled receiver is only 0x0c bytes wide, so any wider use of the same object is outside this target.`, `floating point addition follows the default x87/SSE rounding mode; no SSE rounding-mode manipulation is observed`, `gate-vector3-add-runtime-rounding-and-aliasing`, `runtime validation not performed; static decompilation and disassembly only`, `the native body is a leaf, so no dependency port is required and none was introduced`, `the receiver struct is only 0x0c bytes wide here, so any wider use of the same object is outside this target`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Aliasing between destination and either source is not guarded and is covered only by the model test.
- Floating point addition follows the default SSE rounding mode; no rounding-mode manipulation is observed.
- No original-process invocation was captured.
- The modelled receiver is only 0x0c bytes wide, so any wider use of the same object is outside this target.
- Whether any caller depends on the intermediate staging of the three sums
- Whether callers rely on the returned pointer or only on the side effect
- Whether destination is guaranteed distinct from the two sources in real callers
- Which namespace the 0x0c-byte vector type belongs to
- floating point addition follows the default x87/SSE rounding mode; no SSE rounding-mode manipulation is observed
- gate-vector3-add-runtime-rounding-and-aliasing
- runtime validation not performed; static decompilation and disassembly only
- the native body is a leaf, so no dependency port is required and none was introduced
- the receiver struct is only 0x0c bytes wide here, so any wider use of the same object is outside this target
