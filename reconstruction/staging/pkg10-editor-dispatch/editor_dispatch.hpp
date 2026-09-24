#pragma once

#include <cstdint>

namespace openspore::reconstruction::pkg10_editor_dispatch {

struct OpaqueEditor;
struct OpaqueEditorModeManager;
struct OpaqueEditorModeTarget;

inline constexpr std::uint32_t kEditorModeTargetVtableOffset = 0x7c;
inline constexpr std::uint32_t kEditorModeTargetVtableSlot = 0x1f;

using EditorModeTargetSlot7C = void(__thiscall *)(OpaqueEditorModeTarget *,
                                                  std::uint32_t, std::uint32_t);

static_assert(sizeof(EditorModeTargetSlot7C) == 4,
              "the raw x86 target slot requires a 32-bit function pointer");

void __thiscall editor_mode_manager_set_active_mode(OpaqueEditorModeManager *,
                                                    std::uint32_t);

bool __thiscall editor_set_active_mode(OpaqueEditor *, std::uint32_t,
                                       std::uint32_t);

void *__thiscall editor_mode_manager_lookup_target(OpaqueEditorModeManager *,
                                                   std::uint32_t);

void __thiscall
editor_mode_manager_apply_target_state(OpaqueEditorModeManager *, std::uint32_t,
                                       std::uint32_t, std::uint32_t);

void __thiscall editor_mode_manager_set_lighting(OpaqueEditorModeManager *,
                                                 std::uint32_t);

} // namespace openspore::reconstruction::pkg10_editor_dispatch
