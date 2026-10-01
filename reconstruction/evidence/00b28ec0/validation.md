# Validation 0x00b28ec0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg20_persistence_boundary/persistence_boundary.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 403-instruction listing names 12 data address(es) (0x13cc3e0, 0x13cc55c, 0x13eb844, 0x13eb90c, 0x13eb938, 0x13ec458, 0x143e774, 0x145fa98, 0x145faa8, 0x1654c00, 0x1897c18, 0x1a0219e) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 7 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (403 of 403 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 24 conditional branch target(s) in the complete 403-instruction listing lie inside the recovered body span 0x00b28ec0..0x00b294a5, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 403-instruction body names 16 indirect transfer(s): 0x00b28f4e dispatches slot 0x14 through the table word in EDX; 0x00b28fd7 is INDIRECT_NON_VTABLE; 0x00b29055 dispatches slot 0xc0 through the table word in EDX; 0x00b290a6 dispatches slot 0xc0 through the table word in EDX; 0x00b290e5 dispatches slot 0x4 through the table word in EAX; 0x00b29153 is INDIRECT_NON_VTABLE; 0x00b2916f is INDIRECT_NON_VTABLE; 0x00b29323 dispatches slot 0x0 through the table word in EAX; 0x00b29366 dispatches slot 0x48 through the table word in EDX; 0x00b29371 dispatches slot 0x20 through the table word in EAX; 0x00b2937a dispatches slot 0x18 through the table word in EDX; 0x00b293b3 dispatches slot 0x2c through the table word in EDX; 0x00b293c0 dispatches slot 0x1c through the table word in EDX; 0x00b293c9 dispatches slot 0x8 through the table word in EDX; 0x00b2942d dispatches slot 0x14 through the table word in EDX; 0x00b29436 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 403 of 403 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 16, so the dispatch is visible in the machine listing but is not proven: 3 of the 16 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x00b28fd7, 0x00b29153, 0x00b2916f), so the dispatch's identity is not established: the target is the memory operand [EAX*0x4 + 0xb294a8], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 2 passed, 4 had no evidence to evaluate; 14 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 14 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `3369fb8027ec0ee8b4b154cd76d0eff0153d80a99e8e52ab503a6692f9252e7d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `fc82b45bfb8192af846dee7372ccc63ae0954f943e8527b47a4ab79e640750f3`
- Pack digest quoted by the briefing: `3369fb8027ec0ee8b4b154cd76d0eff0153d80a99e8e52ab503a6692f9252e7d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-profile-persistence-candidate`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- candidate marker and completion-service runtime outcomes
- commit, rollback, and atomicity are not established
- gate-profile-persistence-candidate
- outer save envelope and post-call checks are outside this boundary
- species, profile, and mode target ownership
