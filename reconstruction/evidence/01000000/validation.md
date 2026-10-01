# Validation 0x01000000

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
| GLOBALS | `WARN` | `partial` | the complete 318-instruction listing names 1 data address(es) (0x1495158) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 318-instruction listing nevertheless reaches 0 receiver displacement(s) through ECX (none), all of which the record accounts for or the listing is the better witness on; the 318-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=318, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 0 displacement(s) to the receiver as proven (none) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x40), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x40) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (318 of 318 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 22 conditional branch target(s) in the complete 318-instruction listing lie inside the recovered body span 0x01000000..0x010003e1, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 318-instruction body names 13 indirect transfer(s): 0x01000086 dispatches slot 0x64 through the table word in EDX; 0x01000095 dispatches slot 0x60 through the table word in EDX; 0x010000ef is FUNCTION_POINTER; 0x01000171 dispatches slot 0x4 through the table word in EDX; 0x01000186 dispatches slot 0x2c through the table word in EDX; 0x010001a4 dispatches slot 0x2c through the table word in EAX; 0x010001d1 dispatches slot 0x30 through the table word in EDX; 0x0100020c dispatches slot 0x34 through the table word in EDX; 0x01000225 dispatches slot 0x14 through the table word in EDX; 0x01000232 dispatches slot 0x8 through the table word in EAX; 0x0100027e dispatches slot 0x80 through the table word in EDX; 0x0100028d dispatches slot 0x8 through the table word in EDX; 0x0100029c dispatches slot 0x4 through the table word in EDX; the machine parse consumed 318 of 318 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 13, so the dispatch is visible in the machine listing but is not proven: 1 of the 13 indirect transfer(s) classify as FUNCTION_POINTER (0x010000ef), so the dispatch's identity is not established: EAX is loaded from [EDX + 0x8c], but EDX is defined by a preceding CALL, so it holds that callee's return value earlier in the listing, so the word it names is not shown to be a table word |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 5 of 8 static checks evaluated, 3 passed, 3 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `816887f145b76199a85c33319df9679cce7a3683f7e7e03f055ebc677c6d8fec`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `51b4fef517650ca1b50d8f3a53d6663fb80b344e79e4f43698e8b05454b64d8f`
- Pack digest quoted by the briefing: `816887f145b76199a85c33319df9679cce7a3683f7e7e03f055ebc677c6d8fec`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
