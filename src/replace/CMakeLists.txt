# Obj36C/36D: clean-room replacement of
# Simulator::Cell::MovePlayerToMousePosition + decompilation-derived
# differential test (docs/REPLACEMENT-ABI.md, docs/REPLACEMENT-DIFF.md).
# Pure C++ — no GPU, no SPORE/ package.
add_library(openspore_replace STATIC Replace.cpp Reference.cpp)
target_include_directories(openspore_replace PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(openspore_replace PUBLIC openspore_sim)

# The differential driver: decompilation reference vs the replacement,
# per-field comparison with explicit tolerance.
add_executable(replace_diff_test tests/diff_test.cpp)
target_link_libraries(replace_diff_test PRIVATE openspore_replace)
add_test(
  NAME replace_diff_test
  COMMAND replace_diff_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
