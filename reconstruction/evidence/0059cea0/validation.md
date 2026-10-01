# Validation 0x0059cea0

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
| GLOBALS | `PASS` | `complete` | the complete 35-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 35-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x8, 0x38), all of which the record accounts for or the listing is the better witness on; the 35-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=35, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x8, 0x38) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x38), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0x8), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (35 of 35 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 35-instruction listing lie inside the recovered body span 0x0059cea0..0x0059cef5, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 35-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `140f4b6de76779fdae1b816fd2031dff117c93d0b9d7a528dbc397f792e91d74`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ca18011c51f93135e587e4f7e317da5be73cf375144a6003cb8e4901d118c95c`
- Pack digest quoted by the briefing: `140f4b6de76779fdae1b816fd2031dff117c93d0b9d7a528dbc397f792e91d74`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Angle units and wrap domain of controller+0x44/+0x48`, `Angle units and wrap domain of controller+0x44/+0x48; Injected at runtime through g_fixed_basis (OpaqueFixedBasis). The file image holds zeros at every one of these addresses, so the reconstruction never promotes a compiled-in value: normalize_epsilon models 0x015e590c/0x015e5910/0x015e5914, orientation models 0x015e5a0c/0x015e5a10/0x015e5a14 and projection models 0x015e5a88/0x015e5a8c/0x015e5a90. Every consumer is a gate until those words are observed at runtime.; Which editor command sites drive SetTargetAngle at runtime`, `Injected at runtime through g_fixed_basis (OpaqueFixedBasis). The file image holds zeros at every one of these addresses, so the reconstruction never promotes a compiled-in value: normalize_epsilon models 0x015e590c/0x015e5910/0x015e5914, orientation models 0x015e5a0c/0x015e5a10/0x015e5a14 and projection models 0x015e5a88/0x015e5a8c/0x015e5a90. Every consumer is a gate until those words are observed at runtime.`, `Which editor command sites drive SetTargetAngle at runtime`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Angle units and wrap domain of controller+0x44/+0x48
- Angle units and wrap domain of controller+0x44/+0x48; Injected at runtime through g_fixed_basis (OpaqueFixedBasis). The file image holds zeros at every one of these addresses, so the reconstruction never promotes a compiled-in value: normalize_epsilon models 0x015e590c/0x015e5910/0x015e5914, orientation models 0x015e5a0c/0x015e5a10/0x015e5a14 and projection models 0x015e5a88/0x015e5a8c/0x015e5a90. Every consumer is a gate until those words are observed at runtime.; Which editor command sites drive SetTargetAngle at runtime
- Injected at runtime through g_fixed_basis (OpaqueFixedBasis). The file image holds zeros at every one of these addresses, so the reconstruction never promotes a compiled-in value: normalize_epsilon models 0x015e590c/0x015e5910/0x015e5914, orientation models 0x015e5a0c/0x015e5a10/0x015e5a14 and projection models 0x015e5a88/0x015e5a8c/0x015e5a90. Every consumer is a gate until those words are observed at runtime.
- Which editor command sites drive SetTargetAngle at runtime
- concrete runtime owners and values remain unresolved
