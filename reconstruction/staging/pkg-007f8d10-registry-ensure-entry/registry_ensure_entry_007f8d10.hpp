// 0x007f8d10 — 0x007f8d10..0x007f8ef0, 158 instructions.
//
// __thiscall, three 4-byte callee-cleaned stack arguments (`RET 0xc`).
// Receiver in ECX.  See registry_ensure_entry_007f8d10.cpp for the annotated
// listing, the x87 balance trace, and everything this reconstruction does NOT
// claim.
//
// Every field name below is offset-derived, never semantic. SporeApp.exe
// carries no MSVC RTTI, so no owning class is asserted anywhere in this file.

#ifndef OPENSPORE_PKG_007F8D10_REGISTRY_ENSURE_ENTRY_007F8D10_HPP
#define OPENSPORE_PKG_007F8D10_REGISTRY_ENSURE_ENTRY_007F8D10_HPP

#include <cstddef>
#include <cstdint>

namespace openspore::pkg_007f8d10 {

// The two fixed words the element carries.  0x007f8dea stores 0x013f6400 and
// 0x007f8df2 stores 0x013f63fc; 0x007f6d90 re-stores the same two constants at
// destination +0x08 and +0x10, which is the shape of an MSVC assignment
// operator re-establishing its own vptrs.
//
// The committed edge export records both stores as vtable-ref rows that collapse
// to the base 0x013f63fc and discards the slot addresses.  /tmp/opencode/vt-ranges.tsv
// gives 0x013f63fc -> 15 slots, and 0x013f6400 is exactly four bytes past it,
// i.e. slot 1 of the same table.  That adjacency is arithmetic on the two
// immediates the listing shows; the contents of those slots were not read, and
// no indirect transfer in this body dispatches through either word, so no slot
// index and no callee is claimed for them.
inline void** const kElementVtableA = reinterpret_cast<void**>(0x013f6400u);
inline void** const kElementVtableB = reinterpret_cast<void**>(0x013f63fcu);

// Element stride: the signed division at 0x007f8d47..0x007f8d6f uses the
// 0x78787879 / SAR 6 magic for 0x88, and 0x007f8db0 (`ADD EBP,0x88`),
// 0x007f8e03 (`LEA EDX,[ECX+0x88]`) and 0x007f8e83 (`IMUL EDI,EDI,0x88`) all
// advance by 0x88.  0x88 == 136.
inline constexpr std::uint32_t kElementStride = 0x88u;

// ---------------------------------------------------------------------------
// Receiver: the container at ECX
// ---------------------------------------------------------------------------
// 0x007f8d3f `LEA ESI,[ECX + 0x4]` and every later access through ESI give
// begin/end/capacity at receiver+0x04/+0x08/+0x0c.  receiver+0x00 is the
// allocation base: 0x007f8820 frees it through 0x00f47380 and tests the word at
// [base-4], the EASTL block-header flag.  receiver+0x1c is the single byte the
// body writes, at 0x007f8ee4.  Nothing between +0x10 and +0x1b is touched.
struct Registry {
    void* alloc_base;          // +0x00
    std::uint8_t* begin;       // +0x04
    std::uint8_t* end;         // +0x08
    std::uint8_t* capacity;    // +0x0c
    std::uint8_t pad_10_to_1b[0x0c];
    std::uint8_t flag_1c;      // +0x1c  — set to 1 at 0x007f8ee4
    std::uint8_t pad_1d_to_1f[0x03];
};
static_assert(sizeof(Registry) == 0x20, "receiver offsets are fixed by the listing");

// ---------------------------------------------------------------------------
// The 0x80-byte object embedded at element+0x08
// ---------------------------------------------------------------------------
// 0x007f8e2e / 0x007f8ebb / 0x007f8ed8 pass element+0x08 as the receiver of
// 0x007f8e35 and 0x007f8ed9, and both take their callee from element+0x0c, i.e.
// +0x04 of this object — so +0x04 is the dispatch word, not a vptr slot.  Its
// value is copied from argument 1 by 0x007f6ff0 (`MOV [param_1+4],[param_2+4]`
// with param_1 = element+0x08), which is the same word 0x007f8d31 tests for
// null before anything else happens.  +0x00 and +0x08 are the two constants
// above; +0x0c is a refcounted word (0x007f6ff0 retain-swaps it from
// argument 1 + 0x0c and releases the old one through its own slot 1); +0x10
// receives the 0x70 bytes 0x007f6ff0 copies from argument 1 + 0x10.
struct Handle;

// The function pointer 0x007f8e35 and 0x007f8ed9 call through.  Arguments are
// the two 0.0f literals the body materialises, then two 32-bit words.
using SubCallback = void (*)(void* self, float arg2, float arg3, std::uint32_t arg4,
                             std::uint32_t arg5);

struct ElementSub {
    void** vtable_00;          // element+0x08 — 0x013f6400
    SubCallback callback_04;   // element+0x0c — the dispatched word
    void** vtable_08;          // element+0x10 — 0x013f63fc
    Handle* handle_0c;         // element+0x14 — retain-swapped
    std::uint8_t body_10[0x70];
};
static_assert(sizeof(ElementSub) == 0x80, "element+0x08..+0x87 is one object");
static_assert(offsetof(ElementSub, callback_04) == 0x04, "dispatch word at sub+0x04");
static_assert(offsetof(ElementSub, handle_0c) == 0x0c, "retained word at sub+0x0c");

// ---------------------------------------------------------------------------
// Element: 0x88 bytes
// ---------------------------------------------------------------------------
// +0x00 is compared against stack argument 2 (0x007f8d80) and against the
// incoming slot value (0x007f8e8d); +0x04 against stack argument 3 (0x007f8d90)
// and receives it at 0x007f8ebd.
struct Element {
    void* key_00;              // element+0x00
    std::uint32_t selector_04; // element+0x04
    ElementSub sub_08;         // element+0x08
};
static_assert(sizeof(Element) == kElementStride, "stride is 0x88");
static_assert(offsetof(Element, selector_04) == 0x04, "");
static_assert(offsetof(Element, sub_08) == 0x08, "");

// ---------------------------------------------------------------------------
// Handle
// ---------------------------------------------------------------------------
// A handle is reached only through its own leading vtable word.  Slot 0 is
// dispatched on the key being installed (0x007f8e94/0x007f8e98) and, inside
// 0x007f6d90, on each copied source handle (0x007f6da1/0x007f6da5,
// 0x007f6dcb/0x007f6dcf).  Slot 1 is dispatched on the prototype's two handles
// during teardown (0x007f8e6f/0x007f8e72, 0x007f8e7e/0x007f8e81) and on a
// displaced handle (0x007f8ea2/0x007f8ea7).  No callee is named for either.
struct Handle {
    void** vtable_00;
};

// ---------------------------------------------------------------------------
// Stack prototype: 0x88 bytes at the bottom of the frame
// ---------------------------------------------------------------------------
// The frame reserves 0x8c bytes (0x007f8d10); the receiver is spilled at
// frame_bottom+0 (E0-0x8c, 0x007f8d1e) and the prototype starts at
// frame_bottom+4 (E0-0x88), so it spans exactly one element.  0x007f8de6 and
// 0x007f8dfa zero prototype+0x00 and +0x14; 0x007f8dea and 0x007f8df2 store the
// two constants at +0x08 and +0x10.  The remaining 0x80 bytes are never written
// by this body and are consumed by 0x007f6d90, which copies all 0x88 bytes — so
// they are modelled as indeterminate rather than invented.  That is not a latent
// defect: the only words of the new element the body later reads are +0x00,
// +0x04, +0x08 (a constant), +0x0c, +0x10 (a constant), +0x14 and +0x18..+0x87,
// and every one of those except the two constants is overwritten before use.
struct Proto {
    Handle* handle_00;             // +0x00  = NULL
    std::uint8_t indeterminate_04[0x04];
    void** vtable_08;              // +0x08  = 0x013f6400
    std::uint8_t indeterminate_0c[0x04];
    void** vtable_10;              // +0x10  = 0x013f63fc
    Handle* handle_14;             // +0x14  = NULL
    std::uint8_t indeterminate_18[0x70];
};
static_assert(sizeof(Proto) == kElementStride, "prototype is one element wide");
static_assert(offsetof(Proto, vtable_08) == 0x08, "");
static_assert(offsetof(Proto, vtable_10) == 0x10, "");
static_assert(offsetof(Proto, handle_14) == 0x14, "");

// 0x007f6d90 — `RET 0x4`, ECX is the destination.  Its body (34 instructions,
// read back from the image) does, in order:
//   dest[0x00] = src[0x00], dispatching slot 0 on it when non-null
//   dest[0x04] = src[0x04]
//   dest[0x08] = 0x013f6400
//   dest[0x0c] = src[0x0c]
//   dest[0x10] = 0x013f63fc
//   dest[0x14] = src[0x14], dispatching slot 0 on it when non-null
//   dest[0x18 .. 0x88) = src[0x18 .. 0x88)   (REP MOVSD, 0x1c dwords)
// It returns its destination; the caller discards it.
void proto_copy_assign_007f6d90(void* dest, const void* src) noexcept;

// 0x007f8820 — receiver-carrying grow helper, called as
//   registry_place_one_more_007f8820(this, old_end, &proto)
// Observed from its body: when [this+0x08] != [this+0x0c] it moves the last live
// element into the new slot with 0x007f7c00(old_end, end-0x88, end), makes a
// one-argument call on &proto with 0x007f7920, and bumps [this+0x08] by 0x88.
// Otherwise it allocates (count ? 2*count : 1) * 0x88 through 0x00f473a0 (the
// EASTL allocator.h site, source line 0xd1), moves the live range with
// 0x007f6ee0/0x007f6f80, frees the old block through 0x00f47380, and rewrites
// begin/end/capacity.
//
// The two initialisation routes are NOT the same and only the first is
// resolved: the in-place route of 0x007f8d10 initialises the new element from
// the prototype (0x007f6d90), whereas this route's 0x007f7c00 initialises it
// from the last live element.  What the new element's +0x00 holds on this route
// is therefore not established here, and it matters: it decides whether
// 0x007f8ea7 releases a displaced handle.  See unresolved_questions.
void registry_place_one_more_007f8820(Registry* self, const void* old_end,
                                      const void* proto) noexcept;

// 0x007f6ff0 — called as element_assign_template_007f6ff0(element+0x08, arg1).
// Observed from its body: sub+0x04 = arg1+0x04; the word at sub+0x0c is
// retain-swapped from arg1+0x0c (dispatch slot 0 on the new value, slot 1 on the
// value it displaced, and only when the two differ); then 0x70 bytes are copied
// from arg1+0x10 to sub+0x10.  It returns its receiver; the caller discards it.
void element_assign_template_007f6ff0(ElementSub* self, const void* src) noexcept;

// The two dispatches through the element's dispatch word (element+0x0c), at
// 0x007f8e35 and 0x007f8ed9.  Both pass the embedded object itself as the first
// stack argument.  The word is data the body loads out of the element, not a
// located vtable, so this stays a port and no callee is named.
void sub_dispatch_slot0(ElementSub* self, float arg2, float arg3, std::uint32_t arg4,
                        std::uint32_t arg5) noexcept;

// Virtual dispatch through a Handle's leading vtable word.
void handle_dispatch_slot0(Handle* self) noexcept;
void handle_dispatch_slot1(Handle* self) noexcept;

// ---------------------------------------------------------------------------
// 0x007f8d10
// ---------------------------------------------------------------------------
// arg1 (entry_ESP+0x4): the source/template object.  It is at least 0x80 bytes —
//                      0x007f6ff0 reads +0x04 and +0x0c and copies 0x70 bytes
//                      from +0x10.  Its word at +0x04 becomes the element's
//                      dispatch word and is called twice, so it is a function
//                      pointer of the SubCallback shape.  Guarded only through
//                      that word (0x007f8d31); arg1 itself is never tested, so a
//                      null arg1 faults at that load.
// arg2 (entry_ESP+0x8): the key handle.  Null is a clean no-op (0x007f8d24).
// arg3 (entry_ESP+0xc): 32-bit selector, matched against element+0x04 and then
//                       stored there.
//
// Returns void.  The x87 stack is balanced on every path — see the trace in the
// .cpp — so nothing is returned in ST0.
void registry_ensure_entry_007f8d10(Registry* self, const void* arg1, void* arg2,
                                    std::uint32_t arg3) noexcept;

}  // namespace openspore::pkg_007f8d10

#endif  // OPENSPORE_PKG_007F8D10_REGISTRY_ENSURE_ENTRY_007F8D10_HPP
