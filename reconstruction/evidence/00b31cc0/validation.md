# Validation 0x00b31cc0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 128-instruction listing name the same 11 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x00b31cc0..0x00b31e96 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00b31e09; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 14 outgoing call edge row(s) over 11 distinct address(es) for 0x00b31cc0; the source span names 9 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 128-instruction listing names 9 data address(es) (0x13ec0c0, 0x140ebc0, 0x146029c, 0x1460388, 0x1485720, 0x167e8b0, 0x167e8b4, 0x167e8b8, 0x167e8e0) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 2 displacement(s) (0x14, 0x60) lie outside the machine-derived receiver bounds (0x4) for ECX, so the source and the body disagree with the receiver record; the source span declares 0x14, 0x60, and the complete 128-instruction listing names none through that register |
| CONSTANTS | `WARN` | `partial` | the machine listing is not fully parsed: 128 of 128 instruction(s) consumed, degraded=True, unparsed=2 |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 128-instruction listing lie inside the recovered body span 0x00b31cc0..0x00b31e96, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 128-instruction body names 4 indirect transfer(s): 0x00b31d01 dispatches slot 0xa4 through the table word in EDX; 0x00b31d70 dispatches slot 0x2c through the table word in EAX; 0x00b31dec dispatches slot 0x58 through the table word in EDX; 0x00b31e61 dispatches slot 0x98 through the table word in EDX; the machine parse consumed 128 of 128 instruction(s) with 2 unparsed and degraded=True, and the machine dispatch record independently counts 4, so the dispatch is visible in the machine listing but is not proven: the machine parse is degraded and 2 instruction(s) were left unparsed |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 7 of 8 static checks evaluated, 3 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `e82496dcc0cdf4ef73104c18576bad96ebf0fcd85c8c45aadbfa5ad421a95843`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `93b5a619948cc30218b76a6563e781ddceb8c93a042acf1630c4609ab1e7d534`
- Pack digest quoted by the briefing: `e82496dcc0cdf4ef73104c18576bad96ebf0fcd85c8c45aadbfa5ad421a95843`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `required`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- concrete runtime owners and values remain unresolved
- required
