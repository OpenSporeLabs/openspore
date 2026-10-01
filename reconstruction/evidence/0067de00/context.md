# Reconstruction context 0x0067de00

- Status: `partial`
- Content SHA-256: `2113ae4004f7a5f7395db42361d13f0e89105cb6b0f2192a82b75a7ca9b77899`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0067de00",
  "phase": "reconstruction",
  "target": "0x0067de00"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueRuntimeService",
  "name": "app_locale_manager_get_0067de00",
  "package": "PKG-RUNTIME-SERVICES-WAVE8",
  "subsystem": "Runtime.Services",
  "va": "0x0067de00"
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
  "content_sha256": "5e31c168d62645a93c9d18f419d794e50174e3498d054ae712b5795d7abfede8",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0067de00 failed: Decompilation did not complete. Reason: ",
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
  "return_note": "opaque 32-bit locale-service pointer",
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
      "va": "0x007d7d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007e9db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008143a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2f7e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b35300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b35860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b84270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cc8940"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccdd70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd9da0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cfbc10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d43e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e55080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00eb2c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fbe4f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fbf570"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x007d7d75",
      "direction": "in",
      "other": "0x007d7d70",
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
    "global:0x015fd8f4"
  ],
  "types": [
    "OpaqueRuntimeService",
    "READ",
    "WRITE",
    "opaque 32-bit locale-service pointer"
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
      "va": "0x007d7d70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007e9db0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008143a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b2f7e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b35300"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b35860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b84270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cc8940"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccdd70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cd9da0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00cfbc10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d43e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e55080"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00eb2c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fbe4f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fbf570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fc6950"
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
    "symbol": "anim_manager_get_0067cae0",
    "va": "0x0067cae0"
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
    "score"
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
    "reconstruction/metadata/pkg-runtime-services-wave8/0067de00.json"
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
    "concrete runtime owners and values remain unresolved",
    "required"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave8/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-runtime-services-wave8/0067de00.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave8/runtime_services_wave8.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave8/runtime_services_wave8.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave8/runtime_services_wave8_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-runtime-services-wave8/0067de00.json",
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
