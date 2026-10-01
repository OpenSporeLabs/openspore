# Validation 0x0041e920

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 34-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; 2 intra-procedural jump(s) target inside the recovered body span 0x0041e920..0x0041e980 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x0041e973, 0x0041e97d; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x0041e920; 245 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `WARN` | `partial` | the complete 34-instruction listing names 1 data address(es) (0x15d115d) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 3 member(s) (flags, kind, stored) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 34-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=34, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 0 displacement(s) to the receiver as proven (none) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x0, 0x12), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0x0, 0x12) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (34 of 34 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 34-instruction listing lie inside the recovered body span 0x0041e920..0x0041e980, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 34-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'const TargetByte*' and the machine return state is WIDTH_4_IN_EAX: the complete 34-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `4bc709a7b2b31d75598af5913b6c1e2be4bef6dbb07527a2b4f5a9bb0f3c8428`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d3421a2907883d223b3c1943be062f65a948d6ca790d9eca3b3be42982d0ea3a`
- Pack digest quoted by the briefing: `4bc709a7b2b31d75598af5913b6c1e2be4bef6dbb07527a2b4f5a9bb0f3c8428`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `The body is a leaf, so no dependency port was introduced.`, `The meaning of the storage mask 0x0030 and of the kind values 0x0001 and 0x0010 is inferred from the compare immediates only.`, `The opaque +0x04..+0x0f region of the slot is never read, so no field evidence exists for it.`, `The sentinel address 0x015d115d is a .data address returned to the caller as a marker; its runtime identity is not established.`, `gate-property-value-resolve-runtime-kind-and-storage-semantics`, `no vtable or callee is involved, so no dependency port was introduced`, `runtime validation not performed; static decompilation and disassembly only`, `the meaning of the storage mask 0x0030 and of the kind values 0x0001 and 0x0010 is inferred from the compare immediates only`, `the opaque +0x04..+0x0f region of the slot is never read, so no field evidence exists for it`, `the sentinel address 0x015d115d is a .data address returned to the caller as a marker; its runtime identity is not established`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The body is a leaf, so no dependency port was introduced.
- The meaning of the storage mask 0x0030 and of the kind values 0x0001 and 0x0010 is inferred from the compare immediates only.
- The opaque +0x04..+0x0f region of the slot is never read, so no field evidence exists for it.
- The sentinel address 0x015d115d is a .data address returned to the caller as a marker; its runtime identity is not established.
- What the 0x015d115d sentinel means to each consumer that receives it
- What the opaque +0x04..+0x0f region of the slot holds
- What the storage mask 0x0030 encodes and how many storage kinds exist
- Whether a direct slot returning its own address is a stable identity or an inlined value
- Why only kind 0x0001 and kind 0x0010 are modelled while the halfword allows 0..0xffff
- gate-property-value-resolve-runtime-kind-and-storage-semantics
- no vtable or callee is involved, so no dependency port was introduced
- runtime validation not performed; static decompilation and disassembly only
- the meaning of the storage mask 0x0030 and of the kind values 0x0001 and 0x0010 is inferred from the compare immediates only
- the opaque +0x04..+0x0f region of the slot is never read, so no field evidence exists for it
- the sentinel address 0x015d115d is a .data address returned to the caller as a marker; its runtime identity is not established
