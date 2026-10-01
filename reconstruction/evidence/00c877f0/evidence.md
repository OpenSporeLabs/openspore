# Evidence 0x00c877f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `efa7dc2b8e32c1c81d9a9e8d4cd5d4153e7e4f1ca7ced40f7acc699dc1f7cac9`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "return_observation": "The live body returns through the item vtable notification path and has no value return.",
  "return_type": "void",
  "stack_arguments": [
    {
      "cleanup": "RET 0x4 in the live body",
      "entry_offset": "ESP+0x04",
      "position": 1,
      "type": "OpaquePropertyList*",
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBX",
      "EDI",
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "e9e0f23a3b4cfa1b4c21f62d6806c53a6684c64ca7fe176c53089a81322a2bff",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
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
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0028"
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
        "obs-0004",
        "obs-0020"
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
        "obs-0007",
        "obs-0008",
        "obs-0013",
        "obs-0022"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          36,
          48
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0013",
        "obs-0022",
        "obs-0028"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0028"
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
        "obs-0028"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0028"
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
      "at": "0x00c877f0",
      "count": 3,
      "first_use": 0,
      "first_write_index": 5,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c877f1",
      "count": 8,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c877f2",
      "count": 3,
      "first_use": 2,
      "first_write_index": 35,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00c877f2",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0004",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00c877f2",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c877f6",
      "count": 8,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c877f7",
      "count": 4,
      "first_use": 4,
      "first_write_index": 12,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c877f7",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c877f9",
      "definite": true,
      "id": "obs-0009",
      "index": 5,
      "kind": "RE
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
    "va": "0x00ac0cb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c878d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c879a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0103a480"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0103fc10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0104e340"
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
      "0x00c877f0",
      "0x00000014",
      "0x00000020",
      "0x00c877f0"
    ],
    "conflict_id": "TB-FL-010",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "do_not_collapse",
      "preferred_claim": null,
      "preserved_alternatives": true,
      "scope_note": "cSpaceInventoryItem identity is strong, but the shared-prefix claim is not transferable to cSpaceToolData or cargo records.",
      "status": "preserved_alternatives",
      "taxonomy": "preserved_alternatives"
    },
    "resolution_status": "preserved_alternatives",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "cSpaceInventoryItem shared-prefix field maps",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  },
  {
    "anchors": [
      "0x01037d30",
      "0x01037d30",
      "0x01037d30",
      "0x01037d30",
      "0x0103a480",
      "0x0103a480",
      "0x0103e8e0",
      "0x0103e8e0",
      "0x0103fc10",
      "0x0103fc10",
      "0x00c877f0",
      "0x00c877f0",
      "0x00596da0",
      "0x01037d30",
      "0x00d2e8a0",
      "0x0103e8e0"
    ],
    "conflict_id": "U-E004",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x01037d30",
      "0x01037d30",
      "0x01037d30",
      "0x01037d30",
      "0x0103a480",
      "0x0103a480",
      "0x0103e8e0",
      "0x0103e8e0",
      "0x0103fc10",
      "0x0103fc10",
      "0x00c877f0",
      "0x00c877f0",
      "0x01037d30",
      "0x0103fba0",
      "0x010535e0",
      "0x010535f0"
    ],
    "conflict_id": "U-E006",
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
  "count": 57,
  "instructions": [
    {
      "address": "00c877f0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c877f1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c877f2",
      "instruction": "MOV ESI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00c877f6",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c877f7",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00c877f9",
      "instruction": "MOV EBX,dword ptr [EDI + 0x30]"
    },
    {
      "address": "00c877fc",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "00c877fe",
      "instruction": "JZ 0x00c8781c"
    },
    {
      "address": "00c87800",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c87802",
      "instruction": "JZ 0x00c8780c"
    },
    {
      "address": "00c87804",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00c87806",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00c87808",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c8780a",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c8780c",
      "instruction": "MOV dword ptr [EDI + 0x30],ESI"
    },
    {
      "address": "00c8780f",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00c87811",
      "instruction": "JZ 0x00c8781c"
    },
    {
      "address": "00c87813",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "00c87815",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00c87818",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00c8781a",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c8781c",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c8781e",
      "instruction": "JZ 0x00c87876"
    },
    {
      "address": "00c87820",
      "instruction": "LEA EAX,[EDI + 0x34]"
    },
    {
      "address": "00c87823",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c87824",
      "instruction": "PUSH 0x3068d95d"
    },
    {
      "address": "00c87829",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c8782a",
      "instruction": "CALL 0x006a1360"
    },
    {
      "address": "00c8782f",
      "instruction": "LEA ECX,[EDI + 0x48]"
    },
    {
      "address": "00c87832",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c87833",
      "instruction": "PUSH 0x4cad19b"
    },
    {
      "address": "00c87838",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c87839",
      "instruction": "CALL 0x006a1360"
    },
    {
      "address": "00c8783e",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00c87840",
      "instruction": "MOV EDX,dword ptr [EDX + 0x24]"
    },
    {
      "address": "00c87843",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "00c87846",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00c8784a",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c8784b",
      "instruction": "PUSH 0x1bfc1dee"
    },
    {
      "address": "00c87850",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c87852",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c87854",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c87856",
      "instruction": "JZ 0x00c8786d"
    },
    {
      "address": "00c87858",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c8785c",
      "instruction": "CMP word ptr [ECX + 0x12],0xa"
    },
    {
      "address": "00c87861",
      "instruction": "JNZ 0x00c8786d"
    },
    {
      "address": "00c87863",
      "instruction": "CALL 0x0041ea00"
    },
    {
      "address": "00c87868",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00c8786a",
      "instruction": "MOV dword ptr [EDI + 0x24],EAX"
    },
    {
      "address": "00c8786d",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "00c8786f",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4c]"
    },
    {
      "address": "00c87872",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c87874",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c87876",
      "instruction": "POP EDI"
    },
    {
      "address": "00c87877",
      "instruction": "POP ESI"
    },
    {
      "address": "00c87878",
      "instruction": "POP EBX"
    },
    {
      "address": "00c87879",
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
  "original_bytes": 15481,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"return_observation\": \"The live body returns through the item vtable notification path and has no value return.\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"cleanup\": \"RET 0x4 in the live body\",\n        \"entry_offset\": \"ESP+0x04\",\n        \"position\": 1,\n        \"type\": \"OpaquePropertyList*\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 14,\n      \"symbol\": \"pkg12_space_00de9fc0\",\n      \"va\": \"0x00de9fc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 10,\n      \"symbol\": \"FUN_00aea230\",\n      \"va\": \"0x00aea230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 10,\n      \"symbol\": \"FUN_00aea5d0\",\n      \"va\": \"0x00aea5d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 10,\n      \"symbol\": \"FUN_00aeb160\",\n      \"va\": \"0x00aeb160\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 10,\n      \"symbol\": \"Simulator_cCommManager_CreateAndDispatchEvent_00aeb720\",\n      \"va\": \"0x00aeb720\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00aea250\",\n      \"va\": \"0x00aea250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"pkg12_space_01021300\",\n      \"va\": \"0x01021300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_0102d1b0\",\n      \"va\": \"0x0102d1b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The live body uses an indirect vtable notification that cannot be linked to a concrete method without a separate vtable reconstruction.\",\n    \"The staging model does not modify the integrated PKG-12 source, so production linkability and runtime property ownership remain out of scope.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"InventoryItem\",\n  \"cluster\": null,\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac0cb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c878d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c879a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0103a480\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0103fc10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0104e340\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00ac0d52\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ac0cb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c8795d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c878d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c87ac1\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c879a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0103a515\",\n        \"direction\": \"in\",\n        \"other\": \"0x0103a480\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0103fcaa\",\n        \"direction\": \"in\",\n        \"other\": \"0x0103fc10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0104e3d5\",\n        \"direction\": \"in\",\n        \"other\": \"0x0104e340\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c87863\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041ea00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c8782a\",\n        \"direction\": \"out\",\n        \"other\": \"0x006a1360\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c87839\",\n        \"direction\": \"out\",\n        \"other\": \"0x006a1360\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 6,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"App::Property::GetText\",\n      \"FUN_0041ea00\",\n      \"PropertyList+0x24\",\n      \"InventoryItem+0x4c\"\n    ],\n    \"manifest_callers\": [\n      \"direct_caller_functions_6\",\n      \"call_xrefs_6\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0477\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n
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
  "body_end": "00c8787b",
  "body_span_bytes": 140,
  "body_start": "00c877f0",
  "callees": [
    "App::Property::GetText",
    "FUN_0041ea00"
  ],
  "callers": [
    "FUN_0103a480",
    "FUN_00c879a0",
    "FUN_0103fc10",
    "FUN_00ac0cb0",
    "FUN_0104e340",
    "FUN_00c878d0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c877f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "cSpaceInventoryItem_ctor",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8877f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined cSpaceInventoryItem_ctor(void)",
  "size_bytes": 140,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c877f0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "00ac0d52"
    },
    {
      "from": "0103a515"
    },
    {
      "from": "0103fcaa"
    },
    {
      "from": "0104e3d5"
    },
    {
      "from": "00c8795d"
    },
    {
      "from": "00c87ac1"
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
  "file": "src/reconstruction/pkg12_space/space_inventory_entry.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_inventory_entry.cpp",
    "reconstruction/staging/pkg12-space/space_inventory_entry.hpp",
    "reconstruction/staging/pkg12-space/space_inventory_entry_model_test.cpp",
    "src/reconstruction/pkg12_space/space_inventory_entry.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg12-space/00c877f0.json"
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
    "gate-space-inventory-item"
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
  "original_bytes": 6678,
  "preview": "{\n  \"category\": \"GAMEPLAY_LOGIC\",\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"mechanics\": 0.99\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 8,\n  \"evidence\": [\n    {\n      \"kind\": \"targeted_decompilation_and_disassembly\",\n      \"observation\": \"PropertyList AddRef/Release, three property IDs, type check 10, +0x24 write, vtable+0x4c call, RET 0x4.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00c877f0\"\n    },\n    {\n      \"kind\": \"sibling_constructor\",\n      \"observation\": \"Installs vtable 0x01473558 and initializes cSpaceInventoryItem fields.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00c87660\"\n    },\n    {\n      \"kind\": \"factory_caller\",\n      \"observation\": \"Allocates 0x7c, base-constructs, and invokes the target with a property list.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00c878d0\"\n    },\n    {\n      \"kind\": \"vtable_memory\",\n      \"observation\": \"The +0x4c slot points to FUN_00b1e4d0; the separate 0x00b14ed0 function is not this slot.\",\n      \"source\": \"ghidra://SporeApp.exe@0x01473558\"\n    }\n  ],\n  \"family\": \"space_inventory_property_application\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": [],\n    \"direct_callers\": [],\n    \"globals\": [],\n    \"structures\": [\n      {\n        \"fields\": [\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\"\n            ]\n          },\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\"\n            ]\n          },\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\"\n            ]\n          },\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\"\n            ]\n          },\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\"\n            ]\n          },\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\"\n            ]\n          }\n        ],\n        \"size\": \"0x7c\",\n        \"type\": \"cSpaceInventoryItem\"\n      },\n      {\n        \"fields\": [\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\"\n            ]\n          },\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\"\n            ]\n          },\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\"\n            ]\n          },\n          {\n            \"keys\": [\n              \"name\",\n              \"offset\"\n            ]\n          }\n        ],\n        \"size\": \"0x50\",\n        \"type\": \"cSpaceInventoryItem__vftable\"\n      },\n      {\n        \"observation\": \"The target uses PropertyList virtual AddRef/Release/GetProperty through its vtable; no concrete PropertyList layout is required for the contract.\",\n        \"type\": \"PropertyList\"\n      }\n    ],\n    \"vtables\": [\n      {\n        \"address\": \"0x01473558\",\n        \"observation\": \"Direct data xrefs from FUN_00c87660 and FUN_00c87770, the two cSpaceInventoryItem setup/teardown paths.\",\n        \"status\": \"candidate_vtable_confirmed\"\n      },\n      {\n        \"observation\": \"The target's indirect call is vtable+0x4c. Under the current Ghidra cSpaceInventoryItem vtable type, +0x4c is ParseProp, not IsAvailableInCurrentPlanet; IsAvailableInCurrentPlanet is +0x44.\",\n        \"status\": \"slot_mapping_corrected\"\n      },\n      {\n        \"address\": \"0x00b1e4d0\",\n        \"observation\": \"The live vtable memory at 0x01473558+0x4c points to FUN_00b1e4d0, which decompiles to a zero-return stub. Do not substitute the separate FUN_00b14ed0 body for this slot.\",\n        \"status\": \"slot_target_observed\"\n      }\n    ],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": \"A null PropertyList skips property extraction and the virtual call, but still performs the old-list release path when different.\",\n      \"identity_boundary\": \"Use SetPropList/apply-from-PropertyList as the semantic role; retain cSpaceInventoryItem_ctor only as the live Ghidra name.\",\n      \"inputs\": [\n        \"one explicit PropertyList pointer; RET 0x4 confirms one dword stack argument\"\n      ],\n      \"ordering\": [\n        \"PropertyList ownership replacement\",\n        \"description/detail text writes\",\n        \"typed property query and conditional item-position write\",\n        \"virtual slot +0x4c\",\n        \"return\"\n      ],\n      \"outputs\": [],\n      \"postconditions\": [],\n      \"preconditions\": [\n        \"receiver is a valid cSpaceInventoryItem-like object\",\n        \"PropertyList virtual methods are valid when the list is non-null\"\n      ],\n      \"purpose\": \"not_reported\",\n      \"return\": {\n        \"status\": \"not_reported\"\n      },\n      \"side_effects\": [\n        \"mpPropList reference count changes\",\n        \"mDescription and mDetailDescription are updated\",\n        \"mItemPosition may be updated\",\n        \"virtual receiver behavior may run\"\n      ],\n      \"status\": \"supported_static_contract_identity_partial\",\n      \"unresolved\": [\n        \"What is the exact semantic identity of receiver vtable slot +0x4c/ParseProp?\",\n        \"What do hashed property IDs 0x3068d95d, 0x04cad19b, and 0x1bfc1dee name?\",\n        \"Is the +0x24 write semantically mItemPosition for every accepted property, or only for a narrower property context?\",\n        \"Should the canonical replacement name be SetPropList or InitializeFromPropertyList?\"\n      ]\n    }\n  },\n  \"invariants\": {\n    \"failure_semantics\": [],\n    \"invariants\": [],\n    \"invariants_status\": \"not_reported\"\n  },\n  \"name\": \"cSpaceInventoryItem_apply_property_list\",\n  \"package\": {\n    \"caveat\": \"not_reported\",
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
  "/Spore/App/PropertyList",
  "/Spore/Simulator/cSpaceInventoryItem",
  "InventoryItem",
  "InventoryItemServices",
  "InventoryItemVtable",
  "LocalizedString",
  "OpaqueLocalizedString",
  "OpaqueProperty",
  "OpaquePropertyList",
  "OpaquePropertyList*",
  "ResourceKey",
  "intrusive_ptr<App::PropertyList>",
  "uint",
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
      "0x00c877f0",
      "0x00000014",
      "0x00000020",
      "0x00c877f0"
    ],
    "conflict_id": "TB-FL-010",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "do_not_collapse",
      "preferred_claim": null,
      "preserved_alternatives": true,
      "scope_note": "cSpaceInventoryItem identity is strong, but the shared-prefix claim is not transferable to cSpaceToolData or cargo records.",
      "status": "preserved_alternatives",
      "taxonomy": "preserved_alternatives"
    },
    "resolution_status": "preserved_alternatives",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "cSpaceInventoryItem shared-prefix field maps",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  },
  {
    "anchors": [
      "0x01037d30",
      "0x01037d30",
      "0x01037d30",
      "0x01037d30",
      "0x0103a480",
      "0x0103a480",
      "0x0103e8e0",
      "0x0103e8e0",
      "0x0103fc10",
      "0x0103fc10",
      "0x00c877f0",
      "0x00c877f0",
      "0x00596da0",
      "0x01037d30",
      "0x00d2e8a0",
      "0x0103e8e0"
    ],
    "conflict_id": "U-E004",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x01037d30",
      "0x01037d30",
      "0x01037d30",
      "0x01037d30",
      "0x0103a480",
      "0x0103a480",
      "0x0103e8e0",
      "0x0103e8e0",
      "0x0103fc10",
      "0x0103fc10",
      "0x00c877f0",
      "0x00c877f0",
      "0x01037d30",
      "0x0103fba0",
      "0x010535e0",
      "0x010535f0"
    ],
    "conflict_id": "U-E006",
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
