# Validation 0x00c982a0

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 201-instruction listing name the same 13 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 16 outgoing call edge row(s) over 13 distinct address(es) for 0x00c982a0; the source span names 12 of them and no others |
| GLOBALS | `WARN` | `partial` | 9 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field bytes, vtable and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it; the 1 displacement(s) in that same span are grounded within the machine-derived receiver bounds (0x0, 0x4, 0x34, 0x230, 0x260, 0x264, 0x268, 0x26c, 0x290, 0x294, 0x298, 0x29c, 0x2a8, 0x2ac, 0x2b0, 0x2bc, 0x2c0, 0x2c4, 0x2c8, 0x2cc, 0x2d0, 0x2d4, 0x2d8, 0x300, 0x301, 0x304, 0x308, 0x30c, 0x310, 0x314, 0x318, 0x31c, 0x328, 0x330, 0x334, 0x338, 0x33c, 0x340, 0x344, 0x348, 0x354, 0x358, 0x35c, 0x368, 0x36c, 0x370, 0x374, 0x380, 0x384, 0x388, 0x398, 0x39c, 0x3a0, 0x3a4, 0x3a8, 0x3ac, 0x418, 0x41c, 0x420, 0x42c, 0x4e8, 0x4ec, 0x4f0, 0x4f4, 0x4f8, 0x4fc, 0x550, 0x554, 0x555, 0x556, 0x557, 0x1868, 0x186c, 0x1870, 0x1874, 0x1878, 0x1879, 0x1880, 0x1884, 0x1888, 0x188c, 0x1890, 0x1891, 0x1898, 0x189c, 0x18a0, 0x18a4, 0x18a8, 0x18a9, 0x18b0, 0x18b4, 0x18b8, 0x18bc, 0x18c0, 0x18c1, 0x18c8, 0x19c4, 0x19c8, 0x19cc, 0x19d0, 0x19d4, 0x19d8), so it is the name alone that is uncorroborated |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 12 source constant(s) are absent from the machine listing: 0x0, 0x18c4, 0x18d0, 0x18d4, 0x18d8, 0x1908, 0x190c, 0x1918, 0x191c, 0x40000000, 0x41200000, 0x4e4 |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 201-instruction listing lie inside the recovered body span 0x00c982a0..0x00c986af, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 201-instruction body names 1 indirect transfer(s): 0x00c98664 dispatches slot 0x4 through the table word in EDX; the machine parse consumed 201 of 201 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 6 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x4, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `8ecd72a18ca092cdd177ed1da5e73e97d1fbc89eda76fe77e0c81146280b31ca`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `0607ae36befb644b3bf539db358d3dab9c87955036cbc468c03c412570c4dfb1`
- Pack digest quoted by the briefing: `8ecd72a18ca092cdd177ed1da5e73e97d1fbc89eda76fe77e0c81146280b31ca`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-tribe-constructor-00c982a0`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No city, building, population, or persistence owner is inferred from this cTribe constructor.
- The concrete owner and runtime lifetime of the optional object at +0x368 remain unresolved.
- The delegated initializer layouts at +0x120, +0x1f4, +0x20c, +0x230, +0x270, +0x3b4, +0x510, +0x530, and +0x558 remain opaque.
- The vector element layout managed by 0x004548d0 at +0x1904 remains opaque beyond the observed pointer words and 14 reserve count.
- gate-tribe-constructor-00c982a0
- runtime validation not run
