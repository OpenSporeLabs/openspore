# Reconstruction context 0x0058b650

- Status: `partial`
- Content SHA-256: `6f07b49769a0818bd834177513d8fff82d7f8d1171a927d63e221c6b892e2a50`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0058b650",
  "phase": "reconstruction",
  "target": "0x0058b650"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Editors::cEditor::OnMouseUp",
  "package": "PKG-EDITOR-INPUT-WAVE6",
  "subsystem": "Editor.Input",
  "va": "0x0058b650"
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
  "content_sha256": "1787913b272cb8016413f441fe608495c09d9983a4a3decbdd163871965fbe14",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0058b650 failed: Decompilation did not complete. Reason: ",
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
  "return_semantics": "bool in AL; selection mouse-up result or false",
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
      "va": "0x004a88d0"
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
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x0058b83d",
      "direction": "out",
      "other": "0x00438a40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b740",
      "direction": "out",
      "other": "0x0044e980",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b859",
      "direction": "out",
      "other": "0x0044efb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b91c",
      "direction": "out",
      "other": "0x0047e6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b940",
      "direction": "out",
      "other": "0x0047e6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b8a8",
      "direction": "out",
      "other": "0x0048fde0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b7b8",
      "direction": "out",
      "other": "0x004a1020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b716",
      "direction": "out",
      "other": "0x004a5e10",
      "reference_type": "direct-call"
    },
 
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
      "runtime validation not run",
      "selection vtable, release ownership, and runtime button state remain gated"
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
      "va": "0x004a88d0"
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
      "callsite": "0x0058b83d",
      "direction": "out",
      "other": "0x00438a40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b740",
      "direction": "out",
      "other": "0x0044e980",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b859",
      "direction": "out",
      "other": "0x0044efb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b91c",
      "direction": "out",
      "other": "0x0047e6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b940",
      "direction": "out",
      "other": "0x0047e6c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b8a8",
      "direction": "out",
      "other": "0x0048fde0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b7b8",
      "direction": "out",
      "other": "0x004a1020",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058b716",
      "direction
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseUp.c",
  "file": "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseUp.c",
    "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-input-wave6/0058b650.json"
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
        "0x00587270",
        "0x0058b650",
        "0x013f57f8",
        "0x0058b650",
        "0x0057f3e0",
        "0x013f57f8",
        "0x005737d0",
        "0x005737d0",
        "0x00576c50",
        "0x00576c50",
        "0x0057ce80",
        "0x0057ce80",
        "0x00584300",
        "0x00584300",
        "0x00587270",
        "0x00587270"
      ],
      "conflict_id": "ceditor_vtable_tail",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x005737d0",
        "0x00588570",
        "0x0058b650",
        "0x00588570",
        "0x0057f3e0",
        "0x005737d0",
        "0x005737d0",
        "0x005737d0",
        "0x00586b00",
        "0x00586b00",
        "0x00587270",
        "0x00587270",
        "0x00587a20",
        "0x00587a20",
        "0x00588570",
        "0x00588570"
      ],
      "conflict_id": "manipulator_types",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The address/layout alternatives are preserved;
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseUp.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-input-wave6/0058b650.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_editor_input_wave6/editor_input.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseUp.c",
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
      "ref": "reconstruction/metadata/pkg-editor-input-wave6/0058b650.json",
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
