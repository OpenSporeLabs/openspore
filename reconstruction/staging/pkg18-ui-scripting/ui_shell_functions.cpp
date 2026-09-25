#include "ui_shell_functions.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg18_ui_scripting {
namespace {

using namespace openspore::reconstruction::pkg18_ui_scripting;

namespace unresolved_contracts {

extern "C" OpaqueUiObject* PKG18_THISCALL
pkg18_re_008105b0(OpaqueUiObject* owner, Opaque id, Opaque flag);
extern "C" std::uint8_t pkg18_re_008053b0();
extern "C" void pkg18_re_00804f80(float x, float y, Opaque* message,
                                  Opaque* message_id);
extern "C" OpaqueUiObject* pkg18_re_0067caa0();
extern "C" void PKG18_THISCALL pkg18_re_005bf950(OpaqueUiShell* shell,
                                                 const std::uint16_t* text);
extern "C" void pkg18_re_00435ed0(Opaque id, Opaque value);
extern "C" OpaqueUiObject* pkg18_re_0067dcc0();
extern "C" void PKG18_THISCALL pkg18_re_00579a90(Opaque* range,
                                                 const std::uint16_t* text);
extern "C" void PKG18_THISCALL pkg18_re_0057eda0(Opaque* range);
extern "C" void pkg18_re_00f47380(Opaque pointer);
extern "C" OpaqueUiObject* pkg18_re_00a206f0();
extern "C" OpaqueUiObject* pkg18_re_004010a0(Opaque value, Opaque* output);
extern "C" Opaque* PKG18_THISCALL pkg18_re_005ecf80(OpaqueUiObject* names,
                                                    Opaque* output,
                                                    Opaque value);

}

using ObjectSlot04 = Opaque(PKG18_THISCALL*)(OpaqueUiObject*);
using ObjectSlot0C = OpaqueUiObject*(PKG18_THISCALL*)(OpaqueUiObject*, Opaque);
using ObjectSlot10 = OpaqueUiObject*(PKG18_THISCALL*)(OpaqueUiObject*);
using ObjectSlot1C = Opaque(PKG18_THISCALL*)(OpaqueUiObject*);
using ObjectSlot1CArg = void(PKG18_THISCALL*)(OpaqueUiObject*, Opaque);
using ObjectSlot20 = Opaque(PKG18_THISCALL*)(OpaqueUiObject*);
using ObjectSlot28 = void(PKG18_THISCALL*)(OpaqueUiObject*, Opaque, Opaque);
using ObjectSlot3C = const std::uint16_t*(PKG18_THISCALL*)(OpaqueUiObject*);
using ObjectSlot44 = OpaqueUiObject*(PKG18_THISCALL*)(OpaqueUiObject*, Opaque*);
using ObjectSlot4C = void(PKG18_THISCALL*)(OpaqueUiObject*, Opaque, Opaque);
using ObjectSlot7C = void(PKG18_THISCALL*)(OpaqueUiObject*, Opaque, Opaque);
using ObjectSlot80 = void(PKG18_THISCALL*)(OpaqueUiObject*, Opaque);
using ObjectSlot94 = void(PKG18_THISCALL*)(OpaqueUiObject*, Opaque, Opaque);
using ObjectSlotDC = void(PKG18_THISCALL*)(OpaqueUiObject*);
using ProviderSlot00 = void(PKG18_THISCALL*)(OpaqueUiObject*,
                                             const std::uint16_t*);
using ProviderSlot04 = Opaque(PKG18_THISCALL*)(OpaqueUiObject*);
using ProviderSlot08 = void(PKG18_THISCALL*)(OpaqueUiObject*,
                                             const std::uint16_t*);
using ProviderSlot10 = void(PKG18_THISCALL*)(OpaqueUiObject*,
                                             const std::uint16_t*);
using ShellSlot1C = void(PKG18_THISCALL*)(OpaqueUiShell*, Opaque);
using AppSlot14 = void(PKG18_THISCALL*)(OpaqueUiObject*, Opaque, Opaque,
                                        Opaque);

template <typename Value>
Value load(const void* object, std::size_t offset) {
  Value value{};
  std::memcpy(&value, static_cast<const unsigned char*>(object) + offset,
              sizeof(value));
  return value;
}

template <typename Value>
void store(void* object, std::size_t offset, Value value) {
  std::memcpy(static_cast<unsigned char*>(object) + offset, &value,
              sizeof(value));
}

template <typename Value>
Value load_shell(const OpaqueUiShell* shell, std::size_t offset) {
  return load<Value>(shell->opaque.data(), offset - sizeof(Opaque));
}

template <typename Value>
void store_shell(OpaqueUiShell* shell, std::size_t offset, Value value) {
  store(shell->opaque.data(), offset - sizeof(Opaque), value);
}

template <typename Value>
Value load_message(const OpaqueUiMessage* message, std::size_t offset) {
  return load<Value>(message->opaque.data(), offset);
}

template <typename To, typename From>
To copy_function(From function) {
  static_assert(sizeof(To) == sizeof(From), "function pointer width mismatch");
  To result{};
  std::memcpy(&result, &function, sizeof(result));
  return result;
}

template <typename Function>
Function object_slot(OpaqueUiObject* object, std::size_t offset) {
  return copy_function<Function>(
      object->vtable->slots[offset / sizeof(Opaque)]);
}

template <typename Function>
Function shell_slot(OpaqueUiShell* shell, std::size_t offset) {
  return copy_function<Function>(shell->vtable->slots[offset / sizeof(Opaque)]);
}

Opaque object_word(OpaqueUiObject* object) {
  return reinterpret_cast<Opaque>(object);
}

OpaqueUiObject* load_service(const OpaqueUiShell* shell, std::size_t offset) {
  return load_shell<OpaqueUiObject*>(shell, offset);
}

OpaqueUiObject* lookup(OpaqueUiObject* owner, Opaque id, Opaque flag) {
  return unresolved_contracts::pkg18_re_008105b0(owner, id, flag);
}

void call_shell_parent(OpaqueUiShell* shell, Opaque value) {
  auto* parent = reinterpret_cast<OpaqueUiObject*>(
      reinterpret_cast<unsigned char*>(shell) - sizeof(Opaque));
  object_slot<ObjectSlot1CArg>(parent, 0x1c)(parent, value);
}

bool submit_to_presentation(OpaqueUiObject* service) {
  if (service == nullptr) {
    return false;
  }
  auto* presentation = unresolved_contracts::pkg18_re_0067caa0();
  object_slot<ObjectSlot4C>(presentation, 0x4c)(presentation, 0,
                                                object_word(service));
  return true;
}

void configure_registry(OpaqueUiObject* manager, Opaque id, Opaque enabled) {
  auto* service = lookup(manager, id, 1);
  if (service == nullptr) {
    return;
  }
  auto* configuration =
      object_slot<ObjectSlot0C>(service, 0x0c)(service, 0x8ed27e7au);
  object_slot<ObjectSlot28>(configuration, 0x28)(configuration, 4, enabled);
}

void call_service_7c(OpaqueUiObject* service, Opaque first, Opaque second) {
  object_slot<ObjectSlot7C>(service, 0x7c)(service, first, second);
}

std::uint32_t wide_length(const std::uint16_t* text) {
  std::uint32_t length = 0;
  while (text[length] != 0) {
    ++length;
  }
  return length;
}

void call_presentation_service(OpaqueUiObject* service) {
  auto* presentation = unresolved_contracts::pkg18_re_0067caa0();
  object_slot<ObjectSlot4C>(presentation, 0x4c)(presentation, 0,
                                                object_word(service));
}

void call_app_state(Opaque state) {
  auto* app_system = unresolved_contracts::pkg18_re_0067dcc0();
  object_slot<AppSlot14>(app_system, 0x14)(app_system, state, 0, 0);
}

}

bool PKG18_THISCALL pkg18_ui_shell_dispatch_005bf9d0(OpaqueUiShell* shell,
                                                     Opaque message_id,
                                                     OpaqueUiMessage* message) {
  if (message_id <= 0x14418c3fu) {
    if (message_id == 0x14418c3fu) {
      if (load_message<Opaque>(message, 0) != load_shell<Opaque>(shell, 0x18)) {
        return false;
      }
      auto* service = lookup(load_service(shell, 0x14), 0xaddc11efu, 1);
      if (service != nullptr) {
        object_slot<ObjectSlot80>(service, 0x80)(
            service, load_message<Opaque>(message, 8));
      }
      return true;
    }
    if (message_id == 0x01ee1001u) {
      if (load_shell<std::uint8_t>(shell, 0x0c) == 0) {
        return false;
      }
      const auto* payload = reinterpret_cast<const unsigned char*>(
          load_message<Opaque>(message, 8));
      if (load<std::uint32_t>(payload, 0x08) != 5 ||
          load<std::uint32_t>(payload, 0x0c) != 1000 ||
          load<std::uint8_t>(payload, 0x10) != 1) {
        return false;
      }
      if (unresolved_contracts::pkg18_re_008053b0() != 0) {
        return false;
      }
      Opaque message_word = reinterpret_cast<Opaque>(message);
      Opaque message_id_word = message_id;
      unresolved_contracts::pkg18_re_00804f80(
          static_cast<float>(load<std::int32_t>(payload, 0x14)),
          static_cast<float>(load<std::int32_t>(payload, 0x18)), &message_word,
          &message_id_word);
      auto* presentation = unresolved_contracts::pkg18_re_0067caa0();
      auto* item = object_slot<ObjectSlot44>(presentation, 0x44)(presentation,
                                                                 &message_word);
      auto* target = lookup(load_service(shell, 0x14), 0x272eb68eu, 1);
      if (item != target) {
        while (item != nullptr) {
          item = object_slot<ObjectSlot10>(item, 0x10)(item);
          if (item == target) {
            return true;
          }
        }
        call_shell_parent(shell, 0);
      }
      return true;
    }
    if (message_id == 0x073127e6u) {
      if (load_message<Opaque>(message, 0) != load_shell<Opaque>(shell, 0x18)) {
        return false;
      }
      auto* service = lookup(load_service(shell, 0x14), 0x5415e48u, 1);
      if (service != nullptr) {
        object_slot<ObjectSlot80>(service, 0x80)(
            service, load_message<Opaque>(message, 8));
      }
      return true;
    }
    return false;
  }
  if (message_id == 0x7aa519dcu) {
    if (load_message<Opaque>(message, 0) != load_shell<Opaque>(shell, 0x18)) {
      return false;
    }
    unresolved_contracts::pkg18_re_005bf950(
        shell, reinterpret_cast<const std::uint16_t*>(
                   load_message<Opaque>(message, 8)));
    return true;
  }
  return false;
}

void PKG18_THISCALL pkg18_ui_shell_set_enabled_005c0380(OpaqueUiShell* shell,
                                                        std::uint8_t enabled) {
  if (load_shell<std::uint8_t>(shell, 0x10) == enabled) {
    return;
  }
  store_shell(shell, 0x10, enabled);
  auto* manager = load_service(shell, 0x18);
  if (enabled != 0) {
    configure_registry(manager, 0x272eb68eu, 1);
    configure_registry(manager, 0x453ef531u, 1);
    if (load_shell<std::uint8_t>(shell, 0x11) != 0) {
      auto* text_service = lookup(manager, 0xc7ceb1bdu, 1);
      if (text_service != nullptr) {
        call_service_7c(text_service, 1, 1);
        auto* text_controller = object_slot<ObjectSlot0C>(text_service, 0x0c)(
            text_service, 0xcf428691u);
        const auto* source =
            object_slot<ObjectSlot3C>(text_service, 0x3c)(text_service);
        object_slot<ObjectSlot94>(text_controller, 0x94)(
            text_controller, wide_length(source), 0);
        object_slot<ObjectSlotDC>(text_controller, 0xdc)(text_controller);
        call_presentation_service(text_service);
      }
      auto* secondary = lookup(manager, 0xd0e6d04bu, 1);
      if (secondary != nullptr) {
        call_service_7c(secondary, 1, 0);
      }
    }
    auto* add_service = lookup(manager, 0xaddc11efu, 1);
    if (add_service != nullptr) {
      call_service_7c(add_service, 2, 1);
    }
    auto* second_service = lookup(manager, 0x5415e48u, 1);
    if (second_service != nullptr) {
      call_service_7c(second_service, 2, 1);
    }
    auto* mode_service = lookup(manager, 0x0552c901u, 1);
    if (mode_service != nullptr && load_shell<Opaque>(shell, 0x20) != 0) {
      call_service_7c(mode_service, 1, 1);
      call_service_7c(mode_service, 2, 1);
    }
    unresolved_contracts::pkg18_re_00435ed0(0x6871e3b9u, 0x046adfeeu);
    call_app_state(0x716d445u);
    return;
  }

  configure_registry(manager, 0x272eb68eu, 0);
  configure_registry(manager, 0x453ef531u, 0);
  if (load_shell<std::uint8_t>(shell, 0x11) != 0) {
    auto* text_service = lookup(manager, 0xc7ceb1bdu, 1);
    if (text_service != nullptr) {
      call_service_7c(text_service, 1, 0);
    }
    const auto* source =
        object_slot<ObjectSlot3C>(text_service, 0x3c)(text_service);
    Opaque range[3]{};
    unresolved_contracts::pkg18_re_00579a90(range, source);
    unresolved_contracts::pkg18_re_0057eda0(range);
    const std::int32_t span = static_cast<std::int32_t>(range[1]) -
                              static_cast<std::int32_t>(range[0]);
    const std::uint32_t masked = static_cast<std::uint32_t>(span) & 0xfffffffeu;
    if (masked == 0) {
      auto* provider = load_service(shell, 0x1c);
      const auto fallback =
          object_slot<ProviderSlot04>(provider, 0x04)(provider);
      unresolved_contracts::pkg18_re_005bf950(
          shell, reinterpret_cast<const std::uint16_t*>(fallback));
    } else {
      const auto* text = reinterpret_cast<const std::uint16_t*>(range[0]);
      unresolved_contracts::pkg18_re_005bf950(shell, text);
      auto* provider = load_service(shell, 0x1c);
      object_slot<ProviderSlot00>(provider, 0x00)(provider, text);
    }
    if (masked > 2 && range[0] != 0) {
      unresolved_contracts::pkg18_re_00f47380(range[0]);
    }
    auto* secondary = lookup(manager, 0xd0e6d04bu, 1);
    if (secondary != nullptr) {
      call_service_7c(secondary, 1, 1);
    }
  }
  auto* add_service = lookup(manager, 0xaddc11efu, 1);
  if (add_service != nullptr) {
    const auto* text =
        object_slot<ObjectSlot3C>(add_service, 0x3c)(add_service);
    auto* provider = load_service(shell, 0x1c);
    object_slot<ProviderSlot08>(provider, 0x08)(provider, text);
    call_service_7c(add_service, 2, 0);
  }
  auto* second_service = lookup(manager, 0x5415e48u, 1);
  if (second_service != nullptr) {
    const auto* text =
        object_slot<ObjectSlot3C>(second_service, 0x3c)(second_service);
    auto* provider = load_service(shell, 0x1c);
    object_slot<ProviderSlot10>(provider, 0x10)(provider, text);
    call_service_7c(second_service, 2, 0);
  }
  auto* mode_service = lookup(manager, 0x0552c901u, 1);
  if (mode_service != nullptr) {
    call_service_7c(mode_service, 1, 0);
    call_service_7c(mode_service, 2, 0);
  }
  unresolved_contracts::pkg18_re_00435ed0(0x6871e3b9u, 0x046adfeeu);
  call_app_state(0x716d446u);
}

bool PKG18_THISCALL pkg18_ui_shell_handle_message_005c0100(
    OpaqueUiShell* shell, Opaque unused, OpaqueUiMessage* message) {
  static_cast<void>(unused);
  const Opaque message_type = load_message<Opaque>(message, 8);
  if (message_type == 1) {
    const Opaque subtype = load_message<Opaque>(message, 0x10);
    if (subtype == 0x0du || subtype == 0x1bu) {
      if ((load_message<std::uint8_t>(message, 0x14) & 0x47u) == 0 &&
          load_shell<std::uint8_t>(shell, 0x10) != 0) {
        shell_slot<ShellSlot1C>(shell, 0x1c)(shell, 0);
        auto* presentation = unresolved_contracts::pkg18_re_0067caa0();
        object_slot<ObjectSlot4C>(presentation, 0x4c)(
            presentation, 0, load_shell<Opaque>(shell, 0x34));
        return true;
      }
      return false;
    }
    if (subtype == 9 && load_message<Opaque>(message, 4) != 0) {
      auto* owner =
          reinterpret_cast<OpaqueUiObject*>(load_message<Opaque>(message, 4));
      const Opaque owner_type = object_slot<ObjectSlot1C>(owner, 0x1c)(owner);
      auto* manager = load_service(shell, 0x18);
      if (owner_type == 0xc7ceb1bdu) {
        return submit_to_presentation(lookup(manager, 0xaddc11efu, 1));
      }
      if (owner_type == 0xaddc11efu) {
        if (submit_to_presentation(lookup(manager, 0x5415e48u, 1))) {
          return true;
        }
        return submit_to_presentation(lookup(manager, 0xc7ceb1bdu, 1));
      }
      if (owner_type == 0x5415e48u) {
        return submit_to_presentation(lookup(manager, 0xc7ceb1bdu, 1));
      }
    }
    return false;
  }
  if (message_type == 0x18u) {
    if (load_message<Opaque>(message, 0x0c) == 1) {
      shell_slot<ShellSlot1C>(shell, 0x1c)(
          shell, load_message<Opaque>(message, 0x14) == 1);
      return true;
    }
    return false;
  }
  if (message_type == 0x287259f6u && load_message<Opaque>(message, 0x0c) == 2) {
    auto* app = unresolved_contracts::pkg18_re_00a206f0();
    const Opaque app_value =
        app == nullptr ? 0 : object_slot<ObjectSlot20>(app, 0x20)(app);
    unresolved_contracts::pkg18_re_00435ed0(0xa03e74b2u, app_value);
    Opaque range[3]{};
    const Opaque value = load_shell<Opaque>(shell, 0x20);
    auto* names = unresolved_contracts::pkg18_re_004010a0(value, range);
    static_cast<void>(
        unresolved_contracts::pkg18_re_005ecf80(names, range, value));
    unresolved_contracts::pkg18_re_005bf950(
        shell, reinterpret_cast<const std::uint16_t*>(range[0]));
    const std::int32_t span = static_cast<std::int32_t>(range[1]) -
                              static_cast<std::int32_t>(range[0]);
    if ((static_cast<std::uint32_t>(span) & 0xfffffffeu) > 2 && range[0] != 0) {
      unresolved_contracts::pkg18_re_00f47380(range[0]);
    }
    return true;
  }
  return false;
}

}
