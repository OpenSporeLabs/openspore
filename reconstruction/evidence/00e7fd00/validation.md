# Validation 0x00e7fd00

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg06_cell_state/cell_state.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 582-instruction listing name the same 32 direct transfer target(s); 5 intra-procedural jump(s) target inside the recovered body span 0x00e7fd00..0x00e80653 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00e7ff57, 0x00e801a6, 0x00e802f8, 0x00e803ec, 0x00e8063b; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 55 outgoing call edge row(s) over 32 distinct address(es) for 0x00e7fd00; 5 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 9 address-named callee(s), against the 55 outgoing call edge row(s) and 32 distinct callee(s) the export records; 23 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00bbb0e0, 0x00bbbde0, 0x00d018d0, 0x00e31100, 0x00e4cc40, 0x00e4cce0, 0x00e4ce40, 0x00e50810, 0x00e5f360, 0x00e65180, 0x00e66010, 0x00e6eb60 and 11 more; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 55 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 12 of them and no others |
| GLOBALS | `WARN` | `partial` | 1 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 7 source field-offset declaration(s) (displacement 0x4128, displacement 0x9c, field constant_2f7d0004, field field_00) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 1 source constant(s) are absent from the machine listing: 0xffffffff |
| CONTROL FLOW | `PASS` | `complete` | all 31 conditional branch target(s) in the complete 582-instruction listing lie inside the recovered body span 0x00e7fd00..0x00e80653, so the branch graph is closed inside it; the source span declares for, if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 582-instruction body names 7 indirect transfer(s): 0x00e7ffc3 dispatches slot 0xc through the table word in EDX; 0x00e7ffda dispatches slot 0x4 through the table word in EDX; 0x00e80085 dispatches slot 0xc through the table word in EDX; 0x00e80096 dispatches slot 0x4 through the table word in EDX; 0x00e800fb dispatches slot 0x34 through the table word in EAX; 0x00e8010d dispatches slot 0x34 through the table word in EDX; 0x00e80120 dispatches slot 0x34 through the table word in EDX; the machine parse consumed 582 of 582 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 7. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'void': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 3 passed, 1 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `38a9875e008e8c90d508a2db5d406af050a3e7a365ba0ff4a358129fc353bfbd`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `f88380edbcf94071c47b5ddd7a03ee2bb34e1ed03b7d0f673e1185fdad3ceec3`
- Pack digest quoted by the briefing: `38a9875e008e8c90d508a2db5d406af050a3e7a365ba0ff4a358129fc353bfbd`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `cell_reset_observation`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- argument roles
- cell_reset_observation
- external manager results
- global registry ownership
- mode table contents
