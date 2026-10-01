# Reconstruction context 0x006a2e20

- Status: `partial`
- Content SHA-256: `72c23a68a73a8765e8bab3f9dab64bba83ee3238b36f171fd3521caad6e3bb26`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a2e20",
  "phase": "reconstruction",
  "target": "0x006a2e20"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::PropertyList::SetProperty",
  "package": "pkg-dfw-006a2e20",
  "subsystem": "App",
  "va": "0x006a2e20"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "7382047a39c1498ddd5c2dd960365ae3f8daf18a58b87210bd7ba95a12731c37",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a2e20 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": [
    "__thiscall",
    "x86-32 thiscall; receiver in ECX, caller cleanup"
  ],
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_register": "EAX",
  "return_semantics": "void. The receiver is copied into EDI at 0x006a2e3b and is never moved back into EAX on any path; the epilogue restores the exception frame and returns. EAX is therefore scratch on every exit, and the only value the function produces is its effect on the receiver's map and its counter at +0x34.",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": [
    "callee",
    "caller"
  ],
  "termination": "RET 0x8"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "editor_query_clear_flags_0093db80",
      "reconstructed": true,
      "va": "0x0093db80"
    }
  ],
  "callers": [
    {
      "name": "opaque_list_set_property_006a30c0",
      "reconstructed": true,
      "va": "0x006a30c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bed460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bed920"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x006a3162",
      "direction": "in",
      "other": "0x006a30c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bed826",
      "direction": "in",
      "other": "0x00bed460",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00beda96",
      "direction": "in",
      "other": "0x00bed920",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2e7c",
      "direction": "out",
      "other": "0x00542b80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2e99",
      "direction": "out",
      "other": "0x00542b80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2e52",
      "direction": "out",
      "other": "0x00612db0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2eb2",
      "direction": "out",
      "other": "0x006a2c50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2ecc",
      "direction": "out",
      "other": "0x0093db80",
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
    "global:PASS",
    "global:the complete 65-instruction listing names no data-segment address and the source span names none"
  ],
  "types": [
    "openspore::reconstruction::pkg_proplist_setprop_w15::MapEntry",
    "openspore::reconstruction::pkg_proplist_setprop_w15::MapLookup",
    "openspore::reconstruction::pkg_proplist_setprop_w15::Property",
    "openspore::reconstruction::pkg_proplist_setprop_w15::PropertyList",
    "openspore::reconstruction::pkg_proplist_setprop_w15::PropertyMap",
    "void"
  ],
  "vtables": [
    "vtable:0x006a2470",
    "vtable:0x01408820"
  ]
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
      "name": "editor_query_clear_flags_0093db80",
      "reconstructed": true,
      "va": "0x0093db80"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": "opaque_list_set_property_006a30c0",
      "reconstructed": true,
      "va": "0x006a30c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bed460"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bed920"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006a3162",
      "direction": "in",
      "other": "0x006a30c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00bed826",
      "direction": "in",
      "other": "0x00bed460",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00beda96",
      "direction": "in",
      "other": "0x00bed920",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2e7c",
      "direction": "out",
      "other": "0x00542b80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2e99",
      "direction": "out",
      "other": "0x00542b80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2e52",
      "direction": "out",
      "other": "0x00612db0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2eb2",
      "direction": "out",
      "other": "0x006a2c50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2ecc",
      "direction": "out",
      "other": "0x0
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
      "shared_vtable:vtable:0x01408820"
    ],
    "package": "pkg-app-proplist-copyall-wave16",
    "score": 10,
    "symbol": "all_copy_from_properties_006a14d0",
    "va": "0x006a14d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408820"
    ],
    "package": "pkg-proplist-dispatch-wave14",
    "score": 10,
    "symbol": "app_property_list_add_all_properties_from_006a1510",
    "va": "0x006a1510"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408820"
    ],
    "package": "pkg-dfw-006a1540",
    "score": 10,
    "symbol": "proplist_write_006a1540",
    "va": "0x006a1540"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408820"
    ],
    "package": "pkg-property-clear-wave13",
    "score": 10,
    "symbol": "property_list_clear_006a2a80",
    "va": "0x006a2a80"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408820"
    ],
    "package": "pkg-property-remove-006a2ef0",
    "score": 10,
    "symbol": "property_list_remove_property_006a2ef0",
    "va": "0x006a2ef0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-cheat-dispatch-0067e6f0",
    "score": 6,
    "symbol": "cCheatManager_func40h_0067e6f0",
    "va": "0x0067e6f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "cheat-func44h-0067e730",
    "score": 6,
    "symbol": "func44h_0067e730",
    "va": "0x0067e730"
  },
  {
    "match_basis": [
      "same_subs
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__SetProperty.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__SetProperty.c",
    "reconstruction/staging/pkg-dfw-006a2e20/dfw_006a2e20.cpp",
    "reconstruction/staging/pkg-dfw-006a2e20/dfw_006a2e20_model_test.cpp",
    "reconstruction/staging/pkg-dfw-006a2e20/dfw_006a2e20_types.hpp",
    "reconstruction/staging/pkg-proplist-setprop-w15/property_set_006a2e20.cpp",
    "reconstruction/staging/pkg-proplist-setprop-w15/property_set_006a2e20.hpp",
    "reconstruction/staging/pkg-proplist-setprop-w15/property_set_006a2e20_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-006a2e20/006a2e20.json",
    "reconstruction/metadata/pkg-proplist-setprop-w15/006a2e20.json"
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
        "0x006a1540",
        "0x006a2f60",
        "0x006a2e20",
        "0x006a2530",
        "0x006a2b80",
        "0x006a2c50",
        "0x00694440",
        "0x006a1540",
        "0x006a1540",
        "0x006a154a",
        "0x006a15f3",
        "0x006a2f60",
        "0x006a2f60",
        "0x006a2f78",
        "0x006a2fe9",
        "0x006a2f60"
      ],
      "conflict_id": "TD-DATA-003",
      "kind": "conflict_ledger",
      "rejected": [
        {
          "path": "competing_hypotheses.1.claim",
          "status": "rejected_for_current_read_write_bodies     ",
          "text": "PropertyList Write serializes the entire recursive parent graph as ordinary local entries."
        }
      ],
      "resolution": null,
      "resolution_status": null,
      "source": "knowledgegraph/research/conflicts/track-d-data-serialization.json",
      "subject": "PropertyList local transfer, parent reference, and PROP framing",
      "unresolved_reason": [
        "The exact three-word parent identity and its manager-side construction are not fully identified.",
        "Outer record envelope, version negotiation, compression, and atomic rollback are not established by the selected bodies."
      ]
    },
    {
      "anchors": [
        "0x006a1540",
        "0x006a2f60",
        "0x006a1540",
        "0x013c7d90",
        "0x013c7d90",
        "0x006a1540",
        "0x006a1540",
        "0x006a1540",
        "0x006a1640",
        "0x006a1640",
        "0x006a2530",
        "0x006a2530",
        "0x006a2e20",
        "0x006a2e20",
      
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__SetProperty.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-006a2e20/006a2e20.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-proplist-setprop-w15/006a2e20.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-006a2e20/dfw_006a2e20.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-006a2e20/dfw_006a2e20_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-006a2e20/dfw_006a2e20_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-proplist-setprop-w15/property_set_006a2e20.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-proplist-setprop-w15/property_set_006a2e20.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-proplist-setprop-w15/property_set_006a2e20_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__SetProperty.c",
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
      "ref": "reconstruction/metadata/pkg-dfw-006a2e20/006a2e20.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-proplist-setprop-w15/006a2e20.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dfw-006a2e20/dfw_006a2e20.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging
[TRUNCATED]
```
