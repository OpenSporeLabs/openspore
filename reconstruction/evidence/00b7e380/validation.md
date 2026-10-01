# Validation 0x00b7e380

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00b7e380-member-ptr-0x2c/member_ptr_0x2c_00b7e380.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00b7e380; 12 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares 1 displacement(s) (0x2c) and every one of them is a displacement the complete 2-instruction listing shows: 1 attributed to the receiver ECX as proven (0x2c); the 2-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=2, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x2c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the listing shows 1 displacement(s) the record does not enumerate (0x2c), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9fb92e02083b9e7d48ca7374d98ceff66fc30353089a04bf59b5ce21d7915b21`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `1a1fffb08f8e24cc97294d161761c926a86fe1f673dcee27275c3ed832bbff8e`
- Pack digest quoted by the briefing: `9fb92e02083b9e7d48ca7374d98ceff66fc30353089a04bf59b5ce21d7915b21`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `confirm the class identity behind the three vtable images; the binary has no MSVC RTTI`, `observe one real virtual call through a slot +0x98 word and record whether the caller consumes EAX`, `record the receiver allocation size at runtime; the 0x30 byte modelled extent is only the prefix through the reached slot`, `record the value at receiver+0x2c and find its consumer, to establish the member's type`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The class identity behind the three vtable images; the binary has no MSVC RTTI.
- The real allocation size of the receiver object; 0x30 is only the modelled prefix through the reached slot.
- The type of the member at offset 0x2c: whether it is an int, a pointer, a char buffer or a sub-object. No instruction in this body reads or writes it, and no consumer is reachable from here.
- confirm the class identity behind the three vtable images; the binary has no MSVC RTTI
- observe one real virtual call through a slot +0x98 word and record whether the caller consumes EAX
- record the receiver allocation size at runtime; the 0x30 byte modelled extent is only the prefix through the reached slot
- record the value at receiver+0x2c and find its consumer, to establish the member's type
