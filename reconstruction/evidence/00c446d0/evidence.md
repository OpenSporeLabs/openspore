# Evidence 0x00c446d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2c0274480a7857eb208216a152012b1ef8b66ce9526532ed01a2eb1d684b976e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "read; ADD ECX,0xF0 then [ECX+0x00], [ECX+0x04] and [ECX+0x08] are the container's three cursors. A null receiver faults at 0x00c446f0's ADD is harmless but the first dereference at 0x00c4470f or 0x00c44721 is not.",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8 (at 0x00c4471e, 0x00c44749 and 0x00c44759)",
  "return_observation": "all three exits are RET 0x8 with no value contract; the two callees' returns are discarded at 0x00c4471b and 0x00c44756, and 0x00c43f20's iterator result is dropped even though the callee computes one.",
  "return_register": "none - EAX is used for the argument pointer, the grow-path position and the callee's discarded return; no exit value is consumed",
  "return_semantics": "none; the only effect is the growth of the vector member at receiver+0xF0 and the write of one 16-byte element into it",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    {
      "instruction": "0x00c446d3: MOV EAX,dword ptr [ESP + 0x14]",
      "offset": "ESP+0x4 at entry (read as [ESP+0x14] after the SUB)",
      "role": "pointer to three consecutive floats, the position to record",
      "width_bytes": 4
    },
    {
      "instruction": "0x00c446e5: MOV AL,byte ptr [ESP + 0x18]",
      "offset": "ESP+0x8 at entry (read as [ESP+0x18] after the SUB)",
      "role": "direction and stored tag: non-zero selects prepend and is normalised to the tag value 1",
      "width_bytes": 1
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "three exits, all RET 0x8; there is no shared epilogue"
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
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x8",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -16, so the listing is not one path",
    "slot_width_ambiguous: one entry slot is read at more than one width",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "73994686343f0918c03a8dd300b6576ea7f6aa4c1cb04f6f34f74b981e632432",
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
        "obs-0024",
        "obs-0027",
        "obs-0030"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0010",
        "obs-0028"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0010",
        "obs-0028"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0021"
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
        "obs-0013",
        "obs-0021"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0004"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00c446d0",
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
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00c446d0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c446d3",
      "count": 8,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x14]",
      "reg": "ESP"
    },
    {
      "at": "0x00c446d3",
      "base": "ESP",
      "disp": 20,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x14]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00c446d3",
      "defini
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
    "va": "0x00b34380"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b452f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0eec0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c13650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c13a30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c18370"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c18740"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c18b40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c190e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c1a3c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c1b020"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c20230"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c2a190"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f235e0"
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
  "count": 44,
  "instructions": [
    {
      "address": "00c446d0",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "00c446d3",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00c446d7",
      "instruction": "MOVSS XMM0,dword ptr [EAX]"
    },
    {
      "address": "00c446db",
      "instruction": "MOVSS XMM1,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00c446e0",
      "instruction": "MOVSS XMM2,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00c446e5",
      "instruction": "MOV AL,byte ptr [ESP + 0x18]"
    },
    {
      "address": "00c446e9",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00c446eb",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c446ed",
      "instruction": "SETNZ DL"
    },
    {
      "address": "00c446f0",
      "instruction": "ADD ECX,0xf0"
    },
    {
      "address": "00c446f6",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00c446fb",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM1"
    },
    {
      "address": "00c44701",
      "instruction": "MOVSS dword ptr [ESP + 0x8],XMM2"
    },
    {
      "address": "00c44707",
      "instruction": "MOV dword ptr [ESP + 0xc],EDX"
    },
    {
      "address": "00c4470b",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c4470d",
      "instruction": "JZ 0x00c44721"
    },
    {
      "address": "00c4470f",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00c44711",
      "instruction": "LEA EAX,[ESP]"
    },
    {
      "address": "00c44714",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c44715",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c44716",
      "instruction": "CALL 0x00c43f20"
    },
    {
      "address": "00c4471b",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00c4471e",
      "instruction": "RET 0x8"
    },
    {
      "address": "00c44721",
      "instruction": "MOV EAX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "00c44724",
      "instruction": "CMP EAX,dword ptr [ECX + 0x8]"
    },
    {
      "address": "00c44727",
      "instruction": "JNC 0x00c4474c"
    },
    {
      "address": "00c44729",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c4472a",
      "instruction": "LEA ESI,[EAX + 0x10]"
    },
    {
      "address": "00c4472d",
      "instruction": "MOV dword ptr [ECX + 0x4],ESI"
    },
    {
      "address": "00c44730",
      "instruction": "POP ESI"
    },
    {
      "address": "00c44731",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c44733",
      "instruction": "JZ 0x00c44756"
    },
    {
      "address": "00c44735",
      "instruction": "MOVSS dword ptr [EAX],XMM0"
    },
    {
      "address": "00c44739",
      "instruction": "MOVSS dword ptr [EAX + 0x4],XMM1"
    },
    {
      "address": "00c4473e",
      "instruction": "MOVSS dword ptr [EAX + 0x8],XMM2"
    },
    {
      "address": "00c44743",
      "instruction": "MOV dword ptr [EAX + 0xc],EDX"
    },
    {
      "address": "00c44746",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00c44749",
      "instruction": "RET 0x8"
    },
    {
      "address": "00c4474c",
      "instruction": "LEA EDX,[ESP]"
    },
    {
      "address": "00c4474f",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c44750",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c44751",
      "instruction": "CALL 0x00c43cc0"
    },
    {
      "address": "00c44756",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00c44759",
      "instruction": "RET 0x8"
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
  "original_bytes": 12992,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"read; ADD ECX,0xF0 then [ECX+0x00], [ECX+0x04] and [ECX+0x08] are the container's three cursors. A null receiver faults at 0x00c446f0's ADD is harmless but the first dereference at 0x00c4470f or 0x00c44721 is not.\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x8 (at 0x00c4471e, 0x00c44749 and 0x00c44759)\",\n    \"return_observation\": \"all three exits are RET 0x8 with no value contract; the two callees' returns are discarded at 0x00c4471b and 0x00c44756, and 0x00c43f20's iterator result is dropped even though the callee computes one.\",\n    \"return_register\": \"none - EAX is used for the argument pointer, the grow-path position and the callee's discarded return; no exit value is consumed\",\n    \"return_semantics\": \"none; the only effect is the growth of the vector member at receiver+0xF0 and the write of one 16-byte element into it\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"instruction\": \"0x00c446d3: MOV EAX,dword ptr [ESP + 0x14]\",\n        \"offset\": \"ESP+0x4 at entry (read as [ESP+0x14] after the SUB)\",\n        \"role\": \"pointer to three consecutive floats, the position to record\",\n        \"width_bytes\": 4\n      },\n      {\n        \"instruction\": \"0x00c446e5: MOV AL,byte ptr [ESP + 0x18]\",\n        \"offset\": \"ESP+0x8 at entry (read as [ESP+0x18] after the SUB)\",\n        \"role\": \"direction and stored tag: non-zero selects prepend and is normalised to the tag value 1\",\n        \"width_bytes\": 1\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"three exits, all RET 0x8; there is no shared epilogue\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b34380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b452f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0eec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c13650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c13a30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c18370\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c18740\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c18b40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c190e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c1a3c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c1b020\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c20230\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c2a190\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f235e0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\"
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
  "body_end": "00c4475b",
  "body_span_bytes": 140,
  "body_start": "00c446d0",
  "callees": [
    "FUN_00c43f20",
    "FUN_00c43cc0"
  ],
  "callers": [
    "FUN_00b452f0",
    "FUN_00f235e0",
    "FUN_00c13650",
    "FUN_00c190e0",
    "FUN_00c0eec0",
    "FUN_00c1b020",
    "FUN_00c2a190",
    "FUN_00c20230",
    "FUN_00c1a3c0",
    "FUN_00c13a30",
    "FUN_00c18370",
    "FUN_00c18740",
    "FUN_00b34380",
    "FUN_00c18b40"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c446d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
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
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00c446d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8446d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c446d0(void)",
  "size_bytes": 140,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c446d0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 16,
  "xrefs": [
    {
      "from": "00b345dc"
    },
    {
      "from": "00b45341"
    },
    {
      "from": "00c1a9e6"
    },
    {
      "from": "00c13937"
    },
    {
      "from": "00c13bef"
    },
    {
      "from": "00c18674"
    },
    {
      "from": "00c18ae5"
    },
    {
      "from": "00c195be"
    },
    {
      "from": "00c0f21e"
    },
    {
      "from": "00c20719"
    },
    {
      "from": "00f237fe"
    },
    {
      "from": "00c1b655"
    },
    {
      "from": "00c18f8d"
    },
    {
      "from": "00c1ea76"
    },
    {
      "from": "00c1ede7"
    },
    {
      "from": "00c2a699"
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
    "reconstruction/staging/wave13-w1-core-b06/c446d0_tagged_vector3_push.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b06/00c446d0.json"
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
    "Confirming that the growth policy is reached with capacity exactly 1 on the first append requires a runtime allocation trace, since the arithmetic is only reached through the callee.",
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
    "The container is empty in the shipping image and the owning subsystem was never started in any recorded run, so the grow path, the prepend path and the inlined append path have all never been observed executing.",
    "The null-cursor behaviour can only be exercised by a container whose insert cursor is null while its end cursor is not, i.e. a corrupt or deliberately initialised state. A runtime test must construct that state deliberately to confirm the original leaves the advanced cursor behind.",
    "The tag dword's meaning requires observing how the list is consumed after insertions from both ends. A differential trace that records the list contents after a prepend-then-append sequence would settle it; nothing static can."
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
