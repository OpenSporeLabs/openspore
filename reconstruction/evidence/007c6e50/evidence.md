# Evidence 0x007c6e50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `20c09fa6a9d48322d2459ca6d8a92c4a71d7afe8bc30a9fe84e88a497155566e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "ret_form": "plain RET",
  "return_type": "bool",
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_read_without_deref",
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
  "content_sha256": "f69f83522d707a7d05282eba44c0235fff1b8a3f74faa8f88dae5bd1c5bc1a0c",
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
    "ghidra_parameter_count": 1,
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
        "obs-0017"
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
        "obs-0002",
        "obs-0003",
        "obs-0005"
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
        "obs-0017"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0017"
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
        "obs-0017"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0017"
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
      "at": "0x007c6e50",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "INC EBX",
      "reg": "EBX",
      "write_kind": "arith"
    },
    {
      "at": "0x007c6e55",
      "count": 6,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESI + 0x4]",
      "reg": "ESI"
    },
    {
      "at": "0x007c6e55",
      "definite": true,
      "id": "obs-0003",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x4]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007c6e58",
      "definite": true,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ESI]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007c6e5a",
      "count": 2,
      "first_use": 5,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x007c6e5b",
      "count": 1,
      "first_use": 6,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 6,
      "kind": "REG_READ",
      "raw": "PUSH EDX",
      "reg": "EDX"
    },
    {
      "at": "0x007c6e5e",
      "id": "obs-0007",
      "index": 8,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00e25bd0",
      "target": "0x00e25bd0"
    },
    {
      "at": "0x007c6e63",
      "count": 1,
      "first_use": 9,
      "first_write_index": null,
      "id": "obs-0008",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + 0xa8],0x0",
      "reg": "EBP"
    },
    {
      "at": "0x007c6e63",
      "base": "EBP",
      "disp": 168,
      "id": "obs-0009",
      "index": 9,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + 0xa8],0x0",
      "reason": "untrusted_frame",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x007c6e6d",
      "definite": true,
      "id": "obs-0010",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007c6e72",
      "count": 1,
      "first_use": 12,
      "first_write_index": 10,
      "id": "obs-0011",
      "index": 12,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x007c6e76",
      "id": "obs-0012",
      "index": 15,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00e25bd0",
      "target": "0x00e25bd0"
    },
    {
      "at": "0x007c6e7b",
      "id": "obs-0013",
      "index": 16,
      "kind": "REG_RESTORE",
      "raw": "POP EDI",
      "reg": "EDI"
    },
    {
      "at": "0x007c6e7c",
      "id": "obs-0014",
      "index": 17,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x007c6e7d",
      "id": "obs-0015",
      "index": 18,
      "kind": "REG_RESTORE",
  
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
  "count": 22,
  "instructions": [
    {
      "address": "007c6e50",
      "instruction": "INC EBX"
    },
    {
      "address": "007c6e51",
      "instruction": "CMP EBX,EDI"
    },
    {
      "address": "007c6e53",
      "instruction": "JL 0x007c6e40"
    },
    {
      "address": "007c6e55",
      "instruction": "MOV ECX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "007c6e58",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "007c6e5a",
      "instruction": "PUSH ECX"
    },
    {
      "address": "007c6e5b",
      "instruction": "PUSH EDX"
    },
    {
      "address": "007c6e5c",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "007c6e5e",
      "instruction": "CALL 0x00e25bd0"
    },
    {
      "address": "007c6e63",
      "instruction": "MOV dword ptr [EBP + 0xa8],0x0"
    },
    {
      "address": "007c6e6d",
      "instruction": "MOV EAX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "007c6e70",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "007c6e72",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007c6e73",
      "instruction": "PUSH ECX"
    },
    {
      "address": "007c6e74",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "007c6e76",
      "instruction": "CALL 0x00e25bd0"
    },
    {
      "address": "007c6e7b",
      "instruction": "POP EDI"
    },
    {
      "address": "007c6e7c",
      "instruction": "POP ESI"
    },
    {
      "address": "007c6e7d",
      "instruction": "POP EBX"
    },
    {
      "address": "007c6e7e",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "007c6e80",
      "instruction": "POP EBP"
    },
    {
      "address": "007c6e81",
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
  "original_bytes": 6192,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"ret_form\": \"plain RET\",\n    \"return_type\": \"bool\",\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"camera_light_origin_helper_007c4900\",\n      \"va\": \"0x007c4900\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"camera_manager_set_active_007c64c0\",\n      \"va\": \"0x007c64c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"cell_get_globals_data_00e4ce20\",\n      \"va\": \"0x00e4ce20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"cell_move_player_to_mouse_position_00e5b790\",\n      \"va\": \"0x00e5b790\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 8,\n      \"symbol\": \"editor_camera_func24h_005a2050\",\n      \"va\": \"0x005a2050\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 8,\n      \"symbol\": \"editor_camera_func54h_005a2320\",\n      \"va\": \"0x005a2320\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 8,\n      \"symbol\": \"editor_camera_on_exit_00c2e640\",\n      \"va\": \"0x00c2e640\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCameraState\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x007c6e5e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e25bd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007c6e76\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e25bd0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0241\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"camera_manager_dispose_007c6e50\",\n  \"normalized_symbol\": \"camera_manager_dispose_007c6e50\",\n  \"observed_mechanics\": [\n    \"{\\\"active_index\\\": \\\"+0xa8\\\", \\\"camera_vector\\\": {\\\"begin\\\": \\\"+0x80\\\", \\\"camera_dispose_slot\\\": \\\"+0x14\\\", \\\"end\\\": \\\"+0x84\\\"}, \\\"guard_field\\\": \\\"+0x0c byte\\\", \\\"guard_semantics\\\": \\\"If +0x0c is zero, return true immediately. Otherwise write zero to +0x0c before any teardown operation.\\\", \\\"message_registry\\\": {\\\"base\\\": \\\"+0x60\\\", \\\"bucket_count\\\": \\\"+0x68\\\", \\\"bucket_pointer\\\": \\\"+0x64\\\"}, \\\"object_fields\\\": {\\\"current_object\\\": \\\"+0x10\\\", \\\"current_object_end\\\": \\\"+0x14\\\"}, \\\"observed_call_order\\\": [\\\"read +0x0c and return true when zero\\\", \\\"write zero to +0x0c\\\", \\\"acquire App::IAppSystem through 0x0067dcc0 and invoke vtable +0x2c with 0xf...\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-CAMERA-WAVE7\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-CAMERA-WAVE7\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-CAMERA-WAVE7\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved_after_parallel_review\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"Original application camera-manager teardown trace is not available; no runtime promotion is claimed.\",\n      \"runtime observation required\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": \"src/reconstruction/pk
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
  "body_end": "007c6e81",
  "body_span_bytes": 66,
  "body_start": "007c6e40",
  "callees": [
    "FUN_00e25bd0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "007c6e50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cCameraManager::Dispose",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCameraManager *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x3c6e50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cCameraManager::Dispose(cCameraManager * this)",
  "size_bytes": 66,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007c6e50",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "007c6e47"
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
  "file": "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
    "src/reconstruction/pkg_camera_wave7/camera_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-camera-wave7/007c6e50.json"
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
    "Original application camera-manager teardown trace is not available; no runtime promotion is claimed.",
    "runtime observation required"
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
  "OpaqueCameraState",
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
