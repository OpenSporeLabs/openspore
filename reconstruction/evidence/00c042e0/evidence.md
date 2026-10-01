# Evidence 0x00c042e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c7a02937eaafa4dfca3abbd75d9bcbfa006f2948f608ca642aa9cea02e3e825f`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +56, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "c85da188ae93395f4e4c6e47e485b8543b923a413ba780bf0370c7118316755f",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
        "obs-0032"
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
        "obs-0002",
        "obs-0003",
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          88,
          2848,
          2892,
          2904,
          3756,
          5748
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0009",
        "obs-0032"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0032"
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
        "obs-0032"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00c042e0",
      "count": 36,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c042e1",
      "count": 17,
      "first_use": 1,
      "first_write_index": 8,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c042e1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c042e3",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x58]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c042e6",
      "count": 20,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x14]",
      "reg": "EAX"
    },
    {
      "at": "0x00c042e6",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x14]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c042ee",
      "count": 12,
      "first_use": 6,
      "first_write_index": 3,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00c042ee",
      "base": "EDX",
      "disp": null,
      "id": "obs-0008",
      "index": 6,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00c042f6",
      "definite": true,
      "id": "obs-0009",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c04357",
      "id": "obs-0010",
      "index": 32,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00bcb660",
      "target": "0x00bcb660"
    },
    {
      "at": "0x00c04363",
      "id": "obs-0011",
      "index": 35,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c0b370",
      "target": "0x00c0b370"
    },
    {
      "at": "0x00c0438c",
      "id": "obs-0012",
      "index": 49,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c0b770",
      "target": "0x00c0b770"
    },
    {
      "at": "0x00c043b2",
      "id": "obs-0013",
      "index": 60,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c0b770",
      "target": "0x00c0b770"
    },
    {
      "at": "0x00c043d8",
      "id": "obs-0014",
      "index": 71,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c0b770",
      "target": "0x00c0b770"
    },
    {
      "at": "0x00c043f3",
      "id": "ob
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +56, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "c85da188ae93395f4e4c6e47e485b8543b923a413ba780bf0370c7118316755f",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
        "obs-0032"
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
        "obs-0002",
        "obs-0003",
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          88,
          2848,
          2892,
          2904,
          3756,
          5748
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0009",
        "obs-0032"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0032"
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
        "obs-0032"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00c042e0",
      "count": 36,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c042e1",
      "count": 17,
      "first_use": 1,
      "first_write_index": 8,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c042e1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c042e3",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x58]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c042e6",
      "count": 20,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x14]",
      "reg": "EAX"
    },
    {
      "at": "0x00c042e6",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x14]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c042ee",
      "count": 12,
      "first_use": 6,
      "first_write_index": 3,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00c042ee",
      "base": "EDX",
      "disp": null,
      "id": "obs-0008",
      "index": 6,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00c042f6",
      "definite": true,
      "id": "obs-0009",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c04357",
      "id": "obs-0010",
      "index": 32,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00bcb660",
      "target": "0x00bcb660"
    },
    {
      "at": "0x00c04363",
      "id": "obs-0011",
      "index": 35,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c0b370",
      "target": "0x00c0b370"
    },
    {
      "at": "0x00c0438c",
      "id": "obs-0012",
      "index": 49,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c0b770",
      "target": "0x00c0b770"
    },
    {
      "at": "0x00c043b2",
      "id": "obs-0013",
      "index": 60,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c0b770",
      "target": "0x00c0b770"
    },
    {
      "at": "0x00c043d8",
      "id": "obs-0014",
      "index": 71,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c0b770",
      "target": "0x00c0b770"
    },
    {
      "at": "0x00c043f3",
      "id": "ob
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
  "count": 179,
  "instructions": [
    {
      "address": "00c042e0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c042e1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c042e3",
      "instruction": "MOV EAX,dword ptr [ESI + 0x58]"
    },
    {
      "address": "00c042e6",
      "instruction": "MOV EDX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00c042e9",
      "instruction": "LEA ECX,[ESI + 0x58]"
    },
    {
      "address": "00c042ec",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00c042ee",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c042f0",
      "instruction": "MOV EAX,dword ptr [ESI + 0xb58]"
    },
    {
      "address": "00c042f6",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c042f8",
      "instruction": "SHR ECX,0x9"
    },
    {
      "address": "00c042fb",
      "instruction": "TEST CL,0x1"
    },
    {
      "address": "00c042fe",
      "instruction": "JZ 0x00c04314"
    },
    {
      "address": "00c04300",
      "instruction": "MOV dword ptr [ESI + 0xeac],0x2"
    },
    {
      "address": "00c0430a",
      "instruction": "PUSH 0x1590800"
    },
    {
      "address": "00c0430f",
      "instruction": "JMP 0x00c043ed"
    },
    {
      "address": "00c04314",
      "instruction": "MOV EDX,EAX"
    },
    {
      "address": "00c04316",
      "instruction": "SHR EDX,0x8"
    },
    {
      "address": "00c04319",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "00c0431c",
      "instruction": "JZ 0x00c04328"
    },
    {
      "address": "00c0431e",
      "instruction": "PUSH 0x1590888"
    },
    {
      "address": "00c04323",
      "instruction": "JMP 0x00c043ed"
    },
    {
      "address": "00c04328",
      "instruction": "MOV ECX,dword ptr [ESI + 0x1674]"
    },
    {
      "address": "00c0432e",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00c04330",
      "instruction": "JZ 0x00c04345"
    },
    {
      "address": "00c04332",
      "instruction": "CMP dword ptr [ECX + 0x15c],0x9"
    },
    {
      "address": "00c04339",
      "instruction": "JNZ 0x00c04345"
    },
    {
      "address": "00c0433b",
      "instruction": "PUSH 0x1590aa8"
    },
    {
      "address": "00c04340",
      "instruction": "JMP 0x00c043ed"
    },
    {
      "address": "00c04345",
      "instruction": "TEST EAX,0x4000"
    },
    {
      "address": "00c0434a",
      "instruction": "JZ 0x00c0436d"
    },
    {
      "address": "00c0434c",
      "instruction": "MOV ECX,dword ptr [ESI + 0xb4c]"
    },
    {
      "address": "00c04352",
      "instruction": "PUSH 0x1590b30"
    },
    {
      "address": "00c04357",
      "instruction": "CALL 0x00bcb660"
    },
    {
      "address": "00c0435c",
      "instruction": "PUSH 0x609ea52"
    },
    {
      "address": "00c04361",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c04363",
      "instruction": "CALL 0x00c0b370"
    },
    {
      "address": "00c04368",
      "instruction": "JMP 0x00c043f8"
    },
    {
      "address": "00c0436d",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00c0436f",
      "instruction": "JZ 0x00c043d6"
    },
    {
      "address": "00c04371",
      "instruction": "MOV EAX,dword ptr [ECX + 0x15c]"
    },
    {
      "address": "00c04377",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c04379",
      "instruction": "JZ 0x00c043d6"
    },
    {
      "address": "00c0437b",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00c0437e",
      "instruction": "JZ 0x00c043cf"
    },
    {
      "address": "00c04380",
      "instruction": "SUB EAX,0x6"
    },
    {
      "address": "00c04383",
      "instruction": "JZ 0x00c043b0"
    },
    {
      "address": "00c04385",
      "instruction": "SUB EAX,0x4"
    },
    {
      "address": "00c04388",
      "instruction": "JZ 0x00c043a9"
    },
    {
      "address": "00c0438a",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c0438c",
      "instruction": "CALL 0x00c0b770"
    },
    {
      "address": "00c04391",
      "instruction": "MOV ECX,dword ptr [ESI + 0xb4c]"
    },
    {
      "address": "00c04397",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c04399",
      "instruction": "JZ 0x00c043a2"
    },
    {
      "address": "00c0439b",
      "instruction": "PUSH 0x15906f0"
    },
    {
      "address": "00c043a0",
      "instruction": "JMP 0x00c043f3"
    },
    {
      "address": "00c043a2",
      "instruction": "PUSH 0x1590778"
    },
    {
      "address": "00c043a7",
      "instruction": "JMP 0x00c043f3"
    },
    {
      "address": "00c043a9",
      "instruction": "PUSH 0x15aa9e8"
    },
    {
      "address": "00c043ae",
      "instruction": "JMP 0x00c043ed"
    },
    {
      "address": "00c043b0",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c043b2",
      "instruction": "CALL 0x00c0b770"
    },
    {
      "address": "00c043b7",
      "instruction": "MOV ECX,dword ptr [ESI + 0xb4c]"
    },
    {
      "address": "00c043bd",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c043bf",
      "instruction": "JZ 0x00c043c8"
    },
    {
      "address": "00c043c1",
      "instruction": "PUSH 0x1590998"
    },
    {
      "address": "00c043c6",
      "instruction": "JMP 0x00c043f3"
    },
    {
      "address": "00c043c8",
      "instruction": "PUSH 0x1590a20"
    },
    {
      "address": "00c043cd",
      "instruction": "JMP 0x00c043f3"
    },
    {
      "address": "00c043cf",
      "instruction": "PUSH 0x1590910"
    },
    {
      "address": "00c043d4",
      "instruction": "JMP 0x00c043ed"
    },
    {
      "address": "00c043d6",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c043d8",
      "instruction": "CALL 0x00c0b770"
    },
    {
      "address": "00c043dd",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c043
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
  "body_end": "00c04589",
  "body_span_bytes": 682,
  "body_start": "00c042e0",
  "callees": [
    "FUN_00c0b7a0",
    "FUN_00c0b780",
    "FUN_00bcb660",
    "FUN_00b5b800",
    "FUN_004df420",
    "FUN_00c0c0e0",
    "FUN_00c0b370",
    "FUN_00c0b770",
    "Editors::cSpeciesManager::Get"
  ],
  "callers": [
    "FUN_00db5e80",
    "FUN_00d53490",
    "FUN_00c04e50",
    "FUN_00d43e30",
    "FUN_00c04dd0",
    "FUN_01016070",
    "FUN_00c099e0",
    "FUN_00c05d40",
    "FUN_00c09fa0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c042e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00c042e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8042e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c042e0(void)",
  "size_bytes": 682,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c042e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 11,
  "xrefs": [
    {
      "from": "00c0aa87"
    },
    {
      "from": "00c09f42"
    },
    {
      "from": "00c04e30"
    },
    {
      "from": "00c05dcd"
    },
    {
      "from": "00d53581"
    },
    {
      "from": "00db5fcf"
    },
    {
      "from": "01016271"
    },
    {
      "from": "00c04f70"
    },
    {
      "from": "00d44737"
    },
    {
      "from": "00cdf704"
    },
    {
      "from": "00d53830"
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
