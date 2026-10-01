# Validation 0x0059cb10

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 45-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 45-instruction listing nevertheless reaches 4 receiver displacement(s) through ECX (0x8, 0xc, 0x38, 0x3c), all of which the record accounts for or the listing is the better witness on; the 45-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=45, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 4 displacement(s) to the receiver as proven (0x8, 0xc, 0x38, 0x3c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x38, 0x3c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 2 displacement(s) the record does not enumerate (0x8, 0xc), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (45 of 45 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 45-instruction listing lie inside the recovered body span 0x0059cb10..0x0059cb7a, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 45-instruction body names 1 indirect transfer(s): 0x0059cb6d dispatches slot 0x4 through the table word in EAX; the machine parse consumed 45 of 45 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `14353a02e653f2cf6b74fb93e92b34bf2c92466a9c9c5323caf3fc6d59730894`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `4a2b97a233623d56cc18748842eb7db83bdd87343ea79cb8f887cd5d696c98ae`
- Pack digest quoted by the briefing: `14353a02e653f2cf6b74fb93e92b34bf2c92466a9c9c5323caf3fc6d59730894`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Interaction with the 0x38 and 0x3c gates at runtime`, `The concrete creature vtable at controller+0x08 and the meaning of slot +4`, `The concrete creature vtable at controller+0x08 and the meaning of slot +4; Whether controller+0x1c is a clip index, hash or resource id, and who reads it; Interaction with the 0x38 and 0x3c gates at runtime; The concrete implementation behind the 0x007cd950 publication port`, `The concrete implementation behind the 0x007cd950 publication port`, `Whether controller+0x1c is a clip index, hash or resource id, and who reads it`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Interaction with the 0x38 and 0x3c gates at runtime
- The concrete creature vtable at controller+0x08 and the meaning of slot +4
- The concrete creature vtable at controller+0x08 and the meaning of slot +4; Whether controller+0x1c is a clip index, hash or resource id, and who reads it; Interaction with the 0x38 and 0x3c gates at runtime; The concrete implementation behind the 0x007cd950 publication port
- The concrete implementation behind the 0x007cd950 publication port
- Whether controller+0x1c is a clip index, hash or resource id, and who reads it
- concrete runtime owners and values remain unresolved
