# Evidence 0x0059cb10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `14353a02e653f2cf6b74fb93e92b34bf2c92466a9c9c5323caf3fc6d59730894`

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
      "name": "animationID",
      "position": 2,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
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
    "ret_form": "RET 0x8",
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "0e82c7a76938e2a07c7143da1ca72c22fe9c15b9b5333e53de6d4ed80ec46300",
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
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0025"
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
        "obs-0003",
        "obs-0009",
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
        "obs-0007",
        "obs-0010",
        "obs-0013",
        "obs-0024"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          56,
          60
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0007",
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
      "at": "0x0059cb10",
      "count": 6,
      "first_use": 0,
      "first_write_index": 13,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0059cb11",
      "count": 6,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x0059cb11",
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
      "at": "0x0059cb11",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0059cb15",
      "count": 7,
      "first_use": 2,
      "first_write_index": 22,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0059cb16",
      "count": 7,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x0059cb17",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x0059cb1d",
      "count": 4,
      "first_use": 6,
      "first_write_index": 1,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ESP + 0x10],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x0059cb1d",
      "base": "ESP",
      "d
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
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
  "count": 45,
  "instructions": [
    {
      "address": "0059cb10",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0059cb11",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0059cb15",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0059cb16",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0059cb17",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "0059cb19",
      "instruction": "CMP dword ptr [EDI + 0x38],0x0"
    },
    {
      "address": "0059cb1d",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "0059cb21",
      "instruction": "JZ 0x0059cb4e"
    },
    {
      "address": "0059cb23",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "0059cb27",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0059cb28",
      "instruction": "LEA EDX,[ESP + 0xc]"
    },
    {
      "address": "0059cb2c",
      "instruction": "LEA ESI,[EDI + 0x8]"
    },
    {
      "address": "0059cb2f",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0059cb30",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0059cb32",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "0059cb37",
      "instruction": "LEA ECX,[EDI + 0xc]"
    },
    {
      "address": "0059cb3a",
      "instruction": "CMP dword ptr [EAX],ECX"
    },
    {
      "address": "0059cb3c",
      "instruction": "JZ 0x0059cb4e"
    },
    {
      "address": "0059cb3e",
      "instruction": "LEA EDX,[ESP + 0x10]"
    },
    {
      "address": "0059cb42",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0059cb43",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0059cb45",
      "instruction": "CALL 0x0059c740"
    },
    {
      "address": "0059cb4a",
      "instruction": "MOV ESI,dword ptr [EAX]"
    },
    {
      "address": "0059cb4c",
      "instruction": "JMP 0x0059cb50"
    },
    {
      "address": "0059cb4e",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "0059cb50",
      "instruction": "CMP dword ptr [EDI + 0x3c],0x0"
    },
    {
      "address": "0059cb54",
      "instruction": "JZ 0x0059cb77"
    },
    {
      "address": "0059cb56",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "0059cb58",
      "instruction": "JZ 0x0059cb77"
    },
    {
      "address": "0059cb5a",
      "instruction": "MOV ECX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "0059cb5d",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0059cb5f",
      "instruction": "JZ 0x0059cb77"
    },
    {
      "address": "0059cb61",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "0059cb63",
      "instruction": "MOV EDI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "0059cb67",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0059cb6a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0059cb6c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0059cb6d",
      "instruction": "CALL EDX"
    },
    {
      "address": "0059cb6f",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0059cb70",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0059cb72",
      "instruction": "CALL 0x007cd950"
    },
    {
      "address": "0059cb77",
      "instruction": "POP EDI"
    },
    {
      "address": "0059cb78",
      "instruction": "POP ESI"
    },
    {
      "address": "0059cb79",
      "instruction": "POP ECX"
    },
    {
      "address": "0059cb7a",
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
  "original_bytes": 9974,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this\": \"OpaqueAnimWorld * in ECX\",\n    \"return_register\": null,\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"creatureID\",\n        \"position\": 1,\n        \"type\": \"std::int32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"animationID\",\n        \"position\": 2,\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorCreatureController_Update_0059b4b0\",\n      \"va\": \"0x0059b4b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n      \"va\": \"0x0059cea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n      \"va\": \"0x0059cf00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"editor_creature_walk_controller_set_target_angle_0059b2f0\",\n      \"va\": \"0x0059b2f0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 3,\n      \"symbol\": \"map_int_whatever_find\",\n      \"va\": \"0x00e5c780\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueEditorRuntime\",\n  \"cluster\": \"gameglobal-misc\",\n  \"confidence\": {\n    \"abi_and_cleanup\": \"high\",\n    \"body\": \"high\",\n    \"call_order\": \"high\",\n    \"independence\": \"high\",\n    \"publication_slot\": \"high\"\n  },\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"map_int_EditorCreatureControllerPtr__get\",\n        \"reconstructed\": false,\n        \"va\": \"0x0059c740\"\n      },\n      {\n        \"name\": \"map_int_whatever_find\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5c780\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00577e10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00582fe0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00579309\",\n        \"direction\": \"in\",\n        \"other\": \"0x00577e10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057932f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00577e10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057934e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00577e10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057936d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00577e10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00583734\",\n        \"direction\": \"in\",\n        \"other\": \"0x00582fe0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059cb45\",\n        \"direction\": \"out\",\n        \"other\": \"0x0059c740\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059cb72\",\n        \"direction\": \"out\",\n        \"other\": \"0x007cd950\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059cb32\",\n        \"direct
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
  "body_end": "0059cb7c",
  "body_span_bytes": 109,
  "body_start": "0059cb10",
  "callees": [
    "map_int_whatever_find",
    "FUN_007cd950",
    "map_int_EditorCreatureControllerPtr__get"
  ],
  "callers": [
    "FUN_00577e10",
    "Editors::cEditor::AddCreature"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0059cb10",
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
  "name": "EditorAnimWorld_PlayAnimation",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x19cb10",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined EditorAnimWorld_PlayAnimation(void)",
  "size_bytes": 109,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0059cb10",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "00583734"
    },
    {
      "from": "00579309"
    },
    {
      "from": "0057936d"
    },
    {
      "from": "0057932f"
    },
    {
      "from": "0057934e"
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
    "reconstruction/metadata/pkg-editor-runtime-wave7/0059cb10.json"
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
    "Interaction with the 0x38 and 0x3c gates at runtime",
    "The concrete creature vtable at controller+0x08 and the meaning of slot +4",
    "The concrete creature vtable at controller+0x08 and the meaning of slot +4; Whether controller+0x1c is a clip index, hash or resource id, and who reads it; Interaction with the 0x38 and 0x3c gates at runtime; The concrete implementation behind the 0x007cd950 publication port",
    "The concrete implementation behind the 0x007cd950 publication port",
    "Whether controller+0x1c is a clip index, hash or resource id, and who reads it"
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
  "std::int32_t",
  "std::uint32_t",
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
