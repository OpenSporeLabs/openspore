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
