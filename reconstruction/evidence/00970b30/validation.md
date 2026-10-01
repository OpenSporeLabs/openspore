# Validation 0x00970b30

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00970b30-slot-1e8-getter/slot_1e8_00970b30.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00970b30; 142 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00970b30; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 2-instruction listing names through ECX (0x1e8) are all within the machine-derived receiver bounds (0x1e8), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f2b7edebf57e7ae385e4af838c8d16376d4593888cf9c900183c8bc54fc1b11e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `2b8e3ed66f10da12c9bc262a4938022f27eacc7a7ceb4898bbf094c45710c289`
- Pack digest quoted by the briefing: `f2b7edebf57e7ae385e4af838c8d16376d4593888cf9c900183c8bc54fc1b11e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Do the 69 distinct callers share one receiver class, or is this slot reachable from more than one type? The fan-in is high and uniform but no witness names the receiver's origin.
- Is 0x00970b10 the only writer of the slot, and is the adjacent setter the only such accessor pair? The setter is adjacent in the image, which is an adjacency and not an enumeration of writers elsewhere in the binary.
- What does the pointer at receiver+0x1e8 point to, and what is at its displacement 0x13c? Three callers load there and one SDK-independent note names nothing; the pointee's type is UNKNOWN.
- Which class is the receiver? Nothing in the pack names it; the record has no namespace, no SDK association and no type. The 142 callers all supply their own ECX and the pack does not say from where.
- Why does the adjacent setter also write [ECX+0x9c] with the constant 1 in the same call? That coupling is observed but its meaning is not recoverable from this target's evidence.
