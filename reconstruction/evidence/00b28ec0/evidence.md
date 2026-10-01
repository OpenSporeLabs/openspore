# Evidence 0x00b28ec0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `3369fb8027ec0ee8b4b154cd76d0eff0153d80a99e8e52ab503a6692f9252e7d`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "opaque receiver pointer",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+4",
      "name": "wide_path",
      "type": "const char16_t*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+8",
      "name": "candidate_marker",
      "observed_access_at_gates": "ESP+0x120 after the 0x110-byte entry ESP adjustment",
      "observed_use": "nonzero value gates both the candidate-target and completion sequences",
      "type": "uint32_t",
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
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
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
    "flow_not_modelled: the linear ESP walk ends at +144, so the listing is not one path",
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
  "content_sha256": "5f3013fa4bae1a15b0e59310b955927be46d1b67694a8983c2d33db40b6ed3e8",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 16,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0220"
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
        "obs-0006"
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
        "obs-0019",
        "obs-0026",
        "obs-0041",
        "obs-0043",
        "obs-0048",
        "obs-0050",
        "obs-0052",
        "obs-0054",
        "obs-0059",
        "obs-0061",
        "obs-0063",
        "obs-0065",
        "obs-0070",
        "obs-0072",
        "obs-0074",
        "obs-0076",
        "obs-0080",
        "obs-0091",
        "obs-0123",
        "obs-0130",
        "obs-0132",
        "obs-0133",
        "obs-0140",
        "obs-0145",
        "obs-0152",
        "obs-0155",
        "obs-0157",
        "obs-0166",
        "obs-0168",
        "obs-0171",
        "obs-0174",
        "obs-0176",
        "obs-0182",
        "obs-0184",
        "obs-0189",
        "obs-0199",
        "obs-0206",
        "obs-0207",
        "obs-0210",
        "obs-0214"
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
        "obs-0019",
        "obs-0026",
        "obs-0041",
        "obs-0043",
        "obs-0048",
        "obs-0050",
        "obs-0052",
        "obs-0054",
        "obs-0059",
        "obs-0061",
        "obs-0063",
        "obs-0065",
        "obs-0070",
        "obs-0072",
        "obs-0074",
        "obs-0076",
        "obs-0080",
        "obs-0091",
        "obs-0123",
        "obs-0130",
        "obs-0132",
        "obs-0133",
        "obs-0140",
        "obs-0145",
        "obs-0152",
        "obs-0155",
        "obs-0157",
        "obs-0166",
        "obs-0168",
        "obs-0171",
        "obs-0174",
        "obs-0176",
        "obs-0182",
        "obs-0184",
        "obs-0189",
        "obs-0199",
        "obs-0206",
        "obs-0207",
        "obs-0210",
        "obs-0214"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0220"
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
        "obs-0106"
      ],
      "claim": "a bulk string write reaches the return register, which is not a struct-return signature",
      "confidence": "INFERRED",
      "id": "RT4",
      "value": {
        "bulk_write": true
      }
    },
    {
      "based_on": [
        "obs-0220"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0220"
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
      "id": "obs-0001"
    },
    {
      "id": "obs-0002"
    },
    {
      "id": "obs-0003"
    
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_004df420",
    "reconstructed": false,
    "va": "0x004df420"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00688fa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006891f0"
  },
  {
    "name": "FUN_00b3d230",
    "reconstructed": false,
    "va": "0x00b3d230"
  },
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
  },
  {
    "name": "FUN_00b3d300",
    "reconstructed": true,
    "va": "0x00b3d300"
  },
  {
    "name": "simulator_game_input_manager_get_00b3d350",
    "reconstructed": true,
    "va": "0x00b3d350"
  },
  {
    "name": "FUN_00b5b800",
    "reconstructed": false,
    "va": "0x00b5b800"
  },
  {
    "name": "FUN_00b7e380",
    "reconstructed": false,
    "va": "0x00b7e380"
  },
  {
    "name": "FUN_01021080",
    "reconstructed": true,
    "va": "0x01021080"
  },
  {
    "name": "FUN_01021230",
    "reconstructed": true,
    "va": "0x01021230"
  },
  {
    "name": "pkg12_space_01021300",
    "reconstructed": true,
    "va": "0x01021300"
  },
  {
    "name": "FUN_01021370",
    "reconstructed": false,
    "va": "0x01021370"
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
    "va": "0x00b294c0"
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
      "0x000051e0",
      "0x00e20860",
      "0x00e20860",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9c90",
      "0x00aeb3e0",
      "0x00b28ec0",
      "0x00b33130",
      "0x00b35300",
      "0x00b444c0",
      "0x00b4a720",
      "0x00de4c20",
      "0x00df5ac0",
      "0x01001360"
    ],
    "conflict_id": "cell_update_state_machine",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00b28ec0",
      "0x00b294c0",
      "0x00bb4ba0",
      "0x00bb4ba0",
      "0x00693900",
      "0x00693900",
      "0x00693900",
      "0x00693900",
      "0x00693d60",
      "0x00693d60",
      "0x00693d60",
      "0x00693d60",
      "0x006a1540",
      "0x006a2f60",
      "0x006a1540",
      "0x006a2f60"
    ],
    "conflict_id": "cross_file_atomicity",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "stars.db.tmp write and replacement are concrete. No transaction boundary is claimed for the full .spo/profile set.",
    "resolution_status": "stars.db.tmp write and replacement are concrete. No transaction boundary is claimed for the full .spo/profile set.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bb4ba0",
      "0x00bb4ba0",
      "0x013c7d90",
      "0x013c7d90",
      "0x00693900",
      "0x00693900",
      "0x00693d60",
      "0x00693d60",
      "0x007d8d40",
      "0x007d8d40",
      "0x00b28ec0",
      "0x00b28ec0",
      "0x00b294c0",
      "0x00b294c0",
      "0x00b335d0",
      "0x00b335d0"
    ],
    "conflict_id": "field_coverage_and_migration",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00b28ec0",
      "0x00b294c0",
      "0x00b3d440",
      "0x00b28ec0",
      "0x00675d70",
      "0x00675d70",
      "0x00676710",
      "0x00676660",
      "0x00676710",
      "0x00676660",
      "0x00676c80",
      "0x00676c80",
      "0x00677140",
      "0x00677140",
      "0x00693900",
      "0x00693900"
    ],
    "conflict_id": "persistence_manager_vtable",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e20860",
      "0x01001360",
      "0x01021960",
      "0x00e20860",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9c90",
      "0x00aeb3e0",
      "0x00b28ec0",
      "0x00b33130",
      "0x00b35300",
      "0x00b444c0",
      "0x00b4a720",
      "0x00de4c20",
      "0x00df5ac0"
    ],
    "conflict_id": "space_context_mode_2_effects",
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
      "0x00692900",
      "0x00b28ec0",
      "0x00b294c0",
      "0x00692900",
      "0x00692880",
      "0x00692880",
      "0x00692900",
      "0x00692900",
      "0x00692ea0",
      "0x00692ea0",
      "0x00692ec0",
      "0x00692ec0",
      "0x00692f90",
      "0x00692f90",
      "0x00693900",
      "0x00693900"
    ],
    "conflict_id": "spo_container_framing",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
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
  "count": 403,
  "instructions": [
    {
      "address": "00b28ec0",
      "instruction": "SUB ESP,0x108"
    },
    {
      "address": "00b28ec6",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b28ec7",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00b28ec8",
      "instruction": "MOV EBP,dword ptr [ESP + 0x114]"
    },
    {
      "address": "00b28ecf",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00b28ed1",
      "instruction": "MOV dword ptr [ESP + 0x4c],ECX"
    },
    {
      "address": "00b28ed5",
      "instruction": "CMP EBP,EBX"
    },
    {
      "address": "00b28ed7",
      "instruction": "JZ 0x00b2949d"
    },
    {
      "address": "00b28edd",
      "instruction": "MOV EAX,EBP"
    },
    {
      "address": "00b28edf",
      "instruction": "LEA EDX,[EAX + 0x2]"
    },
    {
      "address": "00b28ee2",
      "instruction": "MOV CX,word ptr [EAX]"
    },
    {
      "address": "00b28ee5",
      "instruction": "ADD EAX,0x2"
    },
    {
      "address": "00b28ee8",
      "instruction": "CMP CX,BX"
    },
    {
      "address": "00b28eeb",
      "instruction": "JNZ 0x00b28ee2"
    },
    {
      "address": "00b28eed",
      "instruction": "SUB EAX,EDX"
    },
    {
      "address": "00b28eef",
      "instruction": "SAR EAX,0x1"
    },
    {
      "address": "00b28ef1",
      "instruction": "JZ 0x00b2949d"
    },
    {
      "address": "00b28ef7",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b28ef8",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b28ef9",
      "instruction": "MOV dword ptr [ESP + 0x108],EBX"
    },
    {
      "address": "00b28f00",
      "instruction": "MOV dword ptr [ESP + 0xd8],0x13eb90c"
    },
    {
      "address": "00b28f0b",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00b28f0d",
      "instruction": "LEA ECX,[ESP + 0xdc]"
    },
    {
      "address": "00b28f14",
      "instruction": "XCHG dword ptr [ECX],EAX"
    },
    {
      "address": "00b28f16",
      "instruction": "MOV EDI,0x1"
    },
    {
      "address": "00b28f1b",
      "instruction": "MOV dword ptr [ESP + 0xd8],0x13eb844"
    },
    {
      "address": "00b28f26",
      "instruction": "MOV dword ptr [ESP + 0x110],EBX"
    },
    {
      "address": "00b28f2d",
      "instruction": "MOV dword ptr [ESP + 0xe0],EDI"
    },
    {
      "address": "00b28f34",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "00b28f39",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00b28f3b",
      "instruction": "MOV EDX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00b28f3e",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b28f3f",
      "instruction": "LEA ECX,[ESP + 0xdc]"
    },
    {
      "address": "00b28f46",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00b28f47",
      "instruction": "PUSH 0x1a0219e"
    },
    {
      "address": "00b28f4c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b28f4e",
      "instruction": "CALL EDX"
    },
    {
      "address": "00b28f50",
      "instruction": "CALL 0x00401090"
    },
    {
      "address": "00b28f55",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b28f57",
      "instruction": "CALL 0x004df420"
    },
    {
      "address": "00b28f5c",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00b28f5e",
      "instruction": "CMP byte ptr [ESP + 0x120],BL"
    },
    {
      "address": "00b28f65",
      "instruction": "JZ 0x00b290e7"
    },
    {
      "address": "00b28f6b",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00b28f70",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b28f72",
      "instruction": "JZ 0x00b290e7"
    },
    {
      "address": "00b28f78",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00b28f7c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b28f7d",
      "instruction": "MOV dword ptr [ESP + 0x14],EBX"
    },
    {
      "address": "00b28f81",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00b28f86",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b28f88",
      "instruction": "CALL 0x00c30c60"
    },
    {
      "address": "00b28f8d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b28f8e",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00b28f93",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b28f95",
      "instruction": "CALL 0x00bb3750"
    },
    {
      "address": "00b28f9a",
      "instruction": "CMP dword ptr [ESP + 0x10],EBX"
    },
    {
      "address": "00b28f9e",
      "instruction": "JNZ 0x00b28faf"
    },
    {
      "address": "00b28fa0",
      "instruction": "CALL 0x01021230"
    },
    {
      "address": "00b28fa5",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b28fa6",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00b28faa",
      "instruction": "CALL 0x00b5f950"
    },
    {
      "address": "00b28faf",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "00b28fb1",
      "instruction": "JZ 0x00b28fbd"
    },
    {
      "address": "00b28fb3",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00b28fb7",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b28fb8",
      "instruction": "CALL 0x00c8b570"
    },
    {
      "address": "00b28fbd",
      "instruction": "CALL 0x01021370"
    },
    {
      "address": "00b28fc2",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00b28fc4",
      "instruction": "CALL 0x00b5b800"
    },
    {
      "address": "00b28fc9",
      "instruction": "ADD EAX,0xfe9ab400"
    },
    {
      "address": "00b28fce",
      "instruction": "CMP EAX,0x5"
    },
    {
      "address": "00b28fd1",
      "instructi
[TRUNCATED]
```

## external_callees

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "EXT:MSVCR90.DLL::_localtime64",
  "EXT:MSVCR90.DLL::_time64"
]
```

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 21519,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"opaque receiver pointer\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+4\",\n        \"name\": \"wide_path\",\n        \"type\": \"const char16_t*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+8\",\n        \"name\": \"candidate_marker\",\n        \"observed_access_at_gates\": \"ESP+0x120 after the 0x110-byte entry ESP adjustment\",\n        \"observed_use\": \"nonzero value gates both the candidate-target and completion sequences\",\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-PERSISTENCE-BOUNDARY\",\n      \"score\": 10,\n      \"symbol\": \"PaintPersistenceBoundary_submit_004c5200\",\n      \"va\": \"0x004c5200\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"simulator_game_input_manager_get_00b3d350\",\n      \"va\": \"0x00b3d350\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:opaque receiver pointer\"\n      ],\n      \"package\": \"PKG-WAVE6-MISC-ENGINE\",\n      \"score\": 3,\n      \"symbol\": \"destructible_lifecycle_thunk_00b63980\",\n      \"va\": \"0x00b63980\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_01021080\",\n      \"va\": \"0x01021080\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_01021230\",\n      \"va\": \"0x01021230\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 3,\n      \"symbol\": \"pkg12_space_01021300\",\n      \"va\": \"0x01021300\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"runtime_gated\",\n  \"class_type\": \"ProfilePersistenceBoundary\",\n  \"cluster\": null,\n  \"confidence\": 0.86,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_004df420\",\n        \"reconstructed\": false,\n        \"va\": \"0x004df420\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00688fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006891f0\"\n      },\n      {\n        \"name\": \"FUN_00b3d230\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b3d230\"\n      },\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      },\n      {\n        \"name\": \"FUN_00b3d300\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d300\"\n      },\n      {\n        \"name\": \"simulator_game_input_manager_get_00b3d350\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d350\"\n      },\n      {\n        \"name\": \"FUN_00b5b800\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b5b800\"\n      },\n      {\n        \"name\": \"FUN_00b7e380\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b7e380\"\n      },\n      {\n        \"name\": \"FUN_01021080\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021080\"\n      },\n      {\n        \"name\": \"FUN_01021230\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021230\"\n      },\n      {\n        \"name\": \"pkg12_space_01021300\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021300\"\n      },\n      {\n        \"name\": \"FUN_01021370\",\n        \"reconstructed\": false,\n        \"va\": \"0x01021370\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b294c0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b297b4\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b294c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b28f50\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401090\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b29498\",\n        \"direction\": \"out\",\n        \"other\": \"0x00421cf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b292bd\",\n        \"direction\": \"out\",\n        \"other\": \"0x00423650\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b28f57\",\n        \"direction\": \"out\",\n        \"other\": \"0x004df420\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b29271\",\n        \"direction\": \"out\",\
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
  "body_end": "00b294a7",
  "body_span_bytes": 1512,
  "body_start": "00b28ec0",
  "callees": [
    "FUN_00ae9790",
    "FUN_00b268a0",
    "FUN_00bb3750",
    "FUN_00b5b800",
    "FUN_00692ea0",
    "FUN_01021080",
    "FUN_00f47380",
    "FUN_00b3d2a0",
    "FUN_00bb66f0",
    "FUN_00b3d230",
    "FUN_00c8b570",
    "FUN_00baecc0",
    "FUN_00693d60",
    "FUN_00675250",
    "FUN_009a9600",
    "FUN_00c8b590",
    "FUN_00b28da0",
    "FUN_00693900",
    "Simulator::cGameInputManager::Get",
    "_localtime64",
    "FUN_006891f0",
    "FUN_00b7e380",
    "FUN_00688f00",
    "FUN_00bb4ba0",
    "FUN_00b211e0",
    "FUN_00e5c4d0",
    "FUN_00688fa0",
    "_time64",
    "Editors::cSpeciesManager::Get",
    "FUN_00bb59b0",
    "FUN_006755c0",
    "FUN_00b5f950",
    "FUN_00421cf0",
    "FUN_01021370",
    "FUN_00c30c60",
    "FUN_01021230",
    "FUN_01021300",
    "FUN_004df420",
    "FUN_00579a90",
    "App::IAppSystem::Get",
    "FUN_00423650",
    "FUN_00b3d300"
  ],
  "callers": [
    "FUN_00b294c0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b28ec0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    },
    {
      "name": "local_3c",
      "storage": "Stack[-0x3c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_40",
      "storage": "Stack[-0x40]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c4",
      "storage": "Stack[-0xc4]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "FUN_00b28ec0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x728ec0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b28ec0(void)",
  "size_bytes": 1512,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b28ec0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00b297b4"
    },
    {
      "from": "00b29c64"
    },
    {
      "from": "00b2a009"
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
  "file": "src/reconstruction/pkg20_persistence_boundary/persistence_boundary.cpp",
  "files": [
    "src/reconstruction/pkg20_persistence_boundary/persistence_boundary.cpp",
    "src/reconstruction/pkg20_persistence_boundary/persistence_boundary.hpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-persistence-boundary/00b28ec0.json"
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
    "gate-profile-persistence-candidate"
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
  "original_bytes": 8797,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"STRUCTURAL_ONLY\",\n  \"confidence\": {\n    \"events\": \"UNRESOLVED\",\n    \"identity\": \"INFERRED\",\n    \"mechanics\": \"CONFIRMED\",\n    \"overall\": \"high_for_static_mechanics_medium_for_operation_identity\",\n    \"ownership\": \"INFERRED_NOT_CONFIRMED\",\n    \"persistence\": \"SUPPORTED\",\n    \"runtime\": \"UNAVAILABLE\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 43,\n  \"evidence\": [\n    {\n      \"claim\": \"path validation, header-shaped local record, temporary path, serializer/database calls, stream close, replacement, and conditional star database branch\",\n      \"class\": \"direct_body\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b28ec0\"\n    },\n    {\n      \"claim\": \"profile/load wrapper calls the target after path/mode setup; it passes a second context argument\",\n      \"class\": \"direct_caller\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b294c0 at 0x00b297b4\"\n    },\n    {\n      \"claim\": \"matching load path uses the same database/ClassSerializer architecture and closes the read context\",\n      \"class\": \"sibling_body\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b279e0\"\n    },\n    {\n      \"claim\": \"header descriptor setup followed by the common write serializer\",\n      \"class\": \"serializer_wrapper\",\n      \"source\": \"ghidra://SporeApp.exe@0x00b268a0\"\n    },\n    {\n      \"claim\": \"old/temp path construction, move/copy, and removal behavior\",\n      \"class\": \"replacement_sibling\",\n      \"source\": \"ghidra://SporeApp.exe@0x006891f0\"\n    },\n    {\n      \"claim\": \"separate stars.db.tmp to stars.db write and replacement\",\n      \"class\": \"star_database_sibling\",\n      \"source\": \"ghidra://SporeApp.exe@0x00bb4ba0\"\n    },\n    {\n      \"claim\": \"preserves bounded save-candidate role, manager-membership caveat, temp/replace, and unresolved outer envelope\",\n      \"class\": \"committed_artifact\",\n      \"source\": \"knowledgegraph/research/architecture-resolution/followup-06-persistence.json\"\n    }\n  ],\n  \"family\": \"save-profile-transaction-orchestration\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": [\n      {\n        \"name\": \"FUN_00675250\",\n        \"va\": \"0x00675250\"\n      },\n      {\n        \"name\": \"FUN_00baecc0\",\n        \"va\": \"0x00baecc0\"\n      },\n      {\n        \"name\": \"FUN_00b268a0\",\n        \"va\": \"0x00b268a0\"\n      },\n      {\n        \"name\": \"FUN_00bb66f0\",\n        \"va\": \"0x00bb66f0\"\n      },\n      {\n        \"name\": \"FUN_00693d60\",\n        \"va\": \"0x00693d60\"\n      },\n      {\n        \"name\": \"FUN_00b5b800\",\n        \"va\": \"0x00b5b800\"\n      },\n      {\n        \"name\": \"FUN_00b211e0\",\n        \"va\": \"0x00b211e0\"\n      },\n      {\n        \"name\": \"FUN_01021080\",\n        \"va\": \"0x01021080\"\n      },\n      {\n        \"name\": \"FUN_01021230\",\n        \"va\": \"0x01021230\"\n      },\n      {\n        \"name\": \"Editors::cSpeciesManager::Get\",\n        \"va\": \"0x00401090\"\n      },\n      {\n        \"name\": \"Simulator::cGameInputManager::Get\",\n        \"va\": \"0x00b3d350\"\n      },\n      {\n        \"name\": \"FUN_00c30c60\",\n        \"va\": \"0x00c30c60\"\n      }\n    ],\n    \"direct_callers\": [\n      {\n        \"callsites\": [\n          \"0x00b297b4\"\n        ],\n        \"name\": \"FUN_00b294c0\",\n        \"reference_type\": \"UNCONDITIONAL_CALL\",\n        \"va\": \"0x00b294c0\"\n      }\n    ],\n    \"globals\": [],\n    \"structures\": [],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": [\n        \"null or empty path is a no-op with no reported status\",\n        \"several allocation, path, and service branches bypass or short-circuit work; the body uses local cleanup and does not expose a uniform error code\",\n        \"serializer or stream failure may leave the bounded temp/old/recovery path to handle recovery; universal rollback is not proven\",\n        \"the function does not provide a caller-visible success boolean\"\n      ],\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [],\n      \"ordering\": [\n        \"validate and normalize path\",\n        \"initialize application/service context\",\n        \"select mode-specific initialization\",\n        \"derive target and .tmp paths\",\n        \"open write database/stream context\",\n        \"serialize header and optional state records\",\n        \"close database/stream context\",\n        \"replace or remove old path\",\n        \"conditionally update star database\"\n      ],\n      \"outputs\": [],\n      \"postconditions\": [\n        \"For a nonempty path, a temporary path is derived and a write-oriented database/stream context is opened.\",\n        \"A header-shaped record is populated with version-like words 3 and 0x25, a nine-word local-time array, a mode marker, a snapshot-like flag, and a three-word current-planet-like value.\",\n        \"The header is sent through the bounded ClassSerializer/database path and the stream is closed before replacement is attempted.\",\n        \"The selected path is passed to the old/temporary replacement helper 0x006891f0.\",\n        \"A selected mode branch may write stars.db through 0x00bb4ba0 or the alternate star-related path through 0x00bb66f0.\"\n      ],\n      \"preconditions\": [\n        \"path is non-null\",\n        \"path contains at least one UTF-16 code unit before its terminator\",\n        \"database, serializer, and replacement helpers are available for the selected path; allocation and stream failure paths are not fully typed\"\n      ],\n      \"purpose\": \"not_reported\",\n      \"return\": {\n        \"status\": \"not_reported\"\n      },\n      \"side_effects\": [\n        \"file/database writes\",\n        \"temporary-file creation
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
  "ProfilePersistenceBoundary",
  "ProfilePersistenceCandidateServices",
  "ProfilePersistenceRequest",
  "const char16_t*",
  "opaque receiver pointer",
  "uint32_t",
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
      "0x000051e0",
      "0x00e20860",
      "0x00e20860",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9c90",
      "0x00aeb3e0",
      "0x00b28ec0",
      "0x00b33130",
      "0x00b35300",
      "0x00b444c0",
      "0x00b4a720",
      "0x00de4c20",
      "0x00df5ac0",
      "0x01001360"
    ],
    "conflict_id": "cell_update_state_machine",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00b28ec0",
      "0x00b294c0",
      "0x00bb4ba0",
      "0x00bb4ba0",
      "0x00693900",
      "0x00693900",
      "0x00693900",
      "0x00693900",
      "0x00693d60",
      "0x00693d60",
      "0x00693d60",
      "0x00693d60",
      "0x006a1540",
      "0x006a2f60",
      "0x006a1540",
      "0x006a2f60"
    ],
    "conflict_id": "cross_file_atomicity",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "stars.db.tmp write and replacement are concrete. No transaction boundary is claimed for the full .spo/profile set.",
    "resolution_status": "stars.db.tmp write and replacement are concrete. No transaction boundary is claimed for the full .spo/profile set.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bb4ba0",
      "0x00bb4ba0",
      "0x013c7d90",
      "0x013c7d90",
      "0x00693900",
      "0x00693900",
      "0x00693d60",
      "0x00693d60",
      "0x007d8d40",
      "0x007d8d40",
      "0x00b28ec0",
      "0x00b28ec0",
      "0x00b294c0",
      "0x00b294c0",
      "0x00b335d0",
      "0x00b335d0"
    ],
    "conflict_id": "field_coverage_and_migration",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00b28ec0",
      "0x00b294c0",
      "0x00b3d440",
      "0x00b28ec0",
      "0x00675d70",
      "0x00675d70",
      "0x00676710",
      "0x00676660",
      "0x00676710",
      "0x00676660",
      "0x00676c80",
      "0x00676c80",
      "0x00677140",
      "0x00677140",
      "0x00693900",
      "0x00693900"
    ],
    "conflict_id": "persistence_manager_vtable",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e20860",
      "0x01001360",
      "0x01021960",
      "0x00e20860",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9c90",
      "0x00aeb3e0",
      "0x00b28ec0",
      "0x00b33130",
      "0x00b35300",
      "0x00b444c0",
      "0x00b4a720",
      "0x00de4c20",
      "0x00df5ac0"
    ],
    "conflict_id": "space_context_mode_2_effects",
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
   
[TRUNCATED]
```
