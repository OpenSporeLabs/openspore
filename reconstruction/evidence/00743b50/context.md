# Reconstruction context 0x00743b50

- Status: `partial`
- Content SHA-256: `aa9024f3df86ee093fb1385cf197f385192b09186d8dcfc71337529cd3b73623`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00743b50",
  "phase": "reconstruction",
  "target": "0x00743b50"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueEmbeddedObject",
  "name": "FUN_00743b50",
  "package": "PKG-11-H3-HELPER-WAVE2",
  "subsystem": "Simulator.Helpers",
  "va": "0x00743b50"
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
  "content_sha256": "14ef9f4011f4c41a0bc9c265d59b375a395be0cd6690d556812cc70c4e41c111",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00743b50 failed: Decompilation did not complete. Reason: ",
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
      "va": "0x0068f600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0092f960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00943a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00946540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00a33600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b46ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6a530"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4c8c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4f040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4f100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4f330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4f860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4f9d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4fc20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4fca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4ff10"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0068f655",
      "direction": "in",
      "other": "0x0068f600",
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
    "OpaqueEmbeddedObject",
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
      "gate-embedded-first-word-00743b50",
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
      "va": "0x0068f600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0092f960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00943a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00946540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00a33600"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b46ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6a530"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4c8c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4f040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4f100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4f330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4f860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4f9d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4fc20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4fca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4ff10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4ffe0"
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
    "symbol": "strategy_base_constructor_00b5b960",
    "va": "0x00b5b960"
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
      "direct_xref_neighbor"
    ],
    "package": "PKG-CAMERA-WAVE7",
    "score": 3,
    "symbol": "cell_move_player_to_mouse_position_00e5b790",
    "va": "0x00e5b790"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 3,
    "symbol": "cell_mode_strategy_on_mouse_down_00e6c860",
    "va": "0x00e6c860"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 3,
    "symbol": "FUN_00e780a0",
    "va": "0x00e780a0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 3,
    "symbol": "FUN_00e7a4a0",
    "va": "0x00e7a4a0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 3,
    "symbol": "FUN_00e7a7c0",
    "va": "0x00e7a7c0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-06-CELL-STATE",
    "score": 3,
    "symbol": "FUN_00e7fd00",
    "va": "0x00e7fd00"
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
    "reconstruction/metadata/pkg11-h3-helper-wave2/00743b50.json"
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
    "any behavior inferred solely from unrelated src/replace comments",
    "any write outside receiver offset zero",
    "concrete pointee or embedded member type",
    "gate-embedded-first-word-00743b50",
    "runtime validation not run",
    "vtable, ownership, reference-count, or destruction meaning"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-h3-helper-wave2/00743b50.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h3_helper_wave2/helper_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h3_helper_wave2/helper_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h3_helper_wave2/helper_wave2_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg11-h3-helper-wave2/00743b50.json",
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
