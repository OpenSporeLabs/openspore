# Evidence 0x00b8de30

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b158ca312389be20e5199d3bc8d1f7700077a4ad26197247d58adfa89865cb5d`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
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
  "content_sha256": "94b77467efd95f3ef0f783745a419a08e3522ffa05a2601f0b6fdf26836ae157",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0009"
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
        "obs-0005"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          388
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0005",
        "obs-0009"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0009"
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
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009"
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
      "at": "0x00b8de30",
      "count": 1,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x184]",
      "reg": "ECX"
    },
    {
      "at": "0x00b8de30",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x184]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b8de36",
      "count": 4,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00b8de37",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d2a0",
      "target": "0x00b3d2a0"
    },
    {
      "at": "0x00b8de3c",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00b8de3e",
      "id": "obs-0006",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00ba6440",
      "target": "0x00ba6440"
    },
    {
      "at": "0x00b8de44",
      "id": "obs-0007",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d2a0",
      "target": "0x00b3d2a0"
    },
    {
      "at": "0x00b8de4b",
      "id": "obs-0008",
      "index": 8,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00ba6d80",
      "target": "0x00ba6d80"
    },
    {
      "at": "0x00b8de50",
      "form": "RET",
      "id": "obs-0009",
      "imm": null,
      "index": 9,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 10,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
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
    "max_offset": 388,
    "offsets": [
      388
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
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointe
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
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
  "content_sha256": "94b77467efd95f3ef0f783745a419a08e3522ffa05a2601f0b6fdf26836ae157",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0009"
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
        "obs-0005"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          388
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0005",
        "obs-0009"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0009"
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
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009"
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
      "at": "0x00b8de30",
      "count": 1,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x184]",
      "reg": "ECX"
    },
    {
      "at": "0x00b8de30",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x184]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b8de36",
      "count": 4,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00b8de37",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d2a0",
      "target": "0x00b3d2a0"
    },
    {
      "at": "0x00b8de3c",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00b8de3e",
      "id": "obs-0006",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00ba6440",
      "target": "0x00ba6440"
    },
    {
      "at": "0x00b8de44",
      "id": "obs-0007",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d2a0",
      "target": "0x00b3d2a0"
    },
    {
      "at": "0x00b8de4b",
      "id": "obs-0008",
      "index": 8,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00ba6d80",
      "target": "0x00ba6d80"
    },
    {
      "at": "0x00b8de50",
      "form": "RET",
      "id": "obs-0009",
      "imm": null,
      "index": 9,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 10,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
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
    "max_offset": 388,
    "offsets": [
      388
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
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointe
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
    "va": "0x00b96d40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00baf130"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb59b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb9ff0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbe470"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbe5f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bc0180"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd9a80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be9b20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c316c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c34e70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c35810"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c44d00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c46590"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c47a10"
  },
  {
    "name": "FUN_00c47e20",
    "reconstructed": false,
    "va": "0x00c47e20"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nvoid __fastcall FUN_00b8de30(int param_1)\n\n{\n  undefined4 uVar1;\n  \n  uVar1 = *(undefined4 *)(param_1 + 0x184);\n  FUN_00b3d2a0(uVar1);\n  uVar1 = FUN_00ba6440(uVar1);\n  FUN_00b3d2a0(uVar1);\n  FUN_00ba6d80(uVar1);\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 10,
  "instructions": [
    {
      "address": "00b8de30",
      "instruction": "MOV EAX,dword ptr [ECX + 0x184]"
    },
    {
      "address": "00b8de36",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b8de37",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00b8de3c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b8de3e",
      "instruction": "CALL 0x00ba6440"
    },
    {
      "address": "00b8de43",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b8de44",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00b8de49",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b8de4b",
      "instruction": "CALL 0x00ba6d80"
    },
    {
      "address": "00b8de50",
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
  "original_bytes": 13411,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 9,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b96d40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00baf130\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb59b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb9ff0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbe470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbe5f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bc0180\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd9a80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be9b20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c316c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c34e70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c35810\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c44d00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c46590\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c47a10\"\n      },\n      {\n        \"name\": \"FUN_00c47e20\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c47e20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c48600\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c48900\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c491c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c498e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4a220\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4bc00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4ea70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c58920\"\n      },\n      {\n        \"name\": \"FUN_00c59240\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c59240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c59540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c59980\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5b660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5b6c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5b860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5c0f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5c470\"\n      },\n      {
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
  "body_end": "00b8de50",
  "body_span_bytes": 33,
  "body_start": "00b8de30",
  "callees": [
    "FUN_00ba6d80",
    "FUN_00ba6440",
    "FUN_00b3d2a0"
  ],
  "callers": [
    "FUN_0100e780",
    "FUN_00c5f690",
    "FUN_00baf130",
    "FUN_01011530",
    "FUN_00fdeac0",
    "FUN_00ffa900",
    "FUN_01001360",
    "FUN_01039b00",
    "FUN_0101246a",
    "FUN_00c72030",
    "FUN_01049f90",
    "FUN_0103e8e0",
    "FUN_0100dc20",
    "FUN_00c5eed0",
    "FUN_00c8d060",
    "FUN_00c58920",
    "FUN_00c316c0",
    "FUN_0100b0a0",
    "FUN_00bbe5f0",
    "FUN_0100a160",
    "FUN_01011350",
    "FUN_0100d960",
    "FUN_00bc0180",
    "FUN_00c59240",
    "FUN_0103aa00",
    "FUN_00c5b660",
    "FUN_00ffb270",
    "FUN_00c44d00",
    "FUN_00c5b860",
    "FUN_00c47a10",
    "FUN_00c774b0",
    "FUN_00fdabf0",
    "FUN_00e066e0",
    "FUN_010593e0",
    "FUN_0106a280",
    "FUN_0100fb00",
    "FUN_0106cc70",
    "FUN_00c706d0",
    "FUN_00c7f5b0",
    "FUN_0103a7d0",
    "FUN_010146c0",
    "FUN_00c491c0",
    "FUN_00c46590",
    "FUN_0100ebb0",
    "FUN_00fe3b30",
    "FUN_00c5c470",
    "FUN_00c817e0",
    "FUN_01014540",
    "FUN_00c6fe50",
    "FUN_00c4bc00",
    "FUN_00be9b20",
    "FUN_010103f0",
    "FUN_00bbe470",
    "FUN_00c48900",
    "FUN_0102d0b0",
    "FUN_00c70860",
    "FUN_00c47e20",
    "FUN_00c5c0f0",
    "FUN_00c5f770",
    "FUN_010251e0",
    "FUN_010144c0",
    "FUN_0103ca40",
    "FUN_01004e50",
    "FUN_00c61070",
    "FUN_0102df20",
    "FUN_0100aec0",
    "FUN_01065f00",
    "FUN_00c4a220",
    "FUN_00c7ae80",
    "FUN_00fe0160",
    "FUN_00c5efb0",
    "FUN_00c59540",
    "FUN_00ff9100",
    "FUN_0100ea20",
    "FUN_00c5b6c0",
    "FUN_00fdf5f0",
    "FUN_0100dd40",
    "FUN_00bb9ff0",
    "FUN_00c48600",
    "FUN_00dd0e10",
    "FUN_00c34e70",
    "FUN_00c4ea70",
    "FUN_00c5f5f0",
    "FUN_010673f0",
    "FUN_00fefe90",
    "FUN_00ff5930",
    "FUN_0100db40",
    "FUN_00c72190",
    "FUN_01014870",
    "FUN_01056160",
    "FUN_00bb59b0",
    "FUN_00c59980",
    "FUN_00e1a040",
    "FUN_00c35810",
    "FUN_00c5c860",
    "FUN_01003690",
    "FUN_00bd9a80",
    "FUN_00ffc8d0",
    "FUN_00fe9580",
    "FUN_0106a0a0",
    "FUN_01012b50",
    "FUN_0103dee0",
    "FUN_01014e30",
    "FUN_0100ffc0",
    "FUN_00c70b50",
    "FUN_00c498e0",
    "FUN_01070890",
    "FUN_00fde230",
    "FUN_01045200",
    "FUN_0103e6e0",
    "FUN_010219b0",
    "FUN_00b96d40",
    "FUN_01047300",
    "FUN_0100efc0",
    "FUN_00c737a0",
    "FUN_00c62ff0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b8de30",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00b8de30",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x78de30",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b8de30(void)",
  "size_bytes": 33,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b8de30",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00c737bb"
    },
    {
      "from": "00bb59bd"
    },
    {
      "from": "00bb59ff"
    },
    {
      "from": "00baf2b4"
    },
    {
      "from": "00b96e09"
    },
    {
      "from": "00b96e1f"
    },
    {
      "from": "00b96edd"
    },
    {
      "from": "00c6fe58"
    },
    {
      "from": "00c316e4"
    },
    {
      "from": "00fe9b05"
    },
    {
      "from": "00c706dd"
    },
    {
      "from": "00c35846"
    },
    {
      "from": "0103aa82"
    },
    {
      "from": "0103ca87"
    },
    {
      "from": "010452c3"
    },
    {
      "from": "00fe3b6c"
    },
    {
      "from": "00bbe608"
    },
    {
      "from": "00bbe630"
    },
    {
      "from": "0102e002"
    },
    {
      "from": "0102e8c5"
    },
    {
      "from": "0102e940"
    },
    {
      "from": "0102e977"
    },
    {
      "from": "0102e9af"
    },
    {
      "from": "0102e9f0"
    },
    {
      "from": "0102ea28"
    },
    {
      "from": "0102d0d3"
    },
    {
      "from": "0103ec6e"
    },
    {
      "from": "0103defb"
    },
    {
      "from": "0103e74f"
    },
    {
      "from": "00bc035b"
    },
    {
      "from": "00fde281"
    },
    {
      "from": "00fde2ae"
    },
    {
      "from": "00ffa946"
    },
    {
      "from": "00ffa951"
    },
    {
      "from": "010013b0"
    },
    {
      "from": "010219c3"
    },
    {
      "from": "00c34e97"
    },
    {
      "from": "00c70866"
    },
    {
      "from": "01065f2d"
    },
    {
      "from": "01067457"
    },
    {
      "from": "00e066ee"
    },
    {
      "from": "0106a13a"
    },
    {
      "from": "0106d135"
    },
    {
      "from": "00ffc9f9"
    },
    {
      "from": "0106a28e"
    },
    {
      "from": "00c70b5a"
    },
    {
      "from": "00bba097"
    },
    {
      "from": "00bbe48e"
    },
    {
      "from": "00bbe4da"
    },
    {
      "from": "00ff5938"
    },
    {
      "from": "00c7aed8"
    },
    {
      "from": "010037f6"
    },
    {
      "from": "00c46649"
    },
    {
      "from": "00c47ad8"
    },
    {

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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
