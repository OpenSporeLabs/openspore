# Reconstruction context 0x00d01e30

- Status: `partial`
- Content SHA-256: `87ab4a844d3e2ae22f3d6dfdbe8f364e9ec143e6dc01a3be6c270c68496d7f08`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d01e30",
  "phase": "reconstruction",
  "target": "0x00d01e30"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueRelationshipManager",
  "name": "DiplomacyTransition_00d01e30",
  "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
  "subsystem": "Simulator.Diplomacy.Transition",
  "va": "0x00d01e30"
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
  "content_sha256": "9e0dfb5de2c7a72cd2abadcdd320d704142f3f0ce75b45e551cfcb59ce2f2ac3",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00d01e30 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueRelationshipManager*",
  "receiver": "first record",
  "receiver_register": "ECX",
  "return_type": "void",
  "stack_arguments": [
    {
      "name": "event_id",
      "position": 1,
      "type": "OpaqueWord"
    },
    {
      "name": "event_pointer",
      "position": 2,
      "type": "OpaqueEventRecord*"
    },
    {
      "name": "zero",
      "position": 3,
      "type": "OpaqueWord"
    }
  ],
  "stack_cleanup_bytes": 12,
  "termination": "RET 0x8"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "RelationshipLookup_00d01410",
      "reconstructed": true,
      "va": "0x00d01410"
    },
    {
      "name": "RelationshipMapSelect_00d01ab0",
      "reconstructed": true,
      "va": "0x00d01ab0"
    },
    {
      "name": "pkg12_space_01021300",
      "reconstructed": true,
      "va": "0x01021300"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010134d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102cd90"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x01013577",
      "direction": "in",
      "other": "0x010134d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0102cdb6",
      "direction": "in",
      "other": "0x0102cd90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d01ef8",
      "direction": "out",
      "other": "0x00421cf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d01edb",
      "direction": "out",
      "other": "0x00883860",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d01eff",
      "direction": "out",
      "other": "0x00c31c50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d01f06",
      "direction": "out",
      "other": "0x00c31c50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d01e9e",
      "direction": "out",
      "other": "0x00c32830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d01ea6",
      "direction": "out",
      "
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "DiplomacyTransitionPorts",
    "OpaqueEventFactory",
    "OpaqueEventFactory*",
    "OpaqueEventRecord",
    "OpaqueEventRecord*",
    "OpaqueRelationshipEntry",
    "OpaqueRelationshipManager",
    "OpaqueRelationshipManager*",
    "OpaqueRelationshipMap",
    "OpaqueTransitionRecord",
    "OpaqueTransitionRecord*",
    "OpaqueWord",
    "void"
  ],
  "vtables": [
    "vtable:0x00000000"
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
      "gate-diplomacy-transition-00d01e30"
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
      "name": "RelationshipLookup_00d01410",
      "reconstructed": true,
      "va": "0x00d01410"
    },
    {
      "name": "RelationshipMapSelect_00d01ab0",
      "reconstructed": true,
      "va": "0x00d01ab0"
    },
    {
      "name": "pkg12_space_01021300",
      "reconstructed": true,
      "va": "0x01021300"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010134d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0102cd90"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x01013577",
      "direction": "in",
      "other": "0x010134d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0102cdb6",
      "direction": "in",
      "other": "0x0102cd90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d01ef8",
      "direction": "out",
      "other": "0x00421cf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d01edb",
      "direction": "out",
      "other": "0x00883860",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d01eff",
      "direction": "out",
      "other": "0x00c31c50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d01f06",
      "direction": "out",
      "other": "0x00c31c50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d01e9e",
      "direction": "out",
      "other": "0x00c32830",
      "reference_type": "direct
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
      "shared_types:DiplomacyTransitionPorts,OpaqueEventFactory,OpaqueEventFactory*,OpaqueEventRecord",
      "shared_vtable:vtable:0x00000000",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 34,
    "symbol": "DiplomacyTransition_00d06920",
    "va": "0x00d06920"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:DiplomacyTransitionPorts,OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipManager*",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 30,
    "symbol": "DiplomacyTransition_00d038e0",
    "va": "0x00d038e0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:DiplomacyTransitionPorts,OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipManager*",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 30,
    "symbol": "DiplomacyTransition_00d065a0",
    "va": "0x00d065a0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-PRIMITIVES",
    "score": 16,
    "symbol": "RelationshipMapSelect_00d01ab0",
    "va": "0x00d01ab0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_typ
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_diplomacy_transitions/diplomacy_transitions.cpp",
  "files": [
    "reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions.cpp",
    "reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions.hpp",
    "reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions_model_test.cpp",
    "src/reconstruction/pkg13_diplomacy_transitions/diplomacy_transitions.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave5/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-diplomacy-transitions/00d01e30.json"
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
        "0x00d2e480",
        "0x00d2e480",
        "0x00d01410",
        "0x00d01410",
        "0x00d01ab0",
        "0x00d01ab0",
        "0x00d01e30",
        "0x00d01e30",
        "0x00d01f50",
        "0x00d01f50",
        "0x00d01ff0",
        "0x00d01ff0",
        "0x00d038e0",
        "0x00d038e0",
        "0x00d065a0",
        "0x00d065a0"
      ],
      "conflict_id": "U-003-civilization-progression",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
      "resolution_status": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00be34a0",
        "0x00d2e480",
        "0x00d2e480",
        "0x00aeb7b0",
        "0x00aeb160",
        "0x00aeb160",
        "0x00aeb7b0",
        "0x00aeb7b0",
        "0x00aebe90",
        "0x00aebe90",
        "0x00be34a0",
        "0x00d01410",
        "0x00d01410",
        "0x00d01ab0",
        "0x00d01ab0",
        "0x00d01e30"
      ],
      "conflict_id": "U-004-city-buildings",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The declared state surface is retained, but the comple
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave5/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-diplomacy-transitions/00d01e30.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_diplomacy_transitions/diplomacy_transitions.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-source-wave5/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg13-diplomacy-transitions/00d01e30.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
 
[TRUNCATED]
```
