# Evidence 0x00676710

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `86efef20f7e58e70c8fa59e8ec9b21f278768864501dad70ed048672a0bad303`

## abi

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
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "5f66bf4b4a93696031f5908e1091b9f77878d47d3549aab624229644ad665d21",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0048",
        "obs-0053"
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
        "obs-0005",
        "obs-0022"
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
        "obs-0017",
        "obs-0023",
        "obs-0028",
        "obs-0029",
        "obs-0034",
        "obs-0040"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          8,
          36
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010",
        "obs-0017",
        "obs-0023",
        "obs-0028",
        "obs-0029",
        "obs-0034",
        "obs-0040",
        "obs-0048",
        "obs-0053"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0048",
        "obs-0053"
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
        "obs-0048",
        "obs-0053"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0048",
        "obs-0053"
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
      "and_esp": null,
      "at": "0x00676710",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 3,
      "raw": "SUB ESP,0x20",
      "sub": 32
    },
    {
      "at": "0x00676710",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x20",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00676713",
      "count": 2,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00676714",
      "count": 15,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x28]",
      "reg": "ESP"
    },
    {
      "at": "0x00676714",
      "base": "ESP",
      "disp": 40,
      "id": "obs-0005",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x28]",
      "resolved": true,
      "size": 4,
      "trust": "untrusted_frame"
    },
    {
      "at": "0x00676714",
      "definite": true,
      "id": "obs-0006",
      "i
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
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "5f66bf4b4a93696031f5908e1091b9f77878d47d3549aab624229644ad665d21",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0048",
        "obs-0053"
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
        "obs-0005",
        "obs-0022"
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
        "obs-0017",
        "obs-0023",
        "obs-0028",
        "obs-0029",
        "obs-0034",
        "obs-0040"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          8,
          36
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010",
        "obs-0017",
        "obs-0023",
        "obs-0028",
        "obs-0029",
        "obs-0034",
        "obs-0040",
        "obs-0048",
        "obs-0053"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0048",
        "obs-0053"
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
        "obs-0048",
        "obs-0053"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0048",
        "obs-0053"
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
      "and_esp": null,
      "at": "0x00676710",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 3,
      "raw": "SUB ESP,0x20",
      "sub": 32
    },
    {
      "at": "0x00676710",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x20",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00676713",
      "count": 2,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00676714",
      "count": 15,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x28]",
      "reg": "ESP"
    },
    {
      "at": "0x00676714",
      "base": "ESP",
      "disp": 40,
      "id": "obs-0005",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x28]",
      "resolved": true,
      "size": 4,
      "trust": "untrusted_frame"
    },
    {
      "at": "0x00676714",
      "definite": true,
      "id": "obs-0006",
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
    "name": "editor_query_clear_flags_0093db80",
    "reconstructed": true,
    "va": "0x0093db80"
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
    "name": "achievement_progress_update_00676e90",
    "reconstructed": true,
    "va": "0x00676e90"
  },
  {
    "name": "achievement_progress_flag_transition_00676ed0",
    "reconstructed": true,
    "va": "0x00676ed0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00676f20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00676f60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be41b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bff2d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4b310"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cd8e70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cdbd20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cf7630"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d2b5f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d2e580"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d3cdc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d54330"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00db5e80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00de5260"
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
      "0x00676c80",
      "0x00677140",
      "0x007e6470",
      "0x0212d3e7",
      "0x00676c80",
      "0x0212d3e7",
      "0x00675d70",
      "0x00675d70",
      "0x00676710",
      "0x00676660",
      "0x00676710",
      "0x00676660",
      "0x00676c80",
      "0x00676c80",
      "0x00676c80",
      "0x00677140"
    ],
    "conflict_id": "shutdown_message_semantics",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "PreShutdown dispatches 0x0212d3e7 and an achievement listener observes it, but the message semantic role and cross-game persistence write are not proven.",
    "resolution_status": "PreShutdown dispatches 0x0212d3e7 and an achievement listener observes it, but the message semantic role and cross-game persistence write are not proven.",
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
  "count": 91,
  "instructions": [
    {
      "address": "00676710",
      "instruction": "SUB ESP,0x20"
    },
    {
      "address": "00676713",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00676714",
      "instruction": "MOV EBX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00676718",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00676719",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0067671a",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "0067671c",
      "instruction": "MOV ESI,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0067671f",
      "instruction": "MOVZX EAX,byte ptr [ESI + 0x38]"
    },
    {
      "address": "00676723",
      "instruction": "MOV EDX,dword ptr [ESI + 0x24]"
    },
    {
      "address": "00676726",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00676727",
      "instruction": "MOV EDI,dword ptr [ESI + 0x28]"
    },
    {
      "address": "0067672a",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0067672b",
      "instruction": "LEA ECX,[ESP + 0x18]"
    },
    {
      "address": "0067672f",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00676730",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00676731",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00676732",
      "instruction": "MOV dword ptr [ESP + 0x24],EBX"
    },
    {
      "address": "00676736",
      "instruction": "CALL 0x00555a20"
    },
    {
      "address": "0067673b",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "0067673e",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00676740",
      "instruction": "JZ 0x0067674f"
    },
    {
      "address": "00676742",
      "instruction": "CMP EBX,dword ptr [EAX]"
    },
    {
      "address": "00676744",
      "instruction": "JC 0x0067674f"
    },
    {
      "address": "00676746",
      "instruction": "LEA ECX,[EAX + 0x4]"
    },
    {
      "address": "00676749",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "0067674b",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "0067674d",
      "instruction": "JNZ 0x00676751"
    },
    {
      "address": "0067674f",
      "instruction": "MOV EBX,EDI"
    },
    {
      "address": "00676751",
      "instruction": "CMP byte ptr [EBP + 0x24],0x0"
    },
    {
      "address": "00676755",
      "instruction": "JNZ 0x006767fd"
    },
    {
      "address": "0067675b",
      "instruction": "LEA EAX,[ESP + 0x34]"
    },
    {
      "address": "0067675f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00676760",
      "instruction": "LEA ECX,[ESP + 0x18]"
    },
    {
      "address": "00676764",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00676765",
      "instruction": "LEA ECX,[ESI + 0x24]"
    },
    {
      "address": "00676768",
      "instruction": "CALL 0x00554020"
    },
    {
      "address": "0067676d",
      "instruction": "MOV AL,byte ptr [EAX + 0x4]"
    },
    {
      "address": "00676770",
      "instruction": "MOV byte ptr [ESP + 0x13],AL"
    },
    {
      "address": "00676774",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00676776",
      "instruction": "JZ 0x006767ff"
    },
    {
      "address": "0067677c",
      "instruction": "CMP EBX,EDI"
    },
    {
      "address": "0067677e",
      "instruction": "JNZ 0x0067679e"
    },
    {
      "address": "00676780",
      "instruction": "CALL 0x00883860"
    },
    {
      "address": "00676785",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00676787",
      "instruction": "JZ 0x0067679e"
    },
    {
      "address": "00676789",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "0067678b",
      "instruction": "MOV EDX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "0067678e",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00676790",
      "instruction": "LEA ECX,[ESP + 0x38]"
    },
    {
      "address": "00676794",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00676795",
      "instruction": "PUSH 0x5c6930e"
    },
    {
      "address": "0067679a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0067679c",
      "instruction": "CALL EDX"
    },
    {
      "address": "0067679e",
      "instruction": "CALL 0x0061df20"
    },
    {
      "address": "006767a3",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "006767a5",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "006767a7",
      "instruction": "JZ 0x006767e8"
    },
    {
      "address": "006767a9",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "006767ab",
      "instruction": "LEA EDX,[ESP + 0x34]"
    },
    {
      "address": "006767af",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "006767b1",
      "instruction": "MOV word ptr [ESP + 0x2e],CX"
    },
    {
      "address": "006767b6",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006767b7",
      "instruction": "LEA ECX,[ESP + 0x20]"
    },
    {
      "address": "006767bb",
      "instruction": "MOV word ptr [ESP + 0x30],AX"
    },
    {
      "address": "006767c0",
      "instruction": "CALL 0x00427fd0"
    },
    {
      "address": "006767c5",
      "instruction": "LEA EAX,[ESP + 0x1c]"
    },
    {
      "address": "006767c9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006767ca",
      "instruction": "PUSH 0x1edc82b0"
    },
    {
      "address": "006767cf",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "006767d1",
      "instruction": "CALL 0x0061fdb0"
    },
    {
      "address": "006767d6",
      "instruction": "TEST byte ptr [ESP + 0x2c],0x4"
    },
    {
      "address": "006767db",
      "instruction": "JZ 0x006767e8"
    },
    {
      "address": "006767dd",
      "instruction": "PUSH 0x0"
 
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
  "original_bytes": 13197,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:AchievementManagerWire,std::uint8_t gate\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\",\n      \"score\": 28,\n      \"symbol\": \"achievement_progress_flag_transition_00676ed0\",\n      \"va\": \"0x00676ed0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:AchievementManagerWire\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-A2-PROGRESSION-ALTERNATIVE\",\n      \"score\": 17,\n      \"symbol\": \"achievement_progress_update_00676e90\",\n      \"va\": \"0x00676e90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"mission_manager_record_init_00fec3c0\",\n      \"va\": \"0x00fec3c0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"editor_query_clear_flags_0093db80\",\n      \"va\": \"0x0093db80\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"No original-process achievement trace was run.\",\n    \"Record ownership inside 0x00555a20, 0x00554020 and 0x00676660 remains with other packages.\",\n    \"The four call sites with no enclosing function (0x0067702d, 0x0067711d, 0x00de93e8, 0x0100c766) are unreconciled.\",\n    \"The two constant event identifiers 0x05c6930e and 0x01edc82b0 have no SDK binding and remain opaque hashes.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"AchievementManagerWire\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"editor_query_clear_flags_0093db80\",\n        \"reconstructed\": true,\n        \"va\": \"0x0093db80\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"achievement_progress_update_00676e90\",\n        \"reconstructed\": true,\n        \"va\": \"0x00676e90\"\n      },\n      {\n        \"name\": \"achievement_progress_flag_transition_00676ed0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00676ed0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00676f20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00676f60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be41b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bff2d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4b310\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd8e70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cdbd20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cf7630\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2b5f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2e580\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d3cdc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d54330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00db5e80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00de5260\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e2f6e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e82d10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e848c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ec5160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f16580\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdbf90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fde3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe5a20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01005d80\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00676ebf\",\n        \"direction\": \"in\",\n        \"other\": \"0x00676e90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00676f11\",\n        \"direction\": \"in\",\n        \"other\": \"0x00676ed0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00676f4e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00676f20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00676faf\",\n        \"direction\": \"in\",\n        \"other\": \"0x0067
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
  "body_end": "00676808",
  "body_span_bytes": 249,
  "body_start": "00676710",
  "callees": [
    "FUN_00555a20",
    "FUN_00427fd0",
    "FUN_00554020",
    "FUN_00883860",
    "FUN_0061fdb0",
    "FUN_0093db80",
    "FUN_0061df20",
    "FUN_006754d0"
  ],
  "callers": [
    "FUN_00fdbf90",
    "FUN_00fde3e0",
    "FUN_00e82d10",
    "FUN_00e2f6e0",
    "FUN_00cf7630",
    "FUN_01005d80",
    "FUN_00d3cdc0",
    "FUN_00bff2d0",
    "FUN_00de5260",
    "FUN_00d54330",
    "FUN_00d2b5f0",
    "FUN_00676f60",
    "Simulator::cCreatureGameData::AfterGlideFinish",
    "FUN_00fe5a20",
    "FUN_00c4b310",
    "FUN_00cdbd20",
    "FUN_00db5e80",
    "FUN_00676ed0",
    "FUN_00be41b0",
    "FUN_00f16580",
    "Pollinator::cAchievementsManager::SetProgressFlags",
    "FUN_00cd8e70",
    "FUN_00e848c0",
    "FUN_00ec5160",
    "FUN_00676f20"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00676710",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_2",
      "storage": "Stack[-0x2]:2",
      "type": "undefined2"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:2",
      "type": "undefined2"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:1",
      "type": "undefined"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_1d",
      "storage": "Stack[-0x1d]:1",
      "type": "undefined1"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_00676710",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x276710",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00676710(void)",
  "size_bytes": 249,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00676710",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 43,
  "xrefs": [
    {
      "from": "00676ebf"
    },
    {
      "from": "00676f11"
    },
    {
      "from": "00676f4e"
    },
    {
      "from": "00676faf"
    },
    {
      "from": "00cf76bc"
    },
    {
      "from": "00cf76e4"
    },
    {
      "from": "00cf7708"
    },
    {
      "from": "00e2f8e8"
    },
    {
      "from": "00bff46a"
    },
    {
      "from": "00fdc09f"
    },
    {
      "from": "00fde928"
    },
    {
      "from": "00fde9f5"
    },
    {
      "from": "00be43eb"
    },
    {
      "from": "00d3cf5a"
    },
    {
      "from": "00d3d019"
    },
    {
      "from": "00c4b384"
    },
    {
      "from": "01005f2c"
    },
    {
      "from": "0100606f"
    },
    {
      "from": "010060c0"
    },
    {
      "from": "00cd9178"
    },
    {
      "from": "00cdc35d"
    },
    {
      "from": "00cdc3b5"
    },
    {
      "from": "00cdc3ed"
    },
    {
      "from": "00d2e6d7"
    },
    {
      "from": "00d5467c"
    },
    {
      "from": "00db605f"
    },
    {
      "from": "00de52af"
    },
    {
      "from": "00e82d1c"
    },
    {
      "from": "00e84931"
    },
    {
      "from": "00ec517c"
    },
    {
      "from": "00f166cf"
    },
    {
      "from": "00fe60a3"
    },
    {
      "from": "00fe6196"
    },
    {
      "from": "0067702d"
    },
    {
      "from": "0067711d"
    },
    {
      "from": "00d2b5ff"
    },
    {
      "from": "00d2b61b"
    },
    {
      "from": "00d2b637"
    },
    {
      "from": "00d2b653"
    },
    {
      "from": "00d2b66f"
    },
    {
      "from": "00d2b6a1"
    },
    {
      "from": "00de93e8"
    },
    {
      "from": "0100c766"
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
  "file": "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.cpp",
    "reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.hpp",
    "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.cpp",
    "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.hpp",
    "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-a3-achievement-mission-wave2/00676710.json"
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
    "gate-achievement-completion-00676710",
    "runtime validation not run"
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
  "AchievementManagerWire",
  "Opaque sorted range begin",
  "Opaque sorted range end",
  "serializer pointer",
  "std::uint32_t",
  "std::uint8_t gate",
  "std::uint8_t tag"
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
      "0x00676c80",
      "0x00677140",
      "0x007e6470",
      "0x0212d3e7",
      "0x00676c80",
      "0x0212d3e7",
      "0x00675d70",
      "0x00675d70",
      "0x00676710",
      "0x00676660",
      "0x00676710",
      "0x00676660",
      "0x00676c80",
      "0x00676c80",
      "0x00676c80",
      "0x00677140"
    ],
    "conflict_id": "shutdown_message_semantics",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "PreShutdown dispatches 0x0212d3e7 and an achievement listener observes it, but the message semantic role and cross-game persistence write are not proven.",
    "resolution_status": "PreShutdown dispatches 0x0212d3e7 and an achievement listener observes it, but the message semantic role and cross-game persistence write are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
