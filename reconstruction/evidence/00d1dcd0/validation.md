# Validation 0x00d1dcd0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_argscript_wave9/argscript_get_current_scope.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00d1dcd0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x130) and the 1 the complete 2-instruction listing names through ECX (0x130) are all within the machine-derived receiver bounds (0x130), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `3f303f89f9923f4abd8f43be7a7e780fdcf61024536bd6be2df03e201a286fed`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `4a42806ab5d6a0f4dfde622323aa960f71913df2feefdd327add64c0d2071465`
- Pack digest quoted by the briefing: `3f303f89f9923f4abd8f43be7a7e780fdcf61024536bd6be2df03e201a286fed`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `An empty scope returns a null begin word rather than a sentinel string; callers' null handling is unverified.`, `No original-process invocation or indirect-caller trace was captured.`, `Ownership and lifetime of the returned character pointer are unresolved; no reference count is taken or released.`, `The +0x130 string header layout (begin, end, capacity, allocator) is inferred from adjacent fields and is unverified at runtime.`, `gate-argscript-scope-string-header-layout`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- An empty scope returns a null begin word rather than a sentinel string; callers' null handling is unverified.
- Confirmed layout of the +0x130 string header and the +0x154 secondary string
- No original-process invocation or indirect-caller trace was captured.
- Ownership and lifetime of the returned character pointer are unresolved; no reference count is taken or released.
- Ownership of the returned scope pointer
- The +0x130 string header layout (begin, end, capacity, allocator) is inferred from adjacent fields and is unverified at runtime.
- Whether callers treat a null scope as valid
- Whether the +0x164/+0x168 state words gate scope validity
- gate-argscript-scope-string-header-layout
