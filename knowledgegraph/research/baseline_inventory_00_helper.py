import hashlib
import json
import re
import sqlite3
import subprocess
import xml.etree.ElementTree as ET
from collections import Counter
from pathlib import Path

ROOT = Path("/home/juanr/Proyectos/OpenSpore")
OUT = ROOT / "knowledgegraph/research/00-baseline-inventory.json"
EXCLUDED_PARTS = {"__pycache__", ".git", ".codegraph", "build", "Testing", "out", "cache"}


def rel(path):
    return path.relative_to(ROOT).as_posix()


def files_under(prefix, include=None, exclude_parts=EXCLUDED_PARTS, exclude_names=None):
    base = ROOT / prefix
    if not base.exists():
        return []
    exclude_names = set(exclude_names or [])
    result = []
    for path in base.rglob("*"):
        if not path.is_file():
            continue
        parts = set(path.relative_to(ROOT).parts)
        if parts & exclude_parts:
            continue
        if path.name in exclude_names or path.suffix == ".pyc":
            continue
        if include and not include(path):
            continue
        result.append(path)
    return sorted(result, key=rel)


def sha256(path):
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def hash_records(paths):
    return [{"path": rel(path), "sha256": sha256(path), "size_bytes": path.stat().st_size} for path in sorted(paths, key=rel)]


def extension(path):
    return path.suffix.lower() or "<none>"


def file_set(paths, root, selection, authority, formats=None):
    rels = [rel(path) for path in sorted(paths, key=rel)]
    by_ext = Counter(extension(path) for path in paths)
    by_dir = Counter((Path(path).relative_to(Path(root)).parts[0] if len(Path(path).relative_to(Path(root)).parts) > 1 else "<root>") for path in paths)
    return {
        "authority": authority,
        "by_directory": dict(sorted((key or "<root>", value) for key, value in by_dir.items())),
        "by_extension": dict(sorted(by_ext.items())),
        "file_count": len(paths),
        "files": rels,
        "formats": formats or dict(sorted(by_ext.items())),
        "root": root,
        "selection": selection,
        "total_bytes": sum(path.stat().st_size for path in paths),
    }


def run(*args):
    return subprocess.run(args, cwd=ROOT, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True).stdout


def git_status():
    raw = subprocess.run(["git", "status", "--porcelain=v1", "-z", "-uall"], cwd=ROOT, check=True, stdout=subprocess.PIPE, text=True).stdout
    entries = [item for item in raw.split("\0") if item]
    staged = []
    unstaged = []
    untracked = []
    inventory_outputs = {
        "knowledgegraph/research/00-baseline-inventory.json",
        "knowledgegraph/research/baseline_inventory_00_helper.py",
    }
    for entry in entries:
        status = entry[:2]
        path = entry[3:]
        if path in inventory_outputs:
            continue
        if status == "??":
            untracked.append(path)
        else:
            if status[0] != " ":
                staged.append(path)
            if status[1] != " ":
                unstaged.append(path)
    return {
        "staged_paths": sorted(staged),
        "tracked_modified_paths": sorted(unstaged),
        "untracked_paths": sorted(untracked),
    }


def diff_numstat():
    out = {}
    for line in run("git", "diff", "--numstat").splitlines():
        added, deleted, path = line.split("\t", 2)
        out[path] = {"added": int(added), "deleted": int(deleted)}
    return dict(sorted(out.items()))


def value_shape(value):
    if isinstance(value, dict):
        keys = sorted(value)
        return {"key_count": len(keys), "keys": keys, "type": "object"}
    if isinstance(value, list):
        item_keys = sorted({key for item in value if isinstance(item, dict) for key in item})
        return {"item_count": len(value), "item_keys": item_keys, "type": "array"}
    return {"type": type(value).__name__}


def json_meta(path):
    with path.open(encoding="utf-8") as handle:
        doc = json.load(handle)
    return {
        "format": "json",
        "sha256": sha256(path),
        "size_bytes": path.stat().st_size,
        "top_level": {key: value_shape(doc[key]) for key in sorted(doc)},
    }, doc


def jsonl_meta(path):
    keys = set()
    rows = 0
    with path.open(encoding="utf-8") as handle:
        for line in handle:
            if not line.strip():
                continue
            row = json.loads(line)
            keys.update(row)
            rows += 1
    return {
        "format": "json-lines",
        "record_count": rows,
        "record_keys": sorted(keys),
        "sha256": sha256(path),
        "size_bytes": path.stat().st_size,
    }


def tsv_meta(path):
    with path.open(encoding="utf-8", newline="") as handle:
        reader = __import__("csv").reader(handle, delimiter="\t")
        header = next(reader)
        rows = sum(1 for _ in reader)
    return {
        "columns": header,
        "format": "tsv",
        "record_count": rows,
        "sha256": sha256(path),
        "size_bytes": path.stat().st_size,
    }


def sorted_dict(mapping):
    return {key: mapping[key] for key in sorted(mapping)}


def sqlite_inventory():
    uri = "file:/home/juanr/Proyectos/OpenSpore/knowledgegraph/spore.db?mode=ro"
    connection = sqlite3.connect(uri, uri=True)
    connection.execute("PRAGMA query_only=ON")
    tables = [row[0] for row in connection.execute("SELECT name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%' ORDER BY name")]
    inventory = {
        "counts_by_table": {},
        "database_sha256": sha256(ROOT / "knowledgegraph/spore.db"),
        "edge_rows_exported": [],
        "integrity_check": connection.execute("PRAGMA integrity_check").fetchone()[0],
        "logical_state_includes_wal": (ROOT / "knowledgegraph/spore.db-wal").stat().st_size > 0,
        "mode": "sqlite URI mode=ro plus PRAGMA query_only",
        "sidecars": {
            "knowledgegraph/spore.db-shm": {
                "identity": "transient shared-memory sidecar; not used as a content identity",
                "size_bytes": (ROOT / "knowledgegraph/spore.db-shm").stat().st_size,
            },
            "knowledgegraph/spore.db-wal": {
                "sha256": sha256(ROOT / "knowledgegraph/spore.db-wal"),
                "size_bytes": (ROOT / "knowledgegraph/spore.db-wal").stat().st_size,
            },
        },
        "user_version": connection.execute("PRAGMA user_version").fetchone()[0],
    }
    for table in tables:
        columns = [row[1] for row in connection.execute(f'PRAGMA table_info("{table}")')]
        inventory["counts_by_table"][table] = {
            "columns": columns,
            "rows": connection.execute(f'SELECT COUNT(*) FROM "{table}"').fetchone()[0],
        }
    inventory["distributions"] = {
        "investigation_kind": [list(row) for row in connection.execute("SELECT kind,COUNT(*) FROM investigations GROUP BY kind ORDER BY kind")],
        "investigation_triage_status": [list(row) for row in connection.execute("SELECT triage_status,COUNT(*) FROM investigations GROUP BY triage_status ORDER BY triage_status")],
        "triage_classifier_version": [list(row) for row in connection.execute("SELECT classifier_version,COUNT(*) FROM triage GROUP BY classifier_version ORDER BY classifier_version")],
        "triage_snapshot_sha256": [list(row) for row in connection.execute("SELECT snapshot_sha256,COUNT(*) FROM triage GROUP BY snapshot_sha256 ORDER BY snapshot_sha256")],
        "xref_reference_type": [list(row) for row in connection.execute("SELECT reference_type,COUNT(*) FROM xref GROUP BY reference_type ORDER BY reference_type")],
    }
    connection.close()
    return sorted_dict(inventory)


def dossier_inventory():
    paths = files_under("docs/analysis/dossiers", exclude_parts={"__pycache__"})
    json_paths = sorted((path for path in paths if path.suffix == ".json"), key=rel)
    markdown_paths = sorted((path for path in paths if path.suffix == ".md"), key=rel)
    records = []
    for path in json_paths:
        meta, doc = json_meta(path)
        records.append({
            "functions_count": len(doc.get("functions", [])) if isinstance(doc.get("functions"), list) else None,
            "markdown_pair": path.with_suffix(".md").relative_to(ROOT).as_posix(),
            "path": rel(path),
            "schema": doc.get("$schema"),
            "sha256": meta["sha256"],
            "size_bytes": meta["size_bytes"],
            "topic": doc.get("topic"),
            "top_level_keys": sorted(meta["top_level"]),
        })
    return {
        "authoritative_role": "bounded evidence synthesis; not a replacement for raw Ghidra, xref, SDK, or runtime evidence",
        "json_count": len(json_paths),
        "machine_files": records,
        "markdown_count": len(markdown_paths),
        "markdown_files": [rel(path) for path in markdown_paths],
        "pairing": "one JSON and one Markdown file per topic",
        "schema": "re-dossier-1",
        "topic_count": len(records),
    }


def ghidra_inventory():
    root = ROOT / ".spore-analysis/ghidra-exports"
    decompiled = files_under(".spore-analysis/ghidra-exports/decompiled_sdk")
    top_files = sorted((path for path in root.iterdir() if path.is_file()), key=rel)
    file_records = []
    for path in top_files:
        if path.suffix == ".json":
            meta, _ = json_meta(path)
            file_records.append({"path": rel(path), "format": meta["format"], "sha256": meta["sha256"], "size_bytes": meta["size_bytes"], "top_level": meta["top_level"]})
        elif path.suffix == ".tsv":
            meta = tsv_meta(path)
            file_records.append({"path": rel(path), **meta})
        elif path.suffix == ".xml":
            root_element = ET.parse(path).getroot()
            file_records.append({"path": rel(path), "format": "xml", "root": root_element.tag, "sha256": sha256(path), "size_bytes": path.stat().st_size})
        else:
            file_records.append({"path": rel(path), "format": extension(path), "sha256": sha256(path), "size_bytes": path.stat().st_size})
    manifest_path = root / "manifest.json"
    _, manifest = json_meta(manifest_path)
    decomp_hashes = hash_records(decompiled)
    set_digest = hashlib.sha256()
    for record in decomp_hashes:
        set_digest.update(record["path"].encode("utf-8"))
        set_digest.update(b"\0")
        set_digest.update(record["sha256"].encode("ascii"))
        set_digest.update(b"\n")
    return {
        "authoritative_role": "read-only static-analysis export of the pinned binary and community SDK import",
        "binary": {key: manifest["binary"][key] for key in sorted(manifest["binary"])},
        "caveats": sorted(manifest["caveats"]),
        "counts": sorted_dict(manifest["counts"]),
        "decompiled_sdk": {
            "content_set_sha256": set_digest.hexdigest(),
            "file_count": len(decomp_hashes),
            "files": decomp_hashes,
        },
        "files": file_records,
        "ignored_by_git": True,
        "sdk": sorted_dict(manifest["sdk"]),
    }


def fixture_inventory():
    root = ROOT / "tests/fixtures"
    paths = files_under("tests/fixtures")
    scenario_doc = json.loads((root / "cell/fixtures.json").read_text(encoding="utf-8"))
    return {
        "authoritative_role": "synthetic and golden test inputs; not evidence of original semantics by themselves",
        "cell_contract": scenario_doc.get("contract"),
        "cell_scenarios": sorted(str(scenario.get("name")) for scenario in scenario_doc.get("scenarios", [])),
        "cell_scenario_count": len(scenario_doc.get("scenarios", [])),
        "file_hashes": hash_records(paths),
        "files": [rel(path) for path in paths],
        "total_bytes": sum(path.stat().st_size for path in paths),
    }


def main():
    project_controls = [ROOT / path for path in [
        ".github/ISSUE_TEMPLATE.md",
        ".github/PULL_REQUEST_TEMPLATE.md",
        ".gitignore",
        "AGENTS.md",
        "CMakeLists.txt",
        "CODE_OF_CONDUCT.md",
        "CONTRIBUTING.md",
        "LICENSE",
        "OpenSpore.md",
        "README.md",
        "opencode.json",
    ]]
    source = files_under("src")
    docs = files_under("docs")
    tests = files_under("tests")
    asset_tooling = files_under("tools/spore")
    analysis_tooling = files_under("tools", include=lambda path: "__pycache__" not in path.parts and "out" not in path.relative_to(ROOT).parts and "cache" not in path.relative_to(ROOT).parts and path.name not in {"m32target", "probe_tracer", "target", "target_hooked", "probes.json"} and not path.name.startswith("out_") and path.suffix != ".pyc")
    kg_files = files_under("knowledgegraph", exclude_parts={"triage", "research", "__pycache__"})
    triage_paths = files_under("knowledgegraph/triage", exclude_parts=set())
    triage_formats = []
    for path in triage_paths:
        if path.suffix == ".jsonl":
            triage_formats.append({"path": rel(path), **jsonl_meta(path)})
        elif path.suffix == ".json":
            meta, _ = json_meta(path)
            triage_formats.append({"path": rel(path), **meta})
        elif path.suffix == ".tsv":
            triage_formats.append({"path": rel(path), **tsv_meta(path)})
        elif path.suffix == ".md":
            triage_formats.append({"path": rel(path), "format": "markdown", "sha256": sha256(path), "size_bytes": path.stat().st_size})
        else:
            triage_formats.append({"path": rel(path), "format": extension(path), "sha256": sha256(path), "size_bytes": path.stat().st_size})
    generated_validation = []
    for candidate in [ROOT / "tools/observatory/test/m32target", ROOT / "tools/replace/synthetic/target", ROOT / "tools/replace/synthetic/target_hooked", ROOT / "tools/replace/synthetic/out_before.jsonl"]:
        if candidate.exists() and candidate.is_file():
            generated_validation.append({"path": rel(candidate), "sha256": sha256(candidate), "size_bytes": candidate.stat().st_size})
    relevant_analysis = files_under("docs/analysis")
    protected_paths = sorted(set(
        triage_paths
        + relevant_analysis
        + files_under("tools/triage")
        + files_under("tools/ghidra")
        + files_under(".spore-analysis/ghidra-exports")
        + files_under("tests/fixtures")
        + [ROOT / "docs/STATE.md", ROOT / "knowledgegraph/schema.sql", ROOT / "knowledgegraph/scale.py", ROOT / "knowledgegraph/spore.db", ROOT / "tools/re/data/ghidra_snapshot_cell_movement.json", ROOT / "tools/re/data/decompiled/FUN_00e806b0.c", ROOT / "tools/re/data/decompiled/MovePlayerToMousePosition.c"]
    ), key=rel)
    status = git_status()
    artifact = {
        "$schema": "openspore-baseline-inventory-1",
        "authoritative_source_precedence_proposal": [
            {"precedence": 1, "source": "Pinned binary bytes plus replayable runtime traces and manifests", "use": "identity, observed bytes, observed runtime behavior", "limit": "runtime availability and boot stability are not guaranteed; a trace is valid only for its binary, probe-set, environment, and manifest hashes"},
            {"precedence": 2, "source": "Pinned Ghidra exports and raw xref exports", "use": "static function, structure, vtable-candidate, decompilation, and cross-reference facts", "limit": "decompiler output is evidence, not truth; vtable candidates and inferred this-types remain structural inference; no RTTI"},
            {"precedence": 3, "source": "Pinned Spore-ModAPI Ghidra XML", "use": "community-provided names, declarations, and layouts", "limit": "GPL reference-only; reverse-engineered headers, not EA source; a name match is name-level provenance only"},
            {"precedence": 4, "source": "triage-v6 projections, canonical xrefs, debt map, readiness audit, and SDK-boundary adjudication", "use": "campaign selection, classification, readiness, and reproducible structural relationships", "limit": "projection rules and heuristics are not semantic truth; v6 is not ingested in the live DB; three queue VAs are outside the pinned function universe"},
            {"precedence": 5, "source": "Dossiers and analysis reports", "use": "bounded hypotheses, evidence pointers, caveats, and human-readable review", "limit": "secondary synthesis; citations and evidence labels must be retained; reports may contain stale counts"},
            {"precedence": 6, "source": "Current OpenSpore source, contracts, tests, and fixtures", "use": "implemented behavior, clean-room interface contracts, and regression validation", "limit": "implementation and test success do not establish original semantics"},
            {"precedence": 7, "source": "SQLite knowledge graph", "use": "shared conclusions, test outcomes, and decisions with provenance", "limit": "not a source of truth; existing edges are inventoried by count only and no new edge is proposed here"},
            {"precedence": 8, "source": "Project status and historical narrative docs", "use": "workflow context and pointers", "limit": "docs/STATE.md is currently modified; narrative claims require verification against pinned inputs"},
        ],
        "community_and_modding_material": {
            "community_sdk": {
                "git_head": "cbf9206b9a823f0911cd9be0217104a49d72380b",
                "git_worktree_clean": True,
                "license": "GPL-3.0 reference-only",
                "local_path": "/home/juanr/apps/Spore-ModAPI",
                "pinned_xml": "/home/juanr/apps/Spore-ModAPI/SDKtoGhidra/SporeGhidra_march2017.xml",
                "pinned_xml_sha256": sha256(Path("/home/juanr/apps/Spore-ModAPI/SDKtoGhidra/SporeGhidra_march2017.xml")),
                "provenance": "SDK symbol/type import; no source copied into OpenSpore",
            },
            "other_documented_references": [
                {"name": "SporeModder-FX", "license": "GPL-3.0", "repository_copy_present": False, "use": "semantics/format research only"},
                {"name": "librw", "license": "MIT", "repository_copy_present": False, "use": "permitted external renderer reference subject to attribution"},
                {"name": "re3/reVC", "license": "unlicensed reference-only", "repository_copy_present": False, "use": "architectural pattern reference only"},
            ],
        },
        "dirty_worktree": {
            **status,
            "constraint": "All listed modified and untracked paths are pre-existing campaign inputs and must not be reset, rewritten, normalized, or overwritten by baseline inventory work.",
            "diff_numstat": diff_numstat(),
            "untracked_count": len(status["untracked_paths"]),
        },
        "file_sets": {
            "analysis_and_ghidra_tooling": file_set(analysis_tooling, "tools", "all non-generated files under tools; excludes out, caches, bytecode, built probes/targets", "validation and automation implementation; secondary to pinned evidence"),
            "asset_tooling": file_set(asset_tooling, "tools/spore", "all non-generated files under tools/spore; excludes out and bytecode", "clean-room asset-format tools and mappings; not original binary authority"),
            "current_source_tree": file_set(source, "src", "all files under src", "implemented clean-room source; not original-semantic truth"),
            "documentation": file_set(docs, "docs", "all files under docs", "analysis, contracts, reports, and status; secondary narrative and schemas"),
            "knowledgegraph_tooling_and_seed": file_set(kg_files, "knowledgegraph", "knowledgegraph files excluding triage, research output, bytecode, and SQLite runtime sidecars", "shared-memory tooling and canonical seed; no database mutation"),
            "tests": file_set(tests, "tests", "all files under tests excluding bytecode", "test implementation, fixtures, expected outputs, and validation contracts"),
            "triage": file_set(triage_paths, "knowledgegraph/triage", "all current files under knowledgegraph/triage", "pinned triage history, xrefs, classifications, readiness, and structural analyses"),
        },
        "formats_and_counts": {
            "dossiers": dossier_inventory(),
            "fixtures": fixture_inventory(),
            "ghidra_exports": ghidra_inventory(),
            "knowledge_graph_sqlite": sqlite_inventory(),
            "triage_artifacts": sorted(triage_formats, key=lambda row: row["path"]),
        },
        "historical_and_protected_input_hashes": hash_records(protected_paths),
        "immutable_and_protected_inputs": {
            "external_ghidra_project": "/home/juanr/ghidra-spore-project/SporeProject",
            "gog_installers": "gog_installer/*",
            "knowledge_graph": ["knowledgegraph/spore.db", "knowledgegraph/spore.db-wal", "knowledgegraph/spore.db-shm"],
            "pinned_binaries": [
                {"path": "SPORE/SporeBin/SporeApp.exe", "sha256": sha256(ROOT / "SPORE/SporeBin/SporeApp.exe")},
                {"path": "SPORE/SporebinEP1/SporeApp.exe", "sha256": sha256(ROOT / "SPORE/SporebinEP1/SporeApp.exe")},
            ],
            "policy": "Read-only for this campaign. Do not modify source, docs, triage artifacts, SQLite, Ghidra project state, SDK source, SPORE assets, generated traces, or shared final artifacts.",
            "proprietary_game_tree": "SPORE/",
            "rules": "AGENTS.md, CONTRIBUTING.md, LICENSE, .gitignore",
        },
        "known_provenance_and_consistency_limits": [
            "The frozen triage universe is 58,757 functions; xref provenance records a live Ghidra program count of 59,245 and explicitly preserves the frozen universe.",
            "The live SQLite triage table contains 58,757 triage-v4 rows at snapshot 2540f2ca; triage-v5 and triage-v6 are projection files and are not ingested into SQLite.",
            "The v6 JSONL retains classifier_version triage-v5 on rows while adding v6_rationale; summary-f0e310e0.triage-v6.json declares classifier_version triage-v6.",
            "The readiness audit records three queue VAs absent from the pinned triage/function universe and carries them without invented xrefs.",
            "UNKNOWN-HIGH investigation contains 862 input rows, including 44 described as Ghidra non-function addresses, while the pinned triage universe itself remains 58,757.",
            "Ghidra exports contain 478 decompiled SDK-address files, but the report history and SDK-boundary audit use earlier 477/1,186 versus current manifest 478/1,188 snapshots.",
            "The export manifest records 2,035 structures and 25,546 structure-field rows; SQLite records 25,561 field rows. These are different layers and must not be conflated.",
            "SporeApp.exe has no MSVC RTTI. SDK names are reverse-engineered community headers and support only name-level provenance.",
            "Decompilation is P-code evidence with warnings and guessed types; no decompilation claim is ground truth by itself.",
            "No successful cell-mode runtime trace exists in the recorded campaign state; runtime-dependent semantics remain unobserved or negative.",
            "The word DirectX in v5 middleware notes means no D3D/IDirect-named functions or d3dx external xrefs in the frozen classifier inputs; it does not erase the PE import surface recorded by recon.",
            "Current narrative reports contain historical revisions. File hashes, embedded snapshot fields, and raw record counts take precedence over prose counts.",
            "Generated caches, build outputs, traces, logs, PNG/PPM output, and database sidecars are not semantic authority even when present locally.",
        ],
        "provenance": {
            "binary": {
                "path": "SPORE/SporeBin/SporeApp.exe",
                "sha256": sha256(ROOT / "SPORE/SporeBin/SporeApp.exe"),
                "version": "Spore 3.1.0.22 GOG",
            },
            "repository_head": run("git", "rev-parse", "HEAD").strip(),
            "repository_head_subject": run("git", "log", "-1", "--format=%s").strip(),
            "snapshot_ids": {
                "frozen_functions": "2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8",
                "triage_v5_v6": "f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b",
            },
        },
        "repository": {
            "branch": run("git", "branch", "--show-current").strip(),
            "root": str(ROOT),
            "staged_changes": status["staged_paths"],
        },
        "scope": {
            "artifact_path": rel(OUT),
            "determinism": {
                "json_keys": "sorted",
                "timestamps": "excluded",
                "wall_clock_fields": "excluded from this inventory",
            },
            "excluded_from_semantic_inventory": [
                ".git/",
                ".codegraph/",
                "build/",
                "Testing/",
                "SPORE/ except pinned binary identity hashes",
                "gog_installer/",
                "cell_stage.ppm",
                "material_flat.ppm",
                "tools/mcp/cache/",
                "tools/observatory/out/",
                "tools/spore/out/",
                "all __pycache__/ and .pyc files",
            ],
            "purpose": "baseline inventory of authoritative repository inputs for global semantic archaeology",
            "speculative_kg_edges": [],
        },
        "validation_commands": {
            "concise_plan": [
                "Re-hash every path in historical_and_protected_input_hashes and require exact equality.",
                "Parse this inventory as JSON and reject non-sorted object keys or timestamp-like generated fields.",
                "Open knowledgegraph/spore.db with SQLite mode=ro plus PRAGMA query_only and require integrity_check=ok, user_version=4, and recorded table counts.",
                "Require xrefs-2540f2ca.tsv to have 223,704 data rows, 362 external rows, the recorded columns, and pinned SHA-256.",
                "Require triage-v6 JSONL to have 58,757 rows and unique VA8 values; require cluster sum and queue total assertions to agree with row counts.",
                "Require each dossier topic to have one JSON and one Markdown pair under re-dossier-1 and retain evidence labels.",
                "Run build and tests only in a disposable worktree: cmake -S . -B build && cmake --build build -j && ctest --test-dir build -V; then python3 -m unittest discover -s tests -t . -v.",
                "Run classifier/xref regeneration only against disposable copies with --dry-run or an isolated output directory; never rewrite the pinned worktree or live DB during baseline validation.",
                "Re-diff the protected set after all campaign workers finish; no baseline or campaign action may alter it without an explicit handoff.",
            ],
            "executed_read_only_checks": [
                "git status/diff/log inventory",
                "SHA-256 calculation",
                "SQLite mode=ro plus PRAGMA query_only integrity and count queries",
                "JSON/JSONL/TSV/XML schema and row-count parsing by the inventory helper",
            ],
            "not_executed_due_to_write_side_effects": [
                "cmake configure/build",
                "ctest",
                "Python unittest suite",
                "dossier regeneration",
                "triage classifier or xref exporter regeneration",
                "Wine/Ghidra runtime actions",
            ],
            "recorded_baseline_claims_not_reexecuted": {
                "ctest": "36/36",
                "python_unittest": "408/408",
                "source": "docs/STATE.md and triage-v6 analysis reports",
            },
        },
    }
    OUT.write_text(json.dumps(artifact, indent=2, sort_keys=True, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps({
        "artifact": rel(OUT),
        "artifact_sha256": sha256(OUT),
        "protected_hash_count": len(protected_paths),
        "untracked_count": len(status["untracked_paths"]),
    }, sort_keys=True))


if __name__ == "__main__":
    main()
