# Evidence 0x004a88d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7c339cda171bf81827e519d7a02dbc741acd9dc175394ae51cc8b29f91870e41`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__cdecl",
  "hidden_receiver": "absent - the body never reads ECX and the callers never load one",
  "hidden_this_register": null,
  "ordinary_stack_argument_slots": 1,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "EAX is used only as the intermediate result of the first callee and as the pushed copy of the argument at 0x004a88db; it is dead on exit. No caller reads EAX after any of the recorded callsites.",
  "return_register": null,
  "return_semantics": "void",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x8",
      "name": "event_tag",
      "role": "forwarded as the value of the record key 0x03475381; every inspected callsite pushes a 32-bit hash-like literal, e.g. 0x00A03E74B2, 0x00C355901A, 0x00D2C7F386, 0x002570AE6D, 0x00677F1FB8",
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "0x004a88eb RET"
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
    "calling_convention": "__cdecl",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
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
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP"
    ],
    "stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
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
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "025b7990324559d084efa5597a6b7fe53534654bc5a95bcaccef2a88709805a0",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__cdecl",
    "candidate_conventions": [
      "__cdecl",
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
    "persisted_calling_convention": "__cdecl"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0012"
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
        "obs-0008"
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
        "obs-0012"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0012"
      ],
      "claim": "calling convention is __cdecl: the caller cleans the stack and at least one entry slot is read",
      "confidence": "INFERRED",
      "id": "C9",
      "value": "__cdecl"
    },
    {
      "based_on": [
        "obs-0012"
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
        "obs-0012"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0012"
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
      "at": "0x004a88d0",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x004a88d0",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": 8
    },
    {
      "at": "0x004a88d1",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x004a88d1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004a88d3",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x004a88d6",
      "id": "obs-0006",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00435e90",
      "target": "0x00435e90"
    },
    {
      "at": "0x004a88db",
      "count": 2,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x004a88dc",
      "base": "EBP",
      "disp": 8,
      "id": "obs-0008",
      "index": 5,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x004a88dc",
      "definite": true,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x004a88e0",
      "id": "obs-0010",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00435ed0",
      "target": "0x00435ed0"
    },
    {
      
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
    "va": "0x0043c710"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043cad0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573c00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00577580"
  },
  {
    "name": "editor_input_00588570",
    "reconstructed": true,
    "va": "0x00588570"
  },
  {
    "name": "editor_input_0058b650",
    "reconstructed": true,
    "va": "0x0058b650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00591690"
  },
  {
    "name": "Editors::cEditor::HandleMessage",
    "reconstructed": false,
    "va": "0x00591fa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005a63d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005b8fb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005bc0f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005bccc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005c3cb0"
  },
  {
    "name": "palette_select_category_005cb240",
    "reconstructed": true,
    "va": "0x005cb240"
  },
  {
    "name": "FUN_005dda30",
    "reconstructed": true,
    "va": "0x005dda30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005def30"
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
  "count": 12,
  "instructions": [
    {
      "address": "004a88d0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004a88d1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004a88d3",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "004a88d6",
      "instruction": "CALL 0x00435e90"
    },
    {
      "address": "004a88db",
      "instruction": "PUSH EAX"
    },
    {
      "address": "004a88dc",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004a88df",
      "instruction": "PUSH EAX"
    },
    {
      "address": "004a88e0",
      "instruction": "CALL 0x00435ed0"
    },
    {
      "address": "004a88e5",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "004a88e8",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004a88ea",
      "instruction": "POP EBP"
    },
    {
      "address": "004a88eb",
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
  "original_bytes": 15401,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__cdecl\",\n    \"hidden_receiver\": \"absent - the body never reads ECX and the callers never load one\",\n    \"hidden_this_register\": null,\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"EAX is used only as the intermediate result of the first callee and as the pushed copy of the argument at 0x004a88db; it is dead on exit. No caller reads EAX after any of the recorded callsites.\",\n    \"return_register\": null,\n    \"return_semantics\": \"void\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"EBP+0x8\",\n        \"name\": \"event_tag\",\n        \"role\": \"forwarded as the value of the record key 0x03475381; every inspected callsite pushes a 32-bit hash-like literal, e.g. 0x00A03E74B2, 0x00C355901A, 0x00D2C7F386, 0x002570AE6D, 0x00677F1FB8\",\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"0x004a88eb RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-15-EDITOR-SUPPORT\",\n      \"score\": 3,\n      \"symbol\": \"palette_select_category_005cb240\",\n      \"va\": \"0x005cb240\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005dda30\",\n      \"va\": \"0x005dda30\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"Editors_EditorUI_HandleMessage_005e0000\",\n      \"va\": \"0x005e0000\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_bake_probe_004bf770\",\n      \"va\": \"0x004bf770\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The three key/scope constants address a module that is not shipped in this installation, so the record payload cannot be read. This bounds the classification but does not block the body reconstruction.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043c710\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043cad0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00577580\"\n      },\n      {\n        \"name\": \"editor_input_00588570\",\n        \"reconstructed\": true,\n        \"va\": \"0x00588570\"\n      },\n      {\n        \"name\": \"editor_input_0058b650\",\n        \"reconstructed\": true,\n        \"va\": \"0x0058b650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00591690\"\n      },\n      {\n        \"name\": \"Editors::cEditor::HandleMessage\",\n        \"reconstructed\": false,\n        \"va\": \"0x00591fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005a63d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005b8fb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005bc0f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005bccc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005c3cb0\"\n      },\n      {\n        \"name\": \"palette_select_category_005cb240\",\n        \"reconstructed\": true,\n        \"va\": \"0x005cb240\"\n      },\n      {\n        \"name\": \"FUN_005dda30\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dda30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005def30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dfb40\"\n      },\n      {\n        \"name\": \"editor_query_dispatch_005dfd00\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dfd00\"\n      },\n      {\n        \"name\": \"Editors_EditorUI_HandleMessage_005e0000\",\n        \"reconstructed\
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
  "body_end": "004a88eb",
  "body_span_bytes": 28,
  "body_start": "004a88d0",
  "callees": [
    "FUN_00435e90",
    "FUN_00435ed0"
  ],
  "callers": [
    "FUN_005bccc0",
    "Editors::cEditor::OnMouseUp",
    "FUN_00577580",
    "FUN_0043cad0",
    "FUN_005a63d0",
    "FUN_005dfb40",
    "FUN_0043c710",
    "FUN_005dda30",
    "FUN_00573c00",
    "FUN_005b8fb0",
    "FUN_005def30",
    "FUN_005dfd00",
    "FUN_005bc0f0",
    "Editors::cEditor::OnMouseDown",
    "FUN_005cb240",
    "FUN_00591690",
    "Editors::cEditor::HandleMessage",
    "FUN_005c3cb0",
    "FUN_005e0000"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "004a88d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_004a88d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa88d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004a88d0(void)",
  "size_bytes": 28,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004a88d0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 39,
  "xrefs": [
    {
      "from": "0043cdea"
    },
    {
      "from": "0043c9fe"
    },
    {
      "from": "00573d2d"
    },
    {
      "from": "005dda72"
    },
    {
      "from": "0058b7a9"
    },
    {
      "from": "005a694d"
    },
    {
      "from": "005b93af"
    },
    {
      "from": "005bc3e6"
    },
    {
      "from": "005bc404"
    },
    {
      "from": "005bd455"
    },
    {
      "from": "005bd46c"
    },
    {
      "from": "005c3d51"
    },
    {
      "from": "005cb2ea"
    },
    {
      "from": "005e00fa"
    },
    {
      "from": "005e011a"
    },
    {
      "from": "005e01d4"
    },
    {
      "from": "005dfb8b"
    },
    {
      "from": "005dfd83"
    },
    {
      "from": "005dfdeb"
    },
    {
      "from": "005dfe12"
    },
    {
      "from": "005dfe87"
    },
    {
      "from": "005dfeb4"
    },
    {
      "from": "005dff18"
    },
    {
      "from": "005dff7a"
    },
    {
      "from": "00588758"
    },
    {
      "from": "00588806"
    },
    {
      "from": "005775a2"
    },
    {
      "from": "005932d7"
    },
    {
      "from": "00591834"
    },
    {
      "from": "00591a4f"
    },
    {
      "from": "00591ab7"
    },
    {
      "from": "005b3981"
    },
    {
      "from": "005b399f"
    },
    {
      "from": "005c9e34"
    },
    {
      "from": "005df026"
    },
    {
      "from": "005df058"
    },
    {
      "from": "005af90d"
    },
    {
      "from": "005b07c7"
    },
    {
      "from": "005b0dd2"
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
    "reconstruction/staging/wave13-pilot-dispatch-b00/editor_004a88d0.cpp",
    "reconstruction/staging/wave13-pilot-dispatch-b00/editor_004a88d0.hpp",
    "reconstruction/staging/wave13-pilot-dispatch-b00/editor_004a88d0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-dispatch-b00/004a88d0.json"
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
    "A runtime differential test is required to (a) observe the singleton being installed, (b) capture the concrete implementations behind slots +0x20, +0x38, +0x40 and +0x58, and (c) read the three key strings out of the sibling module once that module is available. Without (a) the static observation that the function is a no-op in the imported image says nothing about the shipping build.",
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
    "The undo/redo inference additionally requires observing a listener that reacts to the emitted record."
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
