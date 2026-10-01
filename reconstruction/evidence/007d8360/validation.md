# Validation 0x007d8360

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 51-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 0 distinct address(es) for 0x007d8360; 1 of those rows name an external import rather than an address and are not address-comparable, as in the projection |
| GLOBALS | `WARN` | `partial` | the complete 51-instruction listing names 1 data address(es) (0x13cc4dc) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field entries_begin, name_begin, name_end, vtable and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (51 of 51 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 51-instruction listing lie inside the recovered body span 0x007d8360..0x007d83cc, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 51-instruction body names 2 indirect transfer(s): 0x007d839e is INDIRECT_NON_VTABLE; 0x007d83c4 dispatches slot 0x40 through the table word in EAX; the machine parse consumed 51 of 51 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2, so the dispatch is visible in the machine listing but is not proven: 1 of the 2 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x007d839e), so the dispatch's identity is not established: the target is the memory operand [0x013cc4dc], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'bool': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `4ac238a2e428fca89b0b1897251343d0162edaeb6222eefdb493297a21400360`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3d72146ada8c4abd3ccc4ebd527dfe3e7a3fd110df5b8a039eb3a7add28894cc`
- Pack digest quoted by the briefing: `4ac238a2e428fca89b0b1897251343d0162edaeb6222eefdb493297a21400360`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Observe entry name storage, registry vtable target, and runtime case-insensitive matching; runtime validation is not run.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Observe entry name storage, registry vtable target, and runtime case-insensitive matching; runtime validation is not run.
- concrete runtime owners and values remain unresolved
