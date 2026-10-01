# Evidence 0x00be1fb0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `4a5adc0c69ab672e42ce673d341ef2088843bbbf8a4378d6b367c45ba4915748`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueCity* city",
  "ordinary_stack_arguments": [],
  "return_note": "newly created building identity or null",
  "return_register": "EAX",
  "return_type": "OpaqueBuilding*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "ESI",
    "EBP",
    "EDI"
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "31b273624181cdbea033269f718a280e0950e7fc6f96334971eff23274d93968",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0024",
        "obs-0039"
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
        "obs-0005",
        "obs-0006",
        "obs-0023",
        "obs-0038"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          288,
          856,
          860
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0023",
        "obs-0024",
        "obs-0038",
        "obs-0039"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0024",
        "obs-0039"
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
        "obs-0024",
        "obs-0039"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0024",
        "obs-0039"
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
      "at": "0x00be1fb0",
      "count": 5,
      "first_use": 0,
      "first_write_index": 5,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00be1fb1",
      "count": 7,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00be1fb2",
      "definite": true,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,ECX",
      "reg": "EBX",
      "write_kind": "reg"
    },
    {
      "at": "0x00be1fb4",
      "id": "obs-0004",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d300",
      "target": "0x00b3d300"
    },
    {
      "at": "0x00be1fbe",
      "count": 15,
      "first_use": 5,
      "first_write_index": 12,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00be1fbe",
      "definite": true,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00be1fc0",
      "id": "obs-0007",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b20c60",
      "target": "0x00b20c60"
    },
    {
      "at": "0x00be1fc9",
      "definite": true,
      "id": "obs-0008",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00be1fcb",
      "count": 11,
      "first_use": 10,
      "first_write_index": 15,
      "id": "obs-0009",
      "index": 10,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00be1fce",
      "count": 9,
      "first_use": 12,
      "first_write_index": 9,
      "id": "obs-0010",
      "index": 12,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0xc]",
      "reg": "EDX"
    },
    {
      "at": "0x00be1fce",
      "definite": true,
      "id": "obs-0011",
      "index": 12,
      "kind": "REG_WRIT
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d300",
    "reconstructed": true,
    "va": "0x00b3d300"
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
    "va": "0x00be3850"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be3990"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d130d0"
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
  "count": 75,
  "instructions": [
    {
      "address": "00be1fb0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00be1fb1",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00be1fb2",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00be1fb4",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00be1fb9",
      "instruction": "PUSH 0x436f342"
    },
    {
      "address": "00be1fbe",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00be1fc0",
      "instruction": "CALL 0x00b20c60"
    },
    {
      "address": "00be1fc5",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00be1fc7",
      "instruction": "JZ 0x00be201c"
    },
    {
      "address": "00be1fc9",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00be1fcb",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00be1fcc",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00be1fce",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00be1fd1",
      "instruction": "PUSH 0x436f315"
    },
    {
      "address": "00be1fd6",
      "instruction": "CALL EAX"
    },
    {
      "address": "00be1fd8",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00be1fda",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00be1fdc",
      "instruction": "JZ 0x00be2068"
    },
    {
      "address": "00be1fe2",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00be1fe4",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "00be1fe6",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00be1fe7",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00be1fe8",
      "instruction": "MOV EDI,ESI"
    },
    {
      "address": "00be1fea",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00be1fec",
      "instruction": "MOV dword ptr [ESP + 0x10],EDI"
    },
    {
      "address": "00be1ff0",
      "instruction": "CALL EAX"
    },
    {
      "address": "00be1ff2",
      "instruction": "MOV EAX,dword ptr [EBX + 0x358]"
    },
    {
      "address": "00be1ff8",
      "instruction": "CMP EAX,dword ptr [EBX + 0x35c]"
    },
    {
      "address": "00be1ffe",
      "instruction": "LEA ECX,[EBX + 0x354]"
    },
    {
      "address": "00be2004",
      "instruction": "JNC 0x00be2021"
    },
    {
      "address": "00be2006",
      "instruction": "LEA EDX,[EAX + 0x4]"
    },
    {
      "address": "00be2009",
      "instruction": "MOV dword ptr [ECX + 0x4],EDX"
    },
    {
      "address": "00be200c",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00be200e",
      "instruction": "JZ 0x00be2030"
    },
    {
      "address": "00be2010",
      "instruction": "MOV dword ptr [EAX],ESI"
    },
    {
      "address": "00be2012",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00be2014",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00be2016",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00be2018",
      "instruction": "CALL EDX"
    },
    {
      "address": "00be201a",
      "instruction": "JMP 0x00be2030"
    },
    {
      "address": "00be201c",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00be201e",
      "instruction": "POP EBX"
    },
    {
      "address": "00be201f",
      "instruction": "POP ECX"
    },
    {
      "address": "00be2020",
      "instruction": "RET"
    },
    {
      "address": "00be2021",
      "instruction": "LEA EDX,[ESP + 0x10]"
    },
    {
      "address": "00be2025",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00be2026",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00be2027",
      "instruction": "CALL 0x00edafd0"
    },
    {
      "address": "00be202c",
      "instruction": "MOV EDI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00be2030",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00be2032",
      "instruction": "JZ 0x00be203d"
    },
    {
      "address": "00be2034",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00be2036",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00be2039",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00be203b",
      "instruction": "CALL EDX"
    },
    {
      "address": "00be203d",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00be203e",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00be2040",
      "instruction": "CALL 0x00bd2310"
    },
    {
      "address": "00be2045",
      "instruction": "MOV EAX,dword ptr [EBX + 0x120]"
    },
    {
      "address": "00be204b",
      "instruction": "MOV EDX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "00be204e",
      "instruction": "MOV EBP,dword ptr [ESI + 0x34]"
    },
    {
      "address": "00be2051",
      "instruction": "LEA ECX,[EBX + 0x120]"
    },
    {
      "address": "00be2057",
      "instruction": "LEA EDI,[ESI + 0x34]"
    },
    {
      "address": "00be205a",
      "instruction": "CALL EDX"
    },
    {
      "address": "00be205c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00be205d",
      "instruction": "MOV EAX,dword ptr [EBP + 0x38]"
    },
    {
      "address": "00be2060",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00be2062",
      "instruction": "CALL EAX"
    },
    {
      "address": "00be2064",
      "instruction": "POP EDI"
    },
    {
      "address": "00be2065",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00be2067",
      "instruction": "POP EBP"
    },
    {
      "address": "00be2068",
      "instruction": "POP ESI"
    },
    {
      "address": "00be2069",
      "instruction": "POP EBX"
    },
    {
      "address": "00be206a",
     
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
  "original_bytes": 8674,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueCity* city\",\n    \"ordinary_stack_arguments\": [],\n    \"return_note\": \"newly created building identity or null\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"OpaqueBuilding*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EBP\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"plain RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-C3-TRIBE-CIV-WAVE2\",\n      \"score\": 10,\n      \"symbol\": \"tribe_constructor_00c982a0\",\n      \"va\": \"0x00c982a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0000000c\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 4,\n      \"symbol\": \"editor_query_service_005ca960\",\n      \"va\": \"0x005ca960\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_Update_0059b4b0\",\n      \"va\": \"0x0059b4b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n      \"va\": \"0x0059cb10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n      \"va\": \"0x0059cea0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCity\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d300\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d300\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be3850\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be3990\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d130d0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00be3869\",\n        \"direction\": \"in\",\n        \"other\": \"0x00be3850\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be39bd\",\n        \"direction\": \"in\",\n        \"other\": \"0x00be3990\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d13cc7\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d130d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be1fc0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b20c60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be1fb4\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d300\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be2040\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bd2310\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00be2027\",\n        \"direction\": \"out\",\n        \"other\": \"0x00edafd0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 3,\n    \"fan_out\": 1,\n    \"manifest_callees\": [\n      {\n        \"address\": \"0x00b3d300\",\n        \"role\": \"current root provider\"\n      },\n      {\n        \"address\": \"0x00b20c60\",\n        \"role\": \"factory wrapper\"\n      },\n      {\n        \"address\": \"0x00edafd0\",\n        \"role\": \"building vector insertion/growth\"\n      },\n      {\n        \"address\": \"0x00bd2310\",\n        \"role\": \"building owner/setup helper\"\n      },\n      {\n        \"address\": \"vtable+0x00\",\n        \"role\": \"building AddRef before and during vector insertion\"\n      },\n      {\n        \"address\": \"vtable+0x04\",\n        \"role\": \"building release after insertion\"\n      },\n      {\n        \"address\": \"city+0x120 vtable+0x2c\",\n        \"role\": \"city owner hook\"\n      },\n      {\n        \"address\": \"building+0x34 vtable+0x38\",\n        \"role\": \"building owner hook\"\n      }\n    ],\n    \"manifest_callers\": [\n 
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
  "body_end": "00be206b",
  "body_span_bytes": 188,
  "body_start": "00be1fb0",
  "callees": [
    "FUN_00bd2310",
    "FUN_00b20c60",
    "FUN_00b3d300",
    "FUN_00edafd0"
  ],
  "callers": [
    "FUN_00be3850",
    "FUN_00d130d0",
    "FUN_00be3990"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00be1fb0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00be1fb0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7e1fb0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00be1fb0(void)",
  "size_bytes": 188,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00be1fb0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00be3869"
    },
    {
      "from": "00be39bd"
    },
    {
      "from": "00d13cc7"
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
  "file": "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp",
  "files": [
    "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp",
    "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.hpp",
    "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c3-tribe-civ-wave2/00be1fb0.json"
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
    "gate-city-add-building-00be1fb0",
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
  "OpaqueBuilding* newly created building identity or null",
  "OpaqueCity",
  "OpaqueCity* city"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0000000c"
]
```

## Conflicts

```json
[]
```
