# Evidence 0x00ad1000

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f15e5ca9a6f47e88596603fb2a2eccd8fc3ff23710578095c460bb7f066e287b`

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
      "entry_ESP+0x8"
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
        "size_inferred": true,
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
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_reassigned_before_deref",
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
  "content_sha256": "c35bd3c063f8bfcce3fad2303ae3ac33be4441253f3ee96504d4c23ac2d9ee0a",
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
    "indirect_calls": 8,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0061"
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
        "obs-0005",
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
        "obs-0012",
        "obs-0024",
        "obs-0025",
        "obs-0026",
        "obs-0029",
        "obs-0033",
        "obs-0038",
        "obs-0043"
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
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0061"
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
        "obs-0061"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0061"
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
      "and_esp": null,
      "at": "0x00ad1000",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 6,
      "raw": "SUB ESP,0x14",
      "sub": 20
    },
    {
      "at": "0x00ad1000",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x14",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00ad1003",
      "count": 14,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00ad1004",
      "count": 23,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x20]",
      "reg": "ESP"
    },
    {
      "at": "0x00ad1004",
      "base": "ESP",
      "disp": 32,
      "id": "obs-0005",
      "index": 2,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x20]",
      "resolved": true,
      "size": 4,
      "trust": 
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
      "entry_ESP+0x8"
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
        "size_inferred": true,
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
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_reassigned_before_deref",
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
  "content_sha256": "c35bd3c063f8bfcce3fad2303ae3ac33be4441253f3ee96504d4c23ac2d9ee0a",
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
    "indirect_calls": 8,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0061"
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
        "obs-0005",
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
        "obs-0012",
        "obs-0024",
        "obs-0025",
        "obs-0026",
        "obs-0029",
        "obs-0033",
        "obs-0038",
        "obs-0043"
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
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0061"
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
        "obs-0061"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0061"
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
      "and_esp": null,
      "at": "0x00ad1000",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 6,
      "raw": "SUB ESP,0x14",
      "sub": 20
    },
    {
      "at": "0x00ad1000",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x14",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00ad1003",
      "count": 14,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00ad1004",
      "count": 23,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x20]",
      "reg": "ESP"
    },
    {
      "at": "0x00ad1004",
      "base": "ESP",
      "disp": 32,
      "id": "obs-0005",
      "index": 2,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x20]",
      "resolved": true,
      "size": 4,
      "trust": 
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
  "count": 177,
  "instructions": [
    {
      "address": "00ad1000",
      "instruction": "SUB ESP,0x14"
    },
    {
      "address": "00ad1003",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ad1004",
      "instruction": "MOV EDI,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00ad1008",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00ad100a",
      "instruction": "JLE 0x00ad11e4"
    },
    {
      "address": "00ad1010",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00ad1011",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00ad1012",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ad1013",
      "instruction": "LEA EAX,[ESP + 0x28]"
    },
    {
      "address": "00ad1017",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ad1018",
      "instruction": "ADD ECX,0x88"
    },
    {
      "address": "00ad101e",
      "instruction": "CALL 0x00ad0ca0"
    },
    {
      "address": "00ad1023",
      "instruction": "MOV ECX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00ad1026",
      "instruction": "SUB ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00ad1029",
      "instruction": "LEA ESI,[EAX + 0x8]"
    },
    {
      "address": "00ad102c",
      "instruction": "MOV dword ptr [ESP + 0x18],EAX"
    },
    {
      "address": "00ad1030",
      "instruction": "MOV EAX,0x2aaaaaab"
    },
    {
      "address": "00ad1035",
      "instruction": "IMUL ECX"
    },
    {
      "address": "00ad1037",
      "instruction": "SAR EDX,0x1"
    },
    {
      "address": "00ad1039",
      "instruction": "MOV EBP,EDX"
    },
    {
      "address": "00ad103b",
      "instruction": "SHR EBP,0x1f"
    },
    {
      "address": "00ad103e",
      "instruction": "ADD EBP,EDX"
    },
    {
      "address": "00ad1040",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00ad1045",
      "instruction": "CMP EBP,EDI"
    },
    {
      "address": "00ad1047",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "00ad104b",
      "instruction": "JGE 0x00ad10bd"
    },
    {
      "address": "00ad104d",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ad104e",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ad1050",
      "instruction": "CALL 0x00acd920"
    },
    {
      "address": "00ad1055",
      "instruction": "LEA EBX,[EBP + EBP*0x2]"
    },
    {
      "address": "00ad1059",
      "instruction": "ADD EBX,EBX"
    },
    {
      "address": "00ad105b",
      "instruction": "ADD EBX,EBX"
    },
    {
      "address": "00ad105d",
      "instruction": "SUB EDI,EBP"
    },
    {
      "address": "00ad105f",
      "instruction": "MOV dword ptr [ESP + 0x10],EDI"
    },
    {
      "address": "00ad1063",
      "instruction": "MOV ECX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00ad1067",
      "instruction": "MOV EDI,dword ptr [ESI]"
    },
    {
      "address": "00ad1069",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00ad106a",
      "instruction": "MOV ECX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00ad106e",
      "instruction": "ADD EDI,EBX"
    },
    {
      "address": "00ad1070",
      "instruction": "CALL 0x00b20c60"
    },
    {
      "address": "00ad1075",
      "instruction": "MOV ECX,dword ptr [EDI + 0x8]"
    },
    {
      "address": "00ad1078",
      "instruction": "MOV dword ptr [ESP + 0x1c],EAX"
    },
    {
      "address": "00ad107c",
      "instruction": "MOV dword ptr [ESP + 0x20],ECX"
    },
    {
      "address": "00ad1080",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "00ad1082",
      "instruction": "JZ 0x00ad10a6"
    },
    {
      "address": "00ad1084",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00ad1086",
      "instruction": "JZ 0x00ad1098"
    },
    {
      "address": "00ad1088",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00ad108a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ad108c",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "00ad108e",
      "instruction": "CALL EAX"
    },
    {
      "address": "00ad1090",
      "instruction": "MOV EAX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00ad1094",
      "instruction": "MOV ECX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00ad1098",
      "instruction": "MOV dword ptr [EDI + 0x8],EAX"
    },
    {
      "address": "00ad109b",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00ad109d",
      "instruction": "JZ 0x00ad10a6"
    },
    {
      "address": "00ad109f",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00ad10a1",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "00ad10a4",
      "instruction": "CALL EAX"
    },
    {
      "address": "00ad10a6",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "00ad10a8",
      "instruction": "MOV byte ptr [ECX + EBX*0x1 + 0x4],0x0"
    },
    {
      "address": "00ad10ad",
      "instruction": "ADD EBX,0xc"
    },
    {
      "address": "00ad10b0",
      "instruction": "SUB dword ptr [ESP + 0x10],0x1"
    },
    {
      "address": "00ad10b5",
      "instruction": "JNZ 0x00ad1063"
    },
    {
      "address": "00ad10b7",
      "instruction": "MOV EDI,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00ad10bb",
      "instruction": "JMP 0x00ad10f4"
    },
    {
      "address": "00ad10bd",
      "instruction": "JLE 0x00ad10f4"
    },
    {
      "address": "00ad10bf",
      "instruction": "CMP EDI,EBP"
    },
    {
      "address": "00ad10c1",
      "instruction": "JGE 0x00ad10ec"
    },
    {
      "address": "00ad10c3",
      "instruction": "LEA EBX,[EDI + EDI*0x2]"
    },
    {
      "address": "00ad10c6",
      "instruction": "ADD EBX,EBX"
    },
    {
      "address": "00
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
  "body_end": "00ad11ea",
  "body_span_bytes": 491,
  "body_start": "00ad1000",
  "callees": [
    "FUN_00b225d0",
    "FUN_00b20c60",
    "FUN_00acd920",
    "FUN_00ad0ca0",
    "FUN_00b3d300",
    "FUN_00c0bf00"
  ],
  "callers": [
    "FUN_00ad11f0",
    "FUN_00ad20e0",
    "FUN_00ad2200"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ad1000",
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
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_00ad1000",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6d1000",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ad1000(void)",
  "size_bytes": 491,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ad1000",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00ad1256"
    },
    {
      "from": "00ad21cc"
    },
    {
      "from": "00ad228d"
    },
    {
      "from": "00ad22a0"
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
