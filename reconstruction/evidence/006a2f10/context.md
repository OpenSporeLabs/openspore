# Reconstruction context 0x006a2f10

- Status: `partial`
- Content SHA-256: `6a0ba82d105a6b457cb746581552e673bd69b75bbb86699ac95e1cac56933361`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a2f10",
  "phase": "reconstruction",
  "target": "0x006a2f10"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::PropertyList::AddPropertiesFrom",
  "package": null,
  "subsystem": "App",
  "va": "0x006a2f10"
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
  "content_sha256": "f3f37d2d9217c01f9168687ccb1d0164b2081eae05f8b8577f4b56e45a77a0a0",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a2f10 failed: Decompilation did not complete. Reason: ",
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
      "observed": true,
      "ordinal": 1,
      "read": true,
      "read_at": "0x006a2f10 MOV EAX,dword ptr [ESP + 0x4]",
      "role": "the source property list; its words at +0x18 and +0x1c are the iterated range",
      "sizes": [
        4
      ],
      "written": false
    }
  ],
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee"
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
      "callsite": "0x006a2f3e",
      "direction": "out",
      "other": "0x00542b80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2f37",
      "direction": "out",
      "other": "0x006a2d30",
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
    "global:PASS"
  ],
  "types": [
    "void"
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
      "callsite": "0x006a2f3e",
      "direction": "out",
      "other": "0x00542b80",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x006a2f37",
      "direction": "out",
      "other": "0x006a2d30",
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
    "id": "scc-0217",
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
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__AddPropertiesFrom.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__AddPropertiesFrom.c",
    "reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10.cpp",
    "reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10.hpp",
    "reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-proplist-wave13/006a2f10.json"
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
    "RESOLVED (no longer open) -- CALLS oracle disagreement. The xref export (dependencies.edges) records 2 callees -- 0x006a2d30 from callsite 0x006a2f37 and 0x00542b80 from callsite 0x006a2f3e, both reference_type direct-call -- while the complete 30-instruction listing holds 3 direct transfers: those same 2 CALLs plus 0x006a2f2b JMP 0x006a2f30. extra was {0x006a2f30}, absent {}. The briefing called the extra transfer a tail call; the machine says otherwise and the source follows the machine. The validator's reader has since been fixed to exclude a JMP immediate landing inside the recovered body span, so CALLS now reports PASS with this reconstruction naming only the two real callees.",
    "Return-type evidence conflict: the machine-derived ABI record classifies the return as unclassified_in_EAX / aggregate_unknown with void_possible false, while the live Ghidra prototype and the decompiled body say void. The source encodes void, which is why RETURN SEMANTICS is WARN. The record's abstained_because attributes the gap to unmodelled flow rather than to an observed aggregate return, but no positive machine fact closes it.",
    "SETTLED BY THE MACHINE, recorded because it is the load-bearing claim: 0x006a2f30 is not a callee. It is LEA EAX,[ESI+0x4], the first instruction of the loop body block; it lies inside the body span 0x006a2f10..0x006a2f51; control enters it from the preheader at 0x006a2f2b and re-enters it from the back edge 0x006a2f48 (JNZ 0x006a2f30), and it falls out of the loop at 0x006a2f4a (POP EBX). A tail call
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__AddPropertiesFrom.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-app-proplist-wave13/006a2f10.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__AddPropertiesFrom.c",
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
      "ref": "reconstruction/metadata/pkg-app-proplist-wave13/006a2f10.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10.hpp",
      "source_class": "committed_artifact"
    },
  
[TRUNCATED]
```
