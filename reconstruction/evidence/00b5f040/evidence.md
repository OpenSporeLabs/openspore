# Evidence 0x00b5f040

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `32644721d7a80f20066724506eb79914cf19df062db9dad4acca07f8846f67a9`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "ordinary_stack_arguments": [
    "uint32 first_mode at [ESP+0x14] after four register saves",
    "uint32 second_mode at [ESP+0x18] after four register saves"
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
    "flow_not_modelled: the linear ESP walk ends at +72, so the listing is not one path"
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
  "content_sha256": "d8b8f6b1d7c47f92784092f0d1b632c9821907d4a8a41f55444676a39fe534cb",
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
    "indirect_calls": 8,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0051"
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
        "obs-0010",
        "obs-0012"
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
        "obs-0006",
        "obs-0007",
        "obs-0017"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          12,
          92,
          96
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0017",
        "obs-0051"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0051"
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
        "obs-0051"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0051"
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
      "at": "0x00b5f040",
      "count": 9,
      "first_use": 0,
      "first_write_index": 31,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00b5f041",
      "count": 9,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00b5f041",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x00b5f042",
      "count": 10,
      "first_use": 2,
      "first_write_index": 7,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b5f043",
      "count": 10,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b5f044",
      "count": 10,
      "first_use": 4,
      "first_write_index": 18,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
   
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d380",
    "reconstructed": false,
    "va": "0x00b3d380"
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
  "count": 128,
  "instructions": [
    {
      "address": "00b5f040",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b5f041",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00b5f042",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b5f043",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b5f044",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00b5f046",
      "instruction": "CALL 0x00b3d320"
    },
    {
      "address": "00b5f04b",
      "instruction": "MOV EBP,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00b5f04f",
      "instruction": "MOV ESI,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00b5f053",
      "instruction": "MOV dword ptr [EAX + 0x24],EBP"
    },
    {
      "address": "00b5f056",
      "instruction": "MOV dword ptr [EAX + 0x20],ESI"
    },
    {
      "address": "00b5f059",
      "instruction": "MOV byte ptr [EAX + 0x28],0x0"
    },
    {
      "address": "00b5f05d",
      "instruction": "MOV byte ptr [0x01686af0],0x0"
    },
    {
      "address": "00b5f064",
      "instruction": "CMP EBP,0x2ccd1d2"
    },
    {
      "address": "00b5f06a",
      "instruction": "JNZ 0x00b5f078"
    },
    {
      "address": "00b5f06c",
      "instruction": "CMP ESI,0xdbdba1"
    },
    {
      "address": "00b5f072",
      "instruction": "SETNZ AL"
    },
    {
      "address": "00b5f075",
      "instruction": "MOV byte ptr [EDI + 0xc],AL"
    },
    {
      "address": "00b5f078",
      "instruction": "CALL 0x00b3d380"
    },
    {
      "address": "00b5f07d",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b5f07f",
      "instruction": "CALL 0x00b31a90"
    },
    {
      "address": "00b5f084",
      "instruction": "CMP ESI,0x2ccd1d2"
    },
    {
      "address": "00b5f08a",
      "instruction": "JZ 0x00b5f099"
    },
    {
      "address": "00b5f08c",
      "instruction": "CMP ESI,-0x1"
    },
    {
      "address": "00b5f08f",
      "instruction": "JZ 0x00b5f099"
    },
    {
      "address": "00b5f091",
      "instruction": "CMP ESI,0x1654c08"
    },
    {
      "address": "00b5f097",
      "instruction": "JNZ 0x00b5f09e"
    },
    {
      "address": "00b5f099",
      "instruction": "CALL 0x00b2fbe0"
    },
    {
      "address": "00b5f09e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b5f09f",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00b5f0a1",
      "instruction": "CALL 0x00b5e3f0"
    },
    {
      "address": "00b5f0a6",
      "instruction": "CALL 0x00805070"
    },
    {
      "address": "00b5f0ab",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00b5f0ad",
      "instruction": "PUSH 0x5b598f6"
    },
    {
      "address": "00b5f0b2",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00b5f0b4",
      "instruction": "CALL 0x00810760"
    },
    {
      "address": "00b5f0b9",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00b5f0bb",
      "instruction": "JNZ 0x00b5f0cb"
    },
    {
      "address": "00b5f0bd",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00b5f0bf",
      "instruction": "PUSH 0x5b598f6"
    },
    {
      "address": "00b5f0c4",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00b5f0c6",
      "instruction": "CALL 0x00810660"
    },
    {
      "address": "00b5f0cb",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b5f0cc",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00b5f0cd",
      "instruction": "CALL 0x00b33970"
    },
    {
      "address": "00b5f0d2",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00b5f0d5",
      "instruction": "CALL 0x0067caa0"
    },
    {
      "address": "00b5f0da",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00b5f0dc",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b5f0de",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "00b5f0e1",
      "instruction": "CALL EAX"
    },
    {
      "address": "00b5f0e3",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b5f0e5",
      "instruction": "JZ 0x00b5f0ec"
    },
    {
      "address": "00b5f0e7",
      "instruction": "LEA EBX,[EAX + -0x4]"
    },
    {
      "address": "00b5f0ea",
      "instruction": "JMP 0x00b5f0ee"
    },
    {
      "address": "00b5f0ec",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00b5f0ee",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00b5f0f0",
      "instruction": "CALL 0x008153e0"
    },
    {
      "address": "00b5f0f5",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00b5f0f7",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00b5f0f9",
      "instruction": "CALL 0x00812d60"
    },
    {
      "address": "00b5f0fe",
      "instruction": "MOV ECX,dword ptr [EDI + 0x60]"
    },
    {
      "address": "00b5f101",
      "instruction": "SUB ECX,dword ptr [EDI + 0x5c]"
    },
    {
      "address": "00b5f104",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00b5f106",
      "instruction": "SAR ECX,0x2"
    },
    {
      "address": "00b5f109",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00b5f10b",
      "instruction": "JBE 0x00b5f12d"
    },
    {
      "address": "00b5f10d",
      "instruction": "LEA ECX,[ECX]"
    },
    {
      "address": "00b5f110",
      "instruction": "MOV EDX,dword ptr [EDI + 0x5c]"
    },
    {
      "address": "00b5f113",
      "instruction": "MOV ECX,dword ptr [EDX + EBX*0x4]"
    },
    {
      "address": "00b5f116",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00b5f118",
      "instruction": "MOV EDX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00b5f11b",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b5f11c",
      "instruction": "PUSH EBP"
    },
 
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
  "original_bytes": 8564,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"ordinary_stack_arguments\": [\n      \"uint32 first_mode at [ESP+0x14] after four register saves\",\n      \"uint32 second_mode at [ESP+0x18] after four register saves\"\n    ],\n    \"receiver\": \"Simulator strategy/mode transition object in ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return\": \"void\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueModeTransition\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE8\",\n      \"score\": 24,\n      \"symbol\": \"simulator_strategy_transition_00b5dbb0\",\n      \"va\": \"0x00b5dbb0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 11,\n      \"symbol\": \"app_simulator_mode_bridge_00b63510\",\n      \"va\": \"0x00b63510\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"app_mode_activate_by_name_007d8360\",\n      \"va\": \"0x007d8360\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"app_mode_activate_007d85b0\",\n      \"va\": \"0x007d85b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"app_mode_activate_index_007d8c80\",\n      \"va\": \"0x007d8c80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"strategy_request_ready_00b5b840\",\n      \"va\": \"0x00b5b840\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"strategy_queue_primary_00b5b880\",\n      \"va\": \"0x00b5b880\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-MODE-WAVE7\",\n      \"score\": 8,\n      \"symbol\": \"strategy_queue_secondary_00b5b8a0\",\n      \"va\": \"0x00b5b8a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueModeTransition\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d380\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b3d380\"\n      },\n      {\n        \"name\": \"FUN_00d38840\",\n        \"reconstructed\": false,\n        \"va\": \"0x00d38840\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"app_simulator_mode_bridge_00b63510\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b63510\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b63664\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b63510\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5f0d5\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067caa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5f192\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067cab0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5f199\",\n        \"direction\": \"out\",\n        \"other\": \"0x008017f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5f0a6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00805070\",\n        \"reference_type\": \"thunk\"\n      },\n      {\n        \"callsite\": \"0x00b5f0c6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00810660\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5f0b4\",\n        \"direction\": \"out\",\n        \"other\": \"0x00810760\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5f0f9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00812d60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5f0f0\",\n        \"direction\": \"out\",\n        \"other\": \"0x008153e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5f099\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b2fbe0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5f07f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b31a90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5f0cd\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b33970\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5f046\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d320\",\n        \"reference_type\": \"dire
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
  "body_end": "00b5f1a4",
  "body_span_bytes": 357,
  "body_start": "00b5f040",
  "callees": [
    "FUN_00810760",
    "thunk_FUN_0080fee0",
    "FUN_008153e0",
    "FUN_00b5e3f0",
    "FUN_0067cab0",
    "FUN_00b3d380",
    "FUN_00812d60",
    "FUN_00fd9c60",
    "FUN_00d1bf00",
    "FUN_00cd40b0",
    "FUN_00cf74c0",
    "FUN_00b2fbe0",
    "FUN_00810660",
    "FUN_00b31a90",
    "FUN_00b33970",
    "FUN_0067caa0",
    "FUN_008017f0",
    "FUN_00d38840",
    "FUN_00b3d320"
  ],
  "callers": [
    "FUN_00b63510"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b5f040",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b5f040",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x75f040",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b5f040(void)",
  "size_bytes": 357,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b5f040",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00b63664"
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
    "reconstruction/metadata/pkg-game-mode-wave8/00b5f040.json"
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
    "Bind the live receiver vtable, participant list, shared-state root, and service callbacks before runtime validation; the model test is not an original-process trace."
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
