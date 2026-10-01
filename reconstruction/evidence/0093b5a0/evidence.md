# Evidence 0x0093b5a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `658c6d7c25aa7cbef2372d1d4e225664fd057501d9425dfd7a566ff44a77fca3`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "receiver_register": "ECX",
  "return_type": "void",
  "stack_arguments": [],
  "termination": "plain RET"
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
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "b6ae5fc6826247c7eb507b9e829289c844b812c40df38148de3291198cbc4533",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 4,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017"
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
        "obs-0003",
        "obs-0004",
        "obs-0007",
        "obs-0008"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          4,
          12,
          16,
          20,
          28,
          32,
          36,
          44,
          48
        ],
        "register": "ECX",
        "written_through": 9
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0007",
        "obs-0008",
        "obs-0017"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0017"
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
        "obs-0017"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0017"
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
      "at": "0x0093b5a0",
      "count": 14,
      "first_use": 0,
      "first_write_index": 2,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0093b5a1",
      "count": 9,
      "first_use": 1,
      "first_write_index": 3,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x0093b5a2",
      "count": 2,
      "first_use": 2,
      "first_write_index": 8,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0093b5a2",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x0093b5a4",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "XOR EDI,EDI",
      "reg": "EDI",
      "write_kind": "zero"
    },
    {
      "at": "0x0093b5b1",
      "id": "obs-0006",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0093af00",
      "target": "0x0093af00"
    },
    {
      "at": "0x0093b5b6",
      "definite": true,
      "id": "obs-0007",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x4]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0093b5cf",
      "definite": true,
      "id": "obs-0008",
      "index": 17,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0093b5d1",
      "count": 3,
      "first_use": 18,
      "first_write_index": 17,
      "id": "obs-0009",
      "index": 18,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x8]",
      "reg": "EAX"
    },
    {
      "at": "0x0093b5d1",
      "definite": true,
      "id": "obs-0010",
      "index": 18,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x8]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0093b5d4",
      "count": 1,
      "first_use": 19,
      "first_write_index": 18,
      "id": "obs-0011",
      "index": 19,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x0093b5d4",
      "base": "EDX",
      "disp": null,
      "id": "obs-0012",
      "index": 19,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x
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
    "va": "0x006ab120"
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
    "name": "stream_child_close_and_maybe_delete_0093b610",
    "reconstructed": true,
    "va": "0x0093b610"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e4c130"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0120ddd8"
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
  "count": 37,
  "instructions": [
    {
      "address": "0093b5a0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0093b5a1",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0093b5a2",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0093b5a4",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "0093b5a6",
      "instruction": "MOV dword ptr [ESI],0x143eaac"
    },
    {
      "address": "0093b5ac",
      "instruction": "CMP dword ptr [ESI + 0x4],EDI"
    },
    {
      "address": "0093b5af",
      "instruction": "JZ 0x0093b5d9"
    },
    {
      "address": "0093b5b1",
      "instruction": "CALL 0x0093af00"
    },
    {
      "address": "0093b5b6",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "0093b5b9",
      "instruction": "MOV dword ptr [ESI + 0x1c],EDI"
    },
    {
      "address": "0093b5bc",
      "instruction": "MOV dword ptr [ESI + 0x20],EDI"
    },
    {
      "address": "0093b5bf",
      "instruction": "MOV dword ptr [ESI + 0x2c],EDI"
    },
    {
      "address": "0093b5c2",
      "instruction": "MOV dword ptr [ESI + 0x30],EDI"
    },
    {
      "address": "0093b5c5",
      "instruction": "MOV dword ptr [ESI + 0xc],EDI"
    },
    {
      "address": "0093b5c8",
      "instruction": "MOV dword ptr [ESI + 0x10],EDI"
    },
    {
      "address": "0093b5cb",
      "instruction": "CMP ECX,EDI"
    },
    {
      "address": "0093b5cd",
      "instruction": "JZ 0x0093b5d6"
    },
    {
      "address": "0093b5cf",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "0093b5d1",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "0093b5d4",
      "instruction": "CALL EDX"
    },
    {
      "address": "0093b5d6",
      "instruction": "MOV dword ptr [ESI + 0x4],EDI"
    },
    {
      "address": "0093b5d9",
      "instruction": "MOV EAX,dword ptr [ESI + 0x14]"
    },
    {
      "address": "0093b5dc",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "0093b5de",
      "instruction": "JZ 0x0093b5ec"
    },
    {
      "address": "0093b5e0",
      "instruction": "MOV ECX,dword ptr [0x016c8b44]"
    },
    {
      "address": "0093b5e6",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0093b5e7",
      "instruction": "CALL 0x009276c0"
    },
    {
      "address": "0093b5ec",
      "instruction": "MOV EAX,dword ptr [ESI + 0x24]"
    },
    {
      "address": "0093b5ef",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "0093b5f1",
      "instruction": "JZ 0x0093b5ff"
    },
    {
      "address": "0093b5f3",
      "instruction": "MOV ECX,dword ptr [0x016c8b44]"
    },
    {
      "address": "0093b5f9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0093b5fa",
      "instruction": "CALL 0x009276c0"
    },
    {
      "address": "0093b5ff",
      "instruction": "POP EDI"
    },
    {
      "address": "0093b600",
      "instruction": "MOV dword ptr [ESI],0x13f3a68"
    },
    {
      "address": "0093b606",
      "instruction": "POP ESI"
    },
    {
      "address": "0093b607",
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
  "original_bytes": 8514,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"receiver_register\": \"ECX\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [],\n    \"termination\": \"plain RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:StreamChild,StreamChild*,StreamChildLifecycleServices\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"wave6-serialization-persistence\",\n      \"score\": 33,\n      \"symbol\": \"stream_child_close_and_maybe_delete_0093b610\",\n      \"va\": \"0x0093b610\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-serialization-persistence\",\n      \"score\": 10,\n      \"symbol\": \"memory_stream_initialize_0093bd50\",\n      \"va\": \"0x0093bd50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-serialization-persistence\",\n      \"score\": 10,\n      \"symbol\": \"memory_stream_set_position_0093c0c0\",\n      \"va\": \"0x0093c0c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The vtable transitions, flush-before-parent-reload, exact clear order, parent release after clearing, allocator reload per block, and final vtable are exact; concrete ownership remains unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"StreamChild\",\n  \"cluster\": null,\n  \"confidence\": 0.93,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006ab120\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x008d6ed0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0091c640\"\n      },\n      {\n        \"name\": \"stream_child_close_and_maybe_delete_0093b610\",\n        \"reconstructed\": true,\n        \"va\": \"0x0093b610\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e4c130\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0120ddd8\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006ab2f5\",\n        \"direction\": \"in\",\n        \"other\": \"0x006ab120\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x008d71d5\",\n        \"direction\": \"in\",\n        \"other\": \"0x008d6ed0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0091c85d\",\n        \"direction\": \"in\",\n        \"other\": \"0x0091c640\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0093b613\",\n        \"direction\": \"in\",\n        \"other\": \"0x0093b610\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e4c1ff\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e4c130\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e4c2f7\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e4c130\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0120dddb\",\n        \"direction\": \"in\",\n        \"other\": \"0x0120ddd8\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0093b5e7\",\n        \"direction\": \"out\",\n        \"other\": \"0x009276c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0093b5fa\",\n        \"direction\": \"out\",\n        \"other\": \"0x009276c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0093b5b1\",\n        \"direction\": \"out\",\n        \"other\": \"0x0093af00\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 6,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x0093af00\",\n      \"parent vtable +0x08\",\n      \"0x009276c0\"\n    ],\n    \"manifest_callers\": [\n      \"0x006ab120\",\n      \"0x008d6ed0\",\n      \"0x0091c640\",\n      \"0x0093b610\",\n      \"0x00e4c130\"\n    ],\n    \"nearby_reconstructed
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
  "body_end": "0093b607",
  "body_span_bytes": 104,
  "body_start": "0093b5a0",
  "callees": [
    "FUN_0093af00",
    "FUN_009276c0"
  ],
  "callers": [
    "StreamChild_Close",
    "FUN_00e4c130",
    "FUN_006ab120",
    "FUN_0091c640",
    "FUN_008d6ed0",
    "Unwind@0120ddd8"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0093b5a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "IO::StreamChild::Open",
  "namespace": "IO",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 4,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "StreamChild *"
    },
    {
      "name": "pStreamParent",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "IStream *"
    },
    {
      "name": "nPosition",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "size_type"
    },
    {
      "name": "nSize",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "size_type"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x53b5a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool IO::StreamChild::Open(StreamChild * this, IStream * pStreamParent, size_type nPosition, size_type nSize)",
  "size_bytes": 104,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0093b5a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "0120dddb"
    },
    {
      "from": "006ab2f5"
    },
    {
      "from": "008d71d5"
    },
    {
      "from": "0091c85d"
    },
    {
      "from": "0093b613"
    },
    {
      "from": "00e4c1ff"
    },
    {
      "from": "00e4c2f7"
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
  "file": "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp",
  "files": [
    "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp",
    "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.hpp",
    "src/reconstruction/wave6_serialization_persistence/stream_lifecycle_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-serialization-persistence/0093b5a0.json"
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
    "gate-stream-child-parent-block-and-allocator-lifecycle"
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
  "IStream",
  "StreamChild",
  "StreamChild*",
  "StreamChildLifecycleServices",
  "StreamChildTeardownWindow",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f3a68"
]
```

## Conflicts

```json
[]
```
