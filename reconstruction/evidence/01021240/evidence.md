# Evidence 0x01021240

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7a20f4293c65ba011a1b9942276e9273c15fd53587f219dc7c746c2ecfe1af18`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "no_discriminator: no stack-argument read and no positive receiver evidence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "f1153afca65f8071864d6a15c4c73b88aa12fbb9625b206fdc3f24219e9ad03c",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0003",
        "obs-0004"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0004"
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
        "obs-0004"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004"
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
        "obs-0003",
        "obs-0004"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004"
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
      "at": "0x01021240",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016dda8c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01021245",
      "count": 3,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x8]",
      "reg": "EAX"
    },
    {
      "at": "0x0102124f",
      "form": "RET",
      "id": "obs-0003",
      "imm": null,
      "index": 5,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x01021252",
      "form": "RET",
      "id": "obs-0004",
      "imm": null,
      "index": 7,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 8,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
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
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
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
    "instructions": 8,
    "syntax": "intel",
    "va": "0x01021240"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_UNKNOWN"
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
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "no_discriminator: no stack-argument read and no positive receiver evidence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "f1153afca65f8071864d6a15c4c73b88aa12fbb9625b206fdc3f24219e9ad03c",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0003",
        "obs-0004"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0004"
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
        "obs-0004"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004"
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
        "obs-0003",
        "obs-0004"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004"
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
      "at": "0x01021240",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016dda8c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01021245",
      "count": 3,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x8]",
      "reg": "EAX"
    },
    {
      "at": "0x0102124f",
      "form": "RET",
      "id": "obs-0003",
      "imm": null,
      "index": 5,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x01021252",
      "form": "RET",
      "id": "obs-0004",
      "imm": null,
      "index": 7,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 8,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
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
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
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
    "instructions": 8,
    "syntax": "intel",
    "va": "0x01021240"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_UNKNOWN"
}
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
    "va": "0x00bb4ba0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bba4b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c314a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c31550"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c341a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c382e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c3a2b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c3ae70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c3dba0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4ea70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4f160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c53720"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c5eed0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c5efb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c5f690"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c61070"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nundefined4 FUN_01021240(void)\n\n{\n  if (*(int *)(Simulator__sSpacePlayerData + 8) != 0) {\n    return *(undefined4 *)(*(int *)(Simulator__sSpacePlayerData + 8) + 0x48);\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 8,
  "instructions": [
    {
      "address": "01021240",
      "instruction": "MOV EAX,[0x016dda8c]"
    },
    {
      "address": "01021245",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "01021248",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0102124a",
      "instruction": "JZ 0x01021250"
    },
    {
      "address": "0102124c",
      "instruction": "MOV EAX,dword ptr [EAX + 0x48]"
    },
    {
      "address": "0102124f",
      "instruction": "RET"
    },
    {
      "address": "01021250",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "01021252",
      "instruction": "RET"
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
  "original_bytes": 13202,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb4ba0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bba4b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c314a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c31550\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c341a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c382e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c3a2b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c3ae70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c3dba0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4ea70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4f160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c53720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5eed0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5efb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5f690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c61070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c7bd40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c817e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e07e70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e99c50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fd9de0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fda5e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdade0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdbee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdd390\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdd4f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdd5a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdeac0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe0570\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe9580\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ff7530\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ff8ad0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ffa780\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\
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
  "body_end": "01021252",
  "body_span_bytes": 19,
  "body_start": "01021240",
  "callees": [],
  "callers": [
    "FUN_010251e0",
    "FUN_00c5f690",
    "FUN_00c3ae70",
    "FUN_010229d0",
    "FUN_00bb4ba0",
    "FUN_00fdeac0",
    "FUN_01058c90",
    "FUN_00c61070",
    "FUN_0102df20",
    "FUN_0101be60",
    "FUN_01076b80",
    "FUN_010697b0",
    "FUN_00fdd5a0",
    "FUN_01008100",
    "FUN_01003490",
    "FUN_00c5efb0",
    "FUN_00c53720",
    "FUN_00c3a2b0",
    "FUN_00c5eed0",
    "FUN_01024630",
    "FUN_00bba4b0",
    "FUN_0100b430",
    "FUN_0101bf40",
    "FUN_00fff6a0",
    "FUN_010422e0",
    "FUN_00ff8ad0",
    "FUN_00fdade0",
    "FUN_00c7bd40",
    "FUN_00fdbee0",
    "FUN_00c4ea70",
    "FUN_01057bd0",
    "FUN_00fdd4f0",
    "FUN_00fd9de0",
    "FUN_0102ba30",
    "FUN_00fdd390",
    "FUN_0101bd10",
    "FUN_010593e0",
    "FUN_01009df0",
    "FUN_00ffdbb0",
    "FUN_01056160",
    "FUN_010021a0",
    "FUN_0106a280",
    "FUN_010468f0",
    "FUN_0106cc70",
    "FUN_00e99c50",
    "FUN_010095e0",
    "FUN_01038410",
    "FUN_00c382e0",
    "FUN_0103eff0",
    "FUN_00c3dba0",
    "FUN_00fda5e0",
    "FUN_00ff7530",
    "FUN_00c31550",
    "FUN_0102aa50",
    "FUN_00ffe130",
    "FUN_00ffc8d0",
    "FUN_0106b310",
    "FUN_00ffa780",
    "FUN_00fe9580",
    "FUN_01005180",
    "FUN_01046160",
    "FUN_00c314a0",
    "FUN_00c4f160",
    "FUN_00c817e0",
    "FUN_01008910",
    "FUN_01072d40",
    "FUN_00ffaf20",
    "FUN_00e07e70",
    "FUN_00c341a0",
    "FUN_01069aa0",
    "FUN_00fe0570",
    "FUN_01003df0",
    "FUN_010053c0",
    "FUN_010463b0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "01021240",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_01021240",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc21240",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01021240(void)",
  "size_bytes": 19,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01021240",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00bb4caf"
    },
    {
      "from": "00c3425e"
    },
    {
      "from": "00fe970e"
    },
    {
      "from": "00fe9895"
    },
    {
      "from": "00fe9bea"
    },
    {
      "from": "00fe9ce6"
    },
    {
      "from": "00c314dc"
    },
    {
      "from": "00c31576"
    },
    {
      "from": "00c31585"
    },
    {
      "from": "00c315d5"
    },
    {
      "from": "00c7bdba"
    },
    {
      "from": "0100520b"
    },
    {
      "from": "0102e130"
    },
    {
      "from": "0102e431"
    },
    {
      "from": "0102e681"
    },
    {
      "from": "0102e697"
    },
    {
      "from": "0102e6a7"
    },
    {
      "from": "0102e786"
    },
    {
      "from": "00c3dcca"
    },
    {
      "from": "00c3dcd3"
    },
    {
      "from": "00c3a2b9"
    },
    {
      "from": "00ffe20d"
    },
    {
      "from": "00c3b088"
    },
    {
      "from": "0102ba7b"
    },
    {
      "from": "0106cde4"
    },
    {
      "from": "0106cf2a"
    },
    {
      "from": "0106d7e4"
    },
    {
      "from": "0106d7f9"
    },
    {
      "from": "00ffc8ed"
    },
    {
      "from": "010697d3"
    },
    {
      "from": "0106b36f"
    },
    {
      "from": "0106a299"
    },
    {
      "from": "00c382ed"
    },
    {
      "from": "00c3840c"
    },
    {
      "from": "00fdd3b1"
    },
    {
      "from": "00fdd3c3"
    },
    {
      "from": "00fdd43e"
    },
    {
      "from": "00fdd5bb"
    },
    {
      "from": "00fdd71a"
    },
    {
      "from": "00ff8ad6"
    },
    {
      "from": "0101bd97"
    },
    {
      "from": "0101bea9"
    },
    {
      "from": "00c4eafc"
    },
    {
      "from": "00c4f1ed"
    },
    {
      "from": "00c53779"
    },
    {
      "from": "00ffa784"
    },
    {
      "from": "00c8185d"
    },
    {
      "from": "00e091e2"
    },
    {
      "from": "00e99d91"
    },
    {
      "from": "00fda6bd"
    },
    {
      "from": "00ffdbc4"
    },
    {
      "from": "0100355b"
    },
    {
      "from": "01008109"
    },
    {
      "from": "0101bf60"
    },
    {
      "from": "00fdadf6"
    },
    {
      "from": "00fdaecc"
    },
    {
      "from": "010095e9"
    },
    {
      "from": "00fdbf21"
    },
    {
      "from": "00fdd4f5"
    },
    {
      "from": "00fded41"
    },
    {
      "from": "00fded4c"
    },
    {
      "from": "00fdef63"
    },
    {
      "from": "00fdef78"
    },
    {
      "from": "01069ad8"
    },
    {
      "from": "01069c1e"
    },
    {
      "from": "01069d3b"
    },
    {
      "from": "01069fcc"
    },
    {
      "from": "01069fd4"
    },
    {
      "from": "00ffaf3c"
    },
    {
      "from": "00fff6e9"
    },
    {
      "from": "01005664"
    },
    {
      "from": "01005736"
    },
    {
      "from": "01009ef1"
    },
    {
      "from": "01042330"
    },
    {
      "from": "0104235f"
    },
    {
      "from": "0100b443"
    },
    {
      "from": "010089e7"
    },
    {
      "from": "01038420"
    },
    {
      "from": "01038445"
    },
    {
      "from": "01024796"
    },
    {
      "from": "00bba4bf"
    },
    {
      "from": "0102539a"
    },
    {
      "from": "010253ac"
    },
    {
     
[TRUNCATED]
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
  "files": [],
  "handoffs": [],
  "metadata": []
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
