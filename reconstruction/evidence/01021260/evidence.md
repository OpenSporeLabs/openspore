# Evidence 0x01021260

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c1df758376726904da08ae8c22543e2448480a7fecb029c3810d9c8f425fd0e2`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl-compatible no-argument accessor",
  "return_note": "opaque 32-bit active-planet pointer word",
  "return_register": "EAX",
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
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
  "content_sha256": "a984f05700ac143c4877684d0894bd43d80b62806439f86462f90f26a2cbdedf",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017"
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
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0016"
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
        "obs-0017"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0017"
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
        "obs-0017"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0017"
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
      "at": "0x01021260",
      "count": 4,
      "first_use": 0,
      "first_write_index": 6,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x01021261",
      "count": 3,
      "first_use": 1,
      "first_write_index": 1,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "XOR EDX,EDX",
      "reg": "EDX"
    },
    {
      "at": "0x01021261",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "XOR EDX,EDX",
      "reg": "EDX",
      "write_kind": "zero"
    },
    {
      "at": "0x01021263",
      "count": 4,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ESP],EDX",
      "reg": "ESP"
    },
    {
      "at": "0x01021263",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0005",
      "index": 2,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP],EDX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x01021266",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016dda8c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0102126f",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0007",
      "index": 6,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x0102126f",
      "definite": true,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0102127e",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0009",
      "index": 11,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x01021281",
      "count": 3,
      "first_use": 12,
      "first_write_index": 3,
      "id": "obs-0010",
      "index": 12,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP]",
      "reg": "EAX"
    },
    {
      "at": "0x01021281",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0011",
      "index": 12,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA EAX,[ESP]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x01021284",
      "count": 2,
      "first_use": 13,
      "first_write_index": 14,
      "id": "obs-0012",
      "index": 13,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x01021285",
      "definite"
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
    "va": "0x00acc390"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00acc800"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00acd790"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00acf3e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00acf4c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ad4a10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb890"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2a110"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2bbe0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2bf10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2ec80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2f210"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b2f350"
  },
  {
    "name": "timing_update_body_00b31cc0",
    "reconstructed": true,
    "va": "0x00b31cc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b421b0"
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
  "count": 26,
  "instructions": [
    {
      "address": "01021260",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01021261",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "01021263",
      "instruction": "MOV dword ptr [ESP],EDX"
    },
    {
      "address": "01021266",
      "instruction": "MOV EAX,[0x016dda8c]"
    },
    {
      "address": "0102126b",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0102126d",
      "instruction": "JZ 0x01021277"
    },
    {
      "address": "0102126f",
      "instruction": "MOV ECX,dword ptr [ESP]"
    },
    {
      "address": "01021272",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "01021275",
      "instruction": "JMP 0x01021284"
    },
    {
      "address": "01021277",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "01021279",
      "instruction": "MOV EDX,0x1"
    },
    {
      "address": "0102127e",
      "instruction": "MOV dword ptr [ESP],ECX"
    },
    {
      "address": "01021281",
      "instruction": "LEA EAX,[ESP]"
    },
    {
      "address": "01021284",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01021285",
      "instruction": "MOV ESI,dword ptr [EAX]"
    },
    {
      "address": "01021287",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "0102128a",
      "instruction": "JZ 0x0102129a"
    },
    {
      "address": "0102128c",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0102128e",
      "instruction": "JZ 0x0102129a"
    },
    {
      "address": "01021290",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01021292",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc0]"
    },
    {
      "address": "01021298",
      "instruction": "CALL EDX"
    },
    {
      "address": "0102129a",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "0102129c",
      "instruction": "POP ESI"
    },
    {
      "address": "0102129d",
      "instruction": "POP ECX"
    },
    {
      "address": "0102129e",
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
  "original_bytes": 16203,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl-compatible no-argument accessor\",\n    \"return_note\": \"opaque 32-bit active-planet pointer word\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:ActivePlanetAccessWindow,SpacePlayerDataAccessPrefix\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 22,\n      \"symbol\": \"FUN_010212a0\",\n      \"va\": \"0x010212a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:SpacePlayerDataAccessPrefix\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 19,\n      \"symbol\": \"FUN_01021080\",\n      \"va\": \"0x01021080\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:SpacePlayerDataAccessPrefix\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 19,\n      \"symbol\": \"FUN_01021230\",\n      \"va\": \"0x01021230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d3a0\",\n      \"va\": \"0x00b3d3a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00b3d400\",\n      \"va\": \"0x00b3d400\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cSpaceTrading_Get\",\n      \"va\": \"0x00b3d4d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Null-guarded +0x04 active-planet word read; the host window is not a complete cPlanet layout and the return is borrowed without reference operations.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"ActivePlanetAccessWindow\",\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acc390\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acc800\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acd790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acf3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acf4c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad4a10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb890\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2a110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2bbe0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2bf10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2ec80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2f210\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2f350\"\n      },\n      {\n        \"name\": \"timing_update_body_00b31cc0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b31cc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b421b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b4c270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b60110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6b1a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6baf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b7daf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b8c330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba4f30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbc370\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbc540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbca30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n 
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
  "body_end": "0102129e",
  "body_span_bytes": 63,
  "body_start": "01021260",
  "callees": [],
  "callers": [
    "FUN_00d100b0",
    "FUN_00b2f210",
    "FUN_01066230",
    "FUN_0107c1e0",
    "FUN_00c56170",
    "FUN_00ea5fe0",
    "FUN_00ee9840",
    "FUN_00d07470",
    "FUN_00ccdd70",
    "FUN_00c4ccd0",
    "FUN_00c51bb0",
    "FUN_01001cd0",
    "FUN_0102cd90",
    "FUN_00b8c330",
    "FUN_00bbc370",
    "FUN_00fe3b30",
    "FUN_00c84950",
    "FUN_01050bb0",
    "FUN_00bf0810",
    "FUN_0101bb90",
    "FUN_00bc1450",
    "FUN_00b2bbe0",
    "FUN_00fdf5b0",
    "FUN_00bbf2b0",
    "FUN_00bbcf00",
    "FUN_00b2bf10",
    "FUN_00acd790",
    "FUN_00e98bd0",
    "FUN_00fdf5f0",
    "FUN_01058680",
    "FUN_00be7bf0",
    "FUN_00ff6a50",
    "FUN_00f316d0",
    "FUN_0105b350",
    "FUN_00bc2670",
    "FUN_01058c90",
    "FUN_0106fc90",
    "FUN_01004e50",
    "FUN_00bbf860",
    "FUN_01053240",
    "FUN_010743a0",
    "FUN_0102c720",
    "FUN_00acf4c0",
    "FUN_00b2a110",
    "FUN_00fe0e10",
    "FUN_00c932a0",
    "FUN_00c635c0",
    "FUN_00c4f220",
    "FUN_00bc20e0",
    "FUN_010534c0",
    "FUN_00bf74a0",
    "FUN_010019a0",
    "FUN_00bd8fe0",
    "FUN_00e02040",
    "FUN_010361c0",
    "FUN_00bd9e50",
    "FUN_00bc0180",
    "FUN_00e98c80",
    "FUN_00e0e1a0",
    "FUN_00d1c610",
    "FUN_00dd5160",
    "FUN_00bf8170",
    "FUN_010053c0",
    "FUN_00be2110",
    "FUN_00ffabc0",
    "FUN_00c71bf0",
    "FUN_010377f0",
    "FUN_0104cdb0",
    "FUN_00c474b0",
    "FUN_00acc390",
    "FUN_00c72030",
    "FUN_00bf71d0",
    "FUN_00be4c00",
    "FUN_00e3ede0",
    "FUN_00fe3b10",
    "FUN_0100a960",
    "FUN_00cdd500",
    "FUN_00fde3e0",
    "FUN_00fe0570",
    "FUN_0102b780",
    "FUN_00e35370",
    "FUN_00bbc540",
    "FUN_00cd5f70",
    "FUN_00f35c80",
    "FUN_00acf3e0",
    "FUN_00c51b10",
    "FUN_01077630",
    "FUN_01004fc0",
    "FUN_00acc800",
    "FUN_00e04b40",
    "FUN_00bc2c00",
    "FUN_00ee9690",
    "cScenarioEditHistory_GetLastEntry",
    "FUN_00bbe740",
    "FUN_00cd1960",
    "FUN_00e2abc0",
    "FUN_00bc2f00",
    "FUN_00f3cf10",
    "FUN_00ccefb0",
    "FUN_00c631f0",
    "FUN_00ea5f20",
    "j_cSpaceGfx_Dispose_",
    "FUN_0105a890",
    "FUN_00c560c0",
    "FUN_00b7daf0",
    "FUN_00bc2f70",
    "FUN_0102ce30",
    "FUN_00ce8ab0",
    "FUN_00d3c430",
    "FUN_00c86390",
    "FUN_010027b0",
    "FUN_00c4fe60",
    "FUN_01021370",
    "FUN_00cde2f0",
    "FUN_00c4a6b0",
    "FUN_00bf45f0",
    "FUN_0102cae0",
    "FUN_01034880",
    "FUN_00ea5000",
    "FUN_01076b80",
    "FUN_00c86c70",
    "FUN_00d43e30",
    "FUN_00c5ff50",
    "FUN_00c830f0",
    "FUN_01056d30",
    "FUN_00d5e0c0",
    "FUN_010251e0",
    "FUN_00bf1270",
    "FUN_00ffa2c0",
    "FUN_00cfd220",
    "FUN_00c82f00",
    "FUN_00ffd280",
    "FUN_0106a7b0",
    "FUN_00bcece0",
    "FUN_00bbcb90",
    "FUN_01030fd0",
    "FUN_0102d1b0",
    "FUN_00c382e0",
    "FUN_0105e6d0",
    "FUN_00c61390",
    "FUN_01056160",
    "FUN_00c61450",
    "FUN_00bbe470",
    "FUN_00c54f90",
    "FUN_00bc2b80",
    "FUN_00fdeac0",
    "FUN_00cf50e0",
    "FUN_00becd70",
    "FUN_00fdd390",
    "FUN_00be5dd0",
    "FUN_01067b60",
    "FUN_00c634a0",
    "FUN_00d5ccf0",
    "FUN_00c555d0",
    "FUN_00bff2d0",
    "FUN_00d09d30",
    "FUN_00cfa410",
    "FUN_00c810e0",
    "FUN_00ff8560",
    "FUN_00b421b0",
    "FUN_00be3850",
    "FUN_00c84d60",
    "FUN_00b6b1a0",
    "FUN_00bd0140",
    "FUN_00ff9100",
    "FUN_00b60110",
    "FUN_01053320",
    "FUN_00f32240",
    "FUN_00bcd480",
    "FUN_00dca100",
    "FUN_00fdade0",
    "FUN_00c55ca0",
    "FUN_00bdbf10",
    "FUN_00bf3180",
    "FUN_01071d70",
    "FUN_00ad4a10",
    "FUN_01007ed0",
    "FUN_00ee95a0",
    "FUN_00d50ef0",
    "FUN_00c4c690",
    "FUN_00ff7530",
    "FUN_00e98ae0",
    "FUN_00fdc710",
    "FUN_00dd4b20",
    "FUN_00cdb8b0",
    "FUN_00fdb0c0",
    "FUN_00aeb890",
    "FUN_00d56c30",
    "FUN_00fef140",
    "FUN_00ff6450",
    "FUN_00d32fd0",
    "FUN_00cfeeb0",
    "FUN_00bbca30",
    "FUN_01057bd0",
    "FUN_00c5b150",
    "FUN_01001b60",
    "FUN_00b31cc0",
    "FUN_00b6baf0",
    "FUN_00bbdbf0",
    "FUN_00fe0160",
    "FUN_00c5f530",
    "FUN_00fdc800",
    "FUN_00c57ad0",
    "FUN_010593e0",
    "FUN_00bf14b0",
    "FUN_00bfb930",
    "FUN_00fdfbc0",
    "FUN_00ffb830",
    "FUN_00fdf9f0",
    "FUN_00c50940",
    "FUN_00cfbc10",
    "FUN_00b2ec80",
    "FUN_00ea6f20",
    "FUN_01006370",
    "FUN_00f31de0",
    "FUN_0103fe90",
    "FUN_00aeb240",
    "FUN_00bbe5c0",
    "FUN_00bdb470",
    "FUN_00bc2b30",
    "FUN_01066f20",
    "FUN_0102df20",
    "FUN_00bbcb10",
    "FUN_00ffb270",
    "FUN_00fe0c60",
    "FUN_00c7f390",
    "FUN_00c487d0",
    "FUN_0102cf10",
    "FUN_00ffcab0",
    "FUN_00e43710",
    "FUN_00bf0330",
    "FUN_00bbdff0",
    "FUN_00f37f20",
    "FUN_00c4c790",
    "FUN_00d130d0",
    "FUN_010533d0",
    "FUN_00ba4f30",
    "FUN_01003690",
    "FUN_00fdd5a0",
    "FUN_01000520",
    "FUN_00c38270",
    "FUN_00b2f350",
    "FUN_00c637b0",
    "FUN_0101d130",
    "FUN_00bf57b0",
    "FUN_0106a4e0",
    "FUN_00be7370",
    "FUN_00ffd390",
    "FUN_00c4fc00",
    "FUN_00bf03e0",
    "FUN_00b4c270",
    "FUN_00bc2b60",
    "FUN_00ffaf20",
    "FUN_01049040",
    "FUN_00c706d0",
    "FUN_01023fc0",
    "FUN_00c5da10",
    "FUN_00fdc240",
    "FUN_00e07e70",
    "FUN_010568b0",
    "FUN_00cf31f0",
    "FUN_00fda530"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "01021260",
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
    "reconstruction/metadata/pkg01-roots/01021260.json"
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
    "Separate static writers and cleanup routines can replace or release the +0x04 slot; stale-pointer and lifetime windows remain runtime questions.",
    "The concrete active-planet object is not established by this accessor.",
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
  "ActivePlanetAccessWindow",
  "SpacePlayerDataAccessPrefix",
  "opaque 32-bit active-planet pointer word"
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
