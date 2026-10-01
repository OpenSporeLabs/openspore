# Reconstruction context 0x00834fa0

- Status: `partial`
- Content SHA-256: `c35512cf7d989935d9dfc0d1ffeee8bb53adf363da83b6a2c0d4cd480970c75f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00834fa0",
  "phase": "reconstruction",
  "target": "0x00834fa0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "ZoomOwner",
  "name": "pkg18_text_zoom_rebind_00834fa0",
  "package": "PKG-18-UI-SPACE",
  "subsystem": "UI.Space.TextZoom",
  "va": "0x00834fa0"
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
  "content_sha256": "922c00fd037b45f64f30465a70c546ac2bed84e26cc7757ad6aa673c3b1438a1",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00834fa0 failed: Decompilation did not complete. Reason: ",
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
  "receiver": {
    "register": "ECX",
    "type": "ZoomOwner *",
    "width_bytes": 4
  },
  "return_observation": "AL is zero on the null-source and zero-selected-value paths and one on the normal completion path.",
  "return_register": "EAX",
  "return_type": "bool",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "source",
      "position": 1,
      "type": "Opaque",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "target",
      "position": 2,
      "type": "Opaque",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0c",
      "name": "mode",
      "position": 3,
      "type": "Opaque",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x10",
      "name": "state",
      "position": 4,
      "type": "Opaque",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x14",
      "name": "resource_key_0",
      "position": 5,
      "type": "Opaque",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x18",
      "name": "resource_key_1",
      "position": 6,
      "type": "Opaque",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x1c",
      "name": "resource_key_2",
      "position": 7,
      "type": "Opaque",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 28,
  "termination": "RET 0x1c"
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
      "va": "0x00658440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0066daf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e15780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ecf320"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ef50a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f149d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0106f3d0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00658734",
      "direction": "in",
      "other": "0x00658440",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0066e116",
      "direction": "in",
      "other": "0x0066daf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e15902",
      "direction": "in",
      "other": "0x00e15780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ecf3f3",
      "direction": "in",
      "other": "0x00ecf320",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ef582c",
      "direction": "in",
      "other": "0x00ef50a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ef5d4f",
      "direction": "in",
      "other": "0x00ef50a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f14ad5",
      "direction": "in",
      "other": "0x00f149d0",
      "referenc
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "Opaque",
    "ZoomObject",
    "ZoomOwner",
    "ZoomOwner *",
    "ZoomVtable",
    "bool"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 13680,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-ui-space-text-zoom-rebind\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"STRUCTURAL_ONLY\",\n    \"confidence\": {\n      \"identity\": \"medium\",\n      \"mechanics\": \"high\",\n      \"overall\": \"medium-high\"\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 18,\n    \"evidence\": [\n      {\n        \"claim\": \"The target validates nested virtuals, has a same-binding fast path, replaces four associated objects, updates key/state fields, calls service 0x626e3b8, and returns 0/1.\",\n        \"level\": \"OBSERVED\",\n        \"source\": \"G01\"\n      },\n      {\n        \"claim\": \"RET 0x1c confirms seven stack arguments; the UI/cSPUITextZoom literal and service callback are instruction-level facts.\",\n        \"level\": \"OBSERVED\",\n        \"source\": \"G02\"\n      },\n      {\n        \"claim\": \"Seven named direct callers, eleven direct callees, and 26 depth-2 call-graph edges.\",\n        \"level\": \"OBSERVED\",\n        \"source\": \"G03\"\n      },\n      {\n        \"claim\": \"cSPUITextZoom is 120 bytes; 0x008345c0 installs three vptrs and default sentinels; 0x00989000 returns a UTFWin Window-like object with relevant +0x20c state.\",\n        \"level\": \"OBSERVED\",\n        \"source\": \"G04\"\n      },\n      {\n        \"claim\": \"Constructor, teardown, layout update, and SpaceGameUI sibling paths all operate on the same +0x64..+0x74 slo
[TRUNCATED]
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
      "va": "0x00658440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0066daf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e15780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ecf320"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ef50a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f149d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0106f3d0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00658734",
      "direction": "in",
      "other": "0x00658440",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0066e116",
      "direction": "in",
      "other": "0x0066daf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e15902",
      "direction": "in",
      "other": "0x00e15780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ecf3f3",
      "direction": "in",
      "other": "0x00ecf320",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ef582c",
      "direction": "in",
      "other": "0x00ef50a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ef5d4f",
      "direction": "in",
      "other": "0x00ef50a0",
      "reference_type": "direct-call"
    },
    {
      "callsite"
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
    "symbol": "pkg18_space_ui_initialize_01073700",
    "va": "0x01073700"
  },
  {
    "match_basis": [
      "shared_types:Opaque"
    ],
    "package": "PKG-UTFWIN-LAYOUT-WAVE6",
    "score": 3,
    "symbol": "pkg_utfwin_layout_wave6_00967e80",
    "va": "0x00967e80"
  },
  {
    "match_basis": [
      "shared_types:Opaque"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 3,
    "symbol": "utfwin_0096ffc0",
    "va": "0x0096ffc0"
  },
  {
    "match_basis": [
      "shared_types:Opaque"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 3,
    "symbol": "utfwin_0097e550",
    "va": "0x0097e550"
  },
  {
    "match_basis": [
      "shared_types:Opaque"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 3,
    "symbol": "utfwin_0097e890",
    "va": "0x0097e890"
  },
  {
    "match_basis": [
      "shared_types:Opaque"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 3,
    "symbol": "utfwin_00980200",
    "va": "0x00980200"
  },
  {
    "match_basis": [
      "shared_types:Opaque"
    ],
    "package": "PKG-UTFWIN-EFFECTS-WAVE6",
    "score": 3,
    "symbol": "utfwin_00980470",
    "va": "0x00980470"
  },
  {
    "match_basis": [
      "shared_types:Opaque"
    ],
    "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
    "score": 3,
    "symbol": "mission_track_predicate_00febc90",
    "va": "0x00febc90"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg18_ui_space/zoom_boundary_00834fa0.cpp",
  "files": [
    "reconstruction/staging/pkg18-ui-space/zoom_boundary_00834fa0.cpp",
    "reconstruction/staging/pkg18-ui-space/zoom_boundary_00834fa0.hpp",
    "reconstruction/staging/pkg18-ui-space/zoom_boundary_00834fa0_model_test.cpp",
    "src/reconstruction/pkg18_ui_space/zoom_boundary_00834fa0.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json",
    "reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg18-ui-space/00834fa0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 12645,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"STRUCTURAL_ONLY\",\n  \"confidence\": {\n    \"identity\": \"medium\",\n    \"mechanics\": \"high\",\n    \"overall\": \"medium-high\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 18,\n  \"evidence\": [\n    {\n      \"claim\": \"The target validates nested virtuals, has a same-binding fast path, replaces four associated objects, updates key/state fields, calls service 0x626e3b8, and returns 0/1.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G01\"\n    },\n    {\n      \"claim\": \"RET 0x1c confirms seven stack arguments; the UI/cSPUITextZoom literal and service callback are instruction-level facts.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G02\"\n    },\n    {\n      \"claim\": \"Seven named direct callers, eleven direct callees, and 26 depth-2 call-graph edges.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G03\"\n    },\n    {\n      \"claim\": \"cSPUITextZoom is 120 bytes; 0x008345c0 installs three vptrs and default sentinels; 0x00989000 returns a UTFWin Window-like object with relevant +0x20c state.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G04\"\n    },\n    {\n      \"claim\": \"Constructor, teardown, layout update, and SpaceGameUI sibling paths all operate on the same +0x64..+0x74 slots.\",\n      \"level\": \"SUPPORTED\",\n      \"source\": \"G05\"\n    },\n    {\n      \"claim\": \"The SDK exports cSPUITextZoom::Initialize and a 120-byte structure, but does not recover the target ABI.\",\n      \"level\": \
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
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg18-ui-space/00834fa0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg18-ui-space/zoom_boundary_00834fa0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg18-ui-space/zoom_boundary_00834fa0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg18-ui-space/zoom_boundary_00834fa0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg18_ui_space/zoom_boundary_00834fa0.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg18-ui-space/00834fa0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg18-ui-space/zoom_boundary_00834fa0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/
[TRUNCATED]
```
