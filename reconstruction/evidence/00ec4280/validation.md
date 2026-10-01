# Validation 0x00ec4280

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00ec4280/sw1_00ec4280.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 14-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00ec4280; the source span names 2 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 14-instruction listing names 3 data address(es) (0x148906c, 0x148907c, 0x1489090) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 14-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x0), all of which the record accounts for or the listing is the better witness on; the 14-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=14, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0x0, 0x10, 0x14), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0x10, 0x14) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (14 of 14 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 14-instruction listing lie inside the recovered body span 0x00ec4280..0x00ec42af, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 14-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'SporepediaOnlineAsset*' and the machine return state is WIDTH_4_IN_EAX: the complete 14-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `e5598c850d00187ad46fe7b5bcbed4f0ff710b7550e7798ca95cb5ce0e261fd4`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `0fff28a1748c34e8bec67be9f4b83f91e502c1e1bd42894466688f735cd8175c`
- Pack digest quoted by the briefing: `e5598c850d00187ad46fe7b5bcbed4f0ff710b7550e7798ca95cb5ce0e261fd4`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The interior of 0x00642190 and of the 0x006412A0 chain. The five null-guarded indirect handle releases, the inline-vector comparison and the tail transfer are opaque seams here; this package asserts only the three vptr words, the terminator and the zero-argument convention, all of which were re-read from the image.
- What the class actually is. No MSVC RTTI survives in this binary (the repo's own AGENTS.md says so and the record's evidence_note repeats it), and no record names the class. The type name SporepediaOnlineAsset is for readability and is not a claim. The triage cluster says 'sporepedia-online' and the eight analogue records share this vftable, so the neighbourhood is Sporepedia, but the specific class and its bases are unknown.
- What the other seven bits of the delete-flag byte mean, and who sets them. Only bit 0 is examined here. An MSVC deleting destructor normally encodes more than one condition in that byte, and this body is the only place in this package that can see it, so the question is genuinely open from this VA alone.
- Whether the return value is ever consumed. No caller is recorded for this VA (Ghidra lists callers [] and the only xrefs are the vtable word and the two thunks), so the returning destructor's contract -- whether a caller uses EAX, or whether this is a hand-rolled destructor rather than a compiler-emitted one -- cannot be settled from the image at this address.
- Whether the three bytes at entry_ESP+0x5..0x7 of the argument slot are ever non-zero in real callers. RET 0x4 fixes the slot's width and the 0xF6 r/m8 form fixes that only the low byte is read, but no caller was identified to check what it writes in the upper half.
- Why 0x00EC4280 also appears at 0x0148907C + 0x14 and at 0x0148906C + 0x24, and why the thunks sit at 0x0148907C + 0x08 and 0x0148906C + 0x00. The three tables are consecutive in .rdata and their trailing entries are identical, which is consistent both with one class reachable through two base subobjects and with the linker simply laying related tables next to each other. The bytes do not decide it, so no slot boundary is modelled and no hierarchy is claimed.
