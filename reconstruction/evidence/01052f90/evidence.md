# Evidence 0x01052f90

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `bcb2105470ab7faa3b51bc284f39190d226fd83fa43e03a3dab1295abaae89e9`

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
    "return_semantics": "pointer_like_in_EAX",
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "790ff3d46e93941b1a42232363fc95f6b15f092d0b8fb33c2a3109e986b27a86",
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
    "ghidra_parameter_count": 3,
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
        "obs-0014"
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
        "obs-0014"
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
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0012"
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
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0012"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0014"
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
        "obs-0014"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0014"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x01052f90",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0xc",
      "sub": 12
    },
    {
      "at": "0x01052f90",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0xc",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x01052f93",
      "id": "obs-0003",
      "index": 1,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d240",
      "target": "0x00b3d240"
    },
    {
      "at": "0x01052f98",
      "count": 6,
      "first_use": 2,
      "first_write_index": 14,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x01052f98",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01052f9a",
      "count": 4,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EDX + 0x3c]",
      "reg": "EDX"
    },
    {
      "at": "0x01052f9f",
      "count": 5,
      "first_use": 5,
      "first_write_index": 7,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "LEA ECX,[ESP + 0x4]",
      "reg": "ECX"
    },
    {
      "at": "0x01052f9f",
      "count": 2,
      "first_use": 5,
      "first_write_index": 0,
      "id": 
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
    "return_semantics": "pointer_like_in_EAX",
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "790ff3d46e93941b1a42232363fc95f6b15f092d0b8fb33c2a3109e986b27a86",
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
    "ghidra_parameter_count": 3,
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
        "obs-0014"
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
        "obs-0014"
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
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0012"
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
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0012"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0014"
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
        "obs-0014"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0014"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x01052f90",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0xc",
      "sub": 12
    },
    {
      "at": "0x01052f90",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0xc",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x01052f93",
      "id": "obs-0003",
      "index": 1,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d240",
      "target": "0x00b3d240"
    },
    {
      "at": "0x01052f98",
      "count": 6,
      "first_use": 2,
      "first_write_index": 14,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x01052f98",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01052f9a",
      "count": 4,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EDX + 0x3c]",
      "reg": "EDX"
    },
    {
      "at": "0x01052f9f",
      "count": 5,
      "first_use": 5,
      "first_write_index": 7,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "LEA ECX,[ESP + 0x4]",
      "reg": "ECX"
    },
    {
      "at": "0x01052f9f",
      "count": 2,
      "first_use": 5,
      "first_write_index": 0,
      "id": 
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d240",
    "reconstructed": false,
    "va": "0x00b3d240"
  }
]
```

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
  "count": 18,
  "instructions": [
    {
      "address": "01052f90",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "01052f93",
      "instruction": "CALL 0x00b3d240"
    },
    {
      "address": "01052f98",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "01052f9a",
      "instruction": "MOV EDX,dword ptr [EDX + 0x3c]"
    },
    {
      "address": "01052f9d",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "01052f9f",
      "instruction": "LEA ECX,[ESP + 0x4]"
    },
    {
      "address": "01052fa3",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01052fa4",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01052fa6",
      "instruction": "CALL EDX"
    },
    {
      "address": "01052fa8",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "01052faa",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "01052fae",
      "instruction": "MOV dword ptr [ECX],EDX"
    },
    {
      "address": "01052fb0",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01052fb3",
      "instruction": "MOV dword ptr [ECX + 0x4],EDX"
    },
    {
      "address": "01052fb6",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "01052fb9",
      "instruction": "MOV dword ptr [ECX + 0x8],EAX"
    },
    {
      "address": "01052fbc",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "01052fbf",
      "instruction": "RET 0x4"
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
        "same_subsystem"
      ],
      "package": "PKG-11-H4-HELPER-WAVE3",
      "score": 6,
      "symbol": "address_window_offset_005c65e0",
      "va": "0x005c65e0"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-SIMULATOR-SAFE-WAVE11",
      "score": 6,
      "symbol": "dispatch_key_00628450",
      "va": "0x00628450"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-SIMULATOR-SAFE-WAVE11",
      "score": 6,
      "symbol": "cycle_key_006286a0",
      "va": "0x006286a0"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-SIMULATOR-SAFE-WAVE11",
      "score": 6,
      "symbol": "release_child_0062c910",
      "va": "0x0062c910"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-01-SHARED-STATE-ROOTS",
      "score": 6,
      "symbol": "FUN_00b3d2a0",
      "va": "0x00b3d2a0"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-01-SHARED-STATE-ROOTS",
      "score": 6,
      "symbol": "FUN_00b3d300",
      "va": "0x00b3d300"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-01-SHARED-STATE-ROOTS",
      "score": 6,
      "symbol": "Simulator_GetUIMissionLogManager",
      "va": "0x00b3d4f0"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "PKG-13-E4-EMPIRE-WAVE3",
      "score": 6,
      "symbol": "EmpirePoliticalColor_00c32cd0",
      "va": "0x00c32cd0"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [],
  "body_status": null,
  "class_type": null,
  "cluster": "sim-core-systems",
  "confidence": null,
  "dependencies": {
    "callees": [
      {
        "name": "FUN_00b3d240",
        "reconstructed": false,
        "va": "0x00b3d240"
      }
    ],
    "callees_truncated": false,
    "callers": [],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x01052f93",
        "direction": "out",
        "other": "0x00b3d240",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 0,
    "fan_out": 1,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0600",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "CONFIRMED",
  "globals": [],
  "integration_status": null,
  "name": "Simulator::cDefaultAoETool::OnMouseDown",
  "normalized_symbol": "Simulator::cDefaultAoETool::OnMouseDown",
  "observed_mechanics": [],
  "ownership": {
    "claimability": "queue_candidate",
    "handoff_packages": [],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": null,
    "queue_state": "queued"
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
    "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cDefaultAoETool__OnMouseDown.c",
    "file": null,
    "files": [
      ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cDefaultAoETool__OnMouseDown.c"
    ],
    "handoffs": [],
    "metadata": [],
    "provenance": []
  },
  "status": "queued",
  "subsystem": "Simulator",
  "triage": {
    "category": "GAMEPLAY_LOGIC",
    "cluster": "sim-core-systems",
    "db_triage_status": "QUEUED",
    "decomp_path": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cDefaultAoETool__OnMouseDown.c",
    "dependencies": [
      "resource-io",
      "app-lifecycle",
      "utfwin-framework"
    ],
    "evidence": "CONFIRMED",
    "kg_node_id": "fun:01052f90",
    "name": "Simulator::cDefaultAoETool::OnMouseDown",
    "priority": "P0",
    "provenance": {
      "classifier": "triage-v4",
      "generated_at": "2026-09-23T10:12:09Z",
      "generator": "subagent-7-sequential-triage",
      "sdk_name": "Simulator::cDefaultAoETool::OnMouseDown",
      "snapshot": "2540f2ca",
      "snapshot_sha256": "2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8",
      "vtable_addrs": [
        "0149b8b4"
      ]
    },
    "queue_state": "queued",
    "rank": 19
  },
  "types": [],
  "unresolved_questions": [],
  "va": "0x01052f90",
  "vtables": [
    "vtable:0x0149b8b4"
  ]
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
  "body_end": "01052fc1",
  "body_span_bytes": 50,
  "body_start": "01052f90",
  "callees": [
    "FUN_00b3d240"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01052f90",
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
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "Simulator::cDefaultAoETool::OnMouseDown",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cDefaultAoETool *"
    },
    {
      "name": "pTool",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "cSpaceToolData *"
    },
    {
      "name": "playerPosition",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Vector3 *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0xc52f90",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Simulator::cDefaultAoETool::OnMouseDown(cDefaultAoETool * this, cSpaceToolData * pTool, Vector3 * playerPosition)",
  "size_bytes": 50,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01052f90",
  "vtables": {
    "referenced_by_vtables": [
      "0x0149b8b4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0149b8b4"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cDefaultAoETool__OnMouseDown.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cDefaultAoETool__OnMouseDown.c"
  ],
  "handoffs": [],
  "metadata": []
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
  "status": "queued"
}
```

## types

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0149b8b4"
]
```

## Conflicts

```json
[]
```
