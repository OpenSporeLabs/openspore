# Evidence 0x00b3d4f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9f5c6c50bd57276acb2e11f8fa7ba97071e743c63d23ace3d9167e73d697244e`

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
  "content_sha256": "414a09c2a4bc5f0dad599651159453d0a5a99699264afb8a2fb855a43ce74282",
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
        "obs-0002"
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
        "obs-0002"
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
        "obs-0002"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0002"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0002"
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
      "at": "0x00b3d4f0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eb64]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d4f5",
      "form": "RET",
      "id": "obs-0002",
      "imm": null,
      "index": 1,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 2,
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
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00b3d4f0"
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
  "content_sha256": "414a09c2a4bc5f0dad599651159453d0a5a99699264afb8a2fb855a43ce74282",
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
        "obs-0002"
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
        "obs-0002"
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
        "obs-0002"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0002"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0002"
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
      "at": "0x00b3d4f0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eb64]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d4f5",
      "form": "RET",
      "id": "obs-0002",
      "imm": null,
      "index": 1,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 2,
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
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00b3d4f0"
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
    "va": "0x00b335d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba4f30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c73cf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c73f80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c73ff0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c74210"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c74280"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c74470"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c74550"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c74690"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cd1960"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cd6800"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cd6980"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cde660"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ce8ab0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cf50e0"
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
  "count": 2,
  "instructions": [
    {
      "address": "00b3d4f0",
      "instruction": "MOV EAX,[0x0167eb64]"
    },
    {
      "address": "00b3d4f5",
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
  "original_bytes": 19558,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:32-bit pointer slot\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 17,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:32-bit pointer slot\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 17,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d3a0\",\n      \"va\": \"0x00b3d3a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d400\",\n      \"va\": \"0x00b3d400\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cSpaceTrading_Get\",\n      \"va\": \"0x00b3d4d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00ff3f00\",\n      \"va\": \"0x00ff3f00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_01021080\",\n      \"va\": \"0x01021080\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_01021230\",\n      \"va\": \"0x01021230\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Simulator_GetUIMissionLogManager is alias-unresolved; the mechanically clean body is not evidence of cMissionManager.\",\n  \"audit_findings\": [\n    \"P2-001\"\n  ],\n  \"audit_status\": \"mechanically_clean_with_p2_alias_boundary\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueUIMissionLogManager\",\n  \"cluster\": \"gameglobal-misc\",\n  \"confidence\": 0.75,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b335d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba4f30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c73cf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c73f80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c73ff0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c74210\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c74280\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c74470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c74550\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c74690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd1960\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd6800\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd6980\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cde660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ce8ab0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cf50e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cf7ad0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cfa990\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd2e80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dd30d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e82dc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e82de0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b3372b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b335d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba50f8\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba4f30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c73db7\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c73cf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c73e66\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c73cf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c73fd2\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c73f80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c74143\",\n        \"direc
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
  "body_end": "00b3d4f5",
  "body_span_bytes": 6,
  "body_start": "00b3d4f0",
  "callees": [],
  "callers": [
    "FUN_00dd30d0",
    "FUN_00e82de0",
    "FUN_00e82dc0",
    "FUN_00ce8ab0",
    "FUN_00c74550",
    "FUN_00ba4f30",
    "FUN_00c74210",
    "FUN_00dd2e80",
    "FUN_00cd6980",
    "FUN_00c73ff0",
    "FUN_00cf7ad0",
    "FUN_00cd1960",
    "FUN_00c73f80",
    "FUN_00cd6800",
    "FUN_00c73cf0",
    "FUN_00c74280",
    "FUN_00cde660",
    "FUN_00cf50e0",
    "FUN_00c74470",
    "FUN_00cfa990",
    "FUN_00b335d0",
    "FUN_00c74690"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b3d4f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Simulator_GetUIMissionLogManager",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x73d4f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined Simulator_GetUIMissionLogManager(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d4f0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 38,
  "xrefs": [
    {
      "from": "00c74580"
    },
    {
      "from": "00dd2f97"
    },
    {
      "from": "00dd3120"
    },
    {
      "from": "00b3372b"
    },
    {
      "from": "00ba50f8"
    },
    {
      "from": "00c74711"
    },
    {
      "from": "00c73db7"
    },
    {
      "from": "00c73e66"
    },
    {
      "from": "00c74143"
    },
    {
      "from": "00c743b2"
    },
    {
      "from": "00cd6d31"
    },
    {
      "from": "00cd1a78"
    },
    {
      "from": "00cd1b9c"
    },
    {
      "from": "00cd6888"
    },
    {
      "from": "00ce8c10"
    },
    {
      "from": "00cf51d9"
    },
    {
      "from": "00cf5258"
    },
    {
      "from": "00cf52f3"
    },
    {
      "from": "00cf537a"
    },
    {
      "from": "00cf53ff"
    },
    {
      "from": "00cf5484"
    },
    {
      "from": "00cf551f"
    },
    {
      "from": "00cf7b18"
    },
    {
      "from": "00cf7b23"
    },
    {
      "from": "00cf7b2f"
    },
    {
      "from": "00e82de0"
    },
    {
      "from": "00c73fd2"
    },
    {
      "from": "00c744c2"
    },
    {
      "from": "00c74262"
    },
    {
      "from": "00cfaa4d"
    },
    {
      "from": "00cde785"
    },
    {
      "from": "00cdf13f"
    },
    {
      "from": "00cfe0b7"
    },
    {
      "from": "00cf6e01"
    },
    {
      "from": "00cf6e12"
    },
    {
      "from": "00cf6e1e"
    },
    {
      "from": "00cfa395"
    },
    {
      "from": "00e82dc5"
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
  "file": "src/reconstruction/pkg01_roots/pkg01_roots.cpp",
  "files": [
    "src/reconstruction/pkg01_roots/pkg01_roots.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg01-roots/00b3d4f0.json"
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
    "observe_global_slot_0167eb64"
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 7142,
  "preview": "{\n  \"category\": \"GAMEPLAY_LOGIC\",\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"identity\": 0.72,\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 22,\n  \"evidence\": [\n    {\n      \"kind\": \"disassembly\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b3d4f0\",\n      \"statement\": \"The complete function is MOV EAX,[0x0167eb64]; RET with no branches, calls, writes, or stack arguments.\"\n    },\n    {\n      \"kind\": \"decompilation\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b3d4f0\",\n      \"statement\": \"Targeted pseudocode returns DAT_0167eb64 directly.\"\n    },\n    {\n      \"kind\": \"direct_consumer\",\n      \"source\": \"ghidra://SporeApp.exe@0x00e82de0\",\n      \"statement\": \"The consumer loads the accessor result, dereferences its vtable, and calls slot +0x38 with two arguments.\"\n    },\n    {\n      \"kind\": \"downstream_helper\",\n      \"source\": \"ghidra://SporeApp.exe@0x00e30d20\",\n      \"statement\": \"The helper uses manager fields at +0x3c, +0x40, and +0x44 as vector-like storage and adds UI/AssetDiscoveryCard entries.\"\n    },\n    {\n      \"kind\": \"sibling_accessors\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b3d400,0x00b3d480,0x00b3d4d0,0x00b3d510\",\n      \"statement\": \"Adjacent accessors read neighboring global slots, establishing a direct global service block.\"\n    },\n    {\n      \"kind\": \"repository\",\n      \"source\": \"knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json:182-190\",\n      \"statement\": \"The mission-root overlay records the same address/global/return contract with SUPPORTED evidence and explicitly says the SDK/triage label is not a full manager layout.\"\n    },\n    {\n      \"kind\": \"SDK_related\",\n      \"source\": \"/home/juanr/apps/Spore-ModAPI/Spore ModAPI/Spore/Simulator/cMissionManager.h:33-53,100-140\",\n      \"statement\": \"cMissionManager is a separate 0x144-byte saved-game manager type; the source does not establish that this accessor returns it.\"\n    }\n  ],\n  \"family\": \"read-only global accessor for a UI mission-log manager handle\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": {\n      \"count\": 0,\n      \"items\": [],\n      \"status\": \"leaf\"\n    },\n    \"direct_callers\": {\n      \"canonical\": {\n        \"direct_call_references\": 32,\n        \"fan_out_external\": 0,\n        \"fan_out_internal\": 0,\n        \"gameplay_fan_in\": 0,\n        \"global_fan_in\": 4,\n        \"unique_direct_caller_functions\": 22\n      },\n      \"read_only_ghidra\": {\n        \"direct_call_xrefs\": 38,\n        \"unique_direct_caller_functions\": 22\n      },\n      \"representative\": [\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"use\",\n            \"va\"\n          ]\n        }\n      ]\n    },\n    \"globals\": [\n      {\n        \"access\": \"read\",\n        \"address\": \"0x0167eb64\",\n        \"meaning\": \"opaque UI mission-log manager pointer/handle\",\n        \"name\": \"DAT_0167eb64\",\n        \"writer_status\": \"No direct writer xref was established in the targeted scan; absence is not proof of no computed or bulk publication.\",\n        \"xref_observation\": \"Targeted Ghidra xrefs to the slot found one read at 0x00b3d4f0; raw image bytes at the slot are zero.\"\n      }\n    ],\n    \"structures\": [\n      {\n        \"fields\": [\n          \"vtable at +0x00\",\n          \"vector-like begin/end/capacity observed at +0x3c/+0x40/+0x44 by 0x00e30d20\",\n          \"virtual operation at +0x38 by 0x00e82de0\"\n        ],\n        \"name\": \"unknown UI mission-log manager\",\n        \"status\": \"consumer-inferred opaque object\"\n      },\n      {\n        \"name\": \"Simulator::cMissionManager\",\n        \"reason\": \"SDK defines a separate mission manager with tracked missions at +0xa8; its SDK Get mapping is an interior address of another Ghidra function and does not prove this global is cMissionManager.\",\n        \"size\": \"0x144\",\n        \"status\": \"related but not equated\"\n      }\n    ],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": [],\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [],\n      \"ordering\": [],\n      \"outputs\": [],\n      \"postconditions\": [\n        \"DAT_0167eb64 is read exactly once.\",\n        \"No global, manager, or caller state is modified by the accessor.\",\n        \"No call, lock, allocation, or reference-count operation occurs.\"\n      ],\n      \"preconditions\": [\n        \"The global slot is readable.\",\n        \"For consumers that dereference the result, the slot contains a live manager at the time of use.\"\n      ],\n      \"purpose\": \"read-only global accessor for a UI mission-log manager handle\",\n      \"return\": {\n        \"null_behavior\": \"The accessor itself has no null guard; consumer safety depends on publication/lifetime outside this function.\",\n        \"type\": \"opaque uint32_t\",\n        \"value\": \"Current value of DAT_0167eb64; consumers treat it as a pointer to a vtable-bearing UI mission-log manager.\"\n      },\n      \"side_effects\": {\n        \"consumer_effects\": \"Consumers may add UI mission-log entries, 
[TRUNCATED]
```

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "32-bit pointer slot",
  "OpaqueUIMissionLogManager"
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
