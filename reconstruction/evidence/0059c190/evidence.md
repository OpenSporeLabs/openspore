# Evidence 0x0059c190

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `76f6b4bc5e4a877aca807673530e50f571276cf9db592f0c75f6e9554800a7ff`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__cdecl",
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
    "receiver": false,
    "ret_form": "RET",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "dbc4dd9327c9fd09f4ce588240f07244dc80f6c628e3ecfd60a73c3cc2353ffd",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__cdecl",
    "candidate_conventions": [
      "__cdecl",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0050"
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
        "obs-0005",
        "obs-0026",
        "obs-0033",
        "obs-0034",
        "obs-0040"
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
        "obs-0050"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0026",
        "obs-0033",
        "obs-0034",
        "obs-0040",
        "obs-0050"
      ],
      "claim": "calling convention is __cdecl: the caller cleans the stack and at least one entry slot is read",
      "confidence": "INFERRED",
      "id": "C9",
      "value": "__cdecl"
    },
    {
      "based_on": [
        "obs-0050"
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
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x0059c190",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x30",
      "sub": 48
    },
    {
      "at": "0x0059c190",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x30",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0059c193",
      "count": 3,
      "first_use": 1,
      "first_write_index": 57,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0059c194",
      "count": 23,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x3c]",
      "reg": "ESP"
    },
    {
      "at": "0x0059c194",
      "base": "ESP",
      "disp": 60,
      "id": "obs-0005",
      "index": 2,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x3c]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0059c194",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x3c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0059c198",
      "count": 6,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOVSS XMM0,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x0059c198",
      "d
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059d610"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005b1e30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005d8f10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x009c6fc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ad12a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae46f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b02fa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b134a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b3f3a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b421b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b45ca0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b81780"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b81a40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b94150"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b998a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba0080"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nundefined4 QuaternionToMatrix(undefined4 param_1,float *param_2)\n\n{\n  float fVar1;\n  float fVar2;\n  float fVar3;\n  float fVar4;\n  float local_24;\n  float local_20;\n  float local_1c;\n  float local_18;\n  float local_14;\n  float local_10;\n  float local_c;\n  float local_8;\n  float local_4;\n  \n  fVar1 = *param_2;\n  fVar2 = param_2[1];\n  fVar3 = param_2[2];\n  fVar4 = param_2[3];\n  local_24 = 1.0 - (fVar3 * fVar3 + fVar2 * fVar2) * 2.0;\n  local_20 = (fVar4 * fVar3 + fVar2 * fVar1) * 2.0;\n  local_1c = (fVar3 * fVar1 - fVar4 * fVar2) * 2.0;\n  local_18 = (fVar2 * fVar1 - fVar4 * fVar3) * 2.0;\n  local_14 = 1.0 - (fVar3 * fVar3 + fVar1 * fVar1) * 2.0;\n  local_10 = (fVar4 * fVar1 + fVar3 * fVar2) * 2.0;\n  local_c = (fVar4 * fVar2 + fVar3 * fVar1) * 2.0;\n  local_8 = (fVar3 * fVar2 - fVar4 * fVar1) * 2.0;\n  local_4 = 1.0 - (fVar2 * fVar2 + fVar1 * fVar1) * 2.0;\n  FUN_0041cb40(&local_24);\n  return param_1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 79,
  "instructions": [
    {
      "address": "0059c190",
      "instruction": "SUB ESP,0x30"
    },
    {
      "address": "0059c193",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0059c194",
      "instruction": "MOV EAX,dword ptr [ESP + 0x3c]"
    },
    {
      "address": "0059c198",
      "instruction": "MOVSS XMM0,dword ptr [EAX]"
    },
    {
      "address": "0059c19c",
      "instruction": "MOVSS XMM6,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0059c1a1",
      "instruction": "MOVSS XMM7,dword ptr [EAX + 0x8]"
    },
    {
      "address": "0059c1a6",
      "instruction": "MOVSS XMM5,dword ptr [EAX + 0xc]"
    },
    {
      "address": "0059c1ab",
      "instruction": "MOVAPS XMM4,XMM7"
    },
    {
      "address": "0059c1ae",
      "instruction": "MOVAPS XMM2,XMM7"
    },
    {
      "address": "0059c1b1",
      "instruction": "MULSS XMM2,XMM7"
    },
    {
      "address": "0059c1b5",
      "instruction": "MULSS XMM4,XMM0"
    },
    {
      "address": "0059c1b9",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM5"
    },
    {
      "address": "0059c1bf",
      "instruction": "MULSS XMM5,XMM0"
    },
    {
      "address": "0059c1c3",
      "instruction": "MOVAPS XMM3,XMM6"
    },
    {
      "address": "0059c1c6",
      "instruction": "MULSS XMM3,XMM0"
    },
    {
      "address": "0059c1ca",
      "instruction": "MOVAPS XMM1,XMM0"
    },
    {
      "address": "0059c1cd",
      "instruction": "MULSS XMM1,XMM0"
    },
    {
      "address": "0059c1d1",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x4]"
    },
    {
      "address": "0059c1d7",
      "instruction": "MOVSS dword ptr [ESP + 0x3c],XMM4"
    },
    {
      "address": "0059c1dd",
      "instruction": "MOVAPS XMM4,XMM7"
    },
    {
      "address": "0059c1e0",
      "instruction": "MULSS XMM4,XMM6"
    },
    {
      "address": "0059c1e4",
      "instruction": "MOVSS dword ptr [ESP + 0x8],XMM1"
    },
    {
      "address": "0059c1ea",
      "instruction": "MOVAPS XMM1,XMM6"
    },
    {
      "address": "0059c1ed",
      "instruction": "MULSS XMM1,XMM6"
    },
    {
      "address": "0059c1f1",
      "instruction": "MOVSS dword ptr [ESP + 0xc],XMM5"
    },
    {
      "address": "0059c1f7",
      "instruction": "MOVAPS XMM5,XMM0"
    },
    {
      "address": "0059c1fa",
      "instruction": "MULSS XMM0,XMM7"
    },
    {
      "address": "0059c1fe",
      "instruction": "MOVSS XMM7,dword ptr [0x01485720]"
    },
    {
      "address": "0059c206",
      "instruction": "MULSS XMM5,XMM6"
    },
    {
      "address": "0059c20a",
      "instruction": "MOVAPS XMM6,XMM2"
    },
    {
      "address": "0059c20d",
      "instruction": "ADDSS XMM6,XMM1"
    },
    {
      "address": "0059c211",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "0059c217",
      "instruction": "MOVSS XMM0,dword ptr [0x01470f1c]"
    },
    {
      "address": "0059c21f",
      "instruction": "MULSS XMM6,XMM0"
    },
    {
      "address": "0059c223",
      "instruction": "SUBSS XMM7,XMM6"
    },
    {
      "address": "0059c227",
      "instruction": "MOVSS XMM6,dword ptr [ESP + 0x4]"
    },
    {
      "address": "0059c22d",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM7"
    },
    {
      "address": "0059c233",
      "instruction": "MOVAPS XMM7,XMM6"
    },
    {
      "address": "0059c236",
      "instruction": "ADDSS XMM7,XMM3"
    },
    {
      "address": "0059c23a",
      "instruction": "MULSS XMM7,XMM0"
    },
    {
      "address": "0059c23e",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM7"
    },
    {
      "address": "0059c244",
      "instruction": "MOVSS XMM7,dword ptr [ESP + 0x3c]"
    },
    {
      "address": "0059c24a",
      "instruction": "SUBSS XMM7,XMM5"
    },
    {
      "address": "0059c24e",
      "instruction": "ADDSS XMM5,dword ptr [ESP + 0x3c]"
    },
    {
      "address": "0059c254",
      "instruction": "MULSS XMM7,XMM0"
    },
    {
      "address": "0059c258",
      "instruction": "SUBSS XMM3,XMM6"
    },
    {
      "address": "0059c25c",
      "instruction": "MOVSS XMM6,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0059c262",
      "instruction": "MOVSS dword ptr [ESP + 0x18],XMM7"
    },
    {
      "address": "0059c268",
      "instruction": "MULSS XMM3,XMM0"
    },
    {
      "address": "0059c26c",
      "instruction": "MOVSS dword ptr [ESP + 0x1c],XMM3"
    },
    {
      "address": "0059c272",
      "instruction": "MOVSS XMM3,dword ptr [0x01485720]"
    },
    {
      "address": "0059c27a",
      "instruction": "ADDSS XMM2,XMM6"
    },
    {
      "address": "0059c27e",
      "instruction": "MULSS XMM2,XMM0"
    },
    {
      "address": "0059c282",
      "instruction": "MOVAPS XMM7,XMM3"
    },
    {
      "address": "0059c285",
      "instruction": "SUBSS XMM7,XMM2"
    },
    {
      "address": "0059c289",
      "instruction": "MOVSS XMM2,dword ptr [ESP + 0xc]"
    },
    {
      "address": "0059c28f",
      "instruction": "MOVSS dword ptr [ESP + 0x20],XMM7"
    },
    {
      "address": "0059c295",
      "instruction": "MOV ESI,dword ptr [ESP + 0x38]"
    },
    {
      "address": "0059c299",
      "instruction": "MOVAPS XMM7,XMM2"
    },
    {
      "address": "0059c29c",
      "instruction": "ADDSS XMM7,XMM4"
    },
    {
      "address": "0059c2a0",
      "instruction": "ADDSS XMM1,XMM6"
    },
    {
      "address": "0059c2a4",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "0059c2a8",
      "instruction": "SUBSS XMM4,XMM2"
    },
    {
      "address": "0059c2ac",
      "instruction": "MULSS XMM1,XMM0"
    },
    {
      "address": "0059c2b0",
      "instruction": "MULSS XMM7,XMM0"
    },
    {
      "address": "0059c2b4",
      "instruction": "MULSS XMM5,XMM0"
    },
    {
      "address": "0059c2b8",
      "instruction": "MULSS XMM4,XMM0"
    },
    {
      "address": "0059c2bc",
      "instruction": "SUBSS XMM3,XMM1"
    },
    {
      "address": 
[TRUNCATED]
```

## external_callees

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 12295,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00ff3f00\",\n      \"va\": \"0x00ff3f00\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-C4-CREATURE-WAVE3\",\n      \"score\": 3,\n      \"symbol\": \"Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460\",\n      \"va\": \"0x00c1d460\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"gameglobal-misc\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d610\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005b1e30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005d8f10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x009c6fc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad12a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae46f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b02fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b134a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b3f3a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b421b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b45ca0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b81780\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b81a40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b94150\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b998a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba0080\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bc2900\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd0390\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd2af0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdc050\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdc350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00beabb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00becb10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c050b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c11690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c11920\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c14f70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c163f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c1d120\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c1d290\"\n      },\n      {\n        \"name\": \"Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460\",\n        \"reconstructed\": true,\n        \"va\": \"0x00c1d460\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c36300\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c3ff10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c71bf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c84950\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c897e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8a550\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8aa60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8ae20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c91700\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c93000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c9b740\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c9dd50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cbf120\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cc3f40\"\n      },\n      {\n        \"name\"
[TRUNCATED]
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "0059c2e6",
  "body_span_bytes": 343,
  "body_start": "0059c190",
  "callees": [
    "FUN_0041cb40"
  ],
  "callers": [
    "FUN_00d3d4f0",
    "FUN_00ae46f0",
    "FUN_00ebc2f0",
    "FUN_00f22070",
    "FUN_00ffe3d0",
    "FUN_00c11920",
    "FUN_00b45ca0",
    "FUN_00ebd420",
    "FUN_005b1e30",
    "FUN_00b998a0",
    "FUN_01021740",
    "FUN_00d0ba80",
    "FUN_00c1d120",
    "FUN_00e5e850",
    "FUN_00d342d0",
    "FUN_010543e0",
    "FUN_00fbad70",
    "FUN_00d9aa20",
    "FUN_00ee9350",
    "FUN_00f9d080",
    "FUN_00b81a40",
    "FUN_00f3c870",
    "FUN_00b94150",
    "FUN_00f38330",
    "FUN_00ebe3e0",
    "FUN_00f523a0",
    "FUN_00d0bbd0",
    "FUN_00e97bf0",
    "FUN_00db33d0",
    "FUN_00e89060",
    "FUN_00d124e0",
    "FUN_00d30fb0",
    "FUN_00c9b740",
    "FUN_00c93000",
    "FUN_00cbf120",
    "FUN_00fffdd0",
    "FUN_00f373a0",
    "FUN_00beabb0",
    "FUN_00d8d300",
    "FUN_00ed59e0",
    "FUN_00c9dd50",
    "FUN_00d26c90",
    "FUN_00f36450",
    "Simulator::cPlanetModel::ToSurface",
    "FUN_00c8ae20",
    "FUN_00b3f3a0",
    "FUN_00e893a0",
    "FUN_00d3aa70",
    "FUN_00e8e420",
    "FUN_00c163f0",
    "FUN_00cdcf70",
    "FUN_00c14f70",
    "FUN_00d40230",
    "FUN_00e934f0",
    "FUN_00e911f0",
    "FUN_01043770",
    "FUN_00e953a0",
    "FUN_00c3ff10",
    "FUN_00c1d290",
    "FUN_00c1d460",
    "FUN_00bd0390",
    "FUN_00ad12a0",
    "FUN_00cea6f0",
    "Simulator::Cell::CreateCellObject",
    "FUN_00b134a0",
    "FUN_00b421b0",
    "FUN_00ba0080",
    "FUN_00e92ca0",
    "FUN_00b02fa0",
    "FUN_00f372b0",
    "FUN_00e9a470",
    "FUN_00e99280",
    "FUN_00e9b2b0",
    "FUN_00c71bf0",
    "FUN_00bdc350",
    "FUN_009c6fc0",
    "FUN_01000000",
    "FUN_00c8a550",
    "FUN_00e84150",
    "FUN_00f0dc10",
    "FUN_00bc2900",
    "FUN_00c897e0",
    "FUN_00c050b0",
    "FUN_00d46c30",
    "FUN_00db4a60",
    "FUN_00cea1a0",
    "FUN_00ebdc20",
    "FUN_00d39dc0",
    "FUN_00e9bb40",
    "FUN_00c91700",
    "FUN_00f9cc50",
    "FUN_00bdc050",
    "FUN_00bd2af0",
    "FUN_00c11690",
    "FUN_00e93f50",
    "FUN_00c8aa60",
    "FUN_00ebbfb0",
    "FUN_00becb10",
    "FUN_005d8f10",
    "FUN_00cdd9c0",
    "FUN_00e0e0e0",
    "FUN_00c36300",
    "FUN_00e8c120",
    "FUN_00db86a0",
    "FUN_0059d610",
    "FUN_00ebcc80",
    "FUN_00f9c960",
    "FUN_00c84950",
    "FUN_00d50040",
    "FUN_00ff65f0",
    "FUN_0104ea80",
    "FUN_00cc3f40",
    "FUN_00e76d70"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0059c190",
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
      "type": "float"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "float"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "float *"
    },
    {
      "name": "fVar1",
      "storage": "unique:0000a300:4",
      "type": "float"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "float"
    },
    {
      "name": "fVar2",
      "storage": "unique:0000a300:4",
      "type": "float"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "float"
    },
    {
      "name": "fVar3",
      "storage": "unique:0000a300:4",
      "type": "float"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "float"
    },
    {
      "name": "fVar4",
      "storage": "unique:0000a300:4",
      "type": "float"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "float"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "float"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "float"
    }
  ],
  "locals_count": 15,
  "mode": "live",
  "name": "QuaternionToMatrix",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x19c190",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined QuaternionToMatrix(void)",
  "size_bytes": 343,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0059c190",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00b3f40a"
    },
    {
      "from": "00c89861"
    },
    {
      "from": "00c8afe7"
    },
    {
      "from": "00f9c96e"
    },
    {
      "from": "00f9cc68"
    },
    {
      "from": "00f9d09b"
    },
    {
      "from": "009c7ad2"
    },
    {
      "from": "0059d791"
    },
    {
      "from": "005b1f6e"
    },
    {
      "from": "005d90cb"
    },
    {
      "from": "00bc296a"
    },
    {
      "from": "00b81904"
    },
    {
      "from": "00ad1b6c"
    },
    {
      "from": "00c15023"
    },
    {
      "from": "00ae47bc"
    },
    {
      "from": "00beaf3a"
    },
    {
      "from": "010001dc"
    },
    {
      "from": "00fffeed"
    },
    {
      "from": "0104ebfc"
    },
    {
      "from": "00e92efd"
    },
    {
      "from": "00c8ac11"
    },
    {
      "from": "00b1360e"
    },
    {
      "from": "010217f6"
[TRUNCATED]
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [],
  "handoffs": [],
  "metadata": []
}
```

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocking_reason": null,
  "gates": [],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

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
