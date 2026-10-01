# Evidence 0x00e7b6c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `824938b17aec7864cd546469a45d1fc6320b4dbdfd2735b7e74d031ef8ca7873`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_this": false,
  "hidden_this_register": null,
  "ordinary_stack_argument_slots": 1,
  "receiver": "NONE. Undetermined with reason ecx_read_without_deref. ECX is read at 0x00e7b68b as a LOAD out of memory (MOV ECX,[EAX+0x1b0]) and immediately PUSHed at 0x00e7b691 as the first of 0x00e6d200's four ordinary stack arguments. It is read and written seventeen times across the body and dereferenced nowhere. The body works through EAX, EBX, EDX, EDI, EBP and ESI.",
  "ret_form": "RET",
  "return_register": "ST0",
  "return_semantics": "float_or_x87_in_ST0",
  "return_type": "void",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI"
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
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
  "content_sha256": "d5e3553a4acc60d361a6ecc19e8502b60414e5d17bdaa663c7584df3c6d2a5cb",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0042"
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
        "obs-0006"
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
        "obs-0012",
        "obs-0016",
        "obs-0027",
        "obs-0037"
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
        "obs-0012",
        "obs-0016",
        "obs-0027",
        "obs-0037"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0042"
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
      "and_esp": null,
      "at": "0x00e7b630",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00e7b630",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00e7b633",
      "count": 7,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "CMP byte ptr [ESI + 0x112],0x1",
      "reg": "ESI"
    },
    {
      "at": "0x00e7b63a",
      "count": 4,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00e7b63b",
      "count": 7,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EBP,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x00e7b63b",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0006",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBP,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4,
      "trust": "untrusted_frame"
    },
    {
      "at": "0x00e7b63b",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,dword ptr [ESP + 0x10]",
      "reg": "EBP",
 
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
"\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n\nvoid FUN_00e7b630(undefined4 *param_1)\n\n{\n  undefined4 uVar1;\n  cCellObjectData *cell;\n  undefined4 uVar2;\n  int iVar3;\n  undefined4 *unaff_ESI;\n  float10 extraout_ST0;\n  undefined1 local_8 [4];\n  float local_4;\n  \n  if ((((*(char *)((int)unaff_ESI + 0x112) != '\\x01') &&\n       (*(char *)((int)unaff_ESI + 0x113) != '\\x01')) && (*(char *)(unaff_ESI + 0x5e) == '\\0')) &&\n     ((*(char *)((int)unaff_ESI + 0x17f) == '\\0' && (*(char *)((int)param_1 + 0x17b) == '\\0')))) {\n    cell = (cCellObjectData *)FUN_00b72210(*unaff_ESI);\n    Simulator__Cell__PlayAnimation\n              (cell,(cCellObjectData *)0x0,kAnimIndexCellEatMandNpcBig,cell->mCurrentAnimation);\n    local_4 = (float)extraout_ST0;\n    uVar1 = *unaff_ESI;\n    uVar2 = FUN_00b72160();\n    iVar3 = FUN_00b72210(uVar2);\n    *(float *)(iVar3 + 0x1c) = local_4;\n    *(float *)(iVar3 + 0x20) = local_4;\n    *(undefined4 *)(iVar3 + 0x24) = 0x20;\n    *(undefined4 *)(iVar3 + 0x28) = uVar1;\n    *(undefined4 *)(iVar3 + 0x2c) = 0;\n    *(undefined4 *)(iVar3 + 0x30) = 0xffffffff;\n    *(undefined4 *)(iVar3 + 0x34) = 0xffffffff;\n    *(undefined4 *)(iVar3 + 0x38) = 0;\n    *(undefined4 *)(iVar3 + 0x3c) = 0;\n    *(undefined4 *)(iVar3 + 0x40) = 0;\n    *(undefined4 *)(iVar3 + 0x44) = 0;\n    *(undefined4 *)(iVar3 + 0x48) = DAT_016b3c28;\n    *(undefined4 *)(iVar3 + 0x4c) = DAT_016b3c2c;\n    *(undefined4 *)(iVar3 + 0x50) = DAT_016b3c30;\n    *(undefined4 *)(iVar3 + 0x54) = DAT_016b3c28;\n    *(undefined4 *)(iVar3 + 0x58) = DAT_016b3c2c;\n    *(undefined4 *)(iVar3 + 0x5c) = DAT_016b3c30;\n    *(undefined4 *)(iVar3 + 0x60) = DAT_015a7c4c;\n    *(undefined4 *)(iVar3 + 100) = DAT_015a7c50;\n    *(undefined4 *)(iVar3 + 0x68) = DAT_015a7c54;\n    *(undefined4 *)(iVar3 + 0x6c) = DAT_015a7c58;\n    *(undefined4 *)(iVar3 + 0x70) = 0;\n    *(undefined1 *)(iVar3 + 0x74) = 0;\n    *(undefined4 *)(iVar3 + 0x78) = 0;\n    *(undefined4 *)(iVar3 + 4) = 0;\n    *(undefined1 *)(iVar3 + 8) = 0;\n    FUN_00743b50();\n    iVar3 = thunk_FUN_00e823a0(param_1[0x42],local_8);\n    FUN_00e5d7b0(*(undefined4 *)(iVar3 + 0xb8));\n    FUN_00e780a0(*param_1,1,0,0);\n    FUN_00e59a70();\n    FUN_00e82130();\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 105,
  "instructions": [
    {
      "address": "00e7b630",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00e7b633",
      "instruction": "CMP byte ptr [ESI + 0x112],0x1"
    },
    {
      "address": "00e7b63a",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00e7b63b",
      "instruction": "MOV EBP,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00e7b63f",
      "instruction": "JZ 0x00e7b7ad"
    },
    {
      "address": "00e7b645",
      "instruction": "CMP byte ptr [ESI + 0x113],0x1"
    },
    {
      "address": "00e7b64c",
      "instruction": "JZ 0x00e7b7ad"
    },
    {
      "address": "00e7b652",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e7b653",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00e7b655",
      "instruction": "CMP byte ptr [ESI + 0x178],BL"
    },
    {
      "address": "00e7b65b",
      "instruction": "JNZ 0x00e7b7ac"
    },
    {
      "address": "00e7b661",
      "instruction": "CMP byte ptr [ESI + 0x17f],BL"
    },
    {
      "address": "00e7b667",
      "instruction": "JNZ 0x00e7b7ac"
    },
    {
      "address": "00e7b66d",
      "instruction": "CMP byte ptr [EBP + 0x17b],BL"
    },
    {
      "address": "00e7b673",
      "instruction": "JNZ 0x00e7b7ac"
    },
    {
      "address": "00e7b679",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00e7b67b",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7b681",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7b682",
      "instruction": "ADD ECX,0x1c"
    },
    {
      "address": "00e7b685",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7b686",
      "instruction": "CALL 0x00b72210"
    },
    {
      "address": "00e7b68b",
      "instruction": "MOV ECX,dword ptr [EAX + 0x1b0]"
    },
    {
      "address": "00e7b691",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7b692",
      "instruction": "PUSH 0x31"
    },
    {
      "address": "00e7b694",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e7b695",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7b696",
      "instruction": "CALL 0x00e6d200"
    },
    {
      "address": "00e7b69b",
      "instruction": "FSTP float ptr [ESP + 0x20]"
    },
    {
      "address": "00e7b69f",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7b6a5",
      "instruction": "MOV EDI,dword ptr [ESI]"
    },
    {
      "address": "00e7b6a7",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00e7b6aa",
      "instruction": "ADD ECX,0x54"
    },
    {
      "address": "00e7b6ad",
      "instruction": "CALL 0x00b72160"
    },
    {
      "address": "00e7b6b2",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7b6b8",
      "instruction": "ADD ECX,0x54"
    },
    {
      "address": "00e7b6bb",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7b6bc",
      "instruction": "CALL 0x00b72210"
    },
    {
      "address": "00e7b6c1",
      "instruction": "FLD float ptr [ESP + 0x10]"
    },
    {
      "address": "00e7b6c5",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00e7b6c8",
      "instruction": "FST float ptr [EAX + 0x1c]"
    },
    {
      "address": "00e7b6cb",
      "instruction": "FSTP float ptr [EAX + 0x20]"
    },
    {
      "address": "00e7b6ce",
      "instruction": "MOV dword ptr [EAX + 0x24],0x20"
    },
    {
      "address": "00e7b6d5",
      "instruction": "MOV dword ptr [EAX + 0x28],EDI"
    },
    {
      "address": "00e7b6d8",
      "instruction": "MOV dword ptr [EAX + 0x2c],EBX"
    },
    {
      "address": "00e7b6db",
      "instruction": "OR ECX,0xffffffff"
    },
    {
      "address": "00e7b6de",
      "instruction": "MOV dword ptr [EAX + 0x30],ECX"
    },
    {
      "address": "00e7b6e1",
      "instruction": "MOV dword ptr [EAX + 0x34],ECX"
    },
    {
      "address": "00e7b6e4",
      "instruction": "MOV dword ptr [EAX + 0x38],EBX"
    },
    {
      "address": "00e7b6e7",
      "instruction": "MOV dword ptr [EAX + 0x3c],EBX"
    },
    {
      "address": "00e7b6ea",
      "instruction": "MOVSS dword ptr [EAX + 0x40],XMM0"
    },
    {
      "address": "00e7b6ef",
      "instruction": "MOVSS dword ptr [EAX + 0x44],XMM0"
    },
    {
      "address": "00e7b6f4",
      "instruction": "MOV EDX,dword ptr [0x016b3c28]"
    },
    {
      "address": "00e7b6fa",
      "instruction": "MOV dword ptr [EAX + 0x48],EDX"
    },
    {
      "address": "00e7b6fd",
      "instruction": "MOV ECX,dword ptr [0x016b3c2c]"
    },
    {
      "address": "00e7b703",
      "instruction": "MOV dword ptr [EAX + 0x4c],ECX"
    },
    {
      "address": "00e7b706",
      "instruction": "MOV EDX,dword ptr [0x016b3c30]"
    },
    {
      "address": "00e7b70c",
      "instruction": "MOV dword ptr [EAX + 0x50],EDX"
    },
    {
      "address": "00e7b70f",
      "instruction": "MOV ECX,dword ptr [0x016b3c28]"
    },
    {
      "address": "00e7b715",
      "instruction": "MOV dword ptr [EAX + 0x54],ECX"
    },
    {
      "address": "00e7b718",
      "instruction": "MOV EDX,dword ptr [0x016b3c2c]"
    },
    {
      "address": "00e7b71e",
      "instruction": "MOV dword ptr [EAX + 0x58],EDX"
    },
    {
      "address": "00e7b721",
      "instruction": "MOV ECX,dword ptr [0x016b3c30]"
    },
    {
      "address": "00e7b727",
      "instruction": "MOV dword ptr [EAX + 0x5c],ECX"
    },
    {
      "address": "00e7b72a",
      "instruction": "MOV EDX,dword ptr [0x015a7c4c]"
    },
    {
      "address": "00e7b730",
      "instruction": "MOV dword ptr [EAX + 0x60],EDX"
    },
    {
      "address": "00e7b733",
      "instruction": "MOV ECX,dword ptr [0x015a7c50]"
    },
    {
      "address": "00e7b739",
      "instruction": "MOV dword ptr [EAX + 0x64],ECX"
    },
    {
      "address": "00e7b7
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
  "original_bytes": 9060,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": null,\n    \"hidden_this\": false,\n    \"hidden_this_register\": null,\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": \"NONE. Undetermined with reason ecx_read_without_deref. ECX is read at 0x00e7b68b as a LOAD out of memory (MOV ECX,[EAX+0x1b0]) and immediately PUSHed at 0x00e7b691 as the first of 0x00e6d200's four ordinary stack arguments. It is read and written seventeen times across the body and dereferenced nowhere. The body works through EAX, EBX, EDX, EDI, EBP and ESI.\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"ST0\",\n    \"return_semantics\": \"float_or_x87_in_ST0\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0552\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [\n    \"global:WARN\"\n  ],\n  \"integration_status\": null,\n  \"name\": null,\n  \"normalized_symbol\": null,\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_entry.cpp\",\n      \"reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_model_test.cpp\",\n      \"reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-w2-00e7b6c0/00e7b6c0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Simulator\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"unknown-fun-mass\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"dossier\": null,\n    \"evidence\": \"SUPPORTED\",\n    \"in_degree\": 0,\n    \"kg_node_id\": null,\n    \"name\": null,\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"adjudicated\": true,\n      \"classifier\": \"triage-v6\",\n      \"replacement_candidate\": \"partial\",\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\"\n    }\n  },\n  \"types\": [\n    \"openspore::reconstruction::pkg_w2_00e7b6c0::CalleeTerminator00e7b6c0\",\n    \"openspore::reconstruction::pkg_w2_00e7b6c0::RecordValueSource00e7b6c0\",\n    \"openspore::reconstruction::pkg_w2_00e7b6c0::RecordWrite00e7b6c0\",\n    \"std::size_t\",\n    \"std::uint32_t\",\n    \"std::uint8_t\",\n    \"void\",\n    \"void, and that is a reading of the listing rather than a recovered fact. No instruction places a value in a return register at the single return site. EAX's last write is 0x00e7b79b, whose o
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
  "body_end": "00e7b7b1",
  "body_span_bytes": 386,
  "body_start": "00e7b630",
  "callees": [
    "FUN_00b72160",
    "thunk_FUN_00e823a0",
    "FUN_00b72210",
    "FUN_00743b50",
    "FUN_00e780a0",
    "FUN_00e59a70",
    "FUN_00e5d7b0",
    "Simulator::Cell::PlayAnimation",
    "FUN_00e82130"
  ],
  "callers": [
    "FUN_00e7e7f0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e7b630",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "extraout_ST0",
      "storage": "register:00001100:10",
      "type": "float10"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "float"
    },
    {
      "name": "local_8",
      "storage": "",
      "type": "undefined1[4]"
    },
    {
      "name": "uVar1",
      "storage": "unique:00017200:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4 *"
    },
    {
      "name": "unaff_ESI",
      "storage": "register:00000018:4",
      "type": "undefined4 *"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "uVar2",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "cell",
      "storage": "register:00000000:4",
      "type": "cCellObjectData *"
    }
  ],
  "locals_count": 9,
  "mode": "live",
  "name": "FUN_00e7b630",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa7b6c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e7b630(void)",
  "size_bytes": 386,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e7b6c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00e7e8f1"
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
    "reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_entry.cpp",
    "reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_model_test.cpp",
    "reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00e7b6c0/00e7b6c0.json"
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
  "openspore::reconstruction::pkg_w2_00e7b6c0::CalleeTerminator00e7b6c0",
  "openspore::reconstruction::pkg_w2_00e7b6c0::RecordValueSource00e7b6c0",
  "openspore::reconstruction::pkg_w2_00e7b6c0::RecordWrite00e7b6c0",
  "std::size_t",
  "std::uint32_t",
  "std::uint8_t",
  "void",
  "void, and that is a reading of the listing rather than a recovered fact. No instruction places a value in a return register at the single return site. EAX's last write is 0x00e7b79b, whose only consumer is the call that follows it; XMM0's last write is the XORPS at 0x00e7b6c5, consumed by the two MOVSS at 0x00e7b6ea and 0x00e7b6ef. The machine record's return_register ST0 with return_semantics float_or_x87_in_ST0 is at confidence APPROXIMATION under rule RT1, whose stated basis is that an x87 or SSE instruction appears in the body; it is carried in the header as data and is NOT adopted. The x87 balance is a fact of the listing and it points the same way: the body pushes twice and pops three times, so whatever ST0 held on entry is consumed and nothing is left."
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
