cmake_minimum_required(VERSION 3.16)
project(openspore CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Zero-warning policy for first-party code.
add_compile_options(-Wall -Wextra -Werror)

find_package(Vulkan REQUIRED)

# SDL3 for the interactive Cell Stage presentation (Obj17b). Optional at
# configure time: when absent, cell_stage builds without --interactive
# support (the flag then prints a clear message and skips).
find_package(SDL3 CONFIG QUIET)
if(NOT SDL3_FOUND)
  find_package(PkgConfig QUIET)
  if(PkgConfig_FOUND)
    pkg_check_modules(SDL3_PC QUIET IMPORTED_TARGET sdl3)
  endif()
  if(SDL3_PC_FOUND)
    set(SDL3_FOUND TRUE)
  endif()
endif()

enable_testing()

# CS-22: canonical asset manifest — idempotent build (double-run byte-identical,
# full index coverage). Hermetic: runs over the small fixture package.
find_program(PYTHON3 python3 REQUIRED)
add_test(
  NAME manifest_test
  COMMAND ${PYTHON3} ${CMAKE_CURRENT_SOURCE_DIR}/tools/spore/manifest/manifest.py
          verify ${CMAKE_CURRENT_SOURCE_DIR}/tests/fixtures/mini_package.dbpf
          --out ${CMAKE_CURRENT_BINARY_DIR}/manifest_test.db)

add_subdirectory(src)
