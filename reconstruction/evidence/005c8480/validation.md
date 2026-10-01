# Validation 0x005c8480

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b00/slot_vector_005c8480.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 133-instruction listing names 2 data address(es) (0x13eb430, 0x13ebb38) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 133-instruction listing names through ECX (0x4) are all within the machine-derived receiver bounds (0x0, 0x4, 0x8), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (133 of 133 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 14 conditional branch target(s) in the complete 133-instruction listing lie inside the recovered body span 0x005c8480..0x005c85cc, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 133-instruction body names 4 indirect transfer(s): 0x005c84b8 dispatches slot 0x4 through the table word in EAX; 0x005c84df dispatches slot 0x4 through the table word in EAX; 0x005c84ef dispatches slot 0x8 through the table word in EAX; 0x005c8582 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 133 of 133 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `18db9dded0e9b27eaa5071257a74198e842498ca3711cd167c51f051dd0b6b01`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `28ecde727320b1d6e33f7f75d374be2e4e2767984a4bfd043e46ef5c831006c3`
- Pack digest quoted by the briefing: `18db9dded0e9b27eaa5071257a74198e842498ca3711cd167c51f051dd0b6b01`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists for 0x005c8480; every claim is static and the Cell stage has never been entered in any recorded run.`, `The capacity*16 allocation size and the null-block overflow path can only be confirmed as intentional or as defects by a run that exercises them.`, `The payload's vtable and therefore the meanings of slots +0x4 and +0x8 require a run with a live editor or palette session.`, `Whether the in-capacity arm is ever reached with an interior position can only be settled by instrumenting the 19 uninspected callsites or by a run; the two inspected ones never reach it.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the container an eastl::vector? The +0x160 field correspondence says a vector of pointers, but the spare slot and the cookie-guarded release are not standard vector behaviour, so the SDK type is a candidate and not an identification.
- Is the in-capacity arm reachable with a position strictly inside the array by any caller? Both inspected callers pass `last` and take the grow arm. If some of the other 19 callers pass an interior position, the argument-bound mismatch between 0x005c1dc0's loop and the hole position becomes live, and the arm's element algebra must be re-derived.
- No original-process trace exists for 0x005c8480; every claim is static and the Cell stage has never been entered in any recorded run.
- The 19 uninspected callers include four in the 0x005c2xxx range that the briefing attributes to ENGINE_IMPLEMENTATION. Their argument shapes, and therefore whether any of them uses the in-capacity arm, are not established.
- The capacity*16 allocation size and the null-block overflow path can only be confirmed as intentional or as defects by a run that exercises them.
- The payload's vtable and therefore the meanings of slots +0x4 and +0x8 require a run with a live editor or palette session.
- What are the two NULL arguments at 0x005c851c and 0x005c851e to 0x00f473a0? The shim reorders six parameters and the underlying 0x009289f0 signature was not read, so their positions are unknown.
- What do vtable slots +0x4 and +0x8 actually do -- reference counting, slot-change notification, or something else? Their call-shape consistency across five bodies is strong but does not name them.
- What is the element type, and hence what class owns the vtable whose slots +0x4 and +0x8 are called? The payload is reached only through the container's slots at runtime, so no vtable can be located statically.
- What is the spare slot at [last] FOR? It is written on the in-capacity arm and never read by this function, and it is not part of the {first,last,capacity} triple. Its consumer, if any, is not in these two callsites.
- Whether the in-capacity arm is ever reached with an interior position can only be settled by instrumenting the 19 uninspected callsites or by a run; the two inspected ones never reach it.
- Why is the allocation size capacity*16 bytes for 4-byte elements? Either the slot granularity is deliberately 4x, or this is a bug. Nothing in the binary or the SDK distinguishes the two.
