# Validation 0x00b3d3a0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg01_roots/canonical_roots.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 2-instruction listing names 1 data address(es) (0x167eb0c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 2 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d99303ee74295799dfba477ab135ebe4c56d29eb2933e7eed721b4c69a36a77e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `7fe2faf1d3a3b742c04abeeaf00dec0cd0438d4ee9f844e6a295c0a0e36669b4`
- Pack digest quoted by the briefing: `d99303ee74295799dfba477ab135ebe4c56d29eb2933e7eed721b4c69a36a77e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No runtime trace establishes value equality with DAT_0167eae4 across the lifecycle; physical separation does not establish inequality of values.`, `No runtime trace establishes when DAT_0167eb0c is published, replaced, invalidated, cleared, or unpublished.`, `The borrowed return has no accessor-side generation, liveness, or teardown guarantee.`, `gate-space-root-publication`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the canonical and alternate star slot values equal at every live lifecycle point?
- Can consumers observe a null or stale returned pointer during a mode transition?
- No runtime trace establishes value equality with DAT_0167eae4 across the lifecycle; physical separation does not establish inequality of values.
- No runtime trace establishes when DAT_0167eb0c is published, replaced, invalidated, cleared, or unpublished.
- The borrowed return has no accessor-side generation, liveness, or teardown guarantee.
- What code publishes, replaces, or clears DAT_0167eb0c?
- What concrete object and vtable identity can the slot contain?
- Which owner controls the returned object's lifetime and teardown?
- borrowed-pointer lifetime
- concrete owner
- gate-space-root-publication
- publisher
- replacement order
- slot equality with alternate root
