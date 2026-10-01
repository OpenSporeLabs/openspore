#pragma once

// Reconstruction of UTFWin::Window::func35 @ 0x0095fd60 (SporeApp.exe 3.1.0.22,
// binary sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// Evidence basis (all from the live Ghidra bridge on SporeApp.exe):
//   * disassembly 0x0095fd60..0x0095fdb4 (26 instructions, RET 0x4)
//   * decompilation UTFWin__Window__func35.c (SDK label UTFWin::Window::func35)
//   * 32 references to 0x0095fd60, every one a DATA pointer into a vtable image
//     at vtable_base + 0x04; vtable_base + 0x00 holds 0x0095fa30, which the SDK
//     symbol table labels UTFWin::Window::IsAncestorOf.
//   * slot targets read from the UTFWin vtable images (0x013fdb6c, 0x01414c14):
//     +0x90 -> 0x00960280, +0x114 -> 0x00993200 / 0x006f2f20.
//
// WHAT THE RECEIVER EVIDENCE CARRIES FOR THIS BODY, AND WHAT IT DOES NOT. The
// machine-derived receiver record enumerates offsets=[0x0, 0xa8, 0x1dc] for
// register ECX and is bounds_only: it saw the body reach three words of the
// receiver and could say no more. The complete 26-instruction listing agrees -
//
//   0095fd64  MOV ESI,ECX                      the receiver, aliased into ESI
//   0095fd66  MOV EAX,dword ptr [ESI + 0xa8]    read
//   0095fd74  MOV dword ptr [ESI + 0xa8],ECX    write
//   0095fd82  MOV EAX,dword ptr [ESI]           read, the dispatch word
//   0095fda4  MOV EAX,dword ptr [ESI]           read again, after the first call
//   0095fd9b  CMP dword ptr [ESI + 0x1dc],0x0  read
//
// - and it establishes a width, a displacement and a direction for each of
// them. It establishes nothing about WHICH member of what type occupies any of
// them. `field_a8` ("the last value passed to func35") and `field_1dc` ("the
// gate for the slot 0x90 call") were readings of the instructions, not facts
// about the object, and the record cannot confirm either. So the window type
// below declares no member at all: it is an opaque 0x1e0-byte run reached by
// displacement, and the body never claims to know what the words mean.
//
// The two dispatches are the same story about a different object. The word at
// receiver+0x0 is an ADDRESS: 0x0095fd82 loads it into EAX and 0x0095fd84 /
// 0x0095fda6 index it, one level, at displacements 0x114 and 0x90. Those are
// displacements into a table image, not members of a struct, so the table is an
// opaque run too.
//
// The record handed to slot 0x114 is a third object, and it is the one place
// where a sub-layout IS pinned: the body itself writes three of its words, at
// its own +0x08 (the immediate 0x13), +0x0c (the new value) and +0x10 (the
// previous value), and reads none. +0x00 and +0x04 are never stored by this
// function, so they stay indeterminate and are NOT modelled as zeroed fields -
// they are part of an opaque run the body only writes three words into.

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "UTFWin func35 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_UTFWIN_FUNC35_THISCALL __thiscall
#else
#define PKG_UTFWIN_FUNC35_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_utfwin_func35_wave12 {

using Opaque = std::uint32_t;

struct OpaqueWindow;

// The vtable image the receiver's word 0 points at. The two slots this body
// dispatches through are at displacements 0x90 and 0x114; the extent runs to
// 0x118 because 0x114 + 4 is the last word it reads. The words before 0x90 are
// not enumerated here: the image is a set of addresses, and this body uses two
// of them. Slots 0x00 and 0x04 of the same image hold 0x0095fa30 (SDK label
// UTFWin::Window::IsAncestorOf) and 0x0095fd60 (this body) respectively, read
// out of the image at 0x013fdb6c and 0x01414c14.
struct alignas(4) OpaqueWindowVTable {
  std::array<std::uint8_t, 0x118> opaque_00{};
};

// The receiver, modelled as far as the machine reached and no further: 0x1e0
// bytes, 4-byte aligned, the prefix through the last word it reads. No member
// is declared. The extent is a modelling bound, not a recovered allocation
// size.
struct alignas(4) OpaqueWindow {
  std::array<std::uint8_t, 0x1e0> opaque_00{};
};

// The record handed to vtable slot 0x114, as a 0x14-byte run. func35 writes
// +0x08, +0x0c and +0x10 and reads none of it; +0x00 and +0x04 stay
// indeterminate, which an opaque run says and a zero-initialised struct would
// not.
struct alignas(4) OpaqueStateMessage {
  std::array<std::uint8_t, 0x14> opaque_00{};
};

// Every displacement this body is seen reaching, as values. The three receiver
// ones are the record's own enumeration; the two table ones come from
// `MOV EDX,[EAX + 0x114]` and `MOV EDX,[EAX + 0x90]`; the three record ones
// from the three `MOV [ESP + ...]` stores and the frame arithmetic that fixes
// &record at ESP+4.
constexpr std::size_t kReceiverDispatchWordDisplacement = 0x0;
constexpr std::size_t kReceiverPreviousDisplacement = 0xa8;
constexpr std::size_t kReceiverGateDisplacement = 0x1dc;
constexpr std::size_t kTablePendingSlotDisplacement = 0x90;
constexpr std::size_t kTableMessageSlotDisplacement = 0x114;
constexpr std::size_t kMessageCodeDisplacement = 0x8;
constexpr std::size_t kMessageNewValueDisplacement = 0xc;
constexpr std::size_t kMessagePreviousValueDisplacement = 0x10;
constexpr Opaque kMessageCode = 0x13u;

// The only way this package touches the window, the table or the record: a
// 4-byte word at a stated displacement. A member access would assert an
// identity the receiver record (offsets=[0x0, 0xa8, 0x1dc], bounds_only)
// cannot confirm.
inline Opaque* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Opaque*>(reinterpret_cast<std::uintptr_t>(base) +
                                   displacement);
}

inline const Opaque* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Opaque*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// 0x00960280 walks this->0x3c as a cursor and stops at this->0x38, dispatching
// through vtable slot 0xe0. Observed, not asserted by func35 itself; modelled so
// the slot 0x90 contract can be described in the sidecar.
struct alignas(4) OpaquePendingQueue {
  std::array<std::uint8_t, 0x40> opaque_00{};
};

constexpr std::size_t kPendingQueueStopDisplacement = 0x38;
constexpr std::size_t kPendingQueueCursorDisplacement = 0x3c;

using WindowSlot90 = Opaque(PKG_UTFWIN_FUNC35_THISCALL*)(OpaqueWindow*);
using WindowSlot114 = void(PKG_UTFWIN_FUNC35_THISCALL*)(OpaqueWindow*,
                                                         OpaqueStateMessage*);

static_assert(sizeof(void*) == 4, "UTFWin pointers are 32-bit");
static_assert(sizeof(Opaque) == 4, "UTFWin opaque words are 32-bit");
static_assert(kTableMessageSlotDisplacement + sizeof(Opaque) ==
                  sizeof(OpaqueWindowVTable),
              "0x114 + 4 is the last word the body reads off the table");
static_assert(kTablePendingSlotDisplacement < kTableMessageSlotDisplacement,
              "the two dispatched slots are distinct");
static_assert(kReceiverGateDisplacement + sizeof(Opaque) ==
                  sizeof(OpaqueWindow),
              "0x1dc + 4 is the last word the body reads on the window");
static_assert(kReceiverDispatchWordDisplacement + sizeof(Opaque) <
                  kReceiverPreviousDisplacement,
              "the dispatch word and the previous-value word do not overlap");
static_assert(kReceiverPreviousDisplacement + sizeof(Opaque) <
                  kReceiverGateDisplacement,
              "the previous-value word and the gate word do not overlap");
static_assert(kMessagePreviousValueDisplacement + sizeof(Opaque) ==
                  sizeof(OpaqueStateMessage),
              "0x10 + 4 is the last word the body writes into the record");
static_assert(kMessageCodeDisplacement < kMessageNewValueDisplacement &&
                  kMessageNewValueDisplacement <
                      kMessagePreviousValueDisplacement,
              "the three record words are distinct and ascending");
static_assert(kPendingQueueCursorDisplacement + sizeof(Opaque) ==
                  sizeof(OpaquePendingQueue),
              "0x3c + 4 is the last word 0x00960280 walks");

// Entry point under reconstruction. Name carries the SDK method token (func35)
// and the 8-hex target VA so the validator can bind this span.
void PKG_UTFWIN_FUNC35_THISCALL func35_0095fd60(OpaqueWindow* object,
                                                Opaque value);

}
