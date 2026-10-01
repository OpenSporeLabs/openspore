# Evidence 0x00bb4ba0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2c89c49bc5d5b586a9f7d65b22576b5c001112b6169402ce62958328f3c8ffd1`

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
      "entry_ESP+0x8",
      "entry_ESP+0xc"
    ],
    "ordinary_stack_argument_slots_bounded": {
      "kept": 2,
      "omitted": 16
    },
    "ordinary_stack_arguments": [
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ordinary_stack_arguments_bounded": {
      "kept": 2,
      "omitted": 16
    },
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_arguments_bounded": {
      "kept": 2,
      "omitted": 16
    },
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -10528, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent"
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
  "content_sha256": "33a014880538cd76bc33f091926ac590f372729f5bb34f05019dc579ef18aad3",
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
    "indirect_calls": 10,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0117"
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
        "obs-0049",
        "obs-0050",
        "obs-0052",
        "obs-0056",
        "obs-0059",
        "obs-0064",
        "obs-0065",
        "obs-0072",
        "obs-0074",
        "obs-0075",
        "obs-0076",
        "obs-0077",
        "obs-0078",
        "obs-0079",
        "obs-0080",
        "obs-0081",
        "obs-0082",
        "obs-0085",
        "obs-0087",
        "obs-0092",
        "obs-0095"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 646,
        "observed_slots": 18,
        "total_bytes": 2656
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0011",
        "obs-0021",
        "obs-0022",
        "obs-0043",
        "obs-0045",
        "obs-0051",
        "obs-0052",
        "obs-0054",
        "obs-0060",
        "obs-0062",
        "obs-0064",
        "obs-0085",
        "obs-0087",
        "obs-0092",
        "obs-0095",
        "obs-0099",
        "obs-0101"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          104,
          220,
          224,
          476,
          516,
          540
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0058"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0117"
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
        "obs-0029",
        "obs-0057",
        "obs-0073"
      ],
      "claim": "a bulk string write reaches the return register, which is not a struct-return signature",
      "confidence": "INFERRED",
      "id": "RT4",
      "value": {
        "bulk_write": true
      }
    },
    {
      "based_on": [
        "obs-0117"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
     
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
      "entry_ESP+0x8",
      "entry_ESP+0xc"
    ],
    "ordinary_stack_argument_slots_bounded": {
      "kept": 2,
      "omitted": 16
    },
    "ordinary_stack_arguments": [
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ordinary_stack_arguments_bounded": {
      "kept": 2,
      "omitted": 16
    },
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_arguments_bounded": {
      "kept": 2,
      "omitted": 16
    },
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -10528, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent"
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
  "content_sha256": "33a014880538cd76bc33f091926ac590f372729f5bb34f05019dc579ef18aad3",
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
    "indirect_calls": 10,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0117"
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
        "obs-0049",
        "obs-0050",
        "obs-0052",
        "obs-0056",
        "obs-0059",
        "obs-0064",
        "obs-0065",
        "obs-0072",
        "obs-0074",
        "obs-0075",
        "obs-0076",
        "obs-0077",
        "obs-0078",
        "obs-0079",
        "obs-0080",
        "obs-0081",
        "obs-0082",
        "obs-0085",
        "obs-0087",
        "obs-0092",
        "obs-0095"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 646,
        "observed_slots": 18,
        "total_bytes": 2656
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0011",
        "obs-0021",
        "obs-0022",
        "obs-0043",
        "obs-0045",
        "obs-0051",
        "obs-0052",
        "obs-0054",
        "obs-0060",
        "obs-0062",
        "obs-0064",
        "obs-0085",
        "obs-0087",
        "obs-0092",
        "obs-0095",
        "obs-0099",
        "obs-0101"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          104,
          220,
          224,
          476,
          516,
          540
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0058"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0117"
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
        "obs-0029",
        "obs-0057",
        "obs-0073"
      ],
      "claim": "a bulk string write reaches the return register, which is not a struct-return signature",
      "confidence": "INFERRED",
      "id": "RT4",
      "value": {
        "bulk_write": true
      }
    },
    {
      "based_on": [
        "obs-0117"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
     
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
  "count": 251,
  "instructions": [
    {
      "address": "00bb4ba0",
      "instruction": "MOV EAX,0x14bc"
    },
    {
      "address": "00bb4ba5",
      "instruction": "CALL 0x011e0700"
    },
    {
      "address": "00bb4baa",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bb4bab",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00bb4bad",
      "instruction": "CMP byte ptr [EBX + 0x21c],0x0"
    },
    {
      "address": "00bb4bb4",
      "instruction": "JZ 0x00bb4f26"
    },
    {
      "address": "00bb4bba",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00bb4bbb",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bb4bbc",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bb4bbd",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00bb4bbf",
      "instruction": "CALL 0x00ba6e00"
    },
    {
      "address": "00bb4bc4",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00bb4bc6",
      "instruction": "CALL 0x00bac3a0"
    },
    {
      "address": "00bb4bcb",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00bb4bcd",
      "instruction": "CALL 0x00baf880"
    },
    {
      "address": "00bb4bd2",
      "instruction": "CALL 0x00f48a80"
    },
    {
      "address": "00bb4bd7",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00bb4bd9",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bb4bdb",
      "instruction": "MOV EAX,dword ptr [EDX + 0x20]"
    },
    {
      "address": "00bb4bde",
      "instruction": "PUSH 0x14661f8"
    },
    {
      "address": "00bb4be3",
      "instruction": "CALL EAX"
    },
    {
      "address": "00bb4be5",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00bb4bea",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00bb4bec",
      "instruction": "JZ 0x00bb4cea"
    },
    {
      "address": "00bb4bf2",
      "instruction": "CMP dword ptr [EBX + 0x1dc],0x0"
    },
    {
      "address": "00bb4bf9",
      "instruction": "JZ 0x00bb4c91"
    },
    {
      "address": "00bb4bff",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00bb4c01",
      "instruction": "CALL dword ptr [0x013cc55c]"
    },
    {
      "address": "00bb4c07",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00bb4c0b",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bb4c0c",
      "instruction": "MOV dword ptr [ESP + 0x18],EAX"
    },
    {
      "address": "00bb4c10",
      "instruction": "MOV dword ptr [ESP + 0x1c],EDX"
    },
    {
      "address": "00bb4c14",
      "instruction": "CALL dword ptr [0x013cc3e0]"
    },
    {
      "address": "00bb4c1a",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00bb4c1d",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00bb4c1f",
      "instruction": "JZ 0x00bb4c35"
    },
    {
      "address": "00bb4c21",
      "instruction": "MOV EDI,dword ptr [EBX + 0x1dc]"
    },
    {
      "address": "00bb4c27",
      "instruction": "ADD EDI,0x18"
    },
    {
      "address": "00bb4c2a",
      "instruction": "MOV ECX,0x9"
    },
    {
      "address": "00bb4c2f",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00bb4c31",
      "instruction": "MOVSD.REP ES:EDI,ESI"
    },
    {
      "address": "00bb4c33",
      "instruction": "JMP 0x00bb4c5a"
    },
    {
      "address": "00bb4c35",
      "instruction": "MOV EAX,dword ptr [EBX + 0x1dc]"
    },
    {
      "address": "00bb4c3b",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00bb4c3d",
      "instruction": "ADD EAX,0x18"
    },
    {
      "address": "00bb4c40",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "00bb4c42",
      "instruction": "MOV dword ptr [EAX + 0x4],ECX"
    },
    {
      "address": "00bb4c45",
      "instruction": "MOV dword ptr [EAX + 0x8],ECX"
    },
    {
      "address": "00bb4c48",
      "instruction": "MOV dword ptr [EAX + 0xc],ECX"
    },
    {
      "address": "00bb4c4b",
      "instruction": "MOV dword ptr [EAX + 0x10],ECX"
    },
    {
      "address": "00bb4c4e",
      "instruction": "MOV dword ptr [EAX + 0x14],ECX"
    },
    {
      "address": "00bb4c51",
      "instruction": "MOV dword ptr [EAX + 0x18],ECX"
    },
    {
      "address": "00bb4c54",
      "instruction": "MOV dword ptr [EAX + 0x1c],ECX"
    },
    {
      "address": "00bb4c57",
      "instruction": "MOV dword ptr [EAX + 0x20],ECX"
    },
    {
      "address": "00bb4c5a",
      "instruction": "MOV EDX,dword ptr [EBX + 0x1dc]"
    },
    {
      "address": "00bb4c60",
      "instruction": "MOV EAX,[0x0145f8d4]"
    },
    {
      "address": "00bb4c65",
      "instruction": "MOV dword ptr [EDX + 0x10],EAX"
    },
    {
      "address": "00bb4c68",
      "instruction": "MOV ECX,dword ptr [EBX + 0x1dc]"
    },
    {
      "address": "00bb4c6e",
      "instruction": "MOV EDX,dword ptr [0x0145f8d8]"
    },
    {
      "address": "00bb4c74",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00bb4c76",
      "instruction": "MOV dword ptr [ECX + 0x14],EDX"
    },
    {
      "address": "00bb4c79",
      "instruction": "MOV ECX,dword ptr [EBX + 0x1dc]"
    },
    {
      "address": "00bb4c7f",
      "instruction": "PUSH 0x2"
    },
    {
      "address": "00bb4c81",
      "instruction": "CALL 0x00bb9b00"
    },
    {
      "address": "00bb4c86",
      "instruction": "MOV ECX,dword ptr [EBX + 0x1dc]"
    },
    {
      "address": "00bb4c8c",
      "instruction": "CALL 0x00bb9b80"
    },
    {
      "address": "00bb4c91",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00bb4c96",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bb4c98",
      "instruction": "CALL 0x00c30c60"
    },
    {
      "address": "00bb4c9d",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00bb4c9f",

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
  "body_end": "00bb4f2d",
  "body_span_bytes": 910,
  "body_start": "00bb4ba0",
  "callees": [
    "FUN_00bac3a0",
    "FUN_00f48a80",
    "_localtime64",
    "FUN_00c30c60",
    "FUN_0093c5a0",
    "FUN_01021240",
    "__alloca_probe",
    "FUN_00692f90",
    "Simulator::cSpaceNames::Get",
    "FUN_00692900",
    "FUN_00688fa0",
    "FUN_00693d60",
    "FUN_00b21da0",
    "FUN_00693900",
    "FUN_00d167e0",
    "FUN_00bb9b80",
    "FUN_00f47380",
    "FUN_01021300",
    "FUN_00baf880",
    "FUN_00b3d380",
    "FUN_00ba6e00",
    "FUN_00bb9b00",
    "FUN_01021370",
    "FUN_00423650",
    "FUN_00bf3420",
    "FUN_006891f0",
    "FUN_00692ea0",
    "_time64"
  ],
  "callers": [
    "FUN_00b28ec0",
    "FUN_00bb5640",
    "FUN_00bb6040",
    "FUN_00bb66f0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bb4ba0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00bb4ba0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7b4ba0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bb4ba0(void)",
  "size_bytes": 910,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bb4ba0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00b29403"
    },
    {
      "from": "00bb6355"
    },
    {
      "from": "00bb66f4"
    },
    {
      "from": "00bb5791"
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
[
  {
    "anchors": [
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bb4af0",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00e74a20",
      "0x00e74a20"
    ],
    "conflict_id": "U-004-star-generation-boundary",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
    "resolution_status": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00b28ec0",
      "0x00b294c0",
      "0x00bb4ba0",
      "0x00bb4ba0",
      "0x00693900",
      "0x00693900",
      "0x00693900",
      "0x00693900",
      "0x00693d60",
      "0x00693d60",
      "0x00693d60",
      "0x00693d60",
      "0x006a1540",
      "0x006a2f60",
      "0x006a1540",
      "0x006a2f60"
    ],
    "conflict_id": "cross_file_atomicity",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "stars.db.tmp write and replacement are concrete. No transaction boundary is claimed for the full .spo/profile set.",
    "resolution_status": "stars.db.tmp write and replacement are concrete. No transaction boundary is claimed for the full .spo/profile set.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bb4ba0",
      "0x00bb4ba0",
      "0x013c7d90",
      "0x013c7d90",
      "0x00693900",
      "0x00693900",
      "0x00693d60",
      "0x00693d60",
      "0x007d8d40",
      "0x007d8d40",
      "0x00b28ec0",
      "0x00b28ec0",
      "0x00b294c0",
      "0x00b294c0",
      "0x00b335d0",
      "0x00b335d0"
    ],
    "conflict_id": "field_coverage_and_migration",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bba900",
      "0x00bb4af0",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bba900",
      "0x00bba900",
      "0x00bba900",
      "0x00c86760",
      "0x00c8b700"
    ],
    "conflict_id": "planet_count_materialization",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The generation body increments mPlanetCount while creating cPlanetRecord objects. Lazy materialization and equality with final runtime cPlanets are unresolved.",
    "resolution_status": "The generation body increments mPlanetCount while creating cPlanetRecord objects. Lazy materialization and equality with final runtime cPlanets are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bb4af0",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4c90",
      "0x00bb4af0",
      "0x00bb4100"
    ],
    "conflict_id": "star_generation_address_identity",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Current bodies and SDK anchors are separated rather than merged; the exact SDK entry identity and record-vector append contract remain unresolved.",
    "resolution_status": "Current bodies and SDK anchors are separated rather than merged; the exact SDK entry identity and record-vector append contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Ru
[TRUNCATED]
```
