# Reconstruction context 0x007e6130

- Status: `partial`
- Content SHA-256: `c493f1ea945a6e69f58ff634ea114b67acc8f6af138f33435a86aefec7eb7881`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007e6130",
  "phase": "reconstruction",
  "target": "0x007e6130"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": null,
  "va": "0x007e6130"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "b4edbad76d6bec1fe4dc61a0c3c5ecf5779355cf8fd96e4e6febd8c55516818b",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x007e6130 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "interior continuation of the cdecl-shaped 0x007e6100 body; not a standalone call",
  "hidden_receiver": "No public receiver parameter; ECX is comparison state established by 0x007e6100 and is not the SDK this pointer.",
  "ordinary_stack_arguments": [],
  "return_note": "0/1",
  "return_type": "AL"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "ui_layer_manager_get_0067ca90",
      "reconstructed": true,
      "va": "0x0067ca90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x007e617d",
      "direction": "out",
      "other": "0x0067ca90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e6190",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e61c8",
      "direction": "out",
      "other": "0x0067cb00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e61c0",
      "direction": "out",
      "other": "0x0067cb20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e61e0",
      "direction": "out",
      "other": "0x0067cb50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e61e8",
      "direction": "out",
      "other": "0x0067cb60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e61f0",
      "direction": "out",
      "other": "0x0067cb70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e61f8",
      "direction": "out",
      "other": "0x0067cb80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e6188",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e6198",
      "direction": "out",
      "other": "0x0067dd10",
      "r
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:0x01413874 contains GetAppPluginServices and 0x0153f864 is the first-match output constant."
  ],
  "types": [
    "AL 0/1",
    "AL 0/1 on the interior exit paths",
    "CONDITIONAL_JUMP"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
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
      "name": "ui_layer_manager_get_0067ca90",
      "reconstructed": true,
      "va": "0x0067ca90"
    },
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
      "callsite": "0x007e617d",
      "direction": "out",
      "other": "0x0067ca90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e6190",
      "direction": "out",
      "other": "0x0067caa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e61c8",
      "direction": "out",
      "other": "0x0067cb00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e61c0",
      "direction": "out",
      "other": "0x0067cb20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e61e0",
      "direction": "out",
      "other": "0x0067cb50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e61e8",
      "direction": "out",
      "other": "0x0067cb60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e61f0",
      "direction": "out",
      "other": "0x0067cb70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e61f8",
      "direction": "out",
      "other": "0x0067cb80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x007e6188",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "cal
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE8",
    "score": 3,
    "symbol": "ui_layer_manager_get_0067ca90",
    "va": "0x0067ca90"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp",
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.hpp",
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-lifecycle-wave7/007e6130.json"
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
    "Concrete caller and receiver state for the inherited continuation",
    "Concrete owners and return values of all 16 service ports",
    "Meaning and lifetime of the output words"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-app-lifecycle-wave7/007e6130.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-app-lifecycle-wave7/007e6130.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowled
[TRUNCATED]
```
