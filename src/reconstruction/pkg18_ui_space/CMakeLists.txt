cmake_minimum_required(VERSION 3.16)
project(pkg18_ui_space LANGUAGES CXX)

add_library(pkg18_ui_space STATIC
  ui_space.cpp
)
target_include_directories(pkg18_ui_space PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_features(pkg18_ui_space PUBLIC cxx_std_17)

if(MSVC)
  target_compile_options(pkg18_ui_space PRIVATE /W4 /WX)
else()
  target_compile_options(pkg18_ui_space PRIVATE
    -Wall -Wextra -Werror)
endif()

add_executable(pkg18_ui_space_test
  ui_space_model_test.cpp
)
target_link_libraries(pkg18_ui_space_test PRIVATE
  pkg18_ui_space
)
target_compile_features(pkg18_ui_space_test PRIVATE cxx_std_17)

if(MSVC)
  target_compile_options(pkg18_ui_space_test PRIVATE /W4 /WX)
else()
  target_compile_options(pkg18_ui_space_test PRIVATE
    -Wall -Wextra -Werror)
endif()

enable_testing()
add_test(NAME pkg18_ui_space
  COMMAND pkg18_ui_space_test)
