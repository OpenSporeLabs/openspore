# Reconstruction context 0x006a2f60

- Status: `partial`
- Content SHA-256: `796f5c578e54f527922985ef4bffe4d9b640a0b1e219df6aac7e0b5e24c700d2`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a2f60",
  "phase": "reconstruction",
  "target": "0x006a2f60"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::PropertyList::Read",
  "package": null,
  "subsystem": "App",
  "va": "0x006a2f60"
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
  "content_sha256": "a959d68ce42fdf9f07273dbcf65ddea911f22cfed223ac57504e2e63b4c5810b",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a2f60 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "hidden_this_type": "DirectPropertyList*",
  "return_type": "bool",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "load_site": "0x006a2f65 MOV EBP,dword ptr [ESP + 0x1c]",
      "name": "pInputStream",
      "position": 1,
      "type": "IStream*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4 at 0x006a306a"
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
      "va": "0x006866f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006a3170"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00686ab5",
      "direction": "in",
      "other": "0x006866f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3170",
      "direction": "in",
      "other": "0x006a3170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2fad",
      "direction": "out",
      "other": "0x0067de30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3045",
      "direction": "out",
      "other": "0x00694440",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2ff4",
      "direction": "out",
      "other": "0x006a2b80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2f78",
      "direction": "out",
      "other": "0x0093a780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2fa3",
      "direction": "out",
      "other": "0x0093a780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a302e",
      "direction": "out",
      "other": "0x0093a780",
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
    "DirectPropertyList*",
    "IStream*",
    "bool"
  ],
  "vtables": [
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
      "name": null,
      "reconstructed": false,
      "va": "0x006866f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006a3170"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00686ab5",
      "direction": "in",
      "other": "0x006866f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3170",
      "direction": "in",
      "other": "0x006a3170",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2fad",
      "direction": "out",
      "other": "0x0067de30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a3045",
      "direction": "out",
      "other": "0x00694440",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2ff4",
      "direction": "out",
      "other": "0x006a2b80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2f78",
      "direction": "out",
      "other": "0x0093a780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2fa3",
      "direction": "out",
      "other": "0x0093a780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a302e",
      "direction": "out",
      "other": "0x0093a780",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 2,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {

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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Read.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Read.c",
    "reconstruction/staging/pkg-app-proplist-read-wave17/property_list_read_006a2f60.cpp",
    "reconstruction/staging/pkg-app-proplist-read-wave17/property_list_read_006a2f60.hpp",
    "reconstruction/staging/pkg-app-proplist-read-wave17/property_list_read_006a2f60_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-proplist-read-wave17/006a2f60.json"
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
  "original_bytes": 10563,
  "preview": "{\n  \"conflicts\": {\n    \"original_bytes\": 12946,\n    \"preview\": \"[\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x006a2f60\\\",\\n      \\\"0x006a1540\\\",\\n      \\\"0x00000000\\\",\\n      \\\"0x006a2f60\\\",\\n      \\\"0x00000018\\\",\\n      \\\"0x006a2f60\\\",\\n      \\\"0x006a1540\\\"\\n    ],\\n    \\\"conflict_id\\\": \\\"TB-FL-006\\\",\\n    \\\"kind\\\": \\\"conflict_ledger\\\",\\n    \\\"rejected\\\": [],\\n    \\\"resolution\\\": {\\n      \\\"merge_decision\\\": \\\"do_not_collapse\\\",\\n      \\\"preferred_claim\\\": null,\\n      \\\"preserved_alternatives\\\": true,\\n      \\\"scope_note\\\": \\\"No 4-byte or 0x14-byte layout is a wire contract until the direct reader/writer and stride are observed.\\\",\\n      \\\"status\\\": \\\"preserved_alternatives\\\",\\n      \\\"taxonomy\\\": \\\"preserved_alternatives\\\"\\n    },\\n    \\\"resolution_status\\\": \\\"preserved_alternatives\\\",\\n    \\\"source\\\": \\\"knowledgegraph/research/conflicts/track-b-vtable-fields.json\\\",\\n    \\\"subject\\\": \\\"App::Property 4-byte versus 0x14-byte layout\\\",\\n    \\\"unresolved_reason\\\": \\\"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\\\"\\n  },\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x006a1540\\\",\\n      \\\"0x006a2f60\\\",\\n      \\\"0x00693390\\\",\\n      \\\"0x00694440\\\",\\n      \\\"0x00422e20\\\",\\n      \\\"0x00422eb0\\\",\\n      \\\"0x00422f40\\\",\\n      \\\
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Read.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-app-proplist-read-wave17/006a2f60.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-proplist-read-wave17/property_list_read_006a2f60.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-proplist-read-wave17/property_list_read_006a2f60.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-proplist-read-wave17/property_list_read_006a2f60_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Read.c",
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
      "ref": "reconstruction/metadata/pkg-app-proplist-read-wave17/006a2f60.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-app-proplist-read-wave17/property_list_read_006a2f60.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-app-proplist-read-wave17/property_list_read_006a2f60.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mod
[TRUNCATED]
```
