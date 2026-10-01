# Evidence 0x00b25fb0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e9dd71476cac84f3058f7b227c819b060b6358223b6b141279f3de050788546e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "NounProjection*",
  "ordinary_stack_arguments": [],
  "return_note": "opaque result word",
  "return_register": "EAX",
  "return_type": "NounObject*",
  "return_width_bytes": 4,
  "saved_registers": [
    "ESI",
    "ECX"
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
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
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
  "content_sha256": "3f6199aceb29c4c9fdb719c1cca14678733208527d3c03004f4ecc8c69b61a8a",
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
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0011",
        "obs-0016"
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
        "obs-0007",
        "obs-0010",
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
        "obs-0016"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0011",
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
        "obs-0011",
        "obs-0016"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0016"
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
      "at": "0x00b25fb0",
      "count": 2,
      "first_use": 0,
      "first_write_index": 8,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b25fb1",
      "count": 2,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b25fb2",
      "definite": true,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b25fb4",
      "id": "obs-0004",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x01021300",
      "target": "0x01021300"
    },
    {
      "at": "0x00b25fbd",
      "count": 2,
      "first_use": 6,
      "first_write_index": 6,
      "id": "obs-0005",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x84]",
      "reg": "EAX"
    },
    {
      "at": "0x00b25fbd",
      "definite": true,
      "id": "obs-0006",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EAX + 0x84]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b25fc4",
      "definite": true,
      "id": "obs-0007",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,ESI",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00b25fc6",
      "id": "obs-0008",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b25f40",
      "target": "0x00b25f40"
    },
    {
      "at": "0x00b25fcb",
      "id": "obs-0009",
      "index": 10,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b25fcc",
      "id": "obs-0010",
      "index": 11,
      "kind": "REG_RESTORE",
      "raw": "POP ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b25fcd",
      "form": "RET",
      "id": "obs-0011",
      "imm": null,
      "index": 12,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00b25fce",
      "count": 1,
      "first_use": 13,
      "first_write_index": null,
      "id": "obs-0012",
      "index": 13,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00b25fce",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0013",
      "index": 13,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x00b25fd2",
      "id": "obs-0014",
      "index": 14,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b25fd3",
 
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b25f40",
    "reconstructed": false,
    "va": "0x00b25f40"
  },
  {
    "name": "pkg12_space_01021300",
    "reconstructed": true,
    "va": "0x01021300"
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
    "va": "0x00ae2f70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae37c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aebe90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aee830"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b5f670"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b998a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b99ed0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bcc860"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd7ea0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd80d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bdb3b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bdde70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bde4a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be1340"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be1860"
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
  "count": 17,
  "instructions": [
    {
      "address": "00b25fb0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00b25fb1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b25fb2",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b25fb4",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00b25fb9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b25fbb",
      "instruction": "JZ 0x00b25fce"
    },
    {
      "address": "00b25fbd",
      "instruction": "MOV EAX,dword ptr [EAX + 0x84]"
    },
    {
      "address": "00b25fc3",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b25fc4",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b25fc6",
      "instruction": "CALL 0x00b25f40"
    },
    {
      "address": "00b25fcb",
      "instruction": "POP ESI"
    },
    {
      "address": "00b25fcc",
      "instruction": "POP ECX"
    },
    {
      "address": "00b25fcd",
      "instruction": "RET"
    },
    {
      "address": "00b25fce",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00b25fd2",
      "instruction": "POP ESI"
    },
    {
      "address": "00b25fd3",
      "instruction": "POP ECX"
    },
    {
      "address": "00b25fd4",
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
  "original_bytes": 15223,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"NounProjection*\",\n    \"ordinary_stack_arguments\": [],\n    \"return_note\": \"opaque result word\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"NounObject*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"ESI\",\n      \"ECX\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"plain RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 8,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b25f40\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b25f40\"\n      },\n      {\n        \"name\": \"pkg12_space_01021300\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021300\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae2f70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae37c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebe90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aee830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b5f670\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b998a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b99ed0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bcc860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd7ea0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd80d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdb3b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdde70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bde4a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be1340\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be1860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be88d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be92e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be9980\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00beaa30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bef770\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00befd80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf02b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf1170\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf1270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf14b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false
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
  "body_end": "00b25fd4",
  "body_span_bytes": 37,
  "body_start": "00b25fb0",
  "callees": [
    "FUN_01021300",
    "FUN_00b25f40"
  ],
  "callers": [
    "FUN_00cf84a0",
    "FUN_00aeb240",
    "FUN_00d100b0",
    "FUN_00d06270",
    "FUN_00bf9e70",
    "FUN_00cf31f0",
    "FUN_00be9980",
    "FUN_00bd80d0",
    "FUN_00cf7090",
    "FUN_00e06220",
    "FUN_00cf93b0",
    "FUN_00d00ee0",
    "FUN_00cf0f80",
    "FUN_00bf3180",
    "FUN_00bf8a70",
    "FUN_00bcc860",
    "FUN_00bf1170",
    "FUN_00cfbc10",
    "FUN_00e05de0",
    "FUN_00cf7150",
    "FUN_00cfe930",
    "FUN_00e2ade0",
    "FUN_00dd0380",
    "FUN_00dcedb0",
    "FUN_00cfeeb0",
    "FUN_00fe0160",
    "FUN_00cf7630",
    "FUN_00cf7600",
    "FUN_00ff9100",
    "FUN_00cfa3b0",
    "FUN_00bff2d0",
    "FUN_00b99ed0",
    "FUN_00bf4370",
    "FUN_00cf9ba0",
    "FUN_00cf75d0",
    "FUN_0106fc90",
    "FUN_010050d0",
    "FUN_00bf74a0",
    "FUN_00cf7d40",
    "FUN_00beaa30",
    "FUN_00c00b00",
    "FUN_00e063d0",
    "FUN_00cfee00",
    "FUN_00fe2ab0",
    "FUN_010678e0",
    "FUN_00e052d0",
    "FUN_00e05590",
    "FUN_00bf1270",
    "FUN_00ea17b0",
    "FUN_00be88d0",
    "FUN_00c9e700",
    "FUN_00cfb890",
    "FUN_00cf8e20",
    "FUN_00bdb3b0",
    "FUN_00c07480",
    "FUN_00dd2240",
    "FUN_00be92e0",
    "FUN_00e07e70",
    "FUN_010053c0",
    "FUN_00cf44c0",
    "FUN_00b998a0",
    "FUN_00bf9820",
    "FUN_00e04aa0",
    "FUN_00cf1be0",
    "FUN_00ce8160",
    "FUN_00d56c30",
    "FUN_00b5f670",
    "FUN_00cf8160",
    "FUN_00d130d0",
    "FUN_00d0e170",
    "FUN_00bef770",
    "FUN_00e35370",
    "FUN_00ae2f70",
    "FUN_00ae37c0",
    "FUN_00e053c0",
    "FUN_00cfa120",
    "FUN_00cf6e70",
    "FUN_00bde4a0",
    "FUN_00bf02b0",
    "FUN_00cea1a0",
    "FUN_00cfa0c0",
    "FUN_00bf14b0",
    "FUN_00e2d6a0",
    "FUN_00be1340",
    "FUN_00cf8ec0",
    "FUN_00bdde70",
    "FUN_00bd7ea0",
    "FUN_00caa360",
    "FUN_00e2b9d0",
    "FUN_00aebe90",
    "FUN_00c94470",
    "FUN_00cea970",
    "FUN_00befd80",
    "FUN_00aee830",
    "FUN_00cf78d0",
    "FUN_00be1860",
    "FUN_00bfbbf0",
    "FUN_00ce87c0",
    "FUN_00bfa660",
    "FUN_00e060c0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b25fb0",
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
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00b25fb0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x725fb0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b25fb0(void)",
  "size_bytes": 37,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b25fb0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00d00f0a"
    },
    {
      "from": "00ae2f8d"
    },
    {
      "from": "00beaa8d"
    },
    {
      "from": "00be9371"
    },
    {
      "from": "00be8935"
    },
    {
      "from": "00be8fbd"
    },
    {
      "from": "00be8ff0"
    },
    {
      "from": "00be9016"
    },
    {
      "from": "00be9049"
    },
    {
      "from": "00be906c"
    },
    {
      "from": "00be909f"
    },
    {
      "from": "00be90e1"
    },
    {
      "from": "00be9114"
    },
    {
      "from": "00be9158"
    },
    {
      "from": "00be918b"
    },
    {
      "from": "00be91ae"
    },
    {
      "from": "00be91e1"
    },
    {
      "from": "00ae3810"
    },
    {
      "from": "00ae3831"
    },
    {
      "from": "00ae386b"
    },
    {
      "from": "00ae3884"
    },
    {
      "from": "00ae38c7"
    },
    {
      "from": "00bf4517"
    },
    {
      "from": "00bf4571"
    },
    {
      "from": "00bef794"
    },
    {
      "from": "00bef7b9"
    },
    {
      "from": "00bfbc28"
    },
    {
      "from": "00bfc0d6"
    },
    {
      "from": "00bfc109"
    },
    {
      "from": "00bfc131"
    },
    {
      "from": "00bfc164"
    },
    {
      "from": "00bde4cf"
    },
    {
      "from": "00bf118a"
    },
    {
      "from": "00bf12b9"
    },
    {
      "from": "00aeb3ab"
    },
    {
      "from": "00aec5bd"
    },
    {
      "from": "00bf14f9"
    },
    {
      "from": "00bf31f6"
    },
    {
      "from": "00befdb5"
    },
    {
      "from": "00bf74e7"
    },
    {
      "from": "00bf985d"
    },
    {
      "from": "00bf9eb9"
    },
    {
      "from": "00bfa03b"
    },
    {
      "from": "00bfa67e"
    },
    {
      "from": "00c00c26"
    },
    {
      "from": "00caa5c2"
    },
    {
      "from": "00cf75d7"
    },
    {
      "from": "00cf7639"
    },
    {
      "from": "00cf9f82"
    },
    {
      "from": "00cf9fbe"
    },
    {
      "from": "00cf9ffe"
    },
    {
      "from": "00cf7d4a"
    },
    {
      "from": "00cfef13"
    },
    {
      "from": "00cfef68"
    },
    {
      "from": "00cfef8b"
    },
    {
      "from": "00cff052"
    },
    {
      "from": "00cff3c4"
    },
    {
      "from": "00cff5c9"
    },
    {
      "from": "00cff5f8"
    },
    {
      "from": "00cff6f4"
    },
    {
      "from": "00cff90e"
    },
    {
      "from": "00cff936"
    },
    {
      "from": "00cff967"
    },
    {
      "from": "00cff9f0"
    },
    {
      "from": "00cffa23"
    },
    {
      "from": "00cffb35"
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
  "metadata": [
    "reconstruction/metadata/pkg13-c2-tribe-civilization/00b25fb0.json"
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
    "The current-player provider must return a valid state window before +0x84 is read.",
    "The null-current receiver fallback must not be treated as a valid noun-object result by downstream callers without runtime evidence.",
    "The receiver must be a valid noun-projection-compatible object for 0x00b25f40.",
    "The resolver vector, object pointers, object vtables, and vtable+0x4c targets must be valid.",
    "The resolver's 0x00b21340 map/list callbacks and their ownership effects require original-process observation."
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "NounObject* opaque result word",
  "NounProjection*"
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
  }
]
```
