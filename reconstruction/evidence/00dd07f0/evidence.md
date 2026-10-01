# Evidence 0x00dd07f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d8f785e6a65eadd3240748c2a2f94c3d310c7574c5aeb3a9adcc0dd32080136e`

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
    "flow_not_modelled: the linear ESP walk ends at -28, so the listing is not one path"
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
  "content_sha256": "675e605ecda2d57628f1bea2a581c328fb37ef3c0f861323d895d1bfd41be159",
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
        "obs-0008",
        "obs-0012",
        "obs-0016",
        "obs-0022",
        "obs-0025",
        "obs-0027",
        "obs-0029",
        "obs-0031"
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
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0013"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          132,
          136,
          140,
          152
        ],
        "register": "ECX",
        "written_through": 9
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0008",
        "obs-0012",
        "obs-0013",
        "obs-0016",
        "obs-0022",
        "obs-0025",
        "obs-0027",
        "obs-0029",
        "obs-0031"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0012",
        "obs-0016",
        "obs-0022",
        "obs-0025",
        "obs-0027",
        "obs-0029",
        "obs-0031"
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
        "obs-0008",
        "obs-0012",
        "obs-0016",
        "obs-0022",
        "obs-0025",
        "obs-0027",
        "obs-0029",
        "obs-0031"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0012",
        "obs-0016",
        "obs-0022",
        "obs-0025",
        "obs-0027",
        "obs-0029",
        "obs-0031"
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
      "at": "0x00dd07f0",
      "count": 14,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00dd07f1",
      "count": 6,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00dd07f1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00dd07f3",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x98]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00dd0801",
      "count": 9,
      "first_use": 5,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [EAX + 0xc]",
      "reg": "EAX"
    },
    {
      "at": "0x00dd0801",
      "definite": true,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EAX + 0xc]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00dd0814",
      "id": "obs-0007",
      "index": 9,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00dd0815",
      "form": "RET",
      "id": "obs-0008",
      "imm": null,
      "index": 10,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00dd0820",
      "definite": true,
      "id": "obs-0009",
      "index": 12,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0xc]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00dd0823",
      "count": 3,
      "first_use": 13,
      
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
  "count": 68,
  "instructions": [
    {
      "address": "00dd07f0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00dd07f1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00dd07f3",
      "instruction": "MOV EAX,dword ptr [ESI + 0x98]"
    },
    {
      "address": "00dd07f9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00dd07fb",
      "instruction": "JZ 0x00dd08f0"
    },
    {
      "address": "00dd0801",
      "instruction": "MOV ECX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00dd0804",
      "instruction": "CMP dword ptr [ECX + 0x10],0x6"
    },
    {
      "address": "00dd0808",
      "instruction": "JNZ 0x00dd0816"
    },
    {
      "address": "00dd080a",
      "instruction": "MOV dword ptr [ESI + 0x8c],0xfffffffe"
    },
    {
      "address": "00dd0814",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd0815",
      "instruction": "RET"
    },
    {
      "address": "00dd0816",
      "instruction": "MOV dword ptr [ESI + 0x8c],0x3"
    },
    {
      "address": "00dd0820",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00dd0823",
      "instruction": "MOV EAX,dword ptr [EDX + 0x20]"
    },
    {
      "address": "00dd0826",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "00dd0829",
      "instruction": "JNZ 0x00dd0837"
    },
    {
      "address": "00dd082b",
      "instruction": "MOV dword ptr [ESI + 0x8c],0xfffffffd"
    },
    {
      "address": "00dd0835",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd0836",
      "instruction": "RET"
    },
    {
      "address": "00dd0837",
      "instruction": "MOV ECX,dword ptr [ESI + 0x84]"
    },
    {
      "address": "00dd083d",
      "instruction": "DEC ECX"
    },
    {
      "address": "00dd083e",
      "instruction": "MOV EDX,0x4"
    },
    {
      "address": "00dd0843",
      "instruction": "CMP ECX,EDX"
    },
    {
      "address": "00dd0845",
      "instruction": "JA 0x00dd08f0"
    },
    {
      "address": "00dd084b",
      "instruction": "JMP dword ptr [ECX*0x4 + 0xdd08f4]"
    },
    {
      "address": "00dd0852",
      "instruction": "CMP EAX,0x7"
    },
    {
      "address": "00dd0855",
      "instruction": "JA 0x00dd08f0"
    },
    {
      "address": "00dd085b",
      "instruction": "JMP dword ptr [EAX*0x4 + 0xdd0908]"
    },
    {
      "address": "00dd0862",
      "instruction": "MOV dword ptr [ESI + 0x8c],0x2"
    },
    {
      "address": "00dd086c",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd086d",
      "instruction": "RET"
    },
    {
      "address": "00dd086e",
      "instruction": "LEA EAX,[ESI + 0x4]"
    },
    {
      "address": "00dd0871",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00dd0872",
      "instruction": "CALL 0x00401090"
    },
    {
      "address": "00dd0877",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00dd0879",
      "instruction": "CALL 0x004df400"
    },
    {
      "address": "00dd087e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00dd087f",
      "instruction": "CALL 0x004eb930"
    },
    {
      "address": "00dd0884",
      "instruction": "MOVZX ECX,AL"
    },
    {
      "address": "00dd0887",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00dd088a",
      "instruction": "NEG ECX"
    },
    {
      "address": "00dd088c",
      "instruction": "SBB ECX,ECX"
    },
    {
      "address": "00dd088e",
      "instruction": "AND ECX,0x7ffffffa"
    },
    {
      "address": "00dd0894",
      "instruction": "ADD ECX,0x5"
    },
    {
      "address": "00dd0897",
      "instruction": "MOV dword ptr [ESI + 0x8c],ECX"
    },
    {
      "address": "00dd089d",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd089e",
      "instruction": "RET"
    },
    {
      "address": "00dd089f",
      "instruction": "CMP EAX,EDX"
    },
    {
      "address": "00dd08a1",
      "instruction": "JA 0x00dd08f0"
    },
    {
      "address": "00dd08a3",
      "instruction": "JMP dword ptr [EAX*0x4 + 0xdd0928]"
    },
    {
      "address": "00dd08aa",
      "instruction": "MOV dword ptr [ESI + 0x8c],0x0"
    },
    {
      "address": "00dd08b4",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd08b5",
      "instruction": "RET"
    },
    {
      "address": "00dd08b6",
      "instruction": "MOV dword ptr [ESI + 0x8c],0x1"
    },
    {
      "address": "00dd08c0",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd08c1",
      "instruction": "RET"
    },
    {
      "address": "00dd08c2",
      "instruction": "MOV dword ptr [ESI + 0x8c],0x3"
    },
    {
      "address": "00dd08cc",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd08cd",
      "instruction": "RET"
    },
    {
      "address": "00dd08ce",
      "instruction": "MOV EDX,dword ptr [ESI + 0x88]"
    },
    {
      "address": "00dd08d4",
      "instruction": "SUB EDX,0x53dbcf1"
    },
    {
      "address": "00dd08da",
      "instruction": "NEG EDX"
    },
    {
      "address": "00dd08dc",
      "instruction": "SBB EDX,EDX"
    },
    {
      "address": "00dd08de",
      "instruction": "AND EDX,0x80000006"
    },
    {
      "address": "00dd08e4",
      "instruction": "ADD EDX,0x7fffffff"
    },
    {
      "address": "00dd08ea",
      "instruction": "MOV dword ptr [ESI + 0x8c],EDX"
    },
    {
      "address": "00dd08f0",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd08f1",
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
  "original_bytes": 7751,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147ca30,vtable:0x0147caf8\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147ca30,vtable:0x0147ca70\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147ca30,vtable:0x0147ca70\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func3ch_006417b0\",\n      \"va\": \"0x006417b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147ca30,vtable:0x0147ca70\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0\",\n      \"va\": \"0x006417c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00dd0872\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401090\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0879\",\n        \"direction\": \"out\",\n        \"other\": \"0x004df400\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd087f\",\n        \"direction\": \"out\",\n        \"other\": \"0x004eb930\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0507\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00dd07f0\",\n  \"normalized_symbol\": \"FUN_00dd07f0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w2-00dd07f0/sw2_00dd07f0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00dd07f0/sw2_00dd07f0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00dd07f0/sw2_00dd07f0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w2-00dd07f0/00dd07f0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Sporepedia\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sporepedia-online\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00dd07f0\",\n    \"name\": \"FUN_00dd07f0\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\n      \"vtable_addrs\": [\n        \"0147ca30\",\n        \"0147ca70\",\n        \"0147caf8\",\n        \"0147cc14\"\n      ]\n    },\n    \"queue_state\": \"candidate\",\n    \"r
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
  "body_end": "00dd08f1",
  "body_span_bytes": 258,
  "body_start": "00dd07f0",
  "callees": [
    "FUN_004eb930",
    "FUN_004df400",
    "Editors::cSpeciesManager::Get"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00dd07f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00dd07f0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x9d07f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00dd07f0(void)",
  "size_bytes": 258,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00dd07f0",
  "vtables": {
    "referenced_by_vtables": [
      "0x0147ca30",
      "0x0147ca70",
      "0x0147caf8",
      "0x0147cc14"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "0147cabc"
    },
    {
      "from": "0147cb84"
    },
    {
      "from": "0147cc74"
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
    "reconstruction/staging/pkg-swarm-w2-00dd07f0/sw2_00dd07f0.cpp",
    "reconstruction/staging/pkg-swarm-w2-00dd07f0/sw2_00dd07f0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00dd07f0/sw2_00dd07f0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00dd07f0/00dd07f0.json"
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
  "vtable:0x0147ca30",
  "vtable:0x0147ca70",
  "vtable:0x0147caf8",
  "vtable:0x0147cc14"
]
```

## Conflicts

```json
[]
```
