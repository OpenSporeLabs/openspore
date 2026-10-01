# Evidence 0x00c474b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `dc3ceb5ddeb149f6da7b8bb5b9c943b1b70dd12dc1a5ec50afe2b00f59d2b72f`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x14"
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0x14; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0x14 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "5c290fa518a60539f22241292338b40018ce17f106db91276386deac004f0376",
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
    "ghidra_parameter_count": 0,
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
        "obs-0020",
        "obs-0028",
        "obs-0048",
        "obs-0057",
        "obs-0068",
        "obs-0081"
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
        "obs-0020",
        "obs-0028",
        "obs-0048",
        "obs-0057",
        "obs-0068",
        "obs-0081"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 4,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0035"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 3,
        "observed_slots": 2,
        "total_bytes": 20
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0019",
        "obs-0027",
        "obs-0029",
        "obs-0038",
        "obs-0047",
        "obs-0056",
        "obs-0065",
        "obs-0067",
        "obs-0080"
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
        "obs-0007"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0020",
        "obs-0028",
        "obs-0048",
        "obs-0057",
        "obs-0068",
        "obs-0081"
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
        "obs-0020",
        "obs-0028",
        "obs-0048",
        "obs-0057",
        "obs-0068",
        "obs-0081"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020",
        "obs-0028",
        "obs-0048",
        "obs-0057",
        "obs-0068",
        "obs-0081"
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
      "at": "0x00c474b0",
      "count": 6,
      "first_use": 0,
      "first_write_index": 31,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "reg": "ECX"
    },
    {
      "at": "0x00c474b1",
      "count": 12,
      "first_use": 1,
      "first_write_index": 110,
      "id": "obs-0
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
      "entry_ESP+0x4",
      "entry_ESP+0x14"
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0x14; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0x14 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "5c290fa518a60539f22241292338b40018ce17f106db91276386deac004f0376",
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
    "ghidra_parameter_count": 0,
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
        "obs-0020",
        "obs-0028",
        "obs-0048",
        "obs-0057",
        "obs-0068",
        "obs-0081"
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
        "obs-0020",
        "obs-0028",
        "obs-0048",
        "obs-0057",
        "obs-0068",
        "obs-0081"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 4,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0035"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 3,
        "observed_slots": 2,
        "total_bytes": 20
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0019",
        "obs-0027",
        "obs-0029",
        "obs-0038",
        "obs-0047",
        "obs-0056",
        "obs-0065",
        "obs-0067",
        "obs-0080"
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
        "obs-0007"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0020",
        "obs-0028",
        "obs-0048",
        "obs-0057",
        "obs-0068",
        "obs-0081"
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
        "obs-0020",
        "obs-0028",
        "obs-0048",
        "obs-0057",
        "obs-0068",
        "obs-0081"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020",
        "obs-0028",
        "obs-0048",
        "obs-0057",
        "obs-0068",
        "obs-0081"
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
      "at": "0x00c474b0",
      "count": 6,
      "first_use": 0,
      "first_write_index": 31,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "reg": "ECX"
    },
    {
      "at": "0x00c474b1",
      "count": 12,
      "first_use": 1,
      "first_write_index": 110,
      "id": "obs-0
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
  "count": 130,
  "instructions": [
    {
      "address": "00c474b0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c474b1",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c474b5",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c474b6",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c474b7",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00c474b9",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c474ba",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c474bb",
      "instruction": "MOV dword ptr [ESP + 0x10],EBX"
    },
    {
      "address": "00c474bf",
      "instruction": "CMP EAX,0x8e718b32"
    },
    {
      "address": "00c474c4",
      "instruction": "JNZ 0x00c474d7"
    },
    {
      "address": "00c474c6",
      "instruction": "CALL 0x01021370"
    },
    {
      "address": "00c474cb",
      "instruction": "POP EDI"
    },
    {
      "address": "00c474cc",
      "instruction": "POP ESI"
    },
    {
      "address": "00c474cd",
      "instruction": "POP EBP"
    },
    {
      "address": "00c474ce",
      "instruction": "MOV dword ptr [ESP + 0x4],EAX"
    },
    {
      "address": "00c474d2",
      "instruction": "POP EBX"
    },
    {
      "address": "00c474d3",
      "instruction": "POP ECX"
    },
    {
      "address": "00c474d4",
      "instruction": "RET 0x4"
    },
    {
      "address": "00c474d7",
      "instruction": "CMP EAX,0xa8169426"
    },
    {
      "address": "00c474dc",
      "instruction": "JNZ 0x00c4756f"
    },
    {
      "address": "00c474e2",
      "instruction": "CALL 0x01021260"
    },
    {
      "address": "00c474e7",
      "instruction": "CALL 0x01021230"
    },
    {
      "address": "00c474ec",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00c474ee",
      "instruction": "JNZ 0x00c474fa"
    },
    {
      "address": "00c474f0",
      "instruction": "POP EDI"
    },
    {
      "address": "00c474f1",
      "instruction": "POP ESI"
    },
    {
      "address": "00c474f2",
      "instruction": "POP EBP"
    },
    {
      "address": "00c474f3",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00c474f5",
      "instruction": "POP EBX"
    },
    {
      "address": "00c474f6",
      "instruction": "POP ECX"
    },
    {
      "address": "00c474f7",
      "instruction": "RET 0x4"
    },
    {
      "address": "00c474fa",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c474fc",
      "instruction": "CALL 0x00c8b770"
    },
    {
      "address": "00c47501",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "00c47503",
      "instruction": "CMP EBP,EBX"
    },
    {
      "address": "00c47505",
      "instruction": "JZ 0x00c47602"
    },
    {
      "address": "00c4750b",
      "instruction": "MOV EDI,dword ptr [EBP + 0x14]"
    },
    {
      "address": "00c4750e",
      "instruction": "SUB EDI,dword ptr [EBP + 0x10]"
    },
    {
      "address": "00c47511",
      "instruction": "SAR EDI,0x2"
    },
    {
      "address": "00c47514",
      "instruction": "CMP EDI,EBX"
    },
    {
      "address": "00c47516",
      "instruction": "JLE 0x00c47602"
    },
    {
      "address": "00c4751c",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "00c47520",
      "instruction": "MOV EAX,dword ptr [EBP + 0x10]"
    },
    {
      "address": "00c47523",
      "instruction": "MOV ESI,dword ptr [EAX + EBX*0x4]"
    },
    {
      "address": "00c47526",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c47528",
      "instruction": "JZ 0x00c4754a"
    },
    {
      "address": "00c4752a",
      "instruction": "MOV ECX,dword ptr [ESI + 0x13c]"
    },
    {
      "address": "00c47530",
      "instruction": "MOV dword ptr [ESP + 0x18],ECX"
    },
    {
      "address": "00c47534",
      "instruction": "CALL 0x01021370"
    },
    {
      "address": "00c47539",
      "instruction": "CMP dword ptr [ESP + 0x18],EAX"
    },
    {
      "address": "00c4753d",
      "instruction": "JZ 0x00c4754a"
    },
    {
      "address": "00c4753f",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c47541",
      "instruction": "CALL 0x00c70fb0"
    },
    {
      "address": "00c47546",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c47548",
      "instruction": "JG 0x00c4755b"
    },
    {
      "address": "00c4754a",
      "instruction": "INC EBX"
    },
    {
      "address": "00c4754b",
      "instruction": "CMP EBX,EDI"
    },
    {
      "address": "00c4754d",
      "instruction": "JL 0x00c47520"
    },
    {
      "address": "00c4754f",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c47553",
      "instruction": "POP EDI"
    },
    {
      "address": "00c47554",
      "instruction": "POP ESI"
    },
    {
      "address": "00c47555",
      "instruction": "POP EBP"
    },
    {
      "address": "00c47556",
      "instruction": "POP EBX"
    },
    {
      "address": "00c47557",
      "instruction": "POP ECX"
    },
    {
      "address": "00c47558",
      "instruction": "RET 0x4"
    },
    {
      "address": "00c4755b",
      "instruction": "MOV EDX,dword ptr [ESI + 0x13c]"
    },
    {
      "address": "00c47561",
      "instruction": "POP EDI"
    },
    {
      "address": "00c47562",
      "instruction": "POP ESI"
    },
    {
      "address": "00c47563",
      "instruction": "POP EBP"
    },
    {
      "address": "00c47564",
      "instruction": "MOV dword ptr [ESP + 0x4],EDX"
    },
    {
      "address": "00c47568",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "00c4756a",
      "instruction": "POP EBX"
    },
    {
      "address": "00c4756b",
      "instruction": "POP ECX"
    },
    {
      "address": "00c4756c",
      "instruction": "RET 0x4"
    },
    {
      "address": "00c4756f",
      "instruction": "CMP EAX,0
[TRUNCATED]
```

## external_callees

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## function_identity

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "00c4760d",
  "body_span_bytes": 350,
  "body_start": "00c474b0",
  "callees": [
    "FUN_01021230",
    "FUN_00febdc0",
    "FUN_00ba6dc0",
    "FUN_00feb9f0",
    "FUN_00aed3f0",
    "FUN_01021260",
    "FUN_00c70fb0",
    "FUN_00c59fb0",
    "FUN_00b3d2a0",
    "FUN_00c8b770",
    "FUN_01021370"
  ],
  "callers": [
    "FUN_00c51010",
    "FUN_00c557c0",
    "FUN_00c60e90",
    "FUN_00c63380",
    "FUN_00c4f4e0",
    "FUN_00c5ea60",
    "FUN_00c4b7f0",
    "FUN_00c54380",
    "FUN_00c4e440"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c474b0",
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
      "name": "local_14",
      "storage": "Stack[-0x14]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00c474b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8474b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c474b0(void)",
  "size_bytes": 350,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c474b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 9,
  "xrefs": [
    {
      "from": "00c4b861"
    },
    {
      "from": "00c4e48c"
    },
    {
      "from": "00c4f5ec"
    },
    {
      "from": "00c511aa"
    },
    {
      "from": "00c543fe"
    },
    {
      "from": "00c557cb"
    },
    {
      "from": "00c5ea7d"
    },
    {
      "from": "00c60eb8"
    },
    {
      "from": "00c633ef"
    }
  ]
}
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
[]
```
