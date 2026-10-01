# Validation 0x0102df20

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
| GLOBALS | `WARN` | `partial` | the complete 1375-instruction listing names 6 data address(es) (0x14995e8, 0x149963c, 0x1499660, 0x15b751c, 0x16de7e4, 0x16decac) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 8 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (1375 of 1375 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 116 conditional branch target(s) in the complete 1375-instruction listing lie inside the recovered body span 0x0102df20..0x0102f0b8, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 1375-instruction body names 18 indirect transfer(s): 0x0102df43 dispatches slot 0x20 through the table word in EDX; 0x0102df62 dispatches slot 0x38 through the table word in EDX; 0x0102df75 dispatches slot 0x40 through the table word in EDX; 0x0102df84 dispatches slot 0x40 through the table word in EDX; 0x0102df8d dispatches slot 0x58 through the table word in EDX; 0x0102e064 is INDIRECT_NON_VTABLE; 0x0102e187 dispatches slot 0x60 through the table word in EAX; 0x0102e38b dispatches slot 0xa4 through the table word in EDX; 0x0102e4b9 dispatches slot 0x2c through the table word in EDX; 0x0102e520 dispatches slot 0x2c through the table word in EAX; 0x0102e589 dispatches slot 0x2c through the table word in EDX; 0x0102e5b2 dispatches slot 0x30 through the table word in EDX; 0x0102e5f9 dispatches slot 0x70 through the table word in EAX; 0x0102e609 dispatches slot 0x74 through the table word in EAX; 0x0102e668 dispatches slot 0x14 through the table word in EDX; 0x0102e763 dispatches slot 0xa4 through the table word in EAX; 0x0102eee1 dispatches slot 0x38 through the table word in EAX; 0x0102eefc dispatches slot 0x4 through the table word in EAX; the machine parse consumed 1375 of 1375 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 18, so the dispatch is visible in the machine listing but is not proven: 1 of the 18 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x0102e064), so the dispatch's identity is not established: the target is the memory operand [EAX*0x4 + 0x102f0bc], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 4 of 8 static checks evaluated, 2 passed, 4 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `2d9fcee7e5119f93521cf9e3d6962481c69c2e2562df624b52944b7167ddd47c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `37bb8f7b91d416217404a533ee8e8074e75c8abd74102aeb6983dc59159fa9d4`
- Pack digest quoted by the briefing: `2d9fcee7e5119f93521cf9e3d6962481c69c2e2562df624b52944b7167ddd47c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
