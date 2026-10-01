# Validation 0x005c0380

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg18_ui_scripting/ui_shell_functions.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 348-instruction listing name the same 8 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x005c0380..0x005c0736 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x005c0632; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 24 outgoing call edge row(s) over 8 distinct address(es) for 0x005c0380; the source span names 5 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 348-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 348-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x10, 0x18), all of which the record accounts for or the listing is the better witness on; the 348-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=348, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x10, 0x18) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 5 displacement(s) (0x10, 0x11, 0x18, 0x1c, 0x20), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 3 of those (0x11, 0x1c, 0x20) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (348 of 348 instruction(s), 0 unparsed) and all 25 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 23 conditional branch target(s) in the complete 348-instruction listing lie inside the recovered body span 0x005c0380..0x005c0736, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 348-instruction body names 34 indirect transfer(s): 0x005c03be dispatches slot 0xc through the table word in EDX; 0x005c03cb dispatches slot 0x28 through the table word in EDX; 0x005c03ec dispatches slot 0xc through the table word in EDX; 0x005c03f9 dispatches slot 0x28 through the table word in EDX; 0x005c0426 dispatches slot 0x7c through the table word in EDX; 0x005c0434 dispatches slot 0xc through the table word in EDX; 0x005c043f dispatches slot 0x3c through the table word in EDX; 0x005c0461 dispatches slot 0x94 through the table word in EDX; 0x005c046e dispatches slot 0xdc through the table word in EDX; 0x005c047f dispatches slot 0x4c through the table word in EDX; 0x005c04a0 dispatches slot 0x7c through the table word in EDX; 0x005c04c0 dispatches slot 0x7c through the table word in EDX; 0x005c04e0 dispatches slot 0x7c through the table word in EDX; 0x005c0508 dispatches slot 0x7c through the table word in EDX; 0x005c0515 dispatches slot 0x7c through the table word in EDX; 0x005c053e dispatches slot 0x14 through the table word in EDX; 0x005c055d dispatches slot 0xc through the table word in EDX; 0x005c056a dispatches slot 0x28 through the table word in EDX; 0x005c058b dispatches slot 0xc through the table word in EDX; 0x005c0598 dispatches slot 0x28 through the table word in EDX; 0x005c05c4 dispatches slot 0x7c through the table word in EDX; 0x005c05cd dispatches slot 0x3c through the table word in EDX; 0x005c0614 dispatches slot 0x4 through the table word in EDX; 0x005c0630 dispatches slot 0x0 through the table word in EDX; 0x005c0650 dispatches slot 0x7c through the table word in EDX; 0x005c0689 dispatches slot 0x3c through the table word in EDX; 0x005c0694 dispatches slot 0x8 through the table word in EDX; 0x005c06a1 dispatches slot 0x7c through the table word in EDX; 0x005c06bf dispatches slot 0x3c through the table word in EDX; 0x005c06ca dispatches slot 0x10 through the table word in EDX; 0x005c06d7 dispatches slot 0x7c through the table word in EDX; 0x005c06f9 dispatches slot 0x7c through the table word in EDX; 0x005c0706 dispatches slot 0x7c through the table word in EDX; 0x005c072f dispatches slot 0x14 through the table word in EDX; the machine parse consumed 348 of 348 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 34. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x0, 0x4, 0x8, 0xc, 0x10, 0x3c, 0x94, 0xdc, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'void': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `644c287f20043bea5e333d9d1587d429941953b921029786297fb1b7aad77c74`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3f30f8822f7feb82f16df482079c6e7846d3895644875b281e5d367df0d815c8`
- Pack digest quoted by the briefing: `644c287f20043bea5e333d9d1587d429941953b921029786297fb1b7aad77c74`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-ui-scripting-registration-state`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The original disable branch dereferences the text service after the optional lookup check; no safe null policy is invented.
- The shell, service, text provider, and application system concrete owners remain unresolved.
- The three-word range is opaque; only the observed pointer span and free threshold are asserted.
- application-system state meaning
- gate-ui-scripting-registration-state
- service and text-provider owners
- three-word range ownership
