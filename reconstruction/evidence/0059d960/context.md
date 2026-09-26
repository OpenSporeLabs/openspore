# Reconstruction context 0x0059d960

- Status: `partial`
- Content SHA-256: `016515b98d3484e34306ce9fe12db697383d7b306091eeccb09da66054a25e74`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0059d960",
  "phase": "reconstruction",
  "target": "0x0059d960"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "cEditorAnimEvent__ctor",
  "package": null,
  "subsystem": "GameGlobal",
  "va": "0x0059d960"
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
  "content_sha256": "2c847f3226531bd0b654f99698be6ab62cd1645a077ba8e1a9d2f270bd826064",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

void __fastcall cEditorAnimEvent__ctor(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_013eb918;
  param_1[1] = &PTR_LAB_013f65b4;
  LOCK();
  param_1[2] = 0;
  UNLOCK();
  param_1[8] = 0;
  *param_1 = &PTR_LAB_013f65d4;
  param_1[1] = &PTR_LAB_013f65c4;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  *(undefined1 *)(param_1 + 7) = 0;
  *(undefined1 *)(param_1 + 9) = 0;
  param_1[10] = 0xffffffff;
  param_1[0xb] = 0x3f800000;
  return;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 7034,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__fastcall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"XMM0\",\n    \"return_semantics\": \"float_or_x87_in_XMM0\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"CORE_RESOLVED\",\n  \"conflicts\": [],\n  \"content_sha256\": \"e651e629bf172f02727364fab1df4296232b80cb7c1de9a316ae49a8ba667378\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": \"__fastcall\",\n    \"candidate_conventions\": [\n      \"__fastcall\"\n    ],\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0008\"\n      ],\n      \"claim\"
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
      "va": "0x00573970"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00574110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00591690"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005ad430"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b1e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b4fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b94b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bc630"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005739b0",
      "direction": "in",
      "other": "0x00573970",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00574196",
      "direction": "in",
      "other": "0x00574110",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057e5d7",
      "direction": "in",
      "other": "0x0057e480",
      
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
      "va": "0x00573970"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00574110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0058a5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00591690"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005ad430"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b1e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b4fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b94b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005bc630"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005739b0",
      "direction": "in",
      "other": "0x00573970",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00574196",
      "direction": "in",
      "other": "0x00574110",
      "reference_type": "direct-call"
    },
    {
      "
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
