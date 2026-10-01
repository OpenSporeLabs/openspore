# Validation 0x01021740

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `missing`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 151-instruction listing names 8 data address(es) (0x13ec4b8, 0x1485720, 0x15b7080, 0x16dda8c, 0x16dda90, 0x16dda94, 0x16dda98, 0x16ddb10) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (151 of 151 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 6 conditional branch target(s) in the complete 151-instruction listing lie inside the recovered body span 0x01021740..0x01021951, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 151-instruction body names 9 indirect transfer(s): 0x010217c3 dispatches slot 0x2c through the table word in EDX; 0x010217eb dispatches slot 0x30 through the table word in EDX; 0x0102182a dispatches slot 0xdc through the table word in EDX; 0x010218a8 dispatches slot 0x30 through the table word in EAX; 0x010218b2 dispatches slot 0x2c through the table word in EAX; 0x010218bc dispatches slot 0x10 through the table word in EAX; 0x01021922 dispatches slot 0x20 through the table word in EDX; 0x01021934 dispatches slot 0x144 through the table word in EDX; 0x01021946 dispatches slot 0x28 through the table word in EDX; the machine parse consumed 151 of 151 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 9. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `70e73a8e540fe687ac64131ee210c583c270aa8c9773c8c8ed3c7814d4f8e627`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `dd015c6fbc04b1423e5c3b04372b62ce5c5e22de10c65e30d9a1dd80657fc6d8`
- Pack digest quoted by the briefing: `70e73a8e540fe687ac64131ee210c583c270aa8c9773c8c8ed3c7814d4f8e627`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
