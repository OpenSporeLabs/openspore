# Validation 0x005182f0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 69-instruction listing name the same 2 direct transfer target(s); 3 intra-procedural jump(s) target inside the recovered body span 0x005182f0..0x005183b0 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x0051831e, 0x00518327, 0x005183ad; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 6 outgoing call edge row(s) over 2 distinct address(es) for 0x005182f0; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 69-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field pass_014, vtable_000 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it; the 1 displacement(s) in that same span are grounded within the machine-derived receiver bounds (0x14), so it is the name alone that is uncorroborated |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (69 of 69 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 10 conditional branch target(s) in the complete 69-instruction listing lie inside the recovered body span 0x005182f0..0x005183b0, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 69-instruction body names 1 indirect transfer(s): 0x0051830c dispatches slot 0x44 through the table word in EDX; the machine parse consumed 69 of 69 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x44, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'std::uint32_t': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 69-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `e8ae966b465768720d44196cfb884233909ab110164ed5381980150fd61343a8`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8c57b2c1581a6167409d206ffcea4e4151b49c3050ee12e1b82b896cbb8a59ee`
- Pack digest quoted by the briefing: `e8ae966b465768720d44196cfb884233909ab110164ed5381980150fd61343a8`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Pass field semantics are inferred from 0x00517430, which increments and wraps the counter at 4; that body is owned elsewhere and is not reconstructed here.`, `The 12 attempt limit is a static property; the runtime distribution of the pass field at the limit is not established.`, `The vtable cluster at 0x013f1a30 is unattributed in docs/analysis/vtables.json, so slot 25 is bound to this body by the data pointer alone.`, `The widened 0 and 1 on the short paths follow the repository convention rather than a literal 32 bit store in the original.`, `gate-skin-painter-brush-pass-runtime-probe-and-step-semantics`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Pass field semantics are inferred from 0x00517430, which increments and wraps the counter at 4; that body is owned elsewhere and is not reconstructed here.
- The 12 attempt limit is a static property; the runtime distribution of the pass field at the limit is not established.
- The vtable cluster at 0x013f1a30 is unattributed in docs/analysis/vtables.json, so slot 25 is bound to this body by the data pointer alone.
- The widened 0 and 1 on the short paths follow the repository convention rather than a literal 32 bit store in the original.
- What the graphics probe query at slot +0x44 actually asks
- What the pass field at +0x14 enumerates and which values other than 0, 2 and 3 occur
- What the step port 0x00517430 does per call and how it wraps the counter at 4
- Which class owns the vtable cluster at 0x013f1a30
- Why the attempt limit is 12 and what happens at the limit with a nonzero pass
- gate-skin-painter-brush-pass-runtime-probe-and-step-semantics
