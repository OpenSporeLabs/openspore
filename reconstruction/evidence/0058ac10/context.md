# Reconstruction context 0x0058ac10

- Status: `partial`
- Content SHA-256: `67997607785fb13df85e466bc56fb6e13858e386c237c18f9b93a88261900ffc`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0058ac10",
  "phase": "reconstruction",
  "target": "0x0058ac10"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Editors::cEditor::OnKeyDown",
  "package": "PKG-EDITOR-INPUT-WAVE6",
  "subsystem": "Editor.Input",
  "va": "0x0058ac10"
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
  "content_sha256": "a381a0649ce1de8057627b4aa501cd387fdce07b30a1271ffc3ac8d985b3f256",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0058ac10 failed: Decompilation did not complete. Reason: ",
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
  "return_semantics": "bool in AL from the selected key-down path",
  "return_type": "bool",
  "stack_cleanup_bytes": 8,
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
      "va": "0x00438700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043eed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004adaa0"
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
      "va": "0x005772b0"
    },
    {
      "name": "editor_query_dispatch_005dfd00",
      "reconstructed": true,
      "va": "0x005dfd00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "game_input_on_key_down_00697a50",
      "reconstructed": true,
      "va": "0x00697a50"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x0058ac68",
      "direction": "out",
      "other": "0x00401030",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b25e",
      "direction": "out",
      "other": "0x00401040",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058af55",
      "direction": "out",
      "other": "0x00435a10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058afb5",
      "direction": "out",
      "other": "0x00435a10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b02b",
      "direction": "out",
      "other": "0x00435a10",
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
      "input command domains, external paths, wheel handling, and runtime object/vtable ownership remain gated",
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
      "va": "0x00438700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043eed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004adaa0"
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
      "va": "0x005772b0"
    },
    {
      "name": "editor_query_dispatch_005dfd00",
      "reconstructed": true,
      "va": "0x005dfd00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    },
    {
      "name": "game_input_on_key_down_00697a50",
      "reconstructed": true,
      "va": "0x00697a50"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0058ac68",
      "direction": "out",
      "other": "0x00401030",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b25e",
      "direction": "out",
      "other": "0x00401040",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058af55",
      "direction": "out",
      "other": "0x00435a10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058afb5",
      "direction": "out",
      "other": "0x00435a10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b02b",
      "direction": "out
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnKeyDown.c",
  "file": "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnKeyDown.c",
    "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-input-wave6/0058ac10.json"
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
      "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
      "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x005737d0",
        "0x005737d0",
        "0x00576c50",
        "0x00576c50",
        "0x0057ce80",
        "0x0057ce80",
        "0x00584300",
        "0x00584300",
        "0x00587270",
        "0x00587270",
        "0x00587a20",
        "0x00587a20",
        "0x00588570",
        "0x00588570",
        "0x0058ac10",
        "0x0058ac10"
      ],
      "conflict_id": "editor_runtime_validation",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "A positive hash-pinned original-process trace is required; static naming or c
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnKeyDown.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-input-wave6/0058ac10.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_input_wave6/editor_input.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnKeyDown.c",
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
      "ref": "reconstruction/metadata/pkg-editor-input-wave6/0058ac10.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowle
[TRUNCATED]
```
