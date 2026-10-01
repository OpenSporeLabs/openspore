# Validation 0x00b3d240

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-w2-00b3d240/root_accessor_00b3d240.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00b3d240; 210 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the machine-vs-machine rule: all 1 data address(es) the source span names are recorded as Ghidra data references out of this body, and the complete 2-instruction listing corroborates 1 of them; the artifact records 1 read across 1 reference row(s)the data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 1 data reference row(s) out of 0x00b3d240 over 1 distinct address(es); 1 of them name writable storage (0x0167eac4), which is where a mutable global can live; segment breakdown: .data=1; access modes recorded: 1 read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 2-instruction listing was consumed in full by the machine parse (degraded=False, unparsed=0) and every memory operand it names (0x0167eac4) is a segment-absolute address naming no register, which is the evidence that this function performs no register-relative access and therefore no receiver-relative one -- a receiver is reachable only through a register, so an absolute operand cannot address one; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist; what this says about the absolute addresses themselves is nothing: whether one of them is a global is GLOBALS' question, judged on its own machine sides, and this arm neither confirms nor denies it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `63f8656d4e4fbbbc81bea9232144e249cf173d6622f66caa6ec805eadecbddcb`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `cbba98232c90510e92fcc17d1932aece6a5ae6c0e0d575bed40d07afecedfc86`
- Pack digest quoted by the briefing: `63f8656d4e4fbbbc81bea9232144e249cf173d6622f66caa6ec805eadecbddcb`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Any differential run against the original must arrange for 0x0167eac4 to hold a known word first: the image carries no initializer for it, and a run that reads it as zero observes the loader's zero-fill rather than the game's state.`, `No original-process trace exists for this target (evidence.json categories.runtime is MISSING), so nothing here is runtime-validated.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Any differential run against the original must arrange for 0x0167eac4 to hold a known word first: the image carries no initializer for it, and a run that reads it as zero observes the loader's zero-fill rather than the game's state.
- Are the 26 direct callers (fan_in 158) all expecting the same zero-parameter shape, and does any of them treat the returned word as something other than a table pointer?
- Does the word at 0x0167eac4 participate in a struct shared with 0x0167eac0 and 0x0167ead0 (the neighbours 0x00b3d230 and 0x00b3d250 read)? No layout is claimed and none is implied by adjacency.
- No original-process trace exists for this target (evidence.json categories.runtime is MISSING), so nothing here is runtime-validated.
- What concrete type, if any, lives at 0x0167eac4, and what does the returned word denote? The body proves a 4-byte load; nothing names the storage.
- Which of the four x86-32 conventions does the original use? The body cannot discriminate; only a caller-side contract beyond zero pushed arguments and zero callee cleanup could, and no caller in the recorded set supplies one.
- Who stores 0x0167eac4 before it is read? No write row for the address exists in the data-reference sidecar, but that artifact records only direct references and cannot see a store through a register.
