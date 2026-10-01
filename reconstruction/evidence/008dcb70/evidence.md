# Evidence 0x008dcb70

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7c70ec199b0ca3186fdcb55cda00163d7105dbeb081034abf11398f7f5fd37e3`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit record receiver in ECX and caller cleanup",
  "return_semantics": "available byte count in EAX or -1",
  "return_type": "std::int32_t",
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
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
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
  "content_sha256": "10b8cbd8610946b3574f5abcb2734431a884df9bc1055126fec08a05a407584c",
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
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit record receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0019",
        "obs-0025"
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
        "obs-0011",
        "obs-0014"
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
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0012",
        "obs-0014"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          -4,
          12,
          64,
          68,
          72
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0012",
        "obs-0014",
        "obs-0019",
        "obs-0025"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0019",
        "obs-0025"
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
        "obs-0019",
        "obs-0025"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0019",
        "obs-0025"
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
      "at": "0x008dcb70",
      "count": 10,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x008dcb71",
      "count": 6,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x008dcb71",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x008dcb79",
      "count": 4,
      "first_use": 4,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x008dcb7d",
      "definite": true,
      "id": "obs-0005",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EBX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x008dcb7f",
      "id": "obs-0006",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x008dc510",
      "target": "0x008dc510"
    },
    {
      "at": "0x008dcb84",
      "definite": true,
      "id": "obs-0007",
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
  "count": 51,
  "instructions": [
    {
      "address": "008dcb70",
      "instruction": "PUSH ESI"
    },
    {
      "address": "008dcb71",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "008dcb73",
      "instruction": "CMP dword ptr [ESI + -0x4],0x0"
    },
    {
      "address": "008dcb77",
      "instruction": "JZ 0x008dcbde"
    },
    {
      "address": "008dcb79",
      "instruction": "PUSH EBX"
    },
    {
      "address": "008dcb7a",
      "instruction": "LEA EBX,[ESI + -0x20]"
    },
    {
      "address": "008dcb7d",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "008dcb7f",
      "instruction": "CALL 0x008dc510"
    },
    {
      "address": "008dcb84",
      "instruction": "MOV AL,byte ptr [ESI + 0x48]"
    },
    {
      "address": "008dcb87",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "008dcb89",
      "instruction": "JNZ 0x008dcbd1"
    },
    {
      "address": "008dcb8b",
      "instruction": "PUSH EDI"
    },
    {
      "address": "008dcb8c",
      "instruction": "OR EDI,0xffffffff"
    },
    {
      "address": "008dcb8f",
      "instruction": "CMP dword ptr [ESI + -0x4],0x0"
    },
    {
      "address": "008dcb93",
      "instruction": "JZ 0x008dcbc9"
    },
    {
      "address": "008dcb95",
      "instruction": "MOV ECX,dword ptr [ESI + 0x40]"
    },
    {
      "address": "008dcb98",
      "instruction": "MOV EDI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "008dcb9c",
      "instruction": "MOV EAX,dword ptr [ESI + 0x44]"
    },
    {
      "address": "008dcb9f",
      "instruction": "LEA EDX,[ECX + EDI*0x1]"
    },
    {
      "address": "008dcba2",
      "instruction": "CMP EDX,EAX"
    },
    {
      "address": "008dcba4",
      "instruction": "JA 0x008dcbaa"
    },
    {
      "address": "008dcba6",
      "instruction": "CMP EDX,ECX"
    },
    {
      "address": "008dcba8",
      "instruction": "JNC 0x008dcbae"
    },
    {
      "address": "008dcbaa",
      "instruction": "SUB EAX,ECX"
    },
    {
      "address": "008dcbac",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "008dcbae",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "008dcbb0",
      "instruction": "JZ 0x008dcbc6"
    },
    {
      "address": "008dcbb2",
      "instruction": "PUSH EDI"
    },
    {
      "address": "008dcbb3",
      "instruction": "PUSH ECX"
    },
    {
      "address": "008dcbb4",
      "instruction": "MOV ECX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "008dcbb8",
      "instruction": "PUSH ECX"
    },
    {
      "address": "008dcbb9",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "008dcbbb",
      "instruction": "CALL 0x008dc3f0"
    },
    {
      "address": "008dcbc0",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "008dcbc2",
      "instruction": "JNZ 0x008dcbc6"
    },
    {
      "address": "008dcbc4",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "008dcbc6",
      "instruction": "ADD dword ptr [ESI + 0x40],EDI"
    },
    {
      "address": "008dcbc9",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "008dcbcb",
      "instruction": "POP EDI"
    },
    {
      "address": "008dcbcc",
      "instruction": "POP EBX"
    },
    {
      "address": "008dcbcd",
      "instruction": "POP ESI"
    },
    {
      "address": "008dcbce",
      "instruction": "RET 0x8"
    },
    {
      "address": "008dcbd1",
      "instruction": "MOV EDX,dword ptr [ESI + 0xc]"
    },
    {
      "address": "008dcbd4",
      "instruction": "LEA ECX,[ESI + 0xc]"
    },
    {
      "address": "008dcbd7",
      "instruction": "POP EBX"
    },
    {
      "address": "008dcbd8",
      "instruction": "POP ESI"
    },
    {
      "address": "008dcbd9",
      "instruction": "MOV EDX,dword ptr [EDX + 0x30]"
    },
    {
      "address": "008dcbdc",
      "instruction": "JMP EDX"
    },
    {
      "address": "008dcbde",
      "instruction": "OR EAX,0xffffffff"
    },
    {
      "address": "008dcbe1",
      "instruction": "POP ESI"
    },
    {
      "address": "008dcbe2",
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
  "original_bytes": 6803,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit record receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"available byte count in EAX or -1\",\n    \"return_type\": \"std::int32_t\",\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite\",\n        \"shared_vtable:vtable:0x014368c4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"record_read_data_008dc820\",\n      \"va\": \"0x008dc820\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite\",\n        \"shared_vtable:vtable:0x014368c4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"record_write_seek_008dcab0\",\n      \"va\": \"0x008dcab0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"fixed_memory_stream_seek_0093b950\",\n      \"va\": \"0x0093b950\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"resource-io\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x008dcbbb\",\n        \"direction\": \"out\",\n        \"other\": \"0x008dc3f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x008dcb7f\",\n        \"direction\": \"out\",\n        \"other\": \"0x008dc510\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0275\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"Resource::PFRecordWrite::GetAvailable\",\n  \"normalized_symbol\": \"record_write_read_008dcb70\",\n  \"observed_mechanics\": [\n    \"Rejects an uninitialized state word before prepare and local read work.\",\n    \"Delegates to embedded stream read slot +0x30 when state+0x68 is nonzero.\",\n    \"Local path clamps size by +0x44 limit, delegates the bounded read, advances +0x60 by the accepted count, and returns the count.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-RECORD-IO-WAVE6\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-RECORD-IO-WAVE6\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-RECORD-IO-WAVE6\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"prepare/read ports, stream bounds, and destination lifetime remain gated\",\n      \"runtime validation not run\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_triage_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetAvailable.c\",\n    \"file\": \"src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp\",\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetAvailable.c\",\n      \"src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp\"\n    ],\n    \"handoffs\": [\n      \"reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json\"\n    ],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-record-io-wave6/008dcb70.json\"\n    ],\n    \"provenance\": [\n      \"reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json\",\n      \"reconstruction/metadata/pkg-record-io-wave6/008dcb70.json\",\n      \"reconstruction/staging/pkg-record-io-wave6/pkg_record_io_wave6.cpp\",\n      \"reconstruction/staging/pkg-record-io-wave6/pkg_record_io_wave6_model_test.cpp\"\n    ]\n  },\n  \"status\": \"reconstructed\",\n  \"subsystem\": \"IO.RecordIO\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"resource-io\",\n    \"db_triage_status\"
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
  "body_end": "008dcbe4",
  "body_span_bytes": 117,
  "body_start": "008dcb70",
  "callees": [
    "FUN_008dc510",
    "FUN_008dc3f0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "008dcb70",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Resource::PFRecordWrite::GetAvailable",
  "namespace": "Resource",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "IStream *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "int",
  "return_type_resolved": true,
  "rva": "0x4dcb70",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "int Resource::PFRecordWrite::GetAvailable(IStream * this)",
  "size_bytes": 117,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x008dcb70",
  "vtables": {
    "referenced_by_vtables": [
      "0x014368c4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "014368f4"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetAvailable.c",
  "file": "src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetAvailable.c",
    "src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-record-io-wave6/008dcb70.json"
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
    "prepare/read ports, stream bounds, and destination lifetime remain gated",
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
  "openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream",
  "openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream",
  "openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead",
  "openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite",
  "openspore::reconstruction::pkg_record_io_wave6::RecordWritePorts",
  "std::int32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x014368c4"
]
```

## Conflicts

```json
[]
```
