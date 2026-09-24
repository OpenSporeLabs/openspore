# CMake generated Testfile for 
# Source directory: /home/juanr/Proyectos/OpenSpore
# Build directory: /home/juanr/Proyectos/OpenSpore/build-pkg03
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(manifest_test "/usr/bin/python3" "/home/juanr/Proyectos/OpenSpore/tools/spore/manifest/manifest.py" "verify" "/home/juanr/Proyectos/OpenSpore/tests/fixtures/mini_package.dbpf" "--out" "/home/juanr/Proyectos/OpenSpore/build-pkg03/manifest_test.db")
set_tests_properties(manifest_test PROPERTIES  _BACKTRACE_TRIPLES "/home/juanr/Proyectos/OpenSpore/CMakeLists.txt;32;add_test;/home/juanr/Proyectos/OpenSpore/CMakeLists.txt;0;")
subdirs("src")
