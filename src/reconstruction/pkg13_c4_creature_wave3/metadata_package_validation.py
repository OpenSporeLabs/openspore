import json
import sys
from pathlib import Path

EXPECTED_PACKAGE = "PKG-13-C4-CREATURE-WAVE3"
EXPECTED_ADDRESSES = ("0x00c1c5c0", "0x00c1d460")
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


def ValidateRecord(path, seen):
    with path.open(encoding="utf-8") as stream:
        record = json.load(stream)
    package = record.get("package")
    if not isinstance(package, str):
        return [f"missing package id: {path}"]
    errors = [f"{path}: {error}" for error in ValidatePackageIdentifier(package)]
    address = record.get("function_address")
    if address not in EXPECTED_ADDRESSES:
        errors.append(f"{path}: unexpected function address: {address}")
    if address in seen:
        errors.append(f"{path}: duplicate function address: {address}")
    seen.add(address)
    if not record.get("source_files"):
        errors.append(f"{path}: missing source_files")
    for key in ("signature", "body", "call_graph", "verification"):
        if key not in record:
            errors.append(f"{path}: missing section: {key}")
    return errors


def ValidateCoverage(seen):
    return [f"missing expected record for: {address}" for address in EXPECTED_ADDRESSES if address not in seen]


def RunRejectionSelfCheck():
    samples = (
        "PKG-13-C4-CREATURE-TRIBE-WAVE3",
        "PKG-13-C4-CREATURE-CIV-WAVE3",
        "PKG-13-C4-CREATURE-CITY-WAVE3",
    )
    for package in samples:
        if not IsCombinedCreatureTribeCityPackage(package):
            raise AssertionError(f"combined package id accepted: {package}")


def Main():
    RunRejectionSelfCheck()
    package_directory = Path(__file__).resolve().parents[2]
    metadata_directory = (
        package_directory / "metadata" / "pkg13-c4-creature-wave3"
    )
    records = sorted(metadata_directory.glob("*.json"))
    if not records:
        print(f"no metadata records found: {metadata_directory}", file=sys.stderr)
        return 1
    errors = []
    seen = set()
    for path in records:
        errors.extend(ValidateRecord(path, seen))
    errors.extend(ValidateCoverage(seen))
    if errors:
        for error in errors:
            print(error, file=sys.stderr)
        return 1
    print(f"validated {len(records)} creature wave3 metadata records")
    return 0


if __name__ == "__main__":
    raise SystemExit(Main())
