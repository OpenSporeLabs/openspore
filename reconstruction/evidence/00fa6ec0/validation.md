# Validation 0x00fa6ec0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 40-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 1 distinct address(es) for 0x00fa6ec0; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 40-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 40-instruction listing nevertheless reaches 5 receiver displacement(s) through ECX (0x770, 0x774, 0x784, 0x788, 0x814), all of which the record accounts for or the listing is the better witness on; the 40-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=40, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 5 displacement(s) to the receiver as proven (0x770, 0x774, 0x784, 0x788, 0x814) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 5 displacement(s) (0x770, 0x774, 0x784, 0x788, 0x814), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (40 of 40 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 40-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 40-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `da20f200fcca794b2aa295b7de718e432cc11cfd761a75a176990cf173ecc7d1`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9d4ddda4634e0f0109fd78d7bb6655bf57c6ded804713229775a45a59c631dc5`
- Pack digest quoted by the briefing: `da20f200fcca794b2aa295b7de718e432cc11cfd761a75a176990cf173ecc7d1`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The class name, the method name and the meaning of every receiver word. The binary has no MSVC RTTI, the SDK XML carries no symbol at this address, and the only association available is the transitive vtable classification. Nothing in this package names the class or the method, and the reconstruction names neither.
- What the 0x814 counter counts. 0x00fa7220 increments both 0x814 and 0x818 and 0x00fa5040 increments the ranges' last words, so the two counters at 0x814/0x818 are related, but no listing in this set says what either measures.
- What the body MEANT. The arithmetic is fixed (last += -(span/0xAC)*0xAC) and its two consequences are fixed (a whole-element range ends with last == first; a drifted one keeps only the residue), but nothing in 40 instructions or in the image says whether the original expression was intended as a truncate-to-boundary, a clear, a shrink, or a mistake. The two sibling methods of the same table bound the idiom without deciding it: 0x00fa7220 does copy(begin+0xAC, last, begin); last -= 0xAC (erase(0)) and 0x00fa5040 does copy(begin+i+1, last, begin+i); last -= 0xAC (erase(i)), and neither is this expression.
- What the element's dword at +0xA8 names. It is a 4-byte value the class's search methods compare against a 32-bit argument (0x00fa5080) and 0x00fa7220 reads the dword four bytes below a range's last pointer, which suggests an identifier, but nothing here fixes it. The element's opaque head (0x00..0x37) is likewise untouched by anything in this set -- 0x00f9f620 hands it to a callee whose contract was not read.
- Whether the 0x14 stride of the range headers means a 12-byte vector plus a 4-byte size field, a 12-byte vector plus 4 bytes of padding, or something else. 0x00fa733f shows a capacity compare at the header's +0x08 and nothing in this set reads +0x0C..+0x13, so the tail is left opaque.
- Whether the returned bit pattern means anything at all, as distinct from being a fixed width. The two calls' return values are dead (mechanics.not_modelled) and so is this function's own: no caller in the image reads it. The reconstruction models the register because the listing writes it, and deliberately stops there. If the original source's expression is a leftover whose result no caller used, the value is undefined by intent; if some out-of-image caller (a scripting or modAPI binding) reads it, the pattern is meaningful and this package has not seen that reader.
- Whether the two calls are genuinely dead in the original binary or whether the compiler had more information than this reconstruction does. The reconstruction proves arg1 == arg2 from the three pushes and the absence of any store before the call, which is a property of the emitted code and not of the source. If the source passed a range that the compiler could not prove empty, the source itself is doing something this body no longer shows.
- Which C++ type the original source spelled for the return value, and what that value is for. The WIDTH is not open and the bytes close it: the last write to EAX in the whole body is 0x00fa6f13 IMUL EDI, the low 32 bits of a 64-bit signed product, so the value comes back 32 bits wide and integral, and anything wider or floating is excluded by the listing. The SPELLING is open: std::uint32_t, unsigned int, unsigned long and a 32-bit typedef of the original source's own vocabulary all receive and produce these bytes identically, and abi_derived can say only unclassified_in_EAX with register_class aggregate_unknown, which classifies the register and not the type. Word is a width statement, not a claim about the value. Nothing in this set closes the question: no code in the image calls this body -- the only incoming reference is the DATA reference from 0x01490c48, the slot it occupies in the table whose pointer word is at 0x01490be8 -- so there is no caller whose use of the returned value could tell the types apart.
- __thiscall versus __fastcall. The body reads no argument slot, so the two conventions pass identically and the listing cannot separate them. __thiscall is taken because ECX is dereferenced as a receiver and the sole reference to the body is a virtual-method slot, and the abi record's own confidence is INFERRED, so this is a reasoned choice rather than a proof.
