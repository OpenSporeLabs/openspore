# Evidence 0x00bba640

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `981f1d513f91172c115383127fcc78c7132c92c6690c8a0038eb20dc4430cd1b`

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
    "flow_not_modelled: the linear ESP walk ends at +44, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "3be8ebce15c46999e60384a34ef31211939a556ed353a03f807514b0083925b8",
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
    "indirect_calls": 7,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0056"
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
        "obs-0004",
        "obs-0005",
        "obs-0013",
        "obs-0024",
        "obs-0032",
        "obs-0034",
        "obs-0041",
        "obs-0043",
        "obs-0047"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          112,
          132,
          136,
          172
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0013",
        "obs-0024",
        "obs-0032",
        "obs-0034",
        "obs-0041",
        "obs-0043",
        "obs-0047",
        "obs-0056"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0056"
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
        "obs-0056"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0056"
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
      "and_esp": null,
      "at": "0x00bba640",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 6,
      "raw": "SUB ESP,0x1c",
      "sub": 28
    },
    {
      "at": "0x00bba640",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x1c",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00bba643",
      "count": 8,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00bba644",
      "count": 12,
      "first_use": 2,
      "first_write_index": 15,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EBX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00bba644",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,ECX",
      "reg": "EBX",
      "write_kind": "reg"
    },
    {
      "at": "0x00bba646",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBX + 0x88]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bba659",
      "count": 9,
      "first_use": 6,
      "first_write_index": null,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00bba660",
      "count": 21,
      "first_use": 8,
      "first_write_index": 3,
      "id": "obs-0008",
      "index": 8,
      "kind": "REG_READ",
      "raw": "SAR EAX,0x2",
      "reg": "EAX"
    },
    {
      "at": "0x00bba66b",
      "base": "EBP",
      "disp": 4,
      "id": "obs-0009",
      "index": 11,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDX,dword ptr [EBP + 0x4]",
      "reason": 
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
"\n/* WARNING: Removing unreachable block (ram,0x00bba6f6) */\n/* WARNING: Removing unreachable block (ram,0x00bba6b0) */\n/* WARNING: Removing unreachable block (ram,0x00bba760) */\n/* WARNING: Removing unreachable block (ram,0x00bba710) */\n/* WARNING: Removing unreachable block (ram,0x00bba730) */\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nvoid __fastcall FUN_00bba640(int param_1)\n\n{\n  int iVar1;\n  undefined4 *puVar2;\n  IGameModeManager *pIVar3;\n  int local_18;\n  int *piStack_14;\n  int local_10;\n  IGameModeManager local_c;\n  undefined4 local_8;\n  undefined4 local_4;\n  \n  if (*(int *)(param_1 + 0x88) - *(int *)(param_1 + 0x84) >> 2 != (uint)*(byte *)(param_1 + 0xac)) {\n    FUN_00e25bd0(*(undefined4 *)(param_1 + 0x84),*(undefined4 *)(param_1 + 0x88));\n    local_10 = 0;\n    if (*(char *)(param_1 + 0xac) != '\\0') {\n      local_18 = 0;\n      do {\n        iVar1 = *(int *)(param_1 + 0x70);\n        pIVar3 = App__IGameModeManager__Get();\n        local_8 = 0x5220cb8;\n        local_4 = 1;\n        local_c._vftable0 = (IGameModeManager__vftable *)(iVar1 + local_18);\n        (*pIVar3->_vftable0->Initialize)(&local_c);\n        piStack_14 = (int *)0x0;\n        puVar2 = *(undefined4 **)(param_1 + 0x88);\n        if (puVar2 < *(undefined4 **)(param_1 + 0x8c)) {\n          *(undefined4 **)(param_1 + 0x88) = puVar2 + 1;\n          if (puVar2 == (undefined4 *)0x0) goto LAB_00bba74b;\n          *puVar2 = 0;\n        }\n        else {\n          FUN_00aea5d0(puVar2,&piStack_14);\nLAB_00bba74b:\n          if (piStack_14 != (int *)0x0) {\n            (**(code **)(*piStack_14 + 4))();\n          }\n        }\n        local_18 = local_18 + 0x1000000;\n        local_10 = local_10 + 1;\n      } while (local_10 < (int)(uint)*(byte *)(param_1 + 0xac));\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 116,
  "instructions": [
    {
      "address": "00bba640",
      "instruction": "SUB ESP,0x1c"
    },
    {
      "address": "00bba643",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bba644",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00bba646",
      "instruction": "MOV EAX,dword ptr [EBX + 0x88]"
    },
    {
      "address": "00bba64c",
      "instruction": "SUB EAX,dword ptr [EBX + 0x84]"
    },
    {
      "address": "00bba652",
      "instruction": "MOVZX ECX,byte ptr [EBX + 0xac]"
    },
    {
      "address": "00bba659",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00bba65a",
      "instruction": "LEA EBP,[EBX + 0x84]"
    },
    {
      "address": "00bba660",
      "instruction": "SAR EAX,0x2"
    },
    {
      "address": "00bba663",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "00bba665",
      "instruction": "JZ 0x00bba789"
    },
    {
      "address": "00bba66b",
      "instruction": "MOV EDX,dword ptr [EBP + 0x4]"
    },
    {
      "address": "00bba66e",
      "instruction": "MOV EAX,dword ptr [EBP]"
    },
    {
      "address": "00bba671",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bba672",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bba673",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00bba675",
      "instruction": "CALL 0x00e25bd0"
    },
    {
      "address": "00bba67a",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00bba67c",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "00bba680",
      "instruction": "CMP byte ptr [EBX + 0xac],AL"
    },
    {
      "address": "00bba686",
      "instruction": "JBE 0x00bba789"
    },
    {
      "address": "00bba68c",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bba68d",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bba68e",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "00bba692",
      "instruction": "JMP 0x00bba696"
    },
    {
      "address": "00bba694",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00bba696",
      "instruction": "MOV ESI,dword ptr [EBX + 0x70]"
    },
    {
      "address": "00bba699",
      "instruction": "ADD ESI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00bba69d",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00bba6a1",
      "instruction": "CALL 0x0067dcd0"
    },
    {
      "address": "00bba6a6",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00bba6aa",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00bba6ac",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00bba6ae",
      "instruction": "JZ 0x00bba6bf"
    },
    {
      "address": "00bba6b0",
      "instruction": "MOV dword ptr [ESP + 0x10],0x0"
    },
    {
      "address": "00bba6b8",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00bba6ba",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "00bba6bd",
      "instruction": "CALL EAX"
    },
    {
      "address": "00bba6bf",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00bba6c1",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00bba6c3",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00bba6c5",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00bba6c7",
      "instruction": "LEA EAX,[ESP + 0x20]"
    },
    {
      "address": "00bba6cb",
      "instruction": "MOV dword ptr [ESP + 0x30],ESI"
    },
    {
      "address": "00bba6cf",
      "instruction": "MOV dword ptr [ESP + 0x34],0x5220cb8"
    },
    {
      "address": "00bba6d7",
      "instruction": "MOV dword ptr [ESP + 0x38],0x1"
    },
    {
      "address": "00bba6df",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "00bba6e1",
      "instruction": "MOV EDX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00bba6e4",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bba6e5",
      "instruction": "LEA ECX,[ESP + 0x34]"
    },
    {
      "address": "00bba6e9",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bba6ea",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00bba6ec",
      "instruction": "CALL EDX"
    },
    {
      "address": "00bba6ee",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00bba6f2",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00bba6f4",
      "instruction": "JZ 0x00bba706"
    },
    {
      "address": "00bba6f6",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00bba6f8",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00bba6fb",
      "instruction": "PUSH 0x3e434e1"
    },
    {
      "address": "00bba700",
      "instruction": "CALL EDX"
    },
    {
      "address": "00bba702",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00bba704",
      "instruction": "JMP 0x00bba708"
    },
    {
      "address": "00bba706",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00bba708",
      "instruction": "MOV dword ptr [ESP + 0x18],ESI"
    },
    {
      "address": "00bba70c",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00bba70e",
      "instruction": "JZ 0x00bba718"
    },
    {
      "address": "00bba710",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00bba712",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00bba714",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bba716",
      "instruction": "CALL EDX"
    },
    {
      "address": "00bba718",
      "instruction": "MOV EAX,dword ptr [EBP + 0x4]"
    },
    {
      "
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
  "body_end": "00bba78e",
  "body_span_bytes": 335,
  "body_start": "00bba640",
  "callees": [
    "FUN_00e25bd0",
    "App::IGameModeManager::Get",
    "FUN_00aea5d0"
  ],
  "callers": [
    "FUN_00bbaa60",
    "FUN_00bbac80",
    "FUN_00bbaa80",
    "FUN_00bba790"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bba640",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "pIVar3",
      "storage": "register:00000000:4",
      "type": "IGameModeManager *"
    },
    {
      "name": "puVar2",
      "storage": "unique:00017200:4",
      "type": "undefined4 *"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "int"
    },
    {
      "name": "iVar1",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "IGameModeManager"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "piStack_14",
      "storage": "Stack[-0x14]:4",
      "type": "int *"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 10,
  "mode": "live",
  "name": "FUN_00bba640",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7ba640",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bba640(void)",
  "size_bytes": 335,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bba640",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00bba794"
    },
    {
      "from": "00bbaa63"
    },
    {
      "from": "00bbaa99"
    },
    {
      "from": "00bbaca4"
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
