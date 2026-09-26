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


def Main():
    RunRejectionSelfCheck()
    package_directory = Path(__file__).resolve().parents[2]
    metadata_directory = (
        package_directory
        / "metadata"
        / "pkg13-c3-creature-progression-wave2"
    )
    records = sorted(metadata_directory.glob("*.json"))
    if not records:
        print(f"no metadata records found: {metadata_directory}", file=sys.stderr)
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
