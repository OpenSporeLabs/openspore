# Evidence 0x00a649a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a7b42ecb593cd56ff7fe5374debd6d93d061b6ee46d94839df450da4cd9d8ae6`

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
  "ret_form": "RET (C3, bare)",
  "return_register": "EAX",
  "return_type": "Word",
  "saved_registers": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "callee owns nothing; nominally the caller, and 0 bytes either way",
  "termination": "RET (C3, bare)"
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
    "return_semantics": "pointer_like_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "855207f29d98cf62acb06b99402bb8ce9994aa935c9fd1908fb56a63852d08b5",
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
        "obs-0003"
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
        "obs-0002"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          108
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
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
      "at": "0x00a649a0",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x6c]",
      "reg": "ECX"
    },
    {
      "at": "0x00a649a0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x6c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00a649a3",
      "form": "RET",
      "id": "obs-0003",
      "imm": null,
      "index": 1,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 2,
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
    "max_offset": 108,
    "offsets": [
      108
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
    "register_class": "pointer_like",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": null,
    "present": false,
    "target": null
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00a649a0"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_INFERRED"
}
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
    "va": "0x00a53d20"
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
  "count": 2,
  "instructions": [
    {
      "address": "00a649a0",
      "instruction": "MOV EAX,dword ptr [ECX + 0x6c]"
    },
    {
      "address": "00a649a3",
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
  "original_bytes": 8194,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET (C3, bare)\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"Word\",\n    \"saved_registers\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"callee owns nothing; nominally the caller, and 0 bytes either way\",\n    \"termination\": \"RET (C3, bare)\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:Word\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func3ch_006417b0\",\n      \"va\": \"0x006417b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0\",\n      \"va\": \"0x006417c0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_name_00641810\",\n      \"va\": \"0x00641810\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_id_00641820\",\n      \"va\": \"0x00641820\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a53d20\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00a53da5\",\n        \"direction\": \"in\",\n        \"other\": \"0x00a53d20\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0332\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"FUN_00a649a0\",\n  \"normalized_symbol\": \"FUN_00a649a0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w1-00a649a0/00a649a0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Sporepedia\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sporepedia-online\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00a649a0\",\n    \"name\": \"FUN_00a649a0\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\n      \"vtable_addrs\": [\n        \"013ff648\",\n        \"013ff6ac\",\n        \"01462764\",\n        \"014627bc\",\n        \"0147c9e8\",\n        \"0147ca30\",\n        \"0147ca70\",\n        \"0147caf8\",\n        \"0147cbbc\"
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
  "body_end": "00a649a3",
  "body_span_bytes": 4,
  "body_start": "00a649a0",
  "callees": [],
  "callers": [
    "FUN_00a53d20"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00a649a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00a649a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6649a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00a649a0(void)",
  "size_bytes": 4,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00a649a0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013ff648",
      "0x01462764",
      "0x0147c9e8",
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
  "xref_count": 8,
  "xrefs": [
    {
      "from": "00a53da5"
    },
    {
      "from": "013ff6d0"
    },
    {
      "from": "014627e0"
    },
    {
      "from": "0147ca80"
    },
    {
      "from": "0147cb48"
    },
    {
      "from": "0147cc38"
    },
    {
      "from": "01489118"
    },
    {
      "from": "01489438"
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
    "reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00a649a0/sw1_00a649a0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00a649a0/00a649a0.json"
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
  "Word",
  "std::uint32_t (Word)"
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
  "vtable:0x0147c9e8",
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
