# Validation 0x00b5b880

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `NOT_AVAILABLE` | `none` | the xref export records no call edge out of this target and no listing is available; neither call oracle exists, so there is nothing to agree or disagree with; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00b5b880; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `NOT_AVAILABLE` | `none` | no independent data-reference evidence exists for this target: the xref export records 0 and no complete listing is available |
| FIELDS/OFFSETS | `WARN` | `partial` | 2 source field-offset declaration(s) (field pending, field request_kind) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `WARN` | `partial` | source constants are present and no machine listing is collected for this target, so they cannot be corroborated |
| CONTROL FLOW | `NOT_AVAILABLE` | `none` | no machine control-flow evidence exists for this target: the bridge never populates the dispatch field and no complete listing is collected |
| VIRTUAL DISPATCH | `NOT_AVAILABLE` | `none` | no machine dispatch evidence is collected for this target; the xref export records 0 vtable reference(s) and the record associates 1 vtable(s), which are not independent of each other |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 3 of 8 static checks evaluated, 1 passed, 5 had no evidence to evaluate; 8 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 8 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `PERSISTED`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `e6891309403c1b942681732b5b4fb8b58314e2a9918a0615660b1b7dc89d3201`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d7c3c5fad8528595cd0aae15d2027446eb239a7d48f57aea9f7de63247ccbcb0`
- Pack digest quoted by the briefing: `e6891309403c1b942681732b5b4fb8b58314e2a9918a0615660b1b7dc89d3201`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Observe concrete strategy reachability and first-request-wins state transitions; runtime validation is not run.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Observe concrete strategy reachability and first-request-wins state transitions; runtime validation is not run.
- concrete runtime owners and values remain unresolved
