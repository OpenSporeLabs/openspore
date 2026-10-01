# Reconstruction context 0x0069d3f0

- Status: `partial`
- Content SHA-256: `965e76cfdd006dd536e91dbd44ad6f3d9571c65ae8ca6084c6beca5657e0c08f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0069d3f0",
  "phase": "reconstruction",
  "target": "0x0069d3f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Resource::DatabaseDirectoryFiles::GetRefCount",
  "package": null,
  "subsystem": "Resource",
  "va": "0x0069d3f0"
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
  "content_sha256": "62c882eaee46a275cff5421da1933890f519130c1a81ab54f31320edefacadef",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0069d3f0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "undetermined by the machine ABI record; the reconstruction declares __thiscall from the listing observation below, which is a source-side claim and not a derived fact",
  "receiver": {
    "record_bounds_only": true,
    "record_confidence": "UNKNOWN",
    "record_offsets": [],
    "record_present": null,
    "record_reason": "ecx_reassigned_before_deref",
    "register_named_by_record": null
  },
  "ret_form": "RET",
  "return_note": "not named by the machine ABI record; the reconstruction declares a 32-bit integral return",
  "return_register": "EAX",
  "return_semantics": "integral_in_EAX (the machine record's own wording)",
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
    "global:none; the body names no absolute address"
  ],
  "types": [
    "not named by the machine ABI record; the reconstruction declares a 32-bit integral return",
    "std::int32_t"
  ],
  "vtables": [
    "vtable:0x014084f0",
    "vtable:0x014086a8",
    "vtable:0x01409630",
    "vtable:0x0140a138",
    "vtable:0x01436700",
    "vtable:0x014367b0",
    "vtable:0x01482d38"
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
    "id": "scc-0197",
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
      "shared_vtable:vtable:0x014367b0"
    ],
    "package": "pkg-resource-index-ref-008d86b0",
    "score": 10,
    "symbol": "destroy_index_008d86b0",
    "va": "0x008d86b0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-orchestrate-dogfood-008db310",
    "score": 6,
    "symbol": "pf_index_write_bounds_008db310",
    "va": "0x008db310"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__DatabaseDirectoryFiles__GetRefCount.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__DatabaseDirectoryFiles__GetRefCount.c",
    "reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count.cpp",
    "reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count.hpp",
    "reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-resource-ddf-refcount/0069d3f0.json"
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
    "ABI_UNKNOWN: the machine ABI record abstained -- no_discriminator: no stack-argument read and no positive receiver evidence",
    "ABI_UNKNOWN: the machine ABI record abstained -- receiver_not_determinable: ecx_reassigned_before_deref",
    "Byte-level confirmation of the four instructions is now recorded (evidence.byte_level_confirmation), including that 83c108 is an in-place ADD with no prior definition of ECX. It changes no verdict: the ABI record still abstains with the same two reasons, so the receiver observation remains an observation and the convention remains unestablished.",
    "Can any of the seven vtable-slot call sites pass a null or partially constructed receiver? The body has no guard.",
    "Is the word at receiver+0x8 really this object's reference count? The name comes from the SDK symbol, and a single 32-bit word read cannot distinguish a count from any other counter.",
    "The record associates seven vtables with this target while the xref export records zero vtable references; the classifier association is unexplained and no slot identity is claimed.",
    "The source declares __thiscall from a reading of the listing (ECX is never defined before the dereference, the body reads no stack slot, and Ghidra's own decompilation dereferences in_ECX). That observation is not corroborated by the machine ABI record, which names no receiver register, so the convention stays an observation rather than a derived fact.",
    "What is the concrete type of the receiver, what is the meaning of the 8 bytes below the
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Resource__DatabaseDirectoryFiles__GetRefCount.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-resource-ddf-refcount/0069d3f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__DatabaseDirectoryFiles__GetRefCount.c",
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
      "ref": "reconstruction/metadata/pkg-resource-ddf-refcount/0069d3f0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "pe
[TRUNCATED]
```
