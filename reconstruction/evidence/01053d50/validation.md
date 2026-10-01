# Validation 0x01053d50

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-sim-toolevent-01053d50/sim_tool_event_01053d50.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 30-instruction listing name the same 4 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 4 outgoing call edge row(s) over 4 distinct address(es) for 0x01053d50; the source span names 4 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 30-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x0) and the 0 the complete 30-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x0), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (30 of 30 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 30-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 30-instruction body names 1 indirect transfer(s): 0x01053d8f dispatches slot 0x4c through the table word in EDX; the machine parse consumed 30 of 30 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 4 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `140324ead9bb2055fecd0cd5d702ebb89f5c23b5885c803ed9a0efac6caf3437`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `39eeab34cc3fa41b8cd549c6408b65e60234837b219aecb6ada8c410bc5070ba`
- Pack digest quoted by the briefing: `140324ead9bb2055fecd0cd5d702ebb89f5c23b5885c803ed9a0efac6caf3437`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No differential runtime corpus exists for this virtual, so the ordering and the dispatch are static-only evidence.
- The 16-byte rotation source is never written by this body, so the value the frame receives through that argument is indeterminate here. The original source most plausibly passed a default-constructed or dead value that the compiler proved irrelevant, but nothing in this VA's evidence shows which.
- The base of each pointer block, and therefore the index-8 reading and the resolution of the dispatched byte offset 0x4c to 0x007b86e0, rest on the repetition pattern alone. If the true base is four words later, this function is index 4 and the dispatched word is 0x010537e0 instead.
- The first stack argument is forwarded to the dispatched slot and used nowhere else. Its type is not determined; it is compatible with the cSpaceToolData * that the SDK attaches to the sibling virtual at 0x01053db0, but that is an SDK guess on a different function and is not adopted here.
- The image carries no name for 0x01053d50, so none is claimed. The class is not established either: the function is index 8 of six pointer blocks, but the repeated first word of those blocks is a constructor, so they are not plain MSVC vtables and no RTTI complete-object locator is available to name the class.
- The role of the dispatched slot is unresolved. The address the block reading resolves to decrements a refcount-like word and calls a callback when it reaches zero, but the two forwarded arguments are ignored by it, so it is not established whether the tool is releasing itself, a related object, or invoking a hook with the event arguments.
- The three constants inside the poster (0x4474369, 0x446e39c, 0x58) and the four inside the frame constructor (0x3f800000) belong to the callees, not to this VA, so they are recorded here and deliberately kept out of the staged source span.
