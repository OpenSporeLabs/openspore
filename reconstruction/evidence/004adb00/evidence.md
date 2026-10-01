# Evidence 0x004adb00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a6d1c5055a608a9b2991cf2f5576ec2e0c28ec0e05557dca406d88c8a756a11b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX, spilled to [EBP-0x4] at 0x004adb04 and reloaded at 0x004adb07",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x004adb0a is FLD dword ptr [EAX+0x40], an 80-bit x87 load whose 32-bit single-precision source is promoted to extended precision; nothing is written to EAX, XMM0 or any general register after the load. Every inspected caller consumes the result with FSTP, either to memory (0x0043fda3, 0x005d37c7) or to [ESP+0xc] (0x005d37bc), which is only correct for an ST0 return. On x86-32 a float return therefore does NOT travel in XMM0 as it would under a different ABI, and Ghidra's float10 rendering is the accurate one.",
  "return_register": "ST(0) of the x87 stack",
  "return_semantics": "the 32-bit float stored at receiver+0x40, returned unchanged",
  "return_type": "float",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single exit at 0x004adb10"
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBP"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "bd2320cc0ba63ad4900dbd8dd64dafaa3fce89cf83518e379a56166253b91010",
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
        "obs-0005",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          64
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0012"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x004adb00",
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
      "at": "0x004adb00",
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
      "sub": null
    },
    {
      "at": "0x004adb01",
      "count": 1,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x004adb01",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004adb03",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x004adb04",
      "base": "EBP",
      "disp": -4,
      "id": "obs-0006",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x4],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x004adb07",
      "base": "EBP",
      "disp": -4,
      "id": "obs-0007",
      "index": 4,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + -0x4]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x004adb07",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBP + -0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x004adb0a",
      "count": 1,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_READ",
      "raw": "FLD float ptr [EAX + 0x40]",
      "reg": "EAX"
    },
    {
      "at": "0x004adb0d",
      "definite": true,
      "id": "obs-0010",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ESP,EBP",
      "reg": "ESP",
      "write_kind": "reg"
    },
    {
      "at": "0x004adb0f",
      "id": "obs-0011",
      "index": 7,
      "kind": "REG_RESTORE",
      "raw": "POP EBP",
      "reg": "EBP"
    },
    {
      "at": "0x004adb10",
      "form": "RET",
      "id": "obs-0012",
      "imm": null,
      "index": 8,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 9,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": true,
      "fp": true,
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at":
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
    "va": "0x0043fc20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00485b90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00486910"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0048dcd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0049a2a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005b9840"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005be500"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005d36e0"
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
  "count": 9,
  "instructions": [
    {
      "address": "004adb00",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004adb01",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004adb03",
      "instruction": "PUSH ECX"
    },
    {
      "address": "004adb04",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "004adb07",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004adb0a",
      "instruction": "FLD float ptr [EAX + 0x40]"
    },
    {
      "address": "004adb0d",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004adb0f",
      "instruction": "POP EBP"
    },
    {
      "address": "004adb10",
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
  "original_bytes": 9449,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX, spilled to [EBP-0x4] at 0x004adb04 and reloaded at 0x004adb07\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x004adb0a is FLD dword ptr [EAX+0x40], an 80-bit x87 load whose 32-bit single-precision source is promoted to extended precision; nothing is written to EAX, XMM0 or any general register after the load. Every inspected caller consumes the result with FSTP, either to memory (0x0043fda3, 0x005d37c7) or to [ESP+0xc] (0x005d37bc), which is only correct for an ST0 return. On x86-32 a float return therefore does NOT travel in XMM0 as it would under a different ABI, and Ghidra's float10 rendering is the accurate one.\",\n    \"return_register\": \"ST(0) of the x87 stack\",\n    \"return_semantics\": \"the 32-bit float stored at receiver+0x40, returned unchanged\",\n    \"return_type\": \"float\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"single exit at 0x004adb10\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043fc20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00485b90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00486910\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0048dcd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0049a2a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005b9840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005be500\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005d36e0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0043fda9\",\n        \"direction\": \"in\",\n        \"other\": \"0x0043fc20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00485bb0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00485b90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00485c8d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00485b90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004869df\",\n        \"direction\": \"in\",\n        \"other\": \"0x00486910\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0048ddfe\",\n        \"direction\": \"in\",\n        \"other\": \"0x0048dcd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0049ad2d\",\n        \"direction\": \"in\",\n        \"other\": \"0x0049a2a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0049ae31\",\n        \"direction\": \"in\",\n        \"other\": \"0x0049a2a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005b9a14\",\n        \"direction\": \"in\",\n        \"other\": \"0x005b9840\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": 
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
  "body_end": "004adb10",
  "body_span_bytes": 17,
  "body_start": "004adb00",
  "callees": [],
  "callers": [
    "FUN_005b9840",
    "FUN_0043fc20",
    "FUN_005d36e0",
    "FUN_005be500",
    "FUN_00485b90",
    "FUN_0048dcd0",
    "FUN_00486910",
    "FUN_0049a2a0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "004adb00",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_004adb00",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xadb00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004adb00(void)",
  "size_bytes": 17,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004adb00",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 11,
  "xrefs": [
    {
      "from": "0043fda9"
    },
    {
      "from": "00485bb0"
    },
    {
      "from": "00485c8d"
    },
    {
      "from": "004869df"
    },
    {
      "from": "0048ddfe"
    },
    {
      "from": "0049ad2d"
    },
    {
      "from": "0049ae31"
    },
    {
      "from": "005d37c2"
    },
    {
      "from": "005b9a14"
    },
    {
      "from": "005be68d"
    },
    {
      "from": "005b49be"
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
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_model_min_height_getter.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_model_min_height_getter.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_model_min_height_getter_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b03/004adb00.json"
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
    "A differential test must confirm that the value is returned in ST0 and not in XMM0 in the shipping build. The static evidence for ST0 is strong - FLD with no FXCH and FSTP at every consumer - but it is static.",
    "A trace with a concrete receiver is required before the owning class can be named, because no vtable could be located.",
    "No original-process trace exists for this function. Static analysis cannot show the live value of the +0x40 float, so the SDK's documented -2.0 default is unverified for the shipping build."
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
  "float"
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
