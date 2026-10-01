# Reconstruction context 0x004ae250

- Status: `partial`
- Content SHA-256: `77e5442ce0140dcdac269bcd4233b5d47ec0621d684956f27f59b20995621ede`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x004ae250",
  "phase": "reconstruction",
  "target": "0x004ae250"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueEditorModel",
  "name": "Editors::EditorModel::SetColor",
  "package": "PKG-10-EDITOR-DISPATCH",
  "subsystem": "Editors.EditorModel",
  "va": "0x004ae250"
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
  "content_sha256": "b8b31ec81d0dcaff08802952947481e76180d41b5c50ad617bf4448f1453c745",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x004ae250 failed: Decompilation did not complete. Reason: ",
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
      "adapter_use": "ignored",
      "entry_offset": "ESP+4",
      "name": "index",
      "signed": true,
      "type": "int",
      "width_bytes": 4
    },
    {
      "adapter_use": "ignored",
      "entry_offset": "ESP+8",
      "fields": [
        {
          "keys": [
            "name",
            "offset",
            "type",
            "width_bytes"
          ]
        },
        {
          "keys": [
            "name",
            "offset",
            "type",
            "width_bytes"
          ]
        },
        {
          "keys": [
            "name",
            "offset",
            "type",
            "width_bytes"
          ]
        }
      ],
      "name": "color",
      "type": "EditorModelColor / ColorRGB",
      "width_bytes": 12
    }
  ],
  "stack_cleanup_bytes": 16
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
      "va": "0x00441440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044d8f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044e720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00451400"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00453dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00453e20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00454dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00455fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00456cb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0047fcb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004928d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004942b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049b460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b2f80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b7660"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x004414f4",
      "direction": "in",
      "other": "0x00441440",
      "reference_type": "di
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "EditorModelColor",
    "EditorModelColor / ColorRGB",
    "OpaqueEditorModel",
    "float",
    "int",
    "void"
  ],
  "vtables": [
    "vtable:0x013ef110",
    "vtable:0x013f2194",
    "vtable:0x013f21d8",
    "vtable:0x013f276c",
    "vtable:0x013f2d68",
    "vtable:0x01453254",
    "vtable:0x01453998",
    "vtable:0x01458024",
    "vtable:0x01458788",
    "vtable:0x014599e8",
    "vtable:0x01459a88"
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
      "gate-editor-model-setcolor-symbol-mapping"
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
      "va": "0x00441440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044d8f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044e720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00451400"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00453dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00453e20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00454dc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00455fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00456cb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0047fcb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004928d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004942b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049b460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b2f80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b7660"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x004414f
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
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 10,
    "symbol": "FUN_005dda30",
    "va": "0x005dda30"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 10,
    "symbol": "Editors_EditorUI_HandleMessage_005e0000",
    "va": "0x005e0000"
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
      "shared_vtable:vtable:0x013ef110,vtable:0x013f2194",
      "same_calling_convention"
    ],
    "package": "pkg-vft-preinc-0051e340",
    "score": 6,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013ef110,vtable:0x013f2194",
      "same_calling_convention"
    ],
    "package": "subobject-forward-0051e380",
    "score
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorModel__SetColor.c",
  "file": "src/reconstruction/pkg10_editor_dispatch/editor_model_set_color.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorModel__SetColor.c",
    "src/reconstruction/pkg10_editor_dispatch/editor_model_set_color.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/004ae250.json"
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
    "Do any callers depend on EAX retaining its incoming value, even though the target itself does not write EAX?",
    "EAX preservation expectations",
    "Is 0x004ae250 an intentionally empty callback/base implementation despite the SDK SetColor address association, or is the imported symbol mapping incomplete?",
    "What concrete owners correspond to the ten undefined pointer-table entries?",
    "Why do all observed direct calls and ten pointer-table entries use an ECX-only shape when the SDK/Ghidra formal signature has a 16-byte explicit argument area?",
    "gate-editor-model-setcolor-symbol-mapping",
    "imported address mapping",
    "pointer-table owners",
    "raw ECX-only calls versus SDK formal arguments"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorModel__SetColor.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg10-editor-dispatch/004ae250.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg10_editor_dispatch/editor_model_set_color.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__EditorModel__SetColor.c",
      "source_class": "committed_artifact"
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
      "ref": "reconstruction/metadata/pkg10-editor-dispatch/004ae250.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg10_editor_dispatch/editor_model_set_color.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowl
[TRUNCATED]
```
