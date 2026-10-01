# Reconstruction context 0x0059d8b0

- Status: `partial`
- Content SHA-256: `8c0f26df69ff38492ff4e846bf8a0b179ff69031059c9a52b1aaa29e752986e6`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0059d8b0",
  "phase": "reconstruction",
  "target": "0x0059d8b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueRuntimeService",
  "name": "editor_anim_event_message_send_0059d8b0",
  "package": "PKG-RUNTIME-SERVICES-WAVE7",
  "subsystem": "Runtime.Services",
  "va": "0x0059d8b0"
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
  "content_sha256": "1957ce3b697821b6ed2b4b9505cf281a31450b9566b1f16df7a8aabd2a940a01",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0059d8b0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "ECX = OpaqueEditorAnimEvent*",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "event_id",
      "position": 1,
      "type": "TargetWord"
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "secondary_id",
      "position": 2,
      "type": "TargetWord"
    },
    {
      "entry_offset": "ESP+0x0c",
      "name": "editor_model",
      "position": 3,
      "type": "OpaqueEditorModel*"
    },
    {
      "entry_offset": "ESP+0x10",
      "name": "argument_5",
      "position": 4,
      "type": "TargetWord"
    },
    {
      "entry_offset": "ESP+0x14",
      "name": "flag_6",
      "position": 5,
      "type": "bool"
    },
    {
      "entry_offset": "ESP+0x18",
      "name": "value_7",
      "position": 6,
      "type": "float"
    },
    {
      "entry_offset": "ESP+0x1c",
      "name": "flag_8",
      "position": 7,
      "type": "bool"
    },
    {
      "entry_offset": "ESP+0x20",
      "name": "argument_9",
      "position": 8,
      "type": "TargetWord"
    },
    {
      "entry_offset": "ESP+0x24",
      "name": "value_10",
      "position": 9,
      "type": "float"
    }
  ],
  "return_register": null,
  "return_type": "void",
  "return_width_bytes": 0,
  "stack_cleanup_bytes": 36,
  "termination": "RET 0x24"
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
      "va": "0x00587270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00591690"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b1e30"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00587930",
      "direction": "in",
      "other": "0x00587270",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005879cc",
      "direction": "in",
      "other": "0x00587270",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00591cce",
      "direction": "in",
      "other": "0x00591690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00592a73",
      "direction": "in",
      "other": "0x00591fa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005b2111",
      "direction": "in",
      "other": "0x005b1e30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059d8b3",
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
    "OpaqueEditorModel*",
    "OpaqueRuntimeService",
    "TargetWord",
    "bool",
    "float",
    "void"
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
      "va": "0x00587270"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00591690"
    },
    {
      "name": "Editors::cEditor::HandleMessage",
      "reconstructed": false,
      "va": "0x00591fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b1e30"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00587930",
      "direction": "in",
      "other": "0x00587270",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005879cc",
      "direction": "in",
      "other": "0x00587270",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00591cce",
      "direction": "in",
      "other": "0x00591690",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00592a73",
      "direction": "in",
      "other": "0x00591fa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005b2111",
      "direction": "in",
      "other": "0x005b1e30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0059d8b3",
      "direction": "out",
      "other": "0x0067dcc0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 4,
  "fan_out": 1,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed":
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
      "shared_types:OpaqueEditorModel*,OpaqueRuntimeService,TargetWord",
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 30,
    "symbol": "editor_anim_event_message_post_0059d840",
    "va": "0x0059d840"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "same_class",
      "shared_types:OpaqueRuntimeService,TargetWord",
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 27,
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
      "shared_types:OpaqueRuntimeService",
      "same_calling_convention"
    ],
    "package": "PKG-RUNTIME-SERVICES-WAVE7",
    "score": 24,
    "symbol": "app_canvas_get_message_server_00c871d0",
    "va": "0x00c871d0"
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
    "va": "
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
    "reconstruction/metadata/pkg-runtime-services-wave7/0059d8b0.json"
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
        "0x00573970",
        "0x00573970",
        "0x00586410",
        "0x00586410",
        "0x00587270",
        "0x00587270",
        "0x0059d840",
        "0x0059d840",
        "0x0059d8b0",
        "0x0059d8b0"
      ],
      "conflict_id": "Q-ANIMATION-DISPATCH",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "Editor animation Send/Post surfaces and the editor mode producer are concrete. The final AnimatedCreature/IAnimWorld consumer and pose ordering are unresolved.",
      "resolution_status": "Editor animation Send/Post surfaces and the editor mode producer are concrete. The final AnimatedCreature/IAnimWorld consumer and pose ordering are unresolved.",
      "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
      "subject": null,
      "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
    },
    {
      "anchors": [
        "0x00591fa0",
        "0x00883a90",
        "0x00883ad0",
        "0x00883ad0",
        "0x00883a90",
        "0x00591fa0",
        "0x00573970",
        "0x00573970",
        "0x00586410",
        "0x00586410",
        "0x00587270",
        "0x00587270",
        "0x0059d840",
        "0x0059d840",
        "0x0059d8b0",
        "0x0059d8b0"
      ],
      "conflict_id": "Q-EDITOR-MESSAGE-CATALOG",
      "kind": "conflict_ledger",
      "rejected": [],
      "re
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave7/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-runtime-services-wave7/0059d8b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-runtime-services-wave7/0059d8b0.json",
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
