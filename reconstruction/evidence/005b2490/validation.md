# Validation 0x005b2490

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-005b2490/sw1_005b2490.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 4-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x005b2490; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 4-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x18) and the 1 the complete 4-instruction listing names through ECX (0x18) are all within the machine-derived receiver bounds (0x18), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (4 of 4 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 4-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 4-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `80e5e53bc6b120b0113239608cd0637776bb4ca2a879960fc0d47fed32eee216`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `789d732592bafd5a00d18517df9b695a138f9085f6aa22be12f1bd867c78444f`
- Pack digest quoted by the briefing: `80e5e53bc6b120b0113239608cd0637776bb4ca2a879960fc0d47fed32eee216`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does any caller use the returned value, and as what? The body is entered only through a table slot, so its callers are the dispatch sites, which this package did not enumerate. The return is the incremented word; whether a caller treats it as a count, an index, a new generation or an opaque handle is not established here.
- Is the receiver the head of its object or a sub-object? The body never stores ECX, so a this-adjusting caller is invisible from inside it. The three adjustors (-0x04, -0x10, -0x14) prove the word lives at more than one displacement within a hierarchy, but which class each table belongs to is not established by anything in this package.
- Is the word signed or unsigned? INC EAX is bit-identical for signed and unsigned, nothing in the body tests bit 31, and abi_derived's return_semantics is 'unclassified_in_EAX' (RT2 register_class aggregate_unknown). The reconstruction models it as an unsigned 32-bit word -- which is what fixes the 0xffffffff -> 0x00000000 wrap the machine performs -- and the SIGN itself is unresolved. The declared return type is now spelled std::uint32_t rather than the `Word` alias, and that spelling fixes the WIDTH and the wrap only: unsigned is what the wraparound test at 0xffffffff needs to be defined, and it is not a claim that the original's type is unsigned, because INC EAX cannot distinguish the two and no instruction here reads bit 31. Whether the true type is signed changes no observable behaviour of THIS body and changes the meaning of its return value at every caller.
- What are the eleven other vtables this address is associated with, and does the slot mean the same thing in all of them? The record associates 12 tables, the xref export carries 15 data references, and this binary has no MSVC RTTI, so no slot name is recoverable from it. The two displacements this package verified (+0x00 of the table at 0x013f57f8 and +0x10 of the table at 0x013f7028) are the only slot facts claimed, and the fact that the same address sits at two different displacements in two tables is itself unexplained.
- What is the true size of the receiver? 0x1c is a lower bound this body proves (0x18 + 4) and nothing more. The object is certainly larger -- it is polymorphic, so a dispatch word exists at +0x00 -- but this body never reads or writes any byte outside 0x18..0x1b and no consulted record sizes it.
- What is the word at receiver+0x18? Nothing in this body or in any record consulted here says: it is read, incremented and written, and nothing tests or constrains its value, so it could be a counter, a version, a sequence number, a reference count, an index or a handle. Naming it would be a member story four instructions cannot carry, so the package names it a word and leaves the question here.
