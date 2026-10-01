# Validation 0x00e5cac0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_w2_00e5cac0/ret_eax_from_ecx_00e5cac0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00e5cac0; 3 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 2-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'Receiver*' and the machine return state is WIDTH_4_IN_EAX: the complete 2-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `3121f03d4614eeb125cd7fe348584b2a8b246e88b3e7ac9406addd744b61f65d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `77950f605ec4f72ad5f1c11f405dd627ebed6df59a64714c2e4a8d67f42c596f`
- Pack digest quoted by the briefing: `3121f03d4614eeb125cd7fe348584b2a8b246e88b3e7ac9406addd744b61f65d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the receiver the head of its object or an interior sub-object? The two unadjusted call sites and the one +0xc-adjusted site reach the same body at different displacements, and the body neither adds nor subtracts anything of its own, so the base relationships between them are not recoverable from here.
- What does the popped 4-byte stack slot mean? It is established that the callee pops it and never reads it; whether it is a parameter at all, and if so of what type and meaning, is not established by this listing and is not guessed.
- What is the register_class of the returned value? The record classifies it aggregate_unknown (RT2) and the envelope as unclassified_in_EAX. The listing shows the value is the incoming receiver verbatim, so it is a pointer-shaped 4 bytes, but the machine's own classification is recorded as it stands and is not upgraded here.
- Which class, if any, does this address belong to? R1-VFT establishes that it is a virtual member of SOME class, because it is a slot of a vptr-backed table, and that is as far as the evidence goes. This binary carries no MSVC RTTI, the record names no owning class, and identical folding means one address can be a virtual member of several classes at once, so no class identity is claimed.
- Why does one address live in three vtables? ICF-folded shared stubs and vtable merging both produce that, and nothing in the five bytes distinguishes them.
