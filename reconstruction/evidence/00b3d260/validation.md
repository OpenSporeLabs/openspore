# Validation 0x00b3d260

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00b3d260-simulator-root-slot/root_slot_00b3d260.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | the derived ABI record abstained (ABI_UNKNOWN): no_discriminator: no stack-argument read and no positive receiver evidence |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00b3d260; 42 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the machine-vs-machine rule: all 1 data address(es) the source span names are recorded as Ghidra data references out of this body, and the complete 2-instruction listing corroborates 1 of them; the artifact records 1 read across 1 reference row(s)the data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 1 data reference row(s) out of 0x00b3d260 over 1 distinct address(es); 1 of them name writable storage (0x0167ead8), which is where a mutable global can live; segment breakdown: .data=1; access modes recorded: 1 read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 2-instruction listing was consumed in full by the machine parse (degraded=False, unparsed=0) and every memory operand it names (0x0167ead8) is a segment-absolute address naming no register, which is the evidence that this function performs no register-relative access and therefore no receiver-relative one -- a receiver is reachable only through a register, so an absolute operand cannot address one; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist; what this says about the absolute addresses themselves is nothing: whether one of them is a global is GLOBALS' question, judged on its own machine sides, and this arm neither confirms nor denies it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'std::uint32_t' and the machine return state is WIDTH_4_IN_EAX: the complete 2-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b0085aa93c947e6d94ccacb32ab175cf20214672339c36ed82a5e06e14ecd4da`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `b05360e5a5b4ed9d20d3a1b4aad103ae53aa2a6df04781826f6592b4841d8e21`
- Pack digest quoted by the briefing: `b0085aa93c947e6d94ccacb32ab175cf20214672339c36ed82a5e06e14ecd4da`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Do any of the 16 other slots in the table (0x0167eac0,0x0167eac4,0x0167eac8,0x0167eacc,0x0167ead0,0x0167ead4,0x0167eadc,0x0167eae8,0x0167eaf0,0x0167eaf4,0x0167eafc and the three closed ones) alias each other at a lifecycle point? Nothing here says they do or do not.
- Is 0x00b3d260 the accessor a canonical SDK-named getter would sit on? The 17-slot table at 0x0167eac0..0x0167eafc has one accessor per slot and the SDK import pass named none of them; no SDK identity is claimed.
- Is the returned word ever null at a real callsite, and what do callers do then? None of the eight caller listings read here null-tests the result, so no null contract is claimed in either direction.
- The remaining 29 of the 37 distinct callers (58 callsites total) were not classified by hand. Only 0x00abf710/0x00abf760/0x00abf790/0x00b32ac4/0x00b32c60/0x00bf45f0/0x00bf57b0/0x00bf7d80 were read; fan-in was deliberately not used as semantic evidence.
- What object does 0x0167ead8 point to? Consumers treat it as an object base with a function table at [result+0] and dispatch through slots +0x24, +0x30 and +0x38, but no class, vtable identity, field name, slot owner or object size is established by this body or by any caller read here.
- Who publishes 0x0167ead8, when, and how is it torn down and reset? The project's own promoted metadata for 0x00abf790 already carries this as an open question and this package keeps it open; no first-writer scan was attempted.
