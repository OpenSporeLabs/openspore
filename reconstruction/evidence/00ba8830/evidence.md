# Evidence 0x00ba8830

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `8f4be08be3d6150a2013b9cd71df50689b18321c7a252e4286f081f275c72b6a`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
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
    "ret_form": "RET 0x4",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
    "flow_not_modelled: the linear ESP walk ends at +184, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_read_without_deref",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "2def4afe2b3760118597ff29f37cfedb14f7d8d3c35f2f931a51710a00307197",
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
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0107"
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
        "obs-0007"
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
        "obs-0012",
        "obs-0033",
        "obs-0060",
        "obs-0067",
        "obs-0073",
        "obs-0080",
        "obs-0086",
        "obs-0092",
        "obs-0098"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0027"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0007"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
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
      "id": "obs-0007"
    },
    {
      "id": "obs-0008"
    },
    {
      "id": "obs-0009"
    },
    {
      "id": "obs-0010"
    },
    {
      "id": "obs-0011"
    },
    {
      "id": "obs-0012"
    },
    {
      "id": "obs-0013"
    },
    {
      "id": "obs-0014"
    },
    {
      "id": "obs-0015"
    },
    {
      "id": "obs-0016"
    },
    {
      "id": "obs-0017"
    },
    {
      "id": "obs-0018"
    },
    {
      "id": "obs-0019"
    },
    {
      "id": "obs-0020"
    },
    {
      "id": "obs-0021"
    },
    {
      "id": "obs-0022"
    },
    {
      "id": "obs-0023"
    },
    {
      "id": "obs-0024"
    },
    {
      "id": "obs-0025"
    },
    {
      "id": "obs-0026"
    },
    {
      "id": "obs-0027"
    },
    {
      "id": "obs-0028"
    },
    {
      "id": "obs-0029"
    },
    {
      "id": "obs-0030"
    },
    {
      "id": "obs-0031"
    },
    {
      "id": "obs-0032"
    },
    {
      "id": "obs-0033"
    },
    {
      "id": "obs-0034"
    },
    {
      "id": "obs-0035"
    },
    {
      "id": "obs-0036"
    },
    {
      "id": "obs-0037"
    },
    {
      "id": "obs-0038"
    },
    {
      "id": "obs-0039"
    },
    {
      "id": "obs-0040"
    },
    {
      "id": "obs-0041"
    },
    {
      "id": "obs-0042"
    },
    {
      "id": "obs-0043"
    },
    {
      "id": "obs-0044"
    },
    {
      "id": "obs-0045"
    },
    {
      "id": "obs-0046"
    },
    {
      "id": "obs-0047"
    },
    {

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
    "ret_form": "RET 0x4",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
    "flow_not_modelled: the linear ESP walk ends at +184, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_read_without_deref",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "2def4afe2b3760118597ff29f37cfedb14f7d8d3c35f2f931a51710a00307197",
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
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0107"
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
        "obs-0007"
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
        "obs-0012",
        "obs-0033",
        "obs-0060",
        "obs-0067",
        "obs-0073",
        "obs-0080",
        "obs-0086",
        "obs-0092",
        "obs-0098"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0027"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0007"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
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
      "id": "obs-0007"
    },
    {
      "id": "obs-0008"
    },
    {
      "id": "obs-0009"
    },
    {
      "id": "obs-0010"
    },
    {
      "id": "obs-0011"
    },
    {
      "id": "obs-0012"
    },
    {
      "id": "obs-0013"
    },
    {
      "id": "obs-0014"
    },
    {
      "id": "obs-0015"
    },
    {
      "id": "obs-0016"
    },
    {
      "id": "obs-0017"
    },
    {
      "id": "obs-0018"
    },
    {
      "id": "obs-0019"
    },
    {
      "id": "obs-0020"
    },
    {
      "id": "obs-0021"
    },
    {
      "id": "obs-0022"
    },
    {
      "id": "obs-0023"
    },
    {
      "id": "obs-0024"
    },
    {
      "id": "obs-0025"
    },
    {
      "id": "obs-0026"
    },
    {
      "id": "obs-0027"
    },
    {
      "id": "obs-0028"
    },
    {
      "id": "obs-0029"
    },
    {
      "id": "obs-0030"
    },
    {
      "id": "obs-0031"
    },
    {
      "id": "obs-0032"
    },
    {
      "id": "obs-0033"
    },
    {
      "id": "obs-0034"
    },
    {
      "id": "obs-0035"
    },
    {
      "id": "obs-0036"
    },
    {
      "id": "obs-0037"
    },
    {
      "id": "obs-0038"
    },
    {
      "id": "obs-0039"
    },
    {
      "id": "obs-0040"
    },
    {
      "id": "obs-0041"
    },
    {
      "id": "obs-0042"
    },
    {
      "id": "obs-0043"
    },
    {
      "id": "obs-0044"
    },
    {
      "id": "obs-0045"
    },
    {
      "id": "obs-0046"
    },
    {
      "id": "obs-0047"
    },
    {

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
  "count": 309,
  "instructions": [
    {
      "address": "00ba8830",
      "instruction": "SUB ESP,0x1c"
    },
    {
      "address": "00ba8833",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00ba8834",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00ba8835",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ba8836",
      "instruction": "MOV ESI,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00ba883a",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00ba883c",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00ba883e",
      "instruction": "PUSH 0x8000"
    },
    {
      "address": "00ba8843",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ba8845",
      "instruction": "MOV dword ptr [ESP + 0x14],EBP"
    },
    {
      "address": "00ba8849",
      "instruction": "MOV dword ptr [ESP + 0x10],EBX"
    },
    {
      "address": "00ba884d",
      "instruction": "CALL 0x00bb9af0"
    },
    {
      "address": "00ba8852",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00ba8854",
      "instruction": "JZ 0x00ba885c"
    },
    {
      "address": "00ba8856",
      "instruction": "MOV byte ptr [ESI + 0xac],BL"
    },
    {
      "address": "00ba885c",
      "instruction": "CMP byte ptr [ESI + 0xac],BL"
    },
    {
      "address": "00ba8862",
      "instruction": "JNZ 0x00ba8c29"
    },
    {
      "address": "00ba8868",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ba8869",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00ba886b",
      "instruction": "PUSH 0x100"
    },
    {
      "address": "00ba8870",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ba8872",
      "instruction": "CALL 0x00bb9b00"
    },
    {
      "address": "00ba8877",
      "instruction": "CALL 0x004010a0"
    },
    {
      "address": "00ba887c",
      "instruction": "MOVZX ECX,byte ptr [ESI + 0xac]"
    },
    {
      "address": "00ba8883",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00ba8885",
      "instruction": "SHL ECX,0x18"
    },
    {
      "address": "00ba8888",
      "instruction": "ADD ECX,dword ptr [ESI + 0x70]"
    },
    {
      "address": "00ba888b",
      "instruction": "LEA EAX,[ESP + 0x30]"
    },
    {
      "address": "00ba888f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ba8890",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00ba8891",
      "instruction": "MOV dword ptr [ESP + 0x18],EDI"
    },
    {
      "address": "00ba8895",
      "instruction": "MOV dword ptr [ESP + 0x38],EBX"
    },
    {
      "address": "00ba8899",
      "instruction": "CALL 0x00ba61b0"
    },
    {
      "address": "00ba889e",
      "instruction": "MOV EDX,dword ptr [0x0156c63c]"
    },
    {
      "address": "00ba88a4",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00ba88a7",
      "instruction": "CMP EDX,dword ptr [0x0156c640]"
    },
    {
      "address": "00ba88ad",
      "instruction": "JNZ 0x00ba88c7"
    },
    {
      "address": "00ba88af",
      "instruction": "PUSH 0x7e1310a"
    },
    {
      "address": "00ba88b4",
      "instruction": "LEA EAX,[ESP + 0x1c]"
    },
    {
      "address": "00ba88b8",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ba88b9",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00ba88bb",
      "instruction": "MOV EBX,0x1"
    },
    {
      "address": "00ba88c0",
      "instruction": "CALL 0x005ecf80"
    },
    {
      "address": "00ba88c5",
      "instruction": "JMP 0x00ba88cc"
    },
    {
      "address": "00ba88c7",
      "instruction": "MOV EAX,0x156c63c"
    },
    {
      "address": "00ba88cc",
      "instruction": "MOV EDI,dword ptr [ESP + 0x30]"
    },
    {
      "address": "00ba88d0",
      "instruction": "LEA ECX,[EDI + 0x18]"
    },
    {
      "address": "00ba88d3",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "00ba88d5",
      "instruction": "JZ 0x00ba88e3"
    },
    {
      "address": "00ba88d7",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00ba88da",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00ba88dc",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00ba88dd",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ba88de",
      "instruction": "CALL 0x00423650"
    },
    {
      "address": "00ba88e3",
      "instruction": "TEST BL,0x1"
    },
    {
      "address": "00ba88e6",
      "instruction": "JZ 0x00ba8907"
    },
    {
      "address": "00ba88e8",
      "instruction": "MOV ECX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00ba88ec",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00ba88f0",
      "instruction": "SUB ECX,EAX"
    },
    {
      "address": "00ba88f2",
      "instruction": "AND ECX,0xfffffffe"
    },
    {
      "address": "00ba88f5",
      "instruction": "CMP ECX,0x2"
    },
    {
      "address": "00ba88f8",
      "instruction": "JLE 0x00ba8907"
    },
    {
      "address": "00ba88fa",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00ba88fc",
      "instruction": "JZ 0x00ba8907"
    },
    {
      "address": "00ba88fe",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ba88ff",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "00ba8904",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00ba8907",
      "instruction": "MOV dword ptr [EDI + 0x2c],0x2"
    },
    {
      "address": "00ba890e",
      "instruction": "MOV dword ptr [EDI + 0x28],0x5"
    },
    {
      "address": "00ba8915",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00ba8917",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ba8919",
      "instruction": "MOV dword ptr [EDI + 0x194],0x1"
    },
    {
     
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
  "body_end": "00ba8c31",
  "body_span_bytes": 1026,
  "body_start": "00ba8830",
  "callees": [
    "FUN_00b8dde0",
    "FUN_00f47380",
    "FUN_00f48a80",
    "FUN_00ba61b0",
    "FUN_00989360",
    "FUN_00ba8010",
    "FUN_00bb9b00",
    "FUN_00423650",
    "Simulator::cSpaceNames::Get",
    "FUN_00b8d8e0",
    "FUN_00b3d3d0",
    "FUN_005ecf80",
    "FUN_0103ca40",
    "FUN_00ba6310",
    "FUN_00bb9af0",
    "FUN_00ba64a0"
  ],
  "callers": [
    "FUN_00bb7620",
    "FUN_00bb6700",
    "FUN_00bb6040",
    "FUN_00bb7510"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ba8830",
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
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00ba8830",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7a8830",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ba8830(void)",
  "size_bytes": 1026,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ba8830",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "00bb62ba"
    },
    {
      "from": "00bb7675"
    },
    {
      "from": "00bb7768"
    },
    {
      "from": "00bb6712"
    },
    {
      "from": "00bb7537"
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
