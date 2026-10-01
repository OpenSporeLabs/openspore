"""Hardening regressions for the promotion pipeline.

Modules under test: ``tools/reconstruction_tooling/promote.py`` and
``tools/reconstruction_tooling/build_gate.py``. Every case builds a synthetic
repository under its own ``mkdtemp`` and points ``promote`` at it by ``root=``;
the real repository is only read, never written. The build gate is a stub
module for the cases that are about the pipeline's own logic, and the shipped
gate for the handful that are about what the build actually does -- a stub
cannot prove that a non-compiling translation unit is refused, and that is
precisely what has to be proved.

Each class is named after the property it pins, and every property has an
assertion that would fail if the property were dropped. Nothing here asserts
the absence of a defect: where the pipeline has a hole, the test pins the
current honest behaviour and says so in its name.

Run from the repo root::

    python3 -m pytest tests/test_promotion_hardening.py -q
"""
import hashlib
import importlib
import importlib.util
import json
import os
import re
import shutil
import stat
import sys
import tempfile
import threading
import types
import unittest
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]
if str(REPO) not in sys.path:
    sys.path.insert(0, str(REPO))

from tools.reconstruction_tooling import build_gate, promote

GATE_FULL = "tools.reconstruction_tooling.build_gate"
GATE_PATH = REPO / "tools" / "reconstruction_tooling" / "build_gate.py"
RECONSTRUCTION_CMAKE = REPO / "src" / "reconstruction" / "CMakeLists.txt"
VA = "0x006a2ef0"
BARE = "006a2ef0"
PACKAGE = "pkg-hardening-006a2ef0"
SRC_PACKAGE = "pkg_hardening_006a2ef0"
STEM = "hardening_006a2ef0"
ALT_PACKAGE = "pkg-hardening-alt-006a2ef1"
ALT_SRC_PACKAGE = "pkg_hardening_alt_006a2ef1"
ALT_STEM = "hardening_alt_006a2ef1"

# A claim about validation that nothing in this repository can support. No
# artifact this pipeline writes may contain it.
FORBIDDEN_TOKEN = "STATIC_VALIDATED"

HEADER = """#pragma once

namespace openspore::reconstruction::%(package)s {

struct Record {
  unsigned int value;
};

int Remove(void *self, unsigned int key);

}  // namespace openspore::reconstruction::%(package)s
"""

SOURCE = """#include "%(stem)s.hpp"

namespace openspore::reconstruction::%(package)s {

int Remove(void *self, unsigned int key) {
  (void)self;
  (void)key;
  return 0;
}

}  // namespace openspore::reconstruction::%(package)s
"""

TEST_SOURCE = """#include "%(stem)s.hpp"

#include <cstdlib>

namespace openspore::reconstruction::%(package)s {
}

int main() {
  using namespace openspore::reconstruction::%(package)s;
  if (Remove(nullptr, 1u) != 0) {
    std::abort();
  }
  return 0;
}
"""

ABORTING_TEST = """#include "%(stem)s.hpp"

#include <cstdlib>

int main() {
  std::abort();
}
"""

UNCOMPILABLE_SOURCE = """#include "%(stem)s.hpp"

namespace openspore::reconstruction::%(package)s {

int Remove(void *self, unsigned int key) {
  return this_symbol_does_not_exist_anywhere(self, key);
}

}  // namespace openspore::reconstruction::%(package)s
"""

# The repository's own appended block, verbatim, so the per-target -m32
# question is asked of the real discovery code and not of a copy of it.
SRC_CMAKE_APPENDIX = """# Promoted reconstruction packages (auto-discovered from */promotion.json).
# Each target is x86-32: reconstructed code uses __attribute__((thiscall)).
# Configure with -DCMAKE_CXX_COMPILER=clang++ for the promoted set.
option(OPENSPORE_RECONSTRUCTION "Build promoted reconstruction packages" ON)
if(OPENSPORE_RECONSTRUCTION)
  add_subdirectory(reconstruction)
endif()
"""

SYNTHETIC_ROOT_CMAKE = """cmake_minimum_required(VERSION 3.16)
project(openspore_hardening CXX)
enable_testing()
add_subdirectory(src)
"""

SIBLING_SOURCE = "int sibling64_value() { return 64; }\n"
SIBLING_TEST = "int sibling64_value();\nint main() { return sibling64_value() == 64 ? 0 : 1; }\n"

SIBLING_CMAKE = """add_library(sibling64 STATIC sibling64.cpp)
target_compile_features(sibling64 PUBLIC cxx_std_17)
add_executable(sibling64_test sibling64_test.cpp)
target_link_libraries(sibling64_test PRIVATE sibling64)
add_test(NAME sibling64 COMMAND sibling64_test)
"""


def _digest(path):
    # type: (object) -> str
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def _tree_digest(root):
    # type: (object) -> str
    """A digest of every path and every byte under ``root``.

    Directories are included by name so that an added or removed empty
    directory changes the digest, which is what makes "the scratch tree is
    gone" a checkable statement.
    """
    base = Path(root)
    entries = []
    for path in sorted(base.rglob("*")):
        name = path.relative_to(base).as_posix()
        if path.is_dir():
            entries.append(name + "/")
        elif path.is_file():
            entries.append("%s:%s" % (name, _digest(path)))
    return hashlib.sha256("\n".join(entries).encode("utf-8")).hexdigest()


def _structured(result):
    # type: (dict) -> dict
    """The part of a gate result the determinism claim covers.

    Everything that is a verdict, and nothing that identifies where the run
    happened.
    """
    return {
        "schema": result["schema"],
        "ok": result["ok"],
        "cxx": result["cxx"],
        "m32": result["m32"],
        "tests": result["tests"],
        "packages": result["packages"],
        "steps": [{"name": step["name"], "ok": step["ok"], "returncode": step["returncode"]}
                  for step in result["steps"]],
    }


PATH_IDENTITY_FIELDS = ("build_dir", "source_dir", "command")


def _without_path_identity(result):
    # type: (dict) -> dict
    """A gate result with the documented path-identity fields removed."""
    stripped = {key: value for key, value in result.items()
                if key not in PATH_IDENTITY_FIELDS}
    stripped["steps"] = [{key: value for key, value in step.items()
                          if key not in PATH_IDENTITY_FIELDS}
                         for step in result["steps"]]
    return stripped


def _elf_class(path):
    # type: (object) -> str
    """``ELF32``/``ELF64`` of an executable, or of an archive's first member."""
    data = Path(path).read_bytes()
    offset = data.find(b"!<arch>\n")
    if offset >= 0:
        data = data[offset + 8:]
    index = data.find(b"\x7fELF")
    if index < 0:
        return "no-ELF"
    return {1: "ELF32", 2: "ELF64"}.get(data[index + 4], "unknown")


def _cxx_flags(build_dir, target):
    # type: (object, str) -> str
    """``CXX_FLAGS`` the generated build system will use for one target."""
    for path in sorted(Path(build_dir).rglob("flags.make")):
        if not any(target in part for part in path.parts):
            continue
        match = re.search(r"^CXX_FLAGS\s*=\s*(.*)$", path.read_text(), re.M)
        if match:
            return match.group(1)
    raise AssertionError("no flags.make for %s under %s" % (target, build_dir))


def _step(result, name):
    # type: (dict, str) -> dict
    for step in result["steps"]:
        if step["name"] == name:
            return step
    raise AssertionError("no step %r in %s"
                         % (name, [item["name"] for item in result["steps"]]))


def _wrap_strings(value, path="$"):
    # type: (object, str) -> list
    """Every string (and every dict key) inside a nested structure."""
    found = []
    if isinstance(value, dict):
        for key, item in value.items():
            found.append((path + "." + str(key), str(key)))
            found.extend(_wrap_strings(item, path + "." + str(key)))
    elif isinstance(value, list):
        for index, item in enumerate(value):
            found.extend(_wrap_strings(item, "%s[%d]" % (path, index)))
    elif isinstance(value, str):
        found.append((path, value))
    return found


class GateStub(types.ModuleType):
    """A build gate whose verdict this test chooses, and which records calls."""

    def __init__(self, ok=True):
        # type: (bool) -> None
        types.ModuleType.__init__(self, GATE_FULL)
        self.ok = ok
        self.calls = []
        self.raises = None
        self.seen_roots = []

    def verdict(self):
        # type: () -> dict
        return {"schema": "openspoke-build-gate-1", "ok": self.ok,
                "steps": [{"name": "compile", "ok": self.ok, "returncode": 0 if self.ok else 1}],
                "tests": [], "packages": {}}

    def gate(self, root, packages=None, build_dir=None, jobs=None):
        self.calls.append({"root": str(root), "packages": list(packages or []),
                           "build_dir": build_dir, "jobs": jobs})
        self.seen_roots.append(str(root))
        if self.raises is not None:
            raise self.raises
        document = self.verdict()
        if not self.ok:
            document["tests"] = [{"name": "recon_%s_%s" % (packages[0], STEM + "_model_test"),
                                  "ok": False, "returncode": 1}]
            document["packages"] = {packages[0]: {"ok": False, "status": "test_failed",
                                                  "test_count": 1, "tests": []}}
        return json.loads(json.dumps(document))


class HardeningFixture(unittest.TestCase):
    """A synthetic repository with one staged package and its evidence."""

    def setUp(self):
        self.root = Path(tempfile.mkdtemp(prefix="hardening."))
        self.addCleanup(shutil.rmtree, str(self.root), True)
        for relative in ("reconstruction/staging", "reconstruction/metadata",
                         "reconstruction/evidence", "reconstruction/knowledge",
                         "src/reconstruction"):
            (self.root / relative).mkdir(parents=True, exist_ok=True)
        self.stub = self.install_module(GateStub())

    # -- module plumbing ---------------------------------------------------

    def install_module(self, module):
        # type: (object) -> object
        """Bind a module under the gate's dotted name *and* on its package.

        Both, and a cleanup that puts both back: the promotion seam reads the
        package attribute first, so a substitute that only one of the two knows
        about is a substitute nobody can see -- and one that a teardown leaves
        behind is a substitute that outlives its test.
        """
        self.addCleanup(self._restore_gate_binding, self._gate_binding())
        self._bind(module)
        return module

    def load_real_gate(self):
        # type: () -> object
        """Bind the shipped gate, loaded from its file rather than by name.

        Loading by path is deliberate. The promotion seam resolves the gate
        through the package attribute and then ``sys.modules``, and a test
        elsewhere in this suite leaves a substitute in one or both; importing by
        name would hand that substitute back and every real-gate case in this
        file would silently be testing the substitute instead.
        """
        previous = self._gate_binding()
        self.addCleanup(self._restore_gate_binding, previous)
        spec = importlib.util.spec_from_file_location(GATE_FULL, str(GATE_PATH))
        module = importlib.util.module_from_spec(spec)
        self._bind(module)
        spec.loader.exec_module(module)
        return module

    @staticmethod
    def _gate_binding():
        # type: () -> tuple
        package, name = GATE_FULL.rsplit(".", 1)
        holder = importlib.import_module(package)
        return (sys.modules.get(GATE_FULL), getattr(holder, name, None))

    def _bind(self, module):
        # type: (object) -> None
        package, name = GATE_FULL.rsplit(".", 1)
        sys.modules[GATE_FULL] = module
        setattr(importlib.import_module(package), name, module)

    def _restore_gate_binding(self, previous):
        # type: (tuple) -> None
        package, name = GATE_FULL.rsplit(".", 1)
        holder = importlib.import_module(package)
        if previous[0] is None:
            sys.modules.pop(GATE_FULL, None)
        else:
            sys.modules[GATE_FULL] = previous[0]
        if previous[1] is None:
            if hasattr(holder, name):
                delattr(holder, name)
        else:
            setattr(holder, name, previous[1])

    def copy_reconstruction_cmake(self):
        # type: () -> None
        if not RECONSTRUCTION_CMAKE.is_file():
            self.skipTest("the repository has no src/reconstruction/CMakeLists.txt")
        shutil.copyfile(str(RECONSTRUCTION_CMAKE),
                        str(self.root / "src/reconstruction/CMakeLists.txt"))

    # -- staging -----------------------------------------------------------

    def stage(self, package=PACKAGE, stem=STEM, va=BARE, src_package=None, static="PASS",
              runtime="GATED", source_text=None, test_text=None, report=True,
              metadata=True, evidence=True, source_sha="keep", namespace=True):
        # type: (...) -> dict
        """Write one staging package and every artifact a promotion reads."""
        src_package = src_package or package.replace("-", "_").lower()
        directory = self.root / "reconstruction/staging" / package
        directory.mkdir(parents=True, exist_ok=True)
        text = {"package": src_package if namespace else "legacy_wave", "stem": stem}
        self.write(directory / (stem + ".hpp"), HEADER % text)
        self.write(directory / (stem + ".cpp"),
                   (source_text or SOURCE) % text)
        self.write(directory / (stem + "_model_test.cpp"), (test_text or TEST_SOURCE) % text)
        if metadata:
            self.write(self.root / "reconstruction/metadata" / package / (va + ".json"),
                       json.dumps({"va": "0x" + va, "package": package,
                                   "normalized_symbol": "App::PropertyList::Remove"}))
        if evidence:
            self.write(self.root / "reconstruction/evidence" / va / "evidence.json",
                       json.dumps({"schema": "openspore-evidence-1", "target": "0x" + va,
                                   "binary": {"sha256": "b" * 64}}))
        if report:
            self.write_validation(va, package, stem, static=static, runtime=runtime,
                                  source_sha=source_sha)
        self.write_index(va)
        return {"package": package, "src_package": src_package, "stem": stem, "va": va}

    def write_validation(self, va, package, stem, static="PASS", runtime="GATED",
                         source_sha="keep", schema="openspore-structural-validation-1",
                         omit_sha=False, source_path=None):
        path = self.root / "reconstruction/evidence" / va / "validation.json"
        if source_path is None:
            source_path = "reconstruction/staging/%s/%s.cpp" % (package, stem)
        source = {"path": source_path, "role": "staging"}
        if not omit_sha:
            source["sha256"] = (_digest(self.root / source_path) if source_sha == "keep"
                                else source_sha)
        document = {
            "schema": schema,
            "target": "0x" + va,
            "status": static,
            "source": source,
            "static": {"dimension": "STATIC", "status": static, "checks": {}},
            "runtime": {"dimension": "RUNTIME", "status": runtime,
                        "gated": runtime == "GATED", "gates": [],
                        "reason": "no original-process trace exists in this repository",
                        "validated": 0},
        }
        self.write(path, json.dumps(document, indent=2, sort_keys=True) + "\n")
        return path

    def write_index(self, va):
        path = self.root / "reconstruction/knowledge/index.json"
        document = {"schema": "openspore-knowledge-index-1", "records": {}}
        if path.is_file():
            document = json.loads(path.read_text(encoding="utf-8"))
        document["records"]["0x" + va] = {
            "va": "0x" + va, "normalized_symbol": "App::PropertyList::Remove",
            "subsystem": "App.PropertyList",
            "abi": {"calling_convention": "__thiscall", "return_type": "int",
                    "stack_cleanup_bytes": 4, "architecture": "x86-32"},
        }
        self.write(path, json.dumps(document, indent=2, sort_keys=True) + "\n")

    def write(self, path, text):
        path = Path(path)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")

    # -- assertions --------------------------------------------------------

    def codes(self, document, package=None):
        return sorted(item["code"] for candidate in document["candidates"]
                      if package is None or candidate["package"] == package
                      for item in candidate["blockers"])

    def marker(self, package=SRC_PACKAGE):
        return json.loads((self.root / "src/reconstruction" / package / "promotion.json")
                          .read_text(encoding="utf-8"))

    def record(self, va=BARE):
        return json.loads((self.root / "reconstruction/evidence" / va / "promotion.json")
                          .read_text(encoding="utf-8"))

    def residue(self):
        """Whatever the promotion left under ``src/reconstruction``."""
        base = self.root / "src/reconstruction"
        return sorted(entry.name for entry in base.iterdir())

    def scratch_residue(self):
        """Dotted trees -- scratch, lock, recovery -- that discovery cannot see."""
        return sorted(entry.name for entry in (self.root / "src/reconstruction").iterdir()
                      if entry.name.startswith("."))

    def assert_tree_untouched(self, before):
        self.assertEqual(_tree_digest(self.root / "src"), before["src"],
                         "src/ changed on a failure path")
        self.assertEqual(_tree_digest(self.root / "reconstruction/evidence"), before["evidence"],
                         "reconstruction/evidence/ changed on a failure path")

    def snapshot(self):
        return {"src": _tree_digest(self.root / "src"),
                "evidence": _tree_digest(self.root / "reconstruction/evidence")}


# ---------------------------------------------------------------------------
# Defect 1 -- configure must not set a project-wide flag
# ---------------------------------------------------------------------------

class ConfigureFlagTest(unittest.TestCase):
    """``-DCMAKE_CXX_FLAGS`` is project-wide; the option is not."""

    def setUp(self):
        self.source = Path(tempfile.mkdtemp(prefix="hardening-configure."))
        self.addCleanup(shutil.rmtree, str(self.source), True)

    def configure(self, m32):
        return build_gate.configure(str(self.source), build_dir=str(self.source / "b"),
                                    cxx=build_gate.DEFAULT_CXX, m32=m32)

    def test_configure_never_sets_a_project_wide_cxx_flag(self):
        for m32 in (True, False):
            with self.subTest(m32=m32):
                step = self.configure(m32)
                offenders = [part for part in step["command"] if "CMAKE_CXX_FLAGS" in part]
                self.assertEqual(offenders, [])
                self.assertNotIn("-DCMAKE_CXX_FLAGS=-m32", step["command"])

    def test_m32_is_forwarded_as_the_reconstruction_option(self):
        self.assertIn("-DOPENSPORE_RECONSTRUCTION_M32=ON", self.configure(True)["command"])
        self.assertIn("-DOPENSPORE_RECONSTRUCTION_M32=OFF", self.configure(False)["command"])

    def test_the_m32_key_stays_a_plain_bool(self):
        for m32 in (True, False):
            step = self.configure(m32)
            self.assertIs(step["m32"], m32)
            self.assertIsInstance(step["m32"], bool)

    def test_the_option_is_always_passed_not_omitted(self):
        # Silence would leave an inherited cache in charge of the promoted set.
        for m32 in (True, False):
            option = [part for part in self.configure(m32)["command"]
                      if part.startswith("-D" + build_gate.M32_OPTION + "=")]
            self.assertEqual(len(option), 1, self.configure(m32)["command"])


@unittest.skipUnless(shutil.which("cmake") and shutil.which("clang++"),
                     "cmake and clang++ are required to observe the real flags")
class M32ScopeTest(unittest.TestCase):
    """The promoted set is 32-bit; the rest of the project is not.

    The repository's own ``src/reconstruction/CMakeLists.txt`` is copied in
    verbatim and the gate is pointed at a tree that also has a 64-bit sibling
    target, which is the shape that made a project-wide ``-m32`` destructive.
    """

    def setUp(self):
        if not RECONSTRUCTION_CMAKE.is_file():
            self.skipTest("the repository has no src/reconstruction/CMakeLists.txt")
        self.scratch = Path(tempfile.mkdtemp(prefix="hardening-m32scope."))
        self.addCleanup(shutil.rmtree, str(self.scratch), True)
        self.source = self.scratch / "source"
        self.reconstruction = self.source / "src" / "reconstruction"
        self.package = "pkg_scope_006a2ef0"
        self._build_tree()

    def _build_tree(self):
        (self.reconstruction / self.package).mkdir(parents=True)
        (self.source / "CMakeLists.txt").write_text(SYNTHETIC_ROOT_CMAKE, encoding="utf-8")
        (self.source / "src/CMakeLists.txt").write_text(SRC_CMAKE_APPENDIX + SIBLING_CMAKE,
                                                       encoding="utf-8")
        (self.source / "src/sibling64.cpp").write_text(SIBLING_SOURCE, encoding="utf-8")
        (self.source / "src/sibling64_test.cpp").write_text(SIBLING_TEST, encoding="utf-8")
        shutil.copyfile(str(RECONSTRUCTION_CMAKE), str(self.reconstruction / "CMakeLists.txt"))
        directory = self.reconstruction / self.package
        text = {"package": self.package, "stem": "u_006a2ef0"}
        (directory / "u_006a2ef0.hpp").write_text(HEADER % text, encoding="utf-8")
        (directory / "u_006a2ef0.cpp").write_text(SOURCE % text, encoding="utf-8")
        (directory / "u_006a2ef0_model_test.cpp").write_text(TEST_SOURCE % text, encoding="utf-8")
        (directory / "promotion.json").write_text(json.dumps({
            "schema": "openspore-promotion-1", "package": self.package.replace("_", "-"),
            "src_package": self.package,
            "namespace": "openspore::reconstruction::" + self.package,
            "targets": [{"va": VA, "bare_va": BARE, "symbol": "Remove",
                         "sources": ["u_006a2ef0.cpp"], "headers": ["u_006a2ef0.hpp"],
                         "tests": ["u_006a2ef0_model_test.cpp"]}]},
            indent=2, sort_keys=True) + "\n", encoding="utf-8")

    def test_promoted_targets_are_32bit_and_the_sibling_is_64bit(self):
        build = self.scratch / "build"
        result = build_gate.gate(str(self.source), build_dir=str(build), jobs=1)
        self.assertTrue(result["ok"], _diagnose(result))

        promoted_flags = _cxx_flags(build, self.package)
        sibling_flags = _cxx_flags(build, "sibling64")
        self.assertIn("-m32", promoted_flags.split())
        self.assertNotIn("-m32", sibling_flags.split())

        library = list(build.rglob("lib%s.a" % self.package))
        sibling = list(build.rglob("libsibling64.a"))
        self.assertEqual(len(library), 1)
        self.assertEqual(len(sibling), 1)
        self.assertEqual(_elf_class(library[0]), "ELF32")
        self.assertEqual(_elf_class(sibling[0]), "ELF64")

    def test_the_project_wide_flag_would_have_dragged_the_sibling_in(self):
        # The reason the flag was removed, stated as a test: with the old
        # project-wide -m32 the 64-bit sibling target is compiled 32-bit too.
        import subprocess
        build = self.scratch / "build-old"
        completed = subprocess.run(
            ["cmake", "-S", str(self.source), "-B", str(build),
             "-DCMAKE_CXX_COMPILER=%s" % build_gate.DEFAULT_CXX,
             "-D%s=ON" % build_gate.M32_OPTION, "-DCMAKE_CXX_FLAGS=-m32"],
            capture_output=True)
        self.assertEqual(completed.returncode, 0, completed.stderr.decode("utf-8", "replace"))
        self.assertIn("-m32", _cxx_flags(build, "sibling64").split())

    def test_the_real_repository_root_configures_without_the_flag(self):
        result = build_gate.gate(str(REPO), configure_only=True, jobs=1)
        configure = _step(result, "configure")
        self.assertTrue(result["ok"], _diagnose(result))
        self.assertEqual(configure["returncode"], 0)
        self.assertEqual([part for part in configure["command"]
                          if "CMAKE_CXX_FLAGS" in part], [])
        self.assertIn("-DOPENSPORE_RECONSTRUCTION_M32=ON", configure["command"])


def _diagnose(result):
    lines = ["gate ok=%s" % result["ok"]]
    for step in result["steps"]:
        lines.append("step %s ok=%s rc=%s" % (step["name"], step["ok"], step["returncode"]))
        lines.append(step["stdout_tail"])
        lines.append(step["stderr_tail"])
    return "\n".join(lines)


class PathScrubbingTest(unittest.TestCase):
    """The scrubber, without a build.

    ``root="."`` is a legal way to point the gate at the current directory, and
    it resolves to a one-character needle. A one-character needle matches every
    occurrence of itself, which turned the whole configure output into
    ``3<source-dir>0<source-dir>7``. Asserted here rather than through a gate
    run so it holds on a machine with no compiler.
    """

    def setUp(self):
        self.scratch = Path(tempfile.mkdtemp(prefix="hardening-scrub."))
        self.addCleanup(shutil.rmtree, str(self.scratch), True)

    def test_a_relative_or_single_character_root_is_never_used_as_a_needle(self):
        text = "version 3.0.7 and promotion.json in 0.2s"
        for spelling in (".", "./", "..", ""):
            with self.subTest(root=spelling):
                scrub = build_gate._scrubber(((str(self.scratch / "b"), "<build-dir>"),
                                              (spelling, "<source-dir>")))
                self.assertEqual(scrub(text), text)

    def test_an_absolute_root_is_replaced_in_both_spellings(self):
        scrub = build_gate._scrubber(((str(self.scratch), "<source-dir>"),))
        self.assertEqual(scrub("at %s/src" % self.scratch), "at <source-dir>/src")
        self.assertEqual(scrub("at %s/src" % self.scratch.resolve()), "at <source-dir>/src")

    def test_a_nested_path_is_replaced_before_its_parent(self):
        scrub = build_gate._scrubber(((str(self.scratch), "<source-dir>"),
                                      (str(self.scratch / "a" / "b"), "<build-dir>")))
        self.assertEqual(scrub("at %s/a/b" % self.scratch), "at <build-dir>")

    def test_bytes_and_empty_values_are_handled(self):
        scrub = build_gate._scrubber(((str(self.scratch), "<source-dir>"),))
        self.assertEqual(scrub(b"at " + str(self.scratch).encode("utf-8")), "at <source-dir>")
        self.assertEqual(scrub(""), "")
        self.assertEqual(scrub(None), "")


# ---------------------------------------------------------------------------
# Defect 2 -- a run that found no tests is a failure, not a pass
# ---------------------------------------------------------------------------

class VacuousGreenTest(HardeningFixture):
    def setUp(self):
        HardeningFixture.setUp(self)
        if not RECONSTRUCTION_CMAKE.is_file():
            self.skipTest("the repository has no src/reconstruction/CMakeLists.txt")
        self.load_real_gate()
        self.build = self.root / "build"
        (self.root / "CMakeLists.txt").write_text(SYNTHETIC_ROOT_CMAKE, encoding="utf-8")
        (self.root / "src/CMakeLists.txt").write_text(SRC_CMAKE_APPENDIX, encoding="utf-8")
        self.copy_reconstruction_cmake()

    @unittest.skipUnless(shutil.which("cmake") and shutil.which("ctest"),
                         "cmake and ctest are required")
    def test_ctest_that_found_nothing_is_not_green_despite_exit_zero(self):
        configure = build_gate.configure(str(self.root), build_dir=str(self.build))
        self.assertTrue(configure["ok"], configure["stderr_tail"])
        step = build_gate.ctest(str(self.root), str(self.build))
        self.assertEqual(step["returncode"], 0, "ctest exits 0 when nothing matches")
        self.assertFalse(step["ok"])
        self.assertTrue(step["no_tests_found"])
        self.assertEqual(step["tests"], [])

    @unittest.skipUnless(shutil.which("cmake") and shutil.which("ctest"),
                         "cmake and ctest are required")
    def test_gate_over_a_tree_with_no_promoted_package_is_red(self):
        result = build_gate.gate(str(self.root), build_dir=str(self.build), jobs=1)
        self.assertFalse(result["ok"])
        self.assertEqual(result["packages"], {})
        self.assertEqual(result["tests"], [])
        self.assertFalse(_step(result, "ctest")["ok"])

    def test_a_ctest_that_cannot_run_is_not_green(self):
        saved = dict(os.environ)
        try:
            os.environ["PATH"] = str(self.root / "no-such-bin")
            step = build_gate.ctest(str(self.root), str(self.build))
        finally:
            os.environ.clear()
            os.environ.update(saved)
        self.assertFalse(step["ok"])
        self.assertIsNone(step["returncode"])
        self.assertEqual(step["tests"], [])

    @unittest.skipUnless(shutil.which("cmake"), "cmake is required")
    def test_configure_only_green_claims_no_test_verdict(self):
        self.stage()
        # Nothing installed, so nothing is discovered: the only honest reading
        # of a green configure_only is "configure succeeded".
        result = build_gate.gate(str(self.root), build_dir=str(self.build), jobs=1,
                                 configure_only=True)
        self.assertTrue(result["ok"])
        self.assertEqual(result["tests"], [])
        self.assertEqual([step["name"] for step in result["steps"]], ["m32_probe", "configure"])
        for verdict in result["packages"].values():
            self.assertEqual(verdict["status"], "discovered")
            self.assertEqual(verdict["tests"], [])


# ---------------------------------------------------------------------------
# Defect 3 -- determinism
# ---------------------------------------------------------------------------

@unittest.skipUnless(shutil.which("cmake") and shutil.which("clang++"),
                     "cmake and clang++ are required for a real gate run")
class DeterminismTest(unittest.TestCase):
    def setUp(self):
        self.scratch = Path(tempfile.mkdtemp(prefix="hardening-determinism."))
        self.addCleanup(shutil.rmtree, str(self.scratch), True)
        self.source = self.scratch / "source"
        self._build_tree()

    def _build_tree(self, packages=6):
        reconstruction = self.source / "src" / "reconstruction"
        reconstruction.mkdir(parents=True, exist_ok=True)
        (self.source / "CMakeLists.txt").write_text(SYNTHETIC_ROOT_CMAKE, encoding="utf-8")
        (self.source / "src/CMakeLists.txt").write_text(SRC_CMAKE_APPENDIX, encoding="utf-8")
        shutil.copyfile(str(RECONSTRUCTION_CMAKE), str(reconstruction / "CMakeLists.txt"))
        names = []
        for index in range(packages):
            package = "pkg_det%02d_006a2ef%d" % (index, index)
            directory = reconstruction / package
            directory.mkdir(parents=True)
            stem = "det%02d_006a2ef%d" % (index, index)
            text = {"package": package, "stem": stem}
            (directory / (stem + ".hpp")).write_text(HEADER % text, encoding="utf-8")
            (directory / (stem + ".cpp")).write_text(SOURCE % text, encoding="utf-8")
            (directory / (stem + "_model_test.cpp")).write_text(TEST_SOURCE % text, encoding="utf-8")
            (directory / "promotion.json").write_text(json.dumps({
                "schema": "openspore-promotion-1", "package": package.replace("_", "-"),
                "src_package": package, "namespace": "openspore::reconstruction::" + package,
                "targets": [{"va": "0x006a2ef%d" % index, "bare_va": "006a2ef%d" % index,
                             "symbol": "Remove", "sources": [stem + ".cpp"],
                             "headers": [stem + ".hpp"], "tests": [stem + "_model_test.cpp"]}]},
                indent=2, sort_keys=True) + "\n", encoding="utf-8")
            names.append(package)
        return names

    def gate(self, build_dir, jobs):
        return build_gate.gate(str(self.source), build_dir=str(build_dir), jobs=jobs)

    def test_structured_fields_are_equal_at_any_job_count(self):
        runs = {}
        for jobs in (1, 8):
            runs[jobs] = [self.gate(self.scratch / ("b%d%d" % (jobs, index)), jobs)
                          for index in range(2)]
            self.assertTrue(runs[jobs][0]["ok"], _diagnose(runs[jobs][0]))
        self.assertEqual(_structured(runs[1][0]), _structured(runs[1][1]))
        self.assertEqual(_structured(runs[8][0]), _structured(runs[8][1]))
        self.assertEqual(_structured(runs[1][0]), _structured(runs[8][0]))

    def test_tails_are_stable_at_jobs_one_and_differ_only_in_order_at_jobs_eight(self):
        serial = [self.gate(self.scratch / ("s%d" % index), 1) for index in range(2)]
        parallel = [self.gate(self.scratch / ("p%d" % index), 8) for index in range(2)]
        self.assertEqual(_without_path_identity(serial[0]), _without_path_identity(serial[1]))

        # At -j8 the same build actions are reported, but interleaved and with
        # progress percentages assigned by whichever job finished first -- so
        # the tail is real signal that is not reproducible, exactly as the
        # module's determinism note says.
        def actions(result):
            text = _step(result, "build")["stdout_tail"]
            stripped = re.sub(r"^\[\s*\d+%\]", "", text, flags=re.M)
            return sorted(line for line in stripped.splitlines() if line.strip())

        self.assertEqual(actions(parallel[0]), actions(parallel[1]))
        self.assertNotEqual(_step(parallel[0], "build")["stdout_tail"],
                            _step(parallel[1], "build")["stdout_tail"])
        self.assertEqual(actions(serial[0]), actions(parallel[0]))

    def test_two_scratch_runs_are_comparable_despite_their_random_temp_names(self):
        first = build_gate.gate(str(self.source), jobs=1)
        second = build_gate.gate(str(self.source), jobs=1)
        self.assertNotEqual(first["build_dir"], second["build_dir"])
        self.assertEqual(_without_path_identity(first), _without_path_identity(second))

    def test_the_build_path_never_reaches_the_captured_text(self):
        result = build_gate.gate(str(self.source), build_dir=str(self.scratch / "kept"), jobs=1)
        build_dir = result["build_dir"]
        for step in result["steps"]:
            for key in ("stdout_tail", "stderr_tail"):
                self.assertNotIn(build_dir, step[key],
                                 "%s.%s leaked the build path" % (step["name"], key))
        self.assertIn("<build-dir>", _step(result, "configure")["stdout_tail"])

    def test_the_resolved_source_path_is_scrubbed_too(self):
        scrub = build_gate._scrubber(((self.source, "<source-dir>"),))
        self.assertEqual(scrub("in %s/src" % self.source.resolve()), "in <source-dir>/src")

    def test_ctest_rows_come_back_sorted_by_name(self):
        result = build_gate.gate(str(self.source), build_dir=str(self.scratch / "sorted"), jobs=1)
        names = [row["name"] for row in result["tests"]]
        self.assertEqual(names, sorted(names))
        self.assertGreater(len(names), 1)

    def test_an_inherited_makeflags_cannot_parallelise_a_serial_run(self):
        reference = self.gate(self.scratch / "mf0", 1)
        saved = os.environ.get("MAKEFLAGS")
        try:
            os.environ["MAKEFLAGS"] = "-j8"
            polluted = self.gate(self.scratch / "mf1", 1)
        finally:
            if saved is None:
                os.environ.pop("MAKEFLAGS", None)
            else:
                os.environ["MAKEFLAGS"] = saved
        self.assertEqual(_step(reference, "build")["stdout_tail"],
                         _step(polluted, "build")["stdout_tail"])

    def test_an_inherited_ctest_parallel_level_cannot_reorder_the_verdict(self):
        reference = self.gate(self.scratch / "ct0", 1)
        saved = os.environ.get("CTEST_PARALLEL_LEVEL")
        try:
            os.environ["CTEST_PARALLEL_LEVEL"] = "8"
            polluted = self.gate(self.scratch / "ct1", 1)
        finally:
            if saved is None:
                os.environ.pop("CTEST_PARALLEL_LEVEL", None)
            else:
                os.environ["CTEST_PARALLEL_LEVEL"] = saved
        self.assertEqual(reference["tests"], polluted["tests"])
        self.assertEqual(reference["packages"], polluted["packages"])

    def test_no_timestamp_pid_or_address_survives_in_the_result(self):
        result = build_gate.gate(str(self.source), build_dir=str(self.scratch / "ts"), jobs=1)
        time_key = re.compile(
            r"(?i)^.*(time|timestamp|date|clock|elapsed|duration|started|finished"
            r"|epoch|msec|usec).*$")
        offenders = [path for path, text in _wrap_strings(result) if time_key.match(text)]
        self.assertEqual(offenders, [])
        self.assertNotIn("sec", json.dumps(result["tests"]))


# ---------------------------------------------------------------------------
# Defect 4 -- the build-gate seam
# ---------------------------------------------------------------------------

class GateSeamTest(HardeningFixture):
    """One seam, and it fails closed.

    ``promote._gate_module`` is the only place the gate module is resolved, so
    the pre-flight verdict in ``apply`` and the gate that actually runs cannot
    disagree about whether a gate exists.
    """

    def test_a_gate_module_without_gate_is_an_error_and_never_a_promotion(self):
        self.stage()
        self.install_module(types.ModuleType(GATE_FULL))
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "error")
        self.assertEqual(result["code"], "build_gate_unavailable")
        self.assertFalse((self.root / "src/reconstruction" / SRC_PACKAGE).exists())
        self.assertEqual(self.residue(), [])

    def test_the_seam_prefers_the_package_attribute_then_imports(self):
        self.stage()
        self.assertIs(promote._gate_module(), self.stub,
                      "a substitute bound on the package is the one that must run")
        real = self.load_real_gate()
        holder = importlib.import_module(GATE_FULL.rsplit(".", 1)[0])
        delattr(holder, GATE_FULL.rsplit(".", 1)[1])
        self.addCleanup(setattr, holder, GATE_FULL.rsplit(".", 1)[1], real)
        self.assertIs(promote._gate_module(), real,
                      "with nothing bound on the package the real module is imported")

    def test_a_leftover_gate_substitute_fails_closed(self):
        # Whatever a caller leaves bound to the package, the pipeline's answer
        # is decided by the module it finds: a substitute with no gate() is
        # refused, never promoted past.
        self.stage()
        self.install_module(types.ModuleType(GATE_FULL))
        before = self.snapshot()
        for _ in range(3):
            result = promote.apply(self.root)
            self.assertEqual(result["status"], "error")
            self.assertEqual(result["code"], "build_gate_unavailable")
            self.assertEqual(result["promoted"], [])
        self.assert_tree_untouched(before)

    def test_a_substitute_with_a_gate_is_the_one_that_runs(self):
        self.stage()
        self.assertIs(promote._gate_module(), self.stub)
        promote.apply(self.root)
        self.assertEqual(len(self.stub.calls), 1)
        self.assertEqual(self.stub.calls[0]["packages"], [SRC_PACKAGE])


# ---------------------------------------------------------------------------
# Matrix 1 -- idempotent re-run
# ---------------------------------------------------------------------------

class IdempotenceTest(HardeningFixture):
    def test_a_second_apply_changes_nothing_at_all(self):
        self.stage()
        self.assertEqual(promote.apply(self.root)["status"], "ok")
        before = self.snapshot()
        self.stub.calls = []
        second = promote.apply(self.root)
        self.assertTrue(second["idempotent"])
        self.assertFalse(second["changed"])
        self.assertEqual(second["promoted"], [])
        self.assertEqual(second["already_promoted"], [VA])
        self.assertEqual(second["warnings"], [])
        self.assertEqual(self.stub.calls, [], "a no-op re-run must not spend a gate")
        self.assert_tree_untouched(before)

    def test_repeated_applies_never_duplicate_a_va_row(self):
        self.stage()
        for index in range(5):
            result = promote.apply(self.root)
            self.assertEqual(result["status"], "ok", index)
            self.assertEqual([target["bare_va"] for target in self.marker()["targets"]], [BARE])
        self.assertEqual(len(self.marker()["targets"]), 1)
        self.assertEqual(self.record()["va"], VA)
        self.assertEqual(promote.promoted_packages(self.root), [SRC_PACKAGE])
        self.assertEqual(self.residue(), [SRC_PACKAGE])

    def test_two_independent_roots_produce_byte_identical_markers(self):
        digests = []
        for _ in range(2):
            self.setUp()
            self.stage()
            promote.apply(self.root)
            digests.append((self.root / "src/reconstruction" / SRC_PACKAGE
                            / "promotion.json").read_bytes())
        self.assertEqual(digests[0], digests[1])


# ---------------------------------------------------------------------------
# Matrix 3 -- interrupted promotion recovery
# ---------------------------------------------------------------------------

class InterruptedPromotionTest(HardeningFixture):
    def assert_not_a_promotion_anywhere(self):
        self.assertEqual(promote.promoted_packages(self.root), [])
        self.assertEqual(build_gate.discover_packages(str(self.root)), [])
        self.assertFalse(promote.package_state(self.root, SRC_PACKAGE)["promoted"])

    def test_a_package_dir_without_a_marker_is_invisible_then_completed(self):
        self.stage()
        installed = self.root / "src/reconstruction" / SRC_PACKAGE
        installed.mkdir(parents=True)
        staging = self.root / "reconstruction/staging" / PACKAGE
        for name in sorted(os.listdir(staging)):
            shutil.copyfile(str(staging / name), str(installed / name))
        self.assert_not_a_promotion_anywhere()

        result = promote.apply(self.root)
        self.assertEqual(result["status"], "ok", result.get("detail"))
        self.assertEqual(result["promoted"], [VA])
        self.assertEqual(promote.promoted_packages(self.root), [SRC_PACKAGE])
        self.assertEqual([entry["src_package"] for entry in
                          build_gate.discover_packages(str(self.root))], [SRC_PACKAGE])
        self.assertEqual(result_names(self.residue()), [SRC_PACKAGE])

    def test_a_missing_evidence_record_is_rewritten_by_the_next_run(self):
        self.stage()
        promote.apply(self.root)
        (self.root / "reconstruction/evidence" / BARE / "promotion.json").unlink()
        self.assertFalse((self.root / "reconstruction/evidence" / BARE / "promotion.json").exists())

        result = promote.apply(self.root)
        self.assertEqual(result["status"], "ok", result.get("detail"))
        self.assertTrue(result["changed"], "writing the record is a change")
        self.assertFalse(result["idempotent"])
        self.assertEqual(result["already_promoted"], [VA])
        self.assertEqual(self.record()["va"], VA)
        third = promote.apply(self.root)
        self.assertFalse(third["changed"])
        self.assertTrue(third["idempotent"])

    def test_a_tree_parked_in_scratch_is_rebuilt_by_the_next_run(self):
        # The interrupted state: the previous package was renamed aside and the
        # new one was never installed, so the destination does not exist.
        self.stage()
        promote.apply(self.root)
        installed = self.root / "src/reconstruction" / SRC_PACKAGE
        holder = self.root / "src/reconstruction" / promote.SCRATCH_NAME
        holder.mkdir(parents=True)
        crashed = holder / ("%d.deadbeef" % os.getpid())
        crashed.mkdir()
        os.replace(str(installed), str(crashed / "superseded"))
        self.assertFalse(installed.exists())
        self.assert_not_a_promotion_anywhere()
        self.assertEqual(result_names(self.residue()), [])

        result = promote.apply(self.root)
        self.assertEqual(result["status"], "ok", result.get("detail"))
        self.assertEqual(result["promoted"], [VA])
        self.assertEqual(promote.promoted_packages(self.root), [SRC_PACKAGE])
        self.assertEqual([target["bare_va"] for target in self.marker()["targets"]], [BARE])
        self.assertEqual(self.residue(), [SRC_PACKAGE])

    def test_a_leftover_scratch_tree_is_swept_but_a_live_one_is_kept(self):
        self.stage()
        holder = self.root / "src/reconstruction" / promote.SCRATCH_NAME
        dead = holder / ("cafebabe.%d" % 999999999)
        live = holder / ("0badc0de.%d" % os.getpid())
        for path in (dead, live):
            path.mkdir(parents=True)
            (path / "install").mkdir()
            (path / "install" / "leftover.cpp").write_text("// stale\n", encoding="utf-8")
        self.assertEqual(promote.promoted_packages(self.root), [])
        self.assertEqual(build_gate.discover_packages(str(self.root)), [])

        promote.apply(self.root)
        self.assertFalse(dead.exists(), "a dead owner's scratch tree must be swept")
        self.assertTrue(live.exists(), "a live owner's scratch tree must survive")
        self.assertEqual(result_names(self.residue()), [SRC_PACKAGE])
        self.assertEqual(promote.promoted_packages(self.root), [SRC_PACKAGE])

    def test_scratch_tree_names_carry_the_owner_pid(self):
        # tempfile.mkdtemp names do not end in the pid, and a sweep that cannot
        # read the owner out of the name deletes a live run's tree -- the
        # opposite of what it promises.
        self.stage()
        promote.apply(self.root)
        holder = self.root / "src/reconstruction" / promote.SCRATCH_NAME
        self.assertFalse(holder.exists())
        name = promote._scratch(self.root)
        try:
            self.assertEqual(name.name.rsplit(".", 1)[-1], str(os.getpid()))
            self.assertTrue(promote._alive(int(name.name.rsplit(".", 1)[-1])))
        finally:
            promote._drop_scratch(name)
        self.assertFalse(holder.exists())


def result_names(names):
    # type: (list) -> list
    """The names a build or a discovery path could actually reach."""
    return sorted(name for name in names if not name.startswith("."))


def _raise_oserror(*args, **kwargs):
    # type: (object, object) -> None
    raise OSError("injected: the evidence volume is read-only")


# ---------------------------------------------------------------------------
# Matrix 4 and 5 -- compile and test failures, through the real gate
# ---------------------------------------------------------------------------

@unittest.skipUnless(shutil.which("cmake") and shutil.which("clang++") and shutil.which("ctest"),
                     "cmake, clang++ and ctest are required for the real gate")
class RealGateFailureTest(HardeningFixture):
    def setUp(self):
        HardeningFixture.setUp(self)
        if not RECONSTRUCTION_CMAKE.is_file():
            self.skipTest("the repository has no src/reconstruction/CMakeLists.txt")
        self.load_real_gate()
        self.copy_reconstruction_cmake()

    def assert_refused_with_nothing_installed(self, result, before):
        self.assertEqual(result["status"], "blocked", result.get("detail"))
        self.assertFalse((self.root / "src/reconstruction" / SRC_PACKAGE).exists())
        self.assertFalse((self.root / "reconstruction/evidence" / BARE
                          / "promotion.json").exists())
        self.assert_tree_untouched(before)
        self.assertEqual(self.scratch_residue(), [], "scratch or lock residue left behind")

    def test_a_package_whose_source_does_not_compile_is_refused(self):
        self.stage(source_text=UNCOMPILABLE_SOURCE)
        before = self.snapshot()
        result = promote.apply(self.root, jobs=2)
        self.assert_refused_with_nothing_installed(result, before)
        steps = {step["name"] for step in result["build"]["steps"]}
        self.assertIn("build", steps)
        self.assertFalse(result["build"]["ok"])
        self.assertIn("package_refused", [item["code"] for entry in result["refused"]
                                          for item in entry["blockers"]])

    def test_a_package_that_compiles_but_aborts_is_refused_with_ctest_rows(self):
        self.stage(test_text=ABORTING_TEST)
        before = self.snapshot()
        result = promote.apply(self.root, jobs=2)
        self.assert_refused_with_nothing_installed(result, before)

        ctest = [step for step in result["build"]["steps"] if step["name"] == "ctest"][0]
        self.assertTrue(ctest["ok"] is False)
        self.assertFalse(ctest["no_tests_found"], "the abort is a real test run, not a no-match")
        build_step = [step for step in result["build"]["steps"] if step["name"] == "build"][0]
        self.assertTrue(build_step["ok"], "the test binary compiled; it is the run that fails")

        names = [row["name"] for row in result["build"]["tests"]]
        self.assertIn("recon_%s_%s_model_test" % (SRC_PACKAGE, STEM), names)
        row = [item for item in result["build"]["tests"]
               if item["name"] == "recon_%s_%s_model_test" % (SRC_PACKAGE, STEM)][0]
        self.assertFalse(row["ok"])
        self.assertEqual(row["returncode"], 1)
        self.assertIn("Subprocess aborted", ctest["stdout_tail"] + ctest["stderr_tail"])


# ---------------------------------------------------------------------------
# Matrix 6 -- no state outside the package is left mutated on any failure path
# ---------------------------------------------------------------------------

class FailurePathTest(HardeningFixture):
    """One assertion, applied to every place ``apply`` can fail.

    The injection points are the real ones: each sabotages the step it names
    and lets the exception escape, so whatever that step had already done is
    still on the filesystem when ``apply`` returns. The scenario is a *second*
    promotion of an already-installed package, so the install has a previous
    tree to lose and a swap to interrupt.
    """

    def stage_and_promote(self):
        self.stage()
        promote.apply(self.root)
        (self.root / "reconstruction/evidence" / BARE / "promotion.json").unlink()
        self.write(self.root / "reconstruction/staging" / PACKAGE / (STEM + ".cpp"),
                   (SOURCE % {"package": SRC_PACKAGE, "stem": STEM}) + "\n// second revision\n")
        self.write_validation(BARE, PACKAGE, STEM)
        return self.snapshot()

    def installed_digests(self):
        directory = self.root / "src/reconstruction" / SRC_PACKAGE
        return {name: _digest(directory / name) for name in sorted(os.listdir(directory))}

    def injections(self):
        """``(name, sabotage)`` pairs; each sabotage returns its own undo."""
        def scratch_tree_creation_fails():
            # _scratch has already made its holder when the per-run name is
            # generated, so this is the one failure that could leave a trace
            # under src/ for a promotion that wrote nothing.
            original = promote.os.urandom
            promote.os.urandom = _raise_oserror
            return lambda: setattr(promote.os, "urandom", original)

        def stage_raises():
            original = promote._stage_tree
            def sabotaged(scratch, candidate):
                install = original(scratch, candidate)
                (install / "half_written.cpp").write_text("// half\n", encoding="utf-8")
                raise RuntimeError("injected: after staging the install tree")
            promote._stage_tree = sabotaged
            return lambda: setattr(promote, "_stage_tree", original)

        def marker_write_raises():
            original = promote.write_json_atomic
            def sabotaged(path, value):
                if Path(path).name == promote.PROMOTION_NAME:
                    raise RuntimeError("injected: before the marker was written")
                return original(path, value)
            promote.write_json_atomic = sabotaged
            return lambda: setattr(promote, "write_json_atomic", original)

        def gate_raises():
            self.stub.raises = RuntimeError("injected: the gate exploded")
            return lambda: setattr(self.stub, "raises", None)

        def gate_red():
            self.stub.ok = False
            return lambda: setattr(self.stub, "ok", True)

        def install_not_reached():
            original = promote._install
            def sabotaged(*args, **kwargs):
                raise RuntimeError("injected: before the install")
            promote._install = sabotaged
            return lambda: setattr(promote, "_install", original)

        def install_rename_fails():
            # The one window in which the previous tree exists nowhere else: the
            # rename aside has succeeded and the install rename must not. Only
            # that one rename is broken, so the restore path is left working --
            # sabotaging os.replace wholesale would also break the restore and
            # would be testing the sabotage rather than the pipeline.
            original = promote.os.replace
            state = {"swapped": False}
            def sabotaged(source, destination):
                if str(destination).endswith("superseded"):
                    state["swapped"] = True
                    return original(source, destination)
                if state["swapped"] and str(source).rstrip("/").endswith("install"):
                    raise OSError("injected: the install rename failed")
                return original(source, destination)
            promote.os.replace = sabotaged
            return lambda: setattr(promote.os, "replace", original)

        return [("scratch_tree_creation_fails", scratch_tree_creation_fails),
                ("install_tree_staged", stage_raises),
                ("marker_write", marker_write_raises),
                ("gate_raises", gate_raises),
                ("gate_red", gate_red),
                ("install_not_reached", install_not_reached),
                ("install_rename_fails", install_rename_fails)]

    def test_every_injection_point_leaves_the_tree_untouched(self):
        for name, sabotage in self.injections():
            with self.subTest(injection=name):
                self.setUp()
                before = self.stage_and_promote()
                installed = self.root / "src/reconstruction" / SRC_PACKAGE
                self.assertTrue((installed / "promotion.json").is_file(), name)
                previous = self.installed_digests()
                undo = sabotage()
                try:
                    result = promote.apply(self.root, overwrite=True)
                finally:
                    undo()
                self.assertIn(result["status"], ("blocked", "error"), name)
                self.assertEqual(result["promoted"], [], name)
                self.assert_tree_untouched(before)
                self.assertEqual(self.scratch_residue(), [],
                                 "%s left a scratch or lock tree behind" % name)
                self.assertEqual(self.installed_digests(), previous,
                                 "%s changed the installed package" % name)
                self.assertEqual(promote.promoted_packages(self.root), [SRC_PACKAGE], name)
                self.assertEqual([entry["src_package"] for entry in
                                  build_gate.discover_packages(str(self.root))], [SRC_PACKAGE],
                                 "%s left the package undiscoverable" % name)

    def test_a_failed_install_rename_never_destroys_the_previous_tree(self):
        self.stage_and_promote()
        installed = self.root / "src/reconstruction" / SRC_PACKAGE
        before = self.installed_digests()
        original = promote.os.replace
        state = {"swapped": False}

        def sabotaged(source, destination):
            if str(destination).endswith("superseded"):
                state["swapped"] = True
                return original(source, destination)
            if state["swapped"] and str(source).rstrip("/").endswith("install"):
                raise OSError("injected: the install rename failed")
            return original(source, destination)

        promote.os.replace = sabotaged
        self.addCleanup(setattr, promote.os, "replace", original)
        result = promote.apply(self.root, overwrite=True)
        self.assertTrue(state["swapped"], "the fixture did not reach the swap")
        self.assertEqual(result["status"], "error")
        self.assertEqual(result["code"], "promotion_failed")
        self.assertTrue(installed.is_dir(), "the previous tree must be put back")
        self.assertEqual(self.installed_digests(), before)
        self.assertEqual(promote.promoted_packages(self.root), [SRC_PACKAGE])
        self.assertEqual(self.scratch_residue(), [])

    def test_a_failing_provenance_write_does_not_undo_a_finished_install(self):
        self.stage()
        original = promote._write_record
        promote._write_record = _raise_oserror
        self.addCleanup(setattr, promote, "_write_record", original)
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "ok",
                         "src/ holds exactly the tree the gate approved")
        self.assertEqual(result["promoted"], [VA])
        self.assertEqual([item["code"] for item in result["warnings"]],
                         ["promotion_record_unwritten"])
        self.assertEqual(promote.promoted_packages(self.root), [SRC_PACKAGE])
        self.assertFalse((self.root / "reconstruction/evidence" / BARE
                          / "promotion.json").exists())

        # And the next run completes the record without reinstalling.
        promote._write_record = original
        self.stub.calls = []
        second = promote.apply(self.root)
        self.assertEqual(second["status"], "ok")
        self.assertEqual(self.stub.calls, [])
        self.assertEqual(self.record()["va"], VA)


# ---------------------------------------------------------------------------
# Matrix 7 -- stale and inconsistent metadata
# ---------------------------------------------------------------------------

class StaleMetadataTest(HardeningFixture):
    def test_a_report_that_records_no_digest_is_stale(self):
        self.stage()
        self.write_validation(BARE, PACKAGE, STEM, omit_sha=True)
        before = self.snapshot()
        self.assertIn("validation_stale", self.codes(promote.plan(self.root)))
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assert_tree_untouched(before)

    def test_a_report_whose_digest_does_not_match_is_stale(self):
        self.stage()
        self.write_validation(BARE, PACKAGE, STEM, source_sha="c" * 64)
        before = self.snapshot()
        self.assertIn("validation_stale", self.codes(promote.plan(self.root)))
        self.assertEqual(promote.apply(self.root)["status"], "blocked")
        self.assert_tree_untouched(before)

    def test_a_marker_whose_recorded_digests_no_longer_match_is_not_trusted(self):
        self.stage()
        promote.apply(self.root)
        path = self.root / "src/reconstruction" / SRC_PACKAGE / "promotion.json"
        document = json.loads(path.read_text(encoding="utf-8"))
        document["targets"][0]["staging_sha256"][STEM + ".cpp"] = "d" * 64
        path.write_text(json.dumps(document, indent=2, sort_keys=True) + "\n", encoding="utf-8")

        self.assertFalse(promote.plan(self.root)["candidates"][0]["promoted"])
        self.assertEqual(promote.apply(self.root)["status"], "ok")
        repaired = self.marker()["targets"][0]["staging_sha256"][STEM + ".cpp"]
        self.assertEqual(repaired, _digest(self.root / "reconstruction/staging" / PACKAGE
                                           / (STEM + ".cpp")))

    def test_a_marker_with_an_unknown_schema_is_not_a_promotion(self):
        self.stage()
        promote.apply(self.root)
        path = self.root / "src/reconstruction" / SRC_PACKAGE / "promotion.json"
        document = json.loads(path.read_text(encoding="utf-8"))
        document["schema"] = "openspore-promotion-99"
        path.write_text(json.dumps(document, indent=2, sort_keys=True) + "\n", encoding="utf-8")

        self.assertEqual(promote.promoted_packages(self.root), [])
        self.assertFalse(promote.package_state(self.root, SRC_PACKAGE)["promoted"])
        self.assertEqual(build_gate.discover_packages(str(self.root)), [],
                         "python and the gate must agree on what is promoted")
        # A marker the build would not read cannot own its VA either, so the
        # refusal is not a deadlock.
        self.assertEqual(promote._promoted_va_owners(self.root), {})
        self.assertEqual(promote.apply(self.root)["status"], "ok")
        self.assertEqual(self.marker()["schema"], "openspore-promotion-1")

    def test_a_marker_with_an_unbuildable_src_package_is_not_a_promotion(self):
        self.stage()
        promote.apply(self.root)
        path = self.root / "src/reconstruction" / SRC_PACKAGE / "promotion.json"
        document = json.loads(path.read_text(encoding="utf-8"))
        document["src_package"] = "pkg; rm -rf /"
        path.write_text(json.dumps(document, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        self.assertEqual(promote.promoted_packages(self.root), [])
        self.assertEqual(build_gate.discover_packages(str(self.root)), [])

    def test_an_unreadable_marker_is_not_a_promotion(self):
        self.stage()
        promote.apply(self.root)
        (self.root / "src/reconstruction" / SRC_PACKAGE / "promotion.json").write_text(
            "{not json", encoding="utf-8")
        self.assertEqual(promote.promoted_packages(self.root), [])
        self.assertEqual(build_gate.discover_packages(str(self.root)), [])
        self.assertEqual(promote.apply(self.root)["status"], "ok")

    def test_a_marker_whose_src_package_disagrees_with_its_directory_is_repaired(self):
        # Not detectable at the CMake level -- the protected reconstruction
        # CMakeLists takes the marker's src_package as the target name -- so
        # what is asserted here is that this pipeline never trusts it: the
        # package is not reported as promoted and a re-run rewrites the name.
        self.stage()
        promote.apply(self.root)
        path = self.root / "src/reconstruction" / SRC_PACKAGE / "promotion.json"
        document = json.loads(path.read_text(encoding="utf-8"))
        document["src_package"] = "some_other_name"
        path.write_text(json.dumps(document, indent=2, sort_keys=True) + "\n", encoding="utf-8")

        self.assertEqual(promote.promoted_packages(self.root), [SRC_PACKAGE],
                         "the directory is still readable; its marker is not identical")
        self.assertFalse(promote.plan(self.root)["candidates"][0]["promoted"])
        self.assertEqual(promote.apply(self.root)["status"], "ok")
        self.assertEqual(self.marker()["src_package"], SRC_PACKAGE)


# ---------------------------------------------------------------------------
# Matrix 8 -- deterministic package naming
# ---------------------------------------------------------------------------

class PackageNamingTest(HardeningFixture):
    WELL_FORMED = ("pkg-x-y", "pkg_x_y", "pkg-x_y", "PKG-X-Y", "pkg-x",
                   "pkg11-i1-tool-onselect", "pkg-property-remove-006a2ef0")

    def test_the_normalization_is_total_and_idempotent_on_well_formed_names(self):
        for name in self.WELL_FORMED:
            with self.subTest(name=name):
                dashed, underscored = promote._resolve_package(name)
                self.assertIsNotNone(dashed)
                self.assertEqual(promote._resolve_package(dashed)[0], dashed)
                self.assertEqual(promote._resolve_package(underscored)[0], dashed)
                self.assertTrue(promote.SRC_NAME_RE.match(underscored),
                                "%r -> %r is not a buildable target name" % (name, underscored))

    def test_either_spelling_and_a_path_address_the_same_package(self):
        for spelling in (PACKAGE, SRC_PACKAGE, "src/reconstruction/" + SRC_PACKAGE,
                         "/" + PACKAGE + "/"):
            with self.subTest(spelling=spelling):
                self.assertEqual(promote._resolve_package(spelling)[0], PACKAGE)

    def test_a_hostile_name_is_refused_by_the_gate_rather_than_installed(self):
        # promote itself does not re-check the CMake target-name rule, so the
        # gate is what stands between a hostile staging name and src/. Asserted
        # here so that removing the gate from the path cannot go unnoticed.
        self.stage(package="pkg;bad", stem=STEM, src_package="pkg;bad")
        before = self.snapshot()
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assert_tree_untouched(before)

    def test_two_dashed_packages_that_normalize_to_one_name_are_refused_not_merged(self):
        self.stage()
        # Same normalized name, different staging directories.
        collide = self.root / "reconstruction/staging" / "pkg_hardening_006a2ef0"
        collide.mkdir(parents=True, exist_ok=True)
        text = {"package": SRC_PACKAGE, "stem": STEM}
        (collide / (STEM + ".hpp")).write_text(HEADER % text, encoding="utf-8")
        (collide / (STEM + ".cpp")).write_text(SOURCE % text, encoding="utf-8")
        (collide / (STEM + "_model_test.cpp")).write_text(TEST_SOURCE % text, encoding="utf-8")

        document = promote.plan(self.root)
        codes = self.codes(document)
        self.assertIn("src_package_collision", codes)
        packages = sorted(candidate["package"] for candidate in document["candidates"]
                          if any(item["code"] == "src_package_collision"
                                 for item in candidate["blockers"]))
        self.assertEqual(packages, sorted([PACKAGE, "pkg_hardening_006a2ef0"]))

        before = self.snapshot()
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assertIn("src_package_collision",
                      [item["code"] for entry in result["refused"] for item in entry["blockers"]])
        self.assert_tree_untouched(before)

    def test_one_package_in_both_spellings_is_not_a_collision(self):
        self.stage()
        self.assertEqual(self.codes(promote.plan(self.root)), [])
        self.assertEqual(promote.apply(self.root)["status"], "ok")


# ---------------------------------------------------------------------------
# Matrix 9 and 10 -- no false STATIC_VALIDATED, no runtime leakage
# ---------------------------------------------------------------------------

NON_PASS_STATIC = ("WARN", "FAIL", "PARTIAL", "UNKNOWN", "NOT_AVAILABLE", None, "", "pass",
                   "PASS ", "0")
NON_GATED_RUNTIME = ("PASS", "FAIL", "UNKNOWN", "NOT_AVAILABLE", None, "", "gated", "GATED ")


class StatusInvariantTest(HardeningFixture):
    def installed_marker_or_none(self):
        path = self.root / "src/reconstruction" / SRC_PACKAGE / "promotion.json"
        if not path.is_file():
            return None
        return json.loads(path.read_text(encoding="utf-8"))

    def test_static_status_is_pass_in_every_installed_marker(self):
        for status in NON_PASS_STATIC:
            with self.subTest(static=status):
                self.setUp()
                self.stage(static=status)
                before = self.snapshot()
                result = promote.apply(self.root)
                marker = self.installed_marker_or_none()
                if marker is not None:
                    self.assertEqual(marker["targets"][0]["static_status"], "PASS")
                else:
                    self.assertEqual(result["status"], "blocked")
                    self.assert_tree_untouched(before)

    def test_a_report_downgraded_after_the_install_is_refused_and_nothing_is_reinstalled(self):
        self.stage()
        promote.apply(self.root)
        installed = (self.root / "src/reconstruction" / SRC_PACKAGE / "promotion.json").read_bytes()
        self.write_validation(BARE, PACKAGE, STEM, static="WARN")
        before = self.snapshot()

        document = promote.plan(self.root)
        self.assertEqual(document["candidates"][0]["static_status"], "WARN")
        self.assertIn("static_not_pass", self.codes(document))
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assertEqual(result["promoted"], [])
        self.assert_tree_untouched(before)
        self.assertEqual((self.root / "src/reconstruction" / SRC_PACKAGE / "promotion.json")
                         .read_bytes(), installed)

    def test_the_static_validated_token_is_never_written(self):
        self.stage()
        promote.apply(self.root)
        promote.apply(self.root)
        for path in sorted((self.root).rglob("*")):
            if path.is_file() and path.suffix in (".json", ".cpp", ".hpp", ".txt"):
                self.assertNotIn(FORBIDDEN_TOKEN, path.read_text(encoding="utf-8"),
                                 "%s carries the token" % path)
        self.assertFalse(any(FORBIDDEN_TOKEN in text for _path, text
                             in _wrap_strings(promote.plan(self.root))))

    def test_runtime_status_is_gated_in_every_installed_marker(self):
        for status in NON_GATED_RUNTIME:
            with self.subTest(runtime=status):
                self.setUp()
                self.stage(runtime=status)
                before = self.snapshot()
                result = promote.apply(self.root)
                marker = self.installed_marker_or_none()
                if marker is not None:
                    self.assertEqual(marker["targets"][0]["runtime_status"], "GATED")
                else:
                    self.assertEqual(result["status"], "blocked")
                    self.assert_tree_untouched(before)

    def test_a_report_claiming_a_runtime_pass_is_refused_with_runtime_not_gated(self):
        self.stage(runtime="PASS")
        before = self.snapshot()
        document = promote.plan(self.root)
        self.assertEqual(document["candidates"][0]["runtime_status"], "PASS")
        self.assertIn("runtime_not_gated", self.codes(document))
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assertIn("runtime_not_gated",
                      [item["code"] for entry in result["refused"] for item in entry["blockers"]])
        self.assert_tree_untouched(before)

    def test_the_installed_runtime_validation_block_cannot_claim_a_pass(self):
        self.stage()
        promote.apply(self.root)
        marker = self.marker()
        block = marker["targets"][0]["runtime_validation"]
        self.assertEqual(block["status"], "GATED")
        self.assertIs(block["gated"], True)
        self.assertEqual(block["validated"], 0)
        for text in (json.dumps(marker), json.dumps(self.record())):
            self.assertNotIn('"runtime_status": "PASS"', text)
            self.assertNotIn('"status": "PASS"', text)
        self.assertNotIn("runtime_validated", json.dumps(marker))

    def test_the_required_statuses_are_the_only_ones_accepted(self):
        # The invariant is anchored in the module's own constants, so widening
        # REQUIRED_STATIC_STATUS or REQUIRED_RUNTIME_STATUS is what breaks.
        self.assertEqual(promote.REQUIRED_STATIC_STATUS, "PASS")
        self.assertEqual(promote.REQUIRED_RUNTIME_STATUS, "GATED")
        for status in NON_PASS_STATIC:
            self.assertNotEqual(status, promote.REQUIRED_STATIC_STATUS)
        for status in NON_GATED_RUNTIME:
            self.assertNotEqual(status, promote.REQUIRED_RUNTIME_STATUS)


# ---------------------------------------------------------------------------
# Matrix 11 -- the m32 probe
# ---------------------------------------------------------------------------

class M32ProbeTest(HardeningFixture):
    def write_wrapper(self, name, body):
        path = self.root / name
        self.write(path, body)
        os.chmod(str(path), os.stat(str(path)).st_mode | stat.S_IEXEC | stat.S_IXGRP
                 | stat.S_IXOTH)
        return str(path)

    @unittest.skipUnless(shutil.which("clang++"), "clang++ is required")
    def test_the_probe_is_green_for_a_compiler_that_honours_m32(self):
        step = build_gate.m32_probe(cxx=build_gate.DEFAULT_CXX, m32=True)
        self.assertTrue(step["ok"], step["stdout_tail"])
        self.assertEqual(step["m32_returncode"], 0)
        self.assertNotEqual(step["no_m32_returncode"], 0)

    @unittest.skipUnless(shutil.which("clang++"), "clang++ is required")
    def test_the_probe_goes_red_when_the_compiler_swallows_m32(self):
        real = shutil.which(build_gate.DEFAULT_CXX) or build_gate.DEFAULT_CXX
        wrapper = self.write_wrapper(
            "swallow-m32",
            "#!/bin/sh\n"
            "# A wrapper that drops -m32 the way a mis-configured toolchain does.\n"
            'args=""\n'
            'for a in "$@"; do\n'
            '  if [ "$a" = "-m32" ]; then continue; fi\n'
            '  args="$args \\"$a\\""\n'
            "done\n"
            'eval exec "%s" $args "$@"\n' % real)
        step = build_gate.m32_probe(cxx=wrapper, m32=True)
        self.assertFalse(step["ok"], step["stdout_tail"])
        self.assertNotEqual(step["m32_returncode"], 0,
                            "the thiscall probe must be rejected once -m32 is gone")
        self.assertEqual(step["name"], "m32_probe")

    @unittest.skipUnless(shutil.which("cmake") and shutil.which("clang++"),
                         "cmake and clang++ are required")
    def test_a_gate_whose_compiler_swallows_m32_is_red_and_spends_no_build(self):
        real = shutil.which(build_gate.DEFAULT_CXX) or build_gate.DEFAULT_CXX
        wrapper = self.write_wrapper(
            "gate-m32",
            "#!/bin/sh\nargs=\"\"\n"
            'for a in "$@"; do\n'
            '  if [ "$a" = "-m32" ]; then continue; fi\n'
            '  args="$args \\"$a\\""\n'
            "done\n"
            'eval exec "%s" $args "$@"\n' % real)
        if not RECONSTRUCTION_CMAKE.is_file():
            self.skipTest("the repository has no src/reconstruction/CMakeLists.txt")
        (self.root / "CMakeLists.txt").write_text(SYNTHETIC_ROOT_CMAKE, encoding="utf-8")
        (self.root / "src/CMakeLists.txt").write_text(SRC_CMAKE_APPENDIX, encoding="utf-8")
        self.copy_reconstruction_cmake()
        build = self.root / "build"
        result = build_gate.gate(str(self.root), build_dir=str(build), cxx=wrapper, jobs=1)
        self.assertFalse(result["ok"])
        self.assertEqual([step["name"] for step in result["steps"]], ["m32_probe"])
        self.assertEqual(result["tests"], [])
        self.assertEqual(result["packages"], {})
        self.assertFalse(build.exists(), "no build may be spent on a red probe")


# ---------------------------------------------------------------------------
# Matrix 12 -- concurrent promotion
# ---------------------------------------------------------------------------

class ConcurrencyTest(HardeningFixture):
    def run_concurrently(self, calls):
        results = [None] * len(calls)
        errors = []

        def worker(index, call):
            try:
                results[index] = call()
            except Exception as exc:  # pragma: no cover - a raised thread is the failure
                errors.append("%s: %s" % (type(exc).__name__, exc))

        threads = [threading.Thread(target=worker, args=(index, call))
                   for index, call in enumerate(calls)]
        for thread in threads:
            thread.start()
        for thread in threads:
            thread.join(180)
        for thread in threads:
            self.assertFalse(thread.is_alive(), "a promotion thread did not finish")
        self.assertEqual(errors, [])
        return results

    def test_two_promotions_of_one_package_install_it_once(self):
        self.stage()
        results = self.run_concurrently([lambda: promote.apply(self.root),
                                         lambda: promote.apply(self.root)])
        for result in results:
            self.assertIn(result["status"], ("ok", "blocked"), result.get("detail"))
        changed = [result for result in results if result["changed"]]
        self.assertEqual(len(changed), 1, "exactly one run may report a change")
        self.assertEqual(promote.promoted_packages(self.root), [SRC_PACKAGE])
        self.assertEqual([target["bare_va"] for target in self.marker()["targets"]], [BARE])
        self.assertEqual(self.residue(), [SRC_PACKAGE])
        promoted = sorted(va for result in results for va in result["promoted"])
        self.assertEqual(promoted, [VA])
        already = sorted(va for result in results for va in result["already_promoted"])
        self.assertEqual(already, [VA])
        blocked = [result for result in results if result["status"] == "blocked"]
        for result in blocked:
            self.assertIn("package_locked",
                          [item["code"] for entry in result["refused"]
                           for item in entry["blockers"]])

    def test_four_promotions_of_one_package_still_install_it_once(self):
        self.stage()
        results = self.run_concurrently([lambda: promote.apply(self.root) for _ in range(4)])
        self.assertEqual(len([result for result in results if result["changed"]]), 1)
        self.assertEqual(promote.promoted_packages(self.root), [SRC_PACKAGE])
        self.assertEqual(len(self.marker()["targets"]), 1)
        self.assertEqual(self.residue(), [SRC_PACKAGE])

    def test_two_promotions_of_different_packages_both_succeed(self):
        self.stage()
        second = self.stage(package=ALT_PACKAGE, stem=ALT_STEM, va="006a2ef1",
                            src_package=ALT_SRC_PACKAGE)
        self.assertEqual(self.codes(promote.plan(self.root)), [])
        results = self.run_concurrently([
            lambda: promote.apply(self.root, package=PACKAGE),
            lambda: promote.apply(self.root, package=ALT_PACKAGE)])
        for result in results:
            self.assertEqual(result["status"], "ok", result.get("detail"))
        self.assertEqual(promote.promoted_packages(self.root),
                         sorted([SRC_PACKAGE, second["src_package"]]))
        self.assertEqual(sorted(result_names(self.residue())),
                         sorted([SRC_PACKAGE, second["src_package"]]))
        self.assertEqual(len(self.stub.calls), 2)

    def test_a_lock_held_by_a_live_process_is_waited_on_then_refused(self):
        self.stage()
        holder = self.root / "src/reconstruction" / (promote.LOCK_PREFIX + SRC_PACKAGE)
        holder.mkdir(parents=True)
        (holder / promote.LOCK_OWNER).write_text("%d\n" % os.getpid(), encoding="utf-8")
        saved = promote.LOCK_TIMEOUT
        promote.LOCK_TIMEOUT = 0.2
        self.addCleanup(setattr, promote, "LOCK_TIMEOUT", saved)
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assertIn("package_locked",
                      [item["code"] for entry in result["refused"] for item in entry["blockers"]])
        self.assertEqual(promote.promoted_packages(self.root), [])
        self.assertTrue(holder.exists(), "a refused promotion must not steal a live lock")

    def test_a_lock_left_by_a_dead_process_is_stolen(self):
        self.stage()
        holder = self.root / "src/reconstruction" / (promote.LOCK_PREFIX + SRC_PACKAGE)
        holder.mkdir(parents=True)
        (holder / promote.LOCK_OWNER).write_text("999999999\n", encoding="utf-8")
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "ok", result.get("detail"))
        self.assertFalse(holder.exists(), "the stolen lock must be released again")
        self.assertEqual(promote.promoted_packages(self.root), [SRC_PACKAGE])

    def test_a_lock_with_no_owner_record_is_treated_as_live(self):
        # The window between mkdir and the owner write belongs to whoever won
        # it; treating it as abandoned would let two runs in.
        self.stage()
        holder = self.root / "src/reconstruction" / (promote.LOCK_PREFIX + SRC_PACKAGE)
        holder.mkdir(parents=True)
        self.assertTrue(promote._lock_is_live(holder))
        (holder / promote.LOCK_OWNER).write_text("not-a-pid\n", encoding="utf-8")
        self.assertTrue(promote._lock_is_live(holder))
        (holder / promote.LOCK_OWNER).write_text("999999999\n", encoding="utf-8")
        self.assertFalse(promote._lock_is_live(holder))

    def test_the_lock_is_never_global(self):
        self.stage()
        first = promote._acquire_package_lock(self.root, "pkg_one")
        self.addCleanup(promote._release_package_lock, first)
        second = promote._acquire_package_lock(self.root, "pkg_two")
        self.addCleanup(promote._release_package_lock, second)
        self.assertIsNotNone(first)
        self.assertIsNotNone(second)
        self.assertNotEqual(first, second)

    def test_a_refused_promotion_leaves_no_lock_behind(self):
        self.stage()
        self.stub.ok = False
        before = self.snapshot()
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assert_tree_untouched(before)
        self.assertEqual(self.residue(), [])


if __name__ == "__main__":
    unittest.main()
