# Evidence 0x00b8dde0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d7b2856e1c4e6ce1adf1185e9f13212579647aa1ab3cde22341e3cde189a0355`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "read; the receiver's +0x1A4, +0x1A8 and +0x1AC fields are the comparison targets and the write destinations",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "0x00b8dde1e is a bare RET 0x8 with no value in EAX that any caller reads; the twelve inspected callsites all discard EAX or reload it immediately.",
  "return_register": "none - EAX is used as a scratch load at 0x00b8dde3 and 0x00b8dde15 and its exit value is never consumed",
  "return_semantics": "none; the function's only effect is the conditional write of three dwords into the receiver",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_arguments": [
    {
      "instruction": "0x00b8dde0: MOV EAX,dword ptr [ESP + 0x4]",
      "offset": "ESP+0x4",
      "role": "pointer to a 12-byte ResourceKey {instanceID, typeID, groupID}",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "single exit at 0x00b8dde1e"
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
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "68aad9f281c32b32bc6e2ce0f1459bbe749c1b20f0e79fa663e8d4df9704b5fd",
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
    "ghidra_parameter_count": 0,
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
        "obs-0008"
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
        "obs-0002"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          420,
          424,
          428
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
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
      "at": "0x00b8dde0",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00b8dde0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00b8dde0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b8dde4",
      "count": 7,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x00b8dde4",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b8dde6",
      "count": 6,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "CMP EDX,dword ptr [ECX + 0x1a4]",
      "reg": "ECX"
    },
    {
      "at": "0x00b8de06",
      "count": 2,
      "first_use": 11,
      "first_write_index": 1,
      "id": "obs-0007",
      "index": 11,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ECX + 0x1a4],EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00b8de1e",
      "form": "RET 0x8",
      "id": "obs-0008",
      "imm": 8,
      "index": 16,
      "kind": "RET",
      "raw": "RET 0x8"
    }
  ],
  "parse": {
    "declared_count": 17,
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
      "
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
    "va": "0x00ba5fd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba6120"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba6310"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba64a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba7c20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba8830"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb2a50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbaa80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbac80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c713c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00de6f20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f37690"
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
  "count": 17,
  "instructions": [
    {
      "address": "00b8dde0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00b8dde4",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00b8dde6",
      "instruction": "CMP EDX,dword ptr [ECX + 0x1a4]"
    },
    {
      "address": "00b8ddec",
      "instruction": "JNZ 0x00b8de04"
    },
    {
      "address": "00b8ddee",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00b8ddf1",
      "instruction": "CMP EDX,dword ptr [ECX + 0x1a8]"
    },
    {
      "address": "00b8ddf7",
      "instruction": "JNZ 0x00b8de04"
    },
    {
      "address": "00b8ddf9",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00b8ddfc",
      "instruction": "CMP EDX,dword ptr [ECX + 0x1ac]"
    },
    {
      "address": "00b8de02",
      "instruction": "JZ 0x00b8de1e"
    },
    {
      "address": "00b8de04",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00b8de06",
      "instruction": "MOV dword ptr [ECX + 0x1a4],EDX"
    },
    {
      "address": "00b8de0c",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00b8de0f",
      "instruction": "MOV dword ptr [ECX + 0x1a8],EDX"
    },
    {
      "address": "00b8de15",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00b8de18",
      "instruction": "MOV dword ptr [ECX + 0x1ac],EAX"
    },
    {
      "address": "00b8de1e",
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
  "original_bytes": 11672,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"read; the receiver's +0x1A4, +0x1A8 and +0x1AC fields are the comparison targets and the write destinations\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x8\",\n    \"return_observation\": \"0x00b8dde1e is a bare RET 0x8 with no value in EAX that any caller reads; the twelve inspected callsites all discard EAX or reload it immediately.\",\n    \"return_register\": \"none - EAX is used as a scratch load at 0x00b8dde3 and 0x00b8dde15 and its exit value is never consumed\",\n    \"return_semantics\": \"none; the function's only effect is the conditional write of three dwords into the receiver\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [],\n    \"stack_arguments\": [\n      {\n        \"instruction\": \"0x00b8dde0: MOV EAX,dword ptr [ESP + 0x4]\",\n        \"offset\": \"ESP+0x4\",\n        \"role\": \"pointer to a 12-byte ResourceKey {instanceID, typeID, groupID}\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"single exit at 0x00b8dde1e\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5fd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba6120\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba6310\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba64a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba7c20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba8830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb2a50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbaa80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbac80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c713c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00de6f20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f37690\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00ba6073\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba5fd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba6169\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba6120\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba6355\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba6310\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba6550\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba64a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba7d36\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba7c20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba8938\",\n   
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
  "body_end": "00b8de20",
  "body_span_bytes": 65,
  "body_start": "00b8dde0",
  "callees": [],
  "callers": [
    "FUN_00ba5fd0",
    "FUN_00ba8830",
    "FUN_00ba6120",
    "FUN_00bbaa80",
    "FUN_00ba6310",
    "FUN_00bb2a50",
    "FUN_00bbac80",
    "FUN_00de6f20",
    "FUN_00ba7c20",
    "FUN_00c713c0",
    "FUN_00f37690",
    "FUN_00ba64a0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00b8dde0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b8dde0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x78dde0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b8dde0(void)",
  "size_bytes": 65,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b8dde0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 16,
  "xrefs": [
    {
      "from": "00ba8938"
    },
    {
      "from": "00ba6355"
    },
    {
      "from": "00ba7d36"
    },
    {
      "from": "00bb2cc0"
    },
    {
      "from": "00bb2de3"
    },
    {
      "from": "00bb2f0f"
    },
    {
      "from": "00bb302f"
    },
    {
      "from": "00bb314c"
    },
    {
      "from": "00bbac10"
    },
    {
      "from": "00ba6073"
    },
    {
      "from": "00ba6169"
    },
    {
      "from": "00bbacc8"
    },
    {
      "from": "00c713d1"
    },
    {
      "from": "00de6f94"
    },
    {
      "from": "00f37993"
    },
    {
      "from": "00ba6550"
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
    "reconstruction/staging/wave13-w1-core-b06/b8dde0_planet_record_store_terrain_key.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b06/00b8dde0.json"
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
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
    "No runtime evidence can distinguish 'write the same value' from 'skip the write' by observing memory alone, so any differential fixture for this function must observe side channels, not state.",
    "The change check is only observable through a watcher. A differential test must instrument the field or the paired getter to confirm that a redundant write really is suppressed, and to establish why the compiler emitted the check.",
    "The consume-once behaviour of the paired getter 0x00b8dd60 is a runtime claim about the materialisation service obtained from 0x00f48a80; a write watchpoint on record+0x1A4 across a full planet load is required to confirm it."
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
  "void"
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
