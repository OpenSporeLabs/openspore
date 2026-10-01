# Validation 0x005e0000

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg10_editor_dispatch/editor_command_dispatch.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 295-instruction listing names 1 data address(es) (0x15fd91c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 295-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x10), all of which the record accounts for or the listing is the better witness on; the 295-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=295, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x10) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 6 displacement(s) (0x58, 0x70, 0x9d, 0x9e, 0x108, 0x10c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 6 of those (0x58, 0x70, 0x9d, 0x9e, 0x108, 0x10c) the scan does not attribute to the receiver, and the listing governs there; the listing shows 1 displacement(s) the record does not enumerate (0x10), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (295 of 295 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 35 conditional branch target(s) in the complete 295-instruction listing lie inside the recovered body span 0x005e0000..0x005e0360, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 295-instruction body names 10 indirect transfer(s): 0x005e005a dispatches slot 0xa4 through the table word in EAX; 0x005e0075 dispatches slot 0x1c4 through the table word in EDX; 0x005e00a3 dispatches slot 0x20 through the table word in EAX; 0x005e01c4 dispatches slot 0x18 through the table word in EDX; 0x005e021b dispatches slot 0x14 through the table word in EDX; 0x005e02cb dispatches slot 0x28 through the table word in EAX; 0x005e02e2 dispatches slot 0x28 through the table word in EAX; 0x005e02ee dispatches slot 0x7c through the table word in EAX; 0x005e02fe dispatches slot 0x7c through the table word in EAX; 0x005e0334 dispatches slot 0x4 through the table word in EDX; the machine parse consumed 295 of 295 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 10. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f0f13db34f7f21645cf9d101b4334888130d8d9b6be755654d05094a73353715`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `25925294ee74305ac5a33faeaf91222db14fcf97ed8b3c9109e6582e54f79813`
- Pack digest quoted by the briefing: `f0f13db34f7f21645cf9d101b4334888130d8d9b6be755654d05094a73353715`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-editor-ui-command-dispatch`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- EditorUI+0x10c concrete owner
- What concrete Property* value is supplied to 0x005dd750, and how is that local value populated?
- What concrete types own the generic forwarder, preferences list, selection provider, and dispatch targets?
- What is the semantic identity of outer 0x9a1552d3/0x503517b0 and its two window virtual slots?
- Which concrete UI controls produce the opaque route, preferences, pending, dispatch-pair, and help hashes?
- Why does producer 0x70218642 not pass the target's signed range gate even though the final subtract sequence encodes that value?
- Why is SDK EditorUI+0x10c declared bool while the target loads a 32-bit owner pointer from it?
- gate-editor-ui-command-dispatch
- mode-2 dead branch conflict
- outer route identity
- payload subtypes
- route hash producers
