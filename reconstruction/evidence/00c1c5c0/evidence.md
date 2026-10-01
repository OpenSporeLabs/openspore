# Evidence 0x00c1c5c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `deab567b6f14ae2ff407dde2b964b3ed0d931c3162dd291a0d09beea2bd3b7d7`

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
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10",
      "entry_ESP+0x14"
    ],
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
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x14",
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
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 20,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x14"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +28, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched"
  ],
  "cleanup": {
    "bytes": 20,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x14",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "d9160329580878df2a696917981f81eb05738dd41767cac7bac09566a03e118d",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0101"
      ],
      "claim": "the callee pops 20 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 20,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0023",
        "obs-0067",
        "obs-0075"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 4,
        "total_bytes": 20
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0019",
        "obs-0023",
        "obs-0025",
        "obs-0029",
        "obs-0030"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          192,
          672,
          688,
          816,
          2992,
          3992
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0019",
        "obs-0023",
        "obs-0025",
        "obs-0029",
        "obs-0030",
        "obs-0101"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0101"
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
      "id": 
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
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10",
      "entry_ESP+0x14"
    ],
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
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x14",
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
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 20,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x14"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +28, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched"
  ],
  "cleanup": {
    "bytes": 20,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x14",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "d9160329580878df2a696917981f81eb05738dd41767cac7bac09566a03e118d",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0101"
      ],
      "claim": "the callee pops 20 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 20,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0023",
        "obs-0067",
        "obs-0075"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 4,
        "total_bytes": 20
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0019",
        "obs-0023",
        "obs-0025",
        "obs-0029",
        "obs-0030"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          192,
          672,
          688,
          816,
          2992,
          3992
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0019",
        "obs-0023",
        "obs-0025",
        "obs-0029",
        "obs-0030",
        "obs-0101"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0101"
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
      "id": 
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
    "va": "0x00c0ce80"
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
    "name": null,
    "reconstructed": false,
    "va": "0x00bc4900"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c27dd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d31a70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d32fd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d62d90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d62f60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d630c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d63560"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d64a90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d6ce10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d6e3a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d6e910"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d6f800"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d70c70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d71060"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d71780"
  }
]
```

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
  "count": 196,
  "instructions": [
    {
      "address": "00c1c5c0",
      "instruction": "SUB ESP,0x90"
    },
    {
      "address": "00c1c5c6",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c1c5c7",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c1c5c8",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c1c5c9",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c1c5ca",
      "instruction": "MOV EDI,dword ptr [ESP + 0xac]"
    },
    {
      "address": "00c1c5d1",
      "instruction": "MOVSS XMM0,dword ptr [EDI]"
    },
    {
      "address": "00c1c5d5",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c1c5d7",
      "instruction": "MOV EAX,dword ptr [ESI + 0xc0]"
    },
    {
      "address": "00c1c5dd",
      "instruction": "MOV EDX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "00c1c5e0",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM0"
    },
    {
      "address": "00c1c5e6",
      "instruction": "MOVSS XMM0,dword ptr [EDI + 0x4]"
    },
    {
      "address": "00c1c5eb",
      "instruction": "LEA EBP,[ESI + 0xc0]"
    },
    {
      "address": "00c1c5f1",
      "instruction": "MOVSS dword ptr [ESP + 0x18],XMM0"
    },
    {
      "address": "00c1c5f7",
      "instruction": "MOVSS XMM0,dword ptr [EDI + 0x8]"
    },
    {
      "address": "00c1c5fc",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00c1c5fe",
      "instruction": "MOVSS dword ptr [ESP + 0x1c],XMM0"
    },
    {
      "address": "00c1c604",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c1c606",
      "instruction": "MOV ECX,dword ptr [ESP + 0xa8]"
    },
    {
      "address": "00c1c60d",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00c1c60f",
      "instruction": "MOV EDX,EAX"
    },
    {
      "address": "00c1c611",
      "instruction": "CMP dword ptr [ESI + 0x2b0],EBX"
    },
    {
      "address": "00c1c617",
      "instruction": "JNZ 0x00c1c791"
    },
    {
      "address": "00c1c61d",
      "instruction": "MOVSS XMM0,dword ptr [EDX]"
    },
    {
      "address": "00c1c621",
      "instruction": "UCOMISS XMM0,dword ptr [0x0168d910]"
    },
    {
      "address": "00c1c628",
      "instruction": "LAHF"
    },
    {
      "address": "00c1c629",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00c1c62c",
      "instruction": "JP 0x00c1c656"
    },
    {
      "address": "00c1c62e",
      "instruction": "MOVSS XMM0,dword ptr [EDX + 0x4]"
    },
    {
      "address": "00c1c633",
      "instruction": "UCOMISS XMM0,dword ptr [0x0168d914]"
    },
    {
      "address": "00c1c63a",
      "instruction": "LAHF"
    },
    {
      "address": "00c1c63b",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00c1c63e",
      "instruction": "JP 0x00c1c656"
    },
    {
      "address": "00c1c640",
      "instruction": "MOVSS XMM0,dword ptr [EDX + 0x8]"
    },
    {
      "address": "00c1c645",
      "instruction": "UCOMISS XMM0,dword ptr [0x0168d918]"
    },
    {
      "address": "00c1c64c",
      "instruction": "LAHF"
    },
    {
      "address": "00c1c64d",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00c1c650",
      "instruction": "JNP 0x00c1c791"
    },
    {
      "address": "00c1c656",
      "instruction": "MOVSS XMM3,dword ptr [ECX]"
    },
    {
      "address": "00c1c65a",
      "instruction": "FLD float ptr [ECX + 0x8]"
    },
    {
      "address": "00c1c65d",
      "instruction": "FLD float ptr [ECX + 0x4]"
    },
    {
      "address": "00c1c660",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM3"
    },
    {
      "address": "00c1c666",
      "instruction": "FLD float ptr [ESP + 0x10]"
    },
    {
      "address": "00c1c66a",
      "instruction": "MOVSS XMM1,dword ptr [ECX + 0x4]"
    },
    {
      "address": "00c1c66f",
      "instruction": "FMUL ST0"
    },
    {
      "address": "00c1c671",
      "instruction": "MOVSS XMM2,dword ptr [ECX + 0x8]"
    },
    {
      "address": "00c1c676",
      "instruction": "FLD ST1"
    },
    {
      "address": "00c1c678",
      "instruction": "MOVSS XMM5,dword ptr [EDI + 0x4]"
    },
    {
      "address": "00c1c67d",
      "instruction": "FMULP ST2"
    },
    {
      "address": "00c1c67f",
      "instruction": "MOVSS XMM6,dword ptr [EDI]"
    },
    {
      "address": "00c1c683",
      "instruction": "MOVSS XMM4,dword ptr [EDI + 0x8]"
    },
    {
      "address": "00c1c688",
      "instruction": "MOVAPS XMM7,XMM6"
    },
    {
      "address": "00c1c68b",
      "instruction": "FADDP"
    },
    {
      "address": "00c1c68d",
      "instruction": "FLD ST1"
    },
    {
      "address": "00c1c68f",
      "instruction": "FMULP ST2"
    },
    {
      "address": "00c1c691",
      "instruction": "FADDP"
    },
    {
      "address": "00c1c693",
      "instruction": "FSQRT"
    },
    {
      "address": "00c1c695",
      "instruction": "FLD1"
    },
    {
      "address": "00c1c697",
      "instruction": "FLD ST0"
    },
    {
      "address": "00c1c699",
      "instruction": "FDIVRP ST2,ST0"
    },
    {
      "address": "00c1c69b",
      "instruction": "FXCH"
    },
    {
      "address": "00c1c69d",
      "instruction": "FSTP float ptr [ESP + 0x10]"
    },
    {
      "address": "00c1c6a1",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c1c6a7",
      "instruction": "MULSS XMM3,XMM0"
    },
    {
      "address": "00c1c6ab",
      "instruction": "MULSS XMM2,XMM0"
    },
    {
      "address": "00c1c6af",
      "instruction": "MULSS XMM1,XMM0"
    },
    {
      "address": "00c1c6b3",
      "instruction": "MULSS XMM7,XMM3"
    },
    {
      "address": "00c1c6b7",
      "instruction": "MOVAPS XMM0,XMM5"
    },
    {
      "address": "00c1c6ba",
      "instruction": "MULSS XMM0,XMM1"
    },
    {
      "address": "00c1c6be",
      "instruction": "ADDSS XMM0,XMM7"
    },
    {
      "address": "00c1c6c2",
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
  "original_bytes": 14101,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-13-C4-CREATURE-WAVE3\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460\",\n      \"va\": \"0x00c1d460\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The concrete container at creature+0xBC0, including its real extent, and the semantics of the creature+0x2A0, +0x2B0 and +0x330 fields remain runtime-gated.\",\n    \"The concrete type and lifetime of the request submitted through vtable+0xDC remain runtime-gated.\",\n    \"The intermediate reciprocal-length accumulation is modelled in binary64 while the original uses x87 80-bit extended precision; the difference is bounded by one unit in the last place of the sum and is not claimed as bit-exact at the original's internal precision.\",\n    \"The meaning of the handle header word at handle-0x04 remains runtime-gated.\",\n    \"Whether the unconditional position and basis callback has observable side effects beyond its return value, and what the creature+0x2B0 field suppresses at the caller level, remain runtime-gated.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0ce80\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bc4900\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c27dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d31a70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d32fd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d62d90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d62f60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d630c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d63560\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d64a90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d6ce10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d6e3a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d6e910\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d6f800\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d70c70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d71060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d71780\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d71fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d74060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d7e6e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d7ee90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d7f790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d7ff20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d80a50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d81220\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d841a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d84ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d86690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d86a30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d87620\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d89c50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d89fb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d8a2a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d8dcc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d92560\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d92660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d92880\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d932e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d93670\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d93880\"\n      },\n      {\n        \"name\": nul
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
  "body_end": "00c1c8dd",
  "body_span_bytes": 798,
  "body_start": "00c1c5c0",
  "callees": [
    "FUN_00ac4570",
    "FUN_00f47380",
    "FUN_00c0ce80"
  ],
  "callers": [
    "FUN_00dabc30",
    "FUN_00dba649",
    "FUN_00d32fd0",
    "FUN_00d71060",
    "FUN_00ec1830",
    "FUN_00d71780",
    "FUN_00dad390",
    "FUN_00d932e0",
    "FUN_00d841a0",
    "FUN_00d89fb0",
    "FUN_00db1790",
    "FUN_00d94260",
    "FUN_00d7ee90",
    "FUN_00da2fd0",
    "FUN_00d6f800",
    "FUN_00d62d90",
    "FUN_00d9d5b0",
    "FUN_00d630c0",
    "FUN_00d92660",
    "FUN_00dab1f0",
    "FUN_00dabdf0",
    "FUN_00d7ff20",
    "FUN_00d9d1e0",
    "FUN_00d70c70",
    "FUN_00d93fd0",
    "FUN_00d31a70",
    "FUN_00d952e0",
    "FUN_00d6e910",
    "FUN_00d92560",
    "FUN_00c27dd0",
    "FUN_00d63560",
    "FUN_00dadbc0",
    "FUN_00ec2a70",
    "FUN_00d7e6e0",
    "FUN_00d8dcc0",
    "FUN_00dace20",
    "FUN_00d6e3a0",
    "FUN_00d62f60",
    "FUN_00d9d100",
    "FUN_00d86a30",
    "FUN_00db33d0",
    "FUN_00d80a50",
    "FUN_00d6ce10",
    "FUN_00d8a2a0",
    "FUN_00d89c50",
    "FUN_00da2360",
    "FUN_00d9e570",
    "FUN_00d92880",
    "FUN_00d71fa0",
    "FUN_00d86690",
    "FUN_00d93880",
    "FUN_00d74060",
    "FUN_00d97d93",
    "FUN_00d7f790",
    "FUN_00d87620",
    "FUN_00d93670",
    "FUN_00d81220",
    "FUN_00d9c6f0",
    "FUN_00d64a90",
    "FUN_00bc4900",
    "FUN_00d84ec0",
    "FUN_00dbb840"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c1c5c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_84",
      "storage": "Stack[-0x84]:4",
      "type": "undefined4"
    },
    {
      "name": "local_88",
      "storage": "Stack[-0x88]:4",
      "type": "undefined4"
    },
    {
      "name": "local_8c",
      "storage": "Stack[-0x8c]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00c1c5c0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x81c5c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c1c5c0(void)",
  "size_bytes": 798,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c1c5c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 88,
  "xrefs": [
    {
      "from": "00bc4bcf"
    },
    {
      "from": "00c27fda"
    },
    {
      "from": "00d3229e"
    },
    {
      "from": "00d62f03"
    },
    {
      "from": "00d63067"
    },
    {
      "from": "00d632a0"
    },
    {
      "from": "00d63359"
    },
    {
      "from": "00d63ab6"
    },
    {
      "from": "00d64c26"
    },
    {
      "from": "00d6cf50"
    },
    {
      "from": "00d6e5fc"
    },
    {
      "from": "00d6e665"
    },
    {
      "from": "00d6edfc"
    },
    {
      "from": "00d6f8e8"
    },
    {
      "from": "00d70e3e"
    },
    {
      "from": "00d7198c"
    },
    {
      "from": "00d720eb"
    },
    {
      "from": "00d7e81d"
    },
    {
      "from": "00d7ff00"
    },
    {
      "from": "00d8034e"
    },
    {
      "from": "00d80802"
    },
    {
      "from": "00d80a25"
    },
    {
      "from": "00d810d5"
    },
    {
      "from": "00d8131d"
    },
    {
      "from": "00d84fac"
    },
    {
      "from": "00d867f4"
    },
    {
      "from": "00d86ccb"
    },
    {
      "from": "00d89eb8"
    },
    {
      "from": "00d8a18f"
    },
    {
      "from": "00d8a478"
    },
    {
      "from": "00d8ddc5"
    },
    {
      "from": "00d92652"
    },
    {
      "from": "00d92759"
    },
    {
      "from": "00d92981"
    },
    {
      "from": "00d933b2"
    },
    {
      "from": "00d93783"
    },
    {
      "from": "00d93db8"
    },
    {
      "from": "00d941b5"
    },
    {
      "from": "00d9438f"
    },
    {
      "from": "00d954f0"
    },
    {
      "from": "00d97f63"
    },
    {
      "from": "00d9c93e"
    },
    {
      "from": "00d9d1b7"
    },
    {
      "from": "00d9d7dc"
    },
    {
      "from": "00dab4f4"
    },
    {
      "from": "00dabcf1"
    },
    {
      "from": "00dad0a5"
    },
    {
      "from": "00dadcc2"
    },
    {
      "from": "00dbaa2e"
    },
    {
      "from": "00ec2c8a"
    },
    {
      "from": "00d337b6"
    },
    {
      "from": "00d71341"
    },
    {
      "from": "00dbbd9c"
    },
    {
      "from": "00dbbdc7"
    },
    {
      "from": "00dbbeef"
    },
    {
      "from": "00ec1a82"
    },
    {
      "from": "00d9d2b0"
    },
    {
      "from": "00dac04f"
    },
    {
      "from": "00dac1c3"
    },
    {
      "from": "00dac26b"
    },
    {
      "from": "00d8434e"
    },
    {
      "from": "00d7463e"
    },
    {
      "from": "00d74d0f"
    },
    {
      "from": "00d9e7fe"
    },
    {
      "from": "00d7f188"
    },
    {
      "from": "00db360a"
    },
    {
      "from": "00d87b61"
    },
    {
      "from": "00da2f32"
    },
    {
      "from": "00da3390"
    },
    {
      "from": "00d71b0c"
    },
    {
      "from": "00db1977"
    },
    {
      "from": "00dad516"
    },
    {
      "from": "00dad575"
    },
    {
      "from": "00dad7e4"
    },
    {
      "from": "00da2695"
    },
    {
      "from": "00d79bfc"
    },
    {
      "from": "00d687e0"
    },
    {
      "from": "00d6d86c"
    },
    {
      "from": "00d6d8ce"
    },
    {
      "from": "00d76315"
  
[TRUNCATED]
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
  "files": [
    "reconstruction/staging/pkg13-c4-creature-wave3/creature_wave3.cpp",
    "reconstruction/staging/pkg13-c4-creature-wave3/creature_wave3.hpp",
    "reconstruction/staging/pkg13-c4-creature-wave3/creature_wave3_model_test.cpp",
    "src/reconstruction/pkg13_c4_creature_wave3/creature_wave3.cpp",
    "src/reconstruction/pkg13_c4_creature_wave3/creature_wave3.hpp",
    "src/reconstruction/pkg13_c4_creature_wave3/creature_wave3_model_test.cpp",
    "src/reconstruction/pkg13_c4_creature_wave3/metadata_package_validation.py"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c4-creature-wave3/00c1c5c0.json"
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
    "Exercise a NaN basis and a zero-length basis in the original to confirm the recorded NaN propagation and the absence of a length guard.",
    "No original-process trace, differential run under Wine, or runtime validation has been performed.",
    "Observe a real vtable+0xDC submission to learn whether the request pointer escapes and whether the handle header word at handle-0x04 is a reference count.",
    "Observe the 0x00ac4570 container at creature+0xBC0 to confirm the 60-byte element semantics.",
    "Observe the concrete creature+0x2B0, +0x2A0 and +0x330 field semantics in an original process.",
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
  "const Vector3*",
  "float",
  "int32_t",
  "opaque 116-byte POD matching Simulator::cLocomotionRequest"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
