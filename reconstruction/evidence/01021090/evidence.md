# Evidence 0x01021090

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `577e26ba54b6a8092af630b15b488319161a062964d6bcfcd60c2f173fff9234`

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
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "40e6f12385dba14a0967a57a1966e96a6c4502f03702378237b9f1e308d026de",
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
        "obs-0003"
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
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
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
      "at": "0x01021090",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016dda8c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01021095",
      "count": 1,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x18]",
      "reg": "EAX"
    },
    {
      "at": "0x01021098",
      "form": "RET",
      "id": "obs-0003",
      "imm": null,
      "index": 2,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 3,
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
    "register_class": "pointer_like",
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
    "instructions": 3,
    "syntax": "intel",
    "va": "0x01021090"
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
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "40e6f12385dba14a0967a57a1966e96a6c4502f03702378237b9f1e308d026de",
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
        "obs-0003"
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
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
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
      "at": "0x01021090",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016dda8c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01021095",
      "count": 1,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x18]",
      "reg": "EAX"
    },
    {
      "at": "0x01021098",
      "form": "RET",
      "id": "obs-0003",
      "imm": null,
      "index": 2,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 3,
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
    "register_class": "pointer_like",
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
    "instructions": 3,
    "syntax": "intel",
    "va": "0x01021090"
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
    "va": "0x00ae9f50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aea3d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb3e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aed2c0"
  },
  {
    "name": "FUN_00b1f9d0",
    "reconstructed": false,
    "va": "0x00b1f9d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b68090"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb9eb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbcf00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bcd480"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bcece0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd9a80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bdc8a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bdff50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be2110"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be9b20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf2170"
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
"\nundefined4 FUN_01021090(void)\n\n{\n  return *(undefined4 *)(Simulator__sSpacePlayerData + 0x18);\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 3,
  "instructions": [
    {
      "address": "01021090",
      "instruction": "MOV EAX,[0x016dda8c]"
    },
    {
      "address": "01021095",
      "instruction": "MOV EAX,dword ptr [EAX + 0x18]"
    },
    {
      "address": "01021098",
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
  "original_bytes": 13286,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9f50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aea3d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aed2c0\"\n      },\n      {\n        \"name\": \"FUN_00b1f9d0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b1f9d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b68090\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb9eb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbcf00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bcd480\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bcece0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd9a80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdc8a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdff50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be2110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be9b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf2170\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bfc900\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bfcdd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c309e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c31640\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c322f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c32610\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c341a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c34e70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c34ee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c35810\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c360f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c453b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c45a10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c468b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c469f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c46ab0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c46b80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n 
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
  "body_end": "01021098",
  "body_span_bytes": 9,
  "body_start": "01021090",
  "callees": [],
  "callers": [
    "FUN_01037f20",
    "FUN_00ffa900",
    "FUN_010091d0",
    "FUN_00aeb3e0",
    "FUN_00e2e6e0",
    "FUN_00c8bb00",
    "FUN_01039b00",
    "FUN_00c830f0",
    "FUN_00fdd5a0",
    "FUN_00cc1890",
    "FUN_01037d30",
    "FUN_00c46b80",
    "FUN_00bcd480",
    "FUN_00c453b0",
    "FUN_0106e940",
    "FUN_00c8d060",
    "FUN_00b1f9d0",
    "FUN_00c360f0",
    "FUN_00bfcdd0",
    "FUN_0100a160",
    "FUN_00c5b9c0",
    "FUN_00c76790",
    "FUN_00ffb270",
    "FUN_00c99dc0",
    "FUN_00feb0b0",
    "FUN_00c774b0",
    "FUN_00be2110",
    "FUN_00d92cc0",
    "FUN_010593e0",
    "FUN_00ffb830",
    "FUN_00c95540",
    "FUN_010021a0",
    "FUN_00feb770",
    "FUN_01038300",
    "FUN_01013ba0",
    "FUN_0106ea40",
    "FUN_00dd5160",
    "FUN_00d089d0",
    "FUN_00d05d90",
    "FUN_0102b690",
    "FUN_0102daa0",
    "FUN_01047850",
    "FUN_00d06710",
    "FUN_00c79fa0",
    "FUN_0105b350",
    "FUN_00c309e0",
    "FUN_00c468b0",
    "FUN_01030ef0",
    "FUN_01037f60",
    "FUN_01037dd0",
    "FUN_00cc0700",
    "FUN_0102d1b0",
    "FUN_00c4bc00",
    "FUN_00be9b20",
    "FUN_00c34ee0",
    "FUN_00ffaf20",
    "FUN_00c31640",
    "FUN_00aed2c0",
    "FUN_00c32610",
    "FUN_00bcece0",
    "FUN_00c341a0",
    "FUN_00d009a0",
    "FUN_00d05a20",
    "FUN_01069aa0",
    "FUN_00d06030",
    "FUN_010251e0",
    "FUN_00bdc8a0",
    "FUN_01058c90",
    "FUN_01001700",
    "FUN_0102df20",
    "FUN_00b68090",
    "FUN_01014a80",
    "FUN_00bdff50",
    "FUN_00fe0160",
    "FUN_00c322f0",
    "FUN_00ff6a50",
    "FUN_00ff9100",
    "FUN_00dbfad0",
    "FUN_0100b430",
    "FUN_00d5fb60",
    "FUN_00bfc900",
    "FUN_00bf2170",
    "FUN_00bbcf00",
    "FUN_00c8d000",
    "FUN_00fdade0",
    "FUN_00c34e70",
    "FUN_00c45a10",
    "FUN_00fd9de0",
    "FUN_00ae9f50",
    "FUN_01000dc0",
    "FUN_01023be0",
    "FUN_0104cdb0",
    "FUN_00d064b0",
    "FUN_00e19f60",
    "FUN_00ff5930",
    "FUN_00c46ab0",
    "FUN_01056160",
    "FUN_010468f0",
    "FUN_00c932a0",
    "FUN_00c469f0",
    "FUN_01038410",
    "FUN_00aea3d0",
    "FUN_00c35810",
    "FUN_0103fe90",
    "FUN_010137b0",
    "FUN_00ff7530",
    "FUN_00bd9a80",
    "FUN_00fe9580",
    "FUN_010027b0",
    "FUN_00c705c0",
    "FUN_00bb9eb0",
    "FUN_00e97bf0",
    "FUN_00cfbc10",
    "FUN_0103e6e0",
    "FUN_01037eb0",
    "FUN_01071c20",
    "FUN_01058020",
    "FUN_01037e40",
    "FUN_010129c0"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "01021090",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_01021090",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc21090",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01021090(void)",
  "size_bytes": 9,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01021090",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00c342c7"
    },
    {
      "from": "00fe96bc"
    },
    {
      "from": "00fe99cc"
    },
    {
      "from": "00fe9a80"
    },
    {
      "from": "00fe9aec"
    },
    {
      "from": "00fe9dd4"
    },
    {
      "from": "00fe9dfe"
    },
    {
      "from": "00fea01a"
    },
    {
      "from": "00fea044"
    },
    {
      "from": "00aeb46c"
    },
    {
      "from": "00c35829"
    },
    {
      "from": "00c3591d"
    },
    {
      "from": "00c34f42"
    },
    {
      "from": "00d009b2"
    },
    {
      "from": "00d05cfe"
    },
    {
      "from": "00d05d07"
    },
    {
      "from": "00d05f1c"
    },
    {
      "from": "00d064c7"
    },
    {
      "from": "00d604cd"
    },
    {
      "from": "00bcd48d"
    },
    {
      "from": "00bf221d"
    },
    {
      "from": "00bdc8e5"
    },
    {
      "from": "00bdc8f9"
    },
    {
      "from": "00be2137"
    },
    {
      "from": "00aea10b"
    },
    {
      "from": "00e2e6e4"
    },
    {
      "from": "0102e1eb"
    },
    {
      "from": "0102e4ff"
    },
    {
      "from": "0102e691"
    },
    {
      "from": "0102e6d9"
    },
    {
      "from": "0102ea96"
    },
    {
      "from": "0102eacc"
    },
    {
      "from": "0102eb5a"
    },
    {
      "from": "0102ec45"
    },
    {
      "from": "0102ee42"
    },
    {
      "from": "0102ef3d"
    },
    {
      "from": "0102efd6"
    },
    {
      "from": "00c8bbb1"
    },
    {
      "from": "00c8d00f"
    },
    {
      "from": "010027db"
    },
    {
      "from": "01002965"
    },
    {
      "from": "01001743"
    },
    {
      "from": "0102b697"
    },
    {
      "from": "00c76795"
    },
    {
      "from": "00c705d1"
    },
    {
      "from": "00c32335"
    },
    {
      "from": "0102d21e"
    },
    {
      "from": "0102d709"
    },
    {
      "from": "0102dbe1"
    },
    {
      "from": "01037e45"
    },
    {
      "from": "01037f25"
    },
    {
      "from": "01038307"
    },
    {
      "from": "0103e75d"
    },
    {
      "from": "00aea417"
    },
    {
      "from": "00bbd035"
    },
    {
      "from": "00ffa926"
    },
    {
      "from": "00c34e7c"
    },
    {
      "from": "00c34ea4"
    },
    {
      "from": "00c79fce"
    },
    {
      "from": "0103
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
