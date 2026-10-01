# Validation 0x007e93d0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/wave6_engine_runtime/engine_runtime.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 42-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 4 outgoing call edge row(s) over 2 distinct address(es) for 0x007e93d0; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 42-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | 2 source field-offset declaration(s) (field first_command_line_copy_138, field second_command_line_copy_148) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (42 of 42 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 42-instruction listing lie inside the recovered body span 0x007e93d0..0x007e943e, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 42-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'void': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 5 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `5ea128365f64bf2249e155106f2060cdfd42e08fd15b4ae7e3a200cecc7aac51`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3ca2d8908cc3a7c36004e9f62fcc691a30b907d3f2f9689bb42ca57004ebe127`
- Pack digest quoted by the briefing: `5ea128365f64bf2249e155106f2060cdfd42e08fd15b4ae7e3a200cecc7aac51`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-plugin-command-line-string-lifecycle`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Can either helper mutate or invalidate either incoming source pointer before its scan or append?
- Does the imported CommandLine label accurately describe either UTF-16 input across every caller?
- What allocation, growth, and destruction behavior do the two helper ports retain in the original?
- What concrete relationship exists between the two incoming UTF-16 stack pointers across every caller?
- What concrete semantic values are stored at receiver+0x138 and receiver+0x148?
- What stable EAX value, if any, do callers consume after this wrapper?
- destination string ownership
- gate-plugin-command-line-string-lifecycle
- helper allocation and failure behavior
- semantic identity of both source strings
- stable return EAX contract
