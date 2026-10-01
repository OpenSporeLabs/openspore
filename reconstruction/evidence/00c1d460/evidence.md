# Evidence 0x00c1d460

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1476e8b00e79aabac2001c7be6d3503affb827a19dc931c6ed6ad2f4b89ceead`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +28, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent"
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
  "content_sha256": "4a8f2dc180bf6e64f81263e9ce5fedddc9c092a6224ccdeecac78a3cde4bcbdb",
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
        "obs-0067"
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
        "obs-0021"
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
        "obs-0007",
        "obs-0008",
        "obs-0012",
        "obs-0013",
        "obs-0017",
        "obs-0022",
        "obs-0025",
        "obs-0027",
        "obs-0028",
        "obs-0037",
        "obs-0042",
        "obs-0048",
        "obs-0054",
        "obs-0060",
        "obs-0062"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          192
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0053"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0067"
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
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00c1d460",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 27,
      "raw": "SUB ESP,0x60",
      "sub": 96
    },
    {
      "at": "0x00c1d460",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x60",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c1d463",
      "count": 6,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c1d464",
      "count": 12,
      "first_use": 2,
      "first_write_index": 9,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c1d465",
      "count": 9,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c1d466",
      "definite": true,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "XOR EDI,EDI",
      "reg": "EDI",
      "write_kind": "zero"
    },
    {
      "at": "0x00c1d468",
      "count": 19,
      "first_use": 5,
      "first_write_index": 8,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EBX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +28, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent"
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
  "content_sha256": "4a8f2dc180bf6e64f81263e9ce5fedddc9c092a6224ccdeecac78a3cde4bcbdb",
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
        "obs-0067"
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
        "obs-0021"
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
        "obs-0007",
        "obs-0008",
        "obs-0012",
        "obs-0013",
        "obs-0017",
        "obs-0022",
        "obs-0025",
        "obs-0027",
        "obs-0028",
        "obs-0037",
        "obs-0042",
        "obs-0048",
        "obs-0054",
        "obs-0060",
        "obs-0062"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          192
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0053"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0067"
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
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00c1d460",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 27,
      "raw": "SUB ESP,0x60",
      "sub": 96
    },
    {
      "at": "0x00c1d460",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x60",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c1d463",
      "count": 6,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c1d464",
      "count": 12,
      "first_use": 2,
      "first_write_index": 9,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c1d465",
      "count": 9,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c1d466",
      "definite": true,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "XOR EDI,EDI",
      "reg": "EDI",
      "write_kind": "zero"
    },
    {
      "at": "0x00c1d468",
      "count": 19,
      "first_use": 5,
      "first_write_index": 8,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EBX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "QuaternionToMatrix",
    "reconstructed": false,
    "va": "0x0059c190"
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
    "va": "0x00c1d5e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d2d0b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d512f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e8bf20"
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
  "count": 121,
  "instructions": [
    {
      "address": "00c1d460",
      "instruction": "SUB ESP,0x60"
    },
    {
      "address": "00c1d463",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c1d464",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c1d465",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c1d466",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00c1d468",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00c1d46a",
      "instruction": "MOV dword ptr [ESP + 0xc],EDI"
    },
    {
      "address": "00c1d46e",
      "instruction": "CALL 0x0067ddd0"
    },
    {
      "address": "00c1d473",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00c1d477",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00c1d479",
      "instruction": "CMP ECX,EDI"
    },
    {
      "address": "00c1d47b",
      "instruction": "JZ 0x00c1d488"
    },
    {
      "address": "00c1d47d",
      "instruction": "MOV dword ptr [ESP + 0xc],EDI"
    },
    {
      "address": "00c1d481",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00c1d483",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00c1d486",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c1d488",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00c1d48a",
      "instruction": "MOV EDX,dword ptr [ESP + 0x70]"
    },
    {
      "address": "00c1d48e",
      "instruction": "MOV EAX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "00c1d491",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "00c1d495",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c1d496",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c1d497",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c1d498",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c1d49a",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c1d49c",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c1d49e",
      "instruction": "JZ 0x00c1d5a9"
    },
    {
      "address": "00c1d4a4",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c1d4a5",
      "instruction": "LEA ECX,[ESP + 0x78]"
    },
    {
      "address": "00c1d4a9",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c1d4aa",
      "instruction": "LEA ECX,[EBX + 0xd68]"
    },
    {
      "address": "00c1d4b0",
      "instruction": "CALL 0x00b76460"
    },
    {
      "address": "00c1d4b5",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c1d4b9",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00c1d4bb",
      "instruction": "MOV ESI,dword ptr [EDI]"
    },
    {
      "address": "00c1d4bd",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00c1d4bf",
      "instruction": "CMP ECX,ESI"
    },
    {
      "address": "00c1d4c1",
      "instruction": "JZ 0x00c1d4dc"
    },
    {
      "address": "00c1d4c3",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00c1d4c5",
      "instruction": "JZ 0x00c1d4cd"
    },
    {
      "address": "00c1d4c7",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00c1d4c9",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "00c1d4cb",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c1d4cd",
      "instruction": "MOV dword ptr [EDI],EBP"
    },
    {
      "address": "00c1d4cf",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c1d4d1",
      "instruction": "JZ 0x00c1d4dc"
    },
    {
      "address": "00c1d4d3",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00c1d4d5",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "00c1d4d8",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c1d4da",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c1d4dc",
      "instruction": "MOVSS XMM0,dword ptr [0x0168d988]"
    },
    {
      "address": "00c1d4e4",
      "instruction": "MOVSS dword ptr [ESP + 0x3c],XMM0"
    },
    {
      "address": "00c1d4ea",
      "instruction": "MOVSS XMM0,dword ptr [0x0168d98c]"
    },
    {
      "address": "00c1d4f2",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00c1d4f4",
      "instruction": "MOVSS dword ptr [ESP + 0x40],XMM0"
    },
    {
      "address": "00c1d4fa",
      "instruction": "MOVSS XMM0,dword ptr [0x0168d990]"
    },
    {
      "address": "00c1d502",
      "instruction": "MOV word ptr [ESP + 0x38],CX"
    },
    {
      "address": "00c1d507",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00c1d509",
      "instruction": "MOVSS dword ptr [ESP + 0x44],XMM0"
    },
    {
      "address": "00c1d50f",
      "instruction": "MOVSS XMM0,dword ptr [0x01485720]"
    },
    {
      "address": "00c1d517",
      "instruction": "PUSH 0x168d964"
    },
    {
      "address": "00c1d51c",
      "instruction": "LEA ECX,[ESP + 0x50]"
    },
    {
      "address": "00c1d520",
      "instruction": "MOV word ptr [ESP + 0x3e],DX"
    },
    {
      "address": "00c1d525",
      "instruction": "MOVSS dword ptr [ESP + 0x4c],XMM0"
    },
    {
      "address": "00c1d52b",
      "instruction": "CALL 0x0041cb40"
    },
    {
      "address": "00c1d530",
      "instruction": "MOV EAX,dword ptr [EBX + 0xc0]"
    },
    {
      "address": "00c1d536",
      "instruction": "MOV EDX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "00c1d539",
      "instruction": "LEA ESI,[EBX + 0xc0]"
    },
    {
      "address": "00c1d53f",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c1d541",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c1d543",
      "instruction": "MOV
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
  "original_bytes": 8134,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-13-C4-CREATURE-WAVE3\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cCreatureBase_LocomotionWalkToInterior_00c1c5c0\",\n      \"va\": \"0x00c1c5c0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005bf9d0\",\n      \"va\": \"0x005bf9d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0100\",\n      \"va\": \"0x005c0100\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0380\",\n      \"va\": \"0x005c0380\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 3,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 3,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-13-C3-CREATURE-PROGRESSION-WAVE2\",\n      \"score\": 3,\n      \"symbol\": \"Simulator_cCreatureGameData_Get_00d2e340\",\n      \"va\": \"0x00d2e340\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-13-C3-CREATURE-PROGRESSION-WAVE2\",\n      \"score\": 3,\n      \"symbol\": \"Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0\",\n      \"va\": \"0x00d2e8a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The concrete dynamic type of the created handle and its reference-count contract remain runtime-gated.\",\n    \"The concrete type, size and lifetime of the 56-byte property block remain runtime-gated.\",\n    \"The pool key space and the insert-versus-lookup behaviour of 0x00b76460 for absent keys remain runtime-gated.\",\n    \"Whether the cleanup reload can observe a handle changed by the Start callee is not modelled and remains runtime-gated.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"QuaternionToMatrix\",\n        \"reconstructed\": false,\n        \"va\": \"0x0059c190\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c1d5e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2d0b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d512f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e8bf20\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00c1d618\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c1d5e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d2d1f5\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d2d0b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d5137a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d512f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8bf76\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e8bf20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8bff5\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e8bf20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8c016\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e8bf20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8c023\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e8bf20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c1d52b\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041cb40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c1d576\",\n        \"direction\": \"out\",\n        \"other\": \"0x0059c190\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c1d46e\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067ddd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c1d4b0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b76460\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 4,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0446\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": null,\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460\",\n  \"normalized_symbol\": \"Simulator_cCreatureBase_
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
  "body_end": "00c1d5d5",
  "body_span_bytes": 374,
  "body_start": "00c1d460",
  "callees": [
    "FUN_0067ddd0",
    "QuaternionToMatrix",
    "FUN_0041cb40",
    "FUN_00b76460"
  ],
  "callers": [
    "FUN_00d2d0b0",
    "FUN_00d512f0",
    "FUN_00c1d5e0",
    "FUN_00e8bf20"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c1d460",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_60",
      "storage": "Stack[-0x60]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00c1d460",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x81d460",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c1d460(void)",
  "size_bytes": 374,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c1d460",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 9,
  "xrefs": [
    {
      "from": "00c1d618"
    },
    {
      "from": "00d2d1f5"
    },
    {
      "from": "00d5137a"
    },
    {
      "from": "00e8bf76"
    },
    {
      "from": "00e8bff5"
    },
    {
      "from": "00e8c016"
    },
    {
      "from": "00e8c023"
    },
    {
      "from": "00e8cb10"
    },
    {
      "from": "00dabb56"
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
    "reconstruction/metadata/pkg13-c4-creature-wave3/00c1d460.json"
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
    "Confirm the handle reference-count pair on a live effect, including whether Start with argument 0 can clear the out slot that the cleanup reloads.",
    "Exercise the failure path with a service that returns false while writing a non-null handle, to confirm the Start and Release still run.",
    "No original-process trace, differential run under Wine, or runtime validation has been performed.",
    "Observe a real service create in an original process to confirm the instance id and group id contract and whether the group id is ever non-zero.",
    "Observe a real vtable slot +0x18 submission to learn the concrete property block layout and whether the pointer escapes.",
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
  "UNCONDITIONAL_CALL",
  "opaque 56-byte POD carrying a flag half-word, a count half-word, a three-real position, a real scale and a nine-real rotation",
  "uint32_t"
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
