# Evidence 0x00b515e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2dcc9fe5430d1d72c722a6278ede0087af718b56a0a09bcc15f8c770ea69584c`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "read",
  "hidden_this_register": "ECX, consumed by 0x00b515e8 MOV EDI,ECX and used only at 0x00b51638 to write the byte latch at EDI+0x30. ECX is clobbered by the virtual call at 0x00b51615 and reloaded at 0x00b51617.",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "The body never writes EAX outside the two SETNZ AL instructions at 0x00b51601 and 0x00b5161d, whose results feed TEST AL,AL immediately and are dead by 0x00b51606 / 0x00b51620. Every inspected callsite discards EAX: at 0x00fdc31c the next instruction is a fresh CALL, at 0x00b3d7a8 the next instruction reloads ECX from ESI, at 0x00fe105e the next instruction is CALL 0x00b3d350. The decompiler agrees: `void __fastcall FUN_00b515e0(int param_1)`.",
  "return_register": null,
  "return_semantics": "no value; side effects only",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EDI",
    "ESI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00b5163d"
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
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EDI",
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
  "content_sha256": "0cd0d75a5470585f1114ec56fcefa72b033bdf5c5a37fe8bf380427402c19055",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0018"
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
        "obs-0010"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          48
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0010",
        "obs-0018"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0018"
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
        "obs-0018"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018"
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
      "at": "0x00b515e7",
      "count": 2,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0001",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b515e8",
      "count": 2,
      "first_use": 2,
      "first_write_index": 15,
      "id": "obs-0002",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b515e8",
      "definite": true,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b515ec",
      "definite": true,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167ecd4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b515f5",
      "count": 3,
      "first_use": 7,
      "first_write_index": 8,
      "id": "obs-0005",
      "index": 7,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b515f6",
      "count": 4,
      "first_use": 8,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 8,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [EAX + 0x1c]",
      "reg": "EAX"
    },
    {
      "at": "0x00b515f6",
      "definite": true,
      "id": "obs-0007",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [EAX + 0x1c]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b515f9",
      "id": "obs-0008",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d350",
      "target": "0x00b3d350"
    },
    {
      "at": "0x00b51608",
      "id": "obs-0009",
      "index": 14,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d350",
      "target": "0x00b3d350"
    },
    {
      "at": "0x00b5160d",
      "definite": true,
      "id": "obs-0010",
      "index": 15,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EAX + 0x24]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b51612",
      "definite": true,
      "id": "obs-0011",
      "index": 17,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0xc]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b51615",
      "count": 1,
      "first_use": 18,
      "first_write_index": 17,
      "id": "obs-0012",
      "index": 18,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00b51615",
      "base": "EDX",
      "disp": null,
      "id": "obs-0013",
      "index": 18,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00b51624",
      "id": "obs-0014",
      "index": 24,
      "kind
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "simulator_game_input_manager_get_00b3d350",
    "reconstructed": true,
    "va": "0x00b3d350"
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
    "va": "0x00b3d7a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ed4b70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f44dd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fdc240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fdc710"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fdc800"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fe0160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fe0e10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fe0f40"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 32,
  "instructions": [
    {
      "address": "00b515e0",
      "instruction": "CMP dword ptr [0x0167ecd0],0x0"
    },
    {
      "address": "00b515e7",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b515e8",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00b515ea",
      "instruction": "JZ 0x00b5163c"
    },
    {
      "address": "00b515ec",
      "instruction": "MOV EAX,[0x0167ecd4]"
    },
    {
      "address": "00b515f1",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b515f3",
      "instruction": "JZ 0x00b51633"
    },
    {
      "address": "00b515f5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b515f6",
      "instruction": "MOV ESI,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "00b515f9",
      "instruction": "CALL 0x00b3d350"
    },
    {
      "address": "00b515fe",
      "instruction": "CMP dword ptr [ESI + 0x34],EAX"
    },
    {
      "address": "00b51601",
      "instruction": "SETNZ AL"
    },
    {
      "address": "00b51604",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00b51606",
      "instruction": "JNZ 0x00b51624"
    },
    {
      "address": "00b51608",
      "instruction": "CALL 0x00b3d350"
    },
    {
      "address": "00b5160d",
      "instruction": "MOV ECX,dword ptr [EAX + 0x24]"
    },
    {
      "address": "00b51610",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00b51612",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00b51615",
      "instruction": "CALL EDX"
    },
    {
      "address": "00b51617",
      "instruction": "MOV ECX,dword ptr [ESI + 0x3c]"
    },
    {
      "address": "00b5161a",
      "instruction": "CMP ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00b5161d",
      "instruction": "SETNZ AL"
    },
    {
      "address": "00b51620",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00b51622",
      "instruction": "JZ 0x00b51629"
    },
    {
      "address": "00b51624",
      "instruction": "CALL 0x00b4f7f0"
    },
    {
      "address": "00b51629",
      "instruction": "CMP dword ptr [0x0167ecd4],0x0"
    },
    {
      "address": "00b51630",
      "instruction": "POP ESI"
    },
    {
      "address": "00b51631",
      "instruction": "JNZ 0x00b5163c"
    },
    {
      "address": "00b51633",
      "instruction": "CALL 0x00b512f0"
    },
    {
      "address": "00b51638",
      "instruction": "MOV byte ptr [EDI + 0x30],0x1"
    },
    {
      "address": "00b5163c",
      "instruction": "POP EDI"
    },
    {
      "address": "00b5163d",
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
  "original_bytes": 11164,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"read\",\n    \"hidden_this_register\": \"ECX, consumed by 0x00b515e8 MOV EDI,ECX and used only at 0x00b51638 to write the byte latch at EDI+0x30. ECX is clobbered by the virtual call at 0x00b51615 and reloaded at 0x00b51617.\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"The body never writes EAX outside the two SETNZ AL instructions at 0x00b51601 and 0x00b5161d, whose results feed TEST AL,AL immediately and are dead by 0x00b51606 / 0x00b51620. Every inspected callsite discards EAX: at 0x00fdc31c the next instruction is a fresh CALL, at 0x00b3d7a8 the next instruction reloads ECX from ESI, at 0x00fe105e the next instruction is CALL 0x00b3d350. The decompiler agrees: `void __fastcall FUN_00b515e0(int param_1)`.\",\n    \"return_register\": null,\n    \"return_semantics\": \"no value; side effects only\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET at 0x00b5163d\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"simulator_game_input_manager_get_00b3d350\",\n      \"va\": \"0x00b3d350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"simulator_game_input_manager_get_00b3d350\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d350\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b3d7a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ed4b70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f44dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdc240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdc710\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdc800\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe0160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe0e10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe0f40\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b3d7a3\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b3d7a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ed4bd7\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ed4b70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f44f66\",\n        \"direction\": \"in\",\n        \"other\": \"0x00f44dd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fdc31c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fdc240\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fdc74c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fdc710\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fdc864\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fdc800\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fe03b4\",\n        \"d
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
  "body_end": "00b5163d",
  "body_span_bytes": 94,
  "body_start": "00b515e0",
  "callees": [
    "FUN_00b4f7f0",
    "Simulator::cGameInputManager::Get",
    "FUN_00b512f0"
  ],
  "callers": [
    "FUN_00fe0e10",
    "FUN_00fdc240",
    "FUN_00b3d7a0",
    "FUN_00f44dd0",
    "FUN_00fdc800",
    "FUN_00fdc710",
    "FUN_00fe0f40",
    "FUN_00fe0160",
    "FUN_00ed4b70"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b515e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b515e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7515e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b515e0(void)",
  "size_bytes": 94,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b515e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "00b3d7a3"
    },
    {
      "from": "00fe0e66"
    },
    {
      "from": "00f44f66"
    },
    {
      "from": "00fdc31c"
    },
    {
      "from": "00fdc74c"
    },
    {
      "from": "00fdc864"
    },
    {
      "from": "00fe03b4"
    },
    {
      "from": "00fe105e"
    },
    {
      "from": "00b4cfa2"
    },
    {
      "from": "00ed4bd7"
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
    "reconstruction/staging/wave13-w1-core-b16/b515e0_cached_object_validate.cpp",
    "reconstruction/staging/wave13-w1-core-b16/b515e0_cached_object_validate.hpp",
    "reconstruction/staging/wave13-w1-core-b16/b515e0_cached_object_validate_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b16/00b515e0.json"
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
  "gates": [
    "A runtime differential must confirm that the cGameInputManager pointer stored at +0x34 is really compared by identity and not rewritten behind the cached object's back between calls, which would make the check vacuous.",
    "A runtime trace must show whether [this + 0x30] is ever read, and by which code, before the latch can be named.",
    "A runtime trace with a concrete receiver is required to resolve the slot +0x0c callee: the call must be sampled with ECX holding the sub-object and the callee address recorded.",
    "Every claim here is static. No original-process trace has been captured for 0x00b515e0, and the Cell stage has never been entered in any recorded run."
  ],
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
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "unresolved"
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
