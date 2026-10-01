# Evidence 0x00e3a400

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f5d3cf5959ff0de2bf6a93e97691d501f5fd3d756feb12886e385e5ffeb8118c`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_note": "(declared) against unclassified_in_EAX (record)",
  "return_register": "EAX",
  "return_type": "Word",
  "saved_registers": [
    "none -- the body never pushes a register, so it has no frame and saves nothing"
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x8"
}
```

## abi_derived

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
  "abstained_because": [],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "7b48565f43e1cc4a9888ff5712ec40ab34fa7ee99f6920bae97b097fdd73c858",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0012",
        "obs-0014",
        "obs-0015",
        "obs-0016",
        "obs-0018",
        "obs-0019",
        "obs-0021",
        "obs-0023",
        "obs-0025",
        "obs-0027",
        "obs-0030",
        "obs-0032",
        "obs-0035"
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
        "obs-0002",
        "obs-0004",
        "obs-0013",
        "obs-0017",
        "obs-0020",
        "obs-0022",
        "obs-0024",
        "obs-0026",
        "obs-0028",
        "obs-0031",
        "obs-0033"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          804
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0012",
        "obs-0014",
        "obs-0015",
        "obs-0016",
        "obs-0018",
        "obs-0019",
        "obs-0021",
        "obs-0023",
        "obs-0025",
        "obs-0027",
        "obs-0030",
        "obs-0032",
        "obs-0035"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0012",
        "obs-0014",
        "obs-0015",
        "obs-0016",
        "obs-0018",
        "obs-0019",
        "obs-0021",
        "obs-0023",
        "obs-0025",
        "obs-0027",
        "obs-0030",
        "obs-0032",
        "obs-0035"
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
        "obs-0012",
        "obs-0014",
        "obs-0015",
        "obs-0016",
        "obs-0018",
        "obs-0019",
        "obs-0021",
        "obs-0023",
        "obs-0025",
        "obs-0027",
        "obs-0030",
        "obs-0032",
        "obs-0035"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0012",
        "obs-0014",
        "obs-0015",
        "obs-0016",
        "obs-0018",
        "obs-0019",
        "obs-0021",
        "obs-0023",
        "obs-0025",
        "obs-0027",
        "obs-0030",
        "obs-0032",
        "obs-0035"
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
      "at": "0x00e3a270",
      "count": 11,
      "first_use": 0,
      "first_write_index": 25,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00e3a270",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "in
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
"\nvoid __thiscall FUN_00e3a270(int param_1,int param_2,int param_3)\n\n{\n  undefined4 uVar1;\n  \n  if (param_2 < -0xd876cb5) {\n    if (param_2 != -0xd876cb6) {\n      if (param_2 < -0x55095553) {\n        if (param_2 == -0x55095554) {\nLAB_00e3a2c0:\n          *(undefined4 *)(param_1 + 0x324) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 8);\n          FUN_00e39420(param_3,3,param_1 + 0x2c0);\n          return;\n        }\n        if (param_2 < -0x6086d4b3) {\n          if (param_2 == -0x6086d4b4) {\n            if (*(int *)(param_1 + 0x32c) == -1) {\n              *(undefined **)(param_1 + 0x32c) = &DAT_01654c05;\n            }\n            uVar1 = *(undefined4 *)(*(int *)(param_3 + 0xc) + 8);\n            *(undefined4 *)(param_1 + 0x328) = uVar1;\n            if (*(int *)(param_1 + 0x324) != 0) {\n              return;\n            }\n            *(undefined4 *)(param_1 + 0x324) = uVar1;\n            return;\n          }\n          if (param_2 == -0x7ecc04d2) goto LAB_00e3a4e4;\n          if (param_2 != -0x67f1bc0e) {\n            if (param_2 != -0x660f2e26) {\n              return;\n            }\n            goto LAB_00e3a2c0;\n          }\n        }\n        else if ((param_2 != -0x5f68cc8c) && (param_2 != -0x5934b361)) {\n          return;\n        }\n      }\n      else if (param_2 < -0x27cd4fa6) {\n        if (param_2 != -0x27cd4fa7) {\n          if (param_2 == -0x52189332) {\n            if (*(int *)(param_1 + 0x32c) == -1) {\n              *(undefined **)(param_1 + 0x32c) = &DAT_01654c01;\n            }\n            *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 8);\n            return;\n          }\n          if ((param_2 != -0x324c9691) && (param_2 != -0x2ac936e3)) {\n            return;\n          }\n        }\n      }\n      else {\n        if (param_2 == -0x23568930) goto LAB_00e3a2c0;\n        if (param_2 != -0x1f4362bb) {\n          return;\n        }\n      }\nLAB_00e3a517:\n      if (param_3 == 0) {\n        return;\n      }\n      *(undefined4 *)(param_1 + 0x2d0) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 0xc);\n      *(undefined4 *)(param_1 + 0x2cc) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 0x10);\n      *(undefined4 *)(param_1 + 0x2d4) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 0x14);\n      return;\n    }\n  }\n  else {\n    if (0x3e2a3040 < param_2) {\n      if (param_2 < 0x6cd9ec7c) {\n        if (param_2 != 0x6cd9ec7b) {\n          if (param_2 == 0x5c51063f) goto LAB_00e3a3e2;\n          if (param_2 != 0x5fcf28d0) {\n            if (param_2 != 0x6a9f2620) {\n              return;\n            }\n            goto LAB_00e3a4e4;\n          }\n        }\n      }\n      else {\n        if (param_2 == 0x7115ede5) {\nLAB_00e3a546:\n          *(undefined4 *)(param_1 + 0x30c) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 8);\n          FUN_00e39420(param_3,3,param_1 + 0x29c);\n          return;\n        }\n        if (param_2 != 0x7bceaa86) {\n          return;\n        }\n      }\n      goto LAB_00e3a517;\n    }\n    if (param_2 == 0x3e2a3040) {\n      *(undefined **)(param_1 + 0x32c) = &DAT_01654c00;\n      *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 8);\n      return;\n    }\n    if (0x279c4e55 < param_2) {\n      if (param_2 != 0x2cfa39dd) {\n        if (param_2 != 0x3b38f92a) {\n          return;\n        }\n        if (*(int *)(param_1 + 0x32c) == -1) {\n          *(undefined **)(param_1 + 0x32c) = &DAT_01654c04;\n        }\n        uVar1 = *(undefined4 *)(*(int *)(param_3 + 0xc) + 8);\n        *(undefined4 *)(param_1 + 800) = uVar1;\n        if (*(int *)(param_1 + 0x31c) != 0) {\n          return;\n        }\n        *(undefined4 *)(param_1 + 0x31c) = uVar1;\n        return;\n      }\nLAB_00e3a4e4:\n      *(undefined4 *)(param_1 + 0x31c) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 8);\n      FUN_00e39420(param_3,3,param_1 + 0x2b4);\n      return;\n    }\n    if (param_2 == 0x279c4e55) {\n      if (*(int *)(param_1 + 0x32c) == -1) {\n        *(undefined **)(param_1 + 0x32c) = &DAT_01654c02;\n      }\n      uVar1 = *(undefined4 *)(*(int *)(param_3 + 0xc) + 8);\n      *(undefined4 *)(param_1 + 0x318) = uVar1;\n      if (*(int *)(param_1 + 0x314) != 0) {\n        return;\n      }\n      *(undefined4 *)(param_1 + 0x314) = uVar1;\n      return;\n    }\n    if ((param_2 == -0x6987d84) || (param_2 == 0x13df9c1c)) goto LAB_00e3a546;\n    if (param_2 != 0x25ca9233) {\n      return;\n    }\n  }\nLAB_00e3a3e2:\n  *(undefined4 *)(param_1 + 0x314) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 8);\n  *(undefined4 *)(param_1 + 0x2ac) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 0xc);\n  *(undefined4 *)(param_1 + 0x2a8) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 0x10);\n  *(undefined4 *)(param_1 + 0x2b0) = *(undefined4 *)(*(int *)(param_3 + 0xc) + 0x14);\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 172,
  "instructions": [
    {
      "address": "00e3a270",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00e3a274",
      "instruction": "CMP EAX,0xf278934a"
    },
    {
      "address": "00e3a279",
      "instruction": "JG 0x00e3a3a3"
    },
    {
      "address": "00e3a27f",
      "instruction": "JZ 0x00e3a3e2"
    },
    {
      "address": "00e3a285",
      "instruction": "CMP EAX,0xaaf6aaac"
    },
    {
      "address": "00e3a28a",
      "instruction": "JG 0x00e3a337"
    },
    {
      "address": "00e3a290",
      "instruction": "JZ 0x00e3a2c0"
    },
    {
      "address": "00e3a292",
      "instruction": "CMP EAX,0x9f792b4c"
    },
    {
      "address": "00e3a297",
      "instruction": "JG 0x00e3a31e"
    },
    {
      "address": "00e3a29d",
      "instruction": "JZ 0x00e3a2e5"
    },
    {
      "address": "00e3a29f",
      "instruction": "CMP EAX,0x8133fb2e"
    },
    {
      "address": "00e3a2a4",
      "instruction": "JZ 0x00e3a4e4"
    },
    {
      "address": "00e3a2aa",
      "instruction": "CMP EAX,0x980e43f2"
    },
    {
      "address": "00e3a2af",
      "instruction": "JZ 0x00e3a517"
    },
    {
      "address": "00e3a2b5",
      "instruction": "CMP EAX,0x99f0d1da"
    },
    {
      "address": "00e3a2ba",
      "instruction": "JNZ 0x00e3a568"
    },
    {
      "address": "00e3a2c0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00e3a2c4",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00e3a2c7",
      "instruction": "MOV EDX,dword ptr [EDX + 0x8]"
    },
    {
      "address": "00e3a2ca",
      "instruction": "MOV dword ptr [ECX + 0x324],EDX"
    },
    {
      "address": "00e3a2d0",
      "instruction": "ADD ECX,0x2c0"
    },
    {
      "address": "00e3a2d6",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e3a2d7",
      "instruction": "PUSH 0x3"
    },
    {
      "address": "00e3a2d9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e3a2da",
      "instruction": "CALL 0x00e39420"
    },
    {
      "address": "00e3a2df",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00e3a2e2",
      "instruction": "RET 0x8"
    },
    {
      "address": "00e3a2e5",
      "instruction": "CMP dword ptr [ECX + 0x32c],-0x1"
    },
    {
      "address": "00e3a2ec",
      "instruction": "JNZ 0x00e3a2f8"
    },
    {
      "address": "00e3a2ee",
      "instruction": "MOV dword ptr [ECX + 0x32c],0x1654c05"
    },
    {
      "address": "00e3a2f8",
      "instruction": "CMP dword ptr [ECX + 0x324],0x0"
    },
    {
      "address": "00e3a2ff",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00e3a303",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00e3a306",
      "instruction": "MOV EAX,dword ptr [EDX + 0x8]"
    },
    {
      "address": "00e3a309",
      "instruction": "MOV dword ptr [ECX + 0x328],EAX"
    },
    {
      "address": "00e3a30f",
      "instruction": "JNZ 0x00e3a568"
    },
    {
      "address": "00e3a315",
      "instruction": "MOV dword ptr [ECX + 0x324],EAX"
    },
    {
      "address": "00e3a31b",
      "instruction": "RET 0x8"
    },
    {
      "address": "00e3a31e",
      "instruction": "CMP EAX,0xa0973374"
    },
    {
      "address": "00e3a323",
      "instruction": "JZ 0x00e3a517"
    },
    {
      "address": "00e3a329",
      "instruction": "CMP EAX,0xa6cb4c9f"
    },
    {
      "address": "00e3a32e",
      "instruction": "JZ 0x00e3a517"
    },
    {
      "address": "00e3a334",
      "instruction": "RET 0x8"
    },
    {
      "address": "00e3a337",
      "instruction": "CMP EAX,0xd832b059"
    },
    {
      "address": "00e3a33c",
      "instruction": "JG 0x00e3a38a"
    },
    {
      "address": "00e3a33e",
      "instruction": "JZ 0x00e3a517"
    },
    {
      "address": "00e3a344",
      "instruction": "CMP EAX,0xade76cce"
    },
    {
      "address": "00e3a349",
      "instruction": "JZ 0x00e3a364"
    },
    {
      "address": "00e3a34b",
      "instruction": "CMP EAX,0xcdb3696f"
    },
    {
      "address": "00e3a350",
      "instruction": "JZ 0x00e3a517"
    },
    {
      "address": "00e3a356",
      "instruction": "CMP EAX,0xd536c91d"
    },
    {
      "address": "00e3a35b",
      "instruction": "JZ 0x00e3a517"
    },
    {
      "address": "00e3a361",
      "instruction": "RET 0x8"
    },
    {
      "address": "00e3a364",
      "instruction": "CMP dword ptr [ECX + 0x32c],-0x1"
    },
    {
      "address": "00e3a36b",
      "instruction": "JNZ 0x00e3a377"
    },
    {
      "address": "00e3a36d",
      "instruction": "MOV dword ptr [ECX + 0x32c],0x1654c01"
    },
    {
      "address": "00e3a377",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00e3a37b",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00e3a37e",
      "instruction": "MOV EAX,dword ptr [EDX + 0x8]"
    },
    {
      "address": "00e3a381",
      "instruction": "MOV dword ptr [ECX + 0x310],EAX"
    },
    {
      "address": "00e3a387",
      "instruction": "RET 0x8"
    },
    {
      "address": "00e3a38a",
      "instruction": "CMP EAX,0xdca976d0"
    },
    {
      "address": "00e3a38f",
      "instruction": "JZ 0x00e3a2c0"
    },
    {
      "address": "00e3a395",
      "instruction": "CMP EAX,0xe0bc9d45"
    },
    {
      "address": "00e3a39a",
      "instruction": "JZ 0x00e3a517"
    },
    {
      "address": "00e3a3a0",
      "instruction": "RET 0x8"
    },
    {
      "address": "00e3a3a3",
      "instruction": "CMP EAX,0x3e2a3040"
    },
    {
      "address": "00e3a3a8",
      "instruction": "JG 0x00e3a4be"
    },
    {
      "address": "00e3a3ae",
      "instruction": "JZ 0x00e3a4a1"
    },
    {
      "address": "00e3a3b4",
      "instruction": "CMP EAX,0x279c4e55"
    },
    {
      "address": "00e3a3b9",
      "instruction": "JG 0x0
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
  "original_bytes": 10026,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_note\": \"(declared) against unclassified_in_EAX (record)\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"Word\",\n    \"saved_registers\": [\n      \"none -- the body never pushes a register, so it has no frame and saves nothing\"\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0515\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:WARN\"\n  ],\n  \"integration_status\": null,\n  \"name\": null,\n  \"normalized_symbol\": null,\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w2-00e3a400/00e3a400.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Simulator\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"unknown-fun-mass\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"dossier\": null,\n    \"evidence\": \"INFERRED\",\n    \"in_degree\": 0,\n    \"kg_node_id\": null,\n    \"name\": null,\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"adjudicated\": true,\n      \"classifier\": \"triage-v6\",\n      \"replacement_candidate\": \"partial\",\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\"\n    }\n  },\n  \"types\": [\n    \"Word\",\n    \"Word (declared) against unclassified_in_EAX (record)\"\n  ],\n  \"unresolved_questions\": [\n    \"ABI/CALLS/RETURN SEMANTICS are NOT_AVAILABLE with the detail 'target source span is not deterministically available', and the cause is NOT the reconstruction source. validate._target_span binds a span only through record['name'] or record['normalized_symbol'] (tools/reconstruction_tooling/validate.py:242-291), and the index record for 0x00e3a400 carries BOTH AS NULL: the triage row knowledgegraph/triage/queue-f0e310e0-v6.json has name=null for this VA (source: unknown-high-investigation) and the manifest has no functions[] row for it, so reconstruction_
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
  "body_end": "00e3a56a",
  "body_span_bytes": 763,
  "body_start": "00e3a270",
  "callees": [
    "FUN_00e39420"
  ],
  "callers": [
    "FUN_00e3f970"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e3a270",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar1",
      "storage": "unique:00017200:4",
      "type": "undefined4"
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
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00e3a270",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa3a400",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e3a270(void)",
  "size_bytes": 763,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e3a400",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00e3fc73"
    }
  ]
}
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:WARN"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400.cpp",
    "reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00e3a400/sw2_00e3a400_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00e3a400/00e3a400.json"
  ]
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "Word",
  "Word (declared) against unclassified_in_EAX (record)"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
