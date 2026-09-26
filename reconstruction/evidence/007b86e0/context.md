# Reconstruction context 0x007b86e0

- Status: `partial`
- Content SHA-256: `a90b92849716387287aab2179807e8132cc428ce3b8eefba0cf38d0f748e05f5`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007b86e0",
  "phase": "reconstruction",
  "target": "0x007b86e0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_007b86e0",
  "package": null,
  "subsystem": "Editor",
  "va": "0x007b86e0"
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
  "content_sha256": "b7d7aa44bad61bcd0f89656745ac298da9a5ecb4cc44a6792f7b819767905abc",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

int __fastcall FUN_007b86e0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 8) + -1;
  *(int *)(param_1 + 8) = iVar1;
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 8) = 1;
    (*(code *)**(undefined4 **)(param_1 + 4))(1);
    iVar1 = 0;
  }
  return iVar1;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 6816,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"integral_in_EAX\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"CORE_RESOLVED\",\n  \"conflicts\": [],\n  \"content_sha256\": \"a7fc653e73d27eda207f38e9d44c25eb44cc12c298cb1f94f49330b4818b385d\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": \"__thiscall\",\n    \"candidate_conventions\": [\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 1,\n    \"vtable_shaped_load
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
      "va": "0x00650190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00658c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0065e110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076dee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00782660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bb670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bced0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007c1c10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00801230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b60d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e642a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ed8a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f33bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fffdd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01070290"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00650349",
      "direction": "in",
      "other": "0x00650190",
      "reference_type": "computed-call"
    }
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [],
  "vtables": [
    "vtable:0x013f56a8",
    "vtable:0x013f57f8",
    "vtable:0x013f625c",
    "vtable:0x013f6364",
    "vtable:0x013f68c4",
    "vtable:0x013f6ae0",
    "vtable:0x013f6cec",
    "vtable:0x013f6d6c",
    "vtable:0x013f6de4",
    "vtable:0x013f6f14",
    "vtable:0x013f6fc0",
    "vtable:0x013f7b54"
  ]
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
      "va": "0x00650190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00658c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0065e110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076dee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00782660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bb670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bced0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007c1c10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00801230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b60d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e642a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ed8a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f33bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fffdd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01070290"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00650349",
      "directi
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_vtable:vtable:0x014542e8,vtable:0x014626b8"
    ],
    "package": "PKG-WAVE6-CONTAINERS-MEMORY",
    "score": 4,
    "symbol": "wave6_reference_00432a50",
    "va": "0x00432a50"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_005737d0",
    "va": "0x005737d0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_00585890",
    "va": "0x00585890"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_00585d10",
    "va": "0x00585d10"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_00588570",
    "va": "0x00588570"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_0058ac10",
    "va": "0x0058ac10"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_0058b650",
    "va": "0x0058b650"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x0147c9e8,vtable:0x0147cc14"
    ],
    "package": "PKG-16-SPOREPEDIA-ONLINE",
    "score": 4,
    "symbol": "Sporepedia_cSPAssetDataOTDB_IsEditab
[TRUNCATED]
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
