# Reconstruction context 0x0067dcd0

- Status: `partial`
- Content SHA-256: `7a564678dd837672e1e1c290615f0168e41b73bcb033c3753e078a0a769ac976`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0067dcd0",
  "phase": "reconstruction",
  "target": "0x0067dcd0"
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
  "va": "0x0067dcd0"
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
  "content_sha256": "cee05250f32cceeb84853d9c45f0011e32264abb3830b0e192f5a0dff7141683",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0067dcd0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__cdecl",
  "ordinary_stack_argument_slots": 0,
  "return_note": "borrowed pointer word",
  "return_register": "EAX",
  "return_width_bytes": 4,
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
      "va": "0x004021a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00402cc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00403af0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00404660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00407280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00411e50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00415730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004157d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00417210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00417600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00418500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0041a0c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00430e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00466690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0046c900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ae3b0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x004021b7",
      "direction": "in",
      "other": "0x004021a0",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x015fd894",
    "global:g_wave6_app_manager_globals.app_game_mode_manager_015fd894"
  ],
  "types": [
    "OpaqueAppGameModeManager*",
    "READ",
    "WRITE",
    "borrowed pointer word",
    "undefined4"
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004021a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00402cc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00403af0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00404660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00407280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00411e50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00415730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004157d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00417210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00417600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00418500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0041a0c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00430e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00466690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0046c900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004ae3b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004badd0"
    },
    {
      "name": null,
      "reconst
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_types:READ,WRITE,undefined4",
      "same_calling_convention"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 11,
    "symbol": "App_IStateManager_Get_0067dce0",
    "va": "0x0067dce0"
  },
  {
    "match_basis": [
      "shared_types:READ,WRITE,undefined4",
      "same_calling_convention"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 11,
    "symbol": "App_IPropManager_Get_0067ddf0",
    "va": "0x0067ddf0"
  },
  {
    "match_basis": [
      "shared_types:READ,WRITE"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE8",
    "score": 6,
    "symbol": "ui_layer_manager_get_0067ca90",
    "va": "0x0067ca90"
  },
  {
    "match_basis": [
      "shared_types:READ,WRITE"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE8",
    "score": 6,
    "symbol": "anim_manager_get_0067cae0",
    "va": "0x0067cae0"
  },
  {
    "match_basis": [
      "shared_types:READ,WRITE"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE8",
    "score": 6,
    "symbol": "app_locale_manager_get_0067de00",
    "va": "0x0067de00"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE11",
    "score": 3,
    "symbol": "palette_safe_wave11_fill_node_array_005c7ff0",
    "va": "0x005c7ff0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 3,
    "symbol": "service_005fa8d0",
    "va": "0x005fa8d0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "sco
[TRUNCATED]
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
    "reconstruction/metadata/wave6-app-managers/0067dcd0.json"
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
        "0x00d2e380",
        "0x00d2e480",
        "0x00d2e8a0",
        "0x00d39360",
        "0x045ab96e",
        "0x00d2e480",
        "0x00aebe90",
        "0x045ab96e",
        "0x0067dcd0",
        "0x0067dcd0",
        "0x007d8420",
        "0x007d8420",
        "0x007d8cf0",
        "0x007d8cf0",
        "0x007d8d40",
        "0x007d8d40"
      ],
      "conflict_id": "U-005-evolution-level-promotion",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
      "resolution_status": "0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00594b10",
        "0x00594b10",
        "0x00596da0",
        "0x00596da0",
        "0x00597390",
        "0x00597390",
        "0x00597400",
        "0x00597400",
        "0x00598db0",
        "0x00598db0",
        "0x00598e90",
        "0x00598e90",
        "0x00599440",
        "0x00599440",
        "0x0067dcd0",
        "0x0067dcd0"
      ],
      "conflict_id": "baby_growth_transition",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evi
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-app-managers/0067dcd0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-app-managers/app_managers_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave6-app-managers/0067dcd0.json",
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
