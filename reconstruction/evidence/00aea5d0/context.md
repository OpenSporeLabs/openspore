# Reconstruction context 0x00aea5d0

- Status: `partial`
- Content SHA-256: `643d15bacbad2b1da8259f23a8a62e9e3938516cf81d1591abcaca5ebe169f81`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00aea5d0",
  "phase": "reconstruction",
  "target": "0x00aea5d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "cCommVector",
  "name": "FUN_00aea5d0",
  "package": "PKG-12-SIM-SPACE",
  "subsystem": "Simulator.SpaceCommunication",
  "va": "0x00aea5d0"
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
  "content_sha256": "b866c20afa539321bae4eab7be9118118e94338450f2d73611873977ddfaacbc",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00aea5d0 failed: Decompilation did not complete. Reason: ",
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
    "type": "cCommVector*",
    "width_bytes": 4
  },
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "position",
      "position": 1,
      "type": "cCommEvent**"
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "value",
      "position": 2,
      "type": "cCommEvent**"
    }
  ],
  "stack_cleanup_bytes": 8,
  "termination": "RET 0x8"
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
      "va": "0x00ac0570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acd2d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad12a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae0a80"
    },
    {
      "name": "FUN_00aeb160",
      "reconstructed": true,
      "va": "0x00aeb160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b05b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b068c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b06a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b06bd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b09830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b0b150"
    },
    {
      "name": "noun_manager_logical_destroy_00b225d0",
      "reconstructed": true,
      "va": "0x00b225d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b22650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b227c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b23450"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ac05b3",
      "direction": "in",
      "other": "0x00ac0570",
  
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "cCommEvent",
    "cCommEvent**",
    "cCommVector",
    "cCommVector*",
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
      "va": "0x00ac0570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acd2d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad12a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae0a80"
    },
    {
      "name": "FUN_00aeb160",
      "reconstructed": true,
      "va": "0x00aeb160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb240"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b05b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b068c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b06a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b06bd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b09830"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b0b150"
    },
    {
      "name": "noun_manager_logical_destroy_00b225d0",
      "reconstructed": true,
      "va": "0x00b225d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b22650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b227c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b23450"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b26320"
    
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
      "shared_types:cCommEvent,cCommVector",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 25,
    "symbol": "FUN_00aeb160",
    "va": "0x00aeb160"
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
    "symbol": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
    "va": "0x00aeb720"
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
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 16,
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
    "va": "0x00de9fc0"
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
    "ma
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
    "reconstruction/metadata/pkg12-space/00aea5d0.json"
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
    "The SDK manager field name for the +0x24 vector remains unresolved.",
    "The exact ownership contract of the allocator's prefix word is not promoted beyond the observed conditional release.",
    "allocator failure behavior",
    "gate-space-comm-event-lifecycle",
    "manager vector field name",
    "move helper ownership"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg12-space/00aea5d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_comm_event_lifecycle.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_comm_event_lifecycle.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg12-space/space_comm_event_lifecycle_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg12_space/space_comm_event_lifecycle.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg12-space/00aea5d0.json",
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
