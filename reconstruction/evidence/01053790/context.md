# Reconstruction context 0x01053790

- Status: `partial`
- Content SHA-256: `e0cc4af1e5fda52da08fe48ec9e60bff0643e0809898bb2086c0ac9762006b2e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01053790",
  "phase": "reconstruction",
  "target": "0x01053790"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Simulator::cToolStrategy::OnSelect",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x01053790"
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
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "2bb73b4d98cceb145fcd98b04e84741be546d9e8ac115a4d2509f230e1e25cda",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

/* WARNING: Unknown calling convention */
/* WARNING: Enum "ObjectTYPE": Some values do not have unique names */
/* WARNING: Enum "Names": Some values do not have unique names */

bool Simulator__cToolStrategy__OnSelect(cToolStrategy *this,cSpaceToolData *pTool)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_Simulator__cToolStrategy__OnSelect_01403934;
  if (((uint)this & 1) != 0) {
    FUN_00f47380();
  }
  return SUB41(in_ECX,0);
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 8024,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          1\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          1\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"abstained_because\": [],\n  \"cleanup\": {\n    \"bytes\": 4,\n    \"confidence\": \"OBSERVED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret 0x4\",\n    \"side\": \"callee\"\n  },\n  \"completeness\": \"CORE_RESOLVED\",\n  \"conflicts\": [],\n  \"content_sha256\": \"c7e5f571354c43e8df9428425f2c879aeadf76b94f939613c8b9e8446db72826\",\n  \"conventions\":
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x010537a1",
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
  "types": [],
  "vtables": [
    "vtable:0x01416698",
    "vtable:0x014166c4",
    "vtable:0x0141677c",
    "vtable:0x014167a0",
    "vtable:0x014167ec",
    "vtable:0x014168a8",
    "vtable:0x014169bc",
    "vtable:0x014169f0",
    "vtable:0x0141a504",
    "vtable:0x014402c4",
    "vtable:0x01440fbc",
    "vtable:0x0144144c"
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x010537a1",
      "direction": "out",
      "other": "0x00f47380",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0530",
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
      "same_subsystem"
    ],
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 6,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "cycle_key_006286a0",
    "va": "0x006286a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "Simulator_GetUIMissionLogManager",
    "va": "0x00b3d4f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 6,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cToolStrategy__OnSelect.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cToolStrategy__OnSelect.c"
  ],
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
        "0x01053790",
        "0x01059010",
        "0x01053790",
        "0x01053790",
        "0x01053790",
        "0x01053790",
        "0x01059010",
        "0x01059010",
        "0x01059010",
        "0x00bfc3d0",
        "0x00bfc3d0",
        "0x00bfc7a0",
        "0x00bfc7a0",
        "0x01053790",
        "0x01059010",
        "0x01053790"
      ],
      "conflict_id": "tool_callback_body_mapping",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00bfc3d0",
        "0x00bfc7a0",
        "0x01053790",
        "0x01059010",
        "0x01053790",
        "0x00e7a7c0",
        "0x01053790",
        "0x01053790",
        "0x01053790",
        "0x01059010",
        "0x01059010",
        "0x01059010",
        "0x00bfc3d0",
        "0x00bfc3d0",
        "0x00bfc3d0",
        "0x00bfc460"
      ],
      "conflict_id": "tool_projectile_event_path",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited direct body establis
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'ref': 'GhidraMCP /disassemble_function', 'mode': 'derived', 'source_class': 'derived'}, {'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'mode': 'derived', 'source_class': 'derived'}, {'ref': 'ephemeral reconstruction_knowledge.build_index', 'mode': 'derived', 'source_class': 'generated_index'}, {'ref': 'tools/reconstruction_tooling/abi_infer.py', 'mode': 'derived', 'source_class': 'derived'}, {'ref': 'GhidraMCP /disassemble_function', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'mode': 'live', 'source_class': 'ghidra'}, {'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cToolStrategy__OnSelect.c', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cToolStrategy__OnSelect.c",
      "source_class": "committed_artifact"
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
    "reconstruction/knowledge/index.json",
    ".spore-analysis/ghidra-export
[TRUNCATED]
```
