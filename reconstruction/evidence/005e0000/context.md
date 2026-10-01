# Reconstruction context 0x005e0000

- Status: `partial`
- Content SHA-256: `25925294ee74305ac5a33faeaf91222db14fcf97ed8b3c9109e6582e54f79813`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005e0000",
  "phase": "reconstruction",
  "target": "0x005e0000"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueEditorUI",
  "name": "Editors_EditorUI_HandleMessage_005e0000",
  "package": "PKG-10-EDITOR-DISPATCH",
  "subsystem": "Editors.EditorUI",
  "va": "0x005e0000"
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
  "content_sha256": "f0f13db34f7f21645cf9d101b4334888130d8d9b6be755654d05094a73353715",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005e0000 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "return_register": "AL",
  "return_type": "bool",
  "stack_arguments": [
    {
      "entry_offset": "ESP+4",
      "name": "message_id",
      "signed": false,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+8",
      "name": "pMessage",
      "type": "opaque UTFWin::Message*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8
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
      "va": "0x00573c00"
    },
    {
      "name": "editor_query_service_005ca960",
      "reconstructed": true,
      "va": "0x005ca960"
    },
    {
      "name": "editor_query_reset_005dd750",
      "reconstructed": true,
      "va": "0x005dd750"
    },
    {
      "name": "FUN_005dda30",
      "reconstructed": true,
      "va": "0x005dda30"
    },
    {
      "name": "editor_query_dispatch_005dfd00",
      "reconstructed": true,
      "va": "0x005dfd00"
    },
    {
      "name": "editor_query_clear_flags_0093db80",
      "reconstructed": true,
      "va": "0x0093db80"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x005e00fa",
      "direction": "out",
      "other": "0x004a88d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005e011a",
      "direction": "out",
      "other": "0x004a88d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005e01d4",
      "direction": "out",
      "other": "0x004a88d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005e033e",
      "direction": "out",
      "other": "0x005724a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005e0353",
      "direction": "out",
      "other": "0x00573c00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005e025c",
      "direction": "out",
      "other": "0x0057c590",
      "reference_type": "direc
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueDispatchTarget",
    "OpaqueEditor / Editors::cEditor",
    "OpaqueEditorUI",
    "OpaquePreferenceQuery",
    "OpaquePreferenceQuery*",
    "OpaquePropertyValue",
    "OpaquePropertyValue / Property*",
    "OpaqueUiMessage",
    "OpaqueUiMessage / UTFWin::Message",
    "bool",
    "opaque UTFWin::Message*",
    "opaque command and dispatch targets",
    "opaque pointer",
    "uint32_t",
    "uint8_t",
    "void"
  ],
  "vtables": [
    "vtable:0x013f92c0"
  ]
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 9804,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-editor-ui-command-dispatch\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"BOUNDED_SEMANTIC\",\n    \"confidence\": {\n      \"events\": \"SUPPORTED_FOR_ANALYTICAL_EVENT_IDS\",\n      \"identity\": \"SUPPORTED\",\n      \"mechanics\": \"CONFIRMED\",\n      \"overall\": \"high_for_static_dispatch_medium_for_payload_and_return_abi\",\n      \"ownership\": \"SUPPORTED_WITH_CAVEAT\",\n      \"persistence\": \"CONFIRMED_AS_NON_PERSISTENT\",\n      \"runtime\": \"UNAVAILABLE\"\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 17,\n    \"evidence\": [\n      {\n        \"claim\": \"command-hash switch, receiver guards, mode/history callbacks, and result branches\",\n        \"class\": \"direct_body\",\n        \"source\": \"ghidra://SporeApp.exe@0x005e0000\"\n      },\n      {\n        \"claim\": \"the EditorUI candidate pointer run contains the target address\",\n        \"class\": \"raw_vtable_data\",\n        \"source\": \"ghidra_read_memory(0x013f92a0, 128); target word at 0x013f92d8\"\n      },\n      {\n        \"claim\": \"300-byte EditorUI receiver with editor pointer, message references, mode/control fields, and opaque flag at +0x108\",\n        \"class\": \"structure_layout\",\n        \"source\": \"ghidra_get_struct_layout(EditorUI)\"\n      },\n      {\n        \"claim\": \"mode updater suppresses equal modes, calls cEditor::SetActiveMode, and changes UI window sta
[TRUNCATED]
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
      "va": "0x00573c00"
    },
    {
      "name": "editor_query_service_005ca960",
      "reconstructed": true,
      "va": "0x005ca960"
    },
    {
      "name": "editor_query_reset_005dd750",
      "reconstructed": true,
      "va": "0x005dd750"
    },
    {
      "name": "FUN_005dda30",
      "reconstructed": true,
      "va": "0x005dda30"
    },
    {
      "name": "editor_query_dispatch_005dfd00",
      "reconstructed": true,
      "va": "0x005dfd00"
    },
    {
      "name": "editor_query_clear_flags_0093db80",
      "reconstructed": true,
      "va": "0x0093db80"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005e00fa",
      "direction": "out",
      "other": "0x004a88d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005e011a",
      "direction": "out",
      "other": "0x004a88d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005e01d4",
      "direction": "out",
      "other": "0x004a88d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005e033e",
      "direction": "out",
      "other": "0x005724a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005e0353",
      "direction": "out",
      "other": "0x00573c00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005e025c",

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
      "shared_types:OpaquePreferenceQuery,OpaquePropertyValue",
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 17,
    "symbol": "editor_query_reset_005dd750",
    "va": "0x005dd750"
  },
  {
    "match_basis": [
      "same_package",
      "shared_types:OpaquePreferenceQuery",
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 14,
    "symbol": "editor_query_clear_flags_0093db80",
    "va": "0x0093db80"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 13,
    "symbol": "FUN_005dda30",
    "va": "0x005dda30"
  },
  {
    "match_basis": [
      "same_package",
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 11,
    "symbol": "editor_query_service_005ca960",
    "va": "0x005ca960"
  },
  {
    "match_basis": [
      "same_package",
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 11,
    "symbol": "editor_query_dispatch_005dfd00",
    "va": "0x005dfd00"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 10,
    "symbol": "Editors_EditorModel_SetColor_raw_004ae250",
    "va": "0x004ae250"
  },
  {
    "match_basis": [
      "shared_types:OpaqueUiMessage,opaque pointer"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 6,
    "symbol": "FUN_005
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg10_editor_dispatch/editor_command_dispatch.cpp",
  "files": [
    "src/reconstruction/pkg10_editor_dispatch/editor_command_dispatch.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/005e0000.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 9100,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"events\": \"SUPPORTED_FOR_ANALYTICAL_EVENT_IDS\",\n    \"identity\": \"SUPPORTED\",\n    \"mechanics\": \"CONFIRMED\",\n    \"overall\": \"high_for_static_dispatch_medium_for_payload_and_return_abi\",\n    \"ownership\": \"SUPPORTED_WITH_CAVEAT\",\n    \"persistence\": \"CONFIRMED_AS_NON_PERSISTENT\",\n    \"runtime\": \"UNAVAILABLE\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 17,\n  \"evidence\": [\n    {\n      \"claim\": \"command-hash switch, receiver guards, mode/history callbacks, and result branches\",\n      \"class\": \"direct_body\",\n      \"source\": \"ghidra://SporeApp.exe@0x005e0000\"\n    },\n    {\n      \"claim\": \"the EditorUI candidate pointer run contains the target address\",\n      \"class\": \"raw_vtable_data\",\n      \"source\": \"ghidra_read_memory(0x013f92a0, 128); target word at 0x013f92d8\"\n    },\n    {\n      \"claim\": \"300-byte EditorUI receiver with editor pointer, message references, mode/control fields, and opaque flag at +0x108\",\n      \"class\": \"structure_layout\",\n      \"source\": \"ghidra_get_struct_layout(EditorUI)\"\n    },\n    {\n      \"claim\": \"mode updater suppresses equal modes, calls cEditor::SetActiveMode, and changes UI window state\",\n      \"class\": \"mode_sibling\",\n      \"source\": \"ghidra://SporeApp.exe@0x005dda30\"\n    },\n    {\n      \"claim\": \"Undo and Redo are direct delegated state/history callbacks\",\n      \"class\": \"history_sibli
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
        "0x005e0000",
        "0x70218642",
        "0xb006ef6e",
        "0xf006efa5",
        "0xf019c2e7",
        "0xf019c2f3",
        "0x005e0000",
        "0x004af260",
        "0x005dda30",
        "0x005737d0",
        "0x005737d0",
        "0x00587270",
        "0x00587270",
        "0x00588570",
        "0x00588570",
        "0x0058ac10"
      ],
      "conflict_id": "editor_ui_command_names",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    }
  ],
  "unresolved_questions": [
    "EditorUI+0x10c concrete owner",
    "What concrete Property* value is supplied to 0x005dd750, and how is that local value populated?",
    "What concrete types own the generic forwarder, preferences list, selection provider, and dispatch targets?",
    "What is the semantic identity of outer 0x9a1552d3/0x503517b0 and its two window virtual slots?",
    "Which concrete UI controls produce the opaque route, preferences, pending, dispatch-pair, and help hashes?",
    "Why does producer 0x70
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg10-editor-dispatch/005e0000.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg10_editor_dispatch/editor_command_dispatch.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg10-editor-dispatch/005e0000.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg10_editor_dispatch/editor_command_dispatch.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    "src/reconstruction/pkg10_editor_dispatch/editor_command_dispatch.cpp"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/O
[TRUNCATED]
```
