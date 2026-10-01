# Validation 0x01073700

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg18_ui_space/ui_space.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 985-instruction listing name the same 51 direct transfer target(s); 18 intra-procedural jump(s) target inside the recovered body span 0x01073700..0x0107439c are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x01073773, 0x010737bc, 0x01073881, 0x0107393c, 0x01073997, 0x01073a64, 0x01073bca, 0x01073c6e, 0x01073cb4, 0x01073da6, 0x01073ed6, 0x01073f1c, 0x01074085, 0x01074174, 0x010741f8, 0x010742e9, 0x01074320, 0x0107437f; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 87 outgoing call edge row(s) over 51 distinct address(es) for 0x01073700; 4 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 13 address-named callee(s), against the 87 outgoing call edge row(s) and 51 distinct callee(s) the export records; 38 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x008120d0, 0x00812160, 0x0083c800, 0x0093b6c0, 0x009512c0, 0x009512d0, 0x00b21340, 0x00b3d230, 0x00b3d300, 0x00c326b0, 0x00e012b0, 0x00e03ab0 and 26 more; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 87 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 51 of them and no others |
| GLOBALS | `WARN` | `partial` | 23 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 2 member(s) (bytes, vtable) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 5 displacement(s) declared alongside (0xc, 0x10c, 0x120, 0x20c, 0x224) are reported above with the witness each one rests on; the 985-instruction listing is the governing witness for what this body reaches -- it was not consumed in full by the machine parse (983 of 985 instruction(s) read, degraded=True, unparsed=2) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x224, 0x580) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 24 displacement(s) (0x224, 0x228, 0x22c, 0x230, 0x234, 0x258, 0x2f8, 0x31c, 0x56c, 0x570, 0x574, 0x578, 0x57c, 0x580, 0x598, 0x59c, 0x5a0, 0x5a4, 0x5a8, 0x5c4, 0x5d5, 0x61c, 0x690, 0x694), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 22 of those (0x228, 0x22c, 0x230, 0x234, 0x258, 0x2f8, 0x31c, 0x56c, 0x570, 0x574, 0x578, 0x57c, 0x598, 0x59c, 0x5a0, 0x5a4, 0x5a8, 0x5c4, 0x5d5, 0x61c, 0x690, 0x694) the scan does not attribute to the receiver, and the listing governs there; all of that is a lower bound: the evidence is not known to be the whole body, so no absence is claimed from it |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 5 source constant(s) are absent from the machine listing: 0x348, 0x34c, 0x3f800000, 0x41200000, 0x437a0000 |
| CONTROL FLOW | `PASS` | `complete` | all 96 conditional branch target(s) in the complete 985-instruction listing lie inside the recovered body span 0x01073700..0x0107439c, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 985-instruction body names 50 indirect transfer(s): 0x01073724 dispatches slot 0x4 through the table word in EAX; 0x01073789 dispatches slot 0x8 through the table word in EAX; 0x010737d1 dispatches slot 0x4 through the table word in EAX; 0x010737e4 dispatches slot 0x8 through the table word in EAX; 0x0107383a dispatches slot 0x0 through the table word in EAX; 0x0107384e dispatches slot 0x4 through the table word in EAX; 0x01073896 dispatches slot 0x4 through the table word in EAX; 0x010738aa dispatches slot 0x8 through the table word in EAX; 0x010738fb dispatches slot 0x0 through the table word in EAX; 0x0107390f dispatches slot 0x4 through the table word in EAX; 0x01073950 dispatches slot 0x0 through the table word in EAX; 0x01073964 dispatches slot 0x4 through the table word in EAX; 0x010739ac dispatches slot 0x4 through the table word in EAX; 0x010739c0 dispatches slot 0x8 through the table word in EAX; 0x01073a11 dispatches slot 0x0 through the table word in EAX; 0x01073a25 dispatches slot 0x4 through the table word in EAX; 0x01073a92 dispatches slot 0x0 through the table word in EAX; 0x01073afb dispatches slot 0x38 through the table word in EDX; 0x01073bde dispatches slot 0x0 through the table word in EAX; 0x01073bf2 dispatches slot 0x4 through the table word in EAX; 0x01073c79 dispatches slot 0xd8 through the table word in EDX; 0x01073ce7 dispatches slot 0x0 through the table word in EDX; 0x01073d11 dispatches slot 0x0 through the table word in EDX; 0x01073d1e dispatches slot 0x104 through the table word in EDX; 0x01073d6f dispatches slot 0x104 through the table word in EDX; 0x01073db2 dispatches slot 0x4 through the table word in EDX; 0x01073dc9 dispatches slot 0x38 through the table word in EDX; 0x01073e22 dispatches slot 0x24 through the table word in EAX; 0x01073f30 dispatches slot 0x0 through the table word in EDX; 0x01073f44 dispatches slot 0x4 through the table word in EDX; 0x01073f5e dispatches slot 0x80 through the table word in EDX; 0x01073f7d dispatches slot 0x4 through the table word in EDX; 0x01073fa4 dispatches slot 0x90 through the table word in EDX; 0x01073fe0 is FUNCTION_POINTER; 0x01074051 dispatches slot 0xc0 through the table word in EAX; 0x0107407a dispatches slot 0xc0 through the table word in EDX; 0x010740b1 dispatches slot 0xc through the table word in EDX; 0x010740c3 dispatches slot 0x14 through the table word in EDX; 0x010740cf dispatches slot 0x7c through the table word in EDX; 0x01074189 dispatches slot 0x4 through the table word in EDX; 0x0107419d dispatches slot 0x8 through the table word in EDX; 0x0107420d dispatches slot 0x4 through the table word in EDX; 0x01074221 dispatches slot 0x8 through the table word in EDX; 0x0107426f dispatches slot 0x38 through the table word in EDX; 0x010742fd dispatches slot 0x0 through the table word in EDX; 0x01074311 dispatches slot 0x4 through the table word in EDX; 0x01074347 dispatches slot 0x104 through the table word in EDX; 0x01074366 dispatches slot 0x4 through the table word in EAX; 0x0107437d dispatches slot 0x8 through the table word in EAX; 0x01074393 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 985 of 985 instruction(s) with 2 unparsed and degraded=True, and the machine dispatch record independently counts 50, so the dispatch is visible in the machine listing but is not proven: the machine parse is degraded and 2 instruction(s) were left unparsed and 1 of the 50 indirect transfer(s) classify as FUNCTION_POINTER (0x01073fe0), so the dispatch's identity is not established: EDX is loaded from [EDI], but EDI is defined by an immediate or register assignment, not a memory load earlier in the listing, so the word it names is not shown to be a table word and the source span states slot displacement(s) 0xc, 0x14, 0x38, 0x7c, 0x80, 0x90, 0xb8, 0xc0, 0x258, 0x5c4, 0x694, 0x106f146, 0x1476aa4, 0x40464100, 0x41200000, 0x437a0000 and the machine reads 0x0, 0x4, 0x8, 0xc, 0x14, 0x24, 0x38, 0x7c, 0x80, 0x90, 0xc0, 0xd8, 0x104, so the two disagree about which slot is dispatched |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 7 of 8 static checks evaluated, 2 passed, 1 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b8c4bc7eb049b15ea59a7ae0fd03b0aaee45fa6333d3a1d1d3f9c36650f98173`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `2cdcaa0b0057bc3d51960d99e25a229009120bd7800bad0d8344083ddf2d7545`
- Pack digest quoted by the briefing: `b8c4bc7eb049b15ea59a7ae0fd03b0aaee45fa6333d3a1d1d3f9c36650f98173`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-ui-space-initialization`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- SpaceUiVtable and AppSystem service ownership
- The live function's true branch obtains a service value through +0x38 and stores its +0x0c word, but the concrete object type and persistence meaning are not recovered.
- The raw table callbacks at 0x0149c158 and 0x0149c418 remain opaque in the model; no table persistence or message record is synthesized.
- The saved entry image is observed being released at replacement entry and then selected for a final +0x04 transfer; the ownership interpretation is not inferred.
- concrete service object and persistence meaning at +0x38/+0x0c
- gate-ui-space-initialization
- raw table callback ownership
- saved entry image ownership and final transfer
