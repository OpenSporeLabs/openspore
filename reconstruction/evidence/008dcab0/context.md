# Reconstruction context 0x008dcab0

- Status: `partial`
- Content SHA-256: `f04ca0d3079f082abfdcc64375e608ba7b58f86d5476733900b65ad28f4f7d0e`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x008dcab0",
  "phase": "reconstruction",
  "target": "0x008dcab0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Resource::PFRecordWrite::GetType",
  "package": "PKG-RECORD-IO-WAVE6",
  "subsystem": "IO.RecordIO",
  "va": "0x008dcab0"
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
  "content_sha256": "a29bb2fdbc7c4f07005c5f0a1f4d3c5fd4c31e9b258ffdba5684096f5a38eec3",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x008dcab0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "x86-32 thiscall with first explicit record receiver in ECX and caller cleanup",
  "return_semantics": "bool in AL",
  "return_type": "bool",
  "stack_cleanup_bytes": 8,
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
      "callsite": "0x008dcac0",
      "direction": "out",
      "other": "0x008dc510",
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
    "bool",
    "openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream",
    "openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream",
    "openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead",
    "openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite",
    "openspore::reconstruction::pkg_record_io_wave6::RecordWritePorts"
  ],
  "vtables": [
    "vtable:0x014368c4"
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
      "prepare/read ports, embedded stream, allocator, and runtime limit ownership remain gated",
      "runtime validation not run"
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
      "callsite": "0x008dcac0",
      "direction": "out",
      "other": "0x008dc510",
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
    "id": "scc-0274",
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
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite",
      "shared_vtable:vtable:0x014368c4",
      "same_calling_convention"
    ],
    "package": "PKG-RECORD-IO-WAVE6",
    "score": 29,
    "symbol": "record_read_data_008dc820",
    "va": "0x008dc820"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite",
      "shared_vtable:vtable:0x014368c4",
      "same_calling_convention"
    ],
    "package": "PKG-RECORD-IO-WAVE6",
    "score": 29,
    "symbol": "record_write_read_008dcb70",
    "va": "0x008dcb70"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite"
    ],
    "package": "PKG-RECORD-IO-WAVE6",
    "score": 23,
    "symbol": "fixed_memory_stream_seek_0093b950",
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetType.c",
  "file": "src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetType.c",
    "src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-record-io-wave6/008dcab0.json"
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
    "prepare/read ports, embedded stream, allocator, and runtime limit ownership remain gated",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetType.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-record-io-wave6/008dcab0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetType.c",
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
      "ref": "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-record-io-wave6/008dcab0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/
[TRUNCATED]
```
