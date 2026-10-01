# Evidence 0x00f9fef0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `67c16fa0e3ae44c198af45465cde4dbed1dd7a78d91c46943b2ee3c3dde0de70`

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
  "ordinary_stack_argument_slots": 1,
  "receiver": "ECX carries the receiver, and the witness is the strongest in this campaign. 0x00f9fef3 MOV EDI,ECX copies the incoming register into EDI before anything else touches it; 0x00f9fef5 TEST EDI,EDI and 0x00f9fef7 JZ 0x00f9fefe NULL-TEST it; 0x00f9fef9 LEA EBX,[EDI+0x4] forms an interior address from it. What the machine record states, at INFERRED confidence: receiver {present true, register ECX, provenance vftable_slot_dispatch, bounds_only true, shape null, distinct_offsets 0, offsets [], written_through 0}. What the listing shows: the register is read by eleven instructions and every one of ...",
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_observation": "The record classifies the return as pointer_like in EAX with aggregate_evidence bulk_write false, and the listing agrees on the width and the shape. The listing says more, and only the listing is read here: the early out returns the interior pointer, and the main path does not return at all. The C spelling is Word *, chosen because the value is a plain four-byte interior address; a pointer-to-Receiver spelling would additionally imply a type this package declines to name.",
  "return_register": "EAX",
  "return_semantics": "pointer_like_in_EAX",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +60, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "8b2f88c9c0fc2268fde484d5b372d92b082c9c701520e6d833f446955332e2ca",
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
    "indirect_calls": 10,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0044"
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
        "obs-0008"
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
        "obs-0004"
      ],
      "claim": "ECX carries the receiver: 0x00f9fef0 is slot 35 of the vptr-backed vftable at 0x01490be8, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 35,
        "table": "0x01490be8"
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0013",
        "obs-0044"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0044"
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
        "obs-0044"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0044"
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
      "at": "0x00f9fef0",
      "count": 4,
      "first_use": 0,
      "first_write_index": 8,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00f9fef1",
      "count": 11,
      "first_use": 1,
      "first_write_index": 9,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00f9fef2",
      "count": 10,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00f9fef3",
      "count": 1,
      "first_use": 3,
      "first_write_index": 13,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00f9fef3",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00f9fefe",
      "definite": true,
      "id": "obs-0006",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "XOR EBX,EBX",
      "reg": "EBX",
      "write_kind": "zero"
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "app_direct_property_list_get_direct_bool_006a25a0",
    "reconstructed": true,
    "va": "0x006a25a0"
  }
]
```

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
"\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nvoid __thiscall FUN_00f9fef0(int param_1,int *param_2)\n\n{\n  char cVar1;\n  char cVar2;\n  int iVar3;\n  void *pEffectsRenderer;\n  IShadowWorld *pIVar4;\n  int *piVar5;\n  undefined4 uVar6;\n  int iVar7;\n  \n  if (param_1 == 0) {\n    iVar7 = 0;\n  }\n  else {\n    iVar7 = param_1 + 4;\n  }\n  iVar3 = (**(code **)(*param_2 + 0x58))(8);\n  if (iVar3 != iVar7) {\n    cVar1 = Prop_GetPropValueBool(0x201a4e50);\n    cVar2 = Prop_GetPropValueBool(0xe13ce337);\n    if (cVar1 != '\\0') {\n      FUN_00f96b40();\n      if (cVar2 != '\\0') {\n        FUN_00f9e3a0();\n      }\n    }\n    if (param_1 == 0) {\n      iVar7 = 0;\n    }\n    else {\n      iVar7 = param_1 + 4;\n    }\n    (**(code **)(*param_2 + 0x4c))(iVar7,7,0);\n    if (param_1 == 0) {\n      iVar7 = 0;\n    }\n    else {\n      iVar7 = param_1 + 4;\n    }\n    (**(code **)(*param_2 + 0x4c))(iVar7,8,0);\n    if (param_1 == 0) {\n      pEffectsRenderer = (void *)0x0;\n    }\n    else {\n      pEffectsRenderer = (void *)(param_1 + 4);\n    }\n    iVar7 = 0x21;\n    (**(code **)(*param_2 + 0x4c))(pEffectsRenderer,0x21,0);\n    pIVar4 = Graphics__IShadowWorld__Get();\n    piVar5 = (int *)(*pIVar4->_vftable0->AddEffects)\n                              ((IShadowWorld *)0x3fbae24,pEffectsRenderer,iVar7);\n    iVar7 = *param_2;\n    uVar6 = (**(code **)(*piVar5 + 0x13c))(10,0);\n    (**(code **)(iVar7 + 0x4c))(uVar6);\n    (**(code **)(*piVar5 + 0x134))(1);\n    piVar5 = (int *)FUN_0067ddd0();\n    piVar5 = (int *)(**(code **)(*piVar5 + 0x54))(0x3fbae24);\n                    /* WARNING: Could not recover jumptable at 0x00fa0001. Too many branches */\n                    /* WARNING: Treating indirect jump as call */\n    (**(code **)(*piVar5 + 0xc))(0);\n    return;\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 112,
  "instructions": [
    {
      "address": "00f9fef0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00f9fef1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00f9fef2",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00f9fef3",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00f9fef5",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00f9fef7",
      "instruction": "JZ 0x00f9fefe"
    },
    {
      "address": "00f9fef9",
      "instruction": "LEA EBX,[EDI + 0x4]"
    },
    {
      "address": "00f9fefc",
      "instruction": "JMP 0x00f9ff00"
    },
    {
      "address": "00f9fefe",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00f9ff00",
      "instruction": "MOV ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00f9ff04",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00f9ff06",
      "instruction": "MOV EDX,dword ptr [EAX + 0x58]"
    },
    {
      "address": "00f9ff09",
      "instruction": "PUSH 0x8"
    },
    {
      "address": "00f9ff0b",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f9ff0d",
      "instruction": "CALL EDX"
    },
    {
      "address": "00f9ff0f",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00f9ff11",
      "instruction": "JZ 0x00fa0003"
    },
    {
      "address": "00f9ff17",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00f9ff18",
      "instruction": "MOV EBP,dword ptr [0x015fd918]"
    },
    {
      "address": "00f9ff1e",
      "instruction": "PUSH 0x201a4e50"
    },
    {
      "address": "00f9ff23",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00f9ff25",
      "instruction": "CALL 0x006a25a0"
    },
    {
      "address": "00f9ff2a",
      "instruction": "PUSH 0xe13ce337"
    },
    {
      "address": "00f9ff2f",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00f9ff31",
      "instruction": "MOV BL,AL"
    },
    {
      "address": "00f9ff33",
      "instruction": "CALL 0x006a25a0"
    },
    {
      "address": "00f9ff38",
      "instruction": "MOV byte ptr [ESP + 0x14],AL"
    },
    {
      "address": "00f9ff3c",
      "instruction": "POP EBP"
    },
    {
      "address": "00f9ff3d",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "00f9ff3f",
      "instruction": "JZ 0x00f9ff54"
    },
    {
      "address": "00f9ff41",
      "instruction": "CALL 0x00f96b40"
    },
    {
      "address": "00f9ff46",
      "instruction": "CMP byte ptr [ESP + 0x10],0x0"
    },
    {
      "address": "00f9ff4b",
      "instruction": "JZ 0x00f9ff54"
    },
    {
      "address": "00f9ff4d",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00f9ff4f",
      "instruction": "CALL 0x00f9e3a0"
    },
    {
      "address": "00f9ff54",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00f9ff56",
      "instruction": "JZ 0x00f9ff5d"
    },
    {
      "address": "00f9ff58",
      "instruction": "LEA EAX,[EDI + 0x4]"
    },
    {
      "address": "00f9ff5b",
      "instruction": "JMP 0x00f9ff5f"
    },
    {
      "address": "00f9ff5d",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00f9ff5f",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00f9ff61",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00f9ff63",
      "instruction": "PUSH 0x7"
    },
    {
      "address": "00f9ff65",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00f9ff66",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4c]"
    },
    {
      "address": "00f9ff69",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f9ff6b",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f9ff6d",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00f9ff6f",
      "instruction": "JZ 0x00f9ff76"
    },
    {
      "address": "00f9ff71",
      "instruction": "LEA EAX,[EDI + 0x4]"
    },
    {
      "address": "00f9ff74",
      "instruction": "JMP 0x00f9ff78"
    },
    {
      "address": "00f9ff76",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00f9ff78",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00f9ff7a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00f9ff7c",
      "instruction": "PUSH 0x8"
    },
    {
      "address": "00f9ff7e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00f9ff7f",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4c]"
    },
    {
      "address": "00f9ff82",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f9ff84",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f9ff86",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00f9ff88",
      "instruction": "JZ 0x00f9ff8f"
    },
    {
      "address": "00f9ff8a",
      "instruction": "LEA EAX,[EDI + 0x4]"
    },
    {
      "address": "00f9ff8d",
      "instruction": "JMP 0x00f9ff91"
    },
    {
      "address": "00f9ff8f",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00f9ff91",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00f9ff93",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00f9ff95",
      "instruction": "PUSH 0x21"
    },
    {
      "address": "00f9ff97",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00f9ff98",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4c]"
    },
    {
      "address": "00f9ff9b",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f9ff9d",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f9ff9f",
      "instruction": "CALL 0x0067dd80"
    },
    {
      "address": "00f9ffa4",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00f9ffa6",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0
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
  "original_bytes": 10014,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": \"ECX carries the receiver, and the witness is the strongest in this campaign. 0x00f9fef3 MOV EDI,ECX copies the incoming register into EDI before anything else touches it; 0x00f9fef5 TEST EDI,EDI and 0x00f9fef7 JZ 0x00f9fefe NULL-TEST it; 0x00f9fef9 LEA EBX,[EDI+0x4] forms an interior address from it. What the machine record states, at INFERRED confidence: receiver {present true, register ECX, provenance vftable_slot_dispatch, bounds_only true, shape null, distinct_offsets 0, offsets [], written_through 0}. What the listing shows: the register is read by eleven instructions and every one of ...\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_observation\": \"The record classifies the return as pointer_like in EAX with aggregate_evidence bulk_write false, and the listing agrees on the width and the shape. The listing says more, and only the listing is read here: the early out returns the interior pointer, and the main path does not return at all. The C spelling is Word *, chosen because the value is a plain four-byte interior address; a pointer-to-Receiver spelling would additionally imply a type this package declines to name.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w2-00f999e0\",\n      \"score\": 12,\n      \"symbol\": \"re_00f999e0\",\n      \"va\": \"0x00f999e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-fa0d50-atomic-inc\",\n      \"score\": 12,\n      \"symbol\": \"FUN_00fa0d50\",\n      \"va\": \"0x00fa0d50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-00fa5580\",\n      \"score\": 12,\n      \"symbol\": \"re_00fa5580\",\n      \"va\": \"0x00fa5580\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-00fa6ec0\",\n      \"score\": 12,\n      \"symbol\": \"re_00fa6ec0\",\n      \"va\": \"0x00fa6ec0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-00fa73c0\",\n      \"score\": 12,\n      \"symbol\": \"sw1_snap_and_dispatch_00fa73c0\",\n      \"va\": \"0x00fa73c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-0104c110\",\n      \"score\": 12,\n      \"symbol\": \"re_0104c110\",\n      \"va\": \"0x0104c110\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-005c0dd0\",\n      \"score\": 8,\n      \"symbol\": \"re_005c0dd0\",\n      \"va\": \"0x005c0dd0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-006413d0\",\n      \"score\": 8,\n      \"symbol\": \"re_006413d0\",\n      \"va\": \"0x006413d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"app_direct_property_list_get_direct_bool_006a25a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x006a25a0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00f9ff9f\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9ffdc\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067ddd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9ff25\",\n        \"direction\": \"out\",\n        \"other\": \"0x006a25a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9ff33\",\n        \"direction\": \"out\",\n        \"other\": \"0x006a25a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9ff41\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f96b40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9ff4f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f9e3a0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x006a25a0\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0576\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\"
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
  "body_end": "00fa0008",
  "body_span_bytes": 281,
  "body_start": "00f9fef0",
  "callees": [
    "FUN_00f96b40",
    "Prop_GetPropValueBool",
    "Graphics::IShadowWorld::Get",
    "FUN_00f9e3a0",
    "FUN_0067ddd0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00f9fef0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "pEffectsRenderer",
      "storage": "register:00000000:4",
      "type": "void *"
    },
    {
      "name": "pIVar4",
      "storage": "register:00000000:4",
      "type": "IShadowWorld *"
    },
    {
      "name": "piVar5",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "uVar6",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "cVar2",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "iVar7",
      "storage": "Stack[-0x30]:4",
      "type": "int"
    }
  ],
  "locals_count": 10,
  "mode": "live",
  "name": "FUN_00f9fef0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xb9fef0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00f9fef0(void)",
  "size_bytes": 281,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00f9fef0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01490be8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01490c74"
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
    "reconstruction/staging/pkg-w2-00f9fef0/w2_00f9fef0.cpp",
    "reconstruction/staging/pkg-w2-00f9fef0/w2_00f9fef0_model_test.cpp",
    "reconstruction/staging/pkg-w2-00f9fef0/w2_00f9fef0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00f9fef0/00f9fef0.json"
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
  "openspore::reconstruction::pkg_w2_00f9fef0::Argument",
  "openspore::reconstruction::pkg_w2_00f9fef0::Receiver",
  "openspore::reconstruction::pkg_w2_00f9fef0::Word"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01490be8"
]
```

## Conflicts

```json
[]
```
