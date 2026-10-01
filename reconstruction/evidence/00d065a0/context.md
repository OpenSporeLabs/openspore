# Reconstruction context 0x00d065a0

- Status: `partial`
- Content SHA-256: `523757a7ceb5804ce447ef5630a01145215129c2c67a1d3d46078d32df5a7cdf`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d065a0",
  "phase": "reconstruction",
  "target": "0x00d065a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueRelationshipManager",
  "name": "DiplomacyTransition_00d065a0",
  "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
  "subsystem": "Simulator.Diplomacy.Transition",
  "va": "0x00d065a0"
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
  "content_sha256": "1fe4a44d7e57cb1b94c9deb5fb5a7a945d3da9397c804f0980b85bba75b8d433",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00d065a0 failed: Decompilation did not complete. Reason: ",
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
  "receiver": "result of 0x0067cb30",
  "receiver_register": "ECX",
  "return_type": "void",
  "stack_arguments": [
    "selector 0xC09EDAAC",
    "object"
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
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0060d860"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c30c80"
    },
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
      "va": "0x00fe9580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010134d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01023be0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00fe9b2d",
      "direction": "in",
      "other": "0x00fe9580",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fea211",
      "direction": "in",
      "other": "0x00fe9580",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01013622",
      "direction": "in",
      "other": "0x010134d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01023f73",
      "direction": "in",
      "other": "0x01023be0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d066d5",
      "direction": "out",
      "other": "0x0060d860",
      "reference_type": "direct-c
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
    "OpaqueRelationshipEntry",
    "OpaqueRelationshipManager",
    "OpaqueRelationshipManager*",
    "OpaqueRelationshipMap",
    "OpaqueTransitionRecord",
    "OpaqueTransitionRecord*",
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
      "gate-diplomacy-transition-00d065a0"
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
      "name": null,
      "reconstructed": false,
      "va": "0x0060d860"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c30c80"
    },
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
      "va": "0x00fe9580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010134d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01023be0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00fe9b2d",
      "direction": "in",
      "other": "0x00fe9580",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fea211",
      "direction": "in",
      "other": "0x00fe9580",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01013622",
      "direction": "in",
      "other": "0x010134d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01023f73",
      "direction": "in",
      "other": "0x01023be0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d066d5",
   
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
      "shared_types:DiplomacyTransitionPorts,OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipManager*",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 30,
    "symbol": "DiplomacyTransition_00d01e30",
    "va": "0x00d01e30"
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
    "symbol": "DiplomacyTransition_00d06920",
    "va": "0x00d06920"
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
      "shared_types:OpaqueRelationship
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
    "reconstruction/metadata/pkg13-diplomacy-transitions/00d065a0.json"
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
        "0x00d01e30",
        "0x00d01e30",
        "0x00d038e0",
        "0x00d038e0",
        "0x00d05830",
        "0x00d05830",
        "0x00d06270",
        "0x00d06270",
        "0x00d065a0",
        "0x00d065a0",
        "0x00d06920",
        "0x00d06920",
        "0x00596da0"
      ],
      "conflict_id": "U-E001",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
     
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-source-wave5/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-diplomacy-transitions/00d065a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_diplomacy_transitions/diplomacy_transitions.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg13-diplomacy-transitions/00d065a0.json",
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
