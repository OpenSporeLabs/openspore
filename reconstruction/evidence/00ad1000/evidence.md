# Evidence 0x00ad1000

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `4dc9c2251ccefd1cf2505e2e9bf85f38bc82c542eb391e66341229464c7e81c6`

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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
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
  "content_sha256": "c35bd3c063f8bfcce3fad2303ae3ac33be4441253f3ee96504d4c23ac2d9ee0a",
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
    "indirect_calls": 8,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0061"
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
        "obs-0005",
        "obs-0011"
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
        "obs-0012",
        "obs-0024",
        "obs-0025",
        "obs-0026",
        "obs-0029",
        "obs-0033",
        "obs-0038",
        "obs-0043"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0061"
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
        "obs-0061"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0061"
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
      "at": "0x00ad1000",
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
      "raw": "SUB ESP,0x14",
      "sub": 20
    },
    {
      "at": "0x00ad1000",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x14",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00ad1003",
      "count": 14,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00ad1004",
      "count": 23,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x20]",
      "reg": "ESP"
    },
    {
      "at": "0x00ad1004",
      "base": "ESP",
      "disp": 32,
      "id": "obs-0005",
      "index": 2,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x20]",
      "resolved": true,
      "size": 4,
      "trust": 
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
"\nvoid FUN_00ad1000(int param_1,int param_2)\n\n{\n  int *piVar1;\n  code *pcVar2;\n  int iVar3;\n  int iVar4;\n  int *piVar5;\n  int *piVar6;\n  int iVar7;\n  int iVar8;\n  int local_14;\n  \n  iVar8 = param_2;\n  if (0 < param_2) {\n    iVar3 = FUN_00ad0ca0(&param_1);\n    piVar1 = (int *)(iVar3 + 8);\n    iVar3 = (*(int *)(iVar3 + 0xc) - *(int *)(iVar3 + 8)) / 0xc;\n    iVar4 = FUN_00b3d300();\n    if (iVar3 < iVar8) {\n      FUN_00acd920(iVar8);\n      iVar7 = iVar3 * 0xc;\n      local_14 = iVar8 - iVar3;\n      do {\n        iVar8 = *piVar1;\n        piVar5 = (int *)FUN_00b20c60(param_1);\n        piVar6 = *(int **)(iVar8 + iVar7 + 8);\n        if (piVar5 != piVar6) {\n          if (piVar5 != (int *)0x0) {\n            (**(code **)*piVar5)();\n          }\n          *(int **)(iVar8 + iVar7 + 8) = piVar5;\n          if (piVar6 != (int *)0x0) {\n            (**(code **)(*piVar6 + 4))();\n          }\n        }\n        *(undefined1 *)(*piVar1 + 4 + iVar7) = 0;\n        iVar7 = iVar7 + 0xc;\n        local_14 = local_14 + -1;\n      } while (local_14 != 0);\n      local_14 = 0;\n      iVar8 = param_2;\n    }\n    else if (iVar8 < iVar3) {\n      if (iVar8 < iVar3) {\n        iVar7 = iVar8 * 0xc;\n        param_1 = iVar3 - iVar8;\n        do {\n          FUN_00b225d0(*(undefined4 *)(*piVar1 + 8 + iVar7));\n          iVar7 = iVar7 + 0xc;\n          param_1 = param_1 + -1;\n        } while (param_1 != 0);\n      }\n      FUN_00acd920(iVar8);\n    }\n    iVar7 = (**(code **)(**(int **)(*piVar1 + 8) + 0xc))(0x116dd1b);\n    *(bool *)(iVar4 + 4) = iVar7 != 0;\n    if ((iVar7 != 0) && (iVar3 < iVar8)) {\n      iVar7 = iVar3 * 0xc;\n      iVar4 = iVar8 - iVar3;\n      do {\n        piVar6 = *(int **)(*piVar1 + 8 + iVar7);\n        if ((piVar6 != (int *)0x0) &&\n           (piVar6 = (int *)(**(code **)(*piVar6 + 0xc))(0x116dd1b), iVar8 = param_1,\n           piVar6 != (int *)0x0)) {\n          pcVar2 = *(code **)(*piVar6 + 0x38);\n          *(undefined1 *)((int)piVar6 + 0x75) = 0;\n          (*pcVar2)(&DAT_0167a390);\n          *(undefined1 *)((int)piVar6 + 0x71) = 1;\n          iVar8 = param_1;\n        }\n        iVar7 = iVar7 + 0xc;\n        iVar4 = iVar4 + -1;\n      } while (iVar4 != 0);\n    }\n    iVar4 = (**(code **)(**(int **)(*piVar1 + 8) + 0xc))(&LAB_011c0ba1_2);\n    *(bool *)(local_14 + 5) = iVar4 != 0;\n    iVar4 = (**(code **)(**(int **)(*piVar1 + 8) + 0xc))(0xce9f6639);\n    if ((iVar4 != 0) && (iVar3 < iVar8)) {\n      iVar4 = iVar3 * 0xc;\n      iVar8 = iVar8 - iVar3;\n      do {\n        piVar6 = *(int **)(iVar4 + 8 + *piVar1);\n        if ((piVar6 != (int *)0x0) && (iVar3 = (**(code **)(*piVar6 + 0xc))(0xce9f6639), iVar3 != 0)\n           ) {\n          FUN_00c0bf00(1);\n        }\n        iVar4 = iVar4 + 0xc;\n        iVar8 = iVar8 + -1;\n      } while (iVar8 != 0);\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 14811,
  "preview": "{\n  \"count\": 177,\n  \"instructions\": [\n    {\n      \"address\": \"00ad1000\",\n      \"instruction\": \"SUB ESP,0x14\"\n    },\n    {\n      \"address\": \"00ad1003\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00ad1004\",\n      \"instruction\": \"MOV EDI,dword ptr [ESP + 0x20]\"\n    },\n    {\n      \"address\": \"00ad1008\",\n      \"instruction\": \"TEST EDI,EDI\"\n    },\n    {\n      \"address\": \"00ad100a\",\n      \"instruction\": \"JLE 0x00ad11e4\"\n    },\n    {\n      \"address\": \"00ad1010\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00ad1011\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00ad1012\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00ad1013\",\n      \"instruction\": \"LEA EAX,[ESP + 0x28]\"\n    },\n    {\n      \"address\": \"00ad1017\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00ad1018\",\n      \"instruction\": \"ADD ECX,0x88\"\n    },\n    {\n      \"address\": \"00ad101e\",\n      \"instruction\": \"CALL 0x00ad0ca0\"\n    },\n    {\n      \"address\": \"00ad1023\",\n      \"instruction\": \"MOV ECX,dword ptr [EAX + 0xc]\"\n    },\n    {\n      \"address\": \"00ad1026\",\n      \"instruction\": \"SUB ECX,dword ptr [EAX + 0x8]\"\n    },\n    {\n      \"address\": \"00ad1029\",\n      \"instruction\": \"LEA ESI,[EAX + 0x8]\"\n    },\n    {\n      \"address\": \"00ad102c\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x18],EAX\"\n    },\n    {\n      \"address\": \"00ad1030\",\n      \"instruction\": \"MOV EAX,0x2aaaaaab\"\n    },\n    {\n      \"address\": \"00ad1035\",\n      \"instruction\": \"IMUL ECX\"\n    },\n    {\n      \"address\": \"00ad1037\",\n      \"instruction\": \"SAR EDX,0x1\"\n    },\n    {\n      \"address\": \"00ad1039\",\n      \"instruction\": \"MOV EBP,EDX\"\n    },\n    {\n      \"address\": \"00ad103b\",\n      \"instruction\": \"SHR EBP,0x1f\"\n    },\n    {\n      \"address\": \"00ad103e\",\n      \"instruction\": \"ADD EBP,EDX\"\n    },\n    {\n      \"address\": \"00ad1040\",\n      \"instruction\": \"CALL 0x00b3d300\"\n    },\n    {\n      \"address\": \"00ad1045\",\n      \"instruction\": \"CMP EBP,EDI\"\n    },\n    {\n      \"address\": \"00ad1047\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x14],EAX\"\n    },\n    {\n      \"address\": \"00ad104b\",\n      \"instruction\": \"JGE 0x00ad10bd\"\n    },\n    {\n      \"address\": \"00ad104d\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00ad104e\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00ad1050\",\n      \"instruction\": \"CALL 0x00acd920\"\n    },\n    {\n      \"address\": \"00ad1055\",\n      \"instruction\": \"LEA EBX,[EBP + EBP*0x2]\"\n    },\n    {\n      \"address\": \"00ad1059\",\n      \"instruction\": \"ADD EBX,EBX\"\n    },\n    {\n      \"address\": \"00ad105b\",\n      \"instruction\": \"ADD EBX,EBX\"\n    },\n    {\n      \"address\": \"00ad105d\",\n      \"instruction\": \"SUB EDI,EBP\"\n    },\n    {\n      \"address\": \"00ad105f\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x10],EDI\"\n    },\n    {\n      \"address\": \"00ad1063\",\n      \"instruction\": \"MOV ECX,dword ptr [ESP + 0x28]\"\n    },\n    {\n      \"address\": \"00ad1067\",\n      \"instruction\": \"MOV EDI,dword ptr [ESI]\"\n    },\n    {\n      \"address\": \"00ad1069\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00ad106a\",\n      \"instruction\": \"MOV ECX,dword ptr [ESP + 0x18]\"\n    },\n    {\n      \"address\": \"00ad106e\",\n      \"instruction\": \"ADD EDI,EBX\"\n    },\n    {\n      \"address\": \"00ad1070\",\n      \"instruction\": \"CALL 0x00b20c60\"\n    },\n    {\n      \"address\": \"00ad1075\",\n      \"instruction\": \"MOV ECX,dword ptr [EDI + 0x8]\"\n    },\n    {\n      \"address\": \"00ad1078\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x1c],EAX\"\n    },\n    {\n      \"address\": \"00ad107c\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x20],ECX\"\n    },\n    {\n      \"address\": \"00ad1080\",\n      \"instruction\": \"CMP EAX,ECX\"\n    },\n    {\n      \"address\": \"00ad1082\",\n      \"instruction\": \"JZ 0x00ad10a6\"\n    },\n    {\n      \"address\": \"00ad1084\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"00ad1086\",\n      \"instruction\": \"JZ 0x00ad1098\"\n    },\n    {\n      \"address\": \"00ad1088\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"00ad108a\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00ad108c\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX]\"\n    },\n    {\n      \"address\": \"00ad108e\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00ad1090\",\n      \"instruction\": \"MOV EAX,dword ptr [ESP + 0x1c]\"\n    },\n    {\n      \"address\": \"00ad1094\",\n      \"instruction\": \"MOV ECX,dword ptr [ESP + 0x20]\"\n    },\n    {\n      \"address\": \"00ad1098\",\n      \"instruction\": \"MOV dword ptr [EDI + 0x8],EAX\"\n    },\n    {\n      \"address\": \"00ad109b\",\n      \"instruction\": \"TEST ECX,ECX\"\n    },\n    {\n      \"address\": \"00ad109d\",\n      \"instruction\": \"JZ 0x00ad10a6\"\n    },\n    {\n      \"address\": \"00ad109f\",\n      \"instruction\": \"MOV EDX,dword ptr [ECX]\"\n    },\n    {\n      \"address\": \"00ad10a1\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x4]\"\n    },\n    {\n      \"address\": \"00ad10a4\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00ad10a6\",\n      \"instruction\": \"MOV ECX,dword ptr [ESI]\"\n    },\n    {\n      \"address\": \"00ad10a8\",\n      \"instruction\": \"MOV byte ptr [ECX + EBX*0x1 + 0x4],0x0\"\n    },\n    {\n      \"address\": \"00ad10ad\",\n      \"instruction\": \"ADD EBX,0x
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
  "body_end": "00ad11ea",
  "body_span_bytes": 491,
  "body_start": "00ad1000",
  "callees": [
    "FUN_00acd920",
    "FUN_00b20c60",
    "FUN_00c0bf00",
    "FUN_00b225d0",
    "FUN_00ad0ca0",
    "FUN_00b3d300"
  ],
  "callers": [
    "FUN_00ad2200",
    "FUN_00ad20e0",
    "FUN_00ad11f0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ad1000",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "piVar1",
      "storage": "unique:00006600:4",
      "type": "int *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "piVar5",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "iVar4",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "pcVar2",
      "storage": "unique:00017200:4",
      "type": "undefined *"
    },
    {
      "name": "iVar8",
      "storage": "register:0000001c:4",
      "type": "int"
    },
    {
      "name": "iVar7",
      "storage": "register:0000000c:4",
      "type": "int"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "int"
    },
    {
      "name": "piVar6",
      "storage": "register:00000000:4",
      "type": "int *"
    }
  ],
  "locals_count": 11,
  "mode": "live",
  "name": "FUN_00ad1000",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6d1000",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ad1000(void)",
  "size_bytes": 491,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ad1000",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00ad1256"
    },
    {
      "from": "00ad21cc"
    },
    {
      "from": "00ad228d"
    },
    {
      "from": "00ad22a0"
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
