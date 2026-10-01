# Evidence 0x00bb57b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d823e327583dad52d5901fa62ad59a8873df706ed43bb51f8ddea58128b2c71a`

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
      "entry_ESP+0x8"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +32, so the listing is not one path"
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
  "content_sha256": "db371754e6d9be17a2df908f5bf2d311404de189717e2b74b80cd966eaa87920",
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
        "obs-0046"
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
        "obs-0004",
        "obs-0009"
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
        "obs-0013",
        "obs-0017",
        "obs-0032"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          200
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0012",
        "obs-0013",
        "obs-0017",
        "obs-0032",
        "obs-0046"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0046"
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
      "at": "0x00bb57b0",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 23,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00bb57b0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00bb57b3",
      "count": 10,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x00bb57b3",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0004",
      "index": 1,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00bb57b3",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bb57b7",
      "count": 5,
      "first_use": 2,
      "first_write_index": 7,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00bb57b8",
      "count": 16,
      "first_use": 3,
      "first_write_index": 11,
      "id": "obs-0007",
      "index": 3,
      "kind": "RE
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
      "entry_ESP+0x8"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +32, so the listing is not one path"
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
  "content_sha256": "db371754e6d9be17a2df908f5bf2d311404de189717e2b74b80cd966eaa87920",
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
        "obs-0046"
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
        "obs-0004",
        "obs-0009"
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
        "obs-0013",
        "obs-0017",
        "obs-0032"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          200
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0012",
        "obs-0013",
        "obs-0017",
        "obs-0032",
        "obs-0046"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0046"
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
      "at": "0x00bb57b0",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 23,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00bb57b0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00bb57b3",
      "count": 10,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x00bb57b3",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0004",
      "index": 1,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00bb57b3",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bb57b7",
      "count": 5,
      "first_use": 2,
      "first_write_index": 7,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00bb57b8",
      "count": 16,
      "first_use": 3,
      "first_write_index": 11,
      "id": "obs-0007",
      "index": 3,
      "kind": "RE
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "star_regenerate_00bb4af0",
    "reconstructed": true,
    "va": "0x00bb4af0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbaa60"
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
    "va": "0x00bb5930"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb5ae0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb5b70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fe9580"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fefcd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x010021a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x010251e0"
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
  "count": 125,
  "instructions": [
    {
      "address": "00bb57b0",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00bb57b3",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00bb57b7",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bb57b8",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bb57b9",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bb57ba",
      "instruction": "MOV EDI,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00bb57be",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb57bf",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00bb57c1",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bb57c2",
      "instruction": "MOV dword ptr [ESP + 0x14],EBX"
    },
    {
      "address": "00bb57c6",
      "instruction": "CALL 0x00bb4af0"
    },
    {
      "address": "00bb57cb",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00bb57cd",
      "instruction": "CMP byte ptr [EDI + 0xac],0x0"
    },
    {
      "address": "00bb57d4",
      "instruction": "JBE 0x00bb57f4"
    },
    {
      "address": "00bb57d6",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bb57d7",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00bb57d9",
      "instruction": "CALL 0x00bbaa60"
    },
    {
      "address": "00bb57de",
      "instruction": "CMP byte ptr [EAX + 0x30],0x0"
    },
    {
      "address": "00bb57e2",
      "instruction": "JZ 0x00bb5922"
    },
    {
      "address": "00bb57e8",
      "instruction": "MOVZX ECX,byte ptr [EDI + 0xac]"
    },
    {
      "address": "00bb57ef",
      "instruction": "INC ESI"
    },
    {
      "address": "00bb57f0",
      "instruction": "CMP ESI,ECX"
    },
    {
      "address": "00bb57f2",
      "instruction": "JL 0x00bb57d6"
    },
    {
      "address": "00bb57f4",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00bb57f5",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bb57f6",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00bb57f8",
      "instruction": "CALL 0x00bafae0"
    },
    {
      "address": "00bb57fd",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00bb57ff",
      "instruction": "CALL 0x00801920"
    },
    {
      "address": "00bb5804",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00bb5806",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00bb5808",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bb5809",
      "instruction": "CALL 0x00c84c60"
    },
    {
      "address": "00bb580e",
      "instruction": "FSTP float ptr [ESP + 0x28]"
    },
    {
      "address": "00bb5812",
      "instruction": "PUSH 0x2"
    },
    {
      "address": "00bb5814",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bb5815",
      "instruction": "CALL 0x00c84c60"
    },
    {
      "address": "00bb581a",
      "instruction": "FSTP float ptr [ESP + 0x24]"
    },
    {
      "address": "00bb581e",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00bb5821",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "00bb5823",
      "instruction": "CMP byte ptr [EDI + 0xac],0x0"
    },
    {
      "address": "00bb582a",
      "instruction": "JBE 0x00bb5921"
    },
    {
      "address": "00bb5830",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00bb5831",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00bb5833",
      "instruction": "CALL 0x00bbaa60"
    },
    {
      "address": "00bb5838",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00bb583a",
      "instruction": "TEST byte ptr [ESI + 0x2c],0x2"
    },
    {
      "address": "00bb583e",
      "instruction": "JZ 0x00bb584e"
    },
    {
      "address": "00bb5840",
      "instruction": "PUSH 0xc"
    },
    {
      "address": "00bb5842",
      "instruction": "MOV ECX,0x1601760"
    },
    {
      "address": "00bb5847",
      "instruction": "CALL 0x00a68fb0"
    },
    {
      "address": "00bb584c",
      "instruction": "JMP 0x00bb5851"
    },
    {
      "address": "00bb584e",
      "instruction": "OR EAX,0xffffffff"
    },
    {
      "address": "00bb5851",
      "instruction": "CMP dword ptr [ESI + 0x28],0x1"
    },
    {
      "address": "00bb5855",
      "instruction": "MOV byte ptr [ESI + 0xac],AL"
    },
    {
      "address": "00bb585b",
      "instruction": "JNZ 0x00bb586f"
    },
    {
      "address": "00bb585d",
      "instruction": "PUSH 0xc"
    },
    {
      "address": "00bb585f",
      "instruction": "MOV ECX,0x1601760"
    },
    {
      "address": "00bb5864",
      "instruction": "CALL 0x00a68fb0"
    },
    {
      "address": "00bb5869",
      "instruction": "MOV byte ptr [ESI + 0xad],AL"
    },
    {
      "address": "00bb586f",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bb5871",
      "instruction": "CALL 0x00b8dac0"
    },
    {
      "address": "00bb5876",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00bb5878",
      "instruction": "JZ 0x00bb58bb"
    },
    {
      "address": "00bb587a",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bb587c",
      "instruction": "CALL 0x00b8da70"
    },
    {
      "address": "00bb5881",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "00bb5884",
      "instruction": "JNZ 0x00bb588a"
    },
    {
      "address": "00bb5886",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00bb5888",
      "instruction": "JMP 0x00bb58bd"
    },
    {
      "address": "00bb588a",
      "instruction": "MOV EBX,dword ptr [EBX + 0xc8]"
    },
    {
      "address": "00bb5890",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bb5892",
      "instruction": "AND ECX,0xffffff"
    },
    {
      "address": "00bb5898",
      "
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
  "original_bytes": 7604,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"star_regenerate_00bb4af0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00bb4af0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbaa60\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb5930\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb5ae0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb5b70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe9580\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fefcd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010021a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010251e0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00bb5976\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bb5930\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb5aec\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bb5ae0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb5b83\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bb5b70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fe9a00\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fe9580\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fefd6b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fefcd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010024bf\",\n        \"direction\": \"in\",\n        \"other\": \"0x010021a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010253a7\",\n        \"direction\": \"in\",\n        \"other\": \"0x010251e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb57ff\",\n        \"direction\": \"out\",\n        \"other\": \"0x00801920\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb5847\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a68fb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb5864\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a68fb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb587c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b8da70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb5871\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b8dac0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb57f8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bafae0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb57c6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bb4af0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb57d9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bbaa60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb5833\",\n    
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
  "body_end": "00bb592a",
  "body_span_bytes": 379,
  "body_start": "00bb57b0",
  "callees": [
    "FUN_00b8dac0",
    "FUN_00bb4af0",
    "FUN_00a68fb0",
    "FUN_00801920",
    "FUN_00b8da70",
    "FUN_00bbaa60",
    "FUN_00bafae0",
    "FUN_00c84c60"
  ],
  "callers": [
    "FUN_00bb5b70",
    "FUN_00bb5930",
    "FUN_010251e0",
    "FUN_00fe9580",
    "FUN_00bb5ae0",
    "FUN_00fefcd0",
    "FUN_010021a0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bb57b0",
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
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00bb57b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7b57b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bb57b0(void)",
  "size_bytes": 379,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bb57b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00bb5976"
    },
    {
      "from": "00fe9a00"
    },
    {
      "from": "00bb5aec"
    },
    {
      "from": "00fefd6b"
    },
    {
      "from": "00bb5b83"
    },
    {
      "from": "010253a7"
    },
    {
      "from": "010024bf"
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
