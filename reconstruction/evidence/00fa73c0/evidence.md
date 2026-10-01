# Evidence 0x00fa73c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a192d5012ba262232cd756dda90fd6bb9a494179d71cb9828d3f77eff1a0ea34`

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
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
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
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path"
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
  "content_sha256": "e02772add622cb133b4384caa78047444eeddf5c85e8ebd4545c20a8fc29e3b9",
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
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0023"
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
        "obs-0003",
        "obs-0004",
        "obs-0012",
        "obs-0013"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          40,
          524,
          1944,
          1948,
          2068
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0012",
        "obs-0013",
        "obs-0023"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0023"
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
        "obs-0023"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0023"
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
      "at": "0x00fa73c0",
      "count": 3,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00fa73c1",
      "count": 10,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00fa73c2",
      "count": 4,
      "first_use": 2,
      "first_write_index": 19,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00fa73c2",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00fa73c4",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESI + 0x798]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00fa73ca",
      "count": 3,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00fa73cb",
      "definite": true,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESI + 0x79c]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00fa73d4",
      "id": "obs-0008",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f9f770",
      "target": "0x00f9f770"
    },
    {
      "at": "0x00fa73db",
      "definite": true,
      "id": "obs-0009",
      "index": 11,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0xd05f417d",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x00fa73e2",
      "count": 6,
      "first_use": 13,
      "first_write_index": 20,
      "id": "obs-0010",
      "index": 13,
      "kind": "REG_READ",
      "raw": "SAR EDX,0x5",
      "reg": "EDX"
    },
    {
      "at": "0x00fa73e7",
      "count": 6,
      "first_use": 15,
      "first_write_index": 11,
      "id": "obs-0011",
      "index": 15,
      "kind": "REG_READ",
      "raw": "SHR EAX,0x1f",
      "reg": "EAX"
    },
    {
      "at": "0x00fa73f8",
      "definite": true,
      "id": "obs-0012",
      "index": 19,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x28]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00fa73fb",
      "definit
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
  "count": 46,
  "instructions": [
    {
      "address": "00fa73c0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00fa73c1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00fa73c2",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00fa73c4",
      "instruction": "MOV EBX,dword ptr [ESI + 0x798]"
    },
    {
      "address": "00fa73ca",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00fa73cb",
      "instruction": "MOV EDI,dword ptr [ESI + 0x79c]"
    },
    {
      "address": "00fa73d1",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00fa73d2",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00fa73d3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00fa73d4",
      "instruction": "CALL 0x00f9f770"
    },
    {
      "address": "00fa73d9",
      "instruction": "SUB EDI,EBX"
    },
    {
      "address": "00fa73db",
      "instruction": "MOV EAX,0xd05f417d"
    },
    {
      "address": "00fa73e0",
      "instruction": "IMUL EDI"
    },
    {
      "address": "00fa73e2",
      "instruction": "SAR EDX,0x5"
    },
    {
      "address": "00fa73e5",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "00fa73e7",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "00fa73ea",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "00fa73ec",
      "instruction": "IMUL EAX,EAX,0xac"
    },
    {
      "address": "00fa73f2",
      "instruction": "ADD dword ptr [ESI + 0x79c],EAX"
    },
    {
      "address": "00fa73f8",
      "instruction": "MOV ECX,dword ptr [ESI + 0x28]"
    },
    {
      "address": "00fa73fb",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00fa73fd",
      "instruction": "MOV EAX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "00fa7400",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00fa7403",
      "instruction": "PUSH 0x536250c"
    },
    {
      "address": "00fa7408",
      "instruction": "CALL EAX"
    },
    {
      "address": "00fa740a",
      "instruction": "MOV ECX,dword ptr [ESI + 0x28]"
    },
    {
      "address": "00fa740d",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00fa740f",
      "instruction": "MOV EAX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "00fa7412",
      "instruction": "PUSH 0x536250d"
    },
    {
      "address": "00fa7417",
      "instruction": "CALL EAX"
    },
    {
      "address": "00fa7419",
      "instruction": "MOV ECX,dword ptr [ESI + 0x28]"
    },
    {
      "address": "00fa741c",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00fa741e",
      "instruction": "MOV EAX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "00fa7421",
      "instruction": "PUSH 0x3a23f9a"
    },
    {
      "address": "00fa7426",
      "instruction": "CALL EAX"
    },
    {
      "address": "00fa7428",
      "instruction": "MOV ECX,dword ptr [ESI + 0x20c]"
    },
    {
      "address": "00fa742e",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00fa7430",
      "instruction": "CALL 0x00fbaf10"
    },
    {
      "address": "00fa7435",
      "instruction": "MOV ECX,dword ptr [ESI + 0x20c]"
    },
    {
      "address": "00fa743b",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00fa743d",
      "instruction": "CALL 0x00fbaf50"
    },
    {
      "address": "00fa7442",
      "instruction": "INC dword ptr [ESI + 0x814]"
    },
    {
      "address": "00fa7448",
      "instruction": "POP EDI"
    },
    {
      "address": "00fa7449",
      "instruction": "POP ESI"
    },
    {
      "address": "00fa744a",
      "instruction": "POP EBX"
    },
    {
      "address": "00fa744b",
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
  "original_bytes": 9767,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00fa73d4\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f9f770\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fa7430\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fbaf10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fa743d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fbaf50\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0580\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00fa73c0\",\n  \"normalized_symbol\": \"FUN_00fa73c0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w1-00fa73c0/00fa73c0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Sporepedia\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sporepedia-online\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00fa73c0\",\n    \"name\": \"FUN_00fa73c0\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\n      \"vtable_addrs\": [\n        \"01490be8\"\n      ]\n    },\n    \"queue_state\": \"candidate\",\n    \"rank\": 286\n  },\n  \"types\": [\n    \"void\"\n  ],\n  \"unresolved_questions\": [\n    \"Are the words at receiver+0x798 and +0x79c pointers, indices or counts? Thi
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
  "body_end": "00fa744b",
  "body_span_bytes": 140,
  "body_start": "00fa73c0",
  "callees": [
    "FUN_00fbaf10",
    "FUN_00f9f770",
    "FUN_00fbaf50"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00fa73c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00fa73c0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xba73c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00fa73c0(void)",
  "size_bytes": 140,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00fa73c0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01490be8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01490c58"
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
    "reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00fa73c0/00fa73c0.json"
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
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01490be8"
]
```

## Conflicts

```json
[]
```
