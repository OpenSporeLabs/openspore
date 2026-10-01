# Evidence 0x010537e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0f79550bde5ccb66aa30a67484516ac1d2f75c5b8ee2027b56b561c994f4687e`

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
    "ret_form": "RET 0x4",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
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
    "flow_not_modelled: the linear ESP walk ends at +48, so the listing is not one path",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "9bc08d02b4cacd5a26dd7aa60d22c7cf1732b6ba5935e86759a1d4f82b397569",
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
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0064"
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
        "obs-0005"
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
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0038",
        "obs-0045",
        "obs-0049",
        "obs-0053"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0038",
        "obs-0045",
        "obs-0049",
        "obs-0053",
        "obs-0064"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0005"
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
        "obs-0064"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
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
      "at": "0x010537e0",
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
      "raw": "SUB ESP,0x24",
      "sub": 36
    },
    {
      "at": "0x010537e0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x24",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x010537e3",
      "count": 12,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x010537e4",
      "count": 21,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x2c]",
      "reg": "ESP"
    },
    {
      "at": "0x010537e4",
      "base": "ESP",
      "disp": 44,
      "id": "obs-0005",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x2c]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x010537e4",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x2c]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x010537e8",
      
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
    "ret_form": "RET 0x4",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
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
    "flow_not_modelled: the linear ESP walk ends at +48, so the listing is not one path",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "9bc08d02b4cacd5a26dd7aa60d22c7cf1732b6ba5935e86759a1d4f82b397569",
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
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0064"
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
        "obs-0005"
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
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0038",
        "obs-0045",
        "obs-0049",
        "obs-0053"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0038",
        "obs-0045",
        "obs-0049",
        "obs-0053",
        "obs-0064"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0005"
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
        "obs-0064"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
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
      "at": "0x010537e0",
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
      "raw": "SUB ESP,0x24",
      "sub": 36
    },
    {
      "at": "0x010537e0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x24",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x010537e3",
      "count": 12,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x010537e4",
      "count": 21,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x2c]",
      "reg": "ESP"
    },
    {
      "at": "0x010537e4",
      "base": "ESP",
      "disp": 44,
      "id": "obs-0005",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x2c]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x010537e4",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x2c]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x010537e8",
      
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "simulator_game_input_manager_get_00b3d350",
    "reconstructed": true,
    "va": "0x00b3d350"
  },
  {
    "name": "FUN_00b3d390",
    "reconstructed": false,
    "va": "0x00b3d390"
  }
]
```

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
  "count": 121,
  "instructions": [
    {
      "address": "010537e0",
      "instruction": "SUB ESP,0x24"
    },
    {
      "address": "010537e3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "010537e4",
      "instruction": "MOV ESI,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "010537e8",
      "instruction": "PUSH EDI"
    },
    {
      "address": "010537e9",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "010537eb",
      "instruction": "MOV ECX,dword ptr [ESI + 0x140]"
    },
    {
      "address": "010537f1",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "010537f3",
      "instruction": "JZ 0x0105381b"
    },
    {
      "address": "010537f5",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "010537f7",
      "instruction": "MOV EDX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "010537fa",
      "instruction": "CALL EDX"
    },
    {
      "address": "010537fc",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "010537fe",
      "instruction": "JNZ 0x0105381b"
    },
    {
      "address": "01053800",
      "instruction": "MOV ECX,dword ptr [ESI + 0x140]"
    },
    {
      "address": "01053806",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01053808",
      "instruction": "JZ 0x0105381b"
    },
    {
      "address": "0105380a",
      "instruction": "MOV dword ptr [ESI + 0x140],0x0"
    },
    {
      "address": "01053814",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01053816",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01053819",
      "instruction": "CALL EDX"
    },
    {
      "address": "0105381b",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0105381d",
      "instruction": "CALL 0x0104ccd0"
    },
    {
      "address": "01053822",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "01053824",
      "instruction": "JZ 0x0105396d"
    },
    {
      "address": "0105382a",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "0105382c",
      "instruction": "MOV EDX,dword ptr [EAX + 0x20]"
    },
    {
      "address": "0105382f",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "01053831",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "01053833",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01053834",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "01053836",
      "instruction": "CALL EDX"
    },
    {
      "address": "01053838",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0105383a",
      "instruction": "JZ 0x0105396d"
    },
    {
      "address": "01053840",
      "instruction": "MOV EDI,dword ptr [ESI + 0x114]"
    },
    {
      "address": "01053846",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "01053848",
      "instruction": "CALL 0x0104cd90"
    },
    {
      "address": "0105384d",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0105384f",
      "instruction": "JZ 0x0105390c"
    },
    {
      "address": "01053855",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "01053857",
      "instruction": "MOV EDX,dword ptr [EAX + 0x30]"
    },
    {
      "address": "0105385a",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0105385c",
      "instruction": "CALL EDX"
    },
    {
      "address": "0105385e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0105385f",
      "instruction": "LEA EAX,[ESP + 0x18]"
    },
    {
      "address": "01053863",
      "instruction": "PUSH 0x15b8c88"
    },
    {
      "address": "01053868",
      "instruction": "PUSH EAX"
    },
    {
      "address": "01053869",
      "instruction": "CALL 0x0059aed0"
    },
    {
      "address": "0105386e",
      "instruction": "MOVSS XMM0,dword ptr [EAX]"
    },
    {
      "address": "01053872",
      "instruction": "MOVSS XMM1,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01053877",
      "instruction": "MOVSS XMM2,dword ptr [EAX + 0x8]"
    },
    {
      "address": "0105387c",
      "instruction": "MOVSS XMM3,dword ptr [0x01473c70]"
    },
    {
      "address": "01053884",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "01053886",
      "instruction": "MOV EAX,dword ptr [EDX + 0x2c]"
    },
    {
      "address": "01053889",
      "instruction": "MULSS XMM0,XMM3"
    },
    {
      "address": "0105388d",
      "instruction": "MULSS XMM1,XMM3"
    },
    {
      "address": "01053891",
      "instruction": "MULSS XMM2,XMM3"
    },
    {
      "address": "01053895",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "01053898",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0105389a",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM0"
    },
    {
      "address": "010538a0",
      "instruction": "MOVSS dword ptr [ESP + 0x18],XMM1"
    },
    {
      "address": "010538a6",
      "instruction": "MOVSS dword ptr [ESP + 0x1c],XMM2"
    },
    {
      "address": "010538ac",
      "instruction": "CALL EAX"
    },
    {
      "address": "010538ae",
      "instruction": "MOVSS XMM0,dword ptr [EAX]"
    },
    {
      "address": "010538b2",
      "instruction": "MOVSS XMM1,dword ptr [EAX + 0x4]"
    },
    {
      "address": "010538b7",
      "instruction": "MOVSS XMM2,dword ptr [EAX + 0x8]"
    },
    {
      "address": "010538bc",
      "instruction": "ADDSS XMM0,dword ptr [ESP + 0x14]"
    },
    {
      "address": "010538c2",
      "instruction": "ADDSS XMM1,dword ptr [ESP + 0x18]"
    },
    {
      "address": "010538c8",
      "instruction": "ADDSS XMM2,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "010538ce",
      "instruction": "LEA ECX,[ESP + 0x20]"
    },
    {
      "address": "010538d2",
      "instruction": "PUSH ECX"
    },
    {
      "address": "010538d3"
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
  "original_bytes": 6395,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-core-systems\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"simulator_game_input_manager_get_00b3d350\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d350\"\n      },\n      {\n        \"name\": \"FUN_00b3d390\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b3d390\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x01053869\",\n        \"direction\": \"out\",\n        \"other\": \"0x0059aed0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010538ea\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105391f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d350\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053940\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d390\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053954\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d390\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053961\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d390\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010538f1\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b81630\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053926\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b81630\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105381d\",\n        \"direction\": \"out\",\n        \"other\": \"0x0104ccd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053848\",\n        \"direction\": \"out\",\n        \"other\": \"0x0104cd90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053968\",\n        \"direction\": \"out\",\n        \"other\": \"0x0104e260\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053947\",\n        \"direction\": \"out\",\n        \"other\": \"0x01050640\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105395b\",\n        \"direction\": \"out\",\n        \"other\": \"0x01050bb0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 2,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00b3d350\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0603\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"FUN_010537e0\",\n  \"normalized_symbol\": \"FUN_010537e0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null
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
  "body_end": "01053976",
  "body_span_bytes": 407,
  "body_start": "010537e0",
  "callees": [
    "FUN_0059aed0",
    "FUN_00b3d390",
    "FUN_01050bb0",
    "FUN_0104ccd0",
    "FUN_00b81630",
    "FUN_01050640",
    "FUN_0104cd90",
    "Simulator::cGameInputManager::Get",
    "FUN_0104e260"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "010537e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_010537e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc537e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_010537e0(void)",
  "size_bytes": 407,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x010537e0",
  "vtables": {
    "referenced_by_vtables": [
      "0x0149b4d8",
      "0x0149b8b4",
      "0x0149b498",
      "0x0149b900",
      "0x0149b810",
      "0x0149ba30",
      "0x0149b2e0"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 23,
  "xrefs": [
    {
      "from": "0149bb00"
    },
    {
      "from": "0149b520"
    },
    {
      "from": "0149b568"
    },
    {
      "from": "0149b5f8"
    },
    {
      "from": "0149b640"
    },
    {
      "from": "0149b688"
    },
    {
      "from": "0149b6d0"
    },
    {
      "from": "0149b760"
    },
    {
      "from": "0149b7a8"
    },
    {
      "from": "0149b7f0"
    },
    {
      "from": "0149b840"
    },
    {
      "from": "0149b890"
    },
    {
      "from": "0149b930"
    },
    {
      "from": "0149b980"
    },
    {
      "from": "0149b9c8"
    },
    {
      "from": "0149ba10"
    },
    {
      "from": "0149ba60"
    },
    {
      "from": "0149baa8"
    },
    {
      "from": "01053fb6"
    },
    {
      "from": "010540d9"
    },
    {
      "from": "01058798"
    },
    {
      "from": "0149b2f8"
    },
    {
      "from": "01054116"
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0149b2e0",
  "vtable:0x0149b498",
  "vtable:0x0149b4d8",
  "vtable:0x0149b810",
  "vtable:0x0149b8b4",
  "vtable:0x0149b900",
  "vtable:0x0149ba30"
]
```

## Conflicts

```json
[]
```
