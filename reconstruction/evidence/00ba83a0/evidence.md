# Evidence 0x00ba83a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `201c5b7661f9792a4b7eb490275fdb33e2091ae5bd8387d383debe63a5d5c5ac`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OrderedMap*",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "output",
      "observed_use": "Receives the allocated entry pointer at offset zero.",
      "position": 1,
      "type": "MapInsertResult*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "parent",
      "observed_use": "Forwarded to the red-black insertion helper.",
      "position": 2,
      "type": "OrderedMapEntry*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0C",
      "name": "pair",
      "observed_use": "When non-null, supplies the key at +0x00 and value at +0x04.",
      "position": 3,
      "type": "const MapInsertPair*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x10",
      "name": "insertion_side",
      "observed_use": "Controls the automatic side decision; nonzero forces the helper side-zero path.",
      "position": 4,
      "type": "std::uint8_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 16
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
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x10",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EBP",
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
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 16,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x10",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "50bf2fbf04343c0c5e35126c41650726b5f62b2c05da3ebf3328604293548fc3",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall observed"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0030"
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
        "obs-0002",
        "obs-0006",
        "obs-0013",
        "obs-0021",
        "obs-0024"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 4,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0013",
        "obs-0014",
        "obs-0015",
        "obs-0021"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          20
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0013",
        "obs-0014",
        "obs-0015",
        "obs-0021",
        "obs-0030"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
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
        "obs-0030"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
      }
    },
    {
      "based_on": [
        "obs-0030"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
   
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
    "name": "pkg20_gameglobal_00ba8420",
    "reconstructed": true,
    "va": "0x00ba8420"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00baa660"
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
  "count": 50,
  "instructions": [
    {
      "address": "00ba83a0",
      "instruction": "CMP byte ptr [ESP + 0x10],0x0"
    },
    {
      "address": "00ba83a5",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00ba83a6",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00ba83a7",
      "instruction": "MOV EBP,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00ba83ab",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ba83ac",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ba83ad",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00ba83af",
      "instruction": "JNZ 0x00ba83ca"
    },
    {
      "address": "00ba83b1",
      "instruction": "LEA EAX,[ESI + 0x4]"
    },
    {
      "address": "00ba83b4",
      "instruction": "CMP EBP,EAX"
    },
    {
      "address": "00ba83b6",
      "instruction": "JZ 0x00ba83ca"
    },
    {
      "address": "00ba83b8",
      "instruction": "MOV ECX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00ba83bc",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00ba83be",
      "instruction": "CMP EDX,dword ptr [EBP + 0x10]"
    },
    {
      "address": "00ba83c1",
      "instruction": "JC 0x00ba83ca"
    },
    {
      "address": "00ba83c3",
      "instruction": "MOV EBX,0x1"
    },
    {
      "address": "00ba83c8",
      "instruction": "JMP 0x00ba83cc"
    },
    {
      "address": "00ba83ca",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00ba83cc",
      "instruction": "PUSH 0xd1"
    },
    {
      "address": "00ba83d1",
      "instruction": "PUSH 0x13ebb38"
    },
    {
      "address": "00ba83d6",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00ba83d8",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00ba83da",
      "instruction": "PUSH 0x13f09b4"
    },
    {
      "address": "00ba83df",
      "instruction": "PUSH 0x18"
    },
    {
      "address": "00ba83e1",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "00ba83e6",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00ba83e8",
      "instruction": "LEA EAX,[EDI + 0x10]"
    },
    {
      "address": "00ba83eb",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "00ba83ee",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00ba83f0",
      "instruction": "JZ 0x00ba8400"
    },
    {
      "address": "00ba83f2",
      "instruction": "MOV ECX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00ba83f6",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00ba83f8",
      "instruction": "MOV dword ptr [EAX],EDX"
    },
    {
      "address": "00ba83fa",
      "instruction": "MOV ECX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "00ba83fd",
      "instruction": "MOV dword ptr [EAX + 0x4],ECX"
    },
    {
      "address": "00ba8400",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00ba8401",
      "instruction": "LEA EDX,[ESI + 0x4]"
    },
    {
      "address": "00ba8404",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00ba8405",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00ba8406",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ba8407",
      "instruction": "CALL 0x009216a0"
    },
    {
      "address": "00ba840c",
      "instruction": "MOV EAX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00ba8410",
      "instruction": "INC dword ptr [ESI + 0x14]"
    },
    {
      "address": "00ba8413",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00ba8416",
      "instruction": "MOV dword ptr [EAX],EDI"
    },
    {
      "address": "00ba8418",
      "instruction": "POP EDI"
    },
    {
      "address": "00ba8419",
      "instruction": "POP ESI"
    },
    {
      "address": "00ba841a",
      "instruction": "POP EBP"
    },
    {
      "address": "00ba841b",
      "instruction": "POP EBX"
    },
    {
      "address": "00ba841c",
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
  "original_bytes": 8024,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OrderedMap*\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"output\",\n        \"observed_use\": \"Receives the allocated entry pointer at offset zero.\",\n        \"position\": 1,\n        \"type\": \"MapInsertResult*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"parent\",\n        \"observed_use\": \"Forwarded to the red-black insertion helper.\",\n        \"position\": 2,\n        \"type\": \"OrderedMapEntry*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x0C\",\n        \"name\": \"pair\",\n        \"observed_use\": \"When non-null, supplies the key at +0x00 and value at +0x04.\",\n        \"position\": 3,\n        \"type\": \"const MapInsertPair*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x10\",\n        \"name\": \"insertion_side\",\n        \"observed_use\": \"Controls the automatic side decision; nonzero forces the helper side-zero path.\",\n        \"position\": 4,\n        \"type\": \"std::uint8_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 16\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:MapInsertPair,MapInsertResult,MapInsertResult*,OrderedMap\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 33,\n      \"symbol\": \"pkg20_gameglobal_00ba8420\",\n      \"va\": \"0x00ba8420\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_class\",\n        \"shared_types:OrderedMap,OrderedMapEntry,TargetWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 24,\n      \"symbol\": \"map_int_whatever_find\",\n      \"va\": \"0x00e5c780\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OrderedMap,OrderedMapEntry\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 8,\n      \"symbol\": \"pkg11_sim_core_00b21340\",\n      \"va\": \"0x00b21340\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OrderedMapEntry,TargetWord\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_LookupEmpireByPoliticalId\",\n      \"va\": \"0x00ba9370\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"stream_probe_dispatch_004bc540\",\n      \"va\": \"0x004bc540\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"skin_job_setup_0051a9a0\",\n      \"va\": \"0x0051a9a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No runtime allocator-failure trace is available.\",\n    \"The red-black helper is preserved as an external staging boundary rather than reimplemented in this exclusive file set.\",\n    \"The value word remains semantically opaque.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OrderedMap\",\n  \"cluster\": null,\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"pkg20_gameglobal_00ba8420\",\n        \"reconstructed\": true,\n        \"va\": \"0x00ba8420\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00baa660\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00ba847c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba8420\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00baa6a6\",\n        \"direction\": \"in\",\n        \"other\": \"0x00baa660\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00baa6c0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00baa660\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00baa6eb\",\n        \"direction\": \"in\",\n        \"other\": \"0x00baa660\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba8407\",\n        \"direction\": \"out\",\n        \"other\": \"0x009216a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba83e1\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f473a0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 2,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x00f473a0\",\n      \"0x009216a0\"\n    ],\n    \"manifest_callers\": [\n      \"0x00ba8420\",\n      \"0x00baa660\"\n    ],\n    \"nearby_reconstructed\
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
  "body_end": "00ba841e",
  "body_span_bytes": 127,
  "body_start": "00ba83a0",
  "callees": [
    "FUN_009216a0",
    "FUN_00f473a0"
  ],
  "callers": [
    "FUN_00baa660",
    "FUN_00ba8420"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ba83a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00ba83a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7a83a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ba83a0(void)",
  "size_bytes": 127,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ba83a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00ba847c"
    },
    {
      "from": "00baa6a6"
    },
    {
      "from": "00baa6c0"
    },
    {
      "from": "00baa6eb"
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
  "file": "src/reconstruction/pkg20_gameglobal/map_insert.cpp",
  "files": [
    "reconstruction/staging/pkg20-gameglobal/map_insert.cpp",
    "reconstruction/staging/pkg20-gameglobal/map_insert.hpp",
    "reconstruction/staging/pkg20-gameglobal/map_insert_model_test.cpp",
    "src/reconstruction/pkg20_gameglobal/map_insert.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-gameglobal/00ba83a0.json"
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
    "gate-map-insertion"
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
  "MapInsertPair",
  "MapInsertResult",
  "MapInsertResult*",
  "OrderedMap",
  "OrderedMap*",
  "OrderedMapEntry",
  "OrderedMapEntry*",
  "TargetWord",
  "const MapInsertPair*",
  "std::uint8_t",
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
