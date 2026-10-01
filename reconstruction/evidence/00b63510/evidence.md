# Evidence 0x00b63510

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `036541804307665cd5cfc2a435f0b206e2dfff9c15c5848196b97a6e693fd68a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "ordinary_stack_arguments": [
    "uint32 message_id",
    "void* payload"
  ],
  "receiver": "bridge object in ECX",
  "ret_form": "RET 0x8",
  "return": "AL boolean"
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
      "entry_ESP+0x8",
      "entry_ESP+0x10",
      "entry_ESP+0x1c",
      "entry_ESP+0x34",
      "entry_ESP+0x40",
      "entry_ESP+0x54"
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
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x40",
        "observed": true,
        "ordinal": 16,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x54",
        "observed": true,
        "ordinal": 21,
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
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x40",
        "observed": true,
        "ordinal": 16,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x54",
        "observed": true,
        "ordinal": 21,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -76, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x8 pops less than the highest read slot 0x54; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "no_discriminator: the callee pop of 0x8 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x8 but entry slot 0x54 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "2550bf365e7083324e9709f1122bfd25510c1fa1a344908d58e348506b8efc61",
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
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 5,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0019",
        "obs-0031",
        "obs-0037",
        "obs-0041",
        "obs-0057",
        "obs-0063",
        "obs-0067",
        "obs-0080",
        "obs-0097",
        "obs-0101",
        "obs-0107",
        "obs-0114",
        "obs-0120"
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
    "va": "0x0067dcc0"
  },
  {
    "name": "FUN_00b5b800",
    "reconstructed": false,
    "va": "0x00b5b800"
  },
  {
    "name": "simulator_strategy_transition_00b5dbb0",
    "reconstructed": true,
    "va": "0x00b5dbb0"
  },
  {
    "name": "simulator_strategy_transition_00b5f040",
    "reconstructed": true,
    "va": "0x00b5f040"
  },
  {
    "name": "FUN_01021080",
    "reconstructed": true,
    "va": "0x01021080"
  }
]
```

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x007d85b0",
      "0x007d8c80",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d85b0",
      "0x0212d3e7",
      "0x022d1adc",
      "0x00b63510",
      "0x00b63510",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360"
    ],
    "conflict_id": "U-MODE-TRANSITION-RUNTIME",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Static call order is fixed: old OnExit, active-index write, mode-exit send, new OnEnter, mode-enter send. Runtime reachability and listener completion order are not verified.",
    "resolution_status": "Static call order is fixed: old OnExit, active-index write, mode-exit send, new OnEnter, mode-enter send. Runtime reachability and listener completion order are not verified.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e11333",
      "0x01412598",
      "0x01412598",
      "0x00e11333",
      "0x00e11333",
      "0x00e11333",
      "0x00b63510",
      "0x007d9120",
      "0x00e11333"
    ],
    "conflict_id": "U06",
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
      "0x007d85b0",
      "0x007d8c80",
      "0x00b63510",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d85b0",
      "0x0212d3e7",
      "0x022d1adc",
      "0x00b63510",
      "0x00b63510",
      "0x00b63510",
      "0x00b63510",
      "0x00b63510"
    ],
    "conflict_id": "U08",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The mode helper establishes the static exit/index/message/enter/message order; synchronous-versus-queued delivery and listener priority remain unresolved.",
    "resolution_status": "The mode helper establishes the static exit/index/message/enter/message order; synchronous-versus-queued delivery and listener priority remain unresolved.",
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
  "count": 282,
  "instructions": [
    {
      "address": "00b63510",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b63511",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b63512",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b63513",
      "instruction": "MOV EDI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00b63517",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b63519",
      "instruction": "CMP EDI,0x3e9a620"
    },
    {
      "address": "00b6351f",
      "instruction": "JA 0x00b6368f"
    },
    {
      "address": "00b63525",
      "instruction": "JZ 0x00b63680"
    },
    {
      "address": "00b6352b",
      "instruction": "CMP EDI,0x212d3e7"
    },
    {
      "address": "00b63531",
      "instruction": "JA 0x00b635e5"
    },
    {
      "address": "00b63537",
      "instruction": "JZ 0x00b6361d"
    },
    {
      "address": "00b6353d",
      "instruction": "CMP EDI,0xf62ade"
    },
    {
      "address": "00b63543",
      "instruction": "JZ 0x00b6357c"
    },
    {
      "address": "00b63545",
      "instruction": "CMP EDI,0xf62def"
    },
    {
      "address": "00b6354b",
      "instruction": "JNZ 0x00b6386c"
    },
    {
      "address": "00b63551",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00b63555",
      "instruction": "CMP dword ptr [EAX + 0x18],0x39393837"
    },
    {
      "address": "00b6355c",
      "instruction": "JNZ 0x00b63574"
    },
    {
      "address": "00b6355e",
      "instruction": "CALL 0x00b3d320"
    },
    {
      "address": "00b63563",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b63565",
      "instruction": "JZ 0x00b63574"
    },
    {
      "address": "00b63567",
      "instruction": "CALL 0x00b5b800"
    },
    {
      "address": "00b6356c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b6356d",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b6356f",
      "instruction": "CALL 0x00b5e3f0"
    },
    {
      "address": "00b63574",
      "instruction": "POP EDI"
    },
    {
      "address": "00b63575",
      "instruction": "POP ESI"
    },
    {
      "address": "00b63576",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00b63578",
      "instruction": "POP EBX"
    },
    {
      "address": "00b63579",
      "instruction": "RET 0x8"
    },
    {
      "address": "00b6357c",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00b63580",
      "instruction": "MOV ESI,dword ptr [EAX + 0x10]"
    },
    {
      "address": "00b63583",
      "instruction": "MOV EDI,dword ptr [EAX + 0x18]"
    },
    {
      "address": "00b63586",
      "instruction": "CMP ESI,0x24a4f5a"
    },
    {
      "address": "00b6358c",
      "instruction": "JNZ 0x00b635a7"
    },
    {
      "address": "00b6358e",
      "instruction": "CALL 0x00b3d270"
    },
    {
      "address": "00b63593",
      "instruction": "CMP EDI,dword ptr [EAX + 0x308]"
    },
    {
      "address": "00b63599",
      "instruction": "JNZ 0x00b635a7"
    },
    {
      "address": "00b6359b",
      "instruction": "CALL 0x00b3d270"
    },
    {
      "address": "00b635a0",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b635a2",
      "instruction": "CALL 0x00b108b0"
    },
    {
      "address": "00b635a7",
      "instruction": "CALL 0x00b3d280"
    },
    {
      "address": "00b635ac",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b635ae",
      "instruction": "JZ 0x00b6386c"
    },
    {
      "address": "00b635b4",
      "instruction": "CMP ESI,0x24a4f5a"
    },
    {
      "address": "00b635ba",
      "instruction": "JNZ 0x00b6386c"
    },
    {
      "address": "00b635c0",
      "instruction": "CALL 0x00b3d280"
    },
    {
      "address": "00b635c5",
      "instruction": "CMP EDI,dword ptr [EAX + 0x308]"
    },
    {
      "address": "00b635cb",
      "instruction": "JNZ 0x00b6386c"
    },
    {
      "address": "00b635d1",
      "instruction": "CALL 0x00b3d280"
    },
    {
      "address": "00b635d6",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b635d8",
      "instruction": "CALL 0x00b108b0"
    },
    {
      "address": "00b635dd",
      "instruction": "POP EDI"
    },
    {
      "address": "00b635de",
      "instruction": "POP ESI"
    },
    {
      "address": "00b635df",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00b635e1",
      "instruction": "POP EBX"
    },
    {
      "address": "00b635e2",
      "instruction": "RET 0x8"
    },
    {
      "address": "00b635e5",
      "instruction": "CMP EDI,0x22d1adc"
    },
    {
      "address": "00b635eb",
      "instruction": "JZ 0x00b6361d"
    },
    {
      "address": "00b635ed",
      "instruction": "CMP EDI,0x255abf5"
    },
    {
      "address": "00b635f3",
      "instruction": "JNZ 0x00b6386c"
    },
    {
      "address": "00b635f9",
      "instruction": "MOV ECX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00b635fd",
      "instruction": "MOV EBX,0x1"
    },
    {
      "address": "00b63602",
      "instruction": "CMP dword ptr [ECX + 0x8],EBX"
    },
    {
      "address": "00b63605",
      "instruction": "JZ 0x00b63612"
    },
    {
      "address": "00b63607",
      "instruction": "ADD dword ptr [ESI + 0x30],EBX"
    },
    {
      "address": "00b6360a",
      "instruction": "POP EDI"
    },
    {
      "address": "00b6360b",
      "instruction": "POP ESI"
    },
    {
      "address": "00b6360c",
      "instruction": "MOV AL,BL"
    },
    {
      "address": "00b6360e",
      "instruction": "POP EBX"
    },
    {
      "address": "00b6360f",
      "instruction": "RET 0x8"
    },
    {
      "address": "00b63612",
      "instruction": "DEC dword ptr [ESI + 0x30]"
    },
    {
      "address": "00b63615",
      "instruction": "POP EDI"
    },
    {
      "address": "00b63616",
      "instructi
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
  "original_bytes": 10975,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"ordinary_stack_arguments\": [\n      \"uint32 message_id\",\n      \"void* payload\"\n    ],\n    \"receiver\": \"bridge object in ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return\": \"AL boolean\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"app_mode_activate_by_name_007d8360\",\n      \"va\": \"0x007d8360\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"app_mode_activate_007d85b0\",\n      \"va\": \"0x007d85b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"app_mode_activate_index_007d8c80\",\n      \"va\": \"0x007d8c80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"strategy_request_ready_00b5b840\",\n      \"va\": \"0x00b5b840\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"strategy_queue_primary_00b5b880\",\n      \"va\": \"0x00b5b880\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"strategy_queue_secondary_00b5b8a0\",\n      \"va\": \"0x00b5b8a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"strategy_commit_primary_00b5b8c0\",\n      \"va\": \"0x00b5b8c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"strategy_commit_secondary_00b5b8e0\",\n      \"va\": \"0x00b5b8e0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueGameModeState\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      },\n      {\n        \"name\": \"FUN_00b5b800\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b5b800\"\n      },\n      {\n        \"name\": \"simulator_strategy_transition_00b5dbb0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b5dbb0\"\n      },\n      {\n        \"name\": \"simulator_strategy_transition_00b5f040\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b5f040\"\n      },\n      {\n        \"name\": \"FUN_01021080\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021080\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b63822\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067cb40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b636c2\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b63710\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b6377d\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b63794\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b635a2\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b108b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b635d8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b108b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b63700\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b1e410\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsi
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
  "body_end": "00b63873",
  "body_span_bytes": 868,
  "body_start": "00b63510",
  "callees": [
    "FUN_00b3d270",
    "Graphics::ITextureManager::Get",
    "FUN_00d100b0",
    "FUN_00b5cb20",
    "FUN_00b5e3f0",
    "FUN_01021080",
    "FUN_00b3d280",
    "FUN_00e00ac0",
    "FUN_00b60d80",
    "FUN_01002bd0",
    "FUN_00fd9c60",
    "FUN_00f473a0",
    "FUN_00b5c9d0",
    "FUN_0067cb40",
    "FUN_00d09660",
    "UTFWin::TreeNode::func2Ch",
    "FUN_00b5b800",
    "FUN_00fde3e0",
    "FUN_00b5ca70",
    "FUN_00b5f040",
    "FUN_00b5dbb0",
    "FUN_00b108b0",
    "App::IAppSystem::Get",
    "FUN_00b3d320"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b63510",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b63510",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x763510",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b63510(void)",
  "size_bytes": 868,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b63510",
  "vtables": {
    "referenced_by_vtables": [
      "0x01462818"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0146281c"
    }
  ]
}
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:0x3e9a620 writes the package-owned synthetic 0x01686af1 flag to 1; 0x3e9a625 writes it to 0."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-mode-wave7/00b63510.json"
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
    "Observe receiver validity, all message-id reachability, service identities, mode-object fields, payload validity, and all unresolved native port results; runtime validation is not run."
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
  "OpaqueGameModeState"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00b63510"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x007d85b0",
      "0x007d8c80",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d85b0",
      "0x0212d3e7",
      "0x022d1adc",
      "0x00b63510",
      "0x00b63510",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360"
    ],
    "conflict_id": "U-MODE-TRANSITION-RUNTIME",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Static call order is fixed: old OnExit, active-index write, mode-exit send, new OnEnter, mode-enter send. Runtime reachability and listener completion order are not verified.",
    "resolution_status": "Static call order is fixed: old OnExit, active-index write, mode-exit send, new OnEnter, mode-enter send. Runtime reachability and listener completion order are not verified.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e11333",
      "0x01412598",
      "0x01412598",
      "0x00e11333",
      "0x00e11333",
      "0x00e11333",
      "0x00b63510",
      "0x007d9120",
      "0x00e11333"
    ],
    "conflict_id": "U06",
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
      "0x007d85b0",
      "0x007d8c80",
      "0x00b63510",
      "0x01412598",
      "0x01412598",
      "0x007d8c80",
      "0x007d8c80",
      "0x007d85b0",
      "0x0212d3e7",
      "0x022d1adc",
      "0x00b63510",
      "0x00b63510",
      "0x00b63510",
      "0x00b63510",
      "0x00b63510"
    ],
    "conflict_id": "U08",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The mode helper establishes the static exit/index/message/enter/message order; synchronous-versus-queued delivery and listener priority remain unresolved.",
    "resolution_status": "The mode helper establishes the static exit/index/message/enter/message order; synchronous-versus-queued delivery and listener priority remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
