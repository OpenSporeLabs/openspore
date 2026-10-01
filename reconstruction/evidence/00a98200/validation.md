# Validation 0x00a98200

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 110-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00a98200; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 110-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 110-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x10), all of which the record accounts for or the listing is the better witness on; the 110-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=110, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x10) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0xc, 0x10, 0x50), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0xc, 0x50) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (110 of 110 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 11 conditional branch target(s) in the complete 110-instruction listing lie inside the recovered body span 0x00a98200..0x00a98336, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 110-instruction body names 4 indirect transfer(s): 0x00a9824a dispatches slot 0x14 through the table word in EDX; 0x00a98277 dispatches slot 0x14 through the table word in EDX; 0x00a982a1 dispatches slot 0x14 through the table word in EDX; 0x00a9832e dispatches slot 0x14 through the table word in EDX; the machine parse consumed 110 of 110 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `da46022a7f12512b163a7147fdff596fc32ca9687a6b5d569e898c2de934ade4`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e0eed151fd3717939ae7298303891f5970d250ad84c235875d51fa6419169138`
- Pack digest quoted by the briefing: `da46022a7f12512b163a7147fdff596fc32ca9687a6b5d569e898c2de934ade4`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The canonical machine record's return classification remains in tension with the reconstruction. abi.value.return_semantics is `unclassified_in_EAX` and abi_derived.return.void_possible is false, while this reconstruction declares void on the grounds that no path writes EAX with a value for the caller and Ghidra's own decompilation of the same listing agrees. The disagreement is published rather than resolved: see observed_original_abi.return_note. If the integrator prefers the machine phrase, the honest alternative is to keep `void` in the source and accept the RETURN SEMANTICS warning, which is what happens when the sidecar's return_type is not taken as the canonical claim.
- The identity of the 0x016514cc global. It is the only source of the service pointer in the whole program, this body never writes it, and nothing in this pack identifies it. It is named in this sidecar and in the package header but deliberately not in the reconstructed source, so the repository's GLOBALS check is not asked to corroborate an address the listing never names.
- What the flag word's bit assignments mean. Bits 0, 1 and 2 select which key and which pair dword goes out, bit 4 selects the list call, and bits 5..9 select which of the record's five dwords fills which of the list's five conditional dwords. That the mapping is bit N to the Nth pair is arithmetic over the shifts; the MEANING of any bit is not established here.
- What the four indirect callees do with the frame object they are handed, and whether either callee writes through it. The model assumes nothing about that: the pair's two dwords and the list's three unconditional dwords are written by this body before every call, the list's five conditional dwords are not, and the body never reads any of them back. Whether a callee mutates the frame is not established, and the model test does drive one case where a callee does (kPokeListSlot0) precisely so the frame is treated as shared and mutable rather than as private.
- What the two immediate keys 0xe7a8472 and 0xe7a8474 are. They are pushed as the first stack word of three of the four calls and nothing in this body, in this pack or in the callee's five bytes identifies them. They look like property or event identifiers -- 0xe7a8472 is pushed twice with the pair's first dword 0 and 1, and 0xe7a8474 once with it 0 -- but that is a reading of the pattern, not evidence, and nothing is claimed.
- Whether EBP stays zero across the four calls. The listing borrows EBP as the literal-zero third argument (0x00a9821d) and never re-zeroes it, so a callee that violated the x86-32 callee-saved convention would change the original's behaviour from the second call on. The C++ observers in the model test preserve EBP by that same convention, so the case cannot be driven and is not claimed.
- Whether the service object's leading word is a vtable pointer. The body performs a two-level table read at displacement 0x14 and the repository's site classifier reports VTABLE_SLOT, but that classifier does not check where the base register's word came from. The header and the source therefore call it a table and not a vtable, and the model test installs an ordinary aligned byte run rather than a vtable image.
- Whether this function is a virtual method at all. The xref export records one in-reference and it is a DATA reference from 0x01458794 inside the table at 0x01458788, and reading that table's bytes puts this body at table+0x0c. The record's own vtable association agrees. Nothing fixes a class name, and no record in this pack shows the constructor that installs the table, so the class, its base and its other slots are all unestablished.
