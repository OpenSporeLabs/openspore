# Validation 0x00c37360

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 2-instruction listing names 1 data address(es) (0x168df68) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9ed7c448825143cfe1aa7cb0d51384ebaa1e3fa08d2d42beef17f469dae90051`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9cd3397ca398726504205ec87747829e3c23fe0ca111f2c45999e273b35610d9`
- Pack digest quoted by the briefing: `9ed7c448825143cfe1aa7cb0d51384ebaa1e3fa08d2d42beef17f469dae90051`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential test must confirm that 0x00b60d80 is the only creator of the slot and that no runtime patch retargets 0x0168df68.`, `No original-process trace has been captured for 0x00c37360, so the claim that the slot is non-null during a live Cell stage is static-only.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential test must confirm that 0x00b60d80 is the only creator of the slot and that no runtime patch retargets 0x0168df68.
- Is 0x00f473a0(0x1bc, "Simulator", ...) a generic app-system factory whose name argument is a registry key, or a bespoke Simulator constructor? The 0x00f473a0 body is a six-argument forwarder to 0x009289f0 and does not settle it.
- No original-process trace exists for any function in this batch. Every statement here is static.
- No original-process trace has been captured for 0x00c37360, so the claim that the slot is non-null during a live Cell stage is static-only.
- Of the 40 call sites, only 0x00b6154e was disassembled; the result use at the other 39 is unverified.
- The binary carries no MSVC RTTI, so no class identity can be read from typeinfo; class claims in this record rest only on observed vtable data and SDK header text.
- What is the class of the object behind 0x0168df68? Only its vtable address 0x0146bb78 and its 0x1bc allocation size are observed; no RTTI and no SDK declaration identifies it.
- Why do 0x00b5f1d0 and 0x00c3762a read the global inline rather than calling 0x00c37360? The two spellings are byte-equivalent, so the difference is a compilation artefact, not a semantic one.
