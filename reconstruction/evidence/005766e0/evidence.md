# Evidence 0x005766e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `6b00b6875cc6e32505f1d8183a5147118484e9b4f951599079bb76f9da503f5d`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is copied to EDI at 0x005766e9 and is never read again; the two virtual calls take their receivers from EBX and ESI instead",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_observation": "0x0057670d: MOV EAX,EDI, where EDI was loaded from ECX at 0x005766e9. The single write is on the common tail, so all three exits (equal, completed, and either null path) return the same value.",
  "return_register": "EAX",
  "return_semantics": "the receiver, unchanged; this is a mutator that returns its own this, so the result is chainable",
  "return_type": "RefHolder*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "frame_offset": "[ESP + 0x4] at entry",
      "index": 1,
      "meaning": "a pointer to a pointer. 0x005766e0 loads it and 0x005766e6 dereferences it, so the incoming refcounted pointer is read through two levels of indirection. Every inspected callsite passes the address of a separate dword rather than the value itself.",
      "width": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "three paths, all merging at 0x0057670d: the early return at 0x005766ef, the fall-through after the Release, and the two JZ skips at 0x005766f3 and 0x00576702 which both target 0x0057670d"
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
    "saved_registers": [
      "EBX",
      "EDI",
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
  "content_sha256": "b233cb0986caa0ee323bcf015515f909fe6037290e67a807604a167402df8988",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0020"
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
        "obs-0002"
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
        "obs-0009",
        "obs-0010",
        "obs-0014"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010",
        "obs-0014",
        "obs-0020"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0020"
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
        "obs-0020"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020"
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
      "at": "0x005766e0",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x005766e0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x005766e0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005766e4",
      "count": 3,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x005766e5",
      "count": 4,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005766e6",
      "count": 3,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x005766e6",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [EAX]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005766e8",
      "count": 4,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x005766e9",
      "count": 1,
      "first_use": 5,
      "first_write_index": 13,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005766e9",
      "defi
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
    "va": "0x0057c0e0"
  },
  {
    "name": "editor_input_00588570",
    "reconstructed": true,
    "va": "0x00588570"
  },
  {
    "name": "palette_safe_wave11_fill_node_array_005c7ff0",
    "reconstructed": true,
    "va": "0x005c7ff0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0064acd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00661d10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0069e090"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0069e260"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007bf720"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c3a930"
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
  "count": 27,
  "instructions": [
    {
      "address": "005766e0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "005766e4",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005766e5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005766e6",
      "instruction": "MOV ESI,dword ptr [EAX]"
    },
    {
      "address": "005766e8",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005766e9",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "005766eb",
      "instruction": "MOV EBX,dword ptr [EDI]"
    },
    {
      "address": "005766ed",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "005766ef",
      "instruction": "JZ 0x0057670d"
    },
    {
      "address": "005766f1",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "005766f3",
      "instruction": "JZ 0x005766fe"
    },
    {
      "address": "005766f5",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "005766f7",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "005766fa",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005766fc",
      "instruction": "CALL EAX"
    },
    {
      "address": "005766fe",
      "instruction": "MOV dword ptr [EDI],ESI"
    },
    {
      "address": "00576700",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00576702",
      "instruction": "JZ 0x0057670d"
    },
    {
      "address": "00576704",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "00576706",
      "instruction": "MOV EAX,dword ptr [EDX + 0x8]"
    },
    {
      "address": "00576709",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "0057670b",
      "instruction": "CALL EAX"
    },
    {
      "address": "0057670d",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "0057670f",
      "instruction": "POP EDI"
    },
    {
      "address": "00576710",
      "instruction": "POP ESI"
    },
    {
      "address": "00576711",
      "instruction": "POP EBX"
    },
    {
      "address": "00576712",
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
  "original_bytes": 9841,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX\",\n    \"hidden_this_register\": \"ECX is copied to EDI at 0x005766e9 and is never read again; the two virtual calls take their receivers from EBX and ESI instead\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x4\",\n    \"return_observation\": \"0x0057670d: MOV EAX,EDI, where EDI was loaded from ECX at 0x005766e9. The single write is on the common tail, so all three exits (equal, completed, and either null path) return the same value.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"the receiver, unchanged; this is a mutator that returns its own this, so the result is chainable\",\n    \"return_type\": \"RefHolder*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"frame_offset\": \"[ESP + 0x4] at entry\",\n        \"index\": 1,\n        \"meaning\": \"a pointer to a pointer. 0x005766e0 loads it and 0x005766e6 dereferences it, so the incoming refcounted pointer is read through two levels of indirection. Every inspected callsite passes the address of a separate dword rather than the value itself.\",\n        \"width\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"three paths, all merging at 0x0057670d: the early return at 0x005766ef, the fall-through after the Release, and the two JZ skips at 0x005766f3 and 0x00576702 which both target 0x0057670d\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"palette_safe_wave11_fill_node_array_005c7ff0\",\n      \"va\": \"0x005c7ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057c0e0\"\n      },\n      {\n        \"name\": \"editor_input_00588570\",\n        \"reconstructed\": true,\n        \"va\": \"0x00588570\"\n      },\n      {\n        \"name\": \"palette_safe_wave11_fill_node_array_005c7ff0\",\n        \"reconstructed\": true,\n        \"va\": \"0x005c7ff0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0064acd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00661d10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0069e090\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0069e260\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bf720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c3a930\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0057c160\",\n        \"direction\": \"in\",\n        \"other\": \"0x0057c0e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00588ea8\",\n        \"direction\": \"in\",\n        \"other\": \"0x00588570\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c8342\",\n        \"direction\": \"in\",\n        \"other\": \"0x005c7ff0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0064af7a\",\n        \"direction\": \"in\",\n        \"other\": \"0x0064acd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0064b39a\",\n        \"direction\": \"in\",\n        \"other\": \"0x0064acd0\",\n      
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
  "body_end": "00576714",
  "body_span_bytes": 53,
  "body_start": "005766e0",
  "callees": [],
  "callers": [
    "FUN_00661d10",
    "FUN_007bf720",
    "FUN_0069e260",
    "FUN_0057c0e0",
    "FUN_0069e090",
    "Editors::cEditor::OnMouseDown",
    "FUN_00c3a930",
    "FUN_0064acd0",
    "FUN_005c7ff0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "005766e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005766e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1766e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005766e0(void)",
  "size_bytes": 53,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005766e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 13,
  "xrefs": [
    {
      "from": "0069e308"
    },
    {
      "from": "005c8342"
    },
    {
      "from": "0064af7a"
    },
    {
      "from": "0064b39a"
    },
    {
      "from": "00661f59"
    },
    {
      "from": "00661fd5"
    },
    {
      "from": "0069e131"
    },
    {
      "from": "00c3a9aa"
    },
    {
      "from": "0057c160"
    },
    {
      "from": "00588ea8"
    },
    {
      "from": "007bf944"
    },
    {
      "from": "00c3a8a4"
    },
    {
      "from": "00c3a8cc"
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
    "reconstruction/staging/wave13-w1-dispatch-b02/b5766e0_intrusive_ptr_assign.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b02/b5766e0_intrusive_ptr_assign.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b02/005766e0.json"
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
    "A runtime trace is required to confirm that the concrete AddRef and Release at slots +0x04 and +0x08 of the actual pointee classes are the 0x00432a50 / 0x00404f90 pair, since the vtable was not located statically.",
    "A runtime trace is required to observe whether a self-assignment ever occurs in practice, which is the only way to confirm the guard is exercised rather than dead.",
    "No original-process trace has ever been captured for 0x005766e0; every claim here is static. The original Cell stage has never been entered in any recorded run."
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
  "RefHolder*"
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
