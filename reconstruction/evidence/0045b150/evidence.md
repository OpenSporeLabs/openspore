# Evidence 0x0045b150

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f9f5dc9d4ab6d6e3be02c40680e44253837510ac258bab8312935455cd96bd76`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX, spilled to [EBP-0x78] at 0x0045b156 and reloaded at 0x0045b161 and 0x0045b1f2",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_observation": "the body ends with MOV ESP,EBP / POP EBP / RET 0x4; no MOV to EAX participates in any result.",
  "return_register": "none (EAX is scratch; the last comparison result is discarded at 0x0045b1fd)",
  "return_semantics": "no value. The only result is the removal of the matching map entry and the side effects of the value's vtable slot +0xc.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_arguments": [
    {
      "offset_in_callee": "[EBP + 0x8]",
      "read_by": "0x0045b159: LEA EAX,[EBP + 8] then 0x0045b15c: PUSH EAX -- the ADDRESS is passed, and 0x00421950 dereferences it at 0x0042199b",
      "role": "a uint32 key, passed by pointer to the hash-map lookup",
      "slot": 1,
      "width_bytes": 4
    }
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP"
    ],
    "stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "617275de70468c727230b2cf80aaa8ee1b250b782a56fb8ca7cecd638dd22f71",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0050"
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
        "obs-0009"
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
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0021",
        "obs-0024",
        "obs-0025",
        "obs-0032",
        "obs-0035",
        "obs-0038",
        "obs-0039",
        "obs-0043",
        "obs-0046",
        "obs-0047"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0021",
        "obs-0024",
        "obs-0025",
        "obs-0032",
        "obs-0035",
        "obs-0038",
        "obs-0039",
        "obs-0043",
        "obs-0046",
        "obs-0047"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0050"
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
        "obs-0050"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0050"
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
      "at": "0x0045b150",
      "count": 36,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x0045b150",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": 120
    },
    {
      "at": "0x0045b151",
      "count": 2,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x0045b151",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x0045b153",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x78",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0045b156",
      "count": 13,
      "first_use": 3,
      "first_write_index": 8,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0x78],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0045b156",
      "base": "EBP",
      "disp"
[TRUNCATED]
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
    "va": "0x0043f6b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004a6f10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00575f70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00587270"
  },
  {
    "name": "Editors::cEditor::Update",
    "reconstructed": false,
    "va": "0x0058be50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005b1e30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005dd610"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062f2f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062f610"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062f920"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ef25a0"
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
  "count": 65,
  "instructions": [
    {
      "address": "0045b150",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0045b151",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0045b153",
      "instruction": "SUB ESP,0x78"
    },
    {
      "address": "0045b156",
      "instruction": "MOV dword ptr [EBP + -0x78],ECX"
    },
    {
      "address": "0045b159",
      "instruction": "LEA EAX,[EBP + 0x8]"
    },
    {
      "address": "0045b15c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0045b15d",
      "instruction": "LEA ECX,[EBP + -0x8]"
    },
    {
      "address": "0045b160",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0045b161",
      "instruction": "MOV ECX,dword ptr [EBP + -0x78]"
    },
    {
      "address": "0045b164",
      "instruction": "ADD ECX,0x8"
    },
    {
      "address": "0045b167",
      "instruction": "CALL 0x00421950"
    },
    {
      "address": "0045b16c",
      "instruction": "MOV EDX,dword ptr [EBP + -0x78]"
    },
    {
      "address": "0045b16f",
      "instruction": "ADD EDX,0x8"
    },
    {
      "address": "0045b172",
      "instruction": "MOV dword ptr [EBP + -0x64],EDX"
    },
    {
      "address": "0045b175",
      "instruction": "MOV EAX,dword ptr [EBP + -0x64]"
    },
    {
      "address": "0045b178",
      "instruction": "MOV ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "0045b17b",
      "instruction": "MOV EDX,dword ptr [EBP + -0x64]"
    },
    {
      "address": "0045b17e",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "0045b181",
      "instruction": "LEA ECX,[EAX + ECX*0x4]"
    },
    {
      "address": "0045b184",
      "instruction": "MOV dword ptr [EBP + -0x60],ECX"
    },
    {
      "address": "0045b187",
      "instruction": "MOV EDX,dword ptr [EBP + -0x60]"
    },
    {
      "address": "0045b18a",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "0045b18c",
      "instruction": "MOV dword ptr [EBP + -0x5c],EAX"
    },
    {
      "address": "0045b18f",
      "instruction": "MOV ECX,dword ptr [EBP + -0x5c]"
    },
    {
      "address": "0045b192",
      "instruction": "MOV dword ptr [EBP + -0x14],ECX"
    },
    {
      "address": "0045b195",
      "instruction": "MOV EDX,dword ptr [EBP + -0x60]"
    },
    {
      "address": "0045b198",
      "instruction": "MOV dword ptr [EBP + -0x10],EDX"
    },
    {
      "address": "0045b19b",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0045b19e",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "0045b1a0",
      "instruction": "CMP EAX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "0045b1a3",
      "instruction": "SETNZ CL"
    },
    {
      "address": "0045b1a6",
      "instruction": "MOVZX EDX,CL"
    },
    {
      "address": "0045b1a9",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "0045b1ab",
      "instruction": "JZ 0x0045b1fd"
    },
    {
      "address": "0045b1ad",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0045b1b0",
      "instruction": "MOV dword ptr [EBP + -0x68],EAX"
    },
    {
      "address": "0045b1b3",
      "instruction": "MOV ECX,dword ptr [EBP + -0x68]"
    },
    {
      "address": "0045b1b6",
      "instruction": "MOV EDX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "0045b1b9",
      "instruction": "MOV dword ptr [EBP + -0xc],EDX"
    },
    {
      "address": "0045b1bc",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "0045b1be",
      "instruction": "MOV EAX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "0045b1c1",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "0045b1c3",
      "instruction": "MOV ECX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "0045b1c6",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "0045b1c9",
      "instruction": "CALL EAX"
    },
    {
      "address": "0045b1cb",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "0045b1ce",
      "instruction": "MOV dword ptr [EBP + -0x74],ESP"
    },
    {
      "address": "0045b1d1",
      "instruction": "MOV ECX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "0045b1d4",
      "instruction": "MOV dword ptr [EBP + -0x70],ECX"
    },
    {
      "address": "0045b1d7",
      "instruction": "MOV EDX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0045b1da",
      "instruction": "MOV dword ptr [EBP + -0x6c],EDX"
    },
    {
      "address": "0045b1dd",
      "instruction": "MOV EAX,dword ptr [EBP + -0x74]"
    },
    {
      "address": "0045b1e0",
      "instruction": "MOV ECX,dword ptr [EBP + -0x6c]"
    },
    {
      "address": "0045b1e3",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "0045b1e5",
      "instruction": "MOV EDX,dword ptr [EBP + -0x74]"
    },
    {
      "address": "0045b1e8",
      "instruction": "MOV EAX,dword ptr [EBP + -0x70]"
    },
    {
      "address": "0045b1eb",
      "instruction": "MOV dword ptr [EDX + 0x4],EAX"
    },
    {
      "address": "0045b1ee",
      "instruction": "LEA ECX,[EBP + -0x20]"
    },
    {
      "address": "0045b1f1",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0045b1f2",
      "instruction": "MOV ECX,dword ptr [EBP + -0x78]"
    },
    {
      "address": "0045b1f5",
      "instruction": "ADD ECX,0x8"
    },
    {
      "address": "0045b1f8",
      "instruction": "CALL 0x0045b3e0"
    },
    {
      "address": "0045b1fd",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0045b1ff",
      "instruction": "POP EBP"
    },
    {
      "address": "0045b200",
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
  "original_bytes": 11575,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX, spilled to [EBP-0x78] at 0x0045b156 and reloaded at 0x0045b161 and 0x0045b1f2\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x4\",\n    \"return_observation\": \"the body ends with MOV ESP,EBP / POP EBP / RET 0x4; no MOV to EAX participates in any result.\",\n    \"return_register\": \"none (EAX is scratch; the last comparison result is discarded at 0x0045b1fd)\",\n    \"return_semantics\": \"no value. The only result is the removal of the matching map entry and the side effects of the value's vtable slot +0xc.\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [],\n    \"stack_arguments\": [\n      {\n        \"offset_in_callee\": \"[EBP + 0x8]\",\n        \"read_by\": \"0x0045b159: LEA EAX,[EBP + 8] then 0x0045b15c: PUSH EAX -- the ADDRESS is passed, and 0x00421950 dereferences it at 0x0042199b\",\n        \"role\": \"a uint32 key, passed by pointer to the hash-map lookup\",\n        \"slot\": 1,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043f6b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a6f10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00575f70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"name\": \"Editors::cEditor::Update\",\n        \"reconstructed\": false,\n        \"va\": \"0x0058be50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005b1e30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dd610\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062f2f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062f610\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062f920\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ef25a0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0043f816\",\n        \"direction\": \"in\",\n        \"other\": \"0x0043f6b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0043fa50\",\n        \"direction\": \"in\",\n        \"other\": \"0x0043f6b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004a7aa9\",\n        \"direction\": \"in\",\n        \"other\": \"0x004a6f10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576026\",\n        \"direction\": \"in\",\n        \"other\": \"0x00575f70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576054\",\n        \"direction\": \"in\",\n        \"other\": \"0x00575f70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005760c9\",\n        \"direction\": \"in\",\n        \"other\": \"0x00575f70\",\n        \"reference_type\": \"direct-call\"\n   
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
  "body_end": "0045b202",
  "body_span_bytes": 179,
  "body_start": "0045b150",
  "callees": [
    "FUN_00421950",
    "FUN_0045b3e0"
  ],
  "callers": [
    "FUN_0062f2f0",
    "FUN_0062f920",
    "FUN_00575f70",
    "Editors::cEditor::SetActiveMode",
    "FUN_005dd610",
    "FUN_004a6f10",
    "FUN_0062f610",
    "FUN_00ef25a0",
    "FUN_005b1e30",
    "FUN_0043f6b0",
    "Editors::cEditor::Update"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0045b150",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:1",
      "type": "undefined"
    },
    {
      "name": "local_60",
      "storage": "Stack[-0x60]:4",
      "type": "undefined4"
    },
    {
      "name": "local_64",
      "storage": "Stack[-0x64]:4",
      "type": "undefined4"
    },
    {
      "name": "local_68",
      "storage": "Stack[-0x68]:4",
      "type": "undefined4"
    },
    {
      "name": "local_6c",
      "storage": "Stack[-0x6c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_70",
      "storage": "Stack[-0x70]:4",
      "type": "undefined4"
    },
    {
      "name": "local_74",
      "storage": "Stack[-0x74]:4",
      "type": "undefined4"
    },
    {
      "name": "local_78",
      "storage": "Stack[-0x78]:4",
      "type": "undefined4"
    },
    {
      "name": "local_7c",
      "storage": "Stack[-0x7c]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 14,
  "mode": "live",
  "name": "FUN_0045b150",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x5b150",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0045b150(void)",
  "size_bytes": 179,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0045b150",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 18,
  "xrefs": [
    {
      "from": "0043f816"
    },
    {
      "from": "0043fa50"
    },
    {
      "from": "004a7aa9"
    },
    {
      "from": "00576026"
    },
    {
      "from": "00576054"
    },
    {
      "from": "005760c9"
    },
    {
      "from": "005760f3"
    },
    {
      "from": "005872fb"
    },
    {
      "from": "005877ea"
    },
    {
      "from": "005dd726"
    },
    {
      "from": "0062f95c"
    },
    {
      "from": "005b1fbe"
    },
    {
      "from": "005b1fcf"
    },
    {
      "from": "0062f667"
    },
    {
      "from": "0062f330"
    },
    {
      "from": "00ef25c5"
    },
    {
      "from": "0058c40b"
    },
    {
      "from": "005b4326"
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
    "reconstruction/staging/wave13-w1-dispatch-b00/registry_0045b150.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b00/registry_0045b150.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b00/0045b150.json"
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
    "No original-process trace exists for 0x0045b150; every claim is static and the Cell stage has never been entered in any recorded run.",
    "The 10 uninspected callers are static work and are listed in unresolved_questions rather than as a runtime gate.",
    "The registry's runtime value and the map's own +0x0 field require a run to observe.",
    "The vtable slot +0xc callee is the highest-value runtime unknown: it is the function's only side effect, and no static evidence constrains it.",
    "Whether a live node can ever alias the free-list head, which would make a real hit silently skipped, can only be settled by instrumenting the map's insert path at runtime."
  ],
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
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "bucket array base pointer",
  "bucket count",
  "chain head pointer (nullable)",
  "element count",
  "embedded map base address",
  "free-list head pointer",
  "next-in-chain pointer",
  "payload pointer",
  "uint32 key",
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
