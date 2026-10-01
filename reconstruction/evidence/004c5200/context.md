# Reconstruction context 0x004c5200

- Status: `partial`
- Content SHA-256: `badcc3fcb7cdfd9271319e06de0f2fef5ee47633e6fe3565412a81fe1482ff2e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x004c5200",
  "phase": "reconstruction",
  "target": "0x004c5200"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueEditor",
  "name": "PaintPersistenceBoundary_submit_004c5200",
  "package": "PKG-20-PERSISTENCE-BOUNDARY",
  "subsystem": "PersistenceBoundary.PaintSubmission",
  "va": "0x004c5200"
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
  "content_sha256": "dad0e521f424efcc7eda01009731196f231ca1a1c11f28855ab34a93b67b59f5",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x004c5200 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_type": "opaque editor pointer",
  "return_type": "uint8_t",
  "stack_arguments": [
    {
      "entry_offset": "ESP+4",
      "name": "request",
      "observed_fields": [
        "+0x10",
        "+0x58",
        "+0x8c",
        "+0x98",
        "+0xa4"
      ],
      "type": "opaque request pointer",
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
      "name": "app_direct_property_list_get_direct_bool_006a25a0",
      "reconstructed": true,
      "va": "0x006a25a0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00585d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00591690"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00585f4e",
      "direction": "in",
      "other": "0x00585d40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00586373",
      "direction": "in",
      "other": "0x00585d40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058715c",
      "direction": "in",
      "other": "0x00586b00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587557",
      "direction": "in",
      "other": "0x00587270",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00591a45",
      "direction": "in",
      "other": "0x00591690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00591bea",
      "direction": "in",
      "other": "0x00591690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059316e",
      "direction": "in",
      "other": "0x00591fa0",
      "reference_type": "d
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
    "OpaquePaintJob",
    "PaintJobServices",
    "PaintRequest",
    "opaque editor pointer",
    "opaque request pointer",
    "uint8_t"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 10590,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-paint-bake-submission\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"BOUNDED_SEMANTIC\",\n    \"confidence\": {\n      \"events\": \"ANALYTICAL_ONLY\",\n      \"identity\": \"SUPPORTED\",\n      \"mechanics\": \"CONFIRMED\",\n      \"overall\": \"high_for_static_paint_mechanics_medium_for_argument_and_job_types\",\n      \"ownership\": \"SUPPORTED_WITH_CAVEAT\",\n      \"persistence\": \"CONFIRMED_AS_DERIVED_NON_PERSISTENT\",\n      \"runtime\": \"UNAVAILABLE\"\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 22,\n    \"evidence\": [\n      {\n        \"claim\": \"feature gate, old-job release, 0x84-byte allocation, three-slot population, property fallback, type flags, IBakeManager submission, and boolean-like return\",\n        \"class\": \"direct_body\",\n        \"source\": \"ghidra://SporeApp.exe@0x004c5200\"\n      },\n      {\n        \"claim\": \"136-byte receiver with editor/model/world references, retained job at +0x5c, material/texture fields, and gate at +0x84\",\n        \"class\": \"structure_layout\",\n        \"source\": \"ghidra_get_struct_layout(cEditorSkin)\"\n      },\n      {\n        \"claim\": \"five direct editor callers: cEditor::HandleMessage, cEditor::SetActiveMode, cEditor::SetEditorModel, FUN_00585d40, and FUN_00591690\",\n        \"class\": \"direct_callers\",\n        \"source\": \"ghidra_get_function_callers(0x004c5200)\"\n      },\n   
[TRUNCATED]
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "app_direct_property_list_get_direct_bool_006a25a0",
      "reconstructed": true,
      "va": "0x006a25a0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00585d40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00586b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00591690"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00585f4e",
      "direction": "in",
      "other": "0x00585d40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00586373",
      "direction": "in",
      "other": "0x00585d40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058715c",
      "direction": "in",
      "other": "0x00586b00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00587557",
      "direction": "in",
      "other": "0x00587270",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00591a45",
      "direction": "in",
      "other": "0x00591690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00591bea",
      "direction": "in",
      "other": "0x00591690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005931
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
    "package": "PKG-20-PERSISTENCE-BOUNDARY",
    "score": 10,
    "symbol": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
    "va": "0x00b28ec0"
  },
  {
    "match_basis": [
      "shared_types:OpaqueEditor",
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 5,
    "symbol": "FUN_005dda30",
    "va": "0x005dda30"
  },
  {
    "match_basis": [
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-20-PROPERTY-ADAPTER",
    "score": 5,
    "symbol": "app_direct_property_list_get_direct_bool_006a25a0",
    "va": "0x006a25a0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_scalar_00428060",
    "va": "0x00428060"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_paint_commit_0043ac40",
    "va": "0x0043ac40"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "model_parts_apply_properties_00447150",
    "va": "0x00447150"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WA
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg20_persistence_boundary/paint_job_004c5200.cpp",
  "files": [
    "reconstruction/staging/pkg20-persistence-boundary/paint_job_004c5200.cpp",
    "reconstruction/staging/pkg20-persistence-boundary/paint_job_004c5200.hpp",
    "src/reconstruction/pkg20_persistence_boundary/paint_job_004c5200.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json",
    "reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-persistence-boundary/004c5200.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 9825,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"events\": \"ANALYTICAL_ONLY\",\n    \"identity\": \"SUPPORTED\",\n    \"mechanics\": \"CONFIRMED\",\n    \"overall\": \"high_for_static_paint_mechanics_medium_for_argument_and_job_types\",\n    \"ownership\": \"SUPPORTED_WITH_CAVEAT\",\n    \"persistence\": \"CONFIRMED_AS_DERIVED_NON_PERSISTENT\",\n    \"runtime\": \"UNAVAILABLE\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 22,\n  \"evidence\": [\n    {\n      \"claim\": \"feature gate, old-job release, 0x84-byte allocation, three-slot population, property fallback, type flags, IBakeManager submission, and boolean-like return\",\n      \"class\": \"direct_body\",\n      \"source\": \"ghidra://SporeApp.exe@0x004c5200\"\n    },\n    {\n      \"claim\": \"136-byte receiver with editor/model/world references, retained job at +0x5c, material/texture fields, and gate at +0x84\",\n      \"class\": \"structure_layout\",\n      \"source\": \"ghidra_get_struct_layout(cEditorSkin)\"\n    },\n    {\n      \"claim\": \"five direct editor callers: cEditor::HandleMessage, cEditor::SetActiveMode, cEditor::SetEditorModel, FUN_00585d40, and FUN_00591690\",\n      \"class\": \"direct_callers\",\n      \"source\": \"ghidra_get_function_callers(0x004c5200)\"\n    },\n    {\n      \"claim\": \"checks the retained job's +0x6b/+0x6c state before allowing the old job to be released\",\n      \"class\": \"sibling_helper\",\n      \"source\": \"ghidra://SporeApp.exe@0x004c58b0\"\n    },\n    
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
        "0x004c5200",
        "0x004c5910",
        "0x004c5920",
        "0x004c5200",
        "0x004c5910",
        "0x004c5920",
        "0x004c5920",
        "0x004c5910",
        "0x004c5910",
        "0x004c5920",
        "0x004c5200"
      ],
      "conflict_id": "ceditor_skin_ispainting_alias",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x004c5200",
        "0x00587270",
        "0x0059d840",
        "0x0059d8b0",
        "0x00587270",
        "0x0059d8b0",
        "0x0059d840",
        "0x00591690",
        "0x004c5200",
        "0x005737d0",
        "0x005737d0",
        "0x00576c50",
        "0x00576c50",
        "0x0057ce80",
        "0x0057ce80",
        "0x00584300"
      ],
      "conflict_id": "skin_paint_lifecycle",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without sema
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg20-persistence-boundary/004c5200.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-persistence-boundary/paint_job_004c5200.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-persistence-boundary/paint_job_004c5200.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg20_persistence_boundary/paint_job_004c5200.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg20-persistence-boundary/004c5200.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-persistence-boundary/paint_job_004c5200.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "rec
[TRUNCATED]
```
