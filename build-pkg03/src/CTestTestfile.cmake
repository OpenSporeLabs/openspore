# CMake generated Testfile for 
# Source directory: /home/juanr/Proyectos/OpenSpore/src
# Build directory: /home/juanr/Proyectos/OpenSpore/build-pkg03/src
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(triangle_smoke "sh" "/home/juanr/Proyectos/OpenSpore/tools/observatory/machine_lock.sh" "triangle")
set_tests_properties(triangle_smoke PROPERTIES  WORKING_DIRECTORY "/home/juanr/Proyectos/OpenSpore/build-pkg03/src" _BACKTRACE_TRIPLES "/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;63;add_test;/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;0;")
add_test(asset_render "sh" "/home/juanr/Proyectos/OpenSpore/tools/observatory/machine_lock.sh" "asset_view" "/home/juanr/Proyectos/OpenSpore/SPORE/Data/Spore_Content.package")
set_tests_properties(asset_render PROPERTIES  WORKING_DIRECTORY "/home/juanr/Proyectos/OpenSpore/build-pkg03/src" _BACKTRACE_TRIPLES "/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;73;add_test;/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;0;")
add_test(material_smoke "sh" "/home/juanr/Proyectos/OpenSpore/tools/observatory/machine_lock.sh" "material_smoke" "/home/juanr/Proyectos/OpenSpore/SPORE/Data/Spore_Content.package")
set_tests_properties(material_smoke PROPERTIES  WORKING_DIRECTORY "/home/juanr/Proyectos/OpenSpore/build-pkg03/src" _BACKTRACE_TRIPLES "/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;83;add_test;/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;0;")
add_test(cell_stage "/home/juanr/Proyectos/OpenSpore/build-pkg03/src/cell_stage" "/home/juanr/Proyectos/OpenSpore/SPORE/Data/Spore_Content.package" "--bgmap" "/home/juanr/Proyectos/OpenSpore/SPORE/Data/Spore_Game.package")
set_tests_properties(cell_stage PROPERTIES  WORKING_DIRECTORY "/home/juanr/Proyectos/OpenSpore/build-pkg03/src" _BACKTRACE_TRIPLES "/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;111;add_test;/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;0;")
add_test(scene_config "/home/juanr/Proyectos/OpenSpore/build-pkg03/src/scene_config_test" "/home/juanr/Proyectos/OpenSpore/src/apps/scene.json")
set_tests_properties(scene_config PROPERTIES  WORKING_DIRECTORY "/home/juanr/Proyectos/OpenSpore/build-pkg03/src" _BACKTRACE_TRIPLES "/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;120;add_test;/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;0;")
add_test(cellgfx "/home/juanr/Proyectos/OpenSpore/build-pkg03/src/cellgfx_test")
set_tests_properties(cellgfx PROPERTIES  WORKING_DIRECTORY "/home/juanr/Proyectos/OpenSpore/build-pkg03/src" _BACKTRACE_TRIPLES "/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;127;add_test;/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;0;")
add_test(cellui "/home/juanr/Proyectos/OpenSpore/build-pkg03/src/cellui_test")
set_tests_properties(cellui PROPERTIES  WORKING_DIRECTORY "/home/juanr/Proyectos/OpenSpore/build-pkg03/src" _BACKTRACE_TRIPLES "/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;134;add_test;/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;0;")
add_test(cellmode "/home/juanr/Proyectos/OpenSpore/build-pkg03/src/cellmode_test")
set_tests_properties(cellmode PROPERTIES  WORKING_DIRECTORY "/home/juanr/Proyectos/OpenSpore/build-pkg03/src" _BACKTRACE_TRIPLES "/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;143;add_test;/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;0;")
add_test(cellinput "/home/juanr/Proyectos/OpenSpore/build-pkg03/src/cellinput_test")
set_tests_properties(cellinput PROPERTIES  WORKING_DIRECTORY "/home/juanr/Proyectos/OpenSpore/build-pkg03/src" _BACKTRACE_TRIPLES "/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;151;add_test;/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;0;")
add_test(cellanim "/home/juanr/Proyectos/OpenSpore/build-pkg03/src/cellanim_test")
set_tests_properties(cellanim PROPERTIES  WORKING_DIRECTORY "/home/juanr/Proyectos/OpenSpore/build-pkg03/src" _BACKTRACE_TRIPLES "/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;161;add_test;/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;0;")
add_test(cell_stage_interactive_smoke "bash" "-c" "env -u XDG_SESSION_TYPE DISPLAY=:99 WAYLAND_DISPLAY=invalid-socket-xyz sh /home/juanr/Proyectos/OpenSpore/tools/observatory/machine_lock.sh ./cell_stage /home/juanr/Proyectos/OpenSpore/SPORE/Data/Spore_Content.package --interactive 2>&1 | grep -q 'cell_stage: interactive:'")
set_tests_properties(cell_stage_interactive_smoke PROPERTIES  ENVIRONMENT "DISPLAY=:99" TIMEOUT "20" WORKING_DIRECTORY "/home/juanr/Proyectos/OpenSpore/build-pkg03/src" _BACKTRACE_TRIPLES "/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;172;add_test;/home/juanr/Proyectos/OpenSpore/src/CMakeLists.txt;0;")
subdirs("assets")
subdirs("sim")
subdirs("replace")
