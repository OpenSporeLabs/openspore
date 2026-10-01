# Validation 0x0045b150

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b00/registry_0045b150.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 65-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 10 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (65 of 65 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 65-instruction listing lie inside the recovered body span 0x0045b150..0x0045b200, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 65-instruction body names 1 indirect transfer(s): 0x0045b1c9 dispatches slot 0xc through the table word in EDX; the machine parse consumed 65 of 65 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f9f5dc9d4ab6d6e3be02c40680e44253837510ac258bab8312935455cd96bd76`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ed97b54d220f2a827a9e31073bd326c44a447a59158ceccc278cdfd7bdc0e984`
- Pack digest quoted by the briefing: `f9f5dc9d4ab6d6e3be02c40680e44253837510ac258bab8312935455cd96bd76`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists for 0x0045b150; every claim is static and the Cell stage has never been entered in any recorded run.`, `The 10 uninspected callers are static work and are listed in unresolved_questions rather than as a runtime gate.`, `The registry's runtime value and the map's own +0x0 field require a run to observe.`, `The vtable slot +0xc callee is the highest-value runtime unknown: it is the function's only side effect, and no static evidence constrains it.`, `Whether a live node can ever alias the free-list head, which would make a real hit silently skipped, can only be settled by instrumenting the map's insert path at runtime.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Can a live node ever equal the free-list head, which would make a real hit be silently skipped? Not reachable from the observed paths, but not proven unreachable in general.
- Is 0x0045b150 a vtable entry of the registry? No vtable was located and no pointer scan for this address was performed.
- Is 0x0045b6f0 a destructor or a free-list push? The free-list sentinel implies recycling, but the node's reuse policy is not established.
- No original-process trace exists for 0x0045b150; every claim is static and the Cell stage has never been entered in any recorded run.
- The 10 uninspected callers are static work and are listed in unresolved_questions rather than as a runtime gate.
- The other 10 of the 11 recorded callers were not disassembled. Whether any passes a key that is not an effect id -- and therefore whether the map is really an effect registry -- is not established.
- The registry's runtime value and the map's own +0x0 field require a run to observe.
- The vtable slot +0xc callee is the highest-value runtime unknown: it is the function's only side effect, and no static evidence constrains it.
- What does the payload's vtable slot +0xc do, and why does it take the literal 1? It is the only side effect this function produces and nothing in the binary or the SDK names it.
- What is the map's +0x0 field? All three functions read touch only +0x4, +0x8 and +0xc. An eastl::hash_map would have a count or a mask there; nothing observed uses it.
- What is the type behind 0x015d0c14? The file image holds zero, no vtable was located, and the SDK has no global manager matching this access pattern.
- Whether a live node can ever alias the free-list head, which would make a real hit silently skipped, can only be settled by instrumenting the map's insert path at runtime.
- Why does the bucket array have a sentinel entry at index count rather than storing the free-list head in a dedicated field? This is either an EASTL fixed-pool layout or a bespoke one, and static evidence does not say which.
