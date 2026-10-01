# Validation 0x0062f540

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b05/playmode_backgrounds_0062f540.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 38-instruction listing names 2 data address(es) (0x13fe404, 0x15f7cf4) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 38-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0x34, 0x38, 0x3c), all of which the record accounts for or the listing is the better witness on; the 38-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=38, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x34, 0x38, 0x3c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0x34, 0x38, 0x3c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (38 of 38 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 38-instruction listing lie inside the recovered body span 0x0062f540..0x0062f5b8, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 38-instruction body names 1 indirect transfer(s): 0x0062f5a8 dispatches slot 0x80 through the table word in ESI; the machine parse consumed 38 of 38 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `68f92195b740e1b4df79ddebc62b4bc08e0148df145cda9daf6c06158674ab2c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ec36bce0cb5716d9b03c2e3cdb0fdcead1a574288508ba7c1d9334023b4ff568`
- Pack digest quoted by the briefing: `68f92195b740e1b4df79ddebc62b4bc08e0148df145cda9daf6c06158674ab2c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime trace is required to confirm the runtime value of the global at 0x015F7CF4, the runtime resolution of localization id 0x7518573e, and that the window with control id 0x47ED688 actually exists in the PlayMode layout at the moment this function runs.`, `No original-process trace has been captured for 0x0062f540. Every claim in this record is static.`, `The Cell stage has never been entered in any recorded run, so the Editor/PlayMode path has no runtime oracle at all.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime trace is required to confirm the runtime value of the global at 0x015F7CF4, the runtime resolution of localization id 0x7518573e, and that the window with control id 0x47ED688 actually exists in the PlayMode layout at the moment this function runs.
- Is 0x0062f540 ever reached with the global at 0x015F7CF4 still null while a window is found? Statically impossible to exclude; a differential trace would be needed to confirm the invariant is upheld by the callers rather than by luck.
- No original-process trace has been captured for 0x0062f540. Every claim in this record is static.
- The Cell stage has never been entered in any recorded run, so the Editor/PlayMode path has no runtime oracle at all.
- What does 0x00634dc0 do when its slot +0xf0 fallback runs? The creation path is observed as a call with (id, 1) but its result and side effects were not analysed.
- What does vtable slot +0x80 concretely do? The argument is a resolved text pointer and the SDK declares SetCaption at exactly +0x80, but the implementing class was not located, so the call target is unidentified.
- What is the concrete class of the receiver? The SDK field layout at +0x34/+0x38/+0x3C matches Editors::PlayModeBackgrounds and the region matches, but the SDK's declared address for that class's UpdatePageNumbers matches neither 0x62F520 nor 0x62F570 to this entry, so the class assignment stays a candidate.
- What is the method name? No vtable entry, no imported symbol and no SDK address exist for 0x0062f540, so UpdatePageNumbers is unconfirmed.
- What is the type and owner of the object at 0x015F7CF4? Fifty-one references show sibling writers at +0x18, +0x1c, +0x20, +0x24, +0x28, +0x2c and +0x34, which is consistent with a shared localized-string substitution table, but no type declaration was found.
- What text does localization id 0x7518573e resolve to at run time? It is a runtime id with no static image backing and the same id drives both the anim and the background page-count labels, so its exact format string is unknown.
