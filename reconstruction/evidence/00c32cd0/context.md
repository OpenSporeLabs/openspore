# Reconstruction context 0x00c32cd0

- Status: `partial`
- Content SHA-256: `3edf089ca468113e2c44acab0f47654950c7f1d3c743b1f6dc6c1ec927af1f56`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c32cd0",
  "phase": "reconstruction",
  "target": "0x00c32cd0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c32cd0",
  "package": "PKG-13-E4-EMPIRE-WAVE3",
  "subsystem": "Simulator",
  "va": "0x00c32cd0"
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
  "content_sha256": "e8f1ffd0e83fe67a5735f83642104c59a028cabf09512e05bd7298c6a0910c90",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c32cd0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_type": "OpaqueRecord*",
  "return_type": "OpaqueFloatColor*",
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "output",
      "position": 1,
      "type": "OpaqueFloatColor*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4 on every return path"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "address_window_offset_005c65e0",
      "reconstructed": true,
      "va": "0x005c65e0"
    },
    {
      "name": "pkg13_creature_accessor_00b1fdb0",
      "reconstructed": true,
      "va": "0x00b1fdb0"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c30c80"
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
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b677e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6d3c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
    },
    {
      "name": "FUN_00c33580",
      "reconstructed": false,
      "va": "0x00c33580"
    },
    {
      "name": "ProfileSetter_00c33690",
      "reconstructed": true,
      "va": "0x00c33690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c737a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cc22c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd4b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e06d90"
    },
    {
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
    "OpaqueFloatColor*",
    "OpaqueRecord*"
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
      "name": "address_window_offset_005c65e0",
      "reconstructed": true,
      "va": "0x005c65e0"
    },
    {
      "name": "pkg13_creature_accessor_00b1fdb0",
      "reconstructed": true,
      "va": "0x00b1fdb0"
    },
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "Simulator_LookupEmpireByPoliticalId",
      "reconstructed": true,
      "va": "0x00ba9370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c30c80"
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
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b677e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6d3c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba0080"
    },
    {
      "name": "FUN_00c33580",
      "reconstructed": false,
      "va": "0x00c33580"
    },
    {
      "name": "ProfileSetter_00c33690",
      "reconstructed": true,
      "va": "0x00c33690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c737a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cc22c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00dd4b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x
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
      "shared_types:OpaqueRecord*"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 11,
    "symbol": "PoliticalOwnershipScan_00c8d060",
    "va": "0x00c8d060"
  },
  {
    "match_basis": [
      "same_subsystem",
      "direct_xref_neighbor"
    ],
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 9,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 9,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-sim-toolevent-01053d50",
    "score": 8,
    "symbol": "sim_toolevent_slot8_fun_01053d50",
    "va": "0x01053d50"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "cycle_key_006286a0",
    "va": "0x006286a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3.cpp",
    "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3.hpp",
    "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3_boundary_test.sh",
    "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3_model_test.cpp",
    "src/reconstruction/pkg13_e4_empire_wave3/empire_wave3.cpp",
    "src/reconstruction/pkg13_e4_empire_wave3/empire_wave3.hpp",
    "src/reconstruction/pkg13_e4_empire_wave3/empire_wave3_boundary_test.sh",
    "src/reconstruction/pkg13_e4_empire_wave3/empire_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-e4-empire-wave3/00c32cd0.json"
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
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-e4-empire-wave3/00c32cd0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3_boundary_test.sh', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e4_empire_wave3/empire_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e4_empire_wave3/empire_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e4_empire_wave3/empire_wave3_boundary_test.sh', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e4_empire_wave3/empire_wave3_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg13-e4-empire-wave3/00c32cd0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstructio
[TRUNCATED]
```
