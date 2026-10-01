# Validation 0x0059d110

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b03/editor_anim_world_get_creature_position.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 43-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 43-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x8, 0x38), all of which the record accounts for or the listing is the better witness on; the 43-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=43, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x8, 0x38) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x38), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0x8), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (43 of 43 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 43-instruction listing lie inside the recovered body span 0x0059d110..0x0059d175, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 43-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `982c182765a23a1e698387cefd8edb34e95e21fedfc72cfd101debeea2b6e1d2`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8261c52593cf94b72ff06a6dbad03fc8178f0d90f76c4fcc4ad1c4f9577e272d`
- Pack digest quoted by the briefing: `982c182765a23a1e698387cefd8edb34e95e21fedfc72cfd101debeea2b6e1d2`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A trace must confirm the +0x0c sentinel identity, i.e. that the receiver's +0x0c really is the map's end node in a live instance. This is derived from the find port's source rather than observed at runtime.`, `A trace with a concrete receiver is required before the creature id space can be characterised, and therefore before the 18 unchecked call sites can be assumed safe.`, `No original-process trace exists for this function. Static analysis cannot show whether the mpAnimWorld gate is ever false in a live editor session, or how often the key-absent case occurs.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A trace must confirm the +0x0c sentinel identity, i.e. that the receiver's +0x0c really is the map's end node in a live instance. This is derived from the find port's source rather than observed at runtime.
- A trace with a concrete receiver is required before the creature id space can be characterised, and therefore before the 18 unchecked call sites can be assumed safe.
- Is the coordinate space of AnimatedCreature::mPosition world or model-local? The SDK does not say, and nothing in this body resolves it.
- Is there a sibling writer (a SetTargetPosition-shaped method at 0x59CF00) that this reader is the inverse of? Plausible from the signature but unverified here.
- No original-process trace exists for this function. Static analysis cannot show whether the mpAnimWorld gate is ever false in a live editor session, or how often the key-absent case occurs.
- The original method name. cEditorAnimWorld declares five methods with address pairs and 0x0059d110 matches none of them, so the routine is either undeclared in the SDK or inlined out of a template. No name is claimed.
- What are the 13 undisassembled call sites doing with the result, in particular the one at 0x0063a9ec that Ghidra does not attribute to any function?
- Why are only some of the 18 call sites checking the return value, and what do the unchecked ones do with a stale out buffer? The body guarantees the buffer is untouched on failure, but the callers' pre-initialisation was not verified.
