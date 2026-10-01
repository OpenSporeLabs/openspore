# Validation 0x00801ac0

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `FAIL` | `partial` | the machine-vs-machine rule: the xref export records 2 callee(s) and the complete 63-instruction listing 1 direct transfer(s), and the two sets disagree; 1 export callee(s) the body does not show: 0x00432a50; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00801ac0 |
| GLOBALS | `WARN` | `partial` | 3 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field field_04, field_08, field_0c, field_10 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (63 of 63 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 63-instruction listing lie inside the recovered body span 0x00801ac0..0x00801b5b, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 63-instruction body names 3 indirect transfer(s): 0x00801b15 dispatches slot 0x10 through the table word in EAX; 0x00801b3b dispatches slot 0x24 through the table word in EDX; 0x00801b4e dispatches slot 0x0 through the table word in EDX; the machine parse consumed 63 of 63 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3, so the dispatch is visible in the machine listing but is not proven: the source span states slot displacement(s) 0x10, 0x24, 0x2393756 and the machine reads 0x0, 0x10, 0x24, so the two disagree about which slot is dispatched |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 3 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a036bd6816656180538bd70738ea634232fe18fd7f996631dfac36439487e38b`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3f3206c0543ac339c23d20e5d581dd615ce85281e7208d49b894f5e41c1553cd`
- Pack digest quoted by the briefing: `a036bd6816656180538bd70738ea634232fe18fd7f996631dfac36439487e38b`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `cursor allocator, resource factory, cursor vtable, icon dispatch, and output ownership remain gated`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- cursor allocator, resource factory, cursor vtable, icon dispatch, and output ownership remain gated
- runtime validation not run
