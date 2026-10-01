# Reconstruction context 0x009317e0

- Status: `partial`
- Content SHA-256: `d112bd532b6ec8a31323be590ce4c02a8ffebe920ef53a461c316be97a15d438`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x009317e0",
  "phase": "reconstruction",
  "target": "0x009317e0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "IO::FileStream::SetPath",
  "package": "PKG-FILE-STREAM-WAVE6",
  "subsystem": "IO.FileStream",
  "va": "0x009317e0"
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
  "content_sha256": "01c9907d85bcea42fea9007e3bb7405055448d19fe9b04c3e6482ac38534027a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x009317e0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "x86-32 thiscall with first explicit stream receiver in ECX and caller cleanup",
  "return_semantics": "void",
  "return_type": "void",
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "caller"
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
      "va": "0x0094f720"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0094f76e",
      "direction": "in",
      "other": "0x0094f720",
      "reference_type": "computed-call"
    },
    {
      "callsite": "0x00931801",
      "direction": "out",
      "other": "EXT:KERNEL32.DLL::MultiByteToWideChar",
      "reference_type": "external"
    }
  ],
  "external_callees": [
    "EXT:KERNEL32.DLL::MultiByteToWideChar"
  ]
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "openspore::reconstruction::pkg_file_stream_wave6::FileStream",
    "openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream",
    "openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer",
    "openspore::reconstruction::pkg_file_stream_wave6::StreamChild",
    "openspore::reconstruction::pkg_file_stream_wave6::XmlWriter",
    "void"
  ],
  "vtables": [
    "vtable:0x01436678",
    "vtable:0x0143ca40",
    "vtable:0x0143e670",
    "vtable:0x0143fe78"
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
      "conversion boundary, path encoding, and file-handle lifecycle remain gated",
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0094f720"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0094f76e",
      "direction": "in",
      "other": "0x0094f720",
      "reference_type": "computed-call"
    },
    {
      "callsite": "0x00931801",
      "direction": "out",
      "other": "EXT:KERNEL32.DLL::MultiByteToWideChar",
      "reference_type": "external"
    }
  ],
  "edges_truncated": false,
  "external_callees": [
    "EXT:KERNEL32.DLL::MultiByteToWideChar"
  ],
  "fan_in": 1,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0281",
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
      "shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild",
      "shared_vtable:vtable:0x0143ca40,vtable:0x0143e670",
      "same_calling_convention"
    ],
    "package": "PKG-FILE-STREAM-WAVE6",
    "score": 29,
    "symbol": "pkg_file_stream_wave6_file_stream_increment_ref_009317b0",
    "va": "0x009317b0"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild",
      "shared_vtable:vtable:0x01436678,vtable:0x0143ca40",
      "same_calling_convention"
    ],
    "package": "PKG-FILE-STREAM-WAVE6",
    "score": 29,
    "symbol": "pkg_file_stream_wave6_file_stream_set_wide_path_00931810",
    "va": "0x00931810"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild"
    ],
    "package": "PKG-FILE-STREAM-WAVE6",
    "score":
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/IO__FileStream__SetPath.c",
  "file": "src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/IO__FileStream__SetPath.c",
    "src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-file-stream-wave6/009317e0.json"
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
    "conversion boundary, path encoding, and file-handle lifecycle remain gated",
    "runtime validation not run"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/IO__FileStream__SetPath.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-file-stream-wave6/009317e0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/IO__FileStream__SetPath.c",
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
      "ref": "reconstruction/metadata/pkg-file-stream-wave6/009317e0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowl
[TRUNCATED]
```
