# Validation 0x007c6750

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/df2-live-listing/camera_active_by_id_007c6750.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 360-instruction listing name the same 13 direct transfer target(s); 7 intra-procedural jump(s) target inside the recovered body span 0x007c6750..0x007c6b7c are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x007c67b9, 0x007c6860, 0x007c68b9, 0x007c69d0, 0x007c6a57, 0x007c6a59, 0x007c6aa4; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 20 outgoing call edge row(s) over 13 distinct address(es) for 0x007c6750; 2 of those rows name an external import rather than an address and are not address-comparable, as in the projection; the source span names 13 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 360-instruction listing names 15 data address(es) (0x13cc4cc, 0x13cc50c, 0x13ec468, 0x13ec47c, 0x13ed024, 0x13f2ce4, 0x1401b58, 0x1409070, 0x1410618, 0x1410624, 0x1410628, 0x1410648, 0x1410664, 0x141067c, 0x14f9174) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 360-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x4, 0x10), all of which the record accounts for or the listing is the better witness on; the 360-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=360, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x4, 0x10) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x4, 0x10), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (360 of 360 instruction(s), 0 unparsed) and all 19 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 33 conditional branch target(s) in the complete 360-instruction listing lie inside the recovered body span 0x007c6750..0x007c6b7c, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 360-instruction body names 19 indirect transfer(s): 0x007c6784 dispatches slot 0x58 through the table word in EAX; 0x007c6821 is INDIRECT_NON_VTABLE; 0x007c6851 dispatches slot 0x48 through the table word in EAX; 0x007c68bf is INDIRECT_NON_VTABLE; 0x007c6907 dispatches slot 0x54 through the table word in EAX; 0x007c695c dispatches slot 0xa0 through the table word in EDX; 0x007c6964 is FUNCTION_POINTER; 0x007c6984 dispatches slot 0x48 through the table word in EDX; 0x007c69dd dispatches slot 0x58 through the table word in EAX; 0x007c69fc dispatches slot 0x4c through the table word in EAX; 0x007c6a05 dispatches slot 0x4c through the table word in EDX; 0x007c6a19 dispatches slot 0x1c through the table word in EDX; 0x007c6a2b dispatches slot 0x28 through the table word in EDX; 0x007c6a8b dispatches slot 0x50 through the table word in EAX; 0x007c6ab2 dispatches slot 0x48 through the table word in EDX; 0x007c6ae5 dispatches slot 0xb4 through the table word in EDX; 0x007c6b23 dispatches slot 0x58 through the table word in EDX; 0x007c6b4e dispatches slot 0x9c through the table word in EDX; 0x007c6b61 dispatches slot 0x58 through the table word in EDX; the machine parse consumed 360 of 360 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 19, so the dispatch is visible in the machine listing but is not proven: 1 of the 19 indirect transfer(s) classify as FUNCTION_POINTER (0x007c6964), so the dispatch's identity is not established: EAX is loaded from [EDI], but EDI is defined by an immediate or register assignment, not a memory load earlier in the listing, so the word it names is not shown to be a table word and 2 of the 19 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x007c6821, 0x007c68bf), so the dispatch's identity is not established: the target is the memory operand [0x013cc4cc], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `98ece8d181aa8775f956d7a2efd6149cd696765b09ef1f40ee2c141845f6100f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `871069551f6fc8d1a49db83456b2f7a4492a024f1d8fc3ff3f9318cdf25a9521`
- Pack digest quoted by the briefing: `98ece8d181aa8775f956d7a2efd6149cd696765b09ef1f40ee2c141845f6100f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `no original-process trace exists in this repository; the static reconstruction of 0x007c6750 is unvalidated at runtime`, `the committed evidence pack's disassembly is a truncated envelope, so no listing-dependent check could be adjudicated from committed evidence`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The committed pack's disassembly category is a truncated envelope, so every listing-dependent validation check reads NOT_AVAILABLE for this target. The listing used here came from the live bridge; a reader must not mistake it for the pack's own.
- The common epilogue returns whatever AL holds on the arriving path. The listing names that value for some paths only, and the reconstruction's false default for the rest is a modelling choice, not an observation.
- The identity behind each of the 19 indirect transfers is not established; the reconstruction reports the displacement each target was read at and nothing more.
- The three-word local at entry ESP-0x1C that 0x0093c5a0 fills is only ever measured (word 2 minus word 0, masked with 0xfffffffe, required to exceed 2). What the three words are, and why the third rather than the second bounds the length, is not established.
- The two conflict-ledger entries anchored on this address (app_mode_setter_boundary, camera_address_conflicts) remain unresolved in knowledgegraph/research/conflicts/track-c-state-events.json, and this reconstruction makes no claim about the mode or address transition contract either entry is about.
- What the 0x0083xxxx property helpers are keyed on is not established: the argument doubles as their receiver, and this body does not show what that object is.
- Whether the 0x00f47380 result is a success flag or a pointer-width value is not established; it is declared boolean-shaped because only AL is consumed.
- Which of the two candidate argument shapes 0x00838330/0x008380b0/0x00838020 use as their first stack argument, and whether the recovered strings 'set', 'list', 'bg' and 'renderType' are the complete names, is not established by the body.
- no original-process trace exists in this repository; the static reconstruction of 0x007c6750 is unvalidated at runtime
- the committed evidence pack's disassembly is a truncated envelope, so no listing-dependent check could be adjudicated from committed evidence
