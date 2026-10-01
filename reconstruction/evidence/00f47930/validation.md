# Validation 0x00f47930

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 158-instruction listing name the same 5 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x00f47930..0x00f47adf are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00f479b3; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 7 outgoing call edge row(s) over 5 distinct address(es) for 0x00f47930; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; 1 of those rows name an external import rather than an address and are not address-comparable, as in the projection; the source span names 2 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 158-instruction listing names 3 data address(es) (0x13cc2b8, 0x13f9428, 0x15fd918) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 11 member(s) (active_0c, app_system_20, baseline_10, direct_service_28) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 158-instruction listing is the governing witness for what this body reaches -- it was not consumed in full by the machine parse (157 of 158 instruction(s) read, degraded=True, unparsed=1) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 4 displacement(s) to the receiver as proven (0xc, 0x10, 0x14, 0x18) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 12 displacement(s) (0xc, 0x10, 0x14, 0x18, 0x1c, 0x20, 0x28, 0x2c, 0x30, 0x34, 0x38, 0x3c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 8 of those (0x1c, 0x20, 0x28, 0x2c, 0x30, 0x34, 0x38, 0x3c) the scan does not attribute to the receiver, and the listing governs there; all of that is a lower bound: the evidence is not known to be the whole body, so no absence is claimed from it |
| CONSTANTS | `WARN` | `partial` | the machine listing is not fully parsed: 158 of 158 instruction(s) consumed, degraded=True, unparsed=1 |
| CONTROL FLOW | `PASS` | `complete` | all 15 conditional branch target(s) in the complete 158-instruction listing lie inside the recovered body span 0x00f47930..0x00f47adf, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 158-instruction body names 12 indirect transfer(s): 0x00f4794d is INDIRECT_NON_VTABLE; 0x00f47992 dispatches slot 0x44 through the table word in EDX; 0x00f479c1 dispatches slot 0x34 through the table word in EDX; 0x00f479eb dispatches slot 0x84 through the table word in EAX; 0x00f47a51 dispatches slot 0x38 through the table word in EDX; 0x00f47a6d dispatches slot 0x20 through the table word in EDX; 0x00f47a7c dispatches slot 0x1c through the table word in EDX; 0x00f47a8b dispatches slot 0x28 through the table word in EDX; 0x00f47a9a dispatches slot 0xc through the table word in EDX; 0x00f47aa5 dispatches slot 0x78 through the table word in EDX; 0x00f47ac7 dispatches slot 0x18 through the table word in EDX; 0x00f47ad1 dispatches slot 0x7c through the table word in EDX; the machine parse consumed 158 of 158 instruction(s) with 1 unparsed and degraded=True, and the machine dispatch record independently counts 12, so the dispatch is visible in the machine listing but is not proven: the machine parse is degraded and 1 instruction(s) were left unparsed and 1 of the 12 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x00f4794d), so the dispatch's identity is not established: the target is the memory operand [0x013cc2b8], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 7 of 8 static checks evaluated, 3 passed, 1 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d29b00f77d55b8481d9f603204239296d137a79d8d60116ac2efd3cc30048943`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `1267175e6aa8ba188d861787d410c3e3dfd9b312d3c7ef89e8ebb846cbd26d5f`
- Pack digest quoted by the briefing: `d29b00f77d55b8481d9f603204239296d137a79d8d60116ac2efd3cc30048943`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `required`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- concrete runtime owners and values remain unresolved
- required
