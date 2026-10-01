# Evidence 0x00d018d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `88f645fb86cf31781b7afbe75d928e33f13a0d3dd349fdf9fbea2f226d65d0c5`

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
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "d34e8782d884fcebe03b37689e8781a988eaaa160e8a92460ecbc8e00063799a",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
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
        "obs-0022"
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
        "obs-0009"
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
        "obs-0005",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0022"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0022"
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
        "obs-0022"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0022"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00d018d0",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00d018d0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00d018d0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00d018d4",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00d018d5",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [ECX + 0x4]",
      "reg": "ECX"
    },
    {
      "at": "0x00d018d5",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ECX + 0x4]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00d018d8",
      "count": 3,
      "first_use": 3,
      "first_write_index": 6,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at
[TRUNCATED]
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
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "d34e8782d884fcebe03b37689e8781a988eaaa160e8a92460ecbc8e00063799a",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
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
        "obs-0022"
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
        "obs-0009"
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
        "obs-0005",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0022"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0022"
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
        "obs-0022"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0022"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00d018d0",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00d018d0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00d018d0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00d018d4",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00d018d5",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [ECX + 0x4]",
      "reg": "ECX"
    },
    {
      "at": "0x00d018d5",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ECX + 0x4]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00d018d8",
      "count": 3,
      "first_use": 3,
      "first_write_index": 6,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at
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
    "va": "0x00603650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00708d90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00723cf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0074e2b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007507e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00755da0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00769310"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00774b50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b9420"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b9510"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b9620"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007cf630"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007f2600"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00846db0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00846f10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0089b080"
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
"\nvoid __thiscall FUN_00d018d0(int param_1,undefined4 *param_2,undefined4 *param_3)\n\n{\n  undefined4 *puVar1;\n  undefined4 *puVar2;\n  undefined4 *puVar3;\n  \n  puVar1 = *(undefined4 **)(param_1 + 4);\n  puVar3 = param_2;\n  for (puVar2 = param_3; puVar2 != puVar1; puVar2 = puVar2 + 2) {\n    *puVar3 = *puVar2;\n    puVar3[1] = puVar2[1];\n    puVar3 = puVar3 + 2;\n  }\n  *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + ((int)param_3 - (int)param_2 >> 3) * -8;\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 31,
  "instructions": [
    {
      "address": "00d018d0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00d018d4",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00d018d5",
      "instruction": "MOV EBX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "00d018d8",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d018d9",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d018da",
      "instruction": "MOV EDI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00d018de",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00d018e0",
      "instruction": "MOV EDX,EDI"
    },
    {
      "address": "00d018e2",
      "instruction": "CMP EDI,EBX"
    },
    {
      "address": "00d018e4",
      "instruction": "JZ 0x00d018fc"
    },
    {
      "address": "00d018e6",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00d018e7",
      "instruction": "MOV EBP,dword ptr [EDX]"
    },
    {
      "address": "00d018e9",
      "instruction": "MOV dword ptr [ESI],EBP"
    },
    {
      "address": "00d018eb",
      "instruction": "MOV EBP,dword ptr [EDX + 0x4]"
    },
    {
      "address": "00d018ee",
      "instruction": "MOV dword ptr [ESI + 0x4],EBP"
    },
    {
      "address": "00d018f1",
      "instruction": "ADD EDX,0x8"
    },
    {
      "address": "00d018f4",
      "instruction": "ADD ESI,0x8"
    },
    {
      "address": "00d018f7",
      "instruction": "CMP EDX,EBX"
    },
    {
      "address": "00d018f9",
      "instruction": "JNZ 0x00d018e7"
    },
    {
      "address": "00d018fb",
      "instruction": "POP EBP"
    },
    {
      "address": "00d018fc",
      "instruction": "SUB EDI,EAX"
    },
    {
      "address": "00d018fe",
      "instruction": "SAR EDI,0x3"
    },
    {
      "address": "00d01901",
      "instruction": "NEG EDI"
    },
    {
      "address": "00d01903",
      "instruction": "ADD EDI,EDI"
    },
    {
      "address": "00d01905",
      "instruction": "ADD EDI,EDI"
    },
    {
      "address": "00d01907",
      "instruction": "ADD EDI,EDI"
    },
    {
      "address": "00d01909",
      "instruction": "ADD dword ptr [ECX + 0x4],EDI"
    },
    {
      "address": "00d0190c",
      "instruction": "POP EDI"
    },
    {
      "address": "00d0190d",
      "instruction": "POP ESI"
    },
    {
      "address": "00d0190e",
      "instruction": "POP EBX"
    },
    {
      "address": "00d0190f",
      "instruction": "RET 0x8"
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
  "original_bytes": 12058,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00603650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00708d90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00723cf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0074e2b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007507e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00755da0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00769310\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00774b50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b9420\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b9510\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b9620\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007cf630\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007f2600\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00846db0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00846f10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0089b080\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0089bd50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x008a1b70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00936b70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x009a1770\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a52fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00abba40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00abbbf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00abe110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac4ef0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac52d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac5c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b8c0f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdf750\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdf7e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdf880\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c7b510\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d053e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\
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
  "body_end": "00d01911",
  "body_span_bytes": 66,
  "body_start": "00d018d0",
  "callees": [],
  "callers": [
    "FUN_0101b0f0",
    "FUN_00e31650",
    "PTRREF_00CB1270",
    "FUN_00e7fd00",
    "FUN_008a1b70",
    "FUN_007b9510",
    "FUN_00d053e0",
    "FUN_007f2600",
    "FUN_0089b080",
    "FUN_009a1770",
    "FUN_0074e2b0",
    "FUN_00774b50",
    "FUN_00bdf7e0",
    "FUN_0089bd50",
    "FUN_00ac5c00",
    "FUN_00bdf750",
    "FUN_007507e0",
    "FUN_00e7f9b0",
    "FUN_00a52fa0",
    "FUN_007b9620",
    "PTRREF_00C7B240",
    "FUN_00b8c0f0",
    "FUN_00abba40",
    "FUN_00abe110",
    "FUN_00ac52d0",
    "FUN_007cf630",
    "FUN_00846db0",
    "FUN_00769310",
    "FUN_007b9420",
    "FUN_00ac4ef0",
    "FUN_00708d90",
    "FUN_00936b70",
    "FUN_00755da0",
    "FUN_00abbbf0",
    "FUN_00bdf880",
    "FUN_00846f10",
    "FUN_00e31550",
    "FUN_00603650",
    "FUN_00723cf0",
    "FUN_00c7b510",
    "PTRREF_00C2B170"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00d018d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "puVar2",
      "storage": "register:00000008:4",
      "type": "undefined4 *"
    },
    {
      "name": "puVar3",
      "storage": "register:00000018:4",
      "type": "undefined4 *"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "undefined4 *"
    },
    {
      "name": "puVar1",
      "storage": "unique:00017200:4",
      "type": "undefined4 *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4 *"
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "FUN_00d018d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x9018d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00d018d0(void)",
  "size_bytes": 66,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d018d0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 46,
  "xrefs": [
    {
      "from": "00b8c163"
    },
    {
      "from": "00b8c17c"
    },
    {
      "from": "009a17c0"
    },
    {
      "from": "00bdf773"
    },
    {
      "from": "00846e17"
    },
    {
      "from": "006036d7"
    },
    {
      "from": "00708dd8"
    },
    {
      "from": "00723d26"
    },
    {
      "from": "0074e2ce"
    },
    {
      "from": "00750850"
    },
    {
      "from": "00750869"
    },
    {
      "from": "00755e3d"
    },
    {
      "from": "00769af7"
    },
    {
      "from": "00774b99"
    },
    {
      "from": "007b94b2"
    },
    {
      "from": "007b95bd"
    },
    {
      "from": "007b9675"
    },
    {
      "from": "007cf678"
    },
    {
      "from": "007f265f"
    },
    {
      "from": "0089b0af"
    },
    {
      "from": "0089bd98"
    },
    {
      "from": "00846f6c"
    },
    {
      "from": "00936bc8"
    },
    {
      "from": "00936bf3"
    },
    {
      "from": "00a52fdb"
    },
    {
      "from": "00abbc44"
    },
    {
      "from": "00abe17f"
    },
    {
      "from": "00abe1c3"
    },
    {
      "from": "00ac4f18"
    },
    {
      "from": "00ac5d67"
    },
    {
      "from": "00ac5318"
    },
    {
      "from": "00bdf803"
    },
    {
      "from": "00bdf8a3"
    },
    {
      "from": "0101b13f"
    },
    {
      "from": "00c7b524"
    },
    {
      "from": "00e315dc"
    },
    {
      "from": "00d0543a"
    },
    {
      "from": "00e3165e"
    },
    {
      "from": "00e8002f"
    },
    {
      "from": "008a1bc2"
    },
    {
      "from": "00e7fa52"
    },
    {
      "from": "00e7fb99"
    },
    {
      "from": "00c2b3da"
    },
    {
      "from": "00c7b253"
    },
    {
      "from": "00cb1419"
    },
    {
      "from": "00abba8b"
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
