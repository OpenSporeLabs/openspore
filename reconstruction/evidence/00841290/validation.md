# Validation 0x00841290

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 27-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00841290; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 27-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 2 displacement(s) the source span declares (0x0, 0x3c) and the 0 the complete 27-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x0, 0x3c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (27 of 27 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 27-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 27-instruction body names 1 indirect transfer(s): 0x008412bf dispatches slot 0x3c through the table word in EAX; the machine parse consumed 27 of 27 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 2 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f303c15630ec295d75d1d414c35d3a074df4c5ec143e4e0986d353ae9188d9a9`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `1810162b050b0815a9ddd0e05e1ab4b5c28cefad564c4504a8c334cfd289cff6`
- Pack digest quoted by the briefing: `f303c15630ec295d75d1d414c35d3a074df4c5ec143e4e0986d353ae9188d9a9`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the native return type bool or int, given that only AL is written?
- The briefing carried no ABI projection (evidence.missing_sections: ABI); the whole observed_original_abi block above was derived by hand from the disassembly and must be reviewed against a native build.
- What does the funclet at 0x01217640 do if the +0x3c callee raises an exception, and is the state word at [EBP-4] ever set by a path not present in this body?
- What is the full extent of the vtable beginning at 0x0141c930, and which slots below index 15 belong to base classes?
- What is the single stack argument at [EBP+0x8] (type, producer, and meaning)?
- Which concrete callee does vtable index 15 resolve to for a live FormatParser receiver, and does the base class at 0x0141c930 or the secondary vtable at 0x0141c97c own that slot?
