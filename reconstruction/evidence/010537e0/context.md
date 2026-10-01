# Reconstruction context 0x010537e0

- Status: `partial`
- Content SHA-256: `9867bf2ce953df1489b97282e82afc15416007750f2c23dbc57389cdf31bdec2`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x010537e0",
  "phase": "reconstruction",
  "target": "0x010537e0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_010537e0",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x010537e0"
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
  "content_sha256": "0f79550bde5ccb66aa30a67484516ac1d2f75c5b8ee2027b56b561c994f4687e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x010537e0 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 21945,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\"\n    ],\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"XMM0\",\n    \"return_semantics\": \"float_or_x87_in_XMM0\",\n    \"saved_registers\": [\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"abstained_because\": [\n    \"flow_not_modelled: the linear ESP walk ends at +48, so the listing is not one path\",\n    \"sret_vs_out_param: entry slot 0 is written through a pointer\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 4,\n    \"confidence\": \"OBSERVED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret 0x4\",\n    \"side\": \"cal
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "simulator_game_input_manager_get_00b3d350",
      "reconstructed": true,
      "va": "0x00b3d350"
    },
    {
      "name": "FUN_00b3d390",
      "reconstructed": false,
      "va": "0x00b3d390"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x01053869",
      "direction": "out",
      "other": "0x0059aed0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010538ea",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0105391f",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053940",
      "direction": "out",
      "other": "0x00b3d390",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053954",
      "direction": "out",
      "other": "0x00b3d390",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053961",
      "direction": "out",
      "other": "0x00b3d390",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010538f1",
      "direction": "out",
      "other": "0x00b81630",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053926",
      "direction": "out",
      "other": "0x00b81630",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0105381d",
      "direction": "out",
      "other": "0x0104ccd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053848",
      "direction": "out",
      "other": 
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
      "name": "simulator_game_input_manager_get_00b3d350",
      "reconstructed": true,
      "va": "0x00b3d350"
    },
    {
      "name": "FUN_00b3d390",
      "reconstructed": false,
      "va": "0x00b3d390"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x01053869",
      "direction": "out",
      "other": "0x0059aed0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010538ea",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0105391f",
      "direction": "out",
      "other": "0x00b3d350",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053940",
      "direction": "out",
      "other": "0x00b3d390",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053954",
      "direction": "out",
      "other": "0x00b3d390",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053961",
      "direction": "out",
      "other": "0x00b3d390",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010538f1",
      "direction": "out",
      "other": "0x00b81630",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01053926",
      "direction": "out",
      "other": "0x00b81630",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0105381d",
      "direction": "out",
      "other": "0x0104ccd0",
      "reference_type": "direct-call"
 
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
