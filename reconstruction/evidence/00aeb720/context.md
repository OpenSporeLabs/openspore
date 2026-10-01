# Reconstruction context 0x00aeb720

- Status: `partial`
- Content SHA-256: `c4a5a11390469a7c79eb6e2cf35742eef4587f3e2cc5b2ea97b74396ba9734a3`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00aeb720",
  "phase": "reconstruction",
  "target": "0x00aeb720"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "cCommManager",
  "name": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
  "package": "PKG-12-SIM-SPACE",
  "subsystem": "Simulator.SpaceCommunication",
  "va": "0x00aeb720"
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
  "content_sha256": "cd045afc77cb45f4caa0ebbd5e6eb45f1a3f998873a44375be79a14b41f7d0f3",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00aeb720 failed: Decompilation did not complete. Reason: ",
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
  "receiver": {
    "register": "ECX",
    "type": "cCommManager*",
    "width_bytes": 4
  },
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "payload0",
      "position": 1,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "payload1",
      "position": 2,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0C",
      "name": "payload2",
      "position": 3,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x10",
      "name": "payload3",
      "position": 4,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x14",
      "name": "payload4",
      "position": 5,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x18",
      "name": "payload5",
      "position": 6,
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 24,
  "termination": "RET 0x18"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00aeb160",
      "reconstructed": true,
      "va": "0x00aeb160"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aed2c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c75520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd5160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102c9e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102caa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102cae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102cc30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102cd90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102ce30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102cf10"
    },
    {
      "name": "FUN_0102d1b0",
      "reconstructed": true,
      "va": "0x0102d1b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102df20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01072d40"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00aed3a2",
      "direction": "in",
      "other": "0x00aed2c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c7555d",
      "direction": "in",
      "other": "0x00c75520",
      "reference_type": "direct-call"
    },
    {
      "callsi
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x013f09b4"
  ],
  "types": [
    "OpaquePayloadWord",
    "cCommEvent",
    "cCommManager",
    "cCommManager*",
    "opaque",
    "uint32_t",
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
      "gate-space-comm-event-lifecycle"
    ],
    "validated": 0
  },
  "semantic": {
    "category": "GAMEPLAY_LOGIC",
    "classification": "BOUNDED_SEMANTIC",
    "confidence": {
      "mechanics": 0.99
    },
    "contradictions": [],
    "downstream_unlock_count": 15,
    "evidence": [
      {
        "kind": "targeted_decompilation_and_disassembly",
        "observation": "ECX manager, six stack arguments, RET 0x18, trailing zero, direct creator then dispatch calls.",
        "source": "ghidra://SporeApp.exe@0x00aeb720"
      },
      {
        "kind": "callee_decompilation",
        "observation": "0xa0 allocation, event field writes, intrusive add, manager storage append.",
        "source": "ghidra://SporeApp.exe@0x00aeb160"
      },
      {
        "kind": "callee_decompilation",
        "observation": "Large, warning-heavy consumer; exact current-event, cancellation, and UI ordering remain unresolved.",
        "source": "ghidra://SporeApp.exe@0x00aebe90"
      },
      {
        "kind": "caller_comparison",
        "observation": "Bypasses the wrapper to the creator for an existing event and otherwise uses the wrapper.",
        "source": "ghidra://SporeApp.exe@0x00aed2c0"
      },
      {
        "kind": "caller_comparison",
        "observation": "Mission-oriented dispatcher calls the wrapper with six concrete communication fields.",
        "source": "ghidra://SporeApp.exe@0x0102df20"
      }
    ],
    "family": "simulator_comm_event",
    "interfaces": {
      "boundaries": {},
      "direct_call
[TRUNCATED]
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00aeb160",
      "reconstructed": true,
      "va": "0x00aeb160"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aed2c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c75520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd5160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102c9e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102caa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102cae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102cc30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102cd90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102ce30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102cf10"
    },
    {
      "name": "FUN_0102d1b0",
      "reconstructed": true,
      "va": "0x0102d1b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102df20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01072d40"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00aed3a2",
      "direction": "in",
      "other": "0x00aed2c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c7555d",
      "direction": "in",
      "o
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
      "shared_types:OpaquePayloadWord,cCommEvent,cCommManager,cCommManager*",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 33,
    "symbol": "FUN_00aeb160",
    "va": "0x00aeb160"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:cCommManager,cCommManager*",
      "same_calling_convention"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 27,
    "symbol": "FUN_00aea230",
    "va": "0x00aea230"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:cCommEvent",
      "same_calling_convention"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 19,
    "symbol": "FUN_00aea5d0",
    "va": "0x00aea5d0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:cCommEvent"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 17,
    "symbol": "FUN_00aea250",
    "va": "0x00aea250"
  },
  {
    "match_basis": [
      "same_package",
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 11,
    "symbol": "FUN_0102d1b0",
    "va": "0x0102d1b0"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 10,
    "symbol": "cSpaceInventoryItem_ctor_00c877f0",
    "va": "0x00c877f0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-12-SI
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg12_space/space_comm_event.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_comm_event.cpp",
    "reconstruction/staging/pkg12-space/space_comm_event.hpp",
    "reconstruction/staging/pkg12-space/space_comm_event_model_test.cpp",
    "src/reconstruction/pkg12_space/space_comm_event.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg12-space/00aeb720.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 6246,
  "preview": "{\n  \"category\": \"GAMEPLAY_LOGIC\",\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 15,\n  \"evidence\": [\n    {\n      \"kind\": \"targeted_decompilation_and_disassembly\",\n      \"observation\": \"ECX manager, six stack arguments, RET 0x18, trailing zero, direct creator then dispatch calls.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00aeb720\"\n    },\n    {\n      \"kind\": \"callee_decompilation\",\n      \"observation\": \"0xa0 allocation, event field writes, intrusive add, manager storage append.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00aeb160\"\n    },\n    {\n      \"kind\": \"callee_decompilation\",\n      \"observation\": \"Large, warning-heavy consumer; exact current-event, cancellation, and UI ordering remain unresolved.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00aebe90\"\n    },\n    {\n      \"kind\": \"caller_comparison\",\n      \"observation\": \"Bypasses the wrapper to the creator for an existing event and otherwise uses the wrapper.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00aed2c0\"\n    },\n    {\n      \"kind\": \"caller_comparison\",\n      \"observation\": \"Mission-oriented dispatcher calls the wrapper with six concrete communication fields.\",\n      \"source\": \"ghidra://SporeApp.exe@0x0102df20\"\n    }\n  ],\n  \"family\": \"simulator_comm_event\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": [],\n    \"direct_callers\": [],\n    \"globals\
[TRUNCATED]
```

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "Does every real caller provide a non-null manager and creator result?",
    "Is the exact entry CreateSpaceCommEvent, a default-duration wrapper, or an internal helper absorbed by the SDK address?",
    "What do the six opaque payload words mean at each caller, given pointer-like and event-code words are passed without conversion?",
    "What exact current-event assignment, list/cancellation mutation, UI handling, and release timing does FUN_00aebe90 impose?",
    "What is the exact private source-level name of this convenience wrapper?",
    "What version skew maps the SDK CreateSpaceCommEvent and HandleSpaceCommAction names to nearby addresses?",
    "Which cCommManager current/list offsets are authoritative across the SDK, Ghidra type, and direct creator accesses?",
    "Which original ABI names correspond to the six forwarded stack arguments?",
    "Why does the creator's observed manager storage offset differ from the named Ghidra cCommManager vector field?",
    "creator and dispatcher failure behavior",
    "gate-space-comm-event-lifecycle",
    "manager layout conflict",
    "payload word meanings",
    "private source name"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg12-space/00aeb720.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_comm_event.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_comm_event.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_comm_event_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg12_space/space_comm_event.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg12-space/00aeb720.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_comm_event.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_comm_event.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_comm
[TRUNCATED]
```
