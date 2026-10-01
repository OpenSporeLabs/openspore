# Validation 0x00d2e380

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_creature_state/creature_state.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 36-instruction listing names 4 data address(es) (0x1582e38, 0x1582e3c, 0x1582e40, 0x1582e44) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 5 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (36 of 36 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 36-instruction listing lie inside the recovered body span 0x00d2e380..0x00d2e3fd, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 36-instruction body names 2 indirect transfer(s): 0x00d2e3a8 dispatches slot 0xd8 through the table word in EDX; 0x00d2e3af is INDIRECT_NON_VTABLE; the machine parse consumed 36 of 36 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2, so the dispatch is visible in the machine listing but is not proven: 1 of the 2 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x00d2e3af), so the dispatch's identity is not established: the target is the memory operand [EAX*0x4 + 0xd2e400], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 2 passed, 4 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `aaf6cb642045b7646cd3292f1ce6befb6438c671093d92ab0ad3985364b58c80`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `65c30d99bb9f4550bac06d749436d36ef3a6636ac260dd8893a46e7241a8cc13`
- Pack digest quoted by the briefing: `aaf6cb642045b7646cd3292f1ce6befb6438c671093d92ab0ad3985364b58c80`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `creature_brain_level_dispatch_observation`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original-process -1 lookup result or customized threshold values have been observed.
- The concrete object type and implementation behind vtable slot +0xd8 are unresolved.
- The owner and later writers of the four mutable threshold globals are not established by this target.
- concrete vtable owner
- creature_brain_level_dispatch_observation
- root and object availability
- runtime threshold values
- virtual slot implementation
