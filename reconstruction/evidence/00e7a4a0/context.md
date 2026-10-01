# Reconstruction context 0x00e7a4a0

- Status: `partial`
- Content SHA-256: `88f85100836c9aa1ff90070486e4011934e9dfa6d02fe547ea952585ba761a7f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e7a4a0",
  "phase": "reconstruction",
  "target": "0x00e7a4a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "CellObjectData",
  "name": "FUN_00e7a4a0",
  "package": "PKG-06-CELL-STATE",
  "subsystem": "Simulator.Cell",
  "va": "0x00e7a4a0"
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
  "content_sha256": "1294c5007bcda6db51370023f17c431e764cd8b59a9b46985e45e114d7743867",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e7a4a0 failed: Decompilation did not complete. Reason: ",
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
  "stack_cleanup_bytes": 24
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
      "name": "Simulator::Cell::GetScaleDifferenceWithPlayer",
      "reconstructed": false,
      "va": "0x00e57340"
    },
    {
      "name": "Simulator::Cell::cCellGFX::InstanceEffectOnCell",
      "reconstructed": false,
      "va": "0x00e66840"
    },
    {
      "name": "Simulator::Cell::PlayAnimation",
      "reconstructed": false,
      "va": "0x00e6d200"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7a770"
    },
    {
      "name": "FUN_00e7a7c0",
      "reconstructed": true,
      "va": "0x00e7a7c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e81120"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e7a7ad",
      "direction": "in",
      "other": "0x00e7a770",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a8d8",
      "direction": "in",
      "other": "0x00e7a7c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7b268",
      "direction": "in",
      "other": "0x00e7b240",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81559",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a55d",
      "direction": "out",
      "other": "0x00571cf0",
      "reference_type": "direct-call
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
    "CellObjectData*",
    "CellPoolIndex",
    "CellResourceRef",
    "CellResourceRef*",
    "E52a40Stack6",
    "OpaqueResourceScope",
    "float",
    "std::uint32_t",
    "std::uint8_t"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 13362,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"cell_effect_and_scale_observation\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"NEEDS_RUNTIME\",\n    \"confidence\": {\n      \"overall\": \"SUPPORTED\"\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 21,\n    \"evidence\": [\n      {\n        \"independent_limit\": \"Killer/resource/flag types are decompiler-inferred.\",\n        \"kind\": \"direct_decompilation\",\n        \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7a4a0\",\n        \"supports\": [\n          \"guards\",\n          \"field_113 write\",\n          \"three death effect names\",\n          \"kill counter increment\",\n          \"type 6 record\",\n          \"animations\",\n          \"scale-aware call\"\n        ]\n      },\n      {\n        \"independent_limit\": \"Same binary source; assembly cross-check only.\",\n        \"kind\": \"disassembly\",\n        \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7a4a0\",\n        \"supports\": [\n          \"player branch at +0x411c\",\n          \"field_112/113 checks\",\n          \"type 6 at record+0x24\",\n          \"mKillCount offset +0x6c\",\n          \"animation immediates 10 and 7\"\n        ]\n      },\n      {\n        \"independent_limit\": \"Static xrefs do not prove event frequency.\",\n        \"kind\": \"callgraph_xrefs\",\n        \"source\": \"Ghidra MCP:SporeApp.exe@xrefs@0x00e7a4a0\",\n        \"supports\": [\n          \"4 direct callers\",\
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
      "name": "Simulator::Cell::GetScaleDifferenceWithPlayer",
      "reconstructed": false,
      "va": "0x00e57340"
    },
    {
      "name": "Simulator::Cell::cCellGFX::InstanceEffectOnCell",
      "reconstructed": false,
      "va": "0x00e66840"
    },
    {
      "name": "Simulator::Cell::PlayAnimation",
      "reconstructed": false,
      "va": "0x00e6d200"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7a770"
    },
    {
      "name": "FUN_00e7a7c0",
      "reconstructed": true,
      "va": "0x00e7a7c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e81120"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e7a7ad",
      "direction": "in",
      "other": "0x00e7a770",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a8d8",
      "direction": "in",
      "other": "0x00e7a7c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7b268",
      "direction": "in",
      "other": "0x00e7b240",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e81559",
      "direction": "in",
      "other": "0x00e81120",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a55d",
      
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
      "same_class",
      "shared_types:CellObjectData,CellObjectData*,CellResourceRef",
      "direct_xref_neighbor"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 31,
    "symbol": "FUN_00e7a7c0",
    "va": "0x00e7a7c0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:CellObjectData,CellResourceRef,OpaqueResourceScope"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 28,
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
    "symbol": "FUN_00e7fd00",
    "va": "0x00e7fd00"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-06A-CELL-AI-SELECTION",
    "score": 6,
    "symbol": "cell_ai_select_profile_00e52910",
    "va": "0x00e52910"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-H3-HELPER-WAVE2",
    "score": 3,
    "symbol": "embedded_object_first_word_init_00743b50",
    "va": "0x00743b50"
  }
]
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
    "reconstruction/metadata/pkg06-cell-state/00e7a4a0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 12516,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": \"SUPPORTED\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 21,\n  \"evidence\": [\n    {\n      \"independent_limit\": \"Killer/resource/flag types are decompiler-inferred.\",\n      \"kind\": \"direct_decompilation\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7a4a0\",\n      \"supports\": [\n        \"guards\",\n        \"field_113 write\",\n        \"three death effect names\",\n        \"kill counter increment\",\n        \"type 6 record\",\n        \"animations\",\n        \"scale-aware call\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Same binary source; assembly cross-check only.\",\n      \"kind\": \"disassembly\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7a4a0\",\n      \"supports\": [\n        \"player branch at +0x411c\",\n        \"field_112/113 checks\",\n        \"type 6 at record+0x24\",\n        \"mKillCount offset +0x6c\",\n        \"animation immediates 10 and 7\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Static xrefs do not prove event frequency.\",\n      \"kind\": \"callgraph_xrefs\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@xrefs@0x00e7a4a0\",\n      \"supports\": [\n        \"4 direct callers\",\n        \"17 direct callees\",\n        \"death/effect/animation/event fan-out\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Does not prove disk encoding or transaction.\",\n      \"kind\": \"structure_layout\",\n      \"source\": \"Gh
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
        "0x00e62340",
        "0x00e780a0",
        "0x00e7a7c0",
        "0x00e806b0",
        "0x00e7a7c0",
        "0x00e62340",
        "0x00e780a0",
        "0x00e806b0",
        "0x00e74a20",
        "0x00e780a0",
        "0x00b721d0",
        "0x00b72260",
        "0x00e771d0",
        "0x00e7d370",
        "0x00e7a4a0"
      ],
      "conflict_id": "U6",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
      "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00d2e490",
        "0x00d2e4a0",
        "0x0169e394",
        "0x00d2e490",
        "0x00e7a4a0",
        "0x00e7a7c0",
        "0x0169e394",
        "0x00d2e490",
        "0x00d2e490",
        "0x00d2e490",
        "0x00d2e4a0",
        "0x00d2e4a0",
        "0x00d2e4a0",
        "0x00e57460",
        "0x00e57460",
        "0x00e7a7c0"
      ],
      "conflict_id": "ability_mode_callers_and_domain",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The com
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg06-cell-state/00e7a4a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg06_cell_state/cell_state.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg06-cell-state/00e7a4a0.json",
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
