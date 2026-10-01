# Reconstruction context 0x0067dcf0

- Status: `partial`
- Content SHA-256: `aa93497476e7cb342bc27a84509707e323b5ff013f0757094ef7fc44792dd3d3`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0067dcf0",
  "phase": "reconstruction",
  "target": "0x0067dcf0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueWave6ConfigManager",
  "name": "app_config_manager_get_0067dcf0",
  "package": "WAVE6-ENGINE-RUNTIME",
  "subsystem": "App.Services",
  "va": "0x0067dcf0"
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
  "content_sha256": "7b993b63fd647d80a1cfdac85f216cf78bc16e54b93f7b2c2f6ab23de8711a4b",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0067dcf0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__cdecl",
  "ordinary_stack_arguments": [],
  "return_register": "EAX",
  "return_semantics": "borrowed 32-bit service pointer word returned unchanged",
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
  "callees": [],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00601fd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00603f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00609710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0075df60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0075e900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0075f030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007e9db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007f4710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008013d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008027e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00812c90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00812f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00812ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008131b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f47580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f47ed0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0060211c",
      "direction": "in",
      "other": "0x00601fd0",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x015fd89c"
  ],
  "types": [
    "OpaqueWave6ConfigManager"
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
      "gate-config-manager-slot-publication"
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
      "va": "0x00601fd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00603f10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00609710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0075df60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0075e900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0075f030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007e9db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007f4710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008013d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008027e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00812c90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00812f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00812ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008131b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f47580"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f47ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f51680"
    }
  ],
  "callers_truncated": false,
  "dat
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 8,
    "symbol": "App_IStateManager_Get_0067dce0",
    "va": "0x0067dce0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 8,
    "symbol": "App_IPropManager_Get_0067ddf0",
    "va": "0x0067ddf0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "WAVE6-ENGINE-RUNTIME",
    "score": 8,
    "symbol": "app_system_service_gate_dispatch_007e5f30",
    "va": "0x007e5f30"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "WAVE6-ENGINE-RUNTIME",
    "score": 8,
    "symbol": "app_system_initialize_plugins_007e93d0",
    "va": "0x007e93d0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 6,
    "symbol": "service_005f9230",
    "va": "0x005f9230"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 6,
    "symbol": "service_005f9310",
    "va": "0x005f9310"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 6,
    "symbol": "service_005fa8d0",
    "va": "0x005fa8d0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 6,
    "symbol": "service_005fc330",
    "va": "0x005fc330"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/wave6_engine_runtime/engine_runtime.cpp",
  "files": [
    "reconstruction/staging/wave6-engine-runtime/engine_runtime.cpp",
    "reconstruction/staging/wave6-engine-runtime/engine_runtime.hpp",
    "reconstruction/staging/wave6-engine-runtime/engine_runtime_model_test.cpp",
    "src/reconstruction/wave6_engine_runtime/engine_runtime.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-engine-runtime/0067dcf0.json"
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
    "Does any caller assume a non-null service after this unchecked accessor?",
    "What are the concrete manager lifetime and replacement rules?",
    "Which concrete configuration-manager implementation is published in the original process?",
    "Which startup or registration path writes 0x015fd89c before consumers execute?",
    "concrete configuration manager",
    "gate-config-manager-slot-publication",
    "returned pointer lifetime",
    "slot publisher and replacement order"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-engine-runtime/0067dcf0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-engine-runtime/engine_runtime.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-engine-runtime/engine_runtime.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-engine-runtime/engine_runtime_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_engine_runtime/engine_runtime.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave6-engine-runtime/0067dcf0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-engine-runtime/engine_runtime.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-engine-runtime/engine_runtime.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-
[TRUNCATED]
```
