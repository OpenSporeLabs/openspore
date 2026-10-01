# Evidence 0x00451e50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7e877ab5c4073431fa21e3ead608d45c836bdd1f72230fba3126598e247e1c5d`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "read",
  "hidden_this_register": "ECX; spilled to [EBP - 0x8] at 0x00451e56 and reloaded three times",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_observation": "There is no write to EAX anywhere in the 17 instructions. At 0x004a675b, 0x004a67ba, 0x004a683c, 0x004a684d, 0x004a6893, 0x004a6947, 0x004a69fd, 0x004a6c15, 0x00495d7e, 0x0048d1e0, 0x004ad4cb and 0x004ad53e the next instruction after the CALL either reloads a register or starts a new statement, and in the two loops at 0x004a6728 and 0x004ad50c the loop increment follows immediately.",
  "return_register": null,
  "return_semantics": "void; no call site reads EAX or AL after the call",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [
    {
      "offset_in_frame": "[EBP + 0x8]",
      "read_at": "0x00451e77",
      "role": "the value propagated into the nested object",
      "signedness": "not narrowed by the body; the value is stored and reloaded as a full dword",
      "slot": 1,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4 (MOV ESP,EBP at 0x00451e7d, POP EBP at 0x00451e7f)"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "78549918d1a1b3deb3d2608c096c2467f9a32f9680ee474bd106da35d6b871aa",
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
        "obs-0019"
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
        "obs-0017"
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
        "obs-0006",
        "obs-0007",
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0017"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          396
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0017",
        "obs-0019"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0019"
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
        "obs-0019"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0019"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00451e50",
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
      "and_esp": null,
      "at": "0x00451e50",
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
      "sub": 8
    },
    {
      "at": "0x00451e51",
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
      "at": "0x00451e51",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x00451e53",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00451e56",
      "count": 3,
      "first_use": 3,
      "first_write_index": 7,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0x8],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00451e56",
      "base": "EBP",
      "disp": -8,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x8],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00451e59",
      "base": "EBP",
      "disp": -8,
      "id": "obs-0008",
      "index": 4,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + -0
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
    "va": "0x0048d010"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004956b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004a6690"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004ad470"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004ad4e0"
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
  "count": 17,
  "instructions": [
    {
      "address": "00451e50",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00451e51",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "00451e53",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00451e56",
      "instruction": "MOV dword ptr [EBP + -0x8],ECX"
    },
    {
      "address": "00451e59",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "00451e5c",
      "instruction": "CMP dword ptr [EAX + 0x18c],0x0"
    },
    {
      "address": "00451e63",
      "instruction": "JZ 0x00451e7d"
    },
    {
      "address": "00451e65",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "00451e68",
      "instruction": "MOV EDX,dword ptr [ECX + 0x18c]"
    },
    {
      "address": "00451e6e",
      "instruction": "ADD EDX,0x1c"
    },
    {
      "address": "00451e71",
      "instruction": "MOV dword ptr [EBP + -0x4],EDX"
    },
    {
      "address": "00451e74",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "00451e77",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "00451e7a",
      "instruction": "MOV dword ptr [EAX + 0x1c],ECX"
    },
    {
      "address": "00451e7d",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "00451e7f",
      "instruction": "POP EBP"
    },
    {
      "address": "00451e80",
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
  "original_bytes": 9513,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"read\",\n    \"hidden_this_register\": \"ECX; spilled to [EBP - 0x8] at 0x00451e56 and reloaded three times\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x4\",\n    \"return_observation\": \"There is no write to EAX anywhere in the 17 instructions. At 0x004a675b, 0x004a67ba, 0x004a683c, 0x004a684d, 0x004a6893, 0x004a6947, 0x004a69fd, 0x004a6c15, 0x00495d7e, 0x0048d1e0, 0x004ad4cb and 0x004ad53e the next instruction after the CALL either reloads a register or starts a new statement, and in the two loops at 0x004a6728 and 0x004ad50c the loop increment follows immediately.\",\n    \"return_register\": null,\n    \"return_semantics\": \"void; no call site reads EAX or AL after the call\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"offset_in_frame\": \"[EBP + 0x8]\",\n        \"read_at\": \"0x00451e77\",\n        \"role\": \"the value propagated into the nested object\",\n        \"signedness\": \"not narrowed by the body; the value is stored and reloaded as a full dword\",\n        \"slot\": 1,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4 (MOV ESP,EBP at 0x00451e7d, POP EBP at 0x00451e7f)\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0048d010\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004956b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a6690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ad470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ad4e0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0048d1e0\",\n        \"direction\": \"in\",\n        \"other\": \"0x0048d010\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00495d7e\",\n        \"direction\": \"in\",\n        \"other\": \"0x004956b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004a675b\",\n        \"direction\": \"in\",\n        \"other\": \"0x004a6690\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004a67ba\",\n        \"direction\": \"in\",\n        \"other\": \"0x004a6690\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004a683c\",\n        \"direction\": \"in\",\n        \"other\": \"0x004a6690\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004a684d\",\n        \"direction\": \"in\",\n        \"other\": \"0x004a6690\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004a6893\",\n        \"direction\": \"in\",\n        \"other\": \"0x004a6690\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004a6947\",\n        \"direction\": \"in\",\n        \"other\": \"0x004a6690\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004a69fd\",\n        \"direction\": \"in\",\n        \"other\": \"0x004a6690\",\n       
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
  "body_end": "00451e82",
  "body_span_bytes": 51,
  "body_start": "00451e50",
  "callees": [],
  "callers": [
    "FUN_0048d010",
    "FUN_004a6690",
    "FUN_004956b0",
    "FUN_004ad4e0",
    "FUN_004ad470"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00451e50",
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
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00451e50",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x51e50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00451e50(void)",
  "size_bytes": 51,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00451e50",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 12,
  "xrefs": [
    {
      "from": "00495d7e"
    },
    {
      "from": "004ad4cb"
    },
    {
      "from": "004ad53e"
    },
    {
      "from": "0048d1e0"
    },
    {
      "from": "004a675b"
    },
    {
      "from": "004a67ba"
    },
    {
      "from": "004a683c"
    },
    {
      "from": "004a684d"
    },
    {
      "from": "004a6893"
    },
    {
      "from": "004a6947"
    },
    {
      "from": "004a69fd"
    },
    {
      "from": "004a6c15"
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
    "reconstruction/staging/wave13-w1-dispatch-b05/editor_rigblock_00451e50.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b05/editor_rigblock_00451e50.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b05/editor_rigblock_00451e50_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b05/00451e50.json"
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
    "A runtime trace is required to determine the runtime value of receiver->[+0x18C] in each editor mode, the runtime class of the nested object, and the runtime content of the +0x38 dword.",
    "No original-process trace has been captured for 0x00451e50. Every claim in this record is static.",
    "The Cell stage has never been entered in any recorded run, so no editor path has a runtime oracle."
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
