# Evidence 0x007d8d40

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `39948410cf91340d524bf280a216f1d6269dd05874a33f7d5400716a704ae3ae`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "ordinary_stack_argument_slots": 1,
  "return_register": "EAX is not assigned a defined result by the target body"
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "a3e87a5fa6041ac9bdc8042a525dc883939176c3fbf47607ade0410a990405c1",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0021"
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
        "obs-0006",
        "obs-0008",
        "obs-0010",
        "obs-0017",
        "obs-0019"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          4,
          8,
          44
        ],
        "register": "ECX",
        "written_through": 6
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0004",
        "obs-0019"
      ],
      "claim": "an FS:/GS: operand is an SEH or cookie frame, which is not variadic evidence",
      "confidence": "OBSERVED",
      "id": "V2",
      "value": {
        "seh_or_cookie_frame": true
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0008",
        "obs-0010",
        "obs-0017",
        "obs-0019",
        "obs-0021"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0021"
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
        "obs-0021"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0021"
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
      "at": "0x007d8d47",
      "id": "obs-0001",
      "index": 2,
      "kind": "SEGMENT_TLS",
      "raw": "MOV EAX,FS:[0x0]",
      "segment": "FS",
      "text": "FS:[0x0]"
    },
    {
      "at": "0x007d8d47",
      "definite": true,
      "id": "obs-0002",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,FS:[0x0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007d8d4d",
      "count": 2,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x007d8d4e",
      "id": "obs-0004",
      "index": 4,
      "kind": "SEGMENT_TLS",
      "raw": "MOV dword ptr FS:[0x0],ESP",
      "segment": "FS",
      "text": "dword ptr FS:[0x0]"
    },
    {
      "at": "0x007d8d4e",
      "count": 5,
      "first_use": 4,
      "first_write_index": 28,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV dword ptr FS:[0x0],ESP",
      "reg": "ESP"
    },
    {
      "at": "0x007d8d55",
      "count": 5,
      "first_use": 5,
      "first_write_index": 12,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x007d8d56",
      "count": 10,
      "first_use": 6,
      "first_write_index": 7,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x007d8d57",
      "definite": true,
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x007d8d59",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0009",
      "index": 8,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP + 0x4],ESI",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x007d8d71",
      "definite": true,
      "id": "obs-0010",
      "index": 12,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x2c]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007d8d74",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0011",
      "index": 13,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP + 0x1
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
    "va": "0x007d8cc0"
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
    "va": "0x007d8e20"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 9739,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x007d8060\",\n      \"0x007d8060\",\n      \"0x007d8360\",\n      \"0x007d8360\",\n      \"0x007d85b0\",\n      \"0x007d85b0\",\n      \"0x007d8c30\",\n      \"0x007d8c30\",\n      \"0x007d8c80\",\n      \"0x007d8c80\",\n      \"0x007d8d40\"\n    ],\n    \"conflict_id\": \"Q-INPUT-ROUTING\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n    \"resolution_status\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00d2e380\",\n      \"0x00d2e480\",\n      \"0x00d2e8a0\",\n      \"0x00d39360\",\n      \"0x045ab96e\",\n      \"0x00d2e480\",\n      \"0x00aebe90\",\n      \"0x045ab96e\",\n      \"0x0067dcd0\",\n      \"0x0067dcd0\",\n      \"0x007d8420\",\n      \"0x007d8420\",\n      \"0x007d8cf0\",\n      \"0x007d8cf0\",\n      \"0x007d8d40\",\n      \"0x007d8d40\"\n    ],\n    \"conflict_id\": \"U-005-evolution-level-promotion\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.\",\n    \"resolution_status\": \"0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x007d85b0\",\n      \"0x007d8d40\",\n      \"0x01412598\",\n      \"0x01412598\",\n      \"0x007d8c80\",\n      \"0x007d8d40\",\n      \"0x007d85b0\",\n      \"0x007d8d40\",\n      \"0x01412598\",\n      \"0x007d8c80\",\n      \"0x007c61a0\",\n      \"0x007c61a0\",\n      \"0x007c64c0\",\n      \"0x007c64c0\",\n      \"0x007c6750\",\n      \"0x007c6750\"\n    ],\n    \"conflict_id\": \"app_mode_setter_boundary\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00bb4ba0\",\n      \"0x00bb4ba0\",\n      \"0x013c7d90\",\n      \"0x013c7d90\",\n      \"0x00693900\",\n      \"0x00693900\",\n      \"0x00693d60\",\n      \"0x00693d60\",\n      \"0x007d8d40\",\n      \"0x007d8d40\",\n      \"0x00b28ec0\",\n      \"0x00b28ec0\",\n      \"0x00b294c0\",\n      \"0x00b294c0\",\n      \"0x00b335d0\",\n      \"0x00b335d0\"\n    ],\n    \"conflict_id\": \"field_coverage_and_migration\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.\",\n    \"resolution_status\": \"The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00ca6630\",\n      \"0x00ca6630\",\n      \"0x00ca6630\",\n      \"0x00ca6630\",\n      \"0x00ca6630\",\n      \"0x00c38b10\",\n      \"0x006928c0\",\n      \"0x00693de0\",\n      \"0x007d8d40\"\n    ],\n    \"conflict_id\": \"fleet_aggregate\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x007d85b0\",\n      \"0x007d8c80\",\n      \"0x007d8cf0\",\n      \"0x007d8d40\",\n      \"0x01412598\",\n      \"0x01412598\",\n      \"0x007d8c80\",\n      \"0x007d8c80\",\n      \"0x007d85b0\",\n      \"0x0212d3e7\",\n      \"0x022d1adc\",\n      \"0x00582fe0\",\n      \"0x00582fe0\",\n      \"0x00587270\",\n      \"0x00587270\",\n      \"0x0058be50\"\n    ],\n    \"conflict_id\": \"game_mode_transition_branches\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.\",\n    \"resolution_status\": \"The cited producer, consumer, or registration surface is re
[TRUNCATED]
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
  "count": 30,
  "instructions": [
    {
      "address": "007d8d40",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "007d8d42",
      "instruction": "PUSH 0x1216029"
    },
    {
      "address": "007d8d47",
      "instruction": "MOV EAX,FS:[0x0]"
    },
    {
      "address": "007d8d4d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007d8d4e",
      "instruction": "MOV dword ptr FS:[0x0],ESP"
    },
    {
      "address": "007d8d55",
      "instruction": "PUSH ECX"
    },
    {
      "address": "007d8d56",
      "instruction": "PUSH ESI"
    },
    {
      "address": "007d8d57",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "007d8d59",
      "instruction": "MOV dword ptr [ESP + 0x4],ESI"
    },
    {
      "address": "007d8d5d",
      "instruction": "MOV dword ptr [ESI],0x1412598"
    },
    {
      "address": "007d8d63",
      "instruction": "MOV dword ptr [ESI + 0x4],0x1412584"
    },
    {
      "address": "007d8d6a",
      "instruction": "MOV dword ptr [ESI + 0x8],0x1412580"
    },
    {
      "address": "007d8d71",
      "instruction": "MOV ECX,dword ptr [ESI + 0x2c]"
    },
    {
      "address": "007d8d74",
      "instruction": "MOV dword ptr [ESP + 0x10],0x3"
    },
    {
      "address": "007d8d7c",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "007d8d7e",
      "instruction": "JZ 0x007d8d87"
    },
    {
      "address": "007d8d80",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "007d8d82",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "007d8d85",
      "instruction": "CALL EDX"
    },
    {
      "address": "007d8d87",
      "instruction": "LEA ECX,[ESI + 0x14]"
    },
    {
      "address": "007d8d8a",
      "instruction": "MOV byte ptr [ESP + 0x10],0x2"
    },
    {
      "address": "007d8d8f",
      "instruction": "CALL 0x007d8cc0"
    },
    {
      "address": "007d8d94",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "007d8d98",
      "instruction": "MOV dword ptr [ESI + 0x8],0x13ef094"
    },
    {
      "address": "007d8d9f",
      "instruction": "MOV dword ptr [ESI + 0x4],0x13eb394"
    },
    {
      "address": "007d8da6",
      "instruction": "MOV dword ptr [ESI],0x13eb938"
    },
    {
      "address": "007d8dac",
      "instruction": "POP ESI"
    },
    {
      "address": "007d8dad",
      "instruction": "MOV dword ptr FS:[0x0],ECX"
    },
    {
      "address": "007d8db4",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "007d8db7",
      "instruction": "RET"
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
  "abi": {
    "architecture": "x86-32",
    "ordinary_stack_argument_slots": 1,
    "return_register": "EAX is not assigned a defined result by the target body"
  },
  "analogues": [
    {
      "match_basis": [
        "shared_types:void-like; target does not define EAX"
      ],
      "package": "PKG-06-WAVE6-APP-MANAGERS",
      "score": 3,
      "symbol": "MessageManagerCleanupStorageWalker_008841f0",
      "va": "0x008841f0"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [],
  "body_status": null,
  "class_type": null,
  "cluster": null,
  "confidence": null,
  "dependencies": {
    "callees": [
      {
        "name": null,
        "reconstructed": false,
        "va": "0x007d8cc0"
      }
    ],
    "callees_truncated": false,
    "callers": [
      {
        "name": null,
        "reconstructed": false,
        "va": "0x007d8e20"
      }
    ],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x007d8e23",
        "direction": "in",
        "other": "0x007d8e20",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007d8d8f",
        "direction": "out",
        "other": "0x007d8cc0",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 1,
    "fan_out": 1,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0247",
      "size": 1
    },
    "vtable_reference_count": 6
  },
  "evidence_level": null,
  "globals": [],
  "integration_status": null,
  "name": null,
  "normalized_symbol": null,
  "observed_mechanics": [],
  "ownership": {
    "claimability": "queue_candidate",
    "handoff_packages": [],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": null,
    "queue_state": null
  },
  "package": null,
  "reconstructed": false,
  "review_status": null,
  "runtime": {
    "blocking_reason": null,
    "gates": [],
    "validated": 0
  },
  "runtime_gated": false,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": null,
  "services": [],
  "source": {
    "decomp": null,
    "file": null,
    "files": [
      "reconstruction/staging/wave6-app-managers/app_managers_model_test.cpp"
    ],
    "handoffs": [],
    "metadata": [
      "reconstruction/metadata/wave6-app-managers/007d8d40.json"
    ],
    "provenance": []
  },
  "status": "unresolved",
  "subsystem": null,
  "triage": null,
  "types": [
    "void-like; target does not define EAX"
  ],
  "unresolved_questions": [
    "Does the sole caller always pass a deleting flag, and what happens after the target returns?",
    "What concrete SEH exceptions can escape the helper chain?",
    "What mode-entry payload and owner vtable semantics are reached through the vector cleanup?",
    "What runtime object is stored at manager +0x2c and what does its +0x0c slot do?",
    "Which concrete vtables own the six written table addresses?"
  ],
  "va": "0x007d8d40",
  "vtables": []
}
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "007d8db7",
  "body_span_bytes": 120,
  "body_start": "007d8d40",
  "callees": [
    "FUN_007d8cc0"
  ],
  "callers": [
    "FUN_007d8e20"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "007d8d40",
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
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "App::cGameModeManager::SetActiveModeAt",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cGameModeManager *"
    },
    {
      "name": "index",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "size_t"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x3d8d40",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cGameModeManager::SetActiveModeAt(cGameModeManager * this, size_t index)",
  "size_bytes": 120,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007d8d40",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "007d8e23"
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
    "reconstruction/staging/wave6-app-managers/app_managers_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave6-app-managers/007d8d40.json"
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
  "void-like; target does not define EAX"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
{
  "original_bytes": 9739,
  "preview": "[\n  {\n    \"anchors\": [\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x00e818f0\",\n      \"0x00b3d350\",\n      \"0x007d8060\",\n      \"0x007d8060\",\n      \"0x007d8360\",\n      \"0x007d8360\",\n      \"0x007d85b0\",\n      \"0x007d85b0\",\n      \"0x007d8c30\",\n      \"0x007d8c30\",\n      \"0x007d8c80\",\n      \"0x007d8c80\",\n      \"0x007d8d40\"\n    ],\n    \"conflict_id\": \"Q-INPUT-ROUTING\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n    \"resolution_status\": \"The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00d2e380\",\n      \"0x00d2e480\",\n      \"0x00d2e8a0\",\n      \"0x00d39360\",\n      \"0x045ab96e\",\n      \"0x00d2e480\",\n      \"0x00aebe90\",\n      \"0x045ab96e\",\n      \"0x0067dcd0\",\n      \"0x0067dcd0\",\n      \"0x007d8420\",\n      \"0x007d8420\",\n      \"0x007d8cf0\",\n      \"0x007d8cf0\",\n      \"0x007d8d40\",\n      \"0x007d8d40\"\n    ],\n    \"conflict_id\": \"U-005-evolution-level-promotion\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.\",\n    \"resolution_status\": \"0x45ab96e is a concrete action/message value with a guarded dispatch, but its consumer and brain-level/ability promotion are not identified.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x007d85b0\",\n      \"0x007d8d40\",\n      \"0x01412598\",\n      \"0x01412598\",\n      \"0x007d8c80\",\n      \"0x007d8d40\",\n      \"0x007d85b0\",\n      \"0x007d8d40\",\n      \"0x01412598\",\n      \"0x007d8c80\",\n      \"0x007c61a0\",\n      \"0x007c61a0\",\n      \"0x007c64c0\",\n      \"0x007c64c0\",\n      \"0x007c6750\",\n      \"0x007c6750\"\n    ],\n    \"conflict_id\": \"app_mode_setter_boundary\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00bb4ba0\",\n      \"0x00bb4ba0\",\n      \"0x013c7d90\",\n      \"0x013c7d90\",\n      \"0x00693900\",\n      \"0x00693900\",\n      \"0x00693d60\",\n      \"0x00693d60\",\n      \"0x007d8d40\",\n      \"0x007d8d40\",\n      \"0x00b28ec0\",\n      \"0x00b28ec0\",\n      \"0x00b294c0\",\n      \"0x00b294c0\",\n      \"0x00b335d0\",\n      \"0x00b335d0\"\n    ],\n    \"conflict_id\": \"field_coverage_and_migration\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.\",\n    \"resolution_status\": \"The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.\",\n    \"source\": \"knowledgegraph/research/conflicts/track-c-state-events.json\",\n    \"subject\": null,\n    \"unresolved_reason\": \"Runtime reachability is absent or the required direct body/call path is not recovered.\"\n  },\n  {\n    \"anchors\": [\n      \"0x00ca6630\",\n      \"0x00ca6630\",\n      \"0x00ca6630\",\n      \"0x00ca6630\",\n      \"0x00ca6630\",\n      \"0x00c38b10\",\n      \"0x006928c0\",\n      \"0x00693de0\",\n      \"0x007d8d40\"\n    ],\n    \"conflict_id\": \"fleet_aggregate\",\n    \"kind\": \"conflict_ledger\",\n    \"rejected\": [],\n    \"resolution\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"resolution_status\": \"The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.\",\n    \"source\": \"k
[TRUNCATED]
```
