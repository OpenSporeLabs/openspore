# Validation 0x00dd06a0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 26-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00dd06a0; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 26-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 2 displacement(s) the source span declares (0x84, 0x88) and the 0 the complete 26-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x84, 0x88), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (26 of 26 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 26-instruction listing lie inside the recovered body span 0x00dd06a0..0x00dd06f1, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 26-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f9a92b01b4f0d89fcd63875cde9c303417b8851d63890598606dea94bed7a514`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `155e9e29bb4c800b716b5719e225cf7cec1d6b8e6a629bf3857d224da762e47d`
- Pack digest quoted by the briefing: `f9a92b01b4f0d89fcd63875cde9c303417b8851d63890598606dea94bed7a514`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is 0x00dd06d1's call really argument-free, as a behavioural matter? As a STATIC matter it is: the instruction before the call is 0x00dd06cf's JZ, no instruction pushes for it, and 0x00b6e250's own body reads no stack slot. It is NOT observable through a compiled model, which balances its own pushes, and the model test says so rather than pretending to check it. Two instruments that tried were withdrawn and the reasons are recorded in the model test's own file: a stack-depth difference measured 48 bytes of the compiler's -O0 frame where the listing's prologue accounts for 4, and a read of the word above the callee's return address read the compiler's 12 bytes of call-alignment padding rather than the argument slot. What is asserted instead is the observable content: the model's frame is balanced across the call and the caller's own stack word is untouched when it returns (C1, C3).
- Is 0x00dd06e6's ADD ESP,0x4 the callee's or the caller's? The callee's own terminator is a bare C3 with no immediate, so it is the caller's -- that is established by real evidence. But for a cdecl leaf callee that does not touch the caller's stack, a callee-pops and a caller-pops return are the same machine behaviour, and no black-box observer can tell them apart. Reported as a known limit of the test, not as an open question about the reconstruction.
- Is 0x0147cbbc really the start of a function table? The word at 0x0147cbbc + 0x2c is 0xf0ff0300, which is below the image base and therefore not a code address, in a run where every other word read is a code address or a data address. So either the table starts elsewhere, or something is patched at run time, or the word is a value the collector's table-start heuristic walked past. The package does not resolve it, and it is also not load-bearing: the machine-checked fact is that the body's own address appears exactly once in the image as a dword, and that word is at 0x0147cbe4. No slot index and no slot boundary is declared anywhere in the model, so nothing here depends on the table's start.
- Not fixable from this package, reported not chased: GLOBALS and EVIDENCE COVERAGE are structurally WARN. See validation.expected_reasons and known_blockers.
- The derived ABI record and the listing disagree on the RETURN CLASSIFICATION, and the listing wins. abi_derived.return is {register EAX, register_class aggregate_unknown, type null} and the persisted projection renders it as return_semantics 'unclassified_in_EAX'. The listing is unambiguous: three return sites, three writes to EAX, and a 32-bit value on each. The model's declared return type is std::int32_t, which is a different string, so the validator's RETURN SEMANTICS check will take its semantically-renamed arm. This was checked against the stricter route before the source was written -- evidence_returns.decide defers by its own rule whenever any ABI source carries a return_type or return_semantics claim, so that path cannot adjudicate this target at all. Reported, not chased.
- What are the two receiver words? The word at receiver+0x84 is switched on by two neighbouring members of the same recorded table (0x00dd0650 and 0x00dd0990) through the same DEC / CMP 0x4 / JA five-way jump table, which fixes it as a small discriminant with five arms plus a default; the word at receiver+0x88 is compared against a 32-bit constant and handed to a lookup. Neither is named in this package, because the record is bounds_only and two read-only dwords cannot say what a member is. The discriminant's enum values and the looked-up value's type are not recoverable from this body, and no SDK symbol was recovered for this VA (ghidra_function.sdk_name is null) and the binary has no MSVC RTTI.
- What does 0xff576f79 MEAN? It is demonstrably one value doing three jobs -- the arm's fallback answer, the compare that short-circuits the lookup, and the store on the shared tail -- but nothing in the 26 instructions, and nothing in either callee's own bytes, says whether it is an invalid marker, a null id, a hash, or a coincidence of two unrelated constants that happen to agree. The package names it kAbsentValue, which is a description of its role and NOT a claim about its meaning. See mechanics.present_value_identity and its not_claimed.
- What is the class, and is 0x00dd0b50 its constructor? The recorded table for this VA is 0x0147cbbc; the constructor at 0x00dd0b50 installs 0x0147c9f8, a different table. The two tables share the accessor family 0x00641810 / 0x00641820 / 0x00641850 / 0x006414e0, so they belong to related types in one hierarchy, and the sibling package pkg-swarm-w1-00dd0bc0 reconstructs 0x00dd0bc0 (a destructor on the 0x0147c9f8 table) with the same receiver family. Whether 0x00dd0b50 and this body are the same class, a base and a derived, or two siblings, is NOT settled here and no class name is used anywhere in this package.
