# Evidence 0x0093b6d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2eadf51182d662e652b4d0c0d7fc87300a2efdae515b9ec6df180a5f625ea07f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit child receiver in ECX and caller cleanup",
  "return_semantics": "delegated signed 32-bit result in EAX or zero",
  "return_type": "std::int32_t",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "b7da0338537563763dcffe57a5e5a1aa0cf9f5de5260a0d5b241b96c72979b36",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit child receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0008"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          12
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0008"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0008"
      ],
      "claim": "entry slot 0 is not written through a pointer",
      "confidence": "APPROXIMATION",
      "id": "S2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0008"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x0093b6d0",
      "count": 3,
      "first_use": 0,
      "first_write_index": 2,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "CMP dword ptr [ECX + 0xc],0x0",
      "reg": "ECX"
    },
    {
      "at": "0x0093b6d6",
      "definite": true,
      "id": "obs-0002",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ECX + 0xc]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0093b6d9",
      "definite": true,
      "id": "obs-0003",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0093b6db",
      "count": 2,
      "first_use": 4,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x14]",
      "reg": "EAX"
    },
    {
      "at": "0x0093b6db",
      "definite": true,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x14]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0093b6de",
      "count": 1,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_READ",
      "raw": "JMP EDX",
      "reg": "EDX"
    },
    {
      "at": "0x0093b6de",
      "base": "EDX",
      "disp": null,
      "id": "obs-0007",
      "index": 5,
      "kind": "JMP_INDIRECT",
      "raw": "JMP EDX",
      "via": "register"
    },
    {
      "at": "0x0093b6e2",
      "form": "RET",
      "id": "obs-0008",
      "imm": null,
      "index": 7,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 8,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 12,
    "offsets": [
      12
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "integral",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through 
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 8,
  "instructions": [
    {
      "address": "0093b6d0",
      "instruction": "CMP dword ptr [ECX + 0xc],0x0"
    },
    {
      "address": "0093b6d4",
      "instruction": "JZ 0x0093b6e0"
    },
    {
      "address": "0093b6d6",
      "instruction": "MOV ECX,dword ptr [ECX + 0xc]"
    },
    {
      "address": "0093b6d9",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "0093b6db",
      "instruction": "MOV EDX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "0093b6de",
      "instruction": "JMP EDX"
    },
    {
      "address": "0093b6e0",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "0093b6e2",
      "instruction": "RET"
    }
  ]
}
```

## external_callees

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 7841,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit child receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"delegated signed 32-bit result in EAX or zero\",\n    \"return_type\": \"std::int32_t\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\",\n        \"shared_vtable:vtable:0x0143eaac\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"pkg_file_stream_wave6_stream_buffer_delegate_0093ae60\",\n      \"va\": \"0x0093ae60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_file_stream_wave6_xml_writer_begin_processing_instruction_00901930\",\n      \"va\": \"0x00901930\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_file_stream_wave6_file_stream_increment_ref_009317b0\",\n      \"va\": \"0x009317b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_file_stream_wave6_file_stream_set_utf8_path_009317e0\",\n      \"va\": \"0x009317e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_file_stream_wave6_file_stream_set_wide_path_00931810\",\n      \"va\": \"0x00931810\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0143eaac\"\n      ],\n      \"package\": \"wave6-serialization-persistence\",\n      \"score\": 4,\n      \"symbol\": \"stream_child_close_and_maybe_delete_0093b610\",\n      \"va\": \"0x0093b610\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0143eafc\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"fixed_memory_stream_seek_0093b950\",\n      \"va\": \"0x0093b950\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"resource-io\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0286\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"IO::StreamChild::GetAvailable\",\n  \"normalized_symbol\": \"pkg_file_stream_wave6_stream_child_delegate_0093b6d0\",\n  \"observed_mechanics\": [\n    \"Returns zero when child+0x0c parent is null.\",\n    \"Otherwise calls parent vtable slot +0x14 with parent in ECX and returns its result unchanged.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-FILE-STREAM-WAVE6\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-FILE-STREAM-WAVE6\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-FILE-STREAM-WAVE6\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"parent stream vtable and delegated result ownership remain gated\",\n      \"runtime validation not run\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_triage_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-expo
[TRUNCATED]
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "0093b6e2",
  "body_span_bytes": 19,
  "body_start": "0093b6d0",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0093b6d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "IO::StreamChild::GetAvailable",
  "namespace": "IO",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "StreamChild *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "int",
  "return_type_resolved": true,
  "rva": "0x53b6d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "int IO::StreamChild::GetAvailable(StreamChild * this)",
  "size_bytes": 19,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0093b6d0",
  "vtables": {
    "referenced_by_vtables": [
      "0x0143eaac",
      "0x0143eafc"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0143eafc"
    }
  ]
}
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/IO__StreamChild__GetAvailable.c",
  "file": "src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/IO__StreamChild__GetAvailable.c",
    "src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-file-stream-wave6/0093b6d0.json"
  ]
}
```

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocking_reason": null,
  "gates": [
    "parent stream vtable and delegated result ownership remain gated",
    "runtime validation not run"
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "openspore::reconstruction::pkg_file_stream_wave6::FileStream",
  "openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream",
  "openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer",
  "openspore::reconstruction::pkg_file_stream_wave6::StreamChild",
  "openspore::reconstruction::pkg_file_stream_wave6::XmlWriter",
  "std::int32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0143eaac",
  "vtable:0x0143eafc"
]
```

## Conflicts

```json
[]
```
