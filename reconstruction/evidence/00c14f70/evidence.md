# Evidence 0x00c14f70

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `869f9a4ec78dec640768a73f07feb126be4f46cf857d622f113833ed2fb87259`

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
      "entry_ESP+0x40"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
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
      }
    ],
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -60, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0xc pops less than the highest read slot 0x40; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0xc but entry slot 0x40 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "b58e57ab909a4020b319d2f7b9b0e4a3baf256306ae78e7a5082084ac03ab42e",
  "conventions": {
    "ambiguities": [
      "variadic_suspected"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl"
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
    "indirect_calls": 9,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0065",
        "obs-0072"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0065",
        "obs-0072"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 12,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0013",
        "obs-0015",
        "obs-0019",
        "obs-0024",
        "obs-0025",
        "obs-0066"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 13,
        "observed_slots": 3,
        "total_bytes": 64
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0015",
        "obs-0016",
        "obs-0020",
        "obs-0025",
        "obs-0028",
        "obs-0031",
        "obs-0037",
        "obs-0043",
        "obs-0048",
        "obs-0050",
        "obs-0059",
        "obs-0066"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          192,
          2900
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0042"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0065",
        "obs-0072"
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
      "and_esp": null,
      "at": "0x00c14f70",
      "ebp_is_general_register": true,
      "fp
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
      "entry_ESP+0x40"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
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
      }
    ],
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -60, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0xc pops less than the highest read slot 0x40; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0xc but entry slot 0x40 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "b58e57ab909a4020b319d2f7b9b0e4a3baf256306ae78e7a5082084ac03ab42e",
  "conventions": {
    "ambiguities": [
      "variadic_suspected"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl"
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
    "indirect_calls": 9,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0065",
        "obs-0072"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0065",
        "obs-0072"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 12,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0013",
        "obs-0015",
        "obs-0019",
        "obs-0024",
        "obs-0025",
        "obs-0066"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 13,
        "observed_slots": 3,
        "total_bytes": 64
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0015",
        "obs-0016",
        "obs-0020",
        "obs-0025",
        "obs-0028",
        "obs-0031",
        "obs-0037",
        "obs-0043",
        "obs-0048",
        "obs-0050",
        "obs-0059",
        "obs-0066"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          192,
          2900
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0042"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0065",
        "obs-0072"
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
      "and_esp": null,
      "at": "0x00c14f70",
      "ebp_is_general_register": true,
      "fp
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
  "count": 147,
  "instructions": [
    {
      "address": "00c14f70",
      "instruction": "SUB ESP,0x5c"
    },
    {
      "address": "00c14f73",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c14f74",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c14f75",
      "instruction": "MOV EBP,dword ptr [ESP + 0x68]"
    },
    {
      "address": "00c14f79",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c14f7a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c14f7b",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00c14f7d",
      "instruction": "CMP EBP,-0x1"
    },
    {
      "address": "00c14f80",
      "instruction": "JZ 0x00c15138"
    },
    {
      "address": "00c14f86",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00c14f88",
      "instruction": "MOV dword ptr [ESP + 0x70],EDI"
    },
    {
      "address": "00c14f8c",
      "instruction": "CALL 0x0067ddd0"
    },
    {
      "address": "00c14f91",
      "instruction": "MOV ECX,dword ptr [ESP + 0x70]"
    },
    {
      "address": "00c14f95",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00c14f97",
      "instruction": "CMP ECX,EDI"
    },
    {
      "address": "00c14f99",
      "instruction": "JZ 0x00c14fa6"
    },
    {
      "address": "00c14f9b",
      "instruction": "MOV dword ptr [ESP + 0x70],EDI"
    },
    {
      "address": "00c14f9f",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00c14fa1",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00c14fa4",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c14fa6",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00c14fa8",
      "instruction": "MOV EDX,dword ptr [ESP + 0x74]"
    },
    {
      "address": "00c14fac",
      "instruction": "MOV EAX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "00c14faf",
      "instruction": "LEA ECX,[ESP + 0x70]"
    },
    {
      "address": "00c14fb3",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c14fb4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c14fb5",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c14fb6",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c14fb8",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c14fba",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c14fbc",
      "instruction": "JZ 0x00c15129"
    },
    {
      "address": "00c14fc2",
      "instruction": "MOV ECX,dword ptr [EBX + 0xb54]"
    },
    {
      "address": "00c14fc8",
      "instruction": "CMP ECX,EDI"
    },
    {
      "address": "00c14fca",
      "instruction": "JZ 0x00c15055"
    },
    {
      "address": "00c14fd0",
      "instruction": "CALL 0x00a02bd0"
    },
    {
      "address": "00c14fd5",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c14fd7",
      "instruction": "JNZ 0x00c15055"
    },
    {
      "address": "00c14fd9",
      "instruction": "LEA ECX,[ESP + 0x34]"
    },
    {
      "address": "00c14fdd",
      "instruction": "CALL 0x00434040"
    },
    {
      "address": "00c14fe2",
      "instruction": "MOV EDX,dword ptr [EBX + 0xc0]"
    },
    {
      "address": "00c14fe8",
      "instruction": "MOV EAX,dword ptr [EDX + 0x2c]"
    },
    {
      "address": "00c14feb",
      "instruction": "LEA ESI,[EBX + 0xc0]"
    },
    {
      "address": "00c14ff1",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c14ff3",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c14ff5",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "00c14ff7",
      "instruction": "MOV dword ptr [ESP + 0x38],ECX"
    },
    {
      "address": "00c14ffb",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00c14ffe",
      "instruction": "MOV dword ptr [ESP + 0x3c],EDX"
    },
    {
      "address": "00c15002",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00c15005",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00c15007",
      "instruction": "OR word ptr [ESP + 0x34],0x4"
    },
    {
      "address": "00c1500d",
      "instruction": "INC word ptr [ESP + 0x36]"
    },
    {
      "address": "00c15012",
      "instruction": "MOV dword ptr [ESP + 0x40],EAX"
    },
    {
      "address": "00c15016",
      "instruction": "MOV EAX,dword ptr [EDX + 0x30]"
    },
    {
      "address": "00c15019",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c1501b",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c1501d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c1501e",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00c15022",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c15023",
      "instruction": "CALL 0x0059c190"
    },
    {
      "address": "00c15028",
      "instruction": "MOV ECX,0x9"
    },
    {
      "address": "00c1502d",
      "instruction": "LEA ESI,[ESP + 0x18]"
    },
    {
      "address": "00c15031",
      "instruction": "LEA EDI,[ESP + 0x50]"
    },
    {
      "address": "00c15035",
      "instruction": "MOVSD.REP ES:EDI,ESI"
    },
    {
      "address": "00c15037",
      "instruction": "MOV ECX,dword ptr [ESP + 0x78]"
    },
    {
      "address": "00c1503b",
      "instruction": "OR word ptr [ESP + 0x3c],0x2"
    },
    {
      "address": "00c15041",
      "instruction": "INC word ptr [ESP + 0x3e]"
    },
    {
      "address": "00c15046",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00c15048",
      "instruction": "MOV EDX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "00c1504b",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00c1504e",
      "instruction": "
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
  "body_end": "00c15143",
  "body_span_bytes": 468,
  "body_start": "00c14f70",
  "callees": [
    "FUN_00c0c4b0",
    "FUN_0067ddd0",
    "QuaternionToMatrix",
    "FUN_00a02bd0",
    "FUN_00434040",
    "FUN_009cb300",
    "FUN_009caa40"
  ],
  "callers": [
    "FUN_00c17c80",
    "FUN_00c17d60",
    "FUN_00c17cc0",
    "FUN_00c15470"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c14f70",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00c14f70",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x814f70",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c14f70(void)",
  "size_bytes": 468,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c14f70",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00c17db9"
    },
    {
      "from": "00c17d32"
    },
    {
      "from": "00c15628"
    },
    {
      "from": "00c17cad"
    },
    {
      "from": "00d768a3"
    },
    {
      "from": "00d76e85"
    },
    {
      "from": "00d813aa"
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
