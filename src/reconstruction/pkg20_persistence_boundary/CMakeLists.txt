cmake_minimum_required(VERSION 3.16)
project(openspore_pkg20_persistence_boundary LANGUAGES CXX)
find_package(Python3 COMPONENTS Interpreter REQUIRED)

add_library(openspore_pkg20_persistence_boundary STATIC
  persistence_boundary.cpp)
target_include_directories(openspore_pkg20_persistence_boundary PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(openspore_pkg20_persistence_boundary PUBLIC cxx_std_17)

if(MSVC)
  target_compile_options(openspore_pkg20_persistence_boundary PRIVATE /W4 /WX)
else()
  target_compile_options(openspore_pkg20_persistence_boundary PRIVATE
    -Wall -Wextra -Werror)
endif()

add_executable(pkg20_persistence_boundary_test
  persistence_boundary_test.cpp)
target_link_libraries(pkg20_persistence_boundary_test PRIVATE
  openspore_pkg20_persistence_boundary)
target_compile_features(pkg20_persistence_boundary_test PRIVATE cxx_std_17)

if(MSVC)
  target_compile_options(pkg20_persistence_boundary_test PRIVATE /W4 /WX)
else()
  target_compile_options(pkg20_persistence_boundary_test PRIVATE
    -Wall -Wextra -Werror)
endif()

enable_testing()
add_test(NAME pkg20_persistence_boundary
  COMMAND pkg20_persistence_boundary_test)
add_test(NAME pkg20_persistence_boundary_metadata_abi
  COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/metadata_abi_test.py")
