# Objective-8a asset pipeline: DBPF v3 + QFS + minimal GMDL walker -> Mesh.
add_library(openspore_assets STATIC
  Dbpf.cpp
  Dxt5.cpp
  Gmdl.cpp
  Mesh.cpp
  Texture.cpp)
target_include_directories(openspore_assets PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(assets_test tests/assets_test.cpp)
target_link_libraries(assets_test PRIVATE openspore_assets)
add_test(
  NAME assets_synthetic
  COMMAND assets_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Env-dependent: loads the real chosen asset from the local game install at
# test time (never commits asset bytes). Skips gracefully when SPORE/ is
# absent, so CI without the game still passes.
add_executable(real_asset_test tests/real_asset_test.cpp)
target_link_libraries(real_asset_test PRIVATE openspore_assets)
add_test(
  NAME assets_real
  COMMAND real_asset_test ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Content.package)
