# Reconstruction context 0x006a25a0

- Status: `partial`
- Content SHA-256: `3cb4e4d96be00de713d8c6c6324618f16d5d5f32fb424c6730f90171710aa61b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a25a0",
  "phase": "reconstruction",
  "target": "0x006a25a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "DirectPropertyList",
  "name": "Prop_GetPropValueBool",
  "package": "PKG-20-PROPERTY-ADAPTER",
  "subsystem": "App.Property.DirectPropertyList",
  "va": "0x006a25a0"
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
  "content_sha256": "6454812b2e7824dd5387d3240989f2f687931319223f8fe0cc9bb4e57670bd15",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a25a0 failed: Decompilation did not complete. Reason: ",
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
  "receiver": "DirectPropertyList *",
  "receiver_register": "ECX",
  "return_type": "bool",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "property_id",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "editor_query_clear_flags_0093db80",
      "reconstructed": true,
      "va": "0x0093db80"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040a590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040f3f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040fe00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004157d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004bafc0"
    },
    {
      "name": "PaintPersistenceBoundary_submit_004c5200",
      "reconstructed": true,
      "va": "0x004c5200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004f3de0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0051c6a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00522b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005745c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00575270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057aaa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057ac00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005812b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005855b0"
    }
  
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "0x01",
    "DirectPropertyList",
    "Property",
    "PropertyAdapterServices",
    "PropertyMapEntry",
    "bool",
    "uint32_t"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 7963,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-property-direct-bool\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": \"GAMEPLAY_SUPPORT\",\n    \"classification\": \"STRONG_SEMANTIC\",\n    \"confidence\": {\n      \"identity\": 0.94,\n      \"mechanics\": 0.99\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 102,\n    \"evidence\": [\n      {\n        \"kind\": \"disassembly\",\n        \"source\": \"ghidra://SporeApp.exe@0x006a25a0\",\n        \"statement\": \"The body compares propertyID to +0x38, reads +0x3c + id*4 on the fast path, calls 0x00612db0 on the map path, and returns a normalized byte.\"\n      },\n      {\n        \"kind\": \"decompilation\",\n        \"source\": \"ghidra://SporeApp.exe@0x006a25a0\",\n        \"statement\": \"Pseudocode shows exact-key rejection, Property type/flag selection, DAT_015d115d fallback, and cleanup call.\"\n      },\n      {\n        \"kind\": \"sibling\",\n        \"source\": \"ghidra://SporeApp.exe@0x006a2660\",\n        \"statement\": \"GetDirectInt repeats the same fast-array and vector_map branches.\"\n      },\n      {\n        \"kind\": \"sibling\",\n        \"source\": \"ghidra://SporeApp.exe@0x006a2710\",\n        \"statement\": \"GetDirectFloat repeats the same fast-array and vector_map branches.\"\n      },\n      {\n        \"kind\": \"SDK\",\n        \"source\": \"/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/App/DirectPropertyList.h:31-46,109-145\",\n        \"statement\": \"The SDK defi
[TRUNCATED]
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "editor_query_clear_flags_0093db80",
      "reconstructed": true,
      "va": "0x0093db80"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040a590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040f3f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0040fe00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004157d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004bafc0"
    },
    {
      "name": "PaintPersistenceBoundary_submit_004c5200",
      "reconstructed": true,
      "va": "0x004c5200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004f3de0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0051c6a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00522b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005745c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00575270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057aaa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057ac00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005812b0"
    },
    {
      "name": null,
      "reconstructed": false,
   
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_class",
      "shared_types:DirectPropertyList",
      "same_calling_convention"
    ],
    "package": "PKG-PROPERTY-SAFE-WAVE9",
    "score": 10,
    "symbol": "direct_property_list_add_properties_from_006a1600",
    "va": "0x006a1600"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:DirectPropertyList",
      "same_calling_convention"
    ],
    "package": "PKG-PROPERTY-SAFE-WAVE9",
    "score": 10,
    "symbol": "direct_property_list_get_property_alt_006a1e50",
    "va": "0x006a1e50"
  },
  {
    "match_basis": [
      "shared_types:Property,PropertyMapEntry"
    ],
    "package": "wave6-resources",
    "score": 6,
    "symbol": "property_list_get_property_object_006a24d0",
    "va": "0x006a24d0"
  },
  {
    "match_basis": [
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-20-PERSISTENCE-BOUNDARY",
    "score": 5,
    "symbol": "PaintPersistenceBoundary_submit_004c5200",
    "va": "0x004c5200"
  },
  {
    "match_basis": [
      "shared_types:DirectPropertyList",
      "same_calling_convention"
    ],
    "package": "pkg-direct-property-clear-wave14",
    "score": 5,
    "symbol": "direct_property_list_clear_006a2b20",
    "va": "0x006a2b20"
  },
  {
    "match_basis": [
      "shared_types:PropertyMapEntry"
    ],
    "package": "wave6-resources",
    "score": 3,
    "symbol": "property_list_has_property_006a2470",
    "va": "0x006a2470"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 3,
    "symbol"
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg20_property_adapter/direct_property_list.cpp",
  "files": [
    "reconstruction/staging/pkg20-property-adapter/direct_property_list.cpp",
    "reconstruction/staging/pkg20-property-adapter/direct_property_list.hpp",
    "reconstruction/staging/pkg20-property-adapter/direct_property_list_model_test.cpp",
    "src/reconstruction/pkg20_property_adapter/direct_property_list.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-property-adapter/006a25a0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 7313,
  "preview": "{\n  \"category\": \"GAMEPLAY_SUPPORT\",\n  \"classification\": \"STRONG_SEMANTIC\",\n  \"confidence\": {\n    \"identity\": 0.94,\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 102,\n  \"evidence\": [\n    {\n      \"kind\": \"disassembly\",\n      \"source\": \"ghidra://SporeApp.exe@0x006a25a0\",\n      \"statement\": \"The body compares propertyID to +0x38, reads +0x3c + id*4 on the fast path, calls 0x00612db0 on the map path, and returns a normalized byte.\"\n    },\n    {\n      \"kind\": \"decompilation\",\n      \"source\": \"ghidra://SporeApp.exe@0x006a25a0\",\n      \"statement\": \"Pseudocode shows exact-key rejection, Property type/flag selection, DAT_015d115d fallback, and cleanup call.\"\n    },\n    {\n      \"kind\": \"sibling\",\n      \"source\": \"ghidra://SporeApp.exe@0x006a2660\",\n      \"statement\": \"GetDirectInt repeats the same fast-array and vector_map branches.\"\n    },\n    {\n      \"kind\": \"sibling\",\n      \"source\": \"ghidra://SporeApp.exe@0x006a2710\",\n      \"statement\": \"GetDirectFloat repeats the same fast-array and vector_map branches.\"\n    },\n    {\n      \"kind\": \"SDK\",\n      \"source\": \"/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/App/DirectPropertyList.h:31-46,109-145\",\n      \"statement\": \"The SDK defines the 0x54-byte DirectPropertyList and GetDirectBool fast-access contract.\"\n    },\n    {\n      \"kind\": \"repository\",\n      \"source\": \"docs/analysis/reconstruction-research-queue.md:202\",\n      \"statement\": \"
[TRUNCATED]
```

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "0x00542c30 conversion result",
    "PTR_FUN_0154eb48 callback owner",
    "concrete Property owner",
    "gate-property-direct-bool",
    "runtime pointer-flag ownership"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg20-property-adapter/006a25a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-property-adapter/direct_property_list.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-property-adapter/direct_property_list.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg20-property-adapter/direct_property_list_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg20_property_adapter/direct_property_list.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg20-property-adapter/006a25a0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-property-adapter/direct_property_list.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg20-property-adapter/direct_property_list.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reco
[TRUNCATED]
```
