from pathlib import Path

from .context import build as build_context
from .evidence import collect
from .models import ROOT, write_json_atomic
from .validate import validate


def recover(root=ROOT, va=None, live=False, write=True, out_dir=None):
    evidence = collect(root=root, va=va, live=live, write=write, out_dir=out_dir)
    context = build_context(root=root, va=evidence["target"]["va"], evidence=evidence, live=live, write=write, out_dir=out_dir)
    validation = validate(root=root, va=evidence["target"]["va"], evidence=evidence, context=context, write=write, out_dir=out_dir)
    runtime = validation.get("runtime") or {}
    # "complete" would be a runtime claim, and the runtime dimension has never
    # been observed. A static PASS is accepted-static at best, and the gate it
    # leaves open travels with the result.
    static = validation.get("status")
    if static == "PASS":
        status = "static_accepted"
    elif static == "WARN":
        status = "review_required"
    else:
        status = "partial"
    result = {
        "schema": "openspore-recover-1",
        "target": evidence["target"]["va"],
        "status": status,
        "evidence_state": evidence.get("evidence_state"),
        "evidence": evidence.get("paths", {}),
        "context": context.get("paths", {}),
        "validation": validation.get("paths", {}),
        "validation_status": static,
        "validation_dimension": "STATIC",
        "runtime": {"status": runtime.get("status"),
                    "gated": bool(runtime.get("gated")),
                    "gates": runtime.get("gates") or []},
        "rerun_safe": "per-file-atomic",
        "transactional": False,
        "changed": bool(write),
    }
    if write:
        destination = Path(out_dir) if out_dir else Path(root) / "reconstruction" / "evidence" / evidence["target"]["va"][2:]
        result["workflow"] = str(destination / "recover.json")
        write_json_atomic(destination / "recover.json", result)
    return result
