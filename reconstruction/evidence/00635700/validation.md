# Validation 0x00635700

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 30-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 2 distinct address(es) for 0x00635700; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 30-instruction listing names 4 data address(es) (0x13eb938, 0x13ec458, 0x13fe718, 0x13fe728) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field service_14, service_2c, slot_64, slot_68 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (30 of 30 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 30-instruction listing lie inside the recovered body span 0x00635700..0x0063575c, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 30-instruction body names 2 indirect transfer(s): 0x0063571c dispatches slot 0x4 through the table word in EAX; 0x0063572a dispatches slot 0x4 through the table word in EAX; the machine parse consumed 30 of 30 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2, so the dispatch is visible in the machine listing but is not proven: the source span states slot displacement(s) 0x4, 0x64, 0x68 and the machine reads 0x4, so the two disagree about which slot is dispatched |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'OpaqueImageArchive*' and the machine return state is WIDTH_4_IN_EAX: the complete 30-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 9 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 9 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `0bf85f649bb9c5499d46d15919b0825218111799d0eaee89d3866ac4af5c6951`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8531454be8616768a7bdd3e4fbec3c5255684aed9f753d7af4204a8d4715ffc6`
- Pack digest quoted by the briefing: `0bf85f649bb9c5499d46d15919b0825218111799d0eaee89d3866ac4af5c6951`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `The deallocation port 0x00f47380 is shared with other campaign packages and is not promoted here.`, `The four vtable words are literal image addresses with no class attribution in the live database.`, `The handle release slot at +0x04 and the service destructor 0x00811fe0 are opaque seams and are not promoted.`, `The higher bits of the deleting flag are not interpreted; only its low byte is read.`, `gate-image-archive-destructor-runtime-vtable-owners`, `runtime validation not performed; static decompilation and disassembly only`, `the deallocation port 0x00f47380 is shared with other campaign packages and is not promoted here`, `the deleting flag is a one word formal whose low byte is the only bit read; the higher bits are not interpreted`, `the four vtable words 0x013fe728, 0x013fe718, 0x013ec458 and 0x013eb938 are literal image addresses with no class attribution in the live database`, `the two handle release slots at handle+0x04 and the service destructor 0x00811fe0 are opaque seams and are not promoted`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The deallocation port 0x00f47380 is shared with other campaign packages and is not promoted here.
- The four vtable words are literal image addresses with no class attribution in the live database.
- The handle release slot at +0x04 and the service destructor 0x00811fe0 are opaque seams and are not promoted.
- The higher bits of the deleting flag are not interpreted; only its low byte is read.
- What the service subobjects at +0x14 and +0x2c own and what 0x00811fe0 destroys in them
- What the two handles at +0x64 and +0x68 reference
- What the upper bytes of the deleting flag mean, since only the low byte is read
- Which classes the vtables at 0x013fe728, 0x013fe718, 0x013ec458 and 0x013eb938 belong to
- Who supplies the deallocation in 0x00f47380 and whether it matches the module allocator
- gate-image-archive-destructor-runtime-vtable-owners
- runtime validation not performed; static decompilation and disassembly only
- the deallocation port 0x00f47380 is shared with other campaign packages and is not promoted here
- the deleting flag is a one word formal whose low byte is the only bit read; the higher bits are not interpreted
- the four vtable words 0x013fe728, 0x013fe718, 0x013ec458 and 0x013eb938 are literal image addresses with no class attribution in the live database
- the two handle release slots at handle+0x04 and the service destructor 0x00811fe0 are opaque seams and are not promoted
