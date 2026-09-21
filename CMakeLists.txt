cmake_minimum_required(VERSION 3.16)
project(openspore CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Zero-warning policy for first-party code.
add_compile_options(-Wall -Wextra -Werror)

find_package(Vulkan REQUIRED)

enable_testing()

add_subdirectory(src)
