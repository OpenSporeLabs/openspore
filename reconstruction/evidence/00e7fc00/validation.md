# Validation 0x00e7fc00

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg08_cell_mode/mode_on_exit.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 60-instruction listing name the same 8 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 9 outgoing call edge row(s) over 8 distinct address(es) for 0x00e7fc00; the source span names 8 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 60-instruction listing names 17 data address(es) (0x1550a84, 0x1550ad8, 0x1550adc, 0x1550ae0, 0x1550ae4, 0x1550aec, 0x1550af0, 0x166c004, 0x16b3be0, 0x16b3be4, 0x16b3be8, 0x16b3bec, 0x16b3bf0, 0x16b3bf4, 0x16b3bf8, 0x16b3bfc, 0x16b3c04) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field destination_01550a84, destination_01550ad8, destination_01550adc, destination_01550ae0 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (60 of 60 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 60-instruction listing lie inside the recovered body span 0x00e7fc00..0x00e7fcfa, so the branch graph is closed inside it; the source span declares while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 60-instruction body names 1 indirect transfer(s): 0x00e7fced dispatches slot 0x98 through the table word in EDX; the machine parse consumed 60 of 60 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 3 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d90d4adef673eb28ade9d201483c5df42c2a00531862549fe196bf36ebe3daba`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `203df974eed20b69144287a915e5312af41cbac397873ff38ca682f4ebaf2202`
- Pack digest quoted by the briefing: `d90d4adef673eb28ade9d201483c5df42c2a00531862549fe196bf36ebe3daba`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-cell-mode-on-exit`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- gate-cell-mode-on-exit
- global and Cell-game pool validity
- nested cleanup-helper effects
- record branch, lifetime, and free-list effects
- runtime vtable reachability and mode transition ordering
- serializer, persistence, and ownership behavior
- service identity, vtable target, argument meanings, and side effects
