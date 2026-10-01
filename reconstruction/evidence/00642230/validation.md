# Validation 0x00642230

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_sporepedia_safe_wave10/sporepedia_safe_wave10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 257-instruction listing name the same 10 direct transfer target(s); 4 intra-procedural jump(s) target inside the recovered body span 0x00642230..0x0064252b are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x006422e0, 0x006422f8, 0x006424f8, 0x00642510; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 14 outgoing call edge row(s) over 10 distinct address(es) for 0x00642230; the source span names 10 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 257-instruction listing names 12 data address(es) (0x15da80c, 0x15da810, 0x15da814, 0x15da818, 0x15da8e0, 0x15da8e4, 0x15da8e8, 0x15da8ec, 0x15dab18, 0x15dab1c, 0x15dab20, 0x15dab24) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 17 member(s) (capacity, entries_40, first, flag_24) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 257-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=257, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x2c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 9 displacement(s) (0x0, 0x2c, 0x40, 0x44, 0x6c, 0x90, 0x91, 0x92, 0x94), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 8 of those (0x0, 0x40, 0x44, 0x6c, 0x90, 0x91, 0x92, 0x94) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (257 of 257 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 21 conditional branch target(s) in the complete 257-instruction listing lie inside the recovered body span 0x00642230..0x0064252b, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 257-instruction body names 7 indirect transfer(s): 0x00642280 dispatches slot 0xc through the table word in EDX; 0x00642290 dispatches slot 0x0 through the table word in EDX; 0x0064229e dispatches slot 0xc through the table word in EDX; 0x006422b3 dispatches slot 0x0 through the table word in EDX; 0x006422eb dispatches slot 0xb4 through the table word in EDX; 0x0064235a dispatches slot 0x4 through the table word in EDX; 0x00642369 dispatches slot 0x4 through the table word in EDX; the machine parse consumed 257 of 257 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 7. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x0, 0x4, 0xc, 0xb4, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 257-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 9 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 9 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `6876609c3230f877ec8566a8cf110624555e9f6068d64d6333da640d85a34561`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3e4ed6eb93aef40157a291d8460db80c8e317dba4965ff3761870cf8ec99648e`
- Pack digest quoted by the briefing: `6876609c3230f877ec8566a8cf110624555e9f6068d64d6333da640d85a34561`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Ten callees are modelled as opaque ports and none is promoted to a function record.`, `The asset apply property vtable slot owner at +0xb4 is unattributed in the live database.`, `The clear port count argument is computed as last minus last, which is statically zero; the runtime meaning of a zero count is unverified.`, `The entry vector rewind arithmetic and the inline marker invariant are static only.`, `The selectors 0x0670da17 and 0x03c609f8 and the three tag globals at 0x015da8e0, 0x015dab18 and 0x015da80c are undecoded.`, `The signed maximum comparison depends on runtime supplied entry values.`, `gate-sporepedia-asset-load-runtime-selectors-and-tag-globals`, `runtime validation not performed; static decompilation and disassembly only`, `ten callees are modelled as opaque ports and none is promoted to a function record`, `the asset apply property vtable slot owner at +0xb4 is unattributed in the live database`, `the clear port count argument is computed as last minus last, which is statically zero; the runtime meaning of a zero count is unverified`, `the entry vector rewind arithmetic and the inline marker invariant are static only`, `the selectors 0x0670da17 and 0x03c609f8 and the three tag globals are undecoded`, `the signed maximum comparison against max_6c depends on the entry values, which are runtime supplied`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Ten callees are modelled as opaque ports and none is promoted to a function record.
- The asset apply property vtable slot owner at +0xb4 is unattributed in the live database.
- The clear port count argument is computed as last minus last, which is statically zero; the runtime meaning of a zero count is unverified.
- The entry vector rewind arithmetic and the inline marker invariant are static only.
- The selectors 0x0670da17 and 0x03c609f8 and the three tag globals at 0x015da8e0, 0x015dab18 and 0x015da80c are undecoded.
- The signed maximum comparison depends on runtime supplied entry values.
- What the byte-span rewind of the entry vector end is intended to discard
- What the selectors 0x0670da17 and 0x03c609f8 identify
- What the three tag globals at 0x015da8e0, 0x015dab18 and 0x015da80c encode
- What values the entry lookup returns and how the signed maximum is meant to be used
- Which class owns the asset apply property vtable slot +0xb4
- Why the clear port is called with a statically zero count and what the third argument means
- Why the gate lookup is called once per entry rather than once outside the loop
- gate-sporepedia-asset-load-runtime-selectors-and-tag-globals
- runtime validation not performed; static decompilation and disassembly only
- ten callees are modelled as opaque ports and none is promoted to a function record
- the asset apply property vtable slot owner at +0xb4 is unattributed in the live database
- the clear port count argument is computed as last minus last, which is statically zero; the runtime meaning of a zero count is unverified
- the entry vector rewind arithmetic and the inline marker invariant are static only
- the selectors 0x0670da17 and 0x03c609f8 and the three tag globals are undecoded
- the signed maximum comparison against max_6c depends on the entry values, which are runtime supplied
