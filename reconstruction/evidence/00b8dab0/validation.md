# Validation 0x00b8dab0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00b8dab0-field194-getter/scalar_field_194_00b8dab0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00b8dab0; 78 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00b8dab0; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x194) and the 1 the complete 2-instruction listing names through ECX (0x194) are all within the machine-derived receiver bounds (0x194), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'std::uint32_t' and the machine return state is WIDTH_4_IN_EAX: the complete 2-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `0e6a2ae3a962f5ec94dcd985fd99c04de44c622e22d7bb5259e50f474024a184`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e6621026cdf2eee4c2352af1c794b42e8f9dab459d111e59efaffba143f88cf5`
- Pack digest quoted by the briefing: `0e6a2ae3a962f5ec94dcd985fd99c04de44c622e22d7bb5259e50f474024a184`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the sibling words of this receiver related - +0x184 (which HAS a setter at 0x00b8da80 and a transform getter at 0x00b8da70), +0x188 (LEA only), +0x190 (written at 0x00b8da48), +0x198 (LEA getter, setter at 0x00b8dae6) and +0x19c (written at 0x00b8daef) - a single structure whose fields mean different things, or independent slots? Adjacency in the accessor block is not a layout.
- Does the receiver need an AddRef, and by whom? The body has no room for a reference call, so ownership is undetermined.
- What does the word at receiver+0x194 mean? Four callers show ordinal/threshold behaviour (compared against 2 and 5, reduced with JLE) but no SDK import, committed note or sampled caller names the concept.
- Which class is the receiver? Every sampled caller reaches it through FUN_010212a0, i.e. `dword [esi+0x13c]` of another object, and nothing names the resulting class.
- Who writes the word at +0x194, and when? No access to [ECX+0x194] exists in the 0x400-byte window 0x00b8d900..0x00b8dd00, but indirect or bulk publication outside that window is unexcluded.
