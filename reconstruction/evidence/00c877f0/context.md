# Reconstruction context 0x00c877f0

- Status: `partial`
- Content SHA-256: `78750acc155771de84fdab2ea4c6752b6d96b786d1644ff8c2b45cca510be015`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c877f0",
  "phase": "reconstruction",
  "target": "0x00c877f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "InventoryItem",
  "name": "cSpaceInventoryItem_ctor_00c877f0",
  "package": "PKG-12-SIM-SPACE",
  "subsystem": "Simulator.SpaceInventory",
  "va": "0x00c877f0"
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
  "content_sha256": "efa7dc2b8e32c1c81d9a9e8d4cd5d4153e7e4f1ca7ced40f7acc699dc1f7cac9",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c877f0 failed: Decompilation did not complete. Reason: ",
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
  "return_observation": "The live body returns through the item vtable notification path and has no value return.",
  "return_type": "void",
  "stack_arguments": [
    {
      "cleanup": "RET 0x4 in the live body",
      "entry_offset": "ESP+0x04",
      "position": 1,
      "type": "OpaquePropertyList*",
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
      "va": "0x00ac0cb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c878d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c879a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103a480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103fc10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0104e340"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ac0d52",
      "direction": "in",
      "other": "0x00ac0cb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c8795d",
      "direction": "in",
      "other": "0x00c878d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c87ac1",
      "direction": "in",
      "other": "0x00c879a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0103a515",
      "direction": "in",
      "other": "0x0103a480",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0103fcaa",
      "direction": "in",
      "other": "0x0103fc10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0104e3d5",
      "direction": "in",
      "other": "0x0104e340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c87863",
      "direction": "out",
      "other": "0x0041ea00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c8782a",
      "direction": 
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "/Spore/App/PropertyList",
    "/Spore/Simulator/cSpaceInventoryItem",
    "InventoryItem",
    "InventoryItemServices",
    "InventoryItemVtable",
    "LocalizedString",
    "OpaqueLocalizedString",
    "OpaqueProperty",
    "OpaquePropertyList",
    "OpaquePropertyList*",
    "ResourceKey",
    "intrusive_ptr<App::PropertyList>",
    "uint",
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
  "original_bytes": 7230,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-space-inventory-item\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"classification\": \"BOUNDED_SEMANTIC\",\n    \"confidence\": {\n      \"mechanics\": 0.99\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 8,\n    \"evidence\": [\n      {\n        \"kind\": \"targeted_decompilation_and_disassembly\",\n        \"observation\": \"PropertyList AddRef/Release, three property IDs, type check 10, +0x24 write, vtable+0x4c call, RET 0x4.\",\n        \"source\": \"ghidra://SporeApp.exe@0x00c877f0\"\n      },\n      {\n        \"kind\": \"sibling_constructor\",\n        \"observation\": \"Installs vtable 0x01473558 and initializes cSpaceInventoryItem fields.\",\n        \"source\": \"ghidra://SporeApp.exe@0x00c87660\"\n      },\n      {\n        \"kind\": \"factory_caller\",\n        \"observation\": \"Allocates 0x7c, base-constructs, and invokes the target with a property list.\",\n        \"source\": \"ghidra://SporeApp.exe@0x00c878d0\"\n      },\n      {\n        \"kind\": \"vtable_memory\",\n        \"observation\": \"The +0x4c slot points to FUN_00b1e4d0; the separate 0x00b14ed0 function is not this slot.\",\n        \"source\": \"ghidra://SporeApp.exe@0x01473558\"\n      }\n    ],\n    \"family\": \"space_inventory_property_application\",\n    \"interfaces\": {\n      \"boundaries\": {},\n      \"direct_callees\": [],\n      \"direct_callers\": [],\n      \"globals\": [],\n   
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
      "va": "0x00ac0cb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c878d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c879a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103a480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0103fc10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0104e340"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00ac0d52",
      "direction": "in",
      "other": "0x00ac0cb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c8795d",
      "direction": "in",
      "other": "0x00c878d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c87ac1",
      "direction": "in",
      "other": "0x00c879a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0103a515",
      "direction": "in",
      "other": "0x0103a480",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0103fcaa",
      "direction": "in",
      "other": "0x0103fc10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0104e3d5",
      "direction": "in",
      "other": "0x0104e340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c87863",
      "direction": "out",
      "other": "0x0041ea00",
      "reference_
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
    "package": "PKG-12-SIM-SPACE",
    "score": 14,
    "symbol": "pkg12_space_00de9fc0",
    "va": "0x00de9fc0"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 10,
    "symbol": "FUN_00aea230",
    "va": "0x00aea230"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 10,
    "symbol": "FUN_00aea5d0",
    "va": "0x00aea5d0"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 10,
    "symbol": "FUN_00aeb160",
    "va": "0x00aeb160"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 10,
    "symbol": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
    "va": "0x00aeb720"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 8,
    "symbol": "FUN_00aea250",
    "va": "0x00aea250"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 8,
    "symbol": "pkg12_space_01021300",
    "va": "0x01021300"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 8,
    "symbol": "FUN_0102d1b0",
    "va": "0x0102d1b0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg12_space/space_inventory_entry.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_inventory_entry.cpp",
    "reconstruction/staging/pkg12-space/space_inventory_entry.hpp",
    "reconstruction/staging/pkg12-space/space_inventory_entry_model_test.cpp",
    "src/reconstruction/pkg12_space/space_inventory_entry.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg12-space/00c877f0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 6678,
  "preview": "{\n  \"category\": \"GAMEPLAY_LOGIC\",\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 8,\n  \"evidence\": [\n    {\n      \"kind\": \"targeted_decompilation_and_disassembly\",\n      \"observation\": \"PropertyList AddRef/Release, three property IDs, type check 10, +0x24 write, vtable+0x4c call, RET 0x4.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00c877f0\"\n    },\n    {\n      \"kind\": \"sibling_constructor\",\n      \"observation\": \"Installs vtable 0x01473558 and initializes cSpaceInventoryItem fields.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00c87660\"\n    },\n    {\n      \"kind\": \"factory_caller\",\n      \"observation\": \"Allocates 0x7c, base-constructs, and invokes the target with a property list.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00c878d0\"\n    },\n    {\n      \"kind\": \"vtable_memory\",\n      \"observation\": \"The +0x4c slot points to FUN_00b1e4d0; the separate 0x00b14ed0 function is not this slot.\",\n      \"source\": \"ghidra://SporeApp.exe@0x01473558\"\n    }\n  ],\n  \"family\": \"space_inventory_property_application\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": [],\n    \"direct_callers\": [],\n    \"globals\": [],\n    \"structures\": [\n      {\n        \"fields\": [\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\"\n            ]\n          },\n          {\n            \"keys\": [\n              \"name\"
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
        "0x00c877f0",
        "0x00000014",
        "0x00000020",
        "0x00c877f0"
      ],
      "conflict_id": "TB-FL-010",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": {
        "merge_decision": "do_not_collapse",
        "preferred_claim": null,
        "preserved_alternatives": true,
        "scope_note": "cSpaceInventoryItem identity is strong, but the shared-prefix claim is not transferable to cSpaceToolData or cargo records.",
        "status": "preserved_alternatives",
        "taxonomy": "preserved_alternatives"
      },
      "resolution_status": "preserved_alternatives",
      "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
      "subject": "cSpaceInventoryItem shared-prefix field maps",
      "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
    },
    {
      "anchors": [
        "0x01037d30",
        "0x01037d30",
        "0x01037d30",
        "0x01037d30",
        "0x0103a480",
        "0x0103a480",
        "0x0103e8e0",
        "0x0103e8e0",
        "0x0103fc10",
        "0x0103fc10",
        "0x00c877f0",
        "0x00c877f0",
        "0x00596da0",
        "0x01037d30",
        "0x00d2e8a0",
        "0x0103e8e0"
      ],
      "conflict_id": "U-E004",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not establish the requested transition contract; the avai
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg12-space/00c877f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_inventory_entry.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_inventory_entry.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_inventory_entry_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg12_space/space_inventory_entry.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg12-space/00c877f0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_inventory_entry.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_inventory_entry.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/
[TRUNCATED]
```
