# Validation 0x0069d3f0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 4-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x0069d3f0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 4-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | 1 displacement(s) (0x8) lie outside the machine-derived receiver bounds (none) for ECX, so the source and the body disagree with the receiver record; the source span declares 0x8, and the complete 4-instruction listing names none through that register |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (4 of 4 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 4-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 4-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'std::int32_t' and the machine return state is WIDTH_4_IN_EAX: the complete 4-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `62c882eaee46a275cff5421da1933890f519130c1a81ab54f31320edefacadef`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `628c65548e56dc1ff1ee85b240e9ca89109700f1915952dc74e8ba87ffab0c4c`
- Pack digest quoted by the briefing: `62c882eaee46a275cff5421da1933890f519130c1a81ab54f31320edefacadef`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- ABI_UNKNOWN: the machine ABI record abstained -- no_discriminator: no stack-argument read and no positive receiver evidence
- ABI_UNKNOWN: the machine ABI record abstained -- receiver_not_determinable: ecx_reassigned_before_deref
- Byte-level confirmation of the four instructions is now recorded (evidence.byte_level_confirmation), including that 83c108 is an in-place ADD with no prior definition of ECX. It changes no verdict: the ABI record still abstains with the same two reasons, so the receiver observation remains an observation and the convention remains unestablished.
- Can any of the seven vtable-slot call sites pass a null or partially constructed receiver? The body has no guard.
- Is the word at receiver+0x8 really this object's reference count? The name comes from the SDK symbol, and a single 32-bit word read cannot distinguish a count from any other counter.
- The record associates seven vtables with this target while the xref export records zero vtable references; the classifier association is unexplained and no slot identity is claimed.
- The source declares __thiscall from a reading of the listing (ECX is never defined before the dereference, the body reads no stack slot, and Ghidra's own decompilation dereferences in_ECX). That observation is not corroborated by the machine ABI record, which names no receiver register, so the convention stays an observation rather than a derived fact.
- What is the concrete type of the receiver, what is the meaning of the 8 bytes below the word, and does the word sit at the end of the object?
- Which MSVC source form produced xor eax,eax / add ecx,8 / lock xadd [ecx],eax / ret, and is the operation intended as an interlocked read or as a fetch_add with a zero operand that some caller variant treats differently?
