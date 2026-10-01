# Validation 0x00b515e0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b16/b515e0_cached_object_validate.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 32-instruction listing names 2 data address(es) (0x167ecd0, 0x167ecd4) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 32-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x30), all of which the record accounts for or the listing is the better witness on; the 32-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=32, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x30) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x30), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (32 of 32 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 32-instruction listing lie inside the recovered body span 0x00b515e0..0x00b5163d, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 32-instruction body names 1 indirect transfer(s): 0x00b51615 dispatches slot 0xc through the table word in EAX; the machine parse consumed 32 of 32 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `2dcc9fe5430d1d72c722a6278ede0087af718b56a0a09bcc15f8c770ea69584c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `91be62b01fa80c01378e64a95681731fa6d3b93a0186289dd1872cf8e0fc5e36`
- Pack digest quoted by the briefing: `2dcc9fe5430d1d72c722a6278ede0087af718b56a0a09bcc15f8c770ea69584c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential must confirm that the cGameInputManager pointer stored at +0x34 is really compared by identity and not rewritten behind the cached object's back between calls, which would make the check vacuous.`, `A runtime trace must show whether [this + 0x30] is ever read, and by which code, before the latch can be named.`, `A runtime trace with a concrete receiver is required to resolve the slot +0x0c callee: the call must be sampled with ECX holding the sub-object and the callee address recorded.`, `Every claim here is static. No original-process trace has been captured for 0x00b515e0, and the Cell stage has never been entered in any recorded run.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential must confirm that the cGameInputManager pointer stored at +0x34 is really compared by identity and not rewritten behind the cached object's back between calls, which would make the check vacuous.
- A runtime trace must show whether [this + 0x30] is ever read, and by which code, before the latch can be named.
- A runtime trace with a concrete receiver is required to resolve the slot +0x0c callee: the call must be sampled with ECX holding the sub-object and the callee address recorded.
- Every claim here is static. No original-process trace has been captured for 0x00b515e0, and the Cell stage has never been entered in any recorded run.
- Is the +0x1c sub-object reference itself revalidated? No check on the +0x1c pointer itself was found, so a null there would fault at 0x00b515fe rather than invalidate. Whether the original can be reached in that state is unestablished.
- The SDK candidate set is empty by rejection rather than by absence of reading: GameInputManager.h and cStrategy.h were both read and both conflict with the observed offsets.
- What are the two guard globals semantically? 0x0167ecd0 gates the whole cluster and is written at 0x00b4d8c9 and 0x00b5a4ce, neither of which was analysed. 0x0167ecd4 is the cache. Which of them is 'the subsystem is running' and which is 'the object exists' is inferred from behaviour, not read.
- What class owns the receiver? All nine callers pass the single global 0x0167eae8 through accessor 0x00b3d310, so the receiver is one singleton, but no writer of 0x0167eae8 was located and no Spore-ModAPI header matches the observed field pattern (+0x20, +0x30, +0x60/+0x64 vector, +0x14c8).
- What is the +0x30 latch called and who reads it? Only the two writers (this function and 0x00b5a390) were found. No read of [this + 0x30] was located anywhere in the binary, so the reconstruction cannot say what the flag is FOR, only that it is set on rebuild and cleared on reset.
- What is the 0xd0-byte cached object, and what is the sub-object at its +0x1c? Its allocation (0x00b4d880, size 0xd0, allocator vtable at [0x016e4178] slot +0x10) and its two observed identity fields are established; its class, its remaining 0xcc bytes and the descriptor at 0x01569cdc used to initialise it are not.
- What is the concrete callee of vtable slot +0x0c on [cGameInputManager + 0x24]? The vtable is only reachable through a runtime pointer, so no table address exists in the image and no callee can be named. Return type is bounded to 'pointer whose +0x08 is a comparable dword'.
- Why does 0x00b3d350 get called twice? Either the second call is redundant or the first result is intentionally not reused; the image does not distinguish these.
