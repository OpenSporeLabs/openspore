# Validation 0x005bf9d0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg18_ui_scripting/ui_shell_functions.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 130-instruction listing name the same 5 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x005bf9d0..0x005bfb62 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x005bfb0d; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 6 outgoing call edge row(s) over 5 distinct address(es) for 0x005bf9d0; the source span names 4 of them and no others |
| GLOBALS | `WARN` | `partial` | 1 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 130-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0xc, 0x14, 0x18), all of which the record accounts for or the listing is the better witness on; the 130-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=130, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0xc, 0x14, 0x18) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0x-4, 0xc, 0x14, 0x18), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x-4) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (130 of 130 instruction(s), 0 unparsed) and all 14 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 17 conditional branch target(s) in the complete 130-instruction listing lie inside the recovered body span 0x005bf9d0..0x005bfb62, so the branch graph is closed inside it; the source span declares if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 130-instruction body names 4 indirect transfer(s): 0x005bfaac dispatches slot 0x44 through the table word in EDX; 0x005bfad2 dispatches slot 0x10 through the table word in EDX; 0x005bfaee dispatches slot 0x1c through the table word in EDX; 0x005bfb27 dispatches slot 0x80 through the table word in EDX; the machine parse consumed 130 of 130 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x10, 0x44, 0x80, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'bool': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 5 passed, 1 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `5ffdf54b8584dffb1dc15d24d7ab138cb831ae97eab6abb7594ab9fa6cd7ddc9`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `042376f93754e1aa690162498a20e5c192c1faafde08293e7f78428f55432453`
- Pack digest quoted by the briefing: `5ffdf54b8584dffb1dc15d24d7ab138cb831ae97eab6abb7594ab9fa6cd7ddc9`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-ui-scripting-message-routes`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The concrete editor/input owner of the receiver and the meaning of message ids remain unresolved.
- The concrete shell and service owners are not proven by this function.
- The data xref may be a callback-table reference, but no direct dataflow ties it to Space UI initialization or teardown.
- The input payload and linked item types remain opaque; only offsets and call widths are asserted.
- The surrounding function-pointer table owner is unresolved.
- function-pointer table owner
- gate-ui-scripting-message-routes
- input payload subtype
- shell and service owners
