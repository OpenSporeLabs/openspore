# Reconstruction context 0x00f47930

- Status: `partial`
- Content SHA-256: `ae961e84f385d618d5b725d49e881d201e501eea294dc1ef9f4d001bf05dca5f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00f47930",
  "phase": "reconstruction",
  "target": "0x00f47930"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueFrameRuntime",
  "name": "app_frame_update_00f47930",
  "package": "PKG-FRAME-RUNTIME-WAVE7",
  "subsystem": "Runtime.Frame",
  "va": "0x00f47930"
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
  "content_sha256": "d29b00f77d55b8481d9f603204239296d137a79d8d60116ac2efd3cc30048943",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00f47930 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall with no ordinary stack arguments",
  "ordinary_stack_arguments": [],
  "receiver_register": "ECX",
  "ret_form": "plain RET",
  "return_register": "EAX",
  "return_width_bytes": 0,
  "stack_cleanup_bytes": 0
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f47b10"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00f47bb8",
      "direction": "in",
      "other": "0x00f47b10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f47a45",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f479b3",
      "direction": "out",
      "other": "0x0068f4d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f47a5b",
      "direction": "out",
      "other": "0x00812d30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f47a05",
      "direction": "out",
      "other": "0x00921df0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f479ef",
      "direction": "out",
      "other": "0x00f475b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f47a0f",
      "direction": "out",
      "other": "0x00f475b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f4794d",
      "direction": "out",
      "other": "EXT:KERNEL32.DLL::QueryPerformanceCounter",
      "reference_type": "external"
    }
  ],
  "external_callees": [
    "EXT:KERNEL32.DLL::QueryPerformanceCounter"
  ]
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueFrameRuntime",
    "OpaqueSporeApp*",
    "UNCONDITIONAL_CALL"
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
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0067dcc0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f47b10"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00f47bb8",
      "direction": "in",
      "other": "0x00f47b10",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f47a45",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f479b3",
      "direction": "out",
      "other": "0x0068f4d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f47a5b",
      "direction": "out",
      "other": "0x00812d30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f47a05",
      "direction": "out",
      "other": "0x00921df0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f479ef",
      "direction": "out",
      "other": "0x00f475b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f47a0f",
      "direction": "out",
      "other": "0x00f475b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f4794d",
      "direction": "out",
      "other": "EXT:KERNEL32.DLL::QueryPerformanceCounter",
      "reference_type": "external"
    }
  ],
  "edges_truncated": false,
  "external_callees": [
    "EXT:KERNEL32.DLL::QueryPerformanceCounter"
  ],
  "fan_in": 1,
  "fan_out": 1,
  "manifest
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
      "shared_types:OpaqueFrameRuntime"
    ],
    "package": "PKG-FRAME-RUNTIME-WAVE7",
    "score": 22,
    "symbol": "cell_mode_update_00e80980",
    "va": "0x00e80980"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-FRAME-RUNTIME-WAVE8",
    "score": 6,
    "symbol": "timing_update_body_00b31cc0",
    "va": "0x00b31cc0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-FRAME-RUNTIME-WAVE8",
    "score": 6,
    "symbol": "cell_update_body_00e806b0",
    "va": "0x00e806b0"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005bf9d0",
    "va": "0x005bf9d0"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005c0100",
    "va": "0x005c0100"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005c0380",
    "va": "0x005c0380"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "wave6-resources",
    "score": 3,
    "symbol": "property_list_has_property_006a2470",
    "va": "0x006a2470"
  },
  {
    "match_basis": [
      "shared_types:UNCONDITIONAL_CALL"
    ],
    "package": "wave6-resources",
    "score": 3,
    "symbol": "property_list_get_property_object_006a24d0",
    "va": "0x006a24d0"

[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.cpp",
    "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.hpp",
    "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-frame-runtime-wave7/00f47930.json"
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
        "0x00f47410",
        "0x00f47700",
        "0x00f47ed0",
        "0x00f47700",
        "0x00f47b10",
        "0x00f47b10",
        "0x00f47410",
        "0x00f47700",
        "0x00f47700",
        "0x00f47930",
        "0x00f47930",
        "0x00f47930",
        "0x00f47930",
        "0x00f47b10",
        "0x00f47b10",
        "0x00f47b10"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:0",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
      "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00f47994",
        "0x00f47a14",
        "0x00f47b10",
        "0x00f47930",
        "0x00f47930",
        "0x00f47994",
        "0x00f47a14",
        "0x00f47b10",
        "0x00f47b10",
        "0x00f47994",
        "0x00f47a14",
        "0x00f47994",
        "0x00f47a14"
      ],
      "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:1",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "The committed evidence
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-frame-runtime-wave7/00f47930.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-frame-runtime-wave7/00f47930.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction
[TRUNCATED]
```
