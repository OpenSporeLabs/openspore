# Validation 0x009817c0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-utfwin-hash-offset-009817c0/utfwin_hash_offset_009817c0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 17-instruction listing name the same 1 direct transfer target(s), including a target reached only by a jump; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x009817c0; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 17-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 17-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x4, 0xc), all of which the record accounts for or the listing is the better witness on; the 17-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=17, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x4, 0xc) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the listing shows 2 displacement(s) the record does not enumerate (0x4, 0xc), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (17 of 17 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 17-instruction listing lie inside the recovered body span 0x009817c0..0x009817f1, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 17-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `dc9919649603e2784a0d4ac7f9803b427e11a44140ca286d605ee2919bbb6358`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `efbfbd044497b92fd3130166dd7a19073ecac220036ddefe38894d13d1e5a795`
- Pack digest quoted by the briefing: `dc9919649603e2784a0d4ac7f9803b427e11a44140ca286d605ee2919bbb6358`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation and no indirect-caller trace was captured, so no concrete caller and no real key value are known. The key-to-offset table is proven from the two bodies but the values a real caller passes, and therefore which members these offsets name, cannot be observed without a trace.`, `The member names and declared types behind offsets +0x00, +0x04 and +0x0c are not established; only the offsets themselves are proven.`, `The owning C++ class name and the interface identity of the target's vtable slot are not established, because SporeApp.exe carries no MSVC RTTI.`, `The provenance of the four comparison constants is not established, so it cannot be checked whether another translation unit contributes further keys to the same table that are unreachable from this entry point.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the two this-adjusting thunks 0x00969b40 and 0x00969b50 members of the same interface as this slot, and is the base class boundary at 0x009817c0 or 0x009817b0? The thunks' SUB ECX displacements match this body's two LEA displacements exactly, which is suggestive, but no slot index is claimed for either thunk's own table.
- Is the MOV dword ptr [ESP + 0x4], EAX at 0x009817d2 an artefact of the original build's tail-call lowering, or an explicit argument write in the source? It is a semantic no-op on the argument either way, so the model does not depend on the answer.
- Is the MOV dword ptr [ESP + 0x4],EAX at 0x009817d2 an artefact of the original build's tail-call lowering, or an explicit argument write in the source? It is a no-op on the value either way, and the test cannot observe it -- mutation M10 confirms that removing it leaves the test green. The model states it rather than assuming it away, and that limit is stated in the test as well.
- Is the base of the vtable containing 0x00951240 at 0x01445c10 identifiable, and does that table share an interface with the two tables that contain this target? Only the single pointer occurrence is established; no slot index is claimed for it.
- Is the base of the vtable containing 0x00951240 identifiable, and does it share an interface with the tables that contain this target? Only the single pointer occurrence is established; no slot index is claimed for it.
- No original-process invocation and no indirect-caller trace was captured, so no concrete caller and no real key value are known. The key-to-offset table is proven from the two bodies but the values a real caller passes, and therefore which members these offsets name, cannot be observed without a trace.
- The member names and declared types behind offsets +0x00, +0x04 and +0x0c are not established; only the offsets themselves are proven.
- The owning C++ class name and the interface identity of the target's vtable slot are not established, because SporeApp.exe carries no MSVC RTTI.
- The provenance of the four comparison constants is not established, so it cannot be checked whether another translation unit contributes further keys to the same table that are unreachable from this entry point.
- What are the declared names and types of the members at +0x00, +0x04 and +0x0c of the receiver? The offsets are proven by the LEA and ADD displacements, but nothing in either body dereferences a typed field, so no field name or type is recoverable from this target alone.
- What are the declared names and types of the words at +0x00, +0x04 and +0x0c of the receiver? The offsets are proven by the LEAs and the ADD; nothing in either body dereferences a typed field, so no name or type is recoverable from this target alone.
- What generates the four constants 0x6ec581fd, 0xee3f516e, 0xeec58382 and 0xeef3af8c? They are used only as equality keys in these two bodies, and whether they are hashes of type names, field names or something else is not observable here.
- What generates the four constants 0x6ec58382, 0xeef3af8c, 0xee3f516e and 0x6ec581fd? They are used only as equality keys in these two bodies. Whether they are hashes of type names, field names or something else is not observable here, and this package therefore does not call the argument a hash in its own types even though the record does.
- Which C++ class owns this address, and which interface is its vtable slot a member of? SporeApp.exe carries no MSVC RTTI, so class identity cannot be read from the binary. The record's vtable list is a transitive classifier association and was deliberately not used to name a class.
- Which C++ class owns vtables 0x01441a2c and 0x014447f8, and which interface is the target's slot a member of? SporeApp.exe carries no MSVC RTTI, so class identity cannot be recovered from the binary. The adjacent ASCII string ConsoleWindow at 0x01441a70 is an adjacent symbol, not a proven class name for either table.
- Why does the 0x6ec581fd arm of 0x00951240 return the receiver with no null guard, while every other arm in both bodies is guarded? The asymmetry is observed, reproduced in the test, and not explained: whether it is intentional in the original source or an artefact of how the resolver was generated is not determinable from the machine.
- Why does the 0x6ec581fd arm return the receiver without a null guard while every other arm is guarded? The asymmetry is observed and reproduced, but whether it is intentional in the original source or an artefact of how the resolver was generated is not determinable from the machine.
