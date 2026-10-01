# Validation 0x00bd8210

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 12-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 12-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x0), all of which the record accounts for or the listing is the better witness on; the 12-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=12, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x0, 0x58), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x58) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (12 of 12 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 12-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 12-instruction body names 1 indirect transfer(s): 0x00bd821c dispatches slot 0x58 through the table word in EAX; the machine parse consumed 12 of 12 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c4db125e3afea67a570123d9725d1bf5846db2ef625f82231d50ab34530ac69c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `75f1d47736e9fb26ee5bb9aec93b7f6128b6ba9b6ffafb45986d20bbc80b4ab0`
- Pack digest quoted by the briefing: `c4db125e3afea67a570123d9725d1bf5846db2ef625f82231d50ab34530ac69c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime check must confirm whether the table at receiver+0x4c is rebuilt (dirty byte +0x78) at the moments 0x00bd8210 runs, since that is the only side effect on the path.`, `No original-process trace has been captured for 0x00bd8210, so the claim that equal directions always quantise to equal indices is static-only.`, `The 12-byte out buffer written by the slot +0x58 callee must be observed in a live process before its role can be named.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime check must confirm whether the table at receiver+0x4c is rebuilt (dirty byte +0x78) at the moments 0x00bd8210 runs, since that is the only side effect on the path.
- Eleven of the fourteen observed call sites in region 0x00bf0000 were not disassembled, so their use of the return value is unverified.
- Is 0x00b87dc0 a full rebuild of the table or an incremental update? Only the call site was read.
- Is the object at 0x0167eaf8 really a cGameInputManager? The SDK import names 0x00b3d350 as Simulator::cGameInputManager::Get, but the ModAPI header for that class declares neither the +0x4c table nor the +0x78 dirty byte, so the name may be right while the layout is a different class reached through the same accessor.
- No original-process trace exists for any function in this batch. Every statement here is static.
- No original-process trace has been captured for 0x00bd8210, so the claim that equal directions always quantise to equal indices is static-only.
- The 12-byte out buffer written by the slot +0x58 callee must be observed in a live process before its role can be named.
- The binary carries no MSVC RTTI, so no class identity can be read from typeinfo; class claims in this record rest only on observed vtable data and SDK header text.
- What are the 10 bits at 0x00b8875a? They index a 6*128*128*2-byte table, so they are a packed face/u/v code or a precomputed lighting, navigation or animation index. No writer of that table was located.
- What class owns 0x00bd8210? Its slot +0x4c is used at 0x00d043cf in the same caller but matches no ModAPI declaration, and no vtable for it was located.
- What does the 12-byte out buffer at 0x00bd8218 receive, and is it the same memory as the three floats that 0x00b88590 reads? The slot's return value and its out parameter are separate and the body uses only the return value.
