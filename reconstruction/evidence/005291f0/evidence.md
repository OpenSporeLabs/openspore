# Evidence 0x005291f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1f3d8d089a050416243b0c9a8fb9e9a1a8aad84967334c1b7ef4c4f192e512e1`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__cdecl observed",
  "hidden_this_register": null,
  "return_register": null,
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "matrix",
      "observed_use": "Copies 64 bytes from matrix into the fixed global Matrix4 storage.",
      "position": 1,
      "type": "const Matrix4*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "type",
      "observed_use": "Writes the global transform type before the matrix copy.",
      "position": 2,
      "type": "MatrixType",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 0
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
      "entry_ESP+0x4",
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "ebp_offset": "EBP+0xc",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "EBP"
    ],
    "stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "ebp_offset": "EBP+0xc",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
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
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "e0588921c901049c0f4fd942e3823232324cb6e1991e285d6da788604dd08710",
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
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": "__cdecl observed"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0026"
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
        "obs-0008",
        "obs-0014",
        "obs-0018",
        "obs-0020",
        "obs-0022",
        "obs-0024"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0013",
        "obs-0017",
        "obs-0019",
        "obs-0022"
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
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0013",
        "obs-0017",
        "obs-0019",
        "obs-0022"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0014",
        "obs-0018",
        "obs-0020",
        "obs-0022",
        "obs-0024"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x005291f0",
      "count": 8,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": 4294967280,
      "at": "0x005291f0",
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
      "at": "0x005291f1",
      "count": 6,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x005291f1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x005291f3",
   
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
    "va": "0x00528e90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006eae40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006ee6f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007a8a50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b80ea0"
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
  "count": 37,
  "instructions": [
    {
      "address": "005291f0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "005291f1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "005291f3",
      "instruction": "AND ESP,0xfffffff0"
    },
    {
      "address": "005291f6",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "005291f9",
      "instruction": "MOV EAX,[0x016f9528]"
    },
    {
      "address": "005291fe",
      "instruction": "OR EAX,0x1"
    },
    {
      "address": "00529201",
      "instruction": "MOV [0x016f9528],EAX"
    },
    {
      "address": "00529206",
      "instruction": "MOV ECX,dword ptr [EBP + 0xc]"
    },
    {
      "address": "00529209",
      "instruction": "MOV dword ptr [0x016f96a0],ECX"
    },
    {
      "address": "0052920f",
      "instruction": "MOV EDX,0x1"
    },
    {
      "address": "00529214",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "00529216",
      "instruction": "JZ 0x00529267"
    },
    {
      "address": "00529218",
      "instruction": "MOV dword ptr [0x016fa380],0x16fa4f0"
    },
    {
      "address": "00529222",
      "instruction": "MOV EAX,[0x016fa380]"
    },
    {
      "address": "00529227",
      "instruction": "MOV dword ptr [ESP + 0xc],EAX"
    },
    {
      "address": "0052922b",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "0052922f",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "00529232",
      "instruction": "MOVAPS XMM0,xmmword ptr [EDX]"
    },
    {
      "address": "00529235",
      "instruction": "MOVAPS xmmword ptr [ECX],XMM0"
    },
    {
      "address": "00529238",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0052923b",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "0052923f",
      "instruction": "MOVAPS XMM0,xmmword ptr [EAX + 0x10]"
    },
    {
      "address": "00529243",
      "instruction": "MOVAPS xmmword ptr [ECX + 0x10],XMM0"
    },
    {
      "address": "00529247",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0052924a",
      "instruction": "MOV EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "0052924e",
      "instruction": "MOVAPS XMM0,xmmword ptr [EDX + 0x20]"
    },
    {
      "address": "00529252",
      "instruction": "MOVAPS xmmword ptr [EAX + 0x20],XMM0"
    },
    {
      "address": "00529256",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "00529259",
      "instruction": "MOV EDX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "0052925d",
      "instruction": "MOVAPS XMM0,xmmword ptr [ECX + 0x30]"
    },
    {
      "address": "00529261",
      "instruction": "MOVAPS xmmword ptr [EDX + 0x30],XMM0"
    },
    {
      "address": "00529265",
      "instruction": "JMP 0x0052926f"
    },
    {
      "address": "00529267",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0052926a",
      "instruction": "MOV [0x016fa380],EAX"
    },
    {
      "address": "0052926f",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "00529271",
      "instruction": "POP EBP"
    },
    {
      "address": "00529272",
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
  "original_bytes": 6462,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__cdecl observed\",\n    \"hidden_this_register\": null,\n    \"return_register\": null,\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"matrix\",\n        \"observed_use\": \"Copies 64 bytes from matrix into the fixed global Matrix4 storage.\",\n        \"position\": 1,\n        \"type\": \"const Matrix4*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"type\",\n        \"observed_use\": \"Writes the global transform type before the matrix copy.\",\n        \"position\": 2,\n        \"type\": \"MatrixType\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"WAVE6-PRESENTATION\",\n      \"score\": 14,\n      \"symbol\": \"transform_pre_transform_by_0040ccb0\",\n      \"va\": \"0x0040ccb0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"WAVE6-PRESENTATION\",\n      \"score\": 8,\n      \"symbol\": \"renderware_mesh_set_indices_count_011f96e0\",\n      \"va\": \"0x011f96e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"WAVE6-PRESENTATION\",\n      \"score\": 8,\n      \"symbol\": \"renderware_mesh_set_index_buffer_011f9710\",\n      \"va\": \"0x011f9710\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The dirty, type, fixed-storage pointer, and 64-byte matrix publication order is exact; concrete global owner, initialization, and valid runtime types remain unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"Global state ownership and matrix-type policy remain outside this body.\",\n    \"No runtime graphics-state trace is available.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"Matrix4\",\n  \"cluster\": null,\n  \"confidence\": 0.96,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00528e90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006eae40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006ee6f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007a8a50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b80ea0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005291da\",\n        \"direction\": \"in\",\n        \"other\": \"0x00528e90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006eb1ac\",\n        \"direction\": \"in\",\n        \"other\": \"0x006eae40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006eb477\",\n        \"direction\": \"in\",\n        \"other\": \"0x006eae40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006eb641\",\n        \"direction\": \"in\",\n        \"other\": \"0x006eae40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006ee8b8\",\n        \"direction\": \"in\",\n        \"other\": \"0x006ee6f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007a8b90\",\n        \"direction\": \"in\",\n        \"other\": \"0x007a8a50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b80f54\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b80ea0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 5,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [\n      \"0x00528e90\",\n      \"0x006eae40\",\n      \"0x006ee6f0\",\n      \"0x007a8a50\",\n      \"0x00b80ea0\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0049\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [\n    \"global:0x016f9528\",\n    \"global:The body directly references 0x016f9528, 0x016f96a0, 0x016fa380, and 0x016fa4f0.\"\n  ],\n  \"integration_status\": \"integrated\",\n  \"name\": \"graphics_global_state_set_transform_005291f0\",\n  \"normalized_symbol\": \"graphics_global_state_set_transform_005291f0\",\n  \"observed_mechanics\": [\n    \"cdecl matrix and type words\",\n    \"set dirty bit 0x01 at 0x016f9528 first\",\n    \"store type at 0x016f96a0\",\n    \"publish fixed storage address at 0x016fa380\",\n    \"copy 64 bytes into 0x016fa4f0\",\n    \"no gameplay-state access\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"WAVE6-PRESENTATION\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"WAVE6-PRESENTATION\",\n    \"queue_state\": null\n  },\n  \"package\": \"WAVE6-PRESENTATION\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-graphics-transform-global-publication\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_graphics_transform_publication_order_runtime_owner_unknown\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": nu
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
  "body_end": "00529272",
  "body_span_bytes": 131,
  "body_start": "005291f0",
  "callees": [],
  "callers": [
    "FUN_006eae40",
    "FUN_006ee6f0",
    "FUN_00b80ea0",
    "FUN_007a8a50",
    "Skinner::cSkinnerTexturePainter::StartRender"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "005291f0",
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
  "name": "Graphics::GlobalState::SetTransform",
  "namespace": "Graphics",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "matrix",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "Matrix4 *"
    },
    {
      "name": "type",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "MatrixType"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x1291f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Graphics::GlobalState::SetTransform(Matrix4 * matrix, MatrixType type)",
  "size_bytes": 131,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005291f0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "005291da"
    },
    {
      "from": "006eb1ac"
    },
    {
      "from": "006eb477"
    },
    {
      "from": "006eb641"
    },
    {
      "from": "006ee8b8"
    },
    {
      "from": "007a8b90"
    },
    {
      "from": "00b80f54"
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
  "global:0x016f9528",
  "global:The body directly references 0x016f9528, 0x016f96a0, 0x016fa380, and 0x016fa4f0."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/wave6_presentation/presentation_boundary.cpp",
  "files": [
    "src/reconstruction/wave6_presentation/presentation_boundary.cpp",
    "src/reconstruction/wave6_presentation/presentation_boundary.hpp",
    "src/reconstruction/wave6_presentation/presentation_boundary_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-presentation/005291f0.json"
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
    "gate-graphics-transform-global-publication"
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
  "Matrix4",
  "MatrixType",
  "const Matrix4*",
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
