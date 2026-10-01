# Reconstruction context 0x00ff3f00

- Status: `partial`
- Content SHA-256: `52f983de7b8877a3b05230fe047949e9420793179611bfad559547d5343d93e3`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00ff3f00",
  "phase": "reconstruction",
  "target": "0x00ff3f00"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueTimelineEventData",
  "name": "FUN_00ff3f00",
  "package": "PKG-01-SHARED-STATE-ROOTS",
  "subsystem": "GameGlobal",
  "va": "0x00ff3f00"
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
  "content_sha256": "6851c9d1c49edd054cd2c39d945302a32f2aea94e6924b19fa7bab85281bbe2b",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00ff3f00 failed: Decompilation did not complete. Reason: ",
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
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 5572,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"CORE_RESOLVED\",\n  \"conflicts\": [],\n  \"content_sha256\": \"e22a391cb448cd75d38ca3ea4d08377a0368014ec9b6e3740e0d867e689b1aad\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": \"__thiscall\",\n    \"candidate_conventions\": [\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0003\"\n    
[TRUNCATED]
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
      "va": "0x00b0a6f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2a790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b7a880"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3c520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e07e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e87db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ebf5b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ed7a10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00eed720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00eef4b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00eef570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ef1ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00efdee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00efebb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f001b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f002d0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b0a943",
      "direction": "in",
      "other": "0x00b0a6f0",
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
    "OpaqueTimelineEventData",
    "std::uint32_t"
  ],
  "vtables": [
    "vtable:0x014439c8",
    "vtable:0x0147cbbc"
  ]
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 8383,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"indirect_dispatch_owner_observation\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"NEEDS_RUNTIME\",\n    \"confidence\": {\n      \"overall\": 0.84\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 27,\n    \"evidence\": [\n      {\n        \"finding\": \"Exactly one receiver+0x8c load and return; no callees.\",\n        \"kind\": \"target_decompilation\",\n        \"source\": \"Ghidra 0x00ff3f00\"\n      },\n      {\n        \"finding\": \"The receiver has a local UI timeline-event vtable and is allocated/torn down as a 0xb0 variant.\",\n        \"kind\": \"constructor_destructor\",\n        \"source\": \"Ghidra 0x00dd0ca0 and 0x00dd0cf0\"\n      },\n      {\n        \"finding\": \"The field is command-line-shaped, cleared/released, replaced, and accompanied by an adjacent +0x90 pointer.\",\n        \"kind\": \"field_lifecycle\",\n        \"source\": \"Ghidra 0x00ff3e80, 0x00ff4540, 0x00ff3f10\"\n      },\n      {\n        \"finding\": \"Consumers allocate/use the timeline-event data family and branch on the accessor result in local state paths.\",\n        \"kind\": \"representative_consumers\",\n        \"source\": \"Ghidra 0x00e2f6e0, 0x00e47930, 0x0106c930, 0x0106aa10, 0x0100a960\"\n      },\n      {\n        \"finding\": \"The imported cSPAssetDataOTDB is 0x78 bytes; receiver+0x8c and receiver+0xb8 accesses are outside it.\",\n        \"kind\": \"structure_separator\"
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
      "va": "0x00b0a6f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2a790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b7a880"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c3c520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e07e70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e87db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ebf5b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ed7a10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00eed720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00eef4b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00eef570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ef1ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00efdee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00efebb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f001b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f002d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fda2e0"
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
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d3a0",
    "va": "0x00b3d3a0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d400",
    "va": "0x00b3d400"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "Simulator_cSpaceTrading_Get",
    "va": "0x00b3d4d0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "Simulator_GetUIMissionLogManager",
    "va": "0x00b3d4f0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_01021080",
    "va": "0x01021080"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_01021230",
    "va": "0x01021230"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg01_roots/pkg01_roots.cpp",
  "files": [
    "src/reconstruction/pkg01_roots/pkg01_roots.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg01-roots/00ff3f00.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 7853,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": 0.84\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 27,\n  \"evidence\": [\n    {\n      \"finding\": \"Exactly one receiver+0x8c load and return; no callees.\",\n      \"kind\": \"target_decompilation\",\n      \"source\": \"Ghidra 0x00ff3f00\"\n    },\n    {\n      \"finding\": \"The receiver has a local UI timeline-event vtable and is allocated/torn down as a 0xb0 variant.\",\n      \"kind\": \"constructor_destructor\",\n      \"source\": \"Ghidra 0x00dd0ca0 and 0x00dd0cf0\"\n    },\n    {\n      \"finding\": \"The field is command-line-shaped, cleared/released, replaced, and accompanied by an adjacent +0x90 pointer.\",\n      \"kind\": \"field_lifecycle\",\n      \"source\": \"Ghidra 0x00ff3e80, 0x00ff4540, 0x00ff3f10\"\n    },\n    {\n      \"finding\": \"Consumers allocate/use the timeline-event data family and branch on the accessor result in local state paths.\",\n      \"kind\": \"representative_consumers\",\n      \"source\": \"Ghidra 0x00e2f6e0, 0x00e47930, 0x0106c930, 0x0106aa10, 0x0100a960\"\n    },\n    {\n      \"finding\": \"The imported cSPAssetDataOTDB is 0x78 bytes; receiver+0x8c and receiver+0xb8 accesses are outside it.\",\n      \"kind\": \"structure_separator\",\n      \"source\": \"Ghidra cSPAssetDataOTDB layout\"\n    },\n    {\n      \"finding\": \"No cSPAssetDataOTDB constructor, cCommEvent constructor, Resource IRecord, or network call is attached to the accessor.\",\n      \"kind\":
[TRUNCATED]
```

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "Are the 0x9c and 0xb0 object variants semantically distinct?",
    "Are the 0xb0 and 0x9c variants semantically distinct or only different feature sets?",
    "Does the +0x8c pointer represent a request, an animation/event parameter, or a presentation handle?",
    "What exact local command-line subtype is stored at receiver+0x8c?",
    "What exact values, if any, at receiver+0x8c are pointer values rather than sentinels, and what local subtype do they represent?",
    "What is the exact relationship between receiver+0x8c and receiver+0x90?",
    "What is the exact semantic role of receiver+0x8c: request, animation/event parameter, or presentation state?",
    "What is the relationship between receiver+0x8c and receiver+0x90?",
    "What lifetime and null-window guarantees apply to the returned value when it is pointer-like?",
    "When the field contains a pointer, which code first writes it and who owns the pointee before the first accessor read?",
    "Who first writes the field and who owns the pointer before the first accessor read?",
    "indirect dispatch path",
    "indirect_dispatch_owner_observation",
    "owner type",
    "runtime field value"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg01-roots/00ff3f00.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/pkg01_roots.cpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "derived"
    },
    {
      "mode": "derived",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "derived"
    },
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
      "ref": "reconstruction/metadata/pkg01-roots/00ff3f00.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg01_roots/pkg01_roots.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    "src/reconstruction/pkg01_roots/pkg01_roots.cpp"
  ],
  "r
[TRUNCATED]
```
