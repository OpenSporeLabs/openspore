# Validation 0x00b3d230

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-w2-00b3d230/root_accessor_00b3d230.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00b3d230; 80 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the machine-vs-machine rule: all 1 data address(es) the source span names are recorded as Ghidra data references out of this body, and the complete 2-instruction listing corroborates 1 of them; the artifact records 1 read across 1 reference row(s)the data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 1 data reference row(s) out of 0x00b3d230 over 1 distinct address(es); 1 of them name writable storage (0x0167eac0), which is where a mutable global can live; segment breakdown: .data=1; access modes recorded: 1 read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 2-instruction listing was consumed in full by the machine parse (degraded=False, unparsed=0) and every memory operand it names (0x0167eac0) is a segment-absolute address naming no register, which is the evidence that this function performs no register-relative access and therefore no receiver-relative one -- a receiver is reachable only through a register, so an absolute operand cannot address one; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist; what this says about the absolute addresses themselves is nothing: whether one of them is a global is GLOBALS' question, judged on its own machine sides, and this arm neither confirms nor denies it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c7b9f5576440eec6382727f32d67600e7a653b4e2840e485f8e7fee2dd6aa2ef`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `e3146ec818a7c3f3990946127c92f366a47a80caf25e8390ac5d7257d134b234`
- Pack digest quoted by the briefing: `c7b9f5576440eec6382727f32d67600e7a653b4e2840e485f8e7fee2dd6aa2ef`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential run must call this VA through a direct call, as all 60 recorded callers do; there is no vtable slot and therefore no dispatch path to reconstruct for it.`, `The static validator reported no target source span (validation.json source.path null), so no structural check has been run against the staged sources for this package; that is an orchestrator-side gap, not a pass.`, `The value returned by 0x00b3d230 is whatever is stored at 0x0167eac0 at the moment of the call, so a differential run must establish that dword's value first; the body itself does not determine it and the image carries no initializer for that address.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential run must call this VA through a direct call, as all 60 recorded callers do; there is no vtable slot and therefore no dispatch path to reconstruct for it.
- The static validator reported no target source span (validation.json source.path null), so no structural check has been run against the staged sources for this package; that is an orchestrator-side gap, not a pass.
- The value returned by 0x00b3d230 is whatever is stored at 0x0167eac0 at the moment of the call, so a differential run must establish that dword's value first; the body itself does not determine it and the image carries no initializer for that address.
- What the word at 0x0167eac0 denotes. The body at 0x00b3d230 loads it and returns it; it does not dereference it, test it or store it, so the body fixes the location and the width and nothing about the meaning.
- Whether the 60 callers share a common owner or a common subsystem role. The index record labels the VA subsystem Simulator, but that is a triage label and no caller was reconstructed here to corroborate it.
- Whether the pointer_like classification of the returned word (inference RT2) is a real type or a shape heuristic. Two null-testing callers (0x00c0d3c0, 0x00c38532) are consistent with a pointer but do not establish one.
- Which calling convention the original compiler used. Zero parameters, no receiver and a bare RET make the four x86-32 conventions byte-identical here, and 60 direct call sites that push nothing narrow the field to 'no arguments passed' without selecting a convention.
- Who writes 0x0167eac0. This body never stores to it and no writer was identified in this session; the 60 callers of this VA are all readers. Until a writer is found the dword's lifecycle is unknown.
- Why the accessors at 0x00b3d220, 0x00b3d230, 0x00b3d240 and 0x00b3d250 all read adjacent dwords of .data (0x0167eac0 as an immediate, then 0x0167eac0, 0x0167eac4, 0x0167ead0) and whether the 0x00b3d220 constant form is an initialization of a table the accessors then read. This package reconstructs 0x00b3d230 only, and the neighbour's operand is not used as evidence for it.
