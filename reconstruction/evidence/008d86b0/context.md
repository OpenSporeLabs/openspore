# Reconstruction context 0x008d86b0

- Status: `partial`
- Content SHA-256: `ebe3ba5f177ca5a27c15831c1df27cc38763c66d5d4a1b29b8dcd1e818acd649`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x008d86b0",
  "phase": "reconstruction",
  "target": "0x008d86b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Resource::DatabasePackedFile::DestroyIndex",
  "package": "pkg-resource-index-ref-008d86b0",
  "subsystem": "Resource",
  "va": "0x008d86b0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "b3ef7a285ef40265a0eb0ab632971c500d6f314061f9ff5cb5520f12d12b445a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x008d86b0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_type": "ObservedIndexRefCarrier*",
  "return_register": "EAX",
  "return_type": "ObservedIndexObject*",
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "termination": "RET (0 bytes) at 0x008d86b6; INT3 padding 0xCC at 0x008d86b7"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "DATA",
    "ObservedIndexObject*",
    "ObservedIndexRefCarrier*",
    "high for 'a 32-bit pointer is returned in EAX', low for the pointee class identity"
  ],
  "vtables": [
    "vtable:0x014367b0"
  ]
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0271",
    "size": 1
  },
  "vtable_reference_count": 0
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA"
    ],
    "package": "pkg-orchestrate-dogfood-008db310",
    "score": 9,
    "symbol": "pf_index_write_bounds_008db310",
    "va": "0x008db310"
  },
  {
    "match_basis": [
      "shared_types:DATA",
      "same_calling_convention"
    ],
    "package": "wave6-resources",
    "score": 5,
    "symbol": "property_list_has_property_006a2470",
    "va": "0x006a2470"
  },
  {
    "match_basis": [
      "shared_types:DATA",
      "same_calling_convention"
    ],
    "package": "wave6-resources",
    "score": 5,
    "symbol": "property_list_get_property_object_006a24d0",
    "va": "0x006a24d0"
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
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005bf9d0",
    "va": "0x005bf9d0"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005c0100",
    "va": "0x005c0100"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005c0380",
    "va": "0x005c0380"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "WAVE6-ENGINE-RUNTIME",
    "score": 3,
    "symbol": "app_system_service_gate_dispatch_007e5f30",
    "va": "0x007e5f30"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__DatabasePackedFile__DestroyIndex.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__DatabasePackedFile__DestroyIndex.c",
    "reconstruction/staging/pkg-resource-index-ref-008d86b0/dbp_index_ref_008d86b0.cpp",
    "reconstruction/staging/pkg-resource-index-ref-008d86b0/dbp_index_ref_008d86b0.hpp",
    "reconstruction/staging/pkg-resource-index-ref-008d86b0/dbp_index_ref_008d86b0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-resource-index-ref-008d86b0/008d86b0.json"
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
    "No caller-side use of the return value is observable, because the only reference to this address is the vtable slot itself. What consumers do with the non-owning handle is unproven.",
    "The EA class name of the object stored at +0x260 is unknown. Only its vtable shape is known: slot +0x04 AddRef, slot +0x08 Release, and slot +0x28 called from FUN_008d8c50. No /DatabasePackedFile or /EAIOZoneObject Ghidra structure exists to resolve it.",
    "The SDK label 'DestroyIndex' and the imported prototype 'void ... (DatabasePackedFile* this, EAIOZoneObject* pObject)' both disagree with the machine: the body is a non-destructive single load, and the bare RET proves there is no stack parameter, so the EAIOZoneObject* parameter is not real for this address. Whether the SDK symbol table mis-mapped this address, or names an unrelated accessor, cannot be settled from the binary.",
    "The meaning of the +0x14 dword gate is unknown. It is read as a plain zero/non-zero test by 0x008d86c0 only; nothing observed shows who writes it or what state it represents.",
    "The remaining slots of PTR_FUN_014367b0 are only partly resolved to function entries, so the full class this vtable belongs to is not established. Slot +0x20 resolves to Resource::DatabaseDirectoryFiles::GetRefCount, so the vtable is shared with or adjacent to another class and its owning class is not identified."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Resource__DatabasePackedFile__DestroyIndex.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-resource-index-ref-008d86b0/008d86b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-resource-index-ref-008d86b0/dbp_index_ref_008d86b0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-resource-index-ref-008d86b0/dbp_index_ref_008d86b0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-resource-index-ref-008d86b0/dbp_index_ref_008d86b0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__DatabasePackedFile__DestroyIndex.c",
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
      "ref": "reconstruction/metadata/pkg-resource-index-ref-008d86b0/008d86b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-resource-index-ref-008d86b0/dbp_index_ref_008d86b0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-resource-index-ref-008d86b0/dbp_index_ref_008d86b0.hpp",
      "source_class": "committed_artifact"
    }
[TRUNCATED]
```
