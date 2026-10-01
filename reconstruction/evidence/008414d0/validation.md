# Validation 0x008414d0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 13-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x008414d0; the source span names 1 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 13-instruction listing names 1 data address(es) (0x141bcb0) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 5 member(s) (begin, copy_formatted_00840c20, field_0e0, field_0f0) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 13-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=13, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0xe0, 0xf0, 0xf4) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0xe0, 0xf0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0xf4), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (13 of 13 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 13-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 13-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `2bc780fbf78f4409fe58d24fb238c807d3b66299ad4ac73932675eecbb5377be`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `4a8b589e4ef4d5107b1a318eb4671140b541262189acfb8ff49caa7cd00de540`
- Pack digest quoted by the briefing: `2bc780fbf78f4409fe58d24fb238c807d3b66299ad4ac73932675eecbb5377be`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are there writers of the words at +0xe0 and +0xf0 that would confirm their declared types (a script and a line/index respectively are guesses only)?
- Does any real caller push the declared pString stack argument, and if so who cleans it up given the plain RET?
- FIELDS/OFFSETS: is the machine-derived receiver record wrong, or is the model wrong? The record is narrower than the body: abi_derived.receiver is shape R-DIRECT with offsets [0xe0, 0xf0] and distinct_offsets 2, while the same pack's 13-instruction listing names 0xe0, 0xf0 and 0xf4 through ECX (0xf4 via LEA ESI,[ECX + 0xf4] at 0x008414d7). The record counts only direct [ECX+disp] dereferences, so a displacement carried in a LEA is invisible to it. This package holds that the record under-reports and the model is right, and did not shrink the model to fit the bounds; the disagreement is not settled because the fix belongs in the ABI inference, which is tooling-owned.
- GLOBALS: the body names the data address 0x0141bcb0 and nothing corroborates it -- the xref export carries no data-reference edge type and the pack's globals category is empty -- so its role as the "%s:%d" literal rests on the ghidra_read_memory byte read alone. That is sufficient for a format operand (the bytes are self-identifying) but it means no second machine witness confirms the address is a string and not a pointer to one.
- Is the native return type char* or uint32_t? Ghidra's prototype and the SDK import both say uint, yet the returned dword is the begin word of the string used as the callee's char* destination. Attempt 2 made the abi record's return_type field carry the modeled type alone ('const char*', spelled as the declaration spells it) and moved the argument to return_type_rationale, so the type field is a type again; the disagreement itself is not settled. Note that the abi category in the evidence pack is copied from this record, so agreement between it and the source is a self-consistency check, not independent corroboration -- the independent part is the machine record's own return.register_class 'pointer_like'.
- Is the strlen-1 range inside 0x00840c20 intentional, and what does 0x00454cb0 do with the destination when the range does not fit (the 0x00455d60 reallocation path)?
- Was any ABI projection ever produced for this VA? evidence.missing_sections lists ABI, so the whole observed_original_abi block was derived by hand from the disassembly and needs review against a native build.
- What is the concrete class behind the vtable at 0x0141c930 for a live FormatParser, and does the secondary table at 0x0141c97c override slot 0x5c?
- What is the full extent of the FormatParser vtable beginning at 0x0141c930, and which of the 24 slots up to and including 0x5c belong to base classes? Slots 0x4c and 0x5c hold 0x00841290 (Release) and 0x008414d0 respectively, and slot 0x24 holds 0x00841490.
