# Validation 0x01021240

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-01021240-active-star-record/active_star_record_accessor.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | the derived ABI record abstained (ABI_UNKNOWN): no_discriminator: no stack-argument read and no positive receiver evidence |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 8-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x01021240; 117 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the machine-vs-machine rule: all 1 data address(es) the source span names are recorded as Ghidra data references out of this body, and the complete 8-instruction listing corroborates 1 of them; the artifact records 1 read across 1 reference row(s)the data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 1 data reference row(s) out of 0x01021240 over 1 distinct address(es); 1 of them name writable storage (0x016dda8c), which is where a mutable global can live; segment breakdown: .data=1; access modes recorded: 1 read;  |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (8 of 8 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 8-instruction listing lie inside the recovered body span 0x01021240..0x01021252, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 8-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'std::uint32_t' and the machine return state is WIDTH_4_IN_EAX: the complete 8-instruction listing writes EAX at a determinate 4-byte width before all 2 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7a20f4293c65ba011a1b9942276e9273c15fd53587f219dc7c746c2ecfe1af18`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `bb517eba42876df3dd17b8fe20d639969aa1e0204e5cdbf7d5cbd352583b351c`
- Pack digest quoted by the briefing: `7a20f4293c65ba011a1b9942276e9273c15fd53587f219dc7c746c2ecfe1af18`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Simulator__sSpacePlayerData is defined by both this package and src/reconstruction/pkg01_roots/space_player_data_accessors.cpp. If the integrator merges them into one target, exactly one definition must survive; that reconciliation was left to the integrator.
- The caller's domain is not established. 74 caller functions and 100 xref sites are consistent with a widely-used identity accessor, but fan-in alone does not show what any of them do with the value, and no caller was decompiled under this run's bounded budget.
- The calling convention is undetermined by the body. __cdecl is declared because it is the least committal zero-parameter leaf shape and agrees with the caller-owned cleanup the ABI record states as INFERRED, but __stdcall with zero callee cleanup is byte-identical here and nothing in this body distinguishes them.
- Whether the returned word is genuinely an intrusive_ptr<Simulator::cStarRecord> payload, as the SDK offset column suggests, or a differently-typed 32-bit word that merely occupies 0x48, is not settled by this body's own listing. The reconstruction claims the displacement and the zero-guard and deliberately says nothing about what the word addresses.
