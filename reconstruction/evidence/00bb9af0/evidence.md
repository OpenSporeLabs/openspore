# Evidence 0x00bb9af0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9fa070f257b6fe2f09515e86de29e96a175ce1b8ae0af49c7fd025edc8246b7d`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "unread by the mask itself; the receiver's +0x5C field IS read, so the receiver must be non-null",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_observation": "0x00bb9af7 NEG EAX sets CF from the operand's sign, 0x00bb9af9 SBB EAX,EAX yields 0 (CF clear) or 0xFFFFFFFF (CF set), and 0x00bb9afb NEG EAX maps those to 0 and 1. The full dword is therefore written and bits 8..31 are zero. Every consumer tests AL, never the full dword.",
  "return_register": "EAX",
  "return_semantics": "true iff at least one bit selected by `mask` is set in the receiver's +0x5C dword; the result is exactly 0 or 1, never a mask value",
  "return_type": "bool",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [
    {
      "instruction": "0x00bb9af3: AND EAX,dword ptr [ESP + 0x4]",
      "offset": "ESP+0x4",
      "role": "bit mask",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4 at 0x00bb9afd"
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
    "return_semantics": "unclassified_in_EAX",
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
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "68f7eae95b1d9ac013a4e64f1a0ada9fb072dc39493989e14574006ff5f4bbff",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0006"
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
        "obs-0002"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          92
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0006"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0006"
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
        "obs-0006"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0006"
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
      "at": "0x00bb9af0",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x5c]",
      "reg": "ECX"
    },
    {
      "at": "0x00bb9af0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x5c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bb9af3",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "AND EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00bb9af3",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "AND EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00bb9af9",
      "count": 1,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "SBB EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00bb9afd",
      "form": "RET 0x4",
      "id": "obs-0006",
      "imm": 4,
      "index": 5,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 6,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
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
    "distinct_offsets": 1,
    "max_offset": 92,
    "offsets": [
      92
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class":
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
    "va": "0x00b93550"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b96d40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba6bb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba6f20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba8830"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00badd10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb2070"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb21b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb2330"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb4100"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb6040"
  },
  {
    "name": "FUN_00c47e20",
    "reconstructed": false,
    "va": "0x00c47e20"
  },
  {
    "name": "FUN_00c59240",
    "reconstructed": false,
    "va": "0x00c59240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c59540"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c5f770"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c8b560"
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
  "count": 6,
  "instructions": [
    {
      "address": "00bb9af0",
      "instruction": "MOV EAX,dword ptr [ECX + 0x5c]"
    },
    {
      "address": "00bb9af3",
      "instruction": "AND EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00bb9af7",
      "instruction": "NEG EAX"
    },
    {
      "address": "00bb9af9",
      "instruction": "SBB EAX,EAX"
    },
    {
      "address": "00bb9afb",
      "instruction": "NEG EAX"
    },
    {
      "address": "00bb9afd",
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
  "original_bytes": 13660,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"unread by the mask itself; the receiver's +0x5C field IS read, so the receiver must be non-null\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x4\",\n    \"return_observation\": \"0x00bb9af7 NEG EAX sets CF from the operand's sign, 0x00bb9af9 SBB EAX,EAX yields 0 (CF clear) or 0xFFFFFFFF (CF set), and 0x00bb9afb NEG EAX maps those to 0 and 1. The full dword is therefore written and bits 8..31 are zero. Every consumer tests AL, never the full dword.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"true iff at least one bit selected by `mask` is set in the receiver's +0x5C dword; the result is exactly 0 or 1, never a mask value\",\n    \"return_type\": \"bool\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [],\n    \"stack_arguments\": [\n      {\n        \"instruction\": \"0x00bb9af3: AND EAX,dword ptr [ESP + 0x4]\",\n        \"offset\": \"ESP+0x4\",\n        \"role\": \"bit mask\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4 at 0x00bb9afd\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b93550\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b96d40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba6bb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba6f20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba8830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00badd10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb2070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb21b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb2330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb4100\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb6040\"\n      },\n      {\n        \"name\": \"FUN_00c47e20\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c47e20\"\n      },\n      {\n        \"name\": \"FUN_00c59240\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c59240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c59540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5f770\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8b560\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00df7f60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102daa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010463b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0106cc70\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\
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
  "body_end": "00bb9aff",
  "body_span_bytes": 16,
  "body_start": "00bb9af0",
  "callees": [],
  "callers": [
    "FUN_00c8b560",
    "FUN_00ba8830",
    "FUN_00df7f60",
    "FUN_0102daa0",
    "FUN_00b96d40",
    "FUN_00c59540",
    "FUN_00bb21b0",
    "FUN_00bb2070",
    "FUN_00badd10",
    "FUN_00c5f770",
    "FUN_00ba6f20",
    "FUN_0106cc70",
    "FUN_00b93550",
    "FUN_00c59240",
    "FUN_010463b0",
    "FUN_00c47e20",
    "FUN_00bb4100",
    "FUN_00bb2330",
    "FUN_00ba6bb0",
    "FUN_00bb6040"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00bb9af0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00bb9af0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7b9af0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bb9af0(void)",
  "size_bytes": 16,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bb9af0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 32,
  "xrefs": [
    {
      "from": "00bb60ed"
    },
    {
      "from": "00ba884d"
    },
    {
      "from": "00bb2354"
    },
    {
      "from": "00bb226a"
    },
    {
      "from": "00bb2277"
    },
    {
      "from": "00ba6c45"
    },
    {
      "from": "00bb20dd"
    },
    {
      "from": "00bb20ea"
    },
    {
      "from": "00bade4e"
    },
    {
      "from": "00bb4194"
    },
    {
      "from": "00bb43f0"
    },
    {
      "from": "00bb49f3"
    },
    {
      "from": "00b96dd1"
    },
    {
      "from": "00b96eb9"
    },
    {
      "from": "0102dbd0"
    },
    {
      "from": "0106d04d"
    },
    {
      "from": "00b93574"
    },
    {
      "from": "00c8b565"
    },
    {
      "from": "00c48138"
    },
    {
      "from": "00c4814c"
    },
    {
      "from": "00c48160"
    },
    {
      "from": "00c59394"
    },
    {
      "from": "00c596c1"
    },
    {
      "from": "00c5f95f"
    },
    {
      "from": "00c5f970"
    },
    {
      "from": "00df805f"
    },
    {
      "from": "00ba6f60"
    },
    {
      "from": "00ba6f79"
    },
    {
      "from": "00ba6f95"
    },
    {
      "from": "010464a1"
    },
    {
      "from": "00bb461f"
    },
    {
      "from": "00c4e6db"
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
    "reconstruction/staging/wave13-w1-core-b06/bb9af0_star_record_flag_test.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b06/00bb9af0.json"
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
    "A runtime differential test would have to confirm the flag word's value for a known star system, which is the only way to attach a meaning to individual bits.",
    "Because the function dereferences ECX with no null check, a runtime test that passes a null receiver would fault; that is a property of the original and must be preserved, not defended against.",
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static."
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
  "bool"
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
