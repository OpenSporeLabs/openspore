# Reconstruction context 0x0041dc10

- Status: `partial`
- Content SHA-256: `917e85aa0a25ba154828267b38b381a208267facbf84ef1daf2e430246170c51`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0041dc10",
  "phase": "reconstruction",
  "target": "0x0041dc10"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueVector3",
  "name": "vector3_add_0041dc10",
  "package": "PKG-APP-SAFE-WAVE10",
  "subsystem": "App.Math",
  "va": "0x0041dc10"
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
  "content_sha256": "fcd14989b746a88aa6da3387078a4f6ff87ce6ddda1149b3b31a8226a0a9c6db",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0041dc10 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "cdecl, caller stack cleanup",
  "hidden_this_register": null,
  "receiver_register": null,
  "ret_form": "RET",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x08",
      "machine_type": "OpaqueVector3*",
      "native_reads": [
        "MOV EAX,[EBP + 0x8] at 0x0041dc71 and 0x0041dc97"
      ],
      "normalized_name": "destination",
      "position": 1,
      "width_bytes": 4
    },
    {
      "entry_offset": "EBP+0x0c",
      "machine_type": "const OpaqueVector3*",
      "native_reads": [
        "MOVSS XMM0,[EAX]",
        "MOVSS XMM0,[EDX+0x4]",
        "MOVSS XMM0,[ECX+0x8]"
      ],
      "normalized_name": "left",
      "position": 2,
      "width_bytes": 4
    },
    {
      "entry_offset": "EBP+0x10",
      "machine_type": "const OpaqueVector3*",
      "native_reads": [
        "ADDSS XMM0,[ECX]",
        "ADDSS XMM0,[EAX+0x4]",
        "ADDSS XMM0,[EDX+0x8]"
      ],
      "normalized_name": "right",
      "position": 3,
      "width_bytes": 4
    }
  ],
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
      "va": "0x004099b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00409b90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00409dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00412900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00413cc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004224b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004364a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00436d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004381e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043d690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00440520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00441440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00448fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044a0e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044ad00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044c690"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00409a79",
      "direction": "in",
      "other": "0x004099b0",
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
    "OpaqueVector3",
    "OpaqueVector3*",
    "const OpaqueVector3*"
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
      "Aliasing between destination and either source is not guarded and is covered only by the model test.",
      "Floating point addition follows the default SSE rounding mode; no rounding-mode manipulation is observed.",
      "No original-process invocation was captured.",
      "The modelled receiver is only 0x0c bytes wide, so any wider use of the same object is outside this target.",
      "floating point addition follows the default x87/SSE rounding mode; no SSE rounding-mode manipulation is observed",
      "gate-vector3-add-runtime-rounding-and-aliasing",
      "runtime validation not performed; static decompilation and disassembly only",
      "the native body is a leaf, so no dependency port is required and none was introduced",
      "the receiver struct is only 0x0c bytes wide here, so any wider use of the same object is outside this target"
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
      "va": "0x004099b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00409b90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00409dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00412900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00413cc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004224b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004364a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00436d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004381e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043d690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00440520"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00441440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00448fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044a0e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044ad00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044c690"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0044d9e0"
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
      "same_package"
    ],
    "package": "PKG-APP-SAFE-WAVE10",
    "score": 8,
    "symbol": "cursor_buffer_emit_0041e8b0",
    "va": "0x0041e8b0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-APP-SAFE-WAVE10",
    "score": 8,
    "symbol": "property_value_resolve_0041e920",
    "va": "0x0041e920"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp",
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.hpp",
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-safe-wave10/0041dc10.json"
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
    "Aliasing between destination and either source is not guarded and is covered only by the model test.",
    "Floating point addition follows the default SSE rounding mode; no rounding-mode manipulation is observed.",
    "No original-process invocation was captured.",
    "The modelled receiver is only 0x0c bytes wide, so any wider use of the same object is outside this target.",
    "Whether any caller depends on the intermediate staging of the three sums",
    "Whether callers rely on the returned pointer or only on the side effect",
    "Whether destination is guaranteed distinct from the two sources in real callers",
    "Which namespace the 0x0c-byte vector type belongs to",
    "floating point addition follows the default x87/SSE rounding mode; no SSE rounding-mode manipulation is observed",
    "gate-vector3-add-runtime-rounding-and-aliasing",
    "runtime validation not performed; static decompilation and disassembly only",
    "the native body is a leaf, so no dependency port is required and none was introduced",
    "the receiver struct is only 0x0c bytes wide here, so any wider use of the same object is outside this target"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-app-safe-wave10/0041dc10.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_safe_wave10/app_safe_wave10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-app-safe-wave10/0041dc10.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_app_
[TRUNCATED]
```
