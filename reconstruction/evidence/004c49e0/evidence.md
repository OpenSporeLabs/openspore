# Evidence 0x004c49e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b46bf621a9e87649967bcea8c7f381e4ce91a4d84c8672a825f2e6044ba5ad19`

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
  "return_note": "(32-bit pointer-like dword)",
  "return_observation": "0x004c4a00 MOV EDX,dword ptr [ECX+0x18] and 0x004c4a10 MOV ECX,dword ptr [EAX+0x1c] are dword loads, and 0x004c4a06 / 0x004c4a16 copy the full 32 bits into EAX. 0x004c4a1b XOR EAX,EAX zeroes all 32 bits, so the default is a dword 0 and not a byte 0.",
  "return_register": "EAX",
  "return_semantics": "Either the dword stored at receiver+0x18, the dword stored at receiver+0x1c, or the literal 0, chosen by the index argument. Every observed consumer branches on the result being null and then dereferences it, so the value is an object pointer.",
  "return_type": "void*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x8",
      "name": "index",
      "observed_values": [
        "0x0 at 0x005ab6ff and 0x005ab710",
        "0x1 at seventeen inspected and reported sites including 0x0058757a, 0x0058bfeb, 0x005930b9, 0x00583126"
      ],
      "read_evidence": "0x004c49e9: MOV EAX,dword ptr [EBP + 0x8]",
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "single exit at 0x004c4a20"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "777155126a0daa37895bc238b1ebae931e2b28ce6e17b678bb10ebcdfb15fb9f",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0024"
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
      "confidence": "INFERRED",
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
        "obs-0014",
        "obs-0015",
        "obs-0016",
        "obs-0021"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          28
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0014",
        "obs-0015",
        "obs-0016",
        "obs-0021",
        "obs-0024"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0024"
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
        "obs-0024"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0024"
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
      "at": "0x004c49e0",
      "count": 13,
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
      "at": "0x004c49e0",
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
      "sub": 16
    },
    {
      "at": "0x004c49e1",
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
      "at": "0x004c49e1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004c49e3",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x004c49e6",
      "count": 3,
      "first_use": 3,
      "first_write_index": 11,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0xc],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x004c49e6",
      "base": "EBP",
      "disp": -12,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0xc],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x004c49e9",
      "base": "EBP",
      "disp": 8,
      "id": "obs-0008",
      "index": 4,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + 0x8]",
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
    "va": "0x00574a20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00577620"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00577dd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057af00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057c590"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057e220"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057e480"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057f6c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00582fe0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00585330"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00587270"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0058a350"
  },
  {
    "name": "Editors::cEditor::Update",
    "reconstructed": false,
    "va": "0x0058be50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0058d1c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00591690"
  },
  {
    "name": "Editors::cEditor::HandleMessage",
    "reconstructed": false,
    "va": "0x00591fa0"
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
  "count": 25,
  "instructions": [
    {
      "address": "004c49e0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004c49e1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004c49e3",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "004c49e6",
      "instruction": "MOV dword ptr [EBP + -0xc],ECX"
    },
    {
      "address": "004c49e9",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004c49ec",
      "instruction": "MOV dword ptr [EBP + -0x10],EAX"
    },
    {
      "address": "004c49ef",
      "instruction": "CMP dword ptr [EBP + -0x10],0x0"
    },
    {
      "address": "004c49f3",
      "instruction": "JZ 0x004c49fd"
    },
    {
      "address": "004c49f5",
      "instruction": "CMP dword ptr [EBP + -0x10],0x1"
    },
    {
      "address": "004c49f9",
      "instruction": "JZ 0x004c4a0d"
    },
    {
      "address": "004c49fb",
      "instruction": "JMP 0x004c4a1b"
    },
    {
      "address": "004c49fd",
      "instruction": "MOV ECX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "004c4a00",
      "instruction": "MOV EDX,dword ptr [ECX + 0x18]"
    },
    {
      "address": "004c4a03",
      "instruction": "MOV dword ptr [EBP + -0x4],EDX"
    },
    {
      "address": "004c4a06",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004c4a09",
      "instruction": "JMP 0x004c4a1d"
    },
    {
      "address": "004c4a0d",
      "instruction": "MOV EAX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "004c4a10",
      "instruction": "MOV ECX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "004c4a13",
      "instruction": "MOV dword ptr [EBP + -0x8],ECX"
    },
    {
      "address": "004c4a16",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "004c4a19",
      "instruction": "JMP 0x004c4a1d"
    },
    {
      "address": "004c4a1b",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "004c4a1d",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004c4a1f",
      "instruction": "POP EBP"
    },
    {
      "address": "004c4a20",
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
  "original_bytes": 13616,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32 (x86:LE:32:windows, image base 0x00400000)\",\n    \"calling_convention\": \"__thiscall\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_note\": \"(32-bit pointer-like dword)\",\n    \"return_observation\": \"0x004c4a00 MOV EDX,dword ptr [ECX+0x18] and 0x004c4a10 MOV ECX,dword ptr [EAX+0x1c] are dword loads, and 0x004c4a06 / 0x004c4a16 copy the full 32 bits into EAX. 0x004c4a1b XOR EAX,EAX zeroes all 32 bits, so the default is a dword 0 and not a byte 0.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"Either the dword stored at receiver+0x18, the dword stored at receiver+0x1c, or the literal 0, chosen by the index argument. Every observed consumer branches on the result being null and then dereferences it, so the value is an object pointer.\",\n    \"return_type\": \"void*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"EBP+0x8\",\n        \"name\": \"index\",\n        \"observed_values\": [\n          \"0x0 at 0x005ab6ff and 0x005ab710\",\n          \"0x1 at seventeen inspected and reported sites including 0x0058757a, 0x0058bfeb, 0x005930b9, 0x00583126\"\n        ],\n        \"read_evidence\": \"0x004c49e9: MOV EAX,dword ptr [EBP + 0x8]\",\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"single exit at 0x004c4a20\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00574a20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00577620\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00577dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057af00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057c590\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057e220\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057e480\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057f6c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00582fe0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00585330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0058a350\"\n      },\n      {\n        \"name\": \"Editors::cEditor::Update\",\n        \"reconstructed\": false,\n        \"va\": \"0x0058be50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0058d1c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00591690\"\n      },\n      {\n        \"name\": \"Editors::cEditor::HandleMessage\",\n        \"reconstructed\": false,\n        \"va\": \"0x00591fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005aa7a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\"
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
  "body_end": "004c4a22",
  "body_span_bytes": 67,
  "body_start": "004c49e0",
  "callees": [],
  "callers": [
    "FUN_005aa9c0",
    "FUN_0057f6c0",
    "FUN_0058d1c0",
    "FUN_005aa7a0",
    "FUN_0058a350",
    "FUN_0057e220",
    "FUN_0057c590",
    "FUN_0057e480",
    "FUN_00577dd0",
    "FUN_00577620",
    "Editors::cEditor::SetActiveMode",
    "FUN_0057af00",
    "FUN_00574a20",
    "FUN_005ab5c0",
    "Editors::cEditor::Update",
    "FUN_00591690",
    "FUN_00585330",
    "Editors::cEditor::HandleMessage",
    "Editors::cEditor::AddCreature"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "004c49e0",
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
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_004c49e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc49e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004c49e0(void)",
  "size_bytes": 67,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004c49e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 33,
  "xrefs": [
    {
      "from": "00577de8"
    },
    {
      "from": "0058757c"
    },
    {
      "from": "005875df"
    },
    {
      "from": "00587638"
    },
    {
      "from": "00587730"
    },
    {
      "from": "00587884"
    },
    {
      "from": "00587967"
    },
    {
      "from": "0058312a"
    },
    {
      "from": "0057e248"
    },
    {
      "from": "0057b75d"
    },
    {
      "from": "0058d2a4"
    },
    {
      "from": "005aa7af"
    },
    {
      "from": "005ab701"
    },
    {
      "from": "005ab712"
    },
    {
      "from": "0057c5c8"
    },
    {
      "from": "0057c70b"
    },
    {
      "from": "00574a3c"
    },
    {
      "from": "0057fdfb"
    },
    {
      "from": "0057ffb1"
    },
    {
      "from": "0058006d"
    },
    {
      "from": "00580093"
    },
    {
      "from": "0058a4b6"
    },
    {
      "from": "0058bfed"
    },
    {
      "from": "0058c57c"
    },
    {
      "from": "0058c596"
    },
    {
      "from": "0058c7aa"
    },
    {
      "from": "0057e4af"
    },
    {
      "from": "00577635"
    },
    {
      "from": "00585457"
    },
    {
      "from": "005930bb"
    },
    {
      "from": "00591a12"
    },
    {
      "from": "005aaa0a"
    },
    {
      "from": "005aa5be"
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
    "reconstruction/staging/wave13-w1-dispatch-b01/004c49e0_pick.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/004c49e0_pick.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b01/004c49e0.json"
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
    "A runtime differential test would have to record the two slot values at a few of the call sites to confirm which objects are returned in practice.",
    "No original-process trace exists for this function, so the claim that both arms return live object pointers is static only.",
    "The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made for this Editor-subsystem function."
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
  "void* (32-bit pointer-like dword)"
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
