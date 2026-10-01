# Validation 0x00c0bbd0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00c0bbd0-word-getter-0xb20/word_getter_0xb20_00c0bbd0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00c0bbd0; 38 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00c0bbd0; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 2-instruction listing names through ECX (0xb20) are all within the machine-derived receiver bounds (0xb20), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'uint32_t' and the machine return state is WIDTH_4_IN_EAX: the complete 2-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d40fe2141273afe694f5e30017e5929e4194df30cdc90c145aa74590c82544d5`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8d61423e65ffbb55011bc2fd27050fb981f602e8e09190102be244843ef7ad9a`
- Pack digest quoted by the briefing: `d40fe2141273afe694f5e30017e5929e4194df30cdc90c145aa74590c82544d5`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the receiver's true size recoverable? The same callers index it to at least +0x1350, but no evidence in this pack states an extent, so the model stops at the reached word.
- Is the true calling convention __thiscall or __fastcall? The ABI record lists both as candidates and the observed facts (receiver in ECX, 0 stack words, bare RET, caller cleanup) are consistent with either; no caller pushes an argument and no callee pops one, so nothing here separates them.
- No runtime/traced evidence exists in this repository for this target, so nothing is differentially validated against the original process.
- The 41 xrefs / 30 callers were sampled, not enumerated: 0x00c4fc00, 0x00aca360, 0x00c02eb0, 0x00c08350 only. A caller that dereferences the result would change the return-type argument, though not the load itself.
- What does the word at receiver+0xb20 mean — an id, a handle, an index or a pointer? The listing gives width and displacement only; the bounds_only receiver record cannot name the member. A hint exists but is not proof: the sibling 0x00c0bc00 loads the same word, tests it for null and then ADDs 0x504 to it (falling back to LEA EAX,[ECX+0xb28] when it is null), which is consistent with a pointer or table base. That sibling is owned by another worker and its interpretation is not claimed here.
