# Evidence 0x01000000

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `816887f145b76199a85c33319df9679cce7a3683f7e7e03f055ebc677c6d8fec`

## abi

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
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x30"
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
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
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
    "flow_not_modelled: the linear ESP walk ends at -24, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0x30; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x4 is not a whole number of dword stack arguments, so no convention follows from it",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0x30 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "08c84419901ff7e97c465968702791541e915afe8a6eae92492446e453bced3f",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 13,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0043",
        "obs-0135"
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
        "obs-0043",
        "obs-0135"
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
        "obs-0011",
        "obs-0067",
        "obs-0070",
        "obs-0073",
        "obs-0080"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 8,
        "observed_slots": 4,
        "total_bytes": 48
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0014",
        "obs-0023",
        "obs-0036",
        "obs-0054",
        "obs-0059",
        "obs-0063",
        "obs-0070",
        "obs-0078",
        "obs-0083",
        "obs-0089",
        "obs-0095",
        "obs-0097",
        "obs-0101",
        "obs-0102",
        "obs-0103",
        "obs-0107",
        "obs-0110",
        "obs-0111",
        "obs-0116"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          64
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0135"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x30"
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
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
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
    "flow_not_modelled: the linear ESP walk ends at -24, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0x30; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x4 is not a whole number of dword stack arguments, so no convention follows from it",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0x30 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "08c84419901ff7e97c465968702791541e915afe8a6eae92492446e453bced3f",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 13,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0043",
        "obs-0135"
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
        "obs-0043",
        "obs-0135"
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
        "obs-0011",
        "obs-0067",
        "obs-0070",
        "obs-0073",
        "obs-0080"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 8,
        "observed_slots": 4,
        "total_bytes": 48
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0014",
        "obs-0023",
        "obs-0036",
        "obs-0054",
        "obs-0059",
        "obs-0063",
        "obs-0070",
        "obs-0078",
        "obs-0083",
        "obs-0089",
        "obs-0095",
        "obs-0097",
        "obs-0101",
        "obs-0102",
        "obs-0103",
        "obs-0107",
        "obs-0110",
        "obs-0111",
        "obs-0116"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          64
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0135"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    
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
  "count": 318,
  "instructions": [
    {
      "address": "01000000",
      "instruction": "SUB ESP,0x94"
    },
    {
      "address": "01000006",
      "instruction": "PUSH EBX"
    },
    {
      "address": "01000007",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01000008",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01000009",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0100000a",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "0100000c",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "01000011",
      "instruction": "MOV EDI,dword ptr [ESP + 0xa8]"
    },
    {
      "address": "01000018",
      "instruction": "MOV ESI,dword ptr [EDI + 0x13c]"
    },
    {
      "address": "0100001e",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "01000020",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "01000022",
      "instruction": "MOV dword ptr [ESP + 0x1c],ESI"
    },
    {
      "address": "01000026",
      "instruction": "CALL 0x00c71e30"
    },
    {
      "address": "0100002b",
      "instruction": "CMP EBX,EAX"
    },
    {
      "address": "0100002d",
      "instruction": "JNZ 0x010003d7"
    },
    {
      "address": "01000033",
      "instruction": "PUSH EDI"
    },
    {
      "address": "01000034",
      "instruction": "CALL 0x0102adf0"
    },
    {
      "address": "01000039",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0100003c",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0100003e",
      "instruction": "JNZ 0x010003d7"
    },
    {
      "address": "01000044",
      "instruction": "CALL 0x01002bd0"
    },
    {
      "address": "01000049",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0100004b",
      "instruction": "CALL 0x00a1ad60"
    },
    {
      "address": "01000050",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "01000052",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "01000054",
      "instruction": "CALL 0x00b8dad0"
    },
    {
      "address": "01000059",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "0100005b",
      "instruction": "MOV dword ptr [ESP + 0x24],ECX"
    },
    {
      "address": "0100005f",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01000062",
      "instruction": "MOV dword ptr [ESP + 0x28],EDX"
    },
    {
      "address": "01000066",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "01000069",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0100006b",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0100006d",
      "instruction": "MOV dword ptr [ESP + 0x30],EAX"
    },
    {
      "address": "01000071",
      "instruction": "CALL 0x00c70fd0"
    },
    {
      "address": "01000076",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "01000078",
      "instruction": "MOV EDX,dword ptr [EDX + 0x64]"
    },
    {
      "address": "0100007b",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "0100007d",
      "instruction": "LEA EAX,[ESP + 0x24]"
    },
    {
      "address": "01000081",
      "instruction": "PUSH EAX"
    },
    {
      "address": "01000082",
      "instruction": "PUSH 0x4"
    },
    {
      "address": "01000084",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "01000086",
      "instruction": "CALL EDX"
    },
    {
      "address": "01000088",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "0100008a",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "0100008c",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "0100008f",
      "instruction": "JZ 0x010000e9"
    },
    {
      "address": "01000091",
      "instruction": "PUSH EAX"
    },
    {
      "address": "01000092",
      "instruction": "MOV EAX,dword ptr [EDX + 0x60]"
    },
    {
      "address": "01000095",
      "instruction": "CALL EAX"
    },
    {
      "address": "01000097",
      "instruction": "MOV dword ptr [ESP + 0x18],EAX"
    },
    {
      "address": "0100009b",
      "instruction": "CALL 0x0102f810"
    },
    {
      "address": "010000a0",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "010000a2",
      "instruction": "CALL 0x0102ff00"
    },
    {
      "address": "010000a7",
      "instruction": "MOV ECX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "010000ab",
      "instruction": "SUB EAX,dword ptr [ECX + 0x10]"
    },
    {
      "address": "010000ae",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "010000b0",
      "instruction": "JG 0x010000e1"
    },
    {
      "address": "010000b2",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "010000b4",
      "instruction": "JLE 0x010000e1"
    },
    {
      "address": "010000b6",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "010000b8",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "010000ba",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "010000bc",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "010000be",
      "instruction": "PUSH 0x131a9f54"
    },
    {
      "address": "010000c3",
      "instruction": "PUSH 0x2a84f6ca"
    },
    {
      "address": "010000c8",
      "instruction": "CALL 0x00b3d3e0"
    },
    {
      "address": "010000cd",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "010000cf",
      "instruction": "CALL 0x00dd8640"
    },
    {
      "address": "010000d4",
      "instruction": "POP EDI"
    },
    {
      "address": "010000d5",
      "instruction": "POP ESI"
    },
    {
      "address": "010000d6",
      "instruction": "POP EBP"
    },
    {
      "address": "010000d7",
      "instruction": "POP EBX"
    },
    {
      "address": "010000d8",
      "i
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
  "body_end": "010003e3",
  "body_span_bytes": 996,
  "body_start": "01000000",
  "callees": [
    "FUN_00feb9f0",
    "FUN_01021300",
    "FUN_0067ddd0",
    "QuaternionToMatrix",
    "FUN_0103a480",
    "FUN_01002bd0",
    "FUN_00dd8640",
    "FUN_01041c50",
    "FUN_01005180",
    "FUN_00c70fd0",
    "FUN_00fffdd0",
    "FUN_00c71160",
    "FUN_00a1ad60",
    "FUN_00c71e30",
    "FUN_00b3d3e0",
    "FUN_0102f810",
    "FUN_0102adf0",
    "FUN_00feba90",
    "FUN_00b3d3d0",
    "FUN_0103fc10",
    "FUN_0102ff00",
    "FUN_00434040",
    "FUN_007eb820",
    "FUN_00b8dad0"
  ],
  "callers": [
    "FUN_0102caa0",
    "FUN_01000520"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01000000",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_78",
      "storage": "Stack[-0x78]:4",
      "type": "undefined4"
    },
    {
      "name": "local_7c",
      "storage": "Stack[-0x7c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_80",
      "storage": "Stack[-0x80]:4",
      "type": "undefined4"
    },
    {
      "name": "local_88",
      "storage": "Stack[-0x88]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_01000000",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc00000",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01000000(void)",
  "size_bytes": 996,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01000000",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 61,
  "xrefs": [
    {
      "from": "0102caad"
    },
    {
      "from": "01000555"
    },
    {
      "from": "00db21d2"
    },
    {
      "from": "00c6b2db"
    },
    {
      "from": "00c6b32b"
    },
    {
      "from": "00d6ac33"
    },
    {
      "from": "006e8987"
    },
    {
      "from": "006e89a1"
    },
    {
      "from": "006e89bb"
    },
    {
      "from": "006e89d2"
    },
    {
      "from": "00db00c3"
    },
    {
      "from": "00ce1266"
    },
    {
      "from": "00da6144"
    },
    {
      "from": "00da644f"
    },
    {
      "from": "00c26593"
    },
    {
      "from": "0042d5fd"
    },
    {
      "from": "004aa1fa"
    },
    {
      "from": "004f816c"
    },
    {
      "from": "0056a2a8"
    },
    {
      "from": "0060f6b3"
    },
    {
      "from": "006c1b53"
    },
    {
      "from": "0074574c"
    },
    {
      "from": "007a9aa1"
    },
    {
      "from": "0086daf6"
    },
    {
      "from": "00883b34"
    },
    {
      "from": "0088b78c"
    },
    {
      "from": "0092c8e3"
    },
    {
      "from": "0092ea26"
    },
    {
      "from": "009964f3"
    },
    {
      "from": "009a485a"
    },
    {
      "from": "009a7dc0"
    },
    {
      "from": "009dbc27"
    },
    {
      "from": "009e3cae"
    },
    {
      "from": "00aa6178"
    },
    {
      "from": "00aeea08"
    },
    {
      "from": "00b8da76"
    },
    {
      "from": "00baaef1"
    },
    {
      "from": "00bba772"
    },
    {
      "from": "00c26566"
    },
    {
      "from": "00d1f52f"
    },
    {
      "from": "00d5f7f9"
    },
    {
      "from": "00d6068b"
    },
    {
      "from": "00e33034"
    },
    {
      "from": "00e33098"
    },
    {
      "from": "00f56218"
    },
    {
      "from": "01055fe0"
    },
    {
      "from": "0111d1e8"
    },
    {
      "from": "01168511"
    },
    {
      "from": "011822a7"
    },
    {
      "from": "011ee431"
    },
    {
      "from": "011f3015"
    },
    {
      "from": "00aeda77"
    },
    {
      "from": "00aedc8b"
    },
    {
      "from": "00aeddaa"
    },
    {
      "from": "00f9be35"
    },
    {
      "from": "00f9be5d"
    },
    {
      "from": "00dbaf21"
    },
    {
      "from": "011bb0bb"
    },
    {
      "from": "0092799a"
    },
    {
      "from": "01035708"
    },
    {
      "from": "011299f1"
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
