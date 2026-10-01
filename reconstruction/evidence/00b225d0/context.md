# Reconstruction context 0x00b225d0

- Status: `partial`
- Content SHA-256: `ff9b9ee6e1f3271206045acccfebcbb5f1bdff648ca0f82012ffe9426b4758ba`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b225d0",
  "phase": "reconstruction",
  "target": "0x00b225d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueNounManager",
  "name": "FUN_00b225d0",
  "package": "PKG-11-H3-HELPER-WAVE2",
  "subsystem": "Simulator.NounManager",
  "va": "0x00b225d0"
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
  "content_sha256": "da6c95466c29c31e472cd94b53abe13ffeae36ec9644cffc2da70fce4a563ba2",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b225d0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX is OpaqueNounManager*",
  "ordinary_stack_argument_slots": 1,
  "ret_form": "RET 4",
  "return_type": "void",
  "stack_cleanup_bytes": 4
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "FUN_00aea5d0",
      "reconstructed": true,
      "va": "0x00aea5d0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac79a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac79e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac7a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acd4a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acf4c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad08f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad1000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae0700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae5f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae7100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae73e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b068c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b07980"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b09b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b0c190"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ac79b2",

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueNounManager",
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
      "gate-noun-manager-logical-destroy-00b225d0",
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
      "name": "FUN_00aea5d0",
      "reconstructed": true,
      "va": "0x00aea5d0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac79a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac79e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac7a40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acd4a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ace5a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00acf4c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad08f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ad1000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae0700"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae5f20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae7100"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae73e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b068c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b07980"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b09b00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b0c190"
    },
    {
      "name": null,
   
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
    "package": "PKG-11-H3-HELPER-WAVE2",
    "score": 8,
    "symbol": "embedded_object_first_word_init_00743b50",
    "va": "0x00743b50"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueNounManager"
    ],
    "package": "PKG-13-CREATURE-ACCESSOR",
    "score": 8,
    "symbol": "pkg13_creature_accessor_00b1fdb0",
    "va": "0x00b1fdb0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueNounManager"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-11-H3-HELPER-WAVE2",
    "score": 8,
    "symbol": "strategy_base_constructor_00b5b960",
    "va": "0x00b5b960"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-12-SIM-SPACE",
    "score": 3,
    "symbol": "FUN_00aea5d0",
    "va": "0x00aea5d0"
  },
  {
    "match_basis": [
      "shared_types:OpaqueNounManager"
    ],
    "package": "PKG-13-SIM-CREATURE-TRIBECIV",
    "score": 3,
    "symbol": "Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel",
    "va": "0x00d2e380"
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
    "symbol": "EditorCreat
[TRUNCATED]
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
    "reconstruction/metadata/pkg11-h3-helper-wave2/00b225d0.json"
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
    "C++ inheritance or vector class identity",
    "allocator implementation behind 0x00f473a0 or 0x00f47380",
    "behavior inside 0x00b20d30 or 0x00b201a0",
    "concrete noun or manager C++ type",
    "gate-noun-manager-logical-destroy-00b225d0",
    "runtime pointer validity beyond the modeled no-guard fault boundaries",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg11-h3-helper-wave2/00b225d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg11-h3-helper-wave2/helper_wave2_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h3_helper_wave2/helper_wave2.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h3_helper_wave2/helper_wave2.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg11_h3_helper_wave2/helper_wave2_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg11-h3-helper-wave2/00b225d0.json",
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
