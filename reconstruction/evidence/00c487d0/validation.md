# Validation 0x00c487d0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00c487d0-slot41-scope-exchange/slot41_scope_exchange_00c487d0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 96-instruction listing name the same 9 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x00c487d0..0x00c488f1 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00c4881a, 0x00c488b0; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 10 outgoing call edge row(s) over 9 distinct address(es) for 0x00c487d0; 85 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 10 outgoing call edge row(s) and 9 distinct callee(s) the export records; 9 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00423650, 0x006b5060, 0x006b5240, 0x006b55c0, 0x00aed4d0, 0x00c451e0, 0x00c452a0, 0x01021260, 0x01021300; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 10 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 2 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 96-instruction listing names 1 data address(es) (0x016e0d08); the data-reference artifact is read whole and records 4 reference row(s) out of this body covering every address under review, with access mode(s) read=4 |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 23 member(s) (begin, dispatch1_receiver, dispatch2_receiver, dispatch_accessor1_args) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 96-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=96, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x0, 0x17c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x0, 0x17c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (96 of 96 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 96-instruction listing lie inside the recovered body span 0x00c487d0..0x00c488f1, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 96-instruction body names 3 indirect transfer(s): 0x00c487e1 dispatches slot 0xa4 through the table word in EAX; 0x00c4887b dispatches slot 0x24 through the table word in EAX; 0x00c48891 dispatches slot 0xc through the table word in EAX; the machine parse consumed 96 of 96 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 96-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 5 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `bd6af19adeb37cea21b0b9ab3dc3983507790b30fb78db418671ed33a7bc70dc`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `aacab4b09b3b712a68239e9252fc75118aae2b3e7241858a665105590fd33082`
- Pack digest quoted by the briefing: `bd6af19adeb37cea21b0b9ab3dc3983507790b30fb78db418671ed33a7bc70dc`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the two words of the descriptor at entry_ESP-0x08 initialised anywhere? The body never initialises them and never reads them before 0x006b55c0/dispatch calls that may write through the address at entry_ESP-0x14.
- Does this function really return void? The abi artifact classes the last EAX write as aggregate_unknown and the body computes nothing after POP EBX, so no return type is claimed.
- Is the 5/4 dispatch arity split correct, or is it 6/3? No arity is OBSERVED; only the sum is. This is the first claim to move if a differential run disagrees.
- The 0x01409b1c string constant the wrapper constructor stores at +0x08 and the wide-data source the wrapper accessor eventually yields are untraced.
- The 20+ callers (0x00c48d40, 0x00c48db0, 0x00c48e00, 0x00c4c4b0, 0x00c4ea70, 0x00c4ef00, 0x00c4ef90, 0x00c4fa40, 0x00c4fc00, 0x00c4fe60, 0x00c52160, 0x00c521c0, 0x00c53720, 0x00c552d0, 0x00c55330, ...) are unreconstructed; a caller's use of EAX is the cheapest way to settle the return type and could also cross-check the arity split.
- What are the two 0x00aed4d0 accessors? Each returns an object whose first word indexes a table, and each result is used exactly once as a dispatch receiver, but nothing identifies them. 0x00aed4d0 itself lazily builds a singleton from `FUN_00f473a0(4,"Simulator",0,0,0,0)` with vtable PTR_LAB_0145c0b4.
- What is 0x016e0d08, and what do ScopeState::field_18 and +0x48 mean? The save/publish/restore pattern is observed; the identity is not, and it is not Simulator::sSpacePlayerData.
- What is receiver+0x17c? The listing proves only that it substitutes the receiver when non-zero and becomes dispatch argument 5.
- What is the receiver's class, and what does its table word at displacement 0xa4 do? The body only proves the displacement and the zero-stack-argument __thiscall shape.
- What is the word at player data + 0x13c, and what does dispatch argument 4 do with it?
