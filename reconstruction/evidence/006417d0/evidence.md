# Evidence 0x006417d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `3d62abf59c0c65ec9cc3c7da3f8a3388f76e3869cef439c55fde2b1999a77fde`

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
  "ret_form": "RET 0x4 (both sites)",
  "return_note": "(literal 1 or literal 0 in the low byte only)",
  "return_register": "EAX",
  "return_type": "std::uint8_t",
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
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "23e949b1aeb539b137000f4747656cae3ae0533e92dc27db9e296e95f4d69675",
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
        "obs-0014",
        "obs-0016"
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
        "obs-0010"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
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
        "obs-0004",
        "obs-0009",
        "obs-0010",
        "obs-0011"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          28
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0014",
        "obs-0016"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0010"
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
        "obs-0014",
        "obs-0016"
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
        "obs-0014",
        "obs-0016"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0014",
        "obs-0016"
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
      "at": "0x006417d0",
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
      "at": "0x006417d1",
      "count": 3,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x006417d1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x006417d3",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x1c]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006417da",
      "id": "obs-0005",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x005507a0",
      "target": "0x005507a0"
    },
    {
      "at": "0x006417df",
      "count": 5,
      "first_use": 6,
      "first_write_index": 15,
      "id": "obs-0006",
      "index": 6,
      "kind": "REG_READ",
      "raw": "CMP dword ptr [EAX],-0x1",
      "reg": "EAX"
    },
    {
      "at": "0x006417ed",
      "id": "obs-0007",
      "index": 11,
   
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
  "count": 23,
  "instructions": [
    {
      "address": "006417d0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006417d1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "006417d3",
      "instruction": "MOV ECX,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "006417d6",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "006417d8",
      "instruction": "JZ 0x00641806"
    },
    {
      "address": "006417da",
      "instruction": "CALL 0x005507a0"
    },
    {
      "address": "006417df",
      "instruction": "CMP dword ptr [EAX],-0x1"
    },
    {
      "address": "006417e2",
      "instruction": "JNZ 0x006417ea"
    },
    {
      "address": "006417e4",
      "instruction": "CMP dword ptr [EAX + 0x4],-0x1"
    },
    {
      "address": "006417e8",
      "instruction": "JZ 0x00641806"
    },
    {
      "address": "006417ea",
      "instruction": "MOV ECX,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "006417ed",
      "instruction": "CALL 0x005507a0"
    },
    {
      "address": "006417f2",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "006417f4",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "006417f8",
      "instruction": "MOV dword ptr [ECX],EDX"
    },
    {
      "address": "006417fa",
      "instruction": "MOV EAX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "006417fd",
      "instruction": "MOV dword ptr [ECX + 0x4],EAX"
    },
    {
      "address": "00641800",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00641802",
      "instruction": "POP ESI"
    },
    {
      "address": "00641803",
      "instruction": "RET 0x4"
    },
    {
      "address": "00641806",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00641808",
      "instruction": "POP ESI"
    },
    {
      "address": "00641809",
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
  "original_bytes": 9608,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4 (both sites)\",\n    \"return_note\": \"(literal 1 or literal 0 in the low byte only)\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"std::uint8_t\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func3ch_006417b0\",\n      \"va\": \"0x006417b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0\",\n      \"va\": \"0x006417c0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_name_00641810\",\n      \"va\": \"0x00641810\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_id_00641820\",\n      \"va\": \"0x00641820\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_tags_00641850\",\n      \"va\": \"0x00641850\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006417da\",\n        \"direction\": \"out\",\n        \"other\": \"0x005507a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006417ed\",\n        \"direction\": \"out\",\n        \"other\": \"0x005507a0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0159\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:none. No instruction in the body names a data-segment address, and the model names none.\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_006417d0\",\n  \"normalized_symbol\": \"FUN_006417d0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w1-006417d0/swarm_w1_006417d0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-006417d0/swarm_w1_006417d0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-006417d0/swarm_w1_006417d0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w1-006417d0/006417d0.json\"\n    ],\n    \"provenance\": [\n      \"/tmp/opencode/factory/w1/tasks/006417d0.json (assembled briefing)\",\n      \"GhidraMCP /decompile_function 0x006417d0 (the CONCAT31 return rendering and the shifted parameter naming)\",\n      \"GhidraMCP /disassemble_function 0x005507a0 (11 bytes; receiver+0x18 accessor, C3 terminator)\",\n      \"GhidraMCP /disassemble_function 0x006417d0 (23 instructions, 0x006417d0..0x00641809)\",\n      \"GhidraMCP /get_function_by_address 0x006417d0 (body_span_bytes 60, xref_count 7, callees [FUN_005507a0], no callers, signature \\\"undefined FUN_006417d0(void)\\\")\",\n      \"GhidraMCP /get_function_callers 0x005507a
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
  "body_end": "0064180b",
  "body_span_bytes": 60,
  "body_start": "006417d0",
  "callees": [
    "FUN_005507a0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006417d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_006417d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x2417d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_006417d0(void)",
  "size_bytes": 60,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006417d0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013ff648",
      "0x01462764",
      "0x0147ca30",
      "0x0147ca70",
      "0x0147caf8",
      "0x0147cbbc",
      "0x01489090",
      "0x014893b0",
      "0x013ff6ac",
      "0x0147cc14",
      "0x014890f4",
      "0x01489414",
      "0x014627bc"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "013ff6d8"
    },
    {
      "from": "014627e8"
    },
    {
      "from": "0147ca88"
    },
    {
      "from": "0147cb50"
    },
    {
      "from": "0147cc40"
    },
    {
      "from": "01489120"
    },
    {
      "from": "01489440"
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
  "global:none. No instruction in the body names a data-segment address, and the model names none."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-006417d0/swarm_w1_006417d0.cpp",
    "reconstruction/staging/pkg-swarm-w1-006417d0/swarm_w1_006417d0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-006417d0/swarm_w1_006417d0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-006417d0/006417d0.json"
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
  "std::uint8_t",
  "std::uint8_t (literal 1 or literal 0 in the low byte only)"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013ff648",
  "vtable:0x013ff6ac",
  "vtable:0x01462764",
  "vtable:0x014627bc",
  "vtable:0x0147ca30",
  "vtable:0x0147ca70",
  "vtable:0x0147caf8",
  "vtable:0x0147cbbc",
  "vtable:0x0147cc14",
  "vtable:0x01489090",
  "vtable:0x014890f4",
  "vtable:0x014893b0",
  "vtable:0x01489414"
]
```

## Conflicts

```json
[]
```
