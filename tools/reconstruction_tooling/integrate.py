from pathlib import Path

from .models import ROOT, ToolError, canonical_json, optional_json, sha256_json

try:
    from tools import reconstruction_knowledge as rk
except ImportError as exc:
    raise RuntimeError("reconstruction knowledge module is unavailable") from exc

INDEX_REL = "reconstruction/knowledge/index.json"
BOOTSTRAP_REL = "reconstruction/knowledge/bootstrap.json"


def _current(root):
    index = optional_json(Path(root) / INDEX_REL)
    bootstrap = optional_json(Path(root) / BOOTSTRAP_REL)
    return index, bootstrap


def status(root=ROOT):
    root = Path(root)
    index, bootstrap = _current(root)
    return {
        "schema": "openspore-integration-status-1",
        "index": {"path": INDEX_REL, "present": index is not None, "sha256": None if index is None else sha256_json(index)},
        "bootstrap": {"path": BOOTSTRAP_REL, "present": bootstrap is not None},
        "source_of_truth": "knowledgegraph/research/source-reconstruction-manifest.json",
        "generated": ["reconstruction/knowledge/index.json", "reconstruction/knowledge/bootstrap.json"],
        "changed": False,
    }


def check(root=ROOT):
    root = Path(root)
    current_index, current_bootstrap = _current(root)
    if current_index is None or current_bootstrap is None:
        return {"status": "NOT_AVAILABLE", "reason": "generated index or bootstrap is missing", "changed": False}
    try:
        generated_index, generated_bootstrap = rk.build_index(root)
    except Exception as exc:
        raise ToolError("integration_failed", "cannot rebuild generated projection: %s" % exc, 1)
    index_match = canonical_json(generated_index) == canonical_json(current_index)
    bootstrap_match = canonical_json(generated_bootstrap) == canonical_json(current_bootstrap)
    return {
        "schema": "openspore-integration-status-1",
        "status": "PASS" if index_match and bootstrap_match else "WARN",
        "index_match": index_match,
        "bootstrap_match": bootstrap_match,
        "source_of_truth": "knowledgegraph/research/source-reconstruction-manifest.json",
        "changed": False,
        "index": INDEX_REL,
        "bootstrap": BOOTSTRAP_REL,
    }


def apply(root=ROOT):
    root = Path(root)
    try:
        index, bootstrap = rk.build_index(root)
    except Exception as exc:
        raise ToolError("integration_failed", "cannot rebuild generated projection: %s" % exc, 1)
    rk.write_json_atomic(root / INDEX_REL, index)
    rk.write_json_atomic(root / BOOTSTRAP_REL, bootstrap)
    return {"status": "PASS", "changed": True, "index": INDEX_REL, "bootstrap": BOOTSTRAP_REL, "source_of_truth": "knowledgegraph/research/source-reconstruction-manifest.json"}
