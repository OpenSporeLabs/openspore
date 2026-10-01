# Evidence 0x00aea230

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2b43aa51d784c323e39d0aabdec357c331caa9f917d0eacdaca9ba27d430a3b2`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "receiver": {
    "register": "ECX",
    "type": "cCommManager*",
    "width_bytes": 4
  },
  "return_register": "EAX",
  "return_type": "void*",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "fields": [
        "begin",
        "end"
      ],
      "name": "range",
      "position": 1,
      "type": "cCommStringRange*"
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
    "calling_convention": "__stdcall",
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
    "receiver": false,
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
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "SUPPORTED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [
    {
      "field": "calling_convention",
      "inferred": "__stdcall",
      "kind": "inferred_vs_persisted",
      "persisted": "__thiscall",
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "c4e34fb33a0f45d78833394facc0c65c48499203221570ca24df25f56a1cfb4d",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__stdcall",
    "candidate_conventions": [
      "__stdcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "disagrees",
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
        "obs-0009"
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
        "obs-0009"
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
        "obs-0009"
      ],
      "claim": "calling convention is __stdcall: a callee that pops stack arguments with no register receiver",
      "confidence": "INFERRED",
      "id": "C6",
      "value": "__stdcall"
    },
    {
      "based_on": [
        "obs-0009"
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
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009"
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
      "at": "0x00aea230",
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
      "at": "0x00aea230",
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
      "at": "0x00aea230",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00aea234",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "ADD ECX,0x64",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x00aea23b",
      "count": 3,
      "first_use": 4,
      "first_write_index": 0,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x4]",
      "reg": "EAX"
    },
    {
      "at": "0x00aea23b",
      "definite": true,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x4]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00aea240",
      "count": 1,
      "first_use": 6,
      "first_write_index": 4,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_READ",
      "raw": "PUSH EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00aea242",
      "id": "obs-0008",
      "index": 8,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00454cb0",
      "target": "0x00454cb0"
    },
    {
      "at": "0x00aea247",
      "form": "RET 0x4",
      "id": "obs-0009",
      "imm": 4,
      "index": 9,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 10,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp
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
    "name": "FUN_0102d1b0",
    "reconstructed": true,
    "va": "0x0102d1b0"
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
      "address": "00aea230",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00aea234",
      "instruction": "ADD ECX,0x64"
    },
    {
      "address": "00aea237",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "00aea239",
      "instruction": "JZ 0x00aea247"
    },
    {
      "address": "00aea23b",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00aea23e",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00aea240",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00aea241",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00aea242",
      "instruction": "CALL 0x00454cb0"
    },
    {
      "address": "00aea247",
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
  "original_bytes": 6595,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"receiver\": {\n      \"register\": \"ECX\",\n      \"type\": \"cCommManager*\",\n      \"width_bytes\": 4\n    },\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void*\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"fields\": [\n          \"begin\",\n          \"end\"\n        ],\n        \"name\": \"range\",\n        \"position\": 1,\n        \"type\": \"cCommStringRange*\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:cCommManager,cCommManager*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 27,\n      \"symbol\": \"FUN_00aeb160\",\n      \"va\": \"0x00aeb160\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:cCommManager,cCommManager*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 27,\n      \"symbol\": \"Simulator_cCommManager_CreateAndDispatchEvent_00aeb720\",\n      \"va\": \"0x00aeb720\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 16,\n      \"symbol\": \"FUN_00aea5d0\",\n      \"va\": \"0x00aea5d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 14,\n      \"symbol\": \"FUN_00aea250\",\n      \"va\": \"0x00aea250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 11,\n      \"symbol\": \"FUN_0102d1b0\",\n      \"va\": \"0x0102d1b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 10,\n      \"symbol\": \"cSpaceInventoryItem_ctor_00c877f0\",\n      \"va\": \"0x00c877f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"pkg12_space_00de9fc0\",\n      \"va\": \"0x00de9fc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"pkg12_space_01021300\",\n      \"va\": \"0x01021300\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The caller literals are byte strings despite the downstream decompiler's string16 type label.\",\n    \"The live function dereferences a null range on the non-self path; it has no null guard.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"cCommManager\",\n  \"cluster\": null,\n  \"confidence\": 0.98,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"FUN_0102d1b0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0102d1b0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0102d56d\",\n        \"direction\": \"in\",\n        \"other\": \"0x0102d1b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0102d7a3\",\n        \"direction\": \"in\",\n        \"other\": \"0x0102d1b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00aea242\",\n        \"direction\": \"out\",\n        \"other\": \"0x00454cb0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x00454cb0\"\n    ],\n    \"manifest_callers\": [\n      \"0x0102d1b0\"\n    ],\n    \"nearby_reconstructed\": [\n      \"0x0102d1b0\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0344\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"FUN_00aea230\",\n  \"normalized_symbol\": \"FUN_00aea230\",\n  \"observed_mechanics\": [\n    \"self-range returns without callback\",\n    \"raw range forwarding\",\n    \"RET 4\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-12-SIM-SPACE\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": \"source-wave3/PKG-12-SIM-SPACE\"\n    },\n    \"package\": \"PKG-12-SIM-SPACE\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-12-SIM-SPACE\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-space-comm-string-assignment\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_manager_string_range_assignment_observed\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": \"src/reconstruction/pkg12_space/space_comm_event_lifecycle.cpp\",\n    \"files\": [\n      \"reconstruction/staging/pkg12-space/space_comm_event_lifecycle.cpp\",\n      \"reconstruction/staging/pkg12-space/space_comm_event_lifecycle.hpp\",\n      \"reconstruction/staging/pkg12-space/space_comm_event_lifecyc
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
  "body_end": "00aea249",
  "body_span_bytes": 26,
  "body_start": "00aea230",
  "callees": [
    "FUN_00454cb0"
  ],
  "callers": [
    "FUN_0102d1b0"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00aea230",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00aea230",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6ea230",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00aea230(void)",
  "size_bytes": 26,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00aea230",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "0102d56d"
    },
    {
      "from": "0102d7a3"
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
  "file": "src/reconstruction/pkg12_space/space_comm_event_lifecycle.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_comm_event_lifecycle.cpp",
    "reconstruction/staging/pkg12-space/space_comm_event_lifecycle.hpp",
    "reconstruction/staging/pkg12-space/space_comm_event_lifecycle_model_test.cpp",
    "src/reconstruction/pkg12_space/space_comm_event_lifecycle.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg12-space/00aea230.json"
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
    "gate-space-comm-string-assignment"
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
  "cCommManager",
  "cCommManager*",
  "cCommStringRange",
  "cCommStringRange*",
  "void*"
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
    "derived": "__stdcall",
    "field": "calling_convention",
    "kind": "derived_vs_persisted",
    "persisted": "__thiscall",
    "resolution_status": "unresolved"
  }
]
```
