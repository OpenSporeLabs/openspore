# Evidence 0x00ecc620

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `800580ad1c52a0e028a45e3d8116d6cd501de0b1231e4d760dfe3ae4741eda05`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_note": "(the receiver)",
  "return_register": "EAX",
  "return_type": "OpaqueSporepediaAssetData*",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
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
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
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
          1
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
  "content_sha256": "c14aed0303f1e8b81f642c2c1309e900a562173ea5b1344bc69d358f428c5990",
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
        "obs-0014"
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
        "obs-0011"
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
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          16,
          20,
          128,
          136
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0014"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0014"
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
        "obs-0014"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0014"
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
      "at": "0x00ecc620",
      "count": 9,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00ecc621",
      "count": 1,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00ecc621",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00ecc637",
      "definite": true,
      "id": "obs-0004",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x80]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00ecc63d",
      "definite": true,
      "id": "obs-0005",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x88]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00ecc643",
      "count": 2,
      "first_use": 7,
      "first_write_index": 5,
      "id": "obs-0006",
      "index": 7,
      "kind": "REG_READ",
      "raw": "SUB ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00ecc652",
      "id": "obs-0007",
      "index": 14,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f47380",
      "target": "0x00f47380"
    },
    {
      "at": "0x00ecc657",
      "definite": true,
      "id": "obs-0008",
      "index": 15,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x4",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00ecc65c",
      "id": "obs-0009",
      "index": 17,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00642190",
      "target": "0x00642190"
    },
    {
      "at": "0x00ecc661",
      "count": 1,
      "first_use": 18,
      "first_write_index": 15,
      "id": "obs-0010",
      "index": 18,
      "kind
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "sporepedia_asset_destroy_00642190",
    "reconstructed": true,
    "va": "0x00642190"
  }
]
```

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
  "count": 26,
  "instructions": [
    {
      "address": "00ecc620",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ecc621",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00ecc623",
      "instruction": "MOV dword ptr [ESI],0x14893b0"
    },
    {
      "address": "00ecc629",
      "instruction": "MOV dword ptr [ESI + 0x10],0x148939c"
    },
    {
      "address": "00ecc630",
      "instruction": "MOV dword ptr [ESI + 0x14],0x148938c"
    },
    {
      "address": "00ecc637",
      "instruction": "MOV EAX,dword ptr [ESI + 0x80]"
    },
    {
      "address": "00ecc63d",
      "instruction": "MOV ECX,dword ptr [ESI + 0x88]"
    },
    {
      "address": "00ecc643",
      "instruction": "SUB ECX,EAX"
    },
    {
      "address": "00ecc645",
      "instruction": "AND ECX,0xfffffffe"
    },
    {
      "address": "00ecc648",
      "instruction": "CMP ECX,0x2"
    },
    {
      "address": "00ecc64b",
      "instruction": "JLE 0x00ecc65a"
    },
    {
      "address": "00ecc64d",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00ecc64f",
      "instruction": "JZ 0x00ecc65a"
    },
    {
      "address": "00ecc651",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ecc652",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "00ecc657",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00ecc65a",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ecc65c",
      "instruction": "CALL 0x00642190"
    },
    {
      "address": "00ecc661",
      "instruction": "TEST byte ptr [ESP + 0x8],0x1"
    },
    {
      "address": "00ecc666",
      "instruction": "JZ 0x00ecc671"
    },
    {
      "address": "00ecc668",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ecc669",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "00ecc66e",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00ecc671",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00ecc673",
      "instruction": "POP ESI"
    },
    {
      "address": "00ecc674",
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
  "original_bytes": 8817,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_note\": \"(the receiver)\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"OpaqueSporepediaAssetData*\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014893b0\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014893b0\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014893b0\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014893b0\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func3ch_006417b0\",\n      \"va\": \"0x006417b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014893b0\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0\",\n      \"va\": \"0x006417c0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014893b0\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_id_00641820\",\n      \"va\": \"0x00641820\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014893b0\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_tags_00641850\",\n      \"va\": \"0x00641850\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014893b0\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_time_created_00641860\",\n      \"va\": \"0x00641860\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"sporepedia_asset_destroy_00642190\",\n        \"reconstructed\": true,\n        \"va\": \"0x00642190\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00ecc65c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00642190\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ecc652\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ecc669\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00642190\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0566\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 3\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"FUN_00ecc620\",\n  \"normalized_symbol\": \"FUN_00ecc620\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w1-00ecc620/00ecc620.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Sporepedia\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sporepedia-online\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00ecc620\",\n    \"name\": \"FUN_00ecc620\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490
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
  "body_end": "00ecc676",
  "body_span_bytes": 87,
  "body_start": "00ecc620",
  "callees": [
    "FUN_00f47380",
    "FUN_00642190"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ecc620",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00ecc620",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xacc620",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ecc620(void)",
  "size_bytes": 87,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ecc620",
  "vtables": {
    "referenced_by_vtables": [
      "0x014893b0"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "014893b0"
    },
    {
      "from": "00ecc603"
    },
    {
      "from": "00ecc613"
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
    "reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620.cpp",
    "reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00ecc620/sw1_00ecc620_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00ecc620/00ecc620.json"
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueSporepediaAssetData* (the receiver)",
  "OpaqueSporepediaAssetData* (the receiver). Machine fact, not convention: 0x00ecc671 MOV EAX,ESI executes on BOTH arms -- it sits after the 0x00ecc666 join, reached by falling through the 0x00f47380 call or by the branch -- and ESI is the receiver alias from 0x00ecc621 which is never reassigned. The derived ABI record classifies that EAX as unclassified_in_EAX with type null, which is a statement about its classifier and not about the listing."
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x014893b0"
]
```

## Conflicts

```json
[]
```
