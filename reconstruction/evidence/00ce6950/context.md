# Reconstruction context 0x00ce6950

- Status: `partial`
- Content SHA-256: `c16b631f3bf804f3ae14a28201d637b937ffb3a2aa5d499849d28cd73317a8de`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00ce6950",
  "phase": "reconstruction",
  "target": "0x00ce6950"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00ce6950",
  "package": "PKG-11-H4-HELPER-WAVE3",
  "subsystem": "Simulator",
  "va": "0x00ce6950"
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
  "content_sha256": "b4ab19b74b8b5c4a7f50e8a967cb2ca2149b99ad3f9d0106abd11171cc602710",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00ce6950 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "fastcall-compatible one-argument ECX function",
  "hidden_receiver": "ECX is the opaque context-window pointer",
  "ordinary_stack_argument_slots": 0,
  "ret_form": "RET",
  "return_note": "raw 32-bit word",
  "return_type": "OpaqueContextWord",
  "stack_cleanup_bytes": 0
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
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba57f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba58f3"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5a60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5bd3"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baf790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb99e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf03e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1270"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00aeb4ae",
      "direction": "in",
      "other": "0x00aeb3e0",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueContextWord raw 32-bit word"
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
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb890"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba4f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5650"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba57f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba58f3"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5a60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba5bd3"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00baf790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb99e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf03e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf0810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf1270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf14b0"
    },
    {
      "name": null,
      "reconst
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
      "same_calling_convention"
    ],
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 16,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
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
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "Simulator_GetUIMissionLogManager",
    "va": "0x00b3d4f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 6,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3.cpp",
    "reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3.hpp",
    "reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3_model_test.cpp",
    "src/reconstruction/pkg11_h4_helper_wave3/helper_wave3.cpp",
    "src/reconstruction/pkg11_h4_helper_wave3/helper_wave3.hpp",
    "src/reconstruction/pkg11_h4_helper_wave3/helper_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-h4-helper-wave3/00ce6950.json"
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
      "derived": "__thiscall",
      "field": "calling_convention",
      "kind": "derived_vs_persisted",
      "persisted": "fastcall-compatible one-argument ECX function",
      "resolution_status": "unresolved"
    }
  ],
  "unresolved_questions": [
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-h4-helper-wave3/00ce6950.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h4_helper_wave3/helper_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h4_helper_wave3/helper_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h4_helper_wave3/helper_wave3_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg11-h4-helper-wave3/00ce6950.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstructio
[TRUNCATED]
```
