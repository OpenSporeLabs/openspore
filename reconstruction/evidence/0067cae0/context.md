# Reconstruction context 0x0067cae0

- Status: `partial`
- Content SHA-256: `9edf461542570b3183f059b71e31b9dcd1ca589bd47368a005184896a64979db`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0067cae0",
  "phase": "reconstruction",
  "target": "0x0067cae0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueRuntimeService",
  "name": "anim_manager_get_0067cae0",
  "package": "PKG-RUNTIME-SERVICES-WAVE8",
  "subsystem": "Runtime.Services",
  "va": "0x0067cae0"
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
  "content_sha256": "a2bccb9fe290829e9f618cdffab30d8274af4f7e7eb7979d5eeda27fd923f513",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0067cae0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl-compatible no-argument static accessor",
  "hidden_receiver": null,
  "ordinary_stack_arguments": [],
  "return_note": "opaque 32-bit animation-service pointer",
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
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e02f00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6c9f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ed6540"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0058ccd7",
      "direction": "in",
      "other": "0x0058be50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058cce0",
      "direction": "in",
      "other": "0x0058be50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e03369",
      "direction": "in",
      "other": "0x00e02f00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6cab7",
      "direction": "in",
      "other": "0x00e6c9f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ed670b",
      "direction": "in",
      "other": "0x00ed6540",
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
    "global:0x015fcc5c"
  ],
  "types": [
    "OpaqueRuntimeService",
    "READ",
    "WRITE",
    "opaque 32-bit animation-service pointer"
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
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e02f00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e6c9f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ed6540"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0058ccd7",
      "direction": "in",
      "other": "0x0058be50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0058cce0",
      "direction": "in",
      "other": "0x0058be50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e03369",
      "direction": "in",
      "other": "0x00e02f00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e6cab7",
      "direction": "in",
      "other": "0x00e6c9f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00ed670b",
      "direction": "in",
      "other": "0x00ed6540",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 4,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0179",
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
      "shared_types:OpaqueRuntimeService,READ,WRITE",
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE8",
    "score": 30,
    "symbol": "ui_layer_manager_get_0067ca90",
    "va": "0x0067ca90"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRuntimeService,READ,WRITE",
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE8",
    "score": 30,
    "symbol": "app_locale_manager_get_0067de00",
    "va": "0x0067de00"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRuntimeService"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 14,
    "symbol": "editor_anim_event_message_post_0059d840",
    "va": "0x0059d840"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRuntimeService"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 14,
    "symbol": "editor_anim_event_message_send_0059d8b0",
    "va": "0x0059d8b0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRuntimeService"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 14,
    "symbol": "app_cheat_manager_get_0067dde0",
    "va": "0x0067dde0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRuntimeService"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_runtime_services_wave8/runtime_services_wave8.cpp",
  "files": [
    "src/reconstruction/pkg_runtime_services_wave8/runtime_services_wave8.cpp",
    "src/reconstruction/pkg_runtime_services_wave8/runtime_services_wave8.hpp",
    "src/reconstruction/pkg_runtime_services_wave8/runtime_services_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-runtime-services-wave8/0067cae0.json"
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
        "0x00587270",
        "0x0059d840",
        "0x0059d8b0",
        "0x00587270",
        "0x0059d8b0",
        "0x0059d840",
        "0x0067cae0",
        "0x00b31da0",
        "0x0059ca70",
        "0x0059cac0",
        "0x00b321e0",
        "0x00b32330",
        "0x00b32560",
        "0x0059cea0",
        "0x0059cf00",
        "0x00b63980"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:3",
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
        "0x00571f80",
        "0x00571f80",
        "0x0067cae0",
        "0x00a20670",
        "0x00571f80",
        "0x00572070",
        "0x00572020",
        "0x0059ca70",
        "0x0059cac0",
        "0x0059cea0",
        "0x0059cf00",
        "0x0067dd90",
        "0x00e66280",
        "0x00e66840",
        "0x00e63560",
        "0x0059c6e0"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.j
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave8/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-runtime-services-wave8/0067cae0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave8/runtime_services_wave8.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave8/runtime_services_wave8.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave8/runtime_services_wave8_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-runtime-services-wave8/0067cae0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_runtime_services_wave8/runtime_services_wave8.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_runtime_services_wave8/runtime_services_wave8.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src
[TRUNCATED]
```
