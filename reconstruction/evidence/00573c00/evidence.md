# Evidence 0x00573c00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `21e6ddf8255d5372f657a618329cda5683d8da612c97d61ce22e514b183bb857`

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
      "entry_ESP+0x8"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "17f30856c55164bba7ec2029a69f9b21fc5e88c8421ba32bcdcf8d6b002d1b22",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0033"
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
        "obs-0007",
        "obs-0010"
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
        "obs-0003",
        "obs-0004",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0018"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          60,
          204,
          228,
          796,
          920,
          944,
          948,
          964,
          1176
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0018",
        "obs-0033"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
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
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0033"
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
      "at": "0x00573c00",
      "count": 12,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00573c01",
      "count": 15,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00573c02",
      "count": 7,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00573c02",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00573c04",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0xcc]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00573c0a",
      "count": 2,
      "first_use": 4,
      "first_write_index": 24,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
     
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
"\nvoid __thiscall FUN_00573c00(int param_1,int param_2,int param_3)\n\n{\n  int *piVar1;\n  int iVar2;\n  int *piVar3;\n  char cVar4;\n  undefined4 uVar5;\n  \n  iVar2 = *(int *)(param_1 + 0xcc);\n  piVar1 = (int *)(param_1 + 0xcc);\n  if ((param_2 == iVar2) && ((param_2 == 0 || (param_3 == *(int *)(param_1 + 0x3b0)))))\n  goto LAB_00573d5a;\n  *(int *)(param_1 + 0x3b0) = param_3;\n  *(int *)(param_1 + 0x3b4) = param_3;\n  if (iVar2 == param_2) goto LAB_00573d5a;\n  if (iVar2 != 0) {\n    cVar4 = FUN_004a60a0(param_2,iVar2);\n    if ((*(int *)(param_1 + 0xe4) != 0) && (cVar4 == '\\0')) {\n      uVar5 = FUN_0047e6c0();\n      FUN_004a60a0(uVar5,*piVar1);\n    }\n    FUN_0043a830(0);\n  }\n  if (param_2 == 0) {\n    if ((*(uint *)(*piVar1 + 0xdc8) >> 3 & 1) != 0) {\n      FUN_0043e2b0();\n    }\n    piVar3 = (int *)*piVar1;\n    if (piVar3 != (int *)0x0) {\n      *piVar1 = 0;\n      (**(code **)(*piVar3 + 8))();\n    }\n    if (*(int *)(param_1 + 0x498) != 0) {\n      FUN_005cc690();\n    }\n  }\n  else if ((*(uint *)(param_2 + 0xdc8) >> 1 & 1) == 0) {\n    FUN_004b09b0(param_2);\n    cVar4 = FUN_004a2060(param_2);\n    if ((cVar4 == '\\0') && (*(int *)(param_1 + 0x498) != 0)) {\n      FUN_005cc690();\n    }\n    if (*(int *)(param_1 + 0x31c) == 1) {\n      if ((*(int *)(param_1 + 0x3c4) != 0) && (cVar4 = FUN_005ca920(), cVar4 != '\\0')) {\nLAB_00573d28:\n        FUN_004a88d0(0xbb58117e);\n        FUN_0043a830(1);\n      }\n    }\n    else if (((*(uint *)(*piVar1 + 0xdc8) >> 0xb & 1) == 0) ||\n            ((*(uint *)(*piVar1 + 0xdc8) >> 10 & 1) == 0)) goto LAB_00573d28;\n  }\n  if ((*(int *)(param_1 + 0x31c) == 0) && ((*(uint *)(param_1 + 0x3c) & 0x100) != 0)) {\n    FUN_00573520(*piVar1);\n  }\nLAB_00573d5a:\n  *(bool *)(param_1 + 0x398) = *piVar1 != 0;\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 115,
  "instructions": [
    {
      "address": "00573c00",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00573c01",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00573c02",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00573c04",
      "instruction": "MOV EAX,dword ptr [ESI + 0xcc]"
    },
    {
      "address": "00573c0a",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00573c0e",
      "instruction": "LEA EBX,[ESI + 0xcc]"
    },
    {
      "address": "00573c14",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00573c15",
      "instruction": "MOV EDI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00573c19",
      "instruction": "CMP EDI,EAX"
    },
    {
      "address": "00573c1b",
      "instruction": "JNZ 0x00573c31"
    },
    {
      "address": "00573c1d",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00573c1f",
      "instruction": "JZ 0x00573d5a"
    },
    {
      "address": "00573c25",
      "instruction": "CMP ECX,dword ptr [ESI + 0x3b0]"
    },
    {
      "address": "00573c2b",
      "instruction": "JZ 0x00573d5a"
    },
    {
      "address": "00573c31",
      "instruction": "MOV dword ptr [ESI + 0x3b0],ECX"
    },
    {
      "address": "00573c37",
      "instruction": "MOV dword ptr [ESI + 0x3b4],ECX"
    },
    {
      "address": "00573c3d",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00573c3f",
      "instruction": "JZ 0x00573d5a"
    },
    {
      "address": "00573c45",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00573c47",
      "instruction": "JZ 0x00573c80"
    },
    {
      "address": "00573c49",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00573c4a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00573c4b",
      "instruction": "CALL 0x004a60a0"
    },
    {
      "address": "00573c50",
      "instruction": "MOV ECX,dword ptr [ESI + 0xe4]"
    },
    {
      "address": "00573c56",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00573c59",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00573c5b",
      "instruction": "SETZ AL"
    },
    {
      "address": "00573c5e",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00573c60",
      "instruction": "JZ 0x00573c77"
    },
    {
      "address": "00573c62",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00573c64",
      "instruction": "JZ 0x00573c77"
    },
    {
      "address": "00573c66",
      "instruction": "CALL 0x0047e6c0"
    },
    {
      "address": "00573c6b",
      "instruction": "MOV ECX,dword ptr [EBX]"
    },
    {
      "address": "00573c6d",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00573c6e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00573c6f",
      "instruction": "CALL 0x004a60a0"
    },
    {
      "address": "00573c74",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00573c77",
      "instruction": "MOV ECX,dword ptr [EBX]"
    },
    {
      "address": "00573c79",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00573c7b",
      "instruction": "CALL 0x0043a830"
    },
    {
      "address": "00573c80",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00573c82",
      "instruction": "JNZ 0x00573cc1"
    },
    {
      "address": "00573c84",
      "instruction": "MOV ECX,dword ptr [EBX]"
    },
    {
      "address": "00573c86",
      "instruction": "MOV EDX,dword ptr [ECX + 0xdc8]"
    },
    {
      "address": "00573c8c",
      "instruction": "SHR EDX,0x3"
    },
    {
      "address": "00573c8f",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "00573c92",
      "instruction": "JZ 0x00573c99"
    },
    {
      "address": "00573c94",
      "instruction": "CALL 0x0043e2b0"
    },
    {
      "address": "00573c99",
      "instruction": "MOV ECX,dword ptr [EBX]"
    },
    {
      "address": "00573c9b",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00573c9d",
      "instruction": "JZ 0x00573cac"
    },
    {
      "address": "00573c9f",
      "instruction": "MOV dword ptr [EBX],0x0"
    },
    {
      "address": "00573ca5",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00573ca7",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00573caa",
      "instruction": "CALL EDX"
    },
    {
      "address": "00573cac",
      "instruction": "MOV ECX,dword ptr [ESI + 0x498]"
    },
    {
      "address": "00573cb2",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00573cb4",
      "instruction": "JZ 0x00573d3e"
    },
    {
      "address": "00573cba",
      "instruction": "CALL 0x005cc690"
    },
    {
      "address": "00573cbf",
      "instruction": "JMP 0x00573d3e"
    },
    {
      "address": "00573cc1",
      "instruction": "MOV EAX,dword ptr [EDI + 0xdc8]"
    },
    {
      "address": "00573cc7",
      "instruction": "SHR EAX,0x1"
    },
    {
      "address": "00573cc9",
      "instruction": "TEST AL,0x1"
    },
    {
      "address": "00573ccb",
      "instruction": "JNZ 0x00573d3e"
    },
    {
      "address": "00573ccd",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00573cce",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00573cd0",
      "instruction": "CALL 0x004b09b0"
    },
    {
      "address": "00573cd5",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00573cd6",
      "instruction": "CALL 0x004a2060"
    },
    {
      "address": "00573cdb",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00573cde",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00573ce0",
      "instruction": "JNZ 0x00573cf1"
    },
    {
      "address": "00573ce2",
      "instruction": "MOV ECX,dword ptr [ESI + 0x498]"
  
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
  "body_end": "00573d6b",
  "body_span_bytes": 364,
  "body_start": "00573c00",
  "callees": [
    "FUN_004a88d0",
    "FUN_005cc690",
    "FUN_004a2060",
    "FUN_00573520",
    "FUN_005ca920",
    "FUN_0043a830",
    "FUN_004a60a0",
    "FUN_0047e6c0",
    "FUN_004b09b0",
    "FUN_0043e2b0"
  ],
  "callers": [
    "FUN_0058ba60",
    "FUN_0057f6c0",
    "FUN_005774f0",
    "Editors::cEditor::HandleMessage",
    "Editors::cEditor::OnKeyDown",
    "FUN_00577520",
    "Editors::cEditor::OnMouseUp",
    "FUN_00573d70",
    "Editors::cEditor::SetActiveMode",
    "Editors::cEditor::OnMouseDown",
    "FUN_005858f0",
    "Editors::cEditor::OnExit",
    "FUN_005e0000"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00573c00",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar5",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "piVar1",
      "storage": "unique:00006800:4",
      "type": "int *"
    },
    {
      "name": "iVar2",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "piVar3",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "cVar4",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "int"
    }
  ],
  "locals_count": 8,
  "mode": "live",
  "name": "FUN_00573c00",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x173c00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00573c00(void)",
  "size_bytes": 364,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00573c00",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 17,
  "xrefs": [
    {
      "from": "0057753d"
    },
    {
      "from": "00573ea3"
    },
    {
      "from": "00587465"
    },
    {
      "from": "00585bcd"
    },
    {
      "from": "00587cd4"
    },
    {
      "from": "0058b99b"
    },
    {
      "from": "0058bc51"
    },
    {
      "from": "0058bc77"
    },
    {
      "from": "0058bd42"
    },
    {
      "from": "005e0353"
    },
    {
      "from": "0058028e"
    },
    {
      "from": "0058aec3"
    },
    {
      "from": "0057750e"
    },
    {
      "from": "00588f8f"
    },
    {
      "from": "00589ca5"
    },
    {
      "from": "0059228a"
    },
    {
      "from": "0059303e"
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
