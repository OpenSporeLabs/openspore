# Evidence 0x00c12410

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `8a0ff4c2367b748dd833fdb2ee84f71ffb9d90764ee045569ca3cca698b2cf5b`

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
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c",
      "entry_ESP+0x20",
      "entry_ESP+0x28",
      "entry_ESP+0x2c",
      "entry_ESP+0x30",
      "entry_ESP+0x34",
      "entry_ESP+0x3c",
      "entry_ESP+0x40"
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
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
        "size_inferred": true,
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
      },
      {
        "entry_offset": "entry_ESP+0x28",
        "observed": true,
        "ordinal": 10,
        "read": false,
        "size_inferred": false,
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
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x40",
        "observed": true,
        "ordinal": 16,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x1c",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
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
        "size_inferred": true,
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
        "s
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
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c",
      "entry_ESP+0x20",
      "entry_ESP+0x28",
      "entry_ESP+0x2c",
      "entry_ESP+0x30",
      "entry_ESP+0x34",
      "entry_ESP+0x3c",
      "entry_ESP+0x40"
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
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
        "size_inferred": true,
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
      },
      {
        "entry_offset": "entry_ESP+0x28",
        "observed": true,
        "ordinal": 10,
        "read": false,
        "size_inferred": false,
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
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x40",
        "observed": true,
        "ordinal": 16,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x1c",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
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
        "size_inferred": true,
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
        "s
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
  "count": 142,
  "instructions": [
    {
      "address": "00c12410",
      "instruction": "SUB ESP,0x24"
    },
    {
      "address": "00c12413",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c12414",
      "instruction": "OR ESI,0xffffffff"
    },
    {
      "address": "00c12417",
      "instruction": "CMP byte ptr [ESP + 0x38],0x0"
    },
    {
      "address": "00c1241c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c1241d",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00c1241f",
      "instruction": "JNZ 0x00c12433"
    },
    {
      "address": "00c12421",
      "instruction": "CMP dword ptr [EDI + 0xe8c],ESI"
    },
    {
      "address": "00c12427",
      "instruction": "JZ 0x00c12433"
    },
    {
      "address": "00c12429",
      "instruction": "POP EDI"
    },
    {
      "address": "00c1242a",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00c1242c",
      "instruction": "POP ESI"
    },
    {
      "address": "00c1242d",
      "instruction": "ADD ESP,0x24"
    },
    {
      "address": "00c12430",
      "instruction": "RET 0x1c"
    },
    {
      "address": "00c12433",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c12434",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c12435",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00c12437",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c12438",
      "instruction": "CALL 0x00d38a30"
    },
    {
      "address": "00c1243d",
      "instruction": "FSTP float ptr [ESP + 0x18]"
    },
    {
      "address": "00c12441",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00c12443",
      "instruction": "MOV EDX,dword ptr [EAX + 0xb0]"
    },
    {
      "address": "00c12449",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00c1244c",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c1244e",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c12450",
      "instruction": "MOVSS XMM0,dword ptr [0x013eb1bc]"
    },
    {
      "address": "00c12458",
      "instruction": "MOVSS dword ptr [ESP + 0x40],XMM0"
    },
    {
      "address": "00c1245e",
      "instruction": "MOVSS XMM0,dword ptr [0x0146a32c]"
    },
    {
      "address": "00c12466",
      "instruction": "MOV dword ptr [ESP + 0x2c],EAX"
    },
    {
      "address": "00c1246a",
      "instruction": "MOV dword ptr [ESP + 0x18],ESI"
    },
    {
      "address": "00c1246e",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM0"
    },
    {
      "address": "00c12474",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00c12476",
      "instruction": "JBE 0x00c12624"
    },
    {
      "address": "00c1247c",
      "instruction": "MOV dword ptr [ESP + 0xc],EBX"
    },
    {
      "address": "00c12480",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c12481",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00c12483",
      "instruction": "MOV EBP,dword ptr [EDI + 0xc28]"
    },
    {
      "address": "00c12489",
      "instruction": "MOV EDX,dword ptr [EAX + 0xb4]"
    },
    {
      "address": "00c1248f",
      "instruction": "ADD EBP,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c12493",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c12494",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c12496",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c12498",
      "instruction": "CMP dword ptr [ESP + 0x38],0x0"
    },
    {
      "address": "00c1249d",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00c1249f",
      "instruction": "JZ 0x00c124ce"
    },
    {
      "address": "00c124a1",
      "instruction": "MOV EAX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "00c124a4",
      "instruction": "CMP EAX,0x58"
    },
    {
      "address": "00c124a7",
      "instruction": "JNC 0x00c12613"
    },
    {
      "address": "00c124ad",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c124af",
      "instruction": "AND ECX,0x1f"
    },
    {
      "address": "00c124b2",
      "instruction": "MOV EDX,0x1"
    },
    {
      "address": "00c124b7",
      "instruction": "SHL EDX,CL"
    },
    {
      "address": "00c124b9",
      "instruction": "MOV ECX,dword ptr [ESP + 0x38]"
    },
    {
      "address": "00c124bd",
      "instruction": "SHR EAX,0x5"
    },
    {
      "address": "00c124c0",
      "instruction": "TEST dword ptr [ECX + EAX*0x4],EDX"
    },
    {
      "address": "00c124c3",
      "instruction": "SETNZ AL"
    },
    {
      "address": "00c124c6",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c124c8",
      "instruction": "JZ 0x00c12613"
    },
    {
      "address": "00c124ce",
      "instruction": "CMP dword ptr [ESI + 0xc],0x1"
    },
    {
      "address": "00c124d2",
      "instruction": "JNZ 0x00c12613"
    },
    {
      "address": "00c124d8",
      "instruction": "CMP byte ptr [ESI + 0x114],0x0"
    },
    {
      "address": "00c124df",
      "instruction": "JNZ 0x00c12613"
    },
    {
      "address": "00c124e5",
      "instruction": "MOVSS XMM0,dword ptr [ESI + 0x104]"
    },
    {
      "address": "00c124ed",
      "instruction": "XORPS XMM1,XMM1"
    },
    {
      "address": "00c124f0",
      "instruction": "COMISS XMM1,XMM0"
    },
    {
      "address": "00c124f3",
      "instruction": "JNC 0x00c12506"
    },
    {
      "address": "00c124f5",
      "instruction": "MOVSS XMM2,dword ptr [EDI + 0xe58]"
    },
    {
      "address": "00c124fd",
      "instruction": "COMISS XMM2,XMM0"
    },
    {
      "address": "00c12500",
      "instruction": "JC 0x00c12613"
    },
    {
      "address": "00c12506",
      "instruction": "CMP byte ptr [ESP + 0x40],0x0"
    },
    {
      "address": "00c1250b",
      "instruction": "JNZ 0x00c1251f"
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
  "body_end": "00c12630",
  "body_span_bytes": 545,
  "body_start": "00c12410",
  "callees": [
    "FUN_004d3d70",
    "FUN_00d38a30"
  ],
  "callers": [
    "FUN_00d669c0",
    "FUN_00d697a0",
    "FUN_00d8cde0",
    "FUN_00d71780"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c12410",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00c12410",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x812410",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c12410(void)",
  "size_bytes": 545,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c12410",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "00d66ab1"
    },
    {
      "from": "00d69efa"
    },
    {
      "from": "00d69f58"
    },
    {
      "from": "00d69f7d"
    },
    {
      "from": "00d8cf05"
    },
    {
      "from": "00d71bbe"
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
