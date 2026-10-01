# Reconstruction context 0x00d2e830

- Status: `partial`
- Content SHA-256: `f23b39721e15d6fd19036b40cf968a70643326192e888496a08211f12d6ad72b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d2e830",
  "phase": "reconstruction",
  "target": "0x00d2e830"
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
  "va": "0x00d2e830"
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
  "content_sha256": "a85ad59f17219a57b4fd74b820271ff28fff1fb63026804e0794a8b28428f0e5",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00d2e830 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 9916,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"ST0\",\n    \"return_semantics\": \"float_or_x87_in_ST0\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"PARTIAL\",\n  \"conflicts\": [],\n  \"content_sha256\": \"c7f2e29d9f83275d449d8aadea5b58d1d3097c4f98ed1c72b6a0f1ca4eccfac8\",\n  \"conventions\": {\n    \"ambiguities\": [\n      \"esp_alignment_unknown\"\n    ],\n    \"calling_convention\": null,\n    \"candidate_conventions\": [\n      \"__cdecl\",\n      \"__stdcall\",\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"UNKNOWN\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel",
      "reconstructed": true,
      "va": "0x00d2e380"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3fcf0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00d3fd2f",
      "direction": "in",
      "other": "0x00d3fcf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2e834",
      "direction": "out",
      "other": "0x00b3d300",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2e861",
      "direction": "out",
      "other": "0x00d2e380",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2e83b",
      "direction": "out",
      "other": "0x00f67d90",
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
      "No original-process level-selection trace has been run.",
      "Observe 0x0167eae0, the +0x74 returned object, the +0x10f0 float, and the four threshold globals in an original process.",
      "Resolve concrete progression-player and noun-manager ownership and threshold writers."
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
  "callees": [
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel",
      "reconstructed": true,
      "va": "0x00d2e380"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d3fcf0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00d3fd2f",
      "direction": "in",
      "other": "0x00d3fcf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2e834",
      "direction": "out",
      "other": "0x00b3d300",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2e861",
      "direction": "out",
      "other": "0x00d2e380",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d2e83b",
      "direction": "out",
      "other": "0x00f67d90",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 2,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x00b3d300",
    "0x00d2e380"
  ],
  "scc": {
    "id": "scc-0503",
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
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
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
    "va": "0x00d2e
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
    "reconstruction/metadata/pkg13-c1-creature-progression/00d2e830.json"
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
    "No original-process level-selection trace has been run.",
    "Observe 0x0167eae0, the +0x74 returned object, the +0x10f0 float, and the four threshold globals in an original process.",
    "Resolve concrete progression-player and noun-manager ownership and threshold writers.",
    "The SDK semantic name for this selector is unresolved; the normalized symbol remains opaque.",
    "The later virtual action selected by the caller after sentinel 4 is outside this target.",
    "The runtime relationship between the progression-player +0x10f0 field and DAT_0169e398 is not established by this body."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-c1-creature-progression/00d2e830.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c1-creature-progression/creature_progression.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c1-creature-progression/creature_progression.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-c1-creature-progression/creature_progression_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg13-c1-creature-progression/00d2e830.json",
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
