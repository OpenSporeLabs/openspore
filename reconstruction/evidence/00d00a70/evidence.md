# Evidence 0x00d00a70

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `31b7dad7c244051b7cd22d740f3c33a360f33f344cfaad54d15495b9d29ce7f1`

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
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -68, so the listing is not one path",
    "unparsed_lines_present: 2 line(s) matched no grammar rule"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "02b255241c1df799ace4915500607a0f7927976879d0b571c6c075f9300439f2",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0031",
        "obs-0033",
        "obs-0035",
        "obs-0037",
        "obs-0039"
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
        "obs-0004",
        "obs-0006",
        "obs-0011"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0012"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          16,
          20,
          24,
          28
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0031",
        "obs-0033",
        "obs-0035",
        "obs-0037",
        "obs-0039"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0031",
        "obs-0033",
        "obs-0035",
        "obs-0037",
        "obs-0039"
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
      "at": "0x00d00a70",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00d00a70",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00d00a73",
      "count": 9,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x1c]",
      "reg": "ESP"
    },
    {
      "at": "0x00d00a73",
      "base": "ESP",
 
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
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -68, so the listing is not one path",
    "unparsed_lines_present: 2 line(s) matched no grammar rule"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "02b255241c1df799ace4915500607a0f7927976879d0b571c6c075f9300439f2",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0031",
        "obs-0033",
        "obs-0035",
        "obs-0037",
        "obs-0039"
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
        "obs-0004",
        "obs-0006",
        "obs-0011"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0012"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          16,
          20,
          24,
          28
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0031",
        "obs-0033",
        "obs-0035",
        "obs-0037",
        "obs-0039"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0031",
        "obs-0033",
        "obs-0035",
        "obs-0037",
        "obs-0039"
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
      "at": "0x00d00a70",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00d00a70",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00d00a73",
      "count": 9,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x1c]",
      "reg": "ESP"
    },
    {
      "at": "0x00d00a73",
      "base": "ESP",
 
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae2e20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aea3d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aee830"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b68090"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba58f3"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba5a60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba5bd3"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba5d30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00be88d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bef620"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf5cb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf74a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf8440"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bfa660"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bfbbf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0e6a0"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nundefined4 __thiscall\nFUN_00d00a70(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)\n\n{\n  float10 fVar1;\n  float fVar2;\n  \n  fVar1 = (float10)FUN_00d05a20(param_2,param_3,param_4);\n  fVar2 = (float)fVar1;\n  if ((float)fVar1 <= -10.0) {\n    fVar2 = -10.0;\n  }\n  if (10.0 <= fVar2) {\n    fVar2 = 10.0;\n  }\n  if ((*(float *)(param_1 + 0x14) < fVar2) && (fVar2 < *(float *)(param_1 + 0x18))) {\n    return 2;\n  }\n  if ((*(float *)(param_1 + 0x18) <= fVar2) && (fVar2 < *(float *)(param_1 + 0x1c))) {\n    return 3;\n  }\n  if (*(float *)(param_1 + 0x1c) <= fVar2) {\n    return 4;\n  }\n  if ((fVar2 <= *(float *)(param_1 + 0x14)) &&\n     (*(float *)(param_1 + 0x10) <= fVar2 && fVar2 != *(float *)(param_1 + 0x10))) {\n    return 1;\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 58,
  "instructions": [
    {
      "address": "00d00a70",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "00d00a73",
      "instruction": "MOV EAX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00d00a77",
      "instruction": "MOV EDX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00d00a7b",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d00a7c",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00d00a7e",
      "instruction": "MOV ECX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00d00a82",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d00a83",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d00a84",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00d00a85",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00d00a87",
      "instruction": "CALL 0x00d05a20"
    },
    {
      "address": "00d00a8c",
      "instruction": "FSTP float ptr [ESP + 0x4]"
    },
    {
      "address": "00d00a90",
      "instruction": "MOVSS XMM0,dword ptr [0x01478d5c]"
    },
    {
      "address": "00d00a98",
      "instruction": "MOVSS dword ptr [ESP + 0x1c],XMM0"
    },
    {
      "address": "00d00a9e",
      "instruction": "MOVSS XMM0,dword ptr [0x01478d60]"
    },
    {
      "address": "00d00aa6",
      "instruction": "MOVSS dword ptr [ESP + 0x20],XMM0"
    },
    {
      "address": "00d00aac",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00d00ab2",
      "instruction": "MAXSS XMM0,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00d00ab8",
      "instruction": "MINSS XMM0,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00d00abe",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "00d00ac4",
      "instruction": "MOVSS XMM1,dword ptr [ESI + 0x14]"
    },
    {
      "address": "00d00ac9",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00d00acf",
      "instruction": "COMISS XMM0,XMM1"
    },
    {
      "address": "00d00ad2",
      "instruction": "JBE 0x00d00aea"
    },
    {
      "address": "00d00ad4",
      "instruction": "MOVSS XMM2,dword ptr [ESI + 0x18]"
    },
    {
      "address": "00d00ad9",
      "instruction": "COMISS XMM2,XMM0"
    },
    {
      "address": "00d00adc",
      "instruction": "JBE 0x00d00aea"
    },
    {
      "address": "00d00ade",
      "instruction": "MOV EAX,0x2"
    },
    {
      "address": "00d00ae3",
      "instruction": "POP ESI"
    },
    {
      "address": "00d00ae4",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00d00ae7",
      "instruction": "RET 0xc"
    },
    {
      "address": "00d00aea",
      "instruction": "COMISS XMM0,dword ptr [ESI + 0x18]"
    },
    {
      "address": "00d00aee",
      "instruction": "JC 0x00d00b06"
    },
    {
      "address": "00d00af0",
      "instruction": "MOVSS XMM2,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "00d00af5",
      "instruction": "COMISS XMM2,XMM0"
    },
    {
      "address": "00d00af8",
      "instruction": "JBE 0x00d00b06"
    },
    {
      "address": "00d00afa",
      "instruction": "MOV EAX,0x3"
    },
    {
      "address": "00d00aff",
      "instruction": "POP ESI"
    },
    {
      "address": "00d00b00",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00d00b03",
      "instruction": "RET 0xc"
    },
    {
      "address": "00d00b06",
      "instruction": "COMISS XMM0,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "00d00b0a",
      "instruction": "JC 0x00d00b18"
    },
    {
      "address": "00d00b0c",
      "instruction": "MOV EAX,0x4"
    },
    {
      "address": "00d00b11",
      "instruction": "POP ESI"
    },
    {
      "address": "00d00b12",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00d00b15",
      "instruction": "RET 0xc"
    },
    {
      "address": "00d00b18",
      "instruction": "COMISS XMM1,XMM0"
    },
    {
      "address": "00d00b1b",
      "instruction": "JC 0x00d00b2f"
    },
    {
      "address": "00d00b1d",
      "instruction": "COMISS XMM0,dword ptr [ESI + 0x10]"
    },
    {
      "address": "00d00b21",
      "instruction": "JBE 0x00d00b2f"
    },
    {
      "address": "00d00b23",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "00d00b28",
      "instruction": "POP ESI"
    },
    {
      "address": "00d00b29",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00d00b2c",
      "instruction": "RET 0xc"
    },
    {
      "address": "00d00b2f",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00d00b31",
      "instruction": "POP ESI"
    },
    {
      "address": "00d00b32",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00d00b35",
      "instruction": "RET 0xc"
    }
  ]
}
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
  "original_bytes": 12496,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae2e20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aea3d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aee830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b68090\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba58f3\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5a60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5bd3\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5d30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00be88d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bef620\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf5cb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf74a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf8440\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bfa660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bfbbf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0e6a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c238b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c23da0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c2f5f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c2f690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8eb90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cacf40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ccefb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ce48f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ceee30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cfe820\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cfe930\"\n      },\n      {\n        \"name\": \"RelationshipScoreBand_00d00d00\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d00d00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d00ee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d06270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d5ccf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d9cf70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00da6b10\"\n      },\n      {\n        \"name\": null,\n        \"reconstru
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
  "body_end": "00d00b37",
  "body_span_bytes": 200,
  "body_start": "00d00a70",
  "callees": [
    "FUN_00d05a20"
  ],
  "callers": [
    "FUN_00be88d0",
    "FUN_00dd2650",
    "FUN_00cacf40",
    "FUN_00ae2e20",
    "FUN_00bfbbf0",
    "FUN_00bef620",
    "FUN_00aea3d0",
    "FUN_00c0e6a0",
    "FUN_00c8eb90",
    "FUN_00ce48f0",
    "FUN_00b68090",
    "FUN_00ba5a60",
    "FUN_00bf5cb0",
    "FUN_00bfa660",
    "FUN_00dd4950",
    "FUN_00d5ccf0",
    "FUN_00ba5d30",
    "FUN_00ccefb0",
    "FUN_00e2d6a0",
    "FUN_00aee830",
    "FUN_00daa170",
    "FUN_00cfe820",
    "FUN_00ba5bd3",
    "FUN_00d00d00",
    "FUN_00d06270",
    "FUN_00c23da0",
    "FUN_00c2f5f0",
    "FUN_00da6b10",
    "FUN_00d00ee0",
    "FUN_0102f820",
    "FUN_00bf74a0",
    "FUN_00cfe930",
    "FUN_00c2f690",
    "FUN_00ceee30",
    "FUN_00dc67d0",
    "FUN_00ba58f3",
    "FUN_00da9db0",
    "FUN_00bf8440",
    "FUN_0102df20",
    "FUN_00d9cf70",
    "FUN_00c238b0",
    "FUN_00db6130"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d00a70",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "fVar2",
      "storage": "register:00001200:4",
      "type": "float"
    },
    {
      "name": "param_4",
      "storage": "Stack[0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "fVar1",
      "storage": "register:00001100:10",
      "type": "float10"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "FUN_00d00a70",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x900a70",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00d00a70(void)",
  "size_bytes": 200,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d00a70",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 60,
  "xrefs": [
    {
      "from": "00ba5cf9"
    },
    {
      "from": "00d00f30"
    },
    {
      "from": "00d00f57"
    },
    {
      "from": "00d5cf67"
    },
    {
      "from": "00ae2e2c"
    },
    {
      "from": "00be894e"
    },
    {
      "from": "00ba5b9b"
    },
    {
      "from": "00bfbdcb"
    },
    {
      "from": "00bfbf1e"
    },
    {
      "from": "00bfbfd1"
    },
    {
      "from": "00ba5d77"
    },
    {
      "from": "00bef62c"
    },
    {
      "from": "00bf5d4f"
    },
    {
      "from": "00bf5dff"
    },
    {
      "from": "00bf627f"
    },
    {
      "from": "00bf754e"
    },
    {
      "from": "00bf8537"
    },
    {
      "from": "00bfa79e"
    },
    {
      "from": "00bfa981"
    },
    {
      "from": "00ceee67"
    },
    {
      "from": "00ceeeb1"
    },
    {
      "from": "00cfe861"
    },
    {
      "from": "00cfe99d"
    },
    {
      "from": "00d00d13"
    },
    {
      "from": "00dd26d2"
    },
    {
      "from": "00dd49d2"
    },
    {
      "from": "0102eaab"
    },
    {
      "from": "0102f876"
    },
    {
      "from": "00aea457"
    },
    {
      "from": "00aea47d"
    },
    {
      "from": "00aea496"
    },
    {
      "from": "00aea4af"
    },
    {
      "from": "00aea4c8"
    },
    {
      "from": "00aee8bf"
    },
    {
      "from": "00aee8da"
    },
    {
      "from": "00b68177"
    },
    {
      "from": "00ba5a03"
    },
    {
      "from": "00c0e6fe"
    },
    {
      "from": "00c239bf"
    },
    {
      "from": "00c23ded"
    },
    {
      "from": "00c2f61f"
    },
    {
      "from": "00c2f6e1"
    },
    {
      "from": "00c8ebc4"
    },
    {
      "from": "00cad732"
    },
    {
      "from": "00ccf769"
    },
    {
      "from": "00ccfb8c"
    },
    {
      "from": "00ccfbd2"
    },
    {
      "from": "00ce4baa"
    },
    {
      "from": "00d9cf98"
    },
    {
      "from": "00da6b85"
    },
    {
      "from": "00da9eb0"
    },
    {
      "from": "00daa25e"
    },
    {
      "from": "00daa26e"
    },
    {
      "from": "00db63cf"
    },
    {
      "from": "00dc68b3"
    },
    {
      "from": "00e2e262"
    },
    {
      "from": "00aed895"
    },
    {
      "from": "00d0631b"
    },
    {
      "from": "00d06333"
    },
    {
      "from": "00cdf3a4"
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
  "files": [],
  "handoffs": [],
  "metadata": []
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
  "gates": [],
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
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

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
