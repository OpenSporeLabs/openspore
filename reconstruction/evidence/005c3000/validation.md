# Validation 0x005c3000

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_palette_safe_wave10/pkg_palette_safe_wave10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 122-instruction listing name the same 2 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x005c3000..0x005c31b6 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x005c3194; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x005c3000; 2 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 2 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 122-instruction listing names 2 data address(es) (0x1486110, 0x15fd918) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field begin_0c, body_28, end_10, feature_host_10 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (122 of 122 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 12 conditional branch target(s) in the complete 122-instruction listing lie inside the recovered body span 0x005c3000..0x005c31b6, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 122-instruction body names 7 indirect transfer(s): 0x005c308b dispatches slot 0x38 through the table word in EDX; 0x005c30b3 dispatches slot 0x38 through the table word in EDX; 0x005c3101 dispatches slot 0x6c through the table word in EDX; 0x005c3127 dispatches slot 0x38 through the table word in EAX; 0x005c3173 dispatches slot 0x38 through the table word in EAX; 0x005c3188 dispatches slot 0x38 through the table word in EAX; 0x005c31af dispatches slot 0x6c through the table word in EAX; the machine parse consumed 122 of 122 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 7. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 122-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 5 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `fdece4baec41dece08cea17948ba5a442d86e0651d35f5302c52754ec4b1bb81`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `80a8c9c589329253230bf445a04efdd945c340211dd14eda50094b7d783f562b`
- Pack digest quoted by the briefing: `fdece4baec41dece08cea17948ba5a442d86e0651d35f5302c52754ec4b1bb81`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `The element vtable owner behind slot +0x38 and +0x6c is unattributed in the live database.`, `The feature query port 0x008105b0 and the distinct row port 0x005c2aa0 are opaque seams and are not promoted.`, `The group pointer at +0x6c is dereferenced without a null check, exactly as the native body does.`, `The row gap global at 0x01486110 is modelled as a float whose runtime value is not established.`, `The semantic identity of the feature id 0x05d3f56b is inferred from the call shape only.`, `gate-palette-row-layout-runtime-group-and-feature-values`, `runtime validation not performed; static decompilation and disassembly only`, `the element vtable owner behind slot +0x38 and +0x6c is unattributed in the live database`, `the feature query port 0x008105b0 and the distinct row port 0x005c2aa0 are opaque seams and are not promoted`, `the group vector at group+0x0c/+0x10 is dereferenced without a null group check, exactly as the native body does`, `the row gap global at 0x01486110 is modelled as a float whose runtime value is not established`, `the semantic identity of the feature id 0x05d3f56b is inferred from the call shape only`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The element vtable owner behind slot +0x38 and +0x6c is unattributed in the live database.
- The feature query port 0x008105b0 and the distinct row port 0x005c2aa0 are opaque seams and are not promoted.
- The group pointer at +0x6c is dereferenced without a null check, exactly as the native body does.
- The row gap global at 0x01486110 is modelled as a float whose runtime value is not established.
- The semantic identity of the feature id 0x05d3f56b is inferred from the call shape only.
- What the distinct row port 0x005c2aa0 counts
- What the feature id 0x05d3f56b identifies and which subsystem answers the query
- What the group byte at +0x70 means and how it relates to the group vector span
- Whether a null group at +0x6c is reachable in practice, since the native body does not check it
- Who owns the element vtable slots +0x38 and +0x6c
- gate-palette-row-layout-runtime-group-and-feature-values
- runtime validation not performed; static decompilation and disassembly only
- the element vtable owner behind slot +0x38 and +0x6c is unattributed in the live database
- the feature query port 0x008105b0 and the distinct row port 0x005c2aa0 are opaque seams and are not promoted
- the group vector at group+0x0c/+0x10 is dereferenced without a null group check, exactly as the native body does
- the row gap global at 0x01486110 is modelled as a float whose runtime value is not established
- the semantic identity of the feature id 0x05d3f56b is inferred from the call shape only
