# Validation 0x008db310

- Aggregate: `NOT_AVAILABLE`
- Source: `missing`

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | no canonical source artifact |
| GLOBALS | `NOT_AVAILABLE` | `none` | no canonical source artifact |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | no canonical source artifact |
| CONSTANTS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CONTROL FLOW | `NOT_AVAILABLE` | `none` | no canonical source artifact |
| VIRTUAL DISPATCH | `NOT_AVAILABLE` | `none` | no canonical source artifact |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |
| EVIDENCE COVERAGE | `WARN` | `partial` | 7 of 17 evidence categories are available |

## Unresolved questions

- Concrete ItemsMap node and bucket ownership semantics
- The vtable/data-table owner that reaches this otherwise uncalled function
- Whether destination_size is a byte count or a target index extent in all callers

Runtime remains `NOT_AVAILABLE` unless an exact original-process trace is supplied.
