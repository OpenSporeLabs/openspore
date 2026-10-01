# Reconstruction context 0x005c0380

- Status: `partial`
- Content SHA-256: `3f30f8822f7feb82f16df482079c6e7846d3895644875b281e5d367df0d815c8`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005c0380",
  "phase": "reconstruction",
  "target": "0x005c0380"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueUiShell",
  "name": "FUN_005c0380",
  "package": "PKG-18-UI-SCRIPTING",
  "subsystem": "UI.Scripting",
  "va": "0x005c0380"
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
  "content_sha256": "644c287f20043bea5e333d9d1587d429941953b921029786297fb1b7aad77c74",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005c0380 failed: Decompilation did not complete. Reason: ",
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
  "return_observation": "void; unchanged state returns through the normal epilogue.",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "enabled",
      "position": 1,
      "type": "uint8",
      "width_bytes": 1
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
      "va": "0x0067dcc0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x005c0521",
      "direction": "out",
      "other": "0x00435ed0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0712",
      "direction": "out",
      "other": "0x00435ed0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c05ec",
      "direction": "out",
      "other": "0x00579a90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c05f5",
      "direction": "out",
      "other": "0x0057eda0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0619",
      "direction": "out",
      "other": "0x005bf950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0623",
      "direction": "out",
      "other": "0x005bf950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0470",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0529",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c071a",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c03a9",
      "direction": "out",
      "other": "0x008105b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c03d7",
      "direction": "out",
      "other"
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
    "OpaqueUiObject",
    "OpaqueUiShell",
    "UNCONDITIONAL_CALL",
    "opaque UI shell",
    "uint8"
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
  "original_bytes": 13123,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-ui-scripting-registration-state\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"BOUNDED_SEMANTIC\",\n    \"confidence\": {\n      \"identity\": \"medium-high\",\n      \"mechanics\": \"high\",\n      \"overall\": \"medium-high\"\n    },\n    \"contradictions\": [\n      {\n        \"path\": \"vtable_and_structs.vtable_candidate.projection_conflict\",\n        \"source\": \"knowledgegraph/research/semantic-decomp/worker-05-ui-shell.json\",\n        \"value\": \"The live table extends beyond the imported 0x20-byte EditorNamePanel vtable projection.\"\n      }\n    ],\n    \"downstream_unlock_count\": 8,\n    \"evidence\": [\n      {\n        \"claim\": \"The exact equality guard, field_10 write, enable/disable branches, service-key lookups, text/child operations, and two +0x14 calls are present.\",\n        \"level\": \"OBSERVED\",\n        \"source\": \"G01\"\n      },\n      {\n        \"claim\": \"0x013f7bac is the live data reference and 0x00edb9bd is the unresolved live call xref; the vtable calls are at +0x7c/+0x28/+0x4c/+0x94/+0xdc.\",\n        \"level\": \"OBSERVED\",\n        \"source\": \"G02\"\n      },\n      {\n        \"claim\": \"Eight direct callees, no canonical direct callers, and 17 depth-2 call-graph edges.\",\n        \"level\": \"OBSERVED\",\n        \"limit\": 100,\n        \"source\": \"G03\"\n      },\n      {\n        \"claim\": \"EditorNamePanel is 56 bytes; live t
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
      "va": "0x0067dcc0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005c0521",
      "direction": "out",
      "other": "0x00435ed0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0712",
      "direction": "out",
      "other": "0x00435ed0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c05ec",
      "direction": "out",
      "other": "0x00579a90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c05f5",
      "direction": "out",
      "other": "0x0057eda0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0619",
      "direction": "out",
      "other": "0x005bf950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0623",
      "direction": "out",
      "other": "0x005bf950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0470",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c0529",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c071a",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005c03a9",
      "direction": "out",
      "other": "0x008105b0",
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
      "shared_types:DATA,OpaqueUiObject,OpaqueUiShell,UNCONDITIONAL_CALL",
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
    "symbol": "FUN_005c0100",
    "va": "0x005c0100"
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
      "shared_types:DATA,uint8"
    ],
    "package": "PKG-APP-LIFECYCLE-WAVE7",
    "score": 6,
    "symbol": "app_capp_system_func88h_00a6c940",
    "va": "0x00a6c940"
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
      "shared_types:DATA"
    ],
    "package": "WAVE6-ENGINE-RUNTIME",
    "score": 3,
    "symbol"
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
    "reconstruction/metadata/pkg18-ui-scripting/005c0380.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 12216,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"identity\": \"medium-high\",\n    \"mechanics\": \"high\",\n    \"overall\": \"medium-high\"\n  },\n  \"contradictions\": [\n    {\n      \"path\": \"vtable_and_structs.vtable_candidate.projection_conflict\",\n      \"source\": \"knowledgegraph/research/semantic-decomp/worker-05-ui-shell.json\",\n      \"value\": \"The live table extends beyond the imported 0x20-byte EditorNamePanel vtable projection.\"\n    }\n  ],\n  \"downstream_unlock_count\": 8,\n  \"evidence\": [\n    {\n      \"claim\": \"The exact equality guard, field_10 write, enable/disable branches, service-key lookups, text/child operations, and two +0x14 calls are present.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G01\"\n    },\n    {\n      \"claim\": \"0x013f7bac is the live data reference and 0x00edb9bd is the unresolved live call xref; the vtable calls are at +0x7c/+0x28/+0x4c/+0x94/+0xdc.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G02\"\n    },\n    {\n      \"claim\": \"Eight direct callees, no canonical direct callers, and 17 depth-2 call-graph edges.\",\n      \"level\": \"OBSERVED\",\n      \"limit\": 100,\n      \"source\": \"G03\"\n    },\n    {\n      \"claim\": \"EditorNamePanel is 56 bytes; live table 0x013f7b54 places this target at +0x58 and 005bf9d0 at +0x30.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G04\"\n    },\n    {\n      \"claim\": \"0x005bfd40 initializes the bool and vtable, while 0x005bf950/0x005bfcc0 est
[TRUNCATED]
```

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 9412,
  "preview": "{\n  \"conflicts\": [\n    {\n      \"anchors\": [\n        \"0x00960250\",\n        \"0x00960250\",\n        \"0x005bf9d0\",\n        \"0x005bf9d0\",\n        \"0x005bfd40\",\n        \"0x005bfd40\",\n        \"0x005c0100\",\n        \"0x005c0100\",\n        \"0x005c0380\",\n        \"0x005c0380\",\n        \"0x007d8060\",\n        \"0x007d8060\",\n        \"0x007d8230\",\n        \"0x007d8230\",\n        \"0x007d8360\",\n        \"0x007d8360\"\n      ],\n      \"conflict_id\": \"U-DIALOG-BEHAVIOR\",\n      \"kind\": \"conflict_ledger\",\n      \"rejected\": [],\n      \"resolution\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n      \"resolution_status\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n      \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n      \"subject\": null,\n      \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n    },\n    {\n      \"anchors\": [\n        \"0x00960250\",\n        \"0x00960250\",\n        \"0x005bf9d0\",\n        \"0x005bf9d0\",\n        \"0x005bfd40\",\n        \"0x005bfd40\",\n        \"0x005c0100\",\n        \"0x005c0100\",\n        \"0x005c0380\",\n        \"0x005c0380\",\n        \"0x0095fcc0\",\n        \"0x0095fcc0\",\n        \"0x00960050\",\n        \"0x00960050\",\n        \"0x00960250\",\n        \"0x00960250\"\n      ],\n      \"conflict_
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg18-ui-scripting/005c0380.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg18-ui-scripting/ui_shell_functions_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg18_ui_scripting/ui_shell_functions.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg18-ui-scripting/005c0380.json",
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
