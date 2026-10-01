# Validation 0x008414c0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-argscript-parsefloat-008414c0/parsefloat_008414c0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x008414c0; 34 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x008414c0; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 2-instruction listing names through ECX (0x154) are all within the machine-derived receiver bounds (0x154), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d561bb827865d438869ce11774e07bcca4f11cc6cf3e1e707fd7d282931f2fff`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `6ef0b8e4fb7d33ce23005f507ec5fd53dcb182b0ac45ceb764b2c2c21fc47e97`
- Pack digest quoted by the briefing: `d561bb827865d438869ce11774e07bcca4f11cc6cf3e1e707fd7d282931f2fff`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Runtime validation against the original process is an open capability gate: nothing was attempted and nothing failed.`, `The function is also reachable as a direct call from 34 sites across 30 caller functions, so a differential run can exercise it either through the vtable slot at 0x0141c97c slot 3 or through any of those direct callers.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the two tables 0x0141c930 and 0x0141c97c one vftable seen at two scan offsets, or two related tables? The scan that found them reports 40 and 33 slots respectively; the 18-slot bound claimed here is the thunk argument and the two numbers are not reconciled.
- Does any of the 34 direct call sites pass a receiver of a different concrete type, and are all 30 caller functions reaching it through the same vtable as the slot at 0x0141c97c?
- Runtime validation against the original process is an open capability gate: nothing was attempted and nothing failed.
- The function is also reachable as a direct call from 34 sites across 30 caller functions, so a differential run can exercise it either through the vtable slot at 0x0141c97c slot 3 or through any of those direct callers.
- What class owns this slot? SporeApp.exe has no MSVC RTTI, the table's other slots carry FUN_ placeholders and four SDK-imported labels, and the exported decompilation is an artefact, so no owner is named here.
- What is the 32-bit word at receiver+0x154 semantically? The body fixes its offset, width and read-only access and nothing else; 851 other [reg+0x154] sites exist in the binary, so the displacement alone identifies no member.
- Why do four of the five inspected call sites consume the returned word as an address (move to ECX and call, or null-test then dereference at [EAX+0x1fd4] at 0x00bbc34d)? That is suggestive of a pointer, but no caller and no native rebuild fixes it here and no type is claimed.
