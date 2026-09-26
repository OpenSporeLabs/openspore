# Validation 0x00e5b790

- Aggregate: `UNKNOWN`
- Source: `src/reconstruction/pkg_camera_wave7/camera_wave7.cpp`

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `WARN` | `partial` | source call names are present but canonical callee names are not uniformly available |
| GLOBALS | `NOT_AVAILABLE` | `none` | no global evidence in the canonical pack |
| FIELDS/OFFSETS | `WARN` | `partial` | type/layout references exist but physical offsets are not proven by this validator |
| CONSTANTS | `WARN` | `partial` | source literals are present; exact binary constant context is not proven |
| CONTROL FLOW | `WARN` | `partial` | source control-flow constructs detected without binary CFG evidence |
| VIRTUAL DISPATCH | `UNKNOWN` | `partial` | source uses an opaque slot boundary without canonical vtable evidence |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |
| EVIDENCE COVERAGE | `WARN` | `partial` | 10 of 17 evidence categories are available |

## Unresolved questions

- Original Cell-mode Wine trace and live movement-plane values are not available; no runtime promotion is claimed.
- concrete runtime owners and values remain unresolved
- runtime observation required

Runtime remains `NOT_AVAILABLE` unless an exact original-process trace is supplied.
