# Frontier scoring

The frontier pool is the canonical triage queue plus the generated index frontier. It does not invent targets from the full binary inventory.

## Eligibility

- reconstructed, blocked, completed, or terminal targets are excluded;
- an active owner or stale binary claim is excluded;
- open internal callees defer a target;
- runtime/operator gates remain visible and reduce ordering priority;
- the claim state is read from SQLite `investigations` in read-only mode.

## Components

The score is an ordering aid, not evidence or confidence:

- classifier priority: P0 35, P1 21, P2 11, P3 4;
- evidence scale: `UNKNOWN` through `VERIFIED`, scaled by four;
- inspectability: existing decompilation/source/metadata paths;
- dependency readiness: internal callee state and reconstructed callers;
- reconstructed analogues;
- same-cluster batching;
- runtime/operator penalty when gates exist.

All components are emitted in `score_components`. Reasons identify the source and whether a dimension is persisted, derived, or missing. Missing evidence is not silently converted to zero in the reason list.

## Dependency behavior

Only function-level call dependencies are used for readiness. Product/subsystem cluster lists are hints, not callee edges. A target with unresolved internal callees is `deferred`; it remains visible for ordered work.

## Swarm output

`openspore swarm` returns:

```json
{
  "targets": [
    {
      "va": "0x008db310",
      "priority": 91,
      "dependencies": [],
      "evidence_ready": true,
      "claimable": true
    }
  ]
}
```

Only eligible targets are emitted. The queue is a plan; it does not acquire ownership.
