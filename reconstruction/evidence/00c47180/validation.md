# Validation 0x00c47180

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b08/c47180_manager_slot_replace.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 17-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (17 of 17 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 17-instruction listing lie inside the recovered body span 0x00c47180..0x00c471b0, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 17-instruction body names 1 indirect transfer(s): 0x00c4719b dispatches slot 0xc0 through the table word in EAX; the machine parse consumed 17 of 17 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `42f908493213f4daa48ce3b4806271707a80f5a93da42a61f63a6fd3126966a7`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9d5d7e9637670cd697822ea20c9bd2118c4974d0eded27f08212a3ef7708fbe6`
- Pack digest quoted by the briefing: `42f908493213f4daa48ce3b4806271707a80f5a93da42a61f63a6fd3126966a7`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists. A differential run must confirm the occupant's vtable slot +0xC0 does not re-read the receiver's +0x1E8 slot, which is the invariant the clear-before-detach ordering depends on.`, `The concrete receiver type and the concrete occupant type can only be fixed by observing a vtable pointer in a running process.`, `Whether the dead argument has any effect requires a run that varies it at a callsite and observes an unchanged result.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does 0x00BB59B0 actually use the argument this function pushes? Its first parameter is the manager, so the dead word becomes its `key`, but the reconstruction does not assert what the key does, because 0x00bb59b0's contract was not fully established for that parameter.
- Is the write to +0x1E8 a release, a clear-for-replace, or a reset of an owning smart pointer? The body does no reference counting of its own.
- No original-process trace exists. A differential run must confirm the occupant's vtable slot +0xC0 does not re-read the receiver's +0x1E8 slot, which is the invariant the clear-before-detach ordering depends on.
- The concrete receiver type and the concrete occupant type can only be fixed by observing a vtable pointer in a running process.
- Twenty of the twenty-two recorded callsites were not individually disassembled.
- What are 0x00baf130, 0x00bbaa60, 0x00bb5930 and 0x00b8de30? They were located inside 0x00bb59b0's body and their ret forms read, but their bodies were not reconstructed.
- What class implements the occupant interface with slots +0xBC and +0xC0, and what are those two methods called? The detach/attach reading is inferred from call symmetry only.
- What is the object at 0x0167EAE4? 0x00B3D2A0 reads the pointer but this worker never read the dword or found a vtable for it.
- What is the owning type of the receiver? No vtable for it was located and the binary has no RTTI. All that is established is the single field at +0x1E8.
- Whether the dead argument has any effect requires a run that varies it at a callsite and observes an unchanged result.
- Why is the argument dead at the call to 0x00B3D2A0 yet live at 0x00BB59B0? Either the original signature carried a parameter the build ignores, or the compiler reused the slot. Both fit the bytes; neither is established.
