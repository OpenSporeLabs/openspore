# Validation 0x006a2ef0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_property_remove_006a2ef0/property_remove_006a2ef0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 9-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x006a2ef0; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 9-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x34) and the 0 the complete 9-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x34), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (9 of 9 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 9-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 9-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `4a768d5cc81a25bff0944a1ba4e8034e573dc2837f0f03df5052681beb564b30`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `437240f781f2a72399cc76591c8ce620394b53f65182a3ca3539454eb95e5d76`
- Pack digest quoted by the briefing: `4a768d5cc81a25bff0944a1ba4e8034e573dc2837f0f03df5052681beb564b30`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No direct caller xref exists; the two table references at 0x01408838 and 0x01408888 are the only reachability evidence and no original-process trace was captured, so the calling convention and argument order have not been exercised at runtime.
- The 0x34 receiver word is incremented on every call, including when the port reports no removal, but nothing in the machine record establishes what it counts. The port's own listing places its 0x18-stride entry region immediately below that word (see mechanics.callee_receiver_observations), which makes a version or mutation counter a plausible reading; the sibling body at 0x006a2a80 increments the same displacement after its own mutation. Both are hypotheses, not evidence for this function.
- The return width class is unresolved: the ABI envelope records register_class aggregate_unknown and return.type null, so 'int' rests on the resolved Ghidra prototype plus the pass-through of EAX, not on a width classification.
- The sub-object at receiver + 0x18 is the receiver 0x006a2cb0 operates on, but the machine-derived receiver record does not enumerate that displacement (the LEA is not a memory access) and no type record establishes what that sub-object is; only 0x006a2cb0's own decompilation shows it behaving as a contiguous array of 0x18-byte entries.
- Whether callers of RemoveProperty depend on the 0/1 range the port returns, and whether the increment is expected to happen even when the port reports no removal, are not established by this body.
