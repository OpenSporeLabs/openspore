# Reconstruction context 0x0098f4d0

- Status: `partial`
- Content SHA-256: `33d99d543a88b18350442629774596512504828fb83fbd36dc609aa7b4390a55`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0098f4d0",
  "phase": "reconstruction",
  "target": "0x0098f4d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueMessageManager",
  "name": "App::cMessageManager::GetMessageQueue",
  "package": "PKG-WAVE6-MISC-ENGINE",
  "subsystem": "App.MessageQueue",
  "va": "0x0098f4d0"
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
  "content_sha256": "98ba9d62bbb65e2aa21fb03cb8ae1534b777064f562606390c6823eb7e3109c3",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0098f4d0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall with one hidden ECX receiver and two ordinary stack words",
  "hidden_receiver": "ECX points to the cMessageManager object",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "role": "queue index",
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "role": "queue pointer",
      "type": "opaque pointer word",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x8",
  "return_note": "result of service vtable slot +0x90",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 8
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
    "MessageQueuePorts",
    "OpaqueMessageManager",
    "OpaqueMessageService",
    "opaque pointer word",
    "result of service vtable slot +0x90",
    "uint32_t"
  ],
  "vtables": [
    "vtable:0x01445cb8"
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
      "gate-message-queue-service-vtable-and-ownership"
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [
    "service vtable +0x7c",
    "service vtable +0x90"
  ],
  "manifest_callers": [
    "data_xref_01445cec"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0331",
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
      "same_package"
    ],
    "package": "PKG-WAVE6-MISC-ENGINE",
    "score": 8,
    "symbol": "game_time_manager_get_00b3d480",
    "va": "0x00b3d480"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-WAVE6-MISC-ENGINE",
    "score": 8,
    "symbol": "destructible_lifecycle_thunk_00b63980",
    "va": "0x00b63980"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01445cb8"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 4,
    "symbol": "re_00575ea0",
    "va": "0x00575ea0"
  },
  {
    "match_basis": [
      "shared_types:opaque pointer word"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 3,
    "symbol": "App_IStateManager_Get_0067dce0",
    "va": "0x0067dce0"
  },
  {
    "match_basis": [
      "shared_types:opaque pointer word"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 3,
    "symbol": "App_IPropManager_Get_0067ddf0",
    "va": "0x0067ddf0"
  },
  {
    "match_basis": [
      "shared_types:OpaqueMessageManager"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 3,
    "symbol": "MessageManagerCleanupStorageWalker_008841f0",
    "va": "0x008841f0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cMessageManager__GetMessageQueue.c",
  "file": "src/reconstruction/wave6_misc_engine/misc_engine.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cMessageManager__GetMessageQueue.c",
    "reconstruction/staging/wave6-misc-engine/misc_engine.cpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine.hpp",
    "reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp",
    "src/reconstruction/wave6_misc_engine/misc_engine.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-misc-engine/0098f4d0.json"
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
    "Can a selector above 3 occur at runtime and what side effects follow?",
    "Does the +0x90 result represent a queue pointer, count, or another word?",
    "What are the complete cMessageManager offsets and queue ownership rules?",
    "What are the implementations and return widths of service slots +0x7c and +0x90?",
    "What concrete object is stored at manager-0x208 and how is it published?",
    "gate-message-queue-service-vtable-and-ownership",
    "meaning of returned EAX",
    "queue-pointer ownership",
    "service owner at manager-0x208",
    "slot +0x7c and +0x90 meanings"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cMessageManager__GetMessageQueue.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-misc-engine/0098f4d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-misc-engine/misc_engine.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-misc-engine/misc_engine.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-misc-engine/misc_engine_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_misc_engine/misc_engine.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cMessageManager__GetMessageQueue.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave6-misc-engine/0098f4d0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-misc-engine/misc_engine.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/
[TRUNCATED]
```
