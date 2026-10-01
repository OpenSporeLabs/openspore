# Validation 0x005c0100

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg18_ui_scripting/ui_shell_functions.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 192-instruction listing name the same 8 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x005c0100..0x005c0319 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x005c014c; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 15 outgoing call edge row(s) over 8 distinct address(es) for 0x005c0100; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 7 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 192-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 192-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x20), all of which the record accounts for or the listing is the better witness on; the 192-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=192, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x20) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0x0, 0x18, 0x20), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0x0, 0x18) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 1 source constant(s) are absent from the machine listing: 0x287259f6 |
| CONTROL FLOW | `PASS` | `complete` | all 21 conditional branch target(s) in the complete 192-instruction listing lie inside the recovered body span 0x005c0100..0x005c0319, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 192-instruction body names 9 indirect transfer(s): 0x005c0146 dispatches slot 0x20 through the table word in EDX; 0x005c01c0 dispatches slot 0x1c through the table word in EDX; 0x005c01fe dispatches slot 0x1c through the table word in EDX; 0x005c022f dispatches slot 0x4c through the table word in EDX; 0x005c0266 dispatches slot 0x4c through the table word in EDX; 0x005c029a dispatches slot 0x4c through the table word in EDX; 0x005c02d1 dispatches slot 0x4c through the table word in EDX; 0x005c02f2 dispatches slot 0x1c through the table word in EDX; 0x005c0306 dispatches slot 0x4c through the table word in EDX; the machine parse consumed 192 of 192 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 9. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x1c, 0x20, 0x4c, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'bool': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 5 passed, 1 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `af95489d02e66f9c73e36605a18070e360edac2f9ebabb71ffd643c3e38fa5f8`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d987016b653610d923414f6b19cbea193ad109a8f816d7203e8c7a3750c7e433`
- Pack digest quoted by the briefing: `af95489d02e66f9c73e36605a18070e360edac2f9ebabb71ffd643c3e38fa5f8`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-ui-scripting-message-routes`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The cSpaceNames thunk's ignored first stack words are preserved because the following thiscall consumes them.
- The concrete UI shell, service, presentation, and cSpaceNames owners remain unresolved.
- The three-word output and owner type at message+0x04 remain opaque.
- gate-ui-scripting-message-routes
- message owner type
- runtime service availability
- shell, service, presentation, and cSpaceNames owners
