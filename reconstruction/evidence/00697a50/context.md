# Reconstruction context 0x00697a50

- Status: `partial`
- Content SHA-256: `10565b763cc76bfabd7f5b72ff9bb06ef2fcaa23a599bc2b1c1b515343969f87`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00697a50",
  "phase": "reconstruction",
  "target": "0x00697a50"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueGameInput",
  "name": "game_input_on_key_down_00697a50",
  "package": "PKG-GAME-INPUT-WAVE7",
  "subsystem": "Input",
  "va": "0x00697a50"
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
  "content_sha256": "b46b2aa3aff421a6f06c1793547ffa6cef9b1602bf7e51973aec24a8a7774b22",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00697a50 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX OpaqueGameInput*",
  "ordinary_stack_arguments": [
    {
      "name": "vkCode",
      "offset": "ESP+4",
      "slot": 0,
      "type": "int32"
    },
    {
      "offset": "ESP+8",
      "slot": 1,
      "type": "KeyModifiers",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 8",
  "stack_cleanup_bytes": 8
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
      "va": "0x00585830"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e00650"
    },
    {
      "name": "cell_mode_strategy_on_key_down_00e818f0",
      "reconstructed": true,
      "va": "0x00e818f0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00585843",
      "direction": "in",
      "other": "0x00585830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058ac2d",
      "direction": "in",
      "other": "0x0058ac10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e00655",
      "direction": "in",
      "other": "0x00e00650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8192f",
      "direction": "in",
      "other": "0x00e818f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00697a75",
      "direction": "out",
      "other": "0x006979c0",
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
    "KeyModifiers",
    "OpaqueGameInput",
    "int32",
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
      "Observe receiver validity, key-domain inputs, and the native 0x006979c0 refresh state in the original input owner."
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
      "va": "0x00585830"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e00650"
    },
    {
      "name": "cell_mode_strategy_on_key_down_00e818f0",
      "reconstructed": true,
      "va": "0x00e818f0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00585843",
      "direction": "in",
      "other": "0x00585830",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058ac2d",
      "direction": "in",
      "other": "0x0058ac10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e00655",
      "direction": "in",
      "other": "0x00e00650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e8192f",
      "direction": "in",
      "other": "0x00e818f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00697a75",
      "direction": "out",
      "other": "0x006979c0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 4,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x0058ac10",
    "0x00e818f0"
  ],
  "scc": {
    "id": "scc-0194",
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
      "same_class",
      "shared_types:KeyModifiers,OpaqueGameInput,int32",
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 33,
    "symbol": "cell_mode_strategy_on_key_down_00e818f0",
    "va": "0x00e818f0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:KeyModifiers,OpaqueGameInput,int32",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 30,
    "symbol": "game_input_on_key_up_00697a80",
    "va": "0x00697a80"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameInput,int32",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 27,
    "symbol": "game_input_mouse_up_00697af0",
    "va": "0x00697af0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameInput",
      "same_calling_convention"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 24,
    "symbol": "cell_mode_strategy_on_mouse_move_00e51010",
    "va": "0x00e51010"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueGameInput"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 22,
    "symbol": "simulator_game_input_manager_get_00b3d350",
    "va": "0x00b3d350"
  },
  {
    "match_basis": [
    
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-input-wave7/00697a50.json"
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
    "Observe receiver validity, key-domain inputs, and the native 0x006979c0 refresh state in the original input owner.",
    "concrete runtime owners and values remain unresolved"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-game-input-wave7/00697a50.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-game-input-wave7/00697a50.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS"
[TRUNCATED]
```
