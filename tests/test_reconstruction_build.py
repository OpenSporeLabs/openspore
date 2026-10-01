"""Build-gate tests for the promoted reconstruction packages.

Module under test: ``tools/reconstruction_tooling/build_gate.py``, driving the
real ``src/reconstruction/CMakeLists.txt``. Every case builds a throwaway source
tree under the system temp directory and copies the repository's
``src/reconstruction/CMakeLists.txt`` into it verbatim, so the tests exercise the
shipped discovery logic without writing a single byte into the repository and
without depending on the 86 hand-promoted packages that carry no
``promotion.json`` yet.

Run from the repo root::

    python3 -m pytest tests/test_reconstruction_build.py -q
    python3 -m unittest tests.test_reconstruction_build -v

The cases are chosen around the failure modes that would make this gate lie:
a ``-m32`` that was silently dropped, a ctest run that matched no tests and
exited 0 anyway, a compile error that never reached the verdict, a test binary
that aborts, a package directory that the glob should not have picked up, and
a ``src_package`` string that would otherwise be pasted into ``add_library``.
"""
import json
import os
import re
import shutil
import sys
import tempfile
import unittest
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]
if str(REPO) not in sys.path:
    sys.path.insert(0, str(REPO))

from tools.reconstruction_tooling import build_gate

RECONSTRUCTION_CMAKE = REPO / "src" / "reconstruction" / "CMakeLists.txt"
PACKAGE = "pkg_unit_006a2ef0"
TEST_STEM = "unit_006a2ef0_model_test"
TEST_NAME = "recon_%s_%s" % (PACKAGE, TEST_STEM)

SYNTHETIC_ROOT_CMAKE = """cmake_minimum_required(VERSION 3.16)
project(openspore_synthetic CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Werror)

enable_testing()
add_subdirectory(src)
"""

SYNTHETIC_SRC_CMAKE = """option(OPENSPORE_RECONSTRUCTION "Build promoted reconstruction packages" ON)
if(OPENSPORE_RECONSTRUCTION)
  add_subdirectory(reconstruction)
endif()
"""

UNIT_HEADER = """#pragma once

#include <cstdint>

namespace openspore::reconstruction::%(package)s {

using TargetWord = std::uint32_t;

struct CounterRecord {
  TargetWord value = 0;
};

void __thiscall counter_reset_006a2ef0(CounterRecord* record, TargetWord value);
TargetWord __thiscall counter_read_006a2ef0(CounterRecord* record);

}  // namespace openspore::reconstruction::%(package)s
"""

UNIT_SOURCE = """#include "unit_006a2ef0.hpp"

namespace openspore::reconstruction::%(package)s {

void __thiscall counter_reset_006a2ef0(CounterRecord* record, TargetWord value) {
  record->value = value;
}

TargetWord __thiscall counter_read_006a2ef0(CounterRecord* record) {
  return record->value;
}

}  // namespace openspore::reconstruction::%(package)s
"""

UNIT_TEST = """#include "unit_006a2ef0.hpp"

namespace openspore::reconstruction::%(package)s {
}

int main() {
  openspore::reconstruction::%(package)s::CounterRecord record;
  openspore::reconstruction::%(package)s::counter_reset_006a2ef0(&record, 7u);
  if (openspore::reconstruction::%(package)s::counter_read_006a2ef0(&record) != 7u) {
    return 1;
  }
  return 0;
}
"""

ABORTING_TEST = """#include "unit_006a2ef0.hpp"

#include <cstdlib>

int main() {
  std::abort();
}
"""

UNCOMPILABLE_TEST = """#include "unit_006a2ef0.hpp"

int main() { return this_symbol_does_not_exist_anywhere(); }
"""

TIMESTAMP_KEY_RE = re.compile(
    r"(?i)^(.*(time|timestamp|date|clock|elapsed|duration|started|finished|epoch|msec|usec).*)$")


def write_promotion(path, src_package=PACKAGE, directory_name=None, sources=None,
                    tests=None, symbol="counter_read_006a2ef0", schema="openspore-promotion-1"):
    """Write the frozen promotion.json contract verbatim."""
    path = Path(path)
    path.mkdir(parents=True, exist_ok=True)
    document = {
        "namespace": "openspore::reconstruction::%s" % src_package,
        "package": src_package.replace("_", "-"),
        "schema": schema,
        "src_package": src_package,
        "targets": [
            {
                "bare_va": "006a2ef0",
                "headers": ["unit_006a2ef0.hpp"],
                "sources": list(sources if sources is not None else ["unit_006a2ef0.cpp"]),
                "symbol": symbol,
                "tests": list(tests if tests is not None else ["unit_006a2ef0_model_test.cpp"]),
                "va": "0x006a2ef0",
            }
        ],
    }
    payload = json.dumps(document, indent=2, sort_keys=True) + "\n"
    (path / "promotion.json").write_text(payload, encoding="utf-8")
    return directory_name or path.name


def write_unit_files(directory, test_source=UNIT_TEST, stem=TEST_STEM):
    directory = Path(directory)
    directory.mkdir(parents=True, exist_ok=True)
    mapping = {
        "unit_006a2ef0.hpp": UNIT_HEADER % {"package": PACKAGE},
        "unit_006a2ef0.cpp": UNIT_SOURCE % {"package": PACKAGE},
        "%s.cpp" % stem: test_source % {"package": PACKAGE},
    }
    for name, text in mapping.items():
        (directory / name).write_text(text, encoding="utf-8")
    return sorted(mapping)


def make_tree(base, packages=(), unpromoted=()):
    """A complete synthetic source tree: root CMake, src/, src/reconstruction/.

    ``packages`` is a sequence of dicts with keys ``src_package``, ``stem`` and
    ``test_source``; ``unpromoted`` gets real sources but no promotion.json,
    which is the shape of the 86 hand-promoted directories in the repository.
    """
    base = Path(base)
    recon = base / "src" / "reconstruction"
    recon.mkdir(parents=True, exist_ok=True)
    (base / "CMakeLists.txt").write_text(SYNTHETIC_ROOT_CMAKE, encoding="utf-8")
    (base / "src" / "CMakeLists.txt").write_text(SYNTHETIC_SRC_CMAKE, encoding="utf-8")
    shutil.copyfile(str(RECONSTRUCTION_CMAKE), str(recon / "CMakeLists.txt"))

    for spec in packages:
        directory = recon / spec.get("directory", spec["src_package"])
        write_unit_files(directory, spec.get("test_source", UNIT_TEST), spec.get("stem", TEST_STEM))
        write_promotion(directory, src_package=spec["src_package"],
                        sources=spec.get("sources"),
                        tests=spec.get("tests"),
                        symbol=spec.get("symbol", "counter_read_006a2ef0"))
    for spec in unpromoted:
        directory = recon / spec.get("directory", spec["src_package"])
        write_unit_files(directory, spec.get("test_source", UNIT_TEST), spec.get("stem", TEST_STEM))
    return base


def find_archive(build_dir, name):
    for base, _directories, files in os.walk(str(build_dir)):
        if name in files:
            return True
    return False


def step_by_name(result, name):
    for step in result["steps"]:
        if step["name"] == name:
            return step
    raise AssertionError("no step named %r in %s"
                         % (name, [item["name"] for item in result["steps"]]))


def walk_strings(value, path="$"):
    if isinstance(value, dict):
        for key, item in value.items():
            yield path + "." + str(key), str(key)
            for pair in walk_strings(item, path + "." + str(key)):
                yield pair
    elif isinstance(value, list):
        for index, item in enumerate(value):
            for pair in walk_strings(item, "%s[%d]" % (path, index)):
                yield pair
    elif isinstance(value, str):
        yield path, value


class SyntheticTreeTest(unittest.TestCase):
    """Base class: a throwaway source tree and build directory per test."""

    def setUp(self):
        self.scratch = Path(tempfile.mkdtemp(prefix="openspore-recon-test-"))
        self.addCleanup(shutil.rmtree, str(self.scratch), ignore_errors=True)
        self.source = self.scratch / "source"
        self.build = self.scratch / "build"

    def gate(self, **kwargs):
        kwargs.setdefault("build_dir", str(self.build))
        kwargs.setdefault("jobs", 1)
        return build_gate.gate(str(self.source), **kwargs)


class M32ProbeTest(SyntheticTreeTest):
    """The -m32 assertion the whole gate rests on."""

    def test_probe_observes_the_32bit_asymmetry(self):
        step = build_gate.m32_probe(cxx=build_gate.DEFAULT_CXX, m32=True)
        self.assertEqual(step["name"], "m32_probe")
        self.assertTrue(step["ok"], step["stdout_tail"])
        self.assertEqual(step["m32_returncode"], 0)
        self.assertNotEqual(step["no_m32_returncode"], 0)

    def test_probe_is_a_step_of_every_gate_run(self):
        source = make_tree(self.source, packages=({"src_package": PACKAGE},))
        result = build_gate.gate(str(source), build_dir=str(self.build), jobs=1)
        self.assertEqual(result["steps"][0]["name"], "m32_probe")
        self.assertTrue(step_by_name(result, "m32_probe")["ok"])


class GreenGateTest(SyntheticTreeTest):
    def test_promoted_package_is_green(self):
        source = make_tree(self.source, packages=({"src_package": PACKAGE},))
        result = build_gate.gate(str(source), build_dir=str(self.build), jobs=1)

        self.assertTrue(result["ok"], _diagnose(result))
        self.assertEqual(result["schema"], "openspore-build-gate-1")
        self.assertEqual(result["cxx"], build_gate.DEFAULT_CXX)
        self.assertTrue(result["m32"])
        self.assertEqual([step["name"] for step in result["steps"]],
                         ["m32_probe", "configure", "build", "ctest"])
        self.assertIn({"name": TEST_NAME, "ok": True, "returncode": 0}, result["tests"])
        self.assertTrue(result["packages"][PACKAGE]["ok"])
        self.assertEqual(result["packages"][PACKAGE]["status"], "ok")
        self.assertTrue(find_archive(self.build, "lib%s.a" % PACKAGE))

    def test_configure_only_stops_after_configure(self):
        source = make_tree(self.source, packages=({"src_package": PACKAGE},))
        result = build_gate.gate(str(source), build_dir=str(self.build), jobs=1,
                                 configure_only=True)
        self.assertTrue(result["ok"], _diagnose(result))
        self.assertEqual([step["name"] for step in result["steps"]],
                         ["m32_probe", "configure"])
        self.assertEqual(result["tests"], [])
        self.assertEqual(result["packages"][PACKAGE]["status"], "discovered")

    def test_scratch_build_dir_is_removed(self):
        source = make_tree(self.source, packages=({"src_package": PACKAGE},))
        result = build_gate.gate(str(source))
        self.assertTrue(result["ok"], _diagnose(result))
        self.assertFalse(os.path.exists(result["build_dir"]))
        self.assertFalse(os.path.exists(str(self.build)))


class VacuousPassTest(SyntheticTreeTest):
    """ctest exits 0 when nothing matches; that must not read as green."""

    def test_ctest_with_zero_tests_is_a_failure(self):
        source = make_tree(self.source)
        configure_step = build_gate.configure(str(source), build_dir=str(self.build),
                                              cxx=build_gate.DEFAULT_CXX, m32=True)
        self.assertTrue(configure_step["ok"], configure_step["stderr_tail"])
        step = build_gate.ctest(str(source), str(self.build))
        self.assertFalse(step["ok"])
        self.assertTrue(step["no_tests_found"])
        self.assertEqual(step["returncode"], 0)
        self.assertEqual(step["tests"], [])

    def test_gate_over_an_undiscovered_tree_is_not_green(self):
        source = make_tree(self.source)
        result = build_gate.gate(str(source), build_dir=str(self.build), jobs=1)
        self.assertFalse(result["ok"])
        self.assertEqual(result["packages"], {})
        self.assertEqual(result["tests"], [])


class CompileFailureTest(SyntheticTreeTest):
    def test_uncompilable_test_source_fails_the_gate(self):
        source = make_tree(self.source,
                           packages=({"src_package": PACKAGE, "test_source": UNCOMPILABLE_TEST},))
        result = build_gate.gate(str(source), build_dir=str(self.build), jobs=1)

        self.assertFalse(result["ok"])
        build_step = step_by_name(result, "build")
        self.assertFalse(build_step["ok"])
        self.assertNotEqual(build_step["returncode"], 0)
        # The failing unit is named, so a worker can be pointed at it.
        self.assertIn("unit_006a2ef0_model_test.cpp",
                      build_step["stdout_tail"] + build_step["stderr_tail"])
        self.assertIn("this_symbol_does_not_exist_anywhere",
                      build_step["stdout_tail"] + build_step["stderr_tail"])
        self.assertFalse(result["packages"][PACKAGE]["ok"])
        # The library itself compiles; the test binary does not exist, so ctest
        # reports the registered test as never run rather than as a pass.
        self.assertEqual(result["packages"][PACKAGE]["status"], "test_failed")
        self.assertEqual(result["packages"][PACKAGE]["tests"][0]["status"], "Not Run")
        self.assertIn({"name": TEST_NAME, "ok": False, "returncode": 1}, result["tests"])

    def test_compile_units_names_the_failing_unit(self):
        source = make_tree(self.source,
                           packages=({"src_package": PACKAGE, "test_source": UNCOMPILABLE_TEST},))
        result = build_gate.compile_units(str(source), PACKAGE, ["unit_006a2ef0_model_test.cpp"],
                                          cxx=build_gate.DEFAULT_CXX, m32=True)
        self.assertFalse(result["ok"])
        self.assertEqual(len(result["units"]), 1)
        row = result["units"][0]
        self.assertFalse(row["ok"])
        self.assertNotEqual(row["returncode"], 0)
        self.assertIn("-I", row["command"])
        self.assertTrue(any("unit_006a2ef0_model_test.cpp" in part for part in row["command"]))
        self.assertIn("this_symbol_does_not_exist_anywhere",
                      row["stdout_tail"] + row["stderr_tail"])

    def test_compile_units_accepts_a_good_unit(self):
        source = make_tree(self.source, packages=({"src_package": PACKAGE},))
        result = build_gate.compile_units(str(source), PACKAGE,
                                          ["unit_006a2ef0.cpp", TEST_STEM + ".cpp"],
                                          cxx=build_gate.DEFAULT_CXX, m32=True)
        self.assertTrue(result["ok"], json.dumps([row["stderr_tail"] for row in result["units"]]))
        self.assertEqual(len(result["units"]), 2)


class TestRuntimeFailureTest(SyntheticTreeTest):
    """A test that compiles but aborts is a red gate, not a green one."""

    def test_aborting_test_binary_fails_the_gate(self):
        source = make_tree(self.source,
                           packages=({"src_package": PACKAGE, "test_source": ABORTING_TEST},))
        result = build_gate.gate(str(source), build_dir=str(self.build), jobs=1)

        self.assertTrue(step_by_name(result, "build")["ok"])
        self.assertFalse(step_by_name(result, "ctest")["ok"])
        self.assertFalse(result["ok"])
        rows = dict((row["name"], row) for row in result["tests"])
        self.assertIn(TEST_NAME, rows)
        self.assertFalse(rows[TEST_NAME]["ok"])
        self.assertNotEqual(rows[TEST_NAME]["returncode"], 0)
        self.assertEqual(result["packages"][PACKAGE]["status"], "test_failed")
        self.assertFalse(result["packages"][PACKAGE]["ok"])
        # --output-on-failure: the abort has to be visible in the captured output.
        ctest_step = step_by_name(result, "ctest")
        self.assertIn("--output-on-failure", ctest_step["command"])
        self.assertIn("Subprocess aborted", ctest_step["stdout_tail"] + ctest_step["stderr_tail"])
        self.assertEqual(result["packages"][PACKAGE]["tests"][0]["status"], "Exception")


class DiscoveryTest(SyntheticTreeTest):
    UNPROMOTED = "pkg15_editor_support"

    def test_package_without_promotion_json_is_not_discovered(self):
        source = make_tree(self.source,
                           packages=({"src_package": PACKAGE},),
                           unpromoted=({"src_package": self.UNPROMOTED, "stem": "ignored"},))
        result = build_gate.gate(str(source), build_dir=str(self.build), jobs=1)

        self.assertTrue(result["ok"], _diagnose(result))
        self.assertNotIn(self.UNPROMOTED, result["packages"])
        self.assertEqual(sorted(result["packages"]), [PACKAGE])
        # Absent from the generated build system, not merely unreported.
        self.assertFalse(find_archive(self.build, "lib%s.a" % self.UNPROMOTED))
        self.assertFalse(find_archive(self.build, "%s_model_test" % self.UNPROMOTED))
        configure_output = step_by_name(result, "configure")["stdout_tail"]
        self.assertNotIn(self.UNPROMOTED, configure_output)
        self.assertIn("1 promoted package(s) discovered", configure_output)

    def test_hand_written_package_cmakelists_are_never_invoked(self):
        source = make_tree(self.source, unpromoted=({"src_package": self.UNPROMOTED, "stem": "ignored"},))
        # A hand-written CMakeLists.txt in the package directory must not make
        # the directory a target: only promotion.json does that.
        (source / "src" / "reconstruction" / self.UNPROMOTED / "CMakeLists.txt").write_text(
            "cmake_minimum_required(VERSION 3.16)\nproject(hand_written LANGUAGES CXX)\n",
            encoding="utf-8")
        result = build_gate.gate(str(source), build_dir=str(self.build), jobs=1,
                                 configure_only=True)
        self.assertTrue(result["ok"], _diagnose(result))
        self.assertEqual(result["packages"], {})

    def test_repository_discovery_follows_promotion_json_only(self):
        # The shipped tree is mostly hand-promoted directories that carry no
        # promotion.json, so discovery must ignore them and report only the
        # directories that were promoted through the gate. A directory counts
        # because of its manifest and nothing else, which is the property the
        # synthetic cases above pin down; this case states it about the real
        # repository rather than about a scratch tree.
        found = build_gate.discover_packages(str(REPO))
        directories = [entry for entry in (REPO / "src" / "reconstruction").glob("*/")
                       if entry.is_dir() and not entry.name.startswith(".")]
        self.assertGreater(len(directories), len(found),
                           "most shipped directories are still unpromoted")
        for package in found:
            self.assertTrue((REPO / package["path"] / "promotion.json").is_file())
        # Every discovered package must actually be a real directory here, not a
        # leftover from a scratch or recovery tree.
        for package in found:
            self.assertIn(package["dir"], {entry.name for entry in directories})


class NameValidationTest(SyntheticTreeTest):
    """A src_package string becomes a target name; it is validated first."""

    HOSTILE = "pkg bad; touch /tmp/openspore-pwned"

    def test_hostile_src_package_is_rejected_with_a_warning(self):
        # The directory name is benign on purpose: what is under test is the
        # src_package string inside promotion.json, which is what flows into
        # add_library/add_test.
        source = make_tree(self.source,
                           packages=({"directory": "hostile_probe",
                                      "src_package": self.HOSTILE},))
        result = build_gate.gate(str(source), build_dir=str(self.build), jobs=1,
                                 configure_only=True)
        self.assertTrue(result["ok"], _diagnose(result))
        self.assertEqual(result["packages"], {})
        configure_step = step_by_name(result, "configure")
        self.assertEqual(configure_step["returncode"], 0)
        output = configure_step["stdout_tail"] + configure_step["stderr_tail"]
        self.assertIn("rejecting src_package", output)
        self.assertIn("must match ^[A-Za-z0-9_]+$", output)
        self.assertIn("0 promoted package(s) discovered", output)
        self.assertFalse(os.path.exists("/tmp/openspore-pwned"))
        self.assertEqual(find_archive(self.build, "lib%s.a" % self.HOSTILE), False)

    def test_hostile_name_does_not_break_a_sibling_package(self):
        source = make_tree(self.source,
                           packages=({"src_package": PACKAGE},
                                     {"directory": "evil", "src_package": "pkg;bad"}))
        result = build_gate.gate(str(source), build_dir=str(self.build), jobs=1)
        self.assertTrue(result["ok"], _diagnose(result))
        self.assertEqual(sorted(result["packages"]), [PACKAGE])
        configure_step = step_by_name(result, "configure")
        self.assertIn("rejecting src_package",
                      configure_step["stdout_tail"] + configure_step["stderr_tail"])
        self.assertTrue(result["packages"][PACKAGE]["ok"])

    def test_python_side_agrees_with_the_cmake_name_rule(self):
        source = self.scratch / "h"
        recon = source / "src" / "reconstruction"
        for name in ("pkg_good", "pkg;bad", "pkg bad", "../escape", "1starts_with_digit_is_fine"):
            directory = recon / name
            directory.mkdir(parents=True, exist_ok=True)
            write_promotion(directory, src_package=name)
        found = sorted(item["src_package"] for item in build_gate.discover_packages(str(source)))
        self.assertEqual(found, ["1starts_with_digit_is_fine", "pkg_good"])


class DeterminismTest(SyntheticTreeTest):
    def keys_and_values(self, value):
        return sorted(walk_strings(value))

    def test_no_timestamp_like_field_anywhere(self):
        source = make_tree(self.source, packages=({"src_package": PACKAGE},))
        result = build_gate.gate(str(source), build_dir=str(self.build), jobs=1)
        offenders = [path for path, text in self.keys_and_values(result)
                     if TIMESTAMP_KEY_RE.match(text)]
        self.assertEqual(offenders, [])
        self.assertNotIn("duration", json.dumps(result))

    def test_two_runs_on_the_same_input_are_equal(self):
        source = make_tree(self.source, packages=({"src_package": PACKAGE},))
        first = build_gate.gate(str(source), build_dir=str(self.build), jobs=1)
        shutil.rmtree(str(self.build), ignore_errors=True)
        second = build_gate.gate(str(source), build_dir=str(self.build), jobs=1)
        self.assertTrue(first["ok"], _diagnose(first))
        self.assertTrue(second["ok"], _diagnose(second))
        self.assertEqual(first, second)

    def test_repo_tree_is_untouched(self):
        before = _tree_digest(REPO / "src" / "reconstruction")
        source = make_tree(self.source, packages=({"src_package": PACKAGE},))
        result = build_gate.gate(str(source))
        self.assertTrue(result["ok"], _diagnose(result))
        self.assertEqual(_tree_digest(REPO / "src" / "reconstruction"), before)


def _tree_digest(root):
    entries = []
    for base, directories, files in os.walk(str(root)):
        directories.sort()
        for name in sorted(files):
            path = Path(base) / name
            entries.append((str(path.relative_to(root)), path.stat().st_size))
    return entries


def _diagnose(result):
    lines = ["gate ok=%s" % result["ok"]]
    for step in result["steps"]:
        lines.append("step %s ok=%s rc=%s" % (step["name"], step["ok"], step["returncode"]))
        lines.append(step["stdout_tail"])
        lines.append(step["stderr_tail"])
    return "\n".join(lines)


if __name__ == "__main__":
    unittest.main()
