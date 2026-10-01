# Validation 0x0060d860

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b07/0060d860_resolve_and_submit_keyed_work.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 59-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 59-instruction listing names through ECX (0x58) are all within the machine-derived receiver bounds (0x58), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (59 of 59 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 6 conditional branch target(s) in the complete 59-instruction listing lie inside the recovered body span 0x0060d860..0x0060d918, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 59-instruction body names 1 indirect transfer(s): 0x0060d913 dispatches slot 0x4 through the table word in EDX; the machine parse consumed 59 of 59 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `8e9fbfa49bf9600b0b9446638fd9e20a11c34e907f2405637c5c2ddc835efec5`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `33d2d4290d5db0bc54d5c1b6b997ec6c8602d7b783e23f2cd29976d0f31c1a1b`
- Pack digest quoted by the briefing: `8e9fbfa49bf9600b0b9446638fd9e20a11c34e907f2405637c5c2ddc835efec5`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists for this address.`, `The domain meaning of the keyed work, and whether the AND-based emptiness test ever misfires on real data, need runtime observation.`, `The virtual release at vtable slot +0x4 can only be resolved with a receiver trace that captures the concrete object's vtable.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is 0x00421f60 (inside 0x00552450) the step that actually produces the object, or is the virtual call at slot 0? Both appear in the decompilation and the distinction was not settled.
- No original-process trace exists for this address.
- The 0x30bdee3 constant copied by 0x00552450 is unexplained.
- The domain meaning of the keyed work, and whether the AND-based emptiness test ever misfires on real data, need runtime observation.
- The receiver passed to 0x0093db80 at 0x0060d8fc is computed as [ESP + 4] after PUSH 0, which static stack arithmetic puts on the PUSH ESI home slot, while 0x0093db80 dereferences receiver + 0x10 and + 0x12 - offsets that only make sense for the key descriptor at frame + 0x0c. Ghidra's decompilation names the receiver local_2. This contradiction is unresolved; the reconstruction passes the descriptor, which is the only reading consistent with the callee.
- The virtual release at vtable slot +0x4 can only be resolved with a receiver trace that captures the concrete object's vtable.
- What do the descriptor's kind and flags words mean beyond their use? The kind whitelist {0,2,3,4,0xf,0x10,0x11,0x14} and the flag bits 0x2, 0x4, 0x20 are observed, but their semantics are not.
- What is the 8-byte key pair at resolved object + 0x18? Nothing in the body or in the callees names it.
- Which class is the receiver, and what is the +0x58 gate? Only one of the 15 callers was disassembled and it supplies a global object as the mode descriptor, not the receiver.
- Which concrete function does vtable slot +0x4 resolve to? The resolved object's vtable address is never taken, so the table was not located and the callee stays unresolved.
