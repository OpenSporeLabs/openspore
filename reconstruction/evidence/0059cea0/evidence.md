# Evidence 0x0059cea0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `140f4b6de76779fdae1b816fd2031dff117c93d0b9d7a528dbc397f792e91d74`

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
      "name": "angle",
      "position": 2,
      "type": "float",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0c",
      "name": "applyNow",
      "position": 3,
      "type": "bool",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 12,
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
      "entry_ESP+0x4"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "bf3bf808199bc9e8da037c48501b56bee4031a5d30710dd462944967d3db1742",
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
    "ghidra_parameter_count": 4,
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
        "obs-0003",
        "obs-0008",
        "obs-0010"
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
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x0059cea0",
      "count": 5,
      "first_use": 0,
      "first_write_index": 13,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0059cea1",
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
      "at": "0x0059cea1",
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
      "at": "0x0059cea1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0059cea5",
      "count": 3,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x0059cea6",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x0059ceac",
      "count": 5,
      "first_use": 5,
      "first_write_index": 1,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ESP + 0xc],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x0059ceac",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0008",
      "index": 5,
      "key": 4,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP + 0xc],EAX",
      "resolved": true,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x0059ceb2",
      "count": 4,
      "first_use": 7,
      "first_write_index": null,
      "id": "obs-0009",
      "index": 7,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
  
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "editor_creature_walk_controller_set_target_angle_0059b2f0",
    "reconstructed": true,
    "va": "0x0059b2f0"
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
    "va": "0x00577e10"
  },
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
  "count": 35,
  "instructions": [
    {
      "address": "0059cea0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0059cea1",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0059cea5",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0059cea6",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "0059cea8",
      "instruction": "CMP dword ptr [EDI + 0x38],0x0"
    },
    {
      "address": "0059ceac",
      "instruction": "MOV dword ptr [ESP + 0xc],EAX"
    },
    {
      "address": "0059ceb0",
      "instruction": "JZ 0x0059cef3"
    },
    {
      "address": "0059ceb2",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0059ceb3",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "0059ceb7",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0059ceb8",
      "instruction": "LEA EDX,[ESP + 0xc]"
    },
    {
      "address": "0059cebc",
      "instruction": "LEA ESI,[EDI + 0x8]"
    },
    {
      "address": "0059cebf",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0059cec0",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0059cec2",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "0059cec7",
      "instruction": "ADD EDI,0xc"
    },
    {
      "address": "0059ceca",
      "instruction": "CMP dword ptr [EAX],EDI"
    },
    {
      "address": "0059cecc",
      "instruction": "JZ 0x0059cef2"
    },
    {
      "address": "0059cece",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "0059ced2",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0059ced3",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0059ced5",
      "instruction": "CALL 0x0059c740"
    },
    {
      "address": "0059ceda",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "0059cedc",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0059cede",
      "instruction": "JZ 0x0059cef2"
    },
    {
      "address": "0059cee0",
      "instruction": "MOV EDX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "0059cee4",
      "instruction": "FLD float ptr [ESP + 0x14]"
    },
    {
      "address": "0059cee8",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0059cee9",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0059ceea",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "0059ceed",
      "instruction": "CALL 0x0059b2f0"
    },
    {
      "address": "0059cef2",
      "instruction": "POP ESI"
    },
    {
      "address": "0059cef3",
      "instruction": "POP EDI"
    },
    {
      "address": "0059cef4",
      "instruction": "POP ECX"
    },
    {
      "address": "0059cef5",
      "instruction": "RET 0xc"
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
  "original_bytes": 10483,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this\": \"OpaqueAnimWorld * in ECX\",\n    \"return_register\": null,\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"creatureID\",\n        \"position\": 1,\n        \"type\": \"std::int32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"angle\",\n        \"position\": 2,\n        \"type\": \"float\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x0c\",\n        \"name\": \"applyNow\",\n        \"position\": 3,\n        \"type\": \"bool\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 12,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorCreatureController_Update_0059b4b0\",\n      \"va\": \"0x0059b4b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n      \"va\": \"0x0059cb10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n      \"va\": \"0x0059cf00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE8\",\n      \"score\": 9,\n      \"symbol\": \"editor_creature_walk_controller_set_target_angle_0059b2f0\",\n      \"va\": \"0x0059b2f0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 3,\n      \"symbol\": \"map_int_whatever_find\",\n      \"va\": \"0x00e5c780\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueEditorRuntime\",\n  \"cluster\": null,\n  \"confidence\": {\n    \"abi_and_cleanup\": \"high\",\n    \"body\": \"high\",\n    \"forward_order\": \"high\"\n  },\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"editor_creature_walk_controller_set_target_angle_0059b2f0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059b2f0\"\n      },\n      {\n        \"name\": \"map_int_EditorCreatureControllerPtr__get\",\n        \"reconstructed\": false,\n        \"va\": \"0x0059c740\"\n      },\n      {\n        \"name\": \"map_int_whatever_find\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5c780\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00577e10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00582fe0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00639350\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00578f29\",\n        \"direction\": \"in\",\n        \"other\": \"0x00577e10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00579043\",\n        \"direction\": \"in\",\n        \"other\": \"0x00577e10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005836ce\",\n        \"direction\": \"in\",\n        \"other\": \"0x00582fe0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058767f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00587270\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006396cd\",\n        \"direction\": \"i
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
  "body_end": "0059cef7",
  "body_span_bytes": 88,
  "body_start": "0059cea0",
  "callees": [
    "map_int_whatever_find",
    "Editor_CreatureWalkController_SetTargetAngle",
    "map_int_EditorCreatureControllerPtr__get"
  ],
  "callers": [
    "FUN_00639350",
    "Editors::cEditor::SetActiveMode",
    "FUN_00577e10",
    "Editors::cEditor::AddCreature"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0059cea0",
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
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "Editors::cEditorAnimWorld::SetTargetAngle",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 4,
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
      "name": "angle",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "float"
    },
    {
      "name": "applyNow",
      "ordinal": 3,
      "storage": "Stack[0x10]:1",
      "type": "bool"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x19cea0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Editors::cEditorAnimWorld::SetTargetAngle(cEditorAnimWorld * this, int creatureID, float angle, bool applyNow)",
  "size_bytes": 88,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0059cea0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "0058767f"
    },
    {
      "from": "005836ce"
    },
    {
      "from": "006396cd"
    },
    {
      "from": "00639800"
    },
    {
      "from": "00578f29"
    },
    {
      "from": "00579043"
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
    "reconstruction/metadata/pkg-editor-runtime-wave7/0059cea0.json"
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
    "Angle units and wrap domain of controller+0x44/+0x48",
    "Angle units and wrap domain of controller+0x44/+0x48; Injected at runtime through g_fixed_basis (OpaqueFixedBasis). The file image holds zeros at every one of these addresses, so the reconstruction never promotes a compiled-in value: normalize_epsilon models 0x015e590c/0x015e5910/0x015e5914, orientation models 0x015e5a0c/0x015e5a10/0x015e5a14 and projection models 0x015e5a88/0x015e5a8c/0x015e5a90. Every consumer is a gate until those words are observed at runtime.; Which editor command sites drive SetTargetAngle at runtime",
    "Injected at runtime through g_fixed_basis (OpaqueFixedBasis). The file image holds zeros at every one of these addresses, so the reconstruction never promotes a compiled-in value: normalize_epsilon models 0x015e590c/0x015e5910/0x015e5914, orientation models 0x015e5a0c/0x015e5a10/0x015e5a14 and projection models 0x015e5a88/0x015e5a8c/0x015e5a90. Every consumer is a gate until those words are observed at runtime.",
    "Which editor command sites drive SetTargetAngle at runtime"
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
  "bool",
  "float",
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
