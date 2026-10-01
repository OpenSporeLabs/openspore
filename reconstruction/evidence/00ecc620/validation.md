# Validation 0x00ecc620

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 26-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 2 distinct address(es) for 0x00ecc620; the source span names 2 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 26-instruction listing names 3 data address(es) (0x148938c, 0x148939c, 0x14893b0) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 26-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x0), all of which the record accounts for or the listing is the better witness on; the 26-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=26, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 5 displacement(s) (0x0, 0x10, 0x14, 0x80, 0x88), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 4 of those (0x10, 0x14, 0x80, 0x88) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (26 of 26 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 26-instruction listing lie inside the recovered body span 0x00ecc620..0x00ecc674, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 26-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `800580ad1c52a0e028a45e3d8116d6cd501de0b1231e4d760dfe3ae4741eda05`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9fa19d652459b9c451ba27d2c54ee2a1b10c5098a99afa43d7a29963c216e57b`
- Pack digest quoted by the briefing: `800580ad1c52a0e028a45e3d8116d6cd501de0b1231e4d760dfe3ae4741eda05`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- RUNTIME is GATED at 0. No original-process trace exists in this repository for this VA, nothing was attempted, and nothing failed.
- The class name is CORROBORATED but one indirection away: the string 'Sporepedia/AssetData/cSPScenarioCaptainAssetData' at 0x01489468 is passed to the allocator by the factory 0x00ecc7d0, which constructs with 0x00ecc780, which installs the three dispatch constants this body also installs. This VA's own records carry ghidra_name FUN_00ecc620 and sdk_name null, and the SDK-to-Ghidra import named nothing at this address, so the name is recorded here and deliberately not used in the signature.
- The two adjust-and-jump thunks adjust ECX by 0x10 and 0x14 DOWNWARDS, which fixes that the subobjects owning those vftables sit 0x10 and 0x14 bytes below the complete-object pointer that reached the thunk. The bases those two subobjects belong to are not identified here, and nothing in this body depends on them.
- There are no callers recorded for this VA (briefing.callers is empty and ghidra_function.callers is empty), so the frequencies with which the deleting form and the non-deleting form are actually used are unknown. The body handles both, and the model test drives both, but no evidence says which is the common case.
- What the two words at receiver+0x80 and +0x88 actually are. The body only subtracts and masks them, and this package therefore claims nothing about their type beyond being 32-bit words at those two displacements. Three facts constrain but do not settle it: the constructor initialises them 0x01667bac and 0x01667bae, a two-byte run; 0x00ecc550 passes &receiver+0x80 to a virtual function taken from the table's slot +0x40, so +0x80 is the address of a subobject; and 0x00ecc530 compares +0x80 against +0x84, so the third word in that region is distinct from both. Whether the run is a byte buffer, a null-terminated string, a pointer range or a small inline vector is not established by any record in this repository.
- Whether the deallocation of the +0x80 run and the deallocation of the object are always the same allocator. Both go through 0x00f47380 in this body, but the constructor does not allocate that run (it points it at a static-looking address) and whatever installs a heap run on it is not identified here. Whether some other port is used elsewhere in the class is not established.
- Why the guard's threshold is 2 rather than any other constant. The mask-then-compare pair behaves exactly as an MSVC 'more than one element, so the storage is heap and must be released' test, and 0x00642190 runs the identical idiom on its own pair, but no record states the intent and the unit (bytes, elements, words) is not fixed by any instruction.
