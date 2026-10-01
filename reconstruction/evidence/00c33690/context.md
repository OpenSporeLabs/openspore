# Reconstruction context 0x00c33690

- Status: `partial`
- Content SHA-256: `9f26c03d3012f9480ab87b1ec3437d38159974af22bd4b2c962c4b1e49f3d2ee`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c33690",
  "phase": "reconstruction",
  "target": "0x00c33690"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueSpeciesProfile",
  "name": "FUN_00c33690",
  "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
  "subsystem": "Simulator.SpeciesProfile",
  "va": "0x00c33690"
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
  "content_sha256": "1fe237e753cb553c93edd6b6e33d873974040f57e6e17ebebfd4bd71a4ff041a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c33690 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_type": "OpaqueSpeciesProfile*",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "profile",
      "position": 1,
      "type": "OpaqueProfile*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4 on the single exit"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "star_manager_record_to_planet_00bb5b50",
      "reconstructed": true,
      "va": "0x00bb5b50"
    },
    {
      "name": "EmpirePoliticalColor_00c32cd0",
      "reconstructed": true,
      "va": "0x00c32cd0"
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
      "va": "0x00bb1340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba2a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0100a160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010221f0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00bb1473",
      "direction": "in",
      "other": "0x00bb1340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bba488",
      "direction": "in",
      "other": "0x00bba2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0100a381",
      "direction": "in",
      "other": "0x0100a160",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01022419",
      "direction": "in",
      "other": "0x010221f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c337e7",
      "direction": "out",
      "other": "0x00423650",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c336c8",
      "direction": "out",
  
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueProfile*",
    "OpaqueSpeciesProfile",
    "OpaqueSpeciesProfile*",
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
      "gate-profile-setter-00c33690",
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
      "name": "FUN_00b3d2a0",
      "reconstructed": true,
      "va": "0x00b3d2a0"
    },
    {
      "name": "star_manager_record_to_planet_00bb5b50",
      "reconstructed": true,
      "va": "0x00bb5b50"
    },
    {
      "name": "EmpirePoliticalColor_00c32cd0",
      "reconstructed": true,
      "va": "0x00c32cd0"
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
      "va": "0x00bb1340"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bba2a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0100a160"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010221f0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00bb1473",
      "direction": "in",
      "other": "0x00bb1340",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bba488",
      "direction": "in",
      "other": "0x00bba2a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0100a381",
      "direction": "in",
      "other": "0x0100a160",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01022419",
      "direction": "in",
      "other": "0x010221f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c337e7",
      "direction": "out",
      "other": "0x00423650",
      "reference_type": "d
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
      "same_subsystem"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 14,
    "symbol": "SpeciesProfileSelector_00c30cc0",
    "va": "0x00c30cc0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 14,
    "symbol": "ArchetypeRelationshipsID_00c30e20",
    "va": "0x00c30e20"
  },
  {
    "match_basis": [
      "same_package",
      "same_calling_convention"
    ],
    "package": "PKG-13-E3-EMPIRE-STATE-WAVE2",
    "score": 10,
    "symbol": "HomeWorldMetricLazy_00c31890",
    "va": "0x00c31890"
  },
  {
    "match_basis": [
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-14-A2-WORLD-LIFECYCLE-WAVE2",
    "score": 5,
    "symbol": "star_manager_record_to_planet_00bb5b50",
    "va": "0x00bb5b50"
  },
  {
    "match_basis": [
      "same_calling_convention",
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 5,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 3,
    "symbol": "pkg12_space_01021300",
    "va": "0x01021300"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-RUNTIME-WAVE7",
  
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary.S",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary_test.sh",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.cpp",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.hpp",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2_model_test.cpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary.S",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary_test.sh",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.hpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-e3-empire-state-wave2/00c33690.json"
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
    "gate-profile-setter-00c33690",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg13-e3-empire-state-wave2/00c33690.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary.S', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary_test.sh', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary.S', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary_test.sh', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg13-e3-empire-state-wave2/00c33690.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary.S",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary_test.sh",
      "source_class": "committed_artifact"
    },
    {
      "mode": "p
[TRUNCATED]
```
