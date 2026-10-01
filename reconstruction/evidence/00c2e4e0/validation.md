# Validation 0x00c2e4e0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-sporepedia-nop-slot/sporepedia_nop_slot.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 1-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00c2e4e0; 254 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the complete 1-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 1-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (1 of 1 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 1-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 1-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d955de24af726988f5e68d2e94d0642a50014dfa4e4eadd5f1e4a36a5c39fb53`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `246a4ca4ebf3d171b68ea2d412b77c403b0aa8688f72d0ac61cd2f619a327da3`
- Pack digest quoted by the briefing: `d955de24af726988f5e68d2e94d0642a50014dfa4e4eadd5f1e4a36a5c39fb53`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A pure read of the receiver with no effect is unobservable for a leaf body, in the original as much as in the model, so no test asserts the absence of one; the listing shows no read and the source declares none, which is the whole of the evidence.
- Is the receiver ever observed non-null at a call site? The body never reads it, so its value is unobservable from this function; the 254 incoming call sites are unreconstructed and none was traced.
- What does this slot override, if anything? A bare RET is the shape of an empty virtual function -- a default implementation derived classes inherit -- but no RTTI exists in this binary and the vtable pass never ran, so the base/override relationship is not established.
- Which class is this a virtual member of? The V1-VFT membership is established over 479 vptr-backed tables because identical-code folding collapses every no-op virtual member in this image onto 0x00c2e4e0, so no single class can be named and none is claimed.
- Why does the slot exist? An empty virtual member is the usual shape of a hook the game's classes override elsewhere, but which classes override it, and whether any do, is not established by any record for this target.
