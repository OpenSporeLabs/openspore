# Validation 0x00c0c0e0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00c0c0e0-linked-flag-probe/linked_flag_probe_00c0c0e0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 9-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00c0c0e0; 61 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the complete 9-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00c0c0e0; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares 2 displacement(s) (0x388, 0xe84) and every one of them is a displacement the complete 9-instruction listing shows: 1 attributed to the receiver ECX as proven (0xe84); 1 more (0x388) are shown by the listing under a base that is not the receiver -- 0x388 under EAX -- so the body does use those displacements, on an object this check cannot identify; that is a limit of the attribution here and not a disagreement with the receiver, and no receiver contradiction is claimed for them; the 9-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=9, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0xe84) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0xe84, 0x120c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x120c) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (9 of 9 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 9-instruction listing lie inside the recovered body span 0x00c0c0e0..0x00c0c0fb, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 9-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'std::uint32_t' and the machine return state is WIDTH_4_IN_EAX: the complete 9-instruction listing writes EAX at a determinate 4-byte width before all 2 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c66aa3531259351334162a3fe5fe079a5acf3b00f05705be1ec15950673aa8ea`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `7bd93107adc890e9903b56204c43beed5a80a69243a342c383a1fe3d05f136f1`
- Pack digest quoted by the briefing: `c66aa3531259351334162a3fe5fe079a5acf3b00f05705be1ec15950673aa8ea`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the 0x00c0c0e8 and 0x00c0c0f1 branches semantically two different questions (link absent vs flag clear) that happen to share one exit, or one question tested twice? The machine merges them into one block and gives no way to tell.
- No runtime validation exists for this target: zero differential traces, so the whole reconstruction is static-only and the runtime dimension reports GATED.
- What class is the ECX receiver? The evidence pack carries no class association, no namespace and no SDK name for FUN_00c0c0e0, so none is claimed and the receiver stays opaque.
- What do the 61 call sites ask this predicate? The high fan-in makes an IsX-shaped reading attractive, but what is being queried is not recoverable from the body and is not claimed.
- What does the 32-bit word at 0xe84 point at? The machine only tests it against zero and uses it as an address, so it is modelled as an opaque base; the pointee's identity is unrecoverable from these 28 bytes.
- Why does the derived receiver record enumerate 0x120c when the listing shows only 0xe84 (through ECX) and 0x388 (through EAX)? 0x120c is not an operand of this body. It is either a base offset from a different derivation pass or evidence that the record's bounds conflate the two objects. It was deliberately not modelled.
- Why is the subsystem tag 'Simulator' when no type, string or vtable in the pack corroborates it? The tag comes from the index projection and this package found no evidence for or against it.
