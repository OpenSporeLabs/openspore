# Evidence 0x00f9b7f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `4129d270b3d58e35140e9b217e0e71c0b354905be3c0bf2ba1bd932f5f4a8265`

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
  "return_note": "(INFERRED)",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "ESI",
    "EDI",
    "EBX"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "callee (the RET carries no immediate, so for a zero-argument callee the two readings coincide; the record's stack_cleanup_owner 'caller' is the machine-derived tool's phrasing of the same fact)",
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
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path"
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
  "content_sha256": "caf7c2f7c3e2b827046ae7573cb7158696d2b74335d7e0e4b17e3f6e9b9c6f69",
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
        "obs-0034"
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
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0015",
        "obs-0021",
        "obs-0024",
        "obs-0027"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          40,
          2068
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0015",
        "obs-0021",
        "obs-0024",
        "obs-0027",
        "obs-0034"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0034"
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
        "obs-0034"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0034"
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
      "and_esp": null,
      "at": "0x00f9b7f0",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x18",
      "sub": 24
    },
    {
      "at": "0x00f9b7f0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x18",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00f9b7f3",
      "count": 9,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00f9b7f4",
      "count": 8,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00f9b7f4",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00f9b7f6",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x28]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00f9b801",
      "definite": true,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00f9b803",
      "count": 6,
      "first_use": 7,
      "first_write_index": 6,
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x24]",
      "reg": "EAX"
    },
    {
      "at": "0x00f9b806",
      "count": 4,
      "first_use": 8,
      "first_write_index": 12,
      "id": "obs-0009",
      "index": 8,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00f9b807",
      "count": 5,
      "first_use": 9,
      "first_write_index": 25,
      "id": "obs-0010",
      "index": 9,
      "kind": "REG_READ",
      "raw": "LEA EDX,[ESP + 0x8]",
      "reg": "EDX"
    },
    {
      "at": "0x00f9b807",
      "count": 8,
      "first_use": 9,
      "first_write_index": 0,
      "id": "obs-0011",
      "index": 9,
      "kind": "REG_READ",
    
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "editor_query_clear_flags_0093db80",
    "reconstructed": true,
    "va": "0x0093db80"
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
  "count": 64,
  "instructions": [
    {
      "address": "00f9b7f0",
      "instruction": "SUB ESP,0x18"
    },
    {
      "address": "00f9b7f3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00f9b7f4",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00f9b7f6",
      "instruction": "MOV ECX,dword ptr [ESI + 0x28]"
    },
    {
      "address": "00f9b7f9",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00f9b7fb",
      "instruction": "JZ 0x00f9b8ac"
    },
    {
      "address": "00f9b801",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00f9b803",
      "instruction": "MOV EAX,dword ptr [EAX + 0x24]"
    },
    {
      "address": "00f9b806",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00f9b807",
      "instruction": "LEA EDX,[ESP + 0x8]"
    },
    {
      "address": "00f9b80b",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00f9b80c",
      "instruction": "PUSH 0x3ad556a"
    },
    {
      "address": "00f9b811",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00f9b813",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f9b815",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00f9b817",
      "instruction": "JZ 0x00f9b82b"
    },
    {
      "address": "00f9b819",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00f9b81d",
      "instruction": "CMP word ptr [ECX + 0x12],0xa"
    },
    {
      "address": "00f9b822",
      "instruction": "JNZ 0x00f9b82b"
    },
    {
      "address": "00f9b824",
      "instruction": "CALL 0x0041ea00"
    },
    {
      "address": "00f9b829",
      "instruction": "MOV EDI,dword ptr [EAX]"
    },
    {
      "address": "00f9b82b",
      "instruction": "CMP EDI,dword ptr [ESI + 0x814]"
    },
    {
      "address": "00f9b831",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00f9b832",
      "instruction": "LEA EBX,[ESI + 0x814]"
    },
    {
      "address": "00f9b838",
      "instruction": "JZ 0x00f9b8aa"
    },
    {
      "address": "00f9b83a",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00f9b83c",
      "instruction": "MOV EAX,dword ptr [EDX + 0x80]"
    },
    {
      "address": "00f9b842",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f9b844",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f9b846",
      "instruction": "MOV EDI,dword ptr [ESI + 0x28]"
    },
    {
      "address": "00f9b849",
      "instruction": "MOV ECX,0xa"
    },
    {
      "address": "00f9b84e",
      "instruction": "MOV word ptr [ESP + 0x22],CX"
    },
    {
      "address": "00f9b853",
      "instruction": "MOV EDX,0x2"
    },
    {
      "address": "00f9b858",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00f9b859",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00f9b85d",
      "instruction": "MOV word ptr [ESP + 0x24],DX"
    },
    {
      "address": "00f9b862",
      "instruction": "CALL 0x00427fd0"
    },
    {
      "address": "00f9b867",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00f9b869",
      "instruction": "MOV EDX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00f9b86c",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "00f9b870",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00f9b871",
      "instruction": "PUSH 0x3ad556a"
    },
    {
      "address": "00f9b876",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00f9b878",
      "instruction": "CALL EDX"
    },
    {
      "address": "00f9b87a",
      "instruction": "TEST byte ptr [ESP + 0x20],0x4"
    },
    {
      "address": "00f9b87f",
      "instruction": "JZ 0x00f9b88c"
    },
    {
      "address": "00f9b881",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00f9b883",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00f9b887",
      "instruction": "CALL 0x0093db80"
    },
    {
      "address": "00f9b88c",
      "instruction": "MOV ESI,dword ptr [ESI + 0x28]"
    },
    {
      "address": "00f9b88f",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00f9b891",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00f9b893",
      "instruction": "PUSH 0x31389b5"
    },
    {
      "address": "00f9b898",
      "instruction": "CALL 0x006b1f90"
    },
    {
      "address": "00f9b89d",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00f9b8a0",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00f9b8a1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00f9b8a2",
      "instruction": "CALL 0x006b4b60"
    },
    {
      "address": "00f9b8a7",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00f9b8aa",
      "instruction": "POP EBX"
    },
    {
      "address": "00f9b8ab",
      "instruction": "POP EDI"
    },
    {
      "address": "00f9b8ac",
      "instruction": "POP ESI"
    },
    {
      "address": "00f9b8ad",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "00f9b8b0",
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
  "original_bytes": 10119,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_note\": \"(INFERRED)\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"ESI\",\n      \"EDI\",\n      \"EBX\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"callee (the RET carries no immediate, so for a zero-argument callee the two readings coincide; the record's stack_cleanup_owner 'caller' is the machine-derived tool's phrasing of the same fact)\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"editor_query_clear_flags_0093db80\",\n      \"va\": \"0x0093db80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"terrain-world\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"editor_query_clear_flags_0093db80\",\n        \"reconstructed\": true,\n        \"va\": \"0x0093db80\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00f9b824\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041ea00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9b862\",\n        \"direction\": \"out\",\n        \"other\": \"0x00427fd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9b898\",\n        \"direction\": \"out\",\n        \"other\": \"0x006b1f90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9b8a2\",\n        \"direction\": \"out\",\n        \"other\": \"0x006b4b60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9b887\",\n        \"direction\": \"out\",\n        \"other\": \"0x0093db80\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x0093db80\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0573\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00f9b7f0\",\n  \"normalized_symbol\": \"FUN_00f9b7f0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w1-00f9b7f0/00f9b7f0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Terrain\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"terrain-world\",\n 
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
  "body_end": "00f9b8b0",
  "body_span_bytes": 193,
  "body_start": "00f9b7f0",
  "callees": [
    "FUN_00427fd0",
    "FUN_0041ea00",
    "FUN_006b1f90",
    "FUN_0093db80",
    "FUN_006b4b60"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00f9b7f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00f9b7f0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xb9b7f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00f9b7f0(void)",
  "size_bytes": 193,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00f9b7f0",
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
      "from": "01490c6c"
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
    "reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00f9b7f0/00f9b7f0.json"
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
  "void (INFERRED from the listing; see return_semantics and unresolved_questions)",
  "void (INFERRED)"
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
