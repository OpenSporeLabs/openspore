# Validation 0x0059b0f0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 153-instruction listing names 3 data address(es) (0x13ec5b4, 0x13f64b0, 0x1465544) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 153-instruction listing names through ECX (0x2c) are all within the machine-derived receiver bounds (0x8, 0xc, 0x20, 0x24, 0x28, 0x2c, 0x30, 0x34, 0x38, 0x3c, 0x40), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (153 of 153 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 6 conditional branch target(s) in the complete 153-instruction listing lie inside the recovered body span 0x0059b0f0..0x0059b2e4, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 153-instruction body names 2 indirect transfer(s): 0x0059b257 dispatches slot 0x28 through the table word in EDX; 0x0059b2c1 dispatches slot 0x24 through the table word in EDX; the machine parse consumed 153 of 153 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1f1ba798b05bfb2fbbec8a6a404e973d769a8d404724331740ecc61f1f4022c7`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d24d0e32381d871ee9faba8e1b527bcd8105fb34f758f4d85706a37c18444014`
- Pack digest quoted by the briefing: `1f1ba798b05bfb2fbbec8a6a404e973d769a8d404724331740ecc61f1f4022c7`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Creature layout beyond 0x0c and the AnimatedCreature at controller+0x08`, `The IShadowWorld raycast argument record at 0x0059b294..0x0059b2c0 (eight stack slots) is not owned by this package`, `The picker world returned by 0x0067dd80 and the meaning of its vtable slot 0x28 return value`, `The picker world returned by 0x0067dd80 and the meaning of its vtable slot 0x28 return value; The IShadowWorld raycast argument record at 0x0059b294..0x0059b2c0 (eight stack slots) is not owned by this package; Whether the hit x really is a ground height; Creature layout beyond 0x0c and the AnimatedCreature at controller+0x08`, `Whether the hit x really is a ground height`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Creature layout beyond 0x0c and the AnimatedCreature at controller+0x08
- The IShadowWorld raycast argument record at 0x0059b294..0x0059b2c0 (eight stack slots) is not owned by this package
- The picker world returned by 0x0067dd80 and the meaning of its vtable slot 0x28 return value
- The picker world returned by 0x0067dd80 and the meaning of its vtable slot 0x28 return value; The IShadowWorld raycast argument record at 0x0059b294..0x0059b2c0 (eight stack slots) is not owned by this package; Whether the hit x really is a ground height; Creature layout beyond 0x0c and the AnimatedCreature at controller+0x08
- Whether the hit x really is a ground height
- concrete runtime owners and values remain unresolved
