# Validation 0x00587a20

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `WARN` | `partial` | the dependency edge list is truncated at export time, so the machine callee set is a lower bound and cannot bound the source |
| GLOBALS | `NOT_AVAILABLE` | `none` | no independent data-reference evidence exists for this target; the xref export records 0 |
| FIELDS/OFFSETS | `WARN` | `partial` | 79 source field-offset declaration(s) (displacement 0xb9, field a_10, field a_14, field a_18) are reconstruction-declared and no machine-derived struct layout exists to corroborate them |
| CONSTANTS | `WARN` | `partial` | source constants are present and no machine listing is collected for this target, so they cannot be corroborated |
| CONTROL FLOW | `NOT_AVAILABLE` | `none` | no machine control-flow evidence exists for this target: the bridge never populates the dispatch field and no listing is collected |
| VIRTUAL DISPATCH | `NOT_AVAILABLE` | `none` | no machine dispatch evidence is collected for this target; the xref export records 1 vtable reference(s) and the record associates 1 vtable(s), which are not independent of each other |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 5 of 8 static checks evaluated, 2 passed, 3 had no evidence to evaluate; 9 of 16 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 9 of 16 static evidence categories are available

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `runtime validation not run: no positive hash-pinned original-process trace reaches 0x00587a20 in the committed corpus`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- All 54 direct callees are Ghidra autogen FUN_* names with no SDK name and no recovered body in this repository. Their conventions and argument counts come from their own epilogues, which is enough to call them correctly but not enough to say what they do.
- Does the +0x4d0 float reach both callees? Yes in the reconstruction, and this is a correction of the decompilation rather than a doubt: FSTP overwrites the dead PUSH, so 0x007c53d0 receives the same float the +0x58 entry receives. If the +0x58 entry mutated the receiver in between, the two would still see the same value, because the float was loaded before that call. The open part is only what the two callees do with it.
- How do the 85 indirect callees pop? The balance constraint forces only 0x00587b21. For the other 84 the constraint is satisfied by 'each pops its arguments' but does not uniquely force it; 21 sites with arguments are left free by the constraint system.
- How far does the stack object extend? 0x00421cf0 can address sub-object slots past the 0x40 bytes the frame leaves above the object base, and nothing in this body distinguishes a callee that never sets a high mask bit from one that writes past this caller's frame. Modelled at 0x40, which is correct under the first reading.
- How far does the stack object really extend? 0x00421cf0 can address sub-object slots up to receiver+0x100, but the frame leaves only 0x40 bytes above the object base. The two readings are: the slot 0x44 callee never sets a bit in sub_mask above bit 2, or it writes past this caller's frame. The reconstruction models 0x40 bytes, which is correct under the first reading and not under the second, and nothing in this function distinguishes them.
- Is 0x015eebec a pointer to a pointer? 0x00587b83 loads the word at that address and pushes it as the argument of a table entry at +0x20. Whether the word is itself a pointer, and what it points at, is not decidable here.
- The derived ABI record for this target reports return_register ST0 and return_semantics float_or_x87_in_ST0. That is contradicted by the balanced FLD/FSTP pair at 0x00587b10/0x00587b1b and by an epilogue that reads no return register, so it is not adopted; but the record is the oracle the validator compares against, and this package's `void` will be reported as a disagreement rather than a match.
- What are 0x347536b, 0x3475385 and 0x34753a0, and what distinguishes 0x1d6253c0 from 0xb07c3bbf? They are the literals the two 0x00a206f0 blocks push, and 0x013eb850 shows the string `queuing %ls for bake` four bytes past one of this body's tables, so the neighbourhood is a resource/bake queue record. Nothing in this function says what the words address.
- What are the 13 globals reached through the two-instruction getters? Their MOV EAX,[addr] ; RET shape is established; their meaning is not.
- What class is the receiver? SporeApp.exe carries no MSVC RTTI, so the `cEditor` name on the Ghidra parameter is the SDK symbol and not a machine-derived type. 61 offsets are pinned; the meaning of none of them is established, and 20 of the members are read as pointers to at least six different pointee layouts (count at +0x04 with table at +0x00, count at +0x08 with table at +0x04, table at +0x04 with no count, count at +0x40 with table at *[p], and the rest plain).
- What class is the receiver? SporeApp.exe carries no MSVC RTTI, so the `cEditor` name on the Ghidra parameter is the SDK symbol and not a machine-derived type. 61 offsets are pinned; the meaning of none of them is established.
- What do 0x347536b, 0x3475385, 0x34753a0, 0x60c874f, 0x30c11c7, 0x1d6253c0 and 0xb07c3bbf index? The listing pushes them and nothing here identifies them. 0x13eb430 and 0x13f5ca0 were read out of the binary and are the strings "Editor" and "editor".
- What does bit 1 of p_0d4[0xdc8] mean? It gates both 0x00573d70 and 0x0043a9a0 and nothing else in the body, so it is a one-bit mode flag on that member. Its name and its set/clear sites are outside this function.
- What is the arity of the table entry at +0x44 (0x00587a95)? The listing pushes no argument and the stack object's address is not in a pushed register either: it sits at the callee's third stack-argument position inside this frame, which is only consistent if the callee is variadic or has three or more arguments and pops them. The first two argument words are below the 0x44-byte reservation, in the caller's own frame, and this body never writes them. Callee arity and the values of those two words are both undecidable from this function alone.
- What is the arity of the table entry at +0x44 (0x00587a95)? The listing pushes no argument for this call and the stack object's address is not in a pushed register either: it sits at the callee's third stack-argument position inside this frame, which is only consistent with a variadic callee or one of three or more arguments that pops them. Not decidable from this body.
- Which 8 of the 85 indirect sites does the 49/20/13/2/1 arity split refer to? The split is measured by the stack dataflow; the per-site attribution is in the .cpp comments only for the sites the comments name.
- runtime validation not run: no positive hash-pinned original-process trace reaches 0x00587a20 in the committed corpus
