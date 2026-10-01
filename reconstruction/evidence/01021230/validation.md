# Validation 0x01021230

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
| GLOBALS | `WARN` | `partial` | the complete 3-instruction listing names 1 data address(es) (0x16dda8c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 3 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (3 of 3 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 3-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 3-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `5027f103e4bd679152b8253ec25165658614101c35cb23af29b042872ddd9ba6`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `0d18a7cbd006555649438e8c2dcb2b27fc5ebdce40e67ba2d9a4933e02039fd5`
- Pack digest quoted by the briefing: `5027f103e4bd679152b8253ec25165658614101c35cb23af29b042872ddd9ba6`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No trace establishes when the published global is valid during initialization or teardown.`, `Separate static writers and cleanup routines can replace or release the +0x08 slot; use-after-clear or stale-pointer windows remain runtime questions.`, `The concrete returned object and its lifetime are not established by this accessor.`, `gate-space-player-data-publication`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No trace establishes when the published global is valid during initialization or teardown.
- Separate static writers and cleanup routines can replace or release the +0x08 slot; use-after-clear or stale-pointer windows remain runtime questions.
- The concrete returned object and its lifetime are not established by this accessor.
- What concrete star subtype and vtable can the +0x08 word contain?
- What lifetime guarantee accompanies use of the borrowed returned pointer?
- borrowed-pointer lifetime
- concrete star subtype
- gate-space-player-data-publication
- runtime publication
