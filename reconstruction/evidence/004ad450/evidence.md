# Evidence 0x004ad450

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `cb5caafdc8e52e2c1c8f82c3eccf56cdf7ee54208caaac5877a333400d3d1ed2`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (receiver in ECX), no stack arguments",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is read only by the spill at 0x004ad456",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x004ad45c loads the field into ECX, 0x004ad45f stores it to [EBP-4] and 0x004ad462 loads it straight back into EAX; the round trip through the frame slot is a register-allocation artefact with no effect. There is no null check and no LEA, so the value is the field itself and not &field.",
  "return_register": "EAX",
  "return_semantics": "the pointer stored at receiver+0x30, unmodified and untested",
  "return_type": "void*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single RET at 0x004ad468"
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
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EBP"
    ],
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
  "content_sha256": "dce3801c58b5a50afe80c4e5984e64c2b650218d305637c1e4a7623ac33cdc8f",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall (receiver in ECX), no stack arguments"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0015"
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
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011",
        "obs-0012"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          48
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0015"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0015"
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
        "obs-0015"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0015"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x004ad450",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x004ad450",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": 8
    },
    {
      "at": "0x004ad451",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x004ad451",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004ad453",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x004ad456",
      "count": 2,
      "first_use": 3,
      "first_write_index": 5,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0x8],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x004ad456",
      "base": "EBP",
      "disp": -8,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x8],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x004ad459",
      "base": "EBP",
      "disp": -8,
      "id": "obs-0008",
      "index": 4,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + -0x8]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x004ad459",
      "definite": true,
      "id": "obs-0009",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBP + -0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x004ad45c",
      "count": 1,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0010",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [EAX + 0x30]",
      "reg": "EAX"
    },
    {
      "at": "0x004ad45c",
      "definite": true,
      "id": "obs-0011",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EAX + 0x30]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x004ad45f",
   
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
    "va": "0x0048d010"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0048dcd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00491b40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004956b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004a6690"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057d710"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005b9840"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005ba320"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005bb5a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005bc0f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005bccc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005d27e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005d36e0"
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
  "count": 11,
  "instructions": [
    {
      "address": "004ad450",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004ad451",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004ad453",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "004ad456",
      "instruction": "MOV dword ptr [EBP + -0x8],ECX"
    },
    {
      "address": "004ad459",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "004ad45c",
      "instruction": "MOV ECX,dword ptr [EAX + 0x30]"
    },
    {
      "address": "004ad45f",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "004ad462",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004ad465",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004ad467",
      "instruction": "POP EBP"
    },
    {
      "address": "004ad468",
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
  "original_bytes": 11883,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall (receiver in ECX), no stack arguments\",\n    \"hidden_receiver\": \"ECX\",\n    \"hidden_this_register\": \"ECX is read only by the spill at 0x004ad456\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x004ad45c loads the field into ECX, 0x004ad45f stores it to [EBP-4] and 0x004ad462 loads it straight back into EAX; the round trip through the frame slot is a register-allocation artefact with no effect. There is no null check and no LEA, so the value is the field itself and not &field.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"the pointer stored at receiver+0x30, unmodified and untested\",\n    \"return_type\": \"void*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"single RET at 0x004ad468\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"palette_safe_wave11_fill_node_array_005c7ff0\",\n      \"va\": \"0x005c7ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"service_005fa8d0\",\n      \"va\": \"0x005fa8d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"service_0060ee90\",\n      \"va\": \"0x0060ee90\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"re_00835380\",\n      \"va\": \"0x00835380\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-WAVE6-CONTAINERS-MEMORY\",\n      \"score\": 3,\n      \"symbol\": \"wave6_fixed_pool_allocator_alloc_00926100\",\n      \"va\": \"0x00926100\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"re_00951220\",\n      \"va\": \"0x00951220\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0048d010\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0048dcd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00491b40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004956b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a6690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057d710\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005b9840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005ba320\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005bb5a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005bc0f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005bccc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005d27e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005d36e0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0048d56d\",\n        \"direction\": \"in\",\n        \"other\": \"0x0048d010\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0048dd3c\",\n        \"direction\": \"in\",\n        \"other\": \"0x0048dcd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0048e231\",\n        \"direction\": \"in\",\n        \"other\": \"0x0048dcd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0048e292\",\n        \"direction\": \"in\",\n        \"other\": \"0x0048dcd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0048e4c6\",\n        \"direction\": \"in\",\n        \"other\": \"0x0048dcd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0048e4d9\",\n        \"direction\": \"in\",\n        \"other\": \"0x0048dcd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004926f2\",\n        \"direction\": \"in\",\n        \"other\": \"0x004
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
  "body_end": "004ad468",
  "body_span_bytes": 25,
  "body_start": "004ad450",
  "callees": [],
  "callers": [
    "FUN_005bccc0",
    "FUN_0048d010",
    "FUN_005b9840",
    "FUN_005d27e0",
    "FUN_004a6690",
    "FUN_004956b0",
    "FUN_0048dcd0",
    "FUN_005bc0f0",
    "FUN_005d36e0",
    "FUN_00491b40",
    "FUN_005ba320",
    "FUN_005bb5a0",
    "FUN_0057d710"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "004ad450",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_004ad450",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xad450",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004ad450(void)",
  "size_bytes": 25,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004ad450",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 29,
  "xrefs": [
    {
      "from": "00495732"
    },
    {
      "from": "0048d56d"
    },
    {
      "from": "004a6c3a"
    },
    {
      "from": "004a6c5b"
    },
    {
      "from": "004a6c76"
    },
    {
      "from": "0048dd3c"
    },
    {
      "from": "0048e231"
    },
    {
      "from": "0048e292"
    },
    {
      "from": "0048e4c6"
    },
    {
      "from": "0048e4d9"
    },
    {
      "from": "004926f2"
    },
    {
      "from": "004927c4"
    },
    {
      "from": "005d3c1b"
    },
    {
      "from": "005d2e68"
    },
    {
      "from": "005b9af2"
    },
    {
      "from": "005b9aff"
    },
    {
      "from": "005baea6"
    },
    {
      "from": "005baff0"
    },
    {
      "from": "005bb75a"
    },
    {
      "from": "005bb867"
    },
    {
      "from": "005bb8e8"
    },
    {
      "from": "005bbd96"
    },
    {
      "from": "005bbf05"
    },
    {
      "from": "005bc2b5"
    },
    {
      "from": "005bd0a6"
    },
    {
      "from": "005bd0e7"
    },
    {
      "from": "005bd483"
    },
    {
      "from": "005bd491"
    },
    {
      "from": "0057dc44"
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
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b04/004ad450_related_pointer_getter.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/004ad450_related_pointer_getter.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b04/004ad450.json"
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
    "No original-process trace has been captured. Whether the +0x30 pointer is ever null at a callsite is a runtime fact; statically the getter propagates whatever is there.",
    "The 26 uninspected callsites need at least a sample disassembled before the uniform 'result is the next receiver' reading can be generalised."
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "void*"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
