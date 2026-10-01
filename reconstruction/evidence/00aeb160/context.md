# Reconstruction context 0x00aeb160

- Status: `partial`
- Content SHA-256: `dd9cfa6477254252ecd5997cab00f59524066e972600457cc8a1a8de00226370`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00aeb160",
  "phase": "reconstruction",
  "target": "0x00aeb160"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "cCommManager",
  "name": "FUN_00aeb160",
  "package": "PKG-12-SIM-SPACE",
  "subsystem": "Simulator.SpaceCommunication",
  "va": "0x00aeb160"
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
  "content_sha256": "4c669a4a5458e4d0d1b10af269112b78c3bfb2d5813718513a490ef691e9e241",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00aeb160 failed: Decompilation did not complete. Reason: ",
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
  "return_register": "EAX",
  "return_type": "cCommEvent*",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "payload0",
      "position": 1,
      "type": "OpaqueWord"
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "payload1",
      "position": 2,
      "type": "OpaqueWord"
    },
    {
      "entry_offset": "ESP+0x0c",
      "name": "payload2",
      "position": 3,
      "type": "OpaqueWord"
    },
    {
      "entry_offset": "ESP+0x10",
      "name": "payload3",
      "position": 4,
      "type": "OpaqueWord"
    },
    {
      "entry_offset": "ESP+0x14",
      "name": "payload4",
      "position": 5,
      "type": "OpaqueWord"
    },
    {
      "entry_offset": "ESP+0x18",
      "name": "payload5",
      "position": 6,
      "type": "OpaqueWord"
    },
    {
      "entry_offset": "ESP+0x1c",
      "name": "payload6",
      "position": 7,
      "type": "OpaqueWord"
    }
  ],
  "stack_cleanup_bytes": 28,
  "termination": "RET 0x1c"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00aea250",
      "reconstructed": true,
      "va": "0x00aea250"
    },
    {
      "name": "FUN_00aea5d0",
      "reconstructed": true,
      "va": "0x00aea5d0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
      "reconstructed": true,
      "va": "0x00aeb720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb7b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebc10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aed2c0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00aeb405",
      "direction": "in",
      "other": "0x00aeb3e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00aeb745",
      "direction": "in",
      "other": "0x00aeb720",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00aeb83d",
      "direction": "in",
      "other": "0x00aeb7b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00aebc80",
      "direction": "in",
      "other": "0x00aebc10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00aed30f",
      "direction": "in",
      "other": "0x00aed2c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00aeb186",
      "direction": "out",
      "other": "0x00aea250",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00aeb21e
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaquePayloadWord",
    "OpaqueWord",
    "cCommEvent",
    "cCommEvent*",
    "cCommManager",
    "cCommManager*",
    "cCommVector"
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
  "semantic": {}
}
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00aea250",
      "reconstructed": true,
      "va": "0x00aea250"
    },
    {
      "name": "FUN_00aea5d0",
      "reconstructed": true,
      "va": "0x00aea5d0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
      "reconstructed": true,
      "va": "0x00aeb720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb7b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebc10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aed2c0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00aeb405",
      "direction": "in",
      "other": "0x00aeb3e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00aeb745",
      "direction": "in",
      "other": "0x00aeb720",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00aeb83d",
      "direction": "in",
      "other": "0x00aeb7b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00aebc80",
      "direction": "in",
      "other": "0x00aebc10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00aed30f",
      "direction": "in",
      "other": "0x00aed2c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00aeb186",
      "direction": "out",
      "other": "0x00aea2
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
    "symbol": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
    "va": "0x00aeb720"
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
      "shared_types:cCommEvent,cCommVector",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 25,
    "symbol": "FUN_00aea5d0",
    "va": "0x00aea5d0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:cCommEvent,cCommEvent*",
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 23,
    "symbol": "FUN_00aea250",
    "va": "0x00aea250"
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
    "package": "PKG-12-SIM-SPACE",
    "score": 8,
    "symbol": "pkg12_space_00de9fc0",
   
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg12_space/space_comm_event_lifecycle.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_comm_event_lifecycle.cpp",
    "reconstruction/staging/pkg12-space/space_comm_event_lifecycle.hpp",
    "reconstruction/staging/pkg12-space/space_comm_event_lifecycle_model_test.cpp",
    "src/reconstruction/pkg12_space/space_comm_event_lifecycle.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg12-space/00aeb160.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "anchors": [
        "0x00aeb160",
        "0x00aebe90",
        "0x00aed2c0",
        "0x00c75520",
        "0x00dd5160",
        "0x0102c9e0",
        "0x0102caa0",
        "0x0102cae0",
        "0x0102cc30",
        "0x0102cd90",
        "0x0102ce30",
        "0x0102cf10",
        "0x0102d1b0",
        "0x0102df20",
        "0x01072d40",
        "0x00aeb730"
      ],
      "conflict_id": "LC-006",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "RESOLVED_SUPPORTED",
      "resolution_status": "RESOLVED_SUPPORTED",
      "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
      "subject": "0x00AEB720 communication wrapper",
      "unresolved_reason": "The exact private wrapper name and the full parameter types are not recoverable from static naming alone; the create-and-dispatch contract is resolved."
    },
    {
      "anchors": [
        "0x00aeb160",
        "0x00aeb7b0",
        "0x00aebe90",
        "0x00aeb160",
        "0x00aebe90",
        "0x00aeb7b0"
      ],
      "conflict_id": "Q-COMM-CODEC",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "cCommEvent allocation, list append, and current-event publication are concrete. Versioned codec/defaulting/vector round-trip semantics remain unresolved.",
      "resolution_status": "cCommEvent allocation, list append, and current-event publication are concrete. Versioned codec/defaulting/vector round-trip semantics remain unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",

[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg12-space/00aeb160.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_comm_event_lifecycle.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_comm_event_lifecycle.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_comm_event_lifecycle_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg12_space/space_comm_event_lifecycle.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg12-space/00aeb160.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_comm_event_lifecycle.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg12-space/space_comm_event_lifecycle.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pk
[TRUNCATED]
```
