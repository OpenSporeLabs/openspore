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

add_executable(triangle apps/triangle.cpp)
target_link_libraries(triangle PRIVATE openspore_renderer)

# Smoke test: the app itself checks pixels and exits non-zero on FAIL.
add_test(
  NAME triangle_smoke
  COMMAND triangle
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Objective-8b vertical slice: renders the real chosen gmdl record through
# the Vulkan backend and asserts pixel evidence. Env-dependent (skips when
# SPORE/ is absent); the PPM lands in the build dir, never in git.
add_executable(asset_view apps/asset_view.cpp)
target_link_libraries(asset_view PRIVATE openspore_assets openspore_renderer)
add_test(
  NAME asset_render
  COMMAND asset_view ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Content.package
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Obj15: renders the real mesh through the normal-lit textured path with its
# real DXT5 texture and asserts non-uniform texture pixels + frame-to-frame
# light change. Env-dependent (skips when SPORE/ is absent).
add_executable(material_smoke apps/material_smoke.cpp)
target_link_libraries(material_smoke PRIVATE openspore_assets openspore_renderer)
add_test(
  NAME material_smoke
  COMMAND material_smoke ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Content.package
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(assets)
