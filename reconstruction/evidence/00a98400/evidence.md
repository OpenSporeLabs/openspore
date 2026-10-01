# Evidence 0x00a98400

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `3d06dda746d820601d36ebdf344e4a909108b992195796b1be717e08d101c1ab`

## abi

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
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "ESI"
    ],
    "stack_arguments": [
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "5017c30dacc8c7a87539090d721e692c1c003f590d644301f8c880edbfb38310",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
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
        "obs-0028"
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
        "obs-0004"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0013"
      ],
      "claim": "ECX carries the receiver: 0x00a98400 is slot 6 of the vptr-backed vftable at 0x01458788, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 6,
        "table": "0x01458788"
      }
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0014",
        "obs-0018",
        "obs-0023",
        "obs-0025",
        "obs-0028"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0028"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00a98400",
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
      "raw": "SUB ESP,0x38",
      "sub": 56
    },
    {
      "at": "0x00a98400",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x38",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00a98403",
      "count": 11,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x40]",
      "reg": "ESP"
    },
    {
      "at": "0x00a98403",
      "base": "ESP",
      "disp": 64,
      "id": "obs-0004",
      "index": 1,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x40]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00a98403",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x40]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00a98407",
      "count": 8,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOVSS XMM0
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "ESI"
    ],
    "stack_arguments": [
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "5017c30dacc8c7a87539090d721e692c1c003f590d644301f8c880edbfb38310",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
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
        "obs-0028"
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
        "obs-0004"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0013"
      ],
      "claim": "ECX carries the receiver: 0x00a98400 is slot 6 of the vptr-backed vftable at 0x01458788, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 6,
        "table": "0x01458788"
      }
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0014",
        "obs-0018",
        "obs-0023",
        "obs-0025",
        "obs-0028"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0028"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00a98400",
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
      "raw": "SUB ESP,0x38",
      "sub": 56
    },
    {
      "at": "0x00a98400",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x38",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00a98403",
      "count": 11,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x40]",
      "reg": "ESP"
    },
    {
      "at": "0x00a98403",
      "base": "ESP",
      "disp": 64,
      "id": "obs-0004",
      "index": 1,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x40]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00a98403",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x40]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00a98407",
      "count": 8,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOVSS XMM0
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
  "count": 31,
  "instructions": [
    {
      "address": "00a98400",
      "instruction": "SUB ESP,0x38"
    },
    {
      "address": "00a98403",
      "instruction": "MOV EAX,dword ptr [ESP + 0x40]"
    },
    {
      "address": "00a98407",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00a9840c",
      "instruction": "MOV DX,word ptr [EAX + 0x2]"
    },
    {
      "address": "00a98410",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "00a98416",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a9841b",
      "instruction": "MOVSS dword ptr [ESP + 0x8],XMM0"
    },
    {
      "address": "00a98421",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00a98426",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00a98427",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00a98429",
      "instruction": "MOV CX,word ptr [EAX]"
    },
    {
      "address": "00a9842c",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM0"
    },
    {
      "address": "00a98432",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x10]"
    },
    {
      "address": "00a98437",
      "instruction": "ADD EAX,0x14"
    },
    {
      "address": "00a9843a",
      "instruction": "MOV word ptr [ESP + 0x4],CX"
    },
    {
      "address": "00a9843f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00a98440",
      "instruction": "LEA ECX,[ESP + 0x1c]"
    },
    {
      "address": "00a98444",
      "instruction": "MOV word ptr [ESP + 0xa],DX"
    },
    {
      "address": "00a98449",
      "instruction": "MOVSS dword ptr [ESP + 0x18],XMM0"
    },
    {
      "address": "00a9844f",
      "instruction": "CALL 0x0041cb40"
    },
    {
      "address": "00a98454",
      "instruction": "MOV EAX,dword ptr [ESP + 0x40]"
    },
    {
      "address": "00a98458",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00a98459",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "00a9845d",
      "instruction": "CALL 0x00537f40"
    },
    {
      "address": "00a98462",
      "instruction": "LEA ECX,[ESP + 0x4]"
    },
    {
      "address": "00a98466",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00a98467",
      "instruction": "LEA ECX,[ESI + 0x18]"
    },
    {
      "address": "00a9846a",
      "instruction": "CALL 0x00537dc0"
    },
    {
      "address": "00a9846f",
      "instruction": "POP ESI"
    },
    {
      "address": "00a98470",
      "instruction": "ADD ESP,0x38"
    },
    {
      "address": "00a98473",
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
        "same_subsystem",
        "shared_vtable:vtable:0x01458788"
      ],
      "package": "pkg-vft-preinc-0051e340",
      "score": 10,
      "symbol": "vft_preinc_0051e340",
      "va": "0x0051e340"
    },
    {
      "match_basis": [
        "same_subsystem",
        "shared_vtable:vtable:0x01458788"
      ],
      "package": "subobject-forward-0051e380",
      "score": 10,
      "symbol": "subobject_forward_0051e380",
      "va": "0x0051e380"
    },
    {
      "match_basis": [
        "same_subsystem",
        "shared_vtable:vtable:0x01458788"
      ],
      "package": "pkg-swarm-w2-00a980b0",
      "score": 10,
      "symbol": "re_00a980b0",
      "va": "0x00a980b0"
    },
    {
      "match_basis": [
        "same_subsystem",
        "shared_vtable:vtable:0x01458788"
      ],
      "package": "pkg-swarm-w2-00a98200",
      "score": 10,
      "symbol": "re_00a98200",
      "va": "0x00a98200"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "pkg-swarm-w2-00586700",
      "score": 6,
      "symbol": "re_00586700",
      "va": "0x00586700"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "pkg-swarm-w1-005b2490",
      "score": 6,
      "symbol": "re_005b2490",
      "va": "0x005b2490"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "pkg-swarm-w1-005ba0d0",
      "score": 6,
      "symbol": "re_005ba0d0",
      "va": "0x005ba0d0"
    },
    {
      "match_basis": [
        "same_subsystem"
      ],
      "package": "pkg-editor-child-007f30d0",
      "score": 6,
      "symbol": "FUN_007f30d0",
      "va": "0x007f30d0"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [],
  "body_status": null,
  "class_type": null,
  "cluster": "editor-core",
  "confidence": null,
  "dependencies": {
    "callees": [],
    "callees_truncated": false,
    "callers": [],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x00a9844f",
        "direction": "out",
        "other": "0x0041cb40",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00a9846a",
        "direction": "out",
        "other": "0x00537dc0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00a9845d",
        "direction": "out",
        "other": "0x00537f40",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 0,
    "fan_out": 0,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0341",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "INFERRED",
  "globals": [],
  "integration_status": null,
  "name": "FUN_00a98400",
  "normalized_symbol": "FUN_00a98400",
  "observed_mechanics": [],
  "ownership": {
    "claimability": "queue_candidate",
    "handoff_packages": [],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": null,
    "queue_state": "candidate"
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
    "files": [],
    "handoffs": [],
    "metadata": [],
    "provenance": []
  },
  "status": "candidate",
  "subsystem": "Editor",
  "triage": {
    "category": "GAMEPLAY_LOGIC",
    "cluster": "editor-core",
    "db_triage_status": "candidate",
    "decomp_path": null,
    "dependencies": [],
    "evidence": "INFERRED",
    "kg_node_id": "fun:00a98400",
    "name": "FUN_00a98400",
    "priority": "P1",
    "provenance": {
      "classifier": "triage-v5",
      "sdk_name": null,
      "snapshot": "f0e310e0",
      "snapshot_sha256": "f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b",
      "vtable_addrs": [
        "01458788"
      ]
    },
    "queue_state": "candidate",
    "rank": 272
  },
  "types": [],
  "unresolved_questions": [],
  "va": "0x00a98400",
  "vtables": [
    "vtable:0x01458788"
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
  "body_end": "00a98475",
  "body_span_bytes": 118,
  "body_start": "00a98400",
  "callees": [
    "FUN_0041cb40",
    "FUN_00537f40",
    "FUN_00537dc0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00a98400",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:1",
      "type": "undefined"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined4"
    },
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "undefined4"
    },
    {
      "name": "local_34",
      "storage": "Stack[-0x34]:4",
      "type": "undefined4"
    },
    {
      "name": "local_36",
      "storage": "Stack[-0x36]:2",
      "type": "undefined2"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:2",
      "type": "undefined2"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00a98400",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x698400",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00a98400(void)",
  "size_bytes": 118,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00a98400",
  "vtables": {
    "referenced_by_vtables": [
      "0x01458788"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "014587a0"
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
  "status": "candidate"
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
  "vtable:0x01458788"
]
```

## Conflicts

```json
[]
```
