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
  OUTPUT ${GENERATED_DIR}/shaders_spv.h
  COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/renderer/embed_spv.py
          ${GENERATED_DIR}/triangle.vert.spv ${GENERATED_DIR}/triangle.frag.spv
          ${GENERATED_DIR}/shaders_spv.h
  DEPENDS ${GENERATED_DIR}/triangle.vert.spv ${GENERATED_DIR}/triangle.frag.spv
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
