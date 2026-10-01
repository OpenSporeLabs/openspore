# Validation 0x00ba9370

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg11_sim_core/empire_lookup.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 23-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 5 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (23 of 23 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 23-instruction listing lie inside the recovered body span 0x00ba9370..0x00ba93a8, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 23-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `83d7bbaf683d3c0c6a6d00b7554dda6dd54c9bd2803ae89cac24cd2c29dda970`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d9a4c6e72c125c433a3c2de6bf908b957d2c5b4fd11d989b979f314e7379c35b`
- Pack digest quoted by the briefing: `83d7bbaf683d3c0c6a6d00b7554dda6dd54c9bd2803ae89cac24cd2c29dda970`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-star-manager-and-empire-map-lifecycle`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Can the alternate manager be null while a non-invalid current-player ID is present?
- Does every map entry's key remain synchronized with the payload's cEmpire identity at +0x84?
- Is the alternate root value-equal to the canonical star-manager slot for the full lifecycle?
- The imported Ghidra cEmpire field label at +0x84 is not treated as authoritative for this wrapper.
- What are the ownership and teardown rules for the borrowed empire pointer?
- What code publishes, replaces, or clears the alternate star root at 0x0167eae4?
- alternate star root publisher
- borrowed pointer lifetime
- concurrent map mutation
- gate-star-manager-and-empire-map-lifecycle
- map key and empire identity synchronization
