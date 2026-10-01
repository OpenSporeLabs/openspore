# Evidence 0x005ca960

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `104292f947308e50cbbfe80ac50bc96dbb53c661c280abd2301861deb3e28686`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl-compatible one-stack-word accessor",
  "return_register": "EAX",
  "return_type": "OpaqueService *",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Service whose vtable slot +0x0c is called",
      "position": 1,
      "type": "OpaqueService *",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 0,
  "termination": "RET"
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "32a68ac8ad1d806d27aff696436e7314dc536cefccf6969eaafe4b5783c0970c",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__thiscall"
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
    "persisted_calling_convention": "cdecl-compatible one-stack-word accessor"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0010",
        "obs-0011"
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
        "obs-0002"
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
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011"
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
        "obs-0010",
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x005ca960",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x005ca960",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x005ca960",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005ca968",
      "count": 1,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "ECX"
    },
    {
      "at": "0x005ca968",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005ca96a",
      "count": 2,
      "first_use": 4,
      "first_write_index": 3,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0xc]",
      "reg": "EAX"
    },
    {
      "at": "0x005ca96a",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0xc]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005ca972",
      "count": 1,
      "first_use": 6,
      "first_wri
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
    "name": "Editors_EditorUI_HandleMessage_005e0000",
    "reconstructed": true,
    "va": "0x005e0000"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00817040"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00995b20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e03f80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e133b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e13b50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e1d7a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ea0910"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ee9840"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f0ea20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01063dc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01066f20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01072d40"
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
  "count": 10,
  "instructions": [
    {
      "address": "005ca960",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "005ca964",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "005ca966",
      "instruction": "JZ 0x005ca975"
    },
    {
      "address": "005ca968",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "005ca96a",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "005ca96d",
      "instruction": "PUSH 0x8ed27e7a"
    },
    {
      "address": "005ca972",
      "instruction": "CALL EDX"
    },
    {
      "address": "005ca974",
      "instruction": "RET"
    },
    {
      "address": "005ca975",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "005ca977",
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
  "original_bytes": 10392,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl-compatible one-stack-word accessor\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"OpaqueService *\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"observed_use\": \"Service whose vtable slot +0x0c is called\",\n        \"position\": 1,\n        \"type\": \"OpaqueService *\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:OpaqueService\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 17,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 14,\n      \"symbol\": \"editor_query_reset_005dd750\",\n      \"va\": \"0x005dd750\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 14,\n      \"symbol\": \"editor_query_clear_flags_0093db80\",\n      \"va\": \"0x0093db80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 11,\n      \"symbol\": \"Editors_EditorUI_HandleMessage_005e0000\",\n      \"va\": \"0x005e0000\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"FUN_005dda30\",\n      \"va\": \"0x005dda30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueService\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"service_005f9230\",\n      \"va\": \"0x005f9230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueService\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"service_005f9310\",\n      \"va\": \"0x005f9310\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"Null vtable and null callback paths remain untyped live fault paths and are not normalized.\",\n    \"The indirect owner and callback semantics are unresolved.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueService\",\n  \"cluster\": null,\n  \"confidence\": 0.98,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"Editors_EditorUI_HandleMessage_005e0000\",\n        \"reconstructed\": true,\n        \"va\": \"0x005e0000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00817040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00995b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e03f80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e133b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e13b50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e1d7a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ea0910\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ee9840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f0ea20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01063dc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01066f20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01072d40\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005e02ba\",\n        \"direction\": \"in\",\n        \"other\": \"0x005e0000\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00817324\",\n        \"direction\": \"in\",\n        \"other\": \"0x00817040\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00995dae\",\n        \"direction\": \"in\",\n        \"other\": \"0x00995b20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00995df6\",\n        \"direction\": \"in\",\n        \"other\": \"0x00995b20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e03ff0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e03f80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e041e2\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e03f80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e13ae8\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e133b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e14145\",\n 
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
  "body_end": "005ca977",
  "body_span_bytes": 24,
  "body_start": "005ca960",
  "callees": [],
  "callers": [
    "FUN_00e03f80",
    "FUN_00817040",
    "FUN_01072d40",
    "FUN_00e13b50",
    "FUN_00f0ea20",
    "FUN_00e1d7a0",
    "FUN_01063dc0",
    "FUN_00995b20",
    "FUN_00ea0910",
    "FUN_01066f20",
    "FUN_00ee9840",
    "FUN_00e133b0",
    "FUN_005e0000"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "005ca960",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005ca960",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1ca960",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005ca960(void)",
  "size_bytes": 24,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005ca960",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 29,
  "xrefs": [
    {
      "from": "00e13ae8"
    },
    {
      "from": "00e14145"
    },
    {
      "from": "00817324"
    },
    {
      "from": "005e02ba"
    },
    {
      "from": "00995dae"
    },
    {
      "from": "00995df6"
    },
    {
      "from": "00e1d8f4"
    },
    {
      "from": "00ea0cbf"
    },
    {
      "from": "00ea0d55"
    },
    {
      "from": "00ea0dfa"
    },
    {
      "from": "00ee9aed"
    },
    {
      "from": "00f0ec63"
    },
    {
      "from": "00f0ec86"
    },
    {
      "from": "010671a9"
    },
    {
      "from": "010671c4"
    },
    {
      "from": "010671df"
    },
    {
      "from": "01063e79"
    },
    {
      "from": "01063eb9"
    },
    {
      "from": "01072f03"
    },
    {
      "from": "01073319"
    },
    {
      "from": "00d2c845"
    },
    {
      "from": "00d2c85e"
    },
    {
      "from": "00e03ff0"
    },
    {
      "from": "00e041e2"
    },
    {
      "from": "00f3af94"
    },
    {
      "from": "007fe546"
    },
    {
      "from": "007fe59e"
    },
    {
      "from": "007fe5be"
    },
    {
      "from": "00e01838"
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
  "file": "src/reconstruction/pkg10_editor_dispatch/editor_query_helpers.cpp",
  "files": [
    "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.cpp",
    "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.hpp",
    "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers_model_test.cpp",
    "src/reconstruction/pkg10_editor_dispatch/editor_query_helpers.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/005ca960.json"
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
    "gate-editor-query-service-slot"
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
  "OpaqueService",
  "OpaqueService *"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0000000c"
]
```

## Conflicts

```json
[]
```
