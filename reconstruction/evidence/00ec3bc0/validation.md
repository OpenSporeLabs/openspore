# Validation 0x00ec3bc0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-sporepedia-owned-slot-notify/sporepedia_owned_slot_notify.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 13-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00ec3bc0; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 13-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x20) and the 0 the complete 13-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x20), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (13 of 13 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 13-instruction listing lie inside the recovered body span 0x00ec3bc0..0x00ec3bdd, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 13-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `e90c24836ac398e1c336b4cf492fb5145c561fd084d61c6dfe7b749da1295733`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d7768e562e32d0fbe84c55a60a3c82787a50a411c74db219cb7b4fbd597f2312`
- Pack digest quoted by the briefing: `e90c24836ac398e1c336b4cf492fb5145c561fd084d61c6dfe7b749da1295733`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the branch at 0x00ec3bcd ever taken as not-taken? The re-verified sibling record reconstruction/metadata/pkg-sporepedia-slot-release/00641e10.json writes zero into the same displacement 0x20 of its receiver at 0x00641e1e, before its own dispatch. If both bodies share a receiver, the word this body tests at 0x00ec3bcb is already zero and the block at 0x00ec3bcf..0x00ec3bd9 is dead on the non-null entry path. This is a cross-target inference, not a fact about this body: no record for 0x00ec3bc0 shows the two share a receiver (its own fan_in is 0, callers empty), and 0x00641e10 closed as WARN, so its candidate is unconfirmed. Settling it needs a trace that captures the value at receiver+0x20 both before and after 0x00ec3bc3.
- Is the return word meaningful? The record classifies it as unclassified_in_EAX with register_class aggregate_unknown and void_possible false, and the live decompilation of this body ends in a bare return, so the model neither names nor interprets it.
- What do the three hashed ids 0x1f0372ed, 0xd6a4ff43 and 0xb55857d7 that 0x00eec760 passes to its slot at displacement 0x24 mean, and why does the callee read a short at offset 0x12 of the first argument? None of that is visible in this body.
- What is the 0x80 area that 0x00eec760 writes three words into? The body only forms the address; the live decompilation of that callee stores 0xffffffff and two words of 0x7fffffff there under its own guards, which suggests an initialised bounds or range block, but no record for this target names it.
- What is the receiver's word at displacement 0x20? The receiver record enumerates the displacement and nothing about the member: not whether it is owned, borrowed or a smart handle, and not its type. The model reads it as a pointer only because 0x00ec3bd3 hands it to 0x00eec760, whose own decompilation dereferences its first argument.
- Which class does this body belong to? The record's only class evidence is the transitive association with vtable:0x014890f4 and two analogue functions at 0x00641400 and 0x00641460 that share it. No RTTI and no vtable pass exist for this binary, and the body itself contains no dispatch that would tie it to that table.
- Who calls this body? fan_in is 0 and the caller list is empty, so nothing here establishes the entry conditions under which the receiver's word at 0x20 is expected to be non-null.
- Why does the body re-read a word that 0x00641e10 has just cleared? The ordering is observable in the listing, and the staged candidate for 0x00641e10 clears that word before it transfers control through the pointee's dispatch word, which would make this branch always take the JZ. Nothing for this target establishes that the two functions share a receiver, so the branch is modelled from this listing alone and the question stands.
