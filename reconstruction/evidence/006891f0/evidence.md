# Evidence 0x006891f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7f4f84f7caf16cbecad379e6c359aa3def61208b34aedaf2ca10a8fac3cfb089`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
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
    "flow_not_modelled: the linear ESP walk ends at +36, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_read_without_deref",
    "no_discriminator: no stack-argument read and no positive receiver evidence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "0d05556cd9904d4e2d136d5510d72dbfbb678c5c48cc44409b9b28408cbf7df1",
  "conventions": {
    "ambiguities": [],
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0118"
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
        "obs-0014",
        "obs-0018",
        "obs-0019",
        "obs-0028",
        "obs-0041",
        "obs-0046",
        "obs-0051",
        "obs-0054",
        "obs-0059",
        "obs-0065",
        "obs-0069",
        "obs-0072",
        "obs-0076",
        "obs-0083",
        "obs-0096",
        "obs-0100",
        "obs-0107",
        "obs-0112",
        "obs-0117"
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
        "obs-0001",
        "obs-0004",
        "obs-0117"
      ],
      "claim": "an FS:/GS: operand is an SEH or cookie frame, which is not variadic evidence",
      "confidence": "OBSERVED",
      "id": "V2",
      "value": {
        "seh_or_cookie_frame": true
      }
    },
    {
      "based_on": [
        "obs-0118"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0118"
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
        "obs-0118"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0118"
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
      "id": "obs-0001"
    },
    {
      "id": "obs-0002"
    },
    {
      "id": "obs-0003"
    },
    {
      "id": "obs-0004"
    },
    {
      "id": "obs-0005"
    },
    {
      "id": "obs-0006"
    },
    {
      "id": "obs-0007"
    },
    {
      "id": "obs-0008"
    },
    {
      "id": "obs-0009"
    },
    {
      "id": "obs-0010"
    },
    {
      "id": "obs-0011"
    },
    {
      "id": "obs-0012"
    },
    {
      "id": "obs-0013"
    },
    {
      "id": "obs-0014"
    },
    {
      "id": "obs-0015"
    },
    {
      "id": "obs-0016"
    },
    {
      "id": "obs-0017"
    },
    {
      "id": "obs-0018"
    },
    {
      "id": "obs-0019"
    },
    {
      "id": "obs-0020"
    },
    {
      "id": "obs-0021"
    },
    {
      "id": "obs-0022"
    },
    {
      "id": "obs-0023"
    },
    {
      "id": "obs-0024"
    },
    {
      "id": "obs-0025"
    },
    {
      "id": "obs-0026"
    },
    {
      "id": "obs-0027"
    },
    {
      "id": "obs-0028"
    },
    {
      "id": "obs-0029"
    },
    {
      "id": "obs-0030"
    },
    {
      "id": "obs-0031"
    },
    {
      "id": "obs-0032"
    },
    {
      "id": "obs-0033"
    },
    {
      "id": "obs-0034"
    },
    {
      "id": "obs-0035"
    },
    {
      "id": "obs-0036"
    },
    {
      "id": "obs-0037"
    },
    {
      "id": "obs-0038"
    },
    {
      "id": "obs-0039"
    },
    {
      "id": "obs-0040"
    },
    {
      "id": "obs-0041"
    },
    {
      "id": "obs-0042"
    },
    {
      "id": "obs-0043"
    },
    {
      "id": "obs-0044"
    },
    {
      "id": "obs-0045"
    },
    {
      "id": "obs-0046"
    },
    {
      "id": "obs-0047"
    },
    {
      "id": "obs-0048"
    },
    {
      "id": "obs-0049"
    },
    {
      "id": "obs-0050"
    },
    {
      "id": "obs-0051"
    },
    {
      "id": "obs-0052"
    },
    {
      "id": "obs-0053"
    },
    {
      "id": "obs-0054"
    },
    {
      "id": "obs-0055"
    },
    {
      "id": "obs-0056"
    },

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
"\nvoid FUN_006891f0(undefined4 param_1,undefined4 param_2)\n\n{\n  size_t _Size;\n  int iVar1;\n  void *pvVar2;\n  void *_Src;\n  char cVar3;\n  int *piVar4;\n  undefined4 uVar5;\n  int iVar6;\n  int aiStack_6c [4];\n  int aiStack_5c [4];\n  void *pvStack_4c;\n  undefined2 *puStack_48;\n  int iStack_44;\n  void *pvStack_3c;\n  int iStack_38;\n  int iStack_34;\n  int aiStack_2c [4];\n  int aiStack_1c [2];\n  int iStack_14;\n  void *pvStack_c;\n  undefined1 *puStack_8;\n  undefined4 uStack_4;\n  \n  uStack_4 = 0xffffffff;\n  puStack_8 = &LAB_0120c8a0;\n  pvStack_c = ExceptionList;\n  ExceptionList = &pvStack_c;\n  piVar4 = (int *)FUN_006b1f90(0x4729a47);\n  uVar5 = (**(code **)(*piVar4 + 0x28))();\n  pvStack_3c = (void *)0x0;\n  iStack_38 = 0;\n  iStack_34 = 0;\n  FUN_00579a90(uVar5);\n  _Src = pvStack_3c;\n  iVar6 = iStack_38 - (int)pvStack_3c >> 1;\n  uStack_4 = 0;\n  pvStack_4c = (void *)0x0;\n  puStack_48 = (undefined2 *)0x0;\n  iStack_44 = 0;\n  FUN_00429760(iVar6 + 1);\n  pvVar2 = pvStack_4c;\n  _Size = iVar6 * 2;\n  memcpy(pvStack_4c,_Src,_Size);\n  puStack_48 = (undefined2 *)(_Size + (int)pvVar2);\n  *puStack_48 = 0;\n  uStack_4._0_1_ = 1;\n  FUN_00932ae0(pvVar2);\n  aiStack_6c[0] = 0;\n  aiStack_6c[1] = 0;\n  aiStack_6c[2] = 0;\n  FUN_00579a90(param_2);\n  uStack_4._0_1_ = 2;\n  piVar4 = (int *)FUN_00688f00(aiStack_2c,&pvStack_4c,aiStack_6c);\n  uStack_4._0_1_ = 3;\n  if (piVar4 != aiStack_6c) {\n    FUN_00423650(*piVar4,piVar4[1]);\n  }\n  uStack_4._0_1_ = 2;\n  if ((2 < (int)(aiStack_2c[2] - aiStack_2c[0] & 0xfffffffeU)) && (aiStack_2c[0] != 0)) {\n    FUN_00f47380(aiStack_2c[0]);\n  }\n  aiStack_5c[0] = 0;\n  aiStack_5c[1] = 0;\n  aiStack_5c[2] = 0;\n  FUN_00579a90(param_1);\n  uStack_4._0_1_ = 4;\n  piVar4 = (int *)FUN_00688f00(aiStack_2c,&pvStack_4c,aiStack_5c);\n  uStack_4._0_1_ = 5;\n  if (piVar4 != aiStack_5c) {\n    FUN_00423650(*piVar4,piVar4[1]);\n  }\n  uStack_4._0_1_ = 4;\n  if ((2 < (int)(aiStack_2c[2] - aiStack_2c[0] & 0xfffffffeU)) && (aiStack_2c[0] != 0)) {\n    FUN_00f47380(aiStack_2c[0]);\n  }\n  aiStack_2c[0] = 0;\n  aiStack_2c[1] = 0;\n  aiStack_2c[2] = 0;\n  FUN_00579a90(L\".old\");\n  uStack_4._0_1_ = 6;\n  FUN_00688f00(aiStack_1c,aiStack_6c,aiStack_2c);\n  uStack_4 = CONCAT31(uStack_4._1_3_,8);\n  if ((2 < (int)(aiStack_2c[2] - aiStack_2c[0] & 0xfffffffeU)) && (aiStack_2c[0] != 0)) {\n    FUN_00f47380(aiStack_2c[0]);\n  }\n  iVar6 = aiStack_6c[0];\n  cVar3 = IO_File_Remove(aiStack_6c[0]);\n  if (cVar3 != '\\0') {\n    FUN_00931ff0(iVar6,aiStack_1c[0],1);\n  }\n  iVar1 = aiStack_5c[0];\n  FUN_00931ff0(aiStack_5c[0],iVar6,1);\n  cVar3 = IO_File_Remove(aiStack_1c[0]);\n  if (cVar3 != '\\0') {\n    FUN_00931fd0(aiStack_1c[0]);\n  }\n  if ((2 < (int)(iStack_14 - aiStack_1c[0] & 0xfffffffeU)) && (aiStack_1c[0] != 0)) {\n    FUN_00f47380(aiStack_1c[0]);\n  }\n  if ((2 < (int)(aiStack_5c[2] - iVar1 & 0xfffffffeU)) && (iVar1 != 0)) {\n    FUN_00f47380(iVar1);\n  }\n  if ((2 < (int)(aiStack_6c[2] - iVar6 & 0xfffffffeU)) && (iVar6 != 0)) {\n    FUN_00f47380(iVar6);\n  }\n  if ((2 < (int)(iStack_44 - (int)pvVar2 & 0xfffffffeU)) && (pvVar2 != (void *)0x0)) {\n    FUN_00f47380(pvVar2);\n  }\n  if ((2 < (int)(iStack_34 - (int)pvStack_3c & 0xfffffffeU)) && (pvStack_3c != (void *)0x0)) {\n    FUN_00f47380(pvStack_3c);\n  }\n  ExceptionList = pvStack_c;\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 19745,
  "preview": "{\n  \"count\": 239,\n  \"instructions\": [\n    {\n      \"address\": \"006891f0\",\n      \"instruction\": \"PUSH -0x1\"\n    },\n    {\n      \"address\": \"006891f2\",\n      \"instruction\": \"PUSH 0x120c8a0\"\n    },\n    {\n      \"address\": \"006891f7\",\n      \"instruction\": \"MOV EAX,FS:[0x0]\"\n    },\n    {\n      \"address\": \"006891fd\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"006891fe\",\n      \"instruction\": \"MOV dword ptr FS:[0x0],ESP\"\n    },\n    {\n      \"address\": \"00689205\",\n      \"instruction\": \"SUB ESP,0x60\"\n    },\n    {\n      \"address\": \"00689208\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00689209\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"0068920a\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"0068920b\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"0068920c\",\n      \"instruction\": \"PUSH 0x4729a47\"\n    },\n    {\n      \"address\": \"00689211\",\n      \"instruction\": \"CALL 0x006b1f90\"\n    },\n    {\n      \"address\": \"00689216\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"00689218\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"0068921a\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x28]\"\n    },\n    {\n      \"address\": \"0068921d\",\n      \"instruction\": \"ADD ESP,0x4\"\n    },\n    {\n      \"address\": \"00689220\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00689222\",\n      \"instruction\": \"XOR EDI,EDI\"\n    },\n    {\n      \"address\": \"00689224\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00689225\",\n      \"instruction\": \"LEA ECX,[ESP + 0x44]\"\n    },\n    {\n      \"address\": \"00689229\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x44],EDI\"\n    },\n    {\n      \"address\": \"0068922d\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x48],EDI\"\n    },\n    {\n      \"address\": \"00689231\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x4c],EDI\"\n    },\n    {\n      \"address\": \"00689235\",\n      \"instruction\": \"CALL 0x00579a90\"\n    },\n    {\n      \"address\": \"0068923a\",\n      \"instruction\": \"MOV ESI,dword ptr [ESP + 0x44]\"\n    },\n    {\n      \"address\": \"0068923e\",\n      \"instruction\": \"MOV EBX,dword ptr [ESP + 0x40]\"\n    },\n    {\n      \"address\": \"00689242\",\n      \"instruction\": \"SUB ESI,EBX\"\n    },\n    {\n      \"address\": \"00689244\",\n      \"instruction\": \"SAR ESI,0x1\"\n    },\n    {\n      \"address\": \"00689246\",\n      \"instruction\": \"LEA ECX,[ESI + 0x1]\"\n    },\n    {\n      \"address\": \"00689249\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"0068924a\",\n      \"instruction\": \"LEA ECX,[ESP + 0x34]\"\n    },\n    {\n      \"address\": \"0068924e\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x7c],EDI\"\n    },\n    {\n      \"address\": \"00689252\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x34],EDI\"\n    },\n    {\n      \"address\": \"00689256\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x38],EDI\"\n    },\n    {\n      \"address\": \"0068925a\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x3c],EDI\"\n    },\n    {\n      \"address\": \"0068925e\",\n      \"instruction\": \"CALL 0x00429760\"\n    },\n    {\n      \"address\": \"00689263\",\n      \"instruction\": \"MOV EBP,dword ptr [ESP + 0x30]\"\n    },\n    {\n      \"address\": \"00689267\",\n      \"instruction\": \"ADD ESI,ESI\"\n    },\n    {\n      \"address\": \"00689269\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"0068926a\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"0068926b\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"0068926c\",\n      \"instruction\": \"CALL 0x011e0744\"\n    },\n    {\n      \"address\": \"00689271\",\n      \"instruction\": \"LEA EAX,[ESI + EBP*0x1]\"\n    },\n    {\n      \"address\": \"00689274\",\n      \"instruction\": \"XOR EDX,EDX\"\n    },\n    {\n      \"address\": \"00689276\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x40],EAX\"\n    },\n    {\n      \"address\": \"0068927a\",\n      \"instruction\": \"MOV word ptr [EAX],DX\"\n    },\n    {\n      \"address\": \"0068927d\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"0068927e\",\n      \"instruction\": \"MOV byte ptr [ESP + 0x88],0x1\"\n    },\n    {\n      \"address\": \"00689286\",\n      \"instruction\": \"CALL 0x00932ae0\"\n    },\n    {\n      \"address\": \"0068928b\",\n      \"instruction\": \"MOV EAX,dword ptr [ESP + 0x94]\"\n    },\n    {\n      \"address\": \"00689292\",\n      \"instruction\": \"ADD ESP,0x10\"\n    },\n    {\n      \"address\": \"00689295\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00689296\",\n      \"instruction\": \"LEA ECX,[ESP + 0x14]\"\n    },\n    {\n      \"address\": \"0068929a\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x14],EDI\"\n    },\n    {\n      \"address\": \"0068929e\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x18],EDI\"\n    },\n    {\n      \"address\": \"006892a2\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x1c],EDI\"\n    },\n    {\n      \"address\": \"006892a6\",\n      \"instruction\": \"CALL 0x00579a90\"\n    },\n    {\n      \"address\": \"006892ab\",\n      \"instruction\": \"LEA ECX,[ESP + 0x10]\"\n    },\n    {\n      \"address\": \"006892af\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"006892b0\",\n      \"instruction\": \"LEA EDX,[ESP + 0x34]\"\n    },\n    {\n      \"address\": \"006892b4\",\n      \"instruction\": \"PUSH EDX\"\n    },\n    {\n      \"address\": \"006892b5\",\n      \"instruction\": \"LEA
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
  "body_end": "006894ca",
  "body_span_bytes": 731,
  "body_start": "006891f0",
  "callees": [
    "IO_File_Remove",
    "FUN_006b1f90",
    "FUN_00931fd0",
    "FUN_00932ae0",
    "FUN_00688f00",
    "FUN_00f47380",
    "FUN_00579a90",
    "FUN_00429760",
    "memcpy",
    "FUN_00423650",
    "FUN_00931ff0"
  ],
  "callers": [
    "FUN_00b28ec0",
    "FUN_00bb4ba0",
    "FUN_00580cb0",
    "FUN_00de4850"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006891f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "puStack_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined1 *"
    },
    {
      "name": "uStack_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "_Size",
      "storage": "unique:100000da:4",
      "type": "size_t"
    },
    {
      "name": "iVar1",
      "storage": "unique:1000028a:4",
      "type": "int"
    },
    {
      "name": "iStack_44",
      "storage": "Stack[-0x44]:4",
      "type": "int"
    },
    {
      "name": "pvStack_3c",
      "storage": "Stack[-0x3c]:4",
      "type": "void *"
    },
    {
      "name": "iStack_38",
      "storage": "Stack[-0x38]:4",
      "type": "int"
    },
    {
      "name": "iStack_34",
      "storage": "Stack[-0x34]:4",
      "type": "int"
    },
    {
      "name": "aiStack_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "int[4]"
    },
    {
      "name": "aiStack_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "int[2]"
    },
    {
      "name": "iStack_14",
      "storage": "Stack[-0x14]:4",
      "type": "int"
    },
    {
      "name": "pvStack_c",
      "storage": "Stack[-0xc]:4",
      "type": "void *"
    },
    {
      "name": "aiStack_6c",
      "storage": "Stack[-0x6c]:4",
      "type": "int[4]"
    },
    {
      "name": "aiStack_5c",
      "storage": "Stack[-0x5c]:4",
      "type": "int[4]"
    },
    {
      "name": "pvStack_4c",
      "storage": "Stack[-0x4c]:4",
      "type": "void *"
    },
    {
      "name": "puStack_48",
      "storage": "Stack[-0x48]:4",
      "type": "undefined2 *"
    },
    {
      "name": "pvVar2",
      "storage": "unique:1000028e:4",
      "type": "void *"
    },
    {
      "name": "_Src",
      "storage": "unique:10000292:4",
      "type": "void *"
    },
    {
      "name": "cVar3",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "piVar4",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "uVar5",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "iVar6",
      "storage": "register:00000018:4",
      "type": "int"
    }
  ],
  "locals_count": 24,
  "mode": "live",
  "name": "FUN_006891f0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x2891f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_006891f0(void)",
  "size_bytes": 731,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006891f0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00b293d4"
    },
    {
      "from": "00bb4f0a"
    },
    {
      "from": "00580dc9"
    },
    {
      "from": "00de48eb"
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
