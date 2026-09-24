#include "editor_dispatch.hpp"

#include <cstdint>
#include <cstring>

namespace openspore::reconstruction::pkg10_editor_dispatch {

namespace unresolved_contracts {

using UnresolvedMode2GuardResult = void *;

extern UnresolvedMode2GuardResult __thiscall mode2_guard(OpaqueEditor *,
                                                         std::uint32_t);

extern void editor_mode_notify(std::uint32_t);

extern void *__thiscall raw_manager_lookup(void *, std::uint32_t,
                                           std::uint32_t);

extern std::uint8_t __thiscall raw_manager_set_state(void *, std::uint32_t);

extern std::uint8_t __thiscall
raw_manager_apply_state(void *, void *, std::uint32_t, std::uint32_t);

extern std::uint8_t __thiscall target_selector(OpaqueEditor *);

} // namespace unresolved_contracts

namespace {

template <typename Value>
Value field_at(const void *object, std::uintptr_t offset) {
  Value value;
  std::memcpy(&value, static_cast<const unsigned char *>(object) + offset,
              sizeof(value));
  return value;
}

template <typename Value>
void store_field(void *object, std::uintptr_t offset, Value value) {
  std::memcpy(static_cast<unsigned char *>(object) + offset, &value,
              sizeof(value));
}

using RawTargetVtable = EditorModeTargetSlot7C *;

void *embedded_manager_subobject(OpaqueEditorModeManager *manager,
                                 std::uintptr_t offset) {
  return reinterpret_cast<unsigned char *>(manager) + offset;
}

void dispatch_target_slot(void *target, std::uint32_t first,
                          std::uint32_t second) {
  if (target == nullptr) {
    return;
  }

  const auto vtable = field_at<RawTargetVtable>(target, 0);
  EditorModeTargetSlot7C slot;
  std::memcpy(&slot, &vtable[kEditorModeTargetVtableSlot], sizeof(slot));
  slot(static_cast<OpaqueEditorModeTarget *>(target), first, second);
}

void dispatch_old_mode_targets(OpaqueEditorModeManager *manager,
                               std::uint32_t old_mode) {
  switch (old_mode) {
  case 0:
    dispatch_target_slot(field_at<OpaqueEditorModeTarget *>(manager, 0x68), 1,
                         0);
    dispatch_target_slot(field_at<OpaqueEditorModeTarget *>(manager, 0x80), 1,
                         0);
    dispatch_target_slot(field_at<OpaqueEditorModeTarget *>(manager, 0x84), 1,
                         0);
    break;
  case 1:
    dispatch_target_slot(field_at<OpaqueEditorModeTarget *>(manager, 0x6c), 1,
                         0);
    break;
  case 2:
    dispatch_target_slot(field_at<OpaqueEditorModeTarget *>(manager, 0x64), 1,
                         1);
    dispatch_target_slot(editor_mode_manager_lookup_target(manager, 0x578ec50u),
                         1, 1);
    dispatch_target_slot(
        editor_mode_manager_lookup_target(manager, 0xf006efa5u), 1, 1);
    dispatch_target_slot(
        editor_mode_manager_lookup_target(manager, 0xb006ef6eu), 1, 1);
    if (auto *target = editor_mode_manager_lookup_target(manager, 0x1140129du);
        target != nullptr) {
      const auto selector = unresolved_contracts::target_selector(
          field_at<OpaqueEditor *>(manager, 0x5c));
      dispatch_target_slot(target, 1, static_cast<std::uint32_t>(selector));
    }
    break;
  default:
    break;
  }
}

void dispatch_new_mode_targets(OpaqueEditorModeManager *manager,
                               std::uint32_t mode) {
  switch (mode) {
  case 0: {
    dispatch_target_slot(field_at<OpaqueEditorModeTarget *>(manager, 0x68), 1,
                         1);
    dispatch_target_slot(editor_mode_manager_lookup_target(manager, 0x578ec50u),
                         1, 1);
    dispatch_target_slot(
        editor_mode_manager_lookup_target(manager, 0xf006efa5u), 1, 1);
    dispatch_target_slot(
        editor_mode_manager_lookup_target(manager, 0xb006ef6eu), 1, 1);
    dispatch_target_slot(field_at<OpaqueEditorModeTarget *>(manager, 0x80), 1,
                         1);
    dispatch_target_slot(field_at<OpaqueEditorModeTarget *>(manager, 0x84), 1,
                         1);

    const auto state = unresolved_contracts::raw_manager_lookup(
        embedded_manager_subobject(manager, 0x14), 0x4fcc580u, 1);
    editor_mode_manager_apply_target_state(manager, 0xf019c2e7u, 1, 1);
    if (state != nullptr) {
      unresolved_contracts::raw_manager_apply_state(
          embedded_manager_subobject(manager, 0x44), state, 1, 0x5b598fau);
      unresolved_contracts::raw_manager_set_state(
          embedded_manager_subobject(manager, 0x44), 1);
    } else {
      unresolved_contracts::raw_manager_set_state(
          embedded_manager_subobject(manager, 0x44), 0);
    }
    break;
  }
  case 1: {
    dispatch_target_slot(field_at<OpaqueEditorModeTarget *>(manager, 0x6c), 1,
                         1);
    const auto state = unresolved_contracts::raw_manager_lookup(
        embedded_manager_subobject(manager, 0x14), 0x4fcc581u, 1);
    if (state != nullptr) {
      unresolved_contracts::raw_manager_apply_state(
          embedded_manager_subobject(manager, 0x44), state, 1, 0x5b598fau);
      unresolved_contracts::raw_manager_set_state(
          embedded_manager_subobject(manager, 0x44), 1);
    } else {
      unresolved_contracts::raw_manager_set_state(
          embedded_manager_subobject(manager, 0x44), 0);
    }
    break;
  }
  case 2:
    dispatch_target_slot(field_at<OpaqueEditorModeTarget *>(manager, 0x64), 1,
                         0);
    dispatch_target_slot(editor_mode_manager_lookup_target(manager, 0x578ec50u),
                         1, 0);
    dispatch_target_slot(
        editor_mode_manager_lookup_target(manager, 0xf006efa5u), 1, 0);
    dispatch_target_slot(
        editor_mode_manager_lookup_target(manager, 0xb006ef6eu), 1, 0);
    dispatch_target_slot(
        editor_mode_manager_lookup_target(manager, 0x1140129du), 1, 0);
    break;
  default:
    unresolved_contracts::raw_manager_set_state(
        embedded_manager_subobject(manager, 0x44), 0);
    break;
  }
}

} // namespace

void __thiscall
editor_mode_manager_set_active_mode(OpaqueEditorModeManager *manager,
                                    std::uint32_t mode) {
  const auto mode_value = mode;
  auto *editor = field_at<OpaqueEditor *>(manager, 0x5c);

  if (mode_value == 2 && unresolved_contracts::mode2_guard(editor, 0) == 0) {
    return;
  }
  if (field_at<std::uint32_t>(manager, 0x60) == mode_value) {
    return;
  }
  if (!editor_set_active_mode(editor, mode, 0)) {
    return;
  }

  unresolved_contracts::editor_mode_notify(0x8c35f293u);
  editor_mode_manager_set_lighting(manager, 0);

  const auto old_mode = field_at<std::uint32_t>(manager, 0x60);
  dispatch_old_mode_targets(manager, old_mode);
  dispatch_new_mode_targets(manager, mode_value);
  store_field<std::uint32_t>(manager, 0x60, mode_value);
}

} // namespace openspore::reconstruction::pkg10_editor_dispatch
