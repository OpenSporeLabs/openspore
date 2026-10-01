# Evidence 0x009317e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `01c9907d85bcea42fea9007e3bb7405055448d19fe9b04c3e6482ac38534027a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
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
      "entry_ESP+0x4"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "0a2752d7423ffd6d3f4e0f6ea836a945bc1d971ea15a275d2ced1b6d15ff81da",
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
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit stream receiver in ECX and caller cleanup"
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
      "claim": "the callee pops 4 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 4,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0005"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0005",
        "obs-0008"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
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
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    }
  ],
  "observations": [
    {
      "at": "0x009317e0",
      "count": 2,
      "first_use": 0,
      "first_write_index": 6,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "CMP dword ptr [ECX + 0x4],-0x1",
      "reg": "ECX"
    },
    {
      "at": "0x009317e6",
      "count": 1,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x009317e6",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0003",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x009317e6",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x009317f3",
      "definite": true,
      "id": "obs-0005",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "ADD ECX,0x8",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x009317f9",
      "count": 1,
      "first_use": 9,
      "first_write_index": 2,
      "id": "obs-0006",
      "index": 9,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00931801",
      "base": null,
      "disp": 20759072,
      "id": "obs-0007",
      "index": 12,
      "kind": "CALL_INDIRECT",
      "raw": "CALL dword ptr [0x013cc220]",
      "via": "memory"
    },
    {
      "at": "0x00931807",
      "form": "RET 0x4",
      "id": "obs-0008",
      "imm": 4,
      "index": 13,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 14,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0094f720"
  }
]
```

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
  "count": 14,
  "instructions": [
    {
      "address": "009317e0",
      "instruction": "CMP dword ptr [ECX + 0x4],-0x1"
    },
    {
      "address": "009317e4",
      "instruction": "JNZ 0x00931807"
    },
    {
      "address": "009317e6",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "009317ea",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "009317ec",
      "instruction": "JZ 0x00931807"
    },
    {
      "address": "009317ee",
      "instruction": "PUSH 0x104"
    },
    {
      "address": "009317f3",
      "instruction": "ADD ECX,0x8"
    },
    {
      "address": "009317f6",
      "instruction": "PUSH ECX"
    },
    {
      "address": "009317f7",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "009317f9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "009317fa",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "009317fc",
      "instruction": "PUSH 0xfde9"
    },
    {
      "address": "00931801",
      "instruction": "CALL dword ptr [0x013cc220]"
    },
    {
      "address": "00931807",
      "instruction": "RET 0x4"
    }
  ]
}
```

## external_callees

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "EXT:KERNEL32.DLL::MultiByteToWideChar"
]
```

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 8273,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit stream receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"void\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\",\n        \"shared_vtable:vtable:0x0143ca40,vtable:0x0143e670\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"pkg_file_stream_wave6_file_stream_increment_ref_009317b0\",\n      \"va\": \"0x009317b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\",\n        \"shared_vtable:vtable:0x01436678,vtable:0x0143ca40\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"pkg_file_stream_wave6_file_stream_set_wide_path_00931810\",\n      \"va\": \"0x00931810\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_file_stream_wave6_xml_writer_begin_processing_instruction_00901930\",\n      \"va\": \"0x00901930\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_file_stream_wave6_stream_buffer_delegate_0093ae60\",\n      \"va\": \"0x0093ae60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_file_stream_wave6_stream_child_delegate_0093b6d0\",\n      \"va\": \"0x0093b6d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 2,\n      \"symbol\": \"fixed_memory_stream_seek_0093b950\",\n      \"va\": \"0x0093b950\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"resource-io\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0094f720\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0094f76e\",\n        \"direction\": \"in\",\n        \"other\": \"0x0094f720\",\n        \"reference_type\": \"computed-call\"\n      },\n      {\n        \"callsite\": \"0x00931801\",\n        \"direction\": \"out\",\n        \"other\": \"EXT:KERNEL32.DLL::MultiByteToWideChar\",\n        \"reference_type\": \"external\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [\n      \"EXT:KERNEL32.DLL::MultiByteToWideChar\"\n    ],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0281\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"IO::FileStream::SetPath\",\n  \"normalized_symbol\": \"pkg_file_stream_wave6_file_stream_set_utf8_path_009317e0\",\n  \"observed_mechanics\": [\n    \"Only when handle+0x04 is -1 and path is non-null, calls the stdcall conversion boundary with codepage 0xFDE9, flags zero, source length -1, destination stream+0x08, and capacity 260.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-FILE-STREAM-WAVE6\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-FILE-STREAM-WAVE6\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-FILE-STREAM-WAVE6\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n  
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
  "body_end": "00931809",
  "body_span_bytes": 42,
  "body_start": "009317e0",
  "callees": [
    "MultiByteToWideChar"
  ],
  "callers": [
    "FUN_0094f720"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "009317e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "IO::FileStream::SetPath",
  "namespace": "IO",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "FileStream *"
    },
    {
      "name": "pPath16",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "wchar16 *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x5317e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void IO::FileStream::SetPath(FileStream * this, wchar16 * pPath16)",
  "size_bytes": 42,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x009317e0",
  "vtables": {
    "referenced_by_vtables": [
      "0x0143ca40",
      "0x0143e670",
      "0x0143fe78",
      "0x01436678"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "0094f76e"
    },
    {
      "from": "014366b8"
    },
    {
      "from": "0143ca80"
    },
    {
      "from": "0143e6b0"
    },
    {
      "from": "0143feb8"
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
    "conversion boundary, path encoding, and file-handle lifecycle remain gated",
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
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01436678",
  "vtable:0x0143ca40",
  "vtable:0x0143e670",
  "vtable:0x0143fe78"
]
```

## Conflicts

```json
[]
```
