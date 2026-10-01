# Reconstruction context 0x0067dde0

- Status: `partial`
- Content SHA-256: `2bfdb681b64814e4dfc38de8f6ec37dd1635d2b3fe7c72fd8db8ee9ff0f5434f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0067dde0",
  "phase": "reconstruction",
  "target": "0x0067dde0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueRuntimeService",
  "name": "app_cheat_manager_get_0067dde0",
  "package": "PKG-RUNTIME-SERVICES-WAVE7",
  "subsystem": "Runtime.Services",
  "va": "0x0067dde0"
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
  "content_sha256": "a32e0af3c9f76690afac5c25d12c6c8b161a948dda6f4db93a42a13562ccdfc6",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0067dde0 failed: Decompilation did not complete. Reason: ",
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
  "architecture": "x86:LE:32",
  "calling_convention": "cdecl-compatible no-argument accessor",
  "hidden_receiver": null,
  "ordinary_stack_arguments": [],
  "return_note": "opaque 32-bit service pointer",
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
  "callees": [],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f47ed0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00f4850d",
      "direction": "in",
      "other": "0x00f47ed0",
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
    "global:0x015fd8ec",
    "global:read at 0x0067dde0; write at 0x0067e004 in FUN_0067e000"
  ],
  "types": [
    "OpaqueRuntimeService",
    "opaque 32-bit service pointer"
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
      "required"
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
      "va": "0x00f47ed0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00f4850d",
      "direction": "in",
      "other": "0x00f47ed0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0185",
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
      "same_class",
      "shared_types:OpaqueRuntimeService,opaque 32-bit service pointer",
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 27,
    "symbol": "app_id_generator_get_007c79e0",
    "va": "0x007c79e0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRuntimeService"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 22,
    "symbol": "editor_anim_event_message_post_0059d840",
    "va": "0x0059d840"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRuntimeService"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 22,
    "symbol": "editor_anim_event_message_send_0059d8b0",
    "va": "0x0059d8b0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRuntimeService"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 22,
    "symbol": "app_prop_manager_get_global_property_list_006a3310",
    "va": "0x006a3310"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRuntimeService"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 22,
    "symbol": "app_prop_manager_get_supported_types_006a3400",
    "va": "0x006a3400"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
  
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp",
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.hpp",
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-runtime-services-wave7/0067dde0.json"
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
    "Does any caller require non-null service semantics?",
    "What startup and teardown paths replace or clear the slot?",
    "Which concrete cheat manager is published at 0x015fd8ec?",
    "required"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-runtime-services-wave7/0067dde0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-runtime-services-wave7/0067dde0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src
[TRUNCATED]
```
