# Reconstruction context 0x007d8d40

- Status: `partial`
- Content SHA-256: `e0654805090bde0ae564900927c3e2d4ffc461362a5988403d7a03fce87dfec8`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007d8d40",
  "phase": "reconstruction",
  "target": "0x007d8d40"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": null,
  "va": "0x007d8d40"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "39948410cf91340d524bf280a216f1d6269dd05874a33f7d5400716a704ae3ae",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x007d8d40 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 1,
  "return_register": "EAX is not assigned a defined result by the target body"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007d8cc0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007d8e20"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x007d8e23",
      "direction": "in",
      "other": "0x007d8e20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007d8d8f",
      "direction": "out",
      "other": "0x007d8cc0",
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
    "void-like; target does not define EAX"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
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
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007d8cc0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007d8e20"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x007d8e23",
      "direction": "in",
      "other": "0x007d8e20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007d8d8f",
      "direction": "out",
      "other": "0x007d8cc0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 1,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0247",
    "size": 1
  },
  "vtable_reference_count": 6
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_types:void-like; target does not define EAX"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 3,
    "symbol": "MessageManagerCleanupStorageWalker_008841f0",
    "va": "0x008841f0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave6-app-managers/app_managers_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave6-app-managers/007d8d40.json"
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
  "original_bytes": 9353,
  "preview": "{\n  \"conflicts\": {\n    \"original_bytes\": 9739,\n    \"preview\": \"[\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x00b3d350\\\",\\n      \\\"0x00e818f0\\\",\\n      \\\"0x00b3d350\\\",\\n      \\\"0x00e818f0\\\",\\n      \\\"0x00b3d350\\\",\\n      \\\"0x007d8060\\\",\\n      \\\"0x007d8060\\\",\\n      \\\"0x007d8360\\\",\\n      \\\"0x007d8360\\\",\\n      \\\"0x007d85b0\\\",\\n      \\\"0x007d85b0\\\",\\n      \\\"0x007d8c30\\\",\\n      \\\"0x007d8c30\\\",\\n      \\\"0x007d8c80\\\",\\n      \\\"0x007d8c80\\\",\\n      \\\"0x007d8d40\\\"\\n    ],\\n    \\\"conflict_id\\\": \\\"Q-INPUT-ROUTING\\\",\\n    \\\"kind\\\": \\\"conflict_ledger\\\",\\n    \\\"rejected\\\": [],\\n    \\\"resolution\\\": \\\"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\\\",\\n    \\\"resolution_status\\\": \\\"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\\\",\\n    \\\"source\\\": \\\"knowledgegraph/research/conflicts/track-c-state-events.json\\\",\\n    \\\"subject\\\": null,\\n    \\\"unresolved_reason\\\": \\\"Runtime reachability is absent or the required direct body/call path is not recovered.\\\"\\n  },\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x00d2e380\\\",\\n      \\\"0x00d2e480\\\",\\n      \\\"0x00d2e8a0\\\",\\n      \\\"0x00d39360\\\",\\n      \\\"0x045ab96e\\\",\\n      \\\"0x00d2e480\\\",\\n      \\\"0x00aebe90\\\",\\n      \\\"0x045ab96e\\\",\\n      \\\"0x0067dcd0\\\",\\n      \\\"0x0067dcd0\\\"
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-app-managers/007d8d40.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-app-managers/app_managers_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave6-app-managers/007d8d40.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-app-managers/app_managers_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
    "CONTROL FLOW",
    "VIRTUAL DISPATCH",
    "RETURN SEMANTICS",
    "EVIDENCE COVERAGE"
  ]
}
```
