# Obj17 part A: deterministic cell simulation (movement + one interaction +
# scripted input replay). Pure C++ — no GPU, no SPORE/ package.
add_library(openspore_sim STATIC
  Sim.cpp
  CellGame.cpp
  CellMovement.cpp)
target_include_directories(openspore_sim PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(sim_test tests/sim_test.cpp)
target_link_libraries(sim_test PRIVATE openspore_sim)
add_test(
  NAME sim_test
  COMMAND sim_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Obj35: contract test. Replays the frozen fixtures and asserts the exact
# per-frame oracle (docs/CELL-CONTRACT.md, cell-sim-contract/2). The fixture
# path is baked in at configure time; regenerate it with
# tools/gen_cell_fixtures.py (which calls `sim_test --emit-fixtures`).
add_executable(sim_contract_test tests/sim_contract_test.cpp)
target_link_libraries(sim_contract_test PRIVATE openspore_sim)
target_compile_definitions(sim_contract_test PRIVATE
  CELL_FIXTURES_PATH="${CMAKE_SOURCE_DIR}/tests/fixtures/cell/fixtures.json")
add_test(
  NAME sim_contract_test
  COMMAND sim_contract_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# CS-01: the movement-plane constants pinned from the original binary
# (normal {0,0,1} read from .data; point {0,0,0} BSS load-time value).
add_executable(plane_constants_test tests/plane_constants_test.cpp)
target_link_libraries(plane_constants_test PRIVATE openspore_sim)
add_test(
  NAME plane_constants_test
  COMMAND plane_constants_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# CS-15: the cCellGame state object's Initialize sequence (time scale, flag
# resets, pool capacity 4096, background-bbox from read constants).
add_executable(cellgame_test tests/cellgame_test.cpp)
target_link_libraries(cellgame_test PRIVATE openspore_sim)
add_test(
  NAME cellgame_test
  COMMAND cellgame_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# CS-16: the main object pool cObjectPool<cCellObjectData> — free-list
# allocation to exhaustion at the VERIFIED capacity 4096, then drain + refill.
add_executable(cellpool_test tests/cellpool_test.cpp)
target_link_libraries(cellpool_test PRIVATE openspore_sim)
add_test(
  NAME cellpool_test
  COMMAND cellpool_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# CS-18: CreateCellObject (largest cell function) — pool alloc + the size
# formula + the cCellObjectData fill (position/elevation/opacity/model key).
add_executable(createcell_test tests/createcell_test.cpp)
target_link_libraries(createcell_test PRIVATE openspore_sim)
add_test(
  NAME createcell_test
  COMMAND createcell_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# CS-19: the cell position query (cCellQueryLinkedPool / cCellQueryEntry) —
# the near predicate |C-P| <= C.size + radius over the pool.
add_executable(cellquery_test tests/cellquery_test.cpp)
target_link_libraries(cellquery_test PRIVATE openspore_sim)
add_test(
  NAME cellquery_test
  COMMAND cellquery_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# CS-20: the advect system (GetCurrentAdvectInfo / GetNextAdvectID) — the
# scale -> bucket-key table (DAT_01483c14) + the advect entry lookup.
add_executable(advect_test tests/advect_test.cpp)
target_link_libraries(advect_test PRIVATE openspore_sim)
add_test(
  NAME advect_test
  COMMAND advect_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# CS-21: cell combat rules (GetScaleDifferenceWithPlayer / GetDamageAmount /
# ShouldNotAttack) — table-driven from the decompiled constants.
add_executable(combat_test tests/combat_test.cpp)
target_link_libraries(combat_test PRIVATE openspore_sim)
add_test(
  NAME combat_test
  COMMAND combat_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_executable(cellmovement_test tests/cellmovement_test.cpp)
target_link_libraries(cellmovement_test PRIVATE openspore_sim)
add_test(
  NAME cellmovement_test
  COMMAND cellmovement_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
