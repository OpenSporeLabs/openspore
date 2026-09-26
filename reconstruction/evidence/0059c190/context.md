# Reconstruction context 0x0059c190

- Status: `partial`
- Content SHA-256: `f2a1d3293219442717cd6771e9f2fe0381c469cd0a0970084ef10f3aeca353fa`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0059c190",
  "phase": "reconstruction",
  "target": "0x0059c190"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "QuaternionToMatrix",
  "package": null,
  "subsystem": "GameGlobal",
  "va": "0x0059c190"
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
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "76f6b4bc5e4a877aca807673530e50f571276cf9db592f0c75f6e9554800a7ff",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 QuaternionToMatrix(undefined4 param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  fVar1 = *param_2;
  fVar2 = param_2[1];
  fVar3 = param_2[2];
  fVar4 = param_2[3];
  local_24 = 1.0 - (fVar3 * fVar3 + fVar2 * fVar2) * 2.0;
  local_20 = (fVar4 * fVar3 + fVar2 * fVar1) * 2.0;
  local_1c = (fVar3 * fVar1 - fVar4 * fVar2) * 2.0;
  local_18 = (fVar2 * fVar1 - fVar4 * fVar3) * 2.0;
  local_14 = 1.0 - (fVar3 * fVar3 + fVar1 * fVar1) * 2.0;
  local_10 = (fVar4 * fVar1 + fVar3 * fVar2) * 2.0;
  local_c = (fVar4 * fVar2 + fVar3 * fVar1) * 2.0;
  local_8 = (fVar3 * fVar2 - fVar4 * fVar1) * 2.0;
  local_4 = 1.0 - (fVar2 * fVar2 + fVar1 * fVar1) * 2.0;
  FUN_0041cb40(&local_24);
  return param_1;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 19464,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__cdecl\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\",\n      \"entry_ESP+0x8\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"XMM0\",\n    \"return_semantics\": \"float_or_x87_in_XMM0\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x8\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"calle
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
      "va": "0x0059d610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b1e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005d8f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x009c6fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad12a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae46f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b02fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b134a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b3f3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b421b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b45ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b81780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b81a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b94150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b998a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0059d791",
      "direction": "in",
      "other": "0x0059d610",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [],
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
      "va": "0x0059d610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b1e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005d8f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x009c6fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad12a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae46f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b02fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b134a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b3f3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b421b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b45ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b81780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b81a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b94150"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b998a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bc2900"
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
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00ff3f00",
    "va": "0x00ff3f00"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-C4-CREATURE-WAVE3",
    "score": 3,
    "symbol": "Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460",
    "va": "0x00c1d460"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [],
  "handoffs": [],
  "metadata": []
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
  "unresolved_questions": []
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'ref': 'GhidraMCP /disassemble_function', 'mode': 'derived', 'source_class': 'derived'}, {'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'mode': 'derived', 'source_class': 'derived'}, {'ref': 'ephemeral reconstruction_knowledge.build_index', 'mode': 'derived', 'source_class': 'generated_index'}, {'ref': 'tools/reconstruction_tooling/abi_infer.py', 'mode': 'derived', 'source_class': 'derived'}, {'ref': 'GhidraMCP /disassemble_function', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}`

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
      "ref": "GhidraMCP REST /decompile_function @ http://127.0.0.1:8089",
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
