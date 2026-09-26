# Evidence 0x00dd6df0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d6d0aed8d5595ad9c610ccf44601c2cc30816d89e17e35c3b531a1a48d08b524`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
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
        "size_inferred": true,
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
        "size_inferred": true,
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
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +32, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "2bb4a3673be703267b79140e597b615773c1a3a30aeedbe6826e268f29e764bf",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
      "__thiscall"
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
        "obs-0030",
        "obs-0034"
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
        "obs-0003",
        "obs-0009",
        "obs-0011",
        "obs-0013",
        "obs-0015"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0011",
        "obs-0018"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0011",
        "obs-0018"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0030",
        "obs-0034"
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
        "obs-0030",
        "obs-0034"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0030",
        "obs-0034"
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
      "at": "0x00dd6df0",
      "count": 2,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00dd6df1",
      "count": 5,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00dd6df1",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0003",
      "index": 1,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00dd6df1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESP + 0xc]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00dd6df5",
      "count": 9,
      "first_use": 2,
      "first_write_index": 19,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00dd6df6",
      "count": 6,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 3,
      "kind": 
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
"\nundefined4 __thiscall FUN_00dd6df0(int param_1,undefined4 param_2,int param_3)\n\n{\n  int iVar1;\n  int *piVar2;\n  int iVar3;\n  int iVar4;\n  \n  iVar4 = param_3;\n  if (param_3 != 0) {\n    param_3 = param_2;\n    piVar2 = (int *)map_int_whatever_find(&param_2,&param_3);\n    if ((*piVar2 != param_1 + 0x2c) && (iVar1 = *(int *)(*piVar2 + 0x14), iVar1 != 0)) {\n      piVar2 = (int *)FUN_008105b0(0x35ee914,1);\n      if (piVar2 != (int *)0x0) {\n        piVar2 = (int *)(**(code **)(*piVar2 + 0xf0))(0x47d4388,1);\n        if (piVar2 != (int *)0x0) {\n          iVar3 = (**(code **)(*piVar2 + 0xc))(0xf15f4bd);\n          if ((iVar3 != 0) && ((*(int *)(iVar1 + 0x6c) - *(int *)(iVar1 + 0x68) & 0xfffffffeU) != 0)\n             ) {\n            FUN_005c3d90(iVar4);\n            *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xffffffbf;\n            *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 1;\n            FUN_00dd60c0(iVar1);\n            iVar4 = FUN_00dd5dd0(iVar1);\n            if (iVar4 != 0) {\n              FUN_00dd6bc0(*(undefined4 *)(iVar4 + 0x48));\n            }\n            return 1;\n          }\n        }\n      }\n    }\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 74,
  "instructions": [
    {
      "address": "00dd6df0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00dd6df1",
      "instruction": "MOV EBX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00dd6df5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00dd6df6",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00dd6df7",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00dd6df9",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00dd6dfb",
      "instruction": "JZ 0x00dd6eb5"
    },
    {
      "address": "00dd6e01",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00dd6e05",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00dd6e09",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00dd6e0a",
      "instruction": "LEA EDX,[ESP + 0x14]"
    },
    {
      "address": "00dd6e0e",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00dd6e0f",
      "instruction": "LEA ECX,[EDI + 0x28]"
    },
    {
      "address": "00dd6e12",
      "instruction": "MOV dword ptr [ESP + 0x1c],EAX"
    },
    {
      "address": "00dd6e16",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "00dd6e1b",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00dd6e1d",
      "instruction": "LEA ECX,[EDI + 0x2c]"
    },
    {
      "address": "00dd6e20",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "00dd6e22",
      "instruction": "JZ 0x00dd6eb5"
    },
    {
      "address": "00dd6e28",
      "instruction": "MOV ESI,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00dd6e2b",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00dd6e2d",
      "instruction": "JZ 0x00dd6eb5"
    },
    {
      "address": "00dd6e33",
      "instruction": "MOV ECX,dword ptr [ESI + 0x78]"
    },
    {
      "address": "00dd6e36",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00dd6e38",
      "instruction": "PUSH 0x35ee914"
    },
    {
      "address": "00dd6e3d",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "00dd6e42",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00dd6e44",
      "instruction": "JZ 0x00dd6eb5"
    },
    {
      "address": "00dd6e46",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00dd6e48",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00dd6e4a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00dd6e4c",
      "instruction": "MOV EAX,dword ptr [EDX + 0xf0]"
    },
    {
      "address": "00dd6e52",
      "instruction": "PUSH 0x47d4388"
    },
    {
      "address": "00dd6e57",
      "instruction": "CALL EAX"
    },
    {
      "address": "00dd6e59",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00dd6e5b",
      "instruction": "JZ 0x00dd6eb5"
    },
    {
      "address": "00dd6e5d",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00dd6e5f",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00dd6e61",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00dd6e64",
      "instruction": "PUSH 0xf15f4bd"
    },
    {
      "address": "00dd6e69",
      "instruction": "CALL EAX"
    },
    {
      "address": "00dd6e6b",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00dd6e6d",
      "instruction": "JZ 0x00dd6eb5"
    },
    {
      "address": "00dd6e6f",
      "instruction": "MOV EDX,dword ptr [ESI + 0x6c]"
    },
    {
      "address": "00dd6e72",
      "instruction": "SUB EDX,dword ptr [ESI + 0x68]"
    },
    {
      "address": "00dd6e75",
      "instruction": "LEA ECX,[ESI + 0x68]"
    },
    {
      "address": "00dd6e78",
      "instruction": "TEST EDX,0xfffffffe"
    },
    {
      "address": "00dd6e7e",
      "instruction": "JZ 0x00dd6eb5"
    },
    {
      "address": "00dd6e80",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00dd6e81",
      "instruction": "CALL 0x005c3d90"
    },
    {
      "address": "00dd6e86",
      "instruction": "AND dword ptr [ESI + 0xc],0xffffffbf"
    },
    {
      "address": "00dd6e8a",
      "instruction": "OR dword ptr [ESI + 0xc],0x1"
    },
    {
      "address": "00dd6e8e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00dd6e8f",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00dd6e91",
      "instruction": "CALL 0x00dd60c0"
    },
    {
      "address": "00dd6e96",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00dd6e97",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00dd6e99",
      "instruction": "CALL 0x00dd5dd0"
    },
    {
      "address": "00dd6e9e",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00dd6ea0",
      "instruction": "JZ 0x00dd6ead"
    },
    {
      "address": "00dd6ea2",
      "instruction": "MOV EAX,dword ptr [EAX + 0x48]"
    },
    {
      "address": "00dd6ea5",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00dd6ea6",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00dd6ea8",
      "instruction": "CALL 0x00dd6bc0"
    },
    {
      "address": "00dd6ead",
      "instruction": "POP EDI"
    },
    {
      "address": "00dd6eae",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd6eaf",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00dd6eb1",
      "instruction": "POP EBX"
    },
    {
      "address": "00dd6eb2",
      "instruction": "RET 0x8"
    },
    {
      "address": "00dd6eb5",
      "instruction": "POP EDI"
    },
    {
      "address": "00dd6eb6",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd6eb7",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00dd6eb9",
      "instruction": "POP EBX"
    },
    {
      "address": "00dd6eba",
   
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
  "body_end": "00dd6ebc",
  "body_span_bytes": 205,
  "body_start": "00dd6df0",
  "callees": [
    "FUN_008105b0",
    "FUN_00dd5dd0",
    "FUN_00dd6bc0",
    "FUN_00dd60c0",
    "FUN_005c3d90",
    "map_int_whatever_find"
  ],
  "callers": [
    "FUN_00c4fe60",
    "FUN_00c562b0",
    "FUN_00fe5a20",
    "FUN_010531b0",
    "FUN_00c5c470",
    "FUN_00dd8640",
    "FUN_00c4fc00",
    "FUN_00c568d0",
    "FUN_00c4fa40",
    "FUN_01053980",
    "FUN_00c4c4b0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00dd6df0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar4",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar1",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "piVar2",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00dd6df0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x9d6df0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00dd6df0(void)",
  "size_bytes": 205,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00dd6df0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 22,
  "xrefs": [
    {
      "from": "00dd8753"
    },
    {
      "from": "00c4c589"
    },
    {
      "from": "00c4fce5"
    },
    {
      "from": "00c4fdd4"
    },
    {
      "from": "00c4ff99"
    },
    {
      "from": "00c50132"
    },
    {
      "from": "00c56328"
    },
    {
      "from": "00c56925"
    },
    {
      "from": "00c5c506"
    },
    {
      "from": "00fe5e15"
    },
    {
      "from": "0105320e"
    },
    {
      "from": "01053b9b"
    },
    {
      "from": "00c4fadb"
    },
    {
      "from": "00c4fb5d"
    },
    {
      "from": "00c4fbb5"
    },
    {
      "from": "00c549dc"
    },
    {
      "from": "00c5dd1b"
    },
    {
      "from": "00c5de29"
    },
    {
      "from": "00c5e21c"
    },
    {
      "from": "00c5e563"
    },
    {
      "from": "00c56413"
    },
    {
      "from": "00c5659b"
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
