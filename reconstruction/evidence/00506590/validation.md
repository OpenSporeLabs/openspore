# Validation 0x00506590

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 94-instruction listing name the same 2 direct transfer target(s); 3 intra-procedural jump(s) target inside the recovered body span 0x00506590..0x005066c4 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x005065d5, 0x0050661a, 0x0050665f; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 6 outgoing call edge row(s) over 2 distinct address(es) for 0x00506590; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 94-instruction listing names 4 data address(es) (0x13eecd8, 0x13f116c, 0x1471064, 0x1485720) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 9 member(s) (scale_020, scale_024, scale_028, scale_02c) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 94-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=94, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 0 displacement(s) to the receiver as proven (none) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 7 displacement(s) (0x10, 0x14, 0x1c, 0x20, 0x24, 0x2c, 0x30), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 7 of those (0x10, 0x14, 0x1c, 0x20, 0x24, 0x2c, 0x30) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (94 of 94 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 94-instruction listing lie inside the recovered body span 0x00506590..0x005066c4, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 94-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is SRET_SUSPECTED and the source span declares return type 'void': the ABI envelope records a hidden-pointer return hypothesis (suspected), so the return register holds an address rather than the value and no width read off it would be a claim about the wrong value. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 5 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `0ad8da6ece210aed1973a6e1e50afbb5e09a69c3ef138d7ad68be01d2095c52c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6aa910c99fb891c0e1bdc6657afce9b406bd4dd15e67a6682d495a0a8f1423b0`
- Pack digest quoted by the briefing: `0ad8da6ece210aed1973a6e1e50afbb5e09a69c3ef138d7ad68be01d2095c52c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Receiver class identity is taken from the triage record /Spore/Skinner/cSkinPainter; offsets 0x00..0x0f and above 0x30 are not exercised.`, `The 0x64 size class and the "Skinner" tag at 0x013f116c are inferred from the call shape, not from an SDK signature.`, `The neighbouring 0x005171b0 label is repaired-contained inside this body and no symbol is claimed for it.`, `The two unresolved callees at 0x00f473a0 and 0x005288f0 are owned elsewhere and remain runtime gated.`, `gate-skin-painter-setup-runtime-acquire-and-scale-values`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Receiver class identity is taken from the triage record /Spore/Skinner/cSkinPainter; offsets 0x00..0x0f and above 0x30 are not exercised.
- The 0x64 size class and the "Skinner" tag at 0x013f116c are inferred from the call shape, not from an SDK signature.
- The neighbouring 0x005171b0 label is repaired-contained inside this body and no symbol is claimed for it.
- The two unresolved callees at 0x00f473a0 and 0x005288f0 are owned elsewhere and remain runtime gated.
- What reads the five scale floats written at +0x20 through +0x30
- What the 0x64 size class and the "Skinner" tag at 0x013f116c select in the allocator
- Whether the receiver offsets 0x00..0x0f and above 0x30 are initialised by the caller
- Whether the three texture painters are ever replaced or re-created later
- Who owns the allocator 0x00f473a0 and the constructor 0x005288f0
- gate-skin-painter-setup-runtime-acquire-and-scale-values
