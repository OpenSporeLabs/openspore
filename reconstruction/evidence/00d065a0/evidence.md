# Evidence 0x00d065a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1fe4a44d7e57cb1b94c9deb5fb5a7a945d3da9397c804f0980b85bba75b8d433`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueRelationshipManager*",
  "receiver": "result of 0x0067cb30",
  "receiver_register": "ECX",
  "return_type": "void",
  "stack_arguments": [
    "selector 0xC09EDAAC",
    "object"
  ],
  "stack_cleanup_bytes": 8,
  "termination": "RET 0x8"
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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
    "flow_not_modelled: the linear ESP walk ends at +164, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "81d36298f1acd9af077c336269dee633a6af3d73018d1550d511f8cefe65fbe3",
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
        "obs-0059"
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
        "obs-0009",
        "obs-0011"
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
        "obs-0001",
        "obs-0006",
        "obs-0014",
        "obs-0030",
        "obs-0035",
        "obs-0046",
        "obs-0047",
        "obs-0058"
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
        "obs-0001",
        "obs-0006",
        "obs-0014",
        "obs-0030",
        "obs-0035",
        "obs-0046",
        "obs-0047",
        "obs-0058"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0059"
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
        "obs-0004"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00d065a0",
      "count": 4,
      "first_use": 0,
      "first_write_index": 12,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00d065a1",
      "count": 14,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00d065a2",
      "count": 8,
      "first_use": 2,
      "first_write_index": 6,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00d065a2",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0004",
      "index": 2,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x00d065a3",
      "count": 15,
      "first_use": 3,
      "first_write_index"
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0060d860"
  },
  {
    "name": "FUN_00b3d300",
    "reconstructed": true,
    "va": "0x00b3d300"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c30c80"
  },
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
    "va": "0x00fe9580"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x010134d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01023be0"
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
  },
  {
    "anchors": [
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270",
      "0x00d06270",
      "0x00d065a0",
      "0x00d065a0",
      "0x00d06920",
      "0x00d06920",
      "0x00596da0"
    ],
    "conflict_id": "U-E001",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00be2590",
      "0x00be2590",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270",
      "0x00d06270",
      "0x00d065a0",
      "0x00d065a0",
      "0x00d06920",
      "0x00d06920"
    ],
    "conflict_id": "U-E002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270",
      "0x00d06270",
      "0x00d065a0",
      "0x00d065a0",
      "0x00d06920",
      "0x00d06920",
      "0x01037d30",
      "0x010535e0",
      "0x010535f0"
    ],
    "conflict_id": "U-E003",
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
  "count": 136,
  "instructions": [
    {
      "address": "00d065a0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d065a1",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00d065a2",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00d065a3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d065a4",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00d065a6",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00d065ab",
      "instruction": "MOV EBP,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00d065af",
      "instruction": "MOV ESI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00d065b3",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "00d065b5",
      "instruction": "CMOVZ EBP,EAX"
    },
    {
      "address": "00d065b8",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00d065b9",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d065ba",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d065bc",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "00d065c0",
      "instruction": "CALL 0x00d01f50"
    },
    {
      "address": "00d065c5",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00d065c7",
      "instruction": "JNZ 0x00d066fb"
    },
    {
      "address": "00d065cd",
      "instruction": "MOV ESI,dword ptr [ESI + 0x84]"
    },
    {
      "address": "00d065d3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d065d4",
      "instruction": "MOV EDI,dword ptr [EBP + 0x84]"
    },
    {
      "address": "00d065da",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d065db",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d065dc",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d065dd",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d065de",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d065e0",
      "instruction": "CALL 0x00d01ab0"
    },
    {
      "address": "00d065e5",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d065e6",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d065e8",
      "instruction": "CALL 0x00d01410"
    },
    {
      "address": "00d065ed",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00d065ef",
      "instruction": "JZ 0x00d065f5"
    },
    {
      "address": "00d065f1",
      "instruction": "OR dword ptr [EAX + 0x4],0x1"
    },
    {
      "address": "00d065f5",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d065f6",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d065f7",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d065f8",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d065f9",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d065fb",
      "instruction": "CALL 0x00d01ab0"
    },
    {
      "address": "00d06600",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d06601",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d06603",
      "instruction": "CALL 0x00d01410"
    },
    {
      "address": "00d06608",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00d0660a",
      "instruction": "JZ 0x00d06610"
    },
    {
      "address": "00d0660c",
      "instruction": "AND dword ptr [EAX + 0x4],0xfffffffd"
    },
    {
      "address": "00d06610",
      "instruction": "CMP EBP,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00d06614",
      "instruction": "JZ 0x00d0664c"
    },
    {
      "address": "00d06616",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d06617",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d06618",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d06619",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d0661a",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d0661c",
      "instruction": "CALL 0x00d01ab0"
    },
    {
      "address": "00d06621",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d06622",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d06624",
      "instruction": "CALL 0x00d01410"
    },
    {
      "address": "00d06629",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00d0662b",
      "instruction": "JZ 0x00d06631"
    },
    {
      "address": "00d0662d",
      "instruction": "OR dword ptr [EAX + 0x4],0x1"
    },
    {
      "address": "00d06631",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d06632",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d06633",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d06634",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d06635",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d06637",
      "instruction": "CALL 0x00d01ab0"
    },
    {
      "address": "00d0663c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d0663d",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d0663f",
      "instruction": "CALL 0x00d01410"
    },
    {
      "address": "00d06644",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00d06646",
      "instruction": "JZ 0x00d0664c"
    },
    {
      "address": "00d06648",
      "instruction": "AND dword ptr [EAX + 0x4],0xfffffffd"
    },
    {
      "address": "00d0664c",
      "instruction": "MOV ECX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00d06650",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00d06651",
      "instruction": "CALL 0x00c345f0"
    },
    {
      "address": "00d06656",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00d0665a",
      "instruc
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
  "original_bytes": 12557,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueRelationshipManager*\",\n    \"receiver\": \"result of 0x0067cb30\",\n    \"receiver_register\": \"ECX\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      \"selector 0xC09EDAAC\",\n      \"object\"\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DiplomacyTransitionPorts,OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipManager*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 30,\n      \"symbol\": \"DiplomacyTransition_00d01e30\",\n      \"va\": \"0x00d01e30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DiplomacyTransitionPorts,OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipManager*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 30,\n      \"symbol\": \"DiplomacyTransition_00d038e0\",\n      \"va\": \"0x00d038e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DiplomacyTransitionPorts,OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipManager*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 30,\n      \"symbol\": \"DiplomacyTransition_00d06920\",\n      \"va\": \"0x00d06920\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PRIMITIVES\",\n      \"score\": 16,\n      \"symbol\": \"RelationshipMapSelect_00d01ab0\",\n      \"va\": \"0x00d01ab0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipManager,OpaqueRelationshipMap\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PREDICATE\",\n      \"score\": 16,\n      \"symbol\": \"RelationshipManager_IsAllied2_00d01ff0\",\n      \"va\": \"0x00d01ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueRelationshipEntry,OpaqueRelationshipMap\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PRIMITIVES\",\n      \"score\": 9,\n      \"symbol\": \"RelationshipLookup_00d01410\",\n      \"va\": \"0x00d01410\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 3,\n      \"symbol\": \"pkg12_space_01021300\",\n      \"va\": \"0x01021300\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"All event, relationship, array, and service ports remain opaque.\",\n    \"No original-process trace is available.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueRelationshipManager\",\n  \"cluster\": null,\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0060d860\"\n      },\n      {\n        \"name\": \"FUN_00b3d300\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d300\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c30c80\"\n      },\n      {\n        \"name\": \"RelationshipLookup_00d01410\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d01410\"\n      },\n      {\n        \"name\": \"RelationshipMapSelect_00d01ab0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d01ab0\"\n      },\n      {\n        \"name\": \"pkg12_space_01021300\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021300\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe9580\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010134d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01023be0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00fe9b2d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fe9580\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fea211\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fe9580\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01013622\",\n        \"direction\": \"in\",\n        \"other\": \"0x010134d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01023f73\",\n        \"direction\": \"in\",\n        \"other\": \"0x01023be0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d066d5\",\n        \"direction\": \"out\",\n        \"other\": \"0x0060d860\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d066ce\",\
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
  "body_end": "00d06701",
  "body_span_bytes": 354,
  "body_start": "00d065a0",
  "callees": [
    "FUN_00c7bd40",
    "FUN_0067cb30",
    "FUN_00d01410",
    "FUN_01021300",
    "FUN_00c31c50",
    "FUN_00b3d300",
    "FUN_00d05d90",
    "FUN_00c30c80",
    "FUN_00c345f0",
    "FUN_00d01ab0",
    "FUN_00f67d90",
    "FUN_0060d860",
    "FUN_00d01f50"
  ],
  "callers": [
    "FUN_010134d0",
    "FUN_00fe9580",
    "FUN_01023be0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d065a0",
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
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00d065a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x9065a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00d065a0(void)",
  "size_bytes": 354,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d065a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00fe9b2d"
    },
    {
      "from": "00fea211"
    },
    {
      "from": "01013622"
    },
    {
      "from": "01023f73"
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
  "file": "src/reconstruction/pkg13_diplomacy_transitions/diplomacy_transitions.cpp",
  "files": [
    "reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions.cpp",
    "reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions.hpp",
    "reconstruction/staging/pkg13-diplomacy-transitions/diplomacy_transitions_model_test.cpp",
    "src/reconstruction/pkg13_diplomacy_transitions/diplomacy_transitions.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave5/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-diplomacy-transitions/00d065a0.json"
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
    "gate-diplomacy-transition-00d065a0"
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
  "DiplomacyTransitionPorts",
  "OpaqueRelationshipEntry",
  "OpaqueRelationshipManager",
  "OpaqueRelationshipManager*",
  "OpaqueRelationshipMap",
  "OpaqueTransitionRecord",
  "OpaqueTransitionRecord*",
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
  },
  {
    "anchors": [
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270",
      "0x00d06270",
      "0x00d065a0",
      "0x00d065a0",
      "0x00d06920",
      "0x00d06920",
      "0x00596da0"
    ],
    "conflict_id": "U-E001",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00be2590",
      "0x00be2590",
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270",
      "0x00d06270",
      "0x00d065a0",
      "0x00d065a0",
      "0x00d06920",
      "0x00d06920"
    ],
    "conflict_id": "U-E002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00d01e30",
      "0x00d01e30",
      "0x00d038e0",
      "0x00d038e0",
      "0x00d05830",
      "0x00d05830",
      "0x00d06270",
      "0x00d06270",
      "0x00d065a0",
      "0x00d065a0",
      "0x00d06920",
      "0x00d06920",
      "0x01037d30",
      "0x010535e0",
      "0x010535f0"
    ],
    "conflict_id": "U-E003",
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
