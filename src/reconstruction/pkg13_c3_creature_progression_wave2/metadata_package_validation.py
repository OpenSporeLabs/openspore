import json
import sys
from pathlib import Path

EXPECTED_PACKAGE = "PKG-13-C3-CREATURE-PROGRESSION-WAVE2"
COMBINED_SCOPE_TOKENS = frozenset({"TRIBE", "CIV", "CITY", "TRIBECIV"})


def IsCombinedCreatureTribeCityPackage(package):
    tokens = set(package.split("-"))
    return "CREATURE" in tokens and bool(tokens & COMBINED_SCOPE_TOKENS)


def ValidatePackageIdentifier(package):
    errors = []
    if IsCombinedCreatureTribeCityPackage(package):
        errors.append(f"combined creature/tribe/city package id: {package}")
    if package != EXPECTED_PACKAGE:
        errors.append(f"unexpected package id: {package}")
    return errors


def ValidateRecord(path):
    with path.open(encoding="utf-8") as stream:
        record = json.load(stream)
    package = record.get("package")
    if not isinstance(package, str):
        return [f"missing package id: {path}"]
    return [f"{path}: {error}" for error in ValidatePackageIdentifier(package)]


def RunRejectionSelfCheck():
    samples = (
        "PKG-13-SIM-CREATURE-TRIBECIV-C3-WAVE2",
        "PKG-13-C3-CREATURE-TRIBE-WAVE2",
        "PKG-13-C3-CREATURE-CITY-WAVE2",
    )
    for package in samples:
        if not IsCombinedCreatureTribeCityPackage(package):
            raise AssertionError(f"combined package id accepted: {package}")


def FindRepositoryRoot(package_directory):
    for candidate in (package_directory, *package_directory.parents):
        if (
            (candidate / "reconstruction" / "metadata").is_dir()
            and (candidate / "src" / "reconstruction").is_dir()
        ):
            return candidate
    raise RuntimeError(f"repository root not found from: {package_directory}")


def Main():
    RunRejectionSelfCheck()
    package_directory = Path(__file__).resolve().parent
    repository_root = FindRepositoryRoot(package_directory)
    metadata_directory = (
        repository_root
        / "reconstruction"
        / "metadata"
        / "pkg13-c3-creature-progression-wave2"
    )
    records = sorted(metadata_directory.glob("*.json"))
    expected_names = ["00d2e340.json", "00d2e8a0.json"]
    if [path.name for path in records] != expected_names:
        print(
            f"expected metadata records {expected_names}, found {[path.name for path in records]}",
            file=sys.stderr,
        )
        return 1
    errors = []
    for path in records:
        errors.extend(ValidateRecord(path))
    if errors:
        for error in errors:
            print(error, file=sys.stderr)
        return 1
    print(f"validated {len(records)} creature package metadata records")
    return 0


if __name__ == "__main__":
    raise SystemExit(Main())
