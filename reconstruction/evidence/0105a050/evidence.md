# Evidence 0x0105a050

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7dd4eb8b8e69caf296ebe408dcc14085e51bbb0bafdc61ff43251344116c4767`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x4",
    "entry_ESP+0x8",
    "entry_ESP+0xc",
    "entry_ESP+0x10"
  ],
  "ordinary_stack_arguments": 4,
  "receiver_register": "ECX",
  "ret_form": "RET 0x10",
  "return_register": "EAX",
  "return_semantics": "boolean_in_AL",
  "return_type": "bool",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 16,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x10 at 0x0105a0f0 on the false path and RET 0x10 at 0x0105a0f9 on the true path"
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
    "ret_form": "RET 0x10",
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
    "stack_cleanup_bytes": 16,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x10",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "b02c6d20d20e37a0d5fe32e9b7572a999a7010f07c46bc4f4bf1239a647d9749",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
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
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0028",
        "obs-0030"
      ],
      "claim": "the callee pops 16 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 16,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0004",
        "obs-0009"
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
        "obs-0014",
        "obs-0019",
        "obs-0020"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0014",
        "obs-0019",
        "obs-0020"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0028",
        "obs-0030"
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
        "obs-0006"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x0105a050",
      "count": 7,
      "first_use": 0,
      "first_write_index": 2,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x0105a050",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0002",
      "index": 0,
      "key": 12,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0105a050",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0xc]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0105a054",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0004",
      "index": 1,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0105a054",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ESP + 0x8]",
      "reg": "E
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "root_accessor_00b3d430",
    "reconstructed": true,
    "va": "0x00b3d430"
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
    "va": "0x0105a110"
  },
  {
    "name": "FUN_0105a890",
    "reconstructed": false,
    "va": "0x0105a890"
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
  "count": 57,
  "instructions": [
    {
      "address": "0105a050",
      "instruction": "MOV EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "0105a054",
      "instruction": "MOV EDX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0105a058",
      "instruction": "SUB ESP,0x18"
    },
    {
      "address": "0105a05b",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0105a05c",
      "instruction": "MOV ESI,dword ptr [ESP + 0x20]"
    },
    {
      "address": "0105a060",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0105a062",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0105a063",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0105a064",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0105a065",
      "instruction": "CALL 0x010593e0"
    },
    {
      "address": "0105a06a",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0105a06c",
      "instruction": "JZ 0x0105a0f3"
    },
    {
      "address": "0105a072",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0105a074",
      "instruction": "CALL 0x0104bdb0"
    },
    {
      "address": "0105a079",
      "instruction": "FLDZ"
    },
    {
      "address": "0105a07b",
      "instruction": "FXCH"
    },
    {
      "address": "0105a07d",
      "instruction": "FCOMIP ST0,ST1"
    },
    {
      "address": "0105a07f",
      "instruction": "FSTP ST0"
    },
    {
      "address": "0105a081",
      "instruction": "JBE 0x0105a0ea"
    },
    {
      "address": "0105a083",
      "instruction": "MOV ECX,dword ptr [ESI + 0x124]"
    },
    {
      "address": "0105a089",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0105a08b",
      "instruction": "JZ 0x0105a0ea"
    },
    {
      "address": "0105a08d",
      "instruction": "CALL 0x00cb5ba0"
    },
    {
      "address": "0105a092",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0105a094",
      "instruction": "JNZ 0x0105a0ae"
    },
    {
      "address": "0105a096",
      "instruction": "MOV EAX,dword ptr [ESI + 0x124]"
    },
    {
      "address": "0105a09c",
      "instruction": "CMP byte ptr [EAX + 0x16c],0x0"
    },
    {
      "address": "0105a0a3",
      "instruction": "JNZ 0x0105a0ae"
    },
    {
      "address": "0105a0a5",
      "instruction": "CMP byte ptr [EAX + 0x16d],0x0"
    },
    {
      "address": "0105a0ac",
      "instruction": "JZ 0x0105a0ea"
    },
    {
      "address": "0105a0ae",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0105a0b0",
      "instruction": "CALL 0x0104cd40"
    },
    {
      "address": "0105a0b5",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0105a0b7",
      "instruction": "JZ 0x0105a0ea"
    },
    {
      "address": "0105a0b9",
      "instruction": "LEA EAX,[ESP + 0x4]"
    },
    {
      "address": "0105a0bd",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0105a0be",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "0105a0c2",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0105a0c3",
      "instruction": "MOV ECX,dword ptr [ESI + 0x124]"
    },
    {
      "address": "0105a0c9",
      "instruction": "CALL 0x00cb8ba0"
    },
    {
      "address": "0105a0ce",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0105a0d0",
      "instruction": "CALL 0x0104bdb0"
    },
    {
      "address": "0105a0d5",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0105a0d6",
      "instruction": "LEA EDX,[ESP + 0x8]"
    },
    {
      "address": "0105a0da",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "0105a0dd",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0105a0de",
      "instruction": "CALL 0x00b3d430"
    },
    {
      "address": "0105a0e3",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0105a0e5",
      "instruction": "CALL 0x00bbec40"
    },
    {
      "address": "0105a0ea",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "0105a0ec",
      "instruction": "POP ESI"
    },
    {
      "address": "0105a0ed",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "0105a0f0",
      "instruction": "RET 0x10"
    },
    {
      "address": "0105a0f3",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "0105a0f5",
      "instruction": "POP ESI"
    },
    {
      "address": "0105a0f6",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "0105a0f9",
      "instruction": "RET 0x10"
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
  "original_bytes": 9810,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\",\n      \"entry_ESP+0x8\",\n      \"entry_ESP+0xc\",\n      \"entry_ESP+0x10\"\n    ],\n    \"ordinary_stack_arguments\": 4,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x10\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"boolean_in_AL\",\n    \"return_type\": \"bool\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 16,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x10 at 0x0105a0f0 on the false path and RET 0x10 at 0x0105a0f9 on the true path\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-core-systems\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"root_accessor_00b3d430\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d430\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0105a110\"\n      },\n      {\n        \"name\": \"FUN_0105a890\",\n        \"reconstructed\": false,\n        \"va\": \"0x0105a890\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0105a128\",\n        \"direction\": \"in\",\n        \"other\": \"0x0105a110\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a8af\",\n        \"direction\": \"in\",\n        \"other\": \"0x0105a890\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a0de\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d430\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a0e5\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bbec40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a08d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00cb5ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a0c9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00cb8ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a074\",\n        \"direction\": \"out\",\n        \"other\": \"0x0104bdb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a0d0\",\n        \"direction\": \"out\",\n        \"other\": \"0x0104bdb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a0b0\",\n        \"direction\": \"out\",\n        \"other\": \"0x0104cd40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a065\",\n        \"direction\": \"out\",\n        \"other\": \"0x010593e0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 2,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00b3d430\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0613\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"FUN_0105a050\",\n  \"normalized_symbol\": \"FUN_0105a050\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worke
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
  "body_end": "0105a0fb",
  "body_span_bytes": 172,
  "body_start": "0105a050",
  "callees": [
    "FUN_0104bdb0",
    "FUN_00cb8ba0",
    "FUN_00bbec40",
    "FUN_00b3d430",
    "FUN_010593e0",
    "FUN_00cb5ba0",
    "FUN_0104cd40"
  ],
  "callers": [
    "FUN_0105a110",
    "FUN_0105a890"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0105a050",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:1",
      "type": "undefined"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:1",
      "type": "undefined"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_0105a050",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc5a050",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0105a050(void)",
  "size_bytes": 172,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0105a050",
  "vtables": {
    "referenced_by_vtables": [
      "0x0149b8b4",
      "0x0149b900"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "0105a128"
    },
    {
      "from": "0105a8af"
    },
    {
      "from": "0149b808"
    },
    {
      "from": "0149b948"
    },
    {
      "from": "0105bd33"
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
    "reconstruction/staging/pkg11-h5-update-gate-0105a050/tool_update_gate_0105a050.cpp",
    "reconstruction/staging/pkg11-h5-update-gate-0105a050/tool_update_gate_0105a050.hpp",
    "reconstruction/staging/pkg11-h5-update-gate-0105a050/tool_update_gate_0105a050_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg11-h5-update-gate-0105a050/0105a050.json"
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
    "no original-process trace exists in this repository; the static reconstruction of 0x0105a050 is unvalidated at runtime",
    "the committed evidence pack for this target has no disassembly and no decompilation, so no listing-dependent check can be adjudicated from committed evidence; every listing fact here was read from the live bridge"
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "bool"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0149b8b4",
  "vtable:0x0149b900"
]
```

## Conflicts

```json
[]
```
