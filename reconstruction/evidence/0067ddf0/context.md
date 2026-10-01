# Reconstruction context 0x0067ddf0

- Status: `partial`
- Content SHA-256: `2b8a45ae693bcc794859a89f468e40ea0ea77915bfd28cb3c03145f845e1b036`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0067ddf0",
  "phase": "reconstruction",
  "target": "0x0067ddf0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaquePropManager",
  "name": "App_IPropManager_Get_0067ddf0",
  "package": "PKG-06-WAVE6-APP-MANAGERS",
  "subsystem": "App.Services",
  "va": "0x0067ddf0"
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
  "content_sha256": "7d5425f51a827789fd53012dc15d43e6604a10c87128f1be534b9477233606bd",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0067ddf0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__cdecl",
  "ordinary_stack_argument_slots": 0,
  "return_note": "opaque pointer word",
  "return_register": "EAX",
  "return_width_bytes": 4,
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
      "va": "0x006f24a0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x006f24c0",
      "direction": "in",
      "other": "0x006f24a0",
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
  "globals": [
    "global:0x015fd8f0",
    "global:g_wave6_service_roots.prop_manager_015fd8f0"
  ],
  "types": [
    "OpaquePropManager",
    "OpaquePropManager*",
    "READ",
    "WRITE",
    "Wave6ServiceRoots",
    "opaque pointer word",
    "undefined4"
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
      "gate-property-manager-slot-publication"
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
      "va": "0x006f24a0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006f24c0",
      "direction": "in",
      "other": "0x006f24a0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [
    "direct_caller_functions_1",
    "function_xrefs_3"
  ],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0186",
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
      "same_subsystem",
      "shared_types:READ,WRITE,Wave6ServiceRoots,opaque pointer word",
      "same_calling_convention"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 25,
    "symbol": "App_IStateManager_Get_0067dce0",
    "va": "0x0067dce0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "WAVE6-ENGINE-RUNTIME",
    "score": 8,
    "symbol": "app_config_manager_get_0067dcf0",
    "va": "0x0067dcf0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 8,
    "symbol": "MessageManagerCleanupStorageWalker_008841f0",
    "va": "0x008841f0"
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
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 6,
    "symbol": "servi
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp",
  "files": [
    "reconstruction/staging/wave6-app-managers/service_accessors_cleanup_model_test.cpp",
    "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-app-managers/0067ddf0.json"
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
    "How does the property manager relate to the App service and state-manager slot?",
    "Is the returned manager borrowed, retained, or invalidated during lifecycle transitions?",
    "What concrete IPropManager subtype and vtable are stored in the slot?",
    "Which startup path publishes or replaces DAT_015fd8f0?",
    "concrete IPropManager subtype",
    "gate-property-manager-slot-publication",
    "returned manager lifetime",
    "slot publisher and replacement order"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-app-managers/0067ddf0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-app-managers/service_accessors_cleanup_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave6-app-managers/0067ddf0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave6-app-managers/service_accessors_cleanup_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/i
[TRUNCATED]
```
