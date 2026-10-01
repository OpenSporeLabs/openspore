# Reconstruction context 0x00d00d60

- Status: `partial`
- Content SHA-256: `239296b968f5eeb0f9e721977f068c14634119bd462a8778223059c59a731f57`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00d00d60",
  "phase": "reconstruction",
  "target": "0x00d00d60"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueRelationshipPolicy",
  "name": "RelationshipScoreObjects_00d00d60",
  "package": "PKG-13-E2-DIPLOMACY-ALT",
  "subsystem": "Simulator.Diplomacy",
  "va": "0x00d00d60"
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
  "content_sha256": "5d4a30b2dc7dc72d273e30bf8609fb7b847f919e8db6b0b42aab3ea7b577c02f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00d00d60 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_type": "OpaqueRelationshipPolicy*",
  "receiver": "entry policy",
  "receiver_register": "ECX",
  "return_type": "float",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "first",
      "position": 1,
      "type": "OpaqueIdentityObject*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "second",
      "position": 2,
      "type": "OpaqueIdentityObject*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0c",
      "name": "mode",
      "position": 3,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 12,
  "termination": "RET 0x0c on both paths"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00d00a10",
      "reconstructed": false,
      "va": "0x00d00a10"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dca100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ea8c30"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00dca3ef",
      "direction": "in",
      "other": "0x00dca100",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ea8db8",
      "direction": "in",
      "other": "0x00ea8c30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d00d90",
      "direction": "out",
      "other": "0x00d00a10",
      "reference_type": "direct-call"
    }
  ],
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
    "OpaqueIdentityObject",
    "OpaqueIdentityObject*",
    "OpaqueRelationshipPolicy",
    "OpaqueRelationshipPolicy*",
    "float",
    "std::uint32_t"
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
      "gate-diplomacy-relationship-objects-00d00d60",
      "runtime validation not run"
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
      "name": "FUN_00d00a10",
      "reconstructed": false,
      "va": "0x00d00a10"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dca100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ea8c30"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00dca3ef",
      "direction": "in",
      "other": "0x00dca100",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ea8db8",
      "direction": "in",
      "other": "0x00ea8c30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d00d90",
      "direction": "out",
      "other": "0x00d00a10",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 2,
  "fan_out": 1,
  "manifest_callees": [
    "0x00d00a10"
  ],
  "manifest_callers": [
    "0x00dca100",
    "0x00ea8c30"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0487",
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
      "same_package",
      "same_subsystem",
      "shared_types:OpaqueRelationshipPolicy"
    ],
    "package": "PKG-13-E2-DIPLOMACY-ALT",
    "score": 17,
    "symbol": "RelationshipScoreBand_00d00d00",
    "va": "0x00d00d00"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-PRIMITIVES",
    "score": 8,
    "symbol": "RelationshipMapSelect_00d01ab0",
    "va": "0x00d01ab0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-PREDICATE",
    "score": 8,
    "symbol": "RelationshipManager_IsAllied2_00d01ff0",
    "va": "0x00d01ff0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-PRIMITIVES",
    "score": 6,
    "symbol": "RelationshipLookup_00d01410",
    "va": "0x00d01410"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x00000000",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 6,
    "symbol": "DiplomacyTransition_00d01e30",
    "va": "0x00d01e30"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x00000000",
      "same_calling_convention"
    ],
    "package": "PKG-13-SIM-DIPLOMACY-TRANSITIONS",
    "score": 6,
    "symbol": "DiplomacyTransition_00d06920",
    "va": "0x00d06920"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorCreatureController_SetTargetPosition_0059b
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_e2_diplomacy_alt/diplomacy_alt.cpp",
  "files": [
    "reconstruction/staging/pkg13-e2-diplomacy-alt/diplomacy_alt.cpp",
    "reconstruction/staging/pkg13-e2-diplomacy-alt/diplomacy_alt.hpp",
    "reconstruction/staging/pkg13-e2-diplomacy-alt/diplomacy_alt_model_test.cpp",
    "src/reconstruction/pkg13_e2_diplomacy_alt/diplomacy_alt.cpp",
    "src/reconstruction/pkg13_e2_diplomacy_alt/diplomacy_alt.hpp",
    "src/reconstruction/pkg13_e2_diplomacy_alt/diplomacy_alt_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-e2-diplomacy-alt/00d00d60.json"
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
    "concrete first and second object owners and +0x4c implementations",
    "gate-diplomacy-relationship-objects-00d00d60",
    "relationship policy owner and runtime score availability",
    "runtime meaning and domain of mode",
    "runtime score values for directed identity pairs",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-e2-diplomacy-alt/00d00d60.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e2-diplomacy-alt/diplomacy_alt.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e2-diplomacy-alt/diplomacy_alt.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e2-diplomacy-alt/diplomacy_alt_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e2_diplomacy_alt/diplomacy_alt.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e2_diplomacy_alt/diplomacy_alt.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e2_diplomacy_alt/diplomacy_alt_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg13-e2-diplomacy-alt/00d00d60.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-e2-diplomacy-alt/diplomacy_alt.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-e2-diplomacy-alt/diplomacy_alt.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstr
[TRUNCATED]
```
