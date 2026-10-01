# Validation 0x00aeb720

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg12_space/space_comm_event.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 22-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 7 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (22 of 22 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 22-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 22-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `cd045afc77cb45f4caa0ebbd5e6eb45f1a3f998873a44375be79a14b41f7d0f3`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `c4a5a11390469a7c79eb6e2cf35742eef4587f3e2cc5b2ea97b74396ba9734a3`
- Pack digest quoted by the briefing: `cd045afc77cb45f4caa0ebbd5e6eb45f1a3f998873a44375be79a14b41f7d0f3`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-space-comm-event-lifecycle`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does every real caller provide a non-null manager and creator result?
- What do the six opaque payload words mean at each caller, given pointer-like and event-code words are passed without conversion?
- What is the exact private source-level name of this convenience wrapper?
- What version skew maps the SDK CreateSpaceCommEvent and HandleSpaceCommAction names to nearby addresses?
- Which cCommManager current/list offsets are authoritative across the SDK, Ghidra type, and direct creator accesses?
- creator and dispatcher failure behavior
- gate-space-comm-event-lifecycle
- manager layout conflict
- payload word meanings
- private source name
