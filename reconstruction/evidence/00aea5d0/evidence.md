# Evidence 0x00aea5d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b866c20afa539321bae4eab7be9118118e94338450f2d73611873977ddfaacbc`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "receiver": {
    "register": "ECX",
    "type": "cCommVector*",
    "width_bytes": 4
  },
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "position",
      "position": 1,
      "type": "cCommEvent**"
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "value",
      "position": 2,
      "type": "cCommEvent**"
    }
  ],
  "stack_cleanup_bytes": 8,
  "termination": "RET 0x8"
}
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
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x1c",
      "entry_ESP+0x20"
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
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -24, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x8 pops less than the highest read slot 0x20; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x8 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x8 but entry slot 0x20 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "4be1e76dfe2648ef4883842335280eb50d6bb7dd97c4ed75455a806af880bfc1",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
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
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0030",
        "obs-0050"
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
        "obs-0030",
        "obs-0050"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 8,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0013",
        "obs-0031",
        "obs-0033",
        "obs-0034",
        "obs-0035",
        "obs-0036",
        "obs-0037",
        "obs-0038",
        "obs-0040",
        "obs-0044",
        "obs-0045"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      
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
    "va": "0x00ac0570"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00acd2d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ad12a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ae0a80"
  },
  {
    "name": "FUN_00aeb160",
    "reconstructed": true,
    "va": "0x00aeb160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b05b40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b068c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b06a40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b06bd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b09830"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b0b150"
  },
  {
    "name": "noun_manager_logical_destroy_00b225d0",
    "reconstructed": true,
    "va": "0x00b225d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b22650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b227c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b23450"
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
  "count": 133,
  "instructions": [
    {
      "address": "00aea5d0",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00aea5d3",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00aea5d4",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00aea5d5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00aea5d6",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00aea5d7",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00aea5d9",
      "instruction": "MOV EAX,dword ptr [EDI + 0x4]"
    },
    {
      "address": "00aea5dc",
      "instruction": "CMP EAX,dword ptr [EDI + 0x8]"
    },
    {
      "address": "00aea5df",
      "instruction": "JZ 0x00aea64d"
    },
    {
      "address": "00aea5e1",
      "instruction": "MOV ECX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00aea5e5",
      "instruction": "MOV EBP,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00aea5e9",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00aea5eb",
      "instruction": "CMP ECX,EBP"
    },
    {
      "address": "00aea5ed",
      "instruction": "JC 0x00aea5f6"
    },
    {
      "address": "00aea5ef",
      "instruction": "CMP ECX,EAX"
    },
    {
      "address": "00aea5f1",
      "instruction": "JNC 0x00aea5f6"
    },
    {
      "address": "00aea5f3",
      "instruction": "LEA ESI,[ECX + 0x4]"
    },
    {
      "address": "00aea5f6",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00aea5f8",
      "instruction": "JZ 0x00aea609"
    },
    {
      "address": "00aea5fa",
      "instruction": "MOV ECX,dword ptr [EAX + -0x4]"
    },
    {
      "address": "00aea5fd",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "00aea5ff",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00aea601",
      "instruction": "JZ 0x00aea609"
    },
    {
      "address": "00aea603",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00aea605",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00aea607",
      "instruction": "CALL EDX"
    },
    {
      "address": "00aea609",
      "instruction": "MOV EAX,dword ptr [EDI + 0x4]"
    },
    {
      "address": "00aea60c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00aea60d",
      "instruction": "ADD EAX,-0x4"
    },
    {
      "address": "00aea610",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00aea611",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00aea612",
      "instruction": "CALL 0x00ac97a0"
    },
    {
      "address": "00aea617",
      "instruction": "MOV ESI,dword ptr [ESI]"
    },
    {
      "address": "00aea619",
      "instruction": "MOV EBX,dword ptr [EBP]"
    },
    {
      "address": "00aea61c",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00aea61f",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "00aea621",
      "instruction": "JZ 0x00aea63f"
    },
    {
      "address": "00aea623",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00aea625",
      "instruction": "JZ 0x00aea62f"
    },
    {
      "address": "00aea627",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00aea629",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00aea62b",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00aea62d",
      "instruction": "CALL EDX"
    },
    {
      "address": "00aea62f",
      "instruction": "MOV dword ptr [EBP],ESI"
    },
    {
      "address": "00aea632",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00aea634",
      "instruction": "JZ 0x00aea63f"
    },
    {
      "address": "00aea636",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "00aea638",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00aea63b",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00aea63d",
      "instruction": "CALL EDX"
    },
    {
      "address": "00aea63f",
      "instruction": "ADD dword ptr [EDI + 0x4],0x4"
    },
    {
      "address": "00aea643",
      "instruction": "POP EDI"
    },
    {
      "address": "00aea644",
      "instruction": "POP ESI"
    },
    {
      "address": "00aea645",
      "instruction": "POP EBP"
    },
    {
      "address": "00aea646",
      "instruction": "POP EBX"
    },
    {
      "address": "00aea647",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00aea64a",
      "instruction": "RET 0x8"
    },
    {
      "address": "00aea64d",
      "instruction": "SUB EAX,dword ptr [EDI]"
    },
    {
      "address": "00aea64f",
      "instruction": "SAR EAX,0x2"
    },
    {
      "address": "00aea652",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00aea654",
      "instruction": "JBE 0x00aea686"
    },
    {
      "address": "00aea656",
      "instruction": "ADD EAX,EAX"
    },
    {
      "address": "00aea658",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "00aea65c",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00aea65e",
      "instruction": "JZ 0x00aea694"
    },
    {
      "address": "00aea660",
      "instruction": "PUSH 0xd1"
    },
    {
      "address": "00aea665",
      "instruction": "PUSH 0x13ebb38"
    },
    {
      "address": "00aea66a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00aea66c",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00aea66e",
      "instruction": "ADD EAX,EAX"
    },
    {
      "address": "00aea670",
      "instruction": "ADD EAX,EAX"
    },
    {
      "address": "00aea672",
      "instruction": "PUSH 0x13f09b4"
    },
    {
      "address": "00aea677",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00aea678",
      "instruction": "CALL 0x00f47
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
  "original_bytes": 15591,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"receiver\": {\n      \"register\": \"ECX\",\n      \"type\": \"cCommVector*\",\n      \"width_bytes\": 4\n    },\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"position\",\n        \"position\": 1,\n        \"type\": \"cCommEvent**\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"value\",\n        \"position\": 2,\n        \"type\": \"cCommEvent**\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:cCommEvent,cCommVector\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 25,\n      \"symbol\": \"FUN_00aeb160\",\n      \"va\": \"0x00aeb160\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:cCommEvent\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 19,\n      \"symbol\": \"Simulator_cCommManager_CreateAndDispatchEvent_00aeb720\",\n      \"va\": \"0x00aeb720\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:cCommEvent\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 17,\n      \"symbol\": \"FUN_00aea250\",\n      \"va\": \"0x00aea250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 16,\n      \"symbol\": \"FUN_00aea230\",\n      \"va\": \"0x00aea230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 10,\n      \"symbol\": \"cSpaceInventoryItem_ctor_00c877f0\",\n      \"va\": \"0x00c877f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"pkg12_space_00de9fc0\",\n      \"va\": \"0x00de9fc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"pkg12_space_01021300\",\n      \"va\": \"0x01021300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_0102d1b0\",\n      \"va\": \"0x0102d1b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The live manager layout conflicts with the imported type, so only directly observed vector offsets are modeled.\",\n    \"The target ref-aware move implementation is staged as an opaque helper boundary, although its call order and slot behavior are verified.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"cCommVector\",\n  \"cluster\": null,\n  \"confidence\": 0.93,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ac0570\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00acd2d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ad12a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ae0a80\"\n      },\n      {\n        \"name\": \"FUN_00aeb160\",\n        \"reconstructed\": true,\n        \"va\": \"0x00aeb160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b05b40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b068c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b06a40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b06bd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b09830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b0b150\"\n      },\n      {\n        \"name\": \"noun_manager_logical_destroy_00b225d0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b225d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b22650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b227c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b23450\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b26320\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b2e010\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b60d80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b706a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b77b60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b79aa0\"\n      },\n      {\n        \
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
  "body_end": "00aea71b",
  "body_span_bytes": 332,
  "body_start": "00aea5d0",
  "callees": [
    "FUN_00ac97a0",
    "memcpy",
    "FUN_00f47380",
    "FUN_00f473a0"
  ],
  "callers": [
    "FUN_01014870",
    "FUN_00aeb240",
    "FUN_00c341a0",
    "FUN_00c344f0",
    "FUN_00d5cfd0",
    "FUN_01014540",
    "FUN_00bba640",
    "FUN_00baecc0",
    "FUN_00d5c720",
    "FUN_00bb80f0",
    "FUN_00cee820",
    "FUN_00c8c420",
    "FUN_00da1b00",
    "FUN_01008910",
    "FUN_00b706a0",
    "FUN_00b26320",
    "FUN_00b225d0",
    "FUN_00cf3bf0",
    "FUN_00b05b40",
    "FUN_00b22650",
    "FUN_00c5a990",
    "FUN_00be2b10",
    "FUN_00be0fc0",
    "FUN_00ffb830",
    "FUN_01009a40",
    "FUN_01009470",
    "FUN_00c5d140",
    "FUN_00b79aa0",
    "FUN_00be6900",
    "FUN_00e47930",
    "FUN_00be1ef0",
    "FUN_00c95fe0",
    "FUN_00bb5d80",
    "FUN_00be1e80",
    "FUN_00be7bf0",
    "FUN_00b60d80",
    "FUN_00fedb50",
    "FUN_00ae0a80",
    "FUN_00c09fa0",
    "FUN_010095e0",
    "FUN_00c099e0",
    "FUN_00b77b60",
    "FUN_00aeb160",
    "FUN_00b23450",
    "FUN_00e18150",
    "FUN_00bf4370",
    "FUN_00ad12a0",
    "FUN_00f342d0",
    "FUN_010146c0",
    "FUN_00eeaf00",
    "FUN_00ff8ad0",
    "FUN_00bb8b20",
    "FUN_00e1c7f0",
    "FUN_00c96150",
    "FUN_00d40cc0",
    "FUN_00c4a850",
    "FUN_00c345f0",
    "FUN_00bb1080",
    "FUN_00c85540",
    "FUN_00c85a30",
    "FUN_00b068c0",
    "FUN_00c5fe00",
    "FUN_00b0b150",
    "FUN_00eeb580",
    "FUN_00baf460",
    "FUN_00c86760",
    "FUN_00c8ce40",
    "FUN_00e1d020",
    "FUN_00c34680",
    "FUN_00b2e010",
    "FUN_00bc0180",
    "FUN_00feff80",
    "FUN_00b06a40",
    "FUN_00ac0570",
    "FUN_00bb6040",
    "FUN_00d5fb60",
    "FUN_00d5f4d0",
    "FUN_00d5bfa0",
    "FUN_00c6cf10",
    "FUN_00c4a220",
    "FUN_00bf5630",
    "FUN_00b227c0",
    "FUN_00b06bd0",
    "FUN_0100b0a0",
    "FUN_00d5f780",
    "FUN_00ec8f40",
    "FUN_00b09830",
    "FUN_0102daa0",
    "FUN_00bba790",
    "FUN_00d5c470",
    "FUN_00f40d00",
    "FUN_00fe6bc0",
    "FUN_00cd3bf0",
    "FUN_00e18200",
    "FUN_00d5ccf0",
    "FUN_00c68c00",
    "FUN_00e47700",
    "FUN_00db5e80",
    "FUN_00fe3b90",
    "FUN_00acd2d0",
    "FUN_00e3f970",
    "FUN_01012b50",
    "FUN_00ba1280",
    "FUN_010166c0",
    "FUN_00bb4f30"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00aea5d0",
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
  "name": "FUN_00aea5d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6ea5d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00aea5d0(void)",
  "size_bytes": 332,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00aea5d0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00baed39"
    },
    {
      "from": "00bb6308"
    },
    {
      "from": "00bb11cf"
    },
    {
      "from": "00bb95b7"
    },
    {
      "from": "00bb863c"
    },
    {
      "from": "00bb8703"
    },
    {
      "from": "00bba848"
    },
    {
      "from": "00bba742"
    },
    {
      "from": "00c34218"
    },
    {
      "from": "00b2261b"
    },
    {
      "from": "00c86809"
    },
    {
      "from": "00c855ee"
    },
    {
      "from": "00c8572e"
    },
    {
      "from": "00c86332"
    },
    {
      "from": "00d5c159"
    },
    {
      "from": "00d5c88f"
    },
    {
      "from": "00aeb21e"
    },
    {
      "from": "00c34656"
    },
    {
      "from": "00c346e6"
    },
    {
      "from": "00d5ce26"
    },
    {
      "from": "00b05b89"
    },
    {
      "from": "00d5f7dd"
    },
    {
      "from": "00d5f74a"
    },
    {
      "from": "00e1c81d"
    },
    {
      "from": "00d609f0"
    },
    {
      "from": "00c0a8e8"
    },
    {
      "from": "00cee86b"
    },
    {
      "from": "00c09c0d"
    },
    {
      "from": "00ad162d"
    },
    {
      "from": "00be2b7d"
    },
    {
      "from": "00be1f3f"
    },
    {
      "from": "00bf4462"
    },
    {
      "from": "00aeb37d"
    },
    {
      "from": "00bf567f"
    },
    {
      "from": "00b70734"
    },
    {
      "from": "00c8ced6"
    },
    {
      "from": "01009a86"
    },
    {
      "from": "0102dd60"
    },
    {
      "from": "00b069dc"
    },
    {
      "from": "00b06b77"
    },
    {
      "from": "00b0989d"
    },
    {
      "from": "00b22700"
    },
    {
      "from": "00b22873"
    },
    {
      "from": "00b26433"
    },
    {
      "from": "00b2e0cf"
    },
    {
      "from": "00b0b253"
    },
    {
      "from": "00b0b2e2"
    },
    {
      "from": "00bc0286"
    },
    {
      "from": "00bc055c"
    },
    {
      "from": "00e181be"
    },
    {
      "from": "00e18271"
    },
    {
      "from": "00b77d03"
    },
    {
      "from": "00e3fd4a"
    },
    {
      "from": "00e477ca"
    },
    {
      "from": "00e478fa"
    },
    {
      "from": "00e47e22"
    },
    {
      "from": "00b6163a"
    },
    {
      "from": "00b616ca"
    },
    {
      "from": "00b6175a"
    },
    {
      "from": "00
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
  "file": "src/reconstruction/pkg12_space/space_comm_event_lifecycle.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_comm_event_lifecycle.cpp",
    "reconstruction/staging/pkg12-space/space_comm_event_lifecycle.hpp",
    "reconstruction/staging/pkg12-space/space_comm_event_lifecycle_model_test.cpp",
    "src/reconstruction/pkg12_space/space_comm_event_lifecycle.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg12-space/00aea5d0.json"
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
    "gate-space-comm-event-lifecycle"
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
  "cCommEvent",
  "cCommEvent**",
  "cCommVector",
  "cCommVector*",
  "void"
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
