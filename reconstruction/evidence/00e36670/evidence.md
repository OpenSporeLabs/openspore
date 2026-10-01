# Evidence 0x00e36670

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b3520adbb4fde5a22f213029009dbcbe294f719a99e2537176cd7c9686063e4f`

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
    "ret_form": "RET",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "receiver_not_determinable: ecx_address_taken_without_memory_access",
    "ecx_address_taken_without_memory_access: LEA takes ECX's address without any memory access through it",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_address_taken_without_memory_access), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "75176ce2b63b7180eea2acaca3add9deb5f864356e10bce5334537c7be335e07",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
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
        "obs-0068"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0013",
        "obs-0016",
        "obs-0020",
        "obs-0025",
        "obs-0032"
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
        "obs-0015",
        "obs-0016",
        "obs-0017",
        "obs-0020",
        "obs-0040"
      ],
      "claim": "the register receiver is undetermined: ecx_address_taken_without_memory_access",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_address_taken_without_memory_access",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0016",
        "obs-0017",
        "obs-0020",
        "obs-0040"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_address_taken_without_memory_access) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0032"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00e36670",
      "count": 13,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "reg": "XMM0"
    },
    {
      "at": "0x00e36670",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "and_esp": null,
      "at": "0x00e36673",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": 32
    },
    {
      "at": "0x00e36673",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00e36676",
      "count": 11,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,

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
    "ret_form": "RET",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "receiver_not_determinable: ecx_address_taken_without_memory_access",
    "ecx_address_taken_without_memory_access: LEA takes ECX's address without any memory access through it",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_address_taken_without_memory_access), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "75176ce2b63b7180eea2acaca3add9deb5f864356e10bce5334537c7be335e07",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
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
        "obs-0068"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0013",
        "obs-0016",
        "obs-0020",
        "obs-0025",
        "obs-0032"
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
        "obs-0015",
        "obs-0016",
        "obs-0017",
        "obs-0020",
        "obs-0040"
      ],
      "claim": "the register receiver is undetermined: ecx_address_taken_without_memory_access",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_address_taken_without_memory_access",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0016",
        "obs-0017",
        "obs-0020",
        "obs-0040"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_address_taken_without_memory_access) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0032"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00e36670",
      "count": 13,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "reg": "XMM0"
    },
    {
      "at": "0x00e36670",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "and_esp": null,
      "at": "0x00e36673",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": 32
    },
    {
      "at": "0x00e36673",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00e36676",
      "count": 11,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,

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
  "count": 165,
  "instructions": [
    {
      "address": "00e36670",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00e36673",
      "instruction": "SUB ESP,0x20"
    },
    {
      "address": "00e36676",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e36677",
      "instruction": "MOV ESI,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00e3667b",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00e3667d",
      "instruction": "MOV EDX,dword ptr [EAX + 0xcc]"
    },
    {
      "address": "00e36683",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e36684",
      "instruction": "MOV EDI,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00e36688",
      "instruction": "LEA ECX,[ESP + 0x2c]"
    },
    {
      "address": "00e3668c",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e3668d",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00e3668f",
      "instruction": "MOVSS dword ptr [EDI],XMM0"
    },
    {
      "address": "00e36693",
      "instruction": "MOVSS dword ptr [EDI + 0x4],XMM0"
    },
    {
      "address": "00e36698",
      "instruction": "MOVSS dword ptr [EDI + 0x8],XMM0"
    },
    {
      "address": "00e3669d",
      "instruction": "MOVSS dword ptr [EDI + 0xc],XMM0"
    },
    {
      "address": "00e366a2",
      "instruction": "CALL EDX"
    },
    {
      "address": "00e366a4",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00e366a6",
      "instruction": "MOV EDX,dword ptr [EAX + 0xd0]"
    },
    {
      "address": "00e366ac",
      "instruction": "LEA ECX,[ESP + 0x30]"
    },
    {
      "address": "00e366b0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e366b1",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00e366b3",
      "instruction": "CALL EDX"
    },
    {
      "address": "00e366b5",
      "instruction": "MOV EAX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00e366b9",
      "instruction": "CMP EAX,dword ptr [ESP + 0x30]"
    },
    {
      "address": "00e366bd",
      "instruction": "JZ 0x00e36882"
    },
    {
      "address": "00e366c3",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e366c4",
      "instruction": "MOV EBX,dword ptr [ESP + 0x3c]"
    },
    {
      "address": "00e366c8",
      "instruction": "JMP 0x00e366d0"
    },
    {
      "address": "00e366d0",
      "instruction": "MOV ECX,dword ptr [0x01440aec]"
    },
    {
      "address": "00e366d6",
      "instruction": "LEA ESI,[ECX + EAX*0x1]"
    },
    {
      "address": "00e366d9",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "00e366db",
      "instruction": "JZ 0x00e366ee"
    },
    {
      "address": "00e366dd",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00e366df",
      "instruction": "MOV EAX,dword ptr [EDX + 0x28]"
    },
    {
      "address": "00e366e2",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00e366e4",
      "instruction": "CALL EAX"
    },
    {
      "address": "00e366e6",
      "instruction": "TEST AL,0x1"
    },
    {
      "address": "00e366e8",
      "instruction": "JZ 0x00e3686d"
    },
    {
      "address": "00e366ee",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00e366f0",
      "instruction": "MOV EAX,dword ptr [EDX + 0x38]"
    },
    {
      "address": "00e366f3",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00e366f5",
      "instruction": "CALL EAX"
    },
    {
      "address": "00e366f7",
      "instruction": "MOVSS XMM0,dword ptr [EAX]"
    },
    {
      "address": "00e366fb",
      "instruction": "MOVSS XMM2,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00e36700",
      "instruction": "MOVSS XMM4,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00e36705",
      "instruction": "MOVSS XMM1,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00e3670a",
      "instruction": "MOV EAX,dword ptr [ESP + 0x38]"
    },
    {
      "address": "00e3670e",
      "instruction": "MOVSS dword ptr [ESP + 0x1c],XMM0"
    },
    {
      "address": "00e36714",
      "instruction": "MOVSS dword ptr [ESP + 0x20],XMM2"
    },
    {
      "address": "00e3671a",
      "instruction": "MOVSS dword ptr [ESP + 0x24],XMM4"
    },
    {
      "address": "00e36720",
      "instruction": "MOVSS dword ptr [ESP + 0x28],XMM1"
    },
    {
      "address": "00e36726",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e36728",
      "instruction": "JZ 0x00e367f6"
    },
    {
      "address": "00e3672e",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e3672f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e36730",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00e36734",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e36735",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e36736",
      "instruction": "CALL 0x00e36670"
    },
    {
      "address": "00e3673b",
      "instruction": "MOVSS XMM1,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00e36741",
      "instruction": "MOVSS XMM5,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00e36747",
      "instruction": "MOVSS XMM4,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00e3674d",
      "instruction": "MOVSS XMM3,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00e36753",
      "instruction": "MOVSS XMM6,dword ptr [ESP + 0x30]"
    },
    {
      "address": "00e36759",
      "instruction": "SUBSS XMM3,XMM1"
    },
    {
      "address": "00e3675d",
      "instruction": "MOVAPS XMM0,XMM5"
    },
    {
      "address": "00e36760",
      "instruction": "ADDSS XMM0,XMM1"
    },
    {
      "address": "00e36764",
      "instruction": "MOVSS XMM1,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00e3676a",
      "instruction": "SUBSS
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
  "body_end": "00e36889",
  "body_span_bytes": 538,
  "body_start": "00e36670",
  "callees": [
    "FUN_00e36670"
  ],
  "callers": [
    "FUN_00e368e0",
    "FUN_0082a500",
    "FUN_00e369f0",
    "FUN_00e36670"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e36670",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00e36670",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa36670",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e36670(void)",
  "size_bytes": 538,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e36670",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "0082a659"
    },
    {
      "from": "00e36736"
    },
    {
      "from": "00e36986"
    },
    {
      "from": "00e36a0d"
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
