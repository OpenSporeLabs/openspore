# Reconstruction context 0x007e5f30

- Status: `partial`
- Content SHA-256: `e7ebdaf275b2e8b72a7c225cc8e9ad497e8cb25e2d34e0eb169b655ad6b812a2`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007e5f30",
  "phase": "reconstruction",
  "target": "0x007e5f30"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueWave6AppSystem",
  "name": "App::cAppSystem::Unpause",
  "package": "WAVE6-ENGINE-RUNTIME",
  "subsystem": "App.Lifecycle",
  "va": "0x007e5f30"
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
  "content_sha256": "dd15dacd0f43b574187d15632a1abdf32481742991491678d01b852b7355a789",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x007e5f30 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "ordinary_stack_arguments": [],
  "receiver_register": "ECX",
  "return_register": "EAX",
  "return_width_bytes": 4,
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
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x007e5f40",
      "direction": "out",
      "other": "0x0067dcc0",
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
    "DATA",
    "OpaqueWave6AppService",
    "OpaqueWave6AppSystem",
    "OpaqueWave6AppSystem*",
    "Wave6AppLifecyclePorts"
  ],
  "vtables": [
    "vtable:0x00000018",
    "vtable:0x01413acc",
    "vtable:0x01413b48"
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
      "gate-app-system-service-gate-and-vtable"
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
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x007e5f40",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 1,
  "manifest_callees": [
    "0x0067dcc0",
    "service vtable +0x18"
  ],
  "manifest_callers": [
    "data_xref_01413b48"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0249",
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
      "shared_types:DATA",
      "shared_vtable:vtable:0x01413acc",
      "same_calling_convention"
    ],
    "package": "WAVE6-ENGINE-RUNTIME",
    "score": 17,
    "symbol": "app_system_initialize_plugins_007e93d0",
    "va": "0x007e93d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA",
      "same_calling_convention"
    ],
    "package": "PKG-APP-LIFECYCLE-WAVE8",
    "score": 11,
    "symbol": "app_c_cell_mode_strategy_dispose_00e81f30",
    "va": "0x00e81f30"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA"
    ],
    "package": "PKG-APP-LIFECYCLE-WAVE7",
    "score": 9,
    "symbol": "app_capp_system_hook_windows_007e6080",
    "va": "0x007e6080"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA"
    ],
    "package": "PKG-APP-LIFECYCLE-WAVE7",
    "score": 9,
    "symbol": "app_capp_system_set_effect_collection_ids_007e6100",
    "va": "0x007e6100"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:DATA"
    ],
    "package": "PKG-APP-LIFECYCLE-WAVE7",
    "score": 9,
    "symbol": "app_capp_system_func88h_00a6c940",
    "va": "0x00a6c940"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "WAVE6-ENGINE-RUNTIME",
    "score": 8,
    "symbol": "app_config_manager_get_0067dcf0",
    "va": "0x0067dcf0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01413b48",
      "same_calling_convention"
    ],
    "package": "pkg-sporepedia-nop-slot",
    "score": 6,
    "symbol": "spo
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cAppSystem__Unpause.c",
  "file": "src/reconstruction/wave6_engine_runtime/engine_runtime.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cAppSystem__Unpause.c",
    "reconstruction/staging/wave6-engine-runtime/engine_runtime.cpp",
    "reconstruction/staging/wave6-engine-runtime/engine_runtime.hpp",
    "reconstruction/staging/wave6-engine-runtime/engine_runtime_model_test.cpp",
    "src/reconstruction/wave6_engine_runtime/engine_runtime.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-engine-runtime/007e5f30.json"
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
    "What EAX value is present on entry to the zero-gate path in real callers?",
    "What do selector 0x0462dde3 and the three zero words mean?",
    "What lifecycle or pause state is represented by receiver+0x16c and receiver+0x172?",
    "Which concrete vtable target occupies service+0x18 at runtime?",
    "Which table owner reaches the data pointer at 0x01413b48?",
    "concrete service vtable target",
    "gate-app-system-service-gate-and-vtable",
    "meanings of receiver +0x16c and +0x172",
    "selector and argument meanings",
    "zero-gate caller EAX residue"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__cAppSystem__Unpause.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-engine-runtime/007e5f30.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-engine-runtime/engine_runtime.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-engine-runtime/engine_runtime.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-engine-runtime/engine_runtime_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_engine_runtime/engine_runtime.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cAppSystem__Unpause.c",
      "source_class": "committed_artifact"
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave6-engine-runtime/007e5f30.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-engine-runtime/engine_runtime.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/stag
[TRUNCATED]
```
