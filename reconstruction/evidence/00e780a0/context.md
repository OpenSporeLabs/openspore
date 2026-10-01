# Reconstruction context 0x00e780a0

- Status: `partial`
- Content SHA-256: `25331bd4b4e36b12c072bc3fcc03a13b4b42cb89ff2d9de28913aea6637fd341`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00e780a0",
  "phase": "reconstruction",
  "target": "0x00e780a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "CellObjectData",
  "name": "FUN_00e780a0",
  "package": "PKG-06-CELL-STATE",
  "subsystem": "Simulator.Cell",
  "va": "0x00e780a0"
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
  "content_sha256": "c672d410d7e98cbb27e832f2f1060ffbf0a13aa5bc79fcb973c8c51bbb487b66",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00e780a0 failed: Decompilation did not complete. Reason: ",
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
  "stack_cleanup_bytes": 16
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
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e771d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78b80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e791a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e79460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e794f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e79720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7a0d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7a160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7aa20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7add0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b630"
    }
  ],
  "edge_rows": [
    {
    
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
    "ObservedObjectPool",
    "OpaqueResourceScope",
    "float",
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
  "original_bytes": 13368,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"cell_object_lifetime_observation\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"NEEDS_RUNTIME\",\n    \"confidence\": {\n      \"overall\": \"SUPPORTED\"\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 36,\n    \"evidence\": [\n      {\n        \"independent_limit\": \"Parameter names and replacement semantics are inferred.\",\n        \"kind\": \"direct_decompilation\",\n        \"source\": \"Ghidra MCP:SporeApp.exe@0x00e780a0\",\n        \"supports\": [\n          \"validity guard\",\n          \"avatar clear\",\n          \"query/GFX/child cleanup\",\n          \"scale replacement\",\n          \"unconditional old release\"\n        ]\n      },\n      {\n        \"independent_limit\": \"Same binary source; assembly cross-check only.\",\n        \"kind\": \"disassembly\",\n        \"source\": \"Ghidra MCP:SporeApp.exe@0x00e780a0\",\n        \"supports\": [\n          \"+0x248 detach branch\",\n          \"+0x370 child branch\",\n          \"mScale comparison\",\n          \"tail FUN_00b72260 release\",\n          \"stack/register behavior\"\n        ]\n      },\n      {\n        \"independent_limit\": \"Static callers do not identify runtime reason per call.\",\n        \"kind\": \"callgraph_xrefs\",\n        \"source\": \"Ghidra MCP:SporeApp.exe@xrefs@0x00e780a0\",\n        \"supports\": [\n          \"23 direct callers spanning lifecycle/interaction/frame/population/
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
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e771d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78b80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e78fc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e791a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e79460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e794f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e79720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7a0d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7a160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7aa20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7add0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b5d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e7b630"
    },
 
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
      "shared_types:CellObjectData,CellResourceRef,OpaqueResourceScope"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 28,
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
    "symbol": "FUN_00e7a7c0",
    "va": "0x00e7a7c0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:CellObjectData,CellResourceRef,ObservedObjectPool,OpaqueResourceScope"
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
    "reconstruction/metadata/pkg06-cell-state/00e780a0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 12527,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": \"SUPPORTED\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 36,\n  \"evidence\": [\n    {\n      \"independent_limit\": \"Parameter names and replacement semantics are inferred.\",\n      \"kind\": \"direct_decompilation\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e780a0\",\n      \"supports\": [\n        \"validity guard\",\n        \"avatar clear\",\n        \"query/GFX/child cleanup\",\n        \"scale replacement\",\n        \"unconditional old release\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Same binary source; assembly cross-check only.\",\n      \"kind\": \"disassembly\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e780a0\",\n      \"supports\": [\n        \"+0x248 detach branch\",\n        \"+0x370 child branch\",\n        \"mScale comparison\",\n        \"tail FUN_00b72260 release\",\n        \"stack/register behavior\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Static callers do not identify runtime reason per call.\",\n      \"kind\": \"callgraph_xrefs\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@xrefs@0x00e780a0\",\n      \"supports\": [\n        \"23 direct callers spanning lifecycle/interaction/frame/population/rebuild\",\n        \"13 direct callees\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Child/field names are generic.\",\n      \"kind\": \"structure_layout\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@structure:cCellObjectData\"
[TRUNCATED]
```

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 9595,
  "preview": "{\n  \"conflicts\": {\n    \"original_bytes\": 9017,\n    \"preview\": \"[\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x00e74a20\\\",\\n      \\\"0x00e57460\\\",\\n      \\\"0x00e6d200\\\",\\n      \\\"0x00e57340\\\",\\n      \\\"0x00e780a0\\\",\\n      \\\"0x00000108\\\",\\n      \\\"0x00e74a20\\\",\\n      \\\"0x00000108\\\"\\n    ],\\n    \\\"conflict_id\\\": \\\"TB-FL-012\\\",\\n    \\\"kind\\\": \\\"conflict_ledger\\\",\\n    \\\"rejected\\\": [],\\n    \\\"resolution\\\": {\\n      \\\"merge_decision\\\": \\\"separate_entities\\\",\\n      \\\"preferred_claim\\\": \\\"Use the original direct field/body evidence as the ABI anchor.\\\",\\n      \\\"preserved_alternatives\\\": true,\\n      \\\"scope_note\\\": \\\"The current padding is a replacement limitation and cannot define the original structure.\\\",\\n      \\\"status\\\": \\\"preferred_claim_with_limit\\\",\\n      \\\"taxonomy\\\": \\\"preferred_claim_with_limit\\\"\\n    },\\n    \\\"resolution_status\\\": \\\"preferred_claim_with_limit\\\",\\n    \\\"source\\\": \\\"knowledgegraph/research/conflicts/track-b-vtable-fields.json\\\",\\n    \\\"subject\\\": \\\"cCellObjectData original middle fields versus current opaque padding\\\",\\n    \\\"unresolved_reason\\\": \\\"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\\\"\\n  },\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x00e62340\\\",\\n      \\\"0x00e780a0\\\",\\n      \\\"0x00e7a7c0\\\",\\n      
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg06-cell-state/00e780a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg06_cell_state/cell_state.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg06-cell-state/00e780a0.json",
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
