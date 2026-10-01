# Evidence 0x0093c0c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `667cf7643e88d67b949d25494536fcea864b4fb6786759f414a9588553693712`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "receiver_register": "ECX",
  "return_register": "AL",
  "return_type": "bool",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "operation",
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "amount",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "termination": "RET 0x8"
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
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "7e013a09c2ae6822a1078c2b4d6004c06bcfa601acdb5a7988972b41de166246",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 3,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0019",
        "obs-0022",
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
        "obs-0002",
        "obs-0010",
        "obs-0011",
        "obs-0014"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0009",
        "obs-0013"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          12,
          20,
          24
        ],
        "register": "ECX",
        "written_through": 4
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0009",
        "obs-0013",
        "obs-0019",
        "obs-0022",
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
        "obs-0022",
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
        "obs-0022",
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
        "obs-0022",
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
      "at": "0x0093c0c0",
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
      "at": "0x0093c0c0",
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
      "at": "0x0093c0c0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0093c0c7",
      "count": 11,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0093c0c8",
      "count": 4,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0093c0c8",
  
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
    "va": "0x0041c1d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00902d40"
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
  "count": 45,
  "instructions": [
    {
      "address": "0093c0c0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0093c0c4",
      "instruction": "SUB EAX,0x0"
    },
    {
      "address": "0093c0c7",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0093c0c8",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0093c0ca",
      "instruction": "MOV ECX,dword ptr [ESI + 0x14]"
    },
    {
      "address": "0093c0cd",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0093c0ce",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "0093c0d0",
      "instruction": "JZ 0x0093c0f0"
    },
    {
      "address": "0093c0d2",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "0093c0d5",
      "instruction": "JZ 0x0093c0e5"
    },
    {
      "address": "0093c0d7",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "0093c0da",
      "instruction": "JNZ 0x0093c0f7"
    },
    {
      "address": "0093c0dc",
      "instruction": "MOV EAX,dword ptr [ESI + 0xc]"
    },
    {
      "address": "0093c0df",
      "instruction": "ADD EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "0093c0e3",
      "instruction": "JMP 0x0093c0f4"
    },
    {
      "address": "0093c0e5",
      "instruction": "MOV EDX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "0093c0e9",
      "instruction": "ADD ECX,EDX"
    },
    {
      "address": "0093c0eb",
      "instruction": "MOV dword ptr [ESI + 0x14],ECX"
    },
    {
      "address": "0093c0ee",
      "instruction": "JMP 0x0093c0f7"
    },
    {
      "address": "0093c0f0",
      "instruction": "MOV EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "0093c0f4",
      "instruction": "MOV dword ptr [ESI + 0x14],EAX"
    },
    {
      "address": "0093c0f7",
      "instruction": "MOV EAX,dword ptr [ESI + 0x14]"
    },
    {
      "address": "0093c0fa",
      "instruction": "MOV ECX,dword ptr [ESI + 0xc]"
    },
    {
      "address": "0093c0fd",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "0093c0ff",
      "instruction": "JBE 0x0093c125"
    },
    {
      "address": "0093c101",
      "instruction": "CMP byte ptr [ESI + 0x18],0x0"
    },
    {
      "address": "0093c105",
      "instruction": "JZ 0x0093c11b"
    },
    {
      "address": "0093c107",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0093c108",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0093c10a",
      "instruction": "CALL 0x0093c000"
    },
    {
      "address": "0093c10f",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0093c111",
      "instruction": "JNZ 0x0093c125"
    },
    {
      "address": "0093c113",
      "instruction": "MOV dword ptr [ESI + 0x14],EDI"
    },
    {
      "address": "0093c116",
      "instruction": "POP EDI"
    },
    {
      "address": "0093c117",
      "instruction": "POP ESI"
    },
    {
      "address": "0093c118",
      "instruction": "RET 0x8"
    },
    {
      "address": "0093c11b",
      "instruction": "POP EDI"
    },
    {
      "address": "0093c11c",
      "instruction": "MOV dword ptr [ESI + 0x14],ECX"
    },
    {
      "address": "0093c11f",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "0093c121",
      "instruction": "POP ESI"
    },
    {
      "address": "0093c122",
      "instruction": "RET 0x8"
    },
    {
      "address": "0093c125",
      "instruction": "POP EDI"
    },
    {
      "address": "0093c126",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "0093c128",
      "instruction": "POP ESI"
    },
    {
      "address": "0093c129",
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
  "original_bytes": 8216,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"receiver_register\": \"ECX\",\n    \"return_register\": \"AL\",\n    \"return_type\": \"bool\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"operation\",\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"amount\",\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:MemoryStream,MemoryStream*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-serialization-persistence\",\n      \"score\": 27,\n      \"symbol\": \"memory_stream_initialize_0093bd50\",\n      \"va\": \"0x0093bd50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-serialization-persistence\",\n      \"score\": 10,\n      \"symbol\": \"stream_child_teardown_0093b5a0\",\n      \"va\": \"0x0093b5a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-serialization-persistence\",\n      \"score\": 10,\n      \"symbol\": \"stream_child_close_and_maybe_delete_0093b610\",\n      \"va\": \"0x0093b610\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Operation selection, uint32 wraparound, target publication before comparison, size-not-capacity comparison, disabled-growth clamp, delegated growth, and rollback are exact; allocation remains gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"MemoryStream\",\n  \"cluster\": \"resource-io\",\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0041c1d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00902d40\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0041c81b\",\n        \"direction\": \"in\",\n        \"other\": \"0x0041c1d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00902f04\",\n        \"direction\": \"in\",\n        \"other\": \"0x00902d40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00902f27\",\n        \"direction\": \"in\",\n        \"other\": \"0x00902d40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0093c10a\",\n        \"direction\": \"out\",\n        \"other\": \"0x0093c000\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 2,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x0093c000\"\n    ],\n    \"manifest_callers\": [\n      \"0x0041c1d0\",\n      \"0x00902d40\",\n      \"data_xref_0143eba0\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0289\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"IO::MemoryStream::Write\",\n  \"normalized_symbol\": \"memory_stream_set_position_0093c0c0\",\n  \"observed_mechanics\": [\n    \"operation 0 uses amount\",\n    \"operation 1 adds amount to position\",\n    \"operation 2 adds amount to size\",\n    \"other operations preserve position\",\n    \"publish target before compare\",\n    \"compare target with size at +0x0c\",\n    \"clamp when growth disabled\",\n    \"delegate growth when enabled\",\n    \"restore original position on growth failure\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"wave6-serialization-persistence\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"wave6-serialization-persistence\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"wave6-serialization-persistence\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-memory-stream-pos
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
  "body_end": "0093c12b",
  "body_span_bytes": 108,
  "body_start": "0093c0c0",
  "callees": [
    "FUN_0093c000"
  ],
  "callers": [
    "FUN_0041c1d0",
    "FUN_00902d40"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0093c0c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "IO::MemoryStream::Write",
  "namespace": "IO",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "MemoryStream *"
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
  "rva": "0x53c0c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "int IO::MemoryStream::Write(MemoryStream * this, void * pData, size_t nSize)",
  "size_bytes": 108,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0093c0c0",
  "vtables": {
    "referenced_by_vtables": [
      "0x0143eb70",
      "0x0143cae8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "0041c81b"
    },
    {
      "from": "0143cb10"
    },
    {
      "from": "0143eba0"
    },
    {
      "from": "00902f04"
    },
    {
      "from": "00902f27"
    },
    {
      "from": "00811d32"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/IO__MemoryStream__Write.c",
  "file": "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/IO__MemoryStream__Write.c",
    "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp",
    "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.hpp",
    "src/reconstruction/wave6_serialization_persistence/stream_lifecycle_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-serialization-persistence/0093c0c0.json"
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
    "gate-memory-stream-position-growth-and-allocation"
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
  "MemoryStream",
  "MemoryStream*",
  "MemoryStreamServices",
  "bool",
  "uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0143cae8",
  "vtable:0x0143eb70",
  "vtable:0x0143eb78",
  "vtable:0x0143eba0"
]
```

## Conflicts

```json
[]
```
