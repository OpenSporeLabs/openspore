# Evidence 0x00ba9370

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `83d7bbaf683d3c0c6a6d00b7554dda6dd54c9bd2803ae89cac24cd2c29dda970`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed; ECX receiver and one caller-cleaned stack word",
  "receiver": {
    "register": "ECX",
    "type": "OpaqueStarManager*",
    "width_bytes": 4
  },
  "return_register": "EAX",
  "return_semantics": "Borrowed map payload pointer only when the guarded-hybrid dependent helper returns a non-anchor candidate whose final retained key exactly matches the request; zero on the anchor, invalid request, null payload, or a present key shadowed by a greater right-side candidate.",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Political ID request; 0xffffffff is rejected before receiver dereference.",
      "position": 1,
      "type": "TargetWord",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
  "content_sha256": "bfc8e34f05ef647c9ed5d905b55d083039f9ca9a2bdaf574ce885b038b70afd7",
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
    "persisted_calling_convention": "__thiscall observed; ECX receiver and one caller-cleaned stack word"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0013",
        "obs-0016"
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
        "obs-0003",
        "obs-0007"
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
        "obs-0001",
        "obs-0005",
        "obs-0008",
        "obs-0012",
        "obs-0015"
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
        "obs-0001",
        "obs-0005",
        "obs-0008",
        "obs-0012",
        "obs-0015"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0016"
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
        "obs-0013",
        "obs-0016"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0016"
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
      "at": "0x00ba9370",
      "count": 5,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00ba9371",
      "count": 3,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "CMP dword ptr [ESP + 0x8],-0x1",
      "reg": "ESP"
    },
    {
      "at": "0x00ba9371",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "CMP dword ptr [ESP + 0x8],-0x1",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00ba9376",
      "count": 2,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00ba9377",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00ba937b",
      "count": 5,
      "first_use": 5,
      "first_write_index": 11,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP + 0xc]",
      "reg": "EAX"
    },
    {
      "at": "0x00ba937b",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0007",
      "index": 5,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA EAX,[ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00ba9380",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0008",
      "index": 7,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA ECX,[ESP + 0x8]",
      "reason": "local",
      "resolved": false
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "map_int_whatever_find",
    "reconstructed": true,
    "va": "0x00e5c780"
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
    "va": "0x00ae9040"
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
    "va": "0x00b677e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b6baf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b6cc50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b96d40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba0080"
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
      "0x00ba9370",
      "0x000000a0",
      "0x00000064",
      "0x00000084"
    ],
    "conflict_id": "TB-FL-004",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "do_not_collapse",
      "preferred_claim": null,
      "preserved_alternatives": true,
      "scope_note": "The later matching offsets are not sufficient to validate the earlier alternatives.",
      "status": "preserved_alternatives",
      "taxonomy": "preserved_alternatives"
    },
    "resolution_status": "preserved_alternatives",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "cStarManager selected field-offset maps",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
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
  "count": 23,
  "instructions": [
    {
      "address": "00ba9370",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00ba9371",
      "instruction": "CMP dword ptr [ESP + 0x8],-0x1"
    },
    {
      "address": "00ba9376",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ba9377",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00ba9379",
      "instruction": "JZ 0x00ba93a4"
    },
    {
      "address": "00ba937b",
      "instruction": "LEA EAX,[ESP + 0xc]"
    },
    {
      "address": "00ba937f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ba9380",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "00ba9384",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00ba9385",
      "instruction": "LEA ECX,[ESI + 0x150]"
    },
    {
      "address": "00ba938b",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "00ba9390",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00ba9392",
      "instruction": "ADD ESI,0x154"
    },
    {
      "address": "00ba9398",
      "instruction": "CMP EAX,ESI"
    },
    {
      "address": "00ba939a",
      "instruction": "JZ 0x00ba93a4"
    },
    {
      "address": "00ba939c",
      "instruction": "MOV EAX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00ba939f",
      "instruction": "POP ESI"
    },
    {
      "address": "00ba93a0",
      "instruction": "POP ECX"
    },
    {
      "address": "00ba93a1",
      "instruction": "RET 0x4"
    },
    {
      "address": "00ba93a4",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00ba93a6",
      "instruction": "POP ESI"
    },
    {
      "address": "00ba93a7",
      "instruction": "POP ECX"
    },
    {
      "address": "00ba93a8",
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
  "original_bytes": 17050,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed; ECX receiver and one caller-cleaned stack word\",\n    \"receiver\": {\n      \"register\": \"ECX\",\n      \"type\": \"OpaqueStarManager*\",\n      \"width_bytes\": 4\n    },\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"Borrowed map payload pointer only when the guarded-hybrid dependent helper returns a non-anchor candidate whose final retained key exactly matches the request; zero on the anchor, invalid request, null payload, or a present key shadowed by a greater right-side candidate.\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"observed_use\": \"Political ID request; 0xffffffff is rejected before receiver dereference.\",\n        \"position\": 1,\n        \"type\": \"TargetWord\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueStarManager,OpaqueStarManager*,TargetWord\"\n      ],\n      \"package\": \"PKG-14-A2-WORLD-LIFECYCLE-WAVE2\",\n      \"score\": 14,\n      \"symbol\": \"star_regenerate_00bb4af0\",\n      \"va\": \"0x00bb4af0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"shared_types:OrderedMapEntry\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 11,\n      \"symbol\": \"pkg11_sim_core_00b21340\",\n      \"va\": \"0x00b21340\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueStarManager,OpaqueStarManager*\"\n      ],\n      \"package\": \"PKG-14-A2-WORLD-LIFECYCLE-WAVE2\",\n      \"score\": 11,\n      \"symbol\": \"star_manager_record_to_planet_00bb5b50\",\n      \"va\": \"0x00bb5b50\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OrderedMapEntry,TargetWord\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 9,\n      \"symbol\": \"map_int_whatever_find\",\n      \"va\": \"0x00e5c780\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueStarManager\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_IsNotStarOrBinaryStar\",\n      \"va\": \"0x00c8b6b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OrderedMapEntry,TargetWord\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 6,\n      \"symbol\": \"pkg20_gameglobal_00ba83a0\",\n      \"va\": \"0x00ba83a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OrderedMapEntry,TargetWord\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 6,\n      \"symbol\": \"pkg20_gameglobal_00ba8420\",\n      \"va\": \"0x00ba8420\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No runtime trace validates the shared map dependency under concurrent mutation.\",\n    \"The concrete empire subtype and complete cStarManager identity remain outside this wrapper's body.\",\n    \"The receiver root slot and empire-map payload ownership are not closed by this function alone.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueStarManager\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": 0.94,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"map_int_whatever_find\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5c780\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9590\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9930\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae9f50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebe90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aecf90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aed2c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b20790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b677e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6baf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6cc50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b96d40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba0080\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb4100\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb5640\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bba2a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd15a0\"\n      },\n      {\n        \"name\": null
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
  "body_end": "00ba93aa",
  "body_span_bytes": 59,
  "body_start": "00ba9370",
  "callees": [
    "map_int_whatever_find"
  ],
  "callers": [
    "FUN_01008910",
    "FUN_00c451e0",
    "FUN_00dd2820",
    "FUN_00fde230",
    "FUN_0103dee0",
    "FUN_010251e0",
    "FUN_00c70b50",
    "FUN_01023be0",
    "FUN_00e9a940",
    "FUN_00ae9930",
    "FUN_01042080",
    "FUN_0102cd90",
    "FUN_00d03d70",
    "FUN_0102d1b0",
    "FUN_01056160",
    "FUN_00c4bc00",
    "FUN_00c6fe50",
    "FUN_00fdeac0",
    "FUN_010021a0",
    "FUN_00fdf5f0",
    "FUN_00d5ccf0",
    "FUN_00ff5930",
    "FUN_0103eff0",
    "FUN_01067510",
    "FUN_01000eb0",
    "FUN_00c62ff0",
    "FUN_01047000",
    "FUN_00c37cc0",
    "FUN_0102ba30",
    "FUN_00c5b280",
    "FUN_00c452a0",
    "FUN_01029a60",
    "FUN_01029950",
    "FUN_010129c0",
    "FUN_00c35240",
    "FUN_00ae9040",
    "FUN_0106dd10",
    "FUN_0100e780",
    "FUN_00c774b0",
    "FUN_00fdade0",
    "FUN_0106cc70",
    "FUN_00c3a2b0",
    "FUN_00e06d90",
    "FUN_01038410",
    "FUN_00d05a20",
    "FUN_00fea510",
    "FUN_00ba0080",
    "FUN_010468f0",
    "FUN_01021300",
    "FUN_00e39ab0",
    "FUN_00bf8170",
    "FUN_01058020",
    "FUN_010673f0",
    "FUN_00ffabc0",
    "FUN_00b677e0",
    "FUN_0106c930",
    "FUN_00ff8ad0",
    "FUN_00dd4b20",
    "FUN_01049f90",
    "FUN_0102c9e0",
    "FUN_00dd0e10",
    "FUN_00ffa780",
    "FUN_0102c600",
    "FUN_00fe9580",
    "FUN_01008e60",
    "FUN_01065f00",
    "FUN_00c79fa0",
    "FUN_00c72030",
    "FUN_01013ba0",
    "FUN_01001700",
    "FUN_0102daa0",
    "FUN_0102cc30",
    "FUN_00ae9590",
    "FUN_0103a7d0",
    "FUN_00c72370",
    "FUN_00c75520",
    "FUN_00c737a0",
    "FUN_00b6baf0",
    "FUN_00bb5640",
    "FUN_0100a960",
    "FUN_00ae9f50",
    "FUN_010593e0",
    "FUN_00bd2310",
    "FUN_00bd15a0",
    "FUN_01012b50",
    "FUN_00cfbc10",
    "FUN_00c754e0",
    "FUN_0101246a",
    "FUN_00aed2c0",
    "FUN_00b6cc50",
    "FUN_01005180",
    "FUN_00b96d40",
    "cStarRecord__ctor",
    "FUN_00b20790",
    "FUN_0102acb0",
    "FUN_00c5c860",
    "FUN_00c72c60",
    "FUN_0100b430",
    "FUN_00c322f0",
    "FUN_0100dd40",
    "FUN_00feb770",
    "FUN_00d015d0",
    "FUN_0102d0b0",
    "FUN_0102df20",
    "FUN_00e3cf60",
    "FUN_00ffb270",
    "FUN_010091d0",
    "FUN_0102cf10",
    "FUN_00d06030",
    "FUN_00aeb3e0",
    "FUN_00c5c470",
    "FUN_00c71e30",
    "FUN_00c32cd0",
    "FUN_00e2d6a0",
    "FUN_00c784c0",
    "FUN_01014540",
    "FUN_01006a40",
    "FUN_00c72190",
    "FUN_0102ce30",
    "FUN_01014870",
    "FUN_00aecf90",
    "FUN_01014a80",
    "FUN_01072d40",
    "FUN_010027b0",
    "FUN_00d05d90",
    "FUN_00aebe90",
    "FUN_00bd9a80",
    "FUN_00c706d0",
    "FUN_00bb4100",
    "FUN_01029a10",
    "FUN_01047850",
    "FUN_01076b80",
    "FUN_01003df0",
    "FUN_00c8ce40",
    "FUN_0100fb00",
    "FUN_0103e8e0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ba9370",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00ba9370",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7a9370",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ba9370(void)",
  "size_bytes": 59,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ba9370",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00bba2e7"
    },
    {
      "from": "00c3310f"
    },
    {
      "from": "00b207db"
    },
    {
      "from": "00c737cf"
    },
    {
      "from": "00bb42da"
    },
    {
      "from": "00b96e37"
    },
    {
      "from": "00c6fe7a"
    },
    {
      "from": "00fe959d"
    },
    {
      "from": "00fe96d4"
    },
    {
      "from": "00fe9a70"
    },
    {
      "from": "00fe9b19"
    },
    {
      "from": "00fe9e1a"
    },
    {
      "from": "00fe9e29"
    },
    {
      "from": "00fe9fcd"
    },
    {
      "from": "00fe9fdc"
    },
    {
      "from": "00fea060"
    },
    {
      "from": "00fea06f"
    },
    {
      "from": "00fea1f4"
    },
    {
      "from": "00fea203"
    },
    {
      "from": "00aeb47d"
    },
    {
      "from": "00c70720"
    },
    {
      "from": "00d05c55"
    },
    {
      "from": "00d0165c"
    },
    {
      "from": "00d0166b"
    },
    {
      "from": "00d05dff"
    },
    {
      "from": "01021328"
    },
    {
      "from": "00d5cfbe"
    },
    {
      "from": "00c71e60"
    },
    {
      "from": "00bd23f7"
    },
    {
      "from": "00bd1612"
    },
    {
      "from": "00aebf35"
    },
    {
      "from": "00aec128"
    },
    {
      "from": "00ae95b0"
    },
    {
      "from": "00ae9f89"
    },
    {
      "from": "00c35257"
    },
    {
      "from": "00c3526e"
    },
    {
      "from": "00dd288a"
    },
    {
      "from": "00dd4c2b"
    },
    {
      "from": "01005226"
    },
    {
      "from": "0102e03b"
    },
    {
      "from": "0102e412"
    },
    {
      "from": "0102eb7e"
    },
    {
      "from": "0102ec0a"
    },
    {
      "from": "0102ed91"
    },
    {
      "from": "0102ee66"
    },
    {
      "from": "0102ef93"
    },
    {
      "from": "0102f02a"
    },
 
[TRUNCATED]
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:0x0167eae4"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg11_sim_core/empire_lookup.cpp",
  "files": [
    "reconstruction/staging/pkg11-sim-core/empire_lookup.cpp",
    "reconstruction/staging/pkg11-sim-core/empire_lookup.hpp",
    "reconstruction/staging/pkg11-sim-core/empire_lookup_model_test.cpp",
    "src/reconstruction/pkg11_sim_core/empire_lookup.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-sim-core/00ba9370.json"
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
    "gate-star-manager-and-empire-map-lifecycle"
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
  "EmpireMapEntry",
  "OpaqueStarManager",
  "OpaqueStarManager*",
  "OrderedMapEntry",
  "TargetWord"
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
      "0x00ba9370",
      "0x000000a0",
      "0x00000064",
      "0x00000084"
    ],
    "conflict_id": "TB-FL-004",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "do_not_collapse",
      "preferred_claim": null,
      "preserved_alternatives": true,
      "scope_note": "The later matching offsets are not sufficient to validate the earlier alternatives.",
      "status": "preserved_alternatives",
      "taxonomy": "preserved_alternatives"
    },
    "resolution_status": "preserved_alternatives",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "cStarManager selected field-offset maps",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  }
]
```
