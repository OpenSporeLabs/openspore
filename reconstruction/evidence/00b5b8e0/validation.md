# Validation 0x00b5b8e0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `NOT_AVAILABLE` | `none` | the xref export records no call edge out of this target and no listing is available; neither call oracle exists, so there is nothing to agree or disagree with; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00b5b8e0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `NOT_AVAILABLE` | `none` | no independent data-reference evidence exists for this target: the xref export records 0 and no complete listing is available |
| FIELDS/OFFSETS | `WARN` | `partial` | 3 source field-offset declaration(s) (field committed_b, field pending, field request_kind) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
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
- Content SHA-256: `a90de696617f81caeef5257713b67ee8ee5f404624a6c2efa1a357f3fbbbb41c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `695088da3361f235ad424ac8c88774a1a31296dd97b396cb1192b82c215828cd`
- Pack digest quoted by the briefing: `a90de696617f81caeef5257713b67ee8ee5f404624a6c2efa1a357f3fbbbb41c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Observe concrete strategy commit reachability and whether sentinel commits occur in the original process; runtime validation is not run.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Observe concrete strategy commit reachability and whether sentinel commits occur in the original process; runtime validation is not run.
- concrete runtime owners and values remain unresolved
