# Validation 0x00985ce0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00985ce0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 2-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `WARN` | `partial` | return type differs or is semantically renamed; review required |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `49bcdc5435689b5de6c33728d16ae78bc18d65c4ef6ac7a12505d5d27409213e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3707be2478257c53250dd915406b0844af6e35c9b2a7e5f9c286e551f76aace4`
- Pack digest quoted by the briefing: `49bcdc5435689b5de6c33728d16ae78bc18d65c4ef6ac7a12505d5d27409213e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation or indirect-caller trace was captured.`, `The constant 0x4f063bb3 is not decoded; whether it is a real alignment value, a sentinel, or a placeholder is unresolved.`, `The imported name SetAlignmentHorizontal is a candidate label only; the body performs no alignment write.`, `gate-utfwin-stub-constant-decoding`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Decoded meaning of the 0x4f063bb3 constant
- No original-process invocation or indirect-caller trace was captured.
- The constant 0x4f063bb3 is not decoded; whether it is a real alignment value, a sentinel, or a placeholder is unresolved.
- The imported name SetAlignmentHorizontal is a candidate label only; the body performs no alignment write.
- Whether callers ignore the EAX result
- Why the stub is present in place of the imported setter behavior
- gate-utfwin-stub-constant-decoding
