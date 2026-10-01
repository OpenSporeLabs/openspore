# Reconstruction context 0x00b3d4f0

- Status: `partial`
- Content SHA-256: `5e545aaeb04cac6a49930ddba6a0266029c5345fe373f4a8cfe830bf6bfad5fc`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d4f0",
  "phase": "reconstruction",
  "target": "0x00b3d4f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueUIMissionLogManager",
  "name": "Simulator_GetUIMissionLogManager",
  "package": "PKG-01-SHARED-STATE-ROOTS",
  "subsystem": "Simulator",
  "va": "0x00b3d4f0"
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
  "content_sha256": "9f5c6c50bd57276acb2e11f8fa7ba97071e743c63d23ace3d9167e73d697244e",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b3d4f0 failed: Decompilation did not complete. Reason: ",
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
  "original_bytes": 5056,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"no_discriminator: no stack-argument read and no positive receiver evidence\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"PARTIAL\",\n  \"conflicts\": [],\n  \"content_sha256\": \"414a09c2a4bc5f0dad599651159453d0a5a99699264afb8a2fb855a43ce74282\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": null,\n    \"candidate_conventions\": [\n      \"__cdecl\",\n      \"__stdcall\",\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"UNKNOWN\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0002\"\n      ],\n      \"claim\": \"the caller 
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
      "va": "0x00b335d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c73cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c73f80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c73ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c74210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c74280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c74470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c74550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c74690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd1960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd6800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd6980"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cde660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce8ab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf50e0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b3372b",
      "direction": "in",
      "other": "0x00b335d0",
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
    "32-bit pointer slot",
    "OpaqueUIMissionLogManager"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 7719,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"observe_global_slot_0167eb64\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"classification\": \"NEEDS_RUNTIME\",\n    \"confidence\": {\n      \"identity\": 0.72,\n      \"mechanics\": 0.99\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 22,\n    \"evidence\": [\n      {\n        \"kind\": \"disassembly\",\n        \"source\": \"ghidra://SporeApp.exe@0x00b3d4f0\",\n        \"statement\": \"The complete function is MOV EAX,[0x0167eb64]; RET with no branches, calls, writes, or stack arguments.\"\n      },\n      {\n        \"kind\": \"decompilation\",\n        \"source\": \"ghidra://SporeApp.exe@0x00b3d4f0\",\n        \"statement\": \"Targeted pseudocode returns DAT_0167eb64 directly.\"\n      },\n      {\n        \"kind\": \"direct_consumer\",\n        \"source\": \"ghidra://SporeApp.exe@0x00e82de0\",\n        \"statement\": \"The consumer loads the accessor result, dereferences its vtable, and calls slot +0x38 with two arguments.\"\n      },\n      {\n        \"kind\": \"downstream_helper\",\n        \"source\": \"ghidra://SporeApp.exe@0x00e30d20\",\n        \"statement\": \"The helper uses manager fields at +0x3c, +0x40, and +0x44 as vector-like storage and adds UI/AssetDiscoveryCard entries.\"\n      },\n      {\n        \"kind\": \"sibling_accessors\",\n        \"source\": \"ghidra://SporeApp.exe@0x00b3d400,0x00b3d480,0x00b3d4d0,0x00b3d510\",\n        \"statement\": \"Adjace
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
      "va": "0x00b335d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c73cf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c73f80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c73ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c74210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c74280"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c74470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c74550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c74690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd1960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd6800"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd6980"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cde660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ce8ab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf50e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cf7ad0"
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
      "same_subsystem",
      "shared_types:32-bit pointer slot"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 17,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:32-bit pointer slot"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 17,
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
    "symbol": "FUN_00ff3f00",
    "va": "0x00ff3f00"
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
    "reconstruction/metadata/pkg01-roots/00b3d4f0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 7142,
  "preview": "{\n  \"category\": \"GAMEPLAY_LOGIC\",\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"identity\": 0.72,\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 22,\n  \"evidence\": [\n    {\n      \"kind\": \"disassembly\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b3d4f0\",\n      \"statement\": \"The complete function is MOV EAX,[0x0167eb64]; RET with no branches, calls, writes, or stack arguments.\"\n    },\n    {\n      \"kind\": \"decompilation\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b3d4f0\",\n      \"statement\": \"Targeted pseudocode returns DAT_0167eb64 directly.\"\n    },\n    {\n      \"kind\": \"direct_consumer\",\n      \"source\": \"ghidra://SporeApp.exe@0x00e82de0\",\n      \"statement\": \"The consumer loads the accessor result, dereferences its vtable, and calls slot +0x38 with two arguments.\"\n    },\n    {\n      \"kind\": \"downstream_helper\",\n      \"source\": \"ghidra://SporeApp.exe@0x00e30d20\",\n      \"statement\": \"The helper uses manager fields at +0x3c, +0x40, and +0x44 as vector-like storage and adds UI/AssetDiscoveryCard entries.\"\n    },\n    {\n      \"kind\": \"sibling_accessors\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b3d400,0x00b3d480,0x00b3d4d0,0x00b3d510\",\n      \"statement\": \"Adjacent accessors read neighboring global slots, establishing a direct global service block.\"\n    },\n    {\n      \"kind\": \"repository\",\n      \"source\": \"knowledgegraph/research/global-campaign-2026/track-f-empire-economy.js
[TRUNCATED]
```

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "Is the returned value ever a cMissionManager, or only manager-compatible UI state?",
    "What are the exact receiver fields and argument contract of vtable+0x38?",
    "What code publishes, replaces, or clears DAT_0167eb64?",
    "What concrete manager type and vtable identity does the returned value carry?",
    "What lifetime and null-window guarantees exist for the returned value?",
    "concrete manager type",
    "initialization",
    "observe_global_slot_0167eb64",
    "runtime pointer value"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg01-roots/00b3d4f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/pkg01_roots.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg01-roots/00b3d4f0.json",
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
