# Evidence 0x00b9aa10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0648ffee46aa32eb3b733a086e14e919ed24ad8a8b2866242ab81234b77bfac4`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__cdecl",
  "hidden_receiver": "none; ECX is only ever an explicit argument to the __thiscall callees",
  "hidden_this_register": "ECX is loaded with the species manager, the record's property list or an immediate state pointer before each thiscall; it is never read as an implicit receiver",
  "ordinary_stack_argument_slots": 4,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "the only RET is 0x00b9b088, a bare C3 with no immediate, and the four POPs restore the saved registers immediately before it",
  "return_register": "none",
  "return_semantics": "no value; the body has no write to EAX on any exit path and every path ends at the single epilogue",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "ebp_offset": "+0x08",
      "index": 1,
      "meaning": "Vector3*; loaded at 0x00b9addf MOV EDX,dword ptr [EBP + 0x8] and pushed at 0x00b9ae41 as the second argument of the free-cell search. The same pointer is the search's output, so it is an in/out up-direction-then-position slot.",
      "width": 4
    },
    {
      "ebp_offset": "+0x0c",
      "index": 2,
      "meaning": "base of a std::uint32_t array; 0x00b9aab1 MOV ECX,dword ptr [EBP + 0xc] then 0x00b9aab4 MOV EAX,dword ptr [ECX + EAX*0x4]",
      "width": 4
    },
    {
      "ebp_offset": "+0x10",
      "index": 3,
      "meaning": "element count; 0x00b9aaa8 CMP dword ptr [EBP + 0x10],EAX with JBE to skip the loop, and 0x00b9b05f CMP EAX,dword ptr [EBP + 0x10] with JC to continue",
      "width": 4
    },
    {
      "ebp_offset": "+0x14",
      "index": 4,
      "meaning": "opaque extra value; loaded at 0x00b9af8d and pushed at 0x00b9af94 as the fifth argument of 0x00b93f40. The recursive call at 0x00b9b03f passes the current id in this slot.",
      "width": 4
    }
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single epilogue; the two exit paths are the gate-fail jump to 0x00b9b082 and the fall-through of the outer id loop"
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10"
    ],
    "ordinary_stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
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
        "ebp_offset": "EBP+0xc",
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
        "ebp_offset": "EBP+0x10",
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
        "ebp_offset": "EBP+0x14",
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET",
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
        "ebp_offset": "EBP+0x8",
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
        "ebp_offset": "EBP+0xc",
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
        "ebp_offset": "EBP+0x10",
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
        "ebp_offset": "EBP+0x14",
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "unparsed_lines_present: 2 line(s) matched no grammar rule",
    "receiver_not_determinable: ecx_address_taken_without_memory_access",
    "ecx_address_taken_without_memory_access: LEA takes ECX's address without any memory access through it",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_address_taken_without_memory_access), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "3bc725d4841f28d4b46f4a3370e28c8d7111c929f50e9bf8e083d8c84b0534b3",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__thiscall"
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
    "persisted_calling_convention": "__cdecl"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0193"
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
        "obs-0035",
        "obs-0036",
        "obs-0110",
        "obs-0162",
        "obs-0186"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 4,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0022",
        "obs-0023",
        "obs-0026",
        "obs-0036",
        "obs-0059",
        "obs-0072",
        "obs-0079",
        "obs-0127",
        "obs-0137",
        "obs-0146",
        "obs-0149",
        "obs-0150",
        "obs-0164",
        "obs-0171"
      ],
      "claim": "the register receiver is undetermined: ecx_address_taken_without_memory_access",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_address_taken_without_memory_access",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0022",
        "obs-0023",
        "obs-0026",
        "obs-0036",
        "obs-0059",
        "obs-0072",
        "obs-0079",
        "obs-0127",
        "obs-0137",
        "obs-0146",
        "obs-0149",
        "obs-0150",
        "obs-0164",
        "obs-0171"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_address_taken_without_memory_access) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0193"
      ],
      "claim": "entry slot 0 is not written through a pointer",
      "con
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_004df420",
    "reconstructed": false,
    "va": "0x004df420"
  },
  {
    "name": "FUN_00b3d300",
    "reconstructed": true,
    "va": "0x00b3d300"
  },
  {
    "name": "simulator_game_input_manager_get_00b3d350",
    "reconstructed": true,
    "va": "0x00b3d350"
  },
  {
    "name": "FUN_00b5b800",
    "reconstructed": false,
    "va": "0x00b5b800"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b9aa10"
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
    "va": "0x00b9aa10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b9b090"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b9c830"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b9caa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b9d6d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b9d820"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba1590"
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
  "count": 430,
  "instructions": [
    {
      "address": "00b9aa10",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00b9aa11",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "00b9aa13",
      "instruction": "AND ESP,0xfffffff8"
    },
    {
      "address": "00b9aa16",
      "instruction": "SUB ESP,0xdc"
    },
    {
      "address": "00b9aa1c",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b9aa1d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b9aa1e",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b9aa1f",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00b9aa24",
      "instruction": "CALL 0x00b3d350"
    },
    {
      "address": "00b9aa29",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00b9aa2b",
      "instruction": "CALL 0x00401090"
    },
    {
      "address": "00b9aa30",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00b9aa32",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00b9aa34",
      "instruction": "MOV dword ptr [ESP + 0x2c],EBX"
    },
    {
      "address": "00b9aa38",
      "instruction": "CALL 0x004df420"
    },
    {
      "address": "00b9aa3d",
      "instruction": "CALL 0x00b5b800"
    },
    {
      "address": "00b9aa42",
      "instruction": "CMP EAX,0x1654c01"
    },
    {
      "address": "00b9aa47",
      "instruction": "SETZ byte ptr [ESP + 0x13]"
    },
    {
      "address": "00b9aa4c",
      "instruction": "CALL 0x0067cb40"
    },
    {
      "address": "00b9aa51",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b9aa53",
      "instruction": "JZ 0x00b9b082"
    },
    {
      "address": "00b9aa59",
      "instruction": "LEA EAX,[ESP + 0xa4]"
    },
    {
      "address": "00b9aa60",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b9aa62",
      "instruction": "MOV dword ptr [ESP + 0x90],ECX"
    },
    {
      "address": "00b9aa69",
      "instruction": "LEA EDX,[ESP + 0xb8]"
    },
    {
      "address": "00b9aa70",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00b9aa72",
      "instruction": "LEA ECX,[ESP + 0x90]"
    },
    {
      "address": "00b9aa79",
      "instruction": "MOV dword ptr [ESP + 0xa4],0x0"
    },
    {
      "address": "00b9aa84",
      "instruction": "MOV dword ptr [ESP + 0x90],EAX"
    },
    {
      "address": "00b9aa8b",
      "instruction": "MOV dword ptr [ESP + 0x98],EDX"
    },
    {
      "address": "00b9aa92",
      "instruction": "CALL 0x004cd3c0"
    },
    {
      "address": "00b9aa97",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b9aa99",
      "instruction": "CALL 0x00b7e390"
    },
    {
      "address": "00b9aa9e",
      "instruction": "FSTP float ptr [ESP + 0x78]"
    },
    {
      "address": "00b9aaa2",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00b9aaa4",
      "instruction": "MOV dword ptr [ESP + 0x34],EAX"
    },
    {
      "address": "00b9aaa8",
      "instruction": "CMP dword ptr [EBP + 0x10],EAX"
    },
    {
      "address": "00b9aaab",
      "instruction": "JBE 0x00b9b068"
    },
    {
      "address": "00b9aab1",
      "instruction": "MOV ECX,dword ptr [EBP + 0xc]"
    },
    {
      "address": "00b9aab4",
      "instruction": "MOV EAX,dword ptr [ECX + EAX*0x4]"
    },
    {
      "address": "00b9aab7",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00b9aab9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b9aaba",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00b9aabc",
      "instruction": "MOV dword ptr [ESP + 0x40],EAX"
    },
    {
      "address": "00b9aac0",
      "instruction": "CALL 0x004e0050"
    },
    {
      "address": "00b9aac5",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00b9aac7",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00b9aac9",
      "instruction": "JZ 0x00b9b056"
    },
    {
      "address": "00b9aacf",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00b9aad1",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00b9aad3",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00b9aad5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b9aad6",
      "instruction": "LEA EDX,[ESP + 0x9c]"
    },
    {
      "address": "00b9aadd",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00b9aade",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00b9aae0",
      "instruction": "CALL 0x004dfff0"
    },
    {
      "address": "00b9aae5",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b9aae7",
      "instruction": "JG 0x00b9ab0c"
    },
    {
      "address": "00b9aae9",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00b9aaeb",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00b9aaed",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00b9aaef",
      "instruction": "LEA EAX,[ESP + 0x98]"
    },
    {
      "address": "00b9aaf6",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b9aaf7",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b9aaf8",
      "instruction": "CALL 0x00401090"
    },
    {
      "address": "00b9aafd",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b9aaff",
      "instruction": "CALL 0x004dfff0"
    },
    {
      "address": "00b9ab04",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b9ab06",
      "instruction": "JLE 0x00b9b056"
    },
    {
      "address": "00b9ab0c",
      "instruction": "FLD float ptr [ESI + 0x300]"
    },
    {
      "address": "00b9ab12",
      "instruction": "MOV ECX,0x16888e8"
    },
    {
      "address": "00b9ab17",
      "instruction": "FSTP double ptr [ESP + 0x3c]"
    },
    {
      "address": "00b9ab1b",
      "instruction": "FLD float ptr [ESI + 0x304]
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
  "original_bytes": 15818,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__cdecl\",\n    \"hidden_receiver\": \"none; ECX is only ever an explicit argument to the __thiscall callees\",\n    \"hidden_this_register\": \"ECX is loaded with the species manager, the record's property list or an immediate state pointer before each thiscall; it is never read as an implicit receiver\",\n    \"ordinary_stack_argument_slots\": 4,\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"the only RET is 0x00b9b088, a bare C3 with no immediate, and the four POPs restore the saved registers immediately before it\",\n    \"return_register\": \"none\",\n    \"return_semantics\": \"no value; the body has no write to EAX on any exit path and every path ends at the single epilogue\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"ebp_offset\": \"+0x08\",\n        \"index\": 1,\n        \"meaning\": \"Vector3*; loaded at 0x00b9addf MOV EDX,dword ptr [EBP + 0x8] and pushed at 0x00b9ae41 as the second argument of the free-cell search. The same pointer is the search's output, so it is an in/out up-direction-then-position slot.\",\n        \"width\": 4\n      },\n      {\n        \"ebp_offset\": \"+0x0c\",\n        \"index\": 2,\n        \"meaning\": \"base of a std::uint32_t array; 0x00b9aab1 MOV ECX,dword ptr [EBP + 0xc] then 0x00b9aab4 MOV EAX,dword ptr [ECX + EAX*0x4]\",\n        \"width\": 4\n      },\n      {\n        \"ebp_offset\": \"+0x10\",\n        \"index\": 3,\n        \"meaning\": \"element count; 0x00b9aaa8 CMP dword ptr [EBP + 0x10],EAX with JBE to skip the loop, and 0x00b9b05f CMP EAX,dword ptr [EBP + 0x10] with JC to continue\",\n        \"width\": 4\n      },\n      {\n        \"ebp_offset\": \"+0x14\",\n        \"index\": 4,\n        \"meaning\": \"opaque extra value; loaded at 0x00b9af8d and pushed at 0x00b9af94 as the fifth argument of 0x00b93f40. The recursive call at 0x00b9b03f passes the current id in this slot.\",\n        \"width\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"single epilogue; the two exit paths are the gate-fail jump to 0x00b9b082 and the fall-through of the outer id loop\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"simulator_game_input_manager_get_00b3d350\",\n      \"va\": \"0x00b3d350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_bake_probe_004bf770\",\n      \"va\": \"0x004bf770\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 2,\n      \"symbol\": \"App_IStateManager_Get_0067dce0\",\n      \"va\": \"0x0067dce0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 2,\n      \"symbol\": \"app_config_manager_get_0067dcf0\",\n      \"va\": \"0x0067dcf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 2,\n      \"symbol\": \"App_IPropManager_Get_0067ddf0\",\n      \"va\": \"0x0067ddf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 2,\n      \"symbol\": \"FUN_00b3d3a0\",\n      \"va\": \"0x00b3d3a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_004df420\",\n        \"reconstructed\": false,\n        \"va\": \"0x004df420\"\n      },\n      {\n        \"name\": \"FUN_00b3d300\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d300\"\n      },\n      {\n        \"name\": \"simulator_game_input_manager_get_00b3d350\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d350\"\n      },\n      {\n        \"name\": \"FUN_00b5b800\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b5b800\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b9aa10\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b9aa10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b9b090\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b9c830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b9caa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b9d6d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b9d820\"\n      }
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
  "body_end": "00b9b088",
  "body_span_bytes": 1657,
  "body_start": "00b9aa10",
  "callees": [
    "App::Property::GetBool",
    "FUN_00b965d0",
    "FUN_004dfff0",
    "FUN_00b98230",
    "FUN_004e1c70",
    "FUN_004e0050",
    "FUN_00b90ea0",
    "App::Property::GetArrayUInt32",
    "FUN_00b93f40",
    "FUN_00b970c0",
    "FUN_00b96220",
    "FUN_00f47380",
    "FUN_004df420",
    "FUN_00a68fb0",
    "FUN_004cd3c0",
    "FUN_00b906a0",
    "FUN_00b3d300",
    "Simulator::cGameInputManager::Get",
    "FUN_0067cb40",
    "FUN_00b7e390",
    "FUN_00b97720",
    "FUN_009360d0",
    "FUN_00b5b800",
    "FUN_00b938d0",
    "FUN_00b9aa10",
    "FUN_00b9b090",
    "Editors::cSpeciesManager::Get"
  ],
  "callers": [
    "FUN_00b9d820",
    "FUN_00b9caa0",
    "FUN_00b9aa10",
    "FUN_00b9c830",
    "FUN_00b9b090",
    "FUN_00ba1590",
    "FUN_00b9d6d0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b9aa10",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:1",
      "type": "undefined"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:1",
      "type": "undefined"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:1",
      "type": "undefined"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "undefined4"
    },
    {
      "name": "local_34",
      "storage": "Stack[-0x34]:4",
      "type": "undefined4"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    },
    {
      "name": "local_4c",
      "storage": "Stack[-0x4c]:1",
      "type": "undefined"
    },
    {
      "name": "local_50",
      "storage": "Stack[-0x50]:4",
      "type": "undefined4"
    },
    {
      "name": "local_5c",
      "storage": "Stack[-0x5c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_60",
      "storage": "Stack[-0x60]:4",
      "type": "undefined4"
    },
    {
      "name": "local_64",
      "storage": "Stack[-0x64]:4",
      "type": "undefined4"
    },
    {
      "name": "local_68",
      "storage": "Stack[-0x68]:4",
      "type": "undefined4"
    },
    {
      "name": "local_6c",
      "storage": "Stack[-0x6c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_70",
      "storage": "Stack[-0x70]:4",
      "type": "undefined4"
    },
    {
      "name": "local_74",
      "storage": "Stack[-0x74]:4",
      "type": "undefined4"
    },
    {
      "name": "local_78",
      "storage": "Stack[-0x78]:4",
      "type": "undefined4"
    },
    {
      "name": "local_7c",
      "storage": "Stack[-0x7c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_84",
      "storage": "Stack[-0x84]:8",
      "type": "undefined8"
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
    },
    {
      "name": "local_90",
      "storage": "Stack[-0x90]:4",
      "type": "undefined4"
    },
    {
      "name": "local_94",
      "storage": "Stack[-0x94]:4",
      "type": "undefined4"
    },
    {
      "name": "local_98",
      "storage": "Stack[-0x98]:4",
      "type": "undefined4"
    },
    {
      "name": "local_9c",
      "storage": "Stack[-0x9c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_a8",
      "storage": "Stack[-0xa8]:1",
      "type": "undefined"
    },
    {
      "name": "local_ac",
      "storage": "Stack[-0xac]:4",
      "type": "undefined4"
    },
    {
      "name": "local_b4",
      "storage": "Stack[-0xb4]:8",
      "type": "undefined8"
    },
    {
      "name": "local_b8",
      "storage": "Stack[-0xb8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_bc",
      "storage": "Stack[-0xbc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c0",
      "storage": "Stack[-0xc0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c4",
      "storage": "Stack[-0xc4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c8",
      "storage": "Stack[-0xc8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_cc",
      "storage": "Stack[-0xcc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_d0",
      "storage": "Stack[-0xd0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_d4",
      "storage": "Stack[-0xd4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_d5",
      "storage": "Stack[-0xd5]:1",
      "type": "undefined1"
    },
    {
      "name": "local_dc",
      "storage": "Stack[-0xdc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_dd",
      "storage": "Stack[-0xdd]:1",
      "type": "undefined1"
    },
    {
      "name": "local_de",
      "storage": "Stack[-0xde]:1",
      "type": "undefined"
    },
    {
      "name": "local_df",
      "storage": "Stack[-0xdf]:1",
      "type": "undefined1"
    },
    {
      "name": "local_e0",
      "storage": "Stack[-0xe0]:1",
      "type": "undefined1"
    },
    {
      "name": "local_f4",
      "storage": "Stack[-0xf4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_f8",
      "storage": "Stack[-0xf8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_fc",
      "storage": "Stack[-0xfc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_104",
      "storage": "Stack[-0x104]:4",
      "type": "undefined4"
    },
    {
      "name": "local_108",
      "storage": "Stack[-0x108]:4",
 
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
    "reconstruction/staging/wave13-w1-dispatch-b02/b9aa10_place_species_on_cube_map.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b02/b9aa10_place_species_on_cube_map.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b02/00b9aa10.json"
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
    "A runtime trace is required to confirm the discarded draw at 0x00b9af7b really is dead in the shipping build and not consumed by a patched 0x00b906a0.",
    "A runtime trace is required to determine the maximum recursion depth, since neither the self-recursion nor the mutual recursion with 0x00b9b090 has a bound in the body.",
    "A runtime trace is required to observe whether the sorted table at 0x0168890c ever becomes non-empty, which is the only way to learn its element layout.",
    "A runtime trace is required to read the record floats at +0x300/+0x304 and the component selector at 0x0156c060, which together decide the placement count and the acceptance threshold.",
    "No original-process trace has ever been captured for 0x00b9aa10; every claim here is static. The original Cell stage has never been entered in any recorded run."
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
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
