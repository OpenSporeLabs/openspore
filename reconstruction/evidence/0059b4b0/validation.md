# Validation 0x0059b4b0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 721-instruction listing names 27 data address(es) (0x13eb1bc, 0x13eb8b0, 0x13ec5b4, 0x13f4fd0, 0x13f6480, 0x13f64b0, 0x13f9428, 0x1465544, 0x1470f1c, 0x1471064, 0x1485378, 0x1485548, 0x1485720, 0x150de50, 0x150dfdc, 0x150dfe0, 0x150dfe4, 0x150dfe8, 0x15e590c, 0x15e5910, 0x15e5914, 0x15e5a0c, 0x15e5a10, 0x15e5a14, 0x15e5a88, 0x15e5a8c, 0x15e5a90) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span declares 0 displacement(s) (none) and the alias-aware scan of the listing attributes 3 receiver displacement(s) (0x8, 0xc, 0x4c) to ECX, so nothing the source states is missing from what the machine shows; but the listing is not known to be the whole body (it was not consumed in full by the machine parse (717 of 721 instruction(s) read, degraded=True, unparsed=4)), so that enumeration is a lower bound and is reported as one rather than as a pass; the 721-instruction listing is the governing witness for what this body reaches -- it was not consumed in full by the machine parse (717 of 721 instruction(s) read, degraded=True, unparsed=4) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x8, 0xc, 0x4c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 21 displacement(s) (0x8, 0xc, 0x20, 0x24, 0x44, 0x48, 0x4c, 0x50, 0x54, 0x55, 0x58, 0x5c, 0x60, 0x64, 0x68, 0x6c, 0x74, 0x78, 0x7c, 0x80, 0x84), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 18 of those (0x20, 0x24, 0x44, 0x48, 0x50, 0x54, 0x55, 0x58, 0x5c, 0x60, 0x64, 0x68, 0x6c, 0x74, 0x78, 0x7c, 0x80, 0x84) the scan does not attribute to the receiver, and the listing governs there; all of that is a lower bound: the evidence is not known to be the whole body, so no absence is claimed from it |
| CONSTANTS | `WARN` | `partial` | the machine listing is not fully parsed: 721 of 721 instruction(s) consumed, degraded=True, unparsed=4 |
| CONTROL FLOW | `PASS` | `complete` | all 31 conditional branch target(s) in the complete 721-instruction listing lie inside the recovered body span 0x0059b4b0..0x0059c00c, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 721-instruction body names 5 indirect transfer(s): 0x0059b51a dispatches slot 0x58 through the table word in EDX; 0x0059b52d dispatches slot 0x40 through the table word in EDX; 0x0059b589 dispatches slot 0x5c through the table word in EDX; 0x0059bf0c dispatches slot 0x28 through the table word in EDX; 0x0059bf76 dispatches slot 0x24 through the table word in EDX; the machine parse consumed 721 of 721 instruction(s) with 4 unparsed and degraded=True, and the machine dispatch record independently counts 5, so the dispatch is visible in the machine listing but is not proven: the machine parse is degraded and 4 instruction(s) were left unparsed |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 1 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ee0812a68810d1a79a8985233a78463b6a156949e8a4266a900d125b2fe3f41a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3b201638e9692cc904ca1b5ebae0286061f2a11a3af290028f7f0c08277af74c`
- Pack digest quoted by the briefing: `ee0812a68810d1a79a8985233a78463b6a156949e8a4266a900d125b2fe3f41a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Runtime values of the injected basis words 0x015e5a0c/0x10/0x14, 0x015e5a88/0x8c/0x90 and 0x015e590c/0x015e5910/0x015e5914, which read as zero in the file image`, `Semantics of the 0x00699600, 0x0069b840 and 0x0069b760 helpers (lerp, angle lerp and projection are inferred from usage, not owned)`, `Semantics of the 0x00699600, 0x0069b840 and 0x0069b760 helpers (lerp, angle lerp and projection are inferred from usage, not owned); Runtime values of the injected basis words 0x015e5a0c/0x10/0x14, 0x015e5a88/0x8c/0x90 and 0x015e590c/0x015e5910/0x015e5914, which read as zero in the file image; The four-argument contract of the creature bounds callback beyond the two output slots and two literal zeros; The AnimatedCreature vtable at controller+0x08 and its slots 0x58 and 0x5c; The eight-slot IShadowWorld raycast argument record; The picking helper 0x0067dd80 and its vtable slot 0x28 return value; The meaning of controller+0x1c and of the 0x0059b390 publication port; Whether a zero-length current offset is reachable; the binary produces 1.0f/0.0f = +inf and then 0.0f*inf = NaN, which this reconstruction reproduces but does not test numerically`, `The AnimatedCreature vtable at controller+0x08 and its slots 0x58 and 0x5c`, `The eight-slot IShadowWorld raycast argument record`, `The four-argument contract of the creature bounds callback beyond the two output slots and two literal zeros`, `The meaning of controller+0x1c and of the 0x0059b390 publication port`, `The picking helper 0x0067dd80 and its vtable slot 0x28 return value`, `Whether a zero-length current offset is reachable; the binary produces 1.0f/0.0f = +inf and then 0.0f*inf = NaN, which this reconstruction reproduces but does not test numerically`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Runtime values of the injected basis words 0x015e5a0c/0x10/0x14, 0x015e5a88/0x8c/0x90 and 0x015e590c/0x015e5910/0x015e5914, which read as zero in the file image
- Semantics of the 0x00699600, 0x0069b840 and 0x0069b760 helpers (lerp, angle lerp and projection are inferred from usage, not owned)
- Semantics of the 0x00699600, 0x0069b840 and 0x0069b760 helpers (lerp, angle lerp and projection are inferred from usage, not owned); Runtime values of the injected basis words 0x015e5a0c/0x10/0x14, 0x015e5a88/0x8c/0x90 and 0x015e590c/0x015e5910/0x015e5914, which read as zero in the file image; The four-argument contract of the creature bounds callback beyond the two output slots and two literal zeros; The AnimatedCreature vtable at controller+0x08 and its slots 0x58 and 0x5c; The eight-slot IShadowWorld raycast argument record; The picking helper 0x0067dd80 and its vtable slot 0x28 return value; The meaning of controller+0x1c and of the 0x0059b390 publication port; Whether a zero-length current offset is reachable; the binary produces 1.0f/0.0f = +inf and then 0.0f*inf = NaN, which this reconstruction reproduces but does not test numerically
- The AnimatedCreature vtable at controller+0x08 and its slots 0x58 and 0x5c
- The eight-slot IShadowWorld raycast argument record
- The four-argument contract of the creature bounds callback beyond the two output slots and two literal zeros
- The meaning of controller+0x1c and of the 0x0059b390 publication port
- The picking helper 0x0067dd80 and its vtable slot 0x28 return value
- Whether a zero-length current offset is reachable; the binary produces 1.0f/0.0f = +inf and then 0.0f*inf = NaN, which this reconstruction reproduces but does not test numerically
- concrete runtime owners and values remain unresolved
