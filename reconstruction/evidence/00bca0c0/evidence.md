# Evidence 0x00bca0c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7e1063a25438f0ddf4a033b1507f5f79626e8414d96703f1e369ce33e59ede8a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "owner of the eight-slot record table at +0x20",
  "hidden_this_register": "ECX, read at 0x00bca0cf",
  "ordinary_stack_argument_slots": 4,
  "receiver": true,
  "ret_form": "RET 0x10",
  "return_observation": "0x00bca105 MOVZX EAX,word ptr [EAX + -0x8] loads 16 bits only, 0x00bca10a SHL EDX,0x10 and 0x00bca10e OR EAX,EDX assemble the packed value, and 0x00bca0fe OR EAX,0xffffffff is the not-found answer.",
  "return_register": "EAX",
  "return_semantics": "the matched record's 16-bit identifier in bits 0..15 with the slot index in bits 16..31, or 0xffffffff when no record matches",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "read_at": "0x00bca0c1",
      "role": "key1, compared at 0x00bca0d8 against record+0x04",
      "slot": "entry ESP+4"
    },
    {
      "read_at": "0x00bca0cb",
      "role": "key2, compared at 0x00bca0dd against record+0x08",
      "slot": "entry ESP+8"
    },
    {
      "read_at": "0x00bca0c6",
      "role": "key3, compared at 0x00bca0e5 against record+0x1c only when non-zero",
      "slot": "entry ESP+0xc"
    },
    {
      "read_at": "0x00bca0d2",
      "role": "key4, compared at 0x00bca0ee against record+0x20 only when non-zero",
      "slot": "entry ESP+0x10"
    }
  ],
  "stack_cleanup_bytes": 16,
  "stack_cleanup_owner": "callee",
  "termination": "0x00bca102 RET 0x10 and 0x00bca111 RET 0x10"
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
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10"
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x10",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBX",
      "EDI",
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
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 16,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path",
    "receiver_not_determinable: ecx_address_taken_without_memory_access",
    "ecx_address_taken_without_memory_access: LEA takes ECX's address without any memory access through it",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_address_taken_without_memory_access), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x10",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "6bb44e1e7b960c7543fa9bc474e98e57e164d717132fcf16748a3d3144812ff3",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
      "__thiscall"
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
        "obs-0021",
        "obs-0025"
      ],
      "claim": "the callee pops 16 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 16,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0006",
        "obs-0009",
        "obs-0013"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 4,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0014"
      ],
      "claim": "the register receiver is undetermined: ecx_address_taken_without_memory_access",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_address_taken_without_memory_access",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0014"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_address_taken_without_memory_access) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0021",
        "obs-0025"
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
        "obs-0021",
        "obs-0025"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0021",
        "obs-0025"
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
      "at": "0x00bca0c0",
      "count": 1,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
     
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
    "va": "0x00ba48b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c05a80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c07480"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c09410"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0c630"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0e6a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c20230"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c238b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cdcb10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d1e720"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d2ffd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d4b2f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d697a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d8e8d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d9b110"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00da6b10"
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
      "address": "00bca0c0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bca0c1",
      "instruction": "MOV EBX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00bca0c5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bca0c6",
      "instruction": "MOV ESI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00bca0ca",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bca0cb",
      "instruction": "MOV EDI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00bca0cf",
      "instruction": "LEA EAX,[ECX + 0x28]"
    },
    {
      "address": "00bca0d2",
      "instruction": "MOV ECX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00bca0d6",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00bca0d8",
      "instruction": "CMP dword ptr [EAX + -0x4],EBX"
    },
    {
      "address": "00bca0db",
      "instruction": "JNZ 0x00bca0f3"
    },
    {
      "address": "00bca0dd",
      "instruction": "CMP dword ptr [EAX],EDI"
    },
    {
      "address": "00bca0df",
      "instruction": "JNZ 0x00bca0f3"
    },
    {
      "address": "00bca0e1",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00bca0e3",
      "instruction": "JZ 0x00bca0ea"
    },
    {
      "address": "00bca0e5",
      "instruction": "CMP dword ptr [EAX + 0x14],ESI"
    },
    {
      "address": "00bca0e8",
      "instruction": "JNZ 0x00bca0f3"
    },
    {
      "address": "00bca0ea",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00bca0ec",
      "instruction": "JZ 0x00bca105"
    },
    {
      "address": "00bca0ee",
      "instruction": "CMP dword ptr [EAX + 0x18],ECX"
    },
    {
      "address": "00bca0f1",
      "instruction": "JZ 0x00bca105"
    },
    {
      "address": "00bca0f3",
      "instruction": "INC EDX"
    },
    {
      "address": "00bca0f4",
      "instruction": "ADD EAX,0x44"
    },
    {
      "address": "00bca0f7",
      "instruction": "CMP EDX,0x8"
    },
    {
      "address": "00bca0fa",
      "instruction": "JC 0x00bca0d8"
    },
    {
      "address": "00bca0fc",
      "instruction": "POP EDI"
    },
    {
      "address": "00bca0fd",
      "instruction": "POP ESI"
    },
    {
      "address": "00bca0fe",
      "instruction": "OR EAX,0xffffffff"
    },
    {
      "address": "00bca101",
      "instruction": "POP EBX"
    },
    {
      "address": "00bca102",
      "instruction": "RET 0x10"
    },
    {
      "address": "00bca105",
      "instruction": "MOVZX EAX,word ptr [EAX + -0x8]"
    },
    {
      "address": "00bca109",
      "instruction": "POP EDI"
    },
    {
      "address": "00bca10a",
      "instruction": "SHL EDX,0x10"
    },
    {
      "address": "00bca10d",
      "instruction": "POP ESI"
    },
    {
      "address": "00bca10e",
      "instruction": "OR EAX,EDX"
    },
    {
      "address": "00bca110",
      "instruction": "POP EBX"
    },
    {
      "address": "00bca111",
      "instruction": "RET 0x10"
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
  "original_bytes": 11107,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"owner of the eight-slot record table at +0x20\",\n    \"hidden_this_register\": \"ECX, read at 0x00bca0cf\",\n    \"ordinary_stack_argument_slots\": 4,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x10\",\n    \"return_observation\": \"0x00bca105 MOVZX EAX,word ptr [EAX + -0x8] loads 16 bits only, 0x00bca10a SHL EDX,0x10 and 0x00bca10e OR EAX,EDX assemble the packed value, and 0x00bca0fe OR EAX,0xffffffff is the not-found answer.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"the matched record's 16-bit identifier in bits 0..15 with the slot index in bits 16..31, or 0xffffffff when no record matches\",\n    \"return_type\": \"std::uint32_t\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"read_at\": \"0x00bca0c1\",\n        \"role\": \"key1, compared at 0x00bca0d8 against record+0x04\",\n        \"slot\": \"entry ESP+4\"\n      },\n      {\n        \"read_at\": \"0x00bca0cb\",\n        \"role\": \"key2, compared at 0x00bca0dd against record+0x08\",\n        \"slot\": \"entry ESP+8\"\n      },\n      {\n        \"read_at\": \"0x00bca0c6\",\n        \"role\": \"key3, compared at 0x00bca0e5 against record+0x1c only when non-zero\",\n        \"slot\": \"entry ESP+0xc\"\n      },\n      {\n        \"read_at\": \"0x00bca0d2\",\n        \"role\": \"key4, compared at 0x00bca0ee against record+0x20 only when non-zero\",\n        \"slot\": \"entry ESP+0x10\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 16,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"0x00bca102 RET 0x10 and 0x00bca111 RET 0x10\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba48b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c05a80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c07480\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c09410\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0c630\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0e6a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c20230\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c238b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cdcb10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d1e720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2ffd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d4b2f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d697a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d8e8d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d9b110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00da6b10\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\"
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
  "body_end": "00bca113",
  "body_span_bytes": 84,
  "body_start": "00bca0c0",
  "callees": [],
  "callers": [
    "FUN_00c20230",
    "FUN_00c0c630",
    "FUN_00c0e6a0",
    "FUN_00d1e720",
    "FUN_00d8e8d0",
    "FUN_00c238b0",
    "FUN_00c07480",
    "FUN_00d2ffd0",
    "FUN_00d697a0",
    "FUN_00c05a80",
    "FUN_00cdcb10",
    "FUN_00c09410",
    "FUN_00da6b10",
    "FUN_00d9b110",
    "FUN_00ba48b0",
    "FUN_00d4b2f0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00bca0c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00bca0c0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7ca0c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bca0c0(void)",
  "size_bytes": 84,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bca0c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 22,
  "xrefs": [
    {
      "from": "00c0c939"
    },
    {
      "from": "00c05bbb"
    },
    {
      "from": "00c07894"
    },
    {
      "from": "00c078b8"
    },
    {
      "from": "00d303db"
    },
    {
      "from": "00c0991a"
    },
    {
      "from": "00c09939"
    },
    {
      "from": "00cdcdd2"
    },
    {
      "from": "00d4b372"
    },
    {
      "from": "00d69894"
    },
    {
      "from": "00d8eb60"
    },
    {
      "from": "00d8ecfd"
    },
    {
      "from": "00da6b44"
    },
    {
      "from": "00da6b5c"
    },
    {
      "from": "00d1e75c"
    },
    {
      "from": "00ba49e9"
    },
    {
      "from": "00c0e893"
    },
    {
      "from": "00c23a79"
    },
    {
      "from": "00c23a95"
    },
    {
      "from": "00c20b89"
    },
    {
      "from": "00c92838"
    },
    {
      "from": "00d9b198"
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
    "reconstruction/staging/wave13-w1-core-b07/00bca0c0_fixed_table_lookup.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b07/00bca0c0.json"
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
    "No original-process trace exists for this address.",
    "The record semantics and the owning class can only be settled with a receiver trace or by locating a writer of the eight records."
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
