# Evidence 0x00b3d850

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2c8f51a803f69d4c2db519750b2898bc1efff9561b559a9e7039f8cc79e2d839`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX, read at 0x00b3d851; ECX is then reloaded at 0x00b3d860 with self+0x8 for the port call",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x00b3d86c MOV EAX,ESI is the only write to EAX and it is reached by both exits - the exhaustion path via 0x00b3d85b JZ 0x00b3d86c and the accepted path by falling through - so the return is unconditionally the receiver and the callee's AL result is never propagated.",
  "return_register": "EAX",
  "return_semantics": "the receiver itself, on both exits",
  "return_type": "OpaqueCursor*",
  "return_width_bytes": 4,
  "saved_registers": [
    {
      "pop": "0x00b3d86e",
      "push": "0x00b3d850",
      "register": "ESI"
    }
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00b3d86f"
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
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "baff82757d9d679352c3439b91816f93f1e1905157ed471ca2f14d7a0ff81fe5",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0008"
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
        "obs-0003"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          4
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0008"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0008"
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
        "obs-0008"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008"
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
      "at": "0x00b3d850",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b3d851",
      "count": 2,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b3d851",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b3d856",
      "definite": true,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d85d",
      "count": 2,
      "first_use": 6,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x00b3d863",
      "id": "obs-0006",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c02600",
      "target": "0x00c02600"
    },
    {
      "at": "0x00b3d86e",
      "id": "obs-0007",
      "index": 13,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b3d86f",
      "form": "RET",
      "id": "obs-0008",
      "imm": null,
      "index": 14,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 15,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "INFERRED",
    "distinct_offsets": 2,
    "max_offset": 4,
    "offsets": [
      0,
      4
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-ALIAS",
    "written_through": 1
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence":
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
    "va": "0x00b41a40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c07480"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d35190"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d41a70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d4b860"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d522c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d66600"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d6ef50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d6f090"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d6f1c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d8b910"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d8bb70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d8c3e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d8c850"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d8c9c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d8cab0"
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
  "count": 15,
  "instructions": [
    {
      "address": "00b3d850",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b3d851",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b3d853",
      "instruction": "ADD dword ptr [ESI],0x4"
    },
    {
      "address": "00b3d856",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00b3d858",
      "instruction": "CMP EAX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00b3d85b",
      "instruction": "JZ 0x00b3d86c"
    },
    {
      "address": "00b3d85d",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00b3d85f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b3d860",
      "instruction": "LEA ECX,[ESI + 0x8]"
    },
    {
      "address": "00b3d863",
      "instruction": "CALL 0x00c02600"
    },
    {
      "address": "00b3d868",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00b3d86a",
      "instruction": "JZ 0x00b3d853"
    },
    {
      "address": "00b3d86c",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00b3d86e",
      "instruction": "POP ESI"
    },
    {
      "address": "00b3d86f",
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
  "original_bytes": 12509,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX, read at 0x00b3d851; ECX is then reloaded at 0x00b3d860 with self+0x8 for the port call\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x00b3d86c MOV EAX,ESI is the only write to EAX and it is reached by both exits - the exhaustion path via 0x00b3d85b JZ 0x00b3d86c and the accepted path by falling through - so the return is unconditionally the receiver and the callee's AL result is never propagated.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"the receiver itself, on both exits\",\n    \"return_type\": \"OpaqueCursor*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      {\n        \"pop\": \"0x00b3d86e\",\n        \"push\": \"0x00b3d850\",\n        \"register\": \"ESI\"\n      }\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET at 0x00b3d86f\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b41a40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c07480\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d35190\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d41a70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d4b860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d522c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d66600\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d6ef50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d6f090\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d6f1c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d8b910\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d8bb70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d8c3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d8c850\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d8c9c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d8cab0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d8d300\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00da4400\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b41a66\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b41a40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c07ce6\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c07480\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c07ff7\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c07480
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
  "body_end": "00b3d86f",
  "body_span_bytes": 32,
  "body_start": "00b3d850",
  "callees": [
    "FUN_00c02600"
  ],
  "callers": [
    "FUN_00d66600",
    "FUN_00d8bb70",
    "FUN_00b41a40",
    "FUN_00d35190",
    "FUN_00d6f090",
    "FUN_00d41a70",
    "FUN_00d8c850",
    "FUN_00d8d300",
    "FUN_00d8c9c0",
    "FUN_00d522c0",
    "FUN_00da4400",
    "FUN_00d8cab0",
    "FUN_00d6ef50",
    "FUN_00c07480",
    "FUN_00d6f1c0",
    "FUN_00d8c3e0",
    "FUN_00d4b860",
    "FUN_00d8b910"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00b3d850",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b3d850",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x73d850",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b3d850(void)",
  "size_bytes": 32,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d850",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 24,
  "xrefs": [
    {
      "from": "00b41a66"
    },
    {
      "from": "00c07ce6"
    },
    {
      "from": "00c07ff7"
    },
    {
      "from": "00d41ad5"
    },
    {
      "from": "00d5241b"
    },
    {
      "from": "00d52ae5"
    },
    {
      "from": "00d4b8d3"
    },
    {
      "from": "00d6666b"
    },
    {
      "from": "00d6efce"
    },
    {
      "from": "00d6f0d9"
    },
    {
      "from": "00d6f226"
    },
    {
      "from": "00d8b960"
    },
    {
      "from": "00d8bc87"
    },
    {
      "from": "00d8c5a3"
    },
    {
      "from": "00d8c8ac"
    },
    {
      "from": "00d8c9fa"
    },
    {
      "from": "00d8caea"
    },
    {
      "from": "00d8d493"
    },
    {
      "from": "00da46f8"
    },
    {
      "from": "00d35ee8"
    },
    {
      "from": "00d3617b"
    },
    {
      "from": "00d362c6"
    },
    {
      "from": "00d6433d"
    },
    {
      "from": "00d8e3c8"
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
    "reconstruction/staging/wave13-pilot-core-b01/b3d850_cursor_advance.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-core-b01/00b3d850.json"
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
    "A runtime trace would be needed to observe the element type, to see which of the port's four conditions actually rejects elements in play, and to check whether any caller ever presents a cursor equal to its end.",
    "No original-process trace exists for 0x00b3d850; every claim is static.",
    "The identity of the ctx object and of its vtable slot +0x2c can only be resolved with a receiver whose vtable base is known at run time."
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
  "OpaqueCursor*"
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
