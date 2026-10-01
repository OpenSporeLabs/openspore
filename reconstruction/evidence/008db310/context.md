# Reconstruction context 0x008db310

- Status: `partial`
- Content SHA-256: `91cc23df832e6304076968ddc54324a1f0e45edc39db8374424fd1fe582f8def`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x008db310",
  "phase": "reconstruction",
  "target": "0x008db310"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Resource::PFIndexModifiable::Write",
  "package": "pkg-orchestrate-dogfood-008db310",
  "subsystem": "Resource",
  "va": "0x008db310"
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
  "content_sha256": "6895e4f7d428b10969d95e8fe8ac3079dc5080314985df808258a94d19ba1831",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x008db310 failed: Decompilation did not complete. Reason: ",
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
    "x86-32 thiscall, callee cleanup",
    "__thiscall observed"
  ],
  "convention": "__thiscall observed",
  "hidden_receiver": "ECX, the write carrier, read only at +0x2c and +0x30",
  "hidden_this_register": "ECX",
  "hidden_this_type": "PFIndexModifiableWriteCarrier*",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "destination",
      "position": 1,
      "read_at": "0x008db31c reads ESP+0x14, which is the entry ESP+0x04 after the four register pushes at 0x008db314..0x008db317",
      "type": "void*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "destination_size",
      "position": 2,
      "read_at": "0x008db310 reads ESP+0x08 into EAX before any push",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x8 at 0x008db384 and 0x008db38d",
  "return_register": "AL",
  "return_semantics": "AL is set to 0x1 at 0x008db381 on the no-overlap path and to 0x0 at 0x008db38a on the overlap path; the function returns true when the destination extent is empty or when no scanned record interval overlaps it, and false on the first overlap",
  "return_type": "bool",
  "return_width_bytes": 4,
  "saved_registers": "EBX, EBP, ESI, EDI are pushed at 0x008db314..0x008db317 and popped on both exits",
  "stack_arguments": [
    "{'entry_offset': 'ESP+0x04', 'name': 'destination', 'position': 1, 'type': 'void*', 'width_bytes': 4}",
    "{'entry_offset': 'ESP+0x08', 'name': 'destination_size', 'position': 2, 'type': 'uint32_t', 'w
[TRUNCATED]
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
  "globals": [],
  "types": [
    "DATA",
    "ItemsMap",
    "PFIndexModifiableWriteCarrier*",
    "bool",
    "openspore::reconstruction::pkg_orchestrate_dogfood_008db310::DispatchSlot014368bc",
    "openspore::reconstruction::pkg_orchestrate_dogfood_008db310::OpaqueItemNode",
    "openspore::reconstruction::pkg_orchestrate_dogfood_008db310::OpaquePorts",
    "openspore::reconstruction::pkg_orchestrate_dogfood_008db310::OpaqueWord",
    "openspore::reconstruction::pkg_orchestrate_dogfood_008db310::OpaqueWriteCarrier",
    "uint32_t",
    "void*"
  ],
  "vtables": [
    "vtable:0x01436878"
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
      "No direct caller xref exists, so the producer of the destination pointer and the meaning of the extent word in bytes versus an index count are unconfirmed.",
      "No original-process invocation or indirect-caller trace was captured; runtime_validation stays 0.",
      "The end sentinel at slots[carrier+0x30] is proven as a terminating value but its construction and lifetime are unresolved.",
      "The owner of the pointer run around 0x01436878 that stores 0x008db310 at 0x014368bc is unknown, so the class that reaches this function and the slot index it occupies are unproved.",
      "The record interval values at node+0x0c and node+0x10 are treated as opaque 32-bit offsets; the buffer they index is not identified from this function."
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
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0272",
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
      "shared_types:DATA"
    ],
    "package": "pkg-resource-index-ref-008d86b0",
    "score": 9,
    "symbol": "destroy_index_008d86b0",
    "va": "0x008d86b0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 3,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "PKG-SKINNER-SAFE-WAVE10",
    "score": 3,
    "symbol": "skin_painter_job_brush_pass_005182f0",
    "va": "0x005182f0"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005bf9d0",
    "va": "0x005bf9d0"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005c0100",
    "va": "0x005c0100"
  },
  {
    "match_basis": [
      "shared_types:DATA"
    ],
    "package": "PKG-18-UI-SCRIPTING",
    "score": 3,
    "symbol": "FUN_005c0380",
    "va": "0x005c0380"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-PALETTE-SAFE-WAVE11",
    "score": 3,
    "symbol": "palette_safe_wave11_fill_node_array_005c7ff0",
    "va": "0x005c7ff0"
  },
  {
    "match_basis": [
      "shared_types:void*"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 3,
    "symbol": "service_005fa8d0",
    "va": "0x005fa8d0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c",
    "reconstruction/staging/pkg-orchestrate-dogfood-008db310/dogfood_008db310.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-008db310/dogfood_008db310.hpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-008db310/dogfood_008db310_model_test.cpp",
    "reconstruction/staging/wave6-resources/pf_index_write.cpp",
    "reconstruction/staging/wave6-resources/pf_index_write.hpp",
    "reconstruction/staging/wave6-resources/property_list_variants_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-orchestrate-dogfood-008db310/008db310.json",
    "reconstruction/metadata/wave6-resources/008db310.json"
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
    "Concrete ItemsMap node and bucket ownership semantics",
    "Does the word at carrier+0x30 always equal the live bucket count, or can it be an independent end index? The body only uses it to scale an index into the slot array.",
    "How is the chain at node+0x1c maintained, and can a null link with an exhausted slot run occur in a real index instance? The machine body would read past the array in that case; the model bounds the cursor at the end sentinel instead.",
    "Is the second stack word a byte count of the destination buffer or a count of index entries? The body only proves that it is added to the destination pointer and compared against node record offsets in the same units as node+0x10.",
    "No direct caller xref exists, so the producer of the destination pointer and the meaning of the extent word in bytes versus an index count are unconfirmed.",
    "No original-process invocation or indirect-caller trace was captured; runtime_validation stays 0.",
    "The end sentinel at slots[carrier+0x30] is proven as a terminating value but its construction and lifetime are unresolved.",
    "The owner of the pointer run around 0x01436878 that stores 0x008db310 at 0x014368bc is unknown, so the class that reaches this function and the slot index it occupies are unproved.",
    "The record interval values at node+0x0c and node+0x10 are treated as opaque 32-bit offsets; the buffer they index is not identified from this function.",
    "The vtable/data-table owner that reaches this otherwise uncalled function",
    "What i
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-orchestrate-dogfood-008db310/008db310.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave6-resources/008db310.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-008db310/dogfood_008db310.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-008db310/dogfood_008db310.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-orchestrate-dogfood-008db310/dogfood_008db310_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-resources/pf_index_write.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-resources/pf_index_write.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave6-resources/property_list_variants_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c",
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
      "ref": "reconstruction/metadata/pkg-orchestrate-dogfood-008db310/008db310.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave6-resources/008db310.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-orchestrate-dogfood-008db310/dogfood_008db310.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
     
[TRUNCATED]
```
