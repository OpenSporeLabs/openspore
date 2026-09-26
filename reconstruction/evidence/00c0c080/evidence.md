# Evidence 0x00c0c080

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b2b7e35c20058e693148d0ec58720d2f282559623e35579058b2d935867517ea`

## abi

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
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBP",
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "5a2555c22dd3cc4583a3c8ed6e6e5be9a89eeebd2bfbdca4fd68cacd73e706ec",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0026",
        "obs-0031"
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
        "obs-0016"
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
        "obs-0007",
        "obs-0019"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0026",
        "obs-0031"
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
        "obs-0026",
        "obs-0031"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0026",
        "obs-0031"
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
      "at": "0x00c0c080",
      "count": 1,
      "first_use": 0,
      "first_write_index": 8,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c0c081",
      "count": 1,
      "first_use": 1,
      "first_write_index": 12,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00c0c081",
      "ebp_is_general_register": false,
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
      "at": "0x00c0c082",
      "count": 4,
      "first_use": 2,
      "first_write_index": 9,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c0c083",
      "count": 4,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c0c084",
      "count": 1,
      "first_use": 4,
      "first_write_index": 17,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c0c084",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c0c086",
      "definite": true,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EDI]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c0c088",
      "count": 4,
      "first_use": 6,
      "first
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

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nuint __thiscall FUN_00c0c080(int *param_1,int param_2)\n\n{\n  uint uVar1;\n  int iVar2;\n  uint uVar3;\n  \n  uVar1 = (**(code **)(*param_1 + 0xb0))();\n  uVar3 = 0;\n  if (uVar1 != 0) {\n    do {\n      iVar2 = (**(code **)(*param_1 + 0xb4))(uVar3);\n      if (*(int *)(iVar2 + 8) == param_2) {\n        return uVar3;\n      }\n      uVar3 = uVar3 + 1;\n    } while (uVar3 < uVar1);\n  }\n  return 0xffffffff;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 36,
  "instructions": [
    {
      "address": "00c0c080",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c0c081",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c0c082",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c0c083",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c0c084",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00c0c086",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00c0c088",
      "instruction": "MOV EDX,dword ptr [EAX + 0xb0]"
    },
    {
      "address": "00c0c08e",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c0c090",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00c0c092",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00c0c094",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00c0c096",
      "instruction": "JBE 0x00c0c0b7"
    },
    {
      "address": "00c0c098",
      "instruction": "MOV EBP,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00c0c09c",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "00c0c0a0",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00c0c0a2",
      "instruction": "MOV EDX,dword ptr [EAX + 0xb4]"
    },
    {
      "address": "00c0c0a8",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c0c0a9",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c0c0ab",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c0c0ad",
      "instruction": "CMP dword ptr [EAX + 0x8],EBP"
    },
    {
      "address": "00c0c0b0",
      "instruction": "JZ 0x00c0c0c1"
    },
    {
      "address": "00c0c0b2",
      "instruction": "INC ESI"
    },
    {
      "address": "00c0c0b3",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "00c0c0b5",
      "instruction": "JC 0x00c0c0a0"
    },
    {
      "address": "00c0c0b7",
      "instruction": "POP EDI"
    },
    {
      "address": "00c0c0b8",
      "instruction": "POP ESI"
    },
    {
      "address": "00c0c0b9",
      "instruction": "POP EBP"
    },
    {
      "address": "00c0c0ba",
      "instruction": "OR EAX,0xffffffff"
    },
    {
      "address": "00c0c0bd",
      "instruction": "POP EBX"
    },
    {
      "address": "00c0c0be",
      "instruction": "RET 0x4"
    },
    {
      "address": "00c0c0c1",
      "instruction": "POP EDI"
    },
    {
      "address": "00c0c0c2",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00c0c0c4",
      "instruction": "POP ESI"
    },
    {
      "address": "00c0c0c5",
      "instruction": "POP EBP"
    },
    {
      "address": "00c0c0c6",
      "instruction": "POP EBX"
    },
    {
      "address": "00c0c0c7",
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "00c0c0c9",
  "body_span_bytes": 74,
  "body_start": "00c0c080",
  "callees": [],
  "callers": [
    "FUN_00f10bd0",
    "FUN_00c0dac0",
    "FUN_00c18370",
    "FUN_00c1ad10",
    "FUN_00c1cdd0",
    "FUN_00c222f0",
    "FUN_00c1aed0",
    "FUN_00c197a0",
    "FUN_00c0c140",
    "FUN_00c1aad0",
    "FUN_00c0db10",
    "FUN_00c18740"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00c0c080",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar3",
      "storage": "register:00000018:4",
      "type": "uint"
    },
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int *"
    },
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "uint"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_00c0c080",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x80c080",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c0c080(void)",
  "size_bytes": 74,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c0c080",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 31,
  "xrefs": [
    {
      "from": "00c223cd"
    },
    {
      "from": "00c223e9"
    },
    {
      "from": "00c22405"
    },
    {
      "from": "00c22416"
    },
    {
      "from": "00c22432"
    },
    {
      "from": "00c2244e"
    },
    {
      "from": "00c1aee7"
    },
    {
      "from": "00c1aef5"
    },
    {
      "from": "00c1af92"
    },
    {
      "from": "00c1afa0"
    },
    {
      "from": "00c1981e"
    },
    {
      "from": "00c1982c"
    },
    {
      "from": "00c19839"
    },
    {
      "from": "00c19847"
    },
    {
      "from": "00c1ae28"
    },
    {
      "from": "00c1ae36"
    },
    {
      "from": "00c0c145"
    },
    {
      "from": "00c0c153"
    },
    {
      "from": "00c1abe4"
    },
    {
      "from": "00c1abf2"
    },
    {
      "from": "00c1cde2"
    },
    {
      "from": "00c1cdf0"
    },
    {
      "from": "00c1867f"
    },
    {
      "from": "00c187b5"
    },
    {
      "from": "00f10c54"
    },
    {
      "from": "00c0dac6"
    },
    {
      "from": "00c0dae2"
    },
    {
      "from": "00c0dafe"
    },
    {
      "from": "00c0db16"
    },
    {
      "from": "00c0db32"
    },
    {
      "from": "00c0db4e"
    }
  ]
}
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## types

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
