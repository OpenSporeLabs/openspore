# Reconstruction context 0x005ca960

- Status: `partial`
- Content SHA-256: `736d6be0069bc9ec6221171139f9b0ad217b2b8dbe7bc3cfaa0db6d362422d3f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005ca960",
  "phase": "reconstruction",
  "target": "0x005ca960"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueService",
  "name": "editor_query_service_005ca960",
  "package": "PKG-10-EDITOR-DISPATCH",
  "subsystem": "Editors.Query",
  "va": "0x005ca960"
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
  "content_sha256": "104292f947308e50cbbfe80ac50bc96dbb53c661c280abd2301861deb3e28686",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005ca960 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl-compatible one-stack-word accessor",
  "return_register": "EAX",
  "return_type": "OpaqueService *",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Service whose vtable slot +0x0c is called",
      "position": 1,
      "type": "OpaqueService *",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 0,
  "termination": "RET"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [
    {
      "name": "Editors_EditorUI_HandleMessage_005e0000",
      "reconstructed": true,
      "va": "0x005e0000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00817040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00995b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e03f80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e133b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e13b50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e1d7a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ea0910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ee9840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f0ea20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01063dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01066f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01072d40"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005e02ba",
      "direction": "in",
      "other": "0x005e0000",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00817324",
      "direction": "in",
      "other": "0x00817040",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00995dae",
      "direction": "in",
      "other": "0x00995b20",
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueService",
    "OpaqueService *"
  ],
  "vtables": [
    "vtable:0x0000000c"
  ]
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-editor-query-service-slot"
    ],
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
      "name": "Editors_EditorUI_HandleMessage_005e0000",
      "reconstructed": true,
      "va": "0x005e0000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00817040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00995b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e03f80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e133b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e13b50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e1d7a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ea0910"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ee9840"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f0ea20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01063dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01066f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01072d40"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005e02ba",
      "direction": "in",
      "other": "0x005e0000",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00817324",
      "direction": "in",
      "other": "0x00817040",
      "reference_type": "direct-call"
    },
    {

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
      "shared_types:OpaqueService"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 17,
    "symbol": "editor_query_dispatch_005dfd00",
    "va": "0x005dfd00"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 14,
    "symbol": "editor_query_reset_005dd750",
    "va": "0x005dd750"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 14,
    "symbol": "editor_query_clear_flags_0093db80",
    "va": "0x0093db80"
  },
  {
    "match_basis": [
      "same_package",
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 11,
    "symbol": "Editors_EditorUI_HandleMessage_005e0000",
    "va": "0x005e0000"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 8,
    "symbol": "Editors_EditorModel_SetColor_raw_004ae250",
    "va": "0x004ae250"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 8,
    "symbol": "FUN_005dda30",
    "va": "0x005dda30"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueService"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 8,
    "symbol": "service_005f9230",
    "va": "0x005f9230"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueService"
    ],
    "package": "PKG-APP-SERVICES-SAFE-W
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg10_editor_dispatch/editor_query_helpers.cpp",
  "files": [
    "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.cpp",
    "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.hpp",
    "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers_model_test.cpp",
    "src/reconstruction/pkg10_editor_dispatch/editor_query_helpers.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/005ca960.json"
  ]
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
  "unresolved_questions": [
    "What does the literal 0x8ed27e7a select in each owner?",
    "What lifetime and aliasing rules apply to the returned service pointer?",
    "Which concrete service owners install the vtable used at slot +0x0c?",
    "gate-editor-query-service-slot",
    "meaning of literal 0x8ed27e7a",
    "returned service lifetime",
    "service vtable owner"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg10-editor-dispatch/005ca960.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg10_editor_dispatch/editor_query_helpers.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg10-editor-dispatch/005ca960.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconst
[TRUNCATED]
```
