# Validation 0x00faad80

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00faad80/sw2_00faad80.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 242-instruction listing name the same 15 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x00faad80..0x00fab0d1 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00faaeb9, 0x00fab0a7; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 15 outgoing call edge row(s) over 15 distinct address(es) for 0x00faad80; the source span names 15 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 242-instruction listing names 7 data address(es) (0x13ec4d0, 0x1473c70, 0x1485720, 0x16c9e7c, 0x16c9e80, 0x16c9e84, 0x16c9e8c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 242-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0xa48), all of which the record accounts for or the listing is the better witness on; the 242-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=242, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0xa48) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 18 displacement(s) (0x0, 0x2c, 0xfc, 0x110, 0x111, 0x114, 0x1d0, 0x20c, 0x210, 0x30c, 0x310, 0x314, 0x33d, 0x360, 0x364, 0x36c, 0x370, 0xa48), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 17 of those (0x0, 0x2c, 0xfc, 0x110, 0x111, 0x114, 0x1d0, 0x20c, 0x210, 0x30c, 0x310, 0x314, 0x33d, 0x360, 0x364, 0x36c, 0x370) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (242 of 242 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 19 conditional branch target(s) in the complete 242-instruction listing lie inside the recovered body span 0x00faad80..0x00fab0d1, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 242-instruction body names 6 indirect transfer(s): 0x00faadb0 dispatches slot 0x80 through the table word in EAX; 0x00faae7c dispatches slot 0x1c through the table word in EDX; 0x00faae94 dispatches slot 0x15c through the table word in EDX; 0x00faaec6 dispatches slot 0x10 through the table word in EDX; 0x00faaf34 dispatches slot 0xd8 through the table word in EAX; 0x00faafb5 dispatches slot 0x4c through the table word in EDX; the machine parse consumed 242 of 242 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 6. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 2 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9a684e6c0a7668f853e8062d4f86dc1a9a6b3ce464a2531dc84e2ead586b33f3`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `4c97dd742de08b3d27b31a008f318c5266ba66942bec1c7e36bca827d9f8de65`
- Pack digest quoted by the briefing: `9a684e6c0a7668f853e8062d4f86dc1a9a6b3ce464a2531dc84e2ead586b33f3`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- EVIDENCE COVERAGE is 10 of 17 static categories for this target and no source file, sidecar field or metadata edit can move it: the validator derives it purely from the pack's per-category availability, and this pack reports seven unavailable. It is reported, not chased.
- Nothing inside any of the fifteen direct callees was reconstructed, and no claim is made about any of them beyond the argument list, order and convention its call site fixes, plus the two callees whose own bodies were read out of the image (0x0067dd80 and 0x00f96370) because the body depends on what they do.
- The ECX receiver of 0x00fbf570 is NOT DETERMINED by this body, and this package does not guess it. 0x00faaf0b is the only call whose ECX the listing does not reload; the last write is MOV ECX,ESI at 0x00faaec4 for the slot+0x10 call, whose return type this listing does not fix either. The model passes a declared sentinel and the model test asserts the callee receives exactly it, so the non-claim is checkable. Settling it needs 0x00fbf570's own body.
- The committed ABI record's return_semantics is the phrase 'float_or_x87_in_ST0' and this package declares void. The record's own inference RT1 is an APPROXIMATION derived from a single observation -- 'an x87 or SSE instruction appears in the body' -- and the listing refutes it: the x87 stack is empty at 0x00faade0 and at 0x00fab0d1, because every x87 value the body produces is stored straight back or popped. The honest options were to declare a type true of the listing and record the disagreement (what this package does) or to declare void only if the bytes genuinely produce nothing (also true here, and the reason the choice is not a stretch). No typedef was invented to make the phrase compare equal, and the phrase itself is left intact in the evidence pack. The integrator should treat the record's return clause as superseded by the bytes.
- The conventions of six callees are asserted only as far as the call sites fix them. 0x0067dd80, 0x00690120, 0x006909b0, 0x00f96370, 0x00f96f90 and 0x00f977c0 are all called with no pushed word, so only 'receiver in ECX, no stack argument' is claimed; for a function with no stack arguments cdecl and thiscall are indistinguishable at the call site, and this package does not read the other five terminators to say more. 0x0067dd80's six bytes were read and it is a plain C3.
- What the +0x111 byte is for is not established. It is the third disjunct of the resync condition, so setting it forces the resync block, and no instruction in this body writes it. Whether a sibling body writes it, and what setting it means, is outside what this listing can show.
- What the literal 0x03fbae24 selects is not established. It is a 32-bit value, not a pointer (it is below the image's data segment) and not a float (as a float it would be about 1.09e-38, i.e. a denormal, which no compiler emits for a constant). Ghidra's own decompilation casts it to a pointer, which is the same 32 bits. This package carries it as an opaque Word named kStageId and claims nothing about it.
- What the relay word at the receiver's +0x81c holds is not established. This body clears it, hands the old value to 0x00690120, hands its ADDRESS to 0x00faacd0, and hands whatever 0x00faacd0 left to 0x006909b0 -- including a NULL receiver when the word started null. Whether that is a smart handle, a refcounted pointer or a plain word is not determinable here.
- What the six objects at the receiver's +0x118 hold is not established. This body only LOADS each of the six words and passes it as a receiver to three callees; it never dereferences one. Whether they are sub-objects of this receiver, elements of an array, or something else is not determinable from this body, and the model deliberately names nothing inside them.
- What the three .data words at 0x016c9e7c, 0x016c9e80 and 0x016c9e84 are is not established. This body zeroes them and nothing else in the 242 instructions touches them, and no record in this repository names them. The address 0x016c9e8c, passed by value sixteen bytes higher and never read through, is plausibly part of the same structure, but nothing here establishes that and nothing is claimed.
