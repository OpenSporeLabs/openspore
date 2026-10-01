# Evidence 0x0093bd50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `6e0c00c46c1c5a99455e48b33503ead59e20ef07efe14ee5ec04e77b45f3426b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "receiver_register": "ECX",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "ignored_word",
      "observed_use": "none",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
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
  "content_sha256": "eff84867e66543b381fe6ff2ab87d6d6b27357122d6b3fb3cd92239b99df7317",
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
        "obs-0007"
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
        "obs-0007"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          4,
          8,
          12,
          16,
          20,
          24,
          25,
          28,
          32
        ],
        "register": "ECX",
        "written_through": 10
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0007"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0007"
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
        "obs-0007"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x0093bd50",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [0x01485548]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x0093bd58",
      "count": 10,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0093bd58",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ECX",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x0093bd5a",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "XOR ECX,ECX",
      "reg": "ECX",
      "write_kind": "zero"
    },
    {
      "at": "0x0093bd5c",
      "count": 10,
      "first_use": 3,
      "first_write_index": 1,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EAX],0x143eb78",
      "reg": "EAX"
    },
    {
      "at": "0x0093bd77",
      "count": 1,
      "first_use": 11,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 11,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [EAX + 0x1c],XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x0093bd7f",
      "form": "RET 0x4",
      "id": "obs-0007",
      "imm": 4,
      "index": 13,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 14,
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
    "distinct_offsets": 10,
    "m
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
    "va": "0x006b17a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006c09c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006c0b20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006c0c40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006c0db0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007ebce0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x008dcc80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x008dcdc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x008dcea0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x008dd0d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x008fdd10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00900990"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00946dc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00947d50"
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
  "count": 14,
  "instructions": [
    {
      "address": "0093bd50",
      "instruction": "MOVSS XMM0,dword ptr [0x01485548]"
    },
    {
      "address": "0093bd58",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "0093bd5a",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "0093bd5c",
      "instruction": "MOV dword ptr [EAX],0x143eb78"
    },
    {
      "address": "0093bd62",
      "instruction": "MOV dword ptr [EAX + 0x4],ECX"
    },
    {
      "address": "0093bd65",
      "instruction": "MOV dword ptr [EAX + 0x8],ECX"
    },
    {
      "address": "0093bd68",
      "instruction": "MOV dword ptr [EAX + 0xc],ECX"
    },
    {
      "address": "0093bd6b",
      "instruction": "MOV dword ptr [EAX + 0x10],ECX"
    },
    {
      "address": "0093bd6e",
      "instruction": "MOV dword ptr [EAX + 0x14],ECX"
    },
    {
      "address": "0093bd71",
      "instruction": "MOV byte ptr [EAX + 0x18],CL"
    },
    {
      "address": "0093bd74",
      "instruction": "MOV byte ptr [EAX + 0x19],CL"
    },
    {
      "address": "0093bd77",
      "instruction": "MOVSS dword ptr [EAX + 0x1c],XMM0"
    },
    {
      "address": "0093bd7c",
      "instruction": "MOV dword ptr [EAX + 0x20],ECX"
    },
    {
      "address": "0093bd7f",
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
  "original_bytes": 9479,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"receiver_register\": \"ECX\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"ignored_word\",\n        \"observed_use\": \"none\",\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:MemoryStream,MemoryStream*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-serialization-persistence\",\n      \"score\": 27,\n      \"symbol\": \"memory_stream_set_position_0093c0c0\",\n      \"va\": \"0x0093c0c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-serialization-persistence\",\n      \"score\": 10,\n      \"symbol\": \"stream_child_teardown_0093b5a0\",\n      \"va\": \"0x0093b5a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-serialization-persistence\",\n      \"score\": 10,\n      \"symbol\": \"stream_child_close_and_maybe_delete_0093b610\",\n      \"va\": \"0x0093b610\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The register residues, global float load, vtable, zero stores, untouched padding, and RET 4 are exact; the imported destructor label, allocation owner, and shared-pointer lifetime remain rejected or unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"MemoryStream\",\n  \"cluster\": null,\n  \"confidence\": 0.96,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006b17a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006c09c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006c0b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006c0c40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006c0db0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007ebce0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x008dcc80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x008dcdc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x008dcea0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x008dd0d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x008fdd10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00900990\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00946dc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00947d50\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006b17e9\",\n        \"direction\": \"in\",\n        \"other\": \"0x006b17a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006c0a55\",\n        \"direction\": \"in\",\n        \"other\": \"0x006c09c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006c0baf\",\n        \"direction\": \"in\",\n        \"other\": \"0x006c0b20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006c0cc8\",\n        \"direction\": \"in\",\n        \"other\": \"0x006c0c40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006c0e37\",\n        \"direction\": \"in\",\n        \"other\": \"0x006c0db0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007ebd3d\",\n        \"direction\": \"in\",\n        \"other\": \"0x007ebce0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x008dcced\",\n        \"direct
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
  "body_end": "0093bd81",
  "body_span_bytes": 50,
  "body_start": "0093bd50",
  "callees": [],
  "callers": [
    "FUN_006b17a0",
    "FUN_006c09c0",
    "FUN_006c0b20",
    "FUN_008dd0d0",
    "FUN_007ebce0",
    "FUN_00900990",
    "FUN_008fdd10",
    "FUN_00946dc0",
    "FUN_006c0c40",
    "FUN_008dcc80",
    "FUN_00947d50",
    "FUN_008dcea0",
    "FUN_006c0db0",
    "Resource::PFRecordRead::SetPosition"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0093bd50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "MemoryStream_dtor",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x53bd50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined MemoryStream_dtor(void)",
  "size_bytes": 50,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0093bd50",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 14,
  "xrefs": [
    {
      "from": "007ebd3d"
    },
    {
      "from": "00946e65"
    },
    {
      "from": "006b17e9"
    },
    {
      "from": "006c0cc8"
    },
    {
      "from": "006c0e37"
    },
    {
      "from": "006c0a55"
    },
    {
      "from": "006c0baf"
    },
    {
      "from": "008dcced"
    },
    {
      "from": "008dce2c"
    },
    {
      "from": "008dcf03"
    },
    {
      "from": "008dd130"
    },
    {
      "from": "00947d73"
    },
    {
      "from": "008fdd8b"
    },
    {
      "from": "009009d3"
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
  "file": "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp",
  "files": [
    "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp",
    "src/reconstruction/wave6_serialization_persistence/stream_lifecycle.hpp",
    "src/reconstruction/wave6_serialization_persistence/stream_lifecycle_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-serialization-persistence/0093bd50.json"
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
    "gate-memory-stream-initialization-and-allocation-lifecycle"
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
  "MemoryStream",
  "MemoryStream*",
  "MemoryStreamVtable",
  "uint32_t",
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
