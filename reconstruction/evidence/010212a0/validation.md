# Validation 0x010212a0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg01_roots/space_player_data_accessors.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 32-instruction listing names 1 data address(es) (0x16dda8c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 4 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (32 of 32 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 32-instruction listing lie inside the recovered body span 0x010212a0..0x010212eb, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 32-instruction body names 1 indirect transfer(s): 0x010212d8 dispatches slot 0xc0 through the table word in EAX; the machine parse consumed 32 of 32 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f950a1005174188b52abe700fb27ab0672da1c5b9ba29809bd339516192a2dee`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `02716a895360a5f7099a3076e73754ddadcb87c0ff29df5a941b012a06da54b9`
- Pack digest quoted by the briefing: `f950a1005174188b52abe700fb27ab0672da1c5b9ba29809bd339516192a2dee`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No trace establishes when the published global is valid during initialization or teardown.`, `The concrete +0x13c pointee, reference policy, and lifetime remain unresolved.`, `The planet can be replaced or released by separate static lifecycle paths; validity of the two-level read and returned pointee remains runtime-gated.`, `gate-space-player-data-publication`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- +0x13c pointee type
- Is the +0x13c word always a pointer, and what ownership or lifetime applies to it?
- No trace establishes when the published global is valid during initialization or teardown.
- The concrete +0x13c pointee, reference policy, and lifetime remain unresolved.
- The planet can be replaced or released by separate static lifecycle paths; validity of the two-level read and returned pointee remains runtime-gated.
- What concrete type, vtable, and semantic role does active_planet+0x13c represent?
- What runtime ordering guarantees publication of the global, planet, and +0x13c pointee?
- borrowed-pointer lifetime
- gate-space-player-data-publication
- runtime publication
