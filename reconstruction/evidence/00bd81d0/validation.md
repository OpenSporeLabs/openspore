# Validation 0x00bd81d0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00bd81d0-receiver-slot-getter/simulator_receiver_slot_00bd81d0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00bd81d0; 71 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00bd81d0; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 2-instruction listing names through ECX (0x540) are all within the machine-derived receiver bounds (0x540), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'uint32_t' and the machine return state is WIDTH_4_IN_EAX: the complete 2-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `972825a9c6602f55949b80e2912850177708f7d35ef3aef1b063c8b400723055`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `392376e2f3412415892fd5f4915b2723155efdd9a963809038956d38e4b56eec`
- Pack digest quoted by the briefing: `972825a9c6602f55949b80e2912850177708f7d35ef3aef1b063c8b400723055`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Do any of the 24 unsampled caller functions dereference the returned word? If one does, a pointer reading also fits and contradiction C-RETTYPE would reopen.
- Is there a setter counterpart to this getter elsewhere in the image, as 0x00bd81e0 pairs with 0x00bd81f0 for +0x2f0? Not searched; this package is bounded to the target and its immediate block.
- The derived ABI record's convention resolution (__thiscall over __fastcall) is not observable from this function alone: for a body reading ECX with zero stack arguments the two encodings are identical.
- What are the enumerators of the 0/1/2/-1 domain? The observed comparands establish an enum-like shape and nothing more; the -1 at 0x00bd7160 hints at a signed domain but no name, count or ordering is evidenced.
- What class owns offset 0x540, and what is the field called? No SDK import, namespace or committed research note names either; Ghidra's SDK import left the entry FUN_00bd81d0.
- Who writes +0x540, and when relative to the 31 distinct caller functions that read it? No writer was located for this offset (sibling writers in the block cover +0x33c and +0x2f0 only); this is an unlocated writer, not an established absence.
