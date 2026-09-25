#include "editor_query_helpers.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg10_editor_dispatch {

namespace {

using OpaqueServiceSlot0C = OpaqueService*(__thiscall*)(OpaqueService*,
                                                        std::uint32_t);

template <typename Function>
Function load_slot(void* object, std::size_t offset) {
  Function function;
  void* table;
  std::memcpy(&table, object, sizeof(table));
  std::memcpy(&function, static_cast<const std::uint8_t*>(table) + offset,
              sizeof(function));
  return function;
}

std::uint8_t material_path(OpaqueEditorQueryContext* context,
                           std::uint32_t command, std::uint32_t material_mode,
                           bool common_path) {
  if (pkg10_g_app_properties_015fd918->runtime->prefix[0x118] != 0) {
    auto* material_manager = pkg10_g_material_manager_get_0067dd30();
    auto* material = load_slot<OpaqueMaterialSlot30>(material_manager, 0x30)(
        material_manager, 0x604a51au);
    if (material != nullptr) {
      context->material_mode = material_mode;
      pkg10_g_register_material_00809db0(
          context->material_registration,
          reinterpret_cast<const void*>(&pkg10_g_dat_01519a48));
      return 1;
    }
  }

  context->state = command;
  pkg10_g_debug_004a88d0(0xa03e74b2u);
  if (common_path) {
    pkg10_g_transition_one_005dc4d0(context, 0);
  } else {
    pkg10_g_raw_call_0064bc50(0xdb184acbu, context, 0x54acb9f1u);
  }
  return 1;
}

}

std::uint8_t __thiscall editor_query_dispatch_005dfd00(
    OpaqueEditorQueryContext* context, std::uint32_t command) {
  context->active = 1;
  switch (command) {
    case 0x100:
      return material_path(context, command, 0x604fa6bu, true);
    case 0x101:
    case 0x107:
      context->state = command;
      pkg10_g_transition_args_005df470(context, command, 1);
      return 1;
    case 0x102:
      context->state = command;
      pkg10_g_transition_noargs_005dfb40(context);
      return 1;
    case 0x103:
      context->state = command;
      pkg10_g_transition_noargs_005df8d0(context);
      return 1;
    case 0x104:
      context->state = command;
      pkg10_g_debug_004a88d0(0xa03e74b2u);
      pkg10_g_transition_args_005df470(context, command, 1);
      return 1;
    case 0x105:
      return material_path(context, command, 0x604fab1u, false);
    case 0x106:
      context->state = command;
      pkg10_g_debug_004a88d0(0xa03e74b2u);
      pkg10_g_port_call_006035d0(0x00dbdba1u);
      if (pkg10_g_app_properties_015fd918->runtime->prefix[0x118] != 0) {
        pkg10_g_mode_flag_008098f0(1);
      }
      return 1;
    case 0x108:
      context->state = command;
      pkg10_g_debug_004a88d0(0xa03e74b2u);
      pkg10_g_transition_noargs_00572260(context);
      return 1;
    case 0x109: {
      context->state = 0;
      std::uint32_t local[4]{};
      const auto* words = pkg10_g_editor_output_00572190(context->owner, local);
      for (std::size_t index = 0; index < 4; ++index) {
        local[index] = words[index];
      }
      pkg10_g_editor_apply_005dca00(context, local[0], local[1], local[2],
                                    local[3]);
      return 1;
    }
    case 0x10a:
      pkg10_g_debug_004a88d0(0xa03e74b2u);
      pkg10_g_transition_noargs_005dd300(context);
      return 1;
    case 0x10c: {
      auto* app_system = pkg10_g_app_system_get_0067dcc0();
      load_slot<OpaqueAppSystemInit>(app_system, 0x14)(app_system, 0xf40f8fe4u,
                                                       nullptr, nullptr);
      return 1;
    }
    case 0x10d: {
      pkg10_g_debug_004a88d0(0xa03e74b2u);
      auto* service = pkg10_g_service_lookup_005dc310(context, 0x47bc920u);
      if (service != nullptr) {
        const auto result =
            load_slot<OpaqueServiceSlot28>(service, 0x28)(service);
        pkg10_g_state_decision_005dd610(context, (result & 1u) == 0u ? 1u : 0u);
      }
      return 1;
    }
    default:
      return 0;
  }
}

OpaquePreferenceQuery* __thiscall editor_query_reset_005dd750(
    OpaquePreferenceQuery* query, OpaquePropertyValue* value) {
  query->trailing_flags = 0;
  query->flags = 0;
  static_cast<void>(pkg10_g_property_set_value_bool_00422e20(query, value));
  return query;
}

void __thiscall editor_query_clear_flags_0093db80(OpaquePreferenceQuery* query,
                                                  std::uint8_t clear_value) {
  if ((query->flags & 4u) != 0) {
    pkg10_g_query_callback_0154eb48(1, query, 0, 0, 0, 0);
  }
  if (clear_value != 0 && (query->flags & 2u) == 0) {
    query->trailing_flags = 0;
    query->flags = 0;
  }
}

OpaqueService* __cdecl editor_query_service_005ca960(OpaqueService* service) {
  if (service == nullptr) {
    return nullptr;
  }
  return load_slot<OpaqueServiceSlot0C>(service, 0x0c)(service, 0x8ed27e7au);
}

}
