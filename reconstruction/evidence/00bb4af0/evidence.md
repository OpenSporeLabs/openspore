# Evidence 0x00bb4af0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ebfb532da2d64b7488284e0d53f8be6abea5636cc32332fef07427cdf6c0c646`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueStarManager*",
  "receiver": "ECX",
  "return": "EAX",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "star",
      "position": 1,
      "type": "OpaqueStarRegeneration*"
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "dispatch_word",
      "position": 2,
      "type": "TargetWord"
    }
  ],
  "stack_cleanup_bytes": 8,
  "termination": "RET 0x8"
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
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "f829a20bc4284a2a2198736e0794e72cad554c82550ecbf756bf2a9f73123e69",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
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
        "obs-0030"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0008"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          220,
          224
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0020"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0003"
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
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0030"
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
      "at": "0x00bb4af0",
      "count": 8,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00bb4af1",
      "count": 4,
      "first_use": 1,
      "first_write_index": 10,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00bb4af1",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00bb4af1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bb4afc",
      "count": 6,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00bb4afd",
      "count": 2,
      "first_use": 4,
      "first_write_index": 6,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00bb4afd",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00bb4b0
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d380",
    "reconstructed": false,
    "va": "0x00b3d380"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb9b00"
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
    "name": "FUN_00bb57b0",
    "reconstructed": false,
    "va": "0x00bb57b0"
  },
  {
    "name": "FUN_00c31730",
    "reconstructed": false,
    "va": "0x00c31730"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c34ee0"
  },
  {
    "name": "FUN_00c47e20",
    "reconstructed": false,
    "va": "0x00c47e20"
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
    "va": "0x00c5f770"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01011120"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bb4af0",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00e74a20",
      "0x00e74a20"
    ],
    "conflict_id": "U-004-star-generation-boundary",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
    "resolution_status": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bba900",
      "0x00bb4af0",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bba900",
      "0x00bba900",
      "0x00bba900",
      "0x00c86760",
      "0x00c8b700"
    ],
    "conflict_id": "planet_count_materialization",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The generation body increments mPlanetCount while creating cPlanetRecord objects. Lazy materialization and equality with final runtime cPlanets are unresolved.",
    "resolution_status": "The generation body increments mPlanetCount while creating cPlanetRecord objects. Lazy materialization and equality with final runtime cPlanets are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bb4af0",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4c90",
      "0x00bb4af0",
      "0x00bb4100"
    ],
    "conflict_id": "star_generation_address_identity",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Current bodies and SDK anchors are separated rather than merged; the exact SDK entry identity and record-vector append contract remain unresolved.",
    "resolution_status": "Current bodies and SDK anchors are separated rather than merged; the exact SDK entry identity and record-vector append contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
  "count": 58,
  "instructions": [
    {
      "address": "00bb4af0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bb4af1",
      "instruction": "MOV ESI,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00bb4af5",
      "instruction": "CMP byte ptr [ESI + 0xac],0x0"
    },
    {
      "address": "00bb4afc",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bb4afd",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00bb4aff",
      "instruction": "JNZ 0x00bb4b97"
    },
    {
      "address": "00bb4b05",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bb4b07",
      "instruction": "CALL 0x00801920"
    },
    {
      "address": "00bb4b0c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb4b0d",
      "instruction": "CALL 0x00c8b520"
    },
    {
      "address": "00bb4b12",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00bb4b15",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00bb4b17",
      "instruction": "JZ 0x00bb4b97"
    },
    {
      "address": "00bb4b19",
      "instruction": "CALL 0x00b3d380"
    },
    {
      "address": "00bb4b1e",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bb4b20",
      "instruction": "CALL 0x00b316c0"
    },
    {
      "address": "00bb4b25",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00bb4b27",
      "instruction": "PUSH 0xea60"
    },
    {
      "address": "00bb4b2c",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bb4b2d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb4b2e",
      "instruction": "CALL 0x011e0970"
    },
    {
      "address": "00bb4b33",
      "instruction": "MOV dword ptr [ESI + 0xc],EAX"
    },
    {
      "address": "00bb4b36",
      "instruction": "MOV EDX,dword ptr [EDI + 0xe0]"
    },
    {
      "address": "00bb4b3c",
      "instruction": "MOV EAX,dword ptr [EDI + 0xdc]"
    },
    {
      "address": "00bb4b42",
      "instruction": "LEA ECX,[EDI + 0xdc]"
    },
    {
      "address": "00bb4b48",
      "instruction": "CMP EAX,EDX"
    },
    {
      "address": "00bb4b4a",
      "instruction": "JZ 0x00bb4b76"
    },
    {
      "address": "00bb4b4c",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "00bb4b50",
      "instruction": "CMP dword ptr [EAX],ESI"
    },
    {
      "address": "00bb4b52",
      "instruction": "JZ 0x00bb4b5b"
    },
    {
      "address": "00bb4b54",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "00bb4b57",
      "instruction": "CMP EAX,EDX"
    },
    {
      "address": "00bb4b59",
      "instruction": "JNZ 0x00bb4b50"
    },
    {
      "address": "00bb4b5b",
      "instruction": "CMP EAX,EDX"
    },
    {
      "address": "00bb4b5d",
      "instruction": "JZ 0x00bb4b76"
    },
    {
      "address": "00bb4b5f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb4b60",
      "instruction": "CALL 0x00bf3420"
    },
    {
      "address": "00bb4b65",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00bb4b67",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00bb4b69",
      "instruction": "CALL 0x00bb3800"
    },
    {
      "address": "00bb4b6e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb4b6f",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bb4b71",
      "instruction": "CALL 0x00bb9ad0"
    },
    {
      "address": "00bb4b76",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00bb4b78",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00bb4b7a",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bb4b7c",
      "instruction": "CALL 0x00bb9b00"
    },
    {
      "address": "00bb4b81",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bb4b83",
      "instruction": "CALL 0x00bba500"
    },
    {
      "address": "00bb4b88",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00bb4b8c",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00bb4b8e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb4b8f",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bb4b90",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00bb4b92",
      "instruction": "CALL 0x00bb4100"
    },
    {
      "address": "00bb4b97",
      "instruction": "POP EDI"
    },
    {
      "address": "00bb4b98",
      "instruction": "POP ESI"
    },
    {
      "address": "00bb4b99",
      "instruction": "RET 0x8"
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
  "original_bytes": 11334,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueStarManager*\",\n    \"receiver\": \"ECX\",\n    \"return\": \"EAX\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"star\",\n        \"position\": 1,\n        \"type\": \"OpaqueStarRegeneration*\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"dispatch_word\",\n        \"position\": 2,\n        \"type\": \"TargetWord\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_class\",\n        \"shared_types:OpaqueStarManager,OpaqueStarManager*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-14-A2-WORLD-LIFECYCLE-WAVE2\",\n      \"score\": 21,\n      \"symbol\": \"star_manager_record_to_planet_00bb5b50\",\n      \"va\": \"0x00bb5b50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueStarManager,OpaqueStarManager*,TargetWord\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 14,\n      \"symbol\": \"Simulator_LookupEmpireByPoliticalId\",\n      \"va\": \"0x00ba9370\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-14-A2-WORLD-LIFECYCLE-WAVE2\",\n      \"score\": 10,\n      \"symbol\": \"planet_record_copy_three_word_key_00b8da30\",\n      \"va\": \"0x00b8da30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueStarManager\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 5,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 5,\n      \"symbol\": \"editor_anim_event_message_send_0059d8b0\",\n      \"va\": \"0x0059d8b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 5,\n      \"symbol\": \"app_prop_manager_get_global_property_list_006a3310\",\n      \"va\": \"0x006a3310\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:TargetWord\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"No original-process runtime trace is available for the opaque timing and regeneration services.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueStarManager\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d380\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b3d380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb9b00\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"FUN_00bb57b0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00bb57b0\"\n      },\n      {\n        \"name\": \"FUN_00c31730\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c31730\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c34ee0\"\n      },\n      {\n        \"name\": \"FUN_00c47e20\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c47e20\"\n      },\n      {\n        \"name\": \"FUN_00c59240\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c59240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c59540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5f770\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01011120\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00bb57c6\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bb57b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c31760\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c31730\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c35119\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c34ee0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c3518b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c34ee0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c4820b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c47e20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c593b5\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c59240\",\n        \"reference_type\": 
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
  "body_end": "00bb4b9b",
  "body_span_bytes": 172,
  "body_start": "00bb4af0",
  "callees": [
    "FUN_00b316c0",
    "__aulldiv",
    "FUN_00bf3420",
    "FUN_00c8b520",
    "FUN_00bba500",
    "FUN_00bb9ad0",
    "FUN_00801920",
    "FUN_00bb4100",
    "FUN_00b3d380",
    "FUN_00bb9b00",
    "FUN_00bb3800"
  ],
  "callers": [
    "FUN_00bb57b0",
    "FUN_00c31730",
    "FUN_00c5f770",
    "FUN_00c59240",
    "FUN_00c47e20",
    "FUN_00c59540",
    "FUN_01011120",
    "FUN_00c34ee0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bb4af0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00bb4af0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7b4af0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bb4af0(void)",
  "size_bytes": 172,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bb4af0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 12,
  "xrefs": [
    {
      "from": "00bb57c6"
    },
    {
      "from": "00c31760"
    },
    {
      "from": "00c35119"
    },
    {
      "from": "00c3518b"
    },
    {
      "from": "00c4820b"
    },
    {
      "from": "00c593b5"
    },
    {
      "from": "00c596d8"
    },
    {
      "from": "00c5fa21"
    },
    {
      "from": "010111cb"
    },
    {
      "from": "00c4e773"
    },
    {
      "from": "01026fd5"
    },
    {
      "from": "01027cc4"
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
  "file": "src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.cpp",
  "files": [
    "reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle.cpp",
    "reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle.hpp",
    "reconstruction/staging/pkg14-a2-world-lifecycle-wave2/world_lifecycle_model_test.cpp",
    "src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.cpp",
    "src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle.hpp",
    "src/reconstruction/pkg14_a2_world_lifecycle_wave2/world_lifecycle_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg14-a2-world-lifecycle-wave2/00bb4af0.json"
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
    "gate-star-regenerate-00bb4af0",
    "runtime validation not run"
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
  "OpaqueStarManager",
  "OpaqueStarManager*",
  "OpaqueStarRegeneration*",
  "TargetWord",
  "void"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bb4af0",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00e74a20",
      "0x00e74a20"
    ],
    "conflict_id": "U-004-star-generation-boundary",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
    "resolution_status": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bba900",
      "0x00bb4af0",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bba900",
      "0x00bba900",
      "0x00bba900",
      "0x00c86760",
      "0x00c8b700"
    ],
    "conflict_id": "planet_count_materialization",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The generation body increments mPlanetCount while creating cPlanetRecord objects. Lazy materialization and equality with final runtime cPlanets are unresolved.",
    "resolution_status": "The generation body increments mPlanetCount while creating cPlanetRecord objects. Lazy materialization and equality with final runtime cPlanets are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bb4af0",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4c90",
      "0x00bb4af0",
      "0x00bb4100"
    ],
    "conflict_id": "star_generation_address_identity",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Current bodies and SDK anchors are separated rather than merged; the exact SDK entry identity and record-vector append contract remain unresolved.",
    "resolution_status": "Current bodies and SDK anchors are separated rather than merged; the exact SDK entry identity and record-vector append contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
