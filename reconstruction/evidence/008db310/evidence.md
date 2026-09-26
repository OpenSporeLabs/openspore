# Evidence 0x008db310

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `ad44d0300541c6af575c53c7dbcb775f72d89f458543d8f7c1d40851f3c55fb4`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "hidden_this_type": "PFIndexModifiableWriteCarrier*",
  "return_register": "AL",
  "return_type": "bool",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "destination",
      "position": 1,
      "type": "void*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "destination_size",
      "position": 2,
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "termination": "RET 0x8 at 0x008db384 and 0x008db38d"
}
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## external_callees

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "abi": {
    "calling_convention": "__thiscall observed",
    "hidden_this_register": "ECX",
    "hidden_this_type": "PFIndexModifiableWriteCarrier*",
    "return_register": "AL",
    "return_type": "bool",
    "stack_arguments": [
      {
        "entry_offset": "ESP+0x04",
        "name": "destination",
        "position": 1,
        "type": "void*",
        "width_bytes": 4
      },
      {
        "entry_offset": "ESP+0x08",
        "name": "destination_size",
        "position": 2,
        "type": "uint32_t",
        "width_bytes": 4
      }
    ],
    "stack_cleanup_bytes": 8,
    "termination": "RET 0x8 at 0x008db384 and 0x008db38d"
  },
  "analogues": [
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
    },
    {
      "match_basis": [
        "shared_types:DATA"
      ],
      "package": "PKG-APP-LIFECYCLE-WAVE7",
      "score": 3,
      "symbol": "app_capp_system_hook_windows_007e6080",
      "va": "0x007e6080"
    },
    {
      "match_basis": [
        "shared_types:DATA"
      ],
      "package": "PKG-APP-LIFECYCLE-WAVE7",
      "score": 3,
      "symbol": "app_capp_system_set_effect_collection_ids_007e6100",
      "va": "0x007e6100"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [
    "No direct caller xrefs establish the runtime write-buffer allocation and persistence envelope.",
    "The imported four-parameter prototype is not reconciled beyond the two words consumed by the live body."
  ],
  "body_status": null,
  "class_type": null,
  "cluster": "resource-io",
  "confidence": null,
  "dependencies": {
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
      "id": "scc-0197",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "CONFIRMED",
  "globals": [],
  "integration_status": null,
  "name": "Resource::PFIndexModifiable::Write",
  "normalized_symbol": "Resource::PFIndexModifiable::Write",
  "observed_mechanics": [],
  "ownership": {
    "claimability": "queue_candidate",
    "handoff_packages": [],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": null,
    "queue_state": "queued"
  },
  "package": null,
  "reconstructed": false,
  "review_status": null,
  "runtime": {
    "blocking_reason": null,
    "gates": [],
    "validated": 0
  },
  "runtime_gated": false,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": null,
  "services": [],
  "source": {
    "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c",
    "file": null,
    "files": [
      ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c",
      "reconstruction/staging/wave6-resources/pf_index_write.cpp",
      "reconstruction/staging/wave6-resources/pf_index_write.hpp",
      "reconstruction/staging/wave6-resources/property_list_variants_model_test.cpp"
    ],
    "handoffs": [],
    "metadata": [
      "reconstruction/metadata/wave6-resources/008db310.json"
    ],
    "provenance": []
  },
  "status": "queued",
  "subsystem": "Resource",
  "triage": {
    "category": "ENGINE_INTERFACE",
    "cluster": "resource-io",
    "db_triage_status": "QUEUED",
    "decomp_path": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c",
    "dependencies": [
      "runtime-crt-stl"
    ],
    "evidence": "CONFIRMED",
    "kg_node_id": "fun:008db310",
    "name": "Resource::PFIndexModifiable::Write",
    "priority": "P0",
    "provenance": {
      "classifier": "triage-v4",
      "generated_at": "2026-09-23T10:12:09Z",
      "generator": "subagent-7-sequential-triage",
      "sdk_name": "Resource::PFIndexModifiable::Write",
      "snapshot": "2540f2ca",
      "snapshot_sha256": "2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8",
      "vtable_addrs": [
        "01436878"
      ]
    },
    "queue_state": "queued",
    "rank": 100
  },
  "types": [
    "DATA",
    "ItemsMap",
    "PFIndexModifiableWriteCarrier*",
    "bool",
    "uint32_t",
    "void*"
  ],
  "unresolved_questions": [
    "Concrete ItemsMap node and bucket ownership semantics",
    "The vtable/data-table owner that reaches this otherwise uncalled function",
    "Whether destination_size is a byte count or a target index extent in all callers"
  ],
  "va": "0x008db310",
  "vtables": [
    "vtable:0x01436878"
  ]
}
```

## ghidra_function

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c",
    "reconstruction/staging/wave6-resources/pf_index_write.cpp",
    "reconstruction/staging/wave6-resources/pf_index_write.hpp",
    "reconstruction/staging/wave6-resources/property_list_variants_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave6-resources/008db310.json"
  ]
}
```

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocking_reason": null,
  "gates": [],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "DATA",
  "ItemsMap",
  "PFIndexModifiableWriteCarrier*",
  "bool",
  "uint32_t",
  "void*"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01436878"
]
```

## Conflicts

```json
[]
```
