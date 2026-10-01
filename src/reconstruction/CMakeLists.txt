# Promoted reconstruction packages, discovered automatically.
#
# A package is "promoted" iff it is a directory containing a promotion.json
# whose "schema" is "openspore-promotion-1". Nothing else is picked up -- in
# particular the hand-written pkg15/pkg18/pkg20 CMakeLists.txt files are not
# invoked, because those directories have no promotion.json.
#
# No project() call: this file is included from src/CMakeLists.txt.
cmake_minimum_required(VERSION 3.16)

option(OPENSPORE_RECONSTRUCTION_M32
       "Compile promoted reconstruction packages as x86-32 (required: they use __thiscall)" ON)

# Per-target only: -m32 on a single target keeps the surrounding 64-bit project
# linkable, whereas a project-wide -m32 would drag the renderer and the app
# executables along with it.
set(_recon_target_flags -Wall -Wextra -Werror)
if(OPENSPORE_RECONSTRUCTION_M32)
  list(APPEND _recon_target_flags -m32)
else()
  message(WARNING
    "reconstruction: OPENSPORE_RECONSTRUCTION_M32=OFF. Promoted packages use "
    "__attribute__((thiscall)), which clang and gcc both reject in 64-bit under "
    "-Werror=ignored-attributes. Packages that use it will fail to compile; that "
    "is the honest consequence of building x86-32 reconstructions as x86-64.")
endif()

enable_testing()

# The name read out of promotion.json becomes a target name and a test name,
# so it is validated before use. Nothing else about the JSON is trusted.
set(_recon_valid_name "^[A-Za-z0-9_]+$")
file(GLOB _recon_manifests RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
     "${CMAKE_CURRENT_SOURCE_DIR}/*/promotion.json")
list(SORT _recon_manifests)

set(_recon_packages "")

foreach(_recon_manifest IN LISTS _recon_manifests)
  get_filename_component(_recon_dir "${_recon_manifest}" DIRECTORY)
  set(_recon_abs_dir "${CMAKE_CURRENT_SOURCE_DIR}/${_recon_dir}")
  file(READ "${_recon_abs_dir}/promotion.json" _recon_json)

  if(NOT _recon_json MATCHES "\"schema\"[ \t]*:[ \t]*\"openspore-promotion-1\"")
    message(WARNING "reconstruction: ${_recon_dir}/promotion.json has no "
                    "openspore-promotion-1 schema; skipping.")
    continue()
  endif()
  # The value is captured permissively and only then validated, so a hostile
  # name is reported as a rejection naming the offender rather than as a
  # missing field.
  if(NOT _recon_json MATCHES "\"src_package\"[ \t]*:[ \t]*\"([^\"]*)\"")
    message(WARNING "reconstruction: ${_recon_dir}/promotion.json has no usable "
                    "src_package; skipping.")
    continue()
  endif()
  set(_recon_pkg "${CMAKE_MATCH_1}")
  if(NOT _recon_pkg MATCHES "${_recon_valid_name}")
    message(WARNING "reconstruction: rejecting src_package '${_recon_pkg}' in "
                    "${_recon_dir}/promotion.json: must match ${_recon_valid_name}.")
    continue()
  endif()
  if(_recon_pkg IN_LIST _recon_packages)
    message(WARNING "reconstruction: duplicate src_package '${_recon_pkg}' in "
                    "${_recon_dir}/promotion.json; skipping.")
    continue()
  endif()
  if(TARGET ${_recon_pkg})
    message(WARNING "reconstruction: target '${_recon_pkg}' already exists; "
                    "skipping ${_recon_dir}.")
    continue()
  endif()

  # Union of targets[].sources. The arrays are flat, so a scan for the key
  # followed by "[" gives each array body; the body is then read one quoted
  # element at a time. Scanning by position rather than with MATCHALL keeps the
  # key itself out of the element list, and anchoring on the current offset is
  # what stops a key such as "xsources" from matching. Every element is
  # re-validated and required to exist before it reaches add_library().
  set(_recon_sources "")
  set(_recon_reject "")
  string(LENGTH "${_recon_json}" _recon_json_length)
  set(_recon_at 0)
  while(_recon_at LESS _recon_json_length AND NOT _recon_reject)
    string(SUBSTRING "${_recon_json}" ${_recon_at} -1 _recon_rest)
    if(NOT _recon_rest MATCHES "^([^\"]*)\"sources\"[ \t]*:[ \t]*\\[([^]]*)\\]")
      math(EXPR _recon_at "${_recon_at} + 1")
      continue()
    endif()
    set(_recon_block "${CMAKE_MATCH_2}")
    string(LENGTH "${CMAKE_MATCH_0}" _recon_consumed)
    math(EXPR _recon_at "${_recon_at} + ${_recon_consumed}")
    string(REGEX MATCHALL "\"[^\"]+\"" _recon_items "${_recon_block}")
    foreach(_recon_item IN LISTS _recon_items)
      string(REGEX REPLACE "^\"|\"$" "" _recon_src "${_recon_item}")
      if(_recon_src MATCHES "^\\.\\." OR IS_ABSOLUTE "${_recon_src}")
        set(_recon_reject "refusing non-local source '${_recon_src}'")
      elseif(NOT EXISTS "${_recon_abs_dir}/${_recon_src}")
        set(_recon_reject "${_recon_dir}/${_recon_src} listed in promotion.json does not exist")
      else()
        list(APPEND _recon_sources "${_recon_abs_dir}/${_recon_src}")
      endif()
    endforeach()
  endwhile()
  if(_recon_reject)
    message(WARNING "reconstruction: ${_recon_reject} in ${_recon_dir}/promotion.json; "
                    "skipping package.")
    continue()
  endif()
  if(NOT _recon_sources)
    message(WARNING "reconstruction: ${_recon_dir} (${_recon_pkg}) has no usable "
                    "sources; no target created.")
    continue()
  endif()
  list(REMOVE_DUPLICATES _recon_sources)
  list(SORT _recon_sources)
  list(APPEND _recon_packages "${_recon_pkg}")

  add_library(${_recon_pkg} STATIC ${_recon_sources})
  target_include_directories(${_recon_pkg} PUBLIC "${_recon_abs_dir}")
  target_compile_features(${_recon_pkg} PUBLIC cxx_std_17)
  target_compile_options(${_recon_pkg} PRIVATE ${_recon_target_flags})
  target_link_options(${_recon_pkg} PRIVATE ${_recon_target_flags})

  file(GLOB _recon_test_tus RELATIVE "${_recon_abs_dir}"
       "${_recon_abs_dir}/*_test.cpp")
  list(SORT _recon_test_tus)
  if(NOT _recon_test_tus)
    message(WARNING "reconstruction: ${_recon_dir} (${_recon_pkg}) has no *_test.cpp; "
                    "library built with zero tests. The promotion gate should have "
                    "prevented this.")
  endif()
  foreach(_recon_tu IN LISTS _recon_test_tus)
    get_filename_component(_recon_stem "${_recon_tu}" NAME_WE)
    add_executable(${_recon_pkg}_${_recon_stem} "${_recon_abs_dir}/${_recon_tu}")
    target_link_libraries(${_recon_pkg}_${_recon_stem} PRIVATE ${_recon_pkg})
    target_compile_features(${_recon_pkg}_${_recon_stem} PRIVATE cxx_std_17)
    target_compile_options(${_recon_pkg}_${_recon_stem} PRIVATE ${_recon_target_flags})
    target_link_options(${_recon_pkg}_${_recon_stem} PRIVATE ${_recon_target_flags})
    add_test(NAME recon_${_recon_pkg}_${_recon_stem}
             COMMAND ${_recon_pkg}_${_recon_stem})
  endforeach()

  list(LENGTH _recon_sources _recon_nsrc)
  list(LENGTH _recon_test_tus _recon_ntest)
  message(STATUS "reconstruction: promoted ${_recon_dir} -> ${_recon_pkg} "
                 "(${_recon_nsrc} source(s), ${_recon_ntest} test TU(s), "
                 "m32=${OPENSPORE_RECONSTRUCTION_M32})")
endforeach()

list(LENGTH _recon_packages _recon_count)
message(STATUS "reconstruction: ${_recon_count} promoted package(s) discovered "
               "under src/reconstruction via */promotion.json")
