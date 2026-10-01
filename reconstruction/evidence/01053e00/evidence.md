# Evidence 0x01053e00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b52c3ceda45e9fd3d9b0ebdd779161c4c18949cd88b8e3dc65b20ebf0f66fbe7`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": [
    "__stdcall by machine shape; the record's own derived conventions block abstains",
    "Observed MSVC x86 virtual-member convention already established for this table by the sibling reconstruction of 0x01053db0: the receiver is NOT in ECX but is the first callee-popped stack argument, read as MOV ESI,[ESP+0x20] at 0x01053e04 after SUB ESP,0x18 / PUSH ESI. ECX is used only to carry the receiver of each inner virtual."
  ],
  "hidden_this": false,
  "receiver_register": "none. The machine record's receiver sub-record names no register and enumerates no offsets, with reason ecx_reassigned_before_deref. That is accurate about the DERIVATION (ECX is reassigned at 0x01053e08 before it is ever dereferenced) and it says nothing about the body reaching no fields, which it plainly does. See `contradictions`.",
  "ret_form": "RET 0x8",
  "return_register": "AL",
  "return_type": "bool",
  "return_width_bytes": 1,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    "{'evidence': 'MOV ESI,[ESP+0x20] at 0x01053e04 with the prologue already applied, and MOV ECX,[ESP+0x24] at 0x01053eb4 reloading the same word', 'index': 0, 'offset_hex': '0x04', 'role': 'receiver; the object whose fields at +0x114 and +0x124 are read'}",
    "{'evidence': 'no instruction in the 65-instruction body reads [ESP+0x08] relative to the entry stack pointer, yet RET 0x8 at 0x01053eca and 0x01053ed3 clean eight bytes', 'index': 1, 'offset_hex': '0x08', 'role': 'second callee-popped stack word; never read by this body'}"
  ],
  "stack_cleanup_bytes": 8,
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "b34c3ce26a58e59810963ca45de6623ad51a5b25e7d07a4276a814a57f35dfe4",
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
    "persisted_calling_convention": "[\"__stdcall by machine shape; the record's own derived conventions block abstains\", 'Observed MSVC x86 virtual-member convention already established for this table by the sibling reconstruction of 0x01053db0: the receiver is NOT in ECX but is the first callee-popped stack argument, read as MOV ESI,[ESP+0x20] at 0x01053e04 after SUB ESP,0x18 / PUSH ESI. ECX is used only to carry the receiver of each inner virtual.']"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0029",
        "obs-0031"
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
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0016",
        "obs-0026"
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
        "obs-0009",
        "obs-0016",
        "obs-0026"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0005"
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
      "and_esp": null,
      "at": "0x01053e00",
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
      "raw": "SUB ESP,0x18",
      "sub": 24
    },
    {
      "at": "0x01053e00",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x18",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x01053e03",
      "count": 9,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x01053e04",
      "count": 7,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x20]",
      "reg": "ESP"
    },
    {
      "at": "0x01053e04",
      "base": "ESP",
      "disp": 32,
      "id": "obs-0005",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x20]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x01053e04",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x20]",
      "reg": "ESI",
      "write_kin
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
"\nundefined4 FUN_01053e00(int param_1)\n\n{\n  char cVar1;\n  int *piVar2;\n  undefined4 unaff_retaddr;\n  undefined1 auStack_c [12];\n  \n  if (*(int **)(param_1 + 0x124) != (int *)0x0) {\n    cVar1 = (**(code **)(**(int **)(param_1 + 0x124) + 0x2c))();\n    if ((cVar1 != '\\0') && (piVar2 = *(int **)(param_1 + 0x124), piVar2 != (int *)0x0)) {\n      *(undefined4 *)(param_1 + 0x124) = 0;\n      (**(code **)(*piVar2 + 4))();\n    }\n  }\n  if (*(int *)(param_1 + 0x124) == 0) {\n    return 0;\n  }\n  if (*(int **)(param_1 + 0x114) != (int *)0x0) {\n    piVar2 = (int *)(**(code **)(**(int **)(param_1 + 0x114) + 0xb8))(&PTR_LAB_013f94d4);\n    if (piVar2 != (int *)0x0) {\n      (**(code **)(*piVar2 + 0x30))(auStack_c);\n      goto LAB_01053e7f;\n    }\n  }\n  (**(code **)(**(int **)(param_1 + 0x114) + 0x2c))();\nLAB_01053e7f:\n  (**(code **)(*(int *)(*(int *)(param_1 + 0x124) + 0x34) + 0x38))(&stack0xffffffe4);\n  FUN_00cb5930(unaff_retaddr);\n  return 1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 65,
  "instructions": [
    {
      "address": "01053e00",
      "instruction": "SUB ESP,0x18"
    },
    {
      "address": "01053e03",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01053e04",
      "instruction": "MOV ESI,dword ptr [ESP + 0x20]"
    },
    {
      "address": "01053e08",
      "instruction": "MOV ECX,dword ptr [ESI + 0x124]"
    },
    {
      "address": "01053e0e",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01053e10",
      "instruction": "JZ 0x01053e38"
    },
    {
      "address": "01053e12",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01053e14",
      "instruction": "MOV EDX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "01053e17",
      "instruction": "CALL EDX"
    },
    {
      "address": "01053e19",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "01053e1b",
      "instruction": "JZ 0x01053e38"
    },
    {
      "address": "01053e1d",
      "instruction": "MOV ECX,dword ptr [ESI + 0x124]"
    },
    {
      "address": "01053e23",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01053e25",
      "instruction": "JZ 0x01053e38"
    },
    {
      "address": "01053e27",
      "instruction": "MOV dword ptr [ESI + 0x124],0x0"
    },
    {
      "address": "01053e31",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01053e33",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01053e36",
      "instruction": "CALL EDX"
    },
    {
      "address": "01053e38",
      "instruction": "CMP dword ptr [ESI + 0x124],0x0"
    },
    {
      "address": "01053e3f",
      "instruction": "JZ 0x01053ecd"
    },
    {
      "address": "01053e45",
      "instruction": "MOV ECX,dword ptr [ESI + 0x114]"
    },
    {
      "address": "01053e4b",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01053e4d",
      "instruction": "JZ 0x01053e72"
    },
    {
      "address": "01053e4f",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01053e51",
      "instruction": "MOV EDX,dword ptr [EAX + 0xb8]"
    },
    {
      "address": "01053e57",
      "instruction": "PUSH 0x13f94d4"
    },
    {
      "address": "01053e5c",
      "instruction": "CALL EDX"
    },
    {
      "address": "01053e5e",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "01053e60",
      "instruction": "JZ 0x01053e72"
    },
    {
      "address": "01053e62",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "01053e64",
      "instruction": "MOV EDX,dword ptr [EDX + 0x30]"
    },
    {
      "address": "01053e67",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "01053e6b",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01053e6c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01053e6e",
      "instruction": "CALL EDX"
    },
    {
      "address": "01053e70",
      "instruction": "JMP 0x01053e7f"
    },
    {
      "address": "01053e72",
      "instruction": "MOV ECX,dword ptr [ESI + 0x114]"
    },
    {
      "address": "01053e78",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01053e7a",
      "instruction": "MOV EDX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "01053e7d",
      "instruction": "CALL EDX"
    },
    {
      "address": "01053e7f",
      "instruction": "MOVSS XMM0,dword ptr [EAX]"
    },
    {
      "address": "01053e83",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "01053e89",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01053e8e",
      "instruction": "MOVSS dword ptr [ESP + 0x8],XMM0"
    },
    {
      "address": "01053e94",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x8]"
    },
    {
      "address": "01053e99",
      "instruction": "MOV EAX,dword ptr [ESI + 0x124]"
    },
    {
      "address": "01053e9f",
      "instruction": "LEA ECX,[EAX + 0x34]"
    },
    {
      "address": "01053ea2",
      "instruction": "MOVSS dword ptr [ESP + 0xc],XMM0"
    },
    {
      "address": "01053ea8",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01053eaa",
      "instruction": "MOV EAX,dword ptr [EAX + 0x38]"
    },
    {
      "address": "01053ead",
      "instruction": "LEA EDX,[ESP + 0x4]"
    },
    {
      "address": "01053eb1",
      "instruction": "PUSH EDX"
    },
    {
      "address": "01053eb2",
      "instruction": "CALL EAX"
    },
    {
      "address": "01053eb4",
      "instruction": "MOV ECX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "01053eb8",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01053eb9",
      "instruction": "MOV ECX,dword ptr [ESI + 0x124]"
    },
    {
      "address": "01053ebf",
      "instruction": "CALL 0x00cb5930"
    },
    {
      "address": "01053ec4",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "01053ec6",
      "instruction": "POP ESI"
    },
    {
      "address": "01053ec7",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "01053eca",
      "instruction": "RET 0x8"
    },
    {
      "address": "01053ecd",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "01053ecf",
      "instruction": "POP ESI"
    },
    {
      "address": "01053ed0",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "01053ed3",
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
  "original_bytes": 13056,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": [\n      \"__stdcall by machine shape; the record's own derived conventions block abstains\",\n      \"Observed MSVC x86 virtual-member convention already established for this table by the sibling reconstruction of 0x01053db0: the receiver is NOT in ECX but is the first callee-popped stack argument, read as MOV ESI,[ESP+0x20] at 0x01053e04 after SUB ESP,0x18 / PUSH ESI. ECX is used only to carry the receiver of each inner virtual.\"\n    ],\n    \"hidden_this\": false,\n    \"receiver_register\": \"none. The machine record's receiver sub-record names no register and enumerates no offsets, with reason ecx_reassigned_before_deref. That is accurate about the DERIVATION (ECX is reassigned at 0x01053e08 before it is ever dereferenced) and it says nothing about the body reaching no fields, which it plainly does. See `contradictions`.\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"AL\",\n    \"return_type\": \"bool\",\n    \"return_width_bytes\": 1,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      \"{'evidence': 'MOV ESI,[ESP+0x20] at 0x01053e04 with the prologue already applied, and MOV ECX,[ESP+0x24] at 0x01053eb4 reloading the same word', 'index': 0, 'offset_hex': '0x04', 'role': 'receiver; the object whose fields at +0x114 and +0x124 are read'}\",\n      \"{'evidence': 'no instruction in the 65-instruction body reads [ESP+0x08] relative to the entry stack pointer, yet RET 0x8 at 0x01053eca and 0x01053ed3 clean eight bytes', 'index': 1, 'offset_hex': '0x08', 'role': 'second callee-popped stack word; never read by this body'}\"\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x0149b810,vtable:0x0149b8b4\"\n      ],\n      \"package\": \"pkg-sim-toolevent-01053d50\",\n      \"score\": 10,\n      \"symbol\": \"sim_toolevent_slot8_fun_01053d50\",\n      \"va\": \"0x01053d50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-core-systems\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x01053ebf\",\n        \"direction\": \"out\",\n        \"other\": \"0x00cb5930\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0610\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 1\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:0x013f94d4\",\n    \"global:WARN\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_01053e00\",\n  \"normalized_symbol\": \"FUN_01053e00\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00.cpp\",\n      \"reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00_model_test.cpp\",\n      \"reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00_types.hpp\",\n      \"reconstruction/staging/pkg-sim-beamtool-func5/beam_tool_func5_01053e00.cpp\",\n      \"reconstruction/staging/pkg-sim-beamtool-func5/beam_tool_func5_01053e00.hpp\",\n      \"reconstruction/staging/pkg-sim-beamtool-func5
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
  "body_end": "01053ed5",
  "body_span_bytes": 214,
  "body_start": "01053e00",
  "callees": [
    "FUN_00cb5930"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01053e00",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "unaff_retaddr",
      "storage": "Stack[0x0]:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "piVar2",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "auStack_c",
      "storage": "",
      "type": "undefined1[12]"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_01053e00",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc53e00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01053e00(void)",
  "size_bytes": 214,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01053e00",
  "vtables": {
    "referenced_by_vtables": [
      "0x0149b8b4",
      "0x0149b900",
      "0x0149b810",
      "0x0149ba30"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "0149b824"
    },
    {
      "from": "0149b8c4"
    },
    {
      "from": "0149b914"
    },
    {
      "from": "0149b964"
    },
    {
      "from": "0149ba44"
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
  "global:0x013f94d4",
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
    "reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00.cpp",
    "reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00_model_test.cpp",
    "reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00_types.hpp",
    "reconstruction/staging/pkg-sim-beamtool-func5/beam_tool_func5_01053e00.cpp",
    "reconstruction/staging/pkg-sim-beamtool-func5/beam_tool_func5_01053e00.hpp",
    "reconstruction/staging/pkg-sim-beamtool-func5/beam_tool_func5_01053e00_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-01053e00/01053e00.json",
    "reconstruction/metadata/pkg-sim-beamtool-func5/01053e00.json"
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
  "OpaqueBeamTarget",
  "OpaqueBeamToolState",
  "bool"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00c6a960",
  "vtable:0x0149b810",
  "vtable:0x0149b8b4",
  "vtable:0x0149b900",
  "vtable:0x0149ba30"
]
```

## Conflicts

```json
[]
```
