# Evidence 0x007e93d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5ea128365f64bf2249e155106f2060cdfd42e08fd15b4ae7e3a200cecc7aac51`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "command_line",
      "role": "first UTF-16 source scanned for receiver+0x138",
      "type": "const std::uint16_t*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "second_command_line",
      "role": "second UTF-16 source scanned for receiver+0x148; semantic identity remains unresolved",
      "type": "const std::uint16_t*",
      "width_bytes": 4
    }
  ],
  "receiver_register": "ECX",
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
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "0660aa4a6ad64c166eee30df45ba6ad2b3febc777f3c56e96cd234d22aa7ce62",
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
    "ghidra_parameter_count": 2,
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
        "obs-0018"
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
        "obs-0006"
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
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0012",
        "obs-0013"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0012",
        "obs-0013"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0018"
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
        "obs-0018"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018"
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
      "at": "0x007e93d0",
      "count": 7,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x007e93d1",
      "count": 3,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x007e93d2",
      "count": 11,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x007e93d2",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x007e93d4",
      "count": 2,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x007e93d4",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0006",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x007e93d4",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0xc]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007e93dc",
      "definite": true,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ECX",
     
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
      "0x007e67a0",
      "0x007e93d0"
    ],
    "conflict_id": "U03",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
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
  "count": 42,
  "instructions": [
    {
      "address": "007e93d0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "007e93d1",
      "instruction": "PUSH EDI"
    },
    {
      "address": "007e93d2",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "007e93d4",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "007e93d8",
      "instruction": "CMP word ptr [ECX],0x0"
    },
    {
      "address": "007e93dc",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "007e93de",
      "instruction": "JZ 0x007e93e9"
    },
    {
      "address": "007e93e0",
      "instruction": "ADD EAX,0x2"
    },
    {
      "address": "007e93e3",
      "instruction": "CMP word ptr [EAX],0x0"
    },
    {
      "address": "007e93e7",
      "instruction": "JNZ 0x007e93e0"
    },
    {
      "address": "007e93e9",
      "instruction": "SUB EAX,ECX"
    },
    {
      "address": "007e93eb",
      "instruction": "SAR EAX,0x1"
    },
    {
      "address": "007e93ed",
      "instruction": "LEA EAX,[ECX + EAX*0x2]"
    },
    {
      "address": "007e93f0",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007e93f1",
      "instruction": "LEA ESI,[EDI + 0x138]"
    },
    {
      "address": "007e93f7",
      "instruction": "PUSH ECX"
    },
    {
      "address": "007e93f8",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "007e93fa",
      "instruction": "CALL 0x00423650"
    },
    {
      "address": "007e93ff",
      "instruction": "PUSH 0x5c"
    },
    {
      "address": "007e9401",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "007e9403",
      "instruction": "CALL 0x004f6510"
    },
    {
      "address": "007e9408",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "007e940c",
      "instruction": "CMP word ptr [ECX],0x0"
    },
    {
      "address": "007e9410",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "007e9412",
      "instruction": "JZ 0x007e941d"
    },
    {
      "address": "007e9414",
      "instruction": "ADD EAX,0x2"
    },
    {
      "address": "007e9417",
      "instruction": "CMP word ptr [EAX],0x0"
    },
    {
      "address": "007e941b",
      "instruction": "JNZ 0x007e9414"
    },
    {
      "address": "007e941d",
      "instruction": "SUB EAX,ECX"
    },
    {
      "address": "007e941f",
      "instruction": "SAR EAX,0x1"
    },
    {
      "address": "007e9421",
      "instruction": "LEA EDX,[ECX + EAX*0x2]"
    },
    {
      "address": "007e9424",
      "instruction": "PUSH EDX"
    },
    {
      "address": "007e9425",
      "instruction": "LEA ESI,[EDI + 0x148]"
    },
    {
      "address": "007e942b",
      "instruction": "PUSH ECX"
    },
    {
      "address": "007e942c",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "007e942e",
      "instruction": "CALL 0x00423650"
    },
    {
      "address": "007e9433",
      "instruction": "PUSH 0x5c"
    },
    {
      "address": "007e9435",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "007e9437",
      "instruction": "CALL 0x004f6510"
    },
    {
      "address": "007e943c",
      "instruction": "POP EDI"
    },
    {
      "address": "007e943d",
      "instruction": "POP ESI"
    },
    {
      "address": "007e943e",
      "instruction": "RET 0x8"
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
  "original_bytes": 8043,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"command_line\",\n        \"role\": \"first UTF-16 source scanned for receiver+0x138\",\n        \"type\": \"const std::uint16_t*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"second_command_line\",\n        \"role\": \"second UTF-16 source scanned for receiver+0x148; semantic identity remains unresolved\",\n        \"type\": \"const std::uint16_t*\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"receiver_register\": \"ECX\",\n    \"stack_cleanup_bytes\": 8,\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"shared_types:DATA\",\n        \"shared_vtable:vtable:0x01413acc\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 17,\n      \"symbol\": \"app_system_service_gate_dispatch_007e5f30\",\n      \"va\": \"0x007e5f30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 8,\n      \"symbol\": \"app_config_manager_get_0067dcf0\",\n      \"va\": \"0x0067dcf0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-08-CELL-MODE\",\n      \"score\": 5,\n      \"symbol\": \"cell_mode_on_exit_00e7fc00\",\n      \"va\": \"0x00e7fc00\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE8\",\n      \"score\": 5,\n      \"symbol\": \"app_c_cell_mode_strategy_dispose_00e81f30\",\n      \"va\": \"0x00e81f30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 3,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005bf9d0\",\n      \"va\": \"0x005bf9d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0100\",\n      \"va\": \"0x005c0100\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0380\",\n      \"va\": \"0x005c0380\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"The two uint16 scans, source and end pointers, destination offsets, helper order, separator value, and RET 8 are exact; command-line meaning, allocation, and string ownership remain unresolved.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"pass_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueWave6PluginRegistration\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x007e93fa\",\n        \"direction\": \"out\",\n        \"other\": \"0x00423650\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007e942e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00423650\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007e9403\",\n        \"direction\": \"out\",\n        \"other\": \"0x004f6510\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x007e9437\",\n        \"direction\": \"out\",\n        \"other\": \"0x004f6510\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x00423650\",\n      \"0x004f6510\"\n    ],\n    \"manifest_callers\": [\n      \"data_xref_01413aec\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0253\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::cAppSystem::InitPlugins\",\n  \"normalized_symbol\": \"app_system_initialize_plugins_007e93d0\",\n  \"observed_mechanics\": [\n    \"thiscall ECX receiver with two uint16 pointers\",\n    \"scan each source through uint16 zero\",\n    \"append span to receiver+0x138 then uint16 0x005c\",\n    \"rescan the second source\",\n    \"append span to receiver+0x148 then uint16 0x005c\",\n    \"no source-null guard\",\n    \"RET 8\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"WAVE6-ENGINE-RUNTIME\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"WAVE6-ENGINE-RUNTIME\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"WAVE6-ENGINE-RUNTIME\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-plugin-command-line-string-lifecycle\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_utf16_span_and_separator_append_order_runtime_helpers_unknown\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports
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
  "body_end": "007e9440",
  "body_span_bytes": 113,
  "body_start": "007e93d0",
  "callees": [
    "FUN_00423650",
    "FUN_004f6510"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "007e93d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cAppSystem::InitPlugins",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cAppSystem *"
    },
    {
      "name": "commandLine",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "CommandLine *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x3e93d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cAppSystem::InitPlugins(cAppSystem * this, CommandLine * commandLine)",
  "size_bytes": 113,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007e93d0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01413acc"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01413aec"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cAppSystem__InitPlugins.c",
  "file": "src/reconstruction/wave6_engine_runtime/engine_runtime.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cAppSystem__InitPlugins.c",
    "reconstruction/staging/wave6-engine-runtime/engine_runtime.cpp",
    "reconstruction/staging/wave6-engine-runtime/engine_runtime.hpp",
    "reconstruction/staging/wave6-engine-runtime/engine_runtime_model_test.cpp",
    "src/reconstruction/wave6_engine_runtime/engine_runtime.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-engine-runtime/007e93d0.json"
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
    "gate-plugin-command-line-string-lifecycle"
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
  "OpaqueWave6PluginRegistration",
  "OpaqueWave6PluginRegistration*",
  "OpaqueWave6WideString",
  "Wave6WideStringPorts",
  "const std::uint16_t*"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01413acc"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x007e67a0",
      "0x007e93d0"
    ],
    "conflict_id": "U03",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
