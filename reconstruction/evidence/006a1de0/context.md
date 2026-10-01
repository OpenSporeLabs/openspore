# Reconstruction context 0x006a1de0

- Status: `partial`
- Content SHA-256: `8779c8c99fa5870f6b26bc8aab50bddb39879c3e5605b207c37893396d9684c8`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a1de0",
  "phase": "reconstruction",
  "target": "0x006a1de0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::PropertyList::GetPropertyAlt",
  "package": null,
  "subsystem": "App",
  "va": "0x006a1de0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "f4946786c2443caabc9a07a9a0dbb76ece8e26ef2bde370f87d2abf6f01d20c1",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a1de0 failed: Decompilation did not complete. Reason: ",
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
  "convention": "thiscall with callee stack cleanup",
  "hidden_receiver": "ECX OpaquePropertyList*; copied to ESI at 0x006a1de1",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaquePropertyList*",
  "ordinary_stack_argument_slots": 2,
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "evidence": "MOVZX-free 32-bit use; reloaded at 0x006a1dfb from [ESP+0x1c] with four callee arguments still pushed, which is the same slot as ESP+0x04 at function entry",
      "name": "property_id",
      "position": 1,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "evidence": "reloaded from [ESP+0x10] at 0x006a1e17 and at 0x006a1e2e with ESP+8 adjusted, and pushed as the first callee-visible word of the +0x20 dispatch",
      "name": "result",
      "position": 2,
      "type": "Property **",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x8",
  "return_register": "AL",
  "return_type": "bool",
  "return_width_bytes": 1,
  "saved_registers": "ESI is saved at 0x006a1de0 and restored at 0x006a1e23/0x006a1e3c/0x006a1e43; EDI is pushed at 0x006a1dea and popped at 0x006a1e1e/0x006a1e3b/0x006a1e40; EAX and EDX are caller-saved scratch",
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee; all three exits are RET 0x8",
  "termination": "RET 0x8 at 0x006a1e24, 0x006a1e3d and 0x006a1e44"
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
      "name": "direct_property_list_get_property_alt_006a1e50",
      "reconstructed": true,
      "va": "0x006a1e50"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x006a1e70",
      "direction": "in",
      "other": "0x006a1e50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a1df6",
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
    "0x00612db0 cdecl port type OpaquePropertyListLowerBound00612db0",
    "DATA",
    "OpaqueProperty (forward declared only; size, layout and ownership unresolved)",
    "OpaquePropertyEntry",
    "OpaquePropertyEntry (package-local, stride 0x18, key at 0x00, address-only word at 0x04)",
    "OpaquePropertyEntry*",
    "OpaquePropertyList",
    "OpaquePropertyList (package-local, offsets 0x00, 0x18, 0x1c, 0x2c, 0x30)",
    "OpaquePropertyList*",
    "OpaquePropertyListVtable (package-local window 0x00-0x23, named slots +0x1c and +0x20)",
    "Property **",
    "UNCONDITIONAL_CALL",
    "bool",
    "const uint32_t*",
    "direct-call",
    "opaque 4-byte word"
  ],
  "vtables": [
    "vtable:0x01408820"
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
      "No original-process invocation and no indirect-caller trace were captured for this record.",
      "The concrete implementation behind +0x20 (0x006a1de0 in the table read here, but the runtime table of the +0x30 object was not captured) is a runtime gate.",
      "The pointee type and ownership of the word at entry+0x04 are unresolved; no runtime observation of the returned address was captured.",
      "The runtime object that supplies the +0x30 word and its class identity are unobserved; the chain depth and its termination condition are data dependent.",
      "Whether the entry span is sorted at runtime, and therefore whether the unsigned lower bound is a valid search, is a runtime property of the data."
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
      "name": "direct_property_list_get_property_alt_006a1e50",
      "reconstructed": true,
      "va": "0x006a1e50"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x006a1e70",
      "direction": "in",
      "other": "0x006a1e50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a1df6",
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
    "0x006a1e50"
  ],
  "scc": {
    "id": "scc-0202",
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
    "package": "pkg-dfw-006a1540",
    "score": 12,
    "symbol": "proplist_write_006a1540",
    "va": "0x006a1540"
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
      "shared_types:DATA,UNCONDITIONAL_CALL",
      "shared_vtable:vtable:0x01408820"
    ],
    "package": "wave6-resources",
    "score": 10,
    "symbol": "property_list_has_property_006a2470",
    "va": "0x006a2470
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyAlt.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyAlt.c",
    "reconstruction/staging/pkg-orchestrate-dogfood-006a1de0/dogfood_006a1de0.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-006a1de0/dogfood_006a1de0.hpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-006a1de0/dogfood_006a1de0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-orchestrate-dogfood-006a1de0/006a1de0.json"
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
    "No ABI projection was published in the worker briefing (evidence.missing_sections = [ABI]); the whole ABI block above is derived from the 47-instruction body, from the RET 0x8 exits and from the tail-jump caller record 0x006a1e50.",
    "No original-process invocation and no indirect-caller trace were captured for this record.",
    "The concrete class of the object at +0x30 is inferred, not proved: it answers slots +0x1c and +0x20 with the shapes this table provides, and the in-repo analogue calls that field 'parent'.",
    "The concrete implementation behind +0x20 (0x006a1de0 in the table read here, but the runtime table of the +0x30 object was not captured) is a runtime gate.",
    "The pointee type and ownership of the word at entry+0x04 are unresolved; no runtime observation of the returned address was captured.",
    "The recovered class size of PropertyList; 0x34 is only this body's read frontier, while the analogue record reports a 56-byte gtype.",
    "The runtime object that supplies the +0x30 word and its class identity are unobserved; the chain depth and its termination condition are data dependent.",
    "The runtime value range and meaning of the mode byte at +0x2c, which is dead in this body.",
    "The type, size and ownership of the word at entry+0x04; only its address is observable.",
    "Whether the 'parent' relation is inheritance, aggregation or an override chain, and how the chain terminates.",
    "Whether the entry span is sorted at runtime, and therefore whether the unsigned lower bound is a val
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyAlt.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-orchestrate-dogfood-006a1de0/006a1de0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-006a1de0/dogfood_006a1de0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-006a1de0/dogfood_006a1de0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-006a1de0/dogfood_006a1de0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyAlt.c",
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
      "ref": "reconstruction/metadata/pkg-orchestrate-dogfood-006a1de0/006a1de0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-orchestrate-dogfood-006a1de0/dogfood_006a1de0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-orchestrate-dogfood-006a1de0/dogfood_006a1de0.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mod
[TRUNCATED]
```
