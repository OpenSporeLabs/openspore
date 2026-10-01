# Evidence 0x0059b2f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `986f014f9791d0271d74cdb29e04688acd50d24b0bd93b02b2a2ceec31a3f151`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall with callee stack cleanup",
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_register": null,
  "return_width_bytes": 0,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "machine_type": "float",
      "normalized_name": "angle",
      "position": 1,
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "machine_type": "bool",
      "native_test": "low byte at ESP+0x08",
      "normalized_name": "apply_now",
      "position": 2,
      "width_bytes": 4
    }
  ],
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
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
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "slot_width_ambiguous: one entry slot is read at more than one width"
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
  "content_sha256": "3186f2872e47893231c50ddb4c7a91032bdf60c470b5104c1347352545f60807",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall with callee stack cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0032"
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
        "obs-0002",
        "obs-0006",
        "obs-0009",
        "obs-0013",
        "obs-0014"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0006",
        "obs-0009",
        "obs-0013",
        "obs-0014"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0020",
        "obs-0021",
        "obs-0022",
        "obs-0029"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          8,
          24,
          28,
          32,
          36,
          68,
          72
        ],
        "register": "ECX",
        "written_through": 6
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0020",
        "obs-0021",
        "obs-0022",
        "obs-0029",
        "obs-0032"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0032"
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
        "obs-0004"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x0059b2f0",
      "count": 13,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x0059b2f0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0059b2f0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "and_esp": null,
      "at": "0x0059b2f6",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0004",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x10",
  
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
    "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
    "reconstructed": true,
    "va": "0x0059cea0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062cc20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00638810"
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
  "count": 35,
  "instructions": [
    {
      "address": "0059b2f0",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x4]"
    },
    {
      "address": "0059b2f6",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "0059b2f9",
      "instruction": "CMP byte ptr [ESP + 0x18],0x0"
    },
    {
      "address": "0059b2fe",
      "instruction": "MOVSS dword ptr [ECX + 0x44],XMM0"
    },
    {
      "address": "0059b303",
      "instruction": "JZ 0x0059b37d"
    },
    {
      "address": "0059b305",
      "instruction": "FLD float ptr [ESP + 0x14]"
    },
    {
      "address": "0059b309",
      "instruction": "MOV EAX,dword ptr [ECX + 0x8]"
    },
    {
      "address": "0059b30c",
      "instruction": "FMUL float ptr [0x01471064]"
    },
    {
      "address": "0059b312",
      "instruction": "MOVSS dword ptr [ECX + 0x48],XMM0"
    },
    {
      "address": "0059b317",
      "instruction": "MOVSS XMM0,dword ptr [0x015e5a0c]"
    },
    {
      "address": "0059b31f",
      "instruction": "MOVSS XMM1,dword ptr [0x015e5a10]"
    },
    {
      "address": "0059b327",
      "instruction": "FLD ST0"
    },
    {
      "address": "0059b329",
      "instruction": "MOVSS XMM2,dword ptr [0x015e5a14]"
    },
    {
      "address": "0059b331",
      "instruction": "FSIN"
    },
    {
      "address": "0059b333",
      "instruction": "ADD EAX,0x10"
    },
    {
      "address": "0059b336",
      "instruction": "FSTP float ptr [ESP + 0x18]"
    },
    {
      "address": "0059b33a",
      "instruction": "MOVSS XMM3,dword ptr [ESP + 0x18]"
    },
    {
      "address": "0059b340",
      "instruction": "FCOS"
    },
    {
      "address": "0059b342",
      "instruction": "MULSS XMM0,XMM3"
    },
    {
      "address": "0059b346",
      "instruction": "MULSS XMM1,XMM3"
    },
    {
      "address": "0059b34a",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "0059b34f",
      "instruction": "MOV ECX,dword ptr [ESP]"
    },
    {
      "address": "0059b352",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "0059b354",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM1"
    },
    {
      "address": "0059b35a",
      "instruction": "MOV EDX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "0059b35e",
      "instruction": "MULSS XMM2,XMM3"
    },
    {
      "address": "0059b362",
      "instruction": "MOV dword ptr [EAX + 0x4],EDX"
    },
    {
      "address": "0059b365",
      "instruction": "MOVSS dword ptr [ESP + 0x8],XMM2"
    },
    {
      "address": "0059b36b",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0059b36f",
      "instruction": "MOV dword ptr [EAX + 0x8],ECX"
    },
    {
      "address": "0059b372",
      "instruction": "FSTP float ptr [ESP + 0xc]"
    },
    {
      "address": "0059b376",
      "instruction": "MOV EDX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "0059b37a",
      "instruction": "MOV dword ptr [EAX + 0xc],EDX"
    },
    {
      "address": "0059b37d",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "0059b380",
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
  "original_bytes": 7380,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall with callee stack cleanup\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": null,\n    \"return_width_bytes\": 0,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"machine_type\": \"float\",\n        \"normalized_name\": \"angle\",\n        \"position\": 1,\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"machine_type\": \"bool\",\n        \"native_test\": \"low byte at ESP+0x08\",\n        \"normalized_name\": \"apply_now\",\n        \"position\": 2,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 9,\n      \"symbol\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n      \"va\": \"0x0059cea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 6,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 6,\n      \"symbol\": \"EditorCreatureController_Update_0059b4b0\",\n      \"va\": \"0x0059b4b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 6,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 6,\n      \"symbol\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n      \"va\": \"0x0059cb10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 6,\n      \"symbol\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n      \"va\": \"0x0059cf00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"cursor_buffer_emit_0041e8b0\",\n      \"va\": \"0x0041e8b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"skin_painter_state_setup_00506590\",\n      \"va\": \"0x00506590\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCreatureWalkController\",\n  \"cluster\": \"gameglobal-misc\",\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059cea0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062cc20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00638810\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0059ceed\",\n        \"direction\": \"in\",\n        \"other\": \"0x0059cea0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0062cd14\",\n        \"direction\": \"in\",\n        \"other\": \"0x0062cc20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0063886a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00638810\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 3,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [\n      {\n        \"call_site\": \"0x0059ceed\",\n        \"function\": \"Editors::cEditorAnimWorld::SetTargetAngle\",\n        \"va\": \"0x0059cea0\"\n      },\n      {\n        \"call_site\": \"0x0062cd14\",\n        \"function\": \"FUN_0062cc20\",\n        \"va\": \"0x0062cc20\"\n      },\n      {\n        \"call_site\": \"0x0063886a\",\n        \"function\": \"FUN_00638810\",\n        \"va\": \"0x00638810\"\n      }\n    ],\n    \"nearby_reconstructed\": [\n      \"0x0059cea0\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0087\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"Editor_CreatureWalkController_SetTargetAngle\",\n  \"normalized_symbol\": \"editor_creature_walk_controller_set_target_angle_0059b2f0\",\n  \"observed_mechanics\": [\n    \"{}\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-EDITOR-RUNTIME-WAVE8\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-EDITOR-RUNTIME-WAVE8\",\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": \"PKG-EDITOR-RUNTIME-WAVE8\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved_after_parallel_review\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"required\"\n    ],\n    \"validated\": 0\n  
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
  "body_end": "0059b382",
  "body_span_bytes": 147,
  "body_start": "0059b2f0",
  "callees": [],
  "callers": [
    "Editors::cEditorAnimWorld::SetTargetAngle",
    "FUN_0062cc20",
    "FUN_00638810"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0059b2f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "Editor_CreatureWalkController_SetTargetAngle",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x19b2f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined Editor_CreatureWalkController_SetTargetAngle(void)",
  "size_bytes": 147,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0059b2f0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "0059ceed"
    },
    {
      "from": "0062cd14"
    },
    {
      "from": "0063886a"
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
  "file": "src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8.cpp",
  "files": [
    "src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8.cpp",
    "src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8.hpp",
    "src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-runtime-wave8/0059b2f0.json"
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
    "required"
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
  "OpaqueCreatureWalkController",
  "OpaqueCreatureWalkController*"
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
