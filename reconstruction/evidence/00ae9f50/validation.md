# Validation 0x00ae9f50

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b08/ae9f50_session_boot_register.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 169-instruction listing names 2 data address(es) (0x13eb844, 0x13eb90c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 169-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x20, 0x74), all of which the record accounts for or the listing is the better witness on; the 169-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=169, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x20, 0x74) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0x20, 0x64, 0x68, 0x74), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0x64, 0x68) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (169 of 169 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 15 conditional branch target(s) in the complete 169-instruction listing lie inside the recovered body span 0x00ae9f50..0x00aea166, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 169-instruction body names 3 indirect transfer(s): 0x00aea028 dispatches slot 0x14 through the table word in EDX; 0x00aea089 dispatches slot 0x14 through the table word in EDX; 0x00aea0b9 dispatches slot 0x20 through the table word in EDX; the machine parse consumed 169 of 169 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 2 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `0006c655c9e638c8df883f8902001ab4d5ca0f4fa05972cfae7073c91f296299`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `92a901996f3c68a4427b4a2d01695f2308a1f717ed9d0ca261f233aa311a1904`
- Pack digest quoted by the briefing: `0006c655c9e638c8df883f8902001ab4d5ca0f4fa05972cfae7073c91f296299`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists. A differential run must confirm the two AppSystem submissions, the two publishes and the three memory writes actually occur in the observed order in the shipping build.`, `The claim that 0x00421CF0 destroys the stack records must be observed: a run that keeps the record alive after return would refute it.`, `The sentinel-free runtime values behind the six-entry table at 0x015D9650 used by the sibling 0x00C0CE80 are irrelevant here, but the two record ids 0x3AC86B5 and 0x43F2590 can only be resolved by observing what the AppSystem slot +0x14 does with them.`, `Whether receiver+0x74 can be non-(-1) at entry, and what 0x00BA6D80 returns for it, can only be established at runtime.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original-process trace exists. A differential run must confirm the two AppSystem submissions, the two publishes and the three memory writes actually occur in the observed order in the shipping build.
- The claim that 0x00421CF0 destroys the stack records must be observed: a run that keeps the record alive after return would refute it.
- The sentinel-free runtime values behind the six-entry table at 0x015D9650 used by the sibling 0x00C0CE80 are irrelevant here, but the two record ids 0x3AC86B5 and 0x43F2590 can only be resolved by observing what the AppSystem slot +0x14 does with them.
- What are the 17 unidentified callees for? Each is recorded with its address, callsite and ret form, and left as an opaque port in the reconstruction. Notable gaps: 0x00DD1CA0, 0x00DD30D0, 0x00B3D300, 0x00BD9BF0, 0x01021300, 0x00421CF0, 0x00B3D380, 0x00B32250, 0x00A206F0, 0x00435ED0, 0x00AE8EA0, 0x00E14C10, 0x00BA6D80, 0x01021090, 0x00C35240, 0x00AE0930 and 0x01021300.
- What are the four hashed ids 0x3AC86B5, 0x43F2590, 0x4D02E35 and 0x1E5E7302? Each is read as an immediate and none is resolved to a property, key, class or enum name.
- What are the sub-object's +0x18, +0x20, +0x24, +0x28 and +0x30? They are read as keys, values and one byte flag, and nothing names them.
- What do 0x01021300 and 0x01021090 return? Each is a 9-to-105 instruction getter whose result is only compared or forwarded.
- What is the 0x34-byte record layout, and what do 0x004230E0 and 0x0040FDC0 do when invoked with it? Only the six dwords this function writes are modelled; the rest are left untouched exactly as the original leaves them.
- What is the concrete callee behind vtable slot +0x20 on the object 0x00A206F0 returns, and what is its return value used for beyond the 0x1E5E7302 publish?
- What is the owning type of the receiver? No vtable for it was located and this binary has no RTTI. The fields +0x20, +0x64, +0x68 and +0x74 are all that is established.
- Whether receiver+0x74 can be non-(-1) at entry, and what 0x00BA6D80 returns for it, can only be established at runtime.
- Which AppSystem method is vtable slot +0x14? Ghidra's decompiler calls it `Init`, but the observed three-argument shape (id, record, 0) matches no SDK signature this worker checked, so no name is claimed.
- Why is 0x00B3D490 called twice rather than once? The first result is used only for the null test and the second for the receiver. Both fits a non-idempotent getter, but that is not established.
