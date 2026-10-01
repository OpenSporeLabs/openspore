# Validation 0x00b3d380

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00b3d380-simulator-slot-getter/simulator_slot_getter_00b3d380.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | the derived ABI record abstained (ABI_UNKNOWN): no_discriminator: no stack-argument read and no positive receiver evidence |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00b3d380; 240 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `WARN` | `partial` | the complete 2-instruction listing names 1 data address(es) (0x0167eb04); the data-reference artifact is read whole and records 1 reference row(s) out of this body covering every address under review, with access mode(s) read=1 |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 2-instruction listing was consumed in full by the machine parse (degraded=False, unparsed=0) and every memory operand it names (0x0167eb04) is a segment-absolute address naming no register, which is the evidence that this function performs no register-relative access and therefore no receiver-relative one -- a receiver is reachable only through a register, so an absolute operand cannot address one; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist; what this says about the absolute addresses themselves is nothing: whether one of them is a global is GLOBALS' question, judged on its own machine sides, and this arm neither confirms nor denies it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'OpaqueSimulatorSingleton*' and the machine return state is WIDTH_4_IN_EAX: the complete 2-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `646fbe16cfc222ec58a43759478bc1c9b8dd011da0bfbf87ab67eabb99bb269c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `1b68b652ac2135b24a01ef1c6f73a5691ad04db9bb1062fa7c780ace2361caf0`
- Pack digest quoted by the briefing: `646fbe16cfc222ec58a43759478bc1c9b8dd011da0bfbf87ab67eabb99bb269c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the 0x0167eb00 and 0x0167eb08 slots (accessors 0x00b3d370 and 0x00b3d390, immediate neighbours in the same table) related to this one? Neither is named.
- Does the pointer the entry returns need an AddRef, and if so by whom? The body has no room for a reference call, and no writer is known, so ownership is undetermined.
- Is the byte at pointee+0x48 a flags word with more defined bits than bit 0? Three callers test only bit 0.
- What class does the word at 0x0167eb04 point to? No SDK import, committed research note or sampled caller names it.
- Who publishes 0x0167eb04, and when relative to the 240 callsites that read it? No direct writer exists; indirect or bulk publication is unexcluded.
