# Validation 0x01021260

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
| GLOBALS | `WARN` | `partial` | the complete 26-instruction listing names 1 data address(es) (0x16dda8c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 3 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (26 of 26 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 26-instruction listing lie inside the recovered body span 0x01021260..0x0102129e, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 26-instruction body names 1 indirect transfer(s): 0x01021298 dispatches slot 0xc0 through the table word in EAX; the machine parse consumed 26 of 26 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c1df758376726904da08ae8c22543e2448480a7fecb029c3810d9c8f425fd0e2`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `f32cf4ebc45fbbdf8363b1e650830364b924b8d96879f265561976a46eb3ce98`
- Pack digest quoted by the briefing: `c1df758376726904da08ae8c22543e2448480a7fecb029c3810d9c8f425fd0e2`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No trace establishes when the published global is valid during initialization or teardown.`, `Separate static writers and cleanup routines can replace or release the +0x04 slot; stale-pointer and lifetime windows remain runtime questions.`, `The concrete active-planet object is not established by this accessor.`, `gate-space-player-data-publication`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No trace establishes when the published global is valid during initialization or teardown.
- Separate static writers and cleanup routines can replace or release the +0x04 slot; stale-pointer and lifetime windows remain runtime questions.
- The concrete active-planet object is not established by this accessor.
- What concrete planet subtype and vtable can the +0x04 word contain?
- What lifetime guarantee accompanies use of the borrowed returned pointer?
- borrowed-pointer lifetime
- concrete planet subtype
- gate-space-player-data-publication
- runtime publication
