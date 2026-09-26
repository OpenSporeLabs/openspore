#include <cstdlib>
#include <cstring>

#include "utfwin_drawable_wave9.hpp"

namespace openspore::reconstruction::pkg_utfwin_drawable_wave9 {
namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

int dispatch_calls = 0;
OpaqueObject* dispatched_self = nullptr;
OpaqueWord dispatch_result = 0;

OpaqueWord PKG_UTFWIN_DRAWABLE_THISCALL dispatch_slot_14(OpaqueObject* self) {
  ++dispatch_calls;
  dispatched_self = self;
  return dispatch_result;
}

OpaqueWord pointer_value(const void* pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

void reset_dispatch(OpaqueObjectVTable* vtable, OpaqueWord result) {
  vtable->slot_14 = dispatch_slot_14;
  dispatch_calls = 0;
  dispatched_self = nullptr;
  dispatch_result = result;
}

void test_re_009849a0() {
  OpaqueObjectVTable self_vtable{};
  reset_dispatch(&self_vtable, 0x12345678u);
  OpaqueObject self{&self_vtable};
  OpaqueSpinnerDrawableWire target{};
  target.base.field_00 = 0xaaaaaaaau;
  target.base.field_04 = 0xbbbbbbbbu;
  target.base.field_08 = 0xccccccccu;
  target.base.field_0c = 0xddddddddu;
  target.images_10[0] = 0x01020304u;
  target.images_10[1] = 0x11121314u;
  target.images_10[2] = 0x21222324u;

  re_009849a0(&self, &target.base);

  check(target.base.field_00 == 0x1444c24u);
  check(target.base.field_04 == pointer_value(&self) - 4u);
  check(target.base.field_08 == 1u);
  check(target.base.field_0c == 0x12345678u);
  check(dispatch_calls == 1);
  check(dispatched_self == &self);
  check(target.images_10[0] == 0x01020304u);
  check(target.images_10[1] == 0x11121314u);
  check(target.images_10[2] == 0x21222324u);
}

void test_re_00987ae0() {
  OpaqueObjectVTable self_vtable{};
  reset_dispatch(&self_vtable, 0x87654321u);
  OpaqueObject self{&self_vtable};
  OpaqueStdDrawableWire target{};
  target.base.field_00 = 0xaaaaaaaau;
  target.base.field_04 = 0xbbbbbbbbu;
  target.base.field_08 = 0xccccccccu;
  target.base.field_0c = 0xddddddddu;
  target.images_10[7] = 0x71727374u;
  target.scale_type_30 = 0x31323334u;
  target.scale_area_34[0] = 0x41424344u;
  target.scale_factor_44[1] = 0x51525354u;
  target.hit_mask_4c = 0x61626364u;
  target.property_50 = 0x71727374u;
  target.outline_54[9] = 0x81828384u;

  re_00987ae0(&self, &target.base);

  check(target.base.field_00 == 0x14451c4u);
  check(target.base.field_04 == pointer_value(&self) - 4u);
  check(target.base.field_08 == 1u);
  check(target.base.field_0c == 0x87654321u);
  check(dispatch_calls == 1);
  check(dispatched_self == &self);
  check(target.images_10[7] == 0x71727374u);
  check(target.scale_type_30 == 0x31323334u);
  check(target.scale_area_34[0] == 0x41424344u);
  check(target.scale_factor_44[1] == 0x51525354u);
  check(target.hit_mask_4c == 0x61626364u);
  check(target.property_50 == 0x71727374u);
  check(target.outline_54[9] == 0x81828384u);
}

void test_re_00985ce0() {
  OpaqueImageDrawableWire image{};
  image.base.field_00 = 0xaaaaaaaau;
  image.base.field_04 = 0xbbbbbbbbu;
  image.base.field_08 = 0xccccccccu;
  image.base.field_0c = 0xddddddddu;
  image.scale_10 = 0x01020304u;
  image.flags_14 = 0x11121314u;
  image.tiling_18 = 0x21222324u;
  image.alignment_h_1c = 0x31323334u;
  image.alignment_v_20 = 0x41424344u;
  image.image_24 = 0x51525354u;
  image.outline_28[9] = 0x61626364u;
  const OpaqueImageDrawableWire before = image;

  const OpaqueWord result =
      re_00985ce0(reinterpret_cast<OpaqueObject*>(&image));

  check(result == 0x4f063bb3u);
  check(std::memcmp(&image, &before, sizeof(image)) == 0);
}

void test_re_00b267d0() {
  OpaqueTreeNodeWire node{};
  OpaqueListNode sibling{};
  node.vtable_00 = reinterpret_cast<OpaqueObjectVTable*>(0x12345678u);
  node.ref_count_08 = 0x01020304u;
  node.next_0c = &sibling;
  node.previous_10 = &sibling;
  node.parent_18 = reinterpret_cast<OpaqueTreeNodeWire*>(0x5678u);
  node.children_1c.anchor.next = &node.children_1c.anchor;
  node.children_1c.anchor.previous = &node.children_1c.anchor;
  node.node_flags_28 = 0x090a0b0cu;
  node.node_id_44 = 0x0d0e0f10u;
  const OpaqueTreeNodeWire before = node;

  check(re_00b267d0(reinterpret_cast<OpaqueObject*>(&node), 0x037e958bu) ==
        pointer_value(&node));
  check(re_00b267d0(reinterpret_cast<OpaqueObject*>(&node), 0x037e958cu) == 0u);
  check(std::memcmp(&node, &before, sizeof(node)) == 0);
  check(re_00b267d0(nullptr, 0x037e958bu) == 0u);
  check(re_00b267d0(
            reinterpret_cast<OpaqueObject*>(static_cast<std::uintptr_t>(0x1u)),
            0x037e958bu) == 1u);
}

}

int run_tests() {
  test_re_009849a0();
  test_re_00987ae0();
  test_re_00985ce0();
  test_re_00b267d0();
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_utfwin_drawable_wave9::run_tests();
}
