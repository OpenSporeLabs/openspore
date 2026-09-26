# Reconstruction context 0x0059c740

- Status: `partial`
- Content SHA-256: `40d7c4aff5bebbd2580e17a96e6d243b98c0e6a50634d0c9205300f4fae56321`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0059c740",
  "phase": "reconstruction",
  "target": "0x0059c740"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "map_int_EditorCreatureControllerPtr__get",
  "package": null,
  "subsystem": "GameGlobal",
  "va": "0x0059c740"
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
  "content_sha256": "82ca3c3e315ea14f80aee1dcf7956434a0f021217dab80956afd1612a475c6a8",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 * __thiscall map_int_EditorCreatureControllerPtr__get(int param_1,uint *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint local_8 [2];
  
  puVar1 = (undefined4 *)(param_1 + 4);
  puVar4 = puVar1;
  if (*(undefined4 **)(param_1 + 0xc) != (undefined4 *)0x0) {
    puVar2 = *(undefined4 **)(param_1 + 0xc);
    do {
      if ((uint)puVar2[4] < *param_2) {
        puVar3 = (undefined4 *)*puVar2;
      }
      else {
        puVar3 = (undefined4 *)puVar2[1];
        puVar4 = puVar2;
      }
      puVar2 = puVar3;
    } while (puVar3 != (undefined4 *)0x0);
  }
  if ((puVar4 != puVar1) && ((uint)puVar4[4] <= *param_2)) {
    return puVar4 + 5;
  }
  local_8[0] = *param_2;
  param_2 = (uint *)((uint)param_2 & 0xffffff00);
  local_8[1] = 0;
  FUN_0059c520(&param_2,puVar4,local_8,param_2);
  return (undefined4 *)((int)param_2 + 0x14);
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 14648,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"confidence\": \"UNKNOWN\",\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          1,\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"confidence\": \"UNKNOWN\",\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": true,\n        \"sizes\": [\n          1,\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path\",\n    \"unparsed_lines_present: 2 line(s) matched no grammar rule\",\n    \"slot_width_ambiguous: one entry slot is read at more 
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
      "va": "0x0059c830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059c9c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059ca70"
    },
    {
      "name": "EditorAnimWorld_GetCreatureController_0059cac0",
      "reconstructed": true,
      "va": "0x0059cac0"
    },
    {
      "name": "EditorAnimWorld_PlayAnimation_0059cb10",
      "reconstructed": true,
      "va": "0x0059cb10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cc40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cdb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059ce30"
    },
    {
      "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
      "reconstructed": true,
      "va": "0x0059cea0"
    },
    {
      "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
      "reconstructed": true,
      "va": "0x0059cf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cf60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cfb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059d010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059d060"
    }
  ],
 
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
      "va": "0x0059c830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059c9c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059ca70"
    },
    {
      "name": "EditorAnimWorld_GetCreatureController_0059cac0",
      "reconstructed": true,
      "va": "0x0059cac0"
    },
    {
      "name": "EditorAnimWorld_PlayAnimation_0059cb10",
      "reconstructed": true,
      "va": "0x0059cb10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cbd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cc40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cd20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cdb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059ce30"
    },
    {
      "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
      "reconstructed": true,
      "va": "0x0059cea0"
    },
    {
      "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
      "reconstructed": true,
      "va": "0x0059cf00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cf60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059cfb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059d010"
    },
    {
      "name": null,
      "reconstructed": false,
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
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 3,
    "symbol": "EditorAnimWorld_GetCreatureController_0059cac0",
    "va": "0x0059cac0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 3,
    "symbol": "EditorAnimWorld_PlayAnimation_0059cb10",
    "va": "0x0059cb10"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 3,
    "symbol": "EditorAnimWorld_SetTargetAngle_0059cea0",
    "va": "0x0059cea0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 3,
    "symbol": "EditorAnimWorld_SetTargetPosition_0059cf00",
    "va": "0x0059cf00"
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

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "anchors": [
        "0x0059c740"
      ],
      "kind": "semantic_decomp_contradiction",
      "path": "evidence.6",
      "source": "knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json",
      "statement": {
        "kind": "repository_contradiction",
        "source": "knowledgegraph/research/global-campaign-2026/conflicts/track-a-type-signature.json:602-779",
        "statement": "The conflict artifact calls the target an ordered lower-bound helper, while the live target body and sibling 0x0059c740 enforce exact-key selection."
      },
      "va": "0x00e5c780"
    }
  ],
  "unresolved_questions": [
    "{\"kind\": \"repository_contradiction\", \"source\": \"knowledgegraph/research/global-campaign-2026/conflicts/track-a-type-signature.json:602-779\", \"statement\": \"The conflict artifact calls the target an ordered lower-bound helper, while the live target body and sibling 0x0059c740 enforce exact-key selection.\"}"
  ]
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
