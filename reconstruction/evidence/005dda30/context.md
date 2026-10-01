# Reconstruction context 0x005dda30

- Status: `partial`
- Content SHA-256: `81c7f0e40ab3295ae4b403def83880353eba509570b27c27f8576f6a22bdd520`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005dda30",
  "phase": "reconstruction",
  "target": "0x005dda30"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueEditorModeManager",
  "name": "FUN_005dda30",
  "package": "PKG-10-EDITOR-DISPATCH",
  "subsystem": "Editors",
  "va": "0x005dda30"
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
  "content_sha256": "03a842e3746aa9e43e42ce8f279f199d0e001fe53ed46b08d662f21968a20edd",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005dda30 failed: Decompilation did not complete. Reason: ",
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
  "return_type": "void",
  "stack_arguments": [
    {
      "abi_type": "std::uint32_t",
      "entry_offset": "ESP+4",
      "name": "mode",
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
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
      "va": "0x00574a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dc310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dcf20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dd610"
    },
    {
      "name": "shared_default_stub_00b1e4d0",
      "reconstructed": true,
      "va": "0x00b1e4d0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057c2f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005de9e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dec10"
    },
    {
      "name": "Editors_EditorUI_HandleMessage_005e0000",
      "reconstructed": true,
      "va": "0x005e0000"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0057c326",
      "direction": "in",
      "other": "0x0057c2f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005de9e5",
      "direction": "in",
      "other": "0x005de9e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005ded08",
      "direction": "in",
      "other": "0x005dec10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005e013d",
      "direction": "in",
      "other": "0x005e0000",
      "refe
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueEditor",
    "OpaqueEditorModeManager",
    "OpaqueEditorModeTarget",
    "OpaqueEditorModeTarget / opaque void*",
    "std::uint32_t",
    "void"
  ],
  "vtables": [
    "vtable:0x005ddb6e"
  ]
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 8146,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"editor_mode_transition_observation\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"NEEDS_RUNTIME\",\n    \"confidence\": {\n      \"overall\": 0.9\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 14,\n    \"evidence\": [\n      {\n        \"finding\": \"Mode guard, cEditor::SetActiveMode call, +0x7c window hooks, and receiver+0x60 store.\",\n        \"kind\": \"target_decompilation\",\n        \"source\": \"Ghidra 0x005dda30\"\n      },\n      {\n        \"finding\": \"Four distinct callers; 0x005e0000 supplies explicit Build/Paint/Play request branches.\",\n        \"kind\": \"direct_callers\",\n        \"source\": \"Ghidra callers of 0x005dda30\"\n      },\n      {\n        \"finding\": \"Recovered cEditor body performs old-mode teardown, writes cEditor+0x31c, and performs new-mode entry work.\",\n        \"kind\": \"sibling_and_consumer\",\n        \"source\": \"Ghidra 0x00587270\"\n      },\n      {\n        \"finding\": \"The target is independently recorded as the EditorUI mode updater and generated event editor_active_mode_requested.\",\n        \"kind\": \"committed_state_artifact\",\n        \"source\": \"knowledgegraph/research/state-machines/editor-workflows.json:846-882\"\n      },\n      {\n        \"finding\": \"No direct Sporepedia metadata, cSPAssetDataOTDB, cCommEvent, or network edge.\",\n        \"kind\": \"negative_family_check\",\n        \"source\": \"
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
      "va": "0x00574a20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dc310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dcf20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dd610"
    },
    {
      "name": "shared_default_stub_00b1e4d0",
      "reconstructed": true,
      "va": "0x00b1e4d0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057c2f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005de9e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005dec10"
    },
    {
      "name": "Editors_EditorUI_HandleMessage_005e0000",
      "reconstructed": true,
      "va": "0x005e0000"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0057c326",
      "direction": "in",
      "other": "0x0057c2f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005de9e5",
      "direction": "in",
      "other": "0x005de9e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005ded08",
      "direction": "in",
      "other": "0x005dec10",
      "reference_type": "direct-call"
    },
    {
      "calls
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
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 13,
    "symbol": "Editors_EditorUI_HandleMessage_005e0000",
    "va": "0x005e0000"
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
      "same_package"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 8,
    "symbol": "editor_query_service_005ca960",
    "va": "0x005ca960"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 8,
    "symbol": "editor_query_reset_005dd750",
    "va": "0x005dd750"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 8,
    "symbol": "editor_query_dispatch_005dfd00",
    "va": "0x005dfd00"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 8,
    "symbol": "editor_query_clear_flags_0093db80",
    "va": "0x0093db80"
  },
  {
    "match_basis": [
      "shared_types:OpaqueEditor",
      "same_calling_convention"
    ],
    "package": "PKG-20-PERSISTENCE-BOUNDARY",
    "score": 5,
    "symbol": "PaintPersistenceBoundary_submit_004c5200",
    "va": "0x004c5200"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "pkg-00b1e4d0-shared-default-stub",
    "s
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg10_editor_dispatch/editor_dispatch.cpp",
  "files": [
    "src/reconstruction/pkg10_editor_dispatch/editor_dispatch.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/005dda30.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 7633,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": 0.9\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 14,\n  \"evidence\": [\n    {\n      \"finding\": \"Mode guard, cEditor::SetActiveMode call, +0x7c window hooks, and receiver+0x60 store.\",\n      \"kind\": \"target_decompilation\",\n      \"source\": \"Ghidra 0x005dda30\"\n    },\n    {\n      \"finding\": \"Four distinct callers; 0x005e0000 supplies explicit Build/Paint/Play request branches.\",\n      \"kind\": \"direct_callers\",\n      \"source\": \"Ghidra callers of 0x005dda30\"\n    },\n    {\n      \"finding\": \"Recovered cEditor body performs old-mode teardown, writes cEditor+0x31c, and performs new-mode entry work.\",\n      \"kind\": \"sibling_and_consumer\",\n      \"source\": \"Ghidra 0x00587270\"\n    },\n    {\n      \"finding\": \"The target is independently recorded as the EditorUI mode updater and generated event editor_active_mode_requested.\",\n      \"kind\": \"committed_state_artifact\",\n      \"source\": \"knowledgegraph/research/state-machines/editor-workflows.json:846-882\"\n    },\n    {\n      \"finding\": \"No direct Sporepedia metadata, cSPAssetDataOTDB, cCommEvent, or network edge.\",\n      \"kind\": \"negative_family_check\",\n      \"source\": \"Ghidra direct callee set and structure checks\"\n    }\n  ],\n  \"family\": \"editor_mode_lifecycle\",\n  \"interfaces\": {\n    \"boundaries\": {\n      \"boundary_rule\": \"Keep editor mode state separate from App game-mode state, 
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
        "0x00591fa0",
        "0x005dec10",
        "0x00883a90",
        "0x00883ad0",
        "0x051cc0b8",
        "0xb2e18705",
        "0x00883ad0",
        "0x00883a90",
        "0x00591fa0",
        "0x004af260",
        "0x005dda30",
        "0x00591690",
        "0x051cc0b8",
        "0x00591fa0",
        "0x005dec10",
        "0xb2e18705"
      ],
      "conflict_id": "editor_message_names_and_payloads",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
      "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x0057ce80",
        "0x00587270",
        "0x00587270",
        "0x0057f3e0",
        "0x005dda30",
        "0x005737d0",
        "0x005737d0",
        "0x00576c50",
        "0x00576c50",
        "0x0057ce80",
        "0x0057ce80",
        "0x0057ce80",
        "0x00584300",
        "0x00584300",
        "0x00587270",
        "0x00587270"
      ],
      "conflict_id": "editor_mode_gate",
      "kind": "conflict_ledger",
      "rejected": [],
      "r
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg10-editor-dispatch/005dda30.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg10_editor_dispatch/editor_dispatch.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg10-editor-dispatch/005dda30.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg10_editor_dispatch/editor_dispatch.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    "src/reconstruction/pkg10_editor_dispatch/editor_dispatch.cpp"
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
