# Reconstruction context 0x01073700

- Status: `partial`
- Content SHA-256: `0708e354e79d6770513926e62988bcec0d68a4d282f1c7b7f26b65e68f4da1ee`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01073700",
  "phase": "reconstruction",
  "target": "0x01073700"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "SpaceUiState",
  "name": "pkg18_space_ui_initialize_01073700",
  "package": "PKG-18-UI-SPACE",
  "subsystem": "UI.Space",
  "va": "0x01073700"
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
  "content_sha256": "b8c4bc7eb049b15ea59a7ae0fd03b0aaee45fa6333d3a1d1d3f9c36650f98173",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x01073700 failed: Decompilation did not complete. Reason: ",
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
    "type": "SpaceUiState *",
    "width_bytes": 4
  },
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "termination": "RET for the normal path; saved-image non-null path transfers through the saved image vtable +0x04 slot"
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
    },
    {
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    },
    {
      "name": "FUN_00b3d230",
      "reconstructed": false,
      "va": "0x00b3d230"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "pkg12_space_01021300",
      "reconstructed": true,
      "va": "0x01021300"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010030c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01003230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01006ef0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01007430"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0100311c",
      "direction": "in",
      "other": "0x010030c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0100335b",
      "direction": "in",
      "other": "0x01003230",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010072c4",
      "direction": "in",
      "other": "0x01006ef0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010076d9",
      "direction": "in",
      "other": "0x01007430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01073dcb",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
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
    "SpaceUiObject",
    "SpaceUiObject *",
    "SpaceUiState",
    "SpaceUiState *",
    "SpaceUiVtable"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 15712,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-ui-space-initialization\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"BOUNDED_SEMANTIC\",\n    \"confidence\": {\n      \"identity\": \"medium-high\",\n      \"mechanics\": \"high\",\n      \"overall\": \"medium-high\"\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 55,\n    \"evidence\": [\n      {\n        \"claim\": \"The body creates/replaces named space UI resources, writes field_2F8=-1 and field_5D5=1, configures listener data, and invokes the optional Simulator branch.\",\n        \"level\": \"OBSERVED\",\n        \"source\": \"G01\"\n      },\n      {\n        \"claim\": \"Instruction 0x01073a2e writes [ESI+0x2f8]=0xffffffff; the target has a 0x01074393 jump-table warning and indirect tail.\",\n        \"level\": \"OBSERVED\",\n        \"source\": \"G02\"\n      },\n      {\n        \"claim\": \"Four named direct callers and 51 direct callee endpoints; three direct root edges are present.\",\n        \"level\": \"OBSERVED\",\n        \"limit\": 100,\n        \"source\": \"G03\"\n      },\n      {\n        \"claim\": \"SpaceGameUI is 1708 bytes, matching the 0x6ac allocation; 0x0149c3ec is a seven-slot IWinProc candidate and 0x0149c1d8 is a helper table/string record.\",\n        \"level\": \"OBSERVED\",\n        \"source\": \"G04\"\n      },\n      {\n        \"claim\": \"0x01070ba0 supplies the 0x6ac object, vptrs, mActivePaletteID=0, and field_2F8=-1; 0x0
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
    },
    {
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    },
    {
      "name": "FUN_00b3d230",
      "reconstructed": false,
      "va": "0x00b3d230"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "pkg12_space_01021300",
      "reconstructed": true,
      "va": "0x01021300"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010030c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01003230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01006ef0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01007430"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0100311c",
      "direction": "in",
      "other": "0x010030c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0100335b",
      "direction": "in",
      "other": "0x01003230",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010072c4",
      "direction": "in",
      "other": "0x01006ef0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010076d9",
      "direction": "in",
      "other": "0x01007430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01073dcb",
      "direction": "out"
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-18-UI-SPACE",
    "score": 8,
    "symbol": "pkg18_text_zoom_rebind_00834fa0",
    "va": "0x00834fa0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 3,
    "symbol": "pkg11_sim_core_00b21340",
    "va": "0x00b21340"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 3,
    "symbol": "pkg12_space_01021300",
    "va": "0x01021300"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg18_ui_space/ui_space.cpp",
  "files": [
    "src/reconstruction/pkg18_ui_space/ui_space.cpp",
    "src/reconstruction/pkg18_ui_space/ui_space.hpp",
    "src/reconstruction/pkg18_ui_space/ui_space_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg18-ui-space/01073700.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 14463,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"identity\": \"medium-high\",\n    \"mechanics\": \"high\",\n    \"overall\": \"medium-high\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 55,\n  \"evidence\": [\n    {\n      \"claim\": \"The body creates/replaces named space UI resources, writes field_2F8=-1 and field_5D5=1, configures listener data, and invokes the optional Simulator branch.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G01\"\n    },\n    {\n      \"claim\": \"Instruction 0x01073a2e writes [ESI+0x2f8]=0xffffffff; the target has a 0x01074393 jump-table warning and indirect tail.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G02\"\n    },\n    {\n      \"claim\": \"Four named direct callers and 51 direct callee endpoints; three direct root edges are present.\",\n      \"level\": \"OBSERVED\",\n      \"limit\": 100,\n      \"source\": \"G03\"\n    },\n    {\n      \"claim\": \"SpaceGameUI is 1708 bytes, matching the 0x6ac allocation; 0x0149c3ec is a seven-slot IWinProc candidate and 0x0149c1d8 is a helper table/string record.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G04\"\n    },\n    {\n      \"claim\": \"0x01070ba0 supplies the 0x6ac object, vptrs, mActivePaletteID=0, and field_2F8=-1; 0x01072d40 is the sibling IWinProc event handler.\",\n      \"level\": \"SUPPORTED\",\n      \"source\": \"G05\"\n    },\n    {\n      \"claim\": \"SDK SpaceGameUI layout identifies the field offsets, MessageListenerData shape, Glob
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
        "0x01073a2e",
        "0xffffffff",
        "0x01070ba0",
        "0xffffffff",
        "0x01073700",
        "0x013f7b54",
        "0x005bf9d0",
        "0x005c0380",
        "0x013f7b54",
        "0x005c0380",
        "0x0716d445",
        "0x0716d446",
        "0x00835080",
        "0x00834fa0"
      ],
      "kind": "semantic_decomp_contradiction",
      "path": "evidence_conflicts",
      "source": "knowledgegraph/research/semantic-decomp/worker-05-ui-shell.json",
      "statement": [
        {
          "id": "space_palette_field_offset_conflict",
          "observation": "Live disassembly at 0x01073a2e writes [ESI+0x2f8] = 0xffffffff. The SpaceGameUI structure labels +0x2f8 as field_2F8, not mActivePaletteID. Live constructor 0x01070ba0 writes param_1[0x8f] = 0, which is +0x23c, and param_1[0xbe] = 0xffffffff, which is +0x2f8.",
          "resolution": "Use field_2F8=-1 for the assigned setup body and mActivePaletteID=0 for the constructor-observed state. Do not propagate the historical mActivePaletteID=-1 claim.",
          "scope": "0x01073700 versus historical setup/state-machine claim",
          "sources": [
            "G02",
            "G04",
            "G05",
            "C03",
            "C04"
          ]
        },
        {
          "id": "editor_vtable_projection_mismatch",
          "observation": "The imported EditorNamePanel__vftable projection is 0x20 bytes, but the live table at 0x013f7b54 contains 0x005bf9d0 at +0x30 and 0x005c0380 at +0x58. The live table is therefore longer or begins at a dif
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg18-ui-space/01073700.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg18_ui_space/ui_space.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg18_ui_space/ui_space.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg18_ui_space/ui_space_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg18-ui-space/01073700.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg18_ui_space/ui_space.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg18_ui_space/ui_space.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg18_ui_space/ui_space_model_test.cpp",
   
[TRUNCATED]
```
