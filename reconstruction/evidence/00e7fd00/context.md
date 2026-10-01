# Reconstruction context 0x00e7fd00

- Status: `partial`
- Content SHA-256: `41dcd206543f6ed73faad2177fea7a13183451e322212705eef3d659840098e6`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e7fd00",
  "phase": "reconstruction",
  "target": "0x00e7fd00"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "None",
  "name": "FUN_00e7fd00",
  "package": "PKG-06-CELL-STATE",
  "subsystem": "Simulator.Cell",
  "va": "0x00e7fd00"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "38a9875e008e8c90d508a2db5d406af050a3e7a365ba0ff4a358129fc353bfbd",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e7fd00 failed: Decompilation did not complete. Reason: ",
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
  "stack_cleanup_bytes": 28
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    },
    {
      "name": "FUN_00d018d0",
      "reconstructed": false,
      "va": "0x00d018d0"
    },
    {
      "name": "FUN_00e31100",
      "reconstructed": false,
      "va": "0x00e31100"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e80660"
    },
    {
      "name": "cell_update_body_00e806b0",
      "reconstructed": true,
      "va": "0x00e806b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e809a0"
    },
    {
      "name": "Simulator::Cell::cCellGame::Initialize",
      "reconstructed": false,
      "va": "0x00e80ba0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e8067f",
      "direction": "in",
      "other": "0x00e80660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8069e",
      "direction": "in",
      "other": "0x00e80660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8088c",
      "direction": "in",
      "other": "0x00e806b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80b6c",
      "direction": "in",
      "other": "0x00e809a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80f9f",
      "direction": "in",
      "other": "0x00e80ba0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80126",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-ca
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "CellObjectData",
    "CellResourceRef",
    "None",
    "ObservedAudioConfig",
    "ObservedCallbackVtablePrefix",
    "ObservedObjectPool",
    "ObservedStageRecord",
    "OpaqueResourceScope",
    "std::int32_t",
    "std::uint32_t",
    "std::uint8_t",
    "void"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 15259,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"cell_reset_observation\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"NEEDS_RUNTIME\",\n    \"confidence\": {\n      \"overall\": \"SUPPORTED\"\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 36,\n    \"evidence\": [\n      {\n        \"independent_limit\": \"Several argument types and helper names are undefined.\",\n        \"kind\": \"direct_decompilation\",\n        \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7fd00\",\n        \"supports\": [\n          \"pool drain sequence\",\n          \"serializable progression writes\",\n          \"world-reference branches\",\n          \"population/player creation\",\n          \"hatch selection\"\n        ]\n      },\n      {\n        \"independent_limit\": \"Same binary source; control-flow cross-check only.\",\n        \"kind\": \"disassembly\",\n        \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7fd00\",\n        \"supports\": [\n          \"clear +0x51d8/+0x411c/+0x51d4\",\n          \"pool loops\",\n          \"UI/GFX reset offsets\",\n          \"scale table\",\n          \"serializable offsets +0x1c..+0x28\"\n        ]\n      },\n      {\n        \"independent_limit\": \"Static xrefs do not establish invocation frequency.\",\n        \"kind\": \"callgraph_xrefs\",\n        \"source\": \"Ghidra MCP:SporeApp.exe@xrefs@0x00e7fd00\",\n        \"supports\": [\n          \"4 direct callers\",\n          \"32 direct callees\",\
[TRUNCATED]
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "embedded_object_first_word_init_00743b50",
      "reconstructed": true,
      "va": "0x00743b50"
    },
    {
      "name": "FUN_00d018d0",
      "reconstructed": false,
      "va": "0x00d018d0"
    },
    {
      "name": "FUN_00e31100",
      "reconstructed": false,
      "va": "0x00e31100"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e80660"
    },
    {
      "name": "cell_update_body_00e806b0",
      "reconstructed": true,
      "va": "0x00e806b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e809a0"
    },
    {
      "name": "Simulator::Cell::cCellGame::Initialize",
      "reconstructed": false,
      "va": "0x00e80ba0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e8067f",
      "direction": "in",
      "other": "0x00e80660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8069e",
      "direction": "in",
      "other": "0x00e80660",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8088c",
      "direction": "in",
      "other": "0x00e806b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80b6c",
      "direction": "in",
      "other": "0x00e809a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80f9f",
      "direction": "in",
      "other": "0x00e80ba0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e80126",
    
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:CellObjectData,CellResourceRef,ObservedObjectPool,OpaqueResourceScope"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 23,
    "symbol": "FUN_00e780a0",
    "va": "0x00e780a0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:CellObjectData,CellResourceRef,OpaqueResourceScope"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 23,
    "symbol": "FUN_00e7a4a0",
    "va": "0x00e7a4a0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:CellObjectData,CellResourceRef"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 20,
    "symbol": "FUN_00e7a7c0",
    "va": "0x00e7a7c0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-06A-CELL-AI-SELECTION",
    "score": 14,
    "symbol": "cell_ai_select_profile_00e52910",
    "va": "0x00e52910"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d3b0",
    "va": "0x00b3d3b0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_00b3d3e0",
    "va": "0x00b3d3e0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:None"
    ],
    "package": "PKG-11-H2-ROOT-ACCESSORS",
    "score": 8,
    "symbol": "root_accessor_
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg06_cell_state/cell_state.cpp",
  "files": [
    "src/reconstruction/pkg06_cell_state/cell_state.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg06-cell-state/00e7fd00.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 14358,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": \"SUPPORTED\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 36,\n  \"evidence\": [\n    {\n      \"independent_limit\": \"Several argument types and helper names are undefined.\",\n      \"kind\": \"direct_decompilation\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7fd00\",\n      \"supports\": [\n        \"pool drain sequence\",\n        \"serializable progression writes\",\n        \"world-reference branches\",\n        \"population/player creation\",\n        \"hatch selection\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Same binary source; control-flow cross-check only.\",\n      \"kind\": \"disassembly\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7fd00\",\n      \"supports\": [\n        \"clear +0x51d8/+0x411c/+0x51d4\",\n        \"pool loops\",\n        \"UI/GFX reset offsets\",\n        \"scale table\",\n        \"serializable offsets +0x1c..+0x28\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Static xrefs do not establish invocation frequency.\",\n      \"kind\": \"callgraph_xrefs\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@xrefs@0x00e7fd00\",\n      \"supports\": [\n        \"4 direct callers\",\n        \"32 direct callees\",\n        \"init/frame reachability\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Some binary fields are generic pointers or padding.\",\n      \"kind\": \"structure_layout\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@str
[TRUNCATED]
```

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "anchors": [
        "0x00b72160",
        "0x00b72260",
        "0x00b72270",
        "0x00e665c0",
        "0x00e74a20",
        "0x00e80ba0",
        "0x00e80ba0",
        "0x00e74a20",
        "0x00b72160",
        "0x00b72260",
        "0x00e665c0",
        "0x00e7fd00",
        "0x00e74a20",
        "0x00b72160",
        "0x00b72260",
        "0x00b72270"
      ],
      "conflict_id": "U-001-pool-contract",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The 4096 capacity, 920-byte Cell record, allocation/release path, and first-word free/self-index mechanics are bounded. Original sentinel, index-zero validity, and exact generic entry mapping remain unresolved.",
      "resolution_status": "The 4096 capacity, 920-byte Cell record, allocation/release path, and first-word free/self-index mechanics are bounded. Original sentinel, index-zero validity, and exact generic entry mapping remain unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00e62340",
        "0x00e780a0",
        "0x00e7a7c0",
        "0x00e806b0",
        "0x00e7a7c0",
        "0x00e62340",
        "0x00e780a0",
        "0x00e806b0",
        "0x00e7fd00",
        "0x00e74a20",
        "0x00e780a0",
        "0x00e74a20",
        "0x00e74a20",
        "0x00e4ce20",
        "0x00e5b790",
        "0x00e665c0"
      ],
      "confl
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg06-cell-state/00e7fd00.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg06_cell_state/cell_state.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg06-cell-state/00e7fd00.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg06_cell_state/cell_state.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    "src/reconstruction/pkg06_cell_state/cell_state.cpp"
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
