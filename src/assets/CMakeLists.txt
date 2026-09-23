# Objective-8a asset pipeline: DBPF v3 + QFS + minimal GMDL walker -> Mesh.
add_library(openspore_assets STATIC
  CellResource.cpp
  Dbpf.cpp
  Dxt5.cpp
  Gmdl.cpp
  Mesh.cpp
  Rw4.cpp
  Texture.cpp
  WorldObject.cpp)
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

# CS-02: decode the 0x0F43029A world-object records (model-group placement).
# Env-dependent: loads the real content packages at test time; skips gracefully
# when SPORE/ is absent. Proves every byte of every record is accounted for.
add_executable(worldobj_test tests/worldobj_test.cpp)
target_link_libraries(worldobj_test PRIVATE openspore_assets)
add_test(
  NAME assets_worldobj
  COMMAND
    worldobj_test ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Content.package
    ${PROJECT_SOURCE_DIR}/SPORE/DataEP1/Spore_EP1_Content_01.package)

# CS-03: decode the cCellGlobalsResource record (stage-wide cell tuning).
# Env-dependent: loads the real EP1 data package at test time; skips gracefully
# when SPORE/ is absent. Proves the 276-byte record decodes field-by-field.
add_executable(cellres_test tests/cellres_test.cpp)
target_link_libraries(cellres_test PRIVATE openspore_assets)
add_test(
  NAME assets_cellres
  COMMAND
    cellres_test ${PROJECT_SOURCE_DIR}/SPORE/DataEP1/Spore_EP1_Data.package)

# CS-04: walk the RW4 graphics containers (0x2F4E681B). Env-dependent: loads
# the real content package at test time; skips gracefully when SPORE/ is
# absent. Proves every record walks well-formed (manifest/types tc, in-bounds
# section data, known type codes).
add_executable(rw4_test tests/rw4_test.cpp)
target_link_libraries(rw4_test PRIVATE openspore_assets)
add_test(
  NAME assets_rw4
  COMMAND rw4_test ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Content.package)
