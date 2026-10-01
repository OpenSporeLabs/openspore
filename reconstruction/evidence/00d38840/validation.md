# Validation 0x00d38840

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00d38840-global-singleton-getter/global_singleton_00d38840.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | the derived ABI record abstained (ABI_UNKNOWN): no_discriminator: no stack-argument read and no positive receiver evidence |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00d38840; 59 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `WARN` | `partial` | the complete 2-instruction listing names 1 data address(es) (0x0169e294); the data-reference artifact is read whole and records 1 reference row(s) out of this body covering every address under review, with access mode(s) read=1 |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 2-instruction listing was consumed in full by the machine parse (degraded=False, unparsed=0) and every memory operand it names (0x0169e294) is a segment-absolute address naming no register, which is the evidence that this function performs no register-relative access and therefore no receiver-relative one -- a receiver is reachable only through a register, so an absolute operand cannot address one; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist; what this says about the absolute addresses themselves is nothing: whether one of them is a global is GLOBALS' question, judged on its own machine sides, and this arm neither confirms nor denies it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `82e9e391470ea513006896ee31d2ecc459ccb285f49c973d8e7cc74eede14e85`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `c13c75bd984da3cba053690daa0e84ecfedd2528b9ce9f42e1441f0d0f643028`
- Pack digest quoted by the briefing: `82e9e391470ea513006896ee31d2ecc459ccb285f49c973d8e7cc74eede14e85`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- What TYPE the slot's pointee is. The evidence establishes that it is an object pointer - one writer publishes `this`, and callers use the result as a receiver and index through it - but not its class. The slot's Ghidra label is App::sCreatureModeStrategy while the callee names a TYPE App::cCreatureModeStrategy, and this binary has no MSVC RTTI, so nothing machine-derived ties the two together. Promoting cCreatureModeStrategy to the C type needs RTTI, a vtable-shape match, or an SDK-proven static-member declaration.
- Whether 0x00d3b9b0 is the ONLY writer across the whole program. The pinned sidecar and the live database each record one write row for the slot; neither covers unanalysed or dynamically-reached code.
- Whether all 39 recorded callers use the result the same way. Four were sampled (0x00d4c5e0, 0x00d395a4, 0x00d2b6e0, 0x00d2c280); the other 35 were not, so 'every caller treats it as a receiver' is not claimed.
- Whether the absolute slot address can ever be modelled as a real dereference rather than a stood-up object. That needs the original image mapped, which is outside what this package does.
- Whether the slot is ever null in the running process, and therefore whether any caller has a latent null dereference. The runtime axis is GATED and unattempted, so nothing here answers it.
