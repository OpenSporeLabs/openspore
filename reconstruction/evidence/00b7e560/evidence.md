# Evidence 0x00b7e560

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `6c7301064823d47105d17b83afb0fdcf18fbaddf0861b842d24e249785a11c0d`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl",
  "hidden_this_register": "none",
  "receiver": "ECX",
  "return": "float",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "direction",
      "position": 1,
      "type": "float*"
    }
  ],
  "stack_cleanup_bytes": 0,
  "termination": "plain RET"
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
    "calling_convention": "__cdecl",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": false,
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
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
    "unparsed_lines_present: 3 line(s) matched no grammar rule",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "5fdaf5f6ea1e61e4124f11c16f99c83b6f38e665114e9cb78b32398e832ea121",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__cdecl",
    "candidate_conventions": [
      "__cdecl",
      "__thiscall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "cdecl"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0034"
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
        "obs-0029"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0034"
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
        "obs-0029",
        "obs-0034"
      ],
      "claim": "calling convention is __cdecl: the caller cleans the stack and at least one entry slot is read",
      "confidence": "INFERRED",
      "id": "C9",
      "value": "__cdecl"
    },
    {
      "based_on": [
        "obs-0029"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00b7e560",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00b7e560",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00b7e563",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,0x1601760",
      "reg": "ECX",
      "write_kind": "imm"
    },
    {
      "at": "0x00b7e568",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x009360d0",
      "target": "0x009360d0"
    },
    {
      "at": "0x00b7e56d",
      "id": "obs-0005",
      "index": 3,
      "kind": "UNPARSED",
      "raw": "ST0,ST0",
      "reason": "unknown_mnemonic"
    },
    {
      "at": "0x00b7e590",
      "count": 11,
      "first_use": 17,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 17,
      "kind": "REG_READ",
      "raw": "FSTP float ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00b7e590",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0007",
      "index": 17,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "FSTP float ptr [ESP + 0x4]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x00b7e594",
      "id": "obs-0008",
      "index": 18,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x009360d0",
      "target": "0x009360d0"
    },
    {
      "at": "0x00b7e599",
      "id": "obs-0009",
      "index": 19,
      "kind": "UNPARSED",
      "raw": "ST0,ST0",
      "reason": "unknown_mnemonic"
    },
    {
      "at": "0x00b7e5bc",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0010",
      "index": 33,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "FSTP float ptr [ESP + 0x8]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x00b7e5c0",
      "id": "obs-0011",
      "index": 34,
      "kin
[TRUNCATED]
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
    "va": "0x00b81720"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b81780"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b81a40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b84730"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4c790"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4fc00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cb5770"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d5cfd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d5ef80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e5cae0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e6ff60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e75350"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01007bf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0105b350"
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
  "count": 83,
  "instructions": [
    {
      "address": "00b7e560",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "00b7e563",
      "instruction": "MOV ECX,0x1601760"
    },
    {
      "address": "00b7e568",
      "instruction": "CALL 0x009360d0"
    },
    {
      "address": "00b7e56d",
      "instruction": "FADD ST0,ST0"
    },
    {
      "address": "00b7e56f",
      "instruction": "FLD1"
    },
    {
      "address": "00b7e571",
      "instruction": "FSUB ST1,ST0"
    },
    {
      "address": "00b7e573",
      "instruction": "FXCH"
    },
    {
      "address": "00b7e575",
      "instruction": "FCOMI ST0,ST1"
    },
    {
      "address": "00b7e577",
      "instruction": "JNC 0x00b7e589"
    },
    {
      "address": "00b7e579",
      "instruction": "FSTP ST1"
    },
    {
      "address": "00b7e57b",
      "instruction": "FLD double ptr [0x01454410]"
    },
    {
      "address": "00b7e581",
      "instruction": "FCOMI ST0,ST1"
    },
    {
      "address": "00b7e583",
      "instruction": "JBE 0x00b7e589"
    },
    {
      "address": "00b7e585",
      "instruction": "FSTP ST1"
    },
    {
      "address": "00b7e587",
      "instruction": "JMP 0x00b7e58b"
    },
    {
      "address": "00b7e589",
      "instruction": "FSTP ST0"
    },
    {
      "address": "00b7e58b",
      "instruction": "MOV ECX,0x1601760"
    },
    {
      "address": "00b7e590",
      "instruction": "FSTP float ptr [ESP + 0x4]"
    },
    {
      "address": "00b7e594",
      "instruction": "CALL 0x009360d0"
    },
    {
      "address": "00b7e599",
      "instruction": "FADD ST0,ST0"
    },
    {
      "address": "00b7e59b",
      "instruction": "FLD1"
    },
    {
      "address": "00b7e59d",
      "instruction": "FSUB ST1,ST0"
    },
    {
      "address": "00b7e59f",
      "instruction": "FXCH"
    },
    {
      "address": "00b7e5a1",
      "instruction": "FCOMI ST0,ST1"
    },
    {
      "address": "00b7e5a3",
      "instruction": "JNC 0x00b7e5b5"
    },
    {
      "address": "00b7e5a5",
      "instruction": "FSTP ST1"
    },
    {
      "address": "00b7e5a7",
      "instruction": "FLD double ptr [0x01454410]"
    },
    {
      "address": "00b7e5ad",
      "instruction": "FCOMI ST0,ST1"
    },
    {
      "address": "00b7e5af",
      "instruction": "JBE 0x00b7e5b5"
    },
    {
      "address": "00b7e5b1",
      "instruction": "FSTP ST1"
    },
    {
      "address": "00b7e5b3",
      "instruction": "JMP 0x00b7e5b7"
    },
    {
      "address": "00b7e5b5",
      "instruction": "FSTP ST0"
    },
    {
      "address": "00b7e5b7",
      "instruction": "MOV ECX,0x1601760"
    },
    {
      "address": "00b7e5bc",
      "instruction": "FSTP float ptr [ESP + 0x8]"
    },
    {
      "address": "00b7e5c0",
      "instruction": "CALL 0x009360d0"
    },
    {
      "address": "00b7e5c5",
      "instruction": "FADD ST0,ST0"
    },
    {
      "address": "00b7e5c7",
      "instruction": "FLD1"
    },
    {
      "address": "00b7e5c9",
      "instruction": "FSUB ST1,ST0"
    },
    {
      "address": "00b7e5cb",
      "instruction": "FXCH"
    },
    {
      "address": "00b7e5cd",
      "instruction": "FCOMI ST0,ST1"
    },
    {
      "address": "00b7e5cf",
      "instruction": "JNC 0x00b7e5e1"
    },
    {
      "address": "00b7e5d1",
      "instruction": "FSTP ST1"
    },
    {
      "address": "00b7e5d3",
      "instruction": "FLD double ptr [0x01454410]"
    },
    {
      "address": "00b7e5d9",
      "instruction": "FCOMI ST0,ST1"
    },
    {
      "address": "00b7e5db",
      "instruction": "JBE 0x00b7e5e1"
    },
    {
      "address": "00b7e5dd",
      "instruction": "FSTP ST1"
    },
    {
      "address": "00b7e5df",
      "instruction": "JMP 0x00b7e5e3"
    },
    {
      "address": "00b7e5e1",
      "instruction": "FSTP ST0"
    },
    {
      "address": "00b7e5e3",
      "instruction": "MOVSS XMM2,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00b7e5e9",
      "instruction": "FSTP float ptr [ESP + 0xc]"
    },
    {
      "address": "00b7e5ed",
      "instruction": "MOVSS XMM3,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00b7e5f3",
      "instruction": "MOVSS XMM4,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00b7e5f9",
      "instruction": "MOVAPS XMM0,XMM3"
    },
    {
      "address": "00b7e5fc",
      "instruction": "MULSS XMM0,XMM3"
    },
    {
      "address": "00b7e600",
      "instruction": "MOVAPS XMM1,XMM2"
    },
    {
      "address": "00b7e603",
      "instruction": "MULSS XMM1,XMM2"
    },
    {
      "address": "00b7e607",
      "instruction": "ADDSS XMM0,XMM1"
    },
    {
      "address": "00b7e60b",
      "instruction": "MOVAPS XMM1,XMM4"
    },
    {
      "address": "00b7e60e",
      "instruction": "MULSS XMM1,XMM4"
    },
    {
      "address": "00b7e612",
      "instruction": "ADDSS XMM0,XMM1"
    },
    {
      "address": "00b7e616",
      "instruction": "COMISS XMM0,dword ptr [0x01485720]"
    },
    {
      "address": "00b7e61d",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00b7e622",
      "instruction": "JA 0x00b7e563"
    },
    {
      "address": "00b7e628",
      "instruction": "MOVSS XMM1,dword ptr [0x013ebca0]"
    },
    {
      "address": "00b7e630",
      "instruction": "COMISS XMM1,XMM0"
    },
    {
      "address": "00b7e633",
      "instruction": "JA 0x00b7e563"
    },
    {
      "address": "00b7e639",
      "instruction": "FLD float ptr [ESP]"
    },
    {
      "address": "00b7e63c",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00b7e640",
      "instruction": "FSQRT"
    },
    {
      "address": "00b7e642",
      "instruction": "FLD1"
    },
    {
      "address": "00b7e644",
      "instruction": "FDIVRP"
    },
    {
      "address": "00b7e646",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00b7e649",
      "instruction": "MOVSS XMM0,dword ptr [ESP]"
    },
    {
      "address": "00b7e64e",
      "
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
  "original_bytes": 9442,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl\",\n    \"hidden_this_register\": \"none\",\n    \"receiver\": \"ECX\",\n    \"return\": \"float\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"direction\",\n        \"position\": 1,\n        \"type\": \"float*\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"plain RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-14-A3-WORLD-WAVE3\",\n      \"score\": 8,\n      \"symbol\": \"solar_system_load_00c86760\",\n      \"va\": \"0x00c86760\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"simulator_game_input_manager_get_00b3d350\",\n      \"va\": \"0x00b3d350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-C4-CIV-WAVE3\",\n      \"score\": 2,\n      \"symbol\": \"city_building_economy_update_00be2440\",\n      \"va\": \"0x00be2440\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 2,\n      \"symbol\": \"SpeciesProfileSelector_00c30cc0\",\n      \"va\": \"0x00c30cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 2,\n      \"symbol\": \"ArchetypeRelationshipsID_00c30e20\",\n      \"va\": \"0x00c30e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 2,\n      \"symbol\": \"PoliticalOwnershipScan_00c8d060\",\n      \"va\": \"0x00c8d060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 2,\n      \"symbol\": \"RelationshipScoreBand_00d00d00\",\n      \"va\": \"0x00d00d00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"cell_mode_constructor_00e616c0\",\n      \"va\": \"0x00e616c0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No original-process runtime trace is available for the opaque render sample service.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b81720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b81780\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b81a40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b84730\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4c790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4fc00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cb5770\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d5cfd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d5ef80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e5cae0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e6ff60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e75350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01007bf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0105b350\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b8172b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b81720\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b817c8\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b81780\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b81a88\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b81a40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b8473c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b84730\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b847dd\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b84730\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c4c81a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c4c790\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c4fd19\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c4fc00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c4fe0c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c4fc00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00cb58c7\",\n        \"direction\": \"in\",\n        \"o
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
  "body_end": "00b7e671",
  "body_span_bytes": 274,
  "body_start": "00b7e560",
  "callees": [
    "FUN_009360d0"
  ],
  "callers": [
    "FUN_00e6ff60",
    "FUN_00d5cfd0",
    "FUN_00e75350",
    "FUN_00b81a40",
    "FUN_00e5cae0",
    "FUN_00b84730",
    "FUN_00b81720",
    "FUN_00c4fc00",
    "FUN_00c4c790",
    "FUN_00d5ef80",
    "FUN_0105b350",
    "FUN_00cb5770",
    "Simulator::cPlanetModel::ToSurface",
    "FUN_01007bf0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b7e560",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00b7e560",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x77e560",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b7e560(void)",
  "size_bytes": 274,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b7e560",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 19,
  "xrefs": [
    {
      "from": "00d5f18e"
    },
    {
      "from": "00b817c8"
    },
    {
      "from": "00b8172b"
    },
    {
      "from": "00b8473c"
    },
    {
      "from": "00b847dd"
    },
    {
      "from": "00b81a88"
    },
    {
      "from": "00c4c81a"
    },
    {
      "from": "00c4fd19"
    },
    {
      "from": "00c4fe0c"
    },
    {
      "from": "00cb58c7"
    },
    {
      "from": "00d5d241"
    },
    {
      "from": "00e5cae4"
    },
    {
      "from": "00e75474"
    },
    {
      "from": "00e75647"
    },
    {
      "from": "01007cec"
    },
    {
      "from": "0105b4b8"
    },
    {
      "from": "00e700f0"
    },
    {
      "from": "00dc2a34"
    },
    {
      "from": "00dc2cd7"
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
  "files": [
    "reconstruction/staging/pkg14-a3-world-wave3/world_wave3.cpp",
    "reconstruction/staging/pkg14-a3-world-wave3/world_wave3.hpp",
    "reconstruction/staging/pkg14-a3-world-wave3/world_wave3_model_test.cpp",
    "src/reconstruction/pkg14_a3_world_wave3/world_wave3.cpp",
    "src/reconstruction/pkg14_a3_world_wave3/world_wave3.hpp",
    "src/reconstruction/pkg14_a3_world_wave3/world_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg14-a3-world-wave3/00b7e560.json"
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
    "runtime validation not run"
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
  "OpaqueRenderHelper*",
  "float*",
  "void"
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
