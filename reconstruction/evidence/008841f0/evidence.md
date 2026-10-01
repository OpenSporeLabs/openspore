# Evidence 0x008841f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `67dbf795e261cd51cb2c73848247bdd2d454a50ad1c2c8411340d14147dc66e8`

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
      "EBX",
      "EDI",
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
  "content_sha256": "db853fa95a2b67edaa96c6effd4f5cec45ee00c165c3ec9ba1f560fd14b0d952",
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
    "ghidra_parameter_count": 4,
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
        "obs-0019"
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
        "obs-0002",
        "obs-0003",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          8,
          16,
          20,
          24,
          36
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0006",
        "obs-0019"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0019"
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
        "obs-0019"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0019"
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
      "at": "0x008841f0",
      "count": 10,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x008841f1",
      "count": 2,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x008841f1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x008841f3",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x008841f6",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ESI + 0x10]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x008841f9",
      "definite": true,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x14]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x008841fc",
      "count": 3,
      "first_use": 5,
      "first_write_index": 6,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x008841fd",
      "definite": true,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESI + 0x18]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00884211",
      "count": 1,
      "first_use": 14,
      "first_write_index": 3,
      "id": "obs-0009",
      "index": 14,
      "kind": "REG_READ",
      "raw": "LEA EDX,[EAX + 0xc0]",
      "reg": "EDX"
    },
    {
      "at": "0x00884211",
      "count": 2,
      "first_use": 14,
      "first_write_index": 2,
      "id": "obs-0010",
      "index": 14,
      "kind": "REG_READ",
      "raw": "LEA EDX,[EAX + 0xc0]",
      "reg": "EAX"
    },
    {
      "at": "0x00884223",
      "count": 1,
      "first_use": 20,
      "first_write_index": 21,
      "id": "obs-0011",
      "index": 20,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00884224",
      "definite": true,
      "id": "obs-0012",
      "index": 21,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESI + 0x24]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00884237",
      "id": "obs-0013",
      "index": 30,
      "kind":
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
    "va": "0x00884fb0"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70"
    ],
    "conflict_id": "Q-DISPATCH-ORDER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70"
    ],
    "conflict_id": "Q-QUEUE-LAYOUT",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The 0x14-byte registration Entry and 0x18-byte ProcessQueue record are distinct observed sizes. Their pointer/reference relation and traversal order are not recovered.",
    "resolution_status": "The 0x14-byte registration Entry and 0x18-byte ProcessQueue record are distinct observed sizes. Their pointer/reference relation and traversal order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70"
    ],
    "conflict_id": "Q-SEND-POST-OWNERSHIP",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "MessageSend, MessagePost, and MessagePostFunction have distinct declared ownership surfaces. Queue insertion, release, lock, and immediate/deferred timing are unresolved.",
    "resolution_status": "MessageSend, MessagePost, and MessagePostFunction have distinct declared ownership surfaces. Queue insertion, release, lock, and immediate/deferred timing are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x00f47b10",
      "0x00f47b10"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:3",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
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
  "count": 45,
  "instructions": [
    {
      "address": "008841f0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "008841f1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "008841f3",
      "instruction": "MOV EAX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "008841f6",
      "instruction": "MOV EDX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "008841f9",
      "instruction": "MOV ECX,dword ptr [ESI + 0x14]"
    },
    {
      "address": "008841fc",
      "instruction": "PUSH EDI"
    },
    {
      "address": "008841fd",
      "instruction": "MOV EDI,dword ptr [ESI + 0x18]"
    },
    {
      "address": "00884200",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00884202",
      "instruction": "JZ 0x0088421b"
    },
    {
      "address": "00884204",
      "instruction": "ADD EAX,0x18"
    },
    {
      "address": "00884207",
      "instruction": "CMP EAX,EDX"
    },
    {
      "address": "00884209",
      "instruction": "JNZ 0x00884217"
    },
    {
      "address": "0088420b",
      "instruction": "MOV EAX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "0088420e",
      "instruction": "ADD ECX,0x4"
    },
    {
      "address": "00884211",
      "instruction": "LEA EDX,[EAX + 0xc0]"
    },
    {
      "address": "00884217",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00884219",
      "instruction": "JNZ 0x00884204"
    },
    {
      "address": "0088421b",
      "instruction": "CMP dword ptr [ESI],0x0"
    },
    {
      "address": "0088421e",
      "instruction": "JZ 0x00884256"
    },
    {
      "address": "00884220",
      "instruction": "MOV EDI,dword ptr [ESI + 0x14]"
    },
    {
      "address": "00884223",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00884224",
      "instruction": "MOV EBX,dword ptr [ESI + 0x24]"
    },
    {
      "address": "00884227",
      "instruction": "ADD EBX,0x4"
    },
    {
      "address": "0088422a",
      "instruction": "CMP EDI,EBX"
    },
    {
      "address": "0088422c",
      "instruction": "JNC 0x00884246"
    },
    {
      "address": "0088422e",
      "instruction": "MOV EDI,EDI"
    },
    {
      "address": "00884230",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00884232",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00884234",
      "instruction": "JZ 0x0088423f"
    },
    {
      "address": "00884236",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00884237",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "0088423c",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0088423f",
      "instruction": "ADD EDI,0x4"
    },
    {
      "address": "00884242",
      "instruction": "CMP EDI,EBX"
    },
    {
      "address": "00884244",
      "instruction": "JC 0x00884230"
    },
    {
      "address": "00884246",
      "instruction": "MOV ESI,dword ptr [ESI]"
    },
    {
      "address": "00884248",
      "instruction": "POP EBX"
    },
    {
      "address": "00884249",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "0088424b",
      "instruction": "JZ 0x00884256"
    },
    {
      "address": "0088424d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0088424e",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "00884253",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00884256",
      "instruction": "POP EDI"
    },
    {
      "address": "00884257",
      "instruction": "POP ESI"
    },
    {
      "address": "00884258",
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
        "same_package"
      ],
      "package": "PKG-06-WAVE6-APP-MANAGERS",
      "score": 8,
      "symbol": "App_IStateManager_Get_0067dce0",
      "va": "0x0067dce0"
    },
    {
      "match_basis": [
        "same_package"
      ],
      "package": "PKG-06-WAVE6-APP-MANAGERS",
      "score": 8,
      "symbol": "App_IPropManager_Get_0067ddf0",
      "va": "0x0067ddf0"
    },
    {
      "match_basis": [
        "shared_types:OpaqueMessageManager"
      ],
      "package": "PKG-WAVE6-MISC-ENGINE",
      "score": 3,
      "symbol": "message_manager_get_queue_0098f4d0",
      "va": "0x0098f4d0"
    }
  ],
  "audit_evidence_boundary": "The interior receiver, block walk, pointer-array release order, final root reread, and release-port guards are exact; queue, block, and root ownership remain unresolved.",
  "audit_findings": [],
  "audit_status": "pass_after_repair",
  "blocked": false,
  "blockers": [],
  "body_status": "integrated",
  "class_type": "OpaqueMessageCleanupWindow",
  "cluster": null,
  "confidence": 0.91,
  "dependencies": {
    "callees": [],
    "callees_truncated": false,
    "callers": [
      {
        "name": null,
        "reconstructed": false,
        "va": "0x00884fb0"
      }
    ],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x00885002",
        "direction": "in",
        "other": "0x00884fb0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00884237",
        "direction": "out",
        "other": "0x00f47380",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x0088424e",
        "direction": "out",
        "other": "0x00f47380",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 1,
    "fan_out": 0,
    "manifest_callees": [
      "0x00f47380"
    ],
    "manifest_callers": [
      "0x00884fb0"
    ],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0270",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "OBSERVED",
  "globals": [],
  "integration_status": "integrated",
  "name": "MessageManagerCleanupStorageWalker_008841f0",
  "normalized_symbol": "MessageManagerCleanupStorageWalker_008841f0",
  "observed_mechanics": [
    "ECX points to cMessageManager+0x08",
    "walk 0x18-stride records to end",
    "follow +0x18-limit link with next limit +0xc0",
    "release non-null array items through 0x00f47380",
    "reread root storage after the array loop",
    "release non-null root storage",
    "plain RET"
  ],
  "ownership": {
    "claimability": "do_not_claim",
    "handoff_packages": [
      "PKG-06-WAVE6-APP-MANAGERS"
    ],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "queue_state": null
  },
  "package": "PKG-06-WAVE6-APP-MANAGERS",
  "reconstructed": true,
  "review_status": "approved",
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-message-cleanup-storage-and-release-lifecycle"
    ],
    "validated": 0
  },
  "runtime_gated": true,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": "static_message_cleanup_storage_walk_and_release_order_runtime_ownership_unknown",
  "services": [],
  "source": {
    "decomp": null,
    "file": "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp",
    "files": [
      "reconstruction/staging/wave6-app-managers/service_accessors_cleanup_model_test.cpp",
      "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp"
    ],
    "handoffs": [
      "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
    ],
    "metadata": [
      "reconstruction/metadata/wave6-app-managers/008841f0.json"
    ],
    "provenance": [
      "reconstruction/metadata/wave6-app-managers/008841f0.json"
    ]
  },
  "status": "reconstructed",
  "subsystem": "App.MessageCleanup",
  "triage": null,
  "types": [
    "OpaqueMessageCleanupPorts",
    "OpaqueMessageCleanupWindow",
    "OpaqueMessageManager",
    "void-like; target does not define EAX"
  ],
  "unresolved_questions": [
    "0x18-stride record owner",
    "Can malformed cursor, link, or end pointers reach the same path through SEH?",
    "What are the meanings of the four-byte words in the cMessageManager+0x08 cleanup window?",
    "What concrete queue or block object owns the 0x18-stride records and the +0xc0 next-block limit?",
    "What concrete root, storage, or allocator owns the opaque pointer released after the array loop?",
    "What runtime teardown ordering reaches this walker from the cMessageManager owner?",
    "pointer-array and root storage identity",
    "release callback semantics",
    "teardown reachability"
  ],
  "va": "0x008841f0",
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
  "body_end": "00884258",
  "body_span_bytes": 105,
  "body_start": "008841f0",
  "callees": [
    "FUN_00f47380"
  ],
  "callers": [
    "FUN_00884fb0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "008841f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cMessageManager::ProcessQueue",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 4,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cMessageManager *"
    },
    {
      "name": "param_2",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "param_3",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "int"
    },
    {
      "name": "param_4",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "int"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "int",
  "return_type_resolved": true,
  "rva": "0x4841f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "int App::cMessageManager::ProcessQueue(cMessageManager * this, int param_2, int param_3, int param_4)",
  "size_bytes": 105,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x008841f0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00885002"
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
  "file": "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp",
  "files": [
    "reconstruction/staging/wave6-app-managers/service_accessors_cleanup_model_test.cpp",
    "src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/wave6-app-managers/008841f0.json"
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
    "gate-message-cleanup-storage-and-release-lifecycle"
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
  "OpaqueMessageCleanupPorts",
  "OpaqueMessageCleanupWindow",
  "OpaqueMessageManager",
  "void-like; target does not define EAX"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70"
    ],
    "conflict_id": "Q-DISPATCH-ORDER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70"
    ],
    "conflict_id": "Q-QUEUE-LAYOUT",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The 0x14-byte registration Entry and 0x18-byte ProcessQueue record are distinct observed sizes. Their pointer/reference relation and traversal order are not recovered.",
    "resolution_status": "The 0x14-byte registration Entry and 0x18-byte ProcessQueue record are distinct observed sizes. Their pointer/reference relation and traversal order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70"
    ],
    "conflict_id": "Q-SEND-POST-OWNERSHIP",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "MessageSend, MessagePost, and MessagePostFunction have distinct declared ownership surfaces. Queue insertion, release, lock, and immediate/deferred timing are unresolved.",
    "resolution_status": "MessageSend, MessagePost, and MessagePostFunction have distinct declared ownership surfaces. Queue insertion, release, lock, and immediate/deferred timing are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x00f47b10",
      "0x00f47b10"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:3",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
