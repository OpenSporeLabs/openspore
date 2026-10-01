# Evidence 0x0045b210

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `3b9afbd14b59fcdc538610172d644018854d2c19629dd7ee1f0fefb77e7048fc`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32 (x86:LE:32:windows, image base 0x00400000)",
  "calling_convention": "__thiscall",
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_note": "used by every observed caller as a pointer-like value",
  "return_observation": "0x0045b27a MOV EDX,dword ptr [ECX+4] loads a full dword from the matched node and 0x0045b280 MOV EAX,dword ptr [EBP-0x5c] copies all 32 bits. 0x0045b26d XOR EAX,EAX zeroes all 32 bits on the miss path.",
  "return_register": "EAX",
  "return_semantics": "The mapped 32-bit value of the id when the id has an entry, and the literal 0 when it does not. The mapped value is an object pointer in every sampled use: callers load its vtable and dispatch through it.",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP",
    "EBX is used as a scratch by the callee-prologue spill sequence only"
  ],
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x8",
      "name": "id",
      "observed_values": [
        "0xb8deeb8b (literal, 0x0058bf39)",
        "0xabf6fbdd (literal, 0x0043f951)",
        "dword from [ESI+0x27c] (0x0058bf6a)",
        "dword from [EBP+0x278] (0x005872dc)",
        "dword from [EBP+0x27c] (0x005877cb)"
      ],
      "read_evidence": "0x0045b219 LEA EAX,[EBP + 0x8] followed by 0x0045b21c PUSH EAX -- the argument is read INDIRECTLY, by passing its address to 0x00421950, not by a direct load. The callee dereferences it at 0x0042195c MOV ECX,dword ptr [EAX].",
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "single exit at 0x0045b286"
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
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "2fd7603da214a15d356a7dc4c456801061448184d35f013ef8978c98556fbaa4",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0036"
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
        "obs-0032"
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
        "obs-0032"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0036"
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
        "obs-0036"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0036"
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
      "at": "0x0045b210",
      "count": 24,
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
      "at": "0x0045b210",
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
      "sub": 96
    },
    {
      "at": "0x0045b211",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x0045b211",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x0045b213",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x60",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0045b216",
      "count": 9,
      "first_use": 3,
      "first_write_index": 8,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0x60],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0045b216",
      "base": "EBP",
      "disp": -96,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x60],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {

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
    "va": "0x0045afc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0045b000"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0045b040"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0045b110"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005744b0"
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
    "va": "0x0062f2f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062f920"
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
  "count": 45,
  "instructions": [
    {
      "address": "0045b210",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0045b211",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0045b213",
      "instruction": "SUB ESP,0x60"
    },
    {
      "address": "0045b216",
      "instruction": "MOV dword ptr [EBP + -0x60],ECX"
    },
    {
      "address": "0045b219",
      "instruction": "LEA EAX,[EBP + 0x8]"
    },
    {
      "address": "0045b21c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0045b21d",
      "instruction": "LEA ECX,[EBP + -0x8]"
    },
    {
      "address": "0045b220",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0045b221",
      "instruction": "MOV ECX,dword ptr [EBP + -0x60]"
    },
    {
      "address": "0045b224",
      "instruction": "ADD ECX,0x8"
    },
    {
      "address": "0045b227",
      "instruction": "CALL 0x00421950"
    },
    {
      "address": "0045b22c",
      "instruction": "MOV EDX,dword ptr [EBP + -0x60]"
    },
    {
      "address": "0045b22f",
      "instruction": "ADD EDX,0x8"
    },
    {
      "address": "0045b232",
      "instruction": "MOV dword ptr [EBP + -0x54],EDX"
    },
    {
      "address": "0045b235",
      "instruction": "MOV EAX,dword ptr [EBP + -0x54]"
    },
    {
      "address": "0045b238",
      "instruction": "MOV ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "0045b23b",
      "instruction": "MOV EDX,dword ptr [EBP + -0x54]"
    },
    {
      "address": "0045b23e",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "0045b241",
      "instruction": "LEA ECX,[EAX + ECX*0x4]"
    },
    {
      "address": "0045b244",
      "instruction": "MOV dword ptr [EBP + -0x50],ECX"
    },
    {
      "address": "0045b247",
      "instruction": "MOV EDX,dword ptr [EBP + -0x50]"
    },
    {
      "address": "0045b24a",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "0045b24c",
      "instruction": "MOV dword ptr [EBP + -0x4c],EAX"
    },
    {
      "address": "0045b24f",
      "instruction": "MOV ECX,dword ptr [EBP + -0x4c]"
    },
    {
      "address": "0045b252",
      "instruction": "MOV dword ptr [EBP + -0x10],ECX"
    },
    {
      "address": "0045b255",
      "instruction": "MOV EDX,dword ptr [EBP + -0x50]"
    },
    {
      "address": "0045b258",
      "instruction": "MOV dword ptr [EBP + -0xc],EDX"
    },
    {
      "address": "0045b25b",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0045b25e",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "0045b260",
      "instruction": "CMP EAX,dword ptr [EBP + -0x10]"
    },
    {
      "address": "0045b263",
      "instruction": "SETZ CL"
    },
    {
      "address": "0045b266",
      "instruction": "MOVZX EDX,CL"
    },
    {
      "address": "0045b269",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "0045b26b",
      "instruction": "JZ 0x0045b271"
    },
    {
      "address": "0045b26d",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "0045b26f",
      "instruction": "JMP 0x0045b283"
    },
    {
      "address": "0045b271",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0045b274",
      "instruction": "MOV dword ptr [EBP + -0x58],EAX"
    },
    {
      "address": "0045b277",
      "instruction": "MOV ECX,dword ptr [EBP + -0x58]"
    },
    {
      "address": "0045b27a",
      "instruction": "MOV EDX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "0045b27d",
      "instruction": "MOV dword ptr [EBP + -0x5c],EDX"
    },
    {
      "address": "0045b280",
      "instruction": "MOV EAX,dword ptr [EBP + -0x5c]"
    },
    {
      "address": "0045b283",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0045b285",
      "instruction": "POP EBP"
    },
    {
      "address": "0045b286",
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
  "original_bytes": 12624,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32 (x86:LE:32:windows, image base 0x00400000)\",\n    \"calling_convention\": \"__thiscall\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_note\": \"used by every observed caller as a pointer-like value\",\n    \"return_observation\": \"0x0045b27a MOV EDX,dword ptr [ECX+4] loads a full dword from the matched node and 0x0045b280 MOV EAX,dword ptr [EBP-0x5c] copies all 32 bits. 0x0045b26d XOR EAX,EAX zeroes all 32 bits on the miss path.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"The mapped 32-bit value of the id when the id has an entry, and the literal 0 when it does not. The mapped value is an object pointer in every sampled use: callers load its vtable and dispatch through it.\",\n    \"return_type\": \"std::uint32_t\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX is used as a scratch by the callee-prologue spill sequence only\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"EBP+0x8\",\n        \"name\": \"id\",\n        \"observed_values\": [\n          \"0xb8deeb8b (literal, 0x0058bf39)\",\n          \"0xabf6fbdd (literal, 0x0043f951)\",\n          \"dword from [ESI+0x27c] (0x0058bf6a)\",\n          \"dword from [EBP+0x278] (0x005872dc)\",\n          \"dword from [EBP+0x27c] (0x005877cb)\"\n        ],\n        \"read_evidence\": \"0x0045b219 LEA EAX,[EBP + 0x8] followed by 0x0045b21c PUSH EAX -- the argument is read INDIRECTLY, by passing its address to 0x00421950, not by a direct load. The callee dereferences it at 0x0042195c MOV ECX,dword ptr [EAX].\",\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"single exit at 0x0045b286\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043f6b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0045afc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0045b000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0045b040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0045b110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005744b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00575f70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"name\": \"Editors::cEditor::Update\",\n        \"reconstructed\": false,\n        \"va\": \"0x0058be50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062f2f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062f920\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0043f7ff\",\n        \"direction\": \"in\",\n        \"other\": \"0x0043f6b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0043fa22\",\n        \"direction\": \"in\",\n        \"other\": \"0x0043f6b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0043fa39\",\n   
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
  "body_end": "0045b288",
  "body_span_bytes": 121,
  "body_start": "0045b210",
  "callees": [
    "FUN_00421950"
  ],
  "callers": [
    "FUN_0045b110",
    "FUN_0062f2f0",
    "FUN_0062f920",
    "FUN_00575f70",
    "Editors::cEditor::SetActiveMode",
    "FUN_005744b0",
    "FUN_0045b040",
    "FUN_0045afc0",
    "FUN_0043f6b0",
    "Editors::cEditor::Update",
    "FUN_0045b000"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0045b210",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
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
      "name": "local_50",
      "storage": "Stack[-0x50]:4",
      "type": "undefined4"
    },
    {
      "name": "local_54",
      "storage": "Stack[-0x54]:4",
      "type": "undefined4"
    },
    {
      "name": "local_58",
      "storage": "Stack[-0x58]:4",
      "type": "undefined4"
    },
    {
      "name": "local_5c",
      "storage": "Stack[-0x5c]:4",
      "type": "undefined4"
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
    }
  ],
  "locals_count": 9,
  "mode": "live",
  "name": "FUN_0045b210",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x5b210",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0045b210(void)",
  "size_bytes": 121,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0045b210",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 26,
  "xrefs": [
    {
      "from": "0043f7ff"
    },
    {
      "from": "0043fa22"
    },
    {
      "from": "0043fa39"
    },
    {
      "from": "0045b050"
    },
    {
      "from": "0045afd0"
    },
    {
      "from": "0045b010"
    },
    {
      "from": "0045b120"
    },
    {
      "from": "0057600f"
    },
    {
      "from": "00576039"
    },
    {
      "from": "005760b2"
    },
    {
      "from": "005760dc"
    },
    {
      "from": "005872e4"
    },
    {
      "from": "005877d3"
    },
    {
      "from": "005744f5"
    },
    {
      "from": "00574537"
    },
    {
      "from": "0062f948"
    },
    {
      "from": "0062f96c"
    },
    {
      "from": "0062f980"
    },
    {
      "from": "0062f304"
    },
    {
      "from": "0062f31c"
    },
    {
      "from": "0058bf45"
    },
    {
      "from": "0058bf72"
    },
    {
      "from": "0058c3da"
    },
    {
      "from": "0058c3ef"
    },
    {
      "from": "005b3cc6"
    },
    {
      "from": "005b3dcb"
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
    "reconstruction/staging/wave13-w1-dispatch-b01/0045b210_lookup.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/0045b210_lookup.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b01/0045b210.json"
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
    "A runtime pass would need to record the bucket count and the resolved object pointer for a handful of the hardcoded ids to confirm the id-to-class mapping.",
    "No original-process trace exists, so the claim that the global at 0x015d0c14 is populated and that lookups succeed is static only.",
    "The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made."
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
  "std::uint32_t",
  "std::uint32_t, used by every observed caller as a pointer-like value"
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
