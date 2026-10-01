# Validation 0x00b267d0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 6-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00b267d0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 6-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 6-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (6 of 6 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 6-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 6-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `WARN` | `partial` | return type differs or is semantically renamed; review required |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `8a0c2707fa85ab782f91b01f6f347e0ea781102d163f92f43b79168c33800742`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `1ca631de06a1d9ead8b243cfdc23dad7c175d472286050faf8bc35b57af827dc`
- Pack digest quoted by the briefing: `8a0c2707fa85ab782f91b01f6f347e0ea781102d163f92f43b79168c33800742`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation or indirect-caller trace was captured.`, `The 0x037e958b selector is not decoded; its runtime meaning is unresolved.`, `The imported two-argument signature does not match the one-argument body; callers of the true entry point are unverified.`, `gate-utfwin-tree-node-selector-decoding`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Decoded meaning of the 0x037e958b selector
- No original-process invocation or indirect-caller trace was captured.
- The 0x037e958b selector is not decoded; its runtime meaning is unresolved.
- The imported two-argument signature does not match the one-argument body; callers of the true entry point are unverified.
- Whether returning the receiver pointer signals ownership transfer
- Which vtable slot or call site reaches this body
- Why the live body takes one stack word while the import declares two
- gate-utfwin-tree-node-selector-decoding
