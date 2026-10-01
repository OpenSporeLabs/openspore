# Reconstruction context 0x00588570

- Status: `partial`
- Content SHA-256: `93a740cbadc9f514edcf74c82082691e5fd52496b7280a737ec5470fc410fc73`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00588570",
  "phase": "reconstruction",
  "target": "0x00588570"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Editors::cEditor::OnMouseDown",
  "package": "PKG-EDITOR-INPUT-WAVE6",
  "subsystem": "Editor.Input",
  "va": "0x00588570"
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
  "content_sha256": "49bb46426b6d9f586d78ebeb4ab9d816253454eb1aa0331afd9cacbe1ca1ccb3",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00588570 failed: Decompilation did not complete. Reason: ",
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
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup",
  "return_semantics": "bool in AL from the selected mouse-down path",
  "return_type": "bool",
  "stack_cleanup_bytes": 16,
  "stack_cleanup_owner": "caller"
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
      "va": "0x0045ae10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a88d0"
    },
    {
      "name": "FUN_004adc40",
      "reconstructed": false,
      "va": "0x004adc40"
    },
    {
      "name": "Editors_EditorModel_SetColor_raw_004ae250",
      "reconstructed": true,
      "va": "0x004ae250"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b09b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005766e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005772b0"
    },
    {
      "name": "utfwin_safe_wave11_005ac9f0",
      "reconstructed": true,
      "va": "0x005ac9f0"
    },
    {
      "name": "sporepedia_nop_slot_FUN_00c2e4e0",
      "reconstructed": true,
      "va": "0x00c2e4e0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x005888ee",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00588c7e",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005888b0",
      "direction": "out",
      "other": "0x00435a10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00588c20",
      "direction": "out"
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "bool",
    "openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor",
    "openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks",
    "openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget",
    "openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget",
    "openspore::reconstruction::pkg_editor_input_wave6::TargetWord"
  ],
  "vtables": [
    "vtable:0x013f57f8"
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
      "graphics availability, mode-specific input targets, and runtime button ownership remain gated",
      "runtime validation not run"
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
      "va": "0x0045ae10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a88d0"
    },
    {
      "name": "FUN_004adc40",
      "reconstructed": false,
      "va": "0x004adc40"
    },
    {
      "name": "Editors_EditorModel_SetColor_raw_004ae250",
      "reconstructed": true,
      "va": "0x004ae250"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b09b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573c00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005766e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005772b0"
    },
    {
      "name": "utfwin_safe_wave11_005ac9f0",
      "reconstructed": true,
      "va": "0x005ac9f0"
    },
    {
      "name": "sporepedia_nop_slot_FUN_00c2e4e0",
      "reconstructed": true,
      "va": "0x00c2e4e0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005888ee",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00588c7e",
      "direction": "out",
      "other": "0x00401050",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005888b0",
      "direction": "out",
      "other": "0x00435a10",
      "reference_type"
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
      "shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 29,
    "symbol": "editor_input_005737d0",
    "va": "0x005737d0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 29,
    "symbol": "editor_input_00585890",
    "va": "0x00585890"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "packa
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseDown.c",
  "file": "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseDown.c",
    "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-input-wave6/00588570.json"
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
        "0x00d2e4a0",
        "0x00d2e4a0",
        "0x00aeb7b0",
        "0x005737d0",
        "0x005737d0",
        "0x00585d10",
        "0x00585d10",
        "0x00586410",
        "0x00586410",
        "0x00586b00",
        "0x00586b00",
        "0x00587270",
        "0x00587270",
        "0x00588570",
        "0x00588570",
        "0x0058a5a0"
      ],
      "conflict_id": "U-002-tribe-plans",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
      "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x005737d0",
        "0x00588570",
        "0x0058ac10",
        "0x00b3d350",
        "0x00e818f0",
        "0x00b3d350",
        "0x00e818f0",
        "0x00b3d350",
        "0x005737d0",
        "0x00576c50",
        "0x00576c50",
        "0x0057ce80",
        "0x0057ce80",
        "0x00584300",
        "0x00584300",
        "0x00587a20"
      ],
      "conflict_id": "editor_input_routing",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The input/UI surface is structurally present, but partition, 
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseDown.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-input-wave6/00588570.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_input_wave6/editor_input.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseDown.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-editor-input-wave6/00588570.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/know
[TRUNCATED]
```
