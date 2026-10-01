# Reconstruction context 0x011f96e0

- Status: `partial`
- Content SHA-256: `203c1a33e10ac36d450426af254b9aa9bbbb1acbb593def5f8ddbecc3ce95ec3`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x011f96e0",
  "phase": "reconstruction",
  "target": "0x011f96e0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "Mesh",
  "name": "renderware_mesh_set_indices_count_011f96e0",
  "package": "WAVE6-PRESENTATION",
  "subsystem": "Graphics.RenderWare",
  "va": "0x011f96e0"
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
  "content_sha256": "44ba9b04fc77973ae9deab2a559ab2f05cd7241fd26b09c0a5b6349973e5a84c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x011f96e0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_type": "Mesh*",
  "return_register": null,
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "index_buffer",
      "observed_use": "Stores the pointer at mesh+0x08 and conditionally reads primitiveType at index_buffer+0x14.",
      "position": 1,
      "type": "IndexBuffer*",
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
      "va": "0x006eae40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006eed00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006ef9e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0072b630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00769310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00faef10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00faef90"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x006eb0fc",
      "direction": "in",
      "other": "0x006eae40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006ef8a7",
      "direction": "in",
      "other": "0x006eed00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006efa5d",
      "direction": "in",
      "other": "0x006ef9e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0072bd7e",
      "direction": "in",
      "other": "0x0072b630",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00769886",
      "direction": "in",
      "other": "0x00769310",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00faef1b",
      "direction": "in",
      "other": "0x00faef10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00faf065",
      "direction": "in",
      "other": "0x00faef90",
      "referenc
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:No direct global data references were identified in the target body."
  ],
  "types": [
    "IndexBuffer",
    "IndexBuffer*",
    "Mesh",
    "Mesh*",
    "MeshBoundaryPorts",
    "void"
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
      "gate-index-buffer-ownership-and-count-helper"
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
      "va": "0x006eae40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006eed00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006ef9e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0072b630"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00769310"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00faef10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00faef90"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006eb0fc",
      "direction": "in",
      "other": "0x006eae40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006ef8a7",
      "direction": "in",
      "other": "0x006eed00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006efa5d",
      "direction": "in",
      "other": "0x006ef9e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0072bd7e",
      "direction": "in",
      "other": "0x0072b630",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00769886",
      "direction": "in",
      "other": "0x00769310",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00faef1b",
      "direction": "in",
      "other": "0x00faef10",
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
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:IndexBuffer,Mesh,Mesh*,MeshBoundaryPorts",
      "same_calling_convention"
    ],
    "package": "WAVE6-PRESENTATION",
    "score": 30,
    "symbol": "renderware_mesh_set_index_buffer_011f9710",
    "va": "0x011f9710"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "WAVE6-PRESENTATION",
    "score": 10,
    "symbol": "transform_pre_transform_by_0040ccb0",
    "va": "0x0040ccb0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "WAVE6-PRESENTATION",
    "score": 8,
    "symbol": "graphics_global_state_set_transform_005291f0",
    "va": "0x005291f0"
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
    "package":
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
    "reconstruction/metadata/wave6-presentation/011f96e0.json"
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
    "Does the SDK-normalized method name describe a different formal source-level argument than the raw x86 body?",
    "What is the concrete runtime owner of the published IndexBuffer pointer?",
    "What runtime primitive-type values are accepted by 0x011f95c0?",
    "gate-index-buffer-ownership-and-count-helper",
    "imported name versus raw argument meaning",
    "index-buffer owner and lifetime",
    "valid primitive types for 0x011f95c0"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-presentation/011f96e0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_presentation/presentation_boundary.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_presentation/presentation_boundary.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_presentation/presentation_boundary_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave6-presentation/011f96e0.json",
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
