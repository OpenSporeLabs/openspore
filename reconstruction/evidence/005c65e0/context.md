# Reconstruction context 0x005c65e0

- Status: `partial`
- Content SHA-256: `84abb54e2b4a5b4e2f939e1f7a1374e153658307c481d7ed94166575754fe6be`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005c65e0",
  "phase": "reconstruction",
  "target": "0x005c65e0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_005c65e0",
  "package": "PKG-11-H4-HELPER-WAVE3",
  "subsystem": "Simulator",
  "va": "0x005c65e0"
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
  "content_sha256": "e1a396d6efdec03df620312cec435fce8b762546b3e493a838fb21cf685948bc",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005c65e0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX is the opaque address-window pointer",
  "ordinary_stack_argument_slots": 0,
  "ret_form": "RET",
  "return_note": "raw 32-bit address",
  "return_type": "OpaqueAddressWindow*",
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
      "va": "0x005c7500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac0810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9c90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6baf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6bb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba71b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb1200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb21b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb24d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb3c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb6040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb80f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe470"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005c7663",
      "direction": "in",
      "other": "0x005c7500",
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
    "OpaqueAddressWindow* raw 32-bit address"
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
      "va": "0x005c7500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac0810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9c90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6baf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6b40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6bb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba6e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba71b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb1200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb21b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb24d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb3c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb4f30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb6040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bb80f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bbe5f0"
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
    "symbol": "context_word_read_00ce6950",
    "va": "0x00ce6950"
  },
  {
    "match_basis": [
      "same_subsystem",
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 9,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
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
    "reconstruction/metadata/pkg11-h4-helper-wave3/005c65e0.json"
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
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-h4-helper-wave3/005c65e0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h4_helper_wave3/helper_wave3.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h4_helper_wave3/helper_wave3.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h4_helper_wave3/helper_wave3_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg11-h4-helper-wave3/005c65e0.json",
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
