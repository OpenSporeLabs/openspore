# Reconstruction context 0x00d01ff0

- Status: `partial`
- Content SHA-256: `93346a1b7db6e43867c7556a3fdeeba930b2a79dcab5132032393a54a97cabfc`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d01ff0",
  "phase": "reconstruction",
  "target": "0x00d01ff0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueRelationshipManager",
  "name": "RelationshipManager_IsAllied2_00d01ff0",
  "package": "PKG-13-SIM-DIPLOMACY-PREDICATE",
  "subsystem": "Simulator.Diplomacy",
  "va": "0x00d01ff0"
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
  "content_sha256": "48d92bbcc18997f1b640c4291d133eaaafbbd710325f0ab653e5e18cc36889a2",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00d01ff0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this": "ECX OpaqueRelationshipManager* receiver",
  "return_register": "AL",
  "return_semantics": "Returns byte 0 for a null relationship entry and otherwise (flags >> 1) & 1. Unrelated EAX high bits are not a semantic return contract.",
  "return_width_bytes": 1,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "position": 1,
      "type": "OpaqueEmpire*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "position": 2,
      "type": "OpaqueEmpire*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8
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
      "va": "0x00c4bc00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01008e60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0100dd40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010134d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01047440"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c4bc8a",
      "direction": "in",
      "other": "0x00c4bc00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010090d1",
      "direction": "in",
      "other": "0x01008e60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0100de65",
      "direction": "in",
      "other": "0x0100dd40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01013518",
      "direction": "in",
      "other": "0x010134d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010474f1",
      "direction": "in",
      "other": "0x01047440",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d0202c",
      "direction": "out",
      "other": "0x00d0
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueEmpire",
    "OpaqueEmpire*",
    "OpaqueRelationshipEntry",
    "OpaqueRelationshipManager",
    "OpaqueRelationshipMap"
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
      "gate-diplomacy-relationship-records"
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
      "va": "0x00c4bc00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01008e60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0100dd40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010134d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01047440"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00c4bc8a",
      "direction": "in",
      "other": "0x00c4bc00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010090d1",
      "direction": "in",
      "other": "0x01008e60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0100de65",
      "direction": "in",
      "other": "0x0100dd40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01013518",
      "direction": "in",
      "other": "0x010134d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x010474f1",
      "direction": "in",
      "other": "0x01047440",
      "reference_type": "direct-call"
    },
 
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-PRIMITIVES",
    "score": 22,
    "symbol": "RelationshipMapSelect_00d01ab0",
    "va": "0x00d01ab0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipMap",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 16,
    "symbol": "DiplomacyTransition_00d01e30",
    "va": "0x00d01e30"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipMap",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 16,
    "symbol": "DiplomacyTransition_00d038e0",
    "va": "0x00d038e0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipMap",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 16,
    "symbol": "DiplomacyTransition_00d065a0",
    "va": "0x00d065a0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipMap",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 16,
    "symbol": "DiplomacyTransition_00d069
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_diplomacy_predicate/diplomacy_predicate.cpp",
  "files": [
    "reconstruction/staging/pkg13-diplomacy-predicate/diplomacy_predicate.cpp",
    "reconstruction/staging/pkg13-diplomacy-predicate/diplomacy_predicate.hpp",
    "reconstruction/staging/pkg13-diplomacy-predicate/diplomacy_predicate_test.cpp",
    "src/reconstruction/pkg13_diplomacy_predicate/diplomacy_predicate.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-diplomacy/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-diplomacy-predicate/00d01ff0.json"
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
    }
  ],
  "unresolved_questions": [
    "No original-process alliance records or helper return values have been observed.",
    "The concrete manager, empire, map, and relationship-entry owners remain unresolved.",
    "The current empire cache and refcount side effects of 0x01021300 remain owned by PKG-12.",
    "The exact lower-bound behavior inside 0x00d01ab0 and 0x00d01410 is not part of this target reconstruction.",
    "gate-diplomacy-relationship-records",
    "lower-bound helper behavior",
    "map-selection helper behavior",
    "relationship record
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-diplomacy/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-diplomacy-predicate/00d01ff0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-diplomacy-predicate/diplomacy_predicate.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-diplomacy-predicate/diplomacy_predicate.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-diplomacy-predicate/diplomacy_predicate_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_diplomacy_predicate/diplomacy_predicate.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-diplomacy/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg13-diplomacy-predicate/00d01ff0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-diplomacy-predicate/diplomacy_predicate.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-diplomacy-predicate/diplomacy_predicate.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "
[TRUNCATED]
```
