# Validation 0x005c0a60

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 100-instruction listing name the same 3 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x005c0a60..0x005c0b73 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x005c0aa0; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 3 distinct address(es) for 0x005c0a60; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 3 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 100-instruction listing names 3 data address(es) (0x13f7c30, 0x1667bac, 0x1667bae) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field begin, begin_88, cached_index_20, cached_total_24 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (100 of 100 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 13 conditional branch target(s) in the complete 100-instruction listing lie inside the recovered body span 0x005c0a60..0x005c0b73, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 100-instruction body names 3 indirect transfer(s): 0x005c0add dispatches slot 0x7c through the table word in EDX; 0x005c0af9 dispatches slot 0x7c through the table word in EDX; 0x005c0b45 dispatches slot 0x80 through the table word in EAX; the machine parse consumed 100 of 100 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 1 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the return register EAX is written at a width this module cannot bound on at least one of the 2 reachable return(s) in the complete 100-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `99c29edbdac9e03a785251f96fcff5748b09ce821d175af30e64b7dda836162d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `757ecc63dcce24075cd0ffe71a0df4a8350e504de70a539025eed78c9da8f049`
- Pack digest quoted by the briefing: `99c29edbdac9e03a785251f96fcff5748b09ce821d175af30e64b7dda836162d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `The decoded meaning of the format literal at 0x013f7c30 is inferred as '<n>/<total>' and is unconfirmed by any runtime render.`, `The formatter 0x0041e050 and the release port 0x00f47380 remain dependency-only.`, `The nav and text vtable owners are unattributed in the live database.`, `The unused formal argument is kept only to preserve the RET 0x4 cleanup width.`, `The visibility port 0x005c29c0 is an opaque bool seam and is not promoted.`, `gate-page-visible-slots-runtime-visibility-and-format-literal`, `runtime validation not performed; static decompilation and disassembly only`, `the decoded meaning of the format literal at 0x013f7c30 is inferred as '<n>/<total>' and is not confirmed by a runtime render`, `the nav and text vtable owners at slot +0x7c and +0x80 are unattributed in the live database`, `the text formatter 0x0041e050 and the release port 0x00f47380 remain dependency-only`, `the unused formal argument is retained in the signature to keep the RET 0x4 cleanup width exact`, `the visibility port 0x005c29c0 is modelled as an opaque bool seam and is not promoted`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The decoded meaning of the format literal at 0x013f7c30 is inferred as '<n>/<total>' and is unconfirmed by any runtime render.
- The formatter 0x0041e050 and the release port 0x00f47380 remain dependency-only.
- The nav and text vtable owners are unattributed in the live database.
- The unused formal argument is kept only to preserve the RET 0x4 cleanup width.
- The visibility port 0x005c29c0 is an opaque bool seam and is not promoted.
- What the unused fourth formal was intended to select
- What the visibility port 0x005c29c0 actually tests to decide a slot is visible
- Whether the cached pair at +0x20 and +0x24 is ever invalidated by another path
- Whether the format literal at 0x013f7c30 really renders as '<n>/<total>'
- Who owns the nav vtable slot +0x7c and the text vtable slot +0x80
- gate-page-visible-slots-runtime-visibility-and-format-literal
- runtime validation not performed; static decompilation and disassembly only
- the decoded meaning of the format literal at 0x013f7c30 is inferred as '<n>/<total>' and is not confirmed by a runtime render
- the nav and text vtable owners at slot +0x7c and +0x80 are unattributed in the live database
- the text formatter 0x0041e050 and the release port 0x00f47380 remain dependency-only
- the unused formal argument is retained in the signature to keep the RET 0x4 cleanup width exact
- the visibility port 0x005c29c0 is modelled as an opaque bool seam and is not promoted
