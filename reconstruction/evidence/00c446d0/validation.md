# Validation 0x00c446d0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b06/c446d0_tagged_vector3_push.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 44-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (44 of 44 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 44-instruction listing lie inside the recovered body span 0x00c446d0..0x00c44759, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 44-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `2c0274480a7857eb208216a152012b1ef8b66ce9526532ed01a2eb1d684b976e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3ae062dcd8315e0df385d610bfea830dee88e014e3ceb3c8471c0c60e6c9b915`
- Pack digest quoted by the briefing: `2c0274480a7857eb208216a152012b1ef8b66ce9526532ed01a2eb1d684b976e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Confirming that the growth policy is reached with capacity exactly 1 on the first append requires a runtime allocation trace, since the arithmetic is only reached through the callee.`, `No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.`, `The container is empty in the shipping image and the owning subsystem was never started in any recorded run, so the grow path, the prepend path and the inlined append path have all never been observed executing.`, `The null-cursor behaviour can only be exercised by a container whose insert cursor is null while its end cursor is not, i.e. a corrupt or deliberately initialised state. A runtime test must construct that state deliberately to confirm the original leaves the advanced cursor behind.`, `The tag dword's meaning requires observing how the list is consumed after insertions from both ends. A differential trace that records the list contents after a prepend-then-append sequence would settle it; nothing static can.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Confirming that the growth policy is reached with capacity exactly 1 on the first append requires a runtime allocation trace, since the arithmetic is only reached through the callee.
- Is the null-cursor advance a latent bug in the original? The function leaves receiver+0xF4 set to 0x10 when the cursor was null, so a subsequent call would write to address 0x10. Either the null case is unreachable in practice, or the original tolerates the corruption. Static evidence cannot decide, and the behaviour is preserved rather than defended against.
- No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.
- The briefing's canonical ledger recorded caller_count 14 and callee_count 2; both match the live xref query. The briefing's dependency list also omits the two indirect calls through vtable-loaded EDX at 0x00baf763-style sites, but this function has none, so there is no discrepancy to report here.
- The container is empty in the shipping image and the owning subsystem was never started in any recorded run, so the grow path, the prepend path and the inlined append path have all never been observed executing.
- The null-cursor behaviour can only be exercised by a container whose insert cursor is null while its end cursor is not, i.e. a corrupt or deliberately initialised state. A runtime test must construct that state deliberately to confirm the original leaves the advanced cursor behind.
- The tag dword's meaning requires observing how the list is consumed after insertions from both ends. A differential trace that records the list contents after a prepend-then-append sequence would settle it; nothing static can.
- What class owns the vector at +0xF0? A recursive grep of the ModAPI tree for 0xF0, 0x3E4, 0x19C and 0x1F0 found no header declaring this combination. The owner is an opaque type carrying only the observed offsets. This is the material bound on the record.
- What do the other containers on the same receiver do? Sibling 0x00c44760 manipulates +0x3E4, -0xD4 and the flag at +0x19C, but its body was not read by this batch, so no relationship between the two containers is claimed.
- What do the three floats mean, and what does the tag dword mean? Three consecutive floats and a normalised boolean are observed. Spore/SubSystem/PlanetModel.h's `{Vector3 mCenter; bool mCityZone; bool mVisible;}` is a shape-compatible candidate that would make the 0x10-byte element's last dword two bools, but PlanetModel.h declares no 0xF0 member and nothing observed links the two files, so no claim is made.
- What does the dword 3 at receiver+0x1F0, written by caller 0x00b34380 after a prepend, denote? It looks like a small state enum but nothing observed names it.
- Why is the tag dword stored in the element when it is also the direction selector? Either the list is later partitioned by insertion end, or the two callers happen to want the same information. No static evidence distinguishes these.
