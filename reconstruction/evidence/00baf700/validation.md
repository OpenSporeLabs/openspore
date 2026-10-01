# Validation 0x00baf700

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b06/baf700_interned_object_get_or_create.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 52-instruction listing names 2 data address(es) (0x156c61c, 0x156c620) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (52 of 52 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 52-instruction listing lie inside the recovered body span 0x00baf700..0x00baf78a, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 52-instruction body names 2 indirect transfer(s): 0x00baf763 dispatches slot 0x4 through the table word in EAX; 0x00baf773 dispatches slot 0x2c through the table word in EAX; the machine parse consumed 52 of 52 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `e96e497e24eb045efe28654cf90bbd01bd73d2a78b3f07bb4312a3418506f635`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e49b60c6be0ad6825fda692a9afb6fd845b30bc6ddab694c699a011c5637453c`
- Pack digest quoted by the briefing: `e96e497e24eb045efe28654cf90bbd01bd73d2a78b3f07bb4312a3418506f635`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.`, `The create path cannot execute before the factory host at 0x015FD8A8 is installed, and that host is zero in the shipping image. A differential test must first establish the host is live, then observe the first miss and the exact object the factory stores.`, `The low-byte keying collision risk in 0x00dd85c0 can only be settled by enumerating the runtime hashed names 0x00c30cc0 can produce and checking for shared top 24 bits.`, `The re-fetch after the factory call is a correctness claim about tree rebalancing. Confirming it needs a case where the factory inserts enough nodes to force a rebalance, which cannot be provoked statically.`, `The zero-before-release ordering is a re-entrancy and observability claim. Confirming it needs a concurrent reader of 0x0156C61C during the release, which only a runtime harness can arrange.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does the low-byte-of-the-value keying in 0x00dd85c0 ever cause two distinct names to collide? The insertion path takes the key's top 24 bits and the queried value's low byte, so collision depends on runtime hash values. No static evidence establishes whether the hashed names produced by 0x00c30cc0 ever share their top 24 bits, and if they do the table would return the wrong object.
- Is 0x00c30e80's receiver the caller's stack argument or the preserved ECX? The body loads the stack argument into ECX at 0x00baf701 and then calls 0x00c30e80, so the callee receives the STACK ARGUMENT as its this pointer. If the original source intended a different receiver, the compiled code disagrees with the intent, and static evidence cannot say which is which.
- No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.
- The briefing's canonical ledger recorded caller_count 14 and callee_count 4; the live xref query confirms 15 call sites in 14 caller functions (0x00c784c0 contributing two) and 5 distinct callees (0x00c30e80, 0x00e5c780, 0x0067de30, 0x00dd85c0, and the two vtable slots counted as one entry in the briefing's static call graph because they are indirect). The difference is a counting convention, not a contradiction; the two vtable dispatches are the briefing's omission.
- The create path cannot execute before the factory host at 0x015FD8A8 is installed, and that host is zero in the shipping image. A differential test must first establish the host is live, then observe the first miss and the exact object the factory stores.
- The low-byte keying collision risk in 0x00dd85c0 can only be settled by enumerating the runtime hashed names 0x00c30cc0 can produce and checking for shared top 24 bits.
- The re-fetch after the factory call is a correctness claim about tree rebalancing. Confirming it needs a case where the factory inserts enough nodes to force a rebalance, which cannot be provoked statically.
- The zero-before-release ordering is a re-entrancy and observability claim. Confirming it needs a concurrent reader of 0x0156C61C during the release, which only a runtime harness can arrange.
- What class owns the container at 0x0156C61C? Its layout (+0x00 unused, +0x04 and +0x08 both pointing at the header node 0x0156C620, +0x0C a rightmost node) is consistent with an MSVC red-black tree but was not confirmed to be a conforming std::map, and no SDK container declaration was matched.
- What class owns the factory host at 0x015FD8A8, and what are the concrete functions behind its vtable slots +0x04 and +0x2C? Neither was resolved; the host is installed at runtime and no vtable could be located statically. This is the principal bound on the record.
- What is the incoming ECX for? It is pushed and popped without ever being read, so the function is either a static member with one argument or a __fastcall function whose first argument is unused. Caller 0x00c784c0 does set ECX from 0x00b3d2a0 before both calls, which is consistent with a receiver, but nothing in the body uses it. The reconstruction does not consume it.
- What is the interned object's type? The result is passed straight to 0x0040cf10 alongside hashed constants and a float pointer, which is consistent with a RelationshipEvents configuration instance, but no vtable for the object was located.
