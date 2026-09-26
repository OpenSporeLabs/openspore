# Validation 0x00fc7e10

- Aggregate: `WARN`
- Source: `reconstruction/staging/pkg-utfwin-slot7-wave12/utfwin_slot7_wave12.cpp`

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `WARN` | `partial` | source calls exist without a matching named call oracle |
| GLOBALS | `NOT_AVAILABLE` | `none` | no global evidence in the canonical pack |
| FIELDS/OFFSETS | `WARN` | `partial` | type/layout references exist but physical offsets are not proven by this validator |
| CONSTANTS | `WARN` | `partial` | source literals are present; exact binary constant context is not proven |
| CONTROL FLOW | `WARN` | `partial` | source control-flow constructs detected without binary CFG evidence |
| VIRTUAL DISPATCH | `NOT_AVAILABLE` | `none` | no virtual dispatch evidence available |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |
| EVIDENCE COVERAGE | `WARN` | `partial` | 10 of 17 evidence categories are available |

## Unresolved questions

- Do the two arguments form a related pair, such as a callback and its context? 0x00fc7ec0 consumes them together as a call target and a call argument, which is consistent with that reading, but no arithmetic or relation is applied between them in this function.
- Is the return register value intentional? No instruction produces a result in EAX, so the source level return type is unknown; the SDK label says ImageTiling but the body is setter shaped.
- No original-process invocation or indirect-caller trace was captured, so no concrete caller is known and the argument values a real caller passes cannot be observed.
- The declared types of the words at receiver +0x08 and +0x10 are not established. Their observed uses are a CALL target and a call argument respectively, which constrains but does not prove them.
- The owning C++ class name and the interface identity of slot +0x1c are not established. SporeApp.exe carries no MSVC RTTI, so class identity cannot be read from the binary; the 0x01493990 class is known only to derive from the 0x01491730 class because its constructor calls the latter's constructor.
- What is the declared type and role of the word at receiver +0x10? 0x00fc7ec0 passes it as the third stack word to the +0x08 call, so its role is a call argument, but its type is not proven.
- What is the declared type of the word at receiver +0x08? It is executed as a code address by 0x00fc7ec0 and returned as a dword by 0x0093b6c0, but no declared type is proven.
- Whether the +0x10 and +0x14 words belong to the same sub-object as the constructor-initialised words is unresolved; none of the three constructors initialises them.
- Which C++ class owns vtables 0x01491730, 0x01492140 and 0x01493990, and what interface is slot +0x1c of? The 0x01493990 class provably derives from the 0x01491730 class, but no name is recoverable without RTTI.
- Which function does the SDK mean by GetTiling, this setter shaped slot +0x1c or the zero-argument dword read of receiver +0x08 at 0x0093b6c0 in slot +0x20?
- Why do none of the three constructors initialise +0x10 or +0x14 while this target writes +0x10 and 0x00fc7ec0 reads both? Either the constructors rely on zeroed storage, or those words sit in a different sub-object.

Runtime remains `NOT_AVAILABLE` unless an exact original-process trace is supplied.
