# Evidence 0x01021300

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `03cee8d99e5780867ab568da4ec294c147eb6f2c7382ffb6c8bca599bb5c7df4`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl-compatible no-argument accessor",
  "return_note": "cEmpire* as a borrowed 32-bit pointer word",
  "return_observation": "The return is the cached pointer at sSpacePlayerData+0x1c, or zero when the empire key is 0xffffffff. No return-path AddRef is present.",
  "return_register": "EAX",
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
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
  "content_sha256": "9fcd168ade2e1b9e942e6bd85d9e53d1fd8c755776cec13424d31608bc6ef49d",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0020",
        "obs-0021"
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
        "obs-0002",
        "obs-0003"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0021"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0020",
        "obs-0021"
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
        "obs-0020",
        "obs-0021"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020",
        "obs-0021"
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
      "at": "0x01021300",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [0x016dda8c]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01021306",
      "count": 3,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x18]",
      "reg": "ECX"
    },
    {
      "at": "0x01021306",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x18]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0102131d",
      "count": 3,
      "first_use": 9,
      "first_write_index": 16,
      "id": "obs-0004",
      "index": 9,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x0102131e",
      "count": 4,
      "first_use": 10,
      "first_write_index": 19,
      "id": "obs-0005",
      "index": 10,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0102131f",
      "count": 3,
      "first_use": 11,
      "first_write_index": 17,
      "id": "obs-0006",
      "index": 11,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x01021320",
      "count": 7,
      "first_use": 12,
      "first_write_index": 1,
      "id": "obs-0007",
      "index": 12,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x01021321",
      "id": "obs-0008",
      "index": 13,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d2a0",
      "target": "0x00b3d2a0"
    },
    {
      "at": "0x01021328",
      "id": "obs-0009",
      "index": 15,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00ba9370",
      "target": "0x00ba9370"
    },
    {
      "at": "0x0102132d",
      "definite": true,
      "id": "obs-0010",
      "index": 16,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [0x016dda8c]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01021333",
      "definite": true,
      "id": "obs-0011",
      "index": 17,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [EBX + 0x1c]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01021339",
      "definite": true,
      "id": "obs-0012",
      "index": 19,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,EAX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x01021345",
      "definite": true,
      "id": "obs-0013",
      "index": 25,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {

[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
  },
  {
    "name": "Simulator_LookupEmpireByPoliticalId",
    "reconstructed": true,
    "va": "0x00ba9370"
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
    "name": "FUN_00b25fb0",
    "reconstructed": false,
    "va": "0x00b25fb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b262c0"
  },
  {
    "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
    "reconstructed": true,
    "va": "0x00b28ec0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b6d3c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba0080"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba7080"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba7dc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bae130"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb4ba0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbe740"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bc1450"
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
      "0x01021300",
      "0x0000001c",
      "0x0000001c",
      "0x01021300"
    ],
    "conflict_id": "TB-LC-005",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "do_not_collapse",
      "preferred_claim": null,
      "preserved_alternatives": true,
      "scope_note": "The pointer transition is observed, but destruction versus reference release is not equivalent behavior.",
      "status": "preserved_alternatives",
      "taxonomy": "preserved_alternatives"
    },
    "resolution_status": "preserved_alternatives",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "SpacePlayerData cached empire replacement lifecycle",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
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
  },
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
  "count": 43,
  "instructions": [
    {
      "address": "01021300",
      "instruction": "MOV ECX,dword ptr [0x016dda8c]"
    },
    {
      "address": "01021306",
      "instruction": "MOV EAX,dword ptr [ECX + 0x18]"
    },
    {
      "address": "01021309",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "0102130c",
      "instruction": "JZ 0x01021366"
    },
    {
      "address": "0102130e",
      "instruction": "MOV ECX,dword ptr [ECX + 0x1c]"
    },
    {
      "address": "01021311",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01021313",
      "instruction": "JZ 0x0102131d"
    },
    {
      "address": "01021315",
      "instruction": "CMP dword ptr [ECX + 0x84],EAX"
    },
    {
      "address": "0102131b",
      "instruction": "JZ 0x0102135d"
    },
    {
      "address": "0102131d",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0102131e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0102131f",
      "instruction": "PUSH EDI"
    },
    {
      "address": "01021320",
      "instruction": "PUSH EAX"
    },
    {
      "address": "01021321",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "01021326",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01021328",
      "instruction": "CALL 0x00ba9370"
    },
    {
      "address": "0102132d",
      "instruction": "MOV EBX,dword ptr [0x016dda8c]"
    },
    {
      "address": "01021333",
      "instruction": "MOV EDI,dword ptr [EBX + 0x1c]"
    },
    {
      "address": "01021336",
      "instruction": "ADD EBX,0x1c"
    },
    {
      "address": "01021339",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "0102133b",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "0102133d",
      "instruction": "JZ 0x0102135a"
    },
    {
      "address": "0102133f",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "01021341",
      "instruction": "JZ 0x0102134b"
    },
    {
      "address": "01021343",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "01021345",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "01021347",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "01021349",
      "instruction": "CALL EDX"
    },
    {
      "address": "0102134b",
      "instruction": "MOV dword ptr [EBX],ESI"
    },
    {
      "address": "0102134d",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "0102134f",
      "instruction": "JZ 0x0102135a"
    },
    {
      "address": "01021351",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "01021353",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01021356",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "01021358",
      "instruction": "CALL EDX"
    },
    {
      "address": "0102135a",
      "instruction": "POP EDI"
    },
    {
      "address": "0102135b",
      "instruction": "POP ESI"
    },
    {
      "address": "0102135c",
      "instruction": "POP EBX"
    },
    {
      "address": "0102135d",
      "instruction": "MOV EAX,[0x016dda8c]"
    },
    {
      "address": "01021362",
      "instruction": "MOV EAX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "01021365",
      "instruction": "RET"
    },
    {
      "address": "01021366",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "01021368",
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
  "original_bytes": 28114,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl-compatible no-argument accessor\",\n    \"return_note\": \"cEmpire* as a borrowed 32-bit pointer word\",\n    \"return_observation\": \"The return is the cached pointer at sSpacePlayerData+0x1c, or zero when the empire key is 0xffffffff. No return-path AddRef is present.\",\n    \"return_register\": \"EAX\",\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 11,\n      \"symbol\": \"FUN_0102d1b0\",\n      \"va\": \"0x0102d1b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00aea230\",\n      \"va\": \"0x00aea230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00aea250\",\n      \"va\": \"0x00aea250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00aea5d0\",\n      \"va\": \"0x00aea5d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00aeb160\",\n      \"va\": \"0x00aeb160\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cCommManager_CreateAndDispatchEvent_00aeb720\",\n      \"va\": \"0x00aeb720\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"cSpaceInventoryItem_ctor_00c877f0\",\n      \"va\": \"0x00c877f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"pkg12_space_00de9fc0\",\n      \"va\": \"0x00de9fc0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"A native integration test against the original global state is not available without modifying the existing PKG-12 integration boundary, which is out of scope.\",\n    \"The borrowed return is preserved by the absence of a return-path AddRef, but concrete cEmpire vtable ownership remains unresolved.\",\n    \"The lookup interface is modeled at the root and thiscall find boundaries; no shared map type or runtime manager allocation is reconstructed here.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"SpacePlayerCache\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": 0.92,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      },\n      {\n        \"name\": \"Simulator_LookupEmpireByPoliticalId\",\n        \"reconstructed\": true,\n        \"va\": \"0x00ba9370\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9590\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9930\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9f50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebe90\"\n      },\n      {\n        \"name\": \"FUN_00b25fb0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b25fb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b262c0\"\n      },\n      {\n        \"name\": \"ProfilePersistenceBoundary_run_candidate_00b28ec0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b28ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6d3c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba0080\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba7080\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba7dc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bae130\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb4ba0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbe740\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bc1450\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c31240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c31b50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c322f0\"\n      },\n      {\n        \"name\": \"EmpirePoliticalColor_00c32cd0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00c32cd0\"\n      },\n      {\n        \"name\": \"ProfileSetter_00c33690\",\n        \"reconstructed\": true,\n        \"va\": \"0x00c33690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c34320\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\
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
  "body_end": "01021368",
  "body_span_bytes": 105,
  "body_start": "01021300",
  "callees": [
    "FUN_00ba9370",
    "FUN_00b3d2a0"
  ],
  "callers": [
    "FUN_00c759a0",
    "FUN_00d09560",
    "FUN_00fe6e40",
    "FUN_00dd15a0",
    "FUN_00fe6b20",
    "FUN_01008910",
    "FUN_01068970",
    "FUN_00fee730",
    "FUN_00c46b80",
    "FUN_00ffa900",
    "FUN_00c830f0",
    "FUN_00d5e0c0",
    "FUN_0103dee0",
    "FUN_010251e0",
    "FUN_00ffd280",
    "FUN_01023be0",
    "FUN_00ae9930",
    "FUN_00c46e20",
    "FUN_0102cd90",
    "FUN_00fe55b0",
    "FUN_00ff9800",
    "FUN_00e3e7f0",
    "FUN_00fe7b80",
    "FUN_01050bb0",
    "FUN_0102d1b0",
    "FUN_00c382e0",
    "FUN_00d06920",
    "FUN_00fee3d0",
    "FUN_00bc1450",
    "FUN_00d01f50",
    "FUN_01056160",
    "FUN_01005d80",
    "FUN_00c469f0",
    "FUN_00c4b250",
    "FUN_00c82400",
    "FUN_00ffc160",
    "FUN_010021a0",
    "FUN_00c76800",
    "FUN_00fdf5f0",
    "FUN_00c468b0",
    "FUN_01047300",
    "FUN_0103eff0",
    "FUN_00fe73c0",
    "FUN_0105b350",
    "FUN_00dd21c0",
    "FUN_00bae130",
    "FUN_01014220",
    "FUN_01058c90",
    "FUN_0106fc90",
    "FUN_00dd4950",
    "FUN_00ffc8d0",
    "FUN_00c94470",
    "FUN_00c75a50",
    "FUN_00c62ff0",
    "FUN_01047000",
    "FUN_00b6d3c0",
    "FUN_00cc22c0",
    "FUN_00c44d00",
    "FUN_00ff9100",
    "FUN_00ba7dc0",
    "FUN_00fe6dc0",
    "FUN_010134d0",
    "FUN_01029950",
    "FUN_00d038e0",
    "FUN_010534c0",
    "FUN_00c6e4f0",
    "FUN_010019a0",
    "FUN_0106cc70",
    "FUN_00bb4ba0",
    "FUN_00c46ab0",
    "FUN_00e06d90",
    "FUN_01038410",
    "FUN_0102cd40",
    "FUN_00e91060",
    "FUN_00fea510",
    "FUN_0103b950",
    "FUN_00ba0080",
    "FUN_00d0e170",
    "Simulator::cRelationshipManager::IsAllied2",
    "FUN_00e39ab0",
    "FUN_010053c0",
    "FUN_01058020",
    "FUN_00ffabc0",
    "FUN_00b25fb0",
    "FUN_01000000",
    "FUN_00dd4b20",
    "Simulator::cMissionManager::GetMissionTrackColor",
    "FUN_00d09600",
    "FUN_00c34320",
    "FUN_00fef140",
    "FUN_00d0a1e0",
    "FUN_00c47a10",
    "FUN_0102c600",
    "FUN_00fe9580",
    "FUN_00d01e30",
    "FUN_0102f820",
    "FUN_01065f00",
    "FUN_00c72030",
    "FUN_01001700",
    "FUN_00ba7080",
    "FUN_00b28ec0",
    "FUN_01047440",
    "FUN_00b262c0",
    "FUN_01057bd0",
    "FUN_00ae9590",
    "FUN_0103a7d0",
    "FUN_00c72370",
    "FUN_00c737a0",
    "FUN_00fe0f40",
    "FUN_01050070",
    "FUN_00fe0160",
    "FUN_01016070",
    "FUN_00ae9f50",
    "FUN_00fde3e0",
    "FUN_00fe0570",
    "FUN_010421c0",
    "FUN_00cbc7f0",
    "FUN_0102f8d0",
    "FUN_0102b780",
    "FUN_00c7bd40",
    "FUN_00ca81d0",
    "FUN_010679f0",
    "FUN_00fe2ab0",
    "FUN_00c37180",
    "FUN_0103fe90",
    "FUN_01005180",
    "FUN_010727e0",
    "FUN_01073700",
    "FUN_00bbe740",
    "FUN_00c31b50",
    "FUN_010488e0",
    "FUN_00c322f0",
    "FUN_00fdb9a0",
    "FUN_0100dd40",
    "FUN_00ea5510",
    "FUN_00fda750",
    "FUN_00feb770",
    "FUN_01030b70",
    "FUN_00d065a0",
    "FUN_00fe7e60",
    "FUN_0102df20",
    "FUN_00c487d0",
    "FUN_00fe74a0",
    "FUN_0102cf10",
    "FUN_00fdbf90",
    "FUN_00c33690",
    "FUN_00fe5a20",
    "FUN_00aeb3e0",
    "FUN_00c5c470",
    "FUN_0103aa00",
    "FUN_010697b0",
    "FUN_0106ba00",
    "FUN_00fe72b0",
    "FUN_00c32cd0",
    "FUN_00d130d0",
    "FUN_00feb0b0",
    "FUN_00c47e20",
    "FUN_00fed890",
    "FUN_00c31240",
    "FUN_00c38270",
    "FUN_00cad880",
    "FUN_00c705c0",
    "FUN_0102ce30",
    "FUN_00ffc4e0",
    "FUN_00feb510",
    "FUN_00fe76d0",
    "FUN_01051090",
    "FUN_010027b0",
    "FUN_01007430",
    "FUN_00feed30",
    "FUN_01021370",
    "FUN_0102d820",
    "FUN_00dd2650",
    "FUN_00aebe90",
    "FUN_01045500",
    "FUN_010229d0",
    "FUN_0102cae0",
    "FUN_00c4b2b0",
    "FUN_01047850",
    "FUN_00e07e70",
    "FUN_01003df0",
    "FUN_0100fb00"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01021300",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_01021300",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc21300",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01021300(void)",
  "size_bytes": 105,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01021300",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00b28f6b"
    },
    {
      "from": "00b28f81"
    },
    {
      "from": "00bb4be5"
    },
    {
      "from": "00bb4c91"
    },
    {
      "from": "00bb4ca1"
    },
    {
      "from": "00c33699"
    },
    {
      "from": "00c32d19"
    },
    {
      "from": "00c32d34"
    },
    {
      "from": "00c73980"
    },
    {
      "from": "00fe9b32"
    },
    {
      "from": "00aeb4a0"
    },
    {
      "from": "00c343f8"
    },
    {
      "from": "00d01f53"
    },
    {
      "from": "00b25fb4"
    },
    {
      "from": "00d065a6"
    },
    {
      "from": "00c7bd83"
    },
    {
      "from": "00d06927"
    },
    {
      "from": "00d038e6"
    },
    {
      "from": "01021370"
    },
    {
      "from": "01021379"
    },
    {
      "from": "01021389"
    },
    {
      "from": "0103aa63"
    },
    {
      "from": "0103aa70"
    },
    {
      "from":
[TRUNCATED]
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:0x0167eae4",
  "global:0x016dda8c",
  "global:Simulator::sSpacePlayerData at 0x016DDA8C"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg12_space/space_player_cache.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_player_cache.cpp",
    "reconstruction/staging/pkg12-space/space_player_cache.hpp",
    "reconstruction/staging/pkg12-space/space_player_cache_model_test.cpp",
    "src/reconstruction/pkg12_space/space_player_cache.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg12-space/01021300.json"
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
    "gate-space-player-data-and-empire-lookup"
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
  "original_bytes": 9837,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"STRONG_SEMANTIC\",\n  \"confidence\": {\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 184,\n  \"evidence\": [\n    {\n      \"independence\": \"same-binary disassembly corroborates decompilation\",\n      \"source\": \"Ghidra SporeApp.exe 0x01021300: 43 instructions; offsets +0x18/+0x1c/+0x84; vtable slots +0x00/+0x04\",\n      \"supports\": \"exact control flow and reference ordering\"\n    },\n    {\n      \"independence\": \"independent same-binary lookup helper\",\n      \"source\": \"Ghidra SporeApp.exe 0x00ba9370\",\n      \"supports\": \"mEmpires lower-bound lookup and end-only failure check\"\n    },\n    {\n      \"independence\": \"independent same-binary lifecycle paths\",\n      \"source\": \"Ghidra SporeApp.exe 0x01021d40, 0x01022460, 0x00bad7a0\",\n      \"supports\": \"cache initialization, player-field teardown, and independent empire-map erase\"\n    },\n    {\n      \"independence\": \"independent same-binary consumer\",\n      \"source\": \"Ghidra SporeApp.exe 0x00b25fb0\",\n      \"supports\": \"current-empire identity to kCivilization bridge\"\n    },\n    {\n      \"independence\": \"independent repository static adjudication\",\n      \"source\": \"knowledgegraph/research/root-closure/track-e-empire-chain.md:15-44,55-117,160-186\",\n      \"supports\": \"current-player cEmpire cache purpose, field map, successor behavior, ownership\"\n    },\n    {\n      \"independence\": \"independent repository lifecycle adjudication\",\n      \"source\": \"knowledgegraph/research/root-closure/followup-space-lifecycle.md:9,58-59,124-126 and docs/analysis/architecture-decisions.md:45-51\",\n      \"supports\": \"SpacePlayerData initialization, cache teardown, and independence from map erase\"\n    }\n  ],\n  \"family\": \"SpacePlayerData field accessors and lazy derived-state caches\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": {\n      \"direct\": [\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        }\n      ],\n      \"indirect_callbacks\": []\n    },\n    \"direct_callers\": {\n      \"direct_call_edges\": 246,\n      \"direct_caller_count\": 182,\n      \"downstream_unlock_count\": 182,\n      \"gameplay_caller_count\": 47,\n      \"representative\": [\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"role\",\n            \"va\"\n          ]\n        }\n      ]\n    },\n    \"globals\": [\n      {\n        \"field\": \"mPlayerEmpireID\",\n        \"offset\": \"0x18\",\n        \"structure\": \"SpacePlayerData\",\n        \"type\": \"uint32_t\"\n      },\n      {\n        \"field\": \"mpPlayerEmpire\",\n        \"offset\": \"0x1c\",\n        \"structure\": \"SpacePlayerData\",\n        \"type\": \"intrusive_ptr<cEmpire>\"\n      },\n      {\n        \"field\": \"mPoliticalID\",\n        \"note\": \"The current Ghidra imported layout labels this offset mTrait; the repository's direct cross-check and map-key use support political-identity semantics. The raw offset, not the disputed imported field name, is the closed contract.\",\n        \"offset\": \"0x84\",\n        \"structure\": \"cEmpire\",\n        \"type\": \"uint32_t political identity\"\n      },\n      {\n        \"field\": \"AddRef\",\n        \"offset\": \"vtable+0x00\",\n        \"structure\": \"cEmpire\",\n        \"type\": \"intrusive reference-count method\"\n      },\n      {\n        \"field\": \"Release\",\n        \"offset\": \"vtable+0x04\",\n        \"structure\": \"cEmpire\",\n        \"type\": \"intrusive reference-count method\"\n      },\n      {\n        \"field\": \"mEmpires\",\n        \"offset\": \"0x150\",\n        \"structure\": \"cStarManager\",\n        \"type\": \"map<uint32_t, intrusive_ptr<cEmpire>>\"\n      },\n      {\n        \"address\": \"0x016dda8c\",\n        \"name\": \"Simulator::sSpacePlayerData\",\n        \"type\": \"SpacePlayerData *\"\n      }\n    ],\n    \"structures\": [\n      {\n        \"field\": \"mPlayerEmpireID\",\n        \"offset\": \"0x18\",\n        \"structure\": \"SpacePlayerData\",\n        \"type\": \"uint32_t\"\n      },\n      {\n        \"field\": \"mpPlayerEmpire\",\n        \"offset\": \"0x1c\",\n        \"structure\": \"SpacePlayerData\",\n        \"type\": \"intrusive_ptr<cEmpire>\"\n      },\n      {\n        \"field\": \"mPoliticalID\",\n        \"note\": \"The current Ghidra imported layout labels this offset mTrait; the repository's direct cross-check and map-key use support political-identity semantics. The raw offset, not the disputed imported field name, is the closed contract.\",\n        \"offset\": \"0x84\",\n        \"structure\": \"cEmpire\",\n        \"type\": \"uint32_t political identity\"\n      },\n      {\n        \"field\": \"AddRef\",\n        \"offset\": \"vtable+0x00\",\n        \"structure\": \"cEmpire\",\n        \"type\": \"intrusive reference-count method\"\n      },\n      {\n        \"field\": \"Release\",\n        \"offset\": \"vtable+0x04\",\n        \"structure\": \"cEmpire\",\n        \"type\": \"intrusive reference-count method\"\n    
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
  "/Spore/Simulator/SpacePlayerData",
  "/Spore/Simulator/cEmpire",
  "Empire",
  "EmpireLookup",
  "EmpireTrait",
  "SpacePlayerCache",
  "StagedIdWord",
  "cEmpire* as a borrowed 32-bit pointer word",
  "intrusive_ptr<Simulator::cEmpire>",
  "uint32_t"
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
      "0x01021300",
      "0x0000001c",
      "0x0000001c",
      "0x01021300"
    ],
    "conflict_id": "TB-LC-005",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "do_not_collapse",
      "preferred_claim": null,
      "preserved_alternatives": true,
      "scope_note": "The pointer transition is observed, but destruction versus reference release is not equivalent behavior.",
      "status": "preserved_alternatives",
      "taxonomy": "preserved_alternatives"
    },
    "resolution_status": "preserved_alternatives",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "SpacePlayerData cached empire replacement lifecycle",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
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
  },
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
