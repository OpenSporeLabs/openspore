# Obj17 part A: deterministic cell simulation (movement + one interaction +
# scripted input replay). Pure C++ — no GPU, no SPORE/ package.
add_library(openspore_sim STATIC
  Sim.cpp)
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
