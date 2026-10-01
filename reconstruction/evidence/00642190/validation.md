# Validation 0x00642190

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 46-instruction listing name the same 2 direct transfer target(s), including a target reached only by a jump; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00642190; 5 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 2 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 46-instruction listing names 3 data address(es) (0x13ff648, 0x1462738, 0x1462748) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field access_1c, access_20, access_3c, access_70 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (46 of 46 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 7 conditional branch target(s) in the complete 46-instruction listing lie inside the recovered body span 0x00642190..0x00642205, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 46-instruction body names 5 indirect transfer(s): 0x006421b3 dispatches slot 0x4 through the table word in EAX; 0x006421c1 dispatches slot 0x4 through the table word in EAX; 0x006421e4 dispatches slot 0x4 through the table word in EAX; 0x006421f2 dispatches slot 0x4 through the table word in EAX; 0x00642200 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 46 of 46 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 5. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 3 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x4, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 46-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 5 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `11c0aab85dc03f4b2388c159d2a8ff612814412a1b452233b1e5bd86e6c1b9ea`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6402e24372a93d0afb5116d818c2dc91e8362ff25dd7475a2f858f01f8b247db`
- Pack digest quoted by the briefing: `11c0aab85dc03f4b2388c159d2a8ff612814412a1b452233b1e5bd86e6c1b9ea`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `The base destructor 0x006412a0 is a tail-transfer target and is not promoted; only its three vtable stores are modelled.`, `The free port 0x00f47380 is shared across the campaign and is not promoted here.`, `The handle release slots at asset-ref vtable +0x04 are opaque seams and are not promoted.`, `The invariant that keeps an inline vector from being freed is unverified at runtime.`, `The six vtable words are literal image addresses with no class attribution in the live database.`, `gate-sporepedia-asset-destroy-runtime-vtable-owners`, `runtime validation not performed; static decompilation and disassembly only`, `the base destructor 0x006412a0 is a tail-transfer target and is not promoted; only its three vtable stores are modelled in the default port`, `the free port 0x00f47380 is shared across the campaign and is not promoted here`, `the handle release slots at asset-ref vtable +0x04 are opaque seams and are not promoted`, `the inline marker comparison uses the word at +0x50 against the vector first word at +0x40; the invariant that keeps an inline vector from being freed is unverified at runtime`, `the six vtable words are literal image addresses with no class attribution in the live database`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The base destructor 0x006412a0 is a tail-transfer target and is not promoted; only its three vtable stores are modelled.
- The free port 0x00f47380 is shared across the campaign and is not promoted here.
- The handle release slots at asset-ref vtable +0x04 are opaque seams and are not promoted.
- The invariant that keeps an inline vector from being freed is unverified at runtime.
- The six vtable words are literal image addresses with no class attribution in the live database.
- What the base destructor 0x006412a0 does beyond its three vtable stores
- What the five handles at +0x1c, +0x20, +0x3c, +0x70 and +0x74 reference
- What the inline marker invariant at +0x50 is and who maintains it
- Whether the free at 0x00f47380 matches the allocator that produced the entry vector
- Which classes the six vtable words belong to
- gate-sporepedia-asset-destroy-runtime-vtable-owners
- runtime validation not performed; static decompilation and disassembly only
- the base destructor 0x006412a0 is a tail-transfer target and is not promoted; only its three vtable stores are modelled in the default port
- the free port 0x00f47380 is shared across the campaign and is not promoted here
- the handle release slots at asset-ref vtable +0x04 are opaque seams and are not promoted
- the inline marker comparison uses the word at +0x50 against the vector first word at +0x40; the invariant that keeps an inline vector from being freed is unverified at runtime
- the six vtable words are literal image addresses with no class attribution in the live database
