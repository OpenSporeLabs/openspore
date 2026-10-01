# Validation 0x00f9b7f0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 64-instruction listing name the same 5 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 5 outgoing call edge row(s) over 5 distinct address(es) for 0x00f9b7f0; the source span names 5 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 64-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 64-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0x0, 0x28, 0x814), all of which the record accounts for or the listing is the better witness on; the 64-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=64, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x0, 0x28, 0x814) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0x0, 0x28, 0x814), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (64 of 64 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 64-instruction listing lie inside the recovered body span 0x00f9b7f0..0x00f9b8b0, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 64-instruction body names 3 indirect transfer(s): 0x00f9b813 dispatches slot 0x24 through the table word in EAX; 0x00f9b844 dispatches slot 0x80 through the table word in EDX; 0x00f9b878 dispatches slot 0x14 through the table word in EAX; the machine parse consumed 64 of 64 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `4129d270b3d58e35140e9b217e0e71c0b354905be3c0bf2ba1bd932f5f4a8265`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `38b6ba5fef514931a8a12bc8e03361915ae855b0459f5e8e448c08653c2e2781`
- Pack digest quoted by the briefing: `4129d270b3d58e35140e9b217e0e71c0b354905be3c0bf2ba1bd932f5f4a8265`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 0x006b1f90's own frame does not close under any reading either: it pushes three words, and 0x00e5c780 must remove two of them for the body to balance, yet the value 0x00e5c780 leaves in the slot 0x006b1fa5 reads is not accounted for by anything in its 16 instructions. Both 0x006b1f90 and 0x006b4b60 read as service or thunk code rather than ordinary compiled functions, and neither has a metadata record. This does not affect the reconstruction -- both are modelled as observers with the signatures their own terminators and this call site's pushes fix -- but it is why their internals are not claimed.
- 0x006b4b60's own body reads stack slots one through five (0x006b4b7f MOV EBP,[ESP+0x24], 0x006b4b8f MOV EAX,[ESP+0x30], 0x006b4bab MOV EBX,[ESP+0x2c], 0x006b4bd8 MOV EDI,[ESP+0x34]), while this call site pushes only two. Slots three through five therefore hold the caller's own frame and are read as if they were arguments. The body is 138 instructions and installs its own SEH scope, and this call site is inside that scope, so nothing crashes -- but the mismatch is unexplained by anything in this package and it means 0x006b4b60's real prototype is not the two-argument one this call site implies.
- Runtime validation is not available for this VA: the only reference to 0x00f9b7f0 in the image is the DATA xref from 0x01490c6c, so there is no direct call site to instrument and no reachable entry point outside a constructed object. Every claim in this record is static.
- The dword the +0x24 dispatch publishes in the frame's leading word (frame+0x00) is read exactly once, at 0x00f9b819, and is then treated as a pointer to a 0x14+-byte record. Nothing in this set writes that word after the dispatch and nothing shows what type the pointed-at record is beyond its +0x12 being compared with 0x0a. Whether it is the same kind of record as the one at frame+0x04 is NOT established: 0x00427fd0, which documents the frame+0x04 record's layout, is never handed frame+0x00.
- The identity of the three table entries (+0x24 and +0x14 on the object at receiver+0x28, +0x80 on the receiver) is unknown. They are reachable only through a table the objects name through their leading word, and this binary has no MSVC RTTI, so the table at 0x01490be8 identifies nothing on its own. The packages that already carry 0x0093db80 (pkg-dfw-006a2e20) do not cover them.
- The return type is inferred as void. Both records leave it open (abi.return_semantics 'unclassified_in_EAX', ghidra_function.return_type 'undefined') and the listing's three edges leave three different dead words in EAX. Nothing writes EAX for a caller, so void is the only reading consistent with the machine, but a differential run would settle it.
- The subsystem label 'Terrain' and the cluster 'terrain-world' come from the triage record, not from this body. Nothing in the listing, the callees or the vtable supports or contradicts it. The one fact that is suggestive -- the type code 0x000a compared at 0x00f9b81d, 0x00428009 and 0x0041ea10 -- is suggestive of nothing in particular, and no claim is made.
- The two indirect dispatches at 0x00f9b813 and 0x00f9b878 have no address, so their terminators cannot be read and their 8-byte cleanups are INFERRED. The inference is pinned three ways -- the frame requirement, the register-restoration consequence of the alternative, and the fact that only this value makes every stack-relative address land on a documented field -- but it cannot be confirmed from this binary. Resolving it needs a runtime capture of ESP across either call, or a caller of 0x00f9b7f0 whose own frame shows how much it expects back.
- What the object at receiver+0x28 IS is not stated by any listing in this set. It is read at exactly one word, it is re-read three times, and it is handed to two table entries and one cdecl service. The receiver's word at +0x814 is likewise unnamed: the body only compares it against a candidate and takes its address. Naming either would be a member story the evidence does not carry.
