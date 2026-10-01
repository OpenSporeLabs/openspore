# Evidence 0x00b8d9b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7d94b8f8507ed7f3c9adac6b97204d60b1e8bd4f4a33e561e94100e069f7e4be`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "read; ESI holds it for the whole body and is pushed as the argument to both callees",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET (with a tail JMP to 0x00c4b220 on the deepest path)",
  "return_observation": "Three exits write EAX: 0x00b8d9e1 MOV EAX,EDI (provably 0 on that path), 0x00b8d9e3 the preserved EDI from tier 1, and the tail transfer at 0x00b8d9dc which returns 0x00c4b220's EAX unchanged. The full dword is defined on every exit.",
  "return_register": "EAX",
  "return_semantics": "an opaque context handle: the non-null result of the tier-1 registry resolve, otherwise the tier-2 mission context's lazily resolved +0x1F4 slot, otherwise exactly 0",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "ESI",
    "EDI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00b8d9e5, or JMP 0x00c4b220 at 0x00b8d9dc"
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
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
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
  "content_sha256": "8bfbcf5c0bc7d68e14114ea047e3eba95c2e2298965c4800307804d00186873a",
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
    "ghidra_parameter_count": 0,
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
        "obs-0018"
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
        "obs-0006",
        "obs-0007"
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
        "obs-0018"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0018"
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
        "obs-0014",
        "obs-0018"
      ],
      "claim": "the function can reach a caller by transferring out of the listing, so the path that actually returns was never observed",
      "confidence": "UNKNOWN",
      "id": "T2",
      "value": {
        "form": "epilogue_then_jmp"
      }
    },
    {
      "based_on": [
        "obs-0018"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018"
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
      "at": "0x00b8d9b0",
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
      "at": "0x00b8d9b1",
      "count": 1,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b8d9b1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b8d9b3",
      "count": 2,
      "first_use": 2,
      "first_write_index": 7,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b8d9b5",
      "id": "obs-0005",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d2a0",
      "target": "0x00b3d2a0"
    },
    {
      "at": "0x00b8d9ba",
      "count": 4,
      "first_use": 5,
      "first_write_index": 20,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00b8d9ba",
      "definite": true,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00b8d9bc",
      "id": "obs-0008",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00bb99e0",
      "target": "0x00bb99e0"
    },
    {
      "at": "0x00b8d9c1",
      "definite": true,
      "id": "obs-0009",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,EAX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b8d9c8",
      "id": "obs-0010",
      "index": 11,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00feb9f0",
      "target": "0x00feb9f0"
    },
    {
      "at": "0x00b8d9cf",
      "id": "obs-0011",
      "index": 13,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00fee220",
      "target": "0x00fee220"
    },
    {
      "at": "0x00b8d9d8",
      "id": "obs-0012",
      "index": 16,
      "kind": "REG_RESTORE",
      "raw": "POP EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b8d9db",
      "id": "obs-0013",
      "index": 18,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b8d9dc",
      "id": "obs-0014",
      "index": 19,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x00c4b220",
      "target": "0x00c4b220"
    },
    {
   
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b8d9f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bba870"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c44d00"
  },
  {
    "name": "FUN_00c59240",
    "reconstructed": false,
    "va": "0x00c59240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c59540"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e2eba0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e98500"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fdf5b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fdf5f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fe7e60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x010727e0"
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
  "count": 24,
  "instructions": [
    {
      "address": "00b8d9b0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b8d9b1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b8d9b3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b8d9b4",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b8d9b5",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00b8d9ba",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b8d9bc",
      "instruction": "CALL 0x00bb99e0"
    },
    {
      "address": "00b8d9c1",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00b8d9c3",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00b8d9c5",
      "instruction": "JNZ 0x00b8d9e3"
    },
    {
      "address": "00b8d9c7",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b8d9c8",
      "instruction": "CALL 0x00feb9f0"
    },
    {
      "address": "00b8d9cd",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b8d9cf",
      "instruction": "CALL 0x00fee220"
    },
    {
      "address": "00b8d9d4",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b8d9d6",
      "instruction": "JZ 0x00b8d9e1"
    },
    {
      "address": "00b8d9d8",
      "instruction": "POP EDI"
    },
    {
      "address": "00b8d9d9",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b8d9db",
      "instruction": "POP ESI"
    },
    {
      "address": "00b8d9dc",
      "instruction": "JMP 0x00c4b220"
    },
    {
      "address": "00b8d9e1",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00b8d9e3",
      "instruction": "POP EDI"
    },
    {
      "address": "00b8d9e4",
      "instruction": "POP ESI"
    },
    {
      "address": "00b8d9e5",
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
  "original_bytes": 12285,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"read; ESI holds it for the whole body and is pushed as the argument to both callees\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET (with a tail JMP to 0x00c4b220 on the deepest path)\",\n    \"return_observation\": \"Three exits write EAX: 0x00b8d9e1 MOV EAX,EDI (provably 0 on that path), 0x00b8d9e3 the preserved EDI from tier 1, and the tail transfer at 0x00b8d9dc which returns 0x00c4b220's EAX unchanged. The full dword is defined on every exit.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"an opaque context handle: the non-null result of the tier-1 registry resolve, otherwise the tier-2 mission context's lazily resolved +0x1F4 slot, otherwise exactly 0\",\n    \"return_type\": \"std::uint32_t\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET at 0x00b8d9e5, or JMP 0x00c4b220 at 0x00b8d9dc\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b8d9f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bba870\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c44d00\"\n      },\n      {\n        \"name\": \"FUN_00c59240\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c59240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c59540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e2eba0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e98500\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdf5b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdf5f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe7e60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010727e0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b8da09\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b8d9f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bba885\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bba870\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c44d16\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c44d00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c593f3\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c59240\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c596fc\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c59540\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e2ebbb\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e2eba0\",\n        \"ref
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
  "body_end": "00b8d9e5",
  "body_span_bytes": 54,
  "body_start": "00b8d9b0",
  "callees": [
    "FUN_00bb99e0",
    "FUN_00feb9f0",
    "FUN_00c4b220",
    "FUN_00fee220",
    "FUN_00b3d2a0"
  ],
  "callers": [
    "FUN_00fdf5f0",
    "FUN_00b8d9f0",
    "FUN_00bba870",
    "FUN_00c59240",
    "FUN_00e2eba0",
    "FUN_00c44d00",
    "FUN_00fdf5b0",
    "FUN_010727e0",
    "FUN_00fe7e60",
    "FUN_00c59540",
    "FUN_00e98500"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b8d9b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b8d9b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x78d9b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b8d9b0(void)",
  "size_bytes": 54,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b8d9b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 11,
  "xrefs": [
    {
      "from": "00b8da09"
    },
    {
      "from": "00bba885"
    },
    {
      "from": "00c593f3"
    },
    {
      "from": "00c596fc"
    },
    {
      "from": "00e98913"
    },
    {
      "from": "00fdf5bf"
    },
    {
      "from": "01072899"
    },
    {
      "from": "00fdf61f"
    },
    {
      "from": "00fe7ee2"
    },
    {
      "from": "00e2ebbb"
    },
    {
      "from": "00c44d16"
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
    "reconstruction/staging/wave13-w1-core-b06/b8d9b0_planet_record_resolve_context.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b06/00b8d9b0.json"
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
    "A runtime write watchpoint on the singleton at 0x0167EAE4 and on the context field at +0x1F4 is required to confirm the lazy-resolution claim about 0x00c4b220, which this batch inferred from static structure only.",
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
    "The concrete type of the returned handle can only be established by observing a receiver at a callsite and locating its vtable, neither of which is possible statically.",
    "The tier-1/tier-2 split is a runtime-behavioural claim about which registry is populated in a given game state. A differential test must exercise at least one planet that resolves through tier 1 and one that falls through to tier 2, and observe that tier 1's cross-context write is invisible to the caller."
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
  "std::uint32_t"
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
