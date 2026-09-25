#include "pkg_palette_wave6.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_palette_wave6 {
namespace {

std::uint32_t read_u32(const void* object, std::size_t offset) {
  std::uint32_t value;
  std::memcpy(&value, static_cast<const std::uint8_t*>(object) + offset,
              sizeof(value));
  return value;
}

const void* read_vtable(const void* object) {
  const void* value;
  std::memcpy(&value, object, sizeof(value));
  return value;
}

ViewerItemSlot08 item_slot08(const OpaqueViewerObject* object) {
  const void* const* table =
      reinterpret_cast<const void* const*>(read_vtable(object));
  return reinterpret_cast<ViewerItemSlot08>(table[2]);
}

ViewerObjectSlot04 object_slot04(OpaqueViewerObject* object) {
  const void* const* table =
      reinterpret_cast<const void* const*>(read_vtable(object));
  return reinterpret_cast<ViewerObjectSlot04>(table[1]);
}

ViewerObjectSlot08 object_slot08(OpaqueViewerObject* object) {
  const void* const* table =
      reinterpret_cast<const void* const*>(read_vtable(object));
  return reinterpret_cast<ViewerObjectSlot08>(table[2]);
}

ViewerObjectSlot28 object_slot28(OpaqueViewerObject* object) {
  const void* const* table =
      reinterpret_cast<const void* const*>(read_vtable(object));
  return reinterpret_cast<ViewerObjectSlot28>(table[10]);
}

ViewerSlot34 viewer_slot34(OpaqueAdvancedItemViewer* viewer) {
  const void* const* table =
      reinterpret_cast<const void* const*>(read_vtable(viewer));
  return reinterpret_cast<ViewerSlot34>(table[13]);
}

GraphicsSlot04 graphics_slot04(OpaqueGraphicsRoot* root) {
  const void* const* table =
      reinterpret_cast<const void* const*>(read_vtable(root));
  return reinterpret_cast<GraphicsSlot04>(table[1]);
}

GraphicsSlot34 graphics_slot34(OpaqueGraphicsContext* context) {
  const void* const* table =
      reinterpret_cast<const void* const*>(read_vtable(context));
  return reinterpret_cast<GraphicsSlot34>(table[13]);
}

AppSlot14 app_slot14(OpaqueAppSystem* app) {
  const void* const* table =
      reinterpret_cast<const void* const*>(read_vtable(app));
  return reinterpret_cast<AppSlot14>(table[5]);
}

}

extern "C" OpaquePaletteMain* PKG_PALETTE_THISCALL pkg_palette_005c5ee0(
    OpaquePaletteMain* self, std::uint32_t category_id) {
  unresolved_005c5e90(self);
  if ((category_id & 1U) != 0U) {
    unresolved_00f47380(self);
  }
  return self;
}

extern "C" OpaquePalettePage* PKG_PALETTE_THISCALL pkg_palette_005c8bc0(
    OpaquePalettePage* self, std::uint32_t key) {
  if (key == 0xee3f516eU || key == 0x2f009dd0U ||
      key == 0x72deed2bU) {
    return self;
  }
  return nullptr;
}

extern "C" void PKG_PALETTE_THISCALL pkg_palette_005f4750(
    OpaqueAdvancedItemViewer* self) {
  OpaqueViewerItem* item = self->field17c;
  std::uint8_t available = 1U;
  if (item != nullptr && item->field08 != nullptr) {
    void* argument = item->field31 != 0U
                         ? static_cast<void*>(reinterpret_cast<
                               OpaqueResourceKey*>(reinterpret_cast<
                                   std::uint8_t*>(self) + 0x4cU))
                         : static_cast<void*>(reinterpret_cast<
                               std::uint8_t*>(self) + 0x40U);
    available = item_slot08(item->field08)(item->field08, argument);
  }

  const std::uint8_t item_state =
      available != 0U && self->field198 != 0U &&
              self->field100 == 0x71fa7d3fU
          ? 1U
          : 0U;
  self->field16a = item_state;
  const float scale = available != 0U ? 1.0F : 0.75F;
  self->field94 = self->field188 * scale;
  if (self->field184 == 0U && available != 0U) {
    self->field169 = 1U;
  }

  OpaqueSwatchManager* swatch_manager = unresolved_00401020();
  OpaqueSwatchState* swatch_state =
      unresolved_0113ae10(swatch_manager);
  if (swatch_state != nullptr && self->field16b != 0U) {
    OpaqueViewerObject* constructed = nullptr;
    if (item->field14 != nullptr && item->field31 != 0U) {
      object_slot28(item->field14)(
          item->field14, item,
          reinterpret_cast<OpaqueResourceKey*>(
              reinterpret_cast<std::uint8_t*>(self) + 0x4cU),
          self->field180);
    } else {
      OpaqueViewerObject* allocated = unresolved_00f473a0(
          100U, 0x13eb430U, 0U, 0U, 0U, 0U);
      if (allocated != nullptr) {
        constructed = unresolved_0059f030(
            allocated, item->field2c, read_u32(self->field180, 0x10U),
            read_u32(self->field180, 0x14U), item->field2c, 0x14880158U,
            0U, 1U);
        if (constructed != nullptr) {
          object_slot04(constructed)(constructed);
        }
      }
      unresolved_005ee480(swatch_manager, self->field180, item, constructed,
                          1U);
      if (constructed != nullptr) {
        object_slot08(constructed)(constructed);
      }
    }

    unresolved_005ed320(swatch_manager, 2U);
    OpaqueGraphicsRoot* graphics_root = unresolved_0067caa0();
    OpaqueGraphicsContext* graphics_context =
        graphics_slot04(graphics_root)(graphics_root);
    OpaqueRect* rect = graphics_slot34(graphics_context)(graphics_context);
    unresolved_008283a0(
        swatch_manager, self->field84, self->field88,
        (rect->field08 - rect->field00) * 0.2F,
        (rect->field0c - rect->field04) * 0.0F);
  }

  OpaqueRenderTarget* render_target = viewer_slot34(self)(self, 1U, 1U);
  unresolved_0067cad0();
  unresolved_0080d710(render_target, 1U, 1U);
  if (self->field194 != nullptr) {
    unresolved_0067cad0();
    unresolved_0080d710(static_cast<OpaqueRenderTarget*>(self->field194),
                        1U, 1U);
  }

  OpaqueCommandLine command_line;
  command_line.field08 = 0x0522f9cdU;
  OpaqueAppSystem* app = unresolved_0067dcc0();
  app_slot14(app)(app, 0U, &command_line, 0x0522f9cdU);
}

}
