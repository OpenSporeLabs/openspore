# Evidence 0x00ba8830

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `748b8db3d49084668acc0f843c96bebc94055065f48f758fd1b5112da504f0bb`

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
    "ret_form": "RET 0x4",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +184, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_read_without_deref",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "2def4afe2b3760118597ff29f37cfedb14f7d8d3c35f2f931a51710a00307197",
  "conventions": {
    "ambiguities": [
      "variadic_suspected"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl"
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
        "obs-0107"
      ],
      "claim": "the callee pops 4 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 4,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0007"
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
        "obs-0009",
        "obs-0010",
        "obs-0012",
        "obs-0033",
        "obs-0060",
        "obs-0067",
        "obs-0073",
        "obs-0080",
        "obs-0086",
        "obs-0092",
        "obs-0098"
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
        "obs-0027"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0007"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
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
"\nvoid FUN_00ba8830(int *param_1)\n\n{\n  int iVar1;\n  int iVar2;\n  int *piVar3;\n  char cVar4;\n  undefined **ppuVar5;\n  undefined4 uVar6;\n  int *piVar7;\n  bool bVar8;\n  undefined4 uVar9;\n  cSpaceNames *local_1c [2];\n  int local_14;\n  int iStack_10;\n  int local_c;\n  int *piStack_4;\n  \n  iVar2 = (int)param_1;\n  local_1c[0] = (cSpaceNames *)0x0;\n  cVar4 = FUN_00bb9af0(0x8000);\n  if (cVar4 != '\\0') {\n    *(undefined1 *)(iVar2 + 0xac) = 0;\n  }\n  if (*(char *)(iVar2 + 0xac) == '\\0') {\n    FUN_00bb9b00(0x100,0);\n    local_1c[0] = Simulator__cSpaceNames__Get();\n    param_1 = (int *)0x0;\n    FUN_00ba61b0((uint)*(byte *)(iVar2 + 0xac) * 0x1000000 + *(int *)(iVar2 + 0x70),&param_1);\n    bVar8 = PTR_DAT_0156c63c != PTR_DAT_0156c640;\n    if (bVar8) {\n      ppuVar5 = &PTR_DAT_0156c63c;\n    }\n    else {\n      ppuVar5 = (undefined **)FUN_005ecf80(&local_14,0x7e1310a);\n    }\n    piVar3 = param_1;\n    if (ppuVar5 != (undefined **)(param_1 + 6)) {\n      FUN_00423650(*ppuVar5,ppuVar5[1]);\n    }\n    if (((!bVar8) && (2 < (int)(local_c - local_14 & 0xfffffffeU))) && (local_14 != 0)) {\n      FUN_00f47380(local_14);\n    }\n    piVar3[0xb] = 2;\n    piVar3[10] = 5;\n    uVar9 = 0;\n    piVar3[0x65] = 1;\n    uVar6 = FUN_00989360(0);\n    uVar6 = FUN_00ba8010(&local_14,uVar6);\n    FUN_00b8dde0(uVar6,uVar9);\n    *(undefined1 *)(piVar3 + 0x4c) = 1;\n    piVar7 = (int *)FUN_00f48a80();\n    iVar1 = *piVar7;\n    uVar6 = FUN_00b8d8e0(&local_14);\n    (**(code **)(iVar1 + 8))(uVar6);\n    piVar3[0x2c] = iStack_10;\n    uVar6 = 1;\n    piVar3[0x2d] = local_14;\n    piVar7 = piVar3;\n    FUN_00b3d3d0(piVar3,1);\n    FUN_0103ca40(piVar7,uVar6);\n    *(char *)(iVar2 + 0xac) = *(char *)(iVar2 + 0xac) + '\\x01';\n    piStack_4 = (int *)0x0;\n    (**(code **)(*piVar3 + 4))();\n    FUN_00ba61b0((uint)*(byte *)(iVar2 + 0xac) * 0x1000000 + *(int *)(iVar2 + 0x70),&piStack_4);\n    piVar7 = (int *)FUN_005ecf80(local_1c,0x7e1310a);\n    piVar3 = piStack_4;\n    if (piVar7 != piStack_4 + 6) {\n      FUN_00423650(*piVar7,piVar7[1]);\n    }\n    if ((2 < (int)(local_14 - (int)local_1c[0] & 0xfffffffeU)) &&\n       (local_1c[0] != (cSpaceNames *)0x0)) {\n      FUN_00f47380(local_1c[0]);\n    }\n    piVar3[0xb] = 4;\n    piVar3[10] = 2;\n    piVar3[0x65] = 1;\n    FUN_00ba64a0(piVar3,iVar2,0);\n    *(char *)(iVar2 + 0xac) = *(char *)(iVar2 + 0xac) + '\\x01';\n    piStack_4 = (int *)0x0;\n    (**(code **)(*piVar3 + 4))();\n    FUN_00ba61b0((uint)*(byte *)(iVar2 + 0xac) * 0x1000000 + *(int *)(iVar2 + 0x70),&piStack_4);\n    piVar7 = (int *)FUN_005ecf80(local_1c,0x7e1310a);\n    piVar3 = piStack_4;\n    if (piVar7 != piStack_4 + 6) {\n      FUN_00423650(*piVar7,piVar7[1]);\n    }\n    if ((2 < (int)(local_14 - (int)local_1c[0] & 0xfffffffeU)) &&\n       (local_1c[0] != (cSpaceNames *)0x0)) {\n      FUN_00f47380(local_1c[0]);\n    }\n    piVar3[0xb] = 0;\n    piVar3[10] = 3;\n    piVar3[0x65] = 1;\n    FUN_00ba64a0(piVar3,iVar2,0);\n    FUN_00ba6310(piVar3,0x6334d0ad,0xaf);\n    *(char *)(iVar2 + 0xac) = *(char *)(iVar2 + 0xac) + '\\x01';\n    piStack_4 = (int *)0x0;\n    (**(code **)(*piVar3 + 4))();\n    FUN_00ba61b0((uint)*(byte *)(iVar2 + 0xac) * 0x1000000 + *(int *)(iVar2 + 0x70),&piStack_4);\n    piVar7 = (int *)FUN_005ecf80(local_1c,0x7e1310a);\n    piVar3 = piStack_4;\n    if (piVar7 != piStack_4 + 6) {\n      FUN_00423650(*piVar7,piVar7[1]);\n    }\n    if ((2 < (int)(local_14 - (int)local_1c[0] & 0xfffffffeU)) &&\n       (local_1c[0] != (cSpaceNames *)0x0)) {\n      FUN_00f47380(local_1c[0]);\n    }\n    piVar3[0xb] = 0;\n    piVar3[10] = 2;\n    piVar3[0x65] = 1;\n    FUN_00ba64a0(piVar3,iVar2,0);\n    *(char *)(iVar2 + 0xac) = *(char *)(iVar2 + 0xac) + '\\x01';\n    piStack_4 = (int *)0x0;\n    (**(code **)(*piVar3 + 4))();\n    FUN_00ba61b0((uint)*(byte *)(iVar2 + 0xac) * 0x1000000 + *(int *)(iVar2 + 0x70),&piStack_4);\n    piVar7 = (int *)FUN_005ecf80(local_1c,0x7e1310a);\n    piVar3 = piStack_4;\n    if (piVar7 != piStack_4 + 6) {\n      FUN_00423650(*piVar7,piVar7[1]);\n    }\n    if ((2 < (int)(local_14 - (int)local_1c[0] & 0xfffffffeU)) &&\n       (local_1c[0] != (cSpaceNames *)0x0)) {\n      FUN_00f47380(local_1c[0]);\n    }\n    piVar3[0xb] = 2;\n    piVar3[10] = 1;\n    piVar3[0x65] = 0;\n    FUN_00ba64a0(piVar3,iVar2,0);\n    *(char *)(iVar2 + 0xac) = *(char *)(iVar2 + 0xac) + '\\x01';\n    (**(code **)(*piVar3 + 4))();\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 25591,
  "preview": "{\n  \"count\": 309,\n  \"instructions\": [\n    {\n      \"address\": \"00ba8830\",\n      \"instruction\": \"SUB ESP,0x1c\"\n    },\n    {\n      \"address\": \"00ba8833\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00ba8834\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00ba8835\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00ba8836\",\n      \"instruction\": \"MOV ESI,dword ptr [ESP + 0x2c]\"\n    },\n    {\n      \"address\": \"00ba883a\",\n      \"instruction\": \"MOV EBP,ECX\"\n    },\n    {\n      \"address\": \"00ba883c\",\n      \"instruction\": \"XOR EBX,EBX\"\n    },\n    {\n      \"address\": \"00ba883e\",\n      \"instruction\": \"PUSH 0x8000\"\n    },\n    {\n      \"address\": \"00ba8843\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00ba8845\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x14],EBP\"\n    },\n    {\n      \"address\": \"00ba8849\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x10],EBX\"\n    },\n    {\n      \"address\": \"00ba884d\",\n      \"instruction\": \"CALL 0x00bb9af0\"\n    },\n    {\n      \"address\": \"00ba8852\",\n      \"instruction\": \"TEST AL,AL\"\n    },\n    {\n      \"address\": \"00ba8854\",\n      \"instruction\": \"JZ 0x00ba885c\"\n    },\n    {\n      \"address\": \"00ba8856\",\n      \"instruction\": \"MOV byte ptr [ESI + 0xac],BL\"\n    },\n    {\n      \"address\": \"00ba885c\",\n      \"instruction\": \"CMP byte ptr [ESI + 0xac],BL\"\n    },\n    {\n      \"address\": \"00ba8862\",\n      \"instruction\": \"JNZ 0x00ba8c29\"\n    },\n    {\n      \"address\": \"00ba8868\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00ba8869\",\n      \"instruction\": \"PUSH 0x0\"\n    },\n    {\n      \"address\": \"00ba886b\",\n      \"instruction\": \"PUSH 0x100\"\n    },\n    {\n      \"address\": \"00ba8870\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00ba8872\",\n      \"instruction\": \"CALL 0x00bb9b00\"\n    },\n    {\n      \"address\": \"00ba8877\",\n      \"instruction\": \"CALL 0x004010a0\"\n    },\n    {\n      \"address\": \"00ba887c\",\n      \"instruction\": \"MOVZX ECX,byte ptr [ESI + 0xac]\"\n    },\n    {\n      \"address\": \"00ba8883\",\n      \"instruction\": \"MOV EDI,EAX\"\n    },\n    {\n      \"address\": \"00ba8885\",\n      \"instruction\": \"SHL ECX,0x18\"\n    },\n    {\n      \"address\": \"00ba8888\",\n      \"instruction\": \"ADD ECX,dword ptr [ESI + 0x70]\"\n    },\n    {\n      \"address\": \"00ba888b\",\n      \"instruction\": \"LEA EAX,[ESP + 0x30]\"\n    },\n    {\n      \"address\": \"00ba888f\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00ba8890\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00ba8891\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x18],EDI\"\n    },\n    {\n      \"address\": \"00ba8895\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x38],EBX\"\n    },\n    {\n      \"address\": \"00ba8899\",\n      \"instruction\": \"CALL 0x00ba61b0\"\n    },\n    {\n      \"address\": \"00ba889e\",\n      \"instruction\": \"MOV EDX,dword ptr [0x0156c63c]\"\n    },\n    {\n      \"address\": \"00ba88a4\",\n      \"instruction\": \"ADD ESP,0x8\"\n    },\n    {\n      \"address\": \"00ba88a7\",\n      \"instruction\": \"CMP EDX,dword ptr [0x0156c640]\"\n    },\n    {\n      \"address\": \"00ba88ad\",\n      \"instruction\": \"JNZ 0x00ba88c7\"\n    },\n    {\n      \"address\": \"00ba88af\",\n      \"instruction\": \"PUSH 0x7e1310a\"\n    },\n    {\n      \"address\": \"00ba88b4\",\n      \"instruction\": \"LEA EAX,[ESP + 0x1c]\"\n    },\n    {\n      \"address\": \"00ba88b8\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00ba88b9\",\n      \"instruction\": \"MOV ECX,EDI\"\n    },\n    {\n      \"address\": \"00ba88bb\",\n      \"instruction\": \"MOV EBX,0x1\"\n    },\n    {\n      \"address\": \"00ba88c0\",\n      \"instruction\": \"CALL 0x005ecf80\"\n    },\n    {\n      \"address\": \"00ba88c5\",\n      \"instruction\": \"JMP 0x00ba88cc\"\n    },\n    {\n      \"address\": \"00ba88c7\",\n      \"instruction\": \"MOV EAX,0x156c63c\"\n    },\n    {\n      \"address\": \"00ba88cc\",\n      \"instruction\": \"MOV EDI,dword ptr [ESP + 0x30]\"\n    },\n    {\n      \"address\": \"00ba88d0\",\n      \"instruction\": \"LEA ECX,[EDI + 0x18]\"\n    },\n    {\n      \"address\": \"00ba88d3\",\n      \"instruction\": \"CMP EAX,ECX\"\n    },\n    {\n      \"address\": \"00ba88d5\",\n      \"instruction\": \"JZ 0x00ba88e3\"\n    },\n    {\n      \"address\": \"00ba88d7\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX + 0x4]\"\n    },\n    {\n      \"address\": \"00ba88da\",\n      \"instruction\": \"MOV EAX,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"00ba88dc\",\n      \"instruction\": \"PUSH EDX\"\n    },\n    {\n      \"address\": \"00ba88dd\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00ba88de\",\n      \"instruction\": \"CALL 0x00423650\"\n    },\n    {\n      \"address\": \"00ba88e3\",\n      \"instruction\": \"TEST BL,0x1\"\n    },\n    {\n      \"address\": \"00ba88e6\",\n      \"instruction\": \"JZ 0x00ba8907\"\n    },\n    {\n      \"address\": \"00ba88e8\",\n      \"instruction\": \"MOV ECX,dword ptr [ESP + 0x20]\"\n    },\n    {\n      \"address\": \"00ba88ec\",\n      \"instruction\": \"MOV EAX,dword ptr [ESP + 0x18]\"\n    },\n    {\n      \"address\": \"00ba88f0\",\n      \"instruction\": \"SUB ECX,EAX\"\n    },\n    {\n      \"address\": \"00ba88f2\",\n      \"instruction\": \"AND ECX,0xfffffffe\"\n    },\n    {\n      \"address\": \"00ba88f5\",\n      \"instruction\": \"CMP ECX,0x2\"\n    },\n    {\n      \"address\": \"00ba88f8\",\n      \"instruction\": \"JLE 0x00ba8907\"\n    },\n    {\n      \"address\": \"00ba88fa\",\n     
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
  "body_end": "00ba8c31",
  "body_span_bytes": 1026,
  "body_start": "00ba8830",
  "callees": [
    "Simulator::cSpaceNames::Get",
    "FUN_00b8dde0",
    "FUN_00f48a80",
    "FUN_00ba64a0",
    "FUN_00ba61b0",
    "FUN_00f47380",
    "FUN_00423650",
    "FUN_00b8d8e0",
    "FUN_00989360",
    "FUN_00ba6310",
    "FUN_0103ca40",
    "FUN_005ecf80",
    "FUN_00b3d3d0",
    "FUN_00bb9af0",
    "FUN_00bb9b00",
    "FUN_00ba8010"
  ],
  "callers": [
    "FUN_00bb6700",
    "FUN_00bb7510",
    "FUN_00bb6040",
    "FUN_00bb7620"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ba8830",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar1",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "iVar2",
      "storage": "unique:10000372:4",
      "type": "int"
    },
    {
      "name": "piVar3",
      "storage": "unique:10000376:4",
      "type": "int *"
    },
    {
      "name": "cVar4",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "piStack_4",
      "storage": "Stack[-0x4]:4",
      "type": "int *"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "iStack_10",
      "storage": "Stack[-0x10]:4",
      "type": "int"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "cSpaceNames *[2]"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "int"
    },
    {
      "name": "uVar9",
      "storage": "Stack[-0x30]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "int"
    },
    {
      "name": "ppuVar5",
      "storage": "register:00000000:4",
      "type": "undefined * *"
    },
    {
      "name": "uVar6",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "piVar7",
      "storage": "Stack[-0x3c]:4",
      "type": "int *"
    },
    {
      "name": "bVar8",
      "storage": "register:00000206:1",
      "type": "bool"
    }
  ],
  "locals_count": 15,
  "mode": "live",
  "name": "FUN_00ba8830",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7a8830",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ba8830(void)",
  "size_bytes": 1026,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ba8830",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "00bb62ba"
    },
    {
      "from": "00bb7675"
    },
    {
      "from": "00bb7768"
    },
    {
      "from": "00bb6712"
    },
    {
      "from": "00bb7537"
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
