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

# CS-24: the real cell-stage GMDL family (groups 0x40616201/02). Env-dependent;
# skips gracefully when SPORE/ is absent. Proves the decoder walks the cell
# family (baked-deform trailer) and the scene's models decode to the right
# vertex counts.
add_executable(cell_gmdl_test tests/cell_gmdl_test.cpp)
target_link_libraries(cell_gmdl_test PRIVATE openspore_assets)
add_test(
  NAME assets_cellgmdl
  COMMAND cell_gmdl_test ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Content.package)

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

# CS-05: decode the cCellCellResource records (796 B, type 0xDFAD9F51).
# Env-dependent: loads the real cell packages at test time; skips gracefully
# when SPORE/ is absent. Proves every record walks well-formed, is sane, and
# double-decodes byte-identically.
add_executable(cell_cell_test tests/cell_cell_test.cpp)
target_link_libraries(cell_cell_test PRIVATE openspore_assets)
add_test(
  NAME assets_cellcell
  COMMAND
    cell_cell_test ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Game.package
    ${PROJECT_SOURCE_DIR}/SPORE/DataEP1/Spore_EP1_Data.package)

# CS-06: decode the cCellWorldResource records (type 0x9B8E862F, variable
# length: header + inlined level/advect arrays). Env-dependent; skips
# gracefully when SPORE/ is absent.
add_executable(cell_world_test tests/cell_world_test.cpp)
target_link_libraries(cell_world_test PRIVATE openspore_assets)
add_test(
  NAME assets_cellworld
  COMMAND
    cell_world_test ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Game.package
    ${PROJECT_SOURCE_DIR}/SPORE/DataEP1/Spore_EP1_Data.package)

# CS-07: decode the cCellPopulateResource records (type 0xDA141C1B, variable
# length: header + inlined cMarker[76B] arrays). Env-dependent; skips
# gracefully when SPORE/ is absent. Refs must resolve to real cell records.
add_executable(cell_populate_test tests/cell_populate_test.cpp)
target_link_libraries(cell_populate_test PRIVATE openspore_assets)
add_test(
  NAME assets_cellpopulate
  COMMAND
    cell_populate_test ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Game.package
    ${PROJECT_SOURCE_DIR}/SPORE/DataEP1/Spore_EP1_Data.package)

# CS-08: decode the cCellStructureResource records (type 0x4B9EF6DC, variable
# length: header + inlined cSPAttachment[40B] arrays). Env-dependent; skips
# gracefully when SPORE/ is absent. cell.structure refs must resolve.
add_executable(cell_structure_test tests/cell_structure_test.cpp)
target_link_libraries(cell_structure_test PRIVATE openspore_assets)
add_test(
  NAME assets_cellstructure
  COMMAND
    cell_structure_test ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Game.package
    ${PROJECT_SOURCE_DIR}/SPORE/Data/PatchData.package
    ${PROJECT_SOURCE_DIR}/SPORE/DataEP1/Spore_EP1_Data.package)

# CS-09: decode the cCellLootTableResource records (type 0xD92AF091, variable
# length: header + inlined cLootTableEntry[28B] arrays). Env-dependent; skips
# gracefully when SPORE/ is absent. Entry refs must resolve.
add_executable(cell_loot_test tests/cell_loot_test.cpp)
target_link_libraries(cell_loot_test PRIVATE openspore_assets)
add_test(
  NAME assets_cellloot
  COMMAND
    cell_loot_test ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Game.package
    ${PROJECT_SOURCE_DIR}/SPORE/Data/PatchData.package
    ${PROJECT_SOURCE_DIR}/SPORE/DataEP1/Spore_EP1_Data.package)

# CS-10: decode the cCellLookTableResource (0x8C042499) and
# cCellLookAlgorithmResource (0xDBA35AE2) records. Env-dependent; skips
# gracefully when SPORE/ is absent. Algorithm table refs must resolve.
add_executable(cell_look_test tests/cell_look_test.cpp)
target_link_libraries(cell_look_test PRIVATE openspore_assets)
add_test(
  NAME assets_celllook
  COMMAND
    cell_look_test ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Game.package
    ${PROJECT_SOURCE_DIR}/SPORE/Data/PatchData.package
    ${PROJECT_SOURCE_DIR}/SPORE/DataEP1/Spore_EP1_Data.package)

# CS-11: decode the cCellRandomCreatureResource (0xF9C3D770) and
# cCellPowersResource (0x754BE343) records. Env-dependent; skips gracefully
# when SPORE/ is absent.
add_executable(randcreature_test tests/randcreature_test.cpp)
target_link_libraries(randcreature_test PRIVATE openspore_assets)
add_test(
  NAME assets_randcreature
  COMMAND
    randcreature_test ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Game.package
    ${PROJECT_SOURCE_DIR}/SPORE/Data/PatchData.package
    ${PROJECT_SOURCE_DIR}/SPORE/DataEP1/Spore_EP1_Data.package)

# CS-12: decode the cCellEffectMapResource (0x433FB70C) and
# cCellBackgroundMapResource (0x612B3191) records. Env-dependent; skips
# gracefully when SPORE/ is absent.
add_executable(effectmap_test tests/effectmap_test.cpp)
target_link_libraries(effectmap_test PRIVATE openspore_assets)
add_test(
  NAME assets_effectmap
  COMMAND
    effectmap_test ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Game.package
    ${PROJECT_SOURCE_DIR}/SPORE/Data/PatchData.package
    ${PROJECT_SOURCE_DIR}/SPORE/DataEP1/Spore_EP1_Data.package)

# CS-04: walk the RW4 graphics containers (0x2F4E681B). Env-dependent: loads
# the real content package at test time; skips gracefully when SPORE/ is
# absent. Proves every record walks well-formed (manifest/types tc, in-bounds
# section data, known type codes).
add_executable(rw4_test tests/rw4_test.cpp)
target_link_libraries(rw4_test PRIVATE openspore_assets)
add_test(
  NAME assets_rw4
  COMMAND rw4_test ${PROJECT_SOURCE_DIR}/SPORE/Data/Spore_Content.package)
