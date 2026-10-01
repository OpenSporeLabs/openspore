# Validation 0x0052e640

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 8-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x0052e640; 2 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `PASS` | `complete` | the complete 8-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 8-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (8 of 8 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 8-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 8-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'std::uint8_t' and the machine return state is WIDTH_1_IN_EAX: the complete 8-instruction listing writes EAX at a determinate 1-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `18c11d67b1844222f8536ddec6cf9c95eeb068c14a8cd874a74eb5dfe69d5bf6`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `68c56c2d77a5bbd9e2efec4d8a8779f921bccbb1761eef7887569cb8361920e7`
- Pack digest quoted by the briefing: `18c11d67b1844222f8536ddec6cf9c95eeb068c14a8cd874a74eb5dfe69d5bf6`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists in this repository for 0x0052e640, so every claim in this record is static. A differential run under Wine must confirm the answer is still 0 in the shipping build and that no runtime patch retargets the address.`, `One of the .rdata slots that point here must be observed being called with a concrete receiver before any owning class or slot offset can be named. The __thiscall determination does not satisfy this gate: it fixes the register the receiver arrives in, not the object behind it.`, `The INFERRED confidence of the convention and of the receiver register must not be reported as OBSERVED without a runtime observation of one of these vftable slots being called with a concrete receiver, which is the evidence the R1-VFT rule names as its own basis and the evidence a trace would supply directly.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the three popped dwords really three parameters? The derived record marks all three observed=false and the caller corroborates the count by pushing three, but the body reads none of them, so the count is the popped area rather than a read parameter count. The reconstruction keeps three because `ret 0xc` pops three, not because three parameters were proven.
- Does the JNZ that follows each call site ever get a live value? Both are statically dead in this build, so no differential trace of the original process exists that could show the answer being used.
- Is the C return type bool, unsigned char or std::uint8_t? The machine fixes only the width (one byte of EAX, upper 24 bits undefined) and the value (0). The reconstruction uses std::uint8_t; the choice is source-side and is not verified.
- Is the address a compiler-folded COMDAT shared by several unrelated 'return false' defaults, or one class's default emitted once? Both fit every observation, including the two adjacent equal slots and the 25-table membership count.
- No original-process trace exists in this repository for 0x0052e640, so every claim in this record is static. A differential run under Wine must confirm the answer is still 0 in the shipping build and that no runtime patch retargets the address.
- One of the .rdata slots that point here must be observed being called with a concrete receiver before any owning class or slot offset can be named. The __thiscall determination does not satisfy this gate: it fixes the register the receiver arrives in, not the object behind it.
- The INFERRED confidence of the convention and of the receiver register must not be reported as OBSERVED without a runtime observation of one of these vftable slots being called with a concrete receiver, which is the evidence the R1-VFT rule names as its own basis and the evidence a trace would supply directly.
- What IS the receiver? The convention fixes that ECX carries it and the record fixes that it is present, one 4-byte word wide, and never dereferenced here - so no field offset is claimed in either direction. But the receiver's type, object size, shape and owning class are all unproven, and the body cannot show them because it never looks. That is now the sharpest open question rather than the register, and it stays open.
- What predicate does this answer, and to which question? The body is a constant no; nothing in the evidence names the question. The two direct callers both discard the answer into a statically dead branch, so even the callers do not say. The __thiscall determination does not help: it fixes how the function is called, not what it is for.
- Which class, if any, owns the vftable slots that point here? Six .rdata sites were read live and no table base and no slot offset was derived by this package. R1-VFT names 0x013f2194 slot 8 as the evidence FOR the receiver and counts 25 tables holding this address; that is the rule's own bookkeeping, not an attribution of an owning class, and the other 24 tables are not individually attributed. Ghidra's referenced_by_vtables list of 18 addresses is a classifier association, not a measured table base, and is not used as one.
- Why does a 218-instruction neighbour (0x0052e680) with the same prologue dereference its ECX while this one does not? Both shapes are observed here; which one the original author wrote for this slot is not recorded anywhere in the evidence. The determination that this one is a __thiscall member does not answer it, since the neighbour is a member too.
