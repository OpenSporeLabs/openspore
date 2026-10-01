# Reconstruction context 0x00bf9820

- Status: `partial`
- Content SHA-256: `6ccc1cf27c944fbbac12d2d919a6bbe133d3b776688338c0fb5dac02e63af467`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00bf9820",
  "phase": "reconstruction",
  "target": "0x00bf9820"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "culture_selection_00bf9820",
  "package": "PKG-13-C4-CIV-WAVE3",
  "subsystem": null,
  "va": "0x00bf9820"
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
  "content_sha256": "e0020591ecc33923c8111f5d0291fd9505381fe6f12f8171f582f3a2f562a845",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00bf9820 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall-like",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueCultureSelection* selection",
  "ordinary_stack_arguments": [],
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
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
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    },
    {
      "name": "FUN_00b25ca0",
      "reconstructed": false,
      "va": "0x00b25ca0"
    },
    {
      "name": "FUN_00b25fb0",
      "reconstructed": false,
      "va": "0x00b25fb0"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "simulator_game_input_manager_get_00b3d350",
      "reconstructed": true,
      "va": "0x00b3d350"
    },
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    },
    {
      "name": "FUN_00bd81d0",
      "reconstructed": false,
      "va": "0x00bd81d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd8210"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfbbf0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00bfbe95",
      "direction": "in",
      "other": "0x00bfbbf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bf9924",
      "direction": "out",
      "other": "0x00b21340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bf99bd",
      "direction": "out",
      "other": "0x00b25ca0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bf985d",
      "direction": "out",
      "other": "0x00b25fb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bf9856",
      "direction": "out",
      "other": "0x00b3d300",

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueCultureSelection* selection",
    "uint16_t",
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
  "callees": [
    {
      "name": "pkg11_sim_core_00b21340",
      "reconstructed": true,
      "va": "0x00b21340"
    },
    {
      "name": "FUN_00b25ca0",
      "reconstructed": false,
      "va": "0x00b25ca0"
    },
    {
      "name": "FUN_00b25fb0",
      "reconstructed": false,
      "va": "0x00b25fb0"
    },
    {
      "name": "FUN_00b3d300",
      "reconstructed": true,
      "va": "0x00b3d300"
    },
    {
      "name": "simulator_game_input_manager_get_00b3d350",
      "reconstructed": true,
      "va": "0x00b3d350"
    },
    {
      "name": "FUN_00b5b800",
      "reconstructed": false,
      "va": "0x00b5b800"
    },
    {
      "name": "FUN_00bd81d0",
      "reconstructed": false,
      "va": "0x00bd81d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bd8210"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bfbbf0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00bfbe95",
      "direction": "in",
      "other": "0x00bfbbf0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bf9924",
      "direction": "out",
      "other": "0x00b21340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bf99bd",
      "direction": "out",
      "other": "0x00b25ca0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bf985d",
      "direction": "out",
      "other": "0x00b25fb0",
      "reference_type": "direct-call"
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
      "same_package"
    ],
    "package": "PKG-13-C4-CIV-WAVE3",
    "score": 8,
    "symbol": "city_building_economy_update_00be2440",
    "va": "0x00be2440"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 3,
    "symbol": "pkg11_sim_core_00b21340",
    "va": "0x00b21340"
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
      "direct_xref_neighbor"
    ],
    "package": "PKG-GAME-INPUT-WAVE7",
    "score": 3,
    "symbol": "simulator_game_input_manager_get_00b3d350",
    "va": "0x00b3d350"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.cpp",
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.hpp",
    "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c4-civ-wave3/00bf9820.json"
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
        "0x00b21340",
        "0x00b21340",
        "0x00acd9a0",
        "0x00acd9a0",
        "0x00acd9a0",
        "0x00ace2c0",
        "0x00ace2c0",
        "0x00ace2c0",
        "0x00b25f40",
        "0x00b25f40",
        "0x00ba0080",
        "0x00ba0080",
        "0x00ba0080",
        "0x00bf9820",
        "0x00bf9820",
        "0x00ba8420"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:0",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00e63560",
        "0x00e63560",
        "0x00acd9a0",
        "0x00ace2c0",
        "0x00b25f40",
        "0x00ba0080",
        "0x00bf9820",
        "0x00e5c780",
        "0x00551240",
        "0x0067dd90",
        "0x00e66280",
        "0x00e66840",
        "0x00e63560",
        "0x00e5c780",
        "0x00e63560",
        "0x00571f80"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.j
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-c4-civ-wave3/00bf9820.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_c4_civ_wave3/civ_wave3_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg13-c4-civ-wave3/00bf9820.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg13_c4_civ_wave
[TRUNCATED]
```
