"""Tests for the promotion engine: ``tools/reconstruction_tooling/promote.py``.

Everything here builds a synthetic repository under its own ``mkdtemp`` and
points ``promote`` at it by ``root=``. The real repository is never read
except through a digest snapshot, and no artifact is written outside the
tempdir. The build gate is a stub module injected into ``sys.modules``: the
gate is owned by another agent, and a promotion that is not gated is the
failure this suite exists to prevent, so the stub decides green or red
explicitly instead of compiling anything.

The property under test throughout is the composition
``static == "PASS" and runtime == "GATED"`` (see
``docs/tooling/validation-dimensions.md``). A single non-PASS static status
or a single non-GATED runtime status must refuse the package, a red gate must
leave ``src/`` untouched, and no artifact this module writes may ever claim a
runtime PASS.

Run from the repo root::

    python3 -m unittest tests.test_promotion -v
"""
import hashlib
import json
import os
import shutil
import sys
import tempfile
import types
import unittest
from pathlib import Path

from tools.reconstruction_tooling import promote

GATE_MODULE = "tools.reconstruction_tooling.build_gate"
VA = "0x006a2ef0"
BARE = "006a2ef0"
PACKAGE = "pkg-property-remove-006a2ef0"
SRC_PACKAGE = "pkg_property_remove_006a2ef0"
STEM = "property_remove_006a2ef0"

HEADER = """#pragma once

namespace openspore::reconstruction::%(package)s {

int RemoveProperty(void *self, unsigned int key);

}  // namespace openspore::reconstruction::%(package)s
"""

SOURCE = """#include "%(stem)s.hpp"

namespace openspore::reconstruction::%(package)s {

int RemoveProperty(void *self, unsigned int key) {
  (void)self;
  (void)key;
  return 0;
}

}  // namespace openspore::reconstruction::%(package)s
"""

TEST_SOURCE = """#include "%(stem)s.hpp"

#include <cstdlib>

namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

}  // namespace

int main() {
  using namespace openspore::reconstruction::%(package)s;
  check(RemoveProperty(nullptr, 1u) == 0);
  return 0;
}
"""


def _digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def _tree_digest(root):
    """A digest of every file under ``root``: path plus content, sorted."""
    entries = []
    for path in sorted(Path(root).rglob("*")):
        if path.is_file():
            entries.append("%s:%s" % (path.relative_to(root).as_posix(), _digest(path)))
        elif path.is_dir():
            entries.append("%s/" % path.relative_to(root).as_posix())
    return hashlib.sha256("\n".join(entries).encode("utf-8")).hexdigest()


class PromotionFixture(unittest.TestCase):
    """A synthetic repository with one staged package and its evidence."""

    def setUp(self):
        self.root = Path(tempfile.mkdtemp(prefix="promotion-test."))
        self.addCleanup(shutil.rmtree, str(self.root), True)
        for relative in ("reconstruction/staging", "reconstruction/metadata",
                         "reconstruction/evidence", "reconstruction/knowledge",
                         "src/reconstruction"):
            (self.root / relative).mkdir(parents=True, exist_ok=True)
        self.gate_calls = []
        self.gate_result = {"schema": "openspoke-build-gate-1", "ok": True,
                            "steps": [{"name": "compile", "ok": True, "returncode": 0}],
                            "packages": {SRC_PACKAGE: {"ok": True}}}
        self.gate_error = None
        self._install_gate()

    def _install_gate(self):
        module = types.ModuleType(GATE_MODULE)
        outer = self

        def gate(root, packages=None, build_dir=None, jobs=None):
            outer.gate_calls.append({"root": root, "packages": list(packages or []),
                                     "build_dir": build_dir, "jobs": jobs})
            if outer.gate_error is not None:
                raise outer.gate_error
            return json.loads(json.dumps(outer.gate_result))

        module.gate = gate
        self._swap_gate(module)

    def _swap_gate(self, module):
        package, name = GATE_MODULE.rsplit(".", 1)
        self.addCleanup(self._restore_gate, package, name)
        self._previous = (package, name, sys.modules.get(name), sys.modules[name] if name in sys.modules else None)
        sys.modules[name] = module
        setattr(sys.modules[package], name, module)

    def _restore_gate(self, package, name):
        sys.modules.pop(name, None)
        import importlib
        holder = importlib.import_module(package)
        if self._previous[2] is not None:
            sys.modules[name] = self._previous[2]
            setattr(holder, name, self._previous[2])
        elif hasattr(holder, name):
            delattr(holder, name)

    def gate_fails(self, ok=False):
        self.gate_result = {"schema": "openspoke-build-gate-1", "ok": ok,
                            "steps": [{"name": "compile", "ok": ok, "returncode": 1 if not ok else 0}],
                            "packages": {SRC_PACKAGE: {"ok": ok}}}

    def gate_raises(self):
        self.gate_error = RuntimeError("compiler exploded")

    def stage_package(self, package=PACKAGE, stem=STEM, va=BARE, src_package=None,
                      header=True, test=True, namespace=True, extra_files=None,
                      metadata=True, report=True, static="PASS", runtime="GATED",
                      index=True, evidence=True, stem_files=None):
        """Write one staging package plus the evidence a promotion reads."""
        package = package
        src_package = src_package or package.replace("-", "_").lower()
        directory = self.root / "reconstruction/staging" / package
        directory.mkdir(parents=True, exist_ok=True)
        body = {"package": package, "stem": stem, "package_underscored": src_package}
        if header:
            self._write(directory / (stem + ".hpp"), self._header_text(stem, src_package, namespace))
        if test:
            self._write(directory / (stem + "_model_test.cpp"),
                        self._test_text(stem, src_package, namespace))
        self._write(directory / (stem + ".cpp"), self._source_text(stem, src_package, namespace))
        for name, text in (extra_files or {}).items():
            self._write(directory / name, text)
        for name, text in (stem_files or {}).items():
            self._write(directory / name, text)
        if metadata:
            self._write(self.root / "reconstruction/metadata" / package / (va + ".json"),
                        json.dumps({"va": "0x" + va, "package": package,
                                    "normalized_symbol": "App::PropertyList::RemoveProperty"}))
        if evidence:
            self._write(self.root / "reconstruction/evidence" / va / "evidence.json",
                        json.dumps({"schema": "openspore-evidence-1", "target": "0x" + va,
                                    "binary": {"sha256": "b" * 64}}))
        if report:
            self.write_validation(va, package=package, stem=stem, static=static, runtime=runtime)
        if index:
            self.write_index(va, src_package)
        return {"package": package, "src_package": src_package, "stem": stem, "va": va}

    def _source_text(self, stem, src_package, namespace):
        return SOURCE % {"stem": stem, "package": src_package if namespace else "legacy_wave"}

    def _header_text(self, stem, src_package, namespace):
        return HEADER % {"package": src_package if namespace else "legacy_wave"}

    def _test_text(self, stem, src_package, namespace):
        return TEST_SOURCE % {"stem": stem, "package": src_package if namespace else "legacy_wave"}

    def write_validation(self, va, package, stem, static="PASS", runtime="GATED", source_path=None,
                         sha256="keep", schema="openspore-structural-validation-1"):
        path = self.root / "reconstruction/evidence" / va / "validation.json"
        if source_path is None:
            source_path = "reconstruction/staging/%s/%s.cpp" % (package, stem)
        if sha256 == "keep":
            sha256 = _digest(self.root / source_path)
        runtime_block = {"dimension": "RUNTIME", "status": runtime, "gated": runtime == "GATED",
                         "gates": [], "reason": "no original-process trace exists in this repository",
                         "validated": 0}
        report = {
            "schema": schema,
            "target": "0x" + va,
            "status": static,
            "source": {"path": source_path, "role": "staging", "sha256": sha256},
            "static": {"dimension": "STATIC", "status": static, "checks": {}},
            "runtime": runtime_block,
        }
        if static is None:
            del report["static"]
        self._write(path, json.dumps(report, indent=2, sort_keys=True) + "\n")
        return path

    def write_index(self, va, src_package):
        path = self.root / "reconstruction/knowledge/index.json"
        document = {"schema": "openspore-knowledge-index-1", "records": {}}
        if path.exists():
            document = json.loads(path.read_text(encoding="utf-8"))
        document["records"]["0x" + va] = {
            "va": "0x" + va,
            "normalized_symbol": "App::PropertyList::RemoveProperty",
            "subsystem": "App.PropertyList",
            "abi": {"calling_convention": "__thiscall", "return_type": "int",
                    "stack_cleanup_bytes": 4, "architecture": "x86-32"},
        }
        self._write(path, json.dumps(document, indent=2, sort_keys=True) + "\n")

    def _write(self, path, text):
        path = Path(path)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")

    def codes(self, plan_document, package=None):
        return sorted(item["code"] for candidate in plan_document["candidates"]
                      if package is None or candidate["package"] == package
                      for item in candidate["blockers"])

    def promoted_dir(self, package=SRC_PACKAGE):
        return self.root / "src/reconstruction" / package


class RefusalTest(PromotionFixture):
    """A refusal is a machine-readable reason, never a silent absence."""

    def test_no_test_refused(self):
        self.stage_package(test=False)
        plan_document = promote.plan(self.root)
        self.assertIn("no_test", self.codes(plan_document))
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assertFalse(self.promoted_dir().exists())
        self.assertEqual(self.gate_calls, [])

    def test_static_not_pass_refused_for_every_non_pass_ladder(self):
        for status in ("WARN", "NOT_AVAILABLE", "PARTIAL", "UNKNOWN", "FAIL", None):
            with self.subTest(static=status):
                self.setUp()
                self.stage_package(static=status)
                plan_document = promote.plan(self.root)
                self.assertIn("static_not_pass", self.codes(plan_document))
                result = promote.apply(self.root)
                self.assertEqual(result["status"], "blocked")
                self.assertFalse(self.promoted_dir().exists())

    def test_runtime_not_gated_refused(self):
        for status in ("PASS", "FAIL", "NOT_AVAILABLE", "UNKNOWN", None):
            with self.subTest(runtime=status):
                self.setUp()
                self.stage_package(runtime=status)
                document = promote.plan(self.root)
                self.assertIn("runtime_not_gated", self.codes(document))
                self.assertEqual(document["candidates"][0]["runtime_status"], status)
                self.assertEqual(document["candidates"][0]["static_status"], "PASS")
                result = promote.apply(self.root)
                self.assertEqual(result["status"], "blocked")
                self.assertFalse(self.promoted_dir().exists())

    def test_validation_report_missing_refused(self):
        self.stage_package(report=False)
        plan_document = promote.plan(self.root, package=PACKAGE)
        self.assertIn("validation_report_missing", self.codes(plan_document))
        result = promote.apply(self.root, package=PACKAGE)
        self.assertEqual(result["status"], "blocked")
        self.assertFalse(self.promoted_dir().exists())

    def test_validation_stale_refused_after_source_is_edited(self):
        self.stage_package()
        self.assertEqual(self.codes(promote.plan(self.root)), [])
        source = self.root / "reconstruction/staging" / PACKAGE / (STEM + ".cpp")
        source.write_text(source.read_text(encoding="utf-8") + "\n// late edit\n", encoding="utf-8")
        self.assertIn("validation_stale", self.codes(promote.plan(self.root)))
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assertIn("validation_stale", [item["code"] for entry in result["refused"]
                                           for item in entry["blockers"]])
        self.assertFalse(self.promoted_dir().exists())

    def test_unreadable_validation_report_refused(self):
        self.stage_package()
        path = self.root / "reconstruction/evidence" / BARE / "validation.json"
        path.write_text("{not json", encoding="utf-8")
        self.assertIn("validation_unreadable", self.codes(promote.plan(self.root)))

    def test_unsupported_validation_schema_refused(self):
        self.stage_package()
        self.write_validation(BARE, package=PACKAGE, stem=STEM, schema="openspore-structural-validation-0")
        self.assertIn("validation_schema_unsupported", self.codes(promote.plan(self.root)))

    def test_no_metadata_record_refused(self):
        self.stage_package(metadata=False)
        self.assertIn("no_metadata_record", self.codes(promote.plan(self.root)))

    def test_no_header_refused(self):
        self.stage_package(header=False)
        self.assertIn("no_header", self.codes(promote.plan(self.root)))

    def test_namespace_mismatch_refused(self):
        self.stage_package(namespace=False)
        self.assertIn("namespace_mismatch", self.codes(promote.plan(self.root)))

    def test_namespace_close_comment_is_not_a_declaration(self):
        self.stage_package()
        self._write(self.root / "reconstruction/staging" / PACKAGE / (STEM + ".hpp"),
                    "namespace openspore {\nint unrelated;\n}  // namespace openspore::reconstruction::%s\n" % SRC_PACKAGE)
        self._write(self.root / "reconstruction/staging" / PACKAGE / (STEM + ".cpp"),
                    "namespace legacy_wave {\nint unrelated;\n}\n")
        self._write(self.root / "reconstruction/staging" / PACKAGE / (STEM + "_model_test.cpp"),
                    "int main() { return 0; }\n")
        self.assertIn("namespace_mismatch", self.codes(promote.plan(self.root)))

    def test_expanded_namespace_brace_form_accepted(self):
        self.stage_package(namespace=False)
        staged = self.root / "reconstruction/staging" / PACKAGE
        for name in os.listdir(staged):
            self._write(staged / name, "namespace openspore {\nnamespace reconstruction {\n"
                                       "namespace %s {\nint f();\n}  // namespace %s\n}  // namespace reconstruction\n"
                                       "}  // namespace openspore\n" % (SRC_PACKAGE, SRC_PACKAGE))
        self.assertNotIn("namespace_mismatch", self.codes(promote.plan(self.root)))

    def test_binary_content_refused(self):
        self.stage_package()
        source = self.root / "reconstruction/staging" / PACKAGE / (STEM + ".cpp")
        self.write_validation(BARE, package=PACKAGE, stem=STEM)
        source.write_bytes(b"\x00\x01\x02binary blob")
        self.assertIn("binary_content", self.codes(promote.plan(self.root)))

    def test_plan_refuses_a_package_with_no_evidence_at_all(self):
        self.stage_package(report=False, metadata=False)
        state = promote.package_state(self.root, SRC_PACKAGE)
        self.assertFalse(state["promoted"])
        codes = sorted(item["code"] for target in state["targets"] for item in target["blockers"])
        self.assertIn("validation_report_missing", codes)
        self.assertIn("no_metadata_record", codes)

    def test_blocker_codes_are_declared(self):
        for code in ("validation_report_missing", "static_not_pass", "runtime_not_gated",
                     "validation_stale", "source_missing", "no_header", "no_test",
                     "duplicate_va", "no_metadata_record", "namespace_mismatch",
                     "drifted_existing", "would_drop_files", "binary_content"):
            self.assertIn(code, promote.BLOCKERS)


class DuplicateVaTest(PromotionFixture):
    """One VA, one owning package."""

    def test_two_staging_packages_claiming_one_va(self):
        self.stage_package()
        self.stage_package(package="pkg-property-wave9", stem="property_wave9", va=BARE,
                           src_package="pkg_property_wave9", index=False)
        codes = self.codes(promote.plan(self.root))
        self.assertIn("duplicate_va", codes)
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assertFalse(self.promoted_dir().exists())
        self.assertFalse(self.promoted_dir("pkg_property_wave9").exists())

    def test_duplicate_va_detected_from_a_staged_filename(self):
        self.stage_package()
        self.stage_package(package="pkg-property-safe-wave9", stem="property_safe_wave9",
                           va="006a2ef1", src_package="pkg_property_safe_wave9", index=False,
                           stem_files={"property_list_clear_006a2ef0.cpp": "// a copy\n"})
        codes = self.codes(promote.plan(self.root))
        self.assertIn("duplicate_va", codes)

    def test_va_already_promoted_by_another_package(self):
        self.stage_package()
        self.assertEqual(promote.apply(self.root)["status"], "ok")
        # A second package stages the same VA and validates it too.
        self.stage_package(package="pkg-property-remove-alt", stem="property_remove_alt",
                           va=BARE, src_package="pkg_property_remove_alt")
        codes = self.codes(promote.plan(self.root, package="pkg-property-remove-alt"))
        self.assertIn("duplicate_va", codes)
        result = promote.apply(self.root, package="pkg-property-remove-alt")
        self.assertEqual(result["status"], "blocked")
        self.assertFalse(self.promoted_dir("pkg_property_remove_alt").exists())
        # The original package is untouched by the refused sibling.
        self.assertEqual(promote.promoted_packages(self.root), [SRC_PACKAGE])

    def test_repating_the_same_package_is_not_a_duplicate(self):
        self.stage_package()
        self.assertEqual(promote.apply(self.root)["status"], "ok")
        second = promote.apply(self.root)
        self.assertEqual(second["status"], "ok")
        self.assertEqual(second["promoted"], [])
        self.assertEqual(second["already_promoted"], ["0x" + BARE])


class InstalledTreeTest(PromotionFixture):
    """Existing trees are adopted, refused, or replaced -- never silently."""

    def test_identical_tree_without_a_marker_is_completed(self):
        self.stage_package()
        installed = self.promoted_dir()
        installed.mkdir(parents=True)
        for name in os.listdir(self.root / "reconstruction/staging" / PACKAGE):
            shutil.copyfile(self.root / "reconstruction/staging" / PACKAGE / name, installed / name)
        self.assertEqual(self.codes(promote.plan(self.root)), [])
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "ok")
        self.assertEqual(result["promoted"], ["0x" + BARE])
        self.assertTrue((installed / "promotion.json").is_file())
        self.assertEqual(promote.promoted_packages(self.root), [SRC_PACKAGE])

    def test_unmarked_tree_is_invisible_to_discovery(self):
        self.stage_package()
        installed = self.promoted_dir()
        installed.mkdir(parents=True)
        self._write(installed / (STEM + ".cpp"), "// interrupted\n")
        self.assertEqual(promote.promoted_packages(self.root), [])
        self.assertFalse(promote.package_state(self.root, SRC_PACKAGE)["promoted"])

    def test_drifted_existing_refused_without_overwrite(self):
        self.stage_package()
        installed = self.promoted_dir()
        installed.mkdir(parents=True)
        for name in os.listdir(self.root / "reconstruction/staging" / PACKAGE):
            shutil.copyfile(self.root / "reconstruction/staging" / PACKAGE / name, installed / name)
        self._write(installed / (STEM + ".cpp"), "// an agent edited this\n")
        self.assertIn("drifted_existing", self.codes(promote.plan(self.root)))
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assertIn("// an agent edited this", (installed / (STEM + ".cpp")).read_text(encoding="utf-8"))

    def test_overwrite_replaces_and_records_what_it_dropped(self):
        self.stage_package()
        installed = self.promoted_dir()
        installed.mkdir(parents=True)
        self._write(installed / "stale_wave.cpp", "// not in staging\n")
        self._write(installed / (STEM + ".cpp"), "// an agent edited this\n")
        self.assertIn("drifted_existing", self.codes(promote.plan(self.root)))
        self.assertIn("would_drop_files", self.codes(promote.plan(self.root)))
        result = promote.apply(self.root, overwrite=True)
        self.assertEqual(result["status"], "ok")
        self.assertEqual(result["overwritten"][SRC_PACKAGE], ["stale_wave.cpp"])
        self.assertFalse((installed / "stale_wave.cpp").exists())
        self.assertEqual(_digest(installed / (STEM + ".cpp")),
                         _digest(self.root / "reconstruction/staging" / PACKAGE / (STEM + ".cpp")))

    def test_drifted_existing_is_only_cleared_by_apply(self):
        self.stage_package()
        installed = self.promoted_dir()
        installed.mkdir(parents=True)
        self._write(installed / (STEM + ".cpp"), "// an agent edited this\n")
        self.assertIn("drifted_existing", self.codes(promote.plan(self.root, package=PACKAGE)))
        result = promote.apply(self.root, overwrite=True)
        self.assertEqual(result["status"], "ok")
        self.assertNotIn("drifted_existing", self.codes(promote.plan(self.root, package=PACKAGE)))


class SuccessPathTest(PromotionFixture):
    """The green path, end to end, on a gated compile."""

    def test_promotion_writes_the_contract_shape(self):
        self.stage_package()
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "ok")
        self.assertTrue(result["changed"])
        self.assertFalse(result["idempotent"])
        self.assertEqual(result["promoted"], ["0x" + BARE])
        self.assertEqual(result["summary"]["refused"], 0)
        self.assertEqual(len(self.gate_calls), 1)
        self.assertEqual(self.gate_calls[0]["packages"], [SRC_PACKAGE])
        # The gate must have run outside src/ so a failure cannot half-install.
        self.assertNotIn(str(self.promoted_dir()), self.gate_calls[0]["root"])
        self.assertFalse((self.promoted_dir() / "promotion.json").exists() and False)

        marker = json.loads((self.promoted_dir() / "promotion.json").read_text(encoding="utf-8"))
        self.assertEqual(marker["schema"], "openspore-promotion-1")
        self.assertEqual(marker["package"], PACKAGE)
        self.assertEqual(marker["src_package"], SRC_PACKAGE)
        self.assertEqual(marker["namespace"], "openspore::reconstruction::" + SRC_PACKAGE)
        self.assertEqual(len(marker["targets"]), 1)
        target = marker["targets"][0]
        self.assertEqual(target["va"], "0x" + BARE)
        self.assertEqual(target["bare_va"], BARE)
        self.assertEqual(target["symbol"], "App::PropertyList::RemoveProperty")
        self.assertEqual(target["subsystem"], "App.PropertyList")
        self.assertEqual(target["sources"], [STEM + ".cpp"])
        self.assertEqual(target["headers"], [STEM + ".hpp"])
        self.assertEqual(target["tests"], [STEM + "_model_test.cpp"])
        self.assertEqual(target["staging_dir"], "reconstruction/staging/" + PACKAGE)
        self.assertEqual(target["staging_sha256"][STEM + ".cpp"],
                         _digest(self.root / "reconstruction/staging" / PACKAGE / (STEM + ".cpp")))
        self.assertEqual(target["metadata"], "reconstruction/metadata/%s/%s.json" % (PACKAGE, BARE))
        self.assertEqual(target["metadata_sha256"],
                         _digest(self.root / "reconstruction/metadata" / PACKAGE / (BARE + ".json")))
        self.assertEqual(target["validation"], "reconstruction/evidence/%s/validation.json" % BARE)
        self.assertEqual(target["validation_sha256"],
                         _digest(self.root / "reconstruction/evidence" / BARE / "validation.json"))
        self.assertEqual(target["evidence"], "reconstruction/evidence/%s/evidence.json" % BARE)
        self.assertEqual(target["evidence_sha256"],
                         _digest(self.root / "reconstruction/evidence" / BARE / "evidence.json"))
        self.assertEqual(target["static_status"], "PASS")
        self.assertEqual(target["runtime_status"], "GATED")
        self.assertEqual(target["binary_sha256"], "b" * 64)
        self.assertEqual(target["abi"], {"calling_convention": "__thiscall",
                                         "return_type": "int", "stack_cleanup_bytes": 4})

    def test_only_source_suffixes_are_copied(self):
        self.stage_package(extra_files={"build.sh": "#!/bin/sh\n", "notes.json": "{}\n",
                                        "helper.py": "print(1)\n"})
        self.assertEqual(promote.apply(self.root)["status"], "ok")
        installed = sorted(os.listdir(self.promoted_dir()))
        self.assertEqual(installed, sorted([STEM + ".cpp", STEM + ".hpp",
                                            STEM + "_model_test.cpp", "promotion.json"]))
        for name in ("build.sh", "notes.json", "helper.py"):
            self.assertFalse((self.promoted_dir() / name).exists())

    def test_provenance_record_is_written(self):
        self.stage_package()
        promote.apply(self.root)
        record = json.loads((self.root / "reconstruction/evidence" / BARE / "promotion.json")
                            .read_text(encoding="utf-8"))
        self.assertEqual(record["schema"], "openspore-promotion-record-1")
        self.assertEqual(record["va"], "0x" + BARE)
        self.assertEqual(record["package"], PACKAGE)
        self.assertEqual(record["static_status"], "PASS")
        self.assertEqual(record["runtime_status"], "GATED")
        self.assertTrue(record["promoted_on"])
        self.assertIsNone(record["supersedes"])
        self.assertTrue(record["build"]["ok"])
        self.assertIn("reconstruction/evidence/%s/validation.json" % BARE, record["provenance"])
        self.assertIn("reconstruction/staging/" + PACKAGE, record["provenance"])

    def test_idempotent_rerun_writes_nothing(self):
        self.stage_package()
        promote.apply(self.root)
        self.gate_calls = []
        before = _tree_digest(self.root / "src")
        second = promote.apply(self.root)
        self.assertTrue(second["idempotent"])
        self.assertFalse(second["changed"])
        self.assertEqual(second["already_promoted"], ["0x" + BARE])
        self.assertEqual(second["promoted"], [])
        self.assertEqual(self.gate_calls, [])
        self.assertEqual(before, _tree_digest(self.root / "src"))
        # The gate result is returned from the record, not recomputed.
        self.assertEqual(second["build"], promote._merge_build({SRC_PACKAGE: self.gate_result}))

    def test_rebuild_opt_in_reruns_the_gate(self):
        self.stage_package()
        promote.apply(self.root)
        self.gate_calls = []
        result = promote.apply(self.root, rebuild=True)
        self.assertEqual(len(self.gate_calls), 1)
        self.assertTrue(result["changed"])
        self.assertFalse(result["idempotent"])
        self.assertEqual(result["promoted"], ["0x" + BARE])

    def test_package_filter_accepts_either_spelling(self):
        self.stage_package()
        for name in (PACKAGE, SRC_PACKAGE):
            state = promote.package_state(self.root, name)
            self.assertEqual(state["package"], PACKAGE)
            self.assertEqual(state["src_package"], SRC_PACKAGE)
            self.assertTrue(state["exists"])
            self.assertFalse(state["promoted"])
            self.assertEqual(len(state["targets"]), 1)
            self.assertEqual(self.codes(promote.plan(self.root, package=name)), [])
        self.assertEqual(len(promote.plan(self.root, va=VA)["candidates"]), 1)
        self.assertEqual(len(promote.plan(self.root, va=BARE)["candidates"]), 1)
        self.assertEqual(len(promote.plan(self.root, va="0x6a2ef0")["candidates"]), 1)

    def test_two_targets_in_one_package_promote_together(self):
        self.stage_package()
        second = self.root / "reconstruction/staging" / PACKAGE / "property_second_006a2ef4.cpp"
        self._write(second, SOURCE % {"stem": STEM, "package": SRC_PACKAGE})
        self._write(self.root / "reconstruction/metadata" / PACKAGE / "006a2ef4.json",
                    json.dumps({"va": "0x006a2ef4", "package": PACKAGE}))
        self._write(self.root / "reconstruction/evidence" / "006a2ef4" / "evidence.json",
                    json.dumps({"schema": "openspore-evidence-1", "binary": {"sha256": "c" * 64}}))
        self.write_validation("006a2ef4", package=PACKAGE, stem="property_second_006a2ef4")
        self.write_index("006a2ef4", SRC_PACKAGE)
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "ok")
        self.assertEqual(len(self.gate_calls), 1)
        marker = json.loads((self.promoted_dir() / "promotion.json").read_text(encoding="utf-8"))
        self.assertEqual([target["bare_va"] for target in marker["targets"]], [BARE, "006a2ef4"])

    def test_one_refused_va_refuses_its_package(self):
        self.stage_package()
        self._write(self.root / "reconstruction/metadata" / PACKAGE / "006a2ef4.json",
                    json.dumps({"va": "0x006a2ef4", "package": PACKAGE}))
        self.write_validation("006a2ef4", package=PACKAGE, stem=STEM, static="WARN")
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assertFalse(self.promoted_dir().exists())
        refused = {entry["va"]: [item["code"] for item in entry["blockers"]]
                   for entry in result["refused"]}
        self.assertIn("static_not_pass", refused["0x006a2ef4"])
        self.assertIn("sibling_refused", refused["0x" + BARE])

    def test_gate_is_skipped_when_both_switches_are_off(self):
        self.stage_package()
        result = promote.apply(self.root, build=False, ctest=False)
        self.assertEqual(result["status"], "ok")
        self.assertEqual(self.gate_calls, [])
        self.assertTrue(result["build"]["ok"])


class BuildGateTest(PromotionFixture):
    """A red or missing gate must leave src/ exactly as it was."""

    def test_compile_failure_never_promotes(self):
        self.stage_package()
        self.gate_fails(ok=False)
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assertFalse(self.promoted_dir().exists())
        self.assertEqual(result["build"]["ok"], False)
        self.assertFalse((self.root / "reconstruction/evidence" / BARE / "promotion.json").exists())
        self.assertFalse((self.promoted_dir() / "promotion.json").exists())

    def test_failure_after_an_earlier_package_left_no_partial_tree(self):
        self.stage_package()
        before = _tree_digest(self.root / "src")
        self.gate_fails(ok=False)
        promote.apply(self.root)
        self.assertEqual(before, _tree_digest(self.root / "src"))
        self.assertFalse((self.root / "src/reconstruction" / ".promote-tmp").exists()
                         and any((self.root / "src/reconstruction" / ".promote-tmp").iterdir()))

    def test_raising_gate_writes_nothing(self):
        self.stage_package()
        before = _tree_digest(self.root)
        self.gate_raises()
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "error")
        self.assertEqual(result["code"], "promotion_failed")
        self.assertFalse(self.promoted_dir().exists())
        self.assertEqual(before, _tree_digest(self.root))

    def test_unavailable_gate_is_an_error_not_a_promotion(self):
        self.stage_package()
        original = promote._gate

        def missing(*args, **kwargs):
            raise ImportError("build_gate is unavailable: no such module")

        promote._gate = missing
        self.addCleanup(setattr, promote, "_gate", original)
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "error")
        self.assertEqual(result["code"], "build_gate_unavailable")
        self.assertFalse(self.promoted_dir().exists())
        self.assertFalse((self.root / "reconstruction/evidence" / BARE / "promotion.json").exists())
        # The scratch tree is gone even on the error path, so a retry starts clean.
        self.assertEqual(sorted(os.listdir(self.root / "src/reconstruction")), [])

    def test_gate_module_without_a_gate_entry_point_is_an_error(self):
        self.stage_package()
        module = types.ModuleType(GATE_MODULE)
        self._swap_gate(module)
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "error")
        self.assertEqual(result["code"], "build_gate_unavailable")
        self.assertFalse(self.promoted_dir().exists())
        # plan() must keep working while the other agent is mid-flight.
        self.assertEqual(self.codes(promote.plan(self.root)), [])


class DeterminismTest(PromotionFixture):
    """The same inputs produce the same bytes, and plan touches nothing."""

    def test_two_roots_produce_identical_markers(self):
        digests = []
        for _ in range(2):
            self.setUp()
            self.stage_package()
            promote.apply(self.root)
            digests.append((self.promoted_dir() / "promotion.json").read_bytes())
        self.assertEqual(digests[0], digests[1])

    def test_marker_has_no_wall_clock_or_absolute_path(self):
        self.stage_package()
        promote.apply(self.root)
        text = (self.promoted_dir() / "promotion.json").read_text(encoding="utf-8")
        self.assertNotIn(str(self.root), text)
        self.assertNotIn("promoted_on", text)
        self.assertNotIn("202", text.replace("006a2ef0", ""))
        self.assertNotIn(str(os.getpid()), text)

    def test_plan_writes_nothing(self):
        self.stage_package()
        before = _tree_digest(self.root)
        promote.plan(self.root)
        promote.plan(self.root, package=PACKAGE)
        promote.plan(self.root, va=VA)
        promote.promoted_packages(self.root)
        promote.package_state(self.root, PACKAGE)
        self.assertEqual(before, _tree_digest(self.root))

    def test_plan_is_stable_across_calls(self):
        self.stage_package()
        self.assertEqual(promote.plan(self.root), promote.plan(self.root))

    def test_runtime_never_leaks_into_a_promotion(self):
        self.stage_package()
        promote.apply(self.root)
        marker = json.loads((self.promoted_dir() / "promotion.json").read_text(encoding="utf-8"))
        self.assertEqual(marker["targets"][0]["runtime_status"], "GATED")
        self.assertEqual(marker["targets"][0]["runtime_validation"]["status"], "GATED")
        record = json.loads((self.root / "reconstruction/evidence" / BARE / "promotion.json")
                            .read_text(encoding="utf-8"))
        self.assertEqual(record["runtime_status"], "GATED")
        self.assertNotIn("runtime_validated", json.dumps(marker))
        for text in ((self.promoted_dir() / "promotion.json").read_text(encoding="utf-8"),
                     (self.root / "reconstruction/evidence" / BARE / "promotion.json").read_text(encoding="utf-8")):
            self.assertNotIn('"runtime_status": "PASS"', text)

    def test_inputs_changed_refuses_and_writes_nothing(self):
        self.stage_package()
        staging = self.root / "reconstruction/staging" / PACKAGE / (STEM + ".cpp")
        original = promote._load_candidates

        def moved(root, package=None, va=None, overwrite=False):
            candidates = original(root, package=package, va=va, overwrite=overwrite)
            # The plan is now taken; move the source under it.
            staging.write_text(staging.read_text(encoding="utf-8") + "\n// moved\n", encoding="utf-8")
            return candidates

        promote._load_candidates = moved
        self.addCleanup(setattr, promote, "_load_candidates", original)
        result = promote.apply(self.root)
        self.assertEqual(result["status"], "blocked")
        self.assertFalse(self.promoted_dir().exists())
        self.assertEqual(self.gate_calls, [])
        codes = [item["code"] for entry in result["refused"] for item in entry["blockers"]]
        self.assertIn("inputs_changed", codes)


class RealGateTest(PromotionFixture):
    """One end-to-end pass through the shipped build gate.

    Skipped unless cmake, clang++ and the gate itself are present: the rest of
    this suite stubs the gate so it stays hermetic, but a promotion is only
    real if the repository's own reconstruction CMakeLists can discover the
    marker this module writes and run the model test green.
    """

    @unittest.skipUnless(shutil.which("cmake") and shutil.which("clang++"),
                         "cmake and clang++ are required for the real build gate")
    def test_promotion_survives_a_real_compile_and_test(self):
        entry = Path(__file__).resolve().parents[1] / "src/reconstruction/CMakeLists.txt"
        if not entry.is_file():
            self.skipTest("the repository has no src/reconstruction/CMakeLists.txt")
        self._use_real_gate()
        shutil.copyfile(entry, self.root / "src/reconstruction/CMakeLists.txt")
        self.stage_package()
        result = promote.apply(self.root, jobs=2)
        self.assertEqual(result["status"], "ok", result.get("detail"))
        self.assertTrue(result["build"]["ok"])
        self.assertEqual([step["name"] for step in result["build"]["steps"]],
                         ["m32_probe", "configure", "build", "ctest"])
        self.assertEqual(result["build"]["packages"][SRC_PACKAGE]["status"], "ok")
        self.assertEqual(result["promoted"], ["0x" + BARE])
        self.assertEqual(sorted(p.name for p in self.promoted_dir().iterdir()),
                         ["promotion.json", STEM + ".cpp", STEM + ".hpp",
                          STEM + "_model_test.cpp"])
        again = promote.apply(self.root)
        self.assertTrue(again["idempotent"])
        self.assertEqual(again["already_promoted"], ["0x" + BARE])

    def _use_real_gate(self):
        package, name = GATE_MODULE.rsplit(".", 1)
        self.addCleanup(self._restore_gate, package, name)
        self._previous = (package, name, sys.modules.get(name), sys.modules.get(name))
        sys.modules.pop(name, None)
        if hasattr(sys.modules[package], name):
            delattr(sys.modules[package], name)



# --------------------------------------------------------------------------
# ``promote --va`` must hand the planner a scalar.
#
# Regression lock: ``argparse``'s ``action="append"`` produced a list, the CLI
# forwarded it verbatim, and ``promote._load_candidates`` -> ``_bare`` ->
# ``normalize_va`` then raised ``invalid VA: ['0x00901930']`` before any plan was
# built. Every ``promote plan|apply --va`` in the repo was therefore unusable.
# The programmatic API is scalar already and is left alone; only the CLI's own
# list is unwrapped.
# --------------------------------------------------------------------------
class PromoteVaScalarHandling(unittest.TestCase):

    def _args(self, vas):
        return types.SimpleNamespace(vas=vas)

    def test_no_va_stays_none(self):
        from tools.reconstruction_tooling.cli import _one_va
        self.assertIsNone(_one_va(None, "promote"))
        self.assertIsNone(_one_va([], "promote"))

    def test_a_single_va_is_unwrapped_to_a_scalar(self):
        from tools.reconstruction_tooling.cli import _one_va
        self.assertEqual(_one_va(["0x00901930"], "promote"), "0x00901930")

    def test_a_bare_scalar_is_passed_through_unchanged(self):
        from tools.reconstruction_tooling.cli import _one_va
        self.assertEqual(_one_va("0x00901930", "promote"), "0x00901930")

    def test_several_addresses_are_refused_rather_than_silently_reduced(self):
        from tools.reconstruction_tooling.cli import _one_va
        from tools.reconstruction_tooling.models import ToolError
        with self.assertRaises(ToolError) as caught:
            _one_va(["0x00901930", "0x006a2ef0"], "promote")
        self.assertEqual(caught.exception.code, "unsupported_option")
        self.assertIn("one address", caught.exception.message)

    def test_the_value_the_cli_passes_normalises(self):
        # The end-to-end shape of the defect: a one-element argparse list used to
        # reach normalize_va() as a list and blow up. A scalar must survive it.
        from tools.reconstruction_tooling.cli import _one_va
        from tools.reconstruction_tooling.models import normalize_va
        self.assertEqual(normalize_va(_one_va(["0x00901930"], "promote"))[2:], "00901930")

    def test_the_dispatch_hands_the_planner_a_scalar_not_the_argparse_list(self):
        # The defect was not in _one_va but in what the CLI forwarded, so this
        # drives the real _promote() dispatch and inspects what the planner was
        # actually called with. Reverting the CLI to pass args.vas straight
        # through makes the planner receive a list and this fails.
        from tools.reconstruction_tooling import cli
        captured = {}

        def fake_plan(root, package=None, va=None):
            captured["va"] = va
            return {"schema": "openspore-promotion-plan-1", "candidates": []}

        original = cli.promote_plan
        cli.promote_plan = fake_plan
        try:
            args = types.SimpleNamespace(
                action="plan", package="pkg_fixture", vas=["0x00901930"],
                out=None, no_write=False, overwrite=False, no_build=False,
                no_ctest=False, rebuild=False)
            cli._promote(args)
        finally:
            cli.promote_plan = original

        self.assertIsInstance(captured["va"], str,
                              "the planner is scalar-typed; a list here is the defect")
        self.assertEqual(captured["va"], "0x00901930")
        # And the value the planner receives must survive normalize_va().
        from tools.reconstruction_tooling.models import normalize_va
        self.assertEqual(normalize_va(captured["va"])[2:], "00901930")

    def test_the_real_argparse_shape_reaches_the_planner_as_a_scalar(self):
        # Same dispatch, but with the namespace argparse itself produces for a
        # repeatable --va, so the test cannot drift from the real flag contract.
        from tools.reconstruction_tooling import cli
        captured = {}

        def fake_plan(root, package=None, va=None):
            captured["va"] = va
            return {"schema": "openspore-promotion-plan-1", "candidates": []}

        original = cli.promote_plan
        cli.promote_plan = fake_plan
        try:
            parsed = cli._parser().parse_args(
                ["promote", "plan", "pkg_fixture", "--va", "0x00901930"])
            self.assertEqual(parsed.vas, ["0x00901930"], "argparse yields a list")
            cli._promote(parsed)
        finally:
            cli.promote_plan = original
        self.assertEqual(captured["va"], "0x00901930")

    def test_the_programmatic_api_still_takes_a_scalar(self):
        # promote.plan/apply are unchanged: they take one address, not a list.
        import inspect
        for function in (promote.plan, promote.apply):
            parameter = inspect.signature(function).parameters["va"]
            self.assertIsNone(parameter.default, function.__name__)
        # And the planner narrows on a single address, which is why the CLI
        # refuses more than one rather than picking a winner.
        source = inspect.getsource(promote._load_candidates)
        self.assertIn("wanted_va", source)


if __name__ == "__main__":
    unittest.main()
