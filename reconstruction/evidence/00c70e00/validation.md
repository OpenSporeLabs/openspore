# Validation 0x00c70e00

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00c70e00-field13c/field13c_00c70e00.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | the derived ABI record abstained (ABI_UNKNOWN): no reason recorded |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 6-instruction listing name the same 1 direct transfer target(s), including a target reached only by a jump; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00c70e00; 41 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 1 outgoing call edge row(s) and 1 distinct callee(s) the export records; 1 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00b8dab0; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 1 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 6-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00c70e00; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x13c) and the 1 the complete 6-instruction listing names through ECX (0x13c) are all within the machine-derived receiver bounds (0x13c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (6 of 6 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 6-instruction listing lie inside the recovered body span 0x00c70e00..0x00c70e14, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 6-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'SlotWord': the return register EAX is written at a width this module cannot bound on at least one of the 2 reachable return(s) in the complete 6-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `319b654b6f1c0db4695c2de871ef38a5c8df48ba5e83e3e085c3a0b36660189e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `01483ac37de01e3118900396f5007a3e9c8dd6093e7780b13a29401434a97abd`
- Pack digest quoted by the briefing: `319b654b6f1c0db4695c2de871ef38a5c8df48ba5e83e3e085c3a0b36660189e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Do the two paths' return values denote the same quantity? Nothing in the evidence settles it, and the two arms share one signature.
- Is the constant 1 a boolean, an enum member, a sentinel, or a count? The four sampled callers only order the result against 0x4 and 0x5, which is consistent with every one of those readings.
- Is the receiver argument a `this` or an ordinary first parameter? The bytes cannot say (see not_claimed), and the answer is what would settle __thiscall against __fastcall.
- What class is the TAIL receiver, and does it need an AddRef? The tail target's body is seven bytes with no room for a reference call, so ownership is undetermined; the promoted sibling pkg-00b8dab0-field194-getter carries the same open question for the same word.
- What does the word at receiver+0x13c name, and what class does the receiver belong to? Nothing in the pack names either; the receiver record is bounds_only and the types/globals/vtables categories are all MISSING.
- Why does the derived ABI record abstain with verdict ABI_UNKNOWN? Its own inference T2 gives the reason as the tail transfer - 'the function can reach a caller by transferring out of the listing, so the path that actually returns was never observed' - at confidence UNKNOWN. That observation is incomplete for this body: 0x00c70e0f/0x00c70e14 IS a returning path in the same listing, and the transfer's own target is a two-instruction body whose MOV EAX/RET was read live. See the tooling note in the report.
