# Evidence 0x00e36670

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `6050ffb6b5386cfe8b7134677123ce0abb3a34583f7c0feecd0371c494d99851`

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
    "ret_form": "RET",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "receiver_not_determinable: ecx_address_taken_without_memory_access",
    "ecx_address_taken_without_memory_access: LEA takes ECX's address without any memory access through it",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_address_taken_without_memory_access), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "75176ce2b63b7180eea2acaca3add9deb5f864356e10bce5334537c7be335e07",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0068"
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
        "obs-0007",
        "obs-0013",
        "obs-0016",
        "obs-0020",
        "obs-0025",
        "obs-0032"
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
        "obs-0015",
        "obs-0016",
        "obs-0017",
        "obs-0020",
        "obs-0040"
      ],
      "claim": "the register receiver is undetermined: ecx_address_taken_without_memory_access",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_address_taken_without_memory_access",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0016",
        "obs-0017",
        "obs-0020",
        "obs-0040"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_address_taken_without_memory_access) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0032"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00e36670",
      "count": 13,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "reg": "XMM0"
    },
    {
      "at": "0x00e36670",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "and_esp": null,
      "at": "0x00e36673",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": 32
    },
    {
      "at": "0x00e36673",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00e36676",
      "count": 11,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,

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
"\nfloat * FUN_00e36670(float *param_1,int *param_2)\n\n{\n  int *piVar1;\n  float fVar2;\n  float fVar3;\n  float fVar4;\n  code *pcVar5;\n  float *pfVar6;\n  int *piVar7;\n  uint uVar8;\n  float *pfVar9;\n  float unaff_ESI;\n  float unaff_EDI;\n  float fVar10;\n  float fVar11;\n  float fVar12;\n  float fVar13;\n  float fVar14;\n  undefined4 *unaff_retaddr;\n  float fStack_20;\n  float fStack_1c;\n  undefined4 *puStack_4;\n  \n  piVar7 = param_2;\n  pfVar6 = param_1;\n  pcVar5 = *(code **)(*param_2 + 0xcc);\n  *param_1 = 0.0;\n  param_1[1] = 0.0;\n  param_1[2] = 0.0;\n  param_1[3] = 0.0;\n  (*pcVar5)(&param_1);\n  (**(code **)(*piVar7 + 0xd0))(&param_1);\n  piVar7 = param_2;\n  do {\n    if (puStack_4 == unaff_retaddr) {\n      return pfVar6;\n    }\n    piVar1 = puStack_4 + -1;\n    if (((char)piVar7 == '\\0') || (uVar8 = (**(code **)(*piVar1 + 0x28))(), (uVar8 & 1) != 0)) {\n      pfVar9 = (float *)(**(code **)(*piVar1 + 0x38))();\n      fVar2 = *pfVar9;\n      fVar13 = pfVar9[1];\n      fVar3 = pfVar9[2];\n      fVar4 = pfVar9[3];\n      fVar10 = fVar2;\n      fVar12 = fVar4;\n      fVar11 = fVar13;\n      fVar14 = fVar3;\n      if ((char)param_1 != '\\0') {\n        FUN_00e36670(&stack0xffffffd8,piVar1,param_1,piVar7);\n        fVar12 = fStack_20 - unaff_EDI;\n        unaff_EDI = fVar2 + unaff_EDI;\n        fVar10 = fStack_1c - unaff_ESI;\n        unaff_ESI = fVar13 + unaff_ESI;\n        fStack_20 = unaff_EDI + fVar12;\n        fStack_1c = fVar10 + unaff_ESI;\n        fVar10 = unaff_EDI;\n        fVar12 = fStack_1c;\n        fVar11 = unaff_ESI;\n        fVar14 = fStack_20;\n        if ((fVar2 != fVar3) && (fVar13 != fVar4)) {\n          fVar10 = fVar2;\n          fVar11 = fVar13;\n          fVar14 = fVar3;\n          if ((unaff_EDI != fStack_20) && (unaff_ESI != fStack_1c)) {\n            fVar10 = unaff_EDI;\n            if (fVar2 < unaff_EDI) {\n              fVar10 = fVar2;\n            }\n            fVar11 = unaff_ESI;\n            if (fVar13 < unaff_ESI) {\n              fVar11 = fVar13;\n            }\n            fVar14 = fStack_20;\n            if (fStack_20 < fVar3) {\n              fVar14 = fVar3;\n            }\n            if (fVar4 <= fStack_1c) goto LAB_00e367f6;\n          }\n          fVar12 = fVar4;\n        }\n      }\nLAB_00e367f6:\n      fVar2 = *pfVar6;\n      fVar13 = pfVar6[2];\n      if (fVar2 != fVar13) {\n        fVar3 = pfVar6[1];\n        fVar4 = pfVar6[3];\n        if (fVar3 != fVar4) {\n          if ((fVar10 != fVar14) && (fVar11 != fVar12)) {\n            if (fVar2 < fVar10) {\n              fVar10 = fVar2;\n            }\n            if (fVar3 < fVar11) {\n              fVar11 = fVar3;\n            }\n            if (fVar13 <= fVar14) {\n              fVar13 = fVar14;\n            }\n            fVar2 = fVar10;\n            fVar3 = fVar11;\n            fVar14 = fVar13;\n            if (fVar4 <= fVar12) goto LAB_00e3685a;\n          }\n          fVar11 = fVar3;\n          fVar10 = fVar2;\n          fVar12 = fVar4;\n          fVar14 = fVar13;\n        }\n      }\nLAB_00e3685a:\n      *pfVar6 = fVar10;\n      pfVar6[1] = fVar11;\n      pfVar6[2] = fVar14;\n      pfVar6[3] = fVar12;\n    }\n    puStack_4 = (undefined4 *)*puStack_4;\n  } while( true );\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 13942,
  "preview": "{\n  \"count\": 165,\n  \"instructions\": [\n    {\n      \"address\": \"00e36670\",\n      \"instruction\": \"XORPS XMM0,XMM0\"\n    },\n    {\n      \"address\": \"00e36673\",\n      \"instruction\": \"SUB ESP,0x20\"\n    },\n    {\n      \"address\": \"00e36676\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00e36677\",\n      \"instruction\": \"MOV ESI,dword ptr [ESP + 0x2c]\"\n    },\n    {\n      \"address\": \"00e3667b\",\n      \"instruction\": \"MOV EAX,dword ptr [ESI]\"\n    },\n    {\n      \"address\": \"00e3667d\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX + 0xcc]\"\n    },\n    {\n      \"address\": \"00e36683\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00e36684\",\n      \"instruction\": \"MOV EDI,dword ptr [ESP + 0x2c]\"\n    },\n    {\n      \"address\": \"00e36688\",\n      \"instruction\": \"LEA ECX,[ESP + 0x2c]\"\n    },\n    {\n      \"address\": \"00e3668c\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00e3668d\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00e3668f\",\n      \"instruction\": \"MOVSS dword ptr [EDI],XMM0\"\n    },\n    {\n      \"address\": \"00e36693\",\n      \"instruction\": \"MOVSS dword ptr [EDI + 0x4],XMM0\"\n    },\n    {\n      \"address\": \"00e36698\",\n      \"instruction\": \"MOVSS dword ptr [EDI + 0x8],XMM0\"\n    },\n    {\n      \"address\": \"00e3669d\",\n      \"instruction\": \"MOVSS dword ptr [EDI + 0xc],XMM0\"\n    },\n    {\n      \"address\": \"00e366a2\",\n      \"instruction\": \"CALL EDX\"\n    },\n    {\n      \"address\": \"00e366a4\",\n      \"instruction\": \"MOV EAX,dword ptr [ESI]\"\n    },\n    {\n      \"address\": \"00e366a6\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX + 0xd0]\"\n    },\n    {\n      \"address\": \"00e366ac\",\n      \"instruction\": \"LEA ECX,[ESP + 0x30]\"\n    },\n    {\n      \"address\": \"00e366b0\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00e366b1\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00e366b3\",\n      \"instruction\": \"CALL EDX\"\n    },\n    {\n      \"address\": \"00e366b5\",\n      \"instruction\": \"MOV EAX,dword ptr [ESP + 0x2c]\"\n    },\n    {\n      \"address\": \"00e366b9\",\n      \"instruction\": \"CMP EAX,dword ptr [ESP + 0x30]\"\n    },\n    {\n      \"address\": \"00e366bd\",\n      \"instruction\": \"JZ 0x00e36882\"\n    },\n    {\n      \"address\": \"00e366c3\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00e366c4\",\n      \"instruction\": \"MOV EBX,dword ptr [ESP + 0x3c]\"\n    },\n    {\n      \"address\": \"00e366c8\",\n      \"instruction\": \"JMP 0x00e366d0\"\n    },\n    {\n      \"address\": \"00e366d0\",\n      \"instruction\": \"MOV ECX,dword ptr [0x01440aec]\"\n    },\n    {\n      \"address\": \"00e366d6\",\n      \"instruction\": \"LEA ESI,[ECX + EAX*0x1]\"\n    },\n    {\n      \"address\": \"00e366d9\",\n      \"instruction\": \"TEST BL,BL\"\n    },\n    {\n      \"address\": \"00e366db\",\n      \"instruction\": \"JZ 0x00e366ee\"\n    },\n    {\n      \"address\": \"00e366dd\",\n      \"instruction\": \"MOV EDX,dword ptr [ESI]\"\n    },\n    {\n      \"address\": \"00e366df\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x28]\"\n    },\n    {\n      \"address\": \"00e366e2\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00e366e4\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00e366e6\",\n      \"instruction\": \"TEST AL,0x1\"\n    },\n    {\n      \"address\": \"00e366e8\",\n      \"instruction\": \"JZ 0x00e3686d\"\n    },\n    {\n      \"address\": \"00e366ee\",\n      \"instruction\": \"MOV EDX,dword ptr [ESI]\"\n    },\n    {\n      \"address\": \"00e366f0\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x38]\"\n    },\n    {\n      \"address\": \"00e366f3\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00e366f5\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00e366f7\",\n      \"instruction\": \"MOVSS XMM0,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"00e366fb\",\n      \"instruction\": \"MOVSS XMM2,dword ptr [EAX + 0x4]\"\n    },\n    {\n      \"address\": \"00e36700\",\n      \"instruction\": \"MOVSS XMM4,dword ptr [EAX + 0x8]\"\n    },\n    {\n      \"address\": \"00e36705\",\n      \"instruction\": \"MOVSS XMM1,dword ptr [EAX + 0xc]\"\n    },\n    {\n      \"address\": \"00e3670a\",\n      \"instruction\": \"MOV EAX,dword ptr [ESP + 0x38]\"\n    },\n    {\n      \"address\": \"00e3670e\",\n      \"instruction\": \"MOVSS dword ptr [ESP + 0x1c],XMM0\"\n    },\n    {\n      \"address\": \"00e36714\",\n      \"instruction\": \"MOVSS dword ptr [ESP + 0x20],XMM2\"\n    },\n    {\n      \"address\": \"00e3671a\",\n      \"instruction\": \"MOVSS dword ptr [ESP + 0x24],XMM4\"\n    },\n    {\n      \"address\": \"00e36720\",\n      \"instruction\": \"MOVSS dword ptr [ESP + 0x28],XMM1\"\n    },\n    {\n      \"address\": \"00e36726\",\n      \"instruction\": \"TEST AL,AL\"\n    },\n    {\n      \"address\": \"00e36728\",\n      \"instruction\": \"JZ 0x00e367f6\"\n    },\n    {\n      \"address\": \"00e3672e\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00e3672f\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00e36730\",\n      \"instruction\": \"LEA ECX,[ESP + 0x14]\"\n    },\n    {\n      \"address\": \"00e36734\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00e36735\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00e36736\",\n      \"instruction\": \"CALL 0x00e36670\"\n    },\n    {\n      \"address\": \"00e3673b\",\n      \"instruction\": \"MOVSS XMM1,dword ptr [ESP + 0x1c]\"\n    },\n    {\n      \"address\": \"00e
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
  "body_end": "00e36889",
  "body_span_bytes": 538,
  "body_start": "00e36670",
  "callees": [
    "FUN_00e36670"
  ],
  "callers": [
    "FUN_0082a500",
    "FUN_00e36670",
    "FUN_00e369f0",
    "FUN_00e368e0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e36670",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "fVar13",
      "storage": "register:000012c0:4",
      "type": "float"
    },
    {
      "name": "fVar14",
      "storage": "register:000012c0:4",
      "type": "float"
    },
    {
      "name": "unaff_retaddr",
      "storage": "Stack[0x0]:4",
      "type": "undefined4 *"
    },
    {
      "name": "unaff_EDI",
      "storage": "register:0000001c:4",
      "type": "float"
    },
    {
      "name": "fVar10",
      "storage": "register:00001240:4",
      "type": "float"
    },
    {
      "name": "fVar11",
      "storage": "register:00001280:4",
      "type": "float"
    },
    {
      "name": "fVar12",
      "storage": "register:000012c0:4",
      "type": "float"
    },
    {
      "name": "piVar7",
      "storage": "unique:10000115:4",
      "type": "int *"
    },
    {
      "name": "uVar8",
      "storage": "register:00000000:4",
      "type": "uint"
    },
    {
      "name": "pfVar9",
      "storage": "register:00000000:4",
      "type": "float *"
    },
    {
      "name": "unaff_ESI",
      "storage": "register:00000018:4",
      "type": "float"
    },
    {
      "name": "fVar3",
      "storage": "unique:0000a300:4",
      "type": "float"
    },
    {
      "name": "fVar4",
      "storage": "unique:0000a300:4",
      "type": "float"
    },
    {
      "name": "pcVar5",
      "storage": "unique:00017200:4",
      "type": "undefined *"
    },
    {
      "name": "pfVar6",
      "storage": "unique:10000111:4",
      "type": "float *"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "float *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "int *"
    },
    {
      "name": "piVar1",
      "storage": "unique:00006c00:4",
      "type": "int *"
    },
    {
      "name": "fVar2",
      "storage": "unique:0000a300:4",
      "type": "float"
    },
    {
      "name": "fStack_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "float"
    },
    {
      "name": "puStack_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4 *"
    },
    {
      "name": "fStack_20",
      "storage": "Stack[-0x20]:4",
      "type": "float"
    }
  ],
  "locals_count": 22,
  "mode": "live",
  "name": "FUN_00e36670",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa36670",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e36670(void)",
  "size_bytes": 538,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e36670",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "0082a659"
    },
    {
      "from": "00e36736"
    },
    {
      "from": "00e36986"
    },
    {
      "from": "00e36a0d"
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
