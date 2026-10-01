# Evidence 0x00635760

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f3a323343a28a3cbcf4ddf99e3a344101a4874f62e783222be244d6873883c0f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX, forwarded unchanged to 0x00634dc0; overwritten at 0x0063577b with the resolved window before the tail transfer",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "EAX is a lookup result on entry to the dispatch path and is overwritten with the window pointer at 0x0063577b; on the null path EAX is 0 at 0x0063576a. No consumer reads EAX after any of the recorded call sites, so no return value is observable.",
  "return_register": null,
  "return_semantics": "void",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [],
  "stack_arguments": [
    {
      "entry_offset": "ESP+4",
      "name": "control_id",
      "role": "UTFWin control id, forwarded to the lookup and then replaced by the constant 1 before the tail transfer",
      "type": "std::uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+8",
      "name": "visible",
      "role": "value written into kWinFlagVisible; forwarded verbatim as the second argument of the +0x7C dispatch",
      "type": "bool",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "0x0063577f RET 8 on the null path; 0x0063577d JMP EDX (tail transfer) on the success path"
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
    "calling_convention": "__stdcall",
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
    "receiver": false,
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "SUPPORTED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [
    {
      "field": "calling_convention",
      "inferred": "__stdcall",
      "kind": "inferred_vs_persisted",
      "persisted": "__thiscall",
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "23566c136d25cbbe90d9a8eb0231fb3bdb691da8c7d99ec6fe4f7f87992df0c6",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__stdcall",
    "candidate_conventions": [
      "__stdcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "disagrees",
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
        "obs-0011"
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
        "obs-0002"
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
        "obs-0011"
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
        "obs-0011"
      ],
      "claim": "calling convention is __stdcall: a callee that pops stack arguments with no register receiver",
      "confidence": "INFERRED",
      "id": "C6",
      "value": "__stdcall"
    },
    {
      "based_on": [
        "obs-0011"
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
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011"
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
      "at": "0x00635760",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00635760",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00635760",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00635764",
      "count": 3,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00635765",
      "id": "obs-0005",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00634dc0",
      "target": "0x00634dc0"
    },
    {
      "at": "0x0063576e",
      "definite": true,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00635770",
      "count": 2,
      "first_use": 6,
      "first_write_index": 5,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EDX + 0x7c]",
      "reg": "EDX"
    },
    {
      "at": "0x00635773",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0008",
      "index": 7,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP + 0x4],0x1",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x0063577b",
      "definite": true,
      "id": "obs-0009",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x0063577d",
      "base": "EDX",
      "disp": null,
      "id": "obs-0010",
      "index": 9,
      "ki
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
    "va": "0x0062ba10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062bf10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062c340"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062c990"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062e7a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062e7e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062ebe0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062ec30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062f340"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062f480"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062fc90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062fda0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062fe40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006301a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00630280"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00632ba0"
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
      "address": "00635760",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00635764",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00635765",
      "instruction": "CALL 0x00634dc0"
    },
    {
      "address": "0063576a",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0063576c",
      "instruction": "JZ 0x0063577f"
    },
    {
      "address": "0063576e",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00635770",
      "instruction": "MOV EDX,dword ptr [EDX + 0x7c]"
    },
    {
      "address": "00635773",
      "instruction": "MOV dword ptr [ESP + 0x4],0x1"
    },
    {
      "address": "0063577b",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0063577d",
      "instruction": "JMP EDX"
    },
    {
      "address": "0063577f",
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
  "original_bytes": 15052,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX, forwarded unchanged to 0x00634dc0; overwritten at 0x0063577b with the resolved window before the tail transfer\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x8\",\n    \"return_observation\": \"EAX is a lookup result on entry to the dispatch path and is overwritten with the window pointer at 0x0063577b; on the null path EAX is 0 at 0x0063576a. No consumer reads EAX after any of the recorded call sites, so no return value is observable.\",\n    \"return_register\": null,\n    \"return_semantics\": \"void\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+4\",\n        \"name\": \"control_id\",\n        \"role\": \"UTFWin control id, forwarded to the lookup and then replaced by the constant 1 before the tail transfer\",\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+8\",\n        \"name\": \"visible\",\n        \"role\": \"value written into kWinFlagVisible; forwarded verbatim as the second argument of the +0x7C dispatch\",\n        \"type\": \"bool\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"0x0063577f RET 8 on the null path; 0x0063577d JMP EDX (tail transfer) on the success path\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062ba10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062bf10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062c340\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062c990\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062e7a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062e7e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062ebe0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062ec30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062f340\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062f480\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062fc90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062fda0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062fe40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006301a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00630280\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00632ba0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00632c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00632c60\"\n      },\n      {\n        \"name\": null,\n     
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
  "body_end": "00635781",
  "body_span_bytes": 34,
  "body_start": "00635760",
  "callees": [
    "FUN_00634dc0"
  ],
  "callers": [
    "FUN_0062e7e0",
    "FUN_006301a0",
    "FUN_0062f340",
    "FUN_0063b760",
    "FUN_0062f480",
    "FUN_00632c60",
    "FUN_006411b0",
    "FUN_0063d910",
    "FUN_0062e7a0",
    "FUN_0062c340",
    "FUN_00632c00",
    "FUN_00632ce0",
    "FUN_00630280",
    "FUN_0062ba10",
    "FUN_0062bf10",
    "FUN_0063c8f0",
    "FUN_0063f5c0",
    "FUN_0062ebe0",
    "FUN_0062c990",
    "FUN_0062fe40",
    "FUN_0063e880",
    "FUN_0062ec30",
    "FUN_00636560",
    "FUN_00632ba0",
    "FUN_0062fc90",
    "FUN_00634030",
    "FUN_0062fda0"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00635760",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00635760",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x235760",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00635760(void)",
  "size_bytes": 34,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00635760",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 98,
  "xrefs": [
    {
      "from": "0062bfe2"
    },
    {
      "from": "0062bff1"
    },
    {
      "from": "0062c000"
    },
    {
      "from": "0062c020"
    },
    {
      "from": "0062c367"
    },
    {
      "from": "0062c375"
    },
    {
      "from": "0062c383"
    },
    {
      "from": "0062fcff"
    },
    {
      "from": "0062fd1c"
    },
    {
      "from": "0062fd2a"
    },
    {
      "from": "0062fd38"
    },
    {
      "from": "0062fd46"
    },
    {
      "from": "0062f374"
    },
    {
      "from": "0062f383"
    },
    {
      "from": "0062f392"
    },
    {
      "from": "0062f3a1"
    },
    {
      "from": "0062f3b4"
    },
    {
      "from": "0062f3c3"
    },
    {
      "from": "0062f3d2"
    },
    {
      "from": "0062f3e1"
    },
    {
      "from": "0062f3f4"
    },
    {
      "from": "0062f403"
    },
    {
      "from": "0062f412"
    },
    {
      "from": "0062f421"
    },
    {
      "from": "0062f43b"
    },
    {
      "from": "0062f44a"
    },
    {
      "from": "0062f459"
    },
    {
      "from": "0062f468"
    },
    {
      "from": "0062f49d"
    },
    {
      "from": "0062f4ac"
    },
    {
      "from": "0062f4bb"
    },
    {
      "from": "0062f4ca"
    },
    {
      "from": "0062baef"
    },
    {
      "from": "0062bafe"
    },
    {
      "from": "0062e7ad"
    },
    {
      "from": "0062e7c7"
    },
    {
      "from": "0062e80c"
    },
    {
      "from": "0062ebf3"
    },
    {
      "from": "0062ec4c"
    },
    {
      "from": "0062ec5b"
    },
    {
      "from": "0062fe1d"
    },
    {
      "from": "0062fe2c"
    },
    {
      "from": "0062febd"
    },
    {
      "from": "0062fecc"
    },
    {
      "from": "006301c1"
    },
    {
      "from": "006301d0"
    },
    {
      "from": "006301df"
    },
    {
      "from": "006302a1"
    },
    {
      "from": "006302b0"
    },
    {
      "from": "006302bf"
    },
    {
      "from": "00632bad"
    },
    {
      "from": "00632c0d"
    },
    {
      "from": "00632c6d"
    },
    {
      "from": "00632ced"
    },
    {
      "from": "006340a1"
    },
    {
      "from": "006340b0"
    },
    {
      "from": "00636e6d"
    },
    {
      "from": "00636e97"
    },
    {
      "from": "00636ea5"
    },
    {
      "from": "00636eb3"
    },
    {
      "from": "00636ec1"
    },
    {
      "from": "00636ecf"
    },
    {
      "from": "00636f1f"
    },
    {
      "from": "00636f49"
    },
    {
      "from": "00636f57"
    },
    {
      "from": "00636f65"
    },
    {
      "from": "00636f73"
    },
    {
      "from": "00636f81"
    },
    {
      "from": "0062c9dd"
    },
    {
      "from": "0062c9ec"
    },
    {
      "from": "0062ca27"
    },
    {
      "from": "0062ca36"
    },
    {
      "from": "0063ca50"
    },
    {
      "from": "0063ca5f"
    },
    {
      "from": "0063ca7f"
    },
    {
      "from": "0063ca95"
    },
    {
      "from": "0063d9b1"
    },
    {
      "from": "0063d9c0"
    },
    {
      "from": "0063b780"
    },
    {
      "from": "0063b796"
    },
    {
      "from": "0063e8d9"
    },
    {
      "from": "0063e8f2"
    },
    {
      "from": "0063e9bf"
    },
    {
      "from": "0063e9ce"
    },
    {
      "from": "0063ea0c"
    },
    {
      "from": "0063ea1a"
    },
    {
      "from": "006411e6"
    },
    {
      "from": "006411f4"
    },
    {
      "from": "00641202"
    },
    {
      "from": "0063f6f5"
    },
    {
      "from": "0063f704"
    },
    {
      "from": "0063f713"
    },
    {
      "from": "0062f4ef"
    },
    {
      "from": "0062f501"
    },
    {
      "from": "0062f513"
    },
    {
      "from": "0062f525"
    },
    {
      "from": "0063e4d4"
    },
    {
      "from": "0063e4e3"
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
    "reconstruction/staging/wave13-pilot-dispatch-b00/utfwin_00635760.cpp",
    "reconstruction/staging/wave13-pilot-dispatch-b00/utfwin_00635760.hpp",
    "reconstruction/staging/wave13-pilot-dispatch-b00/utfwin_00635760_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-dispatch-b00/00635760.json"
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
    "A runtime differential test would have to (a) confirm the lookup returns the same window for a given control id, (b) confirm the +0x7C dispatch reaches an IWindow::SetFlag implementation and not a patched one, and (c) confirm the callee really uses RET 8, which the tail transfer requires but which no in-binary observation of the concrete callee can prove.",
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static."
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
  "bool",
  "std::uint32_t",
  "void"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "derived": "__stdcall",
    "field": "calling_convention",
    "kind": "derived_vs_persisted",
    "persisted": "__thiscall",
    "resolution_status": "unresolved"
  }
]
```
