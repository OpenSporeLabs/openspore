# Evidence 0x00c472e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a173a7f6d7cbbddbe01db669f230b9efd32ae038480148e46c8875b45312c255`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX, read at 0x00c472e3 into ESI and never written afterwards",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_register": "none (EAX is scratch)",
  "return_semantics": "no value; EAX is clobbered by the four callees and never written back",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    {
      "pop": "0x00c47340",
      "push": "0x00c472e0",
      "register": "EBX"
    },
    {
      "pop": "0x00c4733f",
      "push": "0x00c472e1",
      "register": "EBP"
    },
    {
      "pop": "0x00c4733e",
      "push": "0x00c472e2",
      "register": "ESI"
    },
    {
      "pop": "0x00c4733d",
      "push": "0x00c472eb",
      "register": "EDI"
    }
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00c47341"
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
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +28, so the listing is not one path"
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
  "content_sha256": "5a4e4c4cad7504747cd37f4491566afb4901a6c917e1aa2dab36b26fef350c77",
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
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0026"
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
        "obs-0005",
        "obs-0006",
        "obs-0016"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          156,
          380
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0016",
        "obs-0026"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0026"
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
        "obs-0026"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0026"
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
      "at": "0x00c472e0",
      "count": 2,
      "first_use": 0,
      "first_write_index": 13,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c472e1",
      "count": 2,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00c472e1",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x00c472e2",
      "count": 8,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c472e3",
      "count": 1,
      "first_use": 3,
      "first_write_index": 18,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c472e3",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c472e5",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,dword ptr [ESI + 0x17c]",
      "reg": "EBP",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c472eb",
      "count": 2,
      "first_use": 5,
      "first_write_index": 10,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c472f2",
      "definite": true,
      "id": "obs-0009",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x9c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c472f8",
      "count": 8,
      "first_use": 10,
      "first_write_index": 9,
      "id": "obs-0010",
      "index": 10,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [EAX + 0x13c]",
      "reg": "EAX"
    },
    {
      "at": "0x00c472f8",
      "definite": true,
      "id": "obs-0011",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [EAX + 0x13c]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c472fe",
      "id": "obs-0012",
      "index": 11,
      "kind": "CALL_DIRECT",
      "raw": "CALL 
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "context_word_read_00ce6950",
    "reconstructed": true,
    "va": "0x00ce6950"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4b760"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4db40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4e230"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4f160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4fe60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c50190"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c50460"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c51ac0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c51e40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c52e30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c52ea0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c55500"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c5f280"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c5f360"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c61570"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c62100"
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
  "count": 38,
  "instructions": [
    {
      "address": "00c472e0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c472e1",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c472e2",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c472e3",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c472e5",
      "instruction": "MOV EBP,dword ptr [ESI + 0x17c]"
    },
    {
      "address": "00c472eb",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c472ec",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "00c472ee",
      "instruction": "JNZ 0x00c472f2"
    },
    {
      "address": "00c472f0",
      "instruction": "MOV EBP,ESI"
    },
    {
      "address": "00c472f2",
      "instruction": "MOV EAX,dword ptr [ESI + 0x9c]"
    },
    {
      "address": "00c472f8",
      "instruction": "MOV EDI,dword ptr [EAX + 0x13c]"
    },
    {
      "address": "00c472fe",
      "instruction": "CALL 0x00c451e0"
    },
    {
      "address": "00c47303",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00c47305",
      "instruction": "MOV EBX,dword ptr [EAX + 0x84]"
    },
    {
      "address": "00c4730b",
      "instruction": "MOV EAX,dword ptr [EDX + 0x10c]"
    },
    {
      "address": "00c47311",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c47313",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c47315",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c47316",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c47318",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c4731a",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00c4731c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c4731d",
      "instruction": "MOV EAX,dword ptr [EDX + 0xa4]"
    },
    {
      "address": "00c47323",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c47325",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c47327",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c47328",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c4732a",
      "instruction": "CALL 0x00ce6950"
    },
    {
      "address": "00c4732f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c47330",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c47331",
      "instruction": "CALL 0x00b3d4a0"
    },
    {
      "address": "00c47336",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c47338",
      "instruction": "CALL 0x00aeb7a0"
    },
    {
      "address": "00c4733d",
      "instruction": "POP EDI"
    },
    {
      "address": "00c4733e",
      "instruction": "POP ESI"
    },
    {
      "address": "00c4733f",
      "instruction": "POP EBP"
    },
    {
      "address": "00c47340",
      "instruction": "POP EBX"
    },
    {
      "address": "00c47341",
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
  "original_bytes": 13507,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX, read at 0x00c472e3 into ESI and never written afterwards\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"none (EAX is scratch)\",\n    \"return_semantics\": \"no value; EAX is clobbered by the four callees and never written back\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      {\n        \"pop\": \"0x00c47340\",\n        \"push\": \"0x00c472e0\",\n        \"register\": \"EBX\"\n      },\n      {\n        \"pop\": \"0x00c4733f\",\n        \"push\": \"0x00c472e1\",\n        \"register\": \"EBP\"\n      },\n      {\n        \"pop\": \"0x00c4733e\",\n        \"push\": \"0x00c472e2\",\n        \"register\": \"ESI\"\n      },\n      {\n        \"pop\": \"0x00c4733d\",\n        \"push\": \"0x00c472eb\",\n        \"register\": \"EDI\"\n      }\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET at 0x00c47341\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 3,\n      \"symbol\": \"context_word_read_00ce6950\",\n      \"va\": \"0x00ce6950\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"context_word_read_00ce6950\",\n        \"reconstructed\": true,\n        \"va\": \"0x00ce6950\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4b760\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4db40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4e230\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4f160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4fe60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c50190\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c50460\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c51ac0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c51e40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c52e30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c52ea0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c55500\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5f280\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5f360\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c61570\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c62100\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c63130\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c63170\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c631b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c63330\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsi
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
  "body_end": "00c47341",
  "body_span_bytes": 98,
  "body_start": "00c472e0",
  "callees": [
    "FUN_00ce6950",
    "FUN_00c451e0",
    "thunk_FUN_00aeb160",
    "FUN_00b3d4a0"
  ],
  "callers": [
    "FUN_00c63170",
    "FUN_00c50460",
    "FUN_00c51ac0",
    "FUN_00c4b760",
    "FUN_00c631b0",
    "FUN_00c50190",
    "FUN_00c4fe60",
    "FUN_00c55500",
    "FUN_00c51e40",
    "FUN_00c4db40",
    "FUN_00c61570",
    "FUN_00c52e30",
    "FUN_00c63330",
    "FUN_00c4e230",
    "FUN_00c4f160",
    "FUN_00c52ea0",
    "FUN_00c5f280",
    "FUN_00c5f360",
    "FUN_00c63130",
    "FUN_00c62100"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c472e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00c472e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8472e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c472e0(void)",
  "size_bytes": 98,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c472e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 23,
  "xrefs": [
    {
      "from": "00c4b78f"
    },
    {
      "from": "00c4db76"
    },
    {
      "from": "00c4e266"
    },
    {
      "from": "00c4f193"
    },
    {
      "from": "00c4ffc8"
    },
    {
      "from": "00c50172"
    },
    {
      "from": "00c501cb"
    },
    {
      "from": "00c50486"
    },
    {
      "from": "00c51aef"
    },
    {
      "from": "00c51e76"
    },
    {
      "from": "00c52e85"
    },
    {
      "from": "00c52f04"
    },
    {
      "from": "00c5552f"
    },
    {
      "from": "00c5f2af"
    },
    {
      "from": "00c5f39d"
    },
    {
      "from": "00c615b1"
    },
    {
      "from": "00c6212f"
    },
    {
      "from": "00c6315f"
    },
    {
      "from": "00c6319f"
    },
    {
      "from": "00c631df"
    },
    {
      "from": "00c63366"
    },
    {
      "from": "00c5ea0a"
    },
    {
      "from": "00c6285b"
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
    "reconstruction/staging/wave13-pilot-core-b01/c472e0_mission_publish.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-core-b01/00c472e0.json"
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
    "A runtime differential test would be needed to confirm the runtime value of 0x0167eb44, the number of records the registry accumulates across a mission transition, and that no runtime patch retargets the two virtual slots.",
    "No original-process trace exists for 0x00c472e0. The classification rests entirely on static reads of SporeApp.exe 3.1.0.22.",
    "The concrete overrides reached through slots +0x10c and +0xa4 can only be named by observing a receiver whose vtable base is known at run time."
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
