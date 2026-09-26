# Evidence 0x00bb0e90

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `8a539d2d4e60a67d1cd07a57cfe7c0c12b08bd19575720daddcfd032e018c523`

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
    "ret_form": "RET 0x8",
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +36, so the listing is not one path",
    "unparsed_lines_present: 3 line(s) matched no grammar rule",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "6071d91dc6457e2d0903e183c83ad0d3f9fb7e1347cad429fe70f39db83cb46d",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0086"
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
        "obs-0005"
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
        "obs-0013",
        "obs-0014",
        "obs-0019",
        "obs-0020",
        "obs-0021",
        "obs-0065",
        "obs-0069",
        "obs-0070",
        "obs-0077"
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
        "obs-0013",
        "obs-0014",
        "obs-0019",
        "obs-0020",
        "obs-0021",
        "obs-0065",
        "obs-0069",
        "obs-0070",
        "obs-0077"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0086"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
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
      "id
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
"\nint FUN_00bb0e90(undefined4 param_1,int param_2)\n\n{\n  float fVar1;\n  int iVar2;\n  int *piVar3;\n  bool bVar4;\n  int *piVar5;\n  int *piVar6;\n  char cVar7;\n  float *pfVar8;\n  int *piVar9;\n  float local_38;\n  float local_34;\n  int local_30;\n  float local_2c;\n  float local_28;\n  float local_24;\n  float local_20;\n  float local_1c [2];\n  int *local_14;\n  int *local_10;\n  undefined4 local_c;\n  \n  local_14 = (int *)0x0;\n  local_10 = (int *)0x0;\n  local_c = 0;\n  FUN_00bb0ca0(param_1,1,0,&local_14);\n  fVar1 = *(float *)(param_2 + 0x10);\n  local_34 = fVar1;\n  if (fVar1 <= 0.0) {\n    local_34 = DAT_0156c638 * 1.1;\n  }\n  local_38 = DAT_0156c638 * 0.015625;\n  bVar4 = true;\n  local_24 = DAT_0156c638 * 0.0234375;\n  local_28 = 3.4028235e+38;\n  local_30 = 0;\n  do {\n    piVar6 = local_10;\n    piVar9 = local_14;\n    if (local_14 != local_10) {\n      do {\n        iVar2 = *piVar9;\n        local_2c = 3.4028235e+38;\n        cVar7 = FUN_00ba6bb0(param_1,iVar2,param_2,&local_2c);\n        if ((cVar7 != '\\0') && (local_2c < local_28)) {\n          local_28 = local_2c;\n          local_30 = iVar2;\n        }\n        piVar9 = piVar9 + 1;\n      } while (piVar9 != piVar6);\n      piVar9 = local_14;\n      piVar3 = local_14;\n      if (local_30 != 0) {\njoined_r0x00bb103d:\n        for (; piVar5 = local_14, piVar9 < piVar6; piVar9 = piVar9 + 1) {\n          local_14 = piVar3;\n          if ((int *)*piVar9 != (int *)0x0) {\n            (**(code **)(*(int *)*piVar9 + 4))();\n          }\n          piVar3 = local_14;\n          local_14 = piVar5;\n        }\n        if ((local_14 != (int *)0x0) && (local_14[-1] != 0)) {\n          local_14 = piVar3;\n          FUN_00f47380(piVar5);\n        }\n        return local_30;\n      }\n    }\n    piVar9 = local_14;\n    piVar3 = local_14;\n    if ((fVar1 == 0.0) || (local_34 <= local_38)) goto joined_r0x00bb103d;\n    if (bVar4) {\n      local_38 = local_24 * 2.0;\n      bVar4 = false;\n      local_20 = local_38;\n      pfVar8 = &local_20;\n    }\n    else {\n      local_38 = local_38 + local_24;\n      local_1c[0] = local_38;\n      pfVar8 = local_1c;\n    }\n    if (local_34 <= local_38) {\n      pfVar8 = &local_34;\n    }\n    local_38 = *pfVar8;\n    FUN_00e25bd0(local_14,piVar6);\n    FUN_00bb0d80(param_1,local_38,&local_14);\n  } while( true );\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 139,
  "instructions": [
    {
      "address": "00bb0e90",
      "instruction": "SUB ESP,0x3c"
    },
    {
      "address": "00bb0e93",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bb0e94",
      "instruction": "MOV EBX,dword ptr [ESP + 0x44]"
    },
    {
      "address": "00bb0e98",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00bb0e99",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bb0e9a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bb0e9b",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00bb0e9d",
      "instruction": "LEA EAX,[ESP + 0x38]"
    },
    {
      "address": "00bb0ea1",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb0ea2",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bb0ea3",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00bb0ea5",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bb0ea6",
      "instruction": "MOV dword ptr [ESP + 0x44],ECX"
    },
    {
      "address": "00bb0eaa",
      "instruction": "MOV dword ptr [ESP + 0x48],ESI"
    },
    {
      "address": "00bb0eae",
      "instruction": "MOV dword ptr [ESP + 0x4c],ESI"
    },
    {
      "address": "00bb0eb2",
      "instruction": "MOV dword ptr [ESP + 0x50],ESI"
    },
    {
      "address": "00bb0eb6",
      "instruction": "CALL 0x00bb0ca0"
    },
    {
      "address": "00bb0ebb",
      "instruction": "MOV ECX,dword ptr [ESP + 0x54]"
    },
    {
      "address": "00bb0ebf",
      "instruction": "MOVSS XMM0,dword ptr [ECX + 0x10]"
    },
    {
      "address": "00bb0ec4",
      "instruction": "XORPS XMM3,XMM3"
    },
    {
      "address": "00bb0ec7",
      "instruction": "COMISS XMM0,XMM3"
    },
    {
      "address": "00bb0eca",
      "instruction": "MOVSS XMM1,dword ptr [0x0156c638]"
    },
    {
      "address": "00bb0ed2",
      "instruction": "JBE 0x00bb0ed9"
    },
    {
      "address": "00bb0ed4",
      "instruction": "MOVAPS XMM2,XMM0"
    },
    {
      "address": "00bb0ed7",
      "instruction": "JMP 0x00bb0ee4"
    },
    {
      "address": "00bb0ed9",
      "instruction": "MOVAPS XMM2,XMM1"
    },
    {
      "address": "00bb0edc",
      "instruction": "MULSS XMM2,dword ptr [0x013ef54c]"
    },
    {
      "address": "00bb0ee4",
      "instruction": "UCOMISS XMM0,XMM3"
    },
    {
      "address": "00bb0ee7",
      "instruction": "LAHF"
    },
    {
      "address": "00bb0ee8",
      "instruction": "MOVSS dword ptr [ESP + 0x18],XMM2"
    },
    {
      "address": "00bb0eee",
      "instruction": "MOV byte ptr [ESP + 0x50],0x1"
    },
    {
      "address": "00bb0ef3",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00bb0ef6",
      "instruction": "JP 0x00bb0efd"
    },
    {
      "address": "00bb0ef8",
      "instruction": "MOV byte ptr [ESP + 0x50],0x0"
    },
    {
      "address": "00bb0efd",
      "instruction": "MOVSS XMM3,dword ptr [0x01465eb8]"
    },
    {
      "address": "00bb0f05",
      "instruction": "MOVAPS XMM0,XMM1"
    },
    {
      "address": "00bb0f08",
      "instruction": "MULSS XMM0,dword ptr [0x01466178]"
    },
    {
      "address": "00bb0f10",
      "instruction": "MULSS XMM1,dword ptr [0x0140e968]"
    },
    {
      "address": "00bb0f18",
      "instruction": "MOV byte ptr [ESP + 0x13],0x1"
    },
    {
      "address": "00bb0f1d",
      "instruction": "MOVSS dword ptr [ESP + 0x28],XMM0"
    },
    {
      "address": "00bb0f23",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM1"
    },
    {
      "address": "00bb0f29",
      "instruction": "MOVSS dword ptr [ESP + 0x24],XMM3"
    },
    {
      "address": "00bb0f2f",
      "instruction": "MOV dword ptr [ESP + 0x1c],ESI"
    },
    {
      "address": "00bb0f33",
      "instruction": "MOV EDI,dword ptr [ESP + 0x38]"
    },
    {
      "address": "00bb0f37",
      "instruction": "MOV EBP,dword ptr [ESP + 0x3c]"
    },
    {
      "address": "00bb0f3b",
      "instruction": "MOV ESI,EDI"
    },
    {
      "address": "00bb0f3d",
      "instruction": "CMP EDI,EBP"
    },
    {
      "address": "00bb0f3f",
      "instruction": "JZ 0x00bb0fac"
    },
    {
      "address": "00bb0f41",
      "instruction": "MOV EAX,dword ptr [ESP + 0x54]"
    },
    {
      "address": "00bb0f45",
      "instruction": "MOV EDI,dword ptr [ESI]"
    },
    {
      "address": "00bb0f47",
      "instruction": "MOVSS XMM0,dword ptr [0x01465eb8]"
    },
    {
      "address": "00bb0f4f",
      "instruction": "LEA EDX,[ESP + 0x20]"
    },
    {
      "address": "00bb0f53",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bb0f54",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb0f55",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bb0f56",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bb0f57",
      "instruction": "MOVSS dword ptr [ESP + 0x30],XMM0"
    },
    {
      "address": "00bb0f5d",
      "instruction": "CALL 0x00ba6bb0"
    },
    {
      "address": "00bb0f62",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00bb0f65",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00bb0f67",
      "instruction": "JZ 0x00bb0f84"
    },
    {
      "address": "00bb0f69",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00bb0f6f",
      "instruction": "MOVSS XMM1,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00bb0f75",
      "instruction": "COMISS XMM1,XMM0"
    },
    {
      "address": "00bb0f78",
      "instruction": "JBE 0x00bb0f84"
    },
    {
      "address": "00bb0f7a",
      "instruction": "MOVSS dword ptr [ESP + 0x24],XMM0"
    },
    {
      "address": "00bb0f80",
      "instruction": "MOV dword ptr [ESP + 0x1c],EDI"
    },
    {
      "address": "00bb0f84",
      "instruction": "ADD ESI,0x4"
    },
    {
      "address": "00bb0f87",
      "instruction": "CMP ESI,EBP"
    },
    {
   
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
  "body_end": "00bb1074",
  "body_span_bytes": 485,
  "body_start": "00bb0e90",
  "callees": [
    "FUN_00bb0d80",
    "FUN_00bb0ca0",
    "FUN_00e25bd0",
    "FUN_00f47380",
    "FUN_00ba6bb0"
  ],
  "callers": [
    "FUN_00bb8b20",
    "FUN_00bb28c0",
    "FUN_00bb80f0",
    "FUN_00bb2610",
    "FUN_00c5c470",
    "FUN_00bb2a50",
    "FUN_00bb4f30"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bb0e90",
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
      "type": "float"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "float[2]"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "float"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "float"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "int *"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "int *"
    },
    {
      "name": "pfVar8",
      "storage": "register:00000000:4",
      "type": "float *"
    },
    {
      "name": "cVar7",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "piVar9",
      "storage": "register:00000018:4",
      "type": "int *"
    },
    {
      "name": "bVar4",
      "storage": "unique:100000fc:1",
      "type": "bool"
    },
    {
      "name": "piVar3",
      "storage": "unique:100000ec:4",
      "type": "int *"
    },
    {
      "name": "piVar6",
      "storage": "unique:10000129:4",
      "type": "int *"
    },
    {
      "name": "piVar5",
      "storage": "unique:10000125:4",
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
      "type": "undefined4"
    },
    {
      "name": "iVar2",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "fVar1",
      "storage": "unique:0000a300:4",
      "type": "float"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "int"
    },
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "float"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "float"
    },
    {
      "name": "local_34",
      "storage": "Stack[-0x34]:4",
      "type": "float"
    }
  ],
  "locals_count": 22,
  "mode": "live",
  "name": "FUN_00bb0e90",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7b0e90",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bb0e90(void)",
  "size_bytes": 485,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bb0e90",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 12,
  "xrefs": [
    {
      "from": "00bb9565"
    },
    {
      "from": "00bb2908"
    },
    {
      "from": "00bb2abc"
    },
    {
      "from": "00bb858b"
    },
    {
      "from": "00bb8663"
    },
    {
      "from": "00bb2739"
    },
    {
      "from": "00c5c81d"
    },
    {
      "from": "00c5c83f"
    },
    {
      "from": "01028416"
    },
    {
      "from": "01028abd"
    },
    {
      "from": "01028b24"
    },
    {
      "from": "00bb5023"
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
