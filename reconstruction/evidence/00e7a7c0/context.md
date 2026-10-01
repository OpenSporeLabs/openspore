# Reconstruction context 0x00e7a7c0

- Status: `partial`
- Content SHA-256: `6b8300082d76a18212b5407cb7e5e96cacbe539c6db4308862d94152d269b10c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e7a7c0",
  "phase": "reconstruction",
  "target": "0x00e7a7c0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "CellObjectData",
  "name": "FUN_00e7a7c0",
  "package": "PKG-06-CELL-STATE",
  "subsystem": "Simulator.Cell",
  "va": "0x00e7a7c0"
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
  "content_sha256": "b172a87585df2590f47d5112a03c1d58f2e1bbe76d9f79fd2f88f70573039f82",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e7a7c0 failed: Decompilation did not complete. Reason: ",
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
      "name": "Simulator::Cell::ShouldNotAttack",
      "reconstructed": false,
      "va": "0x00e57460"
    },
    {
      "name": "Simulator::Cell::GetDamageAmount",
      "reconstructed": false,
      "va": "0x00e58980"
    },
    {
      "name": "Simulator::Cell::cCellUI::ShowHealthRollover",
      "reconstructed": false,
      "va": "0x00e62340"
    },
    {
      "name": "Simulator::Cell::PlayAnimation",
      "reconstructed": false,
      "va": "0x00e6d200"
    },
    {
      "name": "FUN_00e7a4a0",
      "reconstructed": true,
      "va": "0x00e7a4a0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b0a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7e7f0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00e7b15a",
      "direction": "in",
      "other": "0x00e7b0a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7b20a",
      "direction": "in",
      "other": "0x00e7b0a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7f096",
      "direction": "in",
      "other": "0x00e7e7f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a8ec",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a93c",
      "direction": "out",
      "other": "0x00b72210",
      "reference_type
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
    "CellResourceRef",
    "OpaqueCellDirectionPayload",
    "const CellDirectionVector*",
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
  "original_bytes": 12200,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"cell_damage_transition_observation\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"NEEDS_RUNTIME\",\n    \"confidence\": {\n      \"overall\": \"SUPPORTED\"\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 18,\n    \"evidence\": [\n      {\n        \"independent_limit\": \"Decompiler parameter types and unnamed helper semantics are not authoritative.\",\n        \"kind\": \"direct_decompilation\",\n        \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7a7c0\",\n        \"supports\": [\n          \"six-argument body\",\n          \"attack gates\",\n          \"health clamp\",\n          \"animation mapping\",\n          \"death dispatch\"\n        ]\n      },\n      {\n        \"independent_limit\": \"Same binary source; used as an assembly cross-check, not a separate runtime source.\",\n        \"kind\": \"disassembly\",\n        \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7a7c0\",\n        \"supports\": [\n          \"stack argument flow\",\n          \"field offsets +0x17c/+0x244\",\n          \"conditional return paths\"\n        ]\n      },\n      {\n        \"independent_limit\": \"Static call graph does not prove runtime frequency or reachability.\",\n        \"kind\": \"callgraph_xrefs\",\n        \"source\": \"Ghidra MCP:SporeApp.exe@xrefs@0x00e7a7c0\",\n        \"supports\": [\n          \"2 direct callers\",\n          \"16 direct callees\",\n          \"death/effect
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
      "name": "Simulator::Cell::ShouldNotAttack",
      "reconstructed": false,
      "va": "0x00e57460"
    },
    {
      "name": "Simulator::Cell::GetDamageAmount",
      "reconstructed": false,
      "va": "0x00e58980"
    },
    {
      "name": "Simulator::Cell::cCellUI::ShowHealthRollover",
      "reconstructed": false,
      "va": "0x00e62340"
    },
    {
      "name": "Simulator::Cell::PlayAnimation",
      "reconstructed": false,
      "va": "0x00e6d200"
    },
    {
      "name": "FUN_00e7a4a0",
      "reconstructed": true,
      "va": "0x00e7a4a0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b0a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7e7f0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00e7b15a",
      "direction": "in",
      "other": "0x00e7b0a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7b20a",
      "direction": "in",
      "other": "0x00e7b0a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7f096",
      "direction": "in",
      "other": "0x00e7e7f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e7a8ec",
      "direction": "out",
      "other": "0x00743b50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00
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
    "symbol": "FUN_00e7a4a0",
    "va": "0x00e7a4a0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:CellObjectData,CellResourceRef"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 25,
    "symbol": "FUN_00e780a0",
    "va": "0x00e780a0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:CellObjectData,CellResourceRef"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 20,
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
    "reconstruction/metadata/pkg06-cell-state/00e7a7c0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 11417,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": \"SUPPORTED\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 18,\n  \"evidence\": [\n    {\n      \"independent_limit\": \"Decompiler parameter types and unnamed helper semantics are not authoritative.\",\n      \"kind\": \"direct_decompilation\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7a7c0\",\n      \"supports\": [\n        \"six-argument body\",\n        \"attack gates\",\n        \"health clamp\",\n        \"animation mapping\",\n        \"death dispatch\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Same binary source; used as an assembly cross-check, not a separate runtime source.\",\n      \"kind\": \"disassembly\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7a7c0\",\n      \"supports\": [\n        \"stack argument flow\",\n        \"field offsets +0x17c/+0x244\",\n        \"conditional return paths\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Static call graph does not prove runtime frequency or reachability.\",\n      \"kind\": \"callgraph_xrefs\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@xrefs@0x00e7a7c0\",\n      \"supports\": [\n        \"2 direct callers\",\n        \"16 direct callees\",\n        \"death/effect/UI fan-out\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Several fields remain unnamed.\",\n      \"kind\": \"structure_layout\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@structure:cCellObjectData\",\n      \"supports\": [\n    
[TRUNCATED]
```

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 9469,
  "preview": "{\n  \"conflicts\": {\n    \"original_bytes\": 12235,\n    \"preview\": \"[\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x00e62340\\\",\\n      \\\"0x00e780a0\\\",\\n      \\\"0x00e7a7c0\\\",\\n      \\\"0x00e806b0\\\",\\n      \\\"0x00e7a7c0\\\",\\n      \\\"0x00e62340\\\",\\n      \\\"0x00e780a0\\\",\\n      \\\"0x00e806b0\\\",\\n      \\\"0x00e7fd00\\\",\\n      \\\"0x00e74a20\\\",\\n      \\\"0x00e780a0\\\",\\n      \\\"0x00e74a20\\\",\\n      \\\"0x00e74a20\\\",\\n      \\\"0x00e4ce20\\\",\\n      \\\"0x00e5b790\\\",\\n      \\\"0x00e665c0\\\"\\n    ],\\n    \\\"conflict_id\\\": \\\"U-003-cell-respawn-policy\\\",\\n    \\\"kind\\\": \\\"conflict_ledger\\\",\\n    \\\"rejected\\\": [],\\n    \\\"resolution\\\": \\\"Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.\\\",\\n    \\\"resolution_status\\\": \\\"Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.\\\",\\n    \\\"source\\\": \\\"knowledgegraph/research/conflicts/track-c-state-events.json\\\",\\n    \\\"subject\\\": null,\\n    \\\"unresolved_reason\\\": \\\"Runtime reachability is absent or the required direct body/call path is not recovered.\\\"\\n  },\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x00e62340\\\",\\n      \\\"0x00e780a0\\\",\\n      \\\"0x00e7a7c0\\\",\\n      \\\"0x00e806b0\\\",\\n      \\\"0x00e7a7c0\
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg06-cell-state/00e7a7c0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg06_cell_state/cell_state.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg06-cell-state/00e7a7c0.json",
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
