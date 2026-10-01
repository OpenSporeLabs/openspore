# Reconstruction context 0x00931810

- Status: `partial`
- Content SHA-256: `b4f8329fd183f97ddfc5be8da59c44ac03d31fac85f1356ec5cd2663cabd1885`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00931810",
  "phase": "reconstruction",
  "target": "0x00931810"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "IO::FileStream::GetPathCString",
  "package": "PKG-FILE-STREAM-WAVE6",
  "subsystem": "IO.FileStream",
  "va": "0x00931810"
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
  "content_sha256": "579e91c5f1a6d9a86e3eb07d277d20a409bedba0593e2b6411dd293abe870c24",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00931810 failed: Decompilation did not complete. Reason: ",
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
      "va": "0x00631b30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008dd510"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4b470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4c130"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00631cf0",
      "direction": "in",
      "other": "0x00631b30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x008dd52d",
      "direction": "in",
      "other": "0x008dd510",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e4b4ba",
      "direction": "in",
      "other": "0x00e4b470",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e4c17f",
      "direction": "in",
      "other": "0x00e4c130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00931828",
      "direction": "out",
      "other": "EXT:MSVCR90.DLL::wcsncpy",
      "reference_type": "external"
    }
  ],
  "external_callees": [
    "EXT:MSVCR90.DLL::wcsncpy"
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
      "runtime validation not run",
      "wide-copy boundary, path encoding, and file-handle lifecycle remain gated"
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
      "va": "0x00631b30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008dd510"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4b470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e4c130"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00631cf0",
      "direction": "in",
      "other": "0x00631b30",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x008dd52d",
      "direction": "in",
      "other": "0x008dd510",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e4b4ba",
      "direction": "in",
      "other": "0x00e4b470",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00e4c17f",
      "direction": "in",
      "other": "0x00e4c130",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00931828",
      "direction": "out",
      "other": "EXT:MSVCR90.DLL::wcsncpy",
      "reference_type": "external"
    }
  ],
  "edges_truncated": false,
  "external_callees": [
    "EXT:MSVCR90.DLL::wcsncpy"
  ],
  "fan_in": 4,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0282",
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
    "symbol": "pkg_file_stream_wave6_file_stream_set_utf8_path_009317e0",
    "va": "0x009317e0"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/IO__FileStream__GetPathCString.c",
  "file": "src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/IO__FileStream__GetPathCString.c",
    "src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-file-stream-wave6/00931810.json"
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
    "wide-copy boundary, path encoding, and file-handle lifecycle remain gated"
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/IO__FileStream__GetPathCString.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-file-stream-wave6/00931810.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/IO__FileStream__GetPathCString.c",
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
      "ref": "reconstruction/metadata/pkg-file-stream-wave6/00931810.json",
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
