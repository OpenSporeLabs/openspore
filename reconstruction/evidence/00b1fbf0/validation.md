# Validation 0x00b1fbf0

- Aggregate: `WARN`
- Source: `reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.cpp`

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `WARN` | `partial` | source calls exist without a matching named call oracle |
| GLOBALS | `NOT_AVAILABLE` | `none` | no global evidence in the canonical pack |
| FIELDS/OFFSETS | `WARN` | `partial` | type/layout references exist but physical offsets are not proven by this validator |
| CONSTANTS | `WARN` | `partial` | source literals are present; exact binary constant context is not proven |
| CONTROL FLOW | `WARN` | `partial` | source control-flow constructs detected without binary CFG evidence |
| VIRTUAL DISPATCH | `WARN` | `partial` | source virtual-slot boundary and canonical vtable references are present; slot semantics need review |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |
| EVIDENCE COVERAGE | `WARN` | `partial` | 8 of 17 evidence categories are available |

## Unresolved questions

- Is the address a compiler-folded COMDAT shared by many unrelated 'return true' defaults, or a single default deliberately emitted once? Both fit every observation.
- Is the always-true body a shipped default, a build-configuration stub, or a patch target at runtime? No differential trace has been captured for this function, so runtime patching cannot be excluded.
- No original-process trace has been captured for 0x00b1fbf0, so every claim here is static. A runtime differential test must confirm that the answer is still 1 in the shipping build and that no runtime patch retargets the address.
- The 0x00ee8860 virtual dispatch site must be observed with a concrete receiver before the slot's owning class can be named.
- The 356 and 20 vtable-reference counts are raw pointer-scan totals, not proven distinct vtables. The true count is unmeasured.
- What is the correct port spelling for a slot that is dispatched with ECX populated but implemented as a bare RET? The reconstruction keeps an unread receiver parameter, which is a modelling choice rather than an observed fact.
- What predicate is this? The body is a constant yes, but nothing in the observed evidence names the question it answers.
- Which class or classes own the slots that point here? Three distinct slot offsets across three distinct tables are recorded above and they cannot all describe one method.
- Why does caller 0x00a43050 and caller 0x0082c210 call the function and discard the answer? A constant with no side effects makes those calls no-ops in the observed build.

Runtime remains `NOT_AVAILABLE` unless an exact original-process trace is supplied.
