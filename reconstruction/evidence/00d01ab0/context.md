# Reconstruction context 0x00d01ab0

- Status: `partial`
- Content SHA-256: `e68eb7e1096cd8b6d9c32645bdebbba7664f809a1bf599c1ff2ee0aaad5da4dc`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d01ab0",
  "phase": "reconstruction",
  "target": "0x00d01ab0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueRelationshipManager",
  "name": "RelationshipMapSelect_00d01ab0",
  "package": "PKG-13-SIM-DIPLOMACY-PRIMITIVES",
  "subsystem": "Simulator.Diplomacy",
  "va": "0x00d01ab0"
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
  "content_sha256": "d5cc11b7f3f6526b09cc74d4060614aad30a9b5592e5cea6d38b14adbae5f2fe",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00d01ab0 failed: Decompilation did not complete. Reason: ",
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
  "return_register": "EAX",
  "return_semantics": "Returns receiver+0x24 fallback or selected record+0x04 map pointer; normal failure is a non-null fallback address.",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "position": 1,
      "type": "std::uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "position": 2,
      "type": "std::uint32_t",
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
      "name": "context_word_read_00ce6950",
      "reconstructed": true,
      "va": "0x00ce6950"
    },
    {
      "name": "FUN_010212a0",
      "reconstructed": true,
      "va": "0x010212a0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d01b50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d01b80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d01bb0"
    },
    {
      "name": "DiplomacyTransition_00d01e30",
      "reconstructed": true,
      "va": "0x00d01e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d01f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d01f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d01fb0"
    },
    {
      "name": "RelationshipManager_IsAllied2_00d01ff0",
      "reconstructed": true,
      "va": "0x00d01ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d02050"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d03860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d038a0"
    },
    {
      "name": "DiplomacyTransition_00d038e0",
      "reconstructed": true,
      "va": "0x00d038e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d03d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d05830"
    },
    {
      "name": null,
      "recons
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueRelationshipManager",
    "OpaqueRelationshipMap",
    "OpaqueRelationshipRecord",
    "OpaqueSpaceContext",
    "std::uint32_t"
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
      "gate-diplomacy-map-selector"
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
      "name": "context_word_read_00ce6950",
      "reconstructed": true,
      "va": "0x00ce6950"
    },
    {
      "name": "FUN_010212a0",
      "reconstructed": true,
      "va": "0x010212a0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d01b50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d01b80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d01bb0"
    },
    {
      "name": "DiplomacyTransition_00d01e30",
      "reconstructed": true,
      "va": "0x00d01e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d01f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d01f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d01fb0"
    },
    {
      "name": "RelationshipManager_IsAllied2_00d01ff0",
      "reconstructed": true,
      "va": "0x00d01ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d02050"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d03860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d038a0"
    },
    {
      "name": "DiplomacyTransition_00d038e0",
      "reconstructed": true,
      "va": "0x00d038e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d03d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d05830"
    },
    {
   
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
    "package": "PKG-13-SIM-DIPLOMACY-PREDICATE",
    "score": 22,
    "symbol": "RelationshipManager_IsAllied2_00d01ff0",
    "va": "0x00d01ff0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:OpaqueRelationshipMap"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-PRIMITIVES",
    "score": 17,
    "symbol": "RelationshipLookup_00d01410",
    "va": "0x00d01410"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 16,
    "symbol": "DiplomacyTransition_00d01e30",
    "va": "0x00d01e30"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 16,
    "symbol": "DiplomacyTransition_00d038e0",
    "va": "0x00d038e0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 16,
    "symbol": "DiplomacyTransition_00d065a0",
    "va": "0x00d065a0"
  },
 
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_diplomacy_primitives/diplomacy_primitives.cpp",
  "files": [
    "reconstruction/staging/pkg13-diplomacy-primitives/diplomacy_primitives.cpp",
    "reconstruction/staging/pkg13-diplomacy-primitives/diplomacy_primitives.hpp",
    "reconstruction/staging/pkg13-diplomacy-primitives/diplomacy_primitives_test.cpp",
    "src/reconstruction/pkg13_diplomacy_primitives/diplomacy_primitives.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-diplomacy-primitives/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-diplomacy-primitives/00d01ab0.json"
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
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-diplomacy-primitives/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-diplomacy-primitives/00d01ab0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-diplomacy-primitives/diplomacy_primitives.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-diplomacy-primitives/diplomacy_primitives.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-diplomacy-primitives/diplomacy_primitives_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_diplomacy_primitives/diplomacy_primitives.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-diplomacy-primitives/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg13-diplomacy-primitives/00d01ab0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-diplomacy-primitives/diplomacy_primitives.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-diplomacy-primitives/diplomacy_primitives.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted"
[TRUNCATED]
```
