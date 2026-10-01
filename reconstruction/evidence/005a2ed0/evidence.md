# Evidence 0x005a2ed0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ae7b18925be93d0121c00719d869992e4ea0f0df21c10797b1b63cfb21afa8b9`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_note": "HONEST DISCLOSURE, because this field is a worker claim and not a machine token. The machine ABI envelope for this VA records return_semantics \"unclassified_in_EAX\" with return {register EAX, register_class \"aggregate_unknown\", type null, void_possible false} -- machine-vocabulary phrases that name no C++ type. Independently of that envelope the complete listing fixes the value: MOV EAX,ESI at 0x005a2f19 is the last write to EAX before the body's sole RET at 0x005a2f1c, it is unconditional on both paths, and ESI has held the receiver since 0x005a2ed1, so the returned value is the receiver p...",
  "return_register": "EAX",
  "return_type": "SwarmW2005a2ed0Receiver*",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
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
  "content_sha256": "f5968fea5eace898798a833a6d74d3f379b8f9a074347b51b330c7002840fa92",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0015"
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
        "obs-0011"
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
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          4,
          8,
          16
        ],
        "register": "ECX",
        "written_through": 6
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0015"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0015"
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
        "obs-0015"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0015"
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
      "at": "0x005a2ed0",
      "count": 10,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005a2ed1",
      "count": 2,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005a2ed1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x005a2ee7",
      "definite": true,
      "id": "obs-0004",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x10]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005a2eee",
      "definite": true,
      "id": "obs-0005",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005a2ef0",
      "count": 1,
      "first_use": 9,
      "first_write_index": 8,
      "id": "obs-0006",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x4]",
      "reg": "EAX"
    },
    {
      "at": "0x005a2ef0",
      "definite": true,
      "id": "obs-0007",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x4]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005a2ef3",
      "count": 1,
      "first_use": 10,
      "first_write_index": 9,
      "id": "obs-0008",
      "index": 10,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x005a2ef3",
      "base": "EDX",
      "disp": null,
      "id": "obs-0009",
      "index": 10,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x005a2ef5",
      "count": 1,
      "first
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
    "name": "editor_camera_func54h_005a2320",
    "reconstructed": true,
    "va": "0x005a2320"
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
  "count": 22,
  "instructions": [
    {
      "address": "005a2ed0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005a2ed1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005a2ed3",
      "instruction": "MOV dword ptr [ESI],0x13f69c8"
    },
    {
      "address": "005a2ed9",
      "instruction": "MOV dword ptr [ESI + 0x4],0x13f69b8"
    },
    {
      "address": "005a2ee0",
      "instruction": "MOV dword ptr [ESI + 0x8],0x13f69b4"
    },
    {
      "address": "005a2ee7",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "005a2eea",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "005a2eec",
      "instruction": "JZ 0x005a2ef5"
    },
    {
      "address": "005a2eee",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "005a2ef0",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "005a2ef3",
      "instruction": "CALL EDX"
    },
    {
      "address": "005a2ef5",
      "instruction": "TEST byte ptr [ESP + 0x8],0x1"
    },
    {
      "address": "005a2efa",
      "instruction": "MOV dword ptr [ESI + 0x8],0x13ef094"
    },
    {
      "address": "005a2f01",
      "instruction": "MOV dword ptr [ESI + 0x4],0x13eb394"
    },
    {
      "address": "005a2f08",
      "instruction": "MOV dword ptr [ESI],0x13eb938"
    },
    {
      "address": "005a2f0e",
      "instruction": "JZ 0x005a2f19"
    },
    {
      "address": "005a2f10",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005a2f11",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "005a2f16",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "005a2f19",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "005a2f1b",
      "instruction": "POP ESI"
    },
    {
      "address": "005a2f1c",
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
  "original_bytes": 10916,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_note\": \"HONEST DISCLOSURE, because this field is a worker claim and not a machine token. The machine ABI envelope for this VA records return_semantics \\\"unclassified_in_EAX\\\" with return {register EAX, register_class \\\"aggregate_unknown\\\", type null, void_possible false} -- machine-vocabulary phrases that name no C++ type. Independently of that envelope the complete listing fixes the value: MOV EAX,ESI at 0x005a2f19 is the last write to EAX before the body's sole RET at 0x005a2f1c, it is unconditional on both paths, and ESI has held the receiver since 0x005a2ed1, so the returned value is the receiver p...\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"SwarmW2005a2ed0Receiver*\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f69b4\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 9,\n      \"symbol\": \"editor_camera_func54h_005a2320\",\n      \"va\": \"0x005a2320\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f69b4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"editor_camera_func24h_005a2050\",\n      \"va\": \"0x005a2050\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"EVIDENCE COVERAGE: expected WARN at 11 of 17 static categories available. callees_dependencies, contradictions, external_callees, globals, semantic_hypotheses and types are unavailable/MISSING in the committed pack. Nothing in this source can move the dimension.\",\n    \"FIELDS/OFFSETS reaches a grounded PASS, not a confirmed one: the machine-derived receiver record is bounds_only, so it can neither confirm nor refute a member identity. The source asserts no member for any of the four receiver displacements for that reason, and that is the intended resting state rather than a gap.\",\n    \"GLOBALS: expected WARN and unfixable from the source. The body stores six .rdata immediates and the xref export carries no data-reference edge type for this VA (dependencies.data_reference_count 0), so the validator has no second machine side to corroborate a store's mode against. The stores are declared rather than omitted, because omitting them would falsify the body.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"editor_camera_func54h_005a2320\",\n        \"reconstructed\": true,\n        \"va\": \"0x005a2320\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005a2323\",\n        \"direction\": \"in\",\n        \"other\": \"0x005a2320\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005a2f11\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x005a2320\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0103\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 6\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"FUN_005a2ed0\",\n  \"normalized_symbol\": \"FUN_005a2ed0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"cand
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
  "body_end": "005a2f1e",
  "body_span_bytes": 79,
  "body_start": "005a2ed0",
  "callees": [
    "FUN_00f47380"
  ],
  "callers": [
    "Editors::EditorCamera::func54h"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005a2ed0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005a2ed0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1a2ed0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005a2ed0(void)",
  "size_bytes": 79,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005a2ed0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f69b4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "013f69d0"
    },
    {
      "from": "005a2323"
    },
    {
      "from": "005a2333"
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
    "reconstruction/staging/pkg-swarm-w2-005a2ed0/sw2_005a2ed0.cpp",
    "reconstruction/staging/pkg-swarm-w2-005a2ed0/sw2_005a2ed0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-005a2ed0/sw2_005a2ed0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-005a2ed0/005a2ed0.json"
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
    "RUNTIME is GATED: the OpenSpore original has never been executed in this repository, so no runtime claim of any kind is made for 0x005a2ed0. A differential test would need a driver, and the single recorded caller (0x005a2320) is a two-instruction receiver-adjustor thunk that tail-jumps here rather than calling it."
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "SwarmW2005a2ed0Receiver*"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f69b4"
]
```

## Conflicts

```json
[]
```
