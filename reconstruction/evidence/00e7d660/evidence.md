# Evidence 0x00e7d660

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5c3f3013147f57fab0f24f35bfc8cc5b61d01c55a7e0cdb12b80145ca4aa3bc8`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_receiver": "ECX App::cCellModeStrategy*",
  "ordinary_stack_arguments": [
    {
      "evidence": "captured into ESI by MOV ESI,[ESP+0xc] at 0x00e7d670 while ESP was the entry stack pointer minus 8, and used by IMUL ESI, TEST ESI,ESI, and JGE as a signed 32-bit value",
      "name": "nWheelDelta",
      "offset": "ESP+4",
      "slot": 0,
      "type": "int32"
    },
    {
      "evidence": "loaded by FLD float ptr [ESP+0x1c] at 0x00e7d67c into the forwarded word at 0x00e7d680",
      "name": "mouseX",
      "offset": "ESP+8",
      "slot": 1,
      "type": "raw float dword"
    },
    {
      "evidence": "loaded by FLD float ptr [ESP+0xc] at 0x00e7d660 into the forwarded word at 0x00e7d678",
      "name": "mouseY",
      "offset": "ESP+0xc",
      "slot": 2,
      "type": "raw float dword"
    },
    {
      "evidence": "captured into EBX by MOV EBX,[ESP+0x14] at 0x00e7d66b while ESP was the entry stack pointer minus 4, and tested with TEST BL,0x1 and TEST BL,0x2",
      "name": "mouseState",
      "offset": "ESP+0x10",
      "slot": 3,
      "type": "uint32",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x10 on all four return sites",
  "return_register": "AL, set by MOV AL,0x1 or XOR AL,AL",
  "stack_cleanup_bytes": 16
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
      }
    ],
    "ret_form": "RET 0x10",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBX",
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
      }
    ],
    "stack_cleanup_bytes": 16,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path",
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
  "content_sha256": "d7d0a749f09ef9113dd34660556388366d7c91e7c3f5cadf708d76ba0cb0e9fd",
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
    "ghidra_parameter_count": 5,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0024",
        "obs-0030",
        "obs-0035",
        "obs-0039"
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
        "obs-0005",
        "obs-0008",
        "obs-0013"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 4,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0026"
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
        "obs-0003",
        "obs-0026"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0024",
        "obs-0030",
        "obs-0035",
        "obs-0039"
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
        "obs-0010"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00e7d660",
      "count": 7,
      "first_use": 0,
      "first_write_index": 7,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "FLD float ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00e7d660",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0002",
      "index": 0,
      "key": 12,
      "kind": "STACK_SLOT_READ",
      "raw": "FLD float ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e7d664",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b1fbf0",
    "reconstructed": false,
    "va": "0x00b1fbf0"
  }
]
```

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00e5c0f0",
      "0x00e6c860",
      "0x00e7d660"
    ],
    "conflict_id": "U9",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
  "count": 68,
  "instructions": [
    {
      "address": "00e7d660",
      "instruction": "FLD float ptr [ESP + 0xc]"
    },
    {
      "address": "00e7d664",
      "instruction": "MOV ECX,dword ptr [0x016b3c0c]"
    },
    {
      "address": "00e7d66a",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e7d66b",
      "instruction": "MOV EBX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00e7d66f",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e7d670",
      "instruction": "MOV ESI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00e7d674",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e7d675",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00e7d678",
      "instruction": "FSTP float ptr [ESP + 0x4]"
    },
    {
      "address": "00e7d67c",
      "instruction": "FLD float ptr [ESP + 0x1c]"
    },
    {
      "address": "00e7d680",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7d683",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e7d684",
      "instruction": "CALL 0x00697b40"
    },
    {
      "address": "00e7d689",
      "instruction": "TEST BL,0x1"
    },
    {
      "address": "00e7d68c",
      "instruction": "JZ 0x00e7d6ba"
    },
    {
      "address": "00e7d68e",
      "instruction": "CALL 0x00b1fbf0"
    },
    {
      "address": "00e7d693",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e7d695",
      "instruction": "JNZ 0x00e7d6ba"
    },
    {
      "address": "00e7d697",
      "instruction": "MOV EAX,0x88888889"
    },
    {
      "address": "00e7d69c",
      "instruction": "IMUL ESI"
    },
    {
      "address": "00e7d69e",
      "instruction": "ADD EDX,ESI"
    },
    {
      "address": "00e7d6a0",
      "instruction": "SAR EDX,0x6"
    },
    {
      "address": "00e7d6a3",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "00e7d6a5",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "00e7d6a8",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "00e7d6aa",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7d6ab",
      "instruction": "CALL 0x00e50f60"
    },
    {
      "address": "00e7d6b0",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7d6b3",
      "instruction": "POP ESI"
    },
    {
      "address": "00e7d6b4",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00e7d6b6",
      "instruction": "POP EBX"
    },
    {
      "address": "00e7d6b7",
      "instruction": "RET 0x10"
    },
    {
      "address": "00e7d6ba",
      "instruction": "TEST BL,0x2"
    },
    {
      "address": "00e7d6bd",
      "instruction": "JZ 0x00e7d707"
    },
    {
      "address": "00e7d6bf",
      "instruction": "CALL 0x00b1fbf0"
    },
    {
      "address": "00e7d6c4",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e7d6c6",
      "instruction": "JNZ 0x00e7d707"
    },
    {
      "address": "00e7d6c8",
      "instruction": "MOV EAX,[0x016b3c04]"
    },
    {
      "address": "00e7d6cd",
      "instruction": "MOV EDX,dword ptr [EAX + 0x411c]"
    },
    {
      "address": "00e7d6d3",
      "instruction": "LEA ECX,[EAX + 0x1c]"
    },
    {
      "address": "00e7d6d6",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e7d6d7",
      "instruction": "CALL 0x00b721d0"
    },
    {
      "address": "00e7d6dc",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e7d6de",
      "instruction": "JNZ 0x00e7d6e7"
    },
    {
      "address": "00e7d6e0",
      "instruction": "POP ESI"
    },
    {
      "address": "00e7d6e1",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00e7d6e3",
      "instruction": "POP EBX"
    },
    {
      "address": "00e7d6e4",
      "instruction": "RET 0x10"
    },
    {
      "address": "00e7d6e7",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00e7d6e9",
      "instruction": "JGE 0x00e7d710"
    },
    {
      "address": "00e7d6eb",
      "instruction": "FLDZ"
    },
    {
      "address": "00e7d6ed",
      "instruction": "MOV EAX,[0x016b3c14]"
    },
    {
      "address": "00e7d6f2",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7d6f3",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7d6f6",
      "instruction": "PUSH 0x3"
    },
    {
      "address": "00e7d6f8",
      "instruction": "CALL 0x00e7d070"
    },
    {
      "address": "00e7d6fd",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e7d700",
      "instruction": "POP ESI"
    },
    {
      "address": "00e7d701",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00e7d703",
      "instruction": "POP EBX"
    },
    {
      "address": "00e7d704",
      "instruction": "RET 0x10"
    },
    {
      "address": "00e7d707",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e7d708",
      "instruction": "CALL 0x00e51060"
    },
    {
      "address": "00e7d70d",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7d710",
      "instruction": "POP ESI"
    },
    {
      "address": "00e7d711",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00e7d713",
      "instruction": "POP EBX"
    },
    {
      "address": "00e7d714",
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
  "original_bytes": 10698,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_receiver\": \"ECX App::cCellModeStrategy*\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"evidence\": \"captured into ESI by MOV ESI,[ESP+0xc] at 0x00e7d670 while ESP was the entry stack pointer minus 8, and used by IMUL ESI, TEST ESI,ESI, and JGE as a signed 32-bit value\",\n        \"name\": \"nWheelDelta\",\n        \"offset\": \"ESP+4\",\n        \"slot\": 0,\n        \"type\": \"int32\"\n      },\n      {\n        \"evidence\": \"loaded by FLD float ptr [ESP+0x1c] at 0x00e7d67c into the forwarded word at 0x00e7d680\",\n        \"name\": \"mouseX\",\n        \"offset\": \"ESP+8\",\n        \"slot\": 1,\n        \"type\": \"raw float dword\"\n      },\n      {\n        \"evidence\": \"loaded by FLD float ptr [ESP+0xc] at 0x00e7d660 into the forwarded word at 0x00e7d678\",\n        \"name\": \"mouseY\",\n        \"offset\": \"ESP+0xc\",\n        \"slot\": 2,\n        \"type\": \"raw float dword\"\n      },\n      {\n        \"evidence\": \"captured into EBX by MOV EBX,[ESP+0x14] at 0x00e7d66b while ESP was the entry stack pointer minus 4, and tested with TEST BL,0x1 and TEST BL,0x2\",\n        \"name\": \"mouseState\",\n        \"offset\": \"ESP+0x10\",\n        \"slot\": 3,\n        \"type\": \"uint32\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 0x10 on all four return sites\",\n    \"return_register\": \"AL, set by MOV AL,0x1 or XOR AL,AL\",\n    \"stack_cleanup_bytes\": 16\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueCellModeStrategy,int32,raw float dword\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 34,\n      \"symbol\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n      \"va\": \"0x00e5c0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueCellModeStrategy,int32,raw float dword\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 34,\n      \"symbol\": \"cell_mode_strategy_on_mouse_down_00e6c860\",\n      \"va\": \"0x00e6c860\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA,raw float dword\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 18,\n      \"symbol\": \"cell_mode_strategy_on_mouse_move_00e51010\",\n      \"va\": \"0x00e51010\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA,int32\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 18,\n      \"symbol\": \"cell_mode_strategy_on_key_down_00e818f0\",\n      \"va\": \"0x00e818f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:DATA,OpaqueCellModeStrategy\",\n        \"shared_vtable:vtable:0x01485550\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE8\",\n      \"score\": 15,\n      \"symbol\": \"app_c_cell_mode_strategy_dispose_00e81f30\",\n      \"va\": \"0x00e81f30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 11,\n      \"symbol\": \"game_input_on_key_down_00697a50\",\n      \"va\": \"0x00697a50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 11,\n      \"symbol\": \"game_input_on_key_up_00697a80\",\n      \"va\": \"0x00697a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 11,\n      \"symbol\": \"game_input_mouse_up_00697af0\",\n      \"va\": \"0x00697af0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCellModeStrategy\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b1fbf0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b1fbf0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e7d684\",\n        \"direction\": \"out\",\n        \"other\": \"0x00697b40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7d68e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b1fbf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7d6bf\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b1fbf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7d6d7\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b721d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7d6
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
  "body_end": "00e7d716",
  "body_span_bytes": 183,
  "body_start": "00e7d660",
  "callees": [
    "FUN_00b1fbf0",
    "FUN_00e7d070",
    "FUN_00e50f60",
    "FUN_00b721d0",
    "FUN_00e51060",
    "FUN_00697b40"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e7d660",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "App::cCellModeStrategy::OnMouseWheel",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 5,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCellModeStrategy *"
    },
    {
      "name": "nWheelDelta",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "mouseX",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "float"
    },
    {
      "name": "mouseY",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "float"
    },
    {
      "name": "mouseState",
      "ordinal": 4,
      "storage": "Stack[0x14]:4",
      "type": "MouseState"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0xa7d660",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cCellModeStrategy::OnMouseWheel(cCellModeStrategy * this, int nWheelDelta, float mouseX, float mouseY, MouseState mouseState)",
  "size_bytes": 183,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e7d660",
  "vtables": {
    "referenced_by_vtables": [
      "0x01485550"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01485590"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseWheel.c",
  "file": "src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseWheel.c",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8.hpp",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-input-wave8/00e7d660.json"
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
    "Observe the concrete vtable call shape, the effective return of 0x00b1fbf0 including any patching, the 0x00b721d0 lookup result, the wheel accumulator at Game input offset 0x44, and the 0x00e7d070 effects in the original Cell mode."
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
  "DATA",
  "OpaqueCellModeStrategy",
  "bool in AL, true on every path except one",
  "int32",
  "raw float dword",
  "uint32"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00000014",
  "vtable:0x01485550",
  "vtable:0x01485590"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00e5c0f0",
      "0x00e6c860",
      "0x00e7d660"
    ],
    "conflict_id": "U9",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
