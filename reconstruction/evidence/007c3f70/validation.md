# Validation 0x007c3f70

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-007c3f70-receiver-default-block-init/receiver_default_block_init_007c3f70.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 21-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x007c3f70; 41 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `WARN` | `partial` | the complete 21-instruction listing names 5 data address(es) (0x013f0620, 0x01635db8, 0x01635dbc, 0x01635dc0, 0x01635dc4); the data-reference artifact is read whole and records 5 reference row(s) out of this body covering every address under review, with access mode(s) read=5 |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 21-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x140), all of which the record accounts for or the listing is the better witness on; the 21-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=21, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x140) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 13 displacement(s) (0x140, 0x144, 0x148, 0x14c, 0x150, 0x154, 0x158, 0x15c, 0x160, 0x164, 0x168, 0x16c, 0x170), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 12 of those (0x144, 0x148, 0x14c, 0x150, 0x154, 0x158, 0x15c, 0x160, 0x164, 0x168, 0x16c, 0x170) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (21 of 21 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 21-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 21-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the ABI record names XMM0 as the return register; an SSE register: the machine fixes where the value travels and not whether the source said float, double or a vector, so the machine fixes where the value travels and not the C type, and no width can be claimed. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `65e3cf8d92f8f547df174e97ac20c851df2fff53b475b5699f46ef77d5419386`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9e3e87a631386eb73509a86ae8af8d5c86a400eda421c565c496bae5860488a7`
- Pack digest quoted by the briefing: `65e3cf8d92f8f547df174e97ac20c851df2fff53b475b5699f46ef77d5419386`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Class, vtable identity and SDK name are unknown: this binary carries no MSVC RTTI and the entry is not in any vtable slot per the record's dispatch counts (0 indirect calls, 0 vtable-shaped loads).
- No runtime value is claimed for the four writable .data globals 0x01635db8..0x01635dc4; /read_memory shows zeros in the static image, which is not a claim about the running program.
- The bytes below 0x140 are never touched by this body; no evidence here says which code initialises them.
- Whether any of the 65 call sites reads the residual XMM0 (which still holds the 0x013f0620 word at the RET) was not established; the entry is declared void on the grounds that no instruction produces a result.
- __thiscall vs __fastcall: the derived record keeps both open; every observed site loads ECX and pushes nothing, but nothing rules out __fastcall with a discarded EDX.
