from .frontier import frontier
from .models import ROOT, normalize_va, write_json_atomic


def _queue_va(va):
    return normalize_va(va)[2:]


def _claim_identity(claim):
    ids = {str(item.get("id")) for item in (claim.get("claims") or []) if item.get("id")}
    if len(ids) == 1:
        return next(iter(ids))
    return claim.get("id")


def decorate(target, binary_sha256=None):
    # type: (dict, object) -> dict
    """Project one frontier target into a queue-addressable swarm entry.

    Shared with ``orchestrate.plan`` so a target is described identically
    whether it came through ``swarm`` or straight from ``frontier``; a second
    implementation of the VA-format and claim-id translation is exactly the
    kind of drift that made the plan un-claimable in the first place.
    """
    claim = target.get("claim", {})
    queue_row = bool(claim.get("claim_count") or claim.get("claims"))
    return {
        "va": target["va"],
        "priority": target.get("score", 0),
        "dependencies": list(target.get("open_dependencies") or []),
        "evidence_ready": bool(target.get("score", 0)) and bool(target.get("evidence_refs")),
        "claimable": bool(claim.get("claimable", False)),
        "reason_codes": [item.get("code") for item in target.get("reasons", [])],
        "queue_va": _queue_va(target["va"]),
        "queue_id": _claim_identity(claim) if queue_row else None,
        "queue_row": queue_row,
        "name": target.get("name"),
        "package": target.get("package"),
        "subsystem": target.get("subsystem"),
        "category": target.get("category"),
        "cluster": target.get("cluster"),
        "evidence_level": str(target.get("evidence_level") or "UNKNOWN"),
        "runtime_gated": bool(target.get("runtime_gates")),
        "claim_state": claim.get("state"),
        "block_reason": claim.get("block_reason"),
        "disposition": target.get("disposition"),
        "dependency_uncertain": bool(target.get("dependency_uncertain")),
        "open_callees": list((target.get("dependencies") or {}).get("open_callees") or []),
        "binary_sha256": binary_sha256,
        "score_components": target.get("score_components", {}),
    }


def eligible(result):
    # type: (dict) -> list
    """Frontier targets that are dispatchable right now."""
    return [target for target in result.get("targets", [])
            if target.get("disposition") == "eligible"
            and (target.get("claim") or {}).get("claimable")]


def swarm(root=ROOT, limit=20, out=None):
    requested_limit = max(0, int(limit))
    page_limit = max(1000, min(requested_limit * 10, 10000)) if requested_limit else 1000
    result = frontier(root=root, args=type("Args", (), {"limit": page_limit, "offset": 0})())
    binary_sha256 = result.get("binary_sha256")
    entries = []
    for target in result["targets"]:
        claim = target.get("claim", {})
        if target["disposition"] != "eligible" or not claim.get("claimable", False):
            continue
        entries.append(decorate(target, binary_sha256))
    entries = entries[:max(0, int(limit))]
    plan = {
        "$schema": "openspore-swarm-plan-1",
        "status": "ok" if entries or result.get("summary", {}).get("eligible", 0) == 0 else "blocked",
        "binary_sha256": binary_sha256,
        "scoring": result.get("scoring"),
        "summary": result.get("summary", {}),
        "frontier_total": result.get("total", 0),
        "frontier_page_truncated": bool(result.get("truncated")),
        "queue_addressable": sum(1 for item in entries if item["queue_row"]),
        "queue_missing": sum(1 for item in entries if not item["queue_row"]),
        "targets": entries,
    }
    if plan["frontier_page_truncated"]:
        plan["status"] = "blocked"
        plan["warning"] = "frontier page limit reached; widen the repository-derived frontier query"
    if not entries and (result.get("summary", {}).get("eligible", 0) > 0 or any(item.get("claim", {}).get("state") == "coordination_missing" for item in result.get("targets", []))):
        plan["status"] = "blocked"
        plan["warning"] = "eligible targets were not claimable or coordination was unavailable"
    if out:
        write_json_atomic(out, plan)
        plan["path"] = str(out)
    return plan
