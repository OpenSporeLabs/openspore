# Reconstruction context 0x009317b0

- Status: `partial`
- Content SHA-256: `11dcca4560f10a7b8be71c64032db94858b9da35b5b0531855024500c2599237`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x009317b0",
  "phase": "reconstruction",
  "target": "0x009317b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "IO::FileStream::SetPathCString",
  "package": "PKG-FILE-STREAM-WAVE6",
  "subsystem": "IO.FileStream",
  "va": "0x009317b0"
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
  "content_sha256": "26652a957ddf69e19b830901e2dca6ce5c314c9eb57daa0a3aaa2a4c6d2085b7",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x009317b0 failed: Decompilation did not complete. Reason: ",
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
  "return_semantics": "new signed 32-bit reference count in EAX",
  "return_type": "std::int32_t",
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
  "callers": [
    {
      "name": "service_005fa8d0",
      "reconstructed": true,
      "va": "0x005fa8d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005fb430"
    },
    {
      "name": "service_005fc330",
      "reconstructed": true,
      "va": "0x005fc330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005fd260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008d6ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0091c640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00947e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00947ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4c130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f01f40"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x005faad8",
      "direction": "in",
      "other": "0x005fa8d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005fb725",
      "direction": "in",
      "other": "0x005fb430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005fc375",
      "direction": "in",
      "other": "0x005fc330",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005fd4a0",
      "direction": "in",
      "other": "0x005fd260",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x008d6fc3",
      "direction": "in",
      "other": "0x008d6ed0",
[TRUNCATED]
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
    "std::int32_t"
  ],
  "vtables": [
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
      "runtime validation not run",
      "stream lifetime and reference-count synchronization remain gated"
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
      "name": "service_005fa8d0",
      "reconstructed": true,
      "va": "0x005fa8d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005fb430"
    },
    {
      "name": "service_005fc330",
      "reconstructed": true,
      "va": "0x005fc330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005fd260"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008d6ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0091c640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00947e30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00947ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4c130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f01f40"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x005faad8",
      "direction": "in",
      "other": "0x005fa8d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005fb725",
      "direction": "in",
      "other": "0x005fb430",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005fc375",
      "direction": "in",
      "other": "0x005fc330",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005fd4a0",
      "direction": "in",
      "other": "0x005fd260",
      "reference_type": "direct-call"
    },
    {

[TRUNCATED]
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
    "symbol": "pkg_file_stream_wave6_file_stream_set_utf8_path_009317e0",
    "va": "0x009317e0"
  },
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/IO__FileStream__SetPathCString.c",
  "file": "src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/IO__FileStream__SetPathCString.c",
    "src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-file-stream-wave6/009317b0.json"
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
    "runtime validation not run",
    "stream lifetime and reference-count synchronization remain gated"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/IO__FileStream__SetPathCString.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-file-stream-wave6/009317b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/IO__FileStream__SetPathCString.c",
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
      "ref": "reconstruction/metadata/pkg-file-stream-wave6/009317b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstructio
[TRUNCATED]
```
