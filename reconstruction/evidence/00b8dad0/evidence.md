# Evidence 0x00b8dad0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b34ca72bf45cbb741336d4af034d0d394ef8c36f89bbc984bcd09631e08588e7`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX, read at 0x00b8dad0",
  "hidden_this_register": "ECX is read exactly once, by the LEA displacement",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_register": "EAX",
  "return_semantics": "A pointer to receiver + 0x198. Formed with LEA, so it is the address of a member block inside the receiver, not a pointer the receiver stores. The result ALIASES the receiver: writing through it modifies the receiver's +0x198 block, which makes this a mutable-reference accessor rather than a const getter.",
  "return_type": "ResourceKey3*",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00b8dad6"
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX;void_possible",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_address_taken_without_memory_access",
    "ecx_address_taken_without_memory_access: LEA takes ECX's address without any memory access through it",
    "no_discriminator: no stack-argument read and no positive receiver evidence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "52d254a1eb516c60f2bcaf71986550726e083507e35373a46019c07a04ee1aa0",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
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
        "obs-0003"
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
        "obs-0001",
        "obs-0002"
      ],
      "claim": "the register receiver is undetermined: ecx_address_taken_without_memory_access",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_address_taken_without_memory_access",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "EAX is never written and no call can clobber it, so a void return is possible; this is a flag, never a type",
      "confidence": "APPROXIMATION",
      "id": "RT3",
      "value": {
        "void_possible": true
      }
    }
  ],
  "observations": [
    {
      "at": "0x00b8dad0",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ECX + 0x198]",
      "reg": "EAX"
    },
    {
      "at": "0x00b8dad0",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ECX + 0x198]",
      "reg": "ECX"
    },
    {
      "at": "0x00b8dad6",
      "form": "RET",
      "id": "obs-0003",
      "imm": null,
      "index": 1,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 2,
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
    "confidence": "UNKNOWN",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": null,
    "reason": "ecx_address_taken_without_memory_access",
    "register": null,
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": true
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": null,
    "present": false,
    "target": null
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00b8dad0"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_UNKNOWN"
}
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
    "va": "0x00b6b1a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c53bc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c704a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c71750"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c71910"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c829e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e2abc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01000000"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0103af90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0103ca40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0103cd00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0103d9b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0103e6e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0103e8e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0103fe90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01068970"
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
  "count": 2,
  "instructions": [
    {
      "address": "00b8dad0",
      "instruction": "LEA EAX,[ECX + 0x198]"
    },
    {
      "address": "00b8dad6",
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
  "original_bytes": 12415,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX, read at 0x00b8dad0\",\n    \"hidden_this_register\": \"ECX is read exactly once, by the LEA displacement\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"A pointer to receiver + 0x198. Formed with LEA, so it is the address of a member block inside the receiver, not a pointer the receiver stores. The result ALIASES the receiver: writing through it modifies the receiver's +0x198 block, which makes this a mutable-reference accessor rather than a const getter.\",\n    \"return_type\": \"ResourceKey3*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET at 0x00b8dad6\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6b1a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c53bc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c704a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c71750\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c71910\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c829e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e2abc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01000000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0103af90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0103ca40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0103cd00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0103d9b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0103e6e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0103e8e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0103fe90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01068970\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0106ba00\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b6b39c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b6b1a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c53c0f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c53bc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c704aa\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c704a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c7188f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c71750\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"ca
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
  "body_end": "00b8dad6",
  "body_span_bytes": 7,
  "body_start": "00b8dad0",
  "callees": [],
  "callers": [
    "FUN_0103e6e0",
    "FUN_00c704a0",
    "FUN_01068970",
    "FUN_00e2abc0",
    "FUN_0103af90",
    "FUN_0103cd00",
    "FUN_00b6b1a0",
    "FUN_0103fe90",
    "FUN_0103d9b0",
    "FUN_01000000",
    "FUN_0106ba00",
    "FUN_00c53bc0",
    "FUN_0103ca40",
    "FUN_00c71750",
    "FUN_00c829e0",
    "FUN_0103e8e0",
    "FUN_00c71910"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b8dad0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b8dad0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x78dad0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b8dad0(void)",
  "size_bytes": 7,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b8dad0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 25,
  "xrefs": [
    {
      "from": "00c7188f"
    },
    {
      "from": "0103ca4d"
    },
    {
      "from": "01000054"
    },
    {
      "from": "010002a4"
    },
    {
      "from": "0103ed64"
    },
    {
      "from": "0103cdde"
    },
    {
      "from": "0103d9bf"
    },
    {
      "from": "0103e712"
    },
    {
      "from": "00c71963"
    },
    {
      "from": "0106bfdd"
    },
    {
      "from": "00b6b39c"
    },
    {
      "from": "00c53c0f"
    },
    {
      "from": "00c704aa"
    },
    {
      "from": "00c82b18"
    },
    {
      "from": "00c82c0e"
    },
    {
      "from": "00e2ac49"
    },
    {
      "from": "0103afbd"
    },
    {
      "from": "0103afc8"
    },
    {
      "from": "0103b092"
    },
    {
      "from": "0103b0a9"
    },
    {
      "from": "0104002f"
    },
    {
      "from": "01068c8f"
    },
    {
      "from": "01033052"
    },
    {
      "from": "01033530"
    },
    {
      "from": "01026934"
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
    "reconstruction/staging/wave13-w1-core-b08/ae9f50_session_boot_register.cpp",
    "reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp",
    "reconstruction/staging/wave13-w1-core-b08/ba61b0_make_planet_record.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c0b780_sub_object_flag_608.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c0ce80_tier_value_lookup.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c47180_manager_slot_replace.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test2.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b08/00b8dad0.json"
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
    "No original-process trace exists. A differential run must confirm the returned address is still receiver + 0x198 in the shipping build.",
    "The class attribution rests on a type-name literal read at 0x00ba61b0. A run that dumps the concrete vtable pointer of a constructed record would confirm or refute it."
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
  "ResourceKey3*"
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
