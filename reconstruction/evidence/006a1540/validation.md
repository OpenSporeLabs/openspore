# Validation 0x006a1540

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_dfw_006a1540/dfw_006a1540.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 74-instruction listing name the same 2 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x006a1540..0x006a15f3 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x006a15a0, 0x006a15e2; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 2 distinct address(es) for 0x006a1540; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 74-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x18) and the 0 the complete 74-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x18, 0x1c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (74 of 74 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 74-instruction listing lie inside the recovered body span 0x006a1540..0x006a15f3, so the branch graph is closed inside it; the source span declares if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 74-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'bool' and the machine return state is WIDTH_1_IN_EAX: the complete 74-instruction listing writes EAX at a determinate 1-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a4a98ff51009a9a178b1301b963669b2e81fa90ef221dcfc2473ff7c070ed541`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6fb73f40ac2c0c71f49a91e01973f71f440e6d44a0da1380dd96a1761bf92f2a`
- Pack digest quoted by the briefing: `a4a98ff51009a9a178b1301b963669b2e81fa90ef221dcfc2473ff7c070ed541`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original-process trace exists in this repository, so every claim here is static. A trace would be needed to confirm the wire byte order, the meaning of the count word on the wire, and the identity of the type tag at payload+0x12.
- The 0x01408864 anomaly. The word at 0x01408864, one slot after this target's, holds 0x006a3030 -- which lies inside the body of App::PropertyList::Read (0x006a2f60..0x006a306c) and mid-instruction within CALL 0x0093a780 at 0x006a302e. ghidra_get_function_by_address 0x006a3030 resolves to Read, so no function is defined there. Whether that word is a link-time-folded thunk, a mis-relocated entry, or a table that is not this class's vtable is not established. It does not affect this reconstruction, which claims nothing beyond the single word at 0x01408860.
- The App::Property 4-byte-versus-0x14-byte layout conflict (knowledgegraph/research/conflicts/track-b-vtable-fields.json, TB-FL-006, status preserved_alternatives). This body establishes the element stride as 0x18 and reads the first 4-byte word and the address at +0x04; it never reads further, so it cannot settle whether the payload is a 4-byte inline field or a 0x14-byte inline block. The live decompilation of the callee 0x00693390 is consistent with a 0x14-byte inline block (it reads 32-bit words at +0x00/+0x04/+0x08/+0x0c, a 16-bit word at +0x10 and a 16-bit type tag at +0x12, all inside the 0x14 bytes that follow element+0x04), which matches the wave6 model, but that is a claim about the callee and not about this writer, so the ledger's status is left untouched.
- The App::Property 4-byte-versus-0x14-byte layout conflict (knowledgegraph/research/conflicts/track-b-vtable-fields.json, TB-FL-006, status preserved_alternatives; and track-d-data-serialization.json, TD-DATA-002 and TD-DATA-003, both unresolved). This body fixes the stride at 0x18, reads the first 4-byte word and forms the address at +0x04, and never reaches further, so it cannot settle whether the payload is a 4-byte inline field or a 0x14-byte inline block. The model's opaque 0x14 bytes are carried as unexamined bytes, not as a layout claim, and the ledger's status is left untouched.
- The extent of the receiver past +0x1c. This body reads only +0x18 and +0x1c, so the model stops at +0x20. A parent word at +0x30 and a mode byte at +0x2c exist in other reconstructions of the same table; neither is read here and neither is claimed.
- The extent of the receiver past +0x1c. This body reads only +0x18 and +0x1c, so the model stops at +0x20. The live Ghidra type and the wave6 model both carry a parent word at +0x30 and a mode byte at +0x2c, but neither is read here and neither is claimed.
- The receiver type. The demangled symbol says App::PropertyList::Write, but the live Ghidra signature types the receiver as DirectPropertyList * and the decompiled body names it DirectPropertyList *this, while the same table at 0x01408820 also holds App::PropertyList::Clear (0x006a2a80) and App::PropertyList::GetPropertyIDs-adjacent 0x006a3030. The binary has no MSVC RTTI (0 vtable labels were ever produced headless), so which concrete class owns the slot at 0x01408860+0x40 cannot be settled statically. The model uses the displacement-only name OpaquePropertyList and claims no class identity.
- The receiver type. The demangled symbol says App::PropertyList::Write, the live Ghidra signature types the receiver DirectPropertyList *, and the same table at 0x01408820 also holds App::PropertyList::Clear (0x006a2a80) and 0x006a3030 inside App::PropertyList::Read. The binary has no MSVC RTTI, so which concrete class owns the slot cannot be settled statically. The model uses displacement-only names and claims no class identity.
- What the 4-byte word at element +0x00 means. It is read and written verbatim as one stream word immediately before the payload, so it is very likely a property key or type id, but this body establishes only that it is a 4-byte word at that displacement. No name is claimed.
- What the entry word at +0x00 means. It is a 32-bit value written verbatim as one stream word immediately before the payload, so it is very likely a property key or type id, but this body establishes only that it is a 4-byte word at that displacement. No name is claimed.
- Whether the fourth argument of 0x0093aa70 selects byte order. Its live body byte-swaps each element when that argument is not 1 and copies count*4 raw bytes when it is 1, and it also invokes the stream's virtual at +0x10 when the argument is not 1 -- which suggests the argument is an endianness or format selector. Both call sites here pass 0, so this writer always takes the swapping path. The argument's actual meaning is not established.
- Whether the fourth argument of 0x0093aa70 selects byte order. Its live body byte-swaps each element when that argument is not 1 and copies count*4 raw bytes when it is 1, which suggests an endianness or format selector, and it also invokes the stream's virtual at +0x10 when the argument is not 1. Both call sites here pass 0, so this writer always takes the swapping path. The argument's actual meaning is not established and the model's observer takes it as an opaque word.
- Whether the sink's vtable words at +0x10 and +0x14, which 0x0093aa70 invokes with no observed argument, are an endianness setter and a validity check. The decompiler shows no arguments for either, and a non-zero result from +0x14 makes that callee's write fail immediately without touching the sink. None of that is visible from this body.
- Whether the stream's vtable words at +0x10 and +0x14, which 0x0093aa70 invokes with no observed argument, are an endianness setter and a validity check. The decompiler shows no arguments for either, and a non-zero result from +0x14 makes the write fail immediately without touching the sink.
- Whether the two quotients can ever differ in the original. They are evaluated either side of the first stream write, and nothing in this body mutates the receiver, so on any execution reachable from this body they are equal. Whether a subclass overriding the stream write could mutate the list mid-call is not established. The model keeps the two evaluations separate because the listing has them separate; the test makes them differ only by mutating the receiver from the observer, which is a test device and not a claim about the original.
- Whether the two quotients can ever differ. They are evaluated either side of the first stream write, and nothing in this body mutates the receiver, so on any execution reachable from this body they are equal. Whether a subclass overriding the stream write could mutate the list mid-call is not established.
- Who calls this body, and under what conditions. fan_in is 0 and the caller list is empty, so nothing establishes the entry state, whether the range is ever non-empty in practice, or what a failed write is expected to mean to a caller.
