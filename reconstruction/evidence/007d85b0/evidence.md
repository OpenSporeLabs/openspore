# Evidence 0x007d85b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a184ba502b2c5a1eaf1c82bcda16be6e2b61edf02a8293e348e045454f055326`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "ordinary_stack_arguments": [
    "int32 index"
  ],
  "receiver": "AppModeRegistry* in ECX",
  "ret_form": "RET 0x4",
  "return": "void"
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
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path"
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
  "content_sha256": "ab8ce8014ffb690985a89d77cdaf190df5301f0c5147d912e1db175fc33e6abc",
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
        "obs-0056"
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
        "obs-0013"
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
        "obs-0011",
        "obs-0033",
        "obs-0042",
        "obs-0047",
        "obs-0052",
        "obs-0055"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          20,
          24,
          40
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0004",
        "obs-0055"
      ],
      "claim": "an FS:/GS: operand is an SEH or cookie frame, which is not variadic evidence",
      "confidence": "OBSERVED",
      "id": "V2",
      "value": {
        "seh_or_cookie_frame": true
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0033",
        "obs-0042",
        "obs-0047",
        "obs-0052",
        "obs-0055",
        "obs-0056"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0056"
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
        "obs-0056"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0056"
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
      "at": "0x007d85b0",
      "id": "obs-0001",
      "index": 0,
      "kind": "SEGMENT_TLS",
      "raw": "MOV EAX,FS:[0x0]",
      "segment": "FS",
      "text": "FS:[0x0]"
    },
    {
      "at": "0x007d85b0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,FS:[0x0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007d85bd",
      "count": 25,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x007d85be",
      "id": "obs-0004",
      "index": 4,
      "kind": "SEGMENT_TLS",
      "raw": "MOV dword ptr FS:[0x0],ESP",
      "segment": "FS",
      "text": "dword ptr FS:[0x0]"
    },
    {
      "at": "0x007d85be",
      "count": 25,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV dword ptr FS:[0x0],ESP",
      "reg": "ESP"
    },
    {
      "and_esp": null,
      "at": "0x007d85c5",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0006",
      "index": 5,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 14,
      "raw": "SUB ESP,0x80",
      "sub": 128
    },
    {
      "at": "0x007d85c5"
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
    "name": "app_mode_activate_index_007d8c80",
    "reconstructed": true,
    "va": "0x007d8c80"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 9653,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x007d85b0\",\n      \"0x007d8c80\",\n      \"0x01412598\",\n      \"0x01412598\",\n      \"0x007d8c80\",\n      \"0x007d8c80\",\n      \"0x007d85b0\",\n      \"0x0212d3e7\",\n      \"0x022d1adc\",\n      \"0x007d8060\",\n      \"0x007d8060\",\n      \"0x007d8360\",\n      \"0x007d8360\",\n      \"0x007d85b0\",\n      \"0x007d85b0\",\n      \"0x007d8c30\"\n    ],\n    \"conflict_id\": \"Q-APP-ID-CATALOG\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Registration operations, mode IDs, and several named event surfaces are concrete. The complete ID catalog, payload schema, and producer/consumer map are not recovered.\",\n    \"resolution_status\": \"Registration operations, mode IDs, and several named event surfaces are concrete. The complete ID catalog, payload schema, and producer/consumer map are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x007d8060\",\n      \"0x007d8060\",\n      \"0x007d8360\",\n      \"0x007d8360\",\n      \"0x007d85b0\",\n      \"0x007d85b0\",\n      \"0x007d8c30\",\n      \"0x007d8c30\",\n      \"0x007d8c80\",\n      \"0x007d8c80\",\n      \"0x007d8d40\"\n    ],\n    \"conflict_id\": \"Q-INPUT-ROUTING\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n    \"resolution_status\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x007d8060\",\n      \"0x007d8060\",\n      \"0x007d8230\",\n      \"0x007d8230\",\n      \"0x007d8360\",\n      \"0x007d8360\",\n      \"0x007d8470\",\n      \"0x007d8470\",\n      \"0x007d85b0\",\n      \"0x007d85b0\",\n      \"0x007d8c30\"\n    ],\n    \"conflict_id\": \"U-GAME-INPUT-ROUTER\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n    \"resolution_status\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x007d85b0\",\n      \"0x007d8c80\",\n      \"0x01412598\",\n      \"0x01412598\",\n      \"0x007d8c80\",\n      \"0x007d8c80\",\n      \"0x007d85b0\",\n      \"0x0212d3e7\",\n      \"0x022d1adc\",\n      \"0x007d85b0\",\n      \"0x00b1db60\",\n      \"0x00b1db60\",\n      \"0x00b1dbd0\",\n      \"0x00b1dbd0\",\n      \"0x00b5b840\",\n      \"0x00b5b840\"\n    ],\n    \"conflict_id\": \"U-MODE-MESSAGE-PAYLOAD\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The two mode IDs and send sites are concrete. The formal parameter roles and remaining StandardMessage slots are not recovered.\",\n    \"resolution_status\": \"The two mode IDs and send sites are concrete. The formal parameter roles and remaining StandardMessage slots are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x007d85b0\",\n      \"0x007d8c80\",\n      \"0x01412598\",\n      \"0x01412598\",\n      \"0x007d8c80\",\n      \"0x007d8c80\",\n      \"0x007d85b0\",\n      \"0x0212d3e7\",\n      \"0x022d1adc\",\n      \"0x00b63510\",\n      \"0x00b63510\",\n      \"0x007d8060\",\n      \"0x007d8060\",\n      \"0x007d8230\",\n      \"0x007d8230\",\n      \"0x007d8360\"\n    ],\n    \"conflict_id\": \"U-MODE-TRANSITION-RUNTIME\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Static call order is fixed: old OnExit, active-index write, mode-exit send, new OnEnter, mode-enter send. Runtime reachability and listener completion order are not verified.\",\n    \"resolution_status\": \"Static call order is fixed: old OnExit, active-index write, mode-exit send, new OnEnter, mode-enter send. Runtime reachability and listener completion order are not verified.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x007d85b0\",\n      \"0x007d8c80\",\n      \"0x00b63510\",\n      \"0x01412598\",\n      \"0x01412598\",\n      \"0x007d8c80\",\n      \"0x007d8c80\",\n      \"0x007d85b0\",\n      \"0x0212d3e7\",\n      \"0x022d1adc\",\n      \"0x00b63510\",\n      \"0x00b63510\",\n      \"0x00b63510\",\n      \"0x00b63510\",\n      \"0x00b63510\"\n    ],\n    \"conflict_id\": \"U08\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The mode helper establishes the static exit/index/message/enter/message order; syn
[TRUNCATED]
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
  "count": 111,
  "instructions": [
    {
      "address": "007d85b0",
      "instruction": "MOV EAX,FS:[0x0]"
    },
    {
      "address": "007d85b6",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "007d85b8",
      "instruction": "PUSH 0x1215ff3"
    },
    {
      "address": "007d85bd",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007d85be",
      "instruction": "MOV dword ptr FS:[0x0],ESP"
    },
    {
      "address": "007d85c5",
      "instruction": "SUB ESP,0x80"
    },
    {
      "address": "007d85cb",
      "instruction": "PUSH ESI"
    },
    {
      "address": "007d85cc",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "007d85ce",
      "instruction": "MOV ECX,dword ptr [ESI + 0x28]"
    },
    {
      "address": "007d85d1",
      "instruction": "PUSH EDI"
    },
    {
      "address": "007d85d2",
      "instruction": "MOV EDI,dword ptr [ESP + 0x98]"
    },
    {
      "address": "007d85d9",
      "instruction": "CMP EDI,ECX"
    },
    {
      "address": "007d85db",
      "instruction": "JZ 0x007d871c"
    },
    {
      "address": "007d85e1",
      "instruction": "PUSH EBX"
    },
    {
      "address": "007d85e2",
      "instruction": "PUSH EBP"
    },
    {
      "address": "007d85e3",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "007d85e5",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "007d85e7",
      "instruction": "CMP ECX,EBP"
    },
    {
      "address": "007d85e9",
      "instruction": "JL 0x007d8623"
    },
    {
      "address": "007d85eb",
      "instruction": "MOV EDX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "007d85ee",
      "instruction": "SUB EDX,dword ptr [ESI + 0x14]"
    },
    {
      "address": "007d85f1",
      "instruction": "MOV EAX,0x2aaaaaab"
    },
    {
      "address": "007d85f6",
      "instruction": "IMUL EDX"
    },
    {
      "address": "007d85f8",
      "instruction": "SAR EDX,0x2"
    },
    {
      "address": "007d85fb",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "007d85fd",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "007d8600",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "007d8602",
      "instruction": "CMP ECX,EAX"
    },
    {
      "address": "007d8604",
      "instruction": "JGE 0x007d8623"
    },
    {
      "address": "007d8606",
      "instruction": "MOV EDX,dword ptr [ESI + 0x14]"
    },
    {
      "address": "007d8609",
      "instruction": "LEA ECX,[ECX + ECX*0x2]"
    },
    {
      "address": "007d860c",
      "instruction": "MOV ECX,dword ptr [EDX + ECX*0x8]"
    },
    {
      "address": "007d860f",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "007d8611",
      "instruction": "MOV EDX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "007d8614",
      "instruction": "CALL EDX"
    },
    {
      "address": "007d8616",
      "instruction": "MOV EAX,dword ptr [ESI + 0x28]"
    },
    {
      "address": "007d8619",
      "instruction": "MOV ECX,dword ptr [ESI + 0x14]"
    },
    {
      "address": "007d861c",
      "instruction": "LEA EAX,[EAX + EAX*0x2]"
    },
    {
      "address": "007d861f",
      "instruction": "MOV EBX,dword ptr [ECX + EAX*0x8 + 0x4]"
    },
    {
      "address": "007d8623",
      "instruction": "MOV dword ptr [ESI + 0x28],EDI"
    },
    {
      "address": "007d8626",
      "instruction": "CALL 0x00883860"
    },
    {
      "address": "007d862b",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "007d862d",
      "instruction": "CMP EDI,EBP"
    },
    {
      "address": "007d862f",
      "instruction": "JZ 0x007d8695"
    },
    {
      "address": "007d8631",
      "instruction": "MOV dword ptr [ESP + 0x40],EBP"
    },
    {
      "address": "007d8635",
      "instruction": "MOV dword ptr [ESP + 0x10],0x13eb90c"
    },
    {
      "address": "007d863d",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "007d863f",
      "instruction": "LEA EAX,[ESP + 0x14]"
    },
    {
      "address": "007d8643",
      "instruction": "XCHG dword ptr [EAX],EDX"
    },
    {
      "address": "007d8645",
      "instruction": "MOV dword ptr [ESP + 0x10],0x13eb844"
    },
    {
      "address": "007d864d",
      "instruction": "MOV dword ptr [ESP + 0x48],EBP"
    },
    {
      "address": "007d8651",
      "instruction": "MOV EAX,dword ptr [ESI + 0x28]"
    },
    {
      "address": "007d8654",
      "instruction": "MOV EDX,dword ptr [ESI + 0x14]"
    },
    {
      "address": "007d8657",
      "instruction": "LEA ECX,[EAX + EAX*0x2]"
    },
    {
      "address": "007d865a",
      "instruction": "MOV EAX,dword ptr [EDX + ECX*0x8 + 0x4]"
    },
    {
      "address": "007d865e",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "007d8660",
      "instruction": "MOV EDX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "007d8663",
      "instruction": "MOV dword ptr [ESP + 0x18],EAX"
    },
    {
      "address": "007d8667",
      "instruction": "PUSH EBP"
    },
    {
      "address": "007d8668",
      "instruction": "LEA EAX,[ESP + 0x14]"
    },
    {
      "address": "007d866c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007d866d",
      "instruction": "PUSH 0x212d3e7"
    },
    {
      "address": "007d8672",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "007d8674",
      "instruction": "MOV dword ptr [ESP + 0xa4],EBP"
    },
    {
      "address": "007d867b",
      "instruction": "MOV dword ptr [ESP + 0x2c],EBX"
    },
    {
      "address": "007d867f",
      "instruction": "CALL EDX"
    },
    {
      "address": "007d8681",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "007d8685",
      "instruction": "MOV dword ptr [ESP + 0x98],0xffffffff"
    },
    {
      "address": "007d8690",
      "instruction": "CALL 0x00421cf0"
    },
    {
      "address": "007d8695",
      "instructio
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
  "original_bytes": 6406,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"ordinary_stack_arguments\": [\n      \"int32 index\"\n    ],\n    \"receiver\": \"AppModeRegistry* in ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return\": \"void\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 27,\n      \"symbol\": \"app_mode_activate_index_007d8c80\",\n      \"va\": \"0x007d8c80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"app_mode_activate_by_name_007d8360\",\n      \"va\": \"0x007d8360\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"strategy_request_ready_00b5b840\",\n      \"va\": \"0x00b5b840\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"strategy_queue_primary_00b5b880\",\n      \"va\": \"0x00b5b880\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"strategy_queue_secondary_00b5b8a0\",\n      \"va\": \"0x00b5b8a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"strategy_commit_primary_00b5b8c0\",\n      \"va\": \"0x00b5b8c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"strategy_commit_secondary_00b5b8e0\",\n      \"va\": \"0x00b5b8e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameModeState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"app_simulator_mode_bridge_00b63510\",\n      \"va\": \"0x00b63510\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueGameModeState\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"app_mode_activate_index_007d8c80\",\n        \"reconstructed\": true,\n        \"va\": \"0x007d8c80\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x007d8ca5\",\n        \"direction\": \"in\",\n        \"other\": \"0x007d8c80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007d8690\",\n        \"direction\": \"out\",\n        \"other\": \"0x00421cf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007d8715\",\n        \"direction\": \"out\",\n        \"other\": \"0x00421cf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007d8626\",\n        \"direction\": \"out\",\n        \"other\": \"0x00883860\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x007d8c80\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0244\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 2\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"app_mode_activate_007d85b0\",\n  \"normalized_symbol\": \"app_mode_activate_007d85b0\",\n  \"observed_mechanics\": [\n    \"{}\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-GAME-MODE-WAVE7\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-GAME-MODE-WAVE7\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-GAME-MODE-WAVE7\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved_after_parallel_review\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"Observe concrete mode identities, notification manager publication, vtable targets, and runtime transition reachability;
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
  "body_end": "007d8734",
  "body_span_bytes": 389,
  "body_start": "007d85b0",
  "callees": [
    "FUN_00883860",
    "FUN_00421cf0"
  ],
  "callers": [
    "FUN_007d8c80"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "007d85b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_007d85b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3d85b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_007d85b0(void)",
  "size_bytes": 389,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007d85b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "007d8c74"
    },
    {
      "from": "007d8ca5"
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
  "file": "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-mode-wave7/007d85b0.json"
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
    "Observe concrete mode identities, notification manager publication, vtable targets, and runtime transition reachability; runtime validation is not run."
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
{
  "original_bytes": 9653,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x007d85b0\",\n      \"0x007d8c80\",\n      \"0x01412598\",\n      \"0x01412598\",\n      \"0x007d8c80\",\n      \"0x007d8c80\",\n      \"0x007d85b0\",\n      \"0x0212d3e7\",\n      \"0x022d1adc\",\n      \"0x007d8060\",\n      \"0x007d8060\",\n      \"0x007d8360\",\n      \"0x007d8360\",\n      \"0x007d85b0\",\n      \"0x007d85b0\",\n      \"0x007d8c30\"\n    ],\n    \"conflict_id\": \"Q-APP-ID-CATALOG\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Registration operations, mode IDs, and several named event surfaces are concrete. The complete ID catalog, payload schema, and producer/consumer map are not recovered.\",\n    \"resolution_status\": \"Registration operations, mode IDs, and several named event surfaces are concrete. The complete ID catalog, payload schema, and producer/consumer map are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x007d8060\",\n      \"0x007d8060\",\n      \"0x007d8360\",\n      \"0x007d8360\",\n      \"0x007d85b0\",\n      \"0x007d85b0\",\n      \"0x007d8c30\",\n      \"0x007d8c30\",\n      \"0x007d8c80\",\n      \"0x007d8c80\",\n      \"0x007d8d40\"\n    ],\n    \"conflict_id\": \"Q-INPUT-ROUTING\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n    \"resolution_status\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x007d8060\",\n      \"0x007d8060\",\n      \"0x007d8230\",\n      \"0x007d8230\",\n      \"0x007d8360\",\n      \"0x007d8360\",\n      \"0x007d8470\",\n      \"0x007d8470\",\n      \"0x007d85b0\",\n      \"0x007d85b0\",\n      \"0x007d8c30\"\n    ],\n    \"conflict_id\": \"U-GAME-INPUT-ROUTER\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n    \"resolution_status\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x007d85b0\",\n      \"0x007d8c80\",\n      \"0x01412598\",\n      \"0x01412598\",\n      \"0x007d8c80\",\n      \"0x007d8c80\",\n      \"0x007d85b0\",\n      \"0x0212d3e7\",\n      \"0x022d1adc\",\n      \"0x007d85b0\",\n      \"0x00b1db60\",\n      \"0x00b1db60\",\n      \"0x00b1dbd0\",\n      \"0x00b1dbd0\",\n      \"0x00b5b840\",\n      \"0x00b5b840\"\n    ],\n    \"conflict_id\": \"U-MODE-MESSAGE-PAYLOAD\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The two mode IDs and send sites are concrete. The formal parameter roles and remaining StandardMessage slots are not recovered.\",\n    \"resolution_status\": \"The two mode IDs and send sites are concrete. The formal parameter roles and remaining StandardMessage slots are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x007d85b0\",\n      \"0x007d8c80\",\n      \"0x01412598\",\n      \"0x01412598\",\n      \"0x007d8c80\",\n      \"0x007d8c80\",\n      \"0x007d85b0\",\n      \"0x0212d3e7\",\n      \"0x022d1adc\",\n      \"0x00b63510\",\n      \"0x00b63510\",\n      \"0x007d8060\",\n      \"0x007d8060\",\n      \"0x007d8230\",\n      \"0x007d8230\",\n      \"0x007d8360\"\n    ],\n    \"conflict_id\": \"U-MODE-TRANSITION-RUNTIME\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Static call order is fixed: old OnExit, active-index write, mode-exit send, new OnEnter, mode-enter send. Runtime reachability and listener completion order are not verified.\",\n    \"reso
[TRUNCATED]
```
