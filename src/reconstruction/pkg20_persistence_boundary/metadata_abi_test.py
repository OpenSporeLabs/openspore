import json
from pathlib import Path


def require(condition):
    if not condition:
        raise AssertionError


def load_metadata(name):
    root = Path(__file__).resolve().parents[3]
    with (root / "reconstruction" / "metadata" / "pkg20-persistence-boundary" / name).open(
        encoding="utf-8"
    ) as stream:
        return json.load(stream)


def test_profile_abi():
    abi = load_metadata("00b28ec0.json")["abi"]
    require(abi["calling_convention"] == "__thiscall")
    require(abi["hidden_this_register"] == "ECX")
    arguments = {argument["name"]: argument for argument in abi["stack_arguments"]}
    require(arguments["wide_path"]["entry_offset"] == "ESP+4")
    require(arguments["wide_path"]["width_bytes"] == 4)
    require(arguments["candidate_marker"]["entry_offset"] == "ESP+8")
    require(arguments["candidate_marker"]["width_bytes"] == 4)
    require(abi["stack_cleanup_bytes"] == 8)


def test_paint_abi():
    abi = load_metadata("004c5200.json")["abi"]
    require(abi["calling_convention"] == "__thiscall")
    require(abi["hidden_this_register"] == "ECX")
    require(abi["stack_arguments"][0]["entry_offset"] == "ESP+4")
    require(abi["stack_arguments"][0]["width_bytes"] == 4)
    require(abi["stack_cleanup_bytes"] == 4)


if __name__ == "__main__":
    test_profile_abi()
    test_paint_abi()
