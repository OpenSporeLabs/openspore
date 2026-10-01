# Reconstruction context 0x00d2e480

- Status: `partial`
- Content SHA-256: `83dfee62377fdcb789c8a5d368bc095e5e759a76276b5dc5089f6dcee8b98a3a`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d2e480",
  "phase": "reconstruction",
  "target": "0x00d2e480"
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
  "va": "0x00d2e480"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "c190bbf2a6739b575aae92c4093d4c2f3b52a51e261890f7817719c5d8d979d7",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00d2e480 failed: Decompilation did not complete. Reason: ",
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
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 6702,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__cdecl\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"XMM0\",\n    \"return_semantics\": \"float_or_x87_in_XMM0\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"CORE_RESOLVED\",\n  \"conflicts\": [],\n  \"content_sha256\": \"fb899eb38dae99db1fa379ca778c59d8f176442b143331c3e28bc4a4dfcf241a\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": \"__cdecl\",\n    \"candidate_conventions\": [\n      \"__cdecl\",\n      \"__thiscall\"\n  
[TRUNCATED]
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
      "va": "0x00d40230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d43e30"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00d4031b",
      "direction": "in",
      "other": "0x00d40230",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d44272",
      "direction": "in",
      "other": "0x00d43e30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d445fa",
      "direction": "in",
      "other": "0x00d43e30",
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
  "globals": [
    "global:0x0169e398",
    "global:DAT_0169e398",
    "global:float"
  ],
  "types": [
    "UNCONDITIONAL_CALL",
    "float"
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
      "Actual runtime evolution-point values and caller save-restoration context remain unobserved.",
      "The owner and initialization of DAT_0169e398 remain outside this target."
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
      "va": "0x00d40230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d43e30"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00d4031b",
      "direction": "in",
      "other": "0x00d40230",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d44272",
      "direction": "in",
      "other": "0x00d43e30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d445fa",
      "direction": "in",
      "other": "0x00d43e30",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 2,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0501",
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
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005bf9d0",
    "va": "0x005bf9d0"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005c0100",
    "va": "0x005c0100"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005c0380",
    "va": "0x005c0380"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "wave6-resources",
    "score": 3,
    "symbol": "property_list_has_property_006a2470",
    "va": "0x006a2470"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "wave6-resources",
    "score": 3,
    "symbol": "property_list_get_property_object_006a24d0",
    "va": "0x006a24d0"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-13-C4-CREATURE-WAVE3",
    "score": 3,
    "symbol": "Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460",
    "va": "0x00c1d460"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-13-C3-CREATURE-PROGRESSION-WAVE2",
    "score": 3,
    "symbol": "Simulator_cCreatureGameData_Get_00d2e340",
    "va": "0x00d2e340"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-13-C3-CREATURE-PROGRESSION-WAVE2",
    "score": 3,
    "symbol": "Simulator_c
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg13-c1-creature-progression/creature_progression.cpp",
    "reconstruction/staging/pkg13-c1-creature-progression/creature_progression.hpp",
    "reconstruction/staging/pkg13-c1-creature-progression/creature_progression_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg13-c1-creature-progression/00d2e480.json"
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
        "0x00d2e480",
        "0x00d2e480",
        "0x00d01410",
        "0x00d01410",
        "0x00d01ab0",
        "0x00d01ab0",
        "0x00d01e30",
        "0x00d01e30",
        "0x00d01f50",
        "0x00d01f50",
        "0x00d01ff0",
        "0x00d01ff0",
        "0x00d038e0",
        "0x00d038e0",
        "0x00d065a0",
        "0x00d065a0"
      ],
      "conflict_id": "U-003-civilization-progression",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
      "resolution_status": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00be34a0",
        "0x00d2e480",
        "0x00d2e480",
        "0x00aeb7b0",
        "0x00aeb160",
        "0x00aeb160",
        "0x00aeb7b0",
        "0x00aeb7b0",
        "0x00aebe90",
        "0x00aebe90",
        "0x00be34a0",
        "0x00d01410",
        "0x00d01410",
        "0x00d01ab0",
        "0x00d01ab0",
        "0x00d01e30"
      ],
      "conflict_id": "U-004-city-buildings",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The declared state surface is retained, but the comple
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-c1-creature-progression/00d2e480.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c1-creature-progression/creature_progression.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c1-creature-progression/creature_progression.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c1-creature-progression/creature_progression_model_test.cpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "derived"
    },
    {
      "mode": "derived",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "derived"
    },
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
      "ref": "reconstruction/metadata/pkg13-c1-creature-progression/00d2e480.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-c1-creature-progression/creature_progression.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-c1
[TRUNCATED]
```
