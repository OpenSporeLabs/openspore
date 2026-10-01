# Evidence 0x005dd610

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f94eaad3f0ee2de46823d0f7656ce0fdf6003001db4f19c143bd01c25562fab7`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+4",
      "name": "lighting_state",
      "observed_values": [
        0,
        1
      ],
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
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
      "entry_ESP+0x4"
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
      }
    ],
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBX",
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +124, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "bd0d1d6c3ec10c070106921df458e70bdec2744bcde2328e7efe3df14414b161",
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
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0029",
        "obs-0040"
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
        "obs-0029",
        "obs-0040"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0008"
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
        "obs-0002",
        "obs-0003",
        "obs-0008"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0029",
        "obs-0040"
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
        "obs-0029",
        "obs-0040"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0029",
        "obs-0040"
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
      "at": "0x005dd610",
      "count": 11,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005dd611",
      "count": 3,
      "first_use": 1,
      "first_write_index": 15,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005dd611",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x005dd61d",
      "id": "obs-0004",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x008105b0",
      "target": "0x008105b0"
    },
    {
      "at": "0x005dd630",
      "id": "obs-0005",
      "index": 11,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x008105b0",
      "target": "0x008105b0"
    },
    {
      "at": "0x005dd63d",
      "count": 12,
      "first_use": 14,
      "first_write_index": 16,
      "id": "obs-0006",
      "index": 14,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x005dd63d",
      "definite": true,
      "id": "obs-0007",
      "index": 14,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005dd63f",
      "definite": true,
      "id": "obs-0008",
      "index": 15,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x005dd641",
      "count": 5,
  
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
    "va": "0x0045b150"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005dcf20"
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
    "name": "FUN_005dda30",
    "reconstructed": true,
    "va": "0x005dda30"
  },
  {
    "name": "editor_query_dispatch_005dfd00",
    "reconstructed": true,
    "va": "0x005dfd00"
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
  "count": 99,
  "instructions": [
    {
      "address": "005dd610",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005dd611",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005dd613",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dd615",
      "instruction": "PUSH 0x47bc920"
    },
    {
      "address": "005dd61a",
      "instruction": "LEA ECX,[ESI + 0x14]"
    },
    {
      "address": "005dd61d",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005dd622",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005dd624",
      "instruction": "JNZ 0x005dd63d"
    },
    {
      "address": "005dd626",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dd628",
      "instruction": "PUSH 0x47bc920"
    },
    {
      "address": "005dd62d",
      "instruction": "LEA ECX,[ESI + 0x2c]"
    },
    {
      "address": "005dd630",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005dd635",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005dd637",
      "instruction": "JZ 0x005dd73e"
    },
    {
      "address": "005dd63d",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005dd63f",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005dd641",
      "instruction": "MOV EAX,dword ptr [EDX + 0x28]"
    },
    {
      "address": "005dd644",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005dd645",
      "instruction": "CALL EAX"
    },
    {
      "address": "005dd647",
      "instruction": "MOV BL,byte ptr [ESP + 0xc]"
    },
    {
      "address": "005dd64b",
      "instruction": "AND AL,0x1"
    },
    {
      "address": "005dd64d",
      "instruction": "CMP AL,BL"
    },
    {
      "address": "005dd64f",
      "instruction": "JZ 0x005dd73d"
    },
    {
      "address": "005dd655",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "005dd657",
      "instruction": "SETZ CL"
    },
    {
      "address": "005dd65a",
      "instruction": "MOVZX EDX,CL"
    },
    {
      "address": "005dd65d",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dd65f",
      "instruction": "PUSH EDX"
    },
    {
      "address": "005dd660",
      "instruction": "CALL 0x0067cac0"
    },
    {
      "address": "005dd665",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005dd667",
      "instruction": "CALL 0x0067c420"
    },
    {
      "address": "005dd66c",
      "instruction": "CALL 0x00805070"
    },
    {
      "address": "005dd671",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "005dd673",
      "instruction": "JZ 0x005dd6e0"
    },
    {
      "address": "005dd675",
      "instruction": "CALL 0x0067dd50"
    },
    {
      "address": "005dd67a",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005dd67c",
      "instruction": "PUSH 0x2"
    },
    {
      "address": "005dd67e",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005dd680",
      "instruction": "MOV EAX,dword ptr [EDX + 0x5c]"
    },
    {
      "address": "005dd683",
      "instruction": "PUSH 0x16"
    },
    {
      "address": "005dd685",
      "instruction": "CALL EAX"
    },
    {
      "address": "005dd687",
      "instruction": "PUSH 0x4c4ba0a9"
    },
    {
      "address": "005dd68c",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005dd68e",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dd690",
      "instruction": "PUSH 0x4c4ba0a9"
    },
    {
      "address": "005dd695",
      "instruction": "CALL 0x00401050"
    },
    {
      "address": "005dd69a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005dd69c",
      "instruction": "CALL 0x0045ae40"
    },
    {
      "address": "005dd6a1",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dd6a3",
      "instruction": "PUSH 0x47bc920"
    },
    {
      "address": "005dd6a8",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005dd6aa",
      "instruction": "CALL 0x005dc340"
    },
    {
      "address": "005dd6af",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dd6b1",
      "instruction": "PUSH 0x65e561d"
    },
    {
      "address": "005dd6b6",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005dd6b8",
      "instruction": "CALL 0x005dc340"
    },
    {
      "address": "005dd6bd",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005dd6bf",
      "instruction": "PUSH 0x65e4ef4"
    },
    {
      "address": "005dd6c4",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005dd6c6",
      "instruction": "CALL 0x005dc340"
    },
    {
      "address": "005dd6cb",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005dd6cd",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dd6cf",
      "instruction": "PUSH 0x47bc8d8"
    },
    {
      "address": "005dd6d4",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005dd6d6",
      "instruction": "CALL 0x005dcf20"
    },
    {
      "address": "005dd6db",
      "instruction": "POP EBX"
    },
    {
      "address": "005dd6dc",
      "instruction": "POP ESI"
    },
    {
      "address": "005dd6dd",
      "instruction": "RET 0x4"
    },
    {
      "address": "005dd6e0",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005dd6e2",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005dd6e4",
      "instruction": "PUSH 0x47bc8d8"
    },
    {
      "address": "005dd6e9",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005dd6eb",
      "instruction": "CALL 0x005dcf20"
    },
    {
      "address": "005dd6f0",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dd6f2",
      "instruction": "PUSH 0x65e4ef4"
    },
    {
      "address": "005dd6f7",
      "instruction": "MOV ECX,ESI"
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
  "original_bytes": 7841,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+4\",\n        \"name\": \"lighting_state\",\n        \"observed_values\": [\n          0,\n          1\n        ],\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 5,\n      \"symbol\": \"FUN_005dda30\",\n      \"va\": \"0x005dda30\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The binary exposes no RTTI for the lighting object.\",\n    \"The declaration preserves the raw 32-bit stack slot and does not name the state values.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0045b150\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dcf20\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"FUN_005dda30\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dda30\"\n      },\n      {\n        \"name\": \"editor_query_dispatch_005dfd00\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dfd00\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005dda7e\",\n        \"direction\": \"in\",\n        \"other\": \"0x005dda30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dffa6\",\n        \"direction\": \"in\",\n        \"other\": \"0x005dfd00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd695\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401050\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd71f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401050\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd69c\",\n        \"direction\": \"out\",\n        \"other\": \"0x0045ae40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd726\",\n        \"direction\": \"out\",\n        \"other\": \"0x0045b150\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd6aa\",\n        \"direction\": \"out\",\n        \"other\": \"0x005dc340\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd6b8\",\n        \"direction\": \"out\",\n        \"other\": \"0x005dc340\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd6c6\",\n        \"direction\": \"out\",\n        \"other\": \"0x005dc340\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd6f9\",\n        \"direction\": \"out\",\n        \"other\": \"0x005dc340\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd707\",\n        \"direction\": \"out\",\n        \"other\": \"0x005dc340\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd715\",\n        \"direction\": \"out\",\n        \"other\": \"0x005dc340\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd6d6\",\n        \"direction\": \"out\",\n        \"other\": \"0x005dcf20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd6eb\",\n        \"direction\": \"out\",\n        \"other\": \"0x005dcf20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dd667\",\n        \"di
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
  "body_end": "005dd741",
  "body_span_bytes": 306,
  "body_start": "005dd610",
  "callees": [
    "thunk_FUN_0080fee0",
    "FUN_008105b0",
    "FUN_0067cac0",
    "FUN_00401050",
    "FUN_005dcf20",
    "FUN_0067c420",
    "FUN_0045b150",
    "FUN_0045ae40",
    "FUN_005dc340",
    "Graphics::ILightingManager::Get"
  ],
  "callers": [
    "FUN_005dfd00",
    "FUN_005dda30"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005dd610",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005dd610",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1dd610",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005dd610(void)",
  "size_bytes": 306,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005dd610",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "005dda7e"
    },
    {
      "from": "005dffa6"
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
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/005dd610.json"
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueEditorModeManager for ECX",
  "uint32_t",
  "uint32_t for the observed state flag",
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
