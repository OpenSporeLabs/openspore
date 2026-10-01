# Evidence 0x00d01ff0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `48d92bbcc18997f1b640c4291d133eaaafbbd710325f0ab653e5e18cc36889a2`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this": "ECX OpaqueRelationshipManager* receiver",
  "return_register": "AL",
  "return_semantics": "Returns byte 0 for a null relationship entry and otherwise (flags >> 1) & 1. Unrelated EAX high bits are not a semantic return contract.",
  "return_width_bytes": 1,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "position": 1,
      "type": "OpaqueEmpire*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "position": 2,
      "type": "OpaqueEmpire*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8
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
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x8",
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "37dbcd34f9ba1d903311607ab075ba22d26815a3981db9fff50344d53d352c21",
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
    "ghidra_parameter_count": 3,
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
        "obs-0016",
        "obs-0017"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0008"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0008",
        "obs-0009",
        "obs-0010"
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
        "obs-0002",
        "obs-0003",
        "obs-0008",
        "obs-0009",
        "obs-0010"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0016",
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
        "obs-0016",
        "obs-0017"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0016",
        "obs-0017"
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
      "at": "0x00d01ff0",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00d01ff1",
      "count": 5,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00d01ff1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00d01ff3",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x01021300",
      "target": "0x01021300"
    },
    {
      "at": "0x00d01ff8",
      "count": 2,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00d01ff8",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0006",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "RelationshipLookup_00d01410",
    "reconstructed": true,
    "va": "0x00d01410"
  },
  {
    "name": "RelationshipMapSelect_00d01ab0",
    "reconstructed": true,
    "va": "0x00d01ab0"
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
    "va": "0x00c4bc00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01008e60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0100dd40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x010134d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01047440"
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
      "0x00d2e480",
      "0x00d2e480",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d01f50",
      "0x00d01f50",
      "0x00d01ff0",
      "0x00d01ff0",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d065a0",
      "0x00d065a0"
    ],
    "conflict_id": "U-003-civilization-progression",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "resolution_status": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
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
  "count": 34,
  "instructions": [
    {
      "address": "00d01ff0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d01ff1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00d01ff3",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00d01ff8",
      "instruction": "MOV EDX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00d01ffc",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00d02000",
      "instruction": "CMP EDX,EAX"
    },
    {
      "address": "00d02002",
      "instruction": "JNZ 0x00d0200c"
    },
    {
      "address": "00d02004",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00d02006",
      "instruction": "JZ 0x00d02010"
    },
    {
      "address": "00d02008",
      "instruction": "MOV EDX,ECX"
    },
    {
      "address": "00d0200a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00d0200c",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00d0200e",
      "instruction": "JNZ 0x00d02012"
    },
    {
      "address": "00d02010",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00d02012",
      "instruction": "MOV ECX,dword ptr [ECX + 0x84]"
    },
    {
      "address": "00d02018",
      "instruction": "MOV EAX,dword ptr [EDX + 0x84]"
    },
    {
      "address": "00d0201e",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d0201f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d02020",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d02021",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d02022",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00d02024",
      "instruction": "CALL 0x00d01ab0"
    },
    {
      "address": "00d02029",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d0202a",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00d0202c",
      "instruction": "CALL 0x00d01410"
    },
    {
      "address": "00d02031",
      "instruction": "POP ESI"
    },
    {
      "address": "00d02032",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00d02034",
      "instruction": "JZ 0x00d02040"
    },
    {
      "address": "00d02036",
      "instruction": "MOV EAX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00d02039",
      "instruction": "SHR EAX,0x1"
    },
    {
      "address": "00d0203b",
      "instruction": "AND AL,0x1"
    },
    {
      "address": "00d0203d",
      "instruction": "RET 0x8"
    },
    {
      "address": "00d02040",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00d02042",
      "instruction": "RET 0x8"
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
  "original_bytes": 9795,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this\": \"ECX OpaqueRelationshipManager* receiver\",\n    \"return_register\": \"AL\",\n    \"return_semantics\": \"Returns byte 0 for a null relationship entry and otherwise (flags >> 1) & 1. Unrelated EAX high bits are not a semantic return contract.\",\n    \"return_width_bytes\": 1,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"position\": 1,\n        \"type\": \"OpaqueEmpire*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"position\": 2,\n        \"type\": \"OpaqueEmpire*\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PRIMITIVES\",\n      \"score\": 22,\n      \"symbol\": \"RelationshipMapSelect_00d01ab0\",\n      \"va\": \"0x00d01ab0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 16,\n      \"symbol\": \"DiplomacyTransition_00d01e30\",\n      \"va\": \"0x00d01e30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 16,\n      \"symbol\": \"DiplomacyTransition_00d038e0\",\n      \"va\": \"0x00d038e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 16,\n      \"symbol\": \"DiplomacyTransition_00d065a0\",\n      \"va\": \"0x00d065a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 16,\n      \"symbol\": \"DiplomacyTransition_00d06920\",\n      \"va\": \"0x00d06920\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipMap\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PRIMITIVES\",\n      \"score\": 15,\n      \"symbol\": \"RelationshipLookup_00d01410\",\n      \"va\": \"0x00d01410\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 8,\n      \"symbol\": \"RelationshipScoreObjects_00d00d60\",\n      \"va\": \"0x00d00d60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 6,\n      \"symbol\": \"RelationshipScoreBand_00d00d00\",\n      \"va\": \"0x00d00d00\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The current-empire substitution, directed key order, helper call order, null record path, and alliance bit 1 are exact. Map selection and lower-bound lookup remain opaque dependencies; PKG-12 cache/refcount behavior remains external.\",\n  \"audit_findings\": [\n    \"PKG13-DIP-ABI-001\",\n    \"PKG13-DIP-META-001\",\n    \"PKG13-DIP-META-002\",\n    \"PKG13-DIP-META-003\"\n  ],\n  \"audit_status\": \"clean_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"Invalid null-first and null-current combinations are preserved as unchecked paths and are not modeled as successful API inputs.\",\n    \"Runtime manager/empire/map availability and actual relationship records remain gated.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueRelationshipManager\",\n  \"cluster\": null,\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"RelationshipLookup_00d01410\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d01410\"\n      },\n      {\n        \"name\": \"RelationshipMapSelect_00d01ab0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d01ab0\"\n      },\n      {\n        \"name\": \"pkg12_space_01021300\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021300\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4bc00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01008e60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0100dd40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010134d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01047440\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00c4bc8a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c4bc00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010090d1\",\n        \"direction\": \"in\",\n        \"other\": \"0x01008e60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0100de65\
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
  "body_end": "00d02044",
  "body_span_bytes": 85,
  "body_start": "00d01ff0",
  "callees": [
    "FUN_00d01410",
    "FUN_01021300",
    "FUN_00d01ab0"
  ],
  "callers": [
    "FUN_0100dd40",
    "FUN_00c4bc00",
    "FUN_01047440",
    "FUN_010134d0",
    "FUN_01008e60"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d01ff0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Simulator::cRelationshipManager::IsAllied2",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cRelationshipManager *"
    },
    {
      "name": "pEmpire1",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "cEmpire *"
    },
    {
      "name": "pEmpire2",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "cEmpire *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x901ff0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool Simulator::cRelationshipManager::IsAllied2(cRelationshipManager * this, cEmpire * pEmpire1, cEmpire * pEmpire2)",
  "size_bytes": 85,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d01ff0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 9,
  "xrefs": [
    {
      "from": "010090d1"
    },
    {
      "from": "0100de65"
    },
    {
      "from": "01013518"
    },
    {
      "from": "00c4bc8a"
    },
    {
      "from": "010474f1"
    },
    {
      "from": "00aed8f3"
    },
    {
      "from": "00c5bb1d"
    },
    {
      "from": "00fe2ff3"
    },
    {
      "from": "0104a50b"
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
  "file": "src/reconstruction/pkg13_diplomacy_predicate/diplomacy_predicate.cpp",
  "files": [
    "reconstruction/staging/pkg13-diplomacy-predicate/diplomacy_predicate.cpp",
    "reconstruction/staging/pkg13-diplomacy-predicate/diplomacy_predicate.hpp",
    "reconstruction/staging/pkg13-diplomacy-predicate/diplomacy_predicate_test.cpp",
    "src/reconstruction/pkg13_diplomacy_predicate/diplomacy_predicate.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-diplomacy/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-diplomacy-predicate/00d01ff0.json"
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
    "gate-diplomacy-relationship-records"
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
  "OpaqueEmpire",
  "OpaqueEmpire*",
  "OpaqueRelationshipEntry",
  "OpaqueRelationshipManager",
  "OpaqueRelationshipMap"
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
      "0x00d2e480",
      "0x00d2e480",
      "0x00d01410",
      "0x00d01410",
      "0x00d01ab0",
      "0x00d01ab0",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d01f50",
      "0x00d01f50",
      "0x00d01ff0",
      "0x00d01ff0",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d065a0",
      "0x00d065a0"
    ],
    "conflict_id": "U-003-civilization-progression",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "resolution_status": "The technology-level surface is recorded, but the binary writer/callback chain from one level to the next is not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
