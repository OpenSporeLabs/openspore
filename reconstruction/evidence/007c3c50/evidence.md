# Evidence 0x007c3c50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `38c5dadeb827998bdf669e8975a0c011bbee85889d8de8b68f1fb79c538cfdf2`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueWorldViewer*",
  "return_register": "EAX",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "flags",
      "position": 1,
      "type": "std::uint8_t",
      "width_bytes": 1
    }
  ],
  "stack_cleanup_bytes": 4,
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
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "receiver": false,
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ]
  },
  "abstained_because": [
    "no_terminal_ret: the listing is a prefix of a longer function",
    "truncated_listing: the last instruction is neither a return nor an out-of-listing transfer, so the listing stops mid-function"
  ],
  "cleanup": {
    "bytes": null,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": null,
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "8d427d6058e674162d7bc246cd522436c8a44597646e63fbc3a4126951b815fb",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
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
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0005"
      ],
      "claim": "no terminal return is present in the listing",
      "confidence": "UNKNOWN",
      "id": "C2"
    },
    {
      "based_on": [
        "obs-0002"
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
        "obs-0005"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0005"
      ],
      "claim": "entry slot 0 is not written through a pointer",
      "confidence": "APPROXIMATION",
      "id": "S2",
      "value": {
        "present": false
      }
    }
  ],
  "observations": [
    {
      "at": "0x007c3c50",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV DL,byte ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x007c3c50",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV DL,byte ptr [ESP + 0x4]",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x007c3c50",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV DL,byte ptr [ESP + 0x4]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007c3c54",
      "count": 1,
      "first_use": 1,
      "first_write_index": 1,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "XOR EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x007c3c54",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "XOR EAX,EAX",
      "reg": "EAX",
      "write_kind": "zero"
    }
  ],
  "parse": {
    "declared_count": 11,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "OBSERVED",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": false,
    "register": null,
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "integral",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "INFERRED",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 1,
    "slots": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "total_bytes": 4,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": null,
    "present": false,
    "target": null
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 11,
    "syntax": "intel",
    "va
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
    "va": "0x00430e70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005812b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006e3100"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006e8810"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006efe90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f3f20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f41e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f5260"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f54a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076ce50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076d970"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0077f2c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0077f380"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b3340"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b3820"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b6730"
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
  "count": 11,
  "instructions": [
    {
      "address": "007c3c50",
      "instruction": "MOV DL,byte ptr [ESP + 0x4]"
    },
    {
      "address": "007c3c54",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "007c3c56",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "007c3c59",
      "instruction": "JZ 0x007c3c60"
    },
    {
      "address": "007c3c5b",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "007c3c60",
      "instruction": "TEST DL,0x2"
    },
    {
      "address": "007c3c63",
      "instruction": "JZ 0x007c3c68"
    },
    {
      "address": "007c3c65",
      "instruction": "OR EAX,0x2"
    },
    {
      "address": "007c3c68",
      "instruction": "TEST DL,0x4"
    },
    {
      "address": "007c3c6b",
      "instruction": "JZ 0x007c3c70"
    },
    {
      "address": "007c3c6d",
      "instruction": "OR EAX,0x4"
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
  "original_bytes": 13156,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueWorldViewer*\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"std::uint8_t\",\n    \"return_width_bytes\": 1,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"flags\",\n        \"position\": 1,\n        \"type\": \"std::uint8_t\",\n        \"width_bytes\": 1\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_Update_0059b4b0\",\n      \"va\": \"0x0059b4b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n      \"va\": \"0x0059cb10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n      \"va\": \"0x0059cea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n      \"va\": \"0x0059cf00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"editor_anim_event_message_send_0059d8b0\",\n      \"va\": \"0x0059d8b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No runtime render-state trace is available.\",\n    \"The Ghidra function-boundary split at 0x007c3c70 must be corrected or bypassed before any automatic integration.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00430e70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005812b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006e3100\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006e8810\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006efe90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f3f20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f41e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f5260\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f54a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076ce50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076d970\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0077f2c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0077f380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b3340\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b3820\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b6730\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b68f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b7830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b7920\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b7a20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b7ac0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b8cb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bd750\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bfaa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007e7380\"\n      },\n      {\n        \"name\": nul
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
  "body_end": "007c3c6f",
  "body_span_bytes": 32,
  "body_start": "007c3c50",
  "callees": [],
  "callers": [
    "FUN_007b7a20",
    "FUN_007b7920",
    "FUN_00e54ab0",
    "FUN_007e7380",
    "FUN_007b3340",
    "FUN_006e8810",
    "FUN_006efe90",
    "FUN_00e54b80",
    "FUN_006e3100",
    "FUN_007b8cb0",
    "FUN_007bfaa0",
    "FUN_0080da50",
    "FUN_00430e70",
    "FUN_006f54a0",
    "FUN_00f9a7c0",
    "FUN_0080e6b0",
    "FUN_006f3f20",
    "FUN_0077f2c0",
    "FUN_006f5260",
    "FUN_00f9c470",
    "FUN_007b7ac0",
    "FUN_00f67da0",
    "FUN_007b3820",
    "FUN_007bd750",
    "FUN_00fa3860",
    "FUN_005812b0",
    "FUN_0076d970",
    "FUN_006f41e0",
    "FUN_00fa2a20",
    "FUN_007b6730",
    "FUN_0076ce50",
    "FUN_007b7830",
    "FUN_0077f380",
    "FUN_007b68f0",
    "FUN_00fa5cc0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "007c3c50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_007c3c50",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3c3c50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_007c3c50(void)",
  "size_bytes": 32,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007c3c50",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 65,
  "xrefs": [
    {
      "from": "0043168b"
    },
    {
      "from": "004319de"
    },
    {
      "from": "005813b7"
    },
    {
      "from": "005814da"
    },
    {
      "from": "005815b1"
    },
    {
      "from": "006e3b85"
    },
    {
      "from": "006e8b35"
    },
    {
      "from": "006e8ca3"
    },
    {
      "from": "006f3f91"
    },
    {
      "from": "006f4268"
    },
    {
      "from": "006f02e5"
    },
    {
      "from": "006f5399"
    },
    {
      "from": "006f545e"
    },
    {
      "from": "006f557c"
    },
    {
      "from": "006f5675"
    },
    {
      "from": "0076d0e7"
    },
    {
      "from": "0076d4d7"
    },
    {
      "from": "0076d98a"
    },
    {
      "from": "0077f2eb"
    },
    {
      "from": "007b3416"
    },
    {
      "from": "007b3922"
    },
    {
      "from": "007b67fa"
    },
    {
      "from": "007b6868"
    },
    {
      "from": "007b6919"
    },
    {
      "from": "007b784f"
    },
    {
      "from": "007b78c3"
    },
    {
      "from": "007b795a"
    },
    {
      "from": "007b79af"
    },
    {
      "from": "007b7a52"
    },
    {
      "from": "007b7bb0"
    },
    {
      "from": "007b7da8"
    },
    {
      "from": "007b8035"
    },
    {
      "from": "007b8e94"
    },
    {
      "from": "007bd7da"
    },
    {
      "from": "007bd8d4"
    },
    {
      "from": "007bda54"
    },
    {
      "from": "007bfbe6"
    },
    {
      "from": "007e75b4"
    },
    {
      "from": "0080dae9"
    },
    {
      "from": "0080e7b4"
    },
    {
      "from": "00e54af2"
    },
    {
      "from": "00e54c55"
    },
    {
      "from": "00f67e47"
    },
    {
      "from": "00f9a801"
    },
    {
      "from": "00f9a830"
    },
    {
      "from": "00f9c4de"
    },
    {
      "from": "00fa3935"
    },
    {
      "from": "00fa3a21"
    },
    {
      "from": "00fa3582"
    },
    {
      "from": "0077f3da"
    },
    {
      "from": "00760ac8"
    },
    {
      "from": "007b3b1c"
    },
    {
      "from": "007b6677"
    },
    {
      "from": "00b34036"
    },
    {
      "from": "00b34190"
    },
    {
      "from": "00fa5dba"
    },
    {
      "from": "00fd7396"
    },
    {
      "from": "005817b9"
    },
    {
      "from": "00581b02"
    },
    {
      "from": "00581c59"
    },
    {
      "from": "00581d2d"
    },
    {
      "from": "00581ecd"
    },
    {
      "from": "00581fcd"
    },
    {
      "from": "0058205e"
    },
    {
      "from": "010354cf"
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
    "reconstruction/staging/pkg14-a1-world-state/world_state.cpp",
    "reconstruction/staging/pkg14-a1-world-state/world_state.hpp",
    "reconstruction/staging/pkg14-a1-world-state/world_state_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg14-a1-world-state/007c3c50.json"
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
  "OpaqueWorldViewer*",
  "cViewer",
  "std::uint8_t"
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
