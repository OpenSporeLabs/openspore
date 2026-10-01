# Validation 0x00c1c5c0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_c4_creature_wave3/creature_wave3.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 196-instruction listing name the same 3 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x00c1c5c0..0x00c1c8db are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00c1c791, 0x00c1c891; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 4 outgoing call edge row(s) over 3 distinct address(es) for 0x00c1c5c0; 75 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 4 outgoing call edge row(s) and 3 distinct callee(s) the export records; 3 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00ac4570, 0x00c0ce80, 0x00f47380; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 4 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 196-instruction listing names 6 data address(es) (0x13ef480, 0x146a32c, 0x150c900, 0x168d910, 0x168d914, 0x168d918) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 4 member(s) (release_handle, x, y, z) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 196-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=196, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0xc0, 0x2b0, 0xf98) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 6 displacement(s) (0xc0, 0x2a0, 0x2b0, 0x330, 0xbb0, 0xf98), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 3 of those (0x2a0, 0x330, 0xbb0) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (196 of 196 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 10 conditional branch target(s) in the complete 196-instruction listing lie inside the recovered body span 0x00c1c5c0..0x00c1c8db, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 196-instruction body names 2 indirect transfer(s): 0x00c1c604 dispatches slot 0x2c through the table word in EAX; 0x00c1c860 dispatches slot 0xdc through the table word in EDX; the machine parse consumed 196 of 196 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the ABI record names ST0 as the return register; the x87 stack top: the machine fixes where the value travels and not whether the source said float or double, so the machine fixes where the value travels and not the C type, and no width can be claimed. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 5 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `deab567b6f14ae2ff407dde2b964b3ed0d931c3162dd291a0d09beea2bd3b7d7`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `93ad6b3532095358989e37540434b63e3f6f967d58c81249db2496bce2e4d87e`
- Pack digest quoted by the briefing: `deab567b6f14ae2ff407dde2b964b3ed0d931c3162dd291a0d09beea2bd3b7d7`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Exercise a NaN basis and a zero-length basis in the original to confirm the recorded NaN propagation and the absence of a length guard.`, `No original-process trace, differential run under Wine, or runtime validation has been performed.`, `Observe a real vtable+0xDC submission to learn whether the request pointer escapes and whether the handle header word at handle-0x04 is a reference count.`, `Observe the 0x00ac4570 container at creature+0xBC0 to confirm the 60-byte element semantics.`, `Observe the concrete creature+0x2B0, +0x2A0 and +0x330 field semantics in an original process.`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Exercise a NaN basis and a zero-length basis in the original to confirm the recorded NaN propagation and the absence of a length guard.
- No original-process trace, differential run under Wine, or runtime validation has been performed.
- Observe a real vtable+0xDC submission to learn whether the request pointer escapes and whether the handle header word at handle-0x04 is a reference count.
- Observe the 0x00ac4570 container at creature+0xBC0 to confirm the 60-byte element semantics.
- Observe the concrete creature+0x2B0, +0x2A0 and +0x330 field semantics in an original process.
- runtime validation not run
