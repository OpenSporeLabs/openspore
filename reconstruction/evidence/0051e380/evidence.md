# Evidence 0x0051e380

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7b2a9a131940d6d597c54b47b2dcc404e6bb1c00307b65f0af4660813928ef31`

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
  "ordinary_stack_argument_slots": [],
  "ordinary_stack_arguments": [],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_semantics": "EAX at the target's exit is the callee's EAX, a 32-bit word, on every path. The target's own instructions never write EAX.",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x0051e397"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/vftables.py@25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_read_without_deref"
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
  "content_sha256": "e9f85e18466e6c7597113857dd3a1341699f14c9a8825658fef316da2408c96a",
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
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0012"
      ],
      "claim": "calling convention is __thiscall: 0x0051e380 is slot 1 of the vptr-backed vftable at 0x013ef110, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 42,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 1,
        "table": "0x013ef110"
      }
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
      "at": "0x0051e380",
      "count": 4,
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
      "at": "0x0051e380",
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
      "sub": 16
    },
    {
      "at": "0x0051e381",
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
      "at": "0x0051e381",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x0051e383",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0051e386",
      "count": 1,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0x10],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0051e386",
      "base": "EBP",
      "disp": -16,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x10],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x0051e389",
      "base": "EBP",
      "disp": -16,
      "id": "obs-0008",
      "index": 4,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [EBP + -0x10]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x0051e389",
      "definite": true,
      "id": "obs-0009",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EBP + -0x10]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0051e38f",
      "id": "obs-0010",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00453540",
      "target": "0x00453540"
    },
    {
      "at": "0x0051e396",
      "id": "obs-0011",
      "index": 8,
      "kind": "REG_RESTORE",
      "raw": "POP EBP",
      "reg": "EBP"
    },
    {
      "at": "0x0051e397",
      "f
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
  "count": 10,
  "instructions": [
    {
      "address": "0051e380",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0051e381",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0051e383",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "0051e386",
      "instruction": "MOV dword ptr [EBP + -0x10],ECX"
    },
    {
      "address": "0051e389",
      "instruction": "MOV ECX,dword ptr [EBP + -0x10]"
    },
    {
      "address": "0051e38c",
      "instruction": "ADD ECX,0x4"
    },
    {
      "address": "0051e38f",
      "instruction": "CALL 0x00453540"
    },
    {
      "address": "0051e394",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0051e396",
      "instruction": "POP EBP"
    },
    {
      "address": "0051e397",
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
  "original_bytes": 7751,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [],\n    \"ordinary_stack_arguments\": [],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"EAX at the target's exit is the callee's EAX, a 32-bit word, on every path. The target's own instructions never write EAX.\",\n    \"return_type\": \"std::uint32_t\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET at 0x0051e397\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ef110,vtable:0x013f2194\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 6,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f1a30\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 4,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014582e0\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951220\",\n      \"va\": \"0x00951220\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01414614,vtable:0x01458024\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The persisted evidence pack for this target holds no disassembly listing, so the machine-derived receiver record, parse record, and dispatch record are all absent. CONTROL FLOW, GLOBALS, CONSTANTS, FIELDS/OFFSETS, and VIRTUAL DISPATCH cannot be adjudicated against a listing and remain NOT_AVAILABLE; this is a capability ceiling of the evidence pack, not of the reconstruction.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0051e38f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00453540\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0048\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:g_subobject_forward_ports\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_0051e380\",\n  \"normalized_symbol\": \"FUN_0051e380\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/subobject-forward-0051e380/subobject_forward_0051e380.cpp\",\n      \"reconstruction/staging/subobject-forward-0051e380/subobject_forward_0051e380.hpp\",\n      \"reconstruction/staging/subobject-forward-0051e380/subobject_forward_0051e380_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/subobject-forward-0051e380/0051e380.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Editor\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"editor-core\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:0051e380\",\n    \"name\": \"FUN_0051e380\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n    
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
  "body_end": "0051e397",
  "body_span_bytes": 24,
  "body_start": "0051e380",
  "callees": [
    "FUN_00453540"
  ],
  "callers": [],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "0051e380",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_0051e380",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x11e380",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0051e380(void)",
  "size_bytes": 24,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0051e380",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f2194",
      "0x013f1a30",
      "0x01458024",
      "0x01458788",
      "0x013f21d8",
      "0x013f276c",
      "0x013f2d68",
      "0x013ef110",
      "0x01453998",
      "0x013ef1c0",
      "0x013ef270",
      "0x013ef320",
      "0x013ef3c0",
      "0x013f2698",
      "0x013f6e78",
      "0x0140f558",
      "0x01412454",
      "0x01414614",
      "0x01453254",
      "0x014582e0"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 45,
  "xrefs": [
    {
      "from": "013ef114"
    },
    {
      "from": "013ef1c4"
    },
    {
      "from": "013ef274"
    },
    {
      "from": "013ef324"
    },
    {
      "from": "013ef3d4"
    },
    {
      "from": "013ef6b8"
    },
    {
      "from": "013f0330"
    },
    {
      "from": "013f1a60"
    },
    {
      "from": "013f1a38"
    },
    {
      "from": "013f1c80"
    },
    {
      "from": "013f220c"
    },
    {
      "from": "013f21d0"
    },
    {
      "from": "013f26d4"
    },
    {
      "from": "013f27a4"
    },
    {
      "from": "013f2da4"
    },
    {
      "from": "013f6e7c"
    },
    {
      "from": "0140da8c"
    },
    {
      "from": "0140dab4"
    },
    {
      "from": "0140f590"
    },
    {
      "from": "014123f0"
    },
    {
      "from": "01412490"
    },
    {
      "from": "01413084"
    },
    {
      "from": "01414650"
    },
    {
      "from": "01414958"
    },
    {
      "from": "01458168"
    },
    {
      "from": "01458340"
    },
    {
      "from": "01458710"
    },
    {
      "from": "01458c74"
    },
    {
      "from": "01458d20"
    },
    {
      "from": "01459464"
    },
    {
      "from": "01459674"
    },
    {
      "from": "01459948"
    },
    {
      "from": "0148e74c"
    },
    {
      "from": "0148f0d8"
    },
    {
      "from": "0148ff10"
    },
    {
      "from": "01490340"
    },
    {
      "from": "0145328c"
    },
    {
      "from": "01459a24"
    },
    {
      "from": "014539d0"
    },
    {
      "from": "0148f4f0"
    },
    {
      "from": "004b75e3"
    },
    {
      "from": "0145805c"
    },
    {
      "from": "014587c0"
    },
    {
      "from": "0145987c"
    },
    {
      "from": "01459ac0"
    }
  ]
}
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:g_subobject_forward_ports"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/subobject-forward-0051e380/subobject_forward_0051e380.cpp",
    "reconstruction/staging/subobject-forward-0051e380/subobject_forward_0051e380.hpp",
    "reconstruction/staging/subobject-forward-0051e380/subobject_forward_0051e380_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/subobject-forward-0051e380/0051e380.json"
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
  "gates": [],
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
  "runtime_gated": false,
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
  "std::uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0051e380",
  "vtable:0x013ef110",
  "vtable:0x013ef1c0",
  "vtable:0x013ef270",
  "vtable:0x013ef320",
  "vtable:0x013ef3c0",
  "vtable:0x013ef6a4",
  "vtable:0x013f031c",
  "vtable:0x013f1a30",
  "vtable:0x013f1c6c",
  "vtable:0x013f2194",
  "vtable:0x013f21d8",
  "vtable:0x013f2698",
  "vtable:0x013f276c",
  "vtable:0x013f2d68",
  "vtable:0x013f6e78"
]
```

## Conflicts

```json
[]
```
