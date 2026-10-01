# Evidence 0x00596e10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `aecc6a5fc29a5ec5abf1f9120451ff595e14ea8414330e03276989f2e2fb0814`

## abi

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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "0e31aae8533d86531cbea8da387100e4a1eb10f3ef6acb0a3ce6098c16d0fe0a",
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
        "obs-0012"
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
        "obs-0012"
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
        "obs-0012"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0012"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00596e10",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00596e11",
      "count": 5,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00596e11",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00596e13",
      "count": 3,
      "first_use": 2,
      "first_write_index": 11,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP + 0x8]",
      "reg": "EAX"
    },
    {
      "at": "0x00596e13",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00596e13",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0006",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA EAX,[ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00596e1e",
      "id": "obs-0007",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00595eb0",
      "target": "0x00595eb0"
    },
    {
      "at": "0x00596e26",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0008",
      "index": 7,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA ECX,[ESP + 0x8]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x00596e31",
      "id": "obs-0009",
      "index": 10,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x005945b0",
      "target": "0x005945b0"
    },
    {
      "at": "0x00596e36",
      "definite": tr
[TRUNCATED]
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "0e31aae8533d86531cbea8da387100e4a1eb10f3ef6acb0a3ce6098c16d0fe0a",
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
        "obs-0012"
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
        "obs-0012"
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
        "obs-0012"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0012"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00596e10",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00596e11",
      "count": 5,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00596e11",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00596e13",
      "count": 3,
      "first_use": 2,
      "first_write_index": 11,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP + 0x8]",
      "reg": "EAX"
    },
    {
      "at": "0x00596e13",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00596e13",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0006",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA EAX,[ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00596e1e",
      "id": "obs-0007",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00595eb0",
      "target": "0x00595eb0"
    },
    {
      "at": "0x00596e26",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0008",
      "index": 7,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA ECX,[ESP + 0x8]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x00596e31",
      "id": "obs-0009",
      "index": 10,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x005945b0",
      "target": "0x005945b0"
    },
    {
      "at": "0x00596e36",
      "definite": tr
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
    "va": "0x005ef470"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d0e170"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e4fac0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f12fc0"
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
      "0x010535e0",
      "0x010535e0",
      "0x005942e0",
      "0x005942e0",
      "0x00596da0",
      "0x00596da0",
      "0x00596e10",
      "0x00596e10",
      "0x005973a0",
      "0x005973a0",
      "0x00598db0",
      "0x00598db0",
      "0x00598e90",
      "0x00598e90",
      "0x00be2590",
      "0x00be2590"
    ],
    "conflict_id": "U-E007",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
    "resolution_status": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x010535e0",
      "0x010535e0",
      "0x005942e0",
      "0x005942e0",
      "0x00596da0",
      "0x00596da0",
      "0x00596e10",
      "0x00596e10",
      "0x005973a0",
      "0x005973a0",
      "0x00598db0",
      "0x00598db0",
      "0x00598e90",
      "0x00598e90",
      "0x00be2590",
      "0x00be2590"
    ],
    "conflict_id": "U-E008",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00596da0",
      "0x00596da0",
      "0x0103ac40",
      "0x0103ac40",
      "0x0103fba0",
      "0x0103fba0",
      "0x0103fc10",
      "0x0103fc10",
      "0x005942e0",
      "0x005942e0",
      "0x00596da0",
      "0x00596da0",
      "0x00596e10",
      "0x00596e10",
      "0x005973a0",
      "0x005973a0"
    ],
    "conflict_id": "U-E013",
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
  "count": 14,
  "instructions": [
    {
      "address": "00596e10",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00596e11",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00596e13",
      "instruction": "LEA EAX,[ESP + 0x8]"
    },
    {
      "address": "00596e17",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00596e18",
      "instruction": "LEA ECX,[ESI + 0x4d00]"
    },
    {
      "address": "00596e1e",
      "instruction": "CALL 0x00595eb0"
    },
    {
      "address": "00596e23",
      "instruction": "AND byte ptr [EAX],0xfc"
    },
    {
      "address": "00596e26",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "00596e2a",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00596e2b",
      "instruction": "LEA ECX,[ESI + 0x6d80]"
    },
    {
      "address": "00596e31",
      "instruction": "CALL 0x005945b0"
    },
    {
      "address": "00596e36",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00596e38",
      "instruction": "POP ESI"
    },
    {
      "address": "00596e39",
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
  "abi": {},
  "analogues": [
    {
      "match_basis": [
        "same_package"
      ],
      "package": "PKG-11-A4-PROGRESSION-WAVE3",
      "score": 8,
      "symbol": "collectable_unlock_00596da0",
      "va": "0x00596da0"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [
    "Container node allocation, hash layout, and the concrete list/status map implementations remain opaque ports.",
    "Editor visibility synchronization is outside this target and remains with its callers.",
    "No original-process collectable lock trace was run."
  ],
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
        "va": "0x005ef470"
      },
      {
        "name": null,
        "reconstructed": false,
        "va": "0x00d0e170"
      },
      {
        "name": null,
        "reconstructed": false,
        "va": "0x00e4fac0"
      },
      {
        "name": null,
        "reconstructed": false,
        "va": "0x00f12fc0"
      }
    ],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x005ef4f8",
        "direction": "in",
        "other": "0x005ef470",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00d0ec2c",
        "direction": "in",
        "other": "0x00d0e170",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00d0edca",
        "direction": "in",
        "other": "0x00d0e170",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00d0ef2a",
        "direction": "in",
        "other": "0x00d0e170",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00d0f1db",
        "direction": "in",
        "other": "0x00d0e170",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00e4fb4a",
        "direction": "in",
        "other": "0x00e4fac0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00f13046",
        "direction": "in",
        "other": "0x00f12fc0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00596e31",
        "direction": "out",
        "other": "0x005945b0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00596e1e",
        "direction": "out",
        "other": "0x00595eb0",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 4,
    "fan_out": 0,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0085",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": null,
  "globals": [],
  "integration_status": "integrated",
  "name": "collectable_lock_00596e10",
  "normalized_symbol": "collectable_lock_00596e10",
  "observed_mechanics": [],
  "ownership": {
    "claimability": "do_not_claim",
    "handoff_packages": [
      "PKG-11-A4-PROGRESSION-WAVE3"
    ],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": "PKG-11-A4-PROGRESSION-WAVE3",
    "queue_state": null
  },
  "package": "PKG-11-A4-PROGRESSION-WAVE3",
  "reconstructed": true,
  "review_status": "approved_after_reviewed_repairs",
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "runtime validation not run"
    ],
    "validated": 0
  },
  "runtime_gated": true,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": null,
  "services": [],
  "source": {
    "decomp": null,
    "file": null,
    "files": [
      "reconstruction/staging/pkg11-a4-progression-wave3/progression_wave3.cpp",
      "reconstruction/staging/pkg11-a4-progression-wave3/progression_wave3.hpp",
      "src/reconstruction/pkg11_a4_progression_wave3/progression_wave3.cpp",
      "src/reconstruction/pkg11_a4_progression_wave3/progression_wave3.hpp",
      "src/reconstruction/pkg11_a4_progression_wave3/progression_wave3_model_test.cpp"
    ],
    "handoffs": [
      "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
    ],
    "metadata": [
      "reconstruction/metadata/pkg11-a4-progression-wave3/00596e10.json"
    ],
    "provenance": [
      "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json",
      "reconstruction/metadata/pkg11-a4-progression-wave3/00596da0.json",
      "reconstruction/metadata/pkg11-a4-progression-wave3/00596e10.json"
    ]
  },
  "status": "reconstructed",
  "subsystem": null,
  "triage": null,
  "types": [
    "std::int32_t",
    "std::uint32_t"
  ],
  "unresolved_questions": [],
  "va": "0x00596e10",
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
  "body_end": "00596e3b",
  "body_span_bytes": 44,
  "body_start": "00596e10",
  "callees": [
    "FUN_00595eb0",
    "FUN_005945b0"
  ],
  "callers": [
    "FUN_00d0e170",
    "FUN_00f12fc0",
    "FUN_00e4fac0",
    "FUN_005ef470"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00596e10",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00596e10",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x196e10",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00596e10(void)",
  "size_bytes": 44,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00596e10",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "005ef4f8"
    },
    {
      "from": "00d0ec2c"
    },
    {
      "from": "00d0edca"
    },
    {
      "from": "00d0ef2a"
    },
    {
      "from": "00d0f1db"
    },
    {
      "from": "00e4fb4a"
    },
    {
      "from": "00f13046"
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
    "reconstruction/staging/pkg11-a4-progression-wave3/progression_wave3.cpp",
    "reconstruction/staging/pkg11-a4-progression-wave3/progression_wave3.hpp",
    "src/reconstruction/pkg11_a4_progression_wave3/progression_wave3.cpp",
    "src/reconstruction/pkg11_a4_progression_wave3/progression_wave3.hpp",
    "src/reconstruction/pkg11_a4_progression_wave3/progression_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-a4-progression-wave3/00596e10.json"
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
    "runtime validation not run"
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
  "std::int32_t",
  "std::uint32_t"
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
      "0x010535e0",
      "0x010535e0",
      "0x005942e0",
      "0x005942e0",
      "0x00596da0",
      "0x00596da0",
      "0x00596e10",
      "0x00596e10",
      "0x005973a0",
      "0x005973a0",
      "0x00598db0",
      "0x00598db0",
      "0x00598e90",
      "0x00598e90",
      "0x00be2590",
      "0x00be2590"
    ],
    "conflict_id": "U-E007",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
    "resolution_status": "The resource seam and cited call boundary are retained, but original ownership, priority, cache, failure, and load-order semantics are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x010535e0",
      "0x010535e0",
      "0x005942e0",
      "0x005942e0",
      "0x00596da0",
      "0x00596da0",
      "0x00596e10",
      "0x00596e10",
      "0x005973a0",
      "0x005973a0",
      "0x00598db0",
      "0x00598db0",
      "0x00598e90",
      "0x00598e90",
      "0x00be2590",
      "0x00be2590"
    ],
    "conflict_id": "U-E008",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00596da0",
      "0x00596da0",
      "0x0103ac40",
      "0x0103ac40",
      "0x0103fba0",
      "0x0103fba0",
      "0x0103fc10",
      "0x0103fc10",
      "0x005942e0",
      "0x005942e0",
      "0x00596da0",
      "0x00596da0",
      "0x00596e10",
      "0x00596e10",
      "0x005973a0",
      "0x005973a0"
    ],
    "conflict_id": "U-E013",
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
