# Validation 0x0059c190

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-pilot-gameglobal-b03/59c190_quaternion_to_float3x3.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 79-instruction listing names 2 data address(es) (0x1470f1c, 0x1485720) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (79 of 79 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 79-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 79-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `5aef5a1d4232368733d3259b2c9306b7f343a22213fb876fd879e32fe79f882e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `fb86024cd4b3a6512a4049b98ef63fadb5ee029b381b8135b5f399343785350c`
- Pack digest quoted by the briefing: `5aef5a1d4232368733d3259b2c9306b7f343a22213fb876fd879e32fe79f882e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential test must also confirm that at least one caller supplies a unit quaternion, since the body has no normalisation and produces a non-orthonormal matrix otherwise.`, `A differential test must confirm that the destination really receives the same 36 bytes at run time, i.e. that no runtime patch retargets 0x0041cb40 or the two float constants.`, `No original-process trace exists for 0x0059c190. Every statement here is static.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential test must also confirm that at least one caller supplies a unit quaternion, since the body has no normalisation and produces a non-orthonormal matrix otherwise.
- A differential test must confirm that the destination really receives the same 36 bytes at run time, i.e. that no runtime patch retargets 0x0041cb40 or the two float constants.
- Do all 113+ call sites pass a unit quaternion, or does the engine rely on this being a raw formula? Static analysis cannot answer that; it needs a runtime trace or a caller-by-caller normalisation audit.
- Is the quaternion actually stored as (x,y,z,w) in the caller's struct, or does some caller pass a (w,x,y,z) quaternion that the engine happens to treat correctly? The formula constrains the order, but not the caller's intent.
- Is this Quaternion::ToMatrix() itself, a free helper that Quaternion::ToMatrix() calls, or a static member? The argument shape rules out a thiscall member but not the first two.
- No original-process trace exists for 0x0059c190. Every statement here is static.
- What are the other two addresses labelled QuaternionToMatrix (0x0059bef0, 0x004a9a40) in this build, and are their bodies identical? 0x0059bef0 is not a function start in 3.1.0.22 and 0x004a9a40 was not inspected in this batch.
- What is the destination type? Only size 36 and a three-float3 layout are observed. 'Math::Matrix3' is a candidate from Spore ModAPI/Spore/MathUtils.h, not a proven identity.
- Why does the body spill q.x*q.z into its own incoming argument slot ([ESP+0x3c] at 0x0059c1d7) and re-read it three times? It is legal and harmless, but it is compiler scratch reuse, not a contract.
