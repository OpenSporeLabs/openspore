# Evidence 0x00e3a730

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `197c6450293a06a520876a36cef24cc6cfad46821635920c89aafbff079c359d`

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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
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
    "flow_not_modelled: the linear ESP walk ends at +72, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_width_ambiguous: one entry slot is read at more than one width"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "51fe80031be273663051612223d46996f9710052c6b3056f10c534ed32e1088d",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0060"
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
        "obs-0017",
        "obs-0020"
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
        "obs-0017",
        "obs-0020"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0011",
        "obs-0012",
        "obs-0024",
        "obs-0037"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          48,
          392,
          408,
          480
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0011",
        "obs-0012",
        "obs-0024",
        "obs-0037",
        "obs-0060"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0060"
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
        "obs-0060"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0060"
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
      "and_esp": null,
      "at": "0x00e3a730",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00e3a730",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00e3a733",
      "count": 9,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00e3a734",
      "count": 11,
      "first_use": 2,
      "first_write_index": 12,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00e3a735",
      "count": 13,
      "first_use": 3,
      "first_write_index": 6,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
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
    "flow_not_modelled: the linear ESP walk ends at +72, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_width_ambiguous: one entry slot is read at more than one width"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "51fe80031be273663051612223d46996f9710052c6b3056f10c534ed32e1088d",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0060"
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
        "obs-0017",
        "obs-0020"
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
        "obs-0017",
        "obs-0020"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0011",
        "obs-0012",
        "obs-0024",
        "obs-0037"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          48,
          392,
          408,
          480
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0011",
        "obs-0012",
        "obs-0024",
        "obs-0037",
        "obs-0060"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0060"
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
        "obs-0060"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0060"
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
      "and_esp": null,
      "at": "0x00e3a730",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00e3a730",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00e3a733",
      "count": 9,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00e3a734",
      "count": 11,
      "first_use": 2,
      "first_write_index": 12,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00e3a735",
      "count": 13,
      "first_use": 3,
      "first_write_index": 6,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG
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
  "count": 146,
  "instructions": [
    {
      "address": "00e3a730",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "00e3a733",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e3a734",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00e3a735",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e3a736",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e3a737",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00e3a739",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00e3a73b",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00e3a740",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e3a742",
      "instruction": "CALL 0x00f67d90"
    },
    {
      "address": "00e3a747",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00e3a749",
      "instruction": "CMP dword ptr [EBX + 0x1e0],0x2b978c46"
    },
    {
      "address": "00e3a753",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "00e3a755",
      "instruction": "JNZ 0x00e3a767"
    },
    {
      "address": "00e3a757",
      "instruction": "MOV EAX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00e3a75b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e3a75c",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00e3a75e",
      "instruction": "CALL 0x00c756e0"
    },
    {
      "address": "00e3a763",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00e3a765",
      "instruction": "JMP 0x00e3a77a"
    },
    {
      "address": "00e3a767",
      "instruction": "MOV ECX,dword ptr [EBX + 0x188]"
    },
    {
      "address": "00e3a76d",
      "instruction": "MOV EAX,dword ptr [ECX + -0x4]"
    },
    {
      "address": "00e3a770",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e3a772",
      "instruction": "JZ 0x00e3a77a"
    },
    {
      "address": "00e3a774",
      "instruction": "MOV EDI,dword ptr [EAX + 0xf0]"
    },
    {
      "address": "00e3a77a",
      "instruction": "CMP byte ptr [ESP + 0x28],0x0"
    },
    {
      "address": "00e3a77f",
      "instruction": "JZ 0x00e3a7ab"
    },
    {
      "address": "00e3a781",
      "instruction": "MOV EAX,dword ptr [EBP + 0x1108]"
    },
    {
      "address": "00e3a787",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e3a789",
      "instruction": "JZ 0x00e3a7ab"
    },
    {
      "address": "00e3a78b",
      "instruction": "MOV EDX,dword ptr [EBP + 0x1104]"
    },
    {
      "address": "00e3a791",
      "instruction": "MOV ECX,dword ptr [EBP + 0x10fc]"
    },
    {
      "address": "00e3a797",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e3a798",
      "instruction": "MOV EAX,dword ptr [EBP + 0x1100]"
    },
    {
      "address": "00e3a79e",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e3a79f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e3a7a0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e3a7a1",
      "instruction": "CALL 0x00556440"
    },
    {
      "address": "00e3a7a6",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00e3a7a9",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00e3a7ab",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00e3a7ad",
      "instruction": "JZ 0x00e3a8d5"
    },
    {
      "address": "00e3a7b3",
      "instruction": "MOV EDX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00e3a7b7",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e3a7b8",
      "instruction": "CALL 0x00e36f50"
    },
    {
      "address": "00e3a7bd",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e3a7bf",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e3a7c1",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e3a7c3",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00e3a7c5",
      "instruction": "PUSH 0x13f6b3c"
    },
    {
      "address": "00e3a7ca",
      "instruction": "PUSH 0xa0"
    },
    {
      "address": "00e3a7cf",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "00e3a7d1",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "00e3a7d6",
      "instruction": "ADD ESP,0x1c"
    },
    {
      "address": "00e3a7d9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e3a7db",
      "instruction": "JZ 0x00e3a7f8"
    },
    {
      "address": "00e3a7dd",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e3a7df",
      "instruction": "CALL 0x006775f0"
    },
    {
      "address": "00e3a7e4",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00e3a7e8",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e3a7ea",
      "instruction": "JZ 0x00e3a7f8"
    },
    {
      "address": "00e3a7ec",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00e3a7ee",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e3a7f0",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "00e3a7f2",
      "instruction": "CALL EAX"
    },
    {
      "address": "00e3a7f4",
      "instruction": "MOV ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00e3a7f8",
      "instruction": "MOV ECX,dword ptr [EBX + 0x30]"
    },
    {
      "address": "00e3a7fb",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00e3a7fd",
      "instruction": "LEA EDX,[EBP + 0x6299720]"
    },
    {
      "address": "00e3a803",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e3a804",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "00e3a809",
      "instruction": "LEA ECX,[EBP + EBP*0x2]"
    },
    {
      "address": "00e3a80d",
      "instruction": "CMP dword ptr [EBX + 
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
  "body_end": "00e3a8e0",
  "body_span_bytes": 433,
  "body_start": "00e3a730",
  "callees": [
    "FUN_00556440",
    "FUN_00677df0",
    "FUN_00c756e0",
    "FUN_00677700",
    "FUN_00f67d90",
    "FUN_008105b0",
    "FUN_006775f0",
    "FUN_00677d90",
    "FUN_00f473a0",
    "FUN_00677220",
    "FUN_00b3d300",
    "FUN_00e36f50"
  ],
  "callers": [
    "FUN_00e3b9e0",
    "FUN_00e3a8f0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e3a730",
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
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00e3a730",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa3a730",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e3a730(void)",
  "size_bytes": 433,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e3a730",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00e3a933"
    },
    {
      "from": "00e3a949"
    },
    {
      "from": "00e3a95f"
    },
    {
      "from": "00e3a976"
    },
    {
      "from": "00e3a984"
    },
    {
      "from": "00e3bd11"
    },
    {
      "from": "00e3bd99"
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
