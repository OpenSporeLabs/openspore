# Validation 0x00d018d0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00d018d0-erase-range-shift-down/erase_range_shift_down_00d018d0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 31-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00d018d0; 43 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the complete 31-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00d018d0; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 31-instruction listing names through ECX (0x4) are all within the machine-derived receiver bounds (0x4), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (31 of 31 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 31-instruction listing lie inside the recovered body span 0x00d018d0..0x00d0190f, so the branch graph is closed inside it; the source span declares while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 31-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'OpaqueElement*': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 31-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 7 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `88f645fb86cf31781b7afbe75d928e33f13a0d3dd349fdf9fbea2f226d65d0c5`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `b113f30fdedd2fa70f51cc14c06dee0fcc5f2ea93923475e39c323653be8fc46`
- Pack digest quoted by the briefing: `88f645fb86cf31781b7afbe75d928e33f13a0d3dd349fdf9fbea2f226d65d0c5`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- argument names first/last describe what the body does with the two stack words (observable) and the order is corroborated by 16 call sites, but the original author's names are not observable
- no runtime evidence: the model test is a static model of the listing, not a differential test against the game
- only 1 of the 16 call sites (0x007f2600) was individually decompiled; the other 15 rest on the xref export rather than on separate body reads
- the counter-intuitive trip count: erasing one element copies every element after it, so the cost is O(remaining) rather than O(1). It follows from the machine and is asserted by the model test, but it is the claim most worth a second witness
- the element type: only its 8-byte width is fixed, by three machine facts plus one call site
- which member the receiver word at 0x4 is: `tail` is this package's own name, inferred from the loop bound and the ADD that shrinks it, and a bounds_only record cannot corroborate a name
