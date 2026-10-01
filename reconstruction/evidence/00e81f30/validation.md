# Validation 0x00e81f30

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_app_lifecycle_wave8/app_lifecycle_wave8.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 144-instruction listing name the same 12 direct transfer target(s); 3 intra-procedural jump(s) target inside the recovered body span 0x00e81f30..0x00e82120 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00e820bb, 0x00e820df, 0x00e82103; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 18 outgoing call edge row(s) over 12 distinct address(es) for 0x00e81f30; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 144-instruction listing names 19 data address(es) (0x1550a84, 0x1550ad8, 0x1550adc, 0x1550ae0, 0x1550ae4, 0x1550aec, 0x1550af0, 0x166c004, 0x16b3be0, 0x16b3be4, 0x16b3be8, 0x16b3bec, 0x16b3bf0, 0x16b3bf4, 0x16b3bf8, 0x16b3bfc, 0x16b3c04, 0x16b3c08, 0x16b3c0c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field cell_game, cell_gfx, cell_ui, destination and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (144 of 144 instruction(s), 0 unparsed) and all 7 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 7 conditional branch target(s) in the complete 144-instruction listing lie inside the recovered body span 0x00e81f30..0x00e82120, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 144-instruction body names 6 indirect transfer(s): 0x00e8202c dispatches slot 0x88 through the table word in EDX; 0x00e82041 dispatches slot 0x98 through the table word in EDX; 0x00e8205e dispatches slot 0x30 through the table word in EDX; 0x00e820d2 dispatches slot 0x2c through the table word in EDX; 0x00e820f6 dispatches slot 0x2c through the table word in EDX; 0x00e8211a dispatches slot 0x2c through the table word in EDX; the machine parse consumed 144 of 144 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 6. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 2 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x2c, 0x30, 0x88, 0x98, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `db728df432ccaae919132b8ff8e2f623cbda29f99da0157fb317b884797ca59e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `c70505cf2411ea3b93d712d4ac803a862e32e93d806d0fa9b64c8ef46e96d85b`
- Pack digest quoted by the briefing: `db728df432ccaae919132b8ff8e2f623cbda29f99da0157fb317b884797ca59e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `required`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Concrete service and app-system vtable targets behind the four indirect calls.
- Runtime pointer validity and whether the service globals are cleared by nested destructors.
- Runtime values and ownership of the eight global words.
- Whether any nested helper performs persistence or broader lifetime work.
- required
