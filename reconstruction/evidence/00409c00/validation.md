# Validation 0x00409c00

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b04/00409c00_bounding_box_ctor.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 49-instruction listing names 2 data address(es) (0x13eb258, 0x13eb8b0) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 49-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either; the machine-derived receiver record does enumerate 6 displacement(s) (0x0, 0x4, 0x8, 0xc, 0x10, 0x14), which it observed through a register alias rather than through that register's own operands, so the scan is the narrower of the two witnesses here |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (49 of 49 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 49-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 49-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `202c87b8674ad3261ab0ef75bcf7083a14a2d15288491bbe6b60aef084eb878f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `98938aec3e65a47a966590d0764747cc14cc1d8af9b2a50654ee325410a2378e`
- Pack digest quoted by the briefing: `202c87b8674ad3261ab0ef75bcf7083a14a2d15288491bbe6b60aef084eb878f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace has been captured. Whether any of the 28 callsites actually passes the constructed object on to a union or intersection without overwriting it first is a runtime fact.`, `Runtime patching of either global constant cannot be excluded statically; both were read from the on-disk image only.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Do all 24 uninspected callsites pass the result as an out-parameter, or do some keep it as a member? The four inspected ones all do.
- Is the inverted state read back anywhere as a sentinel - for example a containment test that relies on it - or is it only ever an initial value? No reader was identified.
- Is the type really Math::BoundingBox? The 24-byte size and the 0x0C second-vector offset match the SDK declaration exactly, but any other 24-byte aggregate of two unaligned 12-byte vectors would match equally well, and the binary names it nowhere.
- No original-process trace has been captured. Whether any of the 28 callsites actually passes the constructed object on to a union or intersection without overwriting it first is a runtime fact.
- Runtime patching of either global constant cannot be excluded statically; both were read from the on-disk image only.
- The neighbouring constants at 0x013eb254 (00 00 80 00) and 0x013eb260 (ff ff ff 7f) were read while locating the real one and are recorded as context only. Whether they belong to the same table of float constants, and what else references them, was not investigated.
- Why is the constructor out of line? Six constant stores would normally be inlined; the 28 direct callsites and 0 vtable references argue against a virtual override, so an unoptimised translation unit or an address taken somewhere is the likely explanation, and neither was checked.
