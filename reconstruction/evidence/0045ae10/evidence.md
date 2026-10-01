# Evidence 0x0045ae10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `eb0a845a31fed89921d3b0005cd60c6b081ed2281962c36fa09e3a909c9f1ea9`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX, spilled to [EBP-0x6c] at 0x0045ae16 and reloaded at 0x0045ae2c",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "no MOV to EAX appears in the 17 instructions; the epilogue is MOV ESP,EBP / POP EBP / RET 0x8",
  "return_register": "none (EAX is clobbered by the two callees and never written by this body)",
  "return_semantics": "no value; the only result of the call is the side effect inside 0x0045ac20",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_arguments": [
    {
      "offset_in_callee": "[EBP + 0x8]",
      "read_by": "0x0045ae28: MOV ECX,dword ptr [EBP + 0x8]",
      "role": "becomes the second stack argument of 0x0045ac20",
      "slot": 1,
      "width_bytes": 4
    },
    {
      "offset_in_callee": "[EBP + 0xc]",
      "read_by": "0x0045ae24: MOV EAX,dword ptr [EBP + 0xc]",
      "role": "becomes the third stack argument of 0x0045ac20",
      "slot": 2,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x8"
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
        "ebp_offset": "EBP+0x8",
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
        "ebp_offset": "EBP+0xc",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x8",
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "ebp_offset": "EBP+0xc",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
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
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "5c73023d858ea7780296e9fa5747924a6ac2373b6ad450b5a17589b1423b8d94",
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
        "obs-0018"
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
        "obs-0011",
        "obs-0013"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0013",
        "obs-0014",
        "obs-0015"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0013",
        "obs-0014",
        "obs-0015"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0018"
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
        "obs-0018"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018"
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
      "at": "0x0045ae10",
      "count": 7,
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
      "at": "0x0045ae10",
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
      "sub": 108
    },
    {
      "at": "0x0045ae11",
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
      "at": "0x0045ae11",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x0045ae13",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x6c",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0045ae16",
      "count": 3,
      "first_use": 3,
      "first_write_index": 10,
      "id": "obs-0006",
      "
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
    "va": "0x00573f20"
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
    "va": "0x00585d40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00587270"
  },
  {
    "name": "editor_input_00588570",
    "reconstructed": true,
    "va": "0x00588570"
  },
  {
    "name": "Editors::cEditor::HandleMessage",
    "reconstructed": false,
    "va": "0x00591fa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005dec10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062f5c0"
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
    "va": "0x0063ef70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0064c0d0"
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
  "count": 17,
  "instructions": [
    {
      "address": "0045ae10",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0045ae11",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0045ae13",
      "instruction": "SUB ESP,0x6c"
    },
    {
      "address": "0045ae16",
      "instruction": "MOV dword ptr [EBP + -0x6c],ECX"
    },
    {
      "address": "0045ae19",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0045ae1b",
      "instruction": "LEA ECX,[EBP + -0x38]"
    },
    {
      "address": "0045ae1e",
      "instruction": "CALL 0x00434040"
    },
    {
      "address": "0045ae23",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0045ae24",
      "instruction": "MOV EAX,dword ptr [EBP + 0xc]"
    },
    {
      "address": "0045ae27",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0045ae28",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0045ae2b",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0045ae2c",
      "instruction": "MOV ECX,dword ptr [EBP + -0x6c]"
    },
    {
      "address": "0045ae2f",
      "instruction": "CALL 0x0045ac20"
    },
    {
      "address": "0045ae34",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0045ae36",
      "instruction": "POP EBP"
    },
    {
      "address": "0045ae37",
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
  "original_bytes": 11372,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX, spilled to [EBP-0x6c] at 0x0045ae16 and reloaded at 0x0045ae2c\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x8\",\n    \"return_observation\": \"no MOV to EAX appears in the 17 instructions; the epilogue is MOV ESP,EBP / POP EBP / RET 0x8\",\n    \"return_register\": \"none (EAX is clobbered by the two callees and never written by this body)\",\n    \"return_semantics\": \"no value; the only result of the call is the side effect inside 0x0045ac20\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [],\n    \"stack_arguments\": [\n      {\n        \"offset_in_callee\": \"[EBP + 0x8]\",\n        \"read_by\": \"0x0045ae28: MOV ECX,dword ptr [EBP + 0x8]\",\n        \"role\": \"becomes the second stack argument of 0x0045ac20\",\n        \"slot\": 1,\n        \"width_bytes\": 4\n      },\n      {\n        \"offset_in_callee\": \"[EBP + 0xc]\",\n        \"read_by\": \"0x0045ae24: MOV EAX,dword ptr [EBP + 0xc]\",\n        \"role\": \"becomes the third stack argument of 0x0045ac20\",\n        \"slot\": 2,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573f20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005744b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00575f70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00585d40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"name\": \"editor_input_00588570\",\n        \"reconstructed\": true,\n        \"va\": \"0x00588570\"\n      },\n      {\n        \"name\": \"Editors::cEditor::HandleMessage\",\n        \"reconstructed\": false,\n        \"va\": \"0x00591fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dec10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062f5c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062f610\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062f920\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0063ef70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0064c0d0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00573f36\",\n        \"direction\": \"in\",\n        \"other\": \"0x00573f20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057450c\",\n        \"direction\": \"in\",\n        \"other\": \"0x005744b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057454e\",\n        \"direction\": \"in\",\n        \"other\": \"0x005744b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057610c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00575f70\",\n        \"reference_type\": \"direct-call\"\n    
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
  "body_end": "0045ae39",
  "body_span_bytes": 42,
  "body_start": "0045ae10",
  "callees": [
    "FUN_00434040",
    "FUN_0045ac20"
  ],
  "callers": [
    "FUN_0062f920",
    "FUN_00575f70",
    "Editors::cEditor::SetActiveMode",
    "FUN_0064c0d0",
    "FUN_0063ef70",
    "FUN_005744b0",
    "FUN_0062f610",
    "FUN_00573f20",
    "Editors::cEditor::OnMouseDown",
    "FUN_0062f5c0",
    "FUN_005dec10",
    "FUN_00585d40",
    "Editors::cEditor::HandleMessage"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0045ae10",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_3c",
      "storage": "Stack[-0x3c]:1",
      "type": "undefined"
    },
    {
      "name": "local_70",
      "storage": "Stack[-0x70]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_0045ae10",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x5ae10",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0045ae10(void)",
  "size_bytes": 42,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0045ae10",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 16,
  "xrefs": [
    {
      "from": "0057610c"
    },
    {
      "from": "00576125"
    },
    {
      "from": "00587314"
    },
    {
      "from": "00587803"
    },
    {
      "from": "0057450c"
    },
    {
      "from": "0057454e"
    },
    {
      "from": "0062f996"
    },
    {
      "from": "005863f5"
    },
    {
      "from": "0064c24e"
    },
    {
      "from": "0062f6a7"
    },
    {
      "from": "0062f5f8"
    },
    {
      "from": "0063efb1"
    },
    {
      "from": "00573f36"
    },
    {
      "from": "005ded54"
    },
    {
      "from": "005888f5"
    },
    {
      "from": "005934d5"
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
    "reconstruction/staging/wave13-w1-dispatch-b00/registry_0045ae10.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b00/registry_0045ae10.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b00/0045ae10.json"
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
    "A runtime differential test is required to (a) observe the real value of 0x015d0c14 and of 0x015d22f0/f4/f8, (b) resolve the four virtual slots, and (c) determine whether the fourth argument read by 0x0045ac20 is genuinely uninitialised in the shipping build.",
    "No original-process trace exists for 0x0045ae10; every claim is static. The Cell stage has never been entered in any recorded run.",
    "The identity of the 0x14-byte POD cannot be settled statically at all: every field it copies is zero in the image."
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
  "Opaque45ae10Registry*",
  "opaque POD, written by 0x00434040",
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
