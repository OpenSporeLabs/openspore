# Evidence 0x007c3ba0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1ee180d8d4b26e43002937796c85d8ce8cd50a1fc37daba032cc565be0c9e90d`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": [
    "__thiscall",
    "thiscall"
  ],
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueWorldViewer*",
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_semantics": "integral_in_EAX",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path"
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
  "content_sha256": "cb162821d4e22b2984de4ebb023c10d4358cffd4645ed5d560ce7fa599220536",
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
    "persisted_calling_convention": "['__thiscall', 'thiscall']"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0010",
        "obs-0012"
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
        "obs-0002",
        "obs-0003"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          344,
          368
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0010",
        "obs-0012"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0010",
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
        "obs-0010",
        "obs-0012"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0010",
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
      "at": "0x007c3ba0",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x007c3ba1",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x007c3ba1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x007c3ba3",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x158]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007c3bd3",
      "count": 2,
      "first_use": 11,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 11,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x007c3bd4",
      "id": "obs-0006",
      "index": 12,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f47380",
      "target": "0x00f47380"
    },
    {
      "at": "0x007c3bd9",
      "definite": true,
      "id": "obs-0007",
      "index": 13,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x4",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x007c3bf1",
      "id": "obs-0008",
      "index": 19,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f47410",
      "target": "0x00f47410"
    },
    {
      "at": "0x007c3c05",
      "id": "obs-0009",
      "index": 23,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x007c3c06",
      "form": "RET",
      "id": "obs-0010",
      "imm": null,
      "index": 24,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x007c3c09",
      "id": "obs-0011",
      "index": 26,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x007c3c0a",
      "form": "RET",
      "id": "obs-0012",
      "imm": null,
      "index": 27,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 28,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 
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
    "va": "0x00430e70"
  },
  {
    "name": "Editors::cEditor::Dispose",
    "reconstructed": false,
    "va": "0x00576c50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f0890"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f5260"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f9cf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076b000"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076b5d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076b840"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00777060"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0077f210"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b29a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b77a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b9620"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b9e80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007bd540"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007bd640"
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
  "count": 28,
  "instructions": [
    {
      "address": "007c3ba0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "007c3ba1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "007c3ba3",
      "instruction": "MOV EAX,dword ptr [ESI + 0x158]"
    },
    {
      "address": "007c3ba9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "007c3bab",
      "instruction": "JZ 0x007c3be6"
    },
    {
      "address": "007c3bad",
      "instruction": "CMP dword ptr [0x016f6dac],EAX"
    },
    {
      "address": "007c3bb3",
      "instruction": "JNZ 0x007c3bcd"
    },
    {
      "address": "007c3bb5",
      "instruction": "OR dword ptr [0x016f8a38],0x2"
    },
    {
      "address": "007c3bbc",
      "instruction": "OR dword ptr [0x016f9110],0x8"
    },
    {
      "address": "007c3bc3",
      "instruction": "MOV dword ptr [0x016f6dac],0x0"
    },
    {
      "address": "007c3bcd",
      "instruction": "MOV EAX,dword ptr [ESI + 0x158]"
    },
    {
      "address": "007c3bd3",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007c3bd4",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "007c3bd9",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "007c3bdc",
      "instruction": "MOV dword ptr [ESI + 0x158],0x0"
    },
    {
      "address": "007c3be6",
      "instruction": "MOV EAX,dword ptr [ESI + 0x170]"
    },
    {
      "address": "007c3bec",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "007c3bee",
      "instruction": "JZ 0x007c3c07"
    },
    {
      "address": "007c3bf0",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007c3bf1",
      "instruction": "CALL 0x00f47410"
    },
    {
      "address": "007c3bf6",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "007c3bf9",
      "instruction": "MOV dword ptr [ESI + 0x170],0x0"
    },
    {
      "address": "007c3c03",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "007c3c05",
      "instruction": "POP ESI"
    },
    {
      "address": "007c3c06",
      "instruction": "RET"
    },
    {
      "address": "007c3c07",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "007c3c09",
      "instruction": "POP ESI"
    },
    {
      "address": "007c3c0a",
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
  "original_bytes": 14227,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": [\n      \"__thiscall\",\n      \"thiscall\"\n    ],\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueWorldViewer*\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"integral_in_EAX\",\n    \"return_type\": \"std::uint8_t\",\n    \"return_width_bytes\": 1,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No runtime execution of the original release routines is available.\",\n    \"The opaque receiver and release contracts require integration with the world-viewer owner.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00430e70\"\n      },\n      {\n        \"name\": \"Editors::cEditor::Dispose\",\n        \"reconstructed\": false,\n        \"va\": \"0x00576c50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f0890\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f5260\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f9cf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076b000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076b5d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076b840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00777060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0077f210\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b29a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b77a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b9620\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b9e80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bd540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bd640\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bd6b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bd750\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bdd70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007be430\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bea00\"\n      },\n      {\n        \"name\": \"FUN_007c4000\",\n        \"reconstructed\": false,\n        \"va\": \"0x007c4000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007e7380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0080ead0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0080ec40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0080eca0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00adf690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b35860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e66980\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f96c60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f99ff0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f9e1f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f9e350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fa0360\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00feb0f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010372b0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00432347\",\n        \"direction\": \"in\",\n        \"other\": \"0x00430e70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576f70\",\n        \"direction\": \"in\",\n        \"other\": \"0x00576c50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576f9f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00576c50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576fce\",\n        \"direction\": \"in\",\n        \"other\":
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
  "body_end": "007c3c0a",
  "body_span_bytes": 107,
  "body_start": "007c3ba0",
  "callees": [
    "FUN_00f47380",
    "FUN_00f47410"
  ],
  "callers": [
    "FUN_007b9620",
    "FUN_007bd6b0",
    "FUN_00777060",
    "FUN_00f9e350",
    "FUN_00e66980",
    "FUN_0076b5d0",
    "FUN_007bd640",
    "FUN_006f9cf0",
    "FUN_0080eca0",
    "FUN_0076b000",
    "FUN_007b77a0",
    "FUN_007e7380",
    "FUN_00b35860",
    "FUN_007bd540",
    "FUN_00feb0f0",
    "FUN_00430e70",
    "FUN_00f96c60",
    "FUN_007bea00",
    "FUN_007b9e80",
    "FUN_006f5260",
    "FUN_007be430",
    "FUN_007c4000",
    "FUN_00f99ff0",
    "FUN_00f9e1f0",
    "FUN_0076b840",
    "FUN_007b29a0",
    "FUN_007bd750",
    "FUN_007bdd70",
    "FUN_0080ec40",
    "FUN_010372b0",
    "FUN_006f0890",
    "FUN_00adf690",
    "FUN_0080ead0",
    "Editors::cEditor::Dispose",
    "FUN_00fa0360",
    "FUN_0077f210"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "007c3ba0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_007c3ba0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3c3ba0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_007c3ba0(void)",
  "size_bytes": 107,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007c3ba0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 65,
  "xrefs": [
    {
      "from": "007c4009"
    },
    {
      "from": "00432347"
    },
    {
      "from": "0076b5fb"
    },
    {
      "from": "006f0afd"
    },
    {
      "from": "006f0b26"
    },
    {
      "from": "006f0b4f"
    },
    {
      "from": "0076b133"
    },
    {
      "from": "0076b15d"
    },
    {
      "from": "0076b18e"
    },
    {
      "from": "006f5465"
    },
    {
      "from": "006f9d77"
    },
    {
      "from": "006f9da0"
    },
    {
      "from": "006f9dc9"
    },
    {
      "from": "006f9df3"
    },
    {
      "from": "0076b84b"
    },
    {
      "from": "007770d0"
    },
    {
      "from": "0077f253"
    },
    {
      "from": "0077f270"
    },
    {
      "from": "007b29e3"
    },
    {
      "from": "007b9634"
    },
    {
      "from": "007b9e99"
    },
    {
      "from": "007bd5a3"
    },
    {
      "from": "007bd683"
    },
    {
      "from": "007bd6fc"
    },
    {
      "from": "007bd722"
    },
    {
      "from": "007bdc69"
    },
    {
      "from": "007bddb8"
    },
    {
      "from": "007be8a6"
    },
    {
      "from": "007bec7f"
    },
    {
      "from": "007e75d1"
    },
    {
      "from": "0080eafc"
    },
    {
      "from": "0080ec56"
    },
    {
      "from": "0080ed04"
    },
    {
      "from": "00adf748"
    },
    {
      "from": "00b35a8d"
    },
    {
      "from": "00f9a001"
    },
    {
      "from": "00f96c6d"
    },
    {
      "from": "00fa03e9"
    },
    {
      "from": "00f9e232"
    },
    {
      "from": "00f9e355"
    },
    {
      "from": "00feb0fa"
    },
    {
      "from": "010376d5"
    },
    {
      "from": "010376df"
    },
    {
      "from": "010376eb"
    },
    {
      "from": "00e66987"
    },
    {
      "from": "00576f70"
    },
    {
      "from": "00576f9f"
    },
    {
      "from": "00576fce"
    },
    {
      "from": "00576ffd"
    },
    {
      "from": "0057702c"
    },
    {
      "from": "0076db19"
    },
    {
      "from": "007b994a"
    },
    {
      "from": "007b9abe"
    },
    {
      "from": "007bdfd4"
    },
    {
      "from": "007bdffa"
    },
    {
      "from": "007be023"
    },
    {
      "from": "007be052"
    },
    {
      "from": "007be081"
    },
    {
      "from": "007be0b0"
    },
    {
      "from": "007be11a"
    },
    {
      "from": "007be3d4"
    },
    {
      "from": "007b77b9"
    },
    {
      "from": "007e95c9"
    },
    {
      "from": "00b35194"
    },
    {
      "from": "00fa48e3"
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
    "reconstruction/staging/pkg14-a1-world-state/world_state.cpp",
    "reconstruction/staging/pkg14-a1-world-state/world_state.hpp",
    "reconstruction/staging/pkg14-a1-world-state/world_state_model_test.cpp",
    "reconstruction/staging/pkg_editor_007c3ba0/editor_007c3ba0.cpp",
    "reconstruction/staging/pkg_editor_007c3ba0/editor_007c3ba0.hpp",
    "reconstruction/staging/pkg_editor_007c3ba0/editor_007c3ba0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-editor-007c3ba0/007c3ba0.json",
    "reconstruction/metadata/pkg14-a1-world-state/007c3ba0.json"
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
  "gates": [],
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
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueWorldViewer*",
  "cViewer",
  "std::uint8_t"
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
