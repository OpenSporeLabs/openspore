# Reconstruction context 0x006a2ad0

- Status: `partial`
- Content SHA-256: `c4a6a2a1aaa96a75032c9dc1ff5337a7eae3f71e566673e8f32881566a4441b0`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a2ad0",
  "phase": "reconstruction",
  "target": "0x006a2ad0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::DirectPropertyList::CopyFrom",
  "package": "pkg-direct-property-copyfrom-wave14",
  "subsystem": "App",
  "va": "0x006a2ad0"
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
  "content_sha256": "b15e35e5c91141036babdea74291b39015d0026aee642e877d07f3e588366523",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a2ad0 failed: Decompilation did not complete. Reason: ",
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
    {
      "entry_offset": "entry_ESP+0x4",
      "note": "read once into EBX and then reused as the source-list pointer; it is compared against the receiver, addressed at +0x18 and +0x1c, and never written through",
      "observed": true,
      "ordinal": 1,
      "read": "MOV EBX,dword ptr [ESP + 0x8] at 0x006a2ad1, after PUSH EBX",
      "size_bytes": 4
    }
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "EDI",
    "ESI"
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
      "callsite": "0x006a2b0d",
      "direction": "out",
      "other": "0x006a1710",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2ae0",
      "direction": "out",
      "other": "0x006a28f0",
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
    "void"
  ],
  "vtables": [
    "vtable:0x01408870"
  ]
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
      "No original-process trace exists in this repository, so nothing about this body's runtime behaviour is validated: the slot target, the resize contract of 0x006a28f0 and the parent publication at displacement 0x30 are static claims only."
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006a2b0d",
      "direction": "out",
      "other": "0x006a1710",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2ae0",
      "direction": "out",
      "other": "0x006a28f0",
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
    "id": "scc-0213",
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
      "shared_vtable:vtable:0x01408870",
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
      "shared_vtable:vtable:0x01408870",
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
      "shared_vtable:vtable:0x01408870",
      "same_calling_convention"
    ],
    "package": "pkg-direct-property-clear-wave14",
    "score": 12,
    "symbol": "direct_property_list_clear_006a2b20",
    "va": "0x006a2b20"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408870",
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
      "same_calling_convention"
    ],
    "package": "cheat-func44h-0067e730",
    "score": 8,
    "symbol": "func44h_0067e730",
    "va": "0x0067e730"
  },
  {
    "match_basis": [
      "same_subsystem
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__CopyFrom.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__CopyFrom.c",
    "reconstruction/staging/pkg-direct-property-copyfrom-wave14/direct_property_list_copyfrom_006a2ad0.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-direct-property-copyfrom-wave14/006a2ad0.json"
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
    "Is the derived ABI record's inability to classify the last EAX write (return.register_class aggregate_unknown) a real second return value, or only EAX being live across the indirect call? The void claim rests on the decompiler and on the exit paths, not on the derived record.",
    "Is the receiver's word at displacement 0x0 really a vtable pointer, and if so which slot index does displacement 0x14 correspond to in vtable:0x01408870? The association and the single xref from 0x0140889c support it, but the derived ABI record's vtable_shaped_loads count is 0, so the reading is INFERRED.",
    "No original-process trace exists in this repository, so nothing about this body's runtime behaviour is validated: the slot target, the resize contract of 0x006a28f0 and the parent publication at displacement 0x30 are static claims only.",
    "The derived ABI record abstained on flow ('the linear ESP walk ends at +12'), and the derived record's calling-convention confidence is INFERRED rather than proven; no live cross-validation of the convention exists in this repository.",
    "The machine-derived receiver record for this body is bounds_only and enumerates 0x0 and 0x30. bounds_only means it states where the body was SEEN REACHING and nothing more: it is an observation of the inference's own access, not an enumeration of the receiver's words, and it is not a statement about the object. This body addresses receiver displacement 0x18 (LEA ECX,[EDI + 0x18] at 0x006a2add) and the record does not list it, so 0x18 is UNCORROBORATED BY the
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__CopyFrom.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-direct-property-copyfrom-wave14/006a2ad0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-direct-property-copyfrom-wave14/direct_property_list_copyfrom_006a2ad0.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__CopyFrom.c",
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
      "ref": "reconstruction/metadata/pkg-direct-property-copyfrom-wave14/006a2ad0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-direct-property-copyfrom-wave14/direct_property_list_copyfrom_006a2ad0.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__CopyFrom.c"
  ],
  "req
[TRUNCATED]
```
