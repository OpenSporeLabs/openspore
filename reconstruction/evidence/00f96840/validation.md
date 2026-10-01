# Validation 0x00f96840

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-w2-00f96840/w2_00f96840.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 15-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00f96840; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 15-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00f96840; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 15-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x0, 0x814), all of which the record accounts for or the listing is the better witness on; the 15-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=15, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x0, 0x814) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x0, 0x814), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (15 of 15 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 15-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 15-instruction body names 3 indirect transfer(s): 0x00f96848 dispatches slot 0x70 through the table word in EAX; 0x00f96851 dispatches slot 0x60 through the table word in EAX; 0x00f96868 dispatches slot 0x84 through the table word in EAX; the machine parse consumed 15 of 15 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 15-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `22f645cff2fb04be49872c285007442e190e21591aa48add35db52ddda8815ea`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `05754f84544a7c3433d84d7b9b5650e63c16084ba42f35212f0ff5e01d2db872`
- Pack digest quoted by the briefing: `22f645cff2fb04be49872c285007442e190e21591aa48add35db52ddda8815ea`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `no original-process trace exists in this repository; the runtime gate is open, nothing was attempted, and nothing failed`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original-process trace exists in this repository, so nothing here is runtime-validated. Every statement in this record is a static reading of the image and of the machine's own derived ABI record.
- No return type is determinable. The only exit belongs to the routine at table slot 0x84, which is outside this body, so what the caller receives in EAX is that routine's return. The record says the same: return.type null, void_possible false, and a machine return state of UNCLASSIFIED on a body with a tail exit.
- The calling convention is undetermined and the machine record says so. All four candidates (__cdecl, __stdcall, __thiscall, __fastcall) remain open because the body has no terminator to read a cleanup from, and nothing in these 42 bytes separates a COM/__stdcall object from a __thiscall method. A caller-side observation, a this-adjusting entry stub, or a terminator in a neighbouring function would settle it; none of those is in this record.
- The cleanup side and size are undetermined (cleanup.side null, cleanup.bytes null, confidence UNKNOWN). There is no RET immediate to be either, and the body pushes nothing and reads nothing on the stack, so there is no argument to account for either.
- The meaning of the word the body loads at 0x00f96843 beyond "it is the base of the next displacement" is unknown. The model treats it as a table pointer because that is the only use the fifteen instructions make of it, and it does not claim the object's own vtable identity from that.
- The receiver's identity is unresolved: no size, no layout, no member, no vtable-pointer offset, no owning class. bounds_only true and shape R-ALIAS are the record's own limits, and the body neither adjusts nor tests the pointer, so whether ECX points at the head of an object or an interior sub-object is invisible here.
- What the three routines at table slots 0x70, 0x60 and 0x84 do is unknown, as is why that order. The order is transcribed; the reason is not observable from this body. The record associates this address with vtable 0x01490be8, but the binary carries no MSVC RTTI and no SDK name is recorded for that table, so no class, vtable identity or slot name is claimed.
- no original-process trace exists in this repository; the runtime gate is open, nothing was attempted, and nothing failed
