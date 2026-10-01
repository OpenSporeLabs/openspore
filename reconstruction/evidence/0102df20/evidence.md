# Evidence 0x0102df20

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2d9fcee7e5119f93521cf9e3d6962481c69c2e2562df624b52944b7167ddd47c`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl observed; no implicit this parameter",
  "return_observation": "The function has void live decompilation and returns through ordinary RET paths.",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Loaded into ECX from the first stack slot and dereferenced at offset 0 to select a large event-code dispatch.",
      "position": 1,
      "type": "SpaceEvent *",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "observed_use": "Loaded from the second stack slot and forwarded to branch helpers and FUN_0102d1b0.",
      "position": 2,
      "type": "Space *",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0C",
      "observed_use": "Loaded from the third stack slot, null-checked in selected paths, and forwarded to event/cleanup helpers.",
      "position": 3,
      "type": "SpaceContext *",
      "width_bytes": 4
    }
  ]
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
      "entry_ESP+0x10c",
      "entry_ESP+0x118"
    ],
    "ordinary_stack_argument_slots_bounded": {
      "kept": 2,
      "omitted": 22
    },
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x10c",
        "observed": true,
        "ordinal": 67,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x118",
        "observed": true,
        "ordinal": 70,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ordinary_stack_arguments_bounded": {
      "kept": 2,
      "omitted": 22
    },
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x10c",
        "observed": true,
        "ordinal": 67,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x118",
        "observed": true,
        "ordinal": 70,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_arguments_bounded": {
      "kept": 2,
      "omitted": 22
    },
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -5216, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "dfad827b0ece969f9c8016c82606dd239aa7c21461211894f3955920ebd077a9",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
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
    "persisted_calling_convention": "cdecl observed; no implicit this parameter"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 18,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0033",
        "obs-0041",
        "obs-0056",
        "obs-0072",
        "obs-0082",
        "obs-0091",
        "obs-0097",
        "obs-0104",
        "obs-0120",
        "obs-0128",
        "obs-0138",
        "obs-0145",
        "obs-0152",
        "obs-0159",
        "obs-0172",
        "obs-0179",
        "obs-0275",
        "obs-0288",
        "obs-0307",
        "obs-0318",
        "obs-0325",
        "obs-0333",
        "obs-0343",
        "obs-0353",
        "obs-0363",
        "obs-0371",
        "obs-0381",
        "obs-0412",
        "obs-0430",
        "obs-0446",
        "obs-0458",
        "obs-0473",
        "obs-0488",
        "obs-0504",
        "obs-0530",
        "obs-0556",
        "obs-0568",
        "obs-0574",
        "obs-0581",
        "obs-0588"
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
        "obs-0042",
        "obs-0046",
        "obs-0057",
        "obs-0060",
        "obs-0063",
        "obs-0066",
        "obs-0083",
        "obs-0098",
        "obs-0105",
        "obs-0107",
        "obs-0129",
        "obs-0139",
        "obs-0146",
        "obs-0153",
        "obs-0160",
        "obs-0165",
        "obs-0173",
        "obs-0180",
        "obs-0183",
        "obs-0184",
        "obs-0185",
        "obs-0186",
        "obs-0187",
        "obs-0188",
        "obs-0190",
        "obs-0191",
        "obs-0192",
        "obs-0193",
        "obs-0194",
        "obs-0195",
        "obs-0196",
        "obs-0197",
        "obs-0198",
        "obs-0199",
        "obs-0209",
        "obs-0210",
        "obs-0211",
        "obs-0212",
        "obs-0214",
        "obs-0217",
        "obs-0219",
        "obs-0221",
        "obs-0227",
        "obs-0228",
        "obs-0229",
        "obs-0231",
        "obs-0232",
        "obs-0233",
        "obs-0234",
        "obs-0235",
        "obs-0236",
        "obs-0237",
        "obs-0240",
        "obs-0242",
        "obs-0243",
        "obs-0248",
        "obs-0257",
        "obs-0265",
        "obs-0276",
        "obs-0278",
        "obs-0291",
        "obs-0293",
        "obs-0294",
        "obs-0296",
        "obs-0298",
        "obs-0301",
        "obs-0308",
        "obs-0319",
        "obs-0326",
        "obs-0337",
        "obs-0347",
        "obs-0357",
        "obs-0365",
        "obs-037
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "address_window_offset_005c65e0",
    "reconstructed": true,
    "va": "0x005c65e0"
  },
  {
    "name": "achievement_progress_update_00676e90",
    "reconstructed": true,
    "va": "0x00676e90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  },
  {
    "name": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
    "reconstructed": true,
    "va": "0x00aeb720"
  },
  {
    "name": "pkg13_creature_accessor_00b1fdb0",
    "reconstructed": true,
    "va": "0x00b1fdb0"
  },
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
  },
  {
    "name": "FUN_00b3d2c0",
    "reconstructed": false,
    "va": "0x00b3d2c0"
  },
  {
    "name": "FUN_00b3d300",
    "reconstructed": true,
    "va": "0x00b3d300"
  },
  {
    "name": "Simulator_cSpaceTrading_Get",
    "reconstructed": true,
    "va": "0x00b3d4d0"
  },
  {
    "name": "FUN_00b8dab0",
    "reconstructed": false,
    "va": "0x00b8dab0"
  },
  {
    "name": "FUN_00b8de30",
    "reconstructed": false,
    "va": "0x00b8de30"
  },
  {
    "name": "Simulator_LookupEmpireByPoliticalId",
    "reconstructed": true,
    "va": "0x00ba9370"
  },
  {
    "name": "FUN_00bba790",
    "reconstructed": false,
    "va": "0x00bba790"
  },
  {
    "name": "FUN_00c31730",
    "reconstructed": false,
    "va": "0x00c31730"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c485b0"
  },
  {
    "name": "FUN_00c77bf0",
    "reconstructed": false,
    "va": "0x00c77bf0"
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
    "va": "0x00aeb7b0"
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
      "0x00aeb160",
      "0x00aebe90",
      "0x00aed2c0",
      "0x00c75520",
      "0x00dd5160",
      "0x0102c9e0",
      "0x0102caa0",
      "0x0102cae0",
      "0x0102cc30",
      "0x0102cd90",
      "0x0102ce30",
      "0x0102cf10",
      "0x0102d1b0",
      "0x0102df20",
      "0x01072d40",
      "0x00aeb730"
    ],
    "conflict_id": "LC-006",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_SUPPORTED",
    "resolution_status": "RESOLVED_SUPPORTED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x00AEB720 communication wrapper",
    "unresolved_reason": "The exact private wrapper name and the full parameter types are not recoverable from static naming alone; the create-and-dispatch contract is resolved."
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
  "count": 1375,
  "instructions": [
    {
      "address": "0102df20",
      "instruction": "SUB ESP,0x88"
    },
    {
      "address": "0102df26",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0102df27",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0102df28",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0102df29",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0102df2a",
      "instruction": "CALL 0x01021260"
    },
    {
      "address": "0102df2f",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "0102df31",
      "instruction": "CALL 0x00a206f0"
    },
    {
      "address": "0102df36",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "0102df38",
      "instruction": "CMP EAX,EBP"
    },
    {
      "address": "0102df3a",
      "instruction": "JZ 0x0102df49"
    },
    {
      "address": "0102df3c",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "0102df3e",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0102df40",
      "instruction": "MOV EAX,dword ptr [EDX + 0x20]"
    },
    {
      "address": "0102df43",
      "instruction": "CALL EAX"
    },
    {
      "address": "0102df45",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "0102df47",
      "instruction": "JMP 0x0102df4b"
    },
    {
      "address": "0102df49",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "0102df4b",
      "instruction": "CALL 0x00a206f0"
    },
    {
      "address": "0102df50",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "0102df52",
      "instruction": "CMP EDI,EBP"
    },
    {
      "address": "0102df54",
      "instruction": "JZ 0x0102df8f"
    },
    {
      "address": "0102df56",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "0102df58",
      "instruction": "MOV EAX,dword ptr [EDX + 0x38]"
    },
    {
      "address": "0102df5b",
      "instruction": "PUSH 0x3475365"
    },
    {
      "address": "0102df60",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0102df62",
      "instruction": "CALL EAX"
    },
    {
      "address": "0102df64",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "0102df66",
      "instruction": "MOV EAX,dword ptr [EDX + 0x40]"
    },
    {
      "address": "0102df69",
      "instruction": "PUSH 0x7cd49637"
    },
    {
      "address": "0102df6e",
      "instruction": "PUSH 0x3475381"
    },
    {
      "address": "0102df73",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0102df75",
      "instruction": "CALL EAX"
    },
    {
      "address": "0102df77",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "0102df79",
      "instruction": "MOV EAX,dword ptr [EDX + 0x40]"
    },
    {
      "address": "0102df7c",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0102df7d",
      "instruction": "PUSH 0x3475385"
    },
    {
      "address": "0102df82",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0102df84",
      "instruction": "CALL EAX"
    },
    {
      "address": "0102df86",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "0102df88",
      "instruction": "MOV EAX,dword ptr [EDX + 0x58]"
    },
    {
      "address": "0102df8b",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0102df8d",
      "instruction": "CALL EAX"
    },
    {
      "address": "0102df8f",
      "instruction": "MOV ECX,dword ptr [ESP + 0x9c]"
    },
    {
      "address": "0102df96",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "0102df98",
      "instruction": "CMP EAX,0x12293370"
    },
    {
      "address": "0102df9d",
      "instruction": "JG 0x0102e8f7"
    },
    {
      "address": "0102dfa3",
      "instruction": "JZ 0x0102e8bf"
    },
    {
      "address": "0102dfa9",
      "instruction": "CMP EAX,0xc049e8b5"
    },
    {
      "address": "0102dfae",
      "instruction": "JG 0x0102e274"
    },
    {
      "address": "0102dfb4",
      "instruction": "JZ 0x0102ec61"
    },
    {
      "address": "0102dfba",
      "instruction": "CMP EAX,0x9320dbba"
    },
    {
      "address": "0102dfbf",
      "instruction": "JG 0x0102e045"
    },
    {
      "address": "0102dfc5",
      "instruction": "JZ 0x0102e02c"
    },
    {
      "address": "0102dfc7",
      "instruction": "CMP EAX,0x86eb5442"
    },
    {
      "address": "0102dfcc",
      "instruction": "JZ 0x0102e01c"
    },
    {
      "address": "0102dfce",
      "instruction": "CMP EAX,0x8a43c6d9"
    },
    {
      "address": "0102dfd3",
      "instruction": "JZ 0x0102dffc"
    },
    {
      "address": "0102dfd5",
      "instruction": "CMP EAX,0x8a820a27"
    },
    {
      "address": "0102dfda",
      "instruction": "JNZ 0x0102f0ae"
    },
    {
      "address": "0102dfe0",
      "instruction": "MOV ECX,dword ptr [ESP + 0xa0]"
    },
    {
      "address": "0102dfe7",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0102dfe8",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0102dfe9",
      "instruction": "CALL 0x0102caa0"
    },
    {
      "address": "0102dfee",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "0102dff1",
      "instruction": "POP EDI"
    },
    {
      "address": "0102dff2",
      "instruction": "POP ESI"
    },
    {
      "address": "0102dff3",
      "instruction": "POP EBP"
    },
    {
      "address": "0102dff4",
      "instruction": "POP EBX"
    },
    {
      "address": "0102dff5",
      "instruction": "ADD ESP,0x88"
    },
    {
      "address": "0102dffb",
      "instruction": "RET"
    },
    {
      "address": "0102dffc",
      "instruction": "MOV ECX,dword ptr [ESI + 0x13c]"
    },
    {
      "address": "0102e002",
      "instruction": "CALL 0x00b8de30"
    },
    {
      "address": "0102e007",
      "instruction": "PUSH EAX"
    }
[TRUNCATED]
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
  "original_bytes": 13141,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl observed; no implicit this parameter\",\n    \"return_observation\": \"The function has void live decompilation and returns through ordinary RET paths.\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"observed_use\": \"Loaded into ECX from the first stack slot and dereferenced at offset 0 to select a large event-code dispatch.\",\n        \"position\": 1,\n        \"type\": \"SpaceEvent *\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"observed_use\": \"Loaded from the second stack slot and forwarded to branch helpers and FUN_0102d1b0.\",\n        \"position\": 2,\n        \"type\": \"Space *\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x0C\",\n        \"observed_use\": \"Loaded from the third stack slot, null-checked in selected paths, and forwarded to event/cleanup helpers.\",\n        \"position\": 3,\n        \"type\": \"SpaceContext *\",\n        \"width_bytes\": 4\n      }\n    ]\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:Space *,SpaceContext,SpaceContext *\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 14,\n      \"symbol\": \"FUN_0102d1b0\",\n      \"va\": \"0x0102d1b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:cCommEvent,cCommManager\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 9,\n      \"symbol\": \"Simulator_cCommManager_CreateAndDispatchEvent_00aeb720\",\n      \"va\": \"0x00aeb720\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:cCommEvent,cCommManager\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00aeb160\",\n      \"va\": \"0x00aeb160\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 3,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-A2-PROGRESSION-ALTERNATIVE\",\n      \"score\": 3,\n      \"symbol\": \"achievement_progress_update_00676e90\",\n      \"va\": \"0x00676e90\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:cCommManager\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00aea230\",\n      \"va\": \"0x00aea230\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:cCommEvent\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00aea250\",\n      \"va\": \"0x00aea250\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:cCommEvent\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00aea5d0\",\n      \"va\": \"0x00aea5d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"Concrete event, Space, and context layouts require additional direct xrefs, caller analysis, and runtime/differential evidence.\",\n    \"No body implementation is permitted in this phase; only the opaque declarations are staged.\",\n    \"The Ghidra function prototype is currently undefined, so applying a named event subtype or payload type to the analysis database would exceed the observed evidence.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"address_window_offset_005c65e0\",\n        \"reconstructed\": true,\n        \"va\": \"0x005c65e0\"\n      },\n      {\n        \"name\": \"achievement_progress_update_00676e90\",\n        \"reconstructed\": true,\n        \"va\": \"0x00676e90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      },\n      {\n        \"name\": \"Simulator_cCommManager_CreateAndDispatchEvent_00aeb720\",\n        \"reconstructed\": true,\n        \"va\": \"0x00aeb720\"\n      },\n      {\n        \"name\": \"pkg13_creature_accessor_00b1fdb0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b1fdb0\"\n      },\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      },\n      {\n        \"name\": \"FUN_00b3d2c0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b3d2c0\"\n      },\n      {\n        \"name\": \"FUN_00b3d300\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d300\"\n      },\n      {\n        \"name\": \"Simulator_cSpaceTrading_Get\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d4d0\"\n      },\n      {\n        \"name\": \"FUN_00b8dab0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b8dab0\"\n      },\n      {\n        \"name\": \"FUN_00b8de30\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b8de30\"\n      },\n      {\n        \"name\": \"Simulator_LookupEmpireByPoliticalId\",\n        \"reconstructed\": true,\n        \"va\": \"0x00ba9370\"\n      },\n      {\n        \"name\": \"FUN_00bba790\",\n        \"reconstructed\": false,\n        \"va\": \"0x00bba790\"\n      },\n      {\n        \"name\": \"FUN_00c31730\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c31730\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c485b0\"\n      },\n      {\n        \"name\": \"FUN_00c77bf0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c77bf0\"\n      },\n      {\n        \"name\"
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
  "body_end": "0102f0b8",
  "body_span_bytes": 4505,
  "body_start": "0102df20",
  "callees": [
    "FUN_01021230",
    "FUN_0102caa0",
    "FUN_00c559c0",
    "FUN_00c313d0",
    "Simulator::cSpaceTrading::Get",
    "j_Sim_cCommManager_CreateSpaceCommEvent",
    "FUN_0102fa30",
    "FUN_00d00a70",
    "FUN_00c46e20",
    "FUN_0102cd90",
    "FUN_010407d0",
    "FUN_0102d1b0",
    "thunk_FUN_00c44f20",
    "FUN_00d06920",
    "App::IAppSystem::Get",
    "FUN_00ae09b0",
    "FUN_00c8d000",
    "FUN_0102b690",
    "FUN_01030930",
    "FUN_00c59d90",
    "FUN_01021260",
    "FUN_00fe5430",
    "FUN_00d05830",
    "FUN_00c485e0",
    "FUN_00b3d2c0",
    "FUN_01030650",
    "FUN_00c8c9d0",
    "FUN_00bba790",
    "FUN_00a206f0",
    "Pollinator::cAchievementsManager::SetProgressFlags",
    "FUN_01044640",
    "FUN_00d038e0",
    "FUN_00aed3f0",
    "FUN_010019a0",
    "FUN_00675250",
    "FUN_00aea210",
    "FUN_00c7be30",
    "FUN_00ad49b0",
    "FUN_0102cd40",
    "FUN_00c485d0",
    "FUN_010393a0",
    "FUN_0050d440",
    "FUN_01021300",
    "FUN_00c31a00",
    "FUN_00c485b0",
    "FUN_00b8dab0",
    "FUN_00e39ab0",
    "FUN_00b3d2a0",
    "FUN_0102d150",
    "FUN_00b3d300",
    "FUN_00ad79d0",
    "FUN_0102f810",
    "FUN_00f67d90",
    "FUN_00c59f60",
    "FUN_0102c9e0",
    "FUN_005c65e0",
    "FUN_00d06240",
    "FUN_00c31730",
    "FUN_01021080",
    "FUN_0102daa0",
    "FUN_00bfc5f0",
    "FUN_00c57ef0",
    "FUN_0102cc30",
    "FUN_00ad7ad0",
    "FUN_00ae0930",
    "FUN_00c4f040",
    "FUN_0106ac90",
    "FUN_010407c0",
    "FUN_00c8b920",
    "FUN_00b1fdb0",
    "FUN_00c485f0",
    "FUN_0102d0b0",
    "FUN_00c8b770",
    "FUN_00ce6950",
    "FUN_00ba6dc0",
    "FUN_0102cf10",
    "FUN_00c77bf0",
    "FUN_00c30c60",
    "FUN_01021240",
    "FUN_01002bd0",
    "FUN_00ba6490",
    "FUN_00aeb3e0",
    "FUN_00a1ad60",
    "FUN_0102c980",
    "FUN_0102d7e0",
    "FUN_01021090",
    "FUN_01037f20",
    "FUN_00c485c0",
    "FUN_0102ce30",
    "FUN_0102cd30",
    "FUN_00ff45e0",
    "FUN_004e1bf0",
    "FUN_010027b0",
    "FUN_00b8de30",
    "FUN_00b3d4a0",
    "FUN_00c30bb0",
    "FUN_00ba9370",
    "FUN_0102d820",
    "FUN_00c59eb0",
    "FUN_00c59f00",
    "FUN_0102cae0",
    "FUN_0102c9c0",
    "FUN_01030390",
    "FUN_00ffbe50"
  ],
  "callers": [
    "FUN_00aeb7b0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0102df20",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_0102df20",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc2df20",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0102df20(void)",
  "size_bytes": 4505,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0102df20",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00aeb7da"
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
  "files": [],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg12-space/0102df20.json"
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "GameSpace",
  "Space *",
  "SpaceContext",
  "SpaceContext *",
  "SpaceEvent *",
  "cCommEvent",
  "cCommManager",
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
    "anchors": [
      "0x00aeb160",
      "0x00aebe90",
      "0x00aed2c0",
      "0x00c75520",
      "0x00dd5160",
      "0x0102c9e0",
      "0x0102caa0",
      "0x0102cae0",
      "0x0102cc30",
      "0x0102cd90",
      "0x0102ce30",
      "0x0102cf10",
      "0x0102d1b0",
      "0x0102df20",
      "0x01072d40",
      "0x00aeb730"
    ],
    "conflict_id": "LC-006",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_SUPPORTED",
    "resolution_status": "RESOLVED_SUPPORTED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x00AEB720 communication wrapper",
    "unresolved_reason": "The exact private wrapper name and the full parameter types are not recoverable from static naming alone; the create-and-dispatch contract is resolved."
  }
]
```
