# Evidence 0x00697af0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `77f15bf4ed652dcae50d10c0c80b6607ed7e3c3b1e9961c017408b4bfae5cb52`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_receiver": "ECX OpaqueGameInput*",
  "ordinary_stack_arguments": [
    {
      "name": "button",
      "offset": "ESP+4",
      "slot": 0,
      "type": "int32"
    },
    {
      "name": "mouseX",
      "offset": "ESP+8",
      "slot": 1,
      "type": "float"
    },
    {
      "name": "mouseY",
      "offset": "ESP+0xc",
      "slot": 2,
      "type": "float"
    },
    {
      "offset": "ESP+0x10",
      "slot": 3,
      "type": "MouseState",
      "use": "not read",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 16",
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x10",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x10",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "87490f82450464921dc99aaccdb71691dafea1e26574dec563bdf7d30819759e",
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
        "obs-0012"
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
        "obs-0011"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          44,
          48,
          52
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0012"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0002"
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
        "obs-0012"
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
        "obs-0012"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00697af0",
      "count": 3,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00697af0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00697af0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00697af4",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0004",
      "index": 1,
      "key": 8,
      "kind": "STACK_SL
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
    "name": "cell_mode_strategy_on_mouse_up_00e5c0f0",
    "reconstructed": true,
    "va": "0x00e5c0f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f4f630"
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
  "count": 11,
  "instructions": [
    {
      "address": "00697af0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00697af4",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00697afa",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00697afc",
      "instruction": "MOV byte ptr [EAX + ECX*0x1 + 0xfffffc3c],DL"
    },
    {
      "address": "00697b03",
      "instruction": "MOVSS dword ptr [ECX + 0x2c],XMM0"
    },
    {
      "address": "00697b08",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00697b0e",
      "instruction": "MOVSS dword ptr [ECX + 0x30],XMM0"
    },
    {
      "address": "00697b13",
      "instruction": "CMP dword ptr [ECX + 0x34],EAX"
    },
    {
      "address": "00697b16",
      "instruction": "JNZ 0x00697b1b"
    },
    {
      "address": "00697b18",
      "instruction": "MOV dword ptr [ECX + 0x34],EDX"
    },
    {
      "address": "00697b1b",
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
  "original_bytes": 7606,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_receiver\": \"ECX OpaqueGameInput*\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"name\": \"button\",\n        \"offset\": \"ESP+4\",\n        \"slot\": 0,\n        \"type\": \"int32\"\n      },\n      {\n        \"name\": \"mouseX\",\n        \"offset\": \"ESP+8\",\n        \"slot\": 1,\n        \"type\": \"float\"\n      },\n      {\n        \"name\": \"mouseY\",\n        \"offset\": \"ESP+0xc\",\n        \"slot\": 2,\n        \"type\": \"float\"\n      },\n      {\n        \"offset\": \"ESP+0x10\",\n        \"slot\": 3,\n        \"type\": \"MouseState\",\n        \"use\": \"not read\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 16\",\n    \"stack_cleanup_bytes\": 16\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput,int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 27,\n      \"symbol\": \"game_input_on_key_down_00697a50\",\n      \"va\": \"0x00697a50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput,int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 27,\n      \"symbol\": \"game_input_on_key_up_00697a80\",\n      \"va\": \"0x00697a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput,int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 27,\n      \"symbol\": \"cell_mode_strategy_on_key_down_00e818f0\",\n      \"va\": \"0x00e818f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"cell_mode_strategy_on_mouse_move_00e51010\",\n      \"va\": \"0x00e51010\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueGameInput\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"simulator_game_input_manager_get_00b3d350\",\n      \"va\": \"0x00b3d350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 14,\n      \"symbol\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n      \"va\": \"0x00e5c0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 11,\n      \"symbol\": \"cell_mode_strategy_on_mouse_down_00e6c860\",\n      \"va\": \"0x00e6c860\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 11,\n      \"symbol\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n      \"va\": \"0x00e7d660\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueGameInput\",\n  \"cluster\": \"gameglobal-misc\",\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5c0f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f4f630\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e5c115\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e5c0f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f4f78a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00f4f630\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 2,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00e5c0f0\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0196\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"GameInput_MouseUp\",\n  \"normalized_symbol\": \"game_input_mouse_up_00697af0\",\n  \"observed_mechanics\": [\n    \"{\\\"button_index\\\": \\\"The live indexed write is receiver+button-0x3c4; the fourth stack argument is ignored.\\\", \\\"callback_order\\\": \\\"No callback is made by this function.\\\", \\\"sentinel\\\": \\\"The active button is cleared only on equality; an unrelated active button remains unchanged.\\\"}\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-GAME-INPUT-WAVE7\"\n    ],\n    \"manifest\": {\n      \"recor
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
  "body_end": "00697b1d",
  "body_span_bytes": 46,
  "body_start": "00697af0",
  "callees": [],
  "callers": [
    "FUN_00f4f630",
    "App::cCellModeStrategy::OnMouseUp"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00697af0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "GameInput_MouseUp",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x297af0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined GameInput_MouseUp(void)",
  "size_bytes": 46,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00697af0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 9,
  "xrefs": [
    {
      "from": "005a21e5"
    },
    {
      "from": "00b0f202"
    },
    {
      "from": "00cd4244"
    },
    {
      "from": "00cf7441"
    },
    {
      "from": "00d20522"
    },
    {
      "from": "00ef075f"
    },
    {
      "from": "00f4f78a"
    },
    {
      "from": "00fd9f98"
    },
    {
      "from": "00e5c115"
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
  "file": "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-input-wave7/00697af0.json"
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
    "Observe valid button values, receiver storage extent, and active-button identity in the original input owner."
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
  "MouseState",
  "OpaqueGameInput",
  "float",
  "int32",
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
