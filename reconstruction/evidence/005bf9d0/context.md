# Reconstruction context 0x005bf9d0

- Status: `partial`
- Content SHA-256: `90c45379df6d38135f257fb66707ee8f144e546fe70af0b7579dfd390aafe5f5`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005bf9d0",
  "phase": "reconstruction",
  "target": "0x005bf9d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueUiShell",
  "name": "FUN_005bf9d0",
  "package": "PKG-18-UI-SCRIPTING",
  "subsystem": "UI.Scripting",
  "va": "0x005bf9d0"
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
  "content_sha256": "5ffdf54b8584dffb1dc15d24d7ab138cb831ae97eab6abb7594ab9fa6cd7ddc9",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005bf9d0 failed: Decompilation did not complete. Reason: ",
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
    "type": [
      "opaque UI shell/input state",
      "opaque editor/input state"
    ],
    "width_bytes": 4
  },
  "return_observation": [
    "AL is one for handled ids and zero for unmatched ids or failed shape checks.",
    "AL is one for handled branches and zero for unmatched ids or failed shape checks."
  ],
  "stack_arguments": [
    "{'entry_offset': 'ESP+0x04', 'name': 'message_id', 'position': 1, 'type': 'uint32', 'width_bytes': 4}",
    "{'entry_offset': 'ESP+0x08', 'name': 'message', 'position': 2, 'type': 'opaque UI message pointer', 'width_bytes': 4}",
    "{'entry_offset': 'ESP+0x08', 'name': 'message_payload', 'position': 2, 'type': 'opaque pointer', 'width_bytes': 4}"
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
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x005bfb4c",
      "direction": "out",
      "other": "0x005bf950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bfa9b",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bfa7b",
      "direction": "out",
      "other": "0x00804f80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bfa4b",
      "direction": "out",
      "other": "0x008053b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bfaba",
      "direction": "out",
      "other": "0x008105b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bfb13",
      "direction": "out",
      "other": "0x008105b0",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
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
    "opaque UI shell/input state",
    "opaque editor/input state",
    "opaque pointer",
    "uint32"
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
  "original_bytes": 13863,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-ui-scripting-message-routes\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"STRUCTURAL_ONLY\",\n    \"confidence\": {\n      \"identity\": \"medium-high\",\n      \"mechanics\": \"high\",\n      \"overall\": \"medium-high\"\n    },\n    \"contradictions\": [\n      {\n        \"path\": \"vtable_and_structs.vtable_candidate.projection_conflict\",\n        \"source\": \"knowledgegraph/research/semantic-decomp/worker-05-ui-shell.json\",\n        \"value\": \"The imported EditorNamePanel__vftable is 0x20 bytes, so the live table is longer or starts at another interface boundary.\"\n      }\n    ],\n    \"downstream_unlock_count\": 5,\n    \"evidence\": [\n      {\n        \"claim\": \"The body has four message-ID branches, exact payload guards, service +0x80 forwarding, manager +0x44 lookup, list traversal, and 0/1 return behavior.\",\n        \"level\": \"OBSERVED\",\n        \"source\": \"G01\"\n      },\n      {\n        \"claim\": \"The 0x013f7b84 data xref and 0x00edae70 call xref coexist with no resolved direct caller; the adjusted this-4 vtable +0x1c path is visible in the disassembly.\",\n        \"level\": \"OBSERVED\",\n        \"source\": \"G02\"\n      },\n      {\n        \"claim\": \"Five direct callees, zero canonical direct callers, and two observed xrefs.\",\n        \"level\": \"OBSERVED\",\n        \"source\": \"G03\"\n      },\n      {\n        \"claim\": \"EditorNamePanel 
[TRUNCATED]
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005bfb4c",
      "direction": "out",
      "other": "0x005bf950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bfa9b",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bfa7b",
      "direction": "out",
      "other": "0x00804f80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bfa4b",
      "direction": "out",
      "other": "0x008053b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bfaba",
      "direction": "out",
      "other": "0x008105b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005bfb13",
      "direction": "out",
      "other": "0x008105b0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [
    "0x005bf950",
    "0x0067caa0",
    "0x00804f80",
    "0x008053b0",
    "0x008105b0"
  ],
  "manifest_callers": [
    "unmodeled_call_0x00edae70"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0108",
    "size": 1
  },
  "vtable_reference_count": 0
}
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
    "symbol": "FUN_005c0100",
    "va": "0x005c0100"
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
      "shared_types:OpaqueUiMessage,opaque pointer"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 6,
    "symbol": "Editors_EditorUI_HandleMessage_005e0000",
    "va": "0x005e0000"
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
      "shared_types:DATA,uint32"
    ],
    "package": "pkg-dfw-0096ff70",
    "score": 6,
    "symbol": "dfw_func88h_0096ff70",
    "va": "0x0096ff70"
  },
  {
    "match_basis": [
      "shared_types:DATA,uint32"
    ],
    "package": "pkg-dfw-00980c50",
    "score": 6,
  
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
    "reconstruction/metadata/pkg18-ui-scripting/005bf9d0.json",
    "reconstruction/metadata/pkg18-ui-space/005bf9d0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 12842,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"STRUCTURAL_ONLY\",\n  \"confidence\": {\n    \"identity\": \"medium-high\",\n    \"mechanics\": \"high\",\n    \"overall\": \"medium-high\"\n  },\n  \"contradictions\": [\n    {\n      \"path\": \"vtable_and_structs.vtable_candidate.projection_conflict\",\n      \"source\": \"knowledgegraph/research/semantic-decomp/worker-05-ui-shell.json\",\n      \"value\": \"The imported EditorNamePanel__vftable is 0x20 bytes, so the live table is longer or starts at another interface boundary.\"\n    }\n  ],\n  \"downstream_unlock_count\": 5,\n  \"evidence\": [\n    {\n      \"claim\": \"The body has four message-ID branches, exact payload guards, service +0x80 forwarding, manager +0x44 lookup, list traversal, and 0/1 return behavior.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G01\"\n    },\n    {\n      \"claim\": \"The 0x013f7b84 data xref and 0x00edae70 call xref coexist with no resolved direct caller; the adjusted this-4 vtable +0x1c path is visible in the disassembly.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G02\"\n    },\n    {\n      \"claim\": \"Five direct callees, zero canonical direct callers, and two observed xrefs.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G03\"\n    },\n    {\n      \"claim\": \"EditorNamePanel is 56 bytes with the observed fields; live table 0x013f7b54 places this target at +0x30 and 0x005c0380 at +0x58.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G04\"\n    },\n    {\n      \"claim\": \"0x005bfd40 installs the
[TRUNCATED]
```

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 9608,
  "preview": "{\n  \"conflicts\": [\n    {\n      \"anchors\": [\n        \"0x00960250\",\n        \"0x00960250\",\n        \"0x005bf9d0\",\n        \"0x005bf9d0\",\n        \"0x005bfd40\",\n        \"0x005bfd40\",\n        \"0x005c0100\",\n        \"0x005c0100\",\n        \"0x005c0380\",\n        \"0x005c0380\",\n        \"0x007d8060\",\n        \"0x007d8060\",\n        \"0x007d8230\",\n        \"0x007d8230\",\n        \"0x007d8360\",\n        \"0x007d8360\"\n      ],\n      \"conflict_id\": \"U-DIALOG-BEHAVIOR\",\n      \"kind\": \"conflict_ledger\",\n      \"rejected\": [],\n      \"resolution\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n      \"resolution_status\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n      \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n      \"subject\": null,\n      \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n    },\n    {\n      \"anchors\": [\n        \"0x00960250\",\n        \"0x00960250\",\n        \"0x005bf9d0\",\n        \"0x005bf9d0\",\n        \"0x005bfd40\",\n        \"0x005bfd40\",\n        \"0x005c0100\",\n        \"0x005c0100\",\n        \"0x005c0380\",\n        \"0x005c0380\",\n        \"0x0095fcc0\",\n        \"0x0095fcc0\",\n        \"0x00960050\",\n        \"0x00960050\",\n        \"0x00960250\",\n        \"0x00960250\"\n      ],\n      \"conflict_
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg18-ui-scripting/005bf9d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg18-ui-space/005bf9d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg18-ui-scripting/ui_shell_functions_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg18_ui_scripting/ui_shell_functions.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg18-ui-scripting/005bf9d0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg18-ui-space/005bf9d0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg18-ui-
[TRUNCATED]
```
