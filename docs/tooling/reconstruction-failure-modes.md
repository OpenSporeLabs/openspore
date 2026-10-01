# Reconstruction worker failure modes

Patterns that recur across reconstruction waves, with the evidence that
establishes each one and the check that fires. Measured on the 2026-09-28 large
swarm: 61 child sessions, 43 fresh targets, 24 promotions.

Each entry is a **check the validator already fires** plus a shape that satisfies
it without falsifying anything. None of these is a reason to weaken a check; they
are reasons a candidate has the wrong *shape* for the evidence it claims.

---

## 1. A zero displacement is an ABSENCE, not a constant

**Fires as:** `CONSTANTS: FAIL`. Seen 4× in one wave, all four from the same
spelling.

`validate._hex_tokens` extracts every `0x...` literal from the target span and
requires each to appear in the machine listing. But several x86-32 encodings
carry **no displacement byte at all**, so the listing prints the operand bare:

| encoding | instruction text | displacement operand |
|---|---|---|
| `8B 06` | `MOV EAX, dword ptr [ESI]` | none |
| `8B 41 18` | `MOV EAX, dword ptr [ECX + 0x18]` | `0x18` |
| `C7 06 38 B9 3E 01` | `MOV dword ptr [ESI], 0x13eb938` | none |

Writing `*word_at(self, 0x00)` or `*(Word*)(self + 0x0)` therefore states the
literal `0x0`, which the listing does not contain — a FAIL, even though the
reconstruction is byte-for-byte correct.

**Shape that passes:** a bare base load, or the header's *named* displacement
constant when one already exists:

```cpp
// 0x00641783 is 8B 06: a bare [ESI] with no displacement byte, so the zero
// offset is the absence of an operand, not a constant the machine states.
Word* const table = *reinterpret_cast<Vtable* const*>(self);
```

## 2. A `bounds_only` receiver forbids member NAMES, not displacements

**Fires as:** `FIELDS/OFFSETS: WARN`. Seen 7×, and the check's own wording is
the whole rule: *"the field's identity is not corroborated by it"* and *"it is the
name alone that is the review item"*.

The machine-derived `receiver` record is `bounds_only` on most packs. It fixes
*where* the body reached (`offsets`, `max_offset`) and never *which member* is
which. So a struct member name is an unverifiable layout claim, while a
displacement is a local fact the record corroborates.

**Shape that passes:** an opaque byte run plus displacement-named accessors, with
each displacement a `constexpr` pinned by a `static_assert` to its instruction.

```cpp
constexpr std::size_t kFieldDisplacement = 0x6c;
static_assert(kFieldDisplacement == 0x6c, "MOV EAX,DWORD PTR [ECX+0x6C] @ 0x00a649a0");
std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);
return word_at(self, kFieldDisplacement);
```

Corollary: rewriting `offsetof(T, member)` assertions is expected when a member
is removed — replace with an arithmetic assertion between the constants, not by
dropping the check.

## 3. `return_semantics` is a register CLASS, not a C type

**Fires as:** `RETURN SEMANTICS: WARN` ("return type differs or is semantically
renamed"). Seen 19× — the single largest blocker in the wave.

The derived ABI layer renders `return_semantics` in its own vocabulary
(`unclassified_in_EAX`, `pointer_like_in_EAX`, `integral_in_EAX`,
`float_or_x87_in_ST0`, `aggregate_unknown_in_EAX`); the persisted layer renders it
as prose. A survey of every committed pack found **no** `return_semantics` value
that is a C or C++ type name. The sidecar's `abi.return_type` is the canonical
*type* claim, and it is compared against the source span's declared type.

**Shape that passes:** the sidecar's `abi.return_type` states exactly the type the
source span declares, *provided that type is true of the listing*; the machine
phrase goes in a separate field and is never typedef'd after.

| listing fact | declared type |
|---|---|
| `8A 41 24` (partial write), all exits write `AL` only | one byte |
| `8B 41 6C`, caller stores the full word | 32-bit |
| `MOV EAX,ESI` on every exit | `void` |

Never write `typedef ... unclassified_in_EAX;` to make the string match. That
satisfies a comparison and nothing in the machine.

## 4. A `return_type` the checker cannot measure is a NOT_AVAILABLE

**Fires as:** `RETURN SEMANTICS: NOT_AVAILABLE` — *"whose width cannot be
computed from the declaration (a typedef, a class, a template or an alias)"*.

The strict route compares **widths**, and it needs the declared type's width.
`using Word = std::uint32_t;` as a return type is unmeasurable.

**Shape that passes:** the function's *declared return type* is a width-computable
builtin; the alias may stay for everything else (receiver fields, test fixtures).

```cpp
using Word = std::uint32_t;        // still the receiver's word
std::uint32_t re_005b2490(...);    // but the RETURN is width-computable
```

## 5. A `g++` green build is not the gate

**Fires as:** the promotion gate's build/ctest step. Seen 8×, in eight packages
whose own `g++ -m32 -Wall -Wextra -Werror` build was clean.

The gate is **`clang++ -std=c++17 -Wall -Wextra -Werror -m32`**, and it links the
package as a **static library**. Classes that g++ cannot see:

| class | gate error |
|---|---|
| orphaned `constexpr` (a repair rewrote its last use) | `-Wunused-const-variable` |
| `class X;` forward-declared, `struct X` defined | `-Wmismatched-tags` |
| `__attribute__((naked))` containing a C statement | "non-ASM statement in naked function" |
| a side-effecting call inside `decltype`/`static_assert` | `-Wunevaluated-expression` |
| `uint32_t` compared against `SIZE_MAX/2` | `-Wtautological-constant-out-of-range` |
| aggregate of `std::string` initialised with `{"a","b"}` | `-Wmissing-braces` |
| an asm block calling through a register it does not clobber-list | SIGSEGV at run time |

Reproduce the gate exactly, including the archive step, before answering:

```sh
clang++ -std=c++17 -Wall -Wextra -Werror -m32 -I"$D" -c "$D"/<src>.cpp  -o /tmp/s.o
clang++ -std=c++17 -Wall -Wextra -Werror -m32 -I"$D" -c "$D"/<test>.cpp -o /tmp/t.o
ar qc /tmp/p.a /tmp/s.o && ranlib /tmp/p.a
clang++ -Wall -Wextra -Werror -m32 /tmp/t.o -o /tmp/p_test /tmp/p.a && /tmp/p_test
```

## 6. clang's outgoing-argument area makes ESP DEPTH non-portable

**Fires as:** a CTest failure on a check that compares two call sites' stack
depth. Seen 3×, all from the same root cause.

On x86-32 at `-O0`, **clang never materialises a `push` for a cdecl/`__thiscall`
stack argument**: it stores the word into the outgoing-argument area at the
current `%esp` and lets the callee's terminator take it. g++ emits a real
`pushl` plus alignment padding.

```
clang:  movl $0x7,(%esp) ; call *%eax ; subl $0x4,%esp     -> entry ESPs equal
g++:    subl $0xc,%esp ; pushl $0x7 ; call *%eax ; addl $0xc,%esp -> differs by 16
```

So `esp_site_A > esp_site_B` is a statement about compiler scratch layout. And
because the reconstruction's own call sites collapse identically, **no reference
can produce a matching non-zero difference** — hand-writing the reference in asm
destroys the cancellation that makes the differential portable.

**Shape that passes:** measure through the **callee's own entry frame** and the
**caller's net stack effect**, both of which are ABI facts:

- at a callee's entry, `[ESP+4]` is the first stack argument on every compiler;
- the substantive claim is *whether the callee finds a word there*, not how deep
  the caller sat when it called;
- frame shape is read as "the caller's ESP before the call equals its ESP after
  the call returns".

Keep the case label and the check's wording recognisable; replace the channel,
never the substance, and add a mutant that injects the defect the old check
existed to catch.

## 7. The target span binds on the VA token — one definition may hold it

`validate._target_span` locates a target by finding the 8-hex VA as a substring
of a symbol name. A second definition in the same file that also carries the VA
wins if it comes first, and the wrong function is then graded.

**Symptom:** checks that plainly should pass report the *other* function's
return type or missing calling convention.

**Shape that passes:** exactly one symbol in the package embeds the target VA —
the reconstructed one. A helper that merely computes something gets a name with
**no address in it** (a name carrying an address is also read as a direct call
target, which turns `CALLS` into a FAIL).

## 8. A `static_assert` message is source text

`CONSTANTS` runs over `_code(text)`, which strips line and block comments, so a
hex literal in a comment is never the problem — but a hex literal inside a
`static_assert`'s *message string* is, because that string is a live
expression operand. Same for a `constexpr` declared only to satisfy one.

See §1 and §5; both ends of the same rule.
