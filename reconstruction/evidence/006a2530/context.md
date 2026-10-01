# Reconstruction context 0x006a2530

- Status: `partial`
- Content SHA-256: `10ad17d6d55dab64f96ab85dafffe86f1f5df23d988901c4eb4ca734ee008c1d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a2530",
  "phase": "reconstruction",
  "target": "0x006a2530"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::PropertyList::GetProperty",
  "package": null,
  "subsystem": "App",
  "va": "0x006a2530"
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
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "6c2e468b2f0baf6f2811c9e881a09a69677dfbe686e39ddcb86f4e77342fd956",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a2530 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall (receiver in ECX; the SDK prototype's first parameter is named `this`)",
  "hidden_receiver": "ECX = the parent pointer loaded from receiver+0x30 at 0x006a2577",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "ordinary_stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x04",
      "observed": true,
      "ordinal": 1,
      "read": true,
      "read_at": "0x006a254b MOV EDX,dword ptr [ESP + 0x1c] (ESP is entry_ESP-0x18 there), re-used as the comparison operand at 0x006a2556 and as the second push at 0x006a2585",
      "role": "propertyID, the 32-bit key searched for; also the &key pointer target handed to the lower-bound helper at 0x006a253f LEA ECX,[ESP + 0x10] which is entry_ESP+0x04",
      "sizes": [
        4
      ],
      "written": false
    },
    {
      "entry_offset": "entry_ESP+0x08",
      "observed": true,
      "ordinal": 2,
      "read": true,
      "read_at": "0x006a2567 MOV ECX,dword ptr [ESP + 0x10] (ESP is entry_ESP-0x08 there) and 0x006a257e MOV ESI,dword ptr [ESP + 0x10] on the parent path",
      "role": "Property** out parameter; receives the ADDRESS of the matched pair's value half (entry+0x04)",
      "sizes": [
        4
      ],
      "written": true,
      "written_at": "0x006a256f MOV dword ptr [ECX],EAX, and only there"
    }
  ],
  "ret_form": "RET 0x8 at all three return sites",
  "return_register": "EAX",
  "return_type": "bool",
  "stack_arguments": [
    "propertyID (pushed first, 0x006a2585)",
    "out pointer (pus
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [
    {
      "name": "opaque_list_get_property_006a28c0",
      "reconstructed": true,
      "va": "0x006a28c0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x006a28e0",
      "direction": "in",
      "other": "0x006a28c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2546",
      "direction": "out",
      "other": "0x00612db0",
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
    "bool"
  ],
  "vtables": [
    "vtable:0x00000024",
    "vtable:0x0000004c",
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
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": "opaque_list_get_property_006a28c0",
      "reconstructed": true,
      "va": "0x006a28c0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006a28e0",
      "direction": "in",
      "other": "0x006a28c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2546",
      "direction": "out",
      "other": "0x00612db0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x006a28c0"
  ],
  "scc": {
    "id": "scc-0206",
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
    "package": "pkg-dfw-006a2e20",
    "score": 10,
    "symbol": "dfw_property_set_006a2e20",
    "va": "0x006a2e20"
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
 
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetProperty.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetProperty.c",
    "reconstruction/staging/pkg-app-property-get-wave15/property_list_get_property_006a2530.cpp",
    "reconstruction/staging/pkg-app-property-get-wave15/property_list_get_property_006a2530.hpp",
    "reconstruction/staging/pkg-app-property-get-wave15/property_list_get_property_006a2530_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-property-get-wave15/006a2530.json"
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
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetProperty.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-app-property-get-wave15/006a2530.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-property-get-wave15/property_list_get_property_006a2530.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-property-get-wave15/property_list_get_property_006a2530.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-property-get-wave15/property_list_get_property_006a2530_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetProperty.c",
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
      "ref": "reconstruction/metadata/pkg-app-property-get-wave15/006a2530.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-app-property-get-wave15/property_list_get_property_006a2530.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-app-property-get-wave15/property_list_get_property_006a2530.hpp",
      "source_class": "committed_artifact"
   
[TRUNCATED]
```
