# Validation 0x00b225d0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg11_h3_helper_wave2/helper_wave2.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 47-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 47-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0x80, 0x84, 0x88), all of which the record accounts for or the listing is the better witness on; the 47-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=47, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x80, 0x84, 0x88) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x84, 0x88), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0x80), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (47 of 47 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 47-instruction listing lie inside the recovered body span 0x00b225d0..0x00b22644, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 47-instruction body names 3 indirect transfer(s): 0x00b225e9 dispatches slot 0x0 through the table word in EAX; 0x00b22611 dispatches slot 0x0 through the table word in EAX; 0x00b2262f dispatches slot 0x4 through the table word in EAX; the machine parse consumed 47 of 47 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `da6c95466c29c31e472cd94b53abe13ffeae36ec9644cffc2da70fce4a563ba2`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ff9b9ee6e1f3271206045acccfebcbb5f1bdff648ca0f82012ffe9426b4758ba`
- Pack digest quoted by the briefing: `da6c95466c29c31e472cd94b53abe13ffeae36ec9644cffc2da70fce4a563ba2`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-noun-manager-logical-destroy-00b225d0`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- C++ inheritance or vector class identity
- allocator implementation behind 0x00f473a0 or 0x00f47380
- behavior inside 0x00b20d30 or 0x00b201a0
- concrete noun or manager C++ type
- gate-noun-manager-logical-destroy-00b225d0
- runtime pointer validity beyond the modeled no-guard fault boundaries
- runtime validation not run
