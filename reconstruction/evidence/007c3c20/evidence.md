# Evidence 0x007c3c20

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d96c2299c22f94e19e2b4161b27fedd6d668be4198305141faa93f1b025f731b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueWorldViewer*",
  "return_register": null,
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "source",
      "position": 1,
      "type": "const std::uint32_t*",
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
  "content_sha256": "8caea5193eebc6a4f0279238576c8c1b80a332ea3e135a07abe15872ecd54e67",
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
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0008"
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
        "obs-0006",
        "obs-0007"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          320,
          324,
          328,
          332
        ],
        "register": "ECX",
        "written_through": 4
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0008"
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
        "obs-0008"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008"
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
      "at": "0x007c3c20",
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
      "at": "0x007c3c20",
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
      "at": "0x007c3c20",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007c3c24",
      "count": 5,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x007c3c24",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007c3c26",
      "count": 4,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ECX + 0x140],EDX",
      "reg": "ECX"
    },
    {
      "at": "0x007c3c26",
      "count": 3,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0007",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ECX + 0x140],EDX",
      "reg": "EDX"
    },
    {
      "at": "0x007c3c47",
      "form": "RET 0x4",
      "id": "obs-0008",
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
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": nul
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
    "va": "0x005812b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006e3100"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006e4210"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006efe90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f3f20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f41e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076bc91"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076c210"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0077f040"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b3340"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b7ac0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b8cb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007bd750"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007bfee0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007c0780"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007c6200"
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
      "address": "007c3c20",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "007c3c24",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "007c3c26",
      "instruction": "MOV dword ptr [ECX + 0x140],EDX"
    },
    {
      "address": "007c3c2c",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "007c3c2f",
      "instruction": "MOV dword ptr [ECX + 0x144],EDX"
    },
    {
      "address": "007c3c35",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "007c3c38",
      "instruction": "MOV dword ptr [ECX + 0x148],EDX"
    },
    {
      "address": "007c3c3e",
      "instruction": "MOV EAX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "007c3c41",
      "instruction": "MOV dword ptr [ECX + 0x14c],EAX"
    },
    {
      "address": "007c3c47",
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
  "original_bytes": 10615,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueWorldViewer*\",\n    \"return_register\": null,\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"source\",\n        \"position\": 1,\n        \"type\": \"const std::uint32_t*\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:const std::uint32_t*\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"palette_safe_wave11_fill_node_array_005c7ff0\",\n      \"va\": \"0x005c7ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_Update_0059b4b0\",\n      \"va\": \"0x0059b4b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n      \"va\": \"0x0059cb10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n      \"va\": \"0x0059cea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n      \"va\": \"0x0059cf00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No runtime source values or downstream reader semantics are available.\",\n    \"The receiver layout remains an evidence-bounded opaque layout.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005812b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006e3100\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006e4210\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006efe90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f3f20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f41e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076bc91\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076c210\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0077f040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b3340\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b7ac0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b8cb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bd750\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bfee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007c0780\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007c6200\"\n      },\n      {\n        \"name\": \"App::cCameraManager::SetActiveCameraByID\",\n        \"reconstructed\": false,\n        \"va\": \"0x007c6750\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f67da0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f9e280\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fa3860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fa6480\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005813aa\",\n        \"direction\": \"in\",\n        \"other\": \"0x005812b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005814cd\",\n        \"direction\": \"in\",\n        \"other\": \"0x005812b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005815a4\",\n        \"d
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
  "body_end": "007c3c49",
  "body_span_bytes": 42,
  "body_start": "007c3c20",
  "callees": [],
  "callers": [
    "FUN_00f9e280",
    "FUN_007bfee0",
    "FUN_0077f040",
    "FUN_007c0780",
    "FUN_0076c210",
    "FUN_007b7ac0",
    "FUN_00f67da0",
    "FUN_007bd750",
    "FUN_00fa3860",
    "App::cCameraManager::SetActiveCameraByID",
    "FUN_005812b0",
    "FUN_006f41e0",
    "FUN_007b3340",
    "FUN_006efe90",
    "FUN_006e3100",
    "FUN_007b8cb0",
    "FUN_006e4210",
    "FUN_00fa6480",
    "FUN_006f3f20",
    "FUN_007c6200",
    "FUN_0076bc91"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "007c3c20",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_007c3c20",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3c3c20",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_007c3c20(void)",
  "size_bytes": 42,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007c3c20",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 34,
  "xrefs": [
    {
      "from": "005813aa"
    },
    {
      "from": "005814cd"
    },
    {
      "from": "005815a4"
    },
    {
      "from": "006e3b70"
    },
    {
      "from": "006e4e91"
    },
    {
      "from": "006f3f84"
    },
    {
      "from": "006f425b"
    },
    {
      "from": "006f02d8"
    },
    {
      "from": "0076bfdf"
    },
    {
      "from": "0076c4a6"
    },
    {
      "from": "0077f125"
    },
    {
      "from": "0077f1a1"
    },
    {
      "from": "007b340c"
    },
    {
      "from": "007b7d7a"
    },
    {
      "from": "007b802b"
    },
    {
      "from": "007b8d07"
    },
    {
      "from": "007bd7a7"
    },
    {
      "from": "007c05d1"
    },
    {
      "from": "007c0f92"
    },
    {
      "from": "007c62c9"
    },
    {
      "from": "00f67e3d"
    },
    {
      "from": "00f9e302"
    },
    {
      "from": "00fa3915"
    },
    {
      "from": "00fa3a15"
    },
    {
      "from": "00fa65b1"
    },
    {
      "from": "007b3b12"
    },
    {
      "from": "007b666d"
    },
    {
      "from": "00b34183"
    },
    {
      "from": "00581af5"
    },
    {
      "from": "00581c4c"
    },
    {
      "from": "00581d20"
    },
    {
      "from": "00581ec0"
    },
    {
      "from": "00581fc0"
    },
    {
      "from": "007c6b27"
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
    "reconstruction/staging/pkg14-a1-world-state/world_state.cpp",
    "reconstruction/staging/pkg14-a1-world-state/world_state.hpp",
    "reconstruction/staging/pkg14-a1-world-state/world_state_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg14-a1-world-state/007c3c20.json"
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueWorldViewer*",
  "cViewer",
  "const std::uint32_t*",
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
