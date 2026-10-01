# Reconstruction context 0x006a14d0

- Status: `partial`
- Content SHA-256: `e9f6537cf3278386662e046e568b543d13727947cffc5d9a7054f4a62dea435d`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x006a14d0",
  "phase": "reconstruction",
  "target": "0x006a14d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "App::PropertyList::CopyAllPropertiesFrom",
  "package": "pkg-app-proplist-copyall-wave16",
  "subsystem": "App",
  "va": "0x006a14d0"
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
  "content_sha256": "079aa8b946650f4a7be5b12687a97d21cc959ed74ca450248b88de489e415a6f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x006a14d0 failed: Decompilation did not complete. Reason: ",
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
    "{'entry_offset': 'entry_ESP+0x4', 'observed': True, 'ordinal': 1, 'read': True, 'read_at': '0x006a14d2 MOV EDI,dword ptr [ESP + 0xc]', 'read_offset_note': 'the +0xc operand is entry_ESP+0x4 plus the 8 bytes pushed by 0x006a14d0 PUSH ESI and 0x006a14d1 PUSH EDI', 'role': 'the source property list, held in EDI and forwarded as the single stack word of the slot +0x38 dispatch at 0x006a14ff', 'sizes': [4], 'written': False}",
    "{'entry_offset': 'entry_ESP+0x4', 'observed': True, 'ordinal': 1, 'read': True, 'read_at': '0x006a14d2 MOV EDI,dword ptr [ESP + 0xc]', 'read_offset_note': 'the +0xc operand is entry_ESP+0x4 plus the 8 bytes pushed by 0x006a14d0 PUSH ESI and 0x006a14d1 PUSH EDI. Both citations are taken from the persisted abi record and were re-derived from the live listing, which agrees.', 'role': 'the source object. It is held in EDI, compared against the receiver at 0x006a14d8, and forwarded unchanged as the single stack word of the slot +0x38 dispatch at 0x006a14ff.', 'sizes': [4], 'written': False}"
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "EDI",
    "ESI"
  ],
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
  "edge_rows": [],
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
    "vtable:0x00432b50",
    "vtable:0x006a14d0",
    "vtable:0x01408820",
    "vtable:0x01408870",
    "vtable:0x014088bc"
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
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0198",
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
      "shared_vtable:vtable:0x01408820,vtable:0x01408870",
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
    "package": "pkg-direct-property-clear-wave14",
    "score": 12,
    "symbol": "direct_property_list_clear_006a2b20",
    "va": "0x006a2b20"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01408820,vtable:0x01408870",
      "same_calling_convention"
    ],
    "package": "pkg-property-remove-006a2ef0",
    "score": 12,
  
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__CopyAllPropertiesFrom.c",
  "file": "src/reconstruction/pkg_app_proplist_copyall_wave16/all_copy_from_properties_006a14d0.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__CopyAllPropertiesFrom.c",
    "reconstruction/staging/pkg-app-proplist-copyall-wave16/all_copy_from_properties_006a14d0.cpp",
    "reconstruction/staging/pkg-app-proplist-copyall-wave16/all_copy_from_properties_006a14d0.hpp",
    "reconstruction/staging/pkg-app-proplist-copyall-wave16/all_copy_from_properties_006a14d0_model_test.cpp",
    "reconstruction/staging/pkg-dfw-006a14d0/dfw_006a14d0.cpp",
    "reconstruction/staging/pkg-dfw-006a14d0/dfw_006a14d0_model_test.cpp",
    "reconstruction/staging/pkg-dfw-006a14d0/dfw_006a14d0_types.hpp",
    "src/reconstruction/pkg_app_proplist_copyall_wave16/all_copy_from_properties_006a14d0.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-proplist-copyall-wave16/006a14d0.json",
    "reconstruction/metadata/pkg-dfw-006a14d0/006a14d0.json"
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
    "Can the adding step see a stale view of the source? 0x006a1510 reads its argument's word at displacement 0x30 and, when it is non-null, recurses through its own slot +0x38 before calling its own slot +0x30. This body has just cleared the RECEIVER, and on every path past the guard the source is a different object, so the interaction is presumably benign -- but this body performs no check that would make it so, and the recursion inside 0x006a1510 is not characterised here.",
    "Can the re-read of the receiver's table pointer at 0x006a14fa matter? The listing reads it twice, and this body models the re-read. Whether anything between the two reads can change the receiver's table pointer is not determinable from this body, and neither of the two +0x48 targets has been characterised for such a write here.",
    "Is 0x00432b50 the right slot +0x04 target at run time? Both table images agree on it, which is as strong as static evidence gets, but the transfer is dispatched on the HELD OBJECT and that object's dynamic type may be a third class not represented by either image.",
    "No evidence pack. reconstruction/evidence/006a14d0/evidence.json does not exist, so the reconstruction's facts are cited by live address rather than by a persisted artefact. An integrator may want to generate one before promotion.",
    "Return-type evidence. Unlike the pkg-app-proplist-wave13 sibling, no machine-derived ABI record for this target was available to contradict void, so RETURN SEMANTICS has no known conflict. That is an absence of count
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__CopyAllPropertiesFrom.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-app-proplist-copyall-wave16/006a14d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dfw-006a14d0/006a14d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-proplist-copyall-wave16/all_copy_from_properties_006a14d0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-proplist-copyall-wave16/all_copy_from_properties_006a14d0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-app-proplist-copyall-wave16/all_copy_from_properties_006a14d0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-006a14d0/dfw_006a14d0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-006a14d0/dfw_006a14d0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dfw-006a14d0/dfw_006a14d0_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_app_proplist_copyall_wave16/all_copy_from_properties_006a14d0.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__CopyAllPropertiesFrom.c",
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
      "ref": "reconstruction/metadata/pkg-app-proplist-copyall-wave16/006a14d0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-dfw-006a14d0/006a14d0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-app-proplist-copyall-wave16/all_copy_from_properties_006a14d0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mod
[TRUNCATED]
```
