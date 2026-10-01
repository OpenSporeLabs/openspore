# Evidence 0x00c0ce80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ad70ad7a0275ed2bb94be05ec967c0deba7cce623c513c70e2a90bb439322e80`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX, copied to EDI at 0x00c0ce89",
  "hidden_this_register": "ECX is live until 0x00c0cea0 where MOV ECX,EDI re-establishes it for 0x00C0CE30; after 0x00c0ce89 it is never read again, and 0x00c0cee1 overwrites it with receiver+0xC0 for the virtual call.",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_register": "ST0",
  "return_semantics": "ST0 on return, consumed by FSTP. Two shapes. Gate false: the base value, unchanged. Gate true: v + 0.5f * |first_arg_reinterpreted_as_float - v|. The second shape is asymmetric: when the float operand is at or below v the result is the midpoint (v + a) / 2, but when a is above v the result is (3v - a) / 2, which overshoots.",
  "return_type": "float",
  "return_width_bytes": 4,
  "saved_registers": [
    "EDI",
    "ESI (only on the 0x00c0cf1f path)"
  ],
  "stack_arguments": [
    {
      "index": 0,
      "note": "Ghidra's `param_2 == 0.0` test and its `ABS(local_4 - param_2)` are the same single stack word read two ways. The decompiler additionally aliases the zero-initialised local at [E0-4] onto this parameter, which is wrong: 0x00c0ce8b writes 0.0f into the saved-ECX slot, not into the parameter slot. Recorded as a correction.",
      "offset_at_entry": "[ESP + 0x4]",
      "use_1": "TEST EAX,EAX at 0x00c0ce91: zero returns 0.0f immediately, with no callee invoked",
      "use_2": "FLD float ptr [ESP + 0xC] at 0x00c0cf24, reached after the POP ESI and POP EDI, so the same word is the float operand of FSUBR ST0,ST1",
      "width_bytes": 4
    },
    {
      "index": 1,
      "offset_at_entry": "[ESP + 0x8]",
      "use_1": "pushed at 0x00c0ce9e as the second argument of 0x00C0CE30, where it is tested for zero and, when zero, causes receiver+0xFA0 to be added to the index",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "three exits, all RET 0x8: 0x00c0cf36 gate true, 0x00c0cf40 gate false, 0x00c0cf49 first argument zero"
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
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
      },
      {
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
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "b6c8a4074cc003e516cf0e66fc9934f0b7a5916e91d6a30574d196079c9bdadc",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0032",
        "obs-0037",
        "obs-0041"
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
        "obs-0003",
        "obs-0010"
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
        "obs-0001",
        "obs-0008",
        "obs-0010",
        "obs-0011",
        "obs-0031",
        "obs-0036",
        "obs-0040"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          192
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0008",
        "obs-0010",
        "obs-0011",
        "obs-0031",
        "obs-0032",
        "obs-0036",
        "obs-0037",
        "obs-0040",
        "obs-0041"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0032",
        "obs-0037",
        "obs-0041"
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
        "obs-0041"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00c0ce80",
      "count": 5,
      "first_use": 0,
      "first_write_index": 8,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c0ce81",
      "count": 12,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00c0ce81",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00c0ce81",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c0ce85",
      "count": 5,
      "first_use": 2,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "XORPS XMM0,XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00c0ce85",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "XORPS XMM0,XMM0",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00c0ce88",
      "count": 5,
      "first_use": 3,
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b5b800",
    "reconstructed": false,
    "va": "0x00b5b800"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0cf50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0cfa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0cff0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0d050"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0d0c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c190e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c1aad0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c1ad10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c1b020"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c1c080"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c1c1d0"
  },
  {
    "name": "Simulator_cCreatureBase_LocomotionWalkToInterior_00c1c5c0",
    "reconstructed": true,
    "va": "0x00c1c5c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c1de20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c1f8d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c21bf0"
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
  "count": 63,
  "instructions": [
    {
      "address": "00c0ce80",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c0ce81",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c0ce85",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00c0ce88",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c0ce89",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00c0ce8b",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "00c0ce91",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c0ce93",
      "instruction": "JZ 0x00c0cf43"
    },
    {
      "address": "00c0ce99",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c0ce9d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c0ce9e",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c0ce9f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c0cea0",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c0cea2",
      "instruction": "CALL 0x00c0ce30"
    },
    {
      "address": "00c0cea7",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00c0cea9",
      "instruction": "CALL 0x00b5b800"
    },
    {
      "address": "00c0ceae",
      "instruction": "CMP EAX,0x1654c10"
    },
    {
      "address": "00c0ceb3",
      "instruction": "JNZ 0x00c0cec9"
    },
    {
      "address": "00c0ceb5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c0ceb6",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c0ceb7",
      "instruction": "CALL 0x00c03260"
    },
    {
      "address": "00c0cebc",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c0cebe",
      "instruction": "CALL 0x00f31500"
    },
    {
      "address": "00c0cec3",
      "instruction": "FSTP float ptr [ESP + 0x8]"
    },
    {
      "address": "00c0cec7",
      "instruction": "JMP 0x00c0ced8"
    },
    {
      "address": "00c0cec9",
      "instruction": "MOVSS XMM0,dword ptr [ESI*0x4 + 0x15d9650]"
    },
    {
      "address": "00c0ced2",
      "instruction": "MOVSS dword ptr [ESP + 0x8],XMM0"
    },
    {
      "address": "00c0ced8",
      "instruction": "MOV EDX,dword ptr [EDI + 0xc0]"
    },
    {
      "address": "00c0cede",
      "instruction": "MOV EAX,dword ptr [EDX + 0x58]"
    },
    {
      "address": "00c0cee1",
      "instruction": "LEA ECX,[EDI + 0xc0]"
    },
    {
      "address": "00c0cee7",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c0cee9",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c0ceeb",
      "instruction": "JZ 0x00c0cf39"
    },
    {
      "address": "00c0ceed",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c0cef3",
      "instruction": "LEA ECX,[ESI + 0x1]"
    },
    {
      "address": "00c0cef6",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM0"
    },
    {
      "address": "00c0cefc",
      "instruction": "CMP ECX,0x6"
    },
    {
      "address": "00c0ceff",
      "instruction": "JNC 0x00c0cf0c"
    },
    {
      "address": "00c0cf01",
      "instruction": "MOVSS XMM0,dword ptr [ESI*0x4 + 0x15d9654]"
    },
    {
      "address": "00c0cf0a",
      "instruction": "JMP 0x00c0cf19"
    },
    {
      "address": "00c0cf0c",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c0cf0e",
      "instruction": "JBE 0x00c0cf1f"
    },
    {
      "address": "00c0cf10",
      "instruction": "MOVSS XMM0,dword ptr [ESI*0x4 + 0x15d964c]"
    },
    {
      "address": "00c0cf19",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM0"
    },
    {
      "address": "00c0cf1f",
      "instruction": "FLD float ptr [ESP + 0x8]"
    },
    {
      "address": "00c0cf23",
      "instruction": "POP ESI"
    },
    {
      "address": "00c0cf24",
      "instruction": "FLD float ptr [ESP + 0xc]"
    },
    {
      "address": "00c0cf28",
      "instruction": "POP EDI"
    },
    {
      "address": "00c0cf29",
      "instruction": "FSUBR ST0,ST1"
    },
    {
      "address": "00c0cf2b",
      "instruction": "FABS"
    },
    {
      "address": "00c0cf2d",
      "instruction": "FMUL float ptr [0x01471064]"
    },
    {
      "address": "00c0cf33",
      "instruction": "FADDP"
    },
    {
      "address": "00c0cf35",
      "instruction": "POP ECX"
    },
    {
      "address": "00c0cf36",
      "instruction": "RET 0x8"
    },
    {
      "address": "00c0cf39",
      "instruction": "FLD float ptr [ESP + 0x8]"
    },
    {
      "address": "00c0cf3d",
      "instruction": "POP ESI"
    },
    {
      "address": "00c0cf3e",
      "instruction": "POP EDI"
    },
    {
      "address": "00c0cf3f",
      "instruction": "POP ECX"
    },
    {
      "address": "00c0cf40",
      "instruction": "RET 0x8"
    },
    {
      "address": "00c0cf43",
      "instruction": "FLD float ptr [ESP + 0x4]"
    },
    {
      "address": "00c0cf47",
      "instruction": "POP EDI"
    },
    {
      "address": "00c0cf48",
      "instruction": "POP ECX"
    },
    {
      "address": "00c0cf49",
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
  "original_bytes": 15148,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX, copied to EDI at 0x00c0ce89\",\n    \"hidden_this_register\": \"ECX is live until 0x00c0cea0 where MOV ECX,EDI re-establishes it for 0x00C0CE30; after 0x00c0ce89 it is never read again, and 0x00c0cee1 overwrites it with receiver+0xC0 for the virtual call.\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"ST0\",\n    \"return_semantics\": \"ST0 on return, consumed by FSTP. Two shapes. Gate false: the base value, unchanged. Gate true: v + 0.5f * |first_arg_reinterpreted_as_float - v|. The second shape is asymmetric: when the float operand is at or below v the result is the midpoint (v + a) / 2, but when a is above v the result is (3v - a) / 2, which overshoots.\",\n    \"return_type\": \"float\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EDI\",\n      \"ESI (only on the 0x00c0cf1f path)\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"index\": 0,\n        \"note\": \"Ghidra's `param_2 == 0.0` test and its `ABS(local_4 - param_2)` are the same single stack word read two ways. The decompiler additionally aliases the zero-initialised local at [E0-4] onto this parameter, which is wrong: 0x00c0ce8b writes 0.0f into the saved-ECX slot, not into the parameter slot. Recorded as a correction.\",\n        \"offset_at_entry\": \"[ESP + 0x4]\",\n        \"use_1\": \"TEST EAX,EAX at 0x00c0ce91: zero returns 0.0f immediately, with no callee invoked\",\n        \"use_2\": \"FLD float ptr [ESP + 0xC] at 0x00c0cf24, reached after the POP ESI and POP EDI, so the same word is the float operand of FSUBR ST0,ST1\",\n        \"width_bytes\": 4\n      },\n      {\n        \"index\": 1,\n        \"offset_at_entry\": \"[ESP + 0x8]\",\n        \"use_1\": \"pushed at 0x00c0ce9e as the second argument of 0x00C0CE30, where it is tested for zero and, when zero, causes receiver+0xFA0 to be added to the index\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"three exits, all RET 0x8: 0x00c0cf36 gate true, 0x00c0cf40 gate false, 0x00c0cf49 first argument zero\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-C4-CREATURE-WAVE3\",\n      \"score\": 3,\n      \"symbol\": \"Simulator_cCreatureBase_LocomotionWalkToInterior_00c1c5c0\",\n      \"va\": \"0x00c1c5c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b5b800\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b5b800\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0cf50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0cfa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0cff0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0d050\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0d0c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c190e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c1aad0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c1ad10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c1b020\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c1c080\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n     
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
  "body_end": "00c0cf4b",
  "body_span_bytes": 204,
  "body_start": "00c0ce80",
  "callees": [
    "FUN_00f31500",
    "FUN_00b5b800",
    "FUN_00c03260",
    "FUN_00c0ce30"
  ],
  "callers": [
    "FUN_00c0d0c0",
    "FUN_00c0d050",
    "FUN_00c190e0",
    "FUN_00c1b020",
    "FUN_00c0cfa0",
    "FUN_00c1f8d0",
    "FUN_00c0cf50",
    "FUN_00c1de20",
    "FUN_00c1c080",
    "FUN_00c1ad10",
    "FUN_00c1aad0",
    "FUN_00c21bf0",
    "FUN_00c1c1d0",
    "FUN_00c0cff0",
    "FUN_00c1c5c0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c0ce80",
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
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00c0ce80",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x80ce80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c0ce80(void)",
  "size_bytes": 204,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c0ce80",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 33,
  "xrefs": [
    {
      "from": "00c0d00a"
    },
    {
      "from": "00c0d02e"
    },
    {
      "from": "00c0d186"
    },
    {
      "from": "00c0d196"
    },
    {
      "from": "00c1c2c2"
    },
    {
      "from": "00c1c2d1"
    },
    {
      "from": "00c21ebb"
    },
    {
      "from": "00c1c87d"
    },
    {
      "from": "00c1c88c"
    },
    {
      "from": "00c0cf62"
    },
    {
      "from": "00c0cf73"
    },
    {
      "from": "00c0cf84"
    },
    {
      "from": "00c1fdae"
    },
    {
      "from": "00c1fdbf"
    },
    {
      "from": "00c1fdd0"
    },
    {
      "from": "00c1adbc"
    },
    {
      "from": "00c1adcc"
    },
    {
      "from": "00c1ae85"
    },
    {
      "from": "00c1ae95"
    },
    {
      "from": "00c1abba"
    },
    {
      "from": "00c1abc9"
    },
    {
      "from": "00c1c165"
    },
    {
      "from": "00c1c174"
    },
    {
      "from": "00c1e1fc"
    },
    {
      "from": "00c1e20d"
    },
    {
      "from": "00c0cfad"
    },
    {
      "from": "00c193ab"
    },
    {
      "from": "00c193bc"
    },
    {
      "from": "00c0cfe4"
    },
    {
      "from": "00c1b43f"
    },
    {
      "from": "00c1b450"
    },
    {
      "from": "00c0d074"
    },
    {
      "from": "00c0d084"
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
    "reconstruction/staging/wave13-w1-core-b08/ae9f50_session_boot_register.cpp",
    "reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp",
    "reconstruction/staging/wave13-w1-core-b08/ba61b0_make_planet_record.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c0b780_sub_object_flag_608.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c0ce80_tier_value_lookup.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c47180_manager_slot_replace.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test2.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b08/00c0ce80.json"
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
    "No original-process trace exists. A differential run must confirm the six table values at 0x015D9650 and the boolean behind slot +0x58 at the moment this function runs.",
    "The concrete receiver behind the slot +0x58 dispatch must be observed before the owning class can be named.",
    "The sentinel branch is only reachable once 0x01654C10 has been populated at runtime; in the file image it holds 0, so the branch cannot be exercised statically.",
    "The value of the singleton's float vector at singleton+0x10 can only be observed at runtime, which also determines whether 0x00F31500 returns a real element or FLD1."
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
  "float"
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
