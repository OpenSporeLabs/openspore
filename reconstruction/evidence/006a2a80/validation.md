# Validation 0x006a2a80

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_property_clear_wave13/006a2a80_property_list_clear.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 36-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x006a2a80; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 36-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 3 displacement(s) the source span declares (0x18, 0x1c, 0x34) and the 0 the complete 36-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x18, 0x1c, 0x34), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (36 of 36 instruction(s), 0 unparsed) and all 6 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 36-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 36-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `20a297619332bbfefe69949cb6741de471c7c548c99e92ba32d02df506fd6c3f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `745fb13d104460ec8f4ac19c643cd791726a2fe1905d283b59172afb10f9414b`
- Pack digest quoted by the briefing: `20a297619332bbfefe69949cb6741de471c7c548c99e92ba32d02df506fd6c3f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation and no indirect-caller trace were captured, so reachability through vtable 0x01408820 is a runtime gate.`, `The meaning of the element type and of the flag words the release and copy helpers test cannot be recovered from this body; only the traversal stride is claimed.`, `The real body of 0x00612b20 is not reproduced here. It has now been read, and at this call site the pushed range is degenerate (the end cursor is pushed twice), so the port's contract is exactly the observed degenerate return of the third word, the begin cursor. The general non-empty movement path stays unmodelled.`, `The real body of 0x00685a30 is not reproduced here. It has now been read, and the port reproduces its unsigned 0x18-stride traversal but not the per-entry `TEST byte ptr [ESI + 0x14],0x4` release of 0x0093db80, which is out of scope for this record.`, `The semantic identity of the counter word at receiver+0x34 is unknown. Only the unconditional increment is claimed; its initial value and its readers are not observable here.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Identity and initial value of the counter word at receiver+0x34 and its readers elsewhere in the binary.
- No original-process invocation and no indirect-caller trace were captured, so reachability through vtable 0x01408820 is a runtime gate.
- The concrete layout of the 0x18 entry. What is observable from the two callees is a dword at +0x00 and a sub-object at +0x04 spanning to the 0x18 stride boundary, carrying a flag word at its +0x10 and a count word at its +0x12. That is a callee-derived shape, not a claim about 0x006a2a80, and the candidate still declares the element type incomplete.
- The concrete layout of the receiver between offsets 0x00 and 0x17 and between 0x20 and 0x33, which this body never touches.
- The general (non-degenerate) arm of 0x00612b20, now read but not ported: per element it writes the dword at +0x00 inline and thiscall-calls 0x00542b80 with ECX = out_element+0x4 and the source's +0x4 pushed, so each 0x18 entry is a four-dword block plus two flag words copied with flag-dependent side effects rather than a flat memcpy. Only the degenerate return observed at this call site is claimed here.
- The identity of the receiver words at 0x18, 0x1c and 0x34. The machine-derived receiver record is bounds_only and enumerates displacements, not members, so the candidate deliberately names none. A struct layout naming these words requires a source outside this body (the SDK header, or a writer elsewhere in the binary that documents them).
- The meaning of the element type and of the flag words the release and copy helpers test cannot be recovered from this body; only the traversal stride is claimed.
- The real body of 0x00612b20 is not reproduced here. It has now been read, and at this call site the pushed range is degenerate (the end cursor is pushed twice), so the port's contract is exactly the observed degenerate return of the third word, the begin cursor. The general non-empty movement path stays unmodelled.
- The real body of 0x00685a30 is not reproduced here. It has now been read, and the port reproduces its unsigned 0x18-stride traversal but not the per-entry `TEST byte ptr [ESI + 0x14],0x4` release of 0x0093db80, which is out of scope for this record.
- The semantic identity of the counter word at receiver+0x34 is unknown. Only the unconditional increment is claimed; its initial value and its readers are not observable here.
- What 0x0093db80, the release target 0x00685a30 selects with `TEST byte ptr [ESI + 0x14],0x4` on each entry, actually does. Its body tests `byte ptr [ESI + 0x10],0x4` on the address it is handed, and when that is set it makes an indirect call through the data word at 0x0154eb48 with six pushed words. That indirect target is outside this record's scope and is not claimed.
- Whether the byte span at receiver+0x18..0x1c is always an exact multiple of the 0x18 stride. The rewind only lands on the begin cursor when it is; for a ragged span the end cursor is rewound to the nearest lower stride boundary.
- Whether the shared vtable 0x01408820 dispatches this body at a fixed slot, and which callers reach it. The single xref is the vtable word at 0x01408868; no direct caller exists in the xref export, so reachability is dispatch mediated and stays a runtime gate.
