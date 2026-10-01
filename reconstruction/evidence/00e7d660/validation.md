# Validation 0x00e7d660

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 68-instruction listing name the same 6 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 7 outgoing call edge row(s) over 6 distinct address(es) for 0x00e7d660; the source span names 6 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 68-instruction listing names 3 data address(es) (0x16b3c04, 0x16b3c0c, 0x16b3c14) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 4 source field-offset declaration(s) (field health_tick_00e7d070, field input, field local_object_411c, field object_index_01c) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (68 of 68 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 6 conditional branch target(s) in the complete 68-instruction listing lie inside the recovered body span 0x00e7d660..0x00e7d714, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 68-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'bool' and the machine return state is WIDTH_1_IN_EAX: the complete 68-instruction listing writes EAX at a determinate 1-byte width before all 4 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `5c3f3013147f57fab0f24f35bfc8cc5b61d01c55a7e0cdb12b80145ca4aa3bc8`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `b17ede8d667c7a577220b432a0ac781468de2ed5f8db60dcfe1f973376bdf80a`
- Pack digest quoted by the briefing: `5c3f3013147f57fab0f24f35bfc8cc5b61d01c55a7e0cdb12b80145ca4aa3bc8`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Observe the concrete vtable call shape, the effective return of 0x00b1fbf0 including any patching, the 0x00b721d0 lookup result, the wheel accumulator at Game input offset 0x44, and the 0x00e7d070 effects in the original Cell mode.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Observe the concrete vtable call shape, the effective return of 0x00b1fbf0 including any patching, the 0x00b721d0 lookup result, the wheel accumulator at Game input offset 0x44, and the 0x00e7d070 effects in the original Cell mode.
- concrete runtime receiver identity and vtable dispatch reachability for slot 0x40
- runtime reachability of the zoom and health paths, which is zero under the observed gate body
- the identity of the unnamed strategy slot 0x3c target 0x00e81030 between OnMouseUp and OnMouseWheel
- the semantic meaning of mode value 3 in the 0x00e7d070 call and of the sentinel word at 0x016b3c14
- whether the 0x016b3c14 sentinel can ever differ from the value the caller loads at 0x00e7d6ed, which would decide whether the 0x00e7d070 sub-object lookup path is ever taken
- whether the always-true 0x00b1fbf0 body is a shipped default, a build-configuration stub, or a patch target
