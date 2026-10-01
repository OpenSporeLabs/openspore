# Reconstruction context 0x005dfd00

- Status: `partial`
- Content SHA-256: `b3f1982ea90824f4601c62762f87d1e0571a52658e54e6c54a46af5f3555b5c2`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005dfd00",
  "phase": "reconstruction",
  "target": "0x005dfd00"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueEditorQueryContext",
  "name": "editor_query_dispatch_005dfd00",
  "package": "PKG-10-EDITOR-DISPATCH",
  "subsystem": "Editors.Query",
  "va": "0x005dfd00"
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
  "content_sha256": "bb9049639cb700687095d36775b6e49e37437e9afe85122a5d1579417f3b0c74",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005dfd00 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "return_register": "AL",
  "return_type": "std::uint8_t",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Command word selected by the 0x100-based switch table",
      "position": 1,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a88d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dc310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dd610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callers": [
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    },
    {
      "name": "Editors_EditorUI_HandleMessage_005e0000",
      "reconstructed": true,
      "va": "0x005e0000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006352d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006352f0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0058b0d7",
      "direction": "in",
      "other": "0x0058ac10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b2d4",
      "direction": "in",
      "other": "0x0058ac10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b411",
      "direction": "in",
      "other": "0x0058ac10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b52c",
      "direction": "in",
      "other": "0x0058ac10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005e00a8",
      "direction": "in",
      "other": "0x005e0000",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006352db",
      "direction": "in",
      "other": "0x006352d0",
      "r
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x015fd918"
  ],
  "types": [
    "OpaqueAppProperties",
    "OpaqueEditorQueryContext",
    "OpaqueMaterialManager",
    "OpaqueService",
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
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-editor-query-helpers"
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
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a88d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dc310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dd610"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    },
    {
      "name": "Editors_EditorUI_HandleMessage_005e0000",
      "reconstructed": true,
      "va": "0x005e0000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006352d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006352f0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0058b0d7",
      "direction": "in",
      "other": "0x0058ac10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b2d4",
      "direction": "in",
      "other": "0x0058ac10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b411",
      "direction": "in",
      "other": "0x0058ac10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b52c",
      "direction": "in",
      "other": "0x0058ac10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005e00a8",
      "direction": "in",
      "other": "0x005e0000",
      "reference_type": "direct-call"
    },
    {
      "ca
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
    "symbol": "editor_query_service_005ca960",
    "va": "0x005ca960"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 16,
    "symbol": "editor_query_reset_005dd750",
    "va": "0x005dd750"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 16,
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
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_0058ac10",
    "va": "0x0058ac10"
  },
  {
    "match_basis": [
      "shared_types:OpaqueService"
    ],
    "package": "PKG-A
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
    "reconstruction/metadata/pkg10-editor-dispatch/005dfd00.json"
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
    "Does the indirect vtable slot +0x14 return a width that any caller observes beyond AL?",
    "What are the meanings of the command values and material constants beyond their observed call order?",
    "What are the runtime values and ownership of context fields +0x5c, +0xb4, +0xc8, and +0xd0?",
    "What concrete editor, app-system, material-manager, and transition owners implement the external boundaries?",
    "command and material constants",
    "concrete editor, app-system, material-manager, and transition owners",
    "gate-editor-query-helpers",
    "runtime context field values"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg10-editor-dispatch/005dfd00.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg10_editor_dispatch/editor_query_helpers.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg10-editor-dispatch/005dfd00.json",
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
