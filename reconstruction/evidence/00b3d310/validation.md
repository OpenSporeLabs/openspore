# Validation 0x00b3d310

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00b3d310-root-slot-eae8/root_slot_eae8_00b3d310.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | the derived ABI record abstained (ABI_UNKNOWN): no_discriminator: no stack-argument read and no positive receiver evidence |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00b3d310; 125 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the machine-vs-machine rule: all 1 data address(es) the source span names are recorded as Ghidra data references out of this body, and the complete 2-instruction listing corroborates 1 of them; the artifact records 1 read across 1 reference row(s)the data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 1 data reference row(s) out of 0x00b3d310 over 1 distinct address(es); 1 of them name writable storage (0x0167eae8), which is where a mutable global can live; segment breakdown: .data=1; access modes recorded: 1 read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 2-instruction listing was consumed in full by the machine parse (degraded=False, unparsed=0) and every memory operand it names (0x0167eae8) is a segment-absolute address naming no register, which is the evidence that this function performs no register-relative access and therefore no receiver-relative one -- a receiver is reachable only through a register, so an absolute operand cannot address one; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist; what this says about the absolute addresses themselves is nothing: whether one of them is a global is GLOBALS' question, judged on its own machine sides, and this arm neither confirms nor denies it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'OpaqueRootSlotTarget*' and the machine return state is WIDTH_4_IN_EAX: the complete 2-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1e682f32bad14fe5faaa9ec9a6bd37e1a338f4ed3806a782ec30d7f780534adb`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `322a181bd866b9c5329eb6258e49b46b0f76ba62573868a7119743e78c66b6dd`
- Pack digest quoted by the briefing: `1e682f32bad14fe5faaa9ec9a6bd37e1a338f4ed3806a782ec30d7f780534adb`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `no original-process trace exists for this target; nothing was attempted and nothing failed`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does 0x0167eae8 ever alias any neighbouring slot (0x0167eae0, 0x0167eae4, 0x0167eaf0, 0x0167eaf8)? Adjacency in the .data tail proves nothing and no writer was located.
- Is the returned word a pointer, a handle, or an id? Three sampled callers dereference it at +0x20 or move it into ECX as a receiver, which is why it is modelled as a pointer -- but no callee through it has been resolved and no member is claimed.
- Runtime: no original-process trace exists in this repository for this target, so nothing here is a runtime claim.
- What class or object does 0x0167eae8 hold? No writer of the slot exists in the current analysis state, so its publication and teardown paths are unlocated. The raw-dword note in reconstruction/metadata/wave13-w1-core-b16/00b515e0.json (the address occurs once in the file, at 0x0073d311, as a decodable `A1 E8 EA 67 01 C3` in a region Ghidra has not split into a function) was NOT re-verified by this worker and is cited only as a lead.
- What is at displacement +0x20 of the pointee? Sampled callers read it; this body never does, so no member name is claimed.
- Which calling convention do the 90 direct callers actually use? The body cannot discriminate between the four, so the declared __cdecl is a source-side choice and the real answer needs a caller-side or import-side observation.
- no original-process trace exists for this target; nothing was attempted and nothing failed
