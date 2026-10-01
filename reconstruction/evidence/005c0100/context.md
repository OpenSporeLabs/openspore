# Reconstruction context 0x005c0100

- Status: `partial`
- Content SHA-256: `d987016b653610d923414f6b19cbea193ad109a8f816d7203e8c7a3750c7e433`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005c0100",
  "phase": "reconstruction",
  "target": "0x005c0100"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueUiShell",
  "name": "FUN_005c0100",
  "package": "PKG-18-UI-SCRIPTING",
  "subsystem": "UI.Scripting",
  "va": "0x005c0100"
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
  "content_sha256": "af95489d02e66f9c73e36605a18070e360edac2f9ebabb71ffd643c3e38fa5f8",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005c0100 failed: Decompilation did not complete. Reason: ",
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
  "receiver": {
    "register": "ECX",
    "type": "opaque UI shell",
    "width_bytes": 4
  },
  "return_observation": "AL is one for handled message shapes and zero for unmatched shapes.",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "unused",
      "position": 1,
      "type": "opaque uint32",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "message",
      "position": 2,
      "type": "opaque UI message pointer",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "termination": "RET 0x8"
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
      "name": null,
      "reconstructed": false,
      "va": "0x00edb750"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00edb94c",
      "direction": "in",
      "other": "0x00edb750",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0163",
      "direction": "out",
      "other": "0x004010a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0152",
      "direction": "out",
      "other": "0x00435ed0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0176",
      "direction": "out",
      "other": "0x005bf950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c016a",
      "direction": "out",
      "other": "0x005ecf80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0220",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0257",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c028b",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c02c2",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c02f4",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0211",
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
  "types": [
    "DATA",
    "OpaqueUiMessage",
    "OpaqueUiObject",
    "OpaqueUiShell",
    "UNCONDITIONAL_CALL",
    "opaque UI message pointer",
    "opaque UI shell",
    "opaque uint32"
  ],
  "vtables": [
    "vtable:0x013f7b70"
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
      "gate-ui-scripting-message-routes"
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
      "name": null,
      "reconstructed": false,
      "va": "0x00edb750"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00edb94c",
      "direction": "in",
      "other": "0x00edb750",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0163",
      "direction": "out",
      "other": "0x004010a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0152",
      "direction": "out",
      "other": "0x00435ed0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0176",
      "direction": "out",
      "other": "0x005bf950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c016a",
      "direction": "out",
      "other": "0x005ecf80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0220",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0257",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c028b",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c02c2",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c02f4",
      "direction": "out",
      "other": "0x0067caa0",
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
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:DATA,OpaqueUiMessage,OpaqueUiObject,OpaqueUiShell",
      "shared_vtable:vtable:0x013f7b70"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 32,
    "symbol": "FUN_005bf9d0",
    "va": "0x005bf9d0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:DATA,OpaqueUiObject,OpaqueUiShell,UNCONDITIONAL_CALL",
      "shared_vtable:vtable:0x013f7b70"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 32,
    "symbol": "FUN_005c0380",
    "va": "0x005c0380"
  },
  {
    "match_basis": [
      "shared_types:DATA,UNCONDITIONAL_CALL"
    ],
    "package": "wave6-resources",
    "score": 6,
    "symbol": "property_list_has_property_006a2470",
    "va": "0x006a2470"
  },
  {
    "match_basis": [
      "shared_types:DATA,UNCONDITIONAL_CALL"
    ],
    "package": "wave6-resources",
    "score": 6,
    "symbol": "property_list_get_property_object_006a24d0",
    "va": "0x006a24d0"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE10",
    "score": 3,
    "symbol": "skin_painter_job_brush_pass_005182f0",
    "va": "0x005182f0"
  },
  {
    "match_basis": [
      "shared_types:OpaqueUiMessage"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 3,
    "symbol": "Editors_EditorUI_HandleMessage_005e0000",
    "va": "0x005e0000"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "WAVE6-ENGINE-RUNTIME",
    "score": 3,
    
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg18_ui_scripting/ui_shell_functions.cpp",
  "files": [
    "reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.cpp",
    "reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.hpp",
    "reconstruction/staging/pkg18-ui-scripting/ui_shell_functions_model_test.cpp",
    "src/reconstruction/pkg18_ui_scripting/ui_shell_functions.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg18-ui-scripting/005c0100.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "anchors": [
        "0x00960250",
        "0x00960250",
        "0x005bf9d0",
        "0x005bf9d0",
        "0x005bfd40",
        "0x005bfd40",
        "0x005c0100",
        "0x005c0100",
        "0x005c0380",
        "0x005c0380",
        "0x007d8060",
        "0x007d8060",
        "0x007d8230",
        "0x007d8230",
        "0x007d8360",
        "0x007d8360"
      ],
      "conflict_id": "U-DIALOG-BEHAVIOR",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
      "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00960250",
        "0x00960250",
        "0x005bf9d0",
        "0x005bf9d0",
        "0x005bfd40",
        "0x005bfd40",
        "0x005c0100",
        "0x005c0100",
        "0x005c0380",
        "0x005c0380",
        "0x0095fcc0",
        "0x0095fcc0",
        "0x00960050",
        "0x00960050",
        "0x00960250",
        "0x00960250"
      ],
      "conflict_id": "U-SCREEN-STATE-BITS",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and cons
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg18-ui-scripting/005c0100.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg18-ui-scripting/ui_shell_functions_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg18_ui_scripting/ui_shell_functions.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg18-ui-scripting/005c0100.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/stagi
[TRUNCATED]
```
