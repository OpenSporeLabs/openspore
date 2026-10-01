"""Compile-and-test driver for promoted reconstruction packages.

This module is the machine-readable half of the promotion gate. ``promote.py``
imports :func:`gate` and records its verdict; nothing here writes inside the
repository tree, reads a clock, or produces a timestamp.

Why the driver exists
---------------------
The reconstructed units are x86-32 C++ that uses
``__attribute__((thiscall))``. Both clang and gcc accept that attribute in a
64-bit translation unit and then emit a diagnostic for it, so under the
repository's ``-Werror`` policy the units fail to compile. Passing ``-m32`` to
*the promoted targets* (``target_compile_options``/``target_link_options`` in
``src/reconstruction/CMakeLists.txt``) keeps the surrounding 64-bit project
intact and still produces a runnable 32-bit test binary.

That leaves the one failure mode this module exists to make impossible: a
``-m32`` that was silently dropped. If the flag never reached the compiler, a
``__thiscall`` package would be judged on 64-bit object code and the gate would
report green for a binary that was never valid. So every gate run first
compiles a probe translation unit and asserts the asymmetry that makes ``-m32``
meaningful at all:

* without ``-m32`` the ``__thiscall`` attribute is rejected (exit non-zero);
* with ``-m32`` the same translation unit compiles (exit zero).

If that asymmetry does not hold, :func:`gate` returns ``ok: False`` with a step
named ``m32_probe`` and does not spend a build on it.

Determinism
-----------
The claim is deliberately narrower than "the whole dict is reproducible",
because the captured output is a verbatim record and a verbatim record of a
parallel build is not order-stable:

* **The structured fields are deterministic at any ``-j``.** ``schema``,
  ``ok``, ``cxx``, ``m32``, ``tests``, ``packages`` and each step's
  ``name``/``ok``/``returncode`` are equal across runs on identical inputs at
  ``jobs=1`` and at ``jobs=8`` alike. Nothing time-dependent appears: no wall
  clock, no duration, no pid, no address. ctest's per-test ``0.01 sec``
  timings are scrubbed from captured text, and its rows are sorted by name so
  that neither a different ctest version nor an inherited
  ``CTEST_PARALLEL_LEVEL`` can reorder them. The two environment variables that
  would otherwise make a nominal ``jobs=1`` run parallel --
  ``MAKEFLAGS``/``MFLAGS`` for make, ``CTEST_PARALLEL_LEVEL`` for ctest -- are
  removed from the subprocess environment.
* **The captured tails are deterministic only at ``jobs=1``.** They are kept
  raw and in order on purpose: a sorted or deduplicated tail would hide which
  unit failed to compile, which is the whole diagnostic value of the field. A
  parallel ``make`` interleaves its progress lines and a parallel ctest
  interleaves its failure output, so at ``-j>1`` the tail is real signal but
  not reproducible. ``TAIL_LINES`` also means the tail is a *window*: the same
  build emits a different window once its output grows past it.
* **Throwaway paths never reach the text.** Every captured stream has the
  build directory and the source directory replaced by ``<build-dir>`` and
  ``<source-dir>``, so a scratch run (whose temp name is random) is comparable
  with another scratch run. Those paths are this module's own artifacts and
  carry no diagnostic signal.
* **Three kinds of field are identity, not output**, and are the only things
  excluded from the comparison above: the top-level ``build_dir``, each step's
  ``command``, and the ``build_dir``/``source_dir`` the configure step reports
  for itself. Every other field, tails included, is equal across two runs at
  ``jobs=1`` even when the two runs used different build directories.

The two flags :func:`configure` forwards
----------------------------------------
``-DCMAKE_CXX_COMPILER`` is pinned rather than inherited: ``g++ -m32`` fails on
promoted packages that use the raw ``__thiscall`` keyword (verified on this
machine), where ``clang++ -m32`` compiles them.

``-DOPENSPORE_RECONSTRUCTION_M32`` is the switch that actually controls the
promoted set. ``-m32`` is *per-target* in ``src/reconstruction/CMakeLists.txt``
(``target_compile_options``/``target_link_options``), so the 32-bit-ness of a
promoted package does not depend on a project-wide ``CMAKE_CXX_FLAGS``: the
surrounding 64-bit targets of the real repository root are untouched. A
project-wide ``-DCMAKE_CXX_FLAGS=-m32`` would instead drag the Vulkan renderer
and the app executables to 32-bit and break them, so this module never sets
``CMAKE_CXX_FLAGS``. With ``m32=False`` the option is explicitly switched OFF,
which turns the reconstruction CMakeLists into a loud warning rather than a
silent 64-bit build of ``thiscall`` code.
"""
import json
import os
import re
import shutil
import subprocess
import tempfile
from pathlib import Path

DEFAULT_CXX = "clang++"
PROMOTION_SCHEMA = "openspore-promotion-1"
RECONSTRUCTION_SUBPATH = ("src", "reconstruction")
# The option that turns the promoted set's per-target -m32 on and off. Never
# CMAKE_CXX_FLAGS: that is project-wide.
M32_OPTION = "OPENSPORE_RECONSTRUCTION_M32"
NAME_RE = re.compile(r"^[A-Za-z0-9_]+$")
# The probe needs -Werror, otherwise a 64-bit compile only *warns* about the
# unsupported calling convention and the probe would not discriminate.
PROBE_FLAGS = ("-Werror", "-Wall", "-Wextra")
TAIL_LINES = 40

PROBE_SOURCE = """
struct ProbeThiscall {
  int field;
  int Read(void) __attribute__((thiscall));
};

int ProbeThiscall_Read(ProbeThiscall *self) {
  return self->field;
}
"""

CTEST_LINE_RE = re.compile(r"^\s*\d+/\d+\s+Test\s+#\d+:\s+(?P<rest>.*?)\s*$")
CTEST_NO_TESTS = "No tests were found"
# Environment variables that would silently make a nominal jobs=1 run parallel
# and reorder its output. MAKEFLAGS is honoured by the make that
# ``cmake --build`` spawns; CTEST_PARALLEL_LEVEL by ctest itself.
MAKE_ENV_DROP = ("MAKEFLAGS", "MFLAGS", "MAKELEVEL")
CTEST_ENV_DROP = ("CTEST_PARALLEL_LEVEL", "CTEST_OUTPUT_ON_FAILURE")
# ctest puts the failure reason *before* the status marker
# ("...Subprocess aborted***Exception:"), so the marker, not the first token,
# is what identifies the status.
CTEST_MARKER_RE = re.compile(
    r"\*{2,3}\s*(Exception|Failed|Timeout|Not Run|Skipped|Passed)")
# ctest prints "0.01 sec" per test and "Total Test time (real) = 0.05 sec".
DURATION_RE = re.compile(r"\b\d+(?:\.\d+)?\s*sec\b")
TOTAL_TIME_RE = re.compile(r"^\s*Total Test time.*$", re.MULTILINE)


def _tail(text):
    # type: (object) -> str
    """Last TAIL_LINES lines of a captured stream, as a string."""
    if not text:
        return ""
    if isinstance(text, bytes):
        text = text.decode("utf-8", "replace")
    return "\n".join(str(text).splitlines()[-TAIL_LINES:])


def _scrub_durations(text):
    # type: (object) -> str
    """Strip ctest timing noise so captured output is reproducible."""
    if not text:
        return ""
    if isinstance(text, bytes):
        text = text.decode("utf-8", "replace")
    text = TOTAL_TIME_RE.sub("Total Test time (real) = <scrubbed> sec", str(text))
    return DURATION_RE.sub("<scrubbed> sec", text)


def _clean_env(dropped):
    # type: (tuple) -> dict
    """A copy of the environment without the variables that reorder output."""
    env = dict(os.environ)
    for name in dropped:
        env.pop(name, None)
    return env


def _scrubber(pairs):
    # type: (tuple) -> object
    """A callable replacing absolute artifact paths in captured output.

    Both the path as given and its resolved form are replaced, longest first,
    so a nested path is rewritten before the parent it sits under would have
    swallowed it and a build tool that prints the symlink-free spelling still
    matches. A path too short to be one (``""``, ``"."``) is never used as a
    needle: a single character would match every occurrence of itself.
    """
    needles = []
    for path, name in pairs:
        if not path:
            continue
        for spelling in (str(Path(path)), str(Path(path).resolve())):
            if len(spelling) > 1 and spelling not in [item[0] for item in needles]:
                needles.append((spelling, name))
    needles.sort(key=lambda item: (-len(item[0]), item[0]))

    def scrub(text):
        # type: (object) -> str
        if not text:
            return ""
        if isinstance(text, bytes):
            text = text.decode("utf-8", "replace")
        text = str(text)
        for path, name in needles:
            text = text.replace(path, name)
        return text

    return scrub


def _step(name, command, returncode, stdout, stderr, ok=None):
    # type: (str, list, object, object, object, object) -> dict
    """Every step dict in this module has the same shape."""
    if ok is None:
        ok = returncode == 0
    return {
        "name": name,
        "ok": bool(ok),
        "returncode": returncode,
        "command": [str(part) for part in command],
        "stdout_tail": _tail(stdout),
        "stderr_tail": _tail(stderr),
    }


def _run(command, cwd=None, timeout=None, env=None):
    # type: (list, object, object, object) -> tuple
    """Run a command, capturing output. Returns (returncode, stdout, stderr).

    A timeout yields returncode None with whatever output was captured, which
    the callers surface as ok False rather than as a crash.
    """
    try:
        completed = subprocess.run(
            command,
            cwd=str(cwd) if cwd else None,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=timeout,
            env=env,
        )
    except subprocess.TimeoutExpired as expired:
        return None, expired.stdout or b"", expired.stderr or b""
    except OSError as error:
        return None, "", str(error)
    return completed.returncode, completed.stdout, completed.stderr


def _cmake_exe():
    # type: () -> str
    return "cmake"


def _reconstruction_dir(source_dir):
    # type: (Path) -> Path
    return Path(source_dir).joinpath(*RECONSTRUCTION_SUBPATH)


def _promotion_document(path):
    # type: (Path) -> object
    try:
        with Path(path).open(encoding="utf-8") as handle:
            return json.load(handle)
    except (OSError, ValueError):
        return None


def promotion_targets(document):
    # type: (object) -> list
    """The VAs a promotion marker claims, in the spelling it stores them.

    A marker is written once, by ``promote.apply``, from the validation report
    and the metadata records, so it is the authoritative record of what was
    installed. Anything that needs to know "is this VA already promoted?" must
    read it through here rather than re-deriving the answer from a curated
    index, which lags promotion by design.

    Both spellings a marker has ever used are accepted -- ``va`` and
    ``bare_va`` -- because a marker written by an older writer still names the
    VA it installed and refusing to read it would silently retire a package that
    is present in the tree and exercised by the build.
    """
    if not isinstance(document, dict):
        return []
    vas = []
    for entry in document.get("targets") or []:
        if isinstance(entry, str):
            vas.append(entry)
            continue
        if not isinstance(entry, dict):
            continue
        for key in ("va", "bare_va"):
            value = entry.get(key)
            if isinstance(value, str) and value:
                vas.append(value)
                break
    return vas


def discover_packages(source_dir):
    # type: (Path) -> list
    """Promoted packages under ``<source_dir>/src/reconstruction``, sorted.

    Mirrors the CMake discovery rule exactly: a directory counts only when it
    holds a promotion.json with the openspore-promotion-1 schema and an
    ``src_package`` that is safe to use as a target name. Dotted names are
    skipped, so a scratch tree or a recovery tree left by an interrupted
    promotion is invisible here exactly as it is to the ``*/promotion.json``
    glob. The hand-written pkg15/pkg18/pkg20 CMakeLists.txt files are therefore
    never reached.
    """
    root = _reconstruction_dir(source_dir)
    if not root.is_dir():
        return []
    found = []
    for entry in sorted(root.iterdir(), key=lambda item: item.name):
        if not entry.is_dir() or entry.name.startswith("."):
            continue
        document = _promotion_document(entry / "promotion.json")
        if not isinstance(document, dict):
            continue
        if document.get("schema") != PROMOTION_SCHEMA:
            continue
        package = document.get("src_package")
        if not isinstance(package, str) or not NAME_RE.match(package):
            continue
        found.append({
            "dir": entry.name,
            "src_package": package,
            "path": str(entry),
            "test_stems": sorted(
                item.name[:-len(".cpp")]
                for item in entry.glob("*_test.cpp") if item.is_file()
            ),
        })
    return found


def m32_probe(cxx=DEFAULT_CXX, m32=True):
    # type: (str, bool) -> dict
    """Assert the compiler really honours -m32 before anything is built.

    Returns a step dict. ok True means the observed behaviour is the one the
    requested mode requires: with m32 the thiscall probe compiles, without m32
    it does not. Either half alone is not enough -- a probe that failed both
    ways would be indistinguishable from a broken compiler.
    """
    scratch = tempfile.mkdtemp(prefix="openspore-m32-probe-")
    try:
        with open(os.path.join(scratch, "m32_probe.cpp"), "w", encoding="utf-8") as handle:
            handle.write(PROBE_SOURCE)

        def _compile(with_m32):
            # type: (bool) -> tuple
            command = [cxx]
            if with_m32:
                command.append("-m32")
            command.extend(PROBE_FLAGS)
            # Relative paths plus cwd: the compiler still prints an absolute
            # source path in its diagnostics, but the command line itself must
            # not carry a fresh temp path into the result.
            command.extend(["-c", "m32_probe.cpp", "-o", "probe.o"])
            return _run(command, cwd=scratch)

        m32_rc, m32_out, m32_err = _compile(True)
        plain_rc, plain_out, plain_err = _compile(False)
    finally:
        shutil.rmtree(scratch, ignore_errors=True)

    def _clean(stream):
        # type: (object) -> str
        return _tail(stream).replace(scratch, "<m32-probe-scratch>")

    if m32:
        ok = m32_rc == 0 and plain_rc != 0
        expectation = "expected: -m32 compiles the thiscall probe, 64-bit rejects it"
    else:
        ok = plain_rc != 0
        expectation = ("expected: the 64-bit compiler rejects the thiscall probe; "
                       "reconstruction packages cannot be built in this mode")
    stdout = "%s\n--- with -m32 (rc=%s) ---\n%s\n--- without -m32 (rc=%s) ---\n%s" % (
        expectation, m32_rc, _clean(m32_out) + _clean(m32_err),
        plain_rc, _clean(plain_out) + _clean(plain_err))
    step = _step("m32_probe", [cxx, "-m32"], m32_rc, stdout, "", ok=ok)
    step["m32_returncode"] = m32_rc
    step["no_m32_returncode"] = plain_rc
    return step


def configure(root, build_dir=None, cxx=DEFAULT_CXX, m32=True, jobs=None, source_dir=None):
    # type: (object, object, str, bool, object, object) -> dict
    """Run cmake configure into build_dir (a fresh temp dir when None).

    Never uses the repository's own build/ directory. When build_dir is None
    the caller is asking for a throwaway tree, which :func:`gate` removes.
    ``jobs`` is accepted for signature symmetry with :func:`build` and is not
    a configure-time concept.
    """
    root = Path(root)
    source = Path(source_dir) if source_dir else root
    created = build_dir is None
    if created:
        build_dir = tempfile.mkdtemp(prefix="openspore-build-gate-")
    build_dir = Path(build_dir)

    command = [_cmake_exe(), "-S", str(source), "-B", str(build_dir),
               "-DCMAKE_CXX_COMPILER=%s" % cxx,
               "-D%s=%s" % (M32_OPTION, "ON" if m32 else "OFF")]
    returncode, stdout, stderr = _run(command)
    step = _step("configure", command, returncode, stdout, stderr)
    step["build_dir"] = str(build_dir)
    step["source_dir"] = str(source)
    step["m32"] = bool(m32)
    step["m32_option"] = "-D%s=%s" % (M32_OPTION, "ON" if m32 else "OFF")
    step["scratch"] = bool(created)
    return step


def build(root, build_dir, jobs=None):
    # type: (object, object, object) -> dict
    """Compile the configured tree. ``root`` is accepted for symmetry only.

    ``MAKEFLAGS`` is stripped: an inherited ``-j8`` would make a nominal
    ``jobs=1`` run parallel and reorder the captured progress lines.
    """
    build_dir = Path(build_dir)
    command = [_cmake_exe(), "--build", str(build_dir)]
    if jobs:
        command.extend(["--parallel", str(int(jobs))])
    returncode, stdout, stderr = _run(command, cwd=str(build_dir),
                                      env=_clean_env(MAKE_ENV_DROP))
    return _step("build", command, returncode, stdout, stderr)


def _parse_ctest_rows(text):
    # type: (object) -> list
    """Pull the per-test result table out of ctest's stdout.

    ctest exposes no per-test numeric return code, so ``returncode`` is derived
    from the status word: 0 for Passed, 1 for anything else. The status word and
    the failure reason ctest prints with it are both kept, so an abort is never
    flattened into a bare 1.
    """
    if isinstance(text, bytes):
        text = text.decode("utf-8", "replace")
    rows = []
    for line in str(text or "").splitlines():
        match = CTEST_LINE_RE.match(line)
        if not match:
            continue
        pieces = re.split(r"\.{3,}", match.group("rest"), maxsplit=1)
        if len(pieces) != 2:
            continue
        name = pieces[0].strip()
        tail = pieces[1]
        if not name:
            continue
        marker = CTEST_MARKER_RE.search(tail)
        if marker:
            status = marker.group(1)
            reason = tail[:marker.start()].strip()
        else:
            tokens = tail.split()
            if not tokens:
                continue
            status = tokens[0]
            reason = ""
        row = {
            "name": name,
            "ok": status == "Passed",
            "returncode": 0 if status == "Passed" else 1,
            "status": status,
        }
        if reason:
            row["reason"] = reason
        rows.append(row)
    return rows


def ctest(root, build_dir, timeout=None):
    # type: (object, object, object) -> dict
    """Run ctest and parse its result list.

    A run that found no tests is a failure, not a vacuous pass: ctest exits 0
    when nothing matches, so a broken add_test wiring would otherwise report
    green. Rows are sorted by name so the structured list cannot be reordered by
    an inherited ``CTEST_PARALLEL_LEVEL``, which is stripped from the
    subprocess environment along with ``CTEST_OUTPUT_ON_FAILURE``.
    """
    build_dir = Path(build_dir)
    command = ["ctest", "--test-dir", str(build_dir), "--output-on-failure"]
    if timeout:
        command.extend(["--timeout", str(int(timeout))])
    returncode, stdout, stderr = _run(command, cwd=str(build_dir), timeout=timeout,
                                      env=_clean_env(CTEST_ENV_DROP))
    text = _scrub_durations(stdout)
    if not isinstance(text, str):
        text = ""
    rows = _parse_ctest_rows(text)
    rows.sort(key=lambda row: row["name"])
    no_tests = CTEST_NO_TESTS in text or not rows
    ok = returncode == 0 and bool(rows) and not no_tests
    step = _step("ctest", command, returncode, text, stderr, ok=ok)
    step["tests"] = rows
    step["no_tests_found"] = bool(no_tests)
    return step


def compile_units(root, package, units, cxx=DEFAULT_CXX, m32=True, std="c++17"):
    # type: (object, str, list, str, bool, str) -> dict
    """Compile each unit standalone, without the CMake build system.

    ``package`` is a package directory when one exists at that path, else a
    src_package name resolved under ``<root>/src/reconstruction``. The package
    directory is put on the include path, because promoted headers are
    included by plain name. Used for a fast per-unit verdict while a worker is
    still writing the package out; :func:`gate` is the authority.
    """
    root = Path(root)
    candidate = Path(package)
    if not candidate.is_dir():
        candidate = _reconstruction_dir(root) / str(package)
    if not candidate.is_dir():
        return {
            "schema": "openspore-compile-units-1",
            "ok": False,
            "package": str(package),
            "package_dir": str(candidate),
            "cxx": cxx,
            "m32": bool(m32),
            "units": [],
            "error": "package directory not found: %s" % candidate,
        }

    flags = ["-Wall", "-Wextra", "-Werror"]
    if m32:
        flags.append("-m32")

    scratch = tempfile.mkdtemp(prefix="openspore-compile-units-")
    rows = []
    try:
        for index, unit in enumerate(list(units)):
            path = Path(unit)
            if not path.is_absolute():
                path = candidate / unit
            command = [cxx]
            if m32:
                command.append("-m32")
            command.extend(flags)
            command.extend(["-std=%s" % std, "-I", str(candidate),
                            "-c", str(path), "-o", "u%d.o" % index])
            returncode, stdout, stderr = _run(command, cwd=scratch)
            row = _step(unit, command, returncode, stdout, stderr)
            row["unit"] = str(unit)
            rows.append(row)
    finally:
        shutil.rmtree(scratch, ignore_errors=True)

    return {
        "schema": "openspore-compile-units-1",
        "ok": all(row["ok"] for row in rows) and bool(rows),
        "package": str(package),
        "package_dir": str(candidate),
        "cxx": cxx,
        "m32": bool(m32),
        "units": rows,
    }


def _archive_built(build_dir, src_package):
    # type: (Path, str) -> bool
    """True when the package's static library exists somewhere in the build tree."""
    names = ("lib%s.a" % src_package, "%s.lib" % src_package)
    for base, _directories, files in os.walk(str(build_dir)):
        for name in names:
            if name in files:
                return True
    return False


def _package_verdict(entry, built, rows, evaluated):
    # type: (dict, bool, list, bool) -> dict
    """One package's pass/fail, with the reason it failed.

    A package with no test translation units can never be green: the whole
    point of promotion is that a differential model test exists.
    """
    package = entry["src_package"]
    verdict = {"ok": False, "status": "unknown", "tests": [], "test_count": len(entry["test_stems"])}
    if not evaluated:
        verdict["status"] = "discovered"
        verdict["ok"] = True
        return verdict
    if not built:
        verdict["status"] = "not_built"
        return verdict
    if not entry["test_stems"]:
        verdict["status"] = "no_tests"
        return verdict
    by_name = {}
    for row in rows:
        by_name.setdefault(row["name"], row)
    mine = []
    missing = []
    for stem in entry["test_stems"]:
        name = "recon_%s_%s" % (package, stem)
        row = by_name.get(name)
        if row is None:
            missing.append({"name": name, "ok": False, "returncode": 1,
                            "status": "NotFound"})
            continue
        mine.append({"name": name, "ok": row["ok"], "returncode": row["returncode"],
                     "status": row["status"]})
        if row.get("reason"):
            mine[-1]["reason"] = row["reason"]
    verdict["tests"] = mine + missing
    if missing:
        verdict["status"] = "test_missing"
    elif all(item["ok"] for item in mine):
        verdict["status"] = "ok"
        verdict["ok"] = True
    else:
        verdict["status"] = "test_failed"
    return verdict


GATE_SCHEMA = "openspore-build-gate-1"


def _result(ok, build_dir, cxx, m32, steps, tests, verdicts, source=None):
    # type: (bool, object, str, bool, list, list, dict, object) -> dict
    """Assemble the gate's answer, with throwaway paths scrubbed out of the text.

    ``build_dir``/``source_dir`` and each step's ``command`` keep the real paths
    -- they are the identity of the run and a caller may want to re-execute one
    -- but nothing inside a captured stream does, so two scratch runs with
    different temp names stay comparable.
    """
    scrub = _scrubber(((build_dir, "<build-dir>"), (source, "<source-dir>")))
    for step in steps:
        for key in ("stdout_tail", "stderr_tail"):
            step[key] = scrub(step.get(key))
    return {
        "schema": GATE_SCHEMA,
        "ok": bool(ok),
        "build_dir": str(build_dir),
        "cxx": cxx,
        "m32": bool(m32),
        "steps": steps,
        "tests": tests,
        "packages": verdicts,
    }


def gate(root, build_dir=None, packages=None, cxx=DEFAULT_CXX, m32=True, jobs=None,
         configure_only=False, source_dir=None):
    # type: (object, object, object, str, bool, object, bool, object) -> dict
    """Configure, build and test a reconstruction tree, and say whether it is green.

    ``build_dir=None`` means "use a throwaway tree": one is created under the
    system temp directory and removed before returning. A caller that supplies
    ``build_dir`` keeps it, and nothing is ever written inside the repository
    otherwise.

    ``packages`` optionally restricts the reported per-package verdicts to the
    named src_packages; a name that was not discovered is reported ok False
    rather than quietly dropped.

    ``configure_only`` reports ``status: "discovered"`` for every package and
    runs no test at all, so its ``ok: True`` is a statement about configure
    succeeding and nothing else; ``tests`` is empty and no test verdict is
    claimed.
    """
    root = Path(root)
    source = Path(source_dir) if source_dir else root
    scratch = build_dir is None
    if scratch:
        build_dir = tempfile.mkdtemp(prefix="openspore-build-gate-")
    build_dir = Path(build_dir)

    try:
        probe = m32_probe(cxx=cxx, m32=m32)
        if not probe["ok"]:
            return _result(False, build_dir, cxx, m32, [probe], [], {})

        configure_step = configure(root, build_dir=build_dir, cxx=cxx, m32=m32,
                                   jobs=jobs, source_dir=source)
        steps = [probe, configure_step]
        tests = []
        verdicts = {}
        evaluated = False
        ok = configure_step["ok"]

        if ok and not configure_only:
            evaluated = True
            build_step = build(root, build_dir, jobs=jobs)
            ctest_step = ctest(root, build_dir)
            steps.extend([build_step, ctest_step])
            rows = ctest_step["tests"]
            tests = [{"name": row["name"], "ok": row["ok"], "returncode": row["returncode"]}
                     for row in rows]
            ok = build_step["ok"] and ctest_step["ok"] and bool(rows)
            discovered = discover_packages(source)
            for entry in discovered:
                verdict = _package_verdict(entry, _archive_built(build_dir, entry["src_package"]),
                                           rows, evaluated)
                if packages is not None and entry["src_package"] not in packages:
                    continue
                verdicts[entry["src_package"]] = verdict
                if not verdict["ok"]:
                    ok = False
            if packages is not None:
                known = set(entry["src_package"] for entry in discovered)
                for name in packages:
                    if name not in known:
                        verdicts[name] = {"ok": False, "status": "not_discovered",
                                          "tests": [], "test_count": 0}
                        ok = False
        elif ok and configure_only:
            for entry in discover_packages(source):
                if packages is not None and entry["src_package"] not in packages:
                    continue
                verdicts[entry["src_package"]] = _package_verdict(entry, False, [], False)
        elif not ok:
            for entry in discover_packages(source):
                if packages is not None and entry["src_package"] not in packages:
                    continue
                verdicts[entry["src_package"]] = _package_verdict(entry, False, [], True)

        return _result(bool(ok), build_dir, cxx, m32, steps, tests, verdicts,
                       source=source)
    finally:
        if scratch:
            shutil.rmtree(str(build_dir), ignore_errors=True)
