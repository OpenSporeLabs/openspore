# Shader pipeline: GLSL (checked in, original) -> SPIR-V (build-time,
# glslangValidator, REQUIRED — no fallback) -> embedded C arrays
# (shaders_spv.h) -> compiled into the renderer library.
find_program(GLSLANG_VALIDATOR glslangValidator REQUIRED)

set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/renderer/shaders)
set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

add_custom_command(
  OUTPUT ${GENERATED_DIR}/triangle.vert.spv
  COMMAND ${GLSLANG_VALIDATOR} -V ${SHADER_DIR}/triangle.vert -o ${GENERATED_DIR}/triangle.vert.spv
  DEPENDS ${SHADER_DIR}/triangle.vert
  COMMENT "Compiling triangle.vert to SPIR-V"
  VERBATIM)
add_custom_command(
  OUTPUT ${GENERATED_DIR}/triangle.frag.spv
  COMMAND ${GLSLANG_VALIDATOR} -V ${SHADER_DIR}/triangle.frag -o ${GENERATED_DIR}/triangle.frag.spv
  DEPENDS ${SHADER_DIR}/triangle.frag
  COMMENT "Compiling triangle.frag to SPIR-V"
  VERBATIM)
add_custom_command(
  OUTPUT ${GENERATED_DIR}/lit.vert.spv
  COMMAND ${GLSLANG_VALIDATOR} -V ${SHADER_DIR}/lit.vert -o ${GENERATED_DIR}/lit.vert.spv
  DEPENDS ${SHADER_DIR}/lit.vert
  COMMENT "Compiling lit.vert to SPIR-V"
  VERBATIM)
add_custom_command(
  OUTPUT ${GENERATED_DIR}/lit.frag.spv
  COMMAND ${GLSLANG_VALIDATOR} -V ${SHADER_DIR}/lit.frag -o ${GENERATED_DIR}/lit.frag.spv
  DEPENDS ${SHADER_DIR}/lit.frag
  COMMENT "Compiling lit.frag to SPIR-V"
  VERBATIM)
add_custom_command(
  OUTPUT ${GENERATED_DIR}/shaders_spv.h
  COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/renderer/embed_spv.py
          ${GENERATED_DIR}/triangle.vert.spv ${GENERATED_DIR}/triangle.frag.spv
          ${GENERATED_DIR}/lit.vert.spv ${GENERATED_DIR}/lit.frag.spv
          ${GENERATED_DIR}/shaders_spv.h
  DEPENDS ${GENERATED_DIR}/triangle.vert.spv ${GENERATED_DIR}/triangle.frag.spv
          ${GENERATED_DIR}/lit.vert.spv ${GENERATED_DIR}/lit.frag.spv
          ${CMAKE_CURRENT_SOURCE_DIR}/renderer/embed_spv.py
  COMMENT "Embedding SPIR-V as C arrays"
  VERBATIM)

add_library(openspore_renderer STATIC
  renderer/VulkanRenderer.cpp
  ${GENERATED_DIR}/shaders_spv.h)
target_include_directories(openspore_renderer PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${GENERATED_DIR})
target_link_libraries(openspore_renderer PUBLIC Vulkan::Vulkan)

# Shared machine lock (flock /tmp/openspore-machine.lock; body via
# tools/observatory/lock.py; same prefix as the MCP runtime tools and
# menu_walk.sh): display/GPU work serializes with agent trace runs.
set(MACHINE_LOCK ${PROJECT_SOURCE_DIR}/tools/observatory/machine_lock.sh)

add_executable(triangle apps/triangle.cpp)
target_link_libraries(triangle PRIVATE openspore_renderer)

# Smoke test: the app itself checks pixels and exits non-zero on FAIL.
add_test(
  NAME triangle_smoke
  COMMAND sh ${MACHINE_LOCK} triangle
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Objective-8b vertical slice: renders the real chosen gmdl record through
# the Vulkan backend and asserts pixel evidence. Env-dependent (skips when
# SPORE/ is absent); the PPM lands in the build dir, never in git.
add_executable(asset_view apps/asset_view.cpp)
target_link_libraries(asset_view PRIVATE openspore_assets openspore_renderer)
add_test(
  NAME asset_render
  COMMAND sh ${MACHINE_LOCK} asset_view ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Content.package
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Obj15: renders the real mesh through the normal-lit textured path with its
# real DXT5 texture and asserts non-uniform texture pixels + frame-to-frame
# light change. Env-dependent (skips when SPORE/ is absent).
add_executable(material_smoke apps/material_smoke.cpp)
target_link_libraries(material_smoke PRIVATE openspore_assets openspore_renderer)
add_test(
  NAME material_smoke
  COMMAND sh ${MACHINE_LOCK} material_smoke ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Content.package
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Obj16: minimal Cell Stage scene — backdrop patches (real DXT5 texture),
# a stand-in player cell, and food/prey objects, offscreen PPM + a
# deterministic scene manifest on stdout. Env-dependent (skips when SPORE/
# is absent); the PPM lands in the build dir, never in git.
# CS-23: the scene is declarative (apps/scene.json) — SceneConfig loads it.
# CS-26: CellGfx mirrors the cCellGFX preload path (worlds + preloaded records).
add_executable(cell_stage apps/cell_stage.cpp apps/SceneConfig.cpp
  apps/CellGfx.cpp apps/CellUI.cpp apps/CellInput.cpp
  apps/CellModeStrategy.cpp apps/CellAnim.cpp)
target_compile_definitions(cell_stage PRIVATE
  SPORE_CELLSTAGE_SCENE="${CMAKE_CURRENT_SOURCE_DIR}/apps/scene.json")
target_link_libraries(cell_stage PRIVATE
  openspore_assets openspore_renderer openspore_sim)
# Obj17 part B: interactive mode needs SDL3 (window + WSI surface). When the
# system lacks SDL3 the build still works; --interactive prints a notice and
# exits 0.
if(TARGET SDL3::SDL3)
  target_link_libraries(cell_stage PRIVATE SDL3::SDL3)
  target_compile_definitions(cell_stage PRIVATE SPORE_HAS_SDL3=1)
elseif(PkgConfig_FOUND AND PkgConfig::SDL3)
  target_link_libraries(cell_stage PRIVATE PkgConfig::SDL3)
  target_compile_definitions(cell_stage PRIVATE SPORE_HAS_SDL3=1)
endif()
 add_test(
   NAME cell_stage
   COMMAND cell_stage ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Content.package
     --bgmap ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Game.package
   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# CS-23: declarative scene config — hermetic (no GPU, no SPORE/). Loads
# apps/scene.json and asserts the entities + provenance labels round-trip.
add_executable(scene_config_test apps/scene_config_test.cpp apps/SceneConfig.cpp)
add_test(
  NAME scene_config
  COMMAND scene_config_test ${CMAKE_CURRENT_SOURCE_DIR}/apps/scene.json
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# CS-26: cCellGFX preload path — world-handle table + preloaded record keys.
add_executable(cellgfx_test apps/cellgfx_test.cpp apps/CellGfx.cpp)
add_test(
  NAME cellgfx
  COMMAND cellgfx_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# CS-27: cCellUI HUD — Load constants + ShowHealthRollover formula.
add_executable(cellui_test apps/cellui_test.cpp apps/CellUI.cpp)
add_test(
  NAME cellui
  COMMAND cellui_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# CS-28: cCellModeStrategy lifecycle (vtable slots 6/7/8/9/11/17) +
# cGameModeManager switching (OnExit old, OnEnter new, reject OOB index).
add_executable(cellmode_test apps/cellmode_test.cpp apps/CellModeStrategy.cpp
  apps/CellGfx.cpp apps/CellUI.cpp)
add_test(
  NAME cellmode
  COMMAND cellmode_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# CS-29: table-driven key->action (the app's scancode mapping + the
# virtualKey==2 health-toggle special case).
add_executable(cellinput_test apps/cellinput_test.cpp apps/CellInput.cpp)
add_test(
  NAME cellinput
  COMMAND cellinput_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# CS-31: cell animation blend state machine (PlayAnimation @ 00e6d200) +
# event->effect mapping (InstanceEffectOnCell @ 00e66840, LoadEffectMap
# @ 00e63560 3-slot selection). The keyframe decode diff is the existing
# rw4_test (CS-04).
add_executable(cellanim_test apps/cellanim_test.cpp apps/CellAnim.cpp)
add_test(
  NAME cellanim
  COMMAND cellanim_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Obj17 part B smoke: interactive mode with no display must fail gracefully
# (exit 0 with a "no display" notice, never crash). A real Wayland session
# (e.g. KWin) exports WAYLAND_DISPLAY, and SDL's wayland backend falls back to
# the default wayland-0 socket even when the variable is unset — so point it at
# a nonexistent socket and DISPLAY at a dead X server to force every backend to
# fail.
add_test(
  NAME cell_stage_interactive_smoke
  COMMAND bash -c "env -u XDG_SESSION_TYPE DISPLAY=:99 WAYLAND_DISPLAY=invalid-socket-xyz sh ${MACHINE_LOCK} ./cell_stage ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Content.package --interactive 2>&1 | grep -q 'cell_stage: interactive:'"
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set_tests_properties(cell_stage_interactive_smoke PROPERTIES
  TIMEOUT 20
  ENVIRONMENT "DISPLAY=:99")

add_executable(editor_support_test editor/tests/editor_support_test.cpp
  editor/EditorSupport.cpp)
add_test(
  NAME editor_support
  COMMAND editor_support_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_executable(cell_presentation_test apps/cell_presentation_test.cpp
  apps/CellPresentation.cpp apps/CellSceneStage.cpp
  apps/CellGfx.cpp apps/CellUI.cpp)
target_link_libraries(cell_presentation_test PRIVATE
  openspore_assets openspore_renderer)
add_test(
  NAME cell_presentation
  COMMAND cell_presentation_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(assets)
add_subdirectory(sim)
add_subdirectory(replace)
