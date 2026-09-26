# Evidence 0x00688fa0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2b1d134c99ab050a16eb4e73b2c87e68462411bcc381e1372d39e3cf3519aed9`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
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
      }
    ],
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
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +44, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "0002119e3dadd45ceb19991795b744328451c0f5923688acf1e79834262d2ba6",
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
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0095"
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
        "obs-0008"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0014",
        "obs-0015",
        "obs-0023",
        "obs-0026",
        "obs-0035",
        "obs-0048",
        "obs-0051",
        "obs-0055",
        "obs-0081",
        "obs-0086",
        "obs-0089",
        "obs-0094"
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
        "obs-0094"
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
        "obs-0014",
        "obs-0015",
        "obs-0023",
        "obs-0026",
        "obs-0035",
        "obs-0048",
        "obs-0051",
        "obs-0055",
        "obs-0081",
        "obs-0086",
        "obs-0089",
        "obs-0094"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0095"
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
        "obs-0095"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0095"
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
"\nint * FUN_00688fa0(undefined4 param_1)\n\n{\n  size_t _Size;\n  void *_Src;\n  int *piVar1;\n  undefined4 uVar2;\n  void **ppvVar3;\n  int iVar4;\n  void *pvVar5;\n  int unaff_ESI;\n  int iVar6;\n  void *pvStack_4c;\n  undefined2 *puStack_48;\n  undefined4 uStack_44;\n  int iStack_40;\n  void *pvStack_3c;\n  int iStack_38;\n  undefined4 uStack_34;\n  int iStack_30;\n  undefined4 local_2c;\n  undefined4 local_28;\n  undefined4 local_24;\n  int iStack_1c;\n  void *pvStack_18;\n  int iStack_14;\n  undefined1 uStack_10;\n  void *pvStack_c;\n  undefined1 *puStack_8;\n  undefined4 local_4;\n  \n  local_4 = 0xffffffff;\n  puStack_8 = &LAB_0120c84c;\n  pvStack_c = ExceptionList;\n  local_2c = 0;\n  local_28 = 0;\n  local_24 = 0;\n  ExceptionList = &pvStack_c;\n  FUN_00579a90(param_1);\n  local_4 = 0;\n  piVar1 = (int *)FUN_006b1f90(0x4729a47);\n  uVar2 = (**(code **)(*piVar1 + 0x28))();\n  pvStack_3c = (void *)0x0;\n  iStack_38 = 0;\n  uStack_34 = 0;\n  FUN_00579a90(uVar2);\n  _Src = pvStack_3c;\n  iVar6 = iStack_38 - (int)pvStack_3c >> 1;\n  local_4._0_1_ = 1;\n  pvStack_4c = (void *)0x0;\n  puStack_48 = (undefined2 *)0x0;\n  uStack_44 = 0;\n  FUN_00429760(iVar6 + 1);\n  pvVar5 = pvStack_4c;\n  _Size = iVar6 * 2;\n  memcpy(pvStack_4c,_Src,_Size);\n  puStack_48 = (undefined2 *)(_Size + (int)pvVar5);\n  *puStack_48 = 0;\n  local_4._0_1_ = 2;\n  FUN_00932ae0(pvVar5);\n  ppvVar3 = (void **)FUN_00688f00(&iStack_1c,&pvStack_4c,&local_2c);\n  local_4._0_1_ = 3;\n  if (ppvVar3 != &pvStack_4c) {\n    FUN_00423650(*ppvVar3,ppvVar3[1]);\n    pvVar5 = pvStack_4c;\n  }\n  local_4._0_1_ = 2;\n  if ((2 < (int)(iStack_14 - iStack_1c & 0xfffffffeU)) && (iStack_1c != 0)) {\n    FUN_00f47380(iStack_1c);\n  }\n  FUN_00931fd0(pvVar5);\n  iVar6 = FUN_00926020(0x388,\"Simulator\",0,0,0,0);\n  local_4._0_1_ = 4;\n  if (iVar6 == 0) {\n    iVar6 = 0;\n  }\n  else {\n    iVar6 = FUN_008d9f80(0,0);\n  }\n  local_4._0_1_ = 2;\n  if (iVar6 != 0) {\n    (*(code *)**(undefined4 **)(iVar6 + 4))();\n  }\n  local_4._0_1_ = 5;\n  iVar4 = FUN_00926020(0x24,\"Simulator\",0,0,0,0);\n  local_4._0_1_ = 6;\n  if (iVar4 == 0) {\n    piVar1 = (int *)0x0;\n  }\n  else {\n    piVar1 = (int *)FUN_0069fa60(iVar6);\n  }\n  local_4 = CONCAT31(local_4._1_3_,5);\n  (**(code **)(piVar1[1] + 4))();\n  (**(code **)(piVar1[1] + 0x2c))(pvVar5);\n  (**(code **)(*piVar1 + 0x3c))(0,1);\n  uStack_10 = 2;\n  if (unaff_ESI != 0) {\n    (**(code **)(*(int *)(unaff_ESI + 4) + 4))();\n  }\n  if ((2 < (int)(iVar4 - (int)pvVar5 & 0xfffffffeU)) && (pvVar5 != (void *)0x0)) {\n    FUN_00f47380(pvVar5);\n  }\n  if ((2 < (int)(iStack_40 - (int)puStack_48 & 0xfffffffeU)) && (puStack_48 != (undefined2 *)0x0)) {\n    FUN_00f47380(puStack_48);\n  }\n  if ((2 < (int)(iStack_30 - iStack_38 & 0xfffffffeU)) && (iStack_38 != 0)) {\n    FUN_00f47380(iStack_38);\n  }\n  ExceptionList = pvStack_18;\n  return piVar1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 16783,
  "preview": "{\n  \"count\": 203,\n  \"instructions\": [\n    {\n      \"address\": \"00688fa0\",\n      \"instruction\": \"PUSH -0x1\"\n    },\n    {\n      \"address\": \"00688fa2\",\n      \"instruction\": \"PUSH 0x120c84c\"\n    },\n    {\n      \"address\": \"00688fa7\",\n      \"instruction\": \"MOV EAX,FS:[0x0]\"\n    },\n    {\n      \"address\": \"00688fad\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00688fae\",\n      \"instruction\": \"MOV dword ptr FS:[0x0],ESP\"\n    },\n    {\n      \"address\": \"00688fb5\",\n      \"instruction\": \"SUB ESP,0x4c\"\n    },\n    {\n      \"address\": \"00688fb8\",\n      \"instruction\": \"MOV EAX,dword ptr [ESP + 0x5c]\"\n    },\n    {\n      \"address\": \"00688fbc\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00688fbd\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00688fbe\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00688fbf\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00688fc0\",\n      \"instruction\": \"XOR EDI,EDI\"\n    },\n    {\n      \"address\": \"00688fc2\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00688fc3\",\n      \"instruction\": \"LEA ECX,[ESP + 0x40]\"\n    },\n    {\n      \"address\": \"00688fc7\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x40],EDI\"\n    },\n    {\n      \"address\": \"00688fcb\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x44],EDI\"\n    },\n    {\n      \"address\": \"00688fcf\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x48],EDI\"\n    },\n    {\n      \"address\": \"00688fd3\",\n      \"instruction\": \"CALL 0x00579a90\"\n    },\n    {\n      \"address\": \"00688fd8\",\n      \"instruction\": \"PUSH 0x4729a47\"\n    },\n    {\n      \"address\": \"00688fdd\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x68],EDI\"\n    },\n    {\n      \"address\": \"00688fe1\",\n      \"instruction\": \"CALL 0x006b1f90\"\n    },\n    {\n      \"address\": \"00688fe6\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"00688fe8\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00688fea\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x28]\"\n    },\n    {\n      \"address\": \"00688fed\",\n      \"instruction\": \"ADD ESP,0x4\"\n    },\n    {\n      \"address\": \"00688ff0\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00688ff2\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00688ff3\",\n      \"instruction\": \"LEA ECX,[ESP + 0x30]\"\n    },\n    {\n      \"address\": \"00688ff7\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x30],EDI\"\n    },\n    {\n      \"address\": \"00688ffb\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x34],EDI\"\n    },\n    {\n      \"address\": \"00688fff\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x38],EDI\"\n    },\n    {\n      \"address\": \"00689003\",\n      \"instruction\": \"CALL 0x00579a90\"\n    },\n    {\n      \"address\": \"00689008\",\n      \"instruction\": \"MOV ESI,dword ptr [ESP + 0x30]\"\n    },\n    {\n      \"address\": \"0068900c\",\n      \"instruction\": \"MOV EBX,dword ptr [ESP + 0x2c]\"\n    },\n    {\n      \"address\": \"00689010\",\n      \"instruction\": \"SUB ESI,EBX\"\n    },\n    {\n      \"address\": \"00689012\",\n      \"instruction\": \"SAR ESI,0x1\"\n    },\n    {\n      \"address\": \"00689014\",\n      \"instruction\": \"LEA ECX,[ESI + 0x1]\"\n    },\n    {\n      \"address\": \"00689017\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00689018\",\n      \"instruction\": \"LEA ECX,[ESP + 0x20]\"\n    },\n    {\n      \"address\": \"0068901c\",\n      \"instruction\": \"MOV byte ptr [ESP + 0x68],0x1\"\n    },\n    {\n      \"address\": \"00689021\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x20],EDI\"\n    },\n    {\n      \"address\": \"00689025\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x24],EDI\"\n    },\n    {\n      \"address\": \"00689029\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x28],EDI\"\n    },\n    {\n      \"address\": \"0068902d\",\n      \"instruction\": \"CALL 0x00429760\"\n    },\n    {\n      \"address\": \"00689032\",\n      \"instruction\": \"MOV EBP,dword ptr [ESP + 0x1c]\"\n    },\n    {\n      \"address\": \"00689036\",\n      \"instruction\": \"ADD ESI,ESI\"\n    },\n    {\n      \"address\": \"00689038\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00689039\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"0068903a\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"0068903b\",\n      \"instruction\": \"CALL 0x011e0744\"\n    },\n    {\n      \"address\": \"00689040\",\n      \"instruction\": \"ADD ESI,EBP\"\n    },\n    {\n      \"address\": \"00689042\",\n      \"instruction\": \"XOR EDX,EDX\"\n    },\n    {\n      \"address\": \"00689044\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x2c],ESI\"\n    },\n    {\n      \"address\": \"00689048\",\n      \"instruction\": \"MOV word ptr [ESI],DX\"\n    },\n    {\n      \"address\": \"0068904b\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"0068904c\",\n      \"instruction\": \"MOV byte ptr [ESP + 0x74],0x2\"\n    },\n    {\n      \"address\": \"00689051\",\n      \"instruction\": \"CALL 0x00932ae0\"\n    },\n    {\n      \"address\": \"00689056\",\n      \"instruction\": \"LEA EAX,[ESP + 0x4c]\"\n    },\n    {\n      \"address\": \"0068905a\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"0068905b\",\n      \"instruction\": \"LEA ECX,[ESP + 0x30]\"\n    },\n    {\n      \"address\": \"0068905f\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00689060\",\n      \"instruction\": 
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
  "body_end": "006891e5",
  "body_span_bytes": 582,
  "body_start": "00688fa0",
  "callees": [
    "FUN_006b1f90",
    "FUN_00931fd0",
    "FUN_0069fa60",
    "FUN_00932ae0",
    "FUN_00688f00",
    "FUN_00f47380",
    "FUN_008d9f80",
    "FUN_00579a90",
    "FUN_00429760",
    "memcpy",
    "FUN_00423650",
    "FUN_00926020"
  ],
  "callers": [
    "FUN_00b28ec0",
    "FUN_00bb4ba0",
    "FUN_00580cb0",
    "FUN_00de4850"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00688fa0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "pvStack_18",
      "storage": "Stack[-0x18]:4",
      "type": "void *"
    },
    {
      "name": "iStack_14",
      "storage": "Stack[-0x14]:4",
      "type": "int"
    },
    {
      "name": "uStack_10",
      "storage": "Stack[-0x10]:1",
      "type": "undefined1"
    },
    {
      "name": "pvStack_c",
      "storage": "Stack[-0xc]:4",
      "type": "void *"
    },
    {
      "name": "puStack_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined1 *"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
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
      "name": "uStack_34",
      "storage": "Stack[-0x34]:4",
      "type": "undefined4"
    },
    {
      "name": "iStack_30",
      "storage": "Stack[-0x30]:4",
      "type": "int"
    },
    {
      "name": "iStack_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "int"
    },
    {
      "name": "iVar6",
      "storage": "register:00000018:4",
      "type": "int"
    },
    {
      "name": "_Size",
      "storage": "unique:100000ce:4",
      "type": "size_t"
    },
    {
      "name": "_Src",
      "storage": "unique:10000215:4",
      "type": "void *"
    },
    {
      "name": "piVar1",
      "storage": "register:0000000c:4",
      "type": "int *"
    },
    {
      "name": "uVar2",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "ppvVar3",
      "storage": "register:00000000:4",
      "type": "void * *"
    },
    {
      "name": "iVar4",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "pvVar5",
      "storage": "register:00000014:4",
      "type": "void *"
    },
    {
      "name": "unaff_ESI",
      "storage": "register:00000018:4",
      "type": "int"
    },
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
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
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined4"
    },
    {
      "name": "uStack_44",
      "storage": "Stack[-0x44]:4",
      "type": "undefined4"
    },
    {
      "name": "iStack_40",
      "storage": "Stack[-0x40]:4",
      "type": "int"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 28,
  "mode": "live",
  "name": "FUN_00688fa0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x288fa0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00688fa0(void)",
  "size_bytes": 582,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00688fa0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00b2930b"
    },
    {
      "from": "00bb4cef"
    },
    {
      "from": "00580d08"
    },
    {
      "from": "00de485f"
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
