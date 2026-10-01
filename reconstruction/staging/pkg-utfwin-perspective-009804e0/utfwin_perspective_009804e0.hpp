#pragma once

#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_UTFWIN_PERSPECTIVE_THISCALL __thiscall
#define PKG_UTFWIN_PERSPECTIVE_CDECL __cdecl
#else
#define PKG_UTFWIN_PERSPECTIVE_THISCALL __attribute__((thiscall))
#define PKG_UTFWIN_PERSPECTIVE_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_utfwin_perspective_009804e0 {

// /Spore/ObjectTYPE: 32-bit class/interface identifier, passed to Object::Cast.
using ObjectTypeId = std::uint32_t;

struct PerspectiveEffect;
struct PerspectiveEffectVTable;
struct SubObjectVTable;

namespace object_type_id {

// Values taken verbatim from the Spore SDK ObjectTYPE enum
// (.spore-analysis/ghidra-exports/spore_sdk.xml, ENUM "ObjectTYPE" /Spore).
inline constexpr ObjectTypeId kObject = 0xee3f516eu;            // "Object"
inline constexpr ObjectTypeId kILayoutElement = 0xeec58382u;     // "UTFWin::ILayoutElement" (also "UTFWin::Window")
inline constexpr ObjectTypeId kIWindow = 0xeeee8218u;            // "UTFWin::IWindow"
inline constexpr ObjectTypeId kIWinProc = 0x2f009dd0u;           // "UTFWin::IWinProc"
inline constexpr ObjectTypeId kIPerspectiveEffect = 0xef2b293bu; // "UTFWin::IPerspectiveEffect" (also "IGlideEffect"/"IRotateEffect")

}

// Every Spore::Object vftable starts with the same four slots -
// Object__vftable: AddRef@0x00, Release@0x04, _virtual_dtor@0x08, Cast@0x0c -
// so the two vftable shapes below repeat that prefix verbatim.
//
// IPerspectiveEffect__vftable is 0x1c bytes: the four Object slots followed by
// ToWinProc@0x10, GetNearPlane@0x14, SetNearPlane@0x18.
struct PerspectiveEffectVTable {
  void* add_ref_00 = nullptr;
  void* release_04 = nullptr;
  void* virtual_dtor_08 = nullptr;
  void* cast_0c = nullptr;
  void* to_win_proc_10 = nullptr;
  void* get_near_plane_14 = nullptr;
  void* set_near_plane_18 = nullptr;
};

// Vftable of the base sub-object living at object+0x04 (constructor stores
// 0x014440b4 there); its Cast slot holds the this-adjusting thunk 0x00980660.
struct SubObjectVTable {
  void* add_ref_00 = nullptr;
  void* release_04 = nullptr;
  void* virtual_dtor_08 = nullptr;
  void* cast_0c = nullptr;
  void* slots_10[3]{};
};

// The complete UTFWin::PerspectiveEffect object. The constructor at 0x00980680
// requests 0x14 bytes and writes:
//   [+0x00] = 0x014440d0  complete-object vftable (holds 0x009804e0 at +0x0c)
//   [+0x04] = 0x014440b4  sub-object vftable
//   [+0x08] = 0
//   [+0x0c] = 0x01444098  sub-object vftable (holds thunk 0x00980670 at +0x0c)
struct PerspectiveEffect {
  PerspectiveEffectVTable* vtable_00 = nullptr;
  SubObjectVTable* vtable_04 = nullptr;
  ObjectTypeId field_08 = 0;
  SubObjectVTable* vtable_0c = nullptr;
};

// 0x00950eb0 - Object::Cast base implementation reached by tail jump from
// 0x009804e0. Present in ~20 vftables in SporeApp.exe and called directly from
// nine sites, including 0x009804ef (this function) and 0x0097e7ff.
extern "C" void* PKG_UTFWIN_PERSPECTIVE_THISCALL object_cast_00950eb0(
    const void* self, ObjectTypeId type_id);

// 0x009804e0 - UTFWin::PerspectiveEffect::func80h.
//
// SLOT OCCUPANCY, NOT DISPATCH. This function IS the occupant of the
// UTFWin::IPerspectiveEffect__vftable Cast slot: the 0x0c word of the vftable
// 0x014440d0 holds 0x009804e0 (written by the constructor at 0x009806c0), and the
// two this-adjusting thunks 0x00980660 / 0x00980670 jump straight to it. That is
// a fact about who REACHES this function, not about what the function does. The
// 11-instruction body performs no virtual dispatch of its own: it contains no
// indirect transfer through a register or through a memory operand, it never
// loads a vftable word out of the receiver, and its only outgoing transfer is
// the direct tail jump to the base implementation 0x00950eb0. The machine
// dispatch record agrees (indirect_calls = 0).
//
// The struct shapes below are therefore documentation of the object's layout,
// not a dispatch site of this function; the .cpp span for 0x009804e0 treats the
// receiver as opaque bytes and only forms the address self+0x0c.
extern "C" void* PKG_UTFWIN_PERSPECTIVE_THISCALL func80h_009804e0(
    PerspectiveEffect* self, ObjectTypeId type_id);

// 0x00980660 - "SUB ECX,4 / JMP 0x009804e0": Cast thunk for the +0x04
// sub-object. Recovered as a direct-call xref to the target.
extern "C" void* PKG_UTFWIN_PERSPECTIVE_THISCALL cast_thunk_sub_04_00980660(
    SubObjectVTable* self, ObjectTypeId type_id);

// 0x00980670 - "SUB ECX,0x0c / JMP 0x009804e0": Cast thunk for the +0x0c
// sub-object. Recovered as a direct-call xref to the target.
extern "C" void* PKG_UTFWIN_PERSPECTIVE_THISCALL cast_thunk_sub_0c_00980670(
    SubObjectVTable* self, ObjectTypeId type_id);

static_assert(sizeof(void*) == 4, "UTFWin pointers are 32-bit");
static_assert(offsetof(PerspectiveEffect, vtable_04) == 0x04,
              "PerspectiveEffect sub-object vftable offset");
static_assert(offsetof(PerspectiveEffect, field_08) == 0x08,
              "PerspectiveEffect field_08 offset");
static_assert(offsetof(PerspectiveEffect, vtable_0c) == 0x0c,
              "PerspectiveEffect IPerspectiveEffect sub-object offset");
static_assert(sizeof(PerspectiveEffect) == 0x10,
              "observed initialised prefix of the 0x14-byte allocation");
static_assert(offsetof(PerspectiveEffectVTable, cast_0c) == 0x0c,
              "Object::Cast vftable slot");
static_assert(sizeof(PerspectiveEffectVTable) == 0x1c,
              "IPerspectiveEffect__vftable size");
static_assert(offsetof(SubObjectVTable, cast_0c) == 0x0c,
              "sub-object Cast vftable slot");

}
