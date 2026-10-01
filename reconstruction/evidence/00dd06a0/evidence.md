# Evidence 0x00dd06a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f9a92b01b4f0d89fcd63875cde9c303417b8851d63890598606dea94bed7a514`

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
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_type": "std::int32_t",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -8, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "da7481776e2381afdc4d568d9b4a7f31a28d5ea712f9ff2ccd3b3546b23071a5",
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
        "obs-0007",
        "obs-0012",
        "obs-0014"
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
        "obs-0003"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          132,
          136
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0007",
        "obs-0012",
        "obs-0014"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0012",
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
        "obs-0007",
        "obs-0012",
        "obs-0014"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0012",
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
      "at": "0x00dd06a0",
      "count": 5,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00dd06a1",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00dd06a1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00dd06ac",
      "definite": true,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x88]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00dd06b7",
      "count": 2,
      "first_use": 7,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 7,
      "kind": "REG_READ",
      "raw": "SBB EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00dd06c3",
      "id": "obs-0006",
      "index": 10,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00dd06c4",
      "form": "RET",
      "id": "obs-0007",
      "imm": null,
      "index": 11,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00dd06d1",
      "id": "obs-0008",
      "index": 14,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b6e250",
      "target": "0x00b6e250"
    },
    {
      "at": "0x00dd06e1",
      "id": "obs-0009",
      "index": 19,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b6f0d0",
      "target": "0x00b6f0d0"
    },
    {
      "at": "0x00dd06e6",
      "definite": true,
      "id": "obs-0010",
      "index": 20,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x4",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00dd06e9",
      "id": "obs-0011",
      "index": 21,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00dd06ea",
      "form": "RET",
      "id": "obs-0012",
      "imm": null,
      "index": 22,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00dd06f0",
      "id": "obs-0013",
      "index": 24,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00dd06f1",
      "form": "RET",
      "id": "obs-0014",
      "imm": null,
      "index": 25,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
   
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
  "count": 26,
  "instructions": [
    {
      "address": "00dd06a0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00dd06a1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00dd06a3",
      "instruction": "CMP dword ptr [ESI + 0x84],0x1"
    },
    {
      "address": "00dd06aa",
      "instruction": "JNZ 0x00dd06c5"
    },
    {
      "address": "00dd06ac",
      "instruction": "MOV EAX,dword ptr [ESI + 0x88]"
    },
    {
      "address": "00dd06b2",
      "instruction": "SUB EAX,0x2"
    },
    {
      "address": "00dd06b5",
      "instruction": "NEG EAX"
    },
    {
      "address": "00dd06b7",
      "instruction": "SBB EAX,EAX"
    },
    {
      "address": "00dd06b9",
      "instruction": "AND EAX,0xff577f34"
    },
    {
      "address": "00dd06be",
      "instruction": "ADD EAX,0xfffff045"
    },
    {
      "address": "00dd06c3",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd06c4",
      "instruction": "RET"
    },
    {
      "address": "00dd06c5",
      "instruction": "CMP dword ptr [ESI + 0x88],0xff576f79"
    },
    {
      "address": "00dd06cf",
      "instruction": "JZ 0x00dd06eb"
    },
    {
      "address": "00dd06d1",
      "instruction": "CALL 0x00b6e250"
    },
    {
      "address": "00dd06d6",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00dd06d8",
      "instruction": "JZ 0x00dd06eb"
    },
    {
      "address": "00dd06da",
      "instruction": "MOV EAX,dword ptr [ESI + 0x88]"
    },
    {
      "address": "00dd06e0",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00dd06e1",
      "instruction": "CALL 0x00b6f0d0"
    },
    {
      "address": "00dd06e6",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00dd06e9",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd06ea",
      "instruction": "RET"
    },
    {
      "address": "00dd06eb",
      "instruction": "MOV EAX,0xff576f79"
    },
    {
      "address": "00dd06f0",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd06f1",
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
  "original_bytes": 10102,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"std::int32_t\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147cbbc\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147cbbc\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147cbbc\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_name_00641810\",\n      \"va\": \"0x00641810\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147cbbc\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_id_00641820\",\n      \"va\": \"0x00641820\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147cbbc\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_tags_00641850\",\n      \"va\": \"0x00641850\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147cbbc\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_time_created_00641860\",\n      \"va\": \"0x00641860\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147cbbc\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 4,\n      \"symbol\": \"FUN_00ff3f00\",\n      \"va\": \"0x00ff3f00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00dd06d1\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b6e250\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd06e1\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b6f0d0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0506\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00dd06a0\",\n  \"normalized_symbol\": \"FUN_00dd06a0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w1-00dd06a0/00dd06a0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Sporepedia\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sporepedia-online\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00dd06a0\",\n    \"name\": \"FUN_00dd06a0\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\n      \"vtable_addrs\": [\n        \"0147cbbc\"\n      ]\n    },\n    \"queue_state\": \"candidate\",\n    \"rank\": 243\n  },\n  \"types\": [\n    \"std::int32_t\"\n  ],\n  \"unresolved_questions\": [\n    \"Is 0x00dd06d1's call really argument-free, as a behavioural matter? As a STATIC matter it is: the instruction before the call is 0x00dd06cf's JZ, no instruction pushes for it, and 0x00b6e250'
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
  "body_end": "00dd06f1",
  "body_span_bytes": 82,
  "body_start": "00dd06a0",
  "callees": [
    "FUN_00b6e250",
    "FUN_00b6f0d0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00dd06a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00dd06a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x9d06a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00dd06a0(void)",
  "size_bytes": 82,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00dd06a0",
  "vtables": {
    "referenced_by_vtables": [
      "0x0147cbbc"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0147cbe4"
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
  "global:PASS"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00dd06a0/sw1_00dd06a0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00dd06a0/00dd06a0.json"
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
  "std::int32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0147cbbc"
]
```

## Conflicts

```json
[]
```
