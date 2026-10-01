# Validation 0x00c0b780

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b08/c0b780_sub_object_flag_608.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 6-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 6-instruction listing names through ECX (0xb20) are all within the machine-derived receiver bounds (0xb20, 0x1128), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (6 of 6 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 6-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 6-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `086e9462f43e6106d0e18de842b36aa537f283dabbc722939b3682b3b2f18d58`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `c8a3266776b3f593097c5641d3f8484c4dfb22ba9f18d934ae4426c15630c3b2`
- Pack digest quoted by the briefing: `086e9462f43e6106d0e18de842b36aa537f283dabbc722939b3682b3b2f18d58`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists for 0x00c0b780. A differential run must confirm the answer is still 0/1 in the shipping build and that no runtime patch retargets it.`, `The non-null invariant on receiver+0xB20 must be observed at a concrete callsite before any caller-side guard can be claimed.`, `The value of the dword at +0x608, and of the sibling at +0x60C, at the moment 0x00ba27b0 reads them, can only be established at runtime.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are +0x608 and +0x60C two independent dwords, a bitfield, or two slots of a small dispatch array? Only their offsets and non-zero-ness are observed.
- Is the sub-object at +0xB20 ever null in the shipping build? If it can be, this body faults and the caller-side invariant is unverified without a runtime trace.
- No original-process trace exists for 0x00c0b780. A differential run must confirm the answer is still 0/1 in the shipping build and that no runtime patch retargets it.
- The non-null invariant on receiver+0xB20 must be observed at a concrete callsite before any caller-side guard can be claimed.
- The value of the dword at +0x608, and of the sibling at +0x60C, at the moment 0x00ba27b0 reads them, can only be established at runtime.
- Twelve of the eighteen recorded callsites were not individually disassembled, so their receiver setup and result use are recorded from the canonical xref list only.
- What do the return codes 1, 2, 3, 4 and 6 of 0x00ba27b0 mean? Code 5 is never produced by the observed body, which suggests an enumeration this worker cannot name.
- What is the owning type of the receiver? No vtable for it was located and this binary has no RTTI, so nothing beyond the offsets +0xB20 and +0xB88 can be claimed.
- What is the owning type of the sub-object at receiver+0xB20? Only the offsets 0x544, 0x608 and 0x60C inside it are observed.
- What predicate does the dword at +0x608 express? The body proves it is a non-zero test and nothing more.
- Why does 0x00c0b7b8 exist, and what does it do with the 0x60C slot? Its body was read only far enough to establish the flag offset.
