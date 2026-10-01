# Validation 0x00d2e340

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | the derived ABI record abstained (ABI_UNKNOWN): no_discriminator: no stack-argument read and no positive receiver evidence |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00d2e340; 25 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `WARN` | `partial` | the complete 2-instruction listing names 1 data address(es) (0x169e370) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 2-instruction listing names no memory operand through any register at all and it was consumed in full by the machine parse (declared_count=2, degraded=false, unparsed=0), which is the evidence that this function performs no field access; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'OpaqueCreatureGameData*' and the machine return state is WIDTH_4_IN_EAX: the complete 2-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7c5bc4f83d208f93e4cee918dab39bc98eea9a6e54d5e821024136f72ef9d76a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `89f2d58c7334c3dc6ddda2a36b521392ff413203c9f6b9ae93ab180e40a73d4a`
- Pack digest quoted by the briefing: `7c5bc4f83d208f93e4cee918dab39bc98eea9a6e54d5e821024136f72ef9d76a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process accessor trace or runtime validation has been run.`, `Observe the object at 0x0169e370 and its concrete initialization in an original process.`, `Resolve the concrete caller-side type and lifetime contract before promoting the opaque object model.`, `gate-creature-game-data-get-00d2e340`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original-process accessor trace or runtime validation has been run.
- Observe the object at 0x0169e370 and its concrete initialization in an original process.
- Resolve the concrete caller-side type and lifetime contract before promoting the opaque object model.
- gate-creature-game-data-get-00d2e340
- runtime validation not run
