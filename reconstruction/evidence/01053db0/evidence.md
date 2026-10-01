# Evidence 0x01053db0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7873fecaed9f37ddc25e1a878eac1f4ab8c59045adcdc63af21b188c62947492`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": [
    "__stdcall",
    "MSVC x86 virtual-member convention observed: the receiver is passed as the first stack argument and the callee pops it"
  ],
  "hidden_this": false,
  "hidden_this_register": null,
  "ordinary_stack_argument_slots": 1,
  "receiver_register": null,
  "ret_form": "RET 0x4",
  "return_register": [
    "EAX",
    "AL"
  ],
  "return_semantics": "Unconditional success. The result is independent of the owned beam target presence, of the gate word at +0x174, and of the relationship manager global.",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    "{'entry_offset': 'ESP+0x08 at the post-prologue ESP+0x04 slot after PUSH ESI', 'observed_use': 'Copied into ESI at 0x01053db1 by `mov esi, dword ptr [esp+0x8]` immediately after `push esi` at 0x01053db0. The same register is the base for every field access and is reloaded into ECX at 0x01053ddf.', 'position': 1, 'type': 'OpaqueBeamToolState *', 'width_bytes': 4}"
  ],
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
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "478c2d203220097f139c791d3f8be2c47ec2aaa791e5e3d4dce9dc7d935534a9",
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
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
    "persisted_calling_convention": "['__stdcall', 'MSVC x86 virtual-member convention observed: the receiver is passed as the first stack argument and the callee pops it']"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017"
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
        "obs-0003"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0007",
        "obs-0008"
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
        "obs-0005",
        "obs-0007",
        "obs-0008"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0017"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0017"
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
      "at": "0x01053db0",
      "count": 5,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x01053db1",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x01053db1",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x01053db1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01053db5",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x124]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01053dbf",
      "id": "obs-0006",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00cb3c70",
      "target": "0x00cb3c70"
    },
    {
      "at": "0x01053dd8",
      "count": 1,
      "first_use": 10,
      "first_write_index": 2,
      "id": "obs-0007",
      "index": 10,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "ECX"
    },
    {
      "at": "0x01053dd8",
      "definite": true,
      "id": "obs-0008",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "
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
"\n/* WARNING: Unknown calling convention */\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nbool Simulator__cDefaultBeamTool__func4Ch\n               (cDefaultBeamTool *this,cSpaceToolData *pTool,Vector3 *param_3)\n\n{\n  DefaultRefCounted__vftable *pDVar1;\n  char cVar2;\n  \n  if (this[0x18]._vftable1 != (DefaultRefCounted__vftable *)0x0) {\n    FUN_00cb3c70();\n    pDVar1 = this[0x18]._vftable1;\n    if (pDVar1 != (DefaultRefCounted__vftable *)0x0) {\n      this[0x18]._vftable1 = (DefaultRefCounted__vftable *)0x0;\n      (**(code **)(pDVar1->_virtual_dtor + 4))();\n    }\n  }\n  cVar2 = FUN_0104cd50();\n  if (cVar2 != '\\0') {\n    Simulator__cRelationshipManager__Get();\n    FUN_00b78860();\n  }\n  return true;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 23,
  "instructions": [
    {
      "address": "01053db0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01053db1",
      "instruction": "MOV ESI,dword ptr [ESP + 0x8]"
    },
    {
      "address": "01053db5",
      "instruction": "MOV ECX,dword ptr [ESI + 0x124]"
    },
    {
      "address": "01053dbb",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01053dbd",
      "instruction": "JZ 0x01053ddf"
    },
    {
      "address": "01053dbf",
      "instruction": "CALL 0x00cb3c70"
    },
    {
      "address": "01053dc4",
      "instruction": "MOV ECX,dword ptr [ESI + 0x124]"
    },
    {
      "address": "01053dca",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01053dcc",
      "instruction": "JZ 0x01053ddf"
    },
    {
      "address": "01053dce",
      "instruction": "MOV dword ptr [ESI + 0x124],0x0"
    },
    {
      "address": "01053dd8",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01053dda",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01053ddd",
      "instruction": "CALL EDX"
    },
    {
      "address": "01053ddf",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "01053de1",
      "instruction": "CALL 0x0104cd50"
    },
    {
      "address": "01053de6",
      "instruction": "POP ESI"
    },
    {
      "address": "01053de7",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "01053de9",
      "instruction": "JZ 0x01053df7"
    },
    {
      "address": "01053deb",
      "instruction": "CALL 0x00b3d3c0"
    },
    {
      "address": "01053df0",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01053df2",
      "instruction": "CALL 0x00b78860"
    },
    {
      "address": "01053df7",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "01053df9",
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
  "original_bytes": 11908,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": [\n      \"__stdcall\",\n      \"MSVC x86 virtual-member convention observed: the receiver is passed as the first stack argument and the callee pops it\"\n    ],\n    \"hidden_this\": false,\n    \"hidden_this_register\": null,\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": null,\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": [\n      \"EAX\",\n      \"AL\"\n    ],\n    \"return_semantics\": \"Unconditional success. The result is independent of the owned beam target presence, of the gate word at +0x174, and of the relationship manager global.\",\n    \"return_type\": \"std::uint8_t\",\n    \"return_width_bytes\": 1,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      \"{'entry_offset': 'ESP+0x08 at the post-prologue ESP+0x04 slot after PUSH ESI', 'observed_use': 'Copied into ESI at 0x01053db1 by `mov esi, dword ptr [esp+0x8]` immediately after `push esi` at 0x01053db0. The same register is the base for every field access and is reloaded into ECX at 0x01053ddf.', 'position': 1, 'type': 'OpaqueBeamToolState *', 'width_bytes': 4}\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x0149b810,vtable:0x0149b8b4\"\n      ],\n      \"package\": \"pkg-sim-toolevent-01053d50\",\n      \"score\": 10,\n      \"symbol\": \"sim_toolevent_slot8_fun_01053d50\",\n      \"va\": \"0x01053d50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No differential runtime corpus is available for this virtual, so the gate bit and the release ordering are static-only evidence.\",\n    \"Simulator::cDefaultBeamTool::OnMouseDown at 0x01053d00, the only other member carrying this this type, has an unusable decompilation and is not usable to corroborate the field layout.\",\n    \"The owning class of the dispatch slot is unresolved, so the function cannot be tied to a named interface override.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-core-systems\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x01053deb\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d3c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053df2\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b78860\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053dbf\",\n        \"direction\": \"out\",\n        \"other\": \"0x00cb3c70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053de1\",\n        \"direction\": \"out\",\n        \"other\": \"0x0104cd50\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0609\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"Simulator::cDefaultBeamTool::func4Ch\",\n  \"normalized_symbol\": \"Simulator::cDefaultBeamTool::func4Ch\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"servic
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
  "body_end": "01053dfb",
  "body_span_bytes": 76,
  "body_start": "01053db0",
  "callees": [
    "FUN_00cb3c70",
    "FUN_0104cd50",
    "Simulator::cRelationshipManager::Get",
    "FUN_00b78860"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01053db0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "cVar2",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "pDVar1",
      "storage": "unique:00017200:4",
      "type": "DefaultRefCounted__vftable *"
    },
    {
      "name": "param_3",
      "storage": "Stack[0xc]:4",
      "type": "Vector3 *"
    },
    {
      "name": "pTool",
      "storage": "Stack[0x8]:4",
      "type": "cSpaceToolData *"
    },
    {
      "name": "this",
      "storage": "Stack[0x4]:4",
      "type": "cDefaultBeamTool *"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "Simulator::cDefaultBeamTool::func4Ch",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cDefaultBeamTool *"
    },
    {
      "name": "pTool",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "cSpaceToolData *"
    },
    {
      "name": "param_3",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Vector3 *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0xc53db0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool Simulator::cDefaultBeamTool::func4Ch(cDefaultBeamTool * this, cSpaceToolData * pTool, Vector3 * param_3)",
  "size_bytes": 76,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01053db0",
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
  "xref_count": 3,
  "xrefs": [
    {
      "from": "0149b810"
    },
    {
      "from": "0149b900"
    },
    {
      "from": "0149ba30"
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
  "global:PASS"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cDefaultBeamTool__func4Ch.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cDefaultBeamTool__func4Ch.c",
    "reconstruction/staging/pkg-dfw-01053db0/dfw_01053db0.cpp",
    "reconstruction/staging/pkg-dfw-01053db0/dfw_01053db0_types.hpp",
    "reconstruction/staging/pkg-sim-beamtool-func4ch/beam_tool_func4ch.cpp",
    "reconstruction/staging/pkg-sim-beamtool-func4ch/beam_tool_func4ch.hpp",
    "reconstruction/staging/pkg-sim-beamtool-func4ch/beam_tool_func4ch_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-01053db0/01053db0.json",
    "reconstruction/metadata/pkg-sim-beamtool-func4ch/01053db0.json"
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueBeamTarget *",
  "OpaqueBeamToolState *",
  "const OpaqueBeamTargetVTable *",
  "std::uint32_t",
  "std::uint8_t",
  "void (__thiscall *)(OpaqueBeamTarget *)"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00b7d400",
  "vtable:0x01053dd8",
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
