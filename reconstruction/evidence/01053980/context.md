# Reconstruction context 0x01053980

- Status: `partial`
- Content SHA-256: `eeb080dafb81fb34a130a0f9327a7e84681f3b245d5bd456d33e92a2823b4032`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01053980",
  "phase": "reconstruction",
  "target": "0x01053980"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_01053980",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x01053980"
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
  "content_sha256": "e641e0b77c4c1ca7fe11bbb3de0b551d3021c89f54da3c76f21cacd72a3f9c0f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x01053980 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 17714,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\",\n      \"entry_ESP+0xc\",\n      \"entry_ESP+0x14\",\n      \"entry_ESP+0x1c\",\n      \"entry_ESP+0x20\",\n      \"entry_ESP+0x24\",\n      \"entry_ESP+0x30\",\n      \"entry_ESP+0x38\",\n      \"entry_ESP+0x44\",\n      \"entry_ESP+0x4c\",\n      \"entry_ESP+0x54\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0xc\",\n        \"observed\": true,\n        \"ordinal\": 3,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x14\",\n        \"observed\": true,\n        \"ordinal\": 5,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          1\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x1c\",\n        \"observed\": true,\n        \"ordinal\": 7,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\":
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00b3d240",
      "reconstructed": false,
      "va": "0x00b3d240"
    },
    {
      "name": "root_accessor_00b3d3e0",
      "reconstructed": true,
      "va": "0x00b3d3e0"
    },
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    }
  ],
  "callers": [
    {
      "name": "Simulator::cGetOutOfUFOToolStrategy::OnSelect",
      "reconstructed": false,
      "va": "0x01054080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0105b6a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0105ba00"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0105409d",
      "direction": "in",
      "other": "0x01054080",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0105b6b5",
      "direction": "in",
      "other": "0x0105b6a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0105ba15",
      "direction": "in",
      "other": "0x0105ba00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010539ca",
      "direction": "out",
      "other": "0x00a1ad60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010539ee",
      "direction": "out",
      "other": "0x00a1ad60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053b40",
      "direction": "out",
      "other": "0x00b3d240",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053b94",
      "direction": "out",
      "other": "0x00b3d3e0",
      "referenc
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
    "vtable:0x0149b2e0",
    "vtable:0x0149b498",
    "vtable:0x0149b4d8",
    "vtable:0x0149b810",
    "vtable:0x0149b8b4",
    "vtable:0x0149b900",
    "vtable:0x0149ba30"
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
  "callees": [
    {
      "name": "FUN_00b3d240",
      "reconstructed": false,
      "va": "0x00b3d240"
    },
    {
      "name": "root_accessor_00b3d3e0",
      "reconstructed": true,
      "va": "0x00b3d3e0"
    },
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": "Simulator::cGetOutOfUFOToolStrategy::OnSelect",
      "reconstructed": false,
      "va": "0x01054080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0105b6a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0105ba00"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0105409d",
      "direction": "in",
      "other": "0x01054080",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0105b6b5",
      "direction": "in",
      "other": "0x0105b6a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0105ba15",
      "direction": "in",
      "other": "0x0105ba00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010539ca",
      "direction": "out",
      "other": "0x00a1ad60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010539ee",
      "direction": "out",
      "other": "0x00a1ad60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053b40",
      "direction": "out",
      "other": "0x00b3d240",
      "reference_type": "direct-call"
    },
    {
      "callsite":
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x0149b810,vtable:0x0149b8b4"
    ],
    "package": "pkg-sim-toolevent-01053d50",
    "score": 10,
    "symbol": "sim_toolevent_slot8_fun_01053d50",
    "va": "0x01053d50"
  },
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
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

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
