# Validation 0x01021090

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-01021090-space-player-empire-id/space_player_empire_id_01021090.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | the derived ABI record abstained (ABI_UNKNOWN): no_discriminator: no stack-argument read and no positive receiver evidence |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 3-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x01021090; 169 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the machine-vs-machine rule: all 1 data address(es) the source span names are recorded as Ghidra data references out of this body, and the complete 3-instruction listing corroborates 1 of them; the artifact records 1 read across 1 reference row(s)the data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 1 data reference row(s) out of 0x01021090 over 1 distinct address(es); 1 of them name writable storage (0x016dda8c), which is where a mutable global can live; segment breakdown: .data=1; access modes recorded: 1 read;  |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (3 of 3 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 3-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 3-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'std::uint32_t' and the machine return state is WIDTH_4_IN_EAX: the complete 3-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `577e26ba54b6a8092af630b15b488319161a062964d6bcfcd60c2f173fff9234`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e0f4ecb2f629d7ba45cfeadc785c727c483cd54c780cd3e31d568358e2e7662a`
- Pack digest quoted by the briefing: `577e26ba54b6a8092af630b15b488319161a062964d6bcfcd60c2f173fff9234`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Can any recorded call site reach this entry with a null global? The entry faults in that state by construction; whether it is reachable in practice is unestablished, and it is the one fact that would make this accessor unsafe to call early in startup.
- Do the ~100 recorded callers use the returned value as an ID (compare against -1, index a table) or as an address? Not sampled here: the ID reading rests on the export and the lifecycle, not on caller behaviour.
- What class is the object at 0x016dda8c? There is no MSVC RTTI in this binary, no instruction in this body names a type, and the pointee is reached only through this one offset from here.
- What is the numeric domain of the empire ID - a dense index, a handle, a database key? The -1 sentinel at both allocation and teardown says only 'no empire'.
- Which calling convention did the original source declare? The body cannot distinguish __cdecl, __stdcall, __thiscall and __fastcall, and the ABI record abstains. A zero-parameter declaration is used because it is what the machine fixes.
- Who else writes +0x18? The committed lifecycle records 0x01021d40 writing -1 at allocation and 0x01022460 resetting to -1 at teardown, but nothing here enumerates every writer in the binary, and no setter-shaped entry is claimed to exist.
