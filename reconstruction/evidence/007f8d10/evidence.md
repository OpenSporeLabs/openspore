# Evidence 0x007f8d10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e4f60f9a3a339509ef24bf7375e12b3339a0c855eaa2dcf52e11d5546f78d680`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall; receiver in ECX, three callee-cleaned 4-byte stack arguments",
  "ordinary_stack_argument_slots": 3,
  "receiver": "ECX, spilled to E0-0x8c at 0x007f8d1e and reloaded into EAX at 0x007f8edb to write [EAX+0x1c]; read through `LEA ESI,[ECX+0x4]` at 0x007f8d3f",
  "ret_form": "RET 0xc",
  "return_register": "none",
  "return_type": "void",
  "stack_cleanup_bytes": 12,
  "stack_cleanup_owner": "callee"
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0xc",
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "572e38ea7827603cfc0ea9fd6a017db6767d1e24b611273ccfad033e6811a6a0",
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
    "persisted_calling_convention": "__thiscall; receiver in ECX, three callee-cleaned 4-byte stack arguments"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0059"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0009",
        "obs-0020",
        "obs-0021",
        "obs-0024",
        "obs-0036",
        "obs-0037"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0014",
        "obs-0033",
        "obs-0040",
        "obs-0042",
        "obs-0048"
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
        "obs-0007",
        "obs-0008",
        "obs-0014",
        "obs-0033",
        "obs-0040",
        "obs-0042",
        "obs-0048"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0036",
        "obs-0037"
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
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x007f8d10",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "SUB ESP,0x8c",
     
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
    "va": "0x0059a500"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006478c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0064ecc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00658440"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006589d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00658e80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0065fd30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00668070"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00832230"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00834730"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x008347f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00dd5a30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00dd5bb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00dd6570"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00dd7970"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00dd8640"
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
"\nvoid __thiscall FUN_007f8d10(int param_1,int param_2,int *param_3,int param_4)\n\n{\n  int *piVar1;\n  int *piVar2;\n  uint uVar3;\n  int iVar4;\n  int iVar5;\n  uint uVar6;\n  uint uVar7;\n  int *piVar8;\n  int *local_88 [2];\n  undefined **local_80;\n  undefined **local_78;\n  int *local_74;\n  \n  if (param_3 == (int *)0x0) {\n    return;\n  }\n  if (*(int *)(param_2 + 4) == 0) {\n    return;\n  }\n  piVar1 = (int *)(param_1 + 4);\n  iVar5 = *(int *)(param_1 + 8) - *piVar1;\n  uVar3 = (*(int *)(param_1 + 8) - *piVar1) / 0x88;\n  iVar4 = iVar5 >> 0x1f;\n  uVar6 = 0;\n  uVar7 = uVar3;\n  if (iVar5 / 0x88 + iVar4 != iVar4) {\n    piVar8 = (int *)*piVar1;\n    while (piVar2 = (int *)*piVar8, uVar7 = uVar6, piVar2 != (int *)0x0) {\n      if ((piVar2 == param_3) && (piVar8[1] == param_4)) {\n        if (piVar2 != (int *)0x0) {\n          (*(code *)piVar8[3])(piVar8 + 2,0,0,1,0);\n        }\n        break;\n      }\n      uVar6 = uVar6 + 1;\n      piVar8 = piVar8 + 0x22;\n      uVar7 = uVar3;\n      if ((uint)((*(int *)(param_1 + 8) - *piVar1) / 0x88) <= uVar6) break;\n    }\n  }\n  if (uVar7 == (*(int *)(param_1 + 8) - *piVar1) / 0x88) {\n    uVar3 = *(uint *)(param_1 + 8);\n    local_88[0] = (int *)0x0;\n    local_80 = &PTR_FUN_013f6400;\n    local_78 = &PTR_FUN_013f63fc;\n    local_74 = (int *)0x0;\n    if (uVar3 < *(uint *)(param_1 + 0xc)) {\n      *(uint *)(param_1 + 8) = uVar3 + 0x88;\n      if (uVar3 == 0) goto LAB_007f8e83;\n      FUN_007f6d90(local_88);\n    }\n    else {\n      FUN_007f8820(uVar3,local_88);\n    }\n    if (local_74 != (int *)0x0) {\n      (**(code **)(*local_74 + 4))();\n    }\n    if (local_88[0] != (int *)0x0) {\n      (**(code **)(*local_88[0] + 4))();\n    }\n  }\nLAB_007f8e83:\n  piVar8 = (int *)(uVar7 * 0x88 + *piVar1);\n  piVar1 = (int *)*piVar8;\n  if (param_3 != piVar1) {\n    (**(code **)*param_3)();\n    *piVar8 = (int)param_3;\n    if (piVar1 != (int *)0x0) {\n      (**(code **)(*piVar1 + 4))();\n    }\n  }\n  piVar8[1] = param_4;\n  FUN_007f6ff0(param_2);\n  (*(code *)piVar8[3])(piVar8 + 2,0,0,0,0);\n  *(undefined1 *)(param_1 + 0x1c) = 1;\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 158,
  "instructions": [
    {
      "address": "007f8d10",
      "instruction": "SUB ESP,0x8c"
    },
    {
      "address": "007f8d16",
      "instruction": "PUSH EBP"
    },
    {
      "address": "007f8d17",
      "instruction": "MOV EBP,dword ptr [ESP + 0x98]"
    },
    {
      "address": "007f8d1e",
      "instruction": "MOV dword ptr [ESP + 0x4],ECX"
    },
    {
      "address": "007f8d22",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "007f8d24",
      "instruction": "JZ 0x007f8ee9"
    },
    {
      "address": "007f8d2a",
      "instruction": "MOV EAX,dword ptr [ESP + 0x94]"
    },
    {
      "address": "007f8d31",
      "instruction": "CMP dword ptr [EAX + 0x4],0x0"
    },
    {
      "address": "007f8d35",
      "instruction": "JZ 0x007f8ee9"
    },
    {
      "address": "007f8d3b",
      "instruction": "PUSH EBX"
    },
    {
      "address": "007f8d3c",
      "instruction": "FLDZ"
    },
    {
      "address": "007f8d3e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "007f8d3f",
      "instruction": "LEA ESI,[ECX + 0x4]"
    },
    {
      "address": "007f8d42",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "007f8d45",
      "instruction": "SUB ECX,dword ptr [ESI]"
    },
    {
      "address": "007f8d47",
      "instruction": "MOV EAX,0x78787879"
    },
    {
      "address": "007f8d4c",
      "instruction": "IMUL ECX"
    },
    {
      "address": "007f8d4e",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "007f8d51",
      "instruction": "SUB ECX,dword ptr [ESI]"
    },
    {
      "address": "007f8d53",
      "instruction": "SAR EDX,0x6"
    },
    {
      "address": "007f8d56",
      "instruction": "PUSH EDI"
    },
    {
      "address": "007f8d57",
      "instruction": "MOV EDI,EDX"
    },
    {
      "address": "007f8d59",
      "instruction": "SHR EDI,0x1f"
    },
    {
      "address": "007f8d5c",
      "instruction": "ADD EDI,EDX"
    },
    {
      "address": "007f8d5e",
      "instruction": "MOV EAX,0x78787879"
    },
    {
      "address": "007f8d63",
      "instruction": "IMUL ECX"
    },
    {
      "address": "007f8d65",
      "instruction": "SAR EDX,0x6"
    },
    {
      "address": "007f8d68",
      "instruction": "MOV ECX,EDX"
    },
    {
      "address": "007f8d6a",
      "instruction": "SHR ECX,0x1f"
    },
    {
      "address": "007f8d6d",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "007f8d6f",
      "instruction": "ADD ECX,EDX"
    },
    {
      "address": "007f8d71",
      "instruction": "JZ 0x007f8dc1"
    },
    {
      "address": "007f8d73",
      "instruction": "MOV EBP,dword ptr [ESI]"
    },
    {
      "address": "007f8d75",
      "instruction": "MOV EAX,dword ptr [EBP]"
    },
    {
      "address": "007f8d78",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "007f8d7a",
      "instruction": "JZ 0x007f8e48"
    },
    {
      "address": "007f8d80",
      "instruction": "CMP EAX,dword ptr [ESP + 0xa4]"
    },
    {
      "address": "007f8d87",
      "instruction": "JNZ 0x007f8d99"
    },
    {
      "address": "007f8d89",
      "instruction": "MOV EDX,dword ptr [ESP + 0xa8]"
    },
    {
      "address": "007f8d90",
      "instruction": "CMP dword ptr [EBP + 0x4],EDX"
    },
    {
      "address": "007f8d93",
      "instruction": "JZ 0x007f8e1c"
    },
    {
      "address": "007f8d99",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "007f8d9c",
      "instruction": "SUB ECX,dword ptr [ESI]"
    },
    {
      "address": "007f8d9e",
      "instruction": "MOV EAX,0x78787879"
    },
    {
      "address": "007f8da3",
      "instruction": "IMUL ECX"
    },
    {
      "address": "007f8da5",
      "instruction": "SAR EDX,0x6"
    },
    {
      "address": "007f8da8",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "007f8daa",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "007f8dad",
      "instruction": "INC EBX"
    },
    {
      "address": "007f8dae",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "007f8db0",
      "instruction": "ADD EBP,0x88"
    },
    {
      "address": "007f8db6",
      "instruction": "CMP EBX,EAX"
    },
    {
      "address": "007f8db8",
      "instruction": "JC 0x007f8d75"
    },
    {
      "address": "007f8dba",
      "instruction": "MOV EBP,dword ptr [ESP + 0xa4]"
    },
    {
      "address": "007f8dc1",
      "instruction": "FSTP ST0"
    },
    {
      "address": "007f8dc3",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "007f8dc6",
      "instruction": "SUB ECX,dword ptr [ESI]"
    },
    {
      "address": "007f8dc8",
      "instruction": "MOV EAX,0x78787879"
    },
    {
      "address": "007f8dcd",
      "instruction": "IMUL ECX"
    },
    {
      "address": "007f8dcf",
      "instruction": "SAR EDX,0x6"
    },
    {
      "address": "007f8dd2",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "007f8dd4",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "007f8dd7",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "007f8dd9",
      "instruction": "CMP EDI,EAX"
    },
    {
      "address": "007f8ddb",
      "instruction": "JNZ 0x007f8e83"
    },
    {
      "address": "007f8de1",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "007f8de4",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "007f8de6",
      "instruction": "MOV dword ptr [ESP + 0x14],EBX"
    },
    {
      "address": "007f8dea",
      "instruction": "MOV dword ptr [ESP + 0x1c],0x13f6400"
    },
    {
      "address": "007f8df2",
      "instruction": "MOV dword ptr [ESP + 0x24],0x13f63fc"
    },
    {
      "address": "007f8dfa",
      "instruction": "MOV dword ptr [ESP + 0x28],EBX"
    },
    {
      "address": "007f8dfe",
      "instruction": "CMP ECX,dword p
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
  "original_bytes": 13852,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall; receiver in ECX, three callee-cleaned 4-byte stack arguments\",\n    \"ordinary_stack_argument_slots\": 3,\n    \"receiver\": \"ECX, spilled to E0-0x8c at 0x007f8d1e and reloaded into EAX at 0x007f8edb to write [EAX+0x1c]; read through `LEA ESI,[ECX+0x4]` at 0x007f8d3f\",\n    \"ret_form\": \"RET 0xc\",\n    \"return_register\": \"none\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 12,\n    \"stack_cleanup_owner\": \"callee\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059a500\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006478c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0064ecc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00658440\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006589d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00658e80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0065fd30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00668070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00832230\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00834730\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x008347f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd5a30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd5bb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd6570\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd7970\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd8640\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e133b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e13b50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e27310\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e28f40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e29da0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e32250\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e389e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e38bb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e38ce0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e38fd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e390d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e39200\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e40420\"\n      
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
  "body_end": "007f8ef2",
  "body_span_bytes": 483,
  "body_start": "007f8d10",
  "callees": [
    "FUN_007f8820",
    "FUN_007f6ff0",
    "FUN_007f6d90"
  ],
  "callers": [
    "FUN_008347f0",
    "FUN_00dd7970",
    "FUN_00658e80",
    "FUN_00e49f80",
    "FUN_00668070",
    "FUN_00dd8640",
    "FUN_00832230",
    "FUN_00dd5a30",
    "FUN_00e38ce0",
    "FUN_00e40420",
    "FUN_00e29da0",
    "FUN_00e389e0",
    "FUN_00e38bb0",
    "FUN_0059a500",
    "FUN_00e28f40",
    "FUN_006478c0",
    "FUN_00f07fd0",
    "FUN_00e390d0",
    "FUN_00dd5bb0",
    "FUN_00e133b0",
    "FUN_0064ecc0",
    "FUN_00e423a0",
    "FUN_00f0a1e0",
    "FUN_00658440",
    "FUN_00e39200",
    "FUN_00e13b50",
    "FUN_00834730",
    "FUN_01066f20",
    "FUN_00e27310",
    "FUN_0065fd30",
    "FUN_00dd6570",
    "FUN_00e32250",
    "FUN_006589d0",
    "FUN_00e38fd0",
    "PTRREF_007F9230"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "007f8d10",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "piVar1",
      "storage": "unique:00006600:4",
      "type": "int *"
    },
    {
      "name": "param_4",
      "storage": "Stack[0xc]:4",
      "type": "int"
    },
    {
      "name": "local_80",
      "storage": "Stack[-0x80]:4",
      "type": "undefined * *"
    },
    {
      "name": "uVar3",
      "storage": "unique:00017200:4",
      "type": "uint"
    },
    {
      "name": "local_88",
      "storage": "Stack[-0x88]:4",
      "type": "int *[2]"
    },
    {
      "name": "piVar2",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "iVar5",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "local_74",
      "storage": "Stack[-0x74]:4",
      "type": "int *"
    },
    {
      "name": "iVar4",
      "storage": "unique:100000ed:4",
      "type": "int"
    },
    {
      "name": "local_78",
      "storage": "Stack[-0x78]:4",
      "type": "undefined * *"
    },
    {
      "name": "uVar7",
      "storage": "register:0000001c:4",
      "type": "uint"
    },
    {
      "name": "uVar6",
      "storage": "register:0000000c:4",
      "type": "uint"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "int *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "piVar8",
      "storage": "register:00000014:4",
      "type": "int *"
    }
  ],
  "locals_count": 16,
  "mode": "live",
  "name": "FUN_007f8d10",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3f8d10",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_007f8d10(void)",
  "size_bytes": 483,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007f8d10",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 80,
  "xrefs": [
    {
      "from": "00e138b0"
    },
    {
      "from": "00e1392f"
    },
    {
      "from": "00e139b3"
    },
    {
      "from": "00e13a1d"
    },
    {
      "from": "00e13f01"
    },
    {
      "from": "00e13f83"
    },
    {
      "from": "00e14003"
    },
    {
      "from": "00e1406d"
    },
    {
      "from": "00dd88bf"
    },
    {
      "from": "00647b2c"
    },
    {
      "from": "00647b99"
    },
    {
      "from": "00647bf0"
    },
    {
      "from": "00647c5f"
    },
    {
      "from": "00647de8"
    },
    {
      "from": "00647e3e"
    },
    {
      "from": "00647e8f"
    },
    {
      "from": "0059a58b"
    },
    {
      "from": "0064f0f1"
    },
    {
      "from": "0064f153"
    },
    {
      "from": "0064f20b"
    },
    {
      "from": "00658fca"
    },
    {
      "from": "006591ba"
    },
    {
      "from": "006591fd"
    },
    {
      "from": "0065fe6c"
    },
    {
      "from": "0065fec0"
    },
    {
      "from": "0065ff11"
    },
    {
      "from": "00660006"
    },
    {
      "from": "00660054"
    },
    {
      "from": "00668269"
    },
    {
      "from": "00668335"
    },
    {
      "from": "0066848b"
    },
    {
      "from": "0083479a"
    },
    {
      "from": "008348e1"
    },
    {
      "from": "0083231e"
    },
    {
      "from": "00dd7cca"
    },
    {
      "from": "00dd7e7d"
    },
    {
      "from": "00dd5b6d"
    },
    {
      "from": "00dd5cca"
    },
    {
      "from": "00dd5d3e"
    },
    {
      "from": "00dd664c"
    },
    {
      "from": "00dd66b8"
    },
    {
      "from": "00e2977d"
    },
    {
      "from": "00e298ee"
    },
    {
      "from": "00e29a7e"
    },
    {
      "from": "00e29bd9"
    },
    {
      "from": "00e2a00b"
    },
    {
      "from": "00e2a115"
    },
    {
      "from": "00e2a263"
    },
    {
      "from": "00e2a366"
    },
    {
      "from": "00e2a440"
    },
    {
      "from": "00e32419"
    },
    {
      "from": "00e38b68"
    },
    {
      "from": "00e428d6"
    },
    {
      "from": "00658abe"
    },
    {
      "from": "00658b4a"
    },
    {
      "from": "006585b7"
    },
    {
      "from": "0065864f"
    },
    {
      "from": "00f08319"
    },
    {
      "from": "00f0a2e3"
    },
    {
      "from": "010670dc"
    },
    {
      "from": "00e4a1fa"
    },
    {
  
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
  "files": [
    "reconstruction/staging/pkg-007f8d10-registry-ensure-entry/registry_ensure_entry_007f8d10.cpp",
    "reconstruction/staging/pkg-007f8d10-registry-ensure-entry/registry_ensure_entry_007f8d10.hpp",
    "reconstruction/staging/pkg-007f8d10-registry-ensure-entry/registry_ensure_entry_007f8d10_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-007f8d10-registry-ensure-entry/007f8d10.json"
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
  "void"
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
