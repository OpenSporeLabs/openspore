#include "utfwin_perspective_009804e0.hpp"

namespace openspore::reconstruction::pkg_utfwin_perspective_009804e0 {

namespace {

// 0x009804e4 CMP EAX,0xef2b293b: the ObjectTYPE word the target recognises.
constexpr ObjectTypeId kPerspectiveEffectType = object_type_id::kIPerspectiveEffect;

}

extern "C" void* PKG_UTFWIN_PERSPECTIVE_THISCALL object_cast_00950eb0(
    const void* self, ObjectTypeId type_id) {
  // 0x00950eb6 CMP ECX,0x2f009dd0 -> UTFWin::IWinProc -> the object itself.
  if (type_id == object_type_id::kIWinProc) {
    return const_cast<void*>(self);
  }
  // 0x00950ebe CMP ECX,0xee3f516e / 0x00950ec6 CMP ECX,0xeec58382
  // ("Object" and "UTFWin::ILayoutElement") -> the +0x04 sub-object.
  if (type_id == object_type_id::kObject ||
      type_id == object_type_id::kILayoutElement) {
    if (self == nullptr) {
      return nullptr;
    }
    return static_cast<std::uint8_t*>(const_cast<void*>(self)) + 4;
  }
  // 0x00950ec0 XOR EAX,EAX: unknown type word.
  return nullptr;
}

extern "C" void* PKG_UTFWIN_PERSPECTIVE_THISCALL func80h_009804e0(
    PerspectiveEffect* self, ObjectTypeId type_id) {
  // 0x009804e0 MOV EAX,[ESP+0x4] / CMP EAX,0xef2b293b / JZ 0x009804f4
  if (type_id == kPerspectiveEffectType) {
    // 0x009804f4 TEST ECX,ECX / JZ 0x009804fe / 0x009804f8 LEA EAX,[ECX+0xc].
    // The receiver is handled as opaque bytes: the body only forms the address
    // self+0xc, it never loads a field out of the receiver and never calls
    // through one. What lives at 0x014440d0 offset 0x0c is documented in the
    // header and in the metadata sidecar, not here.
    if (self == nullptr) {
      return nullptr;  // 0x009804fe XOR EAX,EAX
    }
    return reinterpret_cast<std::uint8_t*>(self) + 0xc;
  }
  // 0x009804eb MOV [ESP+0x4],EAX / 0x009804ef JMP 0x00950eb0: the receiver in
  // ECX and the type word are forwarded unchanged; the store is the redundant
  // argument spill the compiler emitted for the tail call.
  return object_cast_00950eb0(self, type_id);
}

extern "C" void* PKG_UTFWIN_PERSPECTIVE_THISCALL cast_thunk_sub_04_00980660(
    SubObjectVTable* self, ObjectTypeId type_id) {
  // 0x00980660 SUB ECX,0x4 / 0x00980663 JMP 0x009804e0
  return func80h_009804e0(reinterpret_cast<PerspectiveEffect*>(
                              reinterpret_cast<std::uint8_t*>(self) - 4),
                          type_id);
}

extern "C" void* PKG_UTFWIN_PERSPECTIVE_THISCALL cast_thunk_sub_0c_00980670(
    SubObjectVTable* self, ObjectTypeId type_id) {
  // 0x00980670 SUB ECX,0xc / 0x00980673 JMP 0x009804e0
  return func80h_009804e0(reinterpret_cast<PerspectiveEffect*>(
                              reinterpret_cast<std::uint8_t*>(self) - 0x0c),
                          type_id);
}

}
