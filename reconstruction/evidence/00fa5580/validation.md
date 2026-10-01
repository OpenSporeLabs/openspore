# Validation 0x00fa5580

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00fa5580/swarm_w1_00fa5580.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 46-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00fa5580; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 46-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares 3 displacement(s) (0xac, 0x798, 0x79c) and every one of them is a displacement the complete 46-instruction listing shows: 2 attributed to the receiver ECX as proven (0x798, 0x79c); 1 more (0xac) are shown by the listing under a base that is not the receiver -- 0xac under ECX -- so the body does use those displacements, on an object this check cannot identify; that is a limit of the attribution here and not a disagreement with the receiver, and no receiver contradiction is claimed for them; the 46-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=46, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x798, 0x79c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x798, 0x79c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (46 of 46 instruction(s), 0 unparsed) and all 4 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 46-instruction listing lie inside the recovered body span 0x00fa5580..0x00fa5601, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 46-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `5296af5b263f08d2ea04ecad39f0196c2c1d138e3d7572ff227f327e8b1634e3`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `c0f8bc7232e3cd3108fd465d1af77a8be4148572fcf143c0388af8a45dad252f`
- Pack digest quoted by the briefing: `5296af5b263f08d2ea04ecad39f0196c2c1d138e3d7572ff227f327e8b1634e3`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The only return claim any record carries for this VA is the machine-vocabulary phrase return_semantics 'integral_in_EAX', with return_register EAX and NO return_type field anywhere. That is not a C type, so the validator's string comparison against this package's declared std::uint8_t cannot pass, and RETURN SEMANTICS is a WARN for that reason alone. Declaring a typedef literally named integral_in_EAX would make the string match; that was NOT done, because inventing a C identifier to satisfy a comparison is the opposite of evidence-only, and the width the listing actually fixes (one byte) is asserted by the model and by the model test either way. This is the integrator's call if the aggregate matters more than the spelling.
- What the array IS. Two words at +0x798 and +0x79c, a 0xac stride, a decrement on removal and an increment in a sibling all say 'a fixed-capacity array with a cursor'. No record names it, the 0x7a0 capacity word a sibling reads is not touched by this body, and nothing here says the key at an element's +0xa8 is a name, an id or a hash. No member is named for either receiver word and no element member is named except by its offset.
- Whether the class table's other 25 entries above this one at 0x01490be8 name the class. This binary has no MSVC RTTI, the xref export records vtable_reference_count 0 for this target, and the table association is a transitive classifier artifact (the validator's own source calls record['vtables'] a classifier association that contradicts the xref export). Nothing is named from it here, and the subsystem label 'Sporepedia' on this target comes from the queue record rather than from the model.
- Whether the original C++ return type was bool, char or something else of one byte. The machine fixes the width and the two values; it does not fix the spelling, and no record supplies a return_type. uint8_t is declared as the spelling that asserts only the width.
- Whether the two extra loads of the receiver's two words (0x00fa5584 then 0x00fa55cf, and 0x00fa558a then 0x00fa55a8) are meaningful. Nothing this body calls writes the receiver, so no interleaving can be observed between the first load and the second, and the model reads each once. A mutation that cached the first load in place of the second SURVIVES the model test, which is the honest statement of that limit rather than a claim that the loads are equivalent.
- Why the key sits at +0xa8 of a 0xac record -- i.e. what the preceding 0xa8 bytes are. 0x00f9f620 copies dwords and then x87 floats across the record, so it is plainly a value-like record with a trailing word, but no record for it exists in this repository and none is claimed.
