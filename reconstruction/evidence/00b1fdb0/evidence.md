# Evidence 0x00b1fdb0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c13d6b2575bf20c09cfea510639b667725cda5212497ffce02944139d698c930`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall-compatible ECX-only machine ABI",
  "hidden_this": "OpaqueNounManager* receiver in ECX",
  "return_register": "EAX",
  "return_semantics": "Returns the opaque 32-bit receiver field word unchanged; no pointer cast, sign extension, truncation, or ownership operation occurs.",
  "return_width_bytes": 4,
  "stack_arguments": [],
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "792d336cdd5dc1d5a156fae9c4d6e36b40f0e2e0bd5623a3b1c8e75492f13612",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall-compatible ECX-only machine ABI"
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
        "obs-0001",
        "obs-0002"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          84
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
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
      "at": "0x00b1fdb0",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x54]",
      "reg": "ECX"
    },
    {
      "at": "0x00b1fdb0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x54]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b1fdb3",
      "form": "RET",
      "id": "obs-0003",
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
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 84,
    "offsets": [
      84
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
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
    "va": "0x00b1fdb0"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_INFERRED"
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
    "va": "0x00b0a6f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b19290"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2dac0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2e940"
  },
  {
    "name": "timing_update_body_00b31cc0",
    "reconstructed": true,
    "va": "0x00b31cc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b7a880"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b96d40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba1590"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba9f80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb1340"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb2330"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb23e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb24d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb3750"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb4100"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb5640"
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
      "0x00845310",
      "0x00b1fdb0",
      "0x00845310",
      "0x00b1fdb0",
      "0x00844f70",
      "0x00841440",
      "0x00846e60",
      "0x00841d40",
      "0x00845790",
      "0x00842d10",
      "0x00844180",
      "0x00843000",
      "0x00845310",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:1",
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
  "count": 2,
  "instructions": [
    {
      "address": "00b1fdb0",
      "instruction": "MOV EAX,dword ptr [ECX + 0x54]"
    },
    {
      "address": "00b1fdb3",
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
  "original_bytes": 15741,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall-compatible ECX-only machine ABI\",\n    \"hidden_this\": \"OpaqueNounManager* receiver in ECX\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"Returns the opaque 32-bit receiver field word unchanged; no pointer cast, sign extension, truncation, or ownership operation occurs.\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueNounManager\"\n      ],\n      \"package\": \"PKG-11-H3-HELPER-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"noun_manager_logical_destroy_00b225d0\",\n      \"va\": \"0x00b225d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueNounManager\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueNounManager\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-CREATURE-TRIBECIV\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel\",\n      \"va\": \"0x00d2e380\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-FRAME-RUNTIME-WAVE8\",\n      \"score\": 3,\n      \"symbol\": \"timing_update_body_00b31cc0\",\n      \"va\": \"0x00b31cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 3,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 3,\n      \"symbol\": \"PoliticalOwnershipScan_00c8d060\",\n      \"va\": \"0x00c8d060\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-C3-CREATURE-PROGRESSION-WAVE2\",\n      \"score\": 3,\n      \"symbol\": \"Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0\",\n      \"va\": \"0x00d2e8a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"Original-process noun-manager availability and field values remain runtime-gated.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueNounManager\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": 0.98,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b0a6f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b19290\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2dac0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2e940\"\n      },\n      {\n        \"name\": \"timing_update_body_00b31cc0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b31cc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b7a880\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b96d40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba1590\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba9f80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb1340\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb2330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb23e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb24d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb3750\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb4100\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb5640\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb80f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbcf00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbe470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbe5f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bc1450\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd9a80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be4c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be9b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bff2d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c027d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c02eb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c04010\"\n      },\n      {\n        \"
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
  "body_end": "00b1fdb3",
  "body_span_bytes": 4,
  "body_start": "00b1fdb0",
  "callees": [],
  "callers": [
    "FUN_00d22300",
    "FUN_00f0a750",
    "FUN_00d3d4f0",
    "FUN_00ffa900",
    "FUN_00d40ff0",
    "FUN_00f19ac0",
    "FUN_00d851ed",
    "FUN_00bd9a80",
    "FUN_00f19660",
    "FUN_00bb80f0",
    "FUN_00d41560",
    "FUN_01008910",
    "FUN_00c774b0",
    "FUN_00fde230",
    "FUN_00d29780",
    "FUN_00f1b820",
    "FUN_00d824a0",
    "FUN_00c44d00",
    "FUN_00d8b910",
    "FUN_00d4a4a0",
    "FUN_00d3af00",
    "FUN_00d2d0b0",
    "FUN_00be4c00",
    "FUN_00f1b450",
    "FUN_00c31550",
    "FUN_00bbcf00",
    "FUN_00c7f5b0",
    "FUN_00ba9f80",
    "FUN_00d40e70",
    "FUN_00d522c0",
    "FUN_00d45530",
    "FUN_00fd9de0",
    "FUN_00bbe470",
    "FUN_00f414b0",
    "FUN_00cc1890",
    "FUN_00d39670",
    "FUN_00c0e8d0",
    "FUN_00d49270",
    "FUN_00d299f0",
    "FUN_00d38cc0",
    "FUN_00d2dd20",
    "FUN_0103eff0",
    "FUN_00c04010",
    "FUN_01003df0",
    "FUN_00d29ca0",
    "FUN_00e0b990",
    "FUN_01065f00",
    "FUN_00fe9580",
    "FUN_01072d40",
    "FUN_010021a0",
    "FUN_0100fb00",
    "FUN_00d3a5a0",
    "FUN_00ff8ad0",
    "FUN_00f1aff0",
    "FUN_00d32df0",
    "FUN_00ffa780",
    "FUN_00d50ef0",
    "FUN_00f1a910",
    "FUN_00c8d060",
    "FUN_00d40cc0",
    "FUN_00d30f60",
    "FUN_01023be0",
    "FUN_0100b430",
    "FUN_00d3fcf0",
    "FUN_01076b80",
    "FUN_00f1f600",
    "FUN_00d52e10",
    "FUN_00c09410",
    "FUN_00f1a440",
    "FUN_00ec2f30",
    "FUN_00c07480",
    "FUN_00d630c0",
    "FUN_00fe6490",
    "FUN_00c70b50",
    "FUN_00c35240",
    "FUN_00c7d090",
    "FUN_00c737a0",
    "FUN_00c8ce40",
    "FUN_00d7df80",
    "FUN_00f0e380",
    "FUN_00bb2330",
    "FUN_00d20f00",
    "FUN_00f0f330",
    "FUN_01067510",
    "FUN_00d342d0",
    "FUN_00f3fd90",
    "FUN_00d25e10",
    "FUN_00d5fb60",
    "FUN_00d466f0",
    "FUN_00d2ffd0",
    "FUN_00d4e4a0",
    "FUN_0103e6e0",
    "FUN_00d4b220",
    "FUN_00f0ac40",
    "FUN_00d4b2f0",
    "FUN_00d512f0",
    "FUN_00fea510",
    "FUN_010251e0",
    "FUN_00b96d40",
    "FUN_01005180",
    "FUN_010593e0",
    "FUN_01049040",
    "FUN_00d4bbd0",
    "FUN_00f1f180",
    "FUN_00be9b20",
    "FUN_01069aa0",
    "FUN_00d35190",
    "Simulator::cCreatureGameData::AddEvolutionPoints",
    "FUN_00d4a930",
    "FUN_00c6d0f0",
    "FUN_00eabf30",
    "FUN_00d2a630",
    "FUN_01060df0",
    "FUN_00d38150",
    "FUN_0102daa0",
    "FUN_00f1a640",
    "FUN_00d2c000",
    "FUN_00c7ae80",
    "FUN_00fdeac0",
    "FUN_00d7b7a0",
    "FUN_01039b00",
    "FUN_00d4c5e0",
    "FUN_00d7e340",
    "FUN_00c0e6a0",
    "FUN_00f1aae0",
    "FUN_01056160",
    "FUN_00d3cdc0",
    "FUN_00d70080",
    "FUN_00d856e0",
    "FUN_00dd0e10",
    "FUN_00c8b5b0",
    "FUN_00f195a0",
    "FUN_00f1d5d0",
    "FUN_01058c90",
    "FUN_00d49920",
    "FUN_00b7a880",
    "FUN_00f43420",
    "FUN_00d6d1d0",
    "FUN_00f20ef0",
    "FUN_00ff5930",
    "FUN_00d30830",
    "FUN_0103a7d0",
    "FUN_00d85f20",
    "FUN_00bb23e0",
    "FUN_00e06d90",
    "FUN_00ffaf20",
    "FUN_00d3c6a0",
    "FUN_0102ba30",
    "FUN_00d38900",
    "FUN_0105b350",
    "FUN_00c4bc00",
    "FUN_00c84d60",
    "FUN_0100dd40",
    "FUN_0101246a",
    "FUN_00d239a0",
    "FUN_01012b50",
    "FUN_010091d0",
    "FUN_00f1faa0",
    "FUN_00d9c020",
    "FUN_00c2a190",
    "FUN_00c32cd0",
    "FUN_00d4f8f0",
    "FUN_00d43e30",
    "FUN_00f43bf0",
    "FUN_00d9bc70",
    "FUN_01014870",
    "FUN_00bb3750",
    "FUN_00ffc4e0",
    "FUN_00d21810",
    "FUN_00d655d0",
    "FUN_01038410",
    "FUN_01014540",
    "FUN_00d2d7d0",
    "FUN_0103dee0",
    "FUN_00d53b50",
    "FUN_00c5c470",
    "FUN_00d9a360",
    "FUN_00d3aea0",
    "FUN_0102aa50",
    "FUN_00d21d90",
    "FUN_00ba1590",
    "FUN_00d7d020",
    "FUN_00d31a70",
    "FUN_00d6fa60",
    "FUN_00d32fd0",
    "FUN_00c2ed20",
    "FUN_00fdba50",
    "FUN_00fdd5a0",
    "FUN_00d850a0",
    "FUN_00d2ee70",
    "FUN_00e07540",
    "FUN_0106c930",
    "FUN_0106cc70",
    "FUN_00d858a0",
    "FUN_00c810e0",
    "FUN_00f455e0",
    "FUN_0106a7b0",
    "FUN_00bff2d0",
    "Simulator::cCreatureGameData::GetEvoPointsToNextBrainLevel",
    "FUN_00d7d160",
    "FUN_0101d130",
    "FUN_00d52e90",
    "FUN_00b31cc0",
    "FUN_00c57ad0",
    "FUN_00c5c860",
    "FUN_00d54330",
    "FUN_00d425f0",
    "FUN_00d7eab0",
    "FUN_00d6e7c0",
    "FUN_00d6f800",
    "FUN_00c02eb0",
    "FUN_0100e780",
    "FUN_01047850",
    "FUN_00f07fd0",
    "FUN_00ff7530",
    "FUN_00f0e6e0",
    "FUN_00c08350",
    "FUN_00d4c650",
    "FUN_00d26ed0",
    "FUN_00f10bd0",
    "FUN_00e07e70",
    "FUN_00eede20",
    "FUN_00ebb8b0",
    "FUN_00d32330",
    "FUN_00feb770",
    "FUN_00c62ff0",
    "FUN_00bb4100",
    "FUN_00f19e70",
    "FUN_010677b0",
    "FUN_00c6e4f0",
    "FUN_00ebb980",
    "FUN_00d24550",
    "FUN_00c6d7c0",
    "FUN_00c79fa0",
    "FUN_00d491b0",
    "FUN_00d509c0",
    "FUN_00d1e610",
    "FUN_00f1a070",
    "FUN_00c027d0",
    "FUN_00d4b860",
    "FUN_00bb5640",
    "FUN_00d495b0",
    "FUN_00c0c250",
    "FUN_00f10030",
    "FUN_00ea5510",
    "FUN_00c6fe50",
    "FUN_00d3b0c0",
    "FUN_00fdade0",
    "FUN_00f3e590",
    "FUN_00bc1450",
    "FUN_00b2e940",
    "FUN_00d53490",
    "FUN_00d6fd70",
    "FUN_00bbe5f0",
    "FUN_00f3d900",
    "FUN_00c754e0",
    "FUN_00d3aa70",
    "FUN_00f0fbc0",
    "App::cCreatureModeStrategy::ExecuteAction",
    "FUN_00f32440",
    "FUN_00b19290",
    "FUN_00d3a830",
    "FUN_00fe8f70",
    "Simulator::cCreatureGameData::CalculateAvatarNormalizingScale",
    "FUN_01016070",
    "FUN_00f3dc70",
    "FUN_00f1ae10",
    "FUN_0102d0b0",
    "FUN_00fe6e40",
    "FUN_00d64a90",
    "FUN_00c706d0",
    "FUN_00b0a6f0",
    "FUN_00bb24d0",
    "FUN_00d6e680",
    "FUN_0102df20",
    "FUN_00f40d00",
    "FUN_00fe6bc0",
    "FUN_00d40230",
    "FUN_00ef0de0",
    "FUN_00d27a70",
    "FUN_00f0
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
  "file": "src/reconstruction/pkg13_creature_accessor/b1fdb0_accessor.cpp",
  "files": [
    "reconstruction/staging/pkg13-creature-accessor/b1fdb0_accessor.cpp",
    "reconstruction/staging/pkg13-creature-accessor/b1fdb0_accessor.hpp",
    "reconstruction/staging/pkg13-creature-accessor/b1fdb0_accessor_model_test.cpp",
    "src/reconstruction/pkg13_creature_accessor/b1fdb0_accessor.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave5/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-creature-accessor/00b1fdb0.json"
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
    "gate-creature-accessor-field"
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
  "OpaqueNounManager",
  "OpaqueNounManagerField"
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
      "0x00845310",
      "0x00b1fdb0",
      "0x00845310",
      "0x00b1fdb0",
      "0x00844f70",
      "0x00841440",
      "0x00846e60",
      "0x00841d40",
      "0x00845790",
      "0x00842d10",
      "0x00844180",
      "0x00843000",
      "0x00845310",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:1",
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
