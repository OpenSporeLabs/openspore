# Evidence 0x00c71e30

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0ce5ec82a81cd77cf3d0d5c81aa204ac5f614f59ca5e74688f21388dc2b3f75f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (ECX carries the receiver and is dereferenced at 0x00c71e31 before any definite write to it; both exits are the bare 0xc3; no stack word is read as an argument). THE NAME IS NOT DISCRIMINATED BY THE BYTES - see calling_convention_caveat",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": "ECX, read at 0x00c71e31 (`8b f1`, MOV ESI,ECX) before any definite write; copied into ESI and then read back through ESI at 0x00c71e33, 0x00c71e47 and 0x00c71e50. The record's receiver.shape is R-ALIAS, which is exactly this: the body aliases its receiver into a scratch register rather than dereferencing ECX directly.",
  "ret_form": "RET (0x00c71e66 and 0x00c71e6a, both the bare 0xc3, no imm16)",
  "return_note": "32-bit dword",
  "return_register": "EAX",
  "return_semantics": "the passing arm returns 0x00ba9370's result verbatim - neither 0x00c71e65 (POP ESI) nor 0x00c71e66 (RET) touches EAX; the null arm returns a full 32-bit zero from `33 c0` at 0x00c71e67",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "8ae5299e4a6db525287587600671f9dd7c695969ddbf556a83416ea201e53e67",
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
    "persisted_calling_convention": "__thiscall (ECX carries the receiver and is dereferenced at 0x00c71e31 before any definite write to it; both exits are the bare 0xc3; no stack word is read as an argument). THE NAME IS NOT DISCRIMINATED BY THE BYTES - see calling_convention_caveat"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0014",
        "obs-0016"
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
        "obs-0004"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          212,
          316
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0014",
        "obs-0016"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0014",
        "obs-0016"
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
        "obs-0014",
        "obs-0016"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0014",
        "obs-0016"
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
      "at": "0x00c71e30",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c71e31",
      "count": 2,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c71e31",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c71e33",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x13c]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c71e3d",
      "id": "obs-0005",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b8dab0",
      "target": "0x00b8dab0"
    },
    {
      "at": "0x00c71e47",
      "definite": true,
      "id": "obs-0006",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0xd4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c71e4d",
      "count": 4,
      "first_use": 9,
      "first_write_index": 8,
      "id": "obs-0007",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x4c]",
      "reg": "EAX"
    },
    {
      "at": "0x00c71e4d",
      "definite": true,
      "id": "obs-0008",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x4c]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c71e56",
      "count": 1,
      "first_use": 11,
      "first_write_index": 9,
      "id": "obs-0009",
      "index": 11,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00c71e56",
      "base": "EDX",
      "disp": null,
      "id": "obs-0010",
      "index": 11,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00c71e59",
      "id": "obs-0011",
      "index": 13,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d2a0",
      "target": "0x00b3d2a0"
    },
    {
      "at": "0x00c71e60",
      "id": "obs-0012",
      "index": 15,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00ba9370",
      "target": "0x00ba9370"
    },
    {
      "at": "0x00c71e65",
  
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
  },
  {
    "name": "FUN_00b8dab0",
    "reconstructed": false,
    "va": "0x00b8dab0"
  },
  {
    "name": "Simulator_LookupEmpireByPoliticalId",
    "reconstructed": true,
    "va": "0x00ba9370"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ad4a10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba5270"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbcf00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bdbf10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be7bf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00becd70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c38270"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c54380"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c57ad0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c5b9c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c5c470"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c63380"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c82400"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c830f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d5e0c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00dd2650"
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
"\nundefined4 __fastcall FUN_00c71e30(int param_1)\n\n{\n  int iVar1;\n  undefined4 uVar2;\n  \n  if (*(int *)(param_1 + 0x13c) != 0) {\n    iVar1 = FUN_00b8dab0();\n    if (iVar1 == 5) {\n      uVar2 = (**(code **)(*(int *)(param_1 + 0xd4) + 0x4c))();\n      FUN_00b3d2a0(uVar2);\n      uVar2 = FUN_00ba9370(uVar2);\n      return uVar2;\n    }\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 21,
  "instructions": [
    {
      "address": "00c71e30",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c71e31",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c71e33",
      "instruction": "MOV ECX,dword ptr [ESI + 0x13c]"
    },
    {
      "address": "00c71e39",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00c71e3b",
      "instruction": "JZ 0x00c71e67"
    },
    {
      "address": "00c71e3d",
      "instruction": "CALL 0x00b8dab0"
    },
    {
      "address": "00c71e42",
      "instruction": "CMP EAX,0x5"
    },
    {
      "address": "00c71e45",
      "instruction": "JNZ 0x00c71e67"
    },
    {
      "address": "00c71e47",
      "instruction": "MOV EAX,dword ptr [ESI + 0xd4]"
    },
    {
      "address": "00c71e4d",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4c]"
    },
    {
      "address": "00c71e50",
      "instruction": "LEA ECX,[ESI + 0xd4]"
    },
    {
      "address": "00c71e56",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c71e58",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c71e59",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00c71e5e",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c71e60",
      "instruction": "CALL 0x00ba9370"
    },
    {
      "address": "00c71e65",
      "instruction": "POP ESI"
    },
    {
      "address": "00c71e66",
      "instruction": "RET"
    },
    {
      "address": "00c71e67",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00c71e69",
      "instruction": "POP ESI"
    },
    {
      "address": "00c71e6a",
      "instruction": "RET"
    }
  ]
}
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
  "original_bytes": 15006,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall (ECX carries the receiver and is dereferenced at 0x00c71e31 before any definite write to it; both exits are the bare 0xc3; no stack word is read as an argument). THE NAME IS NOT DISCRIMINATED BY THE BYTES - see calling_convention_caveat\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"ordinary_stack_arguments\": [],\n    \"receiver\": \"ECX, read at 0x00c71e31 (`8b f1`, MOV ESI,ECX) before any definite write; copied into ESI and then read back through ESI at 0x00c71e33, 0x00c71e47 and 0x00c71e50. The record's receiver.shape is R-ALIAS, which is exactly this: the body aliases its receiver into a scratch register rather than dereferencing ECX directly.\",\n    \"ret_form\": \"RET (0x00c71e66 and 0x00c71e6a, both the bare 0xc3, no imm16)\",\n    \"return_note\": \"32-bit dword\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"the passing arm returns 0x00ba9370's result verbatim - neither 0x00c71e65 (POP ESI) nor 0x00c71e66 (RET) touches EAX; the null arm returns a full 32-bit zero from `33 c0` at 0x00c71e67\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 9,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      },\n      {\n        \"name\": \"FUN_00b8dab0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b8dab0\"\n      },\n      {\n        \"name\": \"Simulator_LookupEmpireByPoliticalId\",\n        \"reconstructed\": true,\n        \"va\": \"0x00ba9370\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad4a10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbcf00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdbf10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be7bf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00becd70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c38270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c54380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c57ad0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5b9c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5c470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c63380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c82400\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c830f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d5e0c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd2650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd4950\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd5160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e1d020\"\n      },\n      {
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
  "body_end": "00c71e6a",
  "body_span_bytes": 59,
  "body_start": "00c71e30",
  "callees": [
    "FUN_00ba9370",
    "FUN_00b3d2a0",
    "FUN_00b8dab0"
  ],
  "callers": [
    "FUN_00c38270",
    "FUN_00e1d020",
    "FUN_00d5e0c0",
    "FUN_0106a7b0",
    "FUN_01003690",
    "FUN_00dd4950",
    "FUN_00c63380",
    "FUN_0106fc90",
    "FUN_00c5b9c0",
    "FUN_00c82400",
    "FUN_00bdbf10",
    "FUN_00dd5160",
    "FUN_00ba5270",
    "VTDISC_00FFBB20",
    "FUN_00fdfbc0",
    "FUN_00dd2650",
    "FUN_00ffabc0",
    "FUN_01067b60",
    "FUN_00bbcf00",
    "FUN_00c5c470",
    "FUN_0103fe90",
    "FUN_00ad4a10",
    "FUN_010019a0",
    "FUN_00ff9800",
    "FUN_0105b350",
    "FUN_00ff6a50",
    "FUN_00c57ad0",
    "FUN_00becd70",
    "FUN_010743a0",
    "FUN_00be7bf0",
    "FUN_00c830f0",
    "FUN_00c54380",
    "FUN_00ffd280",
    "FUN_01023fc0",
    "FUN_01001b60",
    "FUN_0106ba00",
    "FUN_01000000",
    "FUN_01057bd0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c71e30",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "uVar2",
      "storage": "register:00000000:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00c71e30",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x871e30",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c71e30(void)",
  "size_bytes": 59,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c71e30",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 51,
  "xrefs": [
    {
      "from": "00d5e344"
    },
    {
      "from": "00ad4a2a"
    },
    {
      "from": "00ad4a3a"
    },
    {
      "from": "00bdc008"
    },
    {
      "from": "00dd2668"
    },
    {
      "from": "00dd4966"
    },
    {
      "from": "010019ae"
    },
    {
      "from": "01000026"
    },
    {
      "from": "00bbd014"
    },
    {
      "from": "00ba52ff"
    },
    {
      "from": "0106bbbd"
    },
    {
      "from": "00be85f0"
    },
    {
      "from": "00bece9d"
    },
    {
      "from": "00c382b5"
    },
    {
      "from": "00ff98cd"
    },
    {
      "from": "00ff6a92"
    },
    {
      "from": "0100397c"
    },
    {
      "from": "00c545bb"
    },
    {
      "from": "00c57b94"
    },
    {
      "from": "00c5ba26"
    },
    {
      "from": "00c5c57f"
    },
    {
      "from": "00c63474"
    },
    {
      "from": "00c8272e"
    },
    {
      "from": "00c833dd"
    },
    {
      "from": "00c836f8"
    },
    {
      "from": "00dd5495"
    },
    {
      "from": "00ffd28b"
    },
    {
      "from": "00e1d429"
    },
    {
      "from": "01001b81"
    },
    {
      "from": "01001b91"
    },
    {
      "from": "00fdfc1c"
    },
    {
      "from": "01074505"
    },
    {
      "from": "0106a7e0"
    },
    {
      "from": "00ffabe0"
    },
    {
      "from": "010240db"
    },
    {
      "from": "0103ff30"
    },
    {
      "from": "0105b4db"
    },
    {
      "from": "01067c1c"
    },
    {
      "from": "010700ab"
    },
    {
      "from": "00c553fa"
    },
    {
      "from": "00c55426"
    },
    {
      "from": "00c55494"
    },
    {
      "from": "00c554bc"
    },
    {
      "from": "00c5e5b9"
    },
    {
      "from": "00c5e6c1"
    },
    {
      "from": "00cfff80"
    },
    {
      "from": "00fe2fc3"
    },
    {
      "from": "00ffbb47"
    },
    {
      "from": "01057ca1"
    },
    {
      "from": "01028bd7"
    },
    {
      "from": "01028d5c"
    }
  ]
}
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
  "files": [
    "reconstruction/staging/pkg-00c71e30-empire5/empire5_00c71e30.cpp",
    "reconstruction/staging/pkg-00c71e30-empire5/empire5_00c71e30.hpp",
    "reconstruction/staging/pkg-00c71e30-empire5/empire5_00c71e30_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-00c71e30-empire5/00c71e30.json"
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
  "32-bit dword"
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
