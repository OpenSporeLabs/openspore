# Validation 0x00e5b790

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_camera_wave7/camera_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `FAIL` | `partial` | the source-vs-xref rule: 1 address-named source call(s) have no call edge in the xref export: 0x00e823a0; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 10 outgoing call edge row(s) over 9 distinct address(es) for 0x00e5b790; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `WARN` | `partial` | the complete 155-instruction listing names 10 data address(es) (0x013eb8b0, 0x01485378, 0x015a7c40, 0x015a7c44, 0x015a7c48, 0x016b3c04, 0x016b3c0c, 0x016b3c28, 0x016b3c2c, 0x016b3c30); the data-reference artifact is read whole and records 14 reference row(s) out of this body covering every address under review, with access mode(s) read=13, other=1 |
| FIELDS/OFFSETS | `WARN` | `partial` | 30 source field-offset declaration(s) (field avatar_index_411c, field cell_game, field cell_ui, field flag_24) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (155 of 155 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 11 conditional branch target(s) in the complete 155-instruction listing lie inside the recovered body span 0x00e5b790..0x00e5ba01, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 155-instruction body names 1 indirect transfer(s): 0x00e5b841 dispatches slot 0x58 through the table word in EDX; the machine parse consumed 155 of 155 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x58, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 4 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `769190db12e3300be241884097ea8910e2cca3664a9b49460162518c9e1d68bf`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5756dca33251fcd1934810497210044647a53b0dad2366003c5cce27393eb3cc`
- Pack digest quoted by the briefing: `769190db12e3300be241884097ea8910e2cca3664a9b49460162518c9e1d68bf`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Original Cell-mode Wine trace and live movement-plane values are not available; no runtime promotion is claimed.`, `runtime observation required`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Original Cell-mode Wine trace and live movement-plane values are not available; no runtime promotion is claimed.
- concrete runtime owners and values remain unresolved
- runtime observation required
