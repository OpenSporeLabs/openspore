# Validation 0x007c61a0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-app-camera-active-007c61a0/camera_active_007c61a0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 8-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x007c61a0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 8-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 2 displacement(s) the source span declares (0x80, 0xa8) and the 2 the complete 8-instruction listing names through ECX (0x80, 0xa8) are all within the machine-derived receiver bounds (0x80, 0xa8), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (8 of 8 instruction(s), 0 unparsed) and all 3 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 8-instruction listing lie inside the recovered body span 0x007c61a0..0x007c61b6, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 8-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ffee35b9c46210fb0f2f63cde48861952a1b96571b8ffbca6a3136262fe75a61`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `c922461b3b64b6ee9f4360b73d75efb88c007b4eee6f9b5e9421a093b51f86a1`
- Pack digest quoted by the briefing: `ffee35b9c46210fb0f2f63cde48861952a1b96571b8ffbca6a3136262fe75a61`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Wine/original camera-manager trace is not available; no runtime promotion is claimed.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is vtable slot 15 of 0x014106a4 definitely ICameraManager::GetActiveCamera? The declaration-order + 2 offset is corroborated by five independent slot bodies but is derived from the public SDK header's declaration order, not from a symbol in the binary, so the rename is not promoted here.
- No runtime or differential trace confirms the negative-index null return under real mnActiveIndex values, so the guard is machine-verified but not behaviourally validated.
- The two slots preceding HandleMessage in the 0x014106a4 table (0x007c75d0, 0x007c76e0) are unidentified, so the table's inheritance depth and its two leading slots are not explained by this record.
- The upper byte of the element payload is never inspected, so the recovered expression cannot distinguish a raw App::ICamera* from any other 4-byte handle; the App::ICamera* reading rests on the SDK vector element type.
- Why does the committed SDK address table place SetViewer at 0x007c61a0 and SetActiveCameraByKey at 0x007c61b0, both of which disagree with the machine? The defect is recorded, not repaired; repairing it would touch symbols owned by other queue rows.
- Wine/original camera-manager trace is not available; no runtime promotion is claimed.
