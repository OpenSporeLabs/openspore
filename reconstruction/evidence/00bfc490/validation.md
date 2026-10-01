# Validation 0x00bfc490

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-pilot-core-b01/bfc490_combatant_ratio.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 8-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 8-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x0, 0x38), all of which the record accounts for or the listing is the better witness on; the 8-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=8, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x0, 0x38) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x0, 0x38), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (8 of 8 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 8-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 8-instruction body names 1 indirect transfer(s): 0x00bfc498 dispatches slot 0x58 through the table word in EAX; the machine parse consumed 8 of 8 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `81920f55c0245202b74be2475b1e07884ec73aed5e10e3dacf6dfe6c909f0692`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e4c57c2b130549ab27f90ec15e56a85ce24364609e03007a8ec810f3c2d1f75b`
- Pack digest quoted by the briefing: `81920f55c0245202b74be2475b1e07884ec73aed5e10e3dacf6dfe6c909f0692`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime trace would be needed to see which override of slot +0x58 is reached for a real creature, to observe the actual return values of the ratio in play, and to check whether the divisor is ever zero.`, `No original-process trace exists for 0x00bfc490; every claim is static.`, `The runtime values of the six threshold and scale globals cannot be recovered statically because they are zero in the file image.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime trace would be needed to see which override of slot +0x58 is reached for a real creature, to observe the actual return values of the ratio in play, and to check whether the divisor is ever zero.
- Can the divisor be zero, and what happens then? Nothing in the body guards it, so the result would be an infinity or a NaN silently returned to the caller. Whether any override can return zero is not established.
- Is the receiver exactly cCombatant or a derived type whose base sits at +0x5a8? cCreatureBase.h:92 documents the cCombatant base at 0x5a8, but only cCreatureBase-derived callers were inspected, and 0x00c0bb90's enclosing object was not identified.
- No original-process trace exists for 0x00bfc490; every claim is static.
- The runtime values of the six threshold and scale globals cannot be recovered statically because they are zero in the file image.
- What are the runtime thresholds at 0x01687a00, 0x01687a0c, 0x01687a10 and 0x01687a14, and the scales at 0x0158129c and 0x015812a0? All are zero or unread in the file image, so the numeric domain of the ratio cannot be bounded further.
- What does slot +0x58 return in each concrete subclass? cCombatant.h says GetMaxHitPoints 'might return hit points or max hit points', so the divisor may be the maximum or the current value for some types, which changes the ratio's meaning per receiver.
- What is the SDK name of this method? cCombatant.h declares only inline GetWeaponRange and SetHealthPoints as non-virtual members, so the name in this record is a reconstruction label.
- Which concrete types call this? 0x00d2b950, 0x00e934f0, 0x00e93f50, 0x00f0efa0 and 0x01072680 are classified ENGINE_IMPLEMENTATION and sit outside the creature region, so the function is reached from more than one hierarchy and the receiver type is genuinely receiver-dependent.
