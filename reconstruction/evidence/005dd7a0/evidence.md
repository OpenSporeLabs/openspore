# Evidence 0x005dd7a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c5b8f96bcc5b851d50a126c5da79598933e3e6a61f23e2044429be06bc3751e8`

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
    "receiver": true,
    "receiver_register": "ECX",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ]
  },
  "abstained_because": [
    "no_terminal_ret: the only exit observed is a tail jump"
  ],
  "cleanup": {
    "bytes": null,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": null,
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "3166581cfa98fd5d7e364413be508f9da5d5d57c4cba76456b31a9426be4f5d3",
  "conventions": {
    "ambiguities": [
      "tail_call"
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
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0033"
      ],
      "claim": "no terminal return is present in the listing",
      "confidence": "UNKNOWN",
      "id": "C2"
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0023",
        "obs-0028"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          92,
          209,
          258
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0033"
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
        "obs-0033"
      ],
      "claim": "this listing is a tail transfer: it inherits its caller's frame and never runs its own RET",
      "confidence": "UNKNOWN",
      "id": "T1",
      "value": {
        "form": "jmp"
      }
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x005dd7a0",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x005dd7a0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x005dd7a3",
      "count": 6,
      "first_use": 1,
      "first_write_index": 7,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x005dd7a4",
      "count": 7,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005dd7a5",
      "count": 5,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005dd7a5",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x005dd7a7",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x5c]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005dd7aa",
      "count": 5,
      "first_use": 5,
      "first_write_index": 32,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x005dd7ab",
      "id": "obs-0009",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0057aaa0",
      "target": "0x0057aaa0"
    },
    {
      "at": "0x005dd7b0",
      "definite": true,
      "id": "obs-0010",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "XOR EBX,EBX",
      "reg": "EBX",
      "write_kind": "zero"
    },
    {
      "at": "0x005dd7b2",
      "count": 8,
      "first_use": 8,
      "first_write_index": 0,
      "id": "obs-0011",
      "index": 8,
      "kind": "REG_READ",
      "raw": "MOV byte ptr [ESP + 0x10],BL",
      "reg": "ESP"
    },
    {
      "at": "0x005dd7b2",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0012",
      "index": 8,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV byte ptr [ESP + 0x10],BL",
      "reason": "local",
      "resolved": false,
      "size": 1,
      "via": "direct"
    },
    {
      "at": "0x005dd7b6",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0013",
      "index": 9,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV byte ptr [ESP + 0xc],BL",
      "reason": "local",
      "resolved": false,
      "size": 1,
      "via": "direct"
    },
    {
      "at": "0x005dd7c7",
      "count": 4,
      "first_use": 14,
      "first_write_index": 36,
      "id": "obs-0014",
      "index": 14,
      "kind": "REG_READ",
      "raw": "JMP dword ptr [EAX*0x4 + 0x5dd840]",
      "reg": "EAX"
    },
    {
      "at": "0x005dd7c7",
      "base": null,
      "disp": 6150208,
      "id": "obs-0015",
      "index": 14,
      "kind": "JMP_INDIRECT",
      "raw": "JMP dword ptr [EAX*
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
"\nvoid __fastcall FUN_005dd7a0(int param_1)\n\n{\n  undefined4 uVar1;\n  int *piVar2;\n  undefined4 unaff_ESI;\n  undefined4 local_4;\n  \n  uVar1 = FUN_0057aaa0();\n  local_4 = 0;\n  if (*(char *)(param_1 + 0x102) != '\\0') {\n    switch(uVar1) {\n    case 0:\n    case 1:\n    case 2:\n      break;\n    case 3:\n    case 4:\n      break;\n    default:\n      goto switchD_005dd7c7_default;\n    }\n    local_4 = 1;\n  }\nswitchD_005dd7c7_default:\n  piVar2 = (int *)FUN_008105b0(0x5b6e484,1);\n  if (piVar2 == (int *)0x0) {\n    piVar2 = (int *)FUN_008105b0(0x5b6e484,1);\n  }\n  if (piVar2 != (int *)0x0) {\n    (**(code **)(*piVar2 + 0x7c))(1,local_4);\n    (**(code **)(*piVar2 + 0x7c))(2,unaff_ESI);\n  }\n  FUN_005dc800();\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 55,
  "instructions": [
    {
      "address": "005dd7a0",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "005dd7a3",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005dd7a4",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005dd7a5",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005dd7a7",
      "instruction": "MOV ECX,dword ptr [ESI + 0x5c]"
    },
    {
      "address": "005dd7aa",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005dd7ab",
      "instruction": "CALL 0x0057aaa0"
    },
    {
      "address": "005dd7b0",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "005dd7b2",
      "instruction": "MOV byte ptr [ESP + 0x10],BL"
    },
    {
      "address": "005dd7b6",
      "instruction": "MOV byte ptr [ESP + 0xc],BL"
    },
    {
      "address": "005dd7ba",
      "instruction": "CMP byte ptr [ESI + 0x102],BL"
    },
    {
      "address": "005dd7c0",
      "instruction": "JZ 0x005dd7de"
    },
    {
      "address": "005dd7c2",
      "instruction": "CMP EAX,0x4"
    },
    {
      "address": "005dd7c5",
      "instruction": "JA 0x005dd7de"
    },
    {
      "address": "005dd7c7",
      "instruction": "JMP dword ptr [EAX*0x4 + 0x5dd840]"
    },
    {
      "address": "005dd7ce",
      "instruction": "MOV byte ptr [ESP + 0xc],BL"
    },
    {
      "address": "005dd7d2",
      "instruction": "JMP 0x005dd7d9"
    },
    {
      "address": "005dd7d4",
      "instruction": "MOV byte ptr [ESP + 0xc],0x1"
    },
    {
      "address": "005dd7d9",
      "instruction": "MOV byte ptr [ESP + 0x10],0x1"
    },
    {
      "address": "005dd7de",
      "instruction": "CMP byte ptr [ESI + 0xd1],BL"
    },
    {
      "address": "005dd7e4",
      "instruction": "JNZ 0x005dd7ea"
    },
    {
      "address": "005dd7e6",
      "instruction": "MOV byte ptr [ESP + 0xc],BL"
    },
    {
      "address": "005dd7ea",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dd7ec",
      "instruction": "PUSH 0x5b6e484"
    },
    {
      "address": "005dd7f1",
      "instruction": "LEA ECX,[ESI + 0x14]"
    },
    {
      "address": "005dd7f4",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005dd7f9",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "005dd7fb",
      "instruction": "JNZ 0x005dd80c"
    },
    {
      "address": "005dd7fd",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dd7ff",
      "instruction": "PUSH 0x5b6e484"
    },
    {
      "address": "005dd804",
      "instruction": "LEA ECX,[ESI + 0x2c]"
    },
    {
      "address": "005dd807",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005dd80c",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "005dd80e",
      "instruction": "CMP EDI,EBX"
    },
    {
      "address": "005dd810",
      "instruction": "JZ 0x005dd832"
    },
    {
      "address": "005dd812",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "005dd816",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "005dd818",
      "instruction": "MOV EDX,dword ptr [EAX + 0x7c]"
    },
    {
      "address": "005dd81b",
      "instruction": "PUSH ECX"
    },
    {
      "address": "005dd81c",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dd81e",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "005dd820",
      "instruction": "CALL EDX"
    },
    {
      "address": "005dd822",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "005dd826",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "005dd828",
      "instruction": "MOV EDX,dword ptr [EAX + 0x7c]"
    },
    {
      "address": "005dd82b",
      "instruction": "PUSH ECX"
    },
    {
      "address": "005dd82c",
      "instruction": "PUSH 0x2"
    },
    {
      "address": "005dd82e",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "005dd830",
      "instruction": "CALL EDX"
    },
    {
      "address": "005dd832",
      "instruction": "POP EDI"
    },
    {
      "address": "005dd833",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005dd835",
      "instruction": "POP ESI"
    },
    {
      "address": "005dd836",
      "instruction": "POP EBX"
    },
    {
      "address": "005dd837",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "005dd83a",
      "instruction": "JMP 0x005dc800"
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
  "body_end": "005dd83e",
  "body_span_bytes": 159,
  "body_start": "005dd7a0",
  "callees": [
    "FUN_005dc800",
    "FUN_0057aaa0",
    "FUN_008105b0"
  ],
  "callers": [
    "FUN_005de690",
    "FUN_0058a1e0",
    "Editors::cEditor::Undo",
    "FUN_0057f6c0",
    "Editors::cEditor::HandleMessage",
    "FUN_0058d1c0",
    "Editors::cEditor::CommitEditHistory",
    "FUN_0057ea30",
    "FUN_0057ed00",
    "Editors::cEditor::Redo",
    "FUN_00586690"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005dd7a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "piVar2",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "unaff_ESI",
      "storage": "register:00000018:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_005dd7a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1dd7a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005dd7a0(void)",
  "size_bytes": 159,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005dd7a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 14,
  "xrefs": [
    {
      "from": "005de849"
    },
    {
      "from": "00586654"
    },
    {
      "from": "0057eb9b"
    },
    {
      "from": "0057ed3c"
    },
    {
      "from": "0058a33c"
    },
    {
      "from": "0058a787"
    },
    {
      "from": "0058a7ca"
    },
    {
      "from": "0058ab12"
    },
    {
      "from": "0058d31a"
    },
    {
      "from": "0058d373"
    },
    {
      "from": "005866f9"
    },
    {
      "from": "0057f7bd"
    },
    {
      "from": "00592ec3"
    },
    {
      "from": "00592f51"
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
