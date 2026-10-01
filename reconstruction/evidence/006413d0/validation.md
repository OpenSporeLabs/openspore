# Validation 0x006413d0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-006413d0/swarm_w1_006413d0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 17-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x006413d0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 17-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 17-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x0), all of which the record accounts for or the listing is the better witness on; the 17-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=17, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (17 of 17 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 17-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 17-instruction body names 3 indirect transfer(s): 0x006413dd dispatches slot 0xa4 through the table word in EAX; 0x006413e9 dispatches slot 0xa8 through the table word in EAX; 0x006413f7 dispatches slot 0xac through the table word in EAX; the machine parse consumed 17 of 17 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 8 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `5b316ce36aab6edf61eaa922054f5aae99e6e15a8c43a4cdf61b021538621cb0`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `90ac78c5347efb5318c9577094323e996307be7d1612bfa1fb181110c88917ed`
- Pack digest quoted by the briefing: `5b316ce36aab6edf61eaa922054f5aae99e6e15a8c43a4cdf61b021538621cb0`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Nothing here is runtime validated. There is no differential trace and no Wine oracle run for this target, so every claim rests on the 43 bytes plus the read-only supporting bytes cited under evidence.provenance.
- The class hierarchy. SporeApp.exe has no MSVC RTTI, the binary's vtable detection never ran headless (0 vtable labels), and the eight tables here are recognised only as data references to this body. So 'this is Sporepedia' comes from the brief's subsystem field and the cluster name, not from a class record, and the class of which this is a virtual method is not established by anything in this package.
- The receiver's real size and what follows its leading word. Only displacement 0x00 is read, so this body contributes no upper bound. The vtable reaches 0xac, which bounds the TABLE and not the object; the object must be at least large enough to hold the leading word, and nothing more is derivable from here.
- The slot index of this body in its own class's table, and hence of the three callees. The eight recorded tables place 0x006413d0 at +0x44, +0x50, +0x60, +0xe0 and +0x108, and the recorded table addresses look like detected run starts rather than guaranteed vtable heads -- several of the words inside them are not code addresses. Until one table's head is confirmed, no ordinal can be stated and no override can be assumed.
- What the three called methods ARE. The displacements 0xa4, 0xa8 and 0xac are fixed, and the targets in the table at 0x013ff648 are 0x00641cd0, 0x00641e10 and 0x00641e40, but this body does not name them, the pack's types list for this VA is empty, sdk_name is null, and the same three displacements resolve to fifteen further different values in the other seven recorded tables. A Sporepedia method name for any of the three would be an invention. This needs the Sporepedia class declaration from the Spore-ModAPI SDK matched against the table at 0x013ff648, which is a different target's job.
- Whether the pushed 0 is a null pointer or a false/0 enum, and its width in the callee's own view. The body pushes a full 4-byte zero and never uses it, so the body cannot distinguish a null pointer from a 32-bit zero-valued flag. The callee's own frame read would settle it, and that is a different target's job.
- Whether the returned EAX is meaningful. The bare RET and the single write to EAX fix the forwarding, but nothing inside this body says whether the 0xac-slot callee returns a scalar its caller wants or a dead EAX. There is no direct caller to read a use out of: the eight inbound references are all vtable slots. Settling it needs either a caller of a reconstructed sibling, or a runtime trace.
