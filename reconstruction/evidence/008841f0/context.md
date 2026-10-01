# Reconstruction context 0x008841f0

- Status: `partial`
- Content SHA-256: `e04a9343fea81ef40851bfb3cf297a45f7a58781c74e9bf88e9d6854e339473b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x008841f0",
  "phase": "reconstruction",
  "target": "0x008841f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueMessageCleanupWindow",
  "name": "MessageManagerCleanupStorageWalker_008841f0",
  "package": "PKG-06-WAVE6-APP-MANAGERS",
  "subsystem": "App.MessageCleanup",
  "va": "0x008841f0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "67dbf795e261cd51cb2c73848247bdd2d454a50ad1c2c8411340d14147dc66e8",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x008841f0 failed: Decompilation did not complete. Reason: ",
      "mode": "LIVE",
      "status": "unavailable"
    }
  ],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `missing`
- Provenance: ``

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "ordinary_stack_argument_slots": 0,
  "return_register": "EAX is not assigned a defined result by the target body",
  "stack_cleanup_bytes": 0
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00884fb0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00885002",
      "direction": "in",
      "other": "0x00884fb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00884237",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0088424e",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueMessageCleanupPorts",
    "OpaqueMessageCleanupWindow",
    "OpaqueMessageManager",
    "void-like; target does not define EAX"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-message-cleanup-storage-and-release-lifecycle"
    ],
    "validated": 0
  },
  "semantic": {}
}
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00884fb0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00885002",
      "direction": "in",
      "other": "0x00884fb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00884237",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0088424e",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [
    "0x00f47380"
  ],
  "manifest_callers": [
    "0x00884fb0"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0270",
    "size": 1
  },
  "vtable_reference_count": 0
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 8,
    "symbol": "App_IStateManager_Get_0067dce0",
    "va": "0x0067dce0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 8,
    "symbol": "App_IPropManager_Get_0067ddf0",
    "va": "0x0067ddf0"
  },
  {
    "match_basis": [
      "shared_types:OpaqueMessageManager"
    ],
    "package": "PKG-WAVE6-MISC-ENGINE",
    "score": 3,
    "symbol": "message_manager_get_queue_0098f4d0",
    "va": "0x0098f4d0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp",
  "files": [
    "reconstruction/staging/wave6-app-managers/service_accessors_cleanup_model_test.cpp",
    "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-app-managers/008841f0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "anchors": [
        "0x000847f0",
        "0x00883a90",
        "0x00883ad0",
        "0x00883b20",
        "0x008841f0",
        "0x00883a90",
        "0x00883ad0",
        "0x00883b20",
        "0x008841f0",
        "0x000847f0",
        "0x0067dc80",
        "0x0067dc80",
        "0x000847f0",
        "0x000847f0",
        "0x0084bd70",
        "0x0084bd70"
      ],
      "conflict_id": "Q-DISPATCH-ORDER",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
      "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x000847f0",
        "0x00883a90",
        "0x00883ad0",
        "0x00883b20",
        "0x008841f0",
        "0x00883a90",
        "0x00883ad0",
        "0x00883b20",
        "0x008841f0",
        "0x000847f0",
        "0x0067dc80",
        "0x0067dc80",
        "0x000847f0",
        "0x000847f0",
        "0x0084bd70",
        "0x0084bd70"
      ],
      "conflict_id": "Q-QUEUE-LAYOUT",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The 0x
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-app-managers/008841f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-app-managers/service_accessors_cleanup_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
    },
    {
      "mode": "derived",
      "ref": "tools/reconstruction_tooling/abi_infer.py",
      "source_class": "derived"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "ghidra"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "ghidra"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/research/source-reconstruction-manifest.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/triage/queue-f0e310e0-v6.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave6-app-managers/008841f0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-app-managers/service_accessors_cleanup_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/i
[TRUNCATED]
```
