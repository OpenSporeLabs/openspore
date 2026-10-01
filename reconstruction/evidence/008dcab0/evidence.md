# Evidence 0x008dcab0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a29bb2fdbc7c4f07005c5f0a1f4d3c5fd4c31e9b258ffdba5684096f5a38eec3`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
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

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -20, so the listing is not one path",
    "ret_imm_below_highest_slot: ret 0x8 pops less than the highest read slot 0xc; everything above it belongs to the caller's frame",
    "no_discriminator: the callee pop of 0x8 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x8 but entry slot 0xc is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "e40686e65b8c4de679f7944b75c28f5f192a5c922b7c2cee9dfa115447c97caf",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "UNKNOWN",
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
        "obs-0013",
        "obs-0016",
        "obs-0019",
        "obs-0021",
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
        "obs-0013",
        "obs-0016",
        "obs-0019",
        "obs-0021",
        "obs-0025"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 8,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0014",
        "obs-0017"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0017"
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
        "written_through": 4
      }
    },
    {
      "based_on": [
        "obs-0025"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0016",
        "obs-0019",
        "obs-0021",
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
        "obs-0013",
        "obs-0016",
        "obs-0019",
        "obs-0021",
        "obs-0025"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0016",
        "obs-0019",
        "obs-0021",
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
      "at": "0x008dcab0",
      "count": 15,
      "first_use": 0,
      "first_write_index": 1,
      "id": "o
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
  "count": 69,
  "instructions": [
    {
      "address": "008dcab0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "008dcab1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "008dcab3",
      "instruction": "CMP dword ptr [ESI + -0x4],0x0"
    },
    {
      "address": "008dcab7",
      "instruction": "JZ 0x008dcb5c"
    },
    {
      "address": "008dcabd",
      "instruction": "LEA ECX,[ESI + -0x20]"
    },
    {
      "address": "008dcac0",
      "instruction": "CALL 0x008dc510"
    },
    {
      "address": "008dcac5",
      "instruction": "MOV AL,byte ptr [ESI + 0x48]"
    },
    {
      "address": "008dcac8",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "008dcaca",
      "instruction": "JNZ 0x008dcb50"
    },
    {
      "address": "008dcad0",
      "instruction": "MOV EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "008dcad4",
      "instruction": "SUB EAX,0x0"
    },
    {
      "address": "008dcad7",
      "instruction": "JZ 0x008dcb2b"
    },
    {
      "address": "008dcad9",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "008dcadc",
      "instruction": "JZ 0x008dcb01"
    },
    {
      "address": "008dcade",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "008dcae1",
      "instruction": "JNZ 0x008dcb4a"
    },
    {
      "address": "008dcae3",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "008dcae7",
      "instruction": "MOV EAX,dword ptr [ESI + 0x44]"
    },
    {
      "address": "008dcaea",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "008dcaec",
      "instruction": "JGE 0x008dcaf8"
    },
    {
      "address": "008dcaee",
      "instruction": "MOV EDX,ECX"
    },
    {
      "address": "008dcaf0",
      "instruction": "NEG EDX"
    },
    {
      "address": "008dcaf2",
      "instruction": "CMP EDX,EAX"
    },
    {
      "address": "008dcaf4",
      "instruction": "JA 0x008dcb33"
    },
    {
      "address": "008dcaf6",
      "instruction": "ADD EAX,ECX"
    },
    {
      "address": "008dcaf8",
      "instruction": "MOV dword ptr [ESI + 0x40],EAX"
    },
    {
      "address": "008dcafb",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "008dcafd",
      "instruction": "POP ESI"
    },
    {
      "address": "008dcafe",
      "instruction": "RET 0x8"
    },
    {
      "address": "008dcb01",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "008dcb05",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "008dcb07",
      "instruction": "JGE 0x008dcb14"
    },
    {
      "address": "008dcb09",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "008dcb0b",
      "instruction": "NEG ECX"
    },
    {
      "address": "008dcb0d",
      "instruction": "CMP ECX,dword ptr [ESI + 0x40]"
    },
    {
      "address": "008dcb10",
      "instruction": "JA 0x008dcb33"
    },
    {
      "address": "008dcb12",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "008dcb14",
      "instruction": "JLE 0x008dcb22"
    },
    {
      "address": "008dcb16",
      "instruction": "MOV EDX,dword ptr [ESI + 0x40]"
    },
    {
      "address": "008dcb19",
      "instruction": "MOV ECX,dword ptr [ESI + 0x44]"
    },
    {
      "address": "008dcb1c",
      "instruction": "ADD EDX,EAX"
    },
    {
      "address": "008dcb1e",
      "instruction": "CMP EDX,ECX"
    },
    {
      "address": "008dcb20",
      "instruction": "JA 0x008dcb47"
    },
    {
      "address": "008dcb22",
      "instruction": "ADD dword ptr [ESI + 0x40],EAX"
    },
    {
      "address": "008dcb25",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "008dcb27",
      "instruction": "POP ESI"
    },
    {
      "address": "008dcb28",
      "instruction": "RET 0x8"
    },
    {
      "address": "008dcb2b",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "008dcb2f",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "008dcb31",
      "instruction": "JGE 0x008dcb40"
    },
    {
      "address": "008dcb33",
      "instruction": "MOV dword ptr [ESI + 0x40],0x0"
    },
    {
      "address": "008dcb3a",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "008dcb3c",
      "instruction": "POP ESI"
    },
    {
      "address": "008dcb3d",
      "instruction": "RET 0x8"
    },
    {
      "address": "008dcb40",
      "instruction": "MOV EAX,dword ptr [ESI + 0x44]"
    },
    {
      "address": "008dcb43",
      "instruction": "CMP ECX,EAX"
    },
    {
      "address": "008dcb45",
      "instruction": "JA 0x008dcaf8"
    },
    {
      "address": "008dcb47",
      "instruction": "MOV dword ptr [ESI + 0x40],ECX"
    },
    {
      "address": "008dcb4a",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "008dcb4c",
      "instruction": "POP ESI"
    },
    {
      "address": "008dcb4d",
      "instruction": "RET 0x8"
    },
    {
      "address": "008dcb50",
      "instruction": "MOV EAX,dword ptr [ESI + 0xc]"
    },
    {
      "address": "008dcb53",
      "instruction": "LEA ECX,[ESI + 0xc]"
    },
    {
      "address": "008dcb56",
      "instruction": "POP ESI"
    },
    {
      "address": "008dcb57",
      "instruction": "MOV EAX,dword ptr [EAX + 0x28]"
    },
    {
      "address": "008dcb5a",
      "instruction": "JMP EAX"
    },
    {
      "address": "008dcb5c",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "008dcb5e",
      "instruction": "POP ESI"
    },
    {
      "address": "008dcb5f",
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
  "original_bytes": 6609,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit record receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"bool in AL\",\n    \"return_type\": \"bool\",\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite\",\n        \"shared_vtable:vtable:0x014368c4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"record_read_data_008dc820\",\n      \"va\": \"0x008dc820\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite\",\n        \"shared_vtable:vtable:0x014368c4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"record_write_read_008dcb70\",\n      \"va\": \"0x008dcb70\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"fixed_memory_stream_seek_0093b950\",\n      \"va\": \"0x0093b950\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"resource-io\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x008dcac0\",\n        \"direction\": \"out\",\n        \"other\": \"0x008dc510\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0274\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"Resource::PFRecordWrite::GetType\",\n  \"normalized_symbol\": \"record_write_seek_008dcab0\",\n  \"observed_mechanics\": [\n    \"Checks the record state word at state-4 and calls the prepare port on the enclosing record.\",\n    \"Delegates to embedded stream seek slot +0x28 when state+0x68 is nonzero.\",\n    \"Otherwise applies unsigned position/limit operations 0, 1, and 2, publishes +0x60, and returns true.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-RECORD-IO-WAVE6\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-RECORD-IO-WAVE6\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-RECORD-IO-WAVE6\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"prepare/read ports, embedded stream, allocator, and runtime limit ownership remain gated\",\n      \"runtime validation not run\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_triage_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetType.c\",\n    \"file\": \"src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp\",\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetType.c\",\n      \"src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp\"\n    ],\n    \"handoffs\": [\n      \"reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json\"\n    ],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-record-io-wave6/008dcab0.json\"\n    ],\n    \"provenance\": [\n      \"reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json\",\n      \"reconstruction/metadata/pkg-record-io-wave6/008dcab0.json\",\n      \"reconstruction/staging/pkg-record-io-wave6/pkg_record_io_wave6.cpp\",\n      \"reconstruction/staging/pkg-record-io-wave6/pkg_record_io_wave6_model_test.cpp\"\n    ]\n  },\n  \"status\": \"reconstructed\",\n  \"subsystem\": \"IO.RecordIO\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"resource-io\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetType.c\",\n    \"dependencies\": [\n      \"runtime-crt-stl\"\n    ],\n    \"evidence\": \"CONFIR
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
  "body_end": "008dcb61",
  "body_span_bytes": 178,
  "body_start": "008dcab0",
  "callees": [
    "FUN_008dc510"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "008dcab0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Resource::PFRecordWrite::GetType",
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
  "return_type": "uint32_t",
  "return_type_resolved": true,
  "rva": "0x4dcab0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "uint32_t Resource::PFRecordWrite::GetType(IStream * this)",
  "size_bytes": 178,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x008dcab0",
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
      "from": "014368ec"
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
    "prepare/read ports, embedded stream, allocator, and runtime limit ownership remain gated",
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
  "vtable:0x014368c4"
]
```

## Conflicts

```json
[]
```
