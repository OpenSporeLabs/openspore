# Evidence 0x00b5dbb0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c15fceed4b51625a43ad01bbc9cf17a22cfbd4b1bdd0547bcb023ce070ce7f00`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "ordinary_stack_arguments": [
    "uint32 first_mode at [ESP+0x44] after the local allocation and four register saves",
    "uint32 second_mode at [ESP+0x48] after the local allocation and four register saves"
  ],
  "receiver": "Simulator strategy/mode transition object in ECX",
  "ret_form": "RET 0x8",
  "return": "void"
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
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": false,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": false,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +152, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "dc25fc0098a5fd21979aad4f0a40cc375f3ae8f1079889079dee11a6d97ca194",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 11,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0095"
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
        "obs-0095"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0012",
        "obs-0040",
        "obs-0041",
        "obs-0049",
        "obs-0050",
        "obs-0052",
        "obs-0062",
        "obs-0070",
        "obs-0072",
        "obs-0078",
        "obs-0080",
        "obs-0089"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          92,
          96
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0012",
        "obs-0040",
        "obs-0041",
        "obs-0049",
        "obs-0050",
        "obs-0052",
        "obs-0062",
        "obs-0070",
        "obs-0072",
        "obs-0078",
        "obs-0080",
        "obs-0089",
        "obs-0095"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0095"
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
        "obs-0095"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0095"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
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
      "id": "obs-00
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
    "va": "0x0067dcc0"
  },
  {
    "name": "FUN_00d38840",
    "reconstructed": false,
    "va": "0x00d38840"
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
    "name": "app_simulator_mode_bridge_00b63510",
    "reconstructed": true,
    "va": "0x00b63510"
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
  "count": 269,
  "instructions": [
    {
      "address": "00b5dbb0",
      "instruction": "SUB ESP,0x30"
    },
    {
      "address": "00b5dbb3",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b5dbb4",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00b5dbb5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b5dbb6",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b5dbb7",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00b5dbb9",
      "instruction": "CALL 0x0067ddd0"
    },
    {
      "address": "00b5dbbe",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00b5dbc0",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b5dbc2",
      "instruction": "MOV EAX,dword ptr [EDX + 0x48]"
    },
    {
      "address": "00b5dbc5",
      "instruction": "CALL EAX"
    },
    {
      "address": "00b5dbc7",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "00b5dbcc",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00b5dbce",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00b5dbd0",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00b5dbd2",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b5dbd4",
      "instruction": "MOV EAX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00b5dbd7",
      "instruction": "PUSH 0x685f4af"
    },
    {
      "address": "00b5dbdc",
      "instruction": "CALL EAX"
    },
    {
      "address": "00b5dbde",
      "instruction": "MOV EDI,dword ptr [ESP + 0x48]"
    },
    {
      "address": "00b5dbe2",
      "instruction": "MOV ESI,dword ptr [ESP + 0x44]"
    },
    {
      "address": "00b5dbe6",
      "instruction": "CMP EDI,0x2ccd1d2"
    },
    {
      "address": "00b5dbec",
      "instruction": "JNZ 0x00b5dc20"
    },
    {
      "address": "00b5dbee",
      "instruction": "CMP ESI,0xdbdba1"
    },
    {
      "address": "00b5dbf4",
      "instruction": "JZ 0x00b5dc60"
    },
    {
      "address": "00b5dbf6",
      "instruction": "CMP ESI,0x1654c00"
    },
    {
      "address": "00b5dbfc",
      "instruction": "JZ 0x00b5dc60"
    },
    {
      "address": "00b5dbfe",
      "instruction": "CMP ESI,0x1654c01"
    },
    {
      "address": "00b5dc04",
      "instruction": "JZ 0x00b5dc60"
    },
    {
      "address": "00b5dc06",
      "instruction": "CMP ESI,0x1654c02"
    },
    {
      "address": "00b5dc0c",
      "instruction": "JZ 0x00b5dc60"
    },
    {
      "address": "00b5dc0e",
      "instruction": "CMP ESI,0x1654c04"
    },
    {
      "address": "00b5dc14",
      "instruction": "JZ 0x00b5dc60"
    },
    {
      "address": "00b5dc16",
      "instruction": "CMP ESI,0x1654c05"
    },
    {
      "address": "00b5dc1c",
      "instruction": "JZ 0x00b5dc60"
    },
    {
      "address": "00b5dc1e",
      "instruction": "JMP 0x00b5dc6e"
    },
    {
      "address": "00b5dc20",
      "instruction": "CMP EDI,0x1654c01"
    },
    {
      "address": "00b5dc26",
      "instruction": "JZ 0x00b5dc40"
    },
    {
      "address": "00b5dc28",
      "instruction": "CMP EDI,0x1654c02"
    },
    {
      "address": "00b5dc2e",
      "instruction": "JZ 0x00b5dc40"
    },
    {
      "address": "00b5dc30",
      "instruction": "CMP EDI,0x1654c04"
    },
    {
      "address": "00b5dc36",
      "instruction": "JZ 0x00b5dc40"
    },
    {
      "address": "00b5dc38",
      "instruction": "CMP EDI,0x1654c05"
    },
    {
      "address": "00b5dc3e",
      "instruction": "JNZ 0x00b5dc6e"
    },
    {
      "address": "00b5dc40",
      "instruction": "CMP ESI,0x1654c00"
    },
    {
      "address": "00b5dc46",
      "instruction": "JZ 0x00b5dc60"
    },
    {
      "address": "00b5dc48",
      "instruction": "CMP ESI,0x1654c01"
    },
    {
      "address": "00b5dc4e",
      "instruction": "JZ 0x00b5dc60"
    },
    {
      "address": "00b5dc50",
      "instruction": "CMP ESI,0x1654c02"
    },
    {
      "address": "00b5dc56",
      "instruction": "JZ 0x00b5dc60"
    },
    {
      "address": "00b5dc58",
      "instruction": "CMP ESI,0x1654c04"
    },
    {
      "address": "00b5dc5e",
      "instruction": "JNZ 0x00b5dc6e"
    },
    {
      "address": "00b5dc60",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "00b5dc62",
      "instruction": "CALL 0x0067de90"
    },
    {
      "address": "00b5dc67",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b5dc69",
      "instruction": "CALL 0x007ebce0"
    },
    {
      "address": "00b5dc6e",
      "instruction": "CALL 0x0067cab0"
    },
    {
      "address": "00b5dc73",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00b5dc75",
      "instruction": "PUSH 0x1002"
    },
    {
      "address": "00b5dc7a",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00b5dc7c",
      "instruction": "CALL 0x00801bb0"
    },
    {
      "address": "00b5dc81",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00b5dc83",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00b5dc85",
      "instruction": "CALL 0x008017f0"
    },
    {
      "address": "00b5dc8a",
      "instruction": "CALL 0x00d38840"
    },
    {
      "address": "00b5dc8f",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00b5dc92",
      "instruction": "LEA ECX,[EAX + 0x8]"
    },
    {
      "address": "00b5dc95",
      "instruction": "MOV EAX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "00b5dc98",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b5dc99",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b5dc9a",
      "instruction": "CALL EAX"
    },
    {
      "address": "00b5dc9c",
      "instruction": "CALL 0x00cd40b0"
    },
    {
      "address": "00b5dca1",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00b5dca4",
      "instructi
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
  "original_bytes": 9825,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"ordinary_stack_arguments\": [\n      \"uint32 first_mode at [ESP+0x44] after the local allocation and four register saves\",\n      \"uint32 second_mode at [ESP+0x48] after the local allocation and four register saves\"\n    ],\n    \"receiver\": \"Simulator strategy/mode transition object in ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return\": \"void\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueModeTransition\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE8\",\n      \"score\": 24,\n      \"symbol\": \"simulator_strategy_transition_00b5f040\",\n      \"va\": \"0x00b5f040\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 11,\n      \"symbol\": \"app_simulator_mode_bridge_00b63510\",\n      \"va\": \"0x00b63510\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"app_mode_activate_by_name_007d8360\",\n      \"va\": \"0x007d8360\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"app_mode_activate_007d85b0\",\n      \"va\": \"0x007d85b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"app_mode_activate_index_007d8c80\",\n      \"va\": \"0x007d8c80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"strategy_request_ready_00b5b840\",\n      \"va\": \"0x00b5b840\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"strategy_queue_primary_00b5b880\",\n      \"va\": \"0x00b5b880\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"strategy_queue_secondary_00b5b8a0\",\n      \"va\": \"0x00b5b8a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueModeTransition\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      },\n      {\n        \"name\": \"FUN_00d38840\",\n        \"reconstructed\": false,\n        \"va\": \"0x00d38840\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"app_simulator_mode_bridge_00b63510\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b63510\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b63672\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b63510\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5ddd8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401090\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5dda5\",\n        \"direction\": \"out\",\n        \"other\": \"0x00454cb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5ddc0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00454cb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5de50\",\n        \"direction\": \"out\",\n        \"other\": \"0x00454cb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5de97\",\n        \"direction\": \"out\",\n        \"other\": \"0x00454cb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5dddf\",\n        \"direction\": \"out\",\n        \"other\": \"0x004df310\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5de22\",\n        \"direction\": \"out\",\n        \"other\": \"0x005805e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5dc6e\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067cab0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5dbc7\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5ddf5\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5dbb9\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067ddd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5dc62\",\n        \"direction\": \"out\",\n        \"other\": \"0x006
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
  "body_end": "00b5df06",
  "body_span_bytes": 855,
  "body_start": "00b5dbb0",
  "callees": [
    "FUN_00f47380",
    "FUN_00801bb0",
    "FUN_0067ddd0",
    "FUN_0067cab0",
    "FUN_004df310",
    "FUN_00fd9c60",
    "FUN_00d1bf00",
    "FUN_0067de90",
    "FUN_00cd40b0",
    "FUN_00cf74c0",
    "FUN_0091ba90",
    "FUN_00b335d0",
    "FUN_00454cb0",
    "FUN_0093c570",
    "FUN_008017f0",
    "Graphics::IRenderer::Get",
    "FUN_007ebce0",
    "FUN_00d38840",
    "Editors::cSpeciesManager::Get",
    "App::IAppSystem::Get",
    "FUN_005805e0"
  ],
  "callers": [
    "FUN_00b63510"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b5dbb0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b5dbb0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x75dbb0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b5dbb0(void)",
  "size_bytes": 855,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b5dbb0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00b63672"
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
  "file": "src/reconstruction/pkg_game_mode_wave8/game_mode_wave8.cpp",
  "files": [
    "src/reconstruction/pkg_game_mode_wave8/game_mode_wave8.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-mode-wave8/00b5dbb0.json"
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
    "Bind the live transition, telemetry, renderer, species-manager, service, and text helper implementations before runtime validation; the model test is not an original-process trace."
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
  "OpaqueModeTransition"
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
