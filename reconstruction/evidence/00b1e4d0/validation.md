# Validation 0x00b1e4d0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_00b1e4d0_shared_default_stub/shared_default_stub_00b1e4d0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00b1e4d0; 5 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 2-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `2e6130f4a992f7c26cd5346756b787af486a9192adec976ff1569c980dc64265`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `dc8e6a1b43b46858115307811b242655697c88dcc062d24aecdd9c8046d4175f`
- Pack digest quoted by the briefing: `2e6130f4a992f7c26cd5346756b787af486a9192adec976ff1569c980dc64265`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `observe one real virtual call through a slot-10 word of one of the 286 tables and record whether the caller consumes only AL or the full EAX, which would settle whether the four direct call sites read a bool`, `record what the 286 owning classes use this default for, if anything; the body cannot say`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The full slot list of the 286 vptr-backed tables: only the slot-10 membership of the first observed table (0x013f69b4) is recorded here.
- Whether any of the four direct call sites (0x00404660, 0x005dda30, 0x006a8610, 0x00d77400) consume the one-byte result as a bool or ignore it entirely: the listing defines AL only, so a caller reading the full EAX would be reading bytes this body never defines.
- Which of the 286 owning classes, if any, rely on this default answering a real query, and which treat it as an uninstantiated placeholder: the body cannot distinguish them, and no runtime trace exists in this repository.
- observe one real virtual call through a slot-10 word of one of the 286 tables and record whether the caller consumes only AL or the full EAX, which would settle whether the four direct call sites read a bool
- record what the 286 owning classes use this default for, if anything; the body cannot say
