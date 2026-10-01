# Evidence 0x00dd0e10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `452016d4a4e0451400c5ac3d6eb9a92e23dcbe3fbed02cec82a793d420bb68f7`

## abi

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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0xb",
      "entry_ESP+0x23",
      "entry_ESP+0x34",
      "entry_ESP+0x3c",
      "entry_ESP+0x44"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0xb",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x23",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x44",
        "observed": true,
        "ordinal": 17,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0xb",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x23",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x44",
        "observed": true,
        "ordinal": 17,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -68, so the listing is not one path",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "2416c4a48c98b320e11eea6fface8e184978189e1fdcc5fafdc5d9223d863dde",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 9,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0034",
        "obs-0053",
        "obs-0078"
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
        "obs-0054",
        "obs-0056",
        "obs-0058",
        "obs-0060",
        "obs-0061",
        "obs-0063",
        "obs-0065",
        "obs-0067"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 12,
        "observed_slots": 5,
        "total_bytes": 68
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0019",
        "obs-0021",
        "obs-0023",
        "obs-0027",
        "obs-0030",
        "obs-0037",
        "obs-0041",
        "obs-0044",
        "obs-0048",
        "obs-0056",
        "obs-0060",
        "obs-0063",
        "obs-0067"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          132,
          136,
          156,
          292
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0019",
        "obs-0021",
        "obs-0023",
        "obs-0027",
        "obs-0030",
        "obs-0034",
        "obs-0037",
        "obs-0041",
        "obs-0044",
        "obs-0048",
        "obs-0053",
        "obs-0056",
        "obs-0060",
        "obs-0063",
        "obs-0067",
        "obs-0078"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in EC
[TRUNCATED]
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0xb",
      "entry_ESP+0x23",
      "entry_ESP+0x34",
      "entry_ESP+0x3c",
      "entry_ESP+0x44"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0xb",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x23",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x44",
        "observed": true,
        "ordinal": 17,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0xb",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x23",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x3c",
        "observed": true,
        "ordinal": 15,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x44",
        "observed": true,
        "ordinal": 17,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -68, so the listing is not one path",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "2416c4a48c98b320e11eea6fface8e184978189e1fdcc5fafdc5d9223d863dde",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 9,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0034",
        "obs-0053",
        "obs-0078"
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
        "obs-0054",
        "obs-0056",
        "obs-0058",
        "obs-0060",
        "obs-0061",
        "obs-0063",
        "obs-0065",
        "obs-0067"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 12,
        "observed_slots": 5,
        "total_bytes": 68
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0019",
        "obs-0021",
        "obs-0023",
        "obs-0027",
        "obs-0030",
        "obs-0037",
        "obs-0041",
        "obs-0044",
        "obs-0048",
        "obs-0056",
        "obs-0060",
        "obs-0063",
        "obs-0067"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          132,
          136,
          156,
          292
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0019",
        "obs-0021",
        "obs-0023",
        "obs-0027",
        "obs-0030",
        "obs-0034",
        "obs-0037",
        "obs-0041",
        "obs-0044",
        "obs-0048",
        "obs-0053",
        "obs-0056",
        "obs-0060",
        "obs-0063",
        "obs-0067",
        "obs-0078"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in EC
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
    "name": "FUN_00b8de30",
    "reconstructed": false,
    "va": "0x00b8de30"
  },
  {
    "name": "Simulator_LookupEmpireByPoliticalId",
    "reconstructed": true,
    "va": "0x00ba9370"
  }
]
```

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
  "count": 191,
  "instructions": [
    {
      "address": "00dd0e10",
      "instruction": "SUB ESP,0x58"
    },
    {
      "address": "00dd0e13",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00dd0e14",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00dd0e16",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00dd0e18",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00dd0e1b",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00dd0e1c",
      "instruction": "CALL EDX"
    },
    {
      "address": "00dd0e1e",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00dd0e20",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00dd0e22",
      "instruction": "JZ 0x00dd1054"
    },
    {
      "address": "00dd0e28",
      "instruction": "MOV EAX,dword ptr [ESI + 0x84]"
    },
    {
      "address": "00dd0e2e",
      "instruction": "DEC EAX"
    },
    {
      "address": "00dd0e2f",
      "instruction": "CMP EAX,0x4"
    },
    {
      "address": "00dd0e32",
      "instruction": "JA 0x00dd1054"
    },
    {
      "address": "00dd0e38",
      "instruction": "JMP dword ptr [EAX*0x4 + 0xdd105c]"
    },
    {
      "address": "00dd0e3f",
      "instruction": "MOV EAX,0x1667bac"
    },
    {
      "address": "00dd0e44",
      "instruction": "MOV dword ptr [ESP + 0x50],EAX"
    },
    {
      "address": "00dd0e48",
      "instruction": "MOV dword ptr [ESP + 0x54],EAX"
    },
    {
      "address": "00dd0e4c",
      "instruction": "MOV EAX,dword ptr [ESI + 0x88]"
    },
    {
      "address": "00dd0e52",
      "instruction": "SUB EAX,0x2"
    },
    {
      "address": "00dd0e55",
      "instruction": "MOV dword ptr [ESP + 0x58],0x1667bae"
    },
    {
      "address": "00dd0e5d",
      "instruction": "MOV dword ptr [ESP + 0x4c],0xcaa303ac"
    },
    {
      "address": "00dd0e65",
      "instruction": "JZ 0x00dd0e82"
    },
    {
      "address": "00dd0e67",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00dd0e6a",
      "instruction": "JNZ 0x00dd0ed0"
    },
    {
      "address": "00dd0e6c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00dd0e6d",
      "instruction": "LEA ECX,[ESP + 0x54]"
    },
    {
      "address": "00dd0e71",
      "instruction": "CALL 0x005c3d90"
    },
    {
      "address": "00dd0e76",
      "instruction": "PUSH 0x1464c3c"
    },
    {
      "address": "00dd0e7b",
      "instruction": "PUSH 0x94acb6f7"
    },
    {
      "address": "00dd0e80",
      "instruction": "JMP 0x00dd0e96"
    },
    {
      "address": "00dd0e82",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00dd0e83",
      "instruction": "LEA ECX,[ESP + 0x54]"
    },
    {
      "address": "00dd0e87",
      "instruction": "CALL 0x005c3d90"
    },
    {
      "address": "00dd0e8c",
      "instruction": "PUSH 0x1464c50"
    },
    {
      "address": "00dd0e91",
      "instruction": "PUSH 0x595b72b"
    },
    {
      "address": "00dd0e96",
      "instruction": "ADD ESI,0x9c"
    },
    {
      "address": "00dd0e9c",
      "instruction": "PUSH 0xad56080c"
    },
    {
      "address": "00dd0ea1",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00dd0ea3",
      "instruction": "CALL 0x006b54b0"
    },
    {
      "address": "00dd0ea8",
      "instruction": "CALL 0x0067de40"
    },
    {
      "address": "00dd0ead",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00dd0eaf",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00dd0eb1",
      "instruction": "MOV EAX,dword ptr [EDX + 0x20]"
    },
    {
      "address": "00dd0eb4",
      "instruction": "CALL EAX"
    },
    {
      "address": "00dd0eb6",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00dd0eb8",
      "instruction": "MOV EDX,dword ptr [EDX + 0x30]"
    },
    {
      "address": "00dd0ebb",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00dd0ebd",
      "instruction": "LEA ECX,[ESP + 0x50]"
    },
    {
      "address": "00dd0ec1",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00dd0ec2",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00dd0ec3",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00dd0ec5",
      "instruction": "CALL EDX"
    },
    {
      "address": "00dd0ec7",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00dd0ec9",
      "instruction": "CALL 0x006b55c0"
    },
    {
      "address": "00dd0ece",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00dd0ed0",
      "instruction": "LEA ECX,[ESP + 0x4c]"
    },
    {
      "address": "00dd0ed4",
      "instruction": "CALL 0x006886e0"
    },
    {
      "address": "00dd0ed9",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00dd0edb",
      "instruction": "POP EDI"
    },
    {
      "address": "00dd0edc",
      "instruction": "POP ESI"
    },
    {
      "address": "00dd0edd",
      "instruction": "ADD ESP,0x58"
    },
    {
      "address": "00dd0ee0",
      "instruction": "RET"
    },
    {
      "address": "00dd0ee1",
      "instruction": "MOV EAX,dword ptr [ESI + 0x88]"
    },
    {
      "address": "00dd0ee7",
      "instruction": "CMP EAX,0x53dbcf1"
    },
    {
      "address": "00dd0eec",
      "instruction": "JZ 0x00dd0f2d"
    },
    {
      "address": "00dd0eee",
      "instruction": "CMP EAX,0x53dbcf3"
    },
    {
      "address": "00dd0ef3",
      "instruction": "JZ 0x00dd0f2d"
    },
    {
      "address": "00dd0ef5",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00dd0ef7",
      "instruction": "LEA EAX,[ESP + 0xb]"
    },
    {
      "address": "00dd0efb",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00dd0efc",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00dd0eff",
      "instruction": "
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
  "original_bytes": 18125,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x0147cbbc\",\n        \"same_semantic_family\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 15,\n      \"symbol\": \"FUN_00ff3f00\",\n      \"va\": \"0x00ff3f00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 8,\n      \"symbol\": \"pkg20_gameglobal_00ba83a0\",\n      \"va\": \"0x00ba83a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 8,\n      \"symbol\": \"pkg20_gameglobal_00ba8420\",\n      \"va\": \"0x00ba8420\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 8,\n      \"symbol\": \"map_int_whatever_find\",\n      \"va\": \"0x00e5c780\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147cbbc\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147cbbc\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147cbbc\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_name_00641810\",\n      \"va\": \"0x00641810\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0147cbbc\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_id_00641820\",\n      \"va\": \"0x00641820\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": true,\n  \"blockers\": [],\n  \"body_status\": \"runtime_gated\",\n  \"class_type\": \"OpaqueGameObject\",\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": 0.6,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"address_window_offset_005c65e0\",\n        \"reconstructed\": true,\n        \"va\": \"0x005c65e0\"\n      },\n      {\n        \"name\": \"pkg13_creature_accessor_00b1fdb0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b1fdb0\"\n      },\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      },\n      {\n        \"name\": \"FUN_00b8de30\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b8de30\"\n      },\n      {\n        \"name\": \"Simulator_LookupEmpireByPoliticalId\",\n        \"reconstructed\": true,\n        \"va\": \"0x00ba9370\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00dd0f08\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041df50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0f40\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041df50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0fa1\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041df50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0fd9\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041df50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0e71\",\n        \"direction\": \"out\",\n        \"other\": \"0x005c3d90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0e87\",\n        \"direction\": \"out\",\n        \"other\": \"0x005c3d90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd104d\",\n        \"direction\": \"out\",\n        \"other\": \"0x005c65e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0ea8\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0ed4\",\n        \"direction\": \"out\",\n        \"other\": \"0x006886e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0ea3\",\n        \"direction\": \"out\",\n        \"other\": \"0x006b54b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0ec9\",\n        \"direction\": \"out\",\n        \"other\": \"0x006b55c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0f6d\",\n        \"direction\": \"out\",\n        \"other\": \"0x006b55c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0f66\",\n        \"direction\": \"out\",\n        \"other\": \"0x00933960\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd1035\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b1fdb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd103b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d2a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dd0f22\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b6ec50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n 
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
  "body_end": "00dd105b",
  "body_span_bytes": 588,
  "body_start": "00dd0e10",
  "callees": [
    "FUN_005c65e0",
    "FUN_0041df50",
    "FUN_006b54b0",
    "FUN_00b3d2a0",
    "FUN_00b6ec50",
    "FUN_005c3d90",
    "FUN_00b8de30",
    "FUN_006b55c0",
    "FUN_00ba9370",
    "FUN_0067de40",
    "FUN_00933960",
    "FUN_006886e0",
    "FUN_00b8d8f0",
    "FUN_00bb9ae0",
    "FUN_00b1fdb0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00dd0e10",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00dd0e10",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x9d0e10",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00dd0e10(void)",
  "size_bytes": 588,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00dd0e10",
  "vtables": {
    "referenced_by_vtables": [
      "0x0147cbbc"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0147cbe0"
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
  "blocking_reason": [
    "owner type",
    "field meanings",
    "vtable implementation",
    "returned object identity"
  ],
  "gates": [
    "indirect_dispatch_state_observation"
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
  "original_bytes": 8765,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": 0.83\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 15,\n  \"evidence\": [\n    {\n      \"finding\": \"Null gate, +0x84/+0x88 switch, ~Epic/~MiniBoss strings, local record construction, and empire lookup branch.\",\n      \"kind\": \"target_decompilation\",\n      \"source\": \"Ghidra 0x00dd0e10\"\n    },\n    {\n      \"finding\": \"The method belongs to a concrete vtable installed on the timeline-event data object and is released by its destructor.\",\n      \"kind\": \"constructor_destructor\",\n      \"source\": \"Ghidra 0x00dd0ca0 and 0x00dd0cf0\"\n    },\n    {\n      \"finding\": \"Allocates UI/TimelineEventSporepediaData at 0xb0 or 0x9c and dispatches its vtable.\",\n      \"kind\": \"allocation_anchor\",\n      \"source\": \"Ghidra 0x00e2f6e0\"\n    },\n    {\n      \"finding\": \"Creates the same timeline-event data family and calls its virtual operations during local event setup.\",\n      \"kind\": \"representative_consumer\",\n      \"source\": \"Ghidra 0x00e47930\"\n    },\n    {\n      \"finding\": \"The candidate cSPAssetDataOTDB is 0x78 bytes; the target accesses fields beyond its end and the observed allocation is 0xb0/0x9c.\",\n      \"kind\": \"structure_separator\",\n      \"source\": \"Ghidra cSPAssetDataOTDB layout\"\n    },\n    {\n      \"finding\": \"No cSPAssetDataOTDB constructor, network call, cCommEvent constructor, or universal event queue is attached to this method.\",\n      \"kind\": \"negative_family_check\",\n      \"source\": \"Ghidra direct callees and data references\"\n    }\n  ],\n  \"family\": \"sporepedia_timeline_event_data\",\n  \"interfaces\": {\n    \"boundaries\": {\n      \"boundary_rule\": \"Keep visible labels, local communication state, and empire lookup as family-specific effects; do not infer online Sporepedia request/response behavior.\",\n      \"local\": \"The receiver and all direct callees are local timeline, UI, communication, and simulator lookup services.\",\n      \"network\": {\n        \"evidence\": [\n          \"The direct body contains local string labels and local service calls but no socket, HTTP, protocol, or online request path.\",\n          \"The surrounding object is allocated as UI/TimelineEventSporepediaData in local consumers.\"\n        ],\n        \"status\": \"no_direct_network_edge\"\n      }\n    },\n    \"direct_callees\": [],\n    \"direct_callers\": [],\n    \"globals\": [],\n    \"structures\": [],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": [],\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [\n        \"TimelineEventSporepediaData-like receiver\",\n        \"receiver+0x84 discriminator\",\n        \"receiver+0x88 subtype or companion selector\",\n        \"receiver+0x9c event payload candidate\"\n      ],\n      \"ordering\": [],\n      \"outputs\": [\n        \"integer result from the selected local path\",\n        \"possible local visible label/message emission\",\n        \"local communication/event-state mutation\"\n      ],\n      \"postconditions\": [\n        \"For the subtype-1 branch, the local service/UI path may emit ~Epic or ~MiniBoss.\",\n        \"For subtype-2 and subtype-4 branches, the method builds a local record through FUN_00b6ec50 and then returns through the local event path.\",\n        \"For subtype-5, the method consults the current noun/empire lookup path and returns an empire-related value or early result.\"\n      ],\n      \"preconditions\": [\n        \"The virtual call at receiver vtable+0x0c must return a non-zero local object or value; otherwise the method returns 0.\",\n        \"The exact meaning of the +0x84 and +0x88 discriminators is not named.\"\n      ],\n      \"purpose\": \"LOCAL_TIMELINE_EVENT_VARIANT_HANDLER\",\n      \"return\": {\n        \"status\": \"not_reported\"\n      },\n      \"side_effects\": [\n        \"Calls FUN_005c3d90, FUN_006b54b0, FUN_006b55c0, FUN_00b6ec50, and local communication helpers.\",\n        \"May use FUN_00b1fdb0/FUN_00b3d2a0/FUN_00ba9370 and FUN_005c65e0 for the empire-dependent branch.\"\n      ],\n      \"status\": \"partial_static_contract\",\n      \"unresolved\": [\n        \"What are the exact semantic names and allowed values of receiver+0x84 and +0x88?\",\n        \"What type and ownership does the vtable+0x0c result have?\",\n        \"Does receiver+0x9c hold a local event payload, a property list, or an opaque service record?\",\n        \"Are the Epic and MiniBoss labels presentation-only or part of a broader communication state transition?\",\n        \"Which virtual consumer invokes this method in each timeline-event variant?\",\n        \"What do the empire lookup values mean in the subtype-5 path?\"\n      ]\n    }\n  },\n  \"invariants\": {\n    \"failure_semantics\": [],\n    \"invariants\": [],\n    \"invariants_status\": \"not_reported\"\n  },\n  \"name\": \"LOCAL_TIMELINE_EVENT_VARIANT_HANDLER\",\n  \"package\": {\n    \"caveat\": \"not_reported\",\n    \"ownership_status\": \"not_reported\",\n    \"primary\": null,\n    \"secondary\": []\n  },\n  \"readiness\": {\n    \"next_action\": \"not_reported\",\n    \"runtime_performed\": false,\n    \"runtime_promoted\": false,\n    \"runtime_required\": true,\n    \"status\": \"NEEDS_RUNTIME\",\n    \"unlock_requirements\": []\n  },\n  \"source\": \"knowledgegraph/research/semantic-decomp/worker-07-sporepedia-events.json\",\n  \"state_events\": {\n    \"events\": [],\n    \"lifecycle\": {\n      \"lifecycle\": [\n        \"FUN_00dd0ca0 constructs the object and installs the vtable family.\",\n        \"The virtual method obtains a local source/value through vtable+0x0c and rejects a null source.\",\n        \"The +0x84/+0x88 dispatch selects visible-label, local-record, or empire-dependent behavior.\",\n        \"The selected path updat
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
  "status": "blocked"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueGameObject"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0147cbbc"
]
```

## Conflicts

```json
[]
```
