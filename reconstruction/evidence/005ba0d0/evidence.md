# Evidence 0x005ba0d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `fdf9b84c74605d7ae30f4908914f17794e7bf8740621397aafbeb28b30823ac0`

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
  "return_type": "Word",
  "saved_registers": [],
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
    "return_semantics": "integral_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
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
  "content_sha256": "feb234efb77e27a25e118d39c4f828d327d4dfb0a304c9a1c2ac7c3b7c8e221a",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0008"
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
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          24
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0008"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
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
      "at": "0x005ba0d0",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x18]",
      "reg": "ECX"
    },
    {
      "at": "0x005ba0d0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x18]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005ba0d3",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "ADD ECX,0x14",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x005ba0d9",
      "count": 3,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ECX + 0x4],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x005ba0e7",
      "definite": true,
      "id": "obs-0005",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005ba0eb",
      "count": 1,
      "first_use": 9,
      "first_write_index": 7,
      "id": "obs-0006",
      "index": 9,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x005ba0eb",
      "base": "EDX",
      "disp": null,
      "id": "obs-0007",
      "index": 9,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x005ba0ef",
      "form": "RET",
      "id": "obs-0008",
      "imm": null,
      "index": 11,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 12,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 24,
    "offsets": [
      24
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "integral",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DER
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
  "count": 12,
  "instructions": [
    {
      "address": "005ba0d0",
      "instruction": "MOV EAX,dword ptr [ECX + 0x18]"
    },
    {
      "address": "005ba0d3",
      "instruction": "ADD ECX,0x14"
    },
    {
      "address": "005ba0d6",
      "instruction": "ADD EAX,-0x1"
    },
    {
      "address": "005ba0d9",
      "instruction": "MOV dword ptr [ECX + 0x4],EAX"
    },
    {
      "address": "005ba0dc",
      "instruction": "JNZ 0x005ba0ef"
    },
    {
      "address": "005ba0de",
      "instruction": "MOV dword ptr [ECX + 0x4],0x1"
    },
    {
      "address": "005ba0e5",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "005ba0e7",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005ba0e9",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005ba0eb",
      "instruction": "CALL EDX"
    },
    {
      "address": "005ba0ed",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "005ba0ef",
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
  "original_bytes": 8570,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"Word\",\n    \"saved_registers\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:Word\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_005737d0\",\n      \"va\": \"0x005737d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585890\",\n      \"va\": \"0x00585890\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585d10\",\n      \"va\": \"0x00585d10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0107\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS - none exist and none are declared\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_005ba0d0\",\n  \"normalized_symbol\": \"FUN_005ba0d0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w1-005ba0d0/sw1_005ba0d0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-005ba0d0/sw1_005ba0d0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-005ba0d0/sw1_005ba0d0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w1-005ba0d0/005ba0d0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Editor\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"editor-core\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:005ba0d0\",\n    \"name\": \"FUN_005ba0d0\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\n      \"vtable_addrs\": [\n        \"013f57f8\",\n        \"013f7028\",\n        \"013f70d4\",\n        \"013f718c\",\n        \"013f7214\",\n        \"013f72ac\",\n        \"013f7348\",\n        \"013f74cc\",\n        \"013f756c\",\n        \"013f7624\",\n        \"013f76c4\",\n        \"013f7774\"\n      ]\n    },\n    \"queue_state\": \"candidate\",\n    \"rank\": 216\n  },\n  \"types\": [\n    \"DispatchSlot0\",\n    \"DispatchSubobject\",\n    \"ReceiverWriteLog\",\n    \"Swarm005ba0d0Receiver\",\n    \"Word\",\n    \"Word (32-bit unsigned)\",\n    \"dispatch_slot0_005ba0eb\",\n    \"re_005ba0d0\"\n  ],\n  \"unresolved_questions\": [\n    \"Duplicate ownership: none at the time of writing. reconstruction/metadata had no 005ba0d0.json before this one and the evidence pack's existing_reconstruction lists no files, handoffs or meta
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
  "body_end": "005ba0ef",
  "body_span_bytes": 32,
  "body_start": "005ba0d0",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "005ba0d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005ba0d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1ba0d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005ba0d0(void)",
  "size_bytes": 32,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005ba0d0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f57f8",
      "0x013f7028",
      "0x013f72ac",
      "0x013f74cc",
      "0x013f756c",
      "0x013f76c4",
      "0x013f7820",
      "0x013f78c0",
      "0x013f70d4",
      "0x013f718c",
      "0x013f7214",
      "0x013f7348",
      "0x013f7624",
      "0x013f7774",
      "0x013f795c"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 18,
  "xrefs": [
    {
      "from": "013f57fc"
    },
    {
      "from": "013f703c"
    },
    {
      "from": "013f70e8"
    },
    {
      "from": "013f7190"
    },
    {
      "from": "013f7228"
    },
    {
      "from": "013f72c0"
    },
    {
      "from": "013f735c"
    },
    {
      "from": "013f74e0"
    },
    {
      "from": "013f7580"
    },
    {
      "from": "013f7638"
    },
    {
      "from": "013f76d8"
    },
    {
      "from": "013f7788"
    },
    {
      "from": "013f7834"
    },
    {
      "from": "013f78d4"
    },
    {
      "from": "013f7970"
    },
    {
      "from": "0057a5e3"
    },
    {
      "from": "0057a603"
    },
    {
      "from": "005ac9b3"
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
  "global:PASS - none exist and none are declared"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-005ba0d0/sw1_005ba0d0.cpp",
    "reconstruction/staging/pkg-swarm-w1-005ba0d0/sw1_005ba0d0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-005ba0d0/sw1_005ba0d0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-005ba0d0/005ba0d0.json"
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
  "DispatchSlot0",
  "DispatchSubobject",
  "ReceiverWriteLog",
  "Swarm005ba0d0Receiver",
  "Word",
  "Word (32-bit unsigned)",
  "dispatch_slot0_005ba0eb",
  "re_005ba0d0"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f57f8",
  "vtable:0x013f7028",
  "vtable:0x013f70d4",
  "vtable:0x013f718c",
  "vtable:0x013f7214",
  "vtable:0x013f72ac",
  "vtable:0x013f7348",
  "vtable:0x013f74cc",
  "vtable:0x013f756c",
  "vtable:0x013f7624",
  "vtable:0x013f76c4",
  "vtable:0x013f7774",
  "vtable:0x013f7820",
  "vtable:0x013f78c0",
  "vtable:0x013f795c"
]
```

## Conflicts

```json
[]
```
