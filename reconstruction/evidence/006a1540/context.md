# Reconstruction context 0x006a1540

- Status: `partial`
- Content SHA-256: `7cfe3a9682e1cc9450b9c2a7ecd5a59a716e8a7f0089e59c0a8d1bea53d38f84`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a1540",
  "phase": "reconstruction",
  "target": "0x006a1540"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::PropertyList::Write",
  "package": "pkg-dfw-006a1540",
  "subsystem": "App",
  "va": "0x006a1540"
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
  "content_sha256": "a4a98ff51009a9a178b1301b963669b2e81fa90ef221dcfc2473ff7c070ed541",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a1540 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    "{'entry_offset': 'entry_ESP+0x4', 'observed': True, 'ordinal': 1, 'read': True, 'read_at': '0x006a1543 MOV EBP,dword ptr [ESP + 0x10] (three pushes precede it, so [ESP+0x10] is entry_ESP+0x4)', 'role': 'an IStream-shaped sink. The body never dereferences it; it is only ever pushed as the first argument of the three direct calls (0x006a156a, 0x006a15b3, 0x006a15cf).', 'sizes': [4], 'written': False}"
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "saved_registers": [
    "ESI",
    "EBP",
    "EBX",
    "EDI"
  ],
  "stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x4",
      "ordinal": 1,
      "read": true,
      "read_at": "0x006a1543 MOV EBP,dword ptr [ESP + 0x10]",
      "role": "an IStream-shaped sink. Never dereferenced by this body; pushed only as the first argument of the three direct calls (0x006a156a, 0x006a15b3, 0x006a15cf). The live Ghidra signature types it IStream *, which is recorded here and not adopted: no record for this target establishes that class.",
      "written": false
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
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
      "callsite": "0x006a15d0",
      "direction": "out",
      "other": "0x00693390",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a156f",
      "direction": "out",
      "other": "0x0093aa70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a15b8",
      "direction": "out",
      "other": "0x0093aa70",
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
    "global:PASS. The complete listing names no data-segment address and the span names none.",
    "global:none: the complete 74-instruction listing names no data-segment address."
  ],
  "types": [
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006a15d0",
      "direction": "out",
      "other": "0x00693390",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a156f",
      "direction": "out",
      "other": "0x0093aa70",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a15b8",
      "direction": "out",
      "other": "0x0093aa70",
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
    "id": "scc-0200",
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
      "shared_vtable:vtable:0x01408820",
      "same_calling_convention"
    ],
    "package": "pkg-app-proplist-copyall-wave16",
    "score": 12,
    "symbol": "all_copy_from_properties_006a14d0",
    "va": "0x006a14d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408820",
      "same_calling_convention"
    ],
    "package": "pkg-proplist-dispatch-wave14",
    "score": 12,
    "symbol": "app_property_list_add_all_properties_from_006a1510",
    "va": "0x006a1510"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408820",
      "same_calling_convention"
    ],
    "package": "pkg-property-clear-wave13",
    "score": 12,
    "symbol": "property_list_clear_006a2a80",
    "va": "0x006a2a80"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408820",
      "same_calling_convention"
    ],
    "package": "pkg-property-remove-006a2ef0",
    "score": 12,
    "symbol": "property_list_remove_property_006a2ef0",
    "va": "0x006a2ef0"
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
      "same_calling_convention"
    ],
    "package": "pkg-cheat-dispatch-0067e6f0",
    "score": 8,
    "symbol": "cCheatManager_func40h_0067e6f0",
    "va": "0x0067e6f0"
  },
  {
    "match_basis": [
      "same_subsystem",
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Write.c",
  "file": "src/reconstruction/pkg_dfw_006a1540/dfw_006a1540.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Write.c",
    "reconstruction/staging/pkg-dfw-006a1540/dfw_006a1540.cpp",
    "reconstruction/staging/pkg-dfw-006a1540/dfw_006a1540_types.hpp",
    "reconstruction/staging/pkg-proplist-write-wave16/proplist_write_006a1540.cpp",
    "reconstruction/staging/pkg-proplist-write-wave16/proplist_write_006a1540.hpp",
    "reconstruction/staging/pkg-proplist-write-wave16/proplist_write_006a1540_model_test.cpp",
    "src/reconstruction/pkg_dfw_006a1540/dfw_006a1540.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-006a1540/006a1540.json",
    "reconstruction/metadata/pkg-proplist-write-wave16/006a1540.json"
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
  "original_bytes": 15962,
  "preview": "{\n  \"conflicts\": {\n    \"original_bytes\": 12946,\n    \"preview\": \"[\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x006a2f60\\\",\\n      \\\"0x006a1540\\\",\\n      \\\"0x00000000\\\",\\n      \\\"0x006a2f60\\\",\\n      \\\"0x00000018\\\",\\n      \\\"0x006a2f60\\\",\\n      \\\"0x006a1540\\\"\\n    ],\\n    \\\"conflict_id\\\": \\\"TB-FL-006\\\",\\n    \\\"kind\\\": \\\"conflict_ledger\\\",\\n    \\\"rejected\\\": [],\\n    \\\"resolution\\\": {\\n      \\\"merge_decision\\\": \\\"do_not_collapse\\\",\\n      \\\"preferred_claim\\\": null,\\n      \\\"preserved_alternatives\\\": true,\\n      \\\"scope_note\\\": \\\"No 4-byte or 0x14-byte layout is a wire contract until the direct reader/writer and stride are observed.\\\",\\n      \\\"status\\\": \\\"preserved_alternatives\\\",\\n      \\\"taxonomy\\\": \\\"preserved_alternatives\\\"\\n    },\\n    \\\"resolution_status\\\": \\\"preserved_alternatives\\\",\\n    \\\"source\\\": \\\"knowledgegraph/research/conflicts/track-b-vtable-fields.json\\\",\\n    \\\"subject\\\": \\\"App::Property 4-byte versus 0x14-byte layout\\\",\\n    \\\"unresolved_reason\\\": \\\"The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available.\\\"\\n  },\\n  {\\n    \\\"anchors\\\": [\\n      \\\"0x006a1540\\\",\\n      \\\"0x006a2f60\\\",\\n      \\\"0x00693390\\\",\\n      \\\"0x00694440\\\",\\n      \\\"0x00422e20\\\",\\n      \\\"0x00422eb0\\\",\\n      \\\"0x00422f40\\\",\\n      \\\
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Write.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-006a1540/006a1540.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-proplist-write-wave16/006a1540.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-006a1540/dfw_006a1540.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-006a1540/dfw_006a1540_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-proplist-write-wave16/proplist_write_006a1540.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-proplist-write-wave16/proplist_write_006a1540.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-proplist-write-wave16/proplist_write_006a1540_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_dfw_006a1540/dfw_006a1540.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__Write.c",
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
      "ref": "reconstruction/metadata/pkg-dfw-006a1540/006a1540.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-proplist-write-wave16/006a1540.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dfw-006a1540/dfw_006a1540.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-
[TRUNCATED]
```
