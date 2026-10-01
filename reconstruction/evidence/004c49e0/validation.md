# Validation 0x004c49e0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b01/004c49e0_pick.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 25-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 25-instruction listing nevertheless reaches 0 receiver displacement(s) through ECX (none), all of which the record accounts for or the listing is the better witness on; the 25-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=25, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 0 displacement(s) to the receiver as proven (none) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x1c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x1c) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (25 of 25 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 25-instruction listing lie inside the recovered body span 0x004c49e0..0x004c4a20, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 25-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b46bf621a9e87649967bcea8c7f381e4ce91a4d84c8672a825f2e6044ba5ad19`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9e69ebcc504ebc6a5b514ac7a8dc1d2a58e9872022a0a42be99f4e4db081b256`
- Pack digest quoted by the briefing: `b46bf621a9e87649967bcea8c7f381e4ce91a4d84c8672a825f2e6044ba5ad19`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential test would have to record the two slot values at a few of the call sites to confirm which objects are returned in practice.`, `No original-process trace exists for this function, so the claim that both arms return live object pointers is static only.`, `The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made for this Editor-subsystem function.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential test would have to record the two slot values at a few of the call sites to confirm which objects are returned in practice.
- Fifteen of the thirty-three code xrefs were not disassembled window-by-window in this batch; their receiver provenances and result uses come from the briefing's call graph.
- Is the i>=2 -> 0 default a shipped guard or a compiler-generated default for an enum-like selector? No caller in this batch ever passes i >= 2, so the answer is not observable statically.
- No original-process trace exists for this function, so the claim that both arms return live object pointers is static only.
- The 0x00574a20 wrapper forces index 1 regardless of its own incoming argument; whether some caller relies on reaching the +0x18 arm through that wrapper was not established.
- The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made for this Editor-subsystem function.
- What concrete type owns slots +0x18 and +0x1c? Three different receiver provenances (cEditor+0x150, cEditor+0x140, unrelated+0xe0) and no located vtable mean no single owner can be named.
- What do the two slots point at? 0x005ab717 shows the returned value is dereferenced at +0x34 and 0x0058c585 at +0x8, so it is an object pointer, but the object type is unresolved.
- Which writer maintains the two slots? No store to receiver+0x18 or receiver+0x1c was located in this batch, so the invariant that keeps them non-null at the observed call sites is unverified.
