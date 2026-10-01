# Evidence 0x0093b610

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d714dfd2e50c0cc078fd24f3968986641bb81c860e183cb02461f67385c80c0f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "receiver_register": "ECX",
  "return_register": "EAX",
  "return_type": "StreamChild*",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "delete_flags",
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
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
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
          1
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
  "content_sha256": "4d77310bee79997fe16abdd1f5a17c143516048937bfb86aa419c12f4e07570e",
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
        "obs-0011"
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
        "obs-0006"
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
        "obs-0002"
      ],
      "claim": "ECX carries the receiver: 0x0093b610 is slot 0 of the vptr-backed vftable at 0x0143eaac, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 0,
        "table": "0x0143eaac"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0011"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
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
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011"
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
      "at": "0x0093b610",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0093b611",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0093b611",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x0093b613",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0093b5a0",
      "target": "0x0093b5a0"
    },
    {
      "at": "0x0093b618",
      "count": 1,
      "first_use": 3,
      "first_write_index": 7,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "TEST byte ptr [ESP + 0x8],0x1",
      "reg": "ESP"
    },
    {
      "at": "0x0093b618",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0006",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "TEST byte ptr [ESP + 0x8],0x1",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x0093b620",
      "id": "obs-0007",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "stream_child_teardown_0093b5a0",
    "reconstructed": true,
    "va": "0x0093b5a0"
  }
]
```

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
  "count": 11,
  "instructions": [
    {
      "address": "0093b610",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0093b611",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0093b613",
      "instruction": "CALL 0x0093b5a0"
    },
    {
      "address": "0093b618",
      "instruction": "TEST byte ptr [ESP + 0x8],0x1"
    },
    {
      "address": "0093b61d",
      "instruction": "JZ 0x0093b628"
    },
    {
      "address": "0093b61f",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0093b620",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "0093b625",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0093b628",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "0093b62a",
      "instruction": "POP ESI"
    },
    {
      "address": "0093b62b",
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
  "original_bytes": 7248,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"receiver_register\": \"ECX\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"StreamChild*\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"delete_flags\",\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:StreamChild,StreamChild*,StreamChildLifecycleServices\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"wave6-serialization-persistence\",\n      \"score\": 33,\n      \"symbol\": \"stream_child_teardown_0093b5a0\",\n      \"va\": \"0x0093b5a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-serialization-persistence\",\n      \"score\": 10,\n      \"symbol\": \"memory_stream_initialize_0093bd50\",\n      \"va\": \"0x0093bd50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"wave6-serialization-persistence\",\n      \"score\": 10,\n      \"symbol\": \"memory_stream_set_position_0093c0c0\",\n      \"va\": \"0x0093c0c0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0143eaac\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"pkg_file_stream_wave6_stream_buffer_delegate_0093ae60\",\n      \"va\": \"0x0093ae60\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0143eaac\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"pkg_file_stream_wave6_stream_child_delegate_0093b6d0\",\n      \"va\": \"0x0093b6d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Teardown-before-delete, bit-zero-only selection, global delete call, pre-delete receiver return, and RET 4 are exact; allocation pairing and vtable ownership remain unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"StreamChild\",\n  \"cluster\": \"unknown-vtable-impl\",\n  \"confidence\": 0.94,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"stream_child_teardown_0093b5a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0093b5a0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0093b613\",\n        \"direction\": \"out\",\n        \"other\": \"0x0093b5a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0093b620\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 1,\n    \"manifest_callees\": [\n      \"0x0093b5a0\",\n      \"0x00f47380\"\n    ],\n    \"manifest_callers\": [\n      \"vtable_xref_0143eaac\"\n    ],\n    \"nearby_reconstructed\": [\n      \"0x0093b5a0\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0285\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"StreamChild_Close\",\n  \"normalized_symbol\": \"stream_child_close_and_maybe_delete_0093b610\",\n  \"observed_mechanics\": [\n    \"save receiver\",\n    \"always call teardown 0x0093b5a0\",\n    \"test only bit zero of delete flags\",\n    \"call global delete 0x00f47380 when set\",\n    \"return the original receiver pointer in EAX\",\n    \"RET 4\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"wave6-serialization-persistence\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"wave6-serialization-persistence\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"wave6-serialization-persistence\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-stream-child-virtual-teardown-and-delete\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_stream_child_teardown_and_scalar_delete_runtime_vtable_ownership_unknown\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": \"src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp\",\n    \"files\": [\n      \"src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp\",\n      \"src/reconstruction/wave6_serialization_persistence/stream_lifecycle.hpp\",\n      \"src/re
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
  "body_end": "0093b62d",
  "body_span_bytes": 30,
  "body_start": "0093b610",
  "callees": [
    "IO::StreamChild::Open",
    "FUN_00f47380"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0093b610",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "StreamChild_Close",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x53b610",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined StreamChild_Close(void)",
  "size_bytes": 30,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0093b610",
  "vtables": {
    "referenced_by_vtables": [
      "0x0143eaac"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0143eaac"
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
    "reconstruction/metadata/wave6-serialization-persistence/0093b610.json"
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
    "gate-stream-child-virtual-teardown-and-delete"
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
  "StreamChild",
  "StreamChild*",
  "StreamChildLifecycleServices",
  "uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0093b610",
  "vtable:0x0143eaac"
]
```

## Conflicts

```json
[]
```
