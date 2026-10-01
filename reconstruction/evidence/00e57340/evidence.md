# Evidence 0x00e57340

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `3b3b537bfc2b28dad5d76416de03d0b32e06dd3360d1e80ea4141021c90848f0`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
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
  "content_sha256": "c186c8fe6e6666b29d8d89cc0914bf14ca234178b2f2e849de6177d54a85a9b8",
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
    "ghidra_parameter_count": 1,
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
        "obs-0022"
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
        "obs-0002",
        "obs-0016",
        "obs-0019"
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
        "obs-0009",
        "obs-0010",
        "obs-0011"
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
        "obs-0009",
        "obs-0010",
        "obs-0011"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0022"
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
        "obs-0022"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0022"
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
      "at": "0x00e57340",
      "count": 7,
      "first_use": 0,
      "first_write_index": 2,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00e57340",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e57340",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e57344",
      "count": 7,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x358]",
      "reg": "EAX"
    },
    {
      "and_esp": null,
      "at": "0x00e5734a",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0005",
      "index": 2,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00e5734a",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00e5734d",
      "count": 6,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00e5734e",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [0x016b3c04]",
      "
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
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
  "content_sha256": "c186c8fe6e6666b29d8d89cc0914bf14ca234178b2f2e849de6177d54a85a9b8",
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
    "ghidra_parameter_count": 1,
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
        "obs-0022"
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
        "obs-0002",
        "obs-0016",
        "obs-0019"
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
        "obs-0009",
        "obs-0010",
        "obs-0011"
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
        "obs-0009",
        "obs-0010",
        "obs-0011"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0022"
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
        "obs-0022"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0022"
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
      "at": "0x00e57340",
      "count": 7,
      "first_use": 0,
      "first_write_index": 2,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00e57340",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e57340",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e57344",
      "count": 7,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x358]",
      "reg": "EAX"
    },
    {
      "and_esp": null,
      "at": "0x00e5734a",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0005",
      "index": 2,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00e5734a",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00e5734d",
      "count": 6,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00e5734e",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [0x016b3c04]",
      "
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
    "name": "Simulator::Cell::ShouldNotAttack",
    "reconstructed": false,
    "va": "0x00e57460"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e57ce0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e57fd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e582c0"
  },
  {
    "name": "Simulator::Cell::GetDamageAmount",
    "reconstructed": false,
    "va": "0x00e58980"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e59e50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e5add0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e5c460"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e5d580"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e660e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e67890"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e68470"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e68630"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e6a250"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e6a3f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e6b370"
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
      "0x00e74a20",
      "0x00e57460",
      "0x00e6d200",
      "0x00e57340",
      "0x00e780a0",
      "0x00000108",
      "0x00e74a20",
      "0x00000108"
    ],
    "conflict_id": "TB-FL-012",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "separate_entities",
      "preferred_claim": "Use the original direct field/body evidence as the ABI anchor.",
      "preserved_alternatives": true,
      "scope_note": "The current padding is a replacement limitation and cannot define the original structure.",
      "status": "preferred_claim_with_limit",
      "taxonomy": "preferred_claim_with_limit"
    },
    "resolution_status": "preferred_claim_with_limit",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "cCellObjectData original middle fields versus current opaque padding",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
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
  "count": 44,
  "instructions": [
    {
      "address": "00e57340",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00e57344",
      "instruction": "MOV EAX,dword ptr [EAX + 0x358]"
    },
    {
      "address": "00e5734a",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00e5734d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e5734e",
      "instruction": "MOV ESI,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e57354",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "00e57357",
      "instruction": "JNZ 0x00e57367"
    },
    {
      "address": "00e57359",
      "instruction": "MOV ECX,dword ptr [ESI + 0x5190]"
    },
    {
      "address": "00e5735f",
      "instruction": "MOV EDX,dword ptr [ECX + 0x1c]"
    },
    {
      "address": "00e57362",
      "instruction": "CALL 0x00e4ee60"
    },
    {
      "address": "00e57367",
      "instruction": "MOV EDX,dword ptr [ESI + 0x5190]"
    },
    {
      "address": "00e5736d",
      "instruction": "MOV EDX,dword ptr [EDX + 0x1c]"
    },
    {
      "address": "00e57370",
      "instruction": "CMP EDX,0x3e8"
    },
    {
      "address": "00e57376",
      "instruction": "JNZ 0x00e5737f"
    },
    {
      "address": "00e57378",
      "instruction": "MOV ECX,0x1483e60"
    },
    {
      "address": "00e5737d",
      "instruction": "JMP 0x00e573a8"
    },
    {
      "address": "00e5737f",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00e57381",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "00e57383",
      "instruction": "JL 0x00e57398"
    },
    {
      "address": "00e57385",
      "instruction": "MOV ECX,0x1483c34"
    },
    {
      "address": "00e5738a",
      "instruction": "LEA EBX,[EBX]"
    },
    {
      "address": "00e57390",
      "instruction": "ADD ECX,0x1c"
    },
    {
      "address": "00e57393",
      "instruction": "INC ESI"
    },
    {
      "address": "00e57394",
      "instruction": "CMP EDX,dword ptr [ECX]"
    },
    {
      "address": "00e57396",
      "instruction": "JGE 0x00e57390"
    },
    {
      "address": "00e57398",
      "instruction": "LEA ECX,[ESI*0x8 + 0x0]"
    },
    {
      "address": "00e5739f",
      "instruction": "SUB ECX,ESI"
    },
    {
      "address": "00e573a1",
      "instruction": "LEA ECX,[ECX*0x4 + 0x1483c14]"
    },
    {
      "address": "00e573a8",
      "instruction": "SUB EAX,dword ptr [ECX]"
    },
    {
      "address": "00e573aa",
      "instruction": "MOV dword ptr [ESP + 0x8],0x4"
    },
    {
      "address": "00e573b2",
      "instruction": "ADD EAX,0x2"
    },
    {
      "address": "00e573b5",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00e573b9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e573bb",
      "instruction": "MOV dword ptr [ESP + 0x4],0x0"
    },
    {
      "address": "00e573c3",
      "instruction": "POP ESI"
    },
    {
      "address": "00e573c4",
      "instruction": "LEA EAX,[ESP + 0xc]"
    },
    {
      "address": "00e573c8",
      "instruction": "JG 0x00e573cd"
    },
    {
      "address": "00e573ca",
      "instruction": "LEA EAX,[ESP]"
    },
    {
      "address": "00e573cd",
      "instruction": "CMP dword ptr [EAX],0x4"
    },
    {
      "address": "00e573d0",
      "instruction": "JLE 0x00e573d6"
    },
    {
      "address": "00e573d2",
      "instruction": "LEA EAX,[ESP + 0x4]"
    },
    {
      "address": "00e573d6",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00e573d8",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e573db",
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
  "original_bytes": 10956,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-cell\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"Simulator::Cell::ShouldNotAttack\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e57460\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e57ce0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e57fd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e582c0\"\n      },\n      {\n        \"name\": \"Simulator::Cell::GetDamageAmount\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e58980\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e59e50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e5add0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e5c460\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e5d580\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e660e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e67890\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e68470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e68630\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e6a250\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e6a3f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e6b370\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e73f60\"\n      },\n      {\n        \"name\": \"FUN_00e7a4a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e7a4a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7b0a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7c8c0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e574d0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e57460\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e57ce6\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e57ce0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e580e4\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e57fd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e58562\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e582c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5899e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e58980\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e589e1\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e58980\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e58a92\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e58980\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e58a9b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e58980\",\n        \"reference_type\": \"direct-call\"\n      
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
  "body_end": "00e573db",
  "body_span_bytes": 156,
  "body_start": "00e57340",
  "callees": [
    "FUN_00e4ee60"
  ],
  "callers": [
    "FUN_00e5add0",
    "Simulator::Cell::ShouldNotAttack",
    "FUN_00e6a250",
    "FUN_00e73f60",
    "FUN_00e5c460",
    "Simulator::Cell::GetDamageAmount",
    "FUN_00e582c0",
    "FUN_00e57fd0",
    "FUN_00e68470",
    "FUN_00e7c8c0",
    "FUN_00e6b370",
    "FUN_00e57ce0",
    "FUN_00e59e50",
    "FUN_00e7b0a0",
    "FUN_00e68630",
    "FUN_00e660e0",
    "FUN_00e7a4a0",
    "FUN_00e67890",
    "FUN_00e6a3f0",
    "FUN_00e5d580"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e57340",
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
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "Simulator::Cell::GetScaleDifferenceWithPlayer",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "otherCell",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCellObjectData *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "ScaleDifference",
  "return_type_resolved": true,
  "rva": "0xa57340",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "ScaleDifference Simulator::Cell::GetScaleDifferenceWithPlayer(cCellObjectData * otherCell)",
  "size_bytes": 156,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e57340",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 32,
  "xrefs": [
    {
      "from": "00e580e4"
    },
    {
      "from": "00e5899e"
    },
    {
      "from": "00e589e1"
    },
    {
      "from": "00e58a92"
    },
    {
      "from": "00e58a9b"
    },
    {
      "from": "00e5ae0a"
    },
    {
      "from": "00e6a5c9"
    },
    {
      "from": "00e6a814"
    },
    {
      "from": "00e6ab3a"
    },
    {
      "from": "00e6ab95"
    },
    {
      "from": "00e59e6d"
    },
    {
      "from": "00e6a293"
    },
    {
      "from": "00e574d0"
    },
    {
      "from": "00e68661"
    },
    {
      "from": "00e68521"
    },
    {
      "from": "00e6856e"
    },
    {
      "from": "00e5c484"
    },
    {
      "from": "00e74688"
    },
    {
      "from": "00e748a1"
    },
    {
      "from": "00e660f3"
    },
    {
      "from": "00e66105"
    },
    {
      "from": "00e6789a"
    },
    {
      "from": "00e7a519"
    },
    {
      "from": "00e7a544"
    },
    {
      "from": "00e7ca8d"
    },
    {
      "from": "00e7cac6"
    },
    {
      "from": "00e6b3eb"
    },
    {
      "from": "00e58562"
    },
    {
      "from": "00e5d593"
    },
    {
      "from": "00e7b0f1"
    },
    {
      "from": "00e57ce6"
    },
    {
      "from": "00e7b2d6"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetScaleDifferenceWithPlayer.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetScaleDifferenceWithPlayer.c"
  ],
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
  "status": "implemented"
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
[
  {
    "anchors": [
      "0x00e74a20",
      "0x00e57460",
      "0x00e6d200",
      "0x00e57340",
      "0x00e780a0",
      "0x00000108",
      "0x00e74a20",
      "0x00000108"
    ],
    "conflict_id": "TB-FL-012",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "separate_entities",
      "preferred_claim": "Use the original direct field/body evidence as the ABI anchor.",
      "preserved_alternatives": true,
      "scope_note": "The current padding is a replacement limitation and cannot define the original structure.",
      "status": "preferred_claim_with_limit",
      "taxonomy": "preferred_claim_with_limit"
    },
    "resolution_status": "preferred_claim_with_limit",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "cCellObjectData original middle fields versus current opaque padding",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
  }
]
```
