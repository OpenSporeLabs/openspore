# Validation 0x00c471c0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-pilot-core-b01/c471c0_mission_settle.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 42-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 42-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x0, 0x130), all of which the record accounts for or the listing is the better witness on; the 42-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=42, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x0, 0x130) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x0, 0x130), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (42 of 42 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 42-instruction listing lie inside the recovered body span 0x00c471c0..0x00c47231, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 42-instruction body names 4 indirect transfer(s): 0x00c471cc dispatches slot 0xf8 through the table word in EAX; 0x00c471dc dispatches slot 0xfc through the table word in EAX; 0x00c47203 dispatches slot 0x19c through the table word in EDX; 0x00c47224 dispatches slot 0x198 through the table word in EDX; the machine parse consumed 42 of 42 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `e0c8b1d2a08dd836a547ecbf95a73b61e8d00fe6a939c899a314218d80c8515c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `f03f6985b10e3eedc34410abdc6770cb652e8a2862801ecf61d7c8676cc19027`
- Pack digest quoted by the briefing: `e0c8b1d2a08dd836a547ecbf95a73b61e8d00fe6a939c899a314218d80c8515c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime trace would be needed to see which of the two terminal slots is actually taken for a real mission transition, and to observe the seven counters the flush touches.`, `Naming the four overrides requires a receiver whose vtable base is known at run time.`, `No original-process trace exists for 0x00c471c0; every claim is static.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime trace would be needed to see which of the two terminal slots is actually taken for a real mission transition, and to observe the seven counters the flush touches.
- Is the flush a no-op when the two virtuals did nothing? Both terminal slots have their results discarded, so if they are pure state changes with no dirty flag, the flush would be redundant - unresolvable statically.
- Naming the four overrides requires a receiver whose vtable base is known at run time.
- No original-process trace exists for 0x00c471c0; every claim is static.
- What are the seven counters the terminal flush walks, and what does 0x01021080 guard? The flush body is known; the domain is not. The flush is skipped entirely when 0x01021080 returns zero, so on some runs this function's last action would be nothing at all.
- What do the four dispatched virtuals do? Slot +0xf8 and +0xfc are boolean predicates, +0x19c is a no-argument action and +0x198 takes that one boolean. cMission.h places HasBeenFulfilled, HasFailed, func19Ch and func198h at exactly those offsets with exactly those arities, but no vtable was found to confirm it and two of the four header names are placeholders.
- What does the bit-1-of-+0x130 test mean in game terms? cMission.h names bit 1 kMissionFlagHideStarName, which would make the +0x19c exit a 'stop hiding the star name' action, but the SDK flag comments are themselves reverse-engineered and partly speculative.
- Which class owns this function? It is non-virtual and appears in no vtable, so cMission stays a candidate. The callers are SetState overrides of several different derived mission types, so the receiver's concrete class varies per call site.
- Why does 0x00c47240 reach this function through a different path (after writing +0x100) while the SetState family reaches it right after 0x00c472e0? Both are consistent with 'last step of a refresh', but the trigger conditions differ and the reason is not established.
