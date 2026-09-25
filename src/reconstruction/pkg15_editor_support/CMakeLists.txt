cmake_minimum_required(VERSION 3.16)
project(pkg15_editor_support LANGUAGES CXX)

add_library(pkg15_editor_support STATIC
  editor_support.cpp
)
target_include_directories(pkg15_editor_support PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_features(pkg15_editor_support PUBLIC cxx_std_17)

if(MSVC)
  target_compile_options(pkg15_editor_support PRIVATE /W4 /WX)
else()
  target_compile_options(pkg15_editor_support PRIVATE
    -Wall -Wextra -Werror)
endif()

add_executable(pkg15_editor_support_test
  editor_support_model_test.cpp
)
target_link_libraries(pkg15_editor_support_test PRIVATE
  pkg15_editor_support
)
target_compile_features(pkg15_editor_support_test PRIVATE cxx_std_17)

if(MSVC)
  target_compile_options(pkg15_editor_support_test PRIVATE /W4 /WX)
else()
  target_compile_options(pkg15_editor_support_test PRIVATE
    -Wall -Wextra -Werror)
endif()

enable_testing()
add_test(NAME pkg15_editor_support
  COMMAND pkg15_editor_support_test)
