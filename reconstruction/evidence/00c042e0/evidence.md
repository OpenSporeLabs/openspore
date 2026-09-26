# Evidence 0x00c042e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `bc0ab75ddcd62c3597f6a709cae7188b1e7d5b0f9eae7591810e144d6e375696`

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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +56, so the listing is not one path"
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
  "content_sha256": "c85da188ae93395f4e4c6e47e485b8543b923a413ba780bf0370c7118316755f",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0032"
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
        "obs-0002",
        "obs-0003",
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          88,
          2848,
          2892,
          2904,
          3756,
          5748
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0009",
        "obs-0032"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0032"
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
        "obs-0032"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00c042e0",
      "count": 36,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c042e1",
      "count": 17,
      "first_use": 1,
      "first_write_index": 8,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c042e1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c042e3",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x58]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c042e6",
      "count": 20,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x14]",
      "reg": "EAX"
    },
    {
      "at": "0x00c042e6",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x14]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c042ee",
      "count": 12,
      "first_use": 6,
      "first_write_index": 3,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00c042ee",
      "base": "EDX",
      "disp": null,
      "id": "obs-0008",
      "index": 6,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00c042f6",
      "definite": true,
      "id": "obs-0009",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c04357",
      "id": "obs-0010",
      "index": 32,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00bcb660",
      "target": "0x00bcb660"
    },
    {
      "at": "0x00c04363",
      "id": "obs-0011",
      "index": 35,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c0b370",
      "target": "0x00c0b370"
    },
    {
      "at": "0x00c0438c",
      "id": "obs-0012",
      "index": 49,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c0b770",
      "target": "0x00c0b770"
    },
    {
      "at": "0x00c043b2",
      "id": "obs-0013",
      "index": 60,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c0b770",
      "target": "0x00c0b770"
    },
    {
      "at": "0x00c043d8",
      "id": "obs-0014",
      "index": 71,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c0b770",
      "target": "0x00c0b770"
    },
    {
      "at": "0x00c043f3",
      "id": "ob
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
"\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nvoid __fastcall FUN_00c042e0(int *param_1)\n\n{\n  char cVar1;\n  int iVar2;\n  int iVar3;\n  uint uVar4;\n  undefined *puVar5;\n  \n  (**(code **)(param_1[0x16] + 0x14))(1);\n  uVar4 = param_1[0x2d6];\n  if ((uVar4 >> 9 & 1) == 0) {\n    if ((uVar4 >> 8 & 1) == 0) {\n      iVar3 = param_1[0x59d];\n      if ((iVar3 == 0) || (*(int *)(iVar3 + 0x15c) != 9)) {\n        if ((uVar4 & 0x4000) != 0) {\n          FUN_00bcb660(&DAT_01590b30);\n          FUN_00c0b370(0x609ea52);\n          goto LAB_00c043f8;\n        }\n        if ((iVar3 == 0) || (iVar3 = *(int *)(iVar3 + 0x15c), iVar3 == 0)) {\n          cVar1 = FUN_00c0b770();\n          if (cVar1 == '\\0') {\n            puVar5 = &DAT_01590778;\n          }\n          else {\n            puVar5 = &DAT_015906f0;\n          }\n        }\n        else if (iVar3 == 1) {\n          puVar5 = &DAT_01590910;\n        }\n        else if (iVar3 == 7) {\n          cVar1 = FUN_00c0b770();\n          if (cVar1 == '\\0') {\n            puVar5 = &DAT_01590a20;\n          }\n          else {\n            puVar5 = &DAT_01590998;\n          }\n        }\n        else if (iVar3 == 0xb) {\n          puVar5 = &DAT_015aa9e8;\n        }\n        else {\n          cVar1 = FUN_00c0b770();\n          if (cVar1 == '\\0') {\n            puVar5 = &DAT_01590778;\n          }\n          else {\n            puVar5 = &DAT_015906f0;\n          }\n        }\n      }\n      else {\n        puVar5 = &DAT_01590aa8;\n      }\n    }\n    else {\n      puVar5 = &DAT_01590888;\n    }\n  }\n  else {\n    param_1[0x3ab] = 2;\n    puVar5 = &DAT_01590800;\n  }\n  FUN_00bcb660(puVar5);\nLAB_00c043f8:\n  if (param_1[0x2c8] != 0) {\n    puVar5 = (undefined *)FUN_00b5b800();\n    *(undefined4 *)(param_1[0x2d3] + 0x5fc) = 0;\n    iVar3 = param_1[0x2d3];\n    cVar1 = FUN_00c0b780();\n    *(uint *)(iVar3 + 0x5fc) = *(uint *)(iVar3 + 0x5fc) | -(uint)(cVar1 != '\\0') & 2;\n    iVar3 = param_1[0x2d3];\n    cVar1 = FUN_00c0b7a0();\n    *(uint *)(iVar3 + 0x5fc) = *(uint *)(iVar3 + 0x5fc) | -(uint)(cVar1 != '\\0') & 4;\n    iVar3 = param_1[0x2d3];\n    cVar1 = FUN_00c0c0e0();\n    *(uint *)(iVar3 + 0x5fc) = *(uint *)(iVar3 + 0x5fc) | -(uint)(cVar1 != '\\0') & 0x80;\n    *(uint *)(param_1[0x2d3] + 0x5fc) =\n         *(uint *)(param_1[0x2d3] + 0x5fc) | (puVar5 != &DAT_01654c01) - 1 & 8;\n    *(uint *)(param_1[0x2d3] + 0x5fc) =\n         *(uint *)(param_1[0x2d3] + 0x5fc) | (puVar5 != &DAT_01654c02) - 1 & 0x8000000;\n    *(uint *)(param_1[0x2d3] + 0x5fc) =\n         *(uint *)(param_1[0x2d3] + 0x5fc) | (puVar5 != &DAT_01654c05) - 1 & 0x400;\n    *(uint *)(param_1[0x2d3] + 0x5fc) =\n         *(uint *)(param_1[0x2d3] + 0x5fc) | (puVar5 != &DAT_01654c04) - 1 & 0x8000;\n    *(uint *)(param_1[0x2d3] + 0x5fc) =\n         *(uint *)(param_1[0x2d3] + 0x5fc) |\n         (-(uint)(*(int *)(param_1[0x2c8] + 0x588) != 1) & 0xffffffc0) + 0x40;\n    if (*(float *)(param_1[0x2c8] + 0x590) <= 0.0) {\n      uVar4 = 0;\n    }\n    else {\n      uVar4 = 0x800;\n    }\n    *(uint *)(param_1[0x2d3] + 0x5fc) = *(uint *)(param_1[0x2d3] + 0x5fc) | uVar4;\n    iVar3 = param_1[0x2d3];\n    Editors__cSpeciesManager__Get();\n    iVar2 = FUN_004df420();\n    *(uint *)(iVar3 + 0x5fc) = *(uint *)(iVar3 + 0x5fc) | (param_1[0x2c8] != iVar2) - 1 & 0x1000;\n  }\n  iVar3 = (**(code **)(*param_1 + 0xd8))();\n  if (4 < iVar3) {\n    *(uint *)(param_1[0x2d3] + 0x5fc) = *(uint *)(param_1[0x2d3] + 0x5fc) | 0x200;\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 14823,
  "preview": "{\n  \"count\": 179,\n  \"instructions\": [\n    {\n      \"address\": \"00c042e0\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00c042e1\",\n      \"instruction\": \"MOV ESI,ECX\"\n    },\n    {\n      \"address\": \"00c042e3\",\n      \"instruction\": \"MOV EAX,dword ptr [ESI + 0x58]\"\n    },\n    {\n      \"address\": \"00c042e6\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX + 0x14]\"\n    },\n    {\n      \"address\": \"00c042e9\",\n      \"instruction\": \"LEA ECX,[ESI + 0x58]\"\n    },\n    {\n      \"address\": \"00c042ec\",\n      \"instruction\": \"PUSH 0x1\"\n    },\n    {\n      \"address\": \"00c042ee\",\n      \"instruction\": \"CALL EDX\"\n    },\n    {\n      \"address\": \"00c042f0\",\n      \"instruction\": \"MOV EAX,dword ptr [ESI + 0xb58]\"\n    },\n    {\n      \"address\": \"00c042f6\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00c042f8\",\n      \"instruction\": \"SHR ECX,0x9\"\n    },\n    {\n      \"address\": \"00c042fb\",\n      \"instruction\": \"TEST CL,0x1\"\n    },\n    {\n      \"address\": \"00c042fe\",\n      \"instruction\": \"JZ 0x00c04314\"\n    },\n    {\n      \"address\": \"00c04300\",\n      \"instruction\": \"MOV dword ptr [ESI + 0xeac],0x2\"\n    },\n    {\n      \"address\": \"00c0430a\",\n      \"instruction\": \"PUSH 0x1590800\"\n    },\n    {\n      \"address\": \"00c0430f\",\n      \"instruction\": \"JMP 0x00c043ed\"\n    },\n    {\n      \"address\": \"00c04314\",\n      \"instruction\": \"MOV EDX,EAX\"\n    },\n    {\n      \"address\": \"00c04316\",\n      \"instruction\": \"SHR EDX,0x8\"\n    },\n    {\n      \"address\": \"00c04319\",\n      \"instruction\": \"TEST DL,0x1\"\n    },\n    {\n      \"address\": \"00c0431c\",\n      \"instruction\": \"JZ 0x00c04328\"\n    },\n    {\n      \"address\": \"00c0431e\",\n      \"instruction\": \"PUSH 0x1590888\"\n    },\n    {\n      \"address\": \"00c04323\",\n      \"instruction\": \"JMP 0x00c043ed\"\n    },\n    {\n      \"address\": \"00c04328\",\n      \"instruction\": \"MOV ECX,dword ptr [ESI + 0x1674]\"\n    },\n    {\n      \"address\": \"00c0432e\",\n      \"instruction\": \"TEST ECX,ECX\"\n    },\n    {\n      \"address\": \"00c04330\",\n      \"instruction\": \"JZ 0x00c04345\"\n    },\n    {\n      \"address\": \"00c04332\",\n      \"instruction\": \"CMP dword ptr [ECX + 0x15c],0x9\"\n    },\n    {\n      \"address\": \"00c04339\",\n      \"instruction\": \"JNZ 0x00c04345\"\n    },\n    {\n      \"address\": \"00c0433b\",\n      \"instruction\": \"PUSH 0x1590aa8\"\n    },\n    {\n      \"address\": \"00c04340\",\n      \"instruction\": \"JMP 0x00c043ed\"\n    },\n    {\n      \"address\": \"00c04345\",\n      \"instruction\": \"TEST EAX,0x4000\"\n    },\n    {\n      \"address\": \"00c0434a\",\n      \"instruction\": \"JZ 0x00c0436d\"\n    },\n    {\n      \"address\": \"00c0434c\",\n      \"instruction\": \"MOV ECX,dword ptr [ESI + 0xb4c]\"\n    },\n    {\n      \"address\": \"00c04352\",\n      \"instruction\": \"PUSH 0x1590b30\"\n    },\n    {\n      \"address\": \"00c04357\",\n      \"instruction\": \"CALL 0x00bcb660\"\n    },\n    {\n      \"address\": \"00c0435c\",\n      \"instruction\": \"PUSH 0x609ea52\"\n    },\n    {\n      \"address\": \"00c04361\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00c04363\",\n      \"instruction\": \"CALL 0x00c0b370\"\n    },\n    {\n      \"address\": \"00c04368\",\n      \"instruction\": \"JMP 0x00c043f8\"\n    },\n    {\n      \"address\": \"00c0436d\",\n      \"instruction\": \"TEST ECX,ECX\"\n    },\n    {\n      \"address\": \"00c0436f\",\n      \"instruction\": \"JZ 0x00c043d6\"\n    },\n    {\n      \"address\": \"00c04371\",\n      \"instruction\": \"MOV EAX,dword ptr [ECX + 0x15c]\"\n    },\n    {\n      \"address\": \"00c04377\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"00c04379\",\n      \"instruction\": \"JZ 0x00c043d6\"\n    },\n    {\n      \"address\": \"00c0437b\",\n      \"instruction\": \"SUB EAX,0x1\"\n    },\n    {\n      \"address\": \"00c0437e\",\n      \"instruction\": \"JZ 0x00c043cf\"\n    },\n    {\n      \"address\": \"00c04380\",\n      \"instruction\": \"SUB EAX,0x6\"\n    },\n    {\n      \"address\": \"00c04383\",\n      \"instruction\": \"JZ 0x00c043b0\"\n    },\n    {\n      \"address\": \"00c04385\",\n      \"instruction\": \"SUB EAX,0x4\"\n    },\n    {\n      \"address\": \"00c04388\",\n      \"instruction\": \"JZ 0x00c043a9\"\n    },\n    {\n      \"address\": \"00c0438a\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00c0438c\",\n      \"instruction\": \"CALL 0x00c0b770\"\n    },\n    {\n      \"address\": \"00c04391\",\n      \"instruction\": \"MOV ECX,dword ptr [ESI + 0xb4c]\"\n    },\n    {\n      \"address\": \"00c04397\",\n      \"instruction\": \"TEST AL,AL\"\n    },\n    {\n      \"address\": \"00c04399\",\n      \"instruction\": \"JZ 0x00c043a2\"\n    },\n    {\n      \"address\": \"00c0439b\",\n      \"instruction\": \"PUSH 0x15906f0\"\n    },\n    {\n      \"address\": \"00c043a0\",\n      \"instruction\": \"JMP 0x00c043f3\"\n    },\n    {\n      \"address\": \"00c043a2\",\n      \"instruction\": \"PUSH 0x1590778\"\n    },\n    {\n      \"address\": \"00c043a7\",\n      \"instruction\": \"JMP 0x00c043f3\"\n    },\n    {\n      \"address\": \"00c043a9\",\n      \"instruction\": \"PUSH 0x15aa9e8\"\n    },\n    {\n      \"address\": \"00c043ae\",\n      \"instruction\": \"JMP 0x00c043ed\"\n    },\n    {\n      \"address\": \"00c043b0\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00c043b2\",\n      \"instruction\": \"CALL 0x00c0b770\"\n    },\n    {\n      \"address\": \"00c043b7\",\n      \"instruction\": \"MOV ECX,dword ptr [ESI + 0xb4c]\"\n    },\n    {\n      \"address\": \"00c043bd\",\n      \"instruction\": \"TEST AL,AL\"\n    },\n    {\n      \"ad
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
  "body_end": "00c04589",
  "body_span_bytes": 682,
  "body_start": "00c042e0",
  "callees": [
    "FUN_00c0c0e0",
    "FUN_00c0b7a0",
    "FUN_004df420",
    "FUN_00c0b770",
    "FUN_00b5b800",
    "Editors::cSpeciesManager::Get",
    "FUN_00bcb660",
    "FUN_00c0b370",
    "FUN_00c0b780"
  ],
  "callers": [
    "FUN_00c09fa0",
    "FUN_00c04dd0",
    "FUN_00d53490",
    "FUN_00c04e50",
    "FUN_00d43e30",
    "FUN_01016070",
    "FUN_00c099e0",
    "FUN_00c05d40",
    "FUN_00db5e80"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c042e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "puVar5",
      "storage": "Stack[-0xc]:4",
      "type": "undefined *"
    },
    {
      "name": "uVar4",
      "storage": "register:00000004:4",
      "type": "uint"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int *"
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "FUN_00c042e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8042e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c042e0(void)",
  "size_bytes": 682,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c042e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 11,
  "xrefs": [
    {
      "from": "00c0aa87"
    },
    {
      "from": "00c09f42"
    },
    {
      "from": "00c04e30"
    },
    {
      "from": "00c05dcd"
    },
    {
      "from": "00d53581"
    },
    {
      "from": "00db5fcf"
    },
    {
      "from": "01016271"
    },
    {
      "from": "00c04f70"
    },
    {
      "from": "00d44737"
    },
    {
      "from": "00cdf704"
    },
    {
      "from": "00d53830"
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
