# Evidence 0x00bba2a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `94acc60cabe3229f39c7259793086750309de34f6bbf4962954b0749771004cc`

## abi

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
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c",
      "entry_ESP+0x20"
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
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": true,
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
        "size_inferred": true,
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
        "size_inferred": true,
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
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
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
    "ret_form": "RET",
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
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": true,
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
        "size_inferred": true,
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
        "size_inferred": true,
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
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -76, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "59cd60af6991d18d9d552f046cc2d062be07baee3b0b5d821daf651f82abcc4a",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0013",
        "obs-0068",
        "obs-0073"
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
        "obs-0015",
        "obs-0019",
        "obs-0020",
        "obs-0021",
        "obs-0024",
        "obs-0027",
        "obs-0029",
        "
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c",
      "entry_ESP+0x20"
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
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": true,
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
        "size_inferred": true,
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
        "size_inferred": true,
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
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
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
    "ret_form": "RET",
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
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": true,
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
        "size_inferred": true,
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
        "size_inferred": true,
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
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -76, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "59cd60af6991d18d9d552f046cc2d062be07baee3b0b5d821daf651f82abcc4a",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0013",
        "obs-0068",
        "obs-0073"
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
        "obs-0015",
        "obs-0019",
        "obs-0020",
        "obs-0021",
        "obs-0024",
        "obs-0027",
        "obs-0029",
        "
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
  "count": 166,
  "instructions": [
    {
      "address": "00bba2a0",
      "instruction": "SUB ESP,0x2c"
    },
    {
      "address": "00bba2a3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bba2a4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bba2a5",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00bba2a7",
      "instruction": "MOV EAX,dword ptr [EDI + 0x4c]"
    },
    {
      "address": "00bba2aa",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00bba2ac",
      "instruction": "SUB EAX,0x2"
    },
    {
      "address": "00bba2af",
      "instruction": "MOV dword ptr [ESP + 0x10],ESI"
    },
    {
      "address": "00bba2b3",
      "instruction": "JZ 0x00bba2fc"
    },
    {
      "address": "00bba2b5",
      "instruction": "SUB EAX,0x2"
    },
    {
      "address": "00bba2b8",
      "instruction": "JZ 0x00bba2f2"
    },
    {
      "address": "00bba2ba",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00bba2bd",
      "instruction": "JZ 0x00bba2d4"
    },
    {
      "address": "00bba2bf",
      "instruction": "MOV dword ptr [EDI + 0x78],ESI"
    },
    {
      "address": "00bba2c2",
      "instruction": "MOV dword ptr [EDI + 0x7c],ESI"
    },
    {
      "address": "00bba2c5",
      "instruction": "MOV dword ptr [EDI + 0x74],ESI"
    },
    {
      "address": "00bba2c8",
      "instruction": "MOV dword ptr [EDI + 0x80],ESI"
    },
    {
      "address": "00bba2ce",
      "instruction": "POP EDI"
    },
    {
      "address": "00bba2cf",
      "instruction": "POP ESI"
    },
    {
      "address": "00bba2d0",
      "instruction": "ADD ESP,0x2c"
    },
    {
      "address": "00bba2d3",
      "instruction": "RET"
    },
    {
      "address": "00bba2d4",
      "instruction": "MOV EAX,dword ptr [EDI + 0x54]"
    },
    {
      "address": "00bba2d7",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bba2d8",
      "instruction": "MOV dword ptr [ESP + 0xc],0xfc5a17bc"
    },
    {
      "address": "00bba2e0",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00bba2e5",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bba2e7",
      "instruction": "CALL 0x00ba9370"
    },
    {
      "address": "00bba2ec",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00bba2f0",
      "instruction": "JMP 0x00bba304"
    },
    {
      "address": "00bba2f2",
      "instruction": "MOV dword ptr [ESP + 0x8],0xefc33700"
    },
    {
      "address": "00bba2fa",
      "instruction": "JMP 0x00bba304"
    },
    {
      "address": "00bba2fc",
      "instruction": "MOV dword ptr [ESP + 0x8],0x876201aa"
    },
    {
      "address": "00bba304",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bba305",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00bba306",
      "instruction": "MOV dword ptr [ESP + 0x1c],0x64"
    },
    {
      "address": "00bba30e",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00bba310",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "00bba312",
      "instruction": "MOV dword ptr [ESP + 0x28],ESI"
    },
    {
      "address": "00bba316",
      "instruction": "CALL 0x00b3d450"
    },
    {
      "address": "00bba31b",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bba31d",
      "instruction": "MOV dword ptr [ESP + 0x14],ECX"
    },
    {
      "address": "00bba321",
      "instruction": "JMP 0x00bba327"
    },
    {
      "address": "00bba323",
      "instruction": "MOV ECX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00bba327",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00bba329",
      "instruction": "JZ 0x00bba34a"
    },
    {
      "address": "00bba32b",
      "instruction": "CMP EBX,dword ptr [EDI + 0x74]"
    },
    {
      "address": "00bba32e",
      "instruction": "JNZ 0x00bba405"
    },
    {
      "address": "00bba334",
      "instruction": "CMP EBP,dword ptr [EDI + 0x78]"
    },
    {
      "address": "00bba337",
      "instruction": "JNZ 0x00bba405"
    },
    {
      "address": "00bba33d",
      "instruction": "MOV EDX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00bba341",
      "instruction": "CMP EDX,dword ptr [EDI + 0x7c]"
    },
    {
      "address": "00bba344",
      "instruction": "JNZ 0x00bba405"
    },
    {
      "address": "00bba34a",
      "instruction": "SUB dword ptr [ESP + 0x1c],0x1"
    },
    {
      "address": "00bba34f",
      "instruction": "JS 0x00bba405"
    },
    {
      "address": "00bba355",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00bba359",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00bba35b",
      "instruction": "JZ 0x00bba368"
    },
    {
      "address": "00bba35d",
      "instruction": "MOV EAX,dword ptr [EAX + 0x58]"
    },
    {
      "address": "00bba360",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bba361",
      "instruction": "CALL 0x00ac1190"
    },
    {
      "address": "00bba366",
      "instruction": "JMP 0x00bba372"
    },
    {
      "address": "00bba368",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00bba36c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bba36d",
      "instruction": "CALL 0x00ac10a0"
    },
    {
      "address": "00bba372",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00bba374",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00bba376",
      "instruction": "JZ 0x00bba40b"
    },
    {
      "address": "00bba37c",
      "instruction": "LEA ECX,[ESP + 0x2c]"
    },
    {
      "address": "00bba380",
      "instruction": "MOV EAX,0x1667bac"
    },
    {
      "address": "00bba385",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bba386",
      "instruction": "MOV ECX,ESI"
    },
    
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
  "body_end": "00bba4ad",
  "body_span_bytes": 526,
  "body_start": "00bba2a0",
  "callees": [
    "FUN_00ba9370",
    "FUN_00f47380",
    "FUN_00baf5d0",
    "Simulator::cStarManager::RecordToPlanet",
    "FUN_004da330",
    "Simulator::cPlanetModel::Get",
    "FUN_00ac1190",
    "FUN_00c33690",
    "FUN_00b3d2a0",
    "FUN_00ac10a0"
  ],
  "callers": [
    "FUN_00bba500",
    "FUN_00ba7220"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bba2a0",
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
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined4"
    },
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 8,
  "mode": "live",
  "name": "cStarRecord__ctor",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7ba2a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined cStarRecord__ctor(void)",
  "size_bytes": 526,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bba2a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00bba51a"
    },
    {
      "from": "00bba552"
    },
    {
      "from": "00ba7259"
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
