# Evidence 0x01053980

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e641e0b77c4c1ca7fe11bbb3de0b551d3021c89f54da3c76f21cacd72a3f9c0f`

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
      "entry_ESP+0xc",
      "entry_ESP+0x14",
      "entry_ESP+0x1c",
      "entry_ESP+0x20",
      "entry_ESP+0x24",
      "entry_ESP+0x30",
      "entry_ESP+0x38",
      "entry_ESP+0x44",
      "entry_ESP+0x4c",
      "entry_ESP+0x54"
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
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
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x44",
        "observed": true,
        "ordinal": 17,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x4c",
        "observed": true,
        "ordinal": 19,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x54",
        "observed": true,
        "ordinal": 21,
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
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
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x44",
        "observed": true,
        "ordinal": 17,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x4c",
        "observed": true,
        "ordinal": 19,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x54",
        "observed": true,
        "ordinal": 21,
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
    "flow_not_modelled: the linear ESP walk ends at -64, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register
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
      "entry_ESP+0xc",
      "entry_ESP+0x14",
      "entry_ESP+0x1c",
      "entry_ESP+0x20",
      "entry_ESP+0x24",
      "entry_ESP+0x30",
      "entry_ESP+0x38",
      "entry_ESP+0x44",
      "entry_ESP+0x4c",
      "entry_ESP+0x54"
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
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
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x44",
        "observed": true,
        "ordinal": 17,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x4c",
        "observed": true,
        "ordinal": 19,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x54",
        "observed": true,
        "ordinal": 21,
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
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
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x44",
        "observed": true,
        "ordinal": 17,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x4c",
        "observed": true,
        "ordinal": 19,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x54",
        "observed": true,
        "ordinal": 21,
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
    "flow_not_modelled: the linear ESP walk ends at -64, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d240",
    "reconstructed": false,
    "va": "0x00b3d240"
  },
  {
    "name": "root_accessor_00b3d3e0",
    "reconstructed": true,
    "va": "0x00b3d3e0"
  },
  {
    "name": "FUN_00b5b800",
    "reconstructed": false,
    "va": "0x00b5b800"
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
    "name": "Simulator::cGetOutOfUFOToolStrategy::OnSelect",
    "reconstructed": false,
    "va": "0x01054080"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0105b6a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0105ba00"
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
  "count": 201,
  "instructions": [
    {
      "address": "01053980",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "01053983",
      "instruction": "PUSH EBX"
    },
    {
      "address": "01053984",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01053985",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01053986",
      "instruction": "MOV ESI,dword ptr [ESP + 0x20]"
    },
    {
      "address": "0105398a",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "0105398c",
      "instruction": "MOV ECX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "01053990",
      "instruction": "MOV EAX,dword ptr [EBP]"
    },
    {
      "address": "01053993",
      "instruction": "MOV EDX,dword ptr [EAX + 0x20]"
    },
    {
      "address": "01053996",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "01053998",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01053999",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0105399a",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "0105399c",
      "instruction": "CALL EDX"
    },
    {
      "address": "0105399e",
      "instruction": "MOV BL,AL"
    },
    {
      "address": "010539a0",
      "instruction": "MOV byte ptr [ESP + 0x20],BL"
    },
    {
      "address": "010539a4",
      "instruction": "CALL 0x00b5b800"
    },
    {
      "address": "010539a9",
      "instruction": "CMP EAX,0x1654c05"
    },
    {
      "address": "010539ae",
      "instruction": "JZ 0x010539bb"
    },
    {
      "address": "010539b0",
      "instruction": "POP ESI"
    },
    {
      "address": "010539b1",
      "instruction": "POP EBP"
    },
    {
      "address": "010539b2",
      "instruction": "MOV AL,BL"
    },
    {
      "address": "010539b4",
      "instruction": "POP EBX"
    },
    {
      "address": "010539b5",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "010539b8",
      "instruction": "RET 0xc"
    },
    {
      "address": "010539bb",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "010539bd",
      "instruction": "JZ 0x01053ba1"
    },
    {
      "address": "010539c3",
      "instruction": "CALL 0x00ffbe50"
    },
    {
      "address": "010539c8",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "010539ca",
      "instruction": "CALL 0x00a1ad60"
    },
    {
      "address": "010539cf",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "010539d1",
      "instruction": "JZ 0x010539d8"
    },
    {
      "address": "010539d3",
      "instruction": "ADD EAX,0x34"
    },
    {
      "address": "010539d6",
      "instruction": "JMP 0x010539da"
    },
    {
      "address": "010539d8",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "010539da",
      "instruction": "CMP dword ptr [ESI + 0x114],EAX"
    },
    {
      "address": "010539e0",
      "instruction": "JNZ 0x01053ba1"
    },
    {
      "address": "010539e6",
      "instruction": "PUSH EDI"
    },
    {
      "address": "010539e7",
      "instruction": "CALL 0x00ffbe50"
    },
    {
      "address": "010539ec",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "010539ee",
      "instruction": "CALL 0x00a1ad60"
    },
    {
      "address": "010539f3",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "010539f5",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "010539f7",
      "instruction": "CALL 0x0104cce0"
    },
    {
      "address": "010539fc",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "010539fe",
      "instruction": "JZ 0x01053a0e"
    },
    {
      "address": "01053a00",
      "instruction": "CALL 0x00ffbe50"
    },
    {
      "address": "01053a05",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01053a07",
      "instruction": "CALL 0x00ffc2d0"
    },
    {
      "address": "01053a0c",
      "instruction": "JMP 0x01053a1a"
    },
    {
      "address": "01053a0e",
      "instruction": "CALL 0x00ffbe50"
    },
    {
      "address": "01053a13",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01053a15",
      "instruction": "CALL 0x00c30cb0"
    },
    {
      "address": "01053a1a",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "01053a1c",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "01053a1e",
      "instruction": "CALL 0x0104cce0"
    },
    {
      "address": "01053a23",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "01053a25",
      "instruction": "JZ 0x01053a2b"
    },
    {
      "address": "01053a27",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "01053a29",
      "instruction": "JNZ 0x01053a42"
    },
    {
      "address": "01053a2b",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "01053a2d",
      "instruction": "CALL 0x0104cd30"
    },
    {
      "address": "01053a32",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "01053a34",
      "instruction": "JZ 0x01053adf"
    },
    {
      "address": "01053a3a",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "01053a3c",
      "instruction": "JZ 0x01053adf"
    },
    {
      "address": "01053a42",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "01053a44",
      "instruction": "CALL 0x0104be30"
    },
    {
      "address": "01053a49",
      "instruction": "FLD float ptr [0x013eb1bc]"
    },
    {
      "address": "01053a4f",
      "instruction": "FXCH"
    },
    {
      "address": "01053a51",
      "instruction": "FUCOMIP ST0,ST1"
    },
    {
      "address": "01053a53",
      "instruction": "FSTP ST0"
    },
    {
      "address": "01053a55",
      "instruction": "LAHF"
    },
    {
      "address": "01053a56",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "01053a59",
      "instruction": "JNP 0x01053ba0"
    },
    {
      "address": "01053a5f"
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
  "original_bytes": 9225,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-core-systems\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d240\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b3d240\"\n      },\n      {\n        \"name\": \"root_accessor_00b3d3e0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d3e0\"\n      },\n      {\n        \"name\": \"FUN_00b5b800\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b5b800\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"Simulator::cGetOutOfUFOToolStrategy::OnSelect\",\n        \"reconstructed\": false,\n        \"va\": \"0x01054080\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0105b6a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0105ba00\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0105409d\",\n        \"direction\": \"in\",\n        \"other\": \"0x01054080\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105b6b5\",\n        \"direction\": \"in\",\n        \"other\": \"0x0105b6a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105ba15\",\n        \"direction\": \"in\",\n        \"other\": \"0x0105ba00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010539ca\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a1ad60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010539ee\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a1ad60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053b40\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d240\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053b94\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d3e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010539a4\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b5b800\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053a15\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c30cb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053b4f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c9f060\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053b9b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00dd6df0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010539c3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ffbe50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010539e7\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ffbe50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053a00\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ffbe50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053a0e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ffbe50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053a07\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ffc2d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053b00\",\n        \"direction\": \"out\",\n        \"other\": \"0x0102aec0\",\n        \"reference_type\
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
  "body_end": "01053bad",
  "body_span_bytes": 558,
  "body_start": "01053980",
  "callees": [
    "FUN_00c9f060",
    "FUN_010527f0",
    "FUN_0104c030",
    "FUN_00a1ad60",
    "FUN_00dd6df0",
    "FUN_00c30cb0",
    "FUN_00b3d3e0",
    "FUN_00b3d240",
    "FUN_00b5b800",
    "FUN_0104cdb0",
    "FUN_0104c010",
    "FUN_0102aec0",
    "FUN_0104cce0",
    "FUN_0104be30",
    "FUN_00ffc2d0",
    "FUN_0104cd30",
    "FUN_0104bff0",
    "FUN_00ffbe50"
  ],
  "callers": [
    "Simulator::cGetOutOfUFOToolStrategy::OnSelect",
    "FUN_0105b6a0",
    "FUN_0105ba00"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01053980",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_01053980",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc53980",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01053980(void)",
  "size_bytes": 558,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01053980",
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
  "xref_count": 24,
  "xrefs": [
    {
      "from": "0105b6b5"
    },
    {
      "from": "0105ba15"
    },
    {
      "from": "0149bb0c"
    },
    {
      "from": "0149bb54"
    },
    {
      "from": "0149b52c"
    },
    {
      "from": "0149b574"
    },
    {
      "from": "0149b604"
    },
    {
      "from": "0149b64c"
    },
    {
      "from": "0149b694"
    },
    {
      "from": "0149b6dc"
    },
    {
      "from": "0149b76c"
    },
    {
      "from": "0149b7b4"
    },
    {
      "from": "0149b7fc"
    },
    {
      "from": "0149b84c"
    },
    {
      "from": "0149b89c"
    },
    {
      "from": "0149b8ec"
    },
    {
      "from": "0149b98c"
    },
    {
      "from": "0149b9d4"
    },
    {
      "from": "0149ba1c"
    },
    {
      "from": "0149ba6c"
    },
    {
      "from": "0149bab4"
    },
    {
      "from": "0105409d"
    },
    {
      "from": "010540bf"
    },
    {
      "from": "0149b304"
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
