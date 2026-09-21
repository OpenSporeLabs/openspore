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

add_subdirectory(src)
