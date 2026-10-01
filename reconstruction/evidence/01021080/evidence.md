# Evidence 0x01021080

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `cd807ab82663773ee934b4b22df61a47984db79e5bf92bd037155122db62c5b7`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl-compatible no-argument accessor",
  "return_note": "enum word",
  "return_register": "EAX",
  "return_type": "SpaceContext",
  "return_width_bytes": 4,
  "stack_cleanup_bytes": 0
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
  "content_sha256": "59505ad483685307e74546a2464b5936066fb2b8ff7310c4fad74dc0c1cb7375",
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
    "persisted_calling_convention": "cdecl-compatible no-argument accessor"
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
      "at": "0x01021080",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016dda8c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01021085",
      "count": 1,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x10]",
      "reg": "EAX"
    },
    {
      "at": "0x01021088",
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
    "va": "0x01021080"
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
    "va": "0x00ad23c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00adbca0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae73e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae9c90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb3e0"
  },
  {
    "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
    "reconstructed": true,
    "va": "0x00b28ec0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b33130"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b35300"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b444c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b4a720"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b4c270"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b5ba30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b5ce70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b5e3f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b60110"
  },
  {
    "name": "app_simulator_mode_bridge_00b63510",
    "reconstructed": true,
    "va": "0x00b63510"
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
      "0x00c341a0",
      "0x00c34ee0",
      "0x00c35240",
      "0x00c8d060",
      "0x00c34ee0",
      "0x00c35240",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021300",
      "0x01021300",
      "0x01021960",
      "0x01021960"
    ],
    "conflict_id": "ownership_field_write_order",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
    "resolution_status": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00c34ee0",
      "0x00c34ee0",
      "0x00c35240",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021300",
      "0x01021300",
      "0x01021960",
      "0x01021960",
      "0x01021d40",
      "0x01021d40",
      "0x01021d40"
    ],
    "conflict_id": "planet_ownership_projection",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00b1db60",
      "0x00b5b880",
      "0x00b5b8a0",
      "0x00b5b8c0",
      "0x00b5b8e0",
      "0x00b5b960",
      "0x00b1db60",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021960",
      "0x01021960",
      "0x01021d40"
    ],
    "conflict_id": "simulator_mode_identifier_mapping",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00c38b10",
      "0x00c38b10",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021300",
      "0x01021300",
      "0x01021960",
      "0x01021960",
      "0x01021d40",
      "0x01021d40",
      "0x01021d40",
      "0x01021d40"
    ],
    "conflict_id": "ufo_fleet_movement_state",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
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
  "count": 3,
  "instructions": [
    {
      "address": "01021080",
      "instruction": "MOV EAX,[0x016dda8c]"
    },
    {
      "address": "01021085",
      "instruction": "MOV EAX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "01021088",
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
  "original_bytes": 16324,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl-compatible no-argument accessor\",\n    \"return_note\": \"enum word\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"SpaceContext\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:SpacePlayerDataAccessPrefix\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 24,\n      \"symbol\": \"FUN_01021230\",\n      \"va\": \"0x01021230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:SpacePlayerDataAccessPrefix\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 19,\n      \"symbol\": \"FUN_01021260\",\n      \"va\": \"0x01021260\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:SpacePlayerDataAccessPrefix\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 19,\n      \"symbol\": \"FUN_010212a0\",\n      \"va\": \"0x010212a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d3a0\",\n      \"va\": \"0x00b3d3a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d400\",\n      \"va\": \"0x00b3d400\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cSpaceTrading_Get\",\n      \"va\": \"0x00b3d4d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Direct +0x10 context-word read with no null guard; host prefix is not the complete 0x34-byte object, and runtime publication/lifetime remain unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"SpacePlayerDataAccessPrefix\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad23c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00adbca0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae73e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9c90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb3e0\"\n      },\n      {\n        \"name\": \"ProfilePersistenceBoundary_run_candidate_00b28ec0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b28ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b33130\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b35300\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b444c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b4a720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b4c270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b5ba30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b5ce70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b5e3f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b60110\"\n      },\n      {\n        \"name\": \"app_simulator_mode_bridge_00b63510\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b63510\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6a200\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6baf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b7daf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b80ea0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbc370\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbcf00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbe740\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbfe80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bc1450\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bc2c00\"\n      },\n
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
  "body_end": "01021088",
  "body_span_bytes": 9,
  "body_start": "01021080",
  "callees": [],
  "callers": [
    "FUN_00c341a0",
    "FUN_00c86c70",
    "FUN_01066230",
    "FUN_00b63510",
    "FUN_01048ce0",
    "FUN_00c8cb20",
    "FUN_00c56170",
    "FUN_00c830f0",
    "FUN_01056d30",
    "FUN_00c4dd10",
    "FUN_00e00a40",
    "FUN_010251e0",
    "FUN_00dd7970",
    "FUN_00c82f00",
    "FUN_00c85380",
    "FUN_0106a7b0",
    "FUN_00c4fa40",
    "FUN_00e9a940",
    "FUN_00ad23c0",
    "FUN_00c4ccd0",
    "FUN_00c51bb0",
    "FUN_01001cd0",
    "FUN_00b35300",
    "FUN_00bbc370",
    "FUN_00fe3b30",
    "FUN_00c84950",
    "FUN_01050bb0",
    "FUN_0102d1b0",
    "FUN_00c382e0",
    "FUN_00b444c0",
    "FUN_00bc1450",
    "FUN_00fd9d30",
    "FUN_0104cb70",
    "FUN_00c61390",
    "FUN_00c54f90",
    "FUN_00fda9f0",
    "FUN_01044b70",
    "FUN_00c3ae70",
    "FUN_00bbcf00",
    "FUN_00c84620",
    "FUN_00c4ea70",
    "FUN_01017790",
    "FUN_00e9cf30",
    "FUN_00c634a0",
    "FUN_00c38900",
    "FUN_00e998d0",
    "FUN_0106b310",
    "FUN_00c5eed0",
    "FUN_00b80ea0",
    "FUN_00adbca0",
    "FUN_00c8c9d0",
    "FUN_01000eb0",
    "FUN_01004e50",
    "FUN_00c810e0",
    "FUN_00c53720",
    "FUN_010743a0",
    "FUN_00cc22c0",
    "FUN_00c84d60",
    "FUN_0102c720",
    "FUN_00c635c0",
    "FUN_00cbb840",
    "FUN_00c4f220",
    "FUN_0102aa50",
    "FUN_00b60110",
    "FUN_00fda1f0",
    "FUN_00c3ad40",
    "FUN_00c774b0",
    "FUN_00e02f00",
    "FUN_00c5f690",
    "FUN_0106cc70",
    "FUN_01003c60",
    "FUN_00c55ca0",
    "FUN_010361c0",
    "FUN_01038410",
    "FUN_00c3c520",
    "FUN_00e0e1a0",
    "FUN_00bbfe80",
    "FUN_00fea510",
    "FUN_00c5efb0",
    "FUN_010053c0",
    "FUN_00b5ce70",
    "FUN_00b4a720",
    "FUN_00c3dae0",
    "FUN_0106c930",
    "FUN_00e97bf0",
    "FUN_010377f0",
    "FUN_0104cdb0",
    "FUN_00fe9580",
    "FUN_00e98db0",
    "FUN_00c5b6c0",
    "FUN_00c5fd90",
    "FUN_01001700",
    "FUN_00b28ec0",
    "FUN_00b6a200",
    "FUN_00e99c50",
    "FUN_00fdbd60",
    "FUN_0100d230",
    "FUN_00be4c00",
    "FUN_00c43e40",
    "FUN_00cb8760",
    "FUN_010030c0",
    "FUN_00c5b150",
    "FUN_010033a0",
    "FUN_00c737a0",
    "FUN_01004c80",
    "FUN_0100d2a0",
    "FUN_00fe3b10",
    "FUN_00fe0f40",
    "FUN_00b6baf0",
    "FUN_00c478b0",
    "FUN_01045200",
    "FUN_00fdc800",
    "FUN_00ffe860",
    "FUN_01043a50",
    "FUN_0101b160",
    "FUN_010593e0",
    "FUN_01062ce0",
    "FUN_01048f00",
    "FUN_01043860",
    "FUN_00c50940",
    "FUN_01003490",
    "FUN_00b5ba30",
    "FUN_00ae9c90",
    "FUN_00e0b990",
    "FUN_00c51b10",
    "FUN_00bc2c00",
    "FUN_00fffdd0",
    "FUN_00e97350",
    "FUN_0106ac90",
    "FUN_00bbe740",
    "FUN_00c61070",
    "FUN_0101a330",
    "FUN_00e99550",
    "FUN_0105f2d0",
    "FUN_00fff8e0",
    "FUN_0102df20",
    "FUN_00c70150",
    "FUN_00ffcab0",
    "FUN_00c5fe00",
    "FUN_00bc2f00",
    "FUN_00aeb3e0",
    "FUN_00e9c7f0",
    "FUN_0105f760",
    "FUN_0102b1d0",
    "FUN_0101b530",
    "FUN_00c631f0",
    "FUN_00e07540",
    "FUN_00c560c0",
    "FUN_00b7daf0",
    "FUN_00c3dba0",
    "FUN_00bc2f70",
    "FUN_00c8d060",
    "FUN_00b5e3f0",
    "FUN_01048d10",
    "FUN_00dd8640",
    "FUN_01072d40",
    "FUN_00c86390",
    "FUN_00c83050",
    "FUN_010027b0",
    "FUN_00e98500",
    "FUN_01044a10",
    "FUN_00ae73e0",
    "FUN_00b4c270",
    "FUN_00c4a6b0",
    "FUN_00b33130",
    "FUN_010229d0",
    "FUN_01049040",
    "FUN_01034880",
    "FUN_00c5da10",
    "FUN_00e07e70",
    "FUN_00da5d60",
    "FUN_01003df0",
    "FUN_00c31550",
    "FUN_00c8ce40",
    "FUN_00fd9d90"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "01021080",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_01021080",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc21080",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01021080(void)",
  "size_bytes": 9,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01021080",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00b291ec"
    },
    {
      "from": "00c34267"
    },
    {
      "from": "00c73866"
    },
    {
      "from": "00fe9704"
    },
    {
      "from": "00fe9877"
    },
    {
      "from": "00fe9be0"
    },
    {
      "from": "00fe9cc8"
    },
    {
      "from": "00aeb43d"
    },
    {
      "from": "00aeb446"
    },
    {
      "from": "00c3157b"
    },
    {
      "from": "00c701fc"
    },
    {
      "from": "00dd8abc"
    },
    {
      "from": "01045276"
    },
    {
      "from": "00fe3b45"
    },
    {
      "from": "00b444cf"
    },
    {
      "from": "00ad2484"
    },
    {
      "from": "00dd7d43"
    },
    {
      "from": "00fe3b10"
    },
    {
      "from": "0102e47b"
    },
    {
      "from": "01048ce3"
    },
    {
      "from": "00c8ca0d"
    },
    {
      "from": "00c8cf60"
    },
    {
      "from": "00c8cb6b"
    },
    {
      "from": "01002987"
    },
    {
      "from": "010018ff"
    },
    {
      "from": "0102b1d6"
    },
    {
      "from": "00c3dae3"
    },
    {
      "from": "00c3dba9"
    },
    {
      "from": "00fffddb"
    },
    {
      "from": "0102d37c"
    },
    {
 
[TRUNCATED]
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:Simulator::sSpacePlayerData at 0x016dda8c"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg01_roots/space_player_data_accessors.cpp",
  "files": [
    "src/reconstruction/pkg01_roots/space_player_data_accessors.cpp",
    "src/reconstruction/pkg01_roots/space_player_data_accessors.hpp",
    "src/reconstruction/pkg01_roots/space_player_data_accessors_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-pkg01-roots/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg01-roots/01021080.json"
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
    "No trace establishes when the published global is valid during initialization or teardown.",
    "Static evidence does not establish runtime context-transition ordering.",
    "Whole-object finalization for Simulator::sSpacePlayerData remains unresolved; this accessor does not establish ownership.",
    "gate-space-player-data-publication"
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
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "SpaceContext enum word",
  "SpaceContextValue",
  "SpacePlayerDataAccessPrefix"
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
      "0x00c341a0",
      "0x00c34ee0",
      "0x00c35240",
      "0x00c8d060",
      "0x00c34ee0",
      "0x00c35240",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021300",
      "0x01021300",
      "0x01021960",
      "0x01021960"
    ],
    "conflict_id": "ownership_field_write_order",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
    "resolution_status": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00c34ee0",
      "0x00c34ee0",
      "0x00c35240",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021300",
      "0x01021300",
      "0x01021960",
      "0x01021960",
      "0x01021d40",
      "0x01021d40",
      "0x01021d40"
    ],
    "conflict_id": "planet_ownership_projection",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00b1db60",
      "0x00b5b880",
      "0x00b5b8a0",
      "0x00b5b8c0",
      "0x00b5b8e0",
      "0x00b5b960",
      "0x00b1db60",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021960",
      "0x01021960",
      "0x01021d40"
    ],
    "conflict_id": "simulator_mode_identifier_mapping",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00c38b10",
      "0x00c38b10",
      "0x00c3ae70",
      "0x00c3dae0",
      "0x01001360",
      "0x01001360",
      "0x01021080",
      "0x01021080",
      "0x01021300",
      "0x01021300",
      "0x01021960",
      "0x01021960",
      "0x01021d40",
      "0x01021d40",
      "0x01021d40",
      "0x01021d40"
    ],
    "conflict_id": "ufo_fleet_movement_state",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
