# Validation 0x00576c50

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Dispose.c`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 402-instruction listing names 5 data address(es) (0x013f5660, 0x013f5670, 0x013f5688, 0x0150cfa0, 0x015eebec); the data-reference artifact is read whole and records 6 reference row(s) out of this body covering every address under review, with access mode(s) read=1, write=1, other=4 |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 402-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0x0, 0x20, 0x2b0), all of which the record accounts for or the listing is the better witness on; the 402-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=402, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x0, 0x20, 0x2b0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 24 displacement(s) (0x0, 0x20, 0x84, 0x88, 0x8c, 0x90, 0x94, 0x98, 0x9c, 0xa0, 0xa8, 0xac, 0x15c, 0x2b0, 0x3cc, 0x3d0, 0x3d4, 0x3d8, 0x3dc, 0x5c0, 0x5c4, 0x5c8, 0x5cc, 0x5d0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 21 of those (0x84, 0x88, 0x8c, 0x90, 0x94, 0x98, 0x9c, 0xa0, 0xa8, 0xac, 0x15c, 0x3cc, 0x3d0, 0x3d4, 0x3d8, 0x3dc, 0x5c0, 0x5c4, 0x5c8, 0x5cc, 0x5d0) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (402 of 402 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 39 conditional branch target(s) in the complete 402-instruction listing lie inside the recovered body span 0x00576c50..0x00577122, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 402-instruction body names 32 indirect transfer(s): 0x00576c64 dispatches slot 0x1c through the table word in EAX; 0x00576c78 dispatches slot 0x1c through the table word in EDX; 0x00576c8b dispatches slot 0x1c through the table word in EDX; 0x00576c9e dispatches slot 0x1c through the table word in EDX; 0x00576cf9 dispatches slot 0x2c through the table word in EAX; 0x00576d0d dispatches slot 0x2c through the table word in EAX; 0x00576d21 dispatches slot 0x2c through the table word in EAX; 0x00576d68 dispatches slot 0x0 through the table word in EAX; 0x00576da4 dispatches slot 0x0 through the table word in EAX; 0x00576de0 dispatches slot 0x170 through the table word in EDX; 0x00576e20 dispatches slot 0x170 through the table word in EDX; 0x00576e60 dispatches slot 0x170 through the table word in EDX; 0x00576e7b dispatches slot 0x4 through the table word in EDX; 0x00576e92 dispatches slot 0x4 through the table word in EDX; 0x00576ea9 dispatches slot 0x4 through the table word in EDX; 0x00576ebc dispatches slot 0x18 through the table word in EDX; 0x00576ecf dispatches slot 0x18 through the table word in EDX; 0x00576ee2 dispatches slot 0x18 through the table word in EDX; 0x00576ef9 dispatches slot 0x4 through the table word in EDX; 0x00576f0c dispatches slot 0x50 through the table word in EDX; 0x00576f2b dispatches slot 0x8 through the table word in EDX; 0x00576f64 dispatches slot 0x0 through the table word in EDX; 0x00577068 dispatches slot 0x38 through the table word in EDX; 0x0057707b dispatches slot 0x40 through the table word in EDX; 0x0057708b dispatches slot 0x40 through the table word in EDX; 0x00577094 dispatches slot 0x58 through the table word in EDX; 0x005770c4 dispatches slot 0x34 through the table word in EDX; 0x005770d3 dispatches slot 0x18 through the table word in EAX; 0x005770e5 dispatches slot 0x38 through the table word in EDX; 0x005770f0 dispatches slot 0x24 through the table word in EDX; 0x005770ff dispatches slot 0x8 through the table word in EDX; 0x0057711b dispatches slot 0x8 through the table word in EDX; the machine parse consumed 402 of 402 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 32. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `2d78ec642798159502ce7b7d22f8846f206e7640f36ec8e073b6db9ebb62f7c8`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8c517d0e2ddf06b579f520fac678d7ce983b2863302498e768267e341f195aa7`
- Pack digest quoted by the briefing: `2d78ec642798159502ce7b7d22f8846f206e7640f36ec8e073b6db9ebb62f7c8`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
