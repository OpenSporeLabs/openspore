# Reconstruction context 0x00be1fb0

- Status: `partial`
- Content SHA-256: `6dbfea34e37915df6a5739727a63330957c6ed904f83c4e53e3fd9b70ab5cd39`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00be1fb0",
  "phase": "reconstruction",
  "target": "0x00be1fb0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueCity",
  "name": "city_add_building_00be1fb0",
  "package": "PKG-13-C3-TRIBE-CIV-WAVE2",
  "subsystem": "Simulator.CityBuilding",
  "va": "0x00be1fb0"
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
  "content_sha256": "4a5adc0c69ab672e42ce673d341ef2088843bbbf8a4378d6b367c45ba4915748",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00be1fb0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueCity* city",
  "ordinary_stack_arguments": [],
  "return_note": "newly created building identity or null",
  "return_register": "EAX",
  "return_type": "OpaqueBuilding*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "ESI",
    "EBP",
    "EDI"
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
  "callees": [
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be3850"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be3990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d130d0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00be3869",
      "direction": "in",
      "other": "0x00be3850",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00be39bd",
      "direction": "in",
      "other": "0x00be3990",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d13cc7",
      "direction": "in",
      "other": "0x00d130d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00be1fc0",
      "direction": "out",
      "other": "0x00b20c60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00be1fb4",
      "direction": "out",
      "other": "0x00b3d300",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00be2040",
      "direction": "out",
      "other": "0x00bd2310",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00be2027",
      "direction": "out",
      "other": "0x00edafd0",
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
    "OpaqueBuilding* newly created building identity or null",
    "OpaqueCity",
    "OpaqueCity* city"
  ],
  "vtables": [
    "vtable:0x0000000c"
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
      "gate-city-add-building-00be1fb0",
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
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be3850"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be3990"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d130d0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00be3869",
      "direction": "in",
      "other": "0x00be3850",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00be39bd",
      "direction": "in",
      "other": "0x00be3990",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00d13cc7",
      "direction": "in",
      "other": "0x00d130d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00be1fc0",
      "direction": "out",
      "other": "0x00b20c60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00be1fb4",
      "direction": "out",
      "other": "0x00b3d300",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00be2040",
      "direction": "out",
      "other": "0x00bd2310",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00be2027",
      "direction": "out",
      "other": "0x00edafd0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 3,
  "fan_out": 1,
  "manifest_callees": [
    {
      "address"
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
      "same_calling_convention"
    ],
    "package": "PKG-13-C3-TRIBE-CIV-WAVE2",
    "score": 10,
    "symbol": "tribe_constructor_00c982a0",
    "va": "0x00c982a0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x0000000c"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 4,
    "symbol": "editor_query_service_005ca960",
    "va": "0x005ca960"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorCreatureController_SetTargetPosition_0059b0f0",
    "va": "0x0059b0f0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorCreatureController_Update_0059b4b0",
    "va": "0x0059b4b0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorAnimWorld_GetCreatureController_0059cac0",
    "va": "0x0059cac0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorAnimWorld_PlayAnimation_0059cb10",
    "va": "0x0059cb10"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
    "score": 2,
    "symbol": "EditorA
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp",
  "files": [
    "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp",
    "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.hpp",
    "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c3-tribe-civ-wave2/00be1fb0.json"
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
    "No population, persistence, or tribe-state owner is inferred from the city/building offsets.",
    "The 0x00b20c60 service object and its internal linked-list/ref operations are not reclassified as city or building ownership by this target.",
    "The 0x00bd2310 helper's complete owner graph and runtime release behavior are outside this body.",
    "The concrete root, factory, building, city-owner, and building-owner types remain opaque.",
    "The native vector allocator's failure behavior is not replaced with a target-local error policy.",
    "gate-city-add-building-00be1fb0",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-c3-tribe-civ-wave2/00be1fb0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg13-c3-tribe-civ-wave2/00be1fb0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
  
[TRUNCATED]
```
