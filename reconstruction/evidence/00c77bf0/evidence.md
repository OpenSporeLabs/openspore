# Evidence 0x00c77bf0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `33129ca39c05c71b0ee68e0c19ab56f19cc1ed5ab9872ec289850908347655db`

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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
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
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path",
    "slot_width_ambiguous: one entry slot is read at more than one width",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "17a1219d2d42760693cdad45a88de2bc2a9eb021a14be9b1937abcadd81473d2",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0026"
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
        "obs-0007",
        "obs-0017",
        "obs-0018"
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
        "obs-0007",
        "obs-0017",
        "obs-0018"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0013"
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
        "obs-0009",
        "obs-0013"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0026"
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
        "obs-0026"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0026"
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
      "and_esp": null,
      "at": "0x00c77bf0",
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
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00c77bf0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c77bf3",
      "count": 1,
      "first_use": 1,
      "first_write_index": 21,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c77bf4",
      "count": 2,
      "first_use": 2,
      "first_write_index": 10,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c77bf5",
      "count": 3,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c77bf6",
      "count": 6,
      "first_use": 4,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x20]",
      "reg": "ESP"
    },
    {
      "at": "0x00c77bf6",
      "base": "ESP",
      "disp": 32,
      "id": "obs-0007",
     
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
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
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path",
    "slot_width_ambiguous: one entry slot is read at more than one width",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "17a1219d2d42760693cdad45a88de2bc2a9eb021a14be9b1937abcadd81473d2",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0026"
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
        "obs-0007",
        "obs-0017",
        "obs-0018"
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
        "obs-0007",
        "obs-0017",
        "obs-0018"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0013"
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
        "obs-0009",
        "obs-0013"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0026"
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
        "obs-0026"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0026"
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
      "and_esp": null,
      "at": "0x00c77bf0",
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
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00c77bf0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c77bf3",
      "count": 1,
      "first_use": 1,
      "first_write_index": 21,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c77bf4",
      "count": 2,
      "first_use": 2,
      "first_write_index": 10,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c77bf5",
      "count": 3,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c77bf6",
      "count": 6,
      "first_use": 4,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x20]",
      "reg": "ESP"
    },
    {
      "at": "0x00c77bf6",
      "base": "ESP",
      "disp": 32,
      "id": "obs-0007",
     
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
    "va": "0x00ae9c90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aea8e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aea9e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeaa80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeab40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb3e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aebe90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aecf90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be92e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf4370"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c00b00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c389f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c7bd40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c81ab0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c82400"
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
"\nbool __thiscall FUN_00c77bf0(int param_1,uint param_2)\n\n{\n  uint *puVar1;\n  int iVar2;\n  uint local_10;\n  undefined1 local_c [12];\n  \n  iVar2 = 0;\n  for (puVar1 = *(uint **)(*(int *)(param_1 + 0x1120) + (param_2 % *(uint *)(param_1 + 0x1124)) * 4)\n      ; puVar1 != (uint *)0x0; puVar1 = (uint *)puVar1[1]) {\n    if (param_2 == *puVar1) {\n      iVar2 = iVar2 + 1;\n    }\n  }\n  if (iVar2 == 0) {\n    local_10 = param_2;\n    FUN_00de5df0(local_c,&local_10,0);\n  }\n  return iVar2 != 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 39,
  "instructions": [
    {
      "address": "00c77bf0",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "00c77bf3",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c77bf4",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c77bf5",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c77bf6",
      "instruction": "MOV EDI,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00c77bfa",
      "instruction": "ADD ECX,0x111c"
    },
    {
      "address": "00c77c00",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00c77c02",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00c77c04",
      "instruction": "DIV dword ptr [ECX + 0x8]"
    },
    {
      "address": "00c77c07",
      "instruction": "MOV EAX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "00c77c0a",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00c77c0c",
      "instruction": "MOV EDX,dword ptr [EAX + EDX*0x4]"
    },
    {
      "address": "00c77c0f",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "00c77c11",
      "instruction": "JZ 0x00c77c1f"
    },
    {
      "address": "00c77c13",
      "instruction": "CMP EDI,dword ptr [EDX]"
    },
    {
      "address": "00c77c15",
      "instruction": "JNZ 0x00c77c18"
    },
    {
      "address": "00c77c17",
      "instruction": "INC ESI"
    },
    {
      "address": "00c77c18",
      "instruction": "MOV EDX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "00c77c1b",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "00c77c1d",
      "instruction": "JNZ 0x00c77c13"
    },
    {
      "address": "00c77c1f",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c77c21",
      "instruction": "SETNZ BL"
    },
    {
      "address": "00c77c24",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "00c77c26",
      "instruction": "JNZ 0x00c77c44"
    },
    {
      "address": "00c77c28",
      "instruction": "MOV byte ptr [ESP + 0x20],BL"
    },
    {
      "address": "00c77c2c",
      "instruction": "MOV EDX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00c77c30",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c77c31",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00c77c35",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c77c36",
      "instruction": "LEA EDX,[ESP + 0x18]"
    },
    {
      "address": "00c77c3a",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c77c3b",
      "instruction": "MOV dword ptr [ESP + 0x18],EDI"
    },
    {
      "address": "00c77c3f",
      "instruction": "CALL 0x00de5df0"
    },
    {
      "address": "00c77c44",
      "instruction": "POP EDI"
    },
    {
      "address": "00c77c45",
      "instruction": "POP ESI"
    },
    {
      "address": "00c77c46",
      "instruction": "MOV AL,BL"
    },
    {
      "address": "00c77c48",
      "instruction": "POP EBX"
    },
    {
      "address": "00c77c49",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00c77c4c",
      "instruction": "RET 0x4"
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
  "original_bytes": 13252,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9c90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aea8e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aea9e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeaa80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeab40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebe90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aecf90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be92e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf4370\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c00b00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c389f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c7bd40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c81ab0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c82400\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c830f0\"\n      },\n      {\n        \"name\": \"PoliticalOwnershipScan_00c8d060\",\n        \"reconstructed\": true,\n        \"va\": \"0x00c8d060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd3fb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd6980\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd7770\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cf31f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cf3bf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cf93b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d091c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d130d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d1e930\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d9bc70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00da2fd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e07e70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e2ade0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdabf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdade0\"\n      },\n      {\n        \"name\": null,\n        \"reconstr
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
  "body_end": "00c77c4e",
  "body_span_bytes": 95,
  "body_start": "00c77bf0",
  "callees": [
    "FUN_00de5df0"
  ],
  "callers": [
    "FUN_00aebe90",
    "FUN_00fe0c60",
    "FUN_00aeaa80",
    "FUN_00aeb3e0",
    "FUN_0102df20",
    "FUN_00c830f0",
    "FUN_00da2fd0",
    "FUN_00fdd5a0",
    "FUN_01003490",
    "FUN_0107bb00",
    "FUN_01041c50",
    "FUN_00c8d060",
    "FUN_00c00b00",
    "FUN_00c82400",
    "FUN_00aeab40",
    "FUN_00cf93b0",
    "FUN_00fdade0",
    "FUN_00c7bd40",
    "FUN_00e2ade0",
    "FUN_00d1e930",
    "FUN_00ffc030",
    "FUN_00fdabf0",
    "FUN_00cd3fb0",
    "FUN_00d130d0",
    "FUN_00fde3e0",
    "FUN_010021a0",
    "FUN_01064560",
    "FUN_00aecf90",
    "FUN_0105a110",
    "FUN_00aeb240",
    "FUN_00cd7770",
    "FUN_00cf31f0",
    "FUN_00ffdc20",
    "FUN_00ffe860",
    "FUN_00c389f0",
    "FUN_00cd6980",
    "FUN_00aea9e0",
    "FUN_00be92e0",
    "FUN_00d9bc70",
    "FUN_01016070",
    "FUN_01014e30",
    "FUN_01002f30",
    "FUN_00e07e70",
    "FUN_01079260",
    "FUN_00cf3bf0",
    "FUN_00bf4370",
    "FUN_01077630",
    "FUN_00d091c0",
    "FUN_00ae9c90",
    "FUN_00c81ab0",
    "FUN_00aea8e0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c77bf0",
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
      "name": "local_c",
      "storage": "",
      "type": "undefined1[12]"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "uint"
    },
    {
      "name": "iVar2",
      "storage": "register:00000018:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "uint"
    },
    {
      "name": "puVar1",
      "storage": "unique:00017200:4",
      "type": "uint *"
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "FUN_00c77bf0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x877bf0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c77bf0(void)",
  "size_bytes": 95,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c77bf0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 75,
  "xrefs": [
    {
      "from": "00aeb596"
    },
    {
      "from": "00aeabc4"
    },
    {
      "from": "00c7bda9"
    },
    {
      "from": "00be9688"
    },
    {
      "from": "00bf4565"
    },
    {
      "from": "00aeb28e"
    },
    {
      "from": "00aece6e"
    },
    {
      "from": "00c00d13"
    },
    {
      "from": "0102e21a"
    },
    {
      "from": "01077792"
    },
    {
      "from": "01041c93"
    },
    {
      "from": "00c38ad5"
    },
    {
      "from": "00aeab34"
    },
    {
      "from": "00aecfa9"
    },
    {
      "from": "00fde572"
    },
    {
      "from": "00fdd5e4"
    },
    {
      "from": "00aeaa74"
    },
    {
      "from": "00c8d2c4"
    },
    {
      "from": "00c81ed0"
    },
    {
      "from": "00c82805"
    },
    {
      "from": "00c835bd"
    },
    {
      "from": "00cd69bb"
    },
    {
      "from": "00cd3fc7"
    },
    {
      "from": "00cf3435"
    },
    {
      "from": "00cf3d9e"
    },
    {
      "from": "00cf3e08"
    },
    {
      "from": "00cf3f03"
    },
    {
      "from": "00cf4132"
    },
    {
      "from": "00cf946c"
    },
    {
      "from": "00d13952"
    },
    {
      "from": "00d139e0"
    },
    {
      "from": "00d09230"
    },
    {
      "from": "00d9bc96"
    },
    {
      "from": "00da323e"
    },
    {
      "from": "00e07f63"
    },
    {
      "from": "00e07fab"
    },
    {
      "from": "00e084cf"
    },
    {
      "from": "00e2b14c"
    },
    {
      "from": "00e2b4c6"
    },
    {
      "from": "010035ba"
    },
    {
      "from": "00fdac39"
    },
    {
      "from": "00fdac8f"
    },
    {
      "from": "00fdadc1"
    },
    {
      "from": "00fdaebd"
    },
    {
      "from": "00fe0d81"
    },
    {
      "from": "00ffc046"
    },
    {
      "from": "00ffea58"
    },
    {
      "from": "00ffead8"
    },
    {
      "from": "00ffec75"
    },
    {
      "from": "00ffdc78"
    },
    {
      "from": "01002f68"
    },
    {
      "from": "00aea988"
    },
    {
      "from": "01014ffd"
    },
    {
      "from": "010163ee"
    },
    {
      "from": "0105a85b"
    },
    {
      "from": "0106464b"
    },
    {
      "from": "0107942f"
    },
    {
      "from": "0107947d"
    },
    {
      "from": "0107bbd2"
    },
    {
      "from": "00cf34fb"
    },
    {
      "from": "00cf376f"
    },
    {
      "from": "00d1eb9b"
    },
    {
      "from": "00d1ed80"
    },
    {
      "from": "00cd7941"
    },
    {
      "from": "00ae9cf0"
    },
    {
      "from": "00c3da2c"
    },
    {
      "from": "00c608ae"
    },
    {
      "from": "00c77f33"
    },
    {
      "from": "00cf67f0"
    },
    {
      "from": "0100227b"
    },
    {
      "from": "00fe32b6"
    },
    {
      "from": "00fe3453"
    },
    {
      "from": "0100c79c"
    },
    {
      "from": "01053fe0"
    },
    {
      "from": "00cd0be0"
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
