# Validation 0x00b5f040

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_game_mode_wave8/game_mode_wave8.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 128-instruction listing name the same 19 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x00b5f040..0x00b5f1a2 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00b5f0ee; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 19 outgoing call edge row(s) over 19 distinct address(es) for 0x00b5f040; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 19 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 128-instruction listing names 2 data address(es) (0x1654c08, 0x1686af0) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field first_mode, flag_01686af0, shared_state, transition_flag_0c and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (128 of 128 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 8 conditional branch target(s) in the complete 128-instruction listing lie inside the recovered body span 0x00b5f040..0x00b5f1a2, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 128-instruction body names 8 indirect transfer(s): 0x00b5f0e1 dispatches slot 0x4 through the table word in EDX; 0x00b5f11d dispatches slot 0x14 through the table word in EAX; 0x00b5f13d dispatches slot 0x14 through the table word in EDX; 0x00b5f14f dispatches slot 0x14 through the table word in EDX; 0x00b5f161 dispatches slot 0x14 through the table word in EDX; 0x00b5f173 dispatches slot 0x14 through the table word in EDX; 0x00b5f185 dispatches slot 0x14 through the table word in EDX; 0x00b5f18e dispatches slot 0x44 through the table word in EDX; the machine parse consumed 128 of 128 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 8. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x4, 0x44, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'void': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 5 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `32644721d7a80f20066724506eb79914cf19df062db9dad4acca07f8846f67a9`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `717bd18b4ad24d9210bdd0c25b285a365254a9335157d774452ce82d02789ea8`
- Pack digest quoted by the briefing: `32644721d7a80f20066724506eb79914cf19df062db9dad4acca07f8846f67a9`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Bind the live receiver vtable, participant list, shared-state root, and service callbacks before runtime validation; the model test is not an original-process trace.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Bind the live receiver vtable, participant list, shared-state root, and service callbacks before runtime validation; the model test is not an original-process trace.
- concrete runtime owners and values remain unresolved
