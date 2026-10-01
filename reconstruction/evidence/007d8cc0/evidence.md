# Evidence 0x007d8cc0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e2c4ec3898e764115b8d9befba99ee8632d75569caea65dd379a077c0c353d03`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "ordinary_stack_argument_slots": 0,
  "return_register": "EAX is not assigned a defined result by the target body",
  "stack_cleanup_bytes": 0
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
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "b84b647cea02833ede5d21d2ed5572b83e7a1327bda219b2eaf20babe13d14be",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": null
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
        "obs-0015",
        "obs-0017"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          4
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0004",
        "obs-0017"
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
        "obs-0015",
        "obs-0017",
        "obs-0018"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
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
      "at": "0x007d8cc7",
      "id": "obs-0001",
      "index": 2,
      "kind": "SEGMENT_TLS",
      "raw": "MOV EAX,FS:[0x0]",
      "segment": "FS",
      "text": "FS:[0x0]"
    },
    {
      "at": "0x007d8cc7",
      "definite": true,
      "id": "obs-0002",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,FS:[0x0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007d8ccd",
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
      "at": "0x007d8cce",
      "id": "obs-0004",
      "index": 4,
      "kind": "SEGMENT_TLS",
      "raw": "MOV dword ptr FS:[0x0],ESP",
      "segment": "FS",
      "text": "dword ptr FS:[0x0]"
    },
    {
      "at": "0x007d8cce",
      "count": 4,
      "first_use": 4,
      "first_write_index": 23,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV dword ptr FS:[0x0],ESP",
      "reg": "ESP"
    },
    {
      "at": "0x007d8cd5",
      "count": 4,
      "first_use": 5,
      "first_write_index": 10,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x007d8cd6",
      "count": 8,
      "first_use": 6,
      "first_write_index": 7,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x007d8cd7",
      "definite": true,
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x007d8cd9",
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
      "at": "0x007d8ce0",
      "definite": true,
      "id": "obs-0010",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007d8ce6",
      "base": "ESP",
      "disp": 24,
      "id": "obs-0011",
      "index": 14,
      "key": null,
      "kind": "ST
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
    "va": "0x007d8d40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0121601e"
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
  "count": 29,
  "instructions": [
    {
      "address": "007d8cc0",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "007d8cc2",
      "instruction": "PUSH 0x120f188"
    },
    {
      "address": "007d8cc7",
      "instruction": "MOV EAX,FS:[0x0]"
    },
    {
      "address": "007d8ccd",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007d8cce",
      "instruction": "MOV dword ptr FS:[0x0],ESP"
    },
    {
      "address": "007d8cd5",
      "instruction": "PUSH ECX"
    },
    {
      "address": "007d8cd6",
      "instruction": "PUSH ESI"
    },
    {
      "address": "007d8cd7",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "007d8cd9",
      "instruction": "MOV dword ptr [ESP + 0x4],ESI"
    },
    {
      "address": "007d8cdd",
      "instruction": "MOV EAX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "007d8ce0",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "007d8ce2",
      "instruction": "PUSH EAX"
    },
    {
      "address": "007d8ce3",
      "instruction": "PUSH ECX"
    },
    {
      "address": "007d8ce4",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "007d8ce6",
      "instruction": "MOV dword ptr [ESP + 0x18],0x0"
    },
    {
      "address": "007d8cee",
      "instruction": "CALL 0x007d87e0"
    },
    {
      "address": "007d8cf3",
      "instruction": "MOV ESI,dword ptr [ESI]"
    },
    {
      "address": "007d8cf5",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "007d8cf7",
      "instruction": "JZ 0x007d8d08"
    },
    {
      "address": "007d8cf9",
      "instruction": "CMP dword ptr [ESI + -0x4],0x0"
    },
    {
      "address": "007d8cfd",
      "instruction": "JZ 0x007d8d08"
    },
    {
      "address": "007d8cff",
      "instruction": "PUSH ESI"
    },
    {
      "address": "007d8d00",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "007d8d05",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "007d8d08",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "007d8d0c",
      "instruction": "POP ESI"
    },
    {
      "address": "007d8d0d",
      "instruction": "MOV dword ptr FS:[0x0],ECX"
    },
    {
      "address": "007d8d14",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "007d8d17",
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
    "ordinary_stack_argument_slots": 0,
    "return_register": "EAX is not assigned a defined result by the target body",
    "stack_cleanup_bytes": 0
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
    "callees": [],
    "callees_truncated": false,
    "callers": [
      {
        "name": null,
        "reconstructed": false,
        "va": "0x007d8d40"
      },
      {
        "name": null,
        "reconstructed": false,
        "va": "0x0121601e"
      }
    ],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x007d8d8f",
        "direction": "in",
        "other": "0x007d8d40",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x01216024",
        "direction": "in",
        "other": "0x0121601e",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007d8cee",
        "direction": "out",
        "other": "0x007d87e0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007d8d00",
        "direction": "out",
        "other": "0x00f47380",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 2,
    "fan_out": 0,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0246",
      "size": 1
    },
    "vtable_reference_count": 0
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
      "reconstruction/metadata/wave6-app-managers/007d8cc0.json"
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
    "Can the SEH path be reached for malformed vector ranges or invalid owner vtables?",
    "What are the complete side effects of the allocator boundary at 0x00f47380?",
    "What concrete mode-entry owner and vtable are stored at each entry +0x00?",
    "What do payload begin/end at +0x08/+0x10 represent, and why is the release condition greater than one byte?",
    "What does the allocation marker immediately before vector begin represent?"
  ],
  "va": "0x007d8cc0",
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
  "body_end": "007d8d17",
  "body_span_bytes": 88,
  "body_start": "007d8cc0",
  "callees": [
    "FUN_00f47380",
    "FUN_007d87e0"
  ],
  "callers": [
    "App::cGameModeManager::SetActiveModeAt",
    "Unwind@0121601e"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "007d8cc0",
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
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_007d8cc0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3d8cc0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_007d8cc0(void)",
  "size_bytes": 88,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007d8cc0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "01216024"
    },
    {
      "from": "007d8d8f"
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
    "reconstruction/metadata/wave6-app-managers/007d8cc0.json"
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
[]
```
