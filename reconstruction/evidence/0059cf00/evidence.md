# Evidence 0x0059cf00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7f981d398e91fe5185b1e14be40a9e46bc0bd758fdb049ea911cec2a8f46fc7b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this": "OpaqueAnimWorld * in ECX",
  "return_register": null,
  "return_type": "void",
  "return_width_bytes": 0,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "creatureID",
      "position": 1,
      "type": "std::int32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "position",
      "position": 2,
      "type": "Vector3 (12 bytes, by value, occupies three argument slots)",
      "width_bytes": 12
    },
    {
      "entry_offset": "ESP+0x14",
      "name": "applyNow",
      "position": 3,
      "type": "bool",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x18",
      "name": "ignoreZ",
      "position": 4,
      "type": "bool",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 24,
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
        "size_inferred": true,
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x18",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
    "stack_cleanup_bytes": 24,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x18"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 24,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x18",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "5c30786d9c97cbc1ed278e45b1d994ea0933c0a3d6992bb323db5fded15602ac",
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
    "ghidra_parameter_count": 5,
    "persisted": "agrees",
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
        "obs-0025"
      ],
      "claim": "the callee pops 24 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 24,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0008",
        "obs-0010",
        "obs-0017",
        "obs-0019"
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
        "obs-0001",
        "obs-0006",
        "obs-0010",
        "obs-0013",
        "obs-0024"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          56
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0006",
        "obs-0010",
        "obs-0013",
        "obs-0024",
        "obs-0025"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0025"
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
        "obs-0025"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0025"
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
      "at": "0x0059cf00",
      "count": 4,
      "first_use": 0,
      "first_write_index": 13,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0059cf01",
      "count": 8,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x0059cf01",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0059cf01",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "EditorCreatureController_SetTargetPosition_0059b0f0",
    "reconstructed": true,
    "va": "0x0059b0f0"
  },
  {
    "name": "map_int_EditorCreatureControllerPtr__get",
    "reconstructed": false,
    "va": "0x0059c740"
  },
  {
    "name": "map_int_whatever_find",
    "reconstructed": true,
    "va": "0x00e5c780"
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
    "va": "0x00582fe0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00587270"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059d240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00639350"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00587270",
      "0x0059d840",
      "0x0059d8b0",
      "0x00587270",
      "0x0059d8b0",
      "0x0059d840",
      "0x0067cae0",
      "0x00b31da0",
      "0x0059ca70",
      "0x0059cac0",
      "0x00b321e0",
      "0x00b32330",
      "0x00b32560",
      "0x0059cea0",
      "0x0059cf00",
      "0x00b63980"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:3",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00571f80",
      "0x00571f80",
      "0x0067cae0",
      "0x00a20670",
      "0x00571f80",
      "0x00572070",
      "0x00572020",
      "0x0059ca70",
      "0x0059cac0",
      "0x0059cea0",
      "0x0059cf00",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x0059c6e0"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:9",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
  "count": 36,
  "instructions": [
    {
      "address": "0059cf00",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0059cf01",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0059cf05",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0059cf06",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "0059cf08",
      "instruction": "CMP dword ptr [EDI + 0x38],0x0"
    },
    {
      "address": "0059cf0c",
      "instruction": "MOV dword ptr [ESP + 0xc],EAX"
    },
    {
      "address": "0059cf10",
      "instruction": "JZ 0x0059cf55"
    },
    {
      "address": "0059cf12",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0059cf13",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "0059cf17",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0059cf18",
      "instruction": "LEA EDX,[ESP + 0xc]"
    },
    {
      "address": "0059cf1c",
      "instruction": "LEA ESI,[EDI + 0x8]"
    },
    {
      "address": "0059cf1f",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0059cf20",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0059cf22",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "0059cf27",
      "instruction": "ADD EDI,0xc"
    },
    {
      "address": "0059cf2a",
      "instruction": "CMP dword ptr [EAX],EDI"
    },
    {
      "address": "0059cf2c",
      "instruction": "JZ 0x0059cf54"
    },
    {
      "address": "0059cf2e",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "0059cf32",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0059cf33",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0059cf35",
      "instruction": "CALL 0x0059c740"
    },
    {
      "address": "0059cf3a",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "0059cf3c",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0059cf3e",
      "instruction": "JZ 0x0059cf54"
    },
    {
      "address": "0059cf40",
      "instruction": "MOV EDX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "0059cf44",
      "instruction": "MOV EAX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "0059cf48",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0059cf49",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0059cf4a",
      "instruction": "LEA EDX,[ESP + 0x1c]"
    },
    {
      "address": "0059cf4e",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0059cf4f",
      "instruction": "CALL 0x0059b0f0"
    },
    {
      "address": "0059cf54",
      "instruction": "POP ESI"
    },
    {
      "address": "0059cf55",
      "instruction": "POP EDI"
    },
    {
      "address": "0059cf56",
      "instruction": "POP ECX"
    },
    {
      "address": "0059cf57",
      "instruction": "RET 0x18"
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
  "original_bytes": 10300,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this\": \"OpaqueAnimWorld * in ECX\",\n    \"return_register\": null,\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"creatureID\",\n        \"position\": 1,\n        \"type\": \"std::int32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"position\",\n        \"position\": 2,\n        \"type\": \"Vector3 (12 bytes, by value, occupies three argument slots)\",\n        \"width_bytes\": 12\n      },\n      {\n        \"entry_offset\": \"ESP+0x14\",\n        \"name\": \"applyNow\",\n        \"position\": 3,\n        \"type\": \"bool\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x18\",\n        \"name\": \"ignoreZ\",\n        \"position\": 4,\n        \"type\": \"bool\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 24,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 27,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorCreatureController_Update_0059b4b0\",\n      \"va\": \"0x0059b4b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n      \"va\": \"0x0059cb10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n      \"va\": \"0x0059cea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"editor_creature_walk_controller_set_target_angle_0059b2f0\",\n      \"va\": \"0x0059b2f0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 3,\n      \"symbol\": \"map_int_whatever_find\",\n      \"va\": \"0x00e5c780\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueEditorRuntime\",\n  \"cluster\": null,\n  \"confidence\": {\n    \"abi_and_cleanup\": \"high\",\n    \"body\": \"high\",\n    \"by_value_contract\": \"high\",\n    \"forward_order\": \"high\"\n  },\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059b0f0\"\n      },\n      {\n        \"name\": \"map_int_EditorCreatureControllerPtr__get\",\n        \"reconstructed\": false,\n        \"va\": \"0x0059c740\"\n      },\n      {\n        \"name\": \"map_int_whatever_find\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5c780\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00582fe0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00639350\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0058362e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00582fe0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00583831\",\n        \"direction\": \"in\",\n        \"other\": \"0x00582fe0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005838b4\",\n        \"direction\": \"in\",\n        \"other\": \"0x00582fe0\",\n        \"reference_type\": \"direct-c
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
  "body_end": "0059cf59",
  "body_span_bytes": 90,
  "body_start": "0059cf00",
  "callees": [
    "map_int_whatever_find",
    "map_int_EditorCreatureControllerPtr__get",
    "Editors::EditorCreatureController::SetTargetPosition"
  ],
  "callers": [
    "FUN_00639350",
    "Editors::cEditor::SetActiveMode",
    "FUN_0059d240",
    "Editors::cEditor::AddCreature"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0059cf00",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "Editors::cEditorAnimWorld::SetTargetPosition",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 5,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cEditorAnimWorld *"
    },
    {
      "name": "creatureID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "position",
      "ordinal": 2,
      "storage": "Stack[0xc]:12",
      "type": "Vector3"
    },
    {
      "name": "applyNow",
      "ordinal": 3,
      "storage": "Stack[0x18]:1",
      "type": "bool"
    },
    {
      "name": "ignoreZ",
      "ordinal": 4,
      "storage": "Stack[0x1c]:1",
      "type": "bool"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x19cf00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Editors::cEditorAnimWorld::SetTargetPosition(cEditorAnimWorld * this, int creatureID, Vector3 position, bool applyNow, bool ignoreZ)",
  "size_bytes": 90,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0059cf00",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 8,
  "xrefs": [
    {
      "from": "005873cc"
    },
    {
      "from": "0058362e"
    },
    {
      "from": "00583831"
    },
    {
      "from": "005838b4"
    },
    {
      "from": "0059d2c2"
    },
    {
      "from": "00639541"
    },
    {
      "from": "00639624"
    },
    {
      "from": "0063aa36"
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
  "file": "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp",
    "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.hpp",
    "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-runtime-wave7/0059cf00.json"
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
    "Coordinate space and units of the forwarded Vector3",
    "Coordinate space and units of the forwarded Vector3; Whether ignoreZ is ever set in practice by editor input paths; Interaction between applyNow and the ground-follow raycast in the target",
    "Interaction between applyNow and the ground-follow raycast in the target",
    "Whether ignoreZ is ever set in practice by editor input paths"
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
  "OpaqueEditorRuntime",
  "Vector3 (12 bytes, by value, occupies three argument slots)",
  "bool",
  "std::int32_t",
  "void"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x00587270",
      "0x0059d840",
      "0x0059d8b0",
      "0x00587270",
      "0x0059d8b0",
      "0x0059d840",
      "0x0067cae0",
      "0x00b31da0",
      "0x0059ca70",
      "0x0059cac0",
      "0x00b321e0",
      "0x00b32330",
      "0x00b32560",
      "0x0059cea0",
      "0x0059cf00",
      "0x00b63980"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:3",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00571f80",
      "0x00571f80",
      "0x0067cae0",
      "0x00a20670",
      "0x00571f80",
      "0x00572070",
      "0x00572020",
      "0x0059ca70",
      "0x0059cac0",
      "0x0059cea0",
      "0x0059cf00",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840",
      "0x00e63560",
      "0x0059c6e0"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:9",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
