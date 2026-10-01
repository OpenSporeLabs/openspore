# Evidence 0x00aeb720

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `cd045afc77cb45f4caa0ebbd5e6eb45f1a3f998873a44375be79a14b41f7d0f3`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "receiver": {
    "register": "ECX",
    "type": "cCommManager*",
    "width_bytes": 4
  },
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "payload0",
      "position": 1,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "payload1",
      "position": 2,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0C",
      "name": "payload2",
      "position": 3,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x10",
      "name": "payload3",
      "position": 4,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x14",
      "name": "payload4",
      "position": 5,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x18",
      "name": "payload5",
      "position": 6,
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 24,
  "termination": "RET 0x18"
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
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x18"
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
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x18",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
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
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 24,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x18"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +32, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 24,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x18",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "c15df3ad911769383c5d96133f14547e12553ab7cde054b154e084d59acc21c2",
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
        "obs-0019"
      ],
      "claim": "the callee pops 24 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 24,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0004",
        "obs-0008",
        "obs-0011",
        "obs-0013",
        "obs-0015"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 6,
        "total_bytes": 24
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0013"
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
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0013"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0019"
      ],
      "claim": "entry slot 0 is not written through a poin
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00aeb160",
    "reconstructed": true,
    "va": "0x00aeb160"
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
    "va": "0x00aed2c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c75520"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00dd5160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0102c9e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0102caa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0102cae0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0102cc30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0102cd90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0102ce30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0102cf10"
  },
  {
    "name": "FUN_0102d1b0",
    "reconstructed": true,
    "va": "0x0102d1b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0102df20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01072d40"
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
  "count": 22,
  "instructions": [
    {
      "address": "00aeb720",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00aeb724",
      "instruction": "MOV EDX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00aeb728",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00aeb729",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00aeb72b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00aeb72c",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00aeb730",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00aeb732",
      "instruction": "MOV ECX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00aeb736",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00aeb737",
      "instruction": "MOV ECX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00aeb73b",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00aeb73c",
      "instruction": "MOV EDX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00aeb740",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00aeb741",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00aeb742",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00aeb743",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00aeb745",
      "instruction": "CALL 0x00aeb160"
    },
    {
      "address": "00aeb74a",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00aeb74b",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00aeb74d",
      "instruction": "CALL 0x00aebe90"
    },
    {
      "address": "00aeb752",
      "instruction": "POP ESI"
    },
    {
      "address": "00aeb753",
      "instruction": "RET 0x18"
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
  "original_bytes": 18170,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"receiver\": {\n      \"register\": \"ECX\",\n      \"type\": \"cCommManager*\",\n      \"width_bytes\": 4\n    },\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"payload0\",\n        \"position\": 1,\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"payload1\",\n        \"position\": 2,\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x0C\",\n        \"name\": \"payload2\",\n        \"position\": 3,\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x10\",\n        \"name\": \"payload3\",\n        \"position\": 4,\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x14\",\n        \"name\": \"payload4\",\n        \"position\": 5,\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x18\",\n        \"name\": \"payload5\",\n        \"position\": 6,\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 24,\n    \"termination\": \"RET 0x18\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaquePayloadWord,cCommEvent,cCommManager,cCommManager*\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 33,\n      \"symbol\": \"FUN_00aeb160\",\n      \"va\": \"0x00aeb160\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:cCommManager,cCommManager*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 27,\n      \"symbol\": \"FUN_00aea230\",\n      \"va\": \"0x00aea230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:cCommEvent\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 19,\n      \"symbol\": \"FUN_00aea5d0\",\n      \"va\": \"0x00aea5d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:cCommEvent\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 17,\n      \"symbol\": \"FUN_00aea250\",\n      \"va\": \"0x00aea250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 11,\n      \"symbol\": \"FUN_0102d1b0\",\n      \"va\": \"0x0102d1b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 10,\n      \"symbol\": \"cSpaceInventoryItem_ctor_00c877f0\",\n      \"va\": \"0x00c877f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"pkg12_space_00de9fc0\",\n      \"va\": \"0x00de9fc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"pkg12_space_01021300\",\n      \"va\": \"0x01021300\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"FUN_00aeb160 and the 1319-instruction FUN_00aebe90 consumer are downstream boundaries and are not reconstructed by this assignment.\",\n    \"Manager layout conflicts prevent a faithful field-level host adapter without additional type and constructor evidence.\",\n    \"No original-process event trace or runtime refcount oracle is available.\",\n    \"The live creator dereferences a null allocation result on its allocation-failure path; the null test is an injected boundary model, not a claim that the original returns null normally.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"cCommManager\",\n  \"cluster\": null,\n  \"confidence\": 0.96,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00aeb160\",\n        \"reconstructed\": true,\n        \"va\": \"0x00aeb160\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aed2c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c75520\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd5160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102c9e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102caa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102cae0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102cc30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102cd90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102ce30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102cf10\"\n      },\n      {\n        \"name\": \"FUN_0102d1b0\",\n        \"reconstructed\": true,\n  
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
  "body_end": "00aeb755",
  "body_span_bytes": 54,
  "body_start": "00aeb720",
  "callees": [
    "FUN_00aeb160",
    "FUN_00aebe90"
  ],
  "callers": [
    "FUN_00aed2c0",
    "FUN_0102df20",
    "FUN_00c75520",
    "FUN_00dd5160",
    "FUN_01072d40",
    "FUN_0102cae0",
    "FUN_0102cf10",
    "FUN_0102cd90",
    "FUN_0102ce30",
    "FUN_0102d1b0",
    "FUN_0102caa0",
    "FUN_0102cc30",
    "FUN_0102c9e0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00aeb720",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "j_Sim_cCommManager_CreateSpaceCommEvent",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6eb720",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined j_Sim_cCommManager_CreateSpaceCommEvent(void)",
  "size_bytes": 54,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00aeb720",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 17,
  "xrefs": [
    {
      "from": "0102e241"
    },
    {
      "from": "0102e3a5"
    },
    {
      "from": "0102e776"
    },
    {
      "from": "0102e7ef"
    },
    {
      "from": "00c7555d"
    },
    {
      "from": "0102ca8b"
    },
    {
      "from": "0102cad8"
    },
    {
      "from": "0102cc18"
    },
    {
      "from": "0102ccef"
    },
    {
      "from": "0102ce1e"
    },
    {
      "from": "0102cef8"
    },
    {
      "from": "0102d0a0"
    },
    {
      "from": "0102d6ee"
    },
    {
      "from": "00dd58f6"
    },
    {
      "from": "00aed3a2"
    },
    {
      "from": "0107342c"
    },
    {
      "from": "00c6055f"
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
  "global:0x013f09b4"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg12_space/space_comm_event.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_comm_event.cpp",
    "reconstruction/staging/pkg12-space/space_comm_event.hpp",
    "reconstruction/staging/pkg12-space/space_comm_event_model_test.cpp",
    "src/reconstruction/pkg12_space/space_comm_event.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg12-space/00aeb720.json"
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
    "gate-space-comm-event-lifecycle"
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 6246,
  "preview": "{\n  \"category\": \"GAMEPLAY_LOGIC\",\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 15,\n  \"evidence\": [\n    {\n      \"kind\": \"targeted_decompilation_and_disassembly\",\n      \"observation\": \"ECX manager, six stack arguments, RET 0x18, trailing zero, direct creator then dispatch calls.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00aeb720\"\n    },\n    {\n      \"kind\": \"callee_decompilation\",\n      \"observation\": \"0xa0 allocation, event field writes, intrusive add, manager storage append.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00aeb160\"\n    },\n    {\n      \"kind\": \"callee_decompilation\",\n      \"observation\": \"Large, warning-heavy consumer; exact current-event, cancellation, and UI ordering remain unresolved.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00aebe90\"\n    },\n    {\n      \"kind\": \"caller_comparison\",\n      \"observation\": \"Bypasses the wrapper to the creator for an existing event and otherwise uses the wrapper.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00aed2c0\"\n    },\n    {\n      \"kind\": \"caller_comparison\",\n      \"observation\": \"Mission-oriented dispatcher calls the wrapper with six concrete communication fields.\",\n      \"source\": \"ghidra://SporeApp.exe@0x0102df20\"\n    }\n  ],\n  \"family\": \"simulator_comm_event\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": [],\n    \"direct_callers\": [],\n    \"globals\": [],\n    \"structures\": [\n      {\n        \"observation\": \"FUN_00aeb160 allocates 0xa0 bytes with the Simulator allocator and initializes a cCommEvent-compatible object through FUN_00aea250.\",\n        \"size\": \"0xa0\",\n        \"type\": \"cCommEvent\"\n      },\n      {\n        \"observation\": \"FUN_00aeb160 writes source at +0x18, planetKey at +0x34, fileID at +0x38, dialogID at +0x3c, mission at +0x40, priority at +0x44, and duration at +0x48; the final wrapper duration is zero.\",\n        \"type\": \"cCommEvent fields\"\n      },\n      {\n        \"observation\": \"Ghidra supplies cCommManager fields including mCurrentCommEvent and mListCommEvents, but the creator's observed list storage uses receiver+0x28/+0x2c; the named Ghidra field offsets are not promoted without a constructor/consumer proof.\",\n        \"size\": \"0x64\",\n        \"type\": \"cCommManager\"\n      }\n    ],\n    \"vtables\": [\n      {\n        \"address\": \"0x0145bed8\",\n        \"observation\": \"FUN_00aea250 installs the cCommEvent primary vtable and a secondary interface vtable; this is indirect lifecycle evidence, not a direct virtual call in 00aeb720.\",\n        \"status\": \"event_vtable_observed_in_creator\"\n      },\n      {\n        \"observation\": \"The wrapper has no vtable load or indirect call; its dispatch is through the two direct callees.\",\n        \"status\": \"no_direct_wrapper_vtable_call\"\n      },\n      {\n        \"observation\": \"The Ghidra cCommManager type has vtable fields but no concrete manager vtable address was recovered for this path.\",\n        \"status\": \"manager_vtable_identity_unresolved\"\n      }\n    ],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": \"No wrapper-level null or duplicate-event check was observed; deeper creator/consumer behavior is delegated.\",\n      \"identity_boundary\": \"The body supports a default-duration create-and-dispatch wrapper, but exact public SDK entry identity and original argument names remain contested.\",\n      \"inputs\": [\n        \"six explicit stack arguments; RET 0x18 confirms six dword arguments\"\n      ],\n      \"ordering\": [\n        \"create event\",\n        \"append/populate event in creator\",\n        \"dispatch/display event in consumer\",\n        \"return\"\n      ],\n      \"outputs\": [],\n      \"postconditions\": [],\n      \"preconditions\": [\n        \"manager receiver and argument values must be valid for FUN_00aeb160 and FUN_00aebe90; the wrapper has no local null guard\"\n      ],\n      \"purpose\": \"not_reported\",\n      \"return\": {\n        \"status\": \"not_reported\"\n      },\n      \"side_effects\": [\n        \"allocates or constructs a 0xa0-byte cCommEvent-compatible object in the creator\",\n        \"updates event fields and manager list storage in the creator\",\n        \"may alter current/list/UI state in the consumer\"\n      ],\n      \"status\": \"supported_static_contract_with_identity_limit\",\n      \"unresolved\": [\n        \"Is the exact entry CreateSpaceCommEvent, a default-duration wrapper, or an internal helper absorbed by the SDK address?\",\n        \"Which original ABI names correspond to the six forwarded stack arguments?\",\n        \"What exact current-event assignment, list/cancellation mutation, UI handling, and release timing does FUN_00aebe90 impose?\",\n        \"Why does the creator's observed manager storage offset differ from the named Ghidra cCommManager vector field?\"\n      ]\n    }\n  },\n  \"invariants\": {\n    \"failure_semantics\": [],\n    \"invariants\": [],\n    \"invariants_status\": \"not_reported\"\n  },\n  \"name\": \"cCommManager_create_space_communication_event_default_duration_wrapper\",\n  \"package\": {\n    \"caveat\": \"not_reported\",\n    \"ownership_status\": \"not_reported\",\n    \"primary\": null,\n    \"secondary\": []\n  },\n  \"readiness\": {\n    \"next_action\": \"Resolve the manager layout and then trace one mission caller; do not promote HandleSpaceCommAction or a universal event ABI.\",\n    \"runtime_performed\": false,\n    \"runtime_promoted\": false,\n    \"runtime_required\": false,\n    \"status\": \"STATIC_READY_WITH_BOUNDED_UNKNOWNS\",\n    \"unlock_requirements\": []\n  },\n  \"source\": \"knowledgegraph/research/semantic-decomp/worker-03-space.json\",\n  \"state_events\": {\n    \"events\": [],\n    \"l
[TRUNCATED]
```

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
  "OpaquePayloadWord",
  "cCommEvent",
  "cCommManager",
  "cCommManager*",
  "opaque",
  "uint32_t",
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
