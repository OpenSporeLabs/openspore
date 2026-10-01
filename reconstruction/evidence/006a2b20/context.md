# Reconstruction context 0x006a2b20

- Status: `partial`
- Content SHA-256: `4fab417a58d0a41e3426acc8a5d89fdc77b8ae49d61b3796336c4a9cb2a082bb`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a2b20",
  "phase": "reconstruction",
  "target": "0x006a2b20"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::DirectPropertyList::Clear",
  "package": "pkg-direct-property-clear-wave14",
  "subsystem": "App",
  "va": "0x006a2b20"
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
  "content_sha256": "32e4f470bfede7a2bbba3cf7ed8747bbbfbd52d5e5d4d82702cd9f218cebdaad",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a2b20 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX",
  "ordinary_stack_arguments": [],
  "ret_form": "RET",
  "return_register": "none",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
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
      "callsite": "0x006a2b40",
      "direction": "out",
      "other": "0x00612b20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2b4f",
      "direction": "out",
      "other": "0x00685a30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2b2f",
      "direction": "out",
      "other": "0x0092cb00",
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
    "DirectPropertyList",
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
      "No original-process invocation and no indirect-caller trace were captured for 0x006a2b20, so the reachability of this body through the shared vtable 0x01408870, and the real values held at receiver+0x38 and receiver+0x3c, remain runtime gates.",
      "No original-process invocation and no indirect-caller trace were captured, so reachability through vtable 0x01408870 is a runtime gate.",
      "The real body of 0x00612b20 is not reproduced here beyond its observed 0x18-stride move and its degenerate-range return. Its non-empty movement path remains unmodelled.",
      "The real body of 0x00685a30 is not reproduced here beyond its 0x18-stride traversal. Its per-entry release call to 0x0093db80 on the sub-object at entry+4, taken when byte entry+0x14 has its 0x4 bit set, is out of scope for this record.",
      "The real body of 0x0092cb00 is not reproduced here beyond its observed dword-fill contract. Its count word is read from receiver+0x38, whose meaning and initial value this body never establishes."
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
      "callsite": "0x006a2b40",
      "direction": "out",
      "other": "0x00612b20",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2b4f",
      "direction": "out",
      "other": "0x00685a30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2b2f",
      "direction": "out",
      "other": "0x0092cb00",
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
    "id": "scc-0214",
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
    "package": "pkg-direct-property-copyfrom-wave14",
    "score": 12,
    "symbol": "App_DirectPropertyList_CopyFrom_006a2ad0",
    "va": "0x006a2ad0"
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
      "shared_types:DirectPropertyList",
      "shared_vtable:vtable:0x01408870",
      "same_calling_convention"
    ],
    "package": "PKG-PROPERTY-SAFE-WAVE9",
    "score": 9,
    "symbol": "direct_property_list_add_properties_from_006a1600",
    "va": "0x006a1600"
  },
  {
    "match_basis": [
      "shared_types:DirectPropertyList",
      "shared_vtable:vtable:0x01408870",
      "same_calling_convention"
    ],
    "package": "PKG-PROPER
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__Clear.c",
  "file": "src/reconstruction/pkg_direct_property_clear_wave14/006a2b20_direct_property_list_clear.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__Clear.c",
    "reconstruction/staging/pkg-direct-property-clear-wave14/006a2b20_direct_property_list_clear.cpp",
    "src/reconstruction/pkg_direct_property_clear_wave14/006a2b20_direct_property_list_clear.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-direct-property-clear-wave14/006a2b20.json"
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
    "No original-process invocation and no indirect-caller trace were captured for 0x006a2b20, so the reachability of this body through the shared vtable 0x01408870, and the real values held at receiver+0x38 and receiver+0x3c, remain runtime gates.",
    "No original-process invocation and no indirect-caller trace were captured, so reachability through vtable 0x01408870 is a runtime gate.",
    "The concrete layout of the receiver between offsets 0x00 and 0x17, and between 0x20 and 0x37, which this body never touches.",
    "The identity of the receiver words at 0x18, 0x1c, 0x38 and 0x3c. The machine-derived receiver record is bounds_only and enumerates displacements, not members, so the candidate deliberately names none. A layout naming these words needs a source outside this body (the SDK header, or a writer elsewhere in the binary).",
    "The meaning of the pair at receiver+0x38 and receiver+0x3c. The 0x0092cb00 body fills count consecutive dwords at dest with a value word and returns dest, so the shape is a (count, destination) pair for a companion array, but whether that array is parallel to the 0x18-stride entry range, indexed by the same stride, or unrelated is not observable from this body.",
    "The real body and general contract of 0x0092cb00 beyond the dword fill, and of 0x00612b20 beyond the 0x18-stride move and its degenerate-range return.",
    "The real body of 0x00612b20 is not reproduced here beyond its observed 0x18-stride move and its degenerate-range return. Its non-empty movement path remains unmodelled
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__Clear.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-direct-property-clear-wave14/006a2b20.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-direct-property-clear-wave14/006a2b20_direct_property_list_clear.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_direct_property_clear_wave14/006a2b20_direct_property_list_clear.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__Clear.c",
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
      "ref": "reconstruction/metadata/pkg-direct-property-clear-wave14/006a2b20.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-direct-property-clear-wave14/006a2b20_direct_property_list_clear.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_direct_property_clear_wave14/006a2b20_direct_property_list_clear.cpp",
      "source_class": "committed_ar
[TRUNCATED]
```
