# Validation 0x005772b0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b03/editor_release_preview_model.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 36-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 36-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0xf0), all of which the record accounts for or the listing is the better witness on; the 36-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=36, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0xf0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0xf0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (36 of 36 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 36-instruction listing lie inside the recovered body span 0x005772b0..0x0057730b, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 36-instruction body names 2 indirect transfer(s): 0x005772ca dispatches slot 0x16c through the table word in EDX; 0x00577307 dispatches slot 0x170 through the table word in EDX; the machine parse consumed 36 of 36 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `36ccd9ab0bd9ab7b4fc92df00b5cc5d14f36dfcf41eb0ce970dc58bef8f2c055`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `a3ede89cb7fa75e7579ed504a47eab210d022148132bac5610cc3beecd883627`
- Pack digest quoted by the briefing: `36ccd9ab0bd9ab7b4fc92df00b5cc5d14f36dfcf41eb0ce970dc58bef8f2c055`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A trace must confirm that IModelWorld slot +0x170 does not itself decrement the counter, since this body reaches it with the counter still at 1 (or 0).`, `A trace with a concrete editor receiver is required before the +0xf0 member and the +0xe9 guard can be given semantic names.`, `No original-process trace has ever been captured for 0x005772b0, so every claim here is static. A differential trace must confirm that mpWorld is non-null whenever the +0xf0 member is non-null, because both virtual calls dereference model->mpWorld twice with no null check.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A trace must confirm that IModelWorld slot +0x170 does not itself decrement the counter, since this body reaches it with the counter still at 1 (or 0).
- A trace with a concrete editor receiver is required before the +0xf0 member and the +0xe9 guard can be given semantic names.
- Is the +0xf0 model a 'preview', 'ghost' or 'highlight' model? The setup writes an all-ones mColor and a bitmask derived from an index-returning world call, which is consistent with several editor overlay uses, and nothing observed here decides between them.
- Is the counter at +0x40 really Model::mnRefCount in the original build, or a per-world counter that happens to share the offset? The five-way offset agreement makes this unlikely but nothing at runtime confirms it.
- No original-process trace has ever been captured for 0x005772b0, so every claim here is static. A differential trace must confirm that mpWorld is non-null whenever the +0xf0 member is non-null, because both virtual calls dereference model->mpWorld twice with no null check.
- What does bit 31 of Model::mFlags (0x80000000) mean? It is undocumented in the SDK Model.h flag enum and in cMWModelInternal::field_138, and no writer of that specific bit was located.
- What is this routine called in the original source? No string, symbol, PDB reference or vtable entry in the binary names it, and the +0xe9 guard is a bare byte with no SDK counterpart.
- Which concrete IModelWorld implementation receives the +0x16c and +0x170 calls? The vtable is a runtime object and no static table was located for these two sites.
- Why is EBX saved only on the FinalRelease path? The body never reads EBX for any other purpose, so the save is a register-allocation artefact of the compiler rather than an invariant.
