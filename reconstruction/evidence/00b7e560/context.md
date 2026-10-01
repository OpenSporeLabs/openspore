# Reconstruction context 0x00b7e560

- Status: `partial`
- Content SHA-256: `af088b178a31f70c2ac7803fba64139eafebf1c96eb3b0727fde1bcd16f5c40d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b7e560",
  "phase": "reconstruction",
  "target": "0x00b7e560"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "sphere_draw_direction_00b7e560",
  "package": "PKG-14-A3-WORLD-WAVE3",
  "subsystem": null,
  "va": "0x00b7e560"
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
  "content_sha256": "6c7301064823d47105d17b83afb0fdcf18fbaddf0861b842d24e249785a11c0d",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b7e560 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl",
  "hidden_this_register": "none",
  "receiver": "ECX",
  "return": "float",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "direction",
      "position": 1,
      "type": "float*"
    }
  ],
  "stack_cleanup_bytes": 0,
  "termination": "plain RET"
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
      "va": "0x00b81720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b81780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b81a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b84730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fc00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cb5770"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d5cfd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d5ef80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e5cae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6ff60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e75350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01007bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0105b350"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b8172b",
      "direction": "in",
      "other": "0x00b81720",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b817c8",
      "direction": "in",
      "other": "0x00b81780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b81a88",
 
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueRenderHelper*",
    "float*",
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b81720"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b81780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b81a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b84730"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4c790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c4fc00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cb5770"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d5cfd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d5ef80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e5cae0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6ff60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e75350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01007bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0105b350"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00b8172b",
      "direction": "in",
      "other": "0x00b81720",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00b817c8",
      "direction": "in",
      "other": "0x00b81780",
[TRUNCATED]
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
    "package": "PKG-14-A3-WORLD-WAVE3",
    "score": 8,
    "symbol": "solar_system_load_00c86760",
    "va": "0x00c86760"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 2,
    "symbol": "simulator_game_input_manager_get_00b3d350",
    "va": "0x00b3d350"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-13-C4-CIV-WAVE3",
    "score": 2,
    "symbol": "city_building_economy_update_00be2440",
    "va": "0x00be2440"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 2,
    "symbol": "SpeciesProfileSelector_00c30cc0",
    "va": "0x00c30cc0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 2,
    "symbol": "ArchetypeRelationshipsID_00c30e20",
    "va": "0x00c30e20"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 2,
    "symbol": "PoliticalOwnershipScan_00c8d060",
    "va": "0x00c8d060"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-13-E2-DIPLOMACY-ALT",
    "score": 2,
    "symbol": "RelationshipScoreBand_00d00d00",
    "va": "0x00d00d00"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-GAME-MODE-WAVE7",
    "score": 2,
    "symbol": "cell_mode_constructor_00e616c0",
    "va": "0x00e616c0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg14-a3-world-wave3/world_wave3.cpp",
    "reconstruction/staging/pkg14-a3-world-wave3/world_wave3.hpp",
    "reconstruction/staging/pkg14-a3-world-wave3/world_wave3_model_test.cpp",
    "src/reconstruction/pkg14_a3_world_wave3/world_wave3.cpp",
    "src/reconstruction/pkg14_a3_world_wave3/world_wave3.hpp",
    "src/reconstruction/pkg14_a3_world_wave3/world_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg14-a3-world-wave3/00b7e560.json"
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
    "The distribution and state ownership behind 0x009360d0 remain opaque.",
    "The helper address 0x01601760 is preserved as the live receiver identity without dereferencing it in the model.",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg14-a3-world-wave3/00b7e560.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a3-world-wave3/world_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a3-world-wave3/world_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg14-a3-world-wave3/world_wave3_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg14_a3_world_wave3/world_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg14_a3_world_wave3/world_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg14_a3_world_wave3/world_wave3_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg14-a3-world-wave3/00b7e560.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg14-a3-world-wave3/world_wave3.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg14-a3-world-wave3/world_wave3.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/sta
[TRUNCATED]
```
