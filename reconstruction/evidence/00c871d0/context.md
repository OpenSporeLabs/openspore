# Reconstruction context 0x00c871d0

- Status: `partial`
- Content SHA-256: `a0d686530abf25893c683a2e36b45081538978e5ca999eaa2f13e7e62fa8b9d6`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c871d0",
  "phase": "reconstruction",
  "target": "0x00c871d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueRuntimeService",
  "name": "App::Canvas::GetMessageServer",
  "package": "PKG-RUNTIME-SERVICES-WAVE7",
  "subsystem": "Runtime.Services",
  "va": "0x00c871d0"
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
  "content_sha256": "afaba9ae4f88c9934d4066ad5b25b1ed3369a08663ce915d0a1300d25a078172",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c871d0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall",
  "hidden_receiver": "ECX = OpaqueCanvas*",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "result",
      "position": 1,
      "type": "CanvasMessageServerResult*",
      "width_bytes": 4
    }
  ],
  "return_note": "same result pointer",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00c87217",
      "direction": "out",
      "other": "0x006a1250",
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
    "global:0x01579eb0, 0x01579eb4, and 0x01579eb8 each have one read reference from this body"
  ],
  "types": [
    "CanvasMessageServerResult*",
    "OpaqueRuntimeService",
    "same result pointer"
  ],
  "vtables": [
    "vtable:0x00000020",
    "vtable:0x01459c6c",
    "vtable:0x0146576c",
    "vtable:0x01471fdc",
    "vtable:0x01472040",
    "vtable:0x01473528",
    "vtable:0x01473590",
    "vtable:0x0149ad14"
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00c87217",
      "direction": "out",
      "other": "0x006a1250",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0477",
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
      "shared_types:OpaqueRuntimeService",
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 24,
    "symbol": "editor_anim_event_message_post_0059d840",
    "va": "0x0059d840"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRuntimeService",
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 24,
    "symbol": "editor_anim_event_message_send_0059d8b0",
    "va": "0x0059d8b0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRuntimeService",
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 24,
    "symbol": "app_prop_manager_get_global_property_list_006a3310",
    "va": "0x006a3310"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRuntimeService",
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 24,
    "symbol": "app_prop_manager_get_supported_types_006a3400",
    "va": "0x006a3400"
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
    "symbol": "app_cheat_manager_get_0067dde0",
    "va": "0x0067dde0"
  },
  {
    "match_basis": 
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__GetMessageServer.c",
  "file": "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__GetMessageServer.c",
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp",
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.hpp",
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-runtime-services-wave7/00c871d0.json"
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
    "What concrete Canvas receiver and vtable are used at runtime?",
    "What do the three global words represent?",
    "What owns the property list at receiver+0x30?",
    "What property-key result is returned by 0x006a1250?",
    "required"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__GetMessageServer.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-runtime-services-wave7/00c871d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__GetMessageServer.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-runtime-services-wave7/00c871d0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref":
[TRUNCATED]
```
