#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "UTFWin perspective wave 12 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_utfwin_perspective_wave12 {

using Opaque = std::uint32_t;

#if defined(_MSC_VER)
#define PKG_PERSPECTIVE_THISCALL __thiscall
#define PKG_PERSPECTIVE_CDECL __cdecl
#else
#define PKG_PERSPECTIVE_THISCALL __attribute__((thiscall))
#define PKG_PERSPECTIVE_CDECL __attribute__((cdecl))
#endif

// Object layout of UTFWin::PerspectiveEffect, transcribed from the
// Spore-ModAPI SDK symbol table (SporeGhidra_march2017.xml, STRUCTURE
// "PerspectiveEffect" in namespace /Spore/UTFWin, SIZE 0x14):
//
//   0x00  PerspectiveEffect__vftable* _vftable0
//   0x04  ILayoutElement__vftable*   _vftable1
//   0x08  int                         mnRefCount
//   0x0c  IPerspectiveEffect__vftable* _vftable2
//   0x10  float                       mfNearPlane
//
// PerspectiveEffect is therefore multiply inherited with two secondary bases,
// the first at +0x04 and the second at +0x0c. The two interface sub-object
// offsets the machine actually produces for this family (0x00980330 returns
// this+0x0c, 0x00950eb0 returns this+0x04) land exactly on those two
// sub-objects, and the sibling thunk at 0x00980470 subtracts 0x0c while the
// thunk reconstructed here subtracts 0x04.
enum : std::uint32_t {
  kPrimaryVtableOffset = 0x00,
  kLayoutElementBaseOffset = 0x04,
  kReferenceCountOffset = 0x08,
  kPerspectiveBaseOffset = 0x0c,
  kNearPlaneOffset = 0x10,
  kObjectSize = 0x14,
};

// Secondary-base adjustment this package's entry point applies: 0x00980480 is
// `SUB ECX, 0x4` followed by an unconditional transfer, so the receiver it is
// entered with is the sub-object at +0x04 and the callee receives the primary.
enum : std::uint32_t { kLayoutElementThisAdjustment = 0x04 };

// The reconstruction is a cross-vtable thunk, so it is reached through a slot,
// never called by name. This is the slot type the receiver was loaded from.
using MessageSlot = Opaque*(PKG_PERSPECTIVE_THISCALL*)(Opaque*, Opaque);

Opaque* PKG_PERSPECTIVE_THISCALL handle_message_00980480(
    Opaque* layout_element_subobject, Opaque message_word);

static_assert(sizeof(Opaque) == 4, "opaque words are 32-bit");
static_assert(sizeof(void*) == 4, "x86-32 pointers are 32-bit");
static_assert(kObjectSize == 0x14, "PerspectiveEffect is 0x14 bytes");
static_assert(kLayoutElementBaseOffset == 0x04,
              "the ILayoutElement sub-object sits at +0x04");
static_assert(kPerspectiveBaseOffset == 0x0c,
              "the IPerspectiveEffect sub-object sits at +0x0c");

}
