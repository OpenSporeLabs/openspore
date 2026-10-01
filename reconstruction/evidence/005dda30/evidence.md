# Evidence 0x005dda30

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `03a842e3746aa9e43e42ce8f279f199d0e001fe53ed46b08d662f21968a20edd`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "return_type": "void",
  "stack_arguments": [
    {
      "abi_type": "std::uint32_t",
      "entry_offset": "ESP+4",
      "name": "mode",
      "type": "std::uint32_t",
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
        "size_inferred": false,
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
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +248, so the listing is not one path"
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
  "content_sha256": "3404a3865455ce15247e7ef48bc227ad0b46d7f6d22dbbfd916a65f28211eee0",
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
    "indirect_calls": 19,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0049",
        "obs-0069"
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
        "obs-0004"
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
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          92,
          96,
          100,
          104,
          108,
          128,
          132
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0049",
        "obs-0069"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0049",
        "obs-0069"
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
        "obs-0049",
        "obs-0069"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0049",
        "obs-0069"
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
      "at": "0x005dda30",
      "count": 5,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x005dda30",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x005dda31",
      "count": 1,
      "first_use": 1,
      "first_write_index": 23,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x005dda31",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBP,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x005dda31",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,dword ptr [ESP + 0x8]",
      "reg": "EBP",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005dda35",
      "count": 35,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005dda36",
      "count": 15,
      "first_use": 3,
      "first_write_index": 6,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005dda36",
      "definite": true,
      "i
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
    "va": "0x004a88d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00574a20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00587270"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005dc310"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005dcf20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005dd610"
  },
  {
    "name": "FUN_00b1e4d0",
    "reconstructed": false,
    "va": "0x00b1e4d0"
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
    "va": "0x0057c2f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005de9e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005dec10"
  },
  {
    "name": "Editors_EditorUI_HandleMessage_005e0000",
    "reconstructed": true,
    "va": "0x005e0000"
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
      "0x00591fa0",
      "0x005dec10",
      "0x00883a90",
      "0x00883ad0",
      "0x051cc0b8",
      "0xb2e18705",
      "0x00883ad0",
      "0x00883a90",
      "0x00591fa0",
      "0x004af260",
      "0x005dda30",
      "0x00591690",
      "0x051cc0b8",
      "0x00591fa0",
      "0x005dec10",
      "0xb2e18705"
    ],
    "conflict_id": "editor_message_names_and_payloads",
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
      "0x0057ce80",
      "0x00587270",
      "0x00587270",
      "0x0057f3e0",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "editor_mode_gate",
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
      "0x005e0000",
      "0x70218642",
      "0xb006ef6e",
      "0xf006efa5",
      "0xf019c2e7",
      "0xf019c2f3",
      "0x005e0000",
      "0x004af260",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x00587270",
      "0x00587270",
      "0x00588570",
      "0x00588570",
      "0x0058ac10"
    ],
    "conflict_id": "editor_ui_command_names",
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
      "0x00586b00",
      "0x00587270",
      "0x00587a20",
      "0x00588570",
      "0x00588570",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00586b00",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "manipulator_cancel",
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
  "count": 281,
  "instructions": [
    {
      "address": "005dda30",
      "instruction": "PUSH EBP"
    },
    {
      "address": "005dda31",
      "instruction": "MOV EBP,dword ptr [ESP + 0x8]"
    },
    {
      "address": "005dda35",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005dda36",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005dda38",
      "instruction": "CMP EBP,0x2"
    },
    {
      "address": "005dda3b",
      "instruction": "JNZ 0x005dda4f"
    },
    {
      "address": "005dda3d",
      "instruction": "MOV ECX,dword ptr [ESI + 0x5c]"
    },
    {
      "address": "005dda40",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005dda42",
      "instruction": "CALL 0x00574a20"
    },
    {
      "address": "005dda47",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005dda49",
      "instruction": "JZ 0x005ddc24"
    },
    {
      "address": "005dda4f",
      "instruction": "CMP dword ptr [ESI + 0x60],EBP"
    },
    {
      "address": "005dda52",
      "instruction": "JZ 0x005ddc24"
    },
    {
      "address": "005dda58",
      "instruction": "MOV ECX,dword ptr [ESI + 0x5c]"
    },
    {
      "address": "005dda5b",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005dda5d",
      "instruction": "PUSH EBP"
    },
    {
      "address": "005dda5e",
      "instruction": "CALL 0x00587270"
    },
    {
      "address": "005dda63",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "005dda65",
      "instruction": "JZ 0x005ddc24"
    },
    {
      "address": "005dda6b",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005dda6c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005dda6d",
      "instruction": "PUSH 0x8c35f293"
    },
    {
      "address": "005dda72",
      "instruction": "CALL 0x004a88d0"
    },
    {
      "address": "005dda77",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "005dda7a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005dda7c",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005dda7e",
      "instruction": "CALL 0x005dd610"
    },
    {
      "address": "005dda83",
      "instruction": "MOV EAX,dword ptr [ESI + 0x60]"
    },
    {
      "address": "005dda86",
      "instruction": "SUB EAX,0x0"
    },
    {
      "address": "005dda89",
      "instruction": "JZ 0x005ddb36"
    },
    {
      "address": "005dda8f",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "005dda92",
      "instruction": "JZ 0x005ddb31"
    },
    {
      "address": "005dda98",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "005dda9b",
      "instruction": "JNZ 0x005ddb72"
    },
    {
      "address": "005ddaa1",
      "instruction": "MOV ECX,dword ptr [ESI + 0x64]"
    },
    {
      "address": "005ddaa4",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "005ddaa6",
      "instruction": "JZ 0x005ddab3"
    },
    {
      "address": "005ddaa8",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "005ddaaa",
      "instruction": "MOV EDX,dword ptr [EAX + 0x7c]"
    },
    {
      "address": "005ddaad",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005ddaaf",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005ddab1",
      "instruction": "CALL EDX"
    },
    {
      "address": "005ddab3",
      "instruction": "PUSH 0x578ec50"
    },
    {
      "address": "005ddab8",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005ddaba",
      "instruction": "CALL 0x005dc310"
    },
    {
      "address": "005ddabf",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005ddac1",
      "instruction": "JZ 0x005ddad0"
    },
    {
      "address": "005ddac3",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005ddac5",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005ddac7",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005ddac9",
      "instruction": "MOV EAX,dword ptr [EDX + 0x7c]"
    },
    {
      "address": "005ddacc",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005ddace",
      "instruction": "CALL EAX"
    },
    {
      "address": "005ddad0",
      "instruction": "PUSH 0xf006efa5"
    },
    {
      "address": "005ddad5",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005ddad7",
      "instruction": "CALL 0x005dc310"
    },
    {
      "address": "005ddadc",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005ddade",
      "instruction": "JZ 0x005ddaed"
    },
    {
      "address": "005ddae0",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005ddae2",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005ddae4",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005ddae6",
      "instruction": "MOV EAX,dword ptr [EDX + 0x7c]"
    },
    {
      "address": "005ddae9",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005ddaeb",
      "instruction": "CALL EAX"
    },
    {
      "address": "005ddaed",
      "instruction": "PUSH 0xb006ef6e"
    },
    {
      "address": "005ddaf2",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005ddaf4",
      "instruction": "CALL 0x005dc310"
    },
    {
      "address": "005ddaf9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005ddafb",
      "instruction": "JZ 0x005ddb0a"
    },
    {
      "address": "005ddafd",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005ddaff",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005ddb01",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005ddb03",
      "instruction": "MOV EAX,dword ptr [EDX + 0x7c]"
    },
    {
      "address": "005ddb06",
      "instruction": "PUSH 0x1"
    },
    {
      "
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
  "original_bytes": 19280,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"abi_type\": \"std::uint32_t\",\n        \"entry_offset\": \"ESP+4\",\n        \"name\": \"mode\",\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 13,\n      \"symbol\": \"Editors_EditorUI_HandleMessage_005e0000\",\n      \"va\": \"0x005e0000\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 10,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"editor_query_service_005ca960\",\n      \"va\": \"0x005ca960\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"editor_query_reset_005dd750\",\n      \"va\": \"0x005dd750\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"editor_query_clear_flags_0093db80\",\n      \"va\": \"0x0093db80\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueEditor\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-PERSISTENCE-BOUNDARY\",\n      \"score\": 5,\n      \"symbol\": \"PaintPersistenceBoundary_submit_004c5200\",\n      \"va\": \"0x004c5200\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The earlier target_selector candidate is rejected: current source and model stub use __thiscall, matching MOV ECX,[manager+0x5c]; CALL 0x00b1e4d0; concrete editor, manager results, virtual implementations, and event ordering remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"Mode semantics and vtable ownership must remain numeric/opaque.\",\n    \"The binary has no usable RTTI for assigning an original class name.\",\n    \"The package declaration intentionally uses void* for the pointer-like 0x00574a20 result; concrete owner and selector semantics remain unresolved.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueEditorModeManager\",\n  \"cluster\": null,\n  \"confidence\": 0.68,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a88d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00574a20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dc310\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dcf20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dd610\"\n      },\n      {\n        \"name\": \"FUN_00b1e4d0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b1e4d0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057c2f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005de9e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dec10\"\n      },\n      {\n        \"name\": \"Editors_EditorUI_HandleMessage_005e0000\",\n        \"reconstructed\": true,\n        \"va\": \"0x005e0000\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0057c326\",\n        \"direction\": \"in\",\n        \"other\": \"0x0057c2f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005de9e5\",\n        \"direction\": \"in\",\n        \"other\": \"0x005de9e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005ded08\",\n        \"direction\": \"in\",\n        \"other\": \"0x005dec10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005e013d\",\n        \"direction\": \"in\",\n        \"other\": \"0x005e0000\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005e015c\",\n        \"direction\": \"in\",\n        \"other\": \"0x005e0000\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005e028b\",\n        \"direction\": \"in\",\n        \"other\": \"0x005e0000\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dda72\",\n        \"direction\": \"out\",\n        \"other\": \"0x004a88d0\",\n        \"reference_type\": \"direct-
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
  "body_end": "005ddd31",
  "body_span_bytes": 770,
  "body_start": "005dda30",
  "callees": [
    "Editors::cEditor::SetActiveMode",
    "FUN_004a88d0",
    "FUN_005dd610",
    "FUN_005dc310",
    "FUN_008105b0",
    "FUN_00810590",
    "FUN_005dcf20",
    "FUN_00574a20",
    "FUN_008121b0",
    "FUN_00b1e4d0"
  ],
  "callers": [
    "FUN_005de9e0",
    "FUN_005dec10",
    "FUN_0057c2f0",
    "FUN_005e0000"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005dda30",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005dda30",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1dda30",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005dda30(void)",
  "size_bytes": 770,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005dda30",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "0057c326"
    },
    {
      "from": "005e013d"
    },
    {
      "from": "005e015c"
    },
    {
      "from": "005e028b"
    },
    {
      "from": "005ded08"
    },
    {
      "from": "005de9e5"
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
  "file": "src/reconstruction/pkg10_editor_dispatch/editor_dispatch.cpp",
  "files": [
    "src/reconstruction/pkg10_editor_dispatch/editor_dispatch.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/005dda30.json"
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
    "editor_mode_transition_observation"
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
  "original_bytes": 7633,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": 0.9\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 14,\n  \"evidence\": [\n    {\n      \"finding\": \"Mode guard, cEditor::SetActiveMode call, +0x7c window hooks, and receiver+0x60 store.\",\n      \"kind\": \"target_decompilation\",\n      \"source\": \"Ghidra 0x005dda30\"\n    },\n    {\n      \"finding\": \"Four distinct callers; 0x005e0000 supplies explicit Build/Paint/Play request branches.\",\n      \"kind\": \"direct_callers\",\n      \"source\": \"Ghidra callers of 0x005dda30\"\n    },\n    {\n      \"finding\": \"Recovered cEditor body performs old-mode teardown, writes cEditor+0x31c, and performs new-mode entry work.\",\n      \"kind\": \"sibling_and_consumer\",\n      \"source\": \"Ghidra 0x00587270\"\n    },\n    {\n      \"finding\": \"The target is independently recorded as the EditorUI mode updater and generated event editor_active_mode_requested.\",\n      \"kind\": \"committed_state_artifact\",\n      \"source\": \"knowledgegraph/research/state-machines/editor-workflows.json:846-882\"\n    },\n    {\n      \"finding\": \"No direct Sporepedia metadata, cSPAssetDataOTDB, cCommEvent, or network edge.\",\n      \"kind\": \"negative_family_check\",\n      \"source\": \"Ghidra direct callee set and structure checks\"\n    }\n  ],\n  \"family\": \"editor_mode_lifecycle\",\n  \"interfaces\": {\n    \"boundaries\": {\n      \"boundary_rule\": \"Keep editor mode state separate from App game-mode state, Simulator strategy state, and Sporepedia timeline data.\",\n      \"local\": \"The entire observed path is local editor/controller state, editor windows, editor models, and mode-specific layout state.\",\n      \"network\": {\n        \"evidence\": [\n          \"The direct callee set contains editor support functions, cEditor::SetActiveMode, and App-lifecycle facades, not a socket, protocol, or online-request function.\",\n          \"The committed editor state-machine evidence identifies UTFWin layouts and cEditor windows as the consumers.\"\n        ],\n        \"not_claimed\": \"An App lifecycle facade called by a downstream editor helper is not treated as a network call.\",\n        \"status\": \"no_direct_network_edge\"\n      }\n    },\n    \"direct_callees\": [],\n    \"direct_callers\": [],\n    \"globals\": [],\n    \"structures\": [],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": [],\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [\n        \"receiver pointer\",\n        \"requested editor mode\",\n        \"mode-specific window/controller pointers at receiver+0x64, +0x6c, +0x68, +0x80, and +0x84\"\n      ],\n      \"ordering\": [],\n      \"outputs\": [\n        \"receiver+0x60 stores the requested mode after the transition path\",\n        \"mode-specific virtual +0x7c state/visibility calls are made on owned windows\"\n      ],\n      \"postconditions\": [\n        \"The receiver's displayed-mode field is updated to the requested mode after teardown/setup work.\",\n        \"Mode-specific UI windows are hidden, shown, or rebuilt through the same +0x7c virtual surface.\",\n        \"No direct event record is allocated by the target.\"\n      ],\n      \"preconditions\": [\n        \"Return without change when receiver+0x60 already equals the requested mode.\",\n        \"The PlayMode-looking request has an additional early-return guard through FUN_00574a20(0).\",\n        \"The exact meaning of the first cEditor::SetActiveMode argument in the decompiler warning remains unresolved.\"\n      ],\n      \"purpose\": \"EDITOR_UI_MODE_REQUEST_AND_WINDOW_LIFECYCLE\",\n      \"return\": {\n        \"status\": \"not_reported\"\n      },\n      \"side_effects\": [\n        \"Calls the recovered Editors::cEditor::SetActiveMode body at 0x00587270.\",\n        \"Calls editor support helpers and App-lifecycle facade functions; those helpers are not network services.\"\n      ],\n      \"status\": \"partial_static_contract\",\n      \"unresolved\": [\n        \"What is the exact imported type of the target receiver and the exact mode-dependent window classes?\",\n        \"Does receiver+0x60 mirror cEditor+0x31c synchronously or is it updated after a deferred transition?\",\n        \"Which cEditorAnimEvent consumer observes each mode-entry send?\",\n        \"What do the unresolved 0x4fcc580/0x4fcc581 and 0x8c35f293 values select?\"\n      ]\n    }\n  },\n  \"invariants\": {\n    \"failure_semantics\": [],\n    \"invariants\": [],\n    \"invariants_status\": \"not_reported\"\n  },\n  \"name\": \"EDITOR_UI_MODE_REQUEST_AND_WINDOW_LIFECYCLE\",\n  \"package\": {\n    \"caveat\": \"not_reported\",\n    \"ownership_status\": \"not_reported\",\n    \"primary\": null,\n    \"secondary\": []\n  },\n  \"readiness\": {\n    \"next_action\": \"not_reported\",\n    \"runtime_performed\": false,\n    \"runtime_promoted\": false,\n    \"runtime_required\": true,\n    \"status\": \"NEEDS_RUNTIME\",\n    \"unlock_requirements\": []\n  },\n  \"source\": \"knowledgegraph/research/semantic-decomp/worker-07-sporepedia-events.json\",\n  \"state_events\": {\n    \"events\": [],\n    \"lifecycle\": {\n      \"lifecycle\": [\n        \"Guard against a no-op request.\",\n        \"Request downstream cEditor mode transition.\",\n        \"Invoke old-mode teardown hooks and new-mode setup hooks through the +0x7c surface.\",\n        \"Update the controller's displayed mode.\",\n        \"Downstream cEditor paths may construct or post cEditorAnimEvent for some mode entries.\"\n      ],\n      \"message_shape\": \"No target-local message object. The cEditorAnimEvent produced farther downstream is a separate 0x30-byte refcounted editor animation event family.\",\n      \"observed_fields\": [\n        {\n          \"keys\": [\n            \"meaning\",\n            \"receiver_offset\"\n     
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
  "OpaqueEditor",
  "OpaqueEditorModeManager",
  "OpaqueEditorModeTarget",
  "OpaqueEditorModeTarget / opaque void*",
  "std::uint32_t",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x005ddb6e"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00591fa0",
      "0x005dec10",
      "0x00883a90",
      "0x00883ad0",
      "0x051cc0b8",
      "0xb2e18705",
      "0x00883ad0",
      "0x00883a90",
      "0x00591fa0",
      "0x004af260",
      "0x005dda30",
      "0x00591690",
      "0x051cc0b8",
      "0x00591fa0",
      "0x005dec10",
      "0xb2e18705"
    ],
    "conflict_id": "editor_message_names_and_payloads",
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
      "0x0057ce80",
      "0x00587270",
      "0x00587270",
      "0x0057f3e0",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "editor_mode_gate",
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
      "0x005e0000",
      "0x70218642",
      "0xb006ef6e",
      "0xf006efa5",
      "0xf019c2e7",
      "0xf019c2f3",
      "0x005e0000",
      "0x004af260",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x00587270",
      "0x00587270",
      "0x00588570",
      "0x00588570",
      "0x0058ac10"
    ],
    "conflict_id": "editor_ui_command_names",
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
      "0x00586b00",
      "0x00587270",
      "0x00587a20",
      "0x00588570",
      "0x00588570",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00586b00",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "manipulator_cancel",
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
