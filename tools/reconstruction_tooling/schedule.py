"""Dependency-aware grouping of frontier targets into dispatch waves.

The rule this module exists to enforce: *do not serialize work that does not
depend on itself*. Three specific things it refuses to do:

* it does not use ``package`` as a grouping key. ``package`` is null for
  252/368 frontier targets and its 60 populated values label already-integrated
  work, so grouping by it would collapse the whole frontier into a handful of
  buckets and run them one at a time;
* it does not use ``analogue`` as an edge. Analogues are shared-signal context
  (same package, shared types, same vtable) computed by
  ``reconstruction_knowledge.analogue_record``; they are attached to the
  briefing as context and never gate dispatch;
* it does not treat co-membership of a cluster as a dependency.

A target is a *unit* on its own unless it is genuinely in a cycle, in which
case the whole strongly-connected component is one unit, because mutual
recursion cannot be ordered. Genuine ordering comes only from call edges to
another target in the same plan, and a target is only held back when a
prerequisite it actually calls is itself un-reconstructed.
"""

import sqlite3

from .models import ROOT

# Call-shaped xref types. vtable-ref and data-ref are excluded: they describe
# dispatch candidates, not an ordering between two reconstructions, and
# including them would manufacture cycles out of every shared vtable.
CALL_REFERENCE_TYPES = ("direct-call", "thunk", "computed-call")
EDGE_QUERY = (
    "SELECT caller_va, callee_va, reference_type, callsite_va FROM xref "
    "WHERE reference_type IN (%s)" % ",".join("?" * len(CALL_REFERENCE_TYPES))
)


def _tarjan(adjacency):
    # type: (dict) -> list
    """Iterative Tarjan SCC. Returns components in a deterministic order.

    Iterative on purpose: a recursive implementation would hit Python's
    recursion limit on a 368-node component, and determinism matters because
    the plan output is compared byte-for-byte.
    """
    index = {}
    low = {}
    on_stack = {}
    stack = []
    result = []
    counter = 0
    for root in sorted(adjacency):
        if root in index:
            continue
        work = [(root, iter(sorted(adjacency[root])))]
        index[root] = low[root] = counter
        counter += 1
        stack.append(root)
        on_stack[root] = True
        while work:
            node, children = work[-1]
            advanced = False
            for child in children:
                if child not in index:
                    index[child] = low[child] = counter
                    counter += 1
                    stack.append(child)
                    on_stack[child] = True
                    work.append((child, iter(sorted(adjacency.get(child, ())))))
                    advanced = True
                    break
                if on_stack.get(child):
                    low[node] = min(low[node], index[child])
            if advanced:
                continue
            work.pop()
            if low[node] == index[node]:
                component = []
                while True:
                    member = stack.pop()
                    on_stack[member] = False
                    component.append(member)
                    if member == node:
                        break
                result.append(sorted(component))
            if work:
                parent = work[-1][0]
                low[parent] = min(low[parent], low[node])
    return sorted(result, key=lambda item: (len(item), item))


def scc_partition(root=ROOT, vas=None, db=None, universe_scope=True):
    # type: (object, object, object, bool) -> dict
    """Map each VA to its component id, size and members.

    Two different notions of "component", and conflating them would be a bug:

    ``members_by_id``  the *scheduling* component -- only VAs in this plan.
        Two plan members in one component must go to one worker, because
        mutual recursion cannot be ordered between them.
    ``cycle_members``  the *analysis* component -- every member in the whole
        binary. A plan target can be a singleton for scheduling while still
        sitting inside a nine-function cycle whose siblings are not in this
        run. That is still worth reporting: the worker has to know the cycle
        exists even though it cannot resolve it alone.

    Edges come from the xref table, which stores bare 8-char hex while the
    planning layer speaks ``0x%08x``, so endpoints are translated through one
    map rather than compared across formats.
    """
    universe = set(vas or ())
    empty = {"id_by_va": {}, "members_by_id": {}, "component_of": {},
             "cycle_members": {}, "edge_count": 0, "degraded": True}
    if not universe:
        return empty
    by_bare = {va[2:] if va.startswith("0x") else va: va for va in universe}
    if db is None:
        return dict(empty)
    try:
        cursor = db.execute(EDGE_QUERY, CALL_REFERENCE_TYPES)
    except sqlite3.Error:
        return dict(empty)
    plan_adjacency = {va: set() for va in universe}
    # Full call graph, built only when the caller asked for cycle reporting.
    full_adjacency = {} if universe_scope else None
    plan_edges = 0
    total_edges = 0
    for caller, callee, _kind, _site in cursor:
        if full_adjacency is not None:
            full_adjacency.setdefault(caller, set()).add(callee)
            total_edges += 1
        source = by_bare.get(caller)
        sink = by_bare.get(callee)
        if source is None or sink is None or source == sink:
            continue
        plan_adjacency[source].add(sink)
        plan_edges += 1
    if plan_edges == 0:
        # No usable xref evidence: report every target as its own scheduling
        # component rather than guessing. Singletons are the honest answer and
        # the plan records that the check was degraded.
        components = [[va] for va in sorted(universe)]
    else:
        components = _tarjan(plan_adjacency)
    id_by_va = {}
    members_by_id = {}
    for number, component in enumerate(components, start=1):
        identifier = "scc-%04d" % number
        members_by_id[identifier] = component
        for va in component:
            id_by_va[va] = identifier
    cycle_members = {}
    if full_adjacency is not None and total_edges:
        for component in _tarjan(full_adjacency):
            if len(component) < 2:
                continue
            translated = ["0x" + va for va in component]
            for va in component:
                cycle_members["0x" + va] = translated
    return {
        "id_by_va": id_by_va,
        "members_by_id": members_by_id,
        "component_of": {identifier: list(component)
                         for identifier, component in members_by_id.items()},
        "cycle_members": cycle_members,
        "edge_count": plan_edges,
        "universe_edges": total_edges,
        "degraded": plan_edges == 0,
    }

def _reconstructed(index, va):
    # type: (dict, str) -> bool
    records = (index or {}).get("records") or {}
    record = records.get(va) or {}
    if not record:
        return False
    return bool(record.get("reconstructed")) or str(
        record.get("status") or "") in ("reconstructed", "integrated")


def _open_callees(target, vas, index):
    # type: (dict, set, dict) -> list
    """Callees inside the plan that are not reconstructed yet.

    This is the only thing that creates an ordering edge. A callee outside the
    plan is context, not a blocker: it is not going to be done by this run, and
    deferring on it would stall the frontier forever.
    """
    raw = target.get("dependencies")
    nested = raw if isinstance(raw, dict) else {}
    candidates = []
    candidates.extend(nested.get("open_callees") or [])
    if isinstance(raw, list):
        candidates.extend(raw)
    candidates.extend(target.get("open_callees") or [])
    candidates.extend(target.get("open_dependencies") or [])
    for row in nested.get("edges") or []:
        if isinstance(row, dict) and row.get("direction") == "out" \
                and row.get("other"):
            candidates.append(row["other"])
    result = set()
    for value in candidates:
        if not isinstance(value, str):
            continue
        text = value.strip().lower()
        if text.startswith("0x"):
            text = text[2:]
        if len(text) != 8:
            continue
        try:
            int(text, 16)
        except ValueError:
            continue
        canonical = "0x" + text
        if canonical in vas and not _reconstructed(index, canonical):
            result.add(canonical)
    return sorted(result)


def classify(targets, index, partition):
    # type: (list, dict, dict) -> list
    """Assign each target a scheduling role. Mutually exclusive, ordered.

    Precedence matters and follows the existing ``frontier`` disposition
    ladder: something that is claimed, blocked, or finished is not available
    work regardless of what else is true about it.
    """
    vas = {target["va"] for target in targets}
    id_by_va = partition.get("id_by_va") or {}
    members_by_id = partition.get("members_by_id") or {}
    cycle_members = partition.get("cycle_members") or {}
    classified = []
    for target in targets:
        va = target["va"]
        identifier = id_by_va.get(va)
        members = members_by_id.get(identifier) or [va]
        cycle = cycle_members.get(va) or [va]
        claim_state = target.get("claim_state")
        open_callees = _open_callees(target, vas, index)
        record = (index or {}).get("records", {}).get(va) or {}
        if target.get("block_reason") or claim_state == "blocked":
            role, reason = "blocked", target.get("block_reason") or "blocked"
        elif claim_state in ("claimed", "active_unowned", "stale_binary",
                             "coordination_missing"):
            role, reason = "claimed", claim_state
        elif target.get("queue_row") is not None and claim_state == "completed":
            role, reason = "completed", claim_state
        elif _reconstructed(index, va) or str(
                record.get("status") or "") == "reconstructed":
            role, reason = "completed", "reconstructed"
        elif len(members) > 1:
            role, reason = "coordinated", "strongly_connected_component"
        elif open_callees:
            role, reason = "dependent", "open_callees"
        elif target.get("dependency_uncertain"):
            role, reason = "uncertain", "dependency_uncertain"
        else:
            role, reason = "independent", "no_open_internal_callees"
        classified.append({
            "va": va,
            "role": role,
            "reason": reason,
            "score": target.get("priority", 0),
            "queue_id": target.get("queue_id"),
            "queue_va": target.get("queue_va"),
            "queue_row": target.get("queue_row"),
            "claimable": bool(target.get("claimable")),
            "claim_state": claim_state,
            "scc": {"id": identifier, "size": len(members), "members": members,
                    "cycle_size": len(cycle), "cycle_members": cycle,
                    "cycle_plan_members": len(set(cycle) & vas)},
            "open_callees": open_callees,
            "name": target.get("name"),
            "cluster": target.get("cluster"),
            "subsystem": target.get("subsystem"),
            "runtime_gated": bool(target.get("runtime_gated")),
            "evidence_ready": bool(target.get("evidence_ready")),
        })
    return classified


def waves(classified):
    # type: (list) -> list
    """Order dispatchable work into waves; a wave is maximally parallel.

    Independent targets and whole SCC units are the parallel bulk. Dependent
    targets wait for the wave that contains their open callees, which is the
    only serialization the dependency graph actually justifies.
    """
    by_va = {item["va"]: item for item in classified}
    available = [item for item in classified
                 if item["role"] in ("independent", "coordinated", "dependent",
                                     "uncertain")]
    # A coordinated unit is scheduled by its lowest-sorting member so the unit
    # is emitted exactly once and deterministically.
    emitted = set()
    schedule = []
    remaining = sorted(available, key=lambda item: (-item["score"], item["va"]))
    completed = set()
    guard = 0
    while remaining:
        guard += 1
        if guard > len(available) + 2:  # pragma: no cover - cycle backstop
            break
        ready, blocked_now = [], []
        for item in remaining:
            if item["va"] in emitted:
                continue
            prerequisites = [dep for dep in item["open_callees"]
                             if dep in by_va and dep not in completed]
            if prerequisites:
                blocked_now.append(item)
                continue
            ready.append(item)
        if not ready:
            # Every remaining target waits on another remaining target. That is
            # a cycle the SCC pass did not catch (it only sees call edges) or a
            # prerequisite outside the plan. Report rather than loop.
            schedule.append({
                "index": len(schedule),
                "reason": "no_progress",
                "targets": [],
                "waiting_on": sorted(
                    {dep for item in blocked_now
                     for dep in item["open_callees"]
                     if dep in by_va and dep not in completed}),
            })
            break
        for item in ready:
            emitted.add(item["va"])
            completed.add(item["va"])
        schedule.append({
            "index": len(schedule),
            "reason": "ready",
            "targets": [
                {
                    "va": item["va"],
                    "queue_id": item["queue_id"],
                    "queue_va": item["queue_va"],
                    "role": item["role"],
                    "score": item["score"],
                    "unit": item["scc"]["id"] if item["role"] == "coordinated" else None,
                    "unit_members": item["scc"]["members"]
                    if item["role"] == "coordinated" else [item["va"]],
                    "name": item["name"],
                    "cluster": item["cluster"],
                    "subsystem": item["subsystem"],
                    "runtime_gated": item["runtime_gated"],
                }
                for item in sorted(ready, key=lambda entry: (-entry["score"], entry["va"]))
            ],
        })
        remaining = [item for item in blocked_now if item["va"] not in emitted]
    return schedule
