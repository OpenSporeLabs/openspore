# Evidence 0x00bba790

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d1f62b7d0c1fc0e21b509e88e837d90d12fb0ab30ab2f2b4f6412564b7abf248`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_semantics": "unclassified_in_EAX",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
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
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
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
  "content_sha256": "cdde3ba8a42aaf3e2d6a4a3c89af3d4a035727b8a65fe5ecb95487dab20f73d2",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0009",
        "obs-0035"
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
        "obs-0003",
        "obs-0008",
        "obs-0010",
        "obs-0034"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          92,
          132,
          136,
          152,
          156
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0013"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0035"
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
        "obs-0009",
        "obs-0035"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0035"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00bba790",
      "count": 8,
      "first_use": 0,
      "first_write_index": 12,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00bba791",
      "count": 12,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00bba792",
      "definite": true,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00bba794",
      "id": "obs-0004",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00bba640",
      "target": "0x00bba640"
    },
    {
      "at": "0x00bba799",
      "definite": true,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EDI + 0x5c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bba79c",
      "count": 9,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_READ",
      "raw": "SHR EAX,0x6",
      "reg": "EAX"
    },
    {
      "at": "0x00bba7a9",
      "id": "obs-0007",
      "index": 9,
      "kind": "REG_RESTORE",
      "raw": "POP EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00bba7aa",
      "id": "obs-0008",
      "index": 10,
      "kind": "REG_RESTORE",
      "raw": "POP ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00bba7ab",
      "form": "RET",
      "id": "obs-0009",
      "imm": null,
      "index": 11,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00bba7ac",
      "definite": true,
      "id": "obs-0010",
      "index": 12,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EDI + 0x9c]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bba7b2",
      "definite": true,
      "id": "obs-0011",
      "index": 13,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EDI + 0x98]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bba7b8",
      "count": 2,
      "first_use": 14,
      "first_write_index": 27,
      "id": "obs-0012",
      "index": 14,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00bba7b8",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0013",
      "index": 14,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_es
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00aea5d0",
    "reconstructed": true,
    "va": "0x00aea5d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b8d970"
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
    "va": "0x00bb4100"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb5ae0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bba870"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bba8c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bba913"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bba990"
  },
  {
    "name": "FUN_00c31730",
    "reconstructed": false,
    "va": "0x00c31730"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c341a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c344f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c34ee0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c35240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c35810"
  },
  {
    "name": "FUN_00c47e20",
    "reconstructed": false,
    "va": "0x00c47e20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c48600"
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
  "count": 76,
  "instructions": [
    {
      "address": "00bba790",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bba791",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bba792",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00bba794",
      "instruction": "CALL 0x00bba640"
    },
    {
      "address": "00bba799",
      "instruction": "MOV EAX,dword ptr [EDI + 0x5c]"
    },
    {
      "address": "00bba79c",
      "instruction": "SHR EAX,0x6"
    },
    {
      "address": "00bba79f",
      "instruction": "TEST AL,0x1"
    },
    {
      "address": "00bba7a1",
      "instruction": "JNZ 0x00bba7ac"
    },
    {
      "address": "00bba7a3",
      "instruction": "LEA EAX,[EDI + 0x84]"
    },
    {
      "address": "00bba7a9",
      "instruction": "POP EDI"
    },
    {
      "address": "00bba7aa",
      "instruction": "POP ECX"
    },
    {
      "address": "00bba7ab",
      "instruction": "RET"
    },
    {
      "address": "00bba7ac",
      "instruction": "MOV ECX,dword ptr [EDI + 0x9c]"
    },
    {
      "address": "00bba7b2",
      "instruction": "MOV EDX,dword ptr [EDI + 0x98]"
    },
    {
      "address": "00bba7b8",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00bba7b9",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bba7ba",
      "instruction": "LEA ESI,[EDI + 0x98]"
    },
    {
      "address": "00bba7c0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bba7c1",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bba7c2",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bba7c4",
      "instruction": "CALL 0x00e25bd0"
    },
    {
      "address": "00bba7c9",
      "instruction": "MOV EAX,dword ptr [EDI + 0x88]"
    },
    {
      "address": "00bba7cf",
      "instruction": "SUB EAX,dword ptr [EDI + 0x84]"
    },
    {
      "address": "00bba7d5",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bba7d7",
      "instruction": "SAR EAX,0x2"
    },
    {
      "address": "00bba7da",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bba7db",
      "instruction": "CALL 0x00d01790"
    },
    {
      "address": "00bba7e0",
      "instruction": "MOV EBP,dword ptr [EDI + 0x88]"
    },
    {
      "address": "00bba7e6",
      "instruction": "SUB EBP,dword ptr [EDI + 0x84]"
    },
    {
      "address": "00bba7ec",
      "instruction": "MOV dword ptr [ESP + 0xc],0x0"
    },
    {
      "address": "00bba7f4",
      "instruction": "SAR EBP,0x2"
    },
    {
      "address": "00bba7f7",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "00bba7f9",
      "instruction": "JLE 0x00bba85b"
    },
    {
      "address": "00bba7fb",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bba7fc",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "00bba800",
      "instruction": "MOV EBX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00bba804",
      "instruction": "MOV ECX,dword ptr [EDI + 0x84]"
    },
    {
      "address": "00bba80a",
      "instruction": "ADD EBX,EBX"
    },
    {
      "address": "00bba80c",
      "instruction": "ADD EBX,EBX"
    },
    {
      "address": "00bba80e",
      "instruction": "MOV ECX,dword ptr [EBX + ECX*0x1]"
    },
    {
      "address": "00bba811",
      "instruction": "CALL 0x00b8d970"
    },
    {
      "address": "00bba816",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00bba818",
      "instruction": "JNZ 0x00bba84d"
    },
    {
      "address": "00bba81a",
      "instruction": "MOV ECX,dword ptr [EDI + 0x84]"
    },
    {
      "address": "00bba820",
      "instruction": "MOV EAX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00bba823",
      "instruction": "ADD ECX,EBX"
    },
    {
      "address": "00bba825",
      "instruction": "CMP EAX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "00bba828",
      "instruction": "JNC 0x00bba844"
    },
    {
      "address": "00bba82a",
      "instruction": "LEA EDX,[EAX + 0x4]"
    },
    {
      "address": "00bba82d",
      "instruction": "MOV dword ptr [ESI + 0x4],EDX"
    },
    {
      "address": "00bba830",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00bba832",
      "instruction": "JZ 0x00bba84d"
    },
    {
      "address": "00bba834",
      "instruction": "MOV ECX,dword ptr [ECX]"
    },
    {
      "address": "00bba836",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "00bba838",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00bba83a",
      "instruction": "JZ 0x00bba84d"
    },
    {
      "address": "00bba83c",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00bba83e",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00bba840",
      "instruction": "CALL EDX"
    },
    {
      "address": "00bba842",
      "instruction": "JMP 0x00bba84d"
    },
    {
      "address": "00bba844",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bba845",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bba846",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bba848",
      "instruction": "CALL 0x00aea5d0"
    },
    {
      "address": "00bba84d",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00bba851",
      "instruction": "INC EAX"
    },
    {
      "address": "00bba852",
      "instruction": "CMP EAX,EBP"
    },
    {
      "address": "00bba854",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00bba858",
      "instruction": "JL 0x00bba800"
    },
    {
      "address": "00bba85a",
      "instruction": "POP EBX"
    },
    {
      "address": "00bba85b",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00bba85d",
      "instruction": "POP ESI"
    },
    {
      "address": "00bba85e",
    
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
  "original_bytes": 16532,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": {\n      \"confidence\": \"APPROXIMATION\",\n      \"derived_slots\": 0,\n      \"gaps\": 0,\n      \"not_complete\": false,\n      \"observed_slots\": 0,\n      \"slots\": [],\n      \"total_bytes\": 0,\n      \"widths_ambiguous\": false\n    },\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00aea5d0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00aea5d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b8d970\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb2330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb23e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb4100\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb5ae0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bba870\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bba8c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bba913\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bba990\"\n      },\n      {\n        \"name\": \"FUN_00c31730\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c31730\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c341a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c344f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c34ee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c35240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c35810\"\n      },\n      {\n        \"name\": \"FUN_00c47e20\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c47e20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c48600\"\n      },\n      {\n        \"name\": \"FUN_00c59240\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c59240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5f770\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c62ff0\"\n      },\n      {\n        \"name\": \"solar_system_load_00c86760\",\n        \"reconstructed\": true,\n        \"va\": \"0x00c86760\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8b5e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8b820\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8bb00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8bc10\"\n      },\n      {\n        \"na
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
  "body_end": "00bba861",
  "body_span_bytes": 210,
  "body_start": "00bba790",
  "callees": [
    "FUN_00b8d970",
    "FUN_00e25bd0",
    "FUN_00bba640",
    "FUN_00d01790",
    "FUN_00aea5d0"
  ],
  "callers": [
    "FUN_00bba913",
    "FUN_00c341a0",
    "FUN_00c62ff0",
    "FUN_00c31730",
    "FUN_00c344f0",
    "FUN_00df7f60",
    "FUN_0102daa0",
    "FUN_00def400",
    "FUN_010251e0",
    "FUN_00c86760",
    "FUN_00bb5ae0",
    "FUN_00c35240",
    "FUN_00c8bc10",
    "FUN_01069aa0",
    "FUN_0106cc70",
    "FUN_00bba870",
    "FUN_00c8b820",
    "FUN_00c47e20",
    "FUN_01038410",
    "FUN_0102c1a0",
    "FUN_00c8d060",
    "FUN_010468f0",
    "FUN_00c48600",
    "FUN_01072d40",
    "Simulator::IsBinaryStar",
    "FUN_00bba990",
    "FUN_01011120",
    "FUN_00c8c420",
    "FUN_010021a0",
    "FUN_00bba8c0",
    "FUN_00c8bb00",
    "FUN_00c5f770",
    "FUN_00c59240",
    "FUN_00c8c2a0",
    "FUN_00c8c5d0",
    "FUN_00c35810",
    "FUN_00bb4100",
    "FUN_00bb2330",
    "FUN_00fe9580",
    "FUN_0102df20",
    "FUN_00bb23e0",
    "FUN_00c8c9d0",
    "FUN_010091d0",
    "FUN_00fefcd0",
    "FUN_00c8ce40",
    "FUN_00c34ee0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bba790",
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
      "name": "local_14",
      "storage": "Stack[-0x14]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00bba790",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7ba790",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bba790(void)",
  "size_bytes": 210,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bba790",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 57,
  "xrefs": [
    {
      "from": "00bb23a2"
    },
    {
      "from": "00bb244e"
    },
    {
      "from": "00bba917"
    },
    {
      "from": "00c3428b"
    },
    {
      "from": "00c8698a"
    },
    {
      "from": "00bb4a02"
    },
    {
      "from": "00c31767"
    },
    {
      "from": "00fe9751"
    },
    {
      "from": "00fe9a07"
    },
    {
      "from": "00fe9c14"
    },
    {
      "from": "00bba8cc"
    },
    {
      "from": "00bb5af3"
    },
    {
      "from": "00c35859"
    },
    {
      "from": "00c34f51"
    },
    {
      "from": "00c35120"
    },
    {
      "from": "00c35192"
    },
    {
      "from": "00c8b5e8"
    },
    {
      "from": "00c8c2ca"
    },
    {
      "from": "00fefd41"
    },
    {
      "from": "00c35294"
    },
    {
      "from": "00c352a8"
    },
    {
      "from": "0102c1c9"
    },
    {
      "from": "0102e6ae"
    },
    {
      "from": "00c8bb0b"
    },
    {
      "from": "00c8c5da"
    },
    {
      "from": "00c8c9d8"
    },
    {
      "from": "00c8ce5b"
    },
    {
      "from": "00bba996"
    },
    {
      "from": "0102dde7"
    },
    {
      "from": "00c8b829"
    },
    {
      "from": "0106d0d5"
    },
    {
      "from": "00c8bc46"
    },
    {
      "from": "00bba873"
    },
    {
      "from": "00c34537"
    },
    {
      "from": "00c48664"
    },
    {
      "from": "00c48227"
    },
    {
      "from": "00c593bc"
    },
    {
      "from": "00c8d06a"
    },
    {
      "from": "00c5fa28"
    },
    {
      "from": "00c8c42b"
    },
    {
      "from": "00df7ff0"
    },
    {
      "from": "00def492"
    },
    {
      "from": "01069d42"
    },
    {
      "from": "01009210"
    },
    {
      "from": "01038e8f"
    },
    {
      "from": "010111d2"
    },
    {
      "from": "010253b3"
    },
    {
      "from": "0107338f"
    },
    {
      "from": "010734c2"
    },
    {
      "from": "01046a2d"
    },
    {
      "from": "00c4e77a"
    },
    {
      "from": "00c630a3"
    },
    {
      "from": "010024d2"
    },
    {
      "from": "01025a6b"
    },
    {
      "from": "01026fdc"
    },
    {
      "from": "01027242"
    },
    {
      "from": "01027ccb"
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
    "reconstruction/staging/pkg_sim_f00bba790/sim_f00bba790.cpp",
    "reconstruction/staging/pkg_sim_f00bba790/sim_f00bba790.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-sim-f00bba790/00bba790.json"
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "NodeKeepPending",
  "OpaqueSimState*",
  "OpaqueWordVector*",
  "StateRefresh",
  "VectorGrowInsert",
  "VectorReserve",
  "VectorResize"
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
