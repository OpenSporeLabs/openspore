# Reconstruction context 0x00b3d420

- Status: `partial`
- Content SHA-256: `47dcfa24c44d7a11538b638407d561750c428ffe8393adcc25a48c929061e5b1`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d420",
  "phase": "reconstruction",
  "target": "0x00b3d420"
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
  "va": "0x00b3d420"
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
  "content_sha256": "577ed9d40530eafb8feed2371d7204799089facdc4e085eb3d550eeda5b48d5b",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b3d420 failed: Decompilation did not complete. Reason: ",
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
      "va": "0x00b02b90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b04aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b07980"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b07fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2b1e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2b430"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2bbe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2f350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b330e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b334e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b73f30"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b02b9b",
      "direction": "in",
      "other": "0x00b02b90",
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
    "global:0x0167eb2c",
    "global:g_wave6_app_manager_globals.simulator_game_mode_manager_0167eb2c"
  ],
  "types": [
    "OpaqueSimulatorGameModeManager*",
    "READ",
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
      "va": "0x00b02b90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b04aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b07980"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b07fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2b1e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2b430"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2bbe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2f350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32f60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b330e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b334e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b73f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b76f10"
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
      "shared_types:READ,undefined4",
      "same_calling_convention"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 8,
    "symbol": "App_IStateManager_Get_0067dce0",
    "va": "0x0067dce0"
  },
  {
    "match_basis": [
      "shared_types:READ,undefined4",
      "same_calling_convention"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 8,
    "symbol": "App_IPropManager_Get_0067ddf0",
    "va": "0x0067ddf0"
  },
  {
    "match_basis": [
      "shared_types:READ"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE8",
    "score": 3,
    "symbol": "ui_layer_manager_get_0067ca90",
    "va": "0x0067ca90"
  },
  {
    "match_basis": [
      "shared_types:READ"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE8",
    "score": 3,
    "symbol": "anim_manager_get_0067cae0",
    "va": "0x0067cae0"
  },
  {
    "match_basis": [
      "shared_types:READ"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE8",
    "score": 3,
    "symbol": "app_locale_manager_get_0067de00",
    "va": "0x0067de00"
  },
  {
    "match_basis": [
      "shared_types:READ"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 3,
    "symbol": "simulator_game_input_manager_get_00b3d350",
    "va": "0x00b3d350"
  },
  {
    "match_basis": [
      "shared_types:undefined4"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 3,
    "symbol": "root_accessor_00b3d3b0",
    "va": "0x00b3d3b0"
  },
  {
    "match_basis": [
      "shared_types:undefined4"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 3,
    "symbol": "root_accessor_
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
    "reconstruction/metadata/wave6-app-managers/00b3d420.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "How does this manager relate to the App IGameModeManager service at 0x015fd894?",
    "Is the returned manager borrowed, retained, or invalidated during lifecycle transitions?",
    "What concrete cGameModeManager subtype and vtable are stored in the slot?",
    "Which code publishes or replaces DAT_0167eb2c?"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-app-managers/00b3d420.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-app-managers/app_managers_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave6-app-managers/00b3d420.json",
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
