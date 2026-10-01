# Validation 0x00b7e560

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg14_a3_world_wave3/world_wave3.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 83-instruction listing name the same 1 direct transfer target(s); 3 intra-procedural jump(s) target inside the recovered body span 0x00b7e560..0x00b7e671 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00b7e58b, 0x00b7e5b7, 0x00b7e5e3; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 1 distinct address(es) for 0x00b7e560; 17 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | 1 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 3 type(s) |
| CONSTANTS | `WARN` | `partial` | the machine listing is not fully parsed: 83 of 83 instruction(s) consumed, degraded=True, unparsed=3 |
| CONTROL FLOW | `PASS` | `complete` | all 8 conditional branch target(s) in the complete 83-instruction listing lie inside the recovered body span 0x00b7e560..0x00b7e671, so the branch graph is closed inside it; the source span declares while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 83-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `6c7301064823d47105d17b83afb0fdcf18fbaddf0861b842d24e249785a11c0d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `af088b178a31f70c2ac7803fba64139eafebf1c96eb3b0727fde1bcd16f5c40d`
- Pack digest quoted by the briefing: `6c7301064823d47105d17b83afb0fdcf18fbaddf0861b842d24e249785a11c0d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The distribution and state ownership behind 0x009360d0 remain opaque.
- The helper address 0x01601760 is preserved as the live receiver identity without dereferencing it in the model.
- runtime validation not run
