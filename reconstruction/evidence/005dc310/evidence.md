# Evidence 0x005dc310

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5969882cb396c3adae2aafd53ff855e315911d5fb2e53757202bf776b8edea3f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX, copied to ESI at 0x005dc316 and never reloaded",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_note": "(a pointer, in EAX); Opaque5dc310Window*; void*",
  "return_observation": "0x005dc323 TEST EAX,EAX and 0x005dc325 JNZ read the first call's EAX; when the branch is not taken the second call at 0x005dc32d leaves its own answer in EAX. Neither POP EDI (0x005dc332) nor POP ESI (0x005dc333) touches EAX, and the epilogue is only those two pops plus RET. The Ghidra decompilation types this function 'void' and drops the result entirely; that typing is a decompiler miss, contradicted by every inspected caller.",
  "return_register": "EAX",
  "return_semantics": "the EAX produced by the last 0x008105b0 call that executed: the +0x14 sub-object's answer when it was non-null, otherwise the +0x2c sub-object's answer (which may itself be null)",
  "return_width_bytes": 4,
  "saved_registers": [
    "EDI",
    "ESI"
  ],
  "stack_arguments": [
    "{'entry_offset': 'ESP+4', 'name': 'lookup_key', 'type': 'uint32_t', 'width_bytes': 4}",
    "{'offset_in_callee': '[ESP + 0xc] before the two pushes', 'read_by': '0x005dc312: MOV EDI,dword ptr [ESP + 0xc]', 'role': 'the control id, forwarded to both 0x008105b0 calls', 'slot': 1, 'width_bytes': 4}"
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
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "ce3e862d30cc98c799ee1ec6aa2b558c80cd6266c1c3c1a4508c1e5bcbe2e5aa",
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
        "obs-0012"
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
        "obs-0004"
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
        "obs-0007"
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
        "obs-0007"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0012"
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
        "obs-0012"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0012"
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
      "at": "0x005dc310",
      "count": 3,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005dc311",
      "count": 3,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x005dc312",
      "count": 1,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x005dc312",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0004",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x005dc312",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005dc316",
      "count": 3,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005dc316",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x005dc31e",
      "id": "obs-0008",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x008105b0",
      "target": "0x008105b0"
    },
    {
      "at": "0x005dc32d",
      "id": "obs-0009",
      "index": 13,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x008105b0",
      "target": "0x008105b0"
    },
    {
      "at": "0x005dc332",
      "id": "obs-0010",
      "index": 14,
      
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
    "name": "Editors::cEditor::Update",
    "reconstructed": false,
    "va": "0x0058be50"
  },
  {
    "name": "Editors::cEditor::HandleMessage",
    "reconstructed": false,
    "va": "0x00591fa0"
  },
  {
    "name": "FUN_005dda30",
    "reconstructed": true,
    "va": "0x005dda30"
  },
  {
    "name": "editor_query_dispatch_005dfd00",
    "reconstructed": true,
    "va": "0x005dfd00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00634e40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00634f20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635010"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635390"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635400"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006354c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635520"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635580"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635600"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635680"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635790"
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
      "address": "005dc310",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005dc311",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005dc312",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "005dc316",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005dc318",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dc31a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005dc31b",
      "instruction": "LEA ECX,[ESI + 0x14]"
    },
    {
      "address": "005dc31e",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005dc323",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005dc325",
      "instruction": "JNZ 0x005dc332"
    },
    {
      "address": "005dc327",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dc329",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005dc32a",
      "instruction": "LEA ECX,[ESI + 0x2c]"
    },
    {
      "address": "005dc32d",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005dc332",
      "instruction": "POP EDI"
    },
    {
      "address": "005dc333",
      "instruction": "POP ESI"
    },
    {
      "address": "005dc334",
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
  "original_bytes": 15909,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX, copied to ESI at 0x005dc316 and never reloaded\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x4\",\n    \"return_note\": \"(a pointer, in EAX); Opaque5dc310Window*; void*\",\n    \"return_observation\": \"0x005dc323 TEST EAX,EAX and 0x005dc325 JNZ read the first call's EAX; when the branch is not taken the second call at 0x005dc32d leaves its own answer in EAX. Neither POP EDI (0x005dc332) nor POP ESI (0x005dc333) touches EAX, and the epilogue is only those two pops plus RET. The Ghidra decompilation types this function 'void' and drops the result entirely; that typing is a decompiler miss, contradicted by every inspected caller.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"the EAX produced by the last 0x008105b0 call that executed: the +0x14 sub-object's answer when it was non-null, otherwise the +0x2c sub-object's answer (which may itself be null)\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      \"{'entry_offset': 'ESP+4', 'name': 'lookup_key', 'type': 'uint32_t', 'width_bytes': 4}\",\n      \"{'offset_in_callee': '[ESP + 0xc] before the two pushes', 'read_by': '0x005dc312: MOV EDI,dword ptr [ESP + 0xc]', 'role': 'the control id, forwarded to both 0x008105b0 calls', 'slot': 1, 'width_bytes': 4}\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"palette_safe_wave11_fill_node_array_005c7ff0\",\n      \"va\": \"0x005c7ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 5,\n      \"symbol\": \"FUN_005dda30\",\n      \"va\": \"0x005dda30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005fa8d0\",\n      \"va\": \"0x005fa8d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_0060ee90\",\n      \"va\": \"0x0060ee90\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 5,\n      \"symbol\": \"FUN_00aea230\",\n      \"va\": \"0x00aea230\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"re_00835380\",\n      \"va\": \"0x00835380\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"Ghidra currently records a void return, so a more specific result type is not supported by the recovered prototype.\",\n    \"The result remains void*: no target owner, RTTI identity, lifetime, or ownership is asserted.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"Editors::cEditor::Update\",\n        \"reconstructed\": false,\n        \"va\": \"0x0058be50\"\n      },\n      {\n        \"name\": \"Editors::cEditor::HandleMessage\",\n        \"reconstructed\": false,\n        \"va\": \"0x00591fa0\"\n      },\n      {\n        \"name\": \"FUN_005dda30\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dda30\"\n      },\n      {\n        \"name\": \"editor_query_dispatch_005dfd00\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dfd00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00634e40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00634f20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635010\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635390\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635400\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006354c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635520\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635580\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"
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
  "body_end": "005dc336",
  "body_span_bytes": 39,
  "body_start": "005dc310",
  "callees": [
    "FUN_008105b0"
  ],
  "callers": [
    "FUN_00635400",
    "FUN_00636320",
    "FUN_00635680",
    "FUN_00637f80",
    "FUN_00635010",
    "FUN_005dda30",
    "FUN_005dfd00",
    "FUN_00637c90",
    "FUN_006377d0",
    "FUN_00635520",
    "FUN_006373e0",
    "FUN_00635160",
    "FUN_00637860",
    "FUN_006354c0",
    "FUN_00635600",
    "FUN_00634e40",
    "FUN_00635390",
    "FUN_006358c0",
    "FUN_00636560",
    "FUN_00638430",
    "FUN_00634f20",
    "FUN_00635790",
    "FUN_00635580",
    "Editors::cEditor::Update",
    "Editors::cEditor::HandleMessage"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005dc310",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005dc310",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1dc310",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005dc310(void)",
  "size_bytes": 39,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005dc310",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 69,
  "xrefs": [
    {
      "from": "005ddaba"
    },
    {
      "from": "005ddad7"
    },
    {
      "from": "005ddaf4"
    },
    {
      "from": "005ddb11"
    },
    {
      "from": "005ddba8"
    },
    {
      "from": "005ddbc5"
    },
    {
      "from": "005ddbe2"
    },
    {
      "from": "005ddbff"
    },
    {
      "from": "005ddc6a"
    },
    {
      "from": "005ddc87"
    },
    {
      "from": "005ddca4"
    },
    {
      "from": "00635973"
    },
    {
      "from": "0063599e"
    },
    {
      "from": "0063518a"
    },
    {
      "from": "006354fa"
    },
    {
      "from": "00637413"
    },
    {
      "from": "00637442"
    },
    {
      "from": "0063745f"
    },
    {
      "from": "0063552f"
    },
    {
      "from": "0063539c"
    },
    {
      "from": "00634f2b"
    },
    {
      "from": "0063579b"
    },
    {
      "from": "0063501b"
    },
    {
      "from": "0063540f"
    },
    {
      "from": "0063542f"
    },
    {
      "from": "00636fda"
    },
    {
      "from": "00637045"
    },
    {
      "from": "0063788e"
    },
    {
      "from": "006378ec"
    },
    {
      "from": "00637916"
    },
    {
      "from": "0063795a"
    },
    {
      "from": "0063799e"
    },
    {
      "from": "006379e2"
    },
    {
      "from": "00637a26"
    },
    {
      "from": "00637a46"
    },
    {
      "from": "00637a66"
    },
    {
      "from": "00637a86"
    },
    {
      "from": "00637aa6"
    },
    {
      "from": "00637ac6"
    },
    {
      "from": "00637ae6"
    },
    {
      "from": "00637b06"
    },
    {
      "from": "00637b27"
    },
    {
      "from": "00637b88"
    },
    {
      "from": "00637bc4"
    },
    {
      "from": "00637c1a"
    },
    {
      "from": "00637ceb"
    },
    {
      "from": "00637d3c"
    },
    {
      "from": "00637d59"
    },
    {
      "from": "00637db9"
    },
    {
      "from": "00637e12"
    },
    {
      "from": "00637e2f"
    },
    {
      "from": "00637e8f"
    },
    {
      "from": "0063560c"
    },
    {
      "from": "0063568c"
    },
    {
      "from": "006363cd"
    },
    {
      "from": "006363ee"
    },
    {
      "from": "00638455"
    },
    {
      "from": "00638027"
    },
    {
      "from": "00638039"
    },
    {
      "from": "00638259"
    },
    {
      "from": "0063558c"
    },
    {
      "from": "006377db"
    },
    {
      "from": "00634e46"
    },
    {
      "from": "005dff89"
    },
    {
      "from": "0058c7e3"
    },
    {
      "from": "0058ca9a"
    },
    {
      "from": "0059230f"
    },
    {
      "from": "00592377"
    },
    {
      "from": "005925ae"
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
    "reconstruction/staging/wave13-w1-dispatch-b00/editor_ui_005dc310.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b00/editor_ui_005dc310.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/005dc310.json",
    "reconstruction/metadata/wave13-w1-dispatch-b00/005dc310.json"
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
    "A runtime differential test is required to resolve vtable slots +0x0c, +0x1c and +0xf0 on a live editor element, and to confirm that the +0x14 candidate really does shadow the +0x2c candidate in the shipping build.",
    "No original-process trace exists for 0x005dc310; every claim is static and the Cell stage has never been entered in any recorded run.",
    "The SDK's UILayoutObjects offsets must be re-derived before the +0x64/+0x68 scan bounds can be attributed to a named member.",
    "Whether the +0x2c fallback is ever load-bearing cannot be settled statically; only a run with the main layout empty would show it."
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
  "EditorUI*",
  "Opaque void* for the lookup result; no concrete target owner or ownership contract is asserted",
  "Opaque5dc310Window* (a pointer, in EAX)",
  "OpaqueEditorModeManager for ECX",
  "pointer (nullable)",
  "pointer one past the last array element",
  "pointer to the first array element",
  "sub-object address (opaque)",
  "uint32_t",
  "uint32_t for the lookup key",
  "void*"
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
