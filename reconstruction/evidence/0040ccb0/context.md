# Reconstruction context 0x0040ccb0

- Status: `partial`
- Content SHA-256: `efb5c9c5c2258a869fe3a50a7ba4587c054c09326bf089a2be765929a8ea315c`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0040ccb0",
  "phase": "reconstruction",
  "target": "0x0040ccb0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "Transform",
  "name": "transform_pre_transform_by_0040ccb0",
  "package": "WAVE6-PRESENTATION",
  "subsystem": "Graphics.Transform",
  "va": "0x0040ccb0"
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
  "content_sha256": "9975a67935c1b350d88a3b1f6ec9eca8ecaed1ffc9a0921d34fe584f98d9a47f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0040ccb0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "hidden_this_type": "Transform*",
  "return_register": "EAX",
  "return_type": "Transform*",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "other",
      "observed_use": "Reads the other transform offset, scale, flags, and rotation.",
      "position": 1,
      "type": "Transform*",
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
  "callees": [],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040aeb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004363d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043d240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043d420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043d690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00441440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005f6260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006271a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00748ad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0074a290"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0074ac80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007507e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00752620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b02b90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b134a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd2af0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0040b1dc",
      "direction": "in",
      "other": "0x0040aeb0",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:No direct gameplay-global data references were identified in the target body."
  ],
  "types": [
    "Matrix3",
    "Transform",
    "Transform*",
    "TransformBoundaryPorts",
    "Vector3"
  ],
  "vtables": []
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
      "gate-transform-helper-semantics-and-runtime-inputs"
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
      "va": "0x0040aeb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004363d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043d240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043d420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043d690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00441440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005f6260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006271a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00748ad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0074a290"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0074ac80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007507e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00752620"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b02b90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b134a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd2af0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d265c0"
    },
    {
      "name": null,
      "reconst
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
      "same_subsystem"
    ],
    "package": "WAVE6-PRESENTATION",
    "score": 14,
    "symbol": "graphics_global_state_set_transform_005291f0",
    "va": "0x005291f0"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "WAVE6-PRESENTATION",
    "score": 10,
    "symbol": "renderware_mesh_set_indices_count_011f96e0",
    "va": "0x011f96e0"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "WAVE6-PRESENTATION",
    "score": 10,
    "symbol": "renderware_mesh_set_index_buffer_011f9710",
    "va": "0x011f9710"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-WAVE6-CONTAINERS-MEMORY",
    "score": 2,
    "symbol": "wave6_reference_00432a50",
    "va": "0x00432a50"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-20-RESOURCE-ADAPTER",
    "score": 2,
    "symbol": "TexturePtr_Set",
    "va": "0x00576650"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 2,
    "symbol": "editor_query_reset_005dd750",
    "va": "0x005dd750"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 2,
    "symbol": "editor_query_dispatch_005dfd00",
    "va": "0x005dfd00"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "wave6-resources",
    "score": 2,
    "symbol": "property_list_has_proper
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/wave6_presentation/presentation_boundary.cpp",
  "files": [
    "src/reconstruction/wave6_presentation/presentation_boundary.cpp",
    "src/reconstruction/wave6_presentation/presentation_boundary.hpp",
    "src/reconstruction/wave6_presentation/presentation_boundary_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-presentation/0040ccb0.json"
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
    "Are helper return pointers always the local destinations under runtime input?",
    "What exact matrix/vector operation is implemented by 0x0041daf0?",
    "What exact rotation convention is implemented by 0x0041de20?",
    "exact helper 0x0041daf0 operation",
    "exact helper 0x0041de20 rotation convention",
    "gate-transform-helper-semantics-and-runtime-inputs",
    "runtime transform validity and null behavior"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-presentation/0040ccb0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_presentation/presentation_boundary.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_presentation/presentation_boundary.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_presentation/presentation_boundary_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave6-presentation/0040ccb0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/wave6_presentation/presentation_boundary.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/wave6_presentation/presentation_boundary.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/wave6_pres
[TRUNCATED]
```
