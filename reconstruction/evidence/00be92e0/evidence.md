# Evidence 0x00be92e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d353713bfd0d5a58ca6ff20422ad3b41ff0d707d15a730c2ff19e400909ad5cf`

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
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c",
      "entry_ESP+0x24",
      "entry_ESP+0x2c",
      "entry_ESP+0x38",
      "entry_ESP+0x3c",
      "entry_ESP+0x84",
      "entry_ESP+0x8c"
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
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x2c",
        "observed": true,
        "ordinal": 11,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x84",
        "observed": true,
        "ordinal": 33,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8c",
        "observed": true,
        "ordinal": 35,
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
    "ret_form": "RET 0x14",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x2c",
        "observed": true,
        "ordinal": 11,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x84",
        "observed": true,
        "ordinal": 33,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
   
[TRUNCATED]
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
      "entry_ESP+0xc",
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c",
      "entry_ESP+0x24",
      "entry_ESP+0x2c",
      "entry_ESP+0x38",
      "entry_ESP+0x3c",
      "entry_ESP+0x84",
      "entry_ESP+0x8c"
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
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x2c",
        "observed": true,
        "ordinal": 11,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x84",
        "observed": true,
        "ordinal": 33,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8c",
        "observed": true,
        "ordinal": 35,
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
    "ret_form": "RET 0x14",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x2c",
        "observed": true,
        "ordinal": 11,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x84",
        "observed": true,
        "ordinal": 33,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
   
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
  "count": 386,
  "instructions": [
    {
      "address": "00be92e0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00be92e4",
      "instruction": "SUB ESP,0x80"
    },
    {
      "address": "00be92ea",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00be92eb",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00be92ec",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00be92ee",
      "instruction": "MOV ECX,dword ptr [ESI + 0x590]"
    },
    {
      "address": "00be92f4",
      "instruction": "MOV dword ptr [ESI + 0x29c],EAX"
    },
    {
      "address": "00be92fa",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00be92fc",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4c]"
    },
    {
      "address": "00be92ff",
      "instruction": "CALL EAX"
    },
    {
      "address": "00be9301",
      "instruction": "MOV EBP,dword ptr [ESP + 0x8c]"
    },
    {
      "address": "00be9308",
      "instruction": "CMP EBP,EAX"
    },
    {
      "address": "00be930a",
      "instruction": "JZ 0x00be9844"
    },
    {
      "address": "00be9310",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00be9311",
      "instruction": "MOV EBX,dword ptr [ESI + 0x590]"
    },
    {
      "address": "00be9317",
      "instruction": "MOV dword ptr [ESP + 0xc],EBX"
    },
    {
      "address": "00be931b",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00be931d",
      "instruction": "JZ 0x00be9327"
    },
    {
      "address": "00be931f",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "00be9321",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "00be9323",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00be9325",
      "instruction": "CALL EAX"
    },
    {
      "address": "00be9327",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00be9328",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00be9329",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00be932e",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00be9330",
      "instruction": "CALL 0x00b25f40"
    },
    {
      "address": "00be9335",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00be9337",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00be9339",
      "instruction": "JNZ 0x00be9359"
    },
    {
      "address": "00be933b",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00be933d",
      "instruction": "JZ 0x00be9842"
    },
    {
      "address": "00be9343",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "00be9345",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "00be9348",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00be934a",
      "instruction": "CALL EAX"
    },
    {
      "address": "00be934c",
      "instruction": "POP EDI"
    },
    {
      "address": "00be934d",
      "instruction": "POP EBX"
    },
    {
      "address": "00be934e",
      "instruction": "POP ESI"
    },
    {
      "address": "00be934f",
      "instruction": "POP EBP"
    },
    {
      "address": "00be9350",
      "instruction": "ADD ESP,0x80"
    },
    {
      "address": "00be9356",
      "instruction": "RET 0x14"
    },
    {
      "address": "00be9359",
      "instruction": "MOV EDX,dword ptr [ESI + 0x120]"
    },
    {
      "address": "00be935f",
      "instruction": "MOV EAX,dword ptr [EDX + 0x58]"
    },
    {
      "address": "00be9362",
      "instruction": "LEA ECX,[ESI + 0x120]"
    },
    {
      "address": "00be9368",
      "instruction": "CALL EAX"
    },
    {
      "address": "00be936a",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00be936f",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00be9371",
      "instruction": "CALL 0x00b25fb0"
    },
    {
      "address": "00be9376",
      "instruction": "CMP EDI,EAX"
    },
    {
      "address": "00be9378",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00be937a",
      "instruction": "SETZ BL"
    },
    {
      "address": "00be937d",
      "instruction": "MOV dword ptr [EDI + 0x44c],ESI"
    },
    {
      "address": "00be9383",
      "instruction": "CALL 0x00befab0"
    },
    {
      "address": "00be9388",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00be938b",
      "instruction": "MOV dword ptr [EDI + 0x4bc],EAX"
    },
    {
      "address": "00be9391",
      "instruction": "OR EAX,0xffffffff"
    },
    {
      "address": "00be9394",
      "instruction": "MOV byte ptr [ESI + 0x2e0],0x1"
    },
    {
      "address": "00be939b",
      "instruction": "MOV byte ptr [ESI + 0x2e1],0x1"
    },
    {
      "address": "00be93a2",
      "instruction": "MOV byte ptr [ESI + 0x2e2],0x1"
    },
    {
      "address": "00be93a9",
      "instruction": "MOV byte ptr [ESI + 0x2e3],0x1"
    },
    {
      "address": "00be93b0",
      "instruction": "MOV byte ptr [ESI + 0x2e4],0x1"
    },
    {
      "address": "00be93b7",
      "instruction": "MOV byte ptr [ESI + 0x2e5],0x1"
    },
    {
      "address": "00be93be",
      "instruction": "MOV byte ptr [ESI + 0x2e6],0x1"
    },
    {
      "address": "00be93c5",
      "instruction": "MOV dword ptr [ESI + 0x74c],EAX"
    },
    {
      "address": "00be93cb",
      "instruction": "MOVSS dword ptr [ESI + 0x748],XMM0"
    },
    {
      "address": "00be93d3",
      "instruction": "MOV dword ptr [ESI + 0x754],EAX"
    },
    {
      "address": "00be93d9",
      "instruction": "MOVSS dword ptr [ESI + 0x750],XMM0"
    },
    {
      "address": "00be93e1",
      "instruction": "MOV dword ptr [ESI + 0x75c],EAX"
    },
    {
      "address": "00be93e7",
      "instruction": "MOVSS dword ptr [ESI + 0x758],XMM0"
    },
    {
      "address": "00b
[TRUNCATED]
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
  "body_end": "00be984e",
  "body_span_bytes": 1391,
  "body_start": "00be92e0",
  "callees": [
    "FUN_00c77bf0",
    "FUN_00bc3110",
    "FUN_00bfc6a0",
    "Simulator::cSpaceTrading::Get",
    "FUN_00adde90",
    "FUN_00ad7ad0",
    "FUN_00cf74c0",
    "FUN_00c772c0",
    "FUN_00ae0930",
    "FUN_00be88d0",
    "FUN_00bc3130",
    "App::IAppSystem::Get",
    "FUN_00dc4c60",
    "FUN_00ae09b0",
    "FUN_00cf8e00",
    "FUN_00b25f40",
    "Simulator::cUIEventLog::Get",
    "FUN_00befab0",
    "FUN_00b3d300",
    "FUN_00b25fb0",
    "FUN_00ad79d0",
    "FUN_00bd7f70",
    "FUN_00b5b800",
    "FUN_00be45b0",
    "FUN_00f67d90",
    "FUN_00ad7a30",
    "FUN_00cf75d0",
    "FUN_00be2440",
    "FUN_00cf7520",
    "FUN_00ad7b70"
  ],
  "callers": [
    "FUN_00be9980",
    "FUN_00be9850",
    "FUN_00beaa30",
    "FUN_00be9cb0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00be92e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00be92e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7e92e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00be92e0(void)",
  "size_bytes": 1391,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00be92e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00beaba4"
    },
    {
      "from": "00be9d4c"
    },
    {
      "from": "00be995e"
    },
    {
      "from": "00be9af3"
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
