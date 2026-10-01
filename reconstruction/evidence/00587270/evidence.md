# Evidence 0x00587270

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `4ddcd5b9682ff17c083266bb47526db5474491ed7104d8111c931e8352f23468`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "return_type": "bool",
  "stack_arguments": [
    {
      "abi_type": "std::uint32_t",
      "entry_offset": "ESP+4",
      "name": "mode",
      "type": "std::uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+8",
      "name": "flag",
      "observed_values": [
        0,
        1
      ],
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
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
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
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
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
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
  "content_sha256": "3ac6af09d845121dd78ee5f80e1ed89d35875b2a13618b1a15f69d7a2b790367",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
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
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 8,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0023",
        "obs-0238"
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
        "obs-0016",
        "obs-0017",
        "obs-0058"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0030",
        "obs-0032",
        "obs-0042",
        "obs-0048",
        "obs-0064",
        "obs-0067",
        "obs-0070",
        "obs-0073",
        "obs-0075",
        "obs-0078",
        "obs-0087",
        "obs-0090",
        "obs-0092",
        "obs-0100",
        "obs-0102",
        "obs-0106",
        "obs-0109",
        "obs-0114",
        "obs-0120",
        "obs-0121",
        "obs-0126",
        "obs-0133",
        "obs-0137",
        "obs-0144",
        "obs-0145",
        "obs-0150",
        "obs-0152",
        "obs-0153",
        "obs-0155",
        "obs-0158",
        "obs-0164",
        "obs-0167",
        "obs-0172",
        "obs-0185",
        "obs-0186",
        "obs-0189",
        "obs-0193",
        "obs-0194",
        "obs-0196",
        "obs-0200",
        "obs-0202",
        "obs-0205",
        "obs-0218",
        "obs-0227",
        "obs-0231"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          60,
          104,
          124,
          152,
          164,
          168,
          212,
          228,
          232,
          233,
          336,
          340,
          460,
          526,
          632,
          636,
          693,
          856,
          864,
          868,
          901,
          908,
          1138,
          1240
        ],
        "register": "ECX",
        "written_through": 7
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0023",
        "obs-0238"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
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
    },
    {
      "id": "obs-0004"
    },
    {
      "id": "obs-0005"
    },
    {
      "id": "obs-0006"
    },
    {
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
    "va": "0x0045ae10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0045b150"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0045b210"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004c49e0"
  },
  {
    "name": "PaintPersistenceBoundary_submit_004c5200",
    "reconstructed": true,
    "va": "0x004c5200"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573c00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573d70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005772b0"
  },
  {
    "name": "EditorAnimWorld_GetCreatureController_0059cac0",
    "reconstructed": true,
    "va": "0x0059cac0"
  },
  {
    "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
    "reconstructed": true,
    "va": "0x0059cea0"
  },
  {
    "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
    "reconstructed": true,
    "va": "0x0059cf00"
  },
  {
    "name": "editor_anim_event_message_send_0059d8b0",
    "reconstructed": true,
    "va": "0x0059d8b0"
  },
  {
    "name": "cEditorAnimEvent__ctor",
    "reconstructed": false,
    "va": "0x0059d960"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
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
    "name": "Editors::cEditor::OnExit",
    "reconstructed": false,
    "va": "0x00587a20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0058a350"
  },
  {
    "name": "Editors::cEditor::HandleMessage",
    "reconstructed": false,
    "va": "0x00591fa0"
  },
  {
    "name": "FUN_005dda30",
    "reconstructed": true,
    "va": "0x005dda30"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 17652,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00587270\",\n      \"0x0059d840\",\n      \"0x0059d8b0\",\n      \"0x00587270\",\n      \"0x0059d8b0\",\n      \"0x0059d840\",\n      \"0x00573970\",\n      \"0x00573970\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00587270\",\n      \"0x00587270\",\n      \"0x0059d840\",\n      \"0x0059d840\",\n      \"0x0059d8b0\",\n      \"0x0059d8b0\"\n    ],\n    \"conflict_id\": \"Q-ANIMATION-DISPATCH\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Editor animation Send/Post surfaces and the editor mode producer are concrete. The final AnimatedCreature/IAnimWorld consumer and pose ordering are unresolved.\",\n    \"resolution_status\": \"Editor animation Send/Post surfaces and the editor mode producer are concrete. The final AnimatedCreature/IAnimWorld consumer and pose ordering are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00591fa0\",\n      \"0x00883a90\",\n      \"0x00883ad0\",\n      \"0x00883ad0\",\n      \"0x00883a90\",\n      \"0x00591fa0\",\n      \"0x00573970\",\n      \"0x00573970\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00587270\",\n      \"0x00587270\",\n      \"0x0059d840\",\n      \"0x0059d840\",\n      \"0x0059d8b0\",\n      \"0x0059d8b0\"\n    ],\n    \"conflict_id\": \"Q-EDITOR-MESSAGE-CATALOG\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.\",\n    \"resolution_status\": \"The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-001-mission-transitions\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"resolution_status\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00d2e4a0\",\n      \"0x00d2e4a0\",\n      \"0x00aeb7b0\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\",\n      \"0x00588570\",\n      \"0x00588570\",\n      \"0x0058a5a0\"\n    ],\n    \"conflict_id\": \"U-002-tribe-plans\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00582fe0\",\n      \"0x00587270\",\n      \"0x0059c830\",\n      \"0x0059c830\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-006-editor-world-slot-conflict\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The +0x360/+0x364 alternatives are preserved; no pointer-pair versus pointer-plus-ID choice is made without a typed body.\",\n    \"resolution_status\": \"The +0x360/+0x364 alternatives are preserved; no pointer-pair versus pointer-plus-ID choice is made without a typed body.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-008-runtime-validation\",\n    \"kind\": \"conflict_ledger\",\n    \"rej
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
  "count": 621,
  "instructions": [
    {
      "address": "00587270",
      "instruction": "SUB ESP,0x20"
    },
    {
      "address": "00587273",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00587274",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00587275",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00587277",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00587278",
      "instruction": "LEA EAX,[EBP + 0x31c]"
    },
    {
      "address": "0058727e",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0058727f",
      "instruction": "MOV EDI,dword ptr [EAX]"
    },
    {
      "address": "00587281",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00587283",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "00587287",
      "instruction": "MOV dword ptr [ESP + 0x10],EDI"
    },
    {
      "address": "0058728b",
      "instruction": "CMP EDI,dword ptr [ESP + 0x34]"
    },
    {
      "address": "0058728f",
      "instruction": "JNZ 0x005872a3"
    },
    {
      "address": "00587291",
      "instruction": "CMP byte ptr [ESP + 0x38],BL"
    },
    {
      "address": "00587295",
      "instruction": "JNZ 0x005872a3"
    },
    {
      "address": "00587297",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00587299",
      "instruction": "POP EDI"
    },
    {
      "address": "0058729a",
      "instruction": "POP ESI"
    },
    {
      "address": "0058729b",
      "instruction": "POP EBP"
    },
    {
      "address": "0058729c",
      "instruction": "POP EBX"
    },
    {
      "address": "0058729d",
      "instruction": "ADD ESP,0x20"
    },
    {
      "address": "005872a0",
      "instruction": "RET 0x8"
    },
    {
      "address": "005872a3",
      "instruction": "MOV EAX,dword ptr [EBP + 0x38c]"
    },
    {
      "address": "005872a9",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "005872ab",
      "instruction": "JZ 0x005872b2"
    },
    {
      "address": "005872ad",
      "instruction": "CMP EAX,0x6"
    },
    {
      "address": "005872b0",
      "instruction": "JNZ 0x00587297"
    },
    {
      "address": "005872b2",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "005872b5",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "005872b7",
      "instruction": "SUB EAX,EBX"
    },
    {
      "address": "005872b9",
      "instruction": "MOVSS dword ptr [EBP + 0x68],XMM0"
    },
    {
      "address": "005872be",
      "instruction": "JZ 0x00587453"
    },
    {
      "address": "005872c4",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "005872c7",
      "instruction": "JZ 0x00587404"
    },
    {
      "address": "005872cd",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "005872d0",
      "instruction": "JNZ 0x00587460"
    },
    {
      "address": "005872d6",
      "instruction": "MOV EAX,dword ptr [EBP + 0x278]"
    },
    {
      "address": "005872dc",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005872dd",
      "instruction": "CALL 0x00401050"
    },
    {
      "address": "005872e2",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005872e4",
      "instruction": "CALL 0x0045b210"
    },
    {
      "address": "005872e9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005872eb",
      "instruction": "JZ 0x00587300"
    },
    {
      "address": "005872ed",
      "instruction": "MOV ECX,dword ptr [EBP + 0x278]"
    },
    {
      "address": "005872f3",
      "instruction": "PUSH ECX"
    },
    {
      "address": "005872f4",
      "instruction": "CALL 0x00401050"
    },
    {
      "address": "005872f9",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005872fb",
      "instruction": "CALL 0x0045b150"
    },
    {
      "address": "00587300",
      "instruction": "MOV EAX,dword ptr [EBP + 0x27c]"
    },
    {
      "address": "00587306",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00587308",
      "instruction": "JZ 0x00587319"
    },
    {
      "address": "0058730a",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "0058730c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0058730d",
      "instruction": "CALL 0x00401050"
    },
    {
      "address": "00587312",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00587314",
      "instruction": "CALL 0x0045ae10"
    },
    {
      "address": "00587319",
      "instruction": "MOV EAX,dword ptr [EBP + 0xa4]"
    },
    {
      "address": "0058731f",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00587321",
      "instruction": "JZ 0x0058733f"
    },
    {
      "address": "00587323",
      "instruction": "LEA EDI,[EAX + 0x1c]"
    },
    {
      "address": "00587326",
      "instruction": "MOV ECX,0x9"
    },
    {
      "address": "0058732b",
      "instruction": "MOV ESI,0x15e505c"
    },
    {
      "address": "00587330",
      "instruction": "MOVSD.REP ES:EDI,ESI"
    },
    {
      "address": "00587332",
      "instruction": "OR word ptr [EAX + 0x8],0x2"
    },
    {
      "address": "00587337",
      "instruction": "INC word ptr [EAX + 0xa]"
    },
    {
      "address": "0058733b",
      "instruction": "MOV EDI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "0058733f",
      "instruction": "MOV ECX,dword ptr [EBP + 0x7c]"
    },
    {
      "address": "00587342",
      "instruction": "CALL 0x0062c340"
    },
    {
      "address": "00587347",
      "instruction": "MOV EAX,dword ptr [EBP + 0xa8]"
    },
    {
      "address": "0058734d",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "0058734f",
      "instruction": "JZ 0x00587355"
    },
    {
      "address": "00587351",
      "instruction": "OR dword ptr [EAX + 0x4],0x1"
    },
    {
      "address": "00587355",
      "instruction": "PU
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
  "original_bytes": 11289,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"return_type\": \"bool\",\n    \"stack_arguments\": [\n      {\n        \"abi_type\": \"std::uint32_t\",\n        \"entry_offset\": \"ESP+4\",\n        \"name\": \"mode\",\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+8\",\n        \"name\": \"flag\",\n        \"observed_values\": [\n          0,\n          1\n        ],\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-PERSISTENCE-BOUNDARY\",\n      \"score\": 5,\n      \"symbol\": \"PaintPersistenceBoundary_submit_004c5200\",\n      \"va\": \"0x004c5200\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 5,\n      \"symbol\": \"FUN_005dda30\",\n      \"va\": \"0x005dda30\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n      \"va\": \"0x0059cea0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n      \"va\": \"0x0059cf00\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"editor_anim_event_message_send_0059d8b0\",\n      \"va\": \"0x0059d8b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"Ghidra's current return type is void even though both assembly exits set AL to 0 or 1.\",\n    \"The package declaration uses the neutral OpaqueEditor type and the raw ABI width.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0045ae10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0045b150\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0045b210\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004c49e0\"\n      },\n      {\n        \"name\": \"PaintPersistenceBoundary_submit_004c5200\",\n        \"reconstructed\": true,\n        \"va\": \"0x004c5200\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573d70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005772b0\"\n      },\n      {\n        \"name\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059cac0\"\n      },\n      {\n        \"name\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059cea0\"\n      },\n      {\n        \"name\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059cf00\"\n      },\n      {\n        \"name\": \"editor_anim_event_message_send_0059d8b0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059d8b0\"\n      },\n      {\n        \"name\": \"cEditorAnimEvent__ctor\",\n        \"reconstructed\": false,\n        \"va\": \"0x0059d960\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"Editors::cEditor::OnExit\",\n        \"reconstructed\": false,\n        \"va\": \"0x00587a20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0058a350\"\n      },\n      {\n        \"name\": \"Editors::cEditor::HandleMessage\",\n        \"reconstructed\": false,\n        \"va\": \"0x00591fa0\"\n      },\n      {\n        \"name\": \"FUN_005dda30\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dda30\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00587c8a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00587a20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058a42d\",\n        \"direction\": \"in\",\n        \"other\": \"0x0058a350\",\n        \"reference_type\": \"direct-call\"\n      },\n    
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
  "body_end": "00587a16",
  "body_span_bytes": 1959,
  "body_start": "00587270",
  "callees": [
    "FUN_004c49e0",
    "FUN_004c4630",
    "FUN_004c5200",
    "FUN_0062c340",
    "FUN_00573390",
    "FUN_0043a9a0",
    "FUN_00573d70",
    "FUN_005794b0",
    "FUN_0059cf60",
    "FUN_0062bf10",
    "Editors::cEditorAnimWorld::DestroyCreature",
    "FUN_00401050",
    "FUN_00576140",
    "Editors::cEditorAnimEvent::MessageSend",
    "App::IAppSystem::Get",
    "FUN_00586960",
    "FUN_004c4650",
    "FUN_004accf0",
    "FUN_00435f40",
    "FUN_0057e340",
    "FUN_00f473a0",
    "cEditorAnimEvent__ctor",
    "FUN_004accb0",
    "FUN_0045b150",
    "FUN_0059aea0",
    "FUN_005772b0",
    "FUN_00a04550",
    "FUN_005dbb60",
    "FUN_0043a830",
    "FUN_00573c00",
    "FUN_0045ae10",
    "Editors::cEditorAnimWorld::SetTargetAngle",
    "FUN_0047e6c0",
    "Editors::cEditorAnimWorld::SetTargetPosition",
    "Editors::cEditorAnimWorld::GetCreatureController",
    "FUN_005744b0",
    "FUN_00573330",
    "FUN_0045b210",
    "FUN_004c58b0",
    "FUN_0046bfd0",
    "FUN_004adca0",
    "FUN_0043a5e0",
    "Editors::cEditor::AddCreature"
  ],
  "callers": [
    "FUN_0058a350",
    "Editors::cEditor::OnExit",
    "Editors::cEditor::HandleMessage",
    "FUN_005dda30"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00587270",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
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
      "name": "local_44",
      "storage": "Stack[-0x44]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 8,
  "mode": "live",
  "name": "Editors::cEditor::SetActiveMode",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cEditor *"
    },
    {
      "name": "mode",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "Mode"
    },
    {
      "name": "param_3",
      "ordinal": 2,
      "storage": "Stack[0xc]:1",
      "type": "bool"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x187270",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Editors::cEditor::SetActiveMode(cEditor * this, Mode mode, bool param_3)",
  "size_bytes": 1959,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00587270",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "005dda5e"
    },
    {
      "from": "00587c8a"
    },
    {
      "from": "0058a42d"
    },
    {
      "from": "005925a0"
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
  "files": [],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/00587270.json"
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueEditor for ECX",
  "OpaqueEditorModeManager for the caller-owned this+0x5c relationship",
  "bool",
  "std::uint32_t",
  "std::uint32_t for the first stack argument",
  "uint32_t"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
{
  "original_bytes": 17652,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00587270\",\n      \"0x0059d840\",\n      \"0x0059d8b0\",\n      \"0x00587270\",\n      \"0x0059d8b0\",\n      \"0x0059d840\",\n      \"0x00573970\",\n      \"0x00573970\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00587270\",\n      \"0x00587270\",\n      \"0x0059d840\",\n      \"0x0059d840\",\n      \"0x0059d8b0\",\n      \"0x0059d8b0\"\n    ],\n    \"conflict_id\": \"Q-ANIMATION-DISPATCH\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Editor animation Send/Post surfaces and the editor mode producer are concrete. The final AnimatedCreature/IAnimWorld consumer and pose ordering are unresolved.\",\n    \"resolution_status\": \"Editor animation Send/Post surfaces and the editor mode producer are concrete. The final AnimatedCreature/IAnimWorld consumer and pose ordering are unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00591fa0\",\n      \"0x00883a90\",\n      \"0x00883ad0\",\n      \"0x00883ad0\",\n      \"0x00883a90\",\n      \"0x00591fa0\",\n      \"0x00573970\",\n      \"0x00573970\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00587270\",\n      \"0x00587270\",\n      \"0x0059d840\",\n      \"0x0059d840\",\n      \"0x0059d8b0\",\n      \"0x0059d8b0\"\n    ],\n    \"conflict_id\": \"Q-EDITOR-MESSAGE-CATALOG\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.\",\n    \"resolution_status\": \"The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-001-mission-transitions\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"resolution_status\": \"Mission enum/field surface is known, but no complete direct writer and callback body establishes each transition. SDK contract is not promoted to native order.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00d2e4a0\",\n      \"0x00d2e4a0\",\n      \"0x00aeb7b0\",\n      \"0x005737d0\",\n      \"0x005737d0\",\n      \"0x00585d10\",\n      \"0x00585d10\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\",\n      \"0x00587270\",\n      \"0x00588570\",\n      \"0x00588570\",\n      \"0x0058a5a0\"\n    ],\n    \"conflict_id\": \"U-002-tribe-plans\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"resolution_status\": \"The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00582fe0\",\n      \"0x00587270\",\n      \"0x0059c830\",\n      \"0x0059c830\",\n      \"0x00576c50\",\n      \"0x00576c50\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00584300\",\n      \"0x00584300\",\n      \"0x00586410\",\n      \"0x00586410\",\n      \"0x00586b00\",\n      \"0x00586b00\",\n      \"0x00587270\"\n    ],\n    \"conflict_id\": \"U-006-editor-world-slot-conflict\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The +0x36
[TRUNCATED]
```
