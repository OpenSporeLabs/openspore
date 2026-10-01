# Evidence 0x00697a80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `37bb0282df45b7aa41ae857a0feaaed9422390f748ca26ac40069842f87c3579`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_receiver": "ECX OpaqueGameInput*",
  "ordinary_stack_arguments": [
    {
      "name": "vkCode",
      "offset": "ESP+4",
      "slot": 0,
      "type": "int32"
    },
    {
      "offset": "ESP+8",
      "slot": 1,
      "type": "KeyModifiers",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 8",
  "stack_cleanup_bytes": 8
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
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "2f05ea9306241069c0baa1b6ba87d111c43e2e17daf36925b8510bdc7159f5ed",
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
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0013"
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
        "obs-0004"
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
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0007"
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
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0007"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0013"
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
        "obs-0013"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0013"
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
      "at": "0x00697a80",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EDX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00697a80",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,ECX",
      "reg": "EDX",
      "write_kind": "reg"
    },
    {
      "at": "0x00697a82",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00697a82",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00697a82",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00697a8e",
      "count": 3,
      "first_use": 4,
      "first_write_index": 7,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00697a8f",
      "definite": true,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ECX",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x00697a94",
      "definite": true,
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,0x1",
      "reg": "ESI",
      "write_kind": "imm"
    },
    {
      "at": "0x00697a9b",
      "count": 4,
      "first_use": 9,
      "first_write_index": 5,
      "id": "obs-0009",
      "index": 9,
      "kind": "REG_READ",
      "raw": "SHR
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
    "va": "0x00585860"
  },
  {
    "name": "editor_input_00585890",
    "reconstructed": true,
    "va": "0x00585890"
  },
  {
    "name": "cell_mode_strategy_on_mouse_move_00e51010",
    "reconstructed": true,
    "va": "0x00e51010"
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
  "count": 17,
  "instructions": [
    {
      "address": "00697a80",
      "instruction": "MOV EDX,ECX"
    },
    {
      "address": "00697a82",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00697a86",
      "instruction": "CMP ECX,0xff"
    },
    {
      "address": "00697a8c",
      "instruction": "JA 0x00697aad"
    },
    {
      "address": "00697a8e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00697a8f",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "00697a91",
      "instruction": "AND ECX,0x1f"
    },
    {
      "address": "00697a94",
      "instruction": "MOV ESI,0x1"
    },
    {
      "address": "00697a99",
      "instruction": "SHL ESI,CL"
    },
    {
      "address": "00697a9b",
      "instruction": "SHR EAX,0x5"
    },
    {
      "address": "00697a9e",
      "instruction": "LEA EAX,[EDX + EAX*0x4]"
    },
    {
      "address": "00697aa1",
      "instruction": "MOV ECX,EDX"
    },
    {
      "address": "00697aa3",
      "instruction": "NOT ESI"
    },
    {
      "address": "00697aa5",
      "instruction": "AND dword ptr [EAX],ESI"
    },
    {
      "address": "00697aa7",
      "instruction": "CALL 0x006979c0"
    },
    {
      "address": "00697aac",
      "instruction": "POP ESI"
    },
    {
      "address": "00697aad",
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
  "original_bytes": 7122,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_receiver\": \"ECX OpaqueGameInput*\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"name\": \"vkCode\",\n        \"offset\": \"ESP+4\",\n        \"slot\": 0,\n        \"type\": \"int32\"\n      },\n      {\n        \"offset\": \"ESP+8\",\n        \"slot\": 1,\n        \"type\": \"KeyModifiers\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 8\",\n    \"stack_cleanup_bytes\": 8\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:KeyModifiers,OpaqueGameInput,int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 30,\n      \"symbol\": \"game_input_on_key_down_00697a50\",\n      \"va\": \"0x00697a50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:KeyModifiers,OpaqueGameInput,int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 30,\n      \"symbol\": \"cell_mode_strategy_on_key_down_00e818f0\",\n      \"va\": \"0x00e818f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput,int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 27,\n      \"symbol\": \"game_input_mouse_up_00697af0\",\n      \"va\": \"0x00697af0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 27,\n      \"symbol\": \"cell_mode_strategy_on_mouse_move_00e51010\",\n      \"va\": \"0x00e51010\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"simulator_game_input_manager_get_00b3d350\",\n      \"va\": \"0x00b3d350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 11,\n      \"symbol\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n      \"va\": \"0x00e5c0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 11,\n      \"symbol\": \"cell_mode_strategy_on_mouse_down_00e6c860\",\n      \"va\": \"0x00e6c860\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 11,\n      \"symbol\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n      \"va\": \"0x00e7d660\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueGameInput\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00585860\"\n      },\n      {\n        \"name\": \"editor_input_00585890\",\n        \"reconstructed\": true,\n        \"va\": \"0x00585890\"\n      },\n      {\n        \"name\": \"cell_mode_strategy_on_mouse_move_00e51010\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e51010\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00585873\",\n        \"direction\": \"in\",\n        \"other\": \"0x00585860\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005858a5\",\n        \"direction\": \"in\",\n        \"other\": \"0x00585890\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e51020\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e51010\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00697aa7\",\n        \"direction\": \"out\",\n        \"other\": \"0x006979c0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 3,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00585890\",\n      \"0x00e51010\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0195\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"game_input_on_key_up_00697a80\",\n  \"normalized_symbol\": \"game_input_on_key_up_00697a80\",\n  \"observed_mechanics\": [\n    \"{\\\"callback_order\\\": \\\"bit clear precedes 0x006979c0 refresh\\\", \\\"invalid_key_behavior\\\": \\\"negative signed values and values above 255 are treated as unsigned values above 255 and leave state unchanged\\\", \\\"modifier_behavior\\\": \\\"the incomin
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
  "body_end": "00697aaf",
  "body_span_bytes": 48,
  "body_start": "00697a80",
  "callees": [
    "FUN_006979c0"
  ],
  "callers": [
    "FUN_00585860",
    "Editors::cEditor::OnKeyUp",
    "App::cCellModeStrategy::OnMouseMove"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00697a80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "GameInput::OnKeyUp",
  "namespace": "GameInput",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "GameInput *"
    },
    {
      "name": "vkCode",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "modifiers",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "KeyModifiers"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x297a80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void GameInput::OnKeyUp(GameInput * this, int vkCode, KeyModifiers modifiers)",
  "size_bytes": 48,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00697a80",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 8,
  "xrefs": [
    {
      "from": "005858a5"
    },
    {
      "from": "00d204f0"
    },
    {
      "from": "00ef08cd"
    },
    {
      "from": "00f4eff0"
    },
    {
      "from": "00e00665"
    },
    {
      "from": "005a2146"
    },
    {
      "from": "00585873"
    },
    {
      "from": "00e51020"
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
  "file": "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-input-wave7/00697a80.json"
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
    "Observe receiver validity, key-domain inputs, and the native 0x006979c0 refresh state in the original input owner."
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
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "KeyModifiers",
  "OpaqueGameInput",
  "int32",
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
