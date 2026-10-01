# Evidence 0x0093b950

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `624307f1e128601ad30205d5b74dc4ddb162cb6097393fccf06c8d4845d7e3a3`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit stream receiver in ECX and caller cleanup",
  "return_semantics": "bool in AL",
  "return_type": "bool",
  "stack_cleanup_bytes": 8,
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "8c5061e07470630c5ce0020f91e3f1dd040a3587f656637d264f3e85c218262c",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit stream receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0011",
        "obs-0012"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0005",
        "obs-0006",
        "obs-0009"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0008",
        "obs-0010"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          12,
          20
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0008",
        "obs-0010",
        "obs-0011",
        "obs-0012"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012"
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
        "obs-0011",
        "obs-0012"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012"
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
      "at": "0x0093b950",
      "count": 4,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x0093b950",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0093b950",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0093b963",
      "count": 6,
      "first_use": 7,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 7,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0xc]",
      "reg": "ECX"
    },
    {
      "at": "0x0093b966",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0005",
      "index": 8,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "ADD EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0093b96c",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0006",
      "index": 10,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
  
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
  "count": 23,
  "instructions": [
    {
      "address": "0093b950",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0093b954",
      "instruction": "SUB EAX,0x0"
    },
    {
      "address": "0093b957",
      "instruction": "JZ 0x0093b975"
    },
    {
      "address": "0093b959",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "0093b95c",
      "instruction": "JZ 0x0093b96c"
    },
    {
      "address": "0093b95e",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "0093b961",
      "instruction": "JNZ 0x0093b97c"
    },
    {
      "address": "0093b963",
      "instruction": "MOV EAX,dword ptr [ECX + 0xc]"
    },
    {
      "address": "0093b966",
      "instruction": "ADD EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "0093b96a",
      "instruction": "JMP 0x0093b979"
    },
    {
      "address": "0093b96c",
      "instruction": "MOV EDX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "0093b970",
      "instruction": "ADD dword ptr [ECX + 0x14],EDX"
    },
    {
      "address": "0093b973",
      "instruction": "JMP 0x0093b97c"
    },
    {
      "address": "0093b975",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "0093b979",
      "instruction": "MOV dword ptr [ECX + 0x14],EAX"
    },
    {
      "address": "0093b97c",
      "instruction": "MOV EAX,dword ptr [ECX + 0xc]"
    },
    {
      "address": "0093b97f",
      "instruction": "CMP dword ptr [ECX + 0x14],EAX"
    },
    {
      "address": "0093b982",
      "instruction": "JBE 0x0093b98c"
    },
    {
      "address": "0093b984",
      "instruction": "MOV dword ptr [ECX + 0x14],EAX"
    },
    {
      "address": "0093b987",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "0093b989",
      "instruction": "RET 0x8"
    },
    {
      "address": "0093b98c",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "0093b98e",
      "instruction": "RET 0x8"
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
  "original_bytes": 7162,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit stream receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"bool in AL\",\n    \"return_type\": \"bool\",\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"record_read_data_008dc820\",\n      \"va\": \"0x008dc820\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"record_write_seek_008dcab0\",\n      \"va\": \"0x008dcab0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"record_write_read_008dcb70\",\n      \"va\": \"0x008dcb70\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0143eafc\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"pkg_file_stream_wave6_stream_child_delegate_0093b6d0\",\n      \"va\": \"0x0093b6d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 2,\n      \"symbol\": \"pkg_file_stream_wave6_file_stream_increment_ref_009317b0\",\n      \"va\": \"0x009317b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 2,\n      \"symbol\": \"pkg_file_stream_wave6_file_stream_set_utf8_path_009317e0\",\n      \"va\": \"0x009317e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 2,\n      \"symbol\": \"pkg_file_stream_wave6_file_stream_set_wide_path_00931810\",\n      \"va\": \"0x00931810\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"resource-io\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0287\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"IO::FixedMemoryStream::Write\",\n  \"normalized_symbol\": \"fixed_memory_stream_seek_0093b950\",\n  \"observed_mechanics\": [\n    \"Reads position +0x14 and size +0x0c, applies operation 0/1/2, and publishes position when it is within size.\",\n    \"Clamps an out-of-range result to size and returns false without preserving the rejected value.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-RECORD-IO-WAVE6\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-RECORD-IO-WAVE6\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-RECORD-IO-WAVE6\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"runtime validation not run\",\n      \"stream size ownership and runtime buffer lifetime remain gated\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_triage_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/IO__FixedMemoryStream__Write.c\",\n    \"file\": \"src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp\",\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/IO__FixedMemoryStream__Write.c\",\n      \"src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp\"\n    ],\n    \"handoffs\": [\n      \"reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json\"\n    ],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-record-io-wave6/0093b950.json\"\n    ],\n    \"provenance\": [\n      \"reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json\",\n      \"reconstruction/metada
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
  "body_end": "0093b990",
  "body_span_bytes": 65,
  "body_start": "0093b950",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0093b950",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "IO::FixedMemoryStream::Write",
  "namespace": "IO",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "FixedMemoryStream *"
    },
    {
      "name": "pData",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "void *"
    },
    {
      "name": "nSize",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "size_t"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "int",
  "return_type_resolved": true,
  "rva": "0x53b950",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "int IO::FixedMemoryStream::Write(FixedMemoryStream * this, void * pData, size_t nSize)",
  "size_bytes": 65,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0093b950",
  "vtables": {
    "referenced_by_vtables": [
      "0x0143eafc",
      "0x0143eb4c"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0143eb4c"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/IO__FixedMemoryStream__Write.c",
  "file": "src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/IO__FixedMemoryStream__Write.c",
    "src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-record-io-wave6/0093b950.json"
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
    "runtime validation not run",
    "stream size ownership and runtime buffer lifetime remain gated"
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
  "bool",
  "openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream",
  "openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream",
  "openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead",
  "openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite",
  "openspore::reconstruction::pkg_record_io_wave6::RecordWritePorts"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0143eafc",
  "vtable:0x0143eb4c"
]
```

## Conflicts

```json
[]
```
