# Validation 0x005a2010

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 14-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x005a2010; 3 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `PASS` | `complete` | the complete 14-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 6 displacement(s) the source span declares (0x74, 0x78, 0x7c, 0x80, 0x84, 0x88) and the 6 the complete 14-instruction listing names through ECX (0x74, 0x78, 0x7c, 0x80, 0x84, 0x88) are all within the machine-derived receiver bounds (0x74, 0x78, 0x7c, 0x80, 0x84, 0x88), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (14 of 14 instruction(s), 0 unparsed) and all 6 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 14-instruction listing lie inside the recovered body span 0x005a2010..0x005a2040, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 14-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'void': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 7 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `77ccab6a0fae46120df0227dd11c03fdd29d341de61b18c2229d31b1dd4c6714`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5e4b88f6fc8d2e6aff6a86ced22022063a18ad867c45f51a3cd8e06134ece8b6`
- Pack digest quoted by the briefing: `77ccab6a0fae46120df0227dd11c03fdd29d341de61b18c2229d31b1dd4c6714`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A full-word gate test would be observably wrong; the low-byte read is fixed by the CMP at the entry.`, `No Wine differential run against the original binary was performed.`, `Receiver class identity unresolved; no vtable label exists for this receiver in the live database.`, `The semantic role of the +0x74 mirrored row versus the +0x80 row is not established by static evidence.`, `gate-editor-row-publish-receiver-identity-and-row-semantics`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A full-word gate test would be observably wrong; the low-byte read is fixed by the CMP at the entry.
- No Wine differential run against the original binary was performed.
- Receiver class identity unresolved; no vtable label exists for this receiver in the live database.
- The semantic role of the +0x74 mirrored row versus the +0x80 row is not established by static evidence.
- What the also_previous formal means above its low byte, since only the low byte is read
- Whether any consumer reads +0x74 at all
- Whether the +0x74 mirrored row is a previous-row cache or a second live row
- Which class the row publisher receiver belongs to; no vtable label exists for it
- gate-editor-row-publish-receiver-identity-and-row-semantics
