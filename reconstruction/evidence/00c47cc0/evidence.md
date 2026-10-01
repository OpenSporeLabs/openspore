# Evidence 0x00c47cc0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e62e82e3094b5b86f1040cd9564c1016a352caf0f26760b21f69d711b5d53575`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall with one callee-cleaned stack dword",
  "hidden_receiver": "read",
  "hidden_this_register": "ECX, read directly, never copied or modified",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_register": null,
  "return_semantics": "no return value; EAX is left holding the argument on exit",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_arguments": [
    {
      "meaning": "the new state/phase value",
      "observed_values": [
        1,
        2,
        3,
        5,
        6,
        7,
        8,
        9,
        "one dynamic value forwarded from a virtual slot +0x7c"
      ],
      "offset_at_entry": "[ESP + 0x4]",
      "read_at": "0x00c47cc0",
      "slot": 0,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "83f13192ec6258de7e9c196e1dca0068cba10db55e7e14505886a2f2384bc9a7",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall with one callee-cleaned stack dword"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0023"
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
        "obs-0002"
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
        "obs-0006",
        "obs-0007",
        "obs-0015",
        "obs-0017",
        "obs-0018",
        "obs-0019",
        "obs-0021"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          132,
          332,
          336,
          348,
          352
        ],
        "register": "ECX",
        "written_through": 6
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0015",
        "obs-0017",
        "obs-0018",
        "obs-0019",
        "obs-0021",
        "obs-0023"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0023"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
      }
    },
    {
      "based_on": [
        "obs-0023"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0023"
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
      "at": "0x00c47cc0",
      "count": 10,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00c47cc0",
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
      "at": "0x00c47cc0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "and_esp": null,
      "at": "0x00c47cc4",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0004",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x40",
      "sub": 64
    },
    {
      "at": "0x00c47cc4",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x40",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c47cc7",
      "count": 1
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
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
    "va": "0x00c48470"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c484e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c485b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c485c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c485d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c485e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c485f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c5a0b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fef3b0"
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
  "count": 43,
  "instructions": [
    {
      "address": "00c47cc0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00c47cc4",
      "instruction": "SUB ESP,0x40"
    },
    {
      "address": "00c47cc7",
      "instruction": "CMP dword ptr [ECX + 0x84],EAX"
    },
    {
      "address": "00c47ccd",
      "instruction": "JZ 0x00c47d6c"
    },
    {
      "address": "00c47cd3",
      "instruction": "MOV dword ptr [ECX + 0x84],EAX"
    },
    {
      "address": "00c47cd9",
      "instruction": "MOV EAX,dword ptr [ECX + 0x14c]"
    },
    {
      "address": "00c47cdf",
      "instruction": "CMP EAX,dword ptr [ECX + 0x150]"
    },
    {
      "address": "00c47ce5",
      "instruction": "JZ 0x00c47cf8"
    },
    {
      "address": "00c47ce7",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00c47ce9",
      "instruction": "MOV word ptr [EAX],DX"
    },
    {
      "address": "00c47cec",
      "instruction": "MOV EAX,dword ptr [ECX + 0x14c]"
    },
    {
      "address": "00c47cf2",
      "instruction": "MOV dword ptr [ECX + 0x150],EAX"
    },
    {
      "address": "00c47cf8",
      "instruction": "MOV EAX,dword ptr [ECX + 0x15c]"
    },
    {
      "address": "00c47cfe",
      "instruction": "CMP EAX,dword ptr [ECX + 0x160]"
    },
    {
      "address": "00c47d04",
      "instruction": "JZ 0x00c47d17"
    },
    {
      "address": "00c47d06",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00c47d08",
      "instruction": "MOV word ptr [EAX],DX"
    },
    {
      "address": "00c47d0b",
      "instruction": "MOV EAX,dword ptr [ECX + 0x15c]"
    },
    {
      "address": "00c47d11",
      "instruction": "MOV dword ptr [ECX + 0x160],EAX"
    },
    {
      "address": "00c47d17",
      "instruction": "CMP dword ptr [ECX + 0x84],0x3"
    },
    {
      "address": "00c47d1e",
      "instruction": "JNZ 0x00c47d6c"
    },
    {
      "address": "00c47d20",
      "instruction": "MOV dword ptr [ESP + 0x30],0x38cf2fd"
    },
    {
      "address": "00c47d28",
      "instruction": "MOV dword ptr [ESP],0x13eb90c"
    },
    {
      "address": "00c47d2f",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00c47d31",
      "instruction": "LEA EAX,[ESP + 0x4]"
    },
    {
      "address": "00c47d35",
      "instruction": "XCHG dword ptr [EAX],EDX"
    },
    {
      "address": "00c47d37",
      "instruction": "MOV dword ptr [ESP],0x13eb844"
    },
    {
      "address": "00c47d3e",
      "instruction": "MOV dword ptr [ESP + 0x38],0x0"
    },
    {
      "address": "00c47d46",
      "instruction": "MOV dword ptr [ESP + 0x8],ECX"
    },
    {
      "address": "00c47d4a",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "00c47d4f",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00c47d51",
      "instruction": "MOV EDX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00c47d54",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c47d56",
      "instruction": "LEA ECX,[ESP + 0x4]"
    },
    {
      "address": "00c47d5a",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c47d5b",
      "instruction": "MOV ECX,dword ptr [ESP + 0x38]"
    },
    {
      "address": "00c47d5f",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c47d60",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c47d62",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c47d64",
      "instruction": "LEA ECX,[ESP]"
    },
    {
      "address": "00c47d67",
      "instruction": "CALL 0x00421cf0"
    },
    {
      "address": "00c47d6c",
      "instruction": "ADD ESP,0x40"
    },
    {
      "address": "00c47d6f",
      "instruction": "RET 0x4"
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
  "original_bytes": 9562,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall with one callee-cleaned stack dword\",\n    \"hidden_receiver\": \"read\",\n    \"hidden_this_register\": \"ECX, read directly, never copied or modified\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": null,\n    \"return_semantics\": \"no return value; EAX is left holding the argument on exit\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [],\n    \"stack_arguments\": [\n      {\n        \"meaning\": \"the new state/phase value\",\n        \"observed_values\": [\n          1,\n          2,\n          3,\n          5,\n          6,\n          7,\n          8,\n          9,\n          \"one dynamic value forwarded from a virtual slot +0x7c\"\n        ],\n        \"offset_at_entry\": \"[ESP + 0x4]\",\n        \"read_at\": \"0x00c47cc0\",\n        \"slot\": 0,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c48470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c484e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c485b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c485c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c485d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c485e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c485f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5a0b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fef3b0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00c484cb\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c48470\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c48595\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c484e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c485b2\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c485b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c485c2\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c485c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c485d2\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c485d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c485e2\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c485e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c485f2\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c485f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c5a108\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c5a0b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fef465\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fef3b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fef47f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fef3b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fef49f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fef3b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fef4a8\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fef3b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fef4c1\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fef3b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fef4d8\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fef3b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fef4ef\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fef3b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c47d67\",\n        \"direction\": \"out\",\n        \"other\": \"0x00421cf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c47d4a\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 9,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0464\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 1\n  },\n  \"evidence_l
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
  "body_end": "00c47d71",
  "body_span_bytes": 178,
  "body_start": "00c47cc0",
  "callees": [
    "FUN_00421cf0",
    "App::IAppSystem::Get"
  ],
  "callers": [
    "FUN_00c485d0",
    "FUN_00fef3b0",
    "FUN_00c5a0b0",
    "FUN_00c485b0",
    "FUN_00c485e0",
    "FUN_00c485f0",
    "FUN_00c484e0",
    "FUN_00c48470",
    "FUN_00c485c0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c47cc0",
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
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    },
    {
      "name": "local_3c",
      "storage": "Stack[-0x3c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_40",
      "storage": "Stack[-0x40]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_00c47cc0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x847cc0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c47cc0(void)",
  "size_bytes": 178,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c47cc0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 18,
  "xrefs": [
    {
      "from": "00c485b2"
    },
    {
      "from": "00c485c2"
    },
    {
      "from": "00c485d2"
    },
    {
      "from": "00c485e2"
    },
    {
      "from": "00c485f2"
    },
    {
      "from": "00c484cb"
    },
    {
      "from": "00c48595"
    },
    {
      "from": "00fef465"
    },
    {
      "from": "00fef47f"
    },
    {
      "from": "00fef49f"
    },
    {
      "from": "00fef4a8"
    },
    {
      "from": "00fef4c1"
    },
    {
      "from": "00fef4d8"
    },
    {
      "from": "00fef4ef"
    },
    {
      "from": "00c542c7"
    },
    {
      "from": "00c54360"
    },
    {
      "from": "00c5a108"
    },
    {
      "from": "00c56fc0"
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
    "reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp",
    "reconstruction/staging/wave13-w1-core-b09/b09_opaque_ports.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_setphase_00c47cc0.cpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_setphase_00c47cc0.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_setphase_00c47cc0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b09/00c47cc0.json"
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
    "A differential fixture would need a real receiver plus a populated app-system singleton, neither of which static evidence supplies.",
    "No original-process trace exists for this address. In particular 0x015fd890 was never observed populated, so the app-system slot +0x14 callee is unknown at runtime as well as statically.",
    "The Cell stage has never been entered in any recorded run, so the real distribution of state values and the real contents of the two wide buffers are unverified."
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
  "dword",
  "pointer",
  "void",
  "vtable pointer",
  "wchar_t* cursor (head)",
  "wchar_t* cursor (tail)"
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
