# Validation 0x006c0550

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_prop_resource_safe_wave9/prop_resource_safe_wave9.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 30-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x006c0550; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 30-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 2 displacement(s) the source span declares (0x4, 0x28) and the 0 the complete 30-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x-4, 0x4, 0x28), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (30 of 30 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 30-instruction listing lie inside the recovered body span 0x006c0550..0x006c0590, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 30-instruction body names 3 indirect transfer(s): 0x006c0567 dispatches slot 0x10 through the table word in EAX; 0x006c057e dispatches slot 0x38 through the table word in EAX; 0x006c0590 dispatches slot 0x38 through the table word in EDX; the machine parse consumed 30 of 30 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 2 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `WARN` | `partial` | return type differs or is semantically renamed; review required |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f46ca0f5ef2ec74535027e03ebb5b5a978c098511c6768556b70121f5a6d474c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `f34b2800c0da16574f28cba671834aacf27653cdb06179fe216e55c02cea06ab`
- Pack digest quoted by the briefing: `f46ca0f5ef2ec74535027e03ebb5b5a978c098511c6768556b70121f5a6d474c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation or indirect-caller trace was captured.`, `The concrete stream vtable owners behind slots +0x10 and +0x38 are unresolved.`, `The high three bytes of the 32-bit write result are dropped at runtime; only the low byte is architecturally observable here.`, `The runtime meaning of the gate word at record+0x1c (owner file-access flag) is unresolved.`, `gate-record-write-stream-vtable-and-owner-access-gate`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Concrete stream vtable owners and their slot semantics
- No original-process invocation or indirect-caller trace was captured.
- Partial-write and error behavior of the write slot
- Producer and lifetime of the gate word at record+0x1c
- The concrete stream vtable owners behind slots +0x10 and +0x38 are unresolved.
- The high three bytes of the 32-bit write result are dropped at runtime; only the low byte is architecturally observable here.
- The runtime meaning of the gate word at record+0x1c (owner file-access flag) is unresolved.
- Whether a full 32-bit status is expected by any caller despite the byte return
- gate-record-write-stream-vtable-and-owner-access-gate
