# Validation 0x00587270

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
| GLOBALS | `WARN` | `partial` | the complete 621-instruction listing names 3 data address(es) (0x13eb430, 0x13eb8b0, 0x15e505c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 621-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x31c), all of which the record accounts for or the listing is the better witness on; the 621-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=621, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x31c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 24 displacement(s) (0x3c, 0x68, 0x7c, 0x98, 0xa4, 0xa8, 0xd4, 0xe4, 0xe8, 0xe9, 0x150, 0x154, 0x1cc, 0x20e, 0x278, 0x27c, 0x2b5, 0x358, 0x360, 0x364, 0x385, 0x38c, 0x472, 0x4d8), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 24 of those (0x3c, 0x68, 0x7c, 0x98, 0xa4, 0xa8, 0xd4, 0xe4, 0xe8, 0xe9, 0x150, 0x154, 0x1cc, 0x20e, 0x278, 0x27c, 0x2b5, 0x358, 0x360, 0x364, 0x385, 0x38c, 0x472, 0x4d8) the scan does not attribute to the receiver, and the listing governs there; the listing shows 1 displacement(s) the record does not enumerate (0x31c), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (621 of 621 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 92 conditional branch target(s) in the complete 621-instruction listing lie inside the recovered body span 0x00587270..0x00587a15, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 621-instruction body names 8 indirect transfer(s): 0x005874c0 dispatches slot 0x8 through the table word in EDX; 0x005876a2 dispatches slot 0x50 through the table word in EDX; 0x0058771a dispatches slot 0x1c through the table word in EDX; 0x00587758 dispatches slot 0x50 through the table word in EDX; 0x0058790e dispatches slot 0x4 through the table word in EAX; 0x00587948 dispatches slot 0x14 through the table word in EDX; 0x005879aa dispatches slot 0x4 through the table word in EDX; 0x005879dc dispatches slot 0x8 through the table word in EDX; the machine parse consumed 621 of 621 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 8. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `4ddcd5b9682ff17c083266bb47526db5474491ed7104d8111c931e8352f23468`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ce7324b2165fdc3639eeb7c7a5fe3c66d878da84c249d5cea10fef73d1e3d582`
- Pack digest quoted by the briefing: `4ddcd5b9682ff17c083266bb47526db5474491ed7104d8111c931e8352f23468`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The original owner type and any derived RTTI identity must not be inferred from the current SDK name.
- The second argument is a 0/1 flag, but its semantic role is not established.
