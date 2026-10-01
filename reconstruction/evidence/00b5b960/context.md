# Reconstruction context 0x00b5b960

- Status: `partial`
- Content SHA-256: `01ec8a578253a9a546f6966eaf5df9c6129dc954653ad2b4a0859ff1031cd799`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b5b960",
  "phase": "reconstruction",
  "target": "0x00b5b960"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueStrategyBaseWire",
  "name": "FUN_00b5b960",
  "package": "PKG-11-H3-HELPER-WAVE2",
  "subsystem": "Simulator.Strategy",
  "va": "0x00b5b960"
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
  "content_sha256": "a434dd6f5ccc99ae53c84f2984bd0281c77990ac7a7333d1e5804df5e1ebca9f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b5b960 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX is the receiver pointer",
  "ordinary_stack_argument_slots": 0,
  "ret_form": "RET",
  "return_type": "void",
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
      "va": "0x00ac0c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac4c20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac6b90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac78a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acf230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00adf420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae7f00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebde0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b0bdb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b0d8d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b1c2c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b1d870"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b232b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b26e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2d480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b31ea0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ac0c73",
      "direction": "in",
      "other": "0x00ac0c70",
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
    "OpaqueStrategyBaseWire",
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
      "gate-strategy-base-constructor-00b5b960",
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
      "va": "0x00ac0c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac4c20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac6b90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac78a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acf230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00adf420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae7f00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebde0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b0bdb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b0d8d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b1c2c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b1d870"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b232b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b26e10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2d480"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b31ea0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b379f0"
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
      "same_calling_convention"
    ],
    "package": "PKG-11-H3-HELPER-WAVE2",
    "score": 10,
    "symbol": "embedded_object_first_word_init_00743b50",
    "va": "0x00743b50"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-11-H3-HELPER-WAVE2",
    "score": 8,
    "symbol": "noun_manager_logical_destroy_00b225d0",
    "va": "0x00b225d0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 2,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 2,
    "symbol": "context_word_read_00ce6950",
    "va": "0x00ce6950"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg11_h3_helper_wave2/helper_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2.cpp",
    "reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2.hpp",
    "reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2_model_test.cpp",
    "src/reconstruction/pkg11_h3_helper_wave2/helper_wave2.cpp",
    "src/reconstruction/pkg11_h3_helper_wave2/helper_wave2.hpp",
    "src/reconstruction/pkg11_h3_helper_wave2/helper_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-h3-helper-wave2/00b5b960.json"
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
        "0x00b5b8a0",
        "0x00b5b8c0",
        "0x00b5b8e0",
        "0x00b5b960",
        "0x00b5b960",
        "0x00b1d870",
        "0x00b1d870",
        "0x00b1db60",
        "0x00b1db60",
        "0x00b1dbd0",
        "0x00b1dbd0",
        "0x00b267f0",
        "0x00b267f0",
        "0x00b5b840",
        "0x00b5b840",
        "0x00b5b880"
      ],
      "conflict_id": "game_mode_identifier_domain",
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
        "0x00b1db60",
        "0x00b5b880",
        "0x00b5b8a0",
        "0x00b5b8c0",
        "0x00b5b8e0",
        "0x00b5b960",
        "0x00b1db60",
        "0x00c3ae70",
        "0x00c3dae0",
        "0x01001360",
        "0x01001360",
        "0x01021080",
        "0x01021080",
        "0x01021960",
        "0x01021960",
        "0x01021d40"
      ],
      "conflict_id": "simulator_mode_identifier_mapping",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The co
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-h3-helper-wave2/00b5b960.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h3_helper_wave2/helper_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h3_helper_wave2/helper_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h3_helper_wave2/helper_wave2_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg11-h3-helper-wave2/00b5b960.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstructio
[TRUNCATED]
```
