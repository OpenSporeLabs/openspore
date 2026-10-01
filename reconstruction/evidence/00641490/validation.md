# Validation 0x00641490

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00641490/swarm_w1_00641490.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 25-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00641490; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 25-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 25-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x0, 0x4), all of which the record accounts for or the listing is the better witness on; the 25-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=25, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x0, 0x4) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0x4), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (25 of 25 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `WARN` | `partial` | 3 of 3 conditional branch target(s) fall outside the recovered body span 0x00641490..0x006414cf, so the listing is a slice and flow continues past it; the source span declares if |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 25-instruction body names 1 indirect transfer(s): 0x006414b6 dispatches slot 0x90 through the table word in EDX; the machine parse consumed 25 of 25 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 15 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'std::uint8_t' and the machine return state is WIDTH_1_IN_EAX: the complete 25-instruction listing writes EAX at a determinate 1-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `be3e91cbdebc25173dbf48be7748814926c5494980ab0bf733607e4d71f3d9f0`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8f425ec78b1913759093a847b0dbcd700cd0bc31301cebd76e701f5cd88ed7b5`
- Pack digest quoted by the briefing: `be3e91cbdebc25173dbf48be7748814926c5494980ab0bf733607e4d71f3d9f0`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `no original-process trace exists for this VA; the runtime axis is GATED at 0 and nothing was attempted`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the pair's uninitialised state ever observable? The body reads the pair only after the slot call reported a non-zero AL, and the one slot occupant this evidence identifies always writes both words on that path -- but the body cannot know that of a table it has not seen, so a table whose 0x90 entry returns non-zero without writing the pair would make this body read uninitialised frame bytes. That is a property of the machine, not of the reconstruction; the model zero-initialises the object and says so in the .cpp.
- The committed record's body span is four bytes short. ghidra_function reports body_end 0x006414cf, size 64 and 25 instructions, and all three conditional branches in it target 0x006414d0 -- outside that span. The image shows the body continuing to 0x006414d6 and the live decompilation follows it. Whether the right fix is to extend the recorded body, to split the failure block into its own function, or to leave it, is a decision for the integrator and for whatever owns the evidence pack; this package reconstructed the body the bytes show and says so in function_extent. It is also why CONTROL FLOW cannot pass for this target: the check bounds the body with the committed listing's own addresses, and no source shape can change that.
- The declared return type is std::uint8_t and the record's canonical return claim is the string 'integral_in_EAX'. Those do not agree textually, which is why RETURN SEMANTICS is a WARN and not a PASS. The machine fixes the width the body writes and tests (8 bits in AL, at 0x006414c9, 0x006414d0 and 0x006414b8) and no record narrows the register class to a width; a C++ spelling that satisfied the string comparison would be a fiction, so the byte is declared and the disagreement is reported instead of gamed. The original source almost certainly said `bool` (the MOV AL,1 / XOR AL,AL idiom is what MSVC emits for it) but that is INFERRED, not machine-fixed, and the model does not claim it.
- What do 0x00552300's four return values (0x0, 0x1, 0x2, and the word it loads at [EBP-0x30]) mean, and why does this body want the one at 0x0055241f -- the arm its listing takes after 0x005523f9 MOVZX EAX,AL / 0x005523fc TEST EAX,EAX falls through to when its own 0x00550970 call returns zero? The body tests only 2 and names only 2. The callee is not owned by this package and nothing about its internals is asserted beyond its convention, its pointer argument and the four values it can return.
- What do the pair's two words measure? Nothing in either body says. 0x006417d0 fetches them through its own receiver+0x1c and rejects all-ones in both, which is consistent with a range, an extent or an index pair, and the body ANDs them rather than comparing either, which is consistent with 'both ends unset'. No name is used.
- What is the function at slot displacement 0x90? Three tables hold 0x006417d0 there, and that function's shape (one stack word, writes two words, rejects all-ones in both, returns AL) matches everything this body does with the call -- but the transfer target is a run-time value in EDX and this body never names it, so a table whose 0x90 entry is a DIFFERENT function of the same signature would be indistinguishable here. The model calls through the loaded pointer and the test supplies its own observer, which is the honest shape for a dispatch.
- What is the receiver's real extent? 0x10 is where this body and 0x00552300 were observed reaching; the object may be larger, and the three dwords 0x00552300 reads through receiver+0x04 are themselves opaque. No member is named for any of them.
- Why are this body's slot entries at +0x80 in three tables and at +0x74 in two others? A single fixed displacement cannot be both. Either the two groups are primary and secondary tables of a multiple-inheritance hierarchy (in which case the object's address within itself differs by four bytes between them) or the record's table starts are off by four bytes for one group. Nothing in this repository settles it, and no slot index is claimed anywhere in this package because of it.
- no original-process trace exists for this VA; the runtime axis is GATED at 0 and nothing was attempted
