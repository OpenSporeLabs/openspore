# Evidence 0x00f9bee0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `891affcf2e7e48fa73ef13d6344277b6547221a56143bfee164a50d12382fe91`

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
  "return_register": "EAX",
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
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
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBX",
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
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +36, so the listing is not one path"
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
  "content_sha256": "3a399207383cef8fb46c80d5d5bc7ef61d862cc410c2442fdfe3628c180f25d2",
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
    "indirect_calls": 9,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0040"
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
        "obs-0008"
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
        "obs-0013"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          2264
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0013",
        "obs-0040"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0040"
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
        "obs-0040"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0040"
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
      "at": "0x00f9bee0",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00f9bee1",
      "count": 1,
      "first_use": 1,
      "first_write_index": 13,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00f9bee1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,ECX",
      "reg": "EBX",
      "write_kind": "reg"
    },
    {
      "at": "0x00f9bee3",
      "count": 11,
      "first_use": 2,
      "first_write_index": 9,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00f9bee4",
      "count": 3,
      "first_use": 3,
      "first_write_index": 8,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00f9beee",
      "definite": true,
      "id": "obs-0006",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "XOR EDI,EDI",
      "reg": "EDI",
      "write_kind": "zero"
    },
    {
      "at": "0x00f9bef0",
      "count": 1,
      "first_use": 9,
      "first_write_index": 90,
      "id": "obs-0007",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x00f9bef0",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0008",
      "index": 9,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00f9bef0",
      "definite": true,
      "id": "obs-0009",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x10]",
      "reg": "ESI",
      "write_kind": "mem
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
  "count": 104,
  "instructions": [
    {
      "address": "00f9bee0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00f9bee1",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00f9bee3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00f9bee4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00f9bee5",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00f9bee7",
      "instruction": "JZ 0x00f9beee"
    },
    {
      "address": "00f9bee9",
      "instruction": "LEA EDI,[EBX + 0x4]"
    },
    {
      "address": "00f9beec",
      "instruction": "JMP 0x00f9bef0"
    },
    {
      "address": "00f9beee",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00f9bef0",
      "instruction": "MOV ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00f9bef4",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00f9bef6",
      "instruction": "MOV EDX,dword ptr [EAX + 0x58]"
    },
    {
      "address": "00f9bef9",
      "instruction": "PUSH 0x8"
    },
    {
      "address": "00f9befb",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f9befd",
      "instruction": "CALL EDX"
    },
    {
      "address": "00f9beff",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00f9bf01",
      "instruction": "JNZ 0x00f9c006"
    },
    {
      "address": "00f9bf07",
      "instruction": "CMP dword ptr [0x016c9e68],0x0"
    },
    {
      "address": "00f9bf0e",
      "instruction": "JZ 0x00f9bf15"
    },
    {
      "address": "00f9bf10",
      "instruction": "CALL 0x00f96c60"
    },
    {
      "address": "00f9bf15",
      "instruction": "CMP dword ptr [EBX + 0x8d8],0x0"
    },
    {
      "address": "00f9bf1c",
      "instruction": "JZ 0x00f9bf25"
    },
    {
      "address": "00f9bf1e",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00f9bf20",
      "instruction": "CALL 0x00f998f0"
    },
    {
      "address": "00f9bf25",
      "instruction": "CALL 0x0067ddd0"
    },
    {
      "address": "00f9bf2a",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00f9bf2c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00f9bf2e",
      "instruction": "MOV EAX,dword ptr [EDX + 0x54]"
    },
    {
      "address": "00f9bf31",
      "instruction": "PUSH 0x3fbae24"
    },
    {
      "address": "00f9bf36",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f9bf38",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00f9bf3a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00f9bf3c",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00f9bf3f",
      "instruction": "PUSH 0x3"
    },
    {
      "address": "00f9bf41",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f9bf43",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00f9bf45",
      "instruction": "MOV EAX,dword ptr [EDX + 0x50]"
    },
    {
      "address": "00f9bf48",
      "instruction": "PUSH 0xa"
    },
    {
      "address": "00f9bf4a",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f9bf4c",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f9bf4e",
      "instruction": "CALL 0x0067dd80"
    },
    {
      "address": "00f9bf53",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00f9bf55",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00f9bf57",
      "instruction": "MOV EAX,dword ptr [EDX + 0x1c]"
    },
    {
      "address": "00f9bf5a",
      "instruction": "PUSH 0x3fbae24"
    },
    {
      "address": "00f9bf5f",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f9bf61",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00f9bf63",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00f9bf65",
      "instruction": "MOV EAX,dword ptr [EDX + 0x134]"
    },
    {
      "address": "00f9bf6b",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00f9bf6d",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f9bf6f",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00f9bf71",
      "instruction": "MOV EAX,dword ptr [EDX + 0x50]"
    },
    {
      "address": "00f9bf74",
      "instruction": "PUSH 0x8"
    },
    {
      "address": "00f9bf76",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f9bf78",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f9bf7a",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00f9bf7c",
      "instruction": "MOV EAX,dword ptr [EDX + 0x50]"
    },
    {
      "address": "00f9bf7f",
      "instruction": "PUSH 0x7"
    },
    {
      "address": "00f9bf81",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f9bf83",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f9bf85",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00f9bf87",
      "instruction": "MOV EAX,dword ptr [EDX + 0x50]"
    },
    {
      "address": "00f9bf8a",
      "instruction": "PUSH 0x21"
    },
    {
      "address": "00f9bf8c",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f9bf8e",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f9bf90",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00f9bf92",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00f9bf94",
      "instruction": "PUSH 0x301"
    },
    {
      "address": "00f9bf99",
      "instruction": "CALL 0x00777ae0"
    },
    {
      "address": "00f9bf9e",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00f9bfa0",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00f9bfa2",
      "instruction": "PUSH 0x304"
    },
    {
      "address": "00f
[TRUNCATED]
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
  "original_bytes": 11617,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00f9bf4e\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9bf25\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067ddd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9bf99\",\n        \"direction\": \"out\",\n        \"other\": \"0x00777ae0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9bfa7\",\n        \"direction\": \"out\",\n        \"other\": \"0x00777ae0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9bfb5\",\n        \"direction\": \"out\",\n        \"other\": \"0x00777ae0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9bfc3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00777ae0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9bfd1\",\n        \"direction\": \"out\",\n        \"other\": \"0x00777ae0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9bfdf\",\n        \"direction\": \"out\",\n        \"other\": \"0x00777ae0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9bff0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00777ae0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9bffe\",\n        \"direction\": \"out\",\n        \"other\": \"0x00777ae0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9bf10\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f96c60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f9bf20\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f998f0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0574\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:WARN\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00f9bee0\",\n  \"normalized_symbol\": \"FUN_00f9bee0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n
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
  "body_end": "00f9c00b",
  "body_span_bytes": 300,
  "body_start": "00f9bee0",
  "callees": [
    "FUN_0067ddd0",
    "Graphics::IShadowWorld::Get",
    "FUN_00777ae0",
    "FUN_00f998f0",
    "FUN_00f96c60"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00f9bee0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00f9bee0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xb9bee0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00f9bee0(void)",
  "size_bytes": 300,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00f9bee0",
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
      "from": "01490c78"
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
  "global:WARN"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00f9bee0/sw2_00f9bee0.cpp",
    "reconstruction/staging/pkg-swarm-w2-00f9bee0/sw2_00f9bee0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00f9bee0/sw2_00f9bee0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00f9bee0/00f9bee0.json"
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
