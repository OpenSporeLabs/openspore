# Validation 0x0043cad0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b04/0043cad0_rigblock_handle_sweep.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 251-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 251-instruction listing nevertheless reaches 0 receiver displacement(s) through ECX (none), all of which the record accounts for or the listing is the better witness on; the 251-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=251, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 0 displacement(s) to the receiver as proven (none) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0x28, 0x160, 0x1b0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 3 of those (0x28, 0x160, 0x1b0) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (251 of 251 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 21 conditional branch target(s) in the complete 251-instruction listing lie inside the recovered body span 0x0043cad0..0x0043cdf5, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 251-instruction body names 3 indirect transfer(s): 0x0043cbed dispatches slot 0x30 through the table word in EAX; 0x0043cc47 dispatches slot 0x30 through the table word in EDX; 0x0043cdd2 dispatches slot 0x30 through the table word in EAX; the machine parse consumed 251 of 251 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c92c1faf73be2d596755115b2ead908cacf4f7a1d945776b080db6689418dab9`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `4953d9a0684bf8a3b16bdb349d62de9cc4c4f97e5dc0909018d8189b4e3c5d7a`
- Pack digest quoted by the briefing: `c92c1faf73be2d596755115b2ead908cacf4f7a1d945776b080db6689418dab9`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace has been captured. A differential run must show which handle classes are actually reached through slot +0x30 and what state 3 does to them.`, `The relationship between this sweep and the globally gated 0x0043ce40 can only be settled by observing both in one run.`, `The three attribute bits and the per-handle flag bytes are only ever read in this build; whether any runtime path sets them, and in which order, needs a trace.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is 0x0043ce40 really the 'complementary' pass, or an independently scheduled one? It is called only when the +0x4C override is clear, and it consults a global that this function does not, so the two are coupled but not obviously a matched pair.
- No original-process trace has been captured. A differential run must show which handle classes are actually reached through slot +0x30 and what state 3 does to them.
- The relationship between this sweep and the globally gated 0x0043ce40 can only be settled by observing both in one run.
- The three attribute bits and the per-handle flag bytes are only ever read in this build; whether any runtime path sets them, and in which order, needs a trace.
- The two call sites at 0x005737c7 and 0x005757bd, and the remaining two the ledger lists, were not disassembled, so the frequency and context of this sweep are unknown.
- What are the three attribute bits 25, 24 and 11 called? The SDK's EditorRigblock lists mBooleanAttributes as an unnamed bitset with no per-bit documentation.
- What do the per-handle flag bytes at +0x92, +0x5D and +0x1D4 mean? They behave as a veto but no SDK field matches, and they sit at three different offsets in three different handle classes.
- What does slot +0x30 on a handle actually do? No concrete receiver was ever available, so the effect of pushing state 3 with the flag set is unknown. This is the single largest gap in the reconstruction.
- What is 0xD0A55625? It is neither an address nor a plausible field offset and is forwarded to 0x00435ed0, whose behaviour was not analysed. It may be a profiler scope id, an event id or a hash.
- Why are the +0x4C and +0x4D override bytes on the model sub-object rather than on the part itself? Their role is established only from how they are used here.
