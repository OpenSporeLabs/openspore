# Evidence 0x00b3d2a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9b888700649ab2c6fe07466d050f51d84cf64ca3b4a09d526a2b9366d3cca32a`

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
  "content_sha256": "cc6293a288da6da5da475c8010960a1c472a9b5a3df1ea00dadad13c444cbd4d",
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
      "at": "0x00b3d2a0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eae4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d2a5",
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
    "va": "0x00b3d2a0"
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
  "content_sha256": "cc6293a288da6da5da475c8010960a1c472a9b5a3df1ea00dadad13c444cbd4d",
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
      "at": "0x00b3d2a0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eae4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d2a5",
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
    "va": "0x00b3d2a0"
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
    "va": "0x00ae9040"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae9500"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae9590"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae9930"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae9f50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb3e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aebe90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aecf90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aed2c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b20790"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b26790"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b279e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b28070"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b28850"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b28da0"
  },
  {
    "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
    "reconstructed": true,
    "va": "0x00b28ec0"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00b3d300",
      "0x00b3d400",
      "0x00b3d2a0",
      "0x00b3d3a0",
      "0x00b5b800",
      "0xffffffff",
      "0x00b3d300",
      "0x00b3d2a0",
      "0x00b3d400",
      "0x00b3d3a0",
      "0x00b5b800"
    ],
    "conflict_id": "CF-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": null,
    "resolution_status": null,
    "source": "knowledgegraph/research/conflicts/track-f-cross-domain-impact.json",
    "subject": null,
    "unresolved_reason": {
      "missing_evidence": [
        "Direct or indirect publisher and teardown evidence for both alternate/canonical manager slot pairs.",
        "Pointer-equality checks across mode and service lifecycle boundaries.",
        "The concrete receiver class and physical storage type behind DAT_0167eaec and forwarded_object+0x20."
      ],
      "status": "blocked"
    }
  },
  {
    "anchors": [
      "0x00b3d440",
      "0x00b3d2a0",
      "0x00b3d440",
      "0x00b3d2a0",
      "0x00b3d2a0",
      "0x00b3d440",
      "0x00b3d440",
      "0x00b3d2a0",
      "0x00b3d2a0",
      "0x00b3d2a0",
      "0x00b3d440",
      "0x00b3d2a0",
      "0x00b3d2a0",
      "0x00b3d440",
      "0x00c7f060",
      "0x00b32b20"
    ],
    "conflict_id": "NM-011",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_OBSERVED",
    "resolution_status": "RESOLVED_OBSERVED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x00B3D2A0 versus 0x00B3D440 accessor identity",
    "unresolved_reason": "The exact type and contract of 0x00B3D2A0 remain unknown; the version-skew alias hypothesis and the GOG persistence-manager identity are resolved."
  },
  {
    "anchors": [
      "0x00b3d2a0",
      "0x00b3d300",
      "0x00b5b800",
      "0x01021300",
      "0x01021300",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9590",
      "0x00ae9930",
      "0x00ae9c90",
      "0x00ae9f50",
      "0x00aeb3e0",
      "0x00aeb3e0",
      "0x00aebe90",
      "0x00b25fb0"
    ],
    "conflict_id": "global_root_identities",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
      "address": "00b3d2a0",
      "instruction": "MOV EAX,[0x0167eae4]"
    },
    {
      "address": "00b3d2a5",
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
  "original_bytes": 22107,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:32-bit pointer slot\",\n        \"same_semantic_family\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 22,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:32-bit pointer slot\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 17,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 9,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d3a0\",\n      \"va\": \"0x00b3d3a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d400\",\n      \"va\": \"0x00b3d400\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cSpaceTrading_Get\",\n      \"va\": \"0x00b3d4d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueStarManager\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_LookupEmpireByPoliticalId\",\n      \"va\": \"0x00ba9370\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueStarManager\"\n      ],\n      \"package\": \"PKG-14-A2-WORLD-LIFECYCLE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"star_regenerate_00bb4af0\",\n      \"va\": \"0x00bb4af0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Alternate star-root accessor only; distinct from 0x00b3d3a0; publication, equality, and lifetime remain unresolved.\",\n  \"audit_findings\": [\n    \"P1-002\"\n  ],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueStarManager\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": 0.75,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9500\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9590\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9930\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9f50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebe90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aecf90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aed2c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b20790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b26790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b279e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b28070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b28850\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b28da0\"\n      },\n      {\n        \"name\": \"ProfilePersistenceBoundary_run_candidate_00b28ec0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b28ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b294c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32ce0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b32f60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b338f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b60d80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b677e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6baf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6cc50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b76160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b8d8f0\"\n      },\n      {\n
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
  "body_end": "00b3d2a5",
  "body_span_bytes": 6,
  "body_start": "00b3d2a0",
  "callees": [],
  "callers": [
    "FUN_00e34bd0",
    "FUN_00c341a0",
    "FUN_00bd9a80",
    "FUN_00c32610",
    "FUN_00c5f770",
    "FUN_00ae9040",
    "FUN_01013ba0",
    "FUN_00c7bd40",
    "FUN_01047440",
    "FUN_00c34ee0",
    "FUN_00d06920",
    "FUN_01008910",
    "FUN_00c774b0",
    "FUN_00df7ce0",
    "FUN_00fde230",
    "FUN_00cfa410",
    "FUN_00c322f0",
    "FUN_00bd2310",
    "FUN_00b6cc50",
    "FUN_01046160",
    "FUN_010129c0",
    "FUN_00c71e30",
    "FUN_00c5f54b",
    "FUN_00c31550",
    "FUN_00c7f5b0",
    "FUN_010137b0",
    "FUN_010221f0",
    "FUN_00bbe470",
    "FUN_00c5b280",
    "FUN_00c359a0",
    "FUN_00c72030",
    "FUN_00d05d90",
    "FUN_00b677e0",
    "FUN_00c474b0",
    "FUN_00c326b0",
    "FUN_0103eff0",
    "FUN_00df66e0",
    "FUN_00dd0550",
    "FUN_010095e0",
    "FUN_0100d2a0",
    "FUN_01021ab0",
    "FUN_01003df0",
    "FUN_00c317a0",
    "FUN_01065f00",
    "FUN_00fe9580",
    "FUN_0102acb0",
    "FUN_00c75520",
    "FUN_00b26790",
    "FUN_00aeb3e0",
    "FUN_01072d40",
    "FUN_00de4610",
    "FUN_01006a40",
    "FUN_010021a0",
    "FUN_00aecf90",
    "FUN_00d06030",
    "FUN_00c47180",
    "FUN_01014a80",
    "FUN_0100fb00",
    "FUN_00bf8170",
    "FUN_00bb21b0",
    "FUN_00df47b0",
    "FUN_010673f0",
    "FUN_00ff8ad0",
    "FUN_00bb8b20",
    "FUN_00de3130",
    "FUN_00fdf5f0",
    "FUN_00df95d0",
    "FUN_00ffa780",
    "FUN_01023be0",
    "FUN_00c30c10",
    "FUN_0100b430",
    "FUN_00fe7100",
    "FUN_01076b80",
    "FUN_01045200",
    "FUN_00bbaa80",
    "FUN_00feed30",
    "FUN_00ae9500",
    "FUN_00c784c0",
    "FUN_00c70b50",
    "FUN_00d05a20",
    "FUN_00c35240",
    "FUN_00c86760",
    "FUN_00c737a0",
    "FUN_010053c0",
    "FUN_00c8ce40",
    "FUN_00b28ec0",
    "FUN_00c72c60",
    "FUN_01044b00",
    "FUN_01067510",
    "FUN_01029a10",
    "FUN_01029a60",
    "FUN_00c76800",
    "FUN_00df7f60",
    "FUN_00c309e0",
    "FUN_010309c0",
    "FUN_00ba6bb0",
    "FUN_00e39ab0",
    "FUN_00c4a220",
    "FUN_00c8be70",
    "FUN_00fea510",
    "FUN_010251e0",
    "FUN_00b96d40",
    "FUN_01005180",
    "FUN_010593e0",
    "FUN_00c59540",
    "FUN_00c33690",
    "FUN_00bd15a0",
    "FUN_00bbac80",
    "FUN_01069aa0",
    "FUN_00c47e20",
    "FUN_00b76160",
    "FUN_00def400",
    "FUN_01022150",
    "FUN_01013a70",
    "FUN_0102daa0",
    "FUN_010103f0",
    "FUN_00c5b6c0",
    "FUN_00dd15a0",
    "FUN_00fdeac0",
    "FUN_01039b00",
    "FUN_00c35810",
    "FUN_00ba0080",
    "FUN_00b8e090",
    "FUN_00c30c80",
    "FUN_00e83430",
    "FUN_01030a30",
    "FUN_00fe6b20",
    "FUN_01056160",
    "FUN_00c4b250",
    "FUN_01042080",
    "FUN_00de9ec0",
    "FUN_0106dd10",
    "FUN_00b279e0",
    "FUN_010468f0",
    "FUN_00dd0e10",
    "FUN_00d5ccf0",
    "FUN_0102ce30",
    "FUN_00b28070",
    "FUN_01058c90",
    "FUN_00dd4b20",
    "FUN_0102cc30",
    "FUN_01029950",
    "FUN_00aebe90",
    "FUN_010027b0",
    "FUN_00ff5930",
    "FUN_00b32b20",
    "FUN_00c316c0",
    "FUN_0103a7d0",
    "FUN_00c3a2b0",
    "FUN_00c451e0",
    "FUN_00e06d90",
    "FUN_00dd4950",
    "FUN_00c37a90",
    "FUN_0102ba30",
    "FUN_0100a160",
    "FUN_00c4bc00",
    "FUN_00c308b0",
    "FUN_00cdd500",
    "FUN_01000eb0",
    "FUN_00ffc7f0",
    "FUN_00c1a3c0",
    "FUN_0100dd40",
    "FUN_0101246a",
    "FUN_00ff34c0",
    "FUN_01021300",
    "FUN_01012b50",
    "FUN_010091d0",
    "FUN_00ff6a50",
    "FUN_00c32cd0",
    "FUN_01014870",
    "FUN_01038410",
    "FUN_01014540",
    "FUN_00aed2c0",
    "FUN_010225d0",
    "FUN_00b20790",
    "FUN_00dd2650",
    "FUN_00c73680",
    "FUN_00ff06a0",
    "FUN_00c47140",
    "FUN_0103dee0",
    "FUN_01001360",
    "FUN_00c5c470",
    "FUN_00c59240",
    "FUN_00b32f60",
    "FUN_010107b0",
    "FUN_00fdd4f0",
    "FUN_00e9a940",
    "FUN_0102c980",
    "FUN_00c72370",
    "FUN_01030930",
    "FUN_010463b0",
    "FUN_00c30c60",
    "FUN_00b294c0",
    "FUN_00c70e20",
    "FUN_00c8e4f0",
    "FUN_00cfbc10",
    "FUN_00bb5d80",
    "FUN_00fdd5a0",
    "FUN_0102c1a0",
    "FUN_00c5b340",
    "FUN_00b60d80",
    "FUN_01070890",
    "FUN_00b8d8f0",
    "FUN_0106c930",
    "FUN_0106cc70",
    "FUN_00ae9590",
    "FUN_01003690",
    "FUN_00c4b220",
    "FUN_00b28da0",
    "FUN_00b338f0",
    "FUN_00b32ce0",
    "FUN_00b33350",
    "FUN_00c5c860",
    "FUN_00b32dd0",
    "FUN_00c4a850",
    "FUN_00fe2ab0",
    "FUN_01011120",
    "FUN_00c75d70",
    "FUN_0100e780",
    "FUN_0102c600",
    "FUN_01047850",
    "FUN_00b6baf0",
    "FUN_00c33cc0",
    "FUN_00ae9f50",
    "FUN_00bae130",
    "FUN_00de8760",
    "FUN_00d4c1b0",
    "FUN_00c33580",
    "FUN_010133c0",
    "FUN_01037c30",
    "FUN_00feb770",
    "FUN_00c62ff0",
    "FUN_00c35320",
    "FUN_00dd2820",
    "FUN_01047000",
    "FUN_0100aec0",
    "FUN_010677b0",
    "FUN_00d015d0",
    "FUN_00fed640",
    "FUN_00c452a0",
    "FUN_00c79fa0",
    "FUN_00d03d70",
    "FUN_010407d0",
    "FUN_00d1c610",
    "FUN_00fdc240",
    "FUN_00ae9930",
    "FUN_00fefcd0",
    "FUN_00ff0700",
    "FUN_00c72190",
    "FUN_00c34320",
    "FUN_00e3cf60",
    "FUN_00c4b2b0",
    "FUN_00b9a8d0",
    "FUN_00c31240",
    "FUN_010219b0",
    "FUN_00fe6dc0",
    "FUN_00c6fe50",
    "FUN_00fdade0",
    "FUN_0100f3e0",
    "FUN_00b8dd60",
    "FUN_00fe8c50",
    "FUN_00c75940",
    "FUN_00c7ada0",
    "FUN_00bbe5f0",
    "FUN_00c57d00",
    "FUN_00c754e0",
    "FUN_00de6f20",
    "FUN_00b8de30",
    "FUN_0100fbc0",
    "FUN_00fe8f70",
    "FUN_01022580",
    "FUN_0105eb90",
    "FUN_0102cd90",
    "FUN_00c31730",
    "FUN_00b28850",
    "FUN_0102d0b0",
    "FUN_00ffabc0",
    "FUN_00fe6e40",
    "FUN_00e2d6a0",
    "FUN_00c314a0",
    "FUN_00c706d0",
    "FUN_00c37cc0",
    "FUN_01037f60",
    "FUN_00fdabf0",
    "FUN_01030aa0",
    "FUN_01048f00",
    "FUN_00bb24d0",
    "FUN_0102df20",
    "FUN_00fe
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
  "file": "src/reconstruction/pkg01_roots/pkg01_roots.cpp",
  "files": [
    "src/reconstruction/pkg01_roots/pkg01_roots.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg01-roots/00b3d2a0.json"
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
    "observe_global_slot_0167eae4"
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
  "original_bytes": 6712,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"mechanics\": 1.0\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 314,\n  \"evidence\": [\n    {\n      \"independence\": \"same-binary disassembly corroborates decompilation\",\n      \"source\": \"Ghidra SporeApp.exe 0x00b3d2a0: MOV EAX,[0x0167eae4]; RET\",\n      \"supports\": \"exact body, no arguments, no branches, no writes\"\n    },\n    {\n      \"independence\": \"independent same-binary field consumers\",\n      \"source\": \"Ghidra SporeApp.exe 0x00ba9370, 0x00b3d2c0, 0x00c4f030, 0x01021300\",\n      \"supports\": \"cStarManager compatibility at mEmpires+0x150 and relationship manager+0x204\"\n    },\n    {\n      \"independence\": \"independent canonical sibling decompilation\",\n      \"source\": \"Ghidra SporeApp.exe 0x00b3d3a0 -> DAT_0167eb0c\",\n      \"supports\": \"target is an alternate path, not the SDK-named canonical cStarManager::Get\"\n    },\n    {\n      \"independence\": \"independent repository static adjudication\",\n      \"source\": \"knowledgegraph/research/noun-star-lifecycle/track-a-root-identity.md:11-19,76-104,118-143\",\n      \"supports\": \"alternate-manager identity, physical separation, bounded publisher negative\"\n    },\n    {\n      \"independence\": \"independent repository architecture decision\",\n      \"source\": \"docs/analysis/architecture-decisions.md:37-43\",\n      \"supports\": \"preserve separate opaque star-root ports until publication and equality are observed\"\n    }\n  ],\n  \"family\": \"alternate/canonical global manager-root accessors\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": {\n      \"direct\": [],\n      \"indirect_callbacks\": []\n    },\n    \"direct_callers\": {\n      \"direct_call_edges\": 510,\n      \"direct_caller_count\": 314,\n      \"downstream_unlock_count\": 314,\n      \"gameplay_caller_count\": 101,\n      \"raw_reader_sibling\": {\n        \"name\": \"FUN_00b3d2c0\",\n        \"role\": \"loads DAT_0167eae4 directly and may return manager+0x204 relationship state\",\n        \"va\": \"0x00b3d2c0\"\n      },\n      \"representative\": [\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        }\n      ]\n    },\n    \"globals\": [\n      {\n        \"field\": \"mEmpires\",\n        \"offset\": \"0x150\",\n        \"structure\": \"cStarManager\",\n        \"type\": \"map<uint32_t, intrusive_ptr<cEmpire>>\"\n      },\n      {\n        \"field\": \"mEmpires end/anchor\",\n        \"offset\": \"0x154\",\n        \"structure\": \"cStarManager\",\n        \"type\": \"map end storage\"\n      },\n      {\n        \"field\": \"mpRelationshipManager\",\n        \"offset\": \"0x204\",\n        \"structure\": \"cStarManager\",\n        \"type\": \"cRelationshipManager *\"\n      },\n      {\n        \"address\": \"0x0167eae4\",\n        \"name\": \"DAT_0167eae4\",\n        \"type\": \"uint32_t pointer slot\"\n      }\n    ],\n    \"structures\": [\n      {\n        \"field\": \"mEmpires\",\n        \"offset\": \"0x150\",\n        \"structure\": \"cStarManager\",\n        \"type\": \"map<uint32_t, intrusive_ptr<cEmpire>>\"\n      },\n      {\n        \"field\": \"mEmpires end/anchor\",\n        \"offset\": \"0x154\",\n        \"structure\": \"cStarManager\",\n        \"type\": \"map end storage\"\n      },\n      {\n        \"field\": \"mpRelationshipManager\",\n        \"offset\": \"0x204\",\n        \"structure\": \"cStarManager\",\n        \"type\": \"cRelationshipManager *\"\n      },\n      {\n        \"address\": \"0x0167eae4\",\n        \"name\": \"DAT_0167eae4\",\n        \"type\": \"uint32_t pointer slot\"\n      }\n    ],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": [],\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [],\n      \"ordering\": [],\n      \"outputs\": [\n        {\n          \"keys\": [\n            \"meaning\",\n            \"name\"\n          ]\n        }\n      ],\n      \"postconditions\": [],\n      \"preconditions\": [],\n      \"purpose\": \"not_reported\",\n      \"return\": {\n        \"on_any_input\": \"raw borrowed cStarManager-compatible pointer or null\",\n        \"ownership_transfer\": false\n      },\n      \"side_effects\": [],\n      \"status\": \"not_reported\",\n      \"unresolved\": [\n        \"What code indirectly publishes, replaces, or clears DAT_0167eae4?\",\n        \"Are DAT_0167eae4 and DAT_0167eb0c value-equal for the full live lifecycle?\",\n        \"Which owner controls the alternate manager's lifetime and teardown?\",\n        \"Can consumers observe a null or stale alternate pointer during mode transition?\"\n      ]\n    }\n  },\n  \"invariants\": {\n    \"failure_semantics\": [],\n    \"invariants\": [\n      \"The function has no branch, validation, fallback, reference operation, lock, or event behavior.\",\n      \"A null, stale, or teardown-time slot value is returned unchanged; dereference safety is entirely a caller/lifecycle invariant.\",\n      \"The alternate and canonical slots are physically distinct; value equality is not an invariant established by this body.\"\n    ],\n    \"invariants_status\": \"reported\"\n  },\n  \"name\": \"FUN_00b3d2a0\",\n  \"package\": {\n    \"caveat\": \"not_reported\",\n    \"ownership_status\": \"not_reported\",\n    \"pri
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
  "OpaqueStarManager"
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
    "anchors": [
      "0x00b3d300",
      "0x00b3d400",
      "0x00b3d2a0",
      "0x00b3d3a0",
      "0x00b5b800",
      "0xffffffff",
      "0x00b3d300",
      "0x00b3d2a0",
      "0x00b3d400",
      "0x00b3d3a0",
      "0x00b5b800"
    ],
    "conflict_id": "CF-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": null,
    "resolution_status": null,
    "source": "knowledgegraph/research/conflicts/track-f-cross-domain-impact.json",
    "subject": null,
    "unresolved_reason": {
      "missing_evidence": [
        "Direct or indirect publisher and teardown evidence for both alternate/canonical manager slot pairs.",
        "Pointer-equality checks across mode and service lifecycle boundaries.",
        "The concrete receiver class and physical storage type behind DAT_0167eaec and forwarded_object+0x20."
      ],
      "status": "blocked"
    }
  },
  {
    "anchors": [
      "0x00b3d440",
      "0x00b3d2a0",
      "0x00b3d440",
      "0x00b3d2a0",
      "0x00b3d2a0",
      "0x00b3d440",
      "0x00b3d440",
      "0x00b3d2a0",
      "0x00b3d2a0",
      "0x00b3d2a0",
      "0x00b3d440",
      "0x00b3d2a0",
      "0x00b3d2a0",
      "0x00b3d440",
      "0x00c7f060",
      "0x00b32b20"
    ],
    "conflict_id": "NM-011",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_OBSERVED",
    "resolution_status": "RESOLVED_OBSERVED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x00B3D2A0 versus 0x00B3D440 accessor identity",
    "unresolved_reason": "The exact type and contract of 0x00B3D2A0 remain unknown; the version-skew alias hypothesis and the GOG persistence-manager identity are resolved."
  },
  {
    "anchors": [
      "0x00b3d2a0",
      "0x00b3d300",
      "0x00b5b800",
      "0x01021300",
      "0x01021300",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9590",
      "0x00ae9930",
      "0x00ae9c90",
      "0x00ae9f50",
      "0x00aeb3e0",
      "0x00aeb3e0",
      "0x00aebe90",
      "0x00b25fb0"
    ],
    "conflict_id": "global_root_identities",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
