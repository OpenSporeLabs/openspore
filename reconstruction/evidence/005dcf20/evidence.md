# Evidence 0x005dcf20

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `cc1cc3a39c0e705bf57fec90cdb424763ed1280d645a8be55fd72d03f6870bf3`

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
      "name": "key",
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+8",
      "name": "flag_a",
      "observed_values": [
        0,
        1
      ],
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+12",
      "name": "flag_b",
      "observed_values": [
        0,
        1
      ],
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 12
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
    "ret_form": "RET 0xc",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBX",
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
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +36, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "cd5493ef21b255b1af0eddbd5fc2443d416f4abe405d217598c53a83360a4d23",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0026"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0006",
        "obs-0007",
        "obs-0014"
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
        "obs-0006",
        "obs-0007",
        "obs-0014"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0026"
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
        "obs-0026"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0026"
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
      "at": "0x005dcf20",
      "count": 7,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005dcf21",
      "count": 3,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x005dcf21",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x005dcf21",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005dcf25",
      "count": 7,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x005dcf26",
      "count": 3,
      "first_use": 3,
      "first_write_index": 21,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005dcf26",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x005dcf2e",
      "id": "obs-0008",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x008105b0",
      "target": "0x008105b0"
    },
    {
      "at": "0x005dcf3d",
      "id": "obs-0009",
      "index": 13,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x008105b0",
      "target": "0x008105b0"
    },
    {
      "at": "0x005dcf
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
    "va": "0x0057c2f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005dd610"
  },
  {
    "name": "FUN_005dda30",
    "reconstructed": true,
    "va": "0x005dda30"
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
  "count": 47,
  "instructions": [
    {
      "address": "005dcf20",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005dcf21",
      "instruction": "MOV ESI,dword ptr [ESP + 0x8]"
    },
    {
      "address": "005dcf25",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005dcf26",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "005dcf28",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dcf2a",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005dcf2b",
      "instruction": "LEA ECX,[EDI + 0x14]"
    },
    {
      "address": "005dcf2e",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005dcf33",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005dcf35",
      "instruction": "JNZ 0x005dcf42"
    },
    {
      "address": "005dcf37",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dcf39",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005dcf3a",
      "instruction": "LEA ECX,[EDI + 0x2c]"
    },
    {
      "address": "005dcf3d",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005dcf42",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "005dcf44",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "005dcf46",
      "instruction": "JZ 0x005dcf89"
    },
    {
      "address": "005dcf48",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "005dcf4a",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "005dcf4d",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005dcf4e",
      "instruction": "PUSH 0x8ed27e7a"
    },
    {
      "address": "005dcf53",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005dcf55",
      "instruction": "CALL EDX"
    },
    {
      "address": "005dcf57",
      "instruction": "MOV EBX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "005dcf5b",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "005dcf5d",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "005dcf5f",
      "instruction": "MOV EDX,dword ptr [EAX + 0x28]"
    },
    {
      "address": "005dcf62",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005dcf63",
      "instruction": "PUSH 0x4"
    },
    {
      "address": "005dcf65",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "005dcf67",
      "instruction": "CALL EDX"
    },
    {
      "address": "005dcf69",
      "instruction": "CMP byte ptr [ESP + 0x18],0x0"
    },
    {
      "address": "005dcf6e",
      "instruction": "JZ 0x005dcf7c"
    },
    {
      "address": "005dcf70",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "005dcf72",
      "instruction": "MOV EDX,dword ptr [EAX + 0x28]"
    },
    {
      "address": "005dcf75",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005dcf76",
      "instruction": "PUSH 0x20"
    },
    {
      "address": "005dcf78",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "005dcf7a",
      "instruction": "CALL EDX"
    },
    {
      "address": "005dcf7c",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "005dcf7e",
      "instruction": "MOV EDX,dword ptr [EAX + 0x94]"
    },
    {
      "address": "005dcf84",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005dcf86",
      "instruction": "CALL EDX"
    },
    {
      "address": "005dcf88",
      "instruction": "POP EBX"
    },
    {
      "address": "005dcf89",
      "instruction": "POP EDI"
    },
    {
      "address": "005dcf8a",
      "instruction": "POP ESI"
    },
    {
      "address": "005dcf8b",
      "instruction": "RET 0xc"
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
    "calling_convention": "__thiscall",
    "hidden_this_register": "ECX",
    "return_type": "void",
    "stack_arguments": [
      {
        "entry_offset": "ESP+4",
        "name": "key",
        "type": "uint32_t",
        "width_bytes": 4
      },
      {
        "entry_offset": "ESP+8",
        "name": "flag_a",
        "observed_values": [
          0,
          1
        ],
        "type": "uint32_t",
        "width_bytes": 4
      },
      {
        "entry_offset": "ESP+12",
        "name": "flag_b",
        "observed_values": [
          0,
          1
        ],
        "type": "uint32_t",
        "width_bytes": 4
      }
    ],
    "stack_cleanup_bytes": 12
  },
  "analogues": [
    {
      "match_basis": [
        "same_calling_convention",
        "direct_xref_neighbor"
      ],
      "package": "PKG-10-EDITOR-DISPATCH",
      "score": 5,
      "symbol": "FUN_005dda30",
      "va": "0x005dda30"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-APP-SAFE-WAVE11",
      "score": 2,
      "symbol": "property_record_assign_pair_004279d0",
      "va": "0x004279d0"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-APP-SAFE-WAVE11",
      "score": 2,
      "symbol": "property_record_assign_scalar_00428060",
      "va": "0x00428060"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-EDITOR-SAFE-WAVE11",
      "score": 2,
      "symbol": "editor_paint_commit_0043ac40",
      "va": "0x0043ac40"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-APP-SAFE-WAVE11",
      "score": 2,
      "symbol": "model_parts_apply_properties_00447150",
      "va": "0x00447150"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-APP-SAFE-WAVE11",
      "score": 2,
      "symbol": "pair_vector_insert_004786e0",
      "va": "0x004786e0"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-EDITOR-SAFE-WAVE11",
      "score": 2,
      "symbol": "editor_entry_expand_004ad6f0",
      "va": "0x004ad6f0"
    },
    {
      "match_basis": [
        "same_calling_convention"
      ],
      "package": "PKG-10-EDITOR-DISPATCH",
      "score": 2,
      "symbol": "Editors_EditorModel_SetColor_raw_004ae250",
      "va": "0x004ae250"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [
    "The declaration uses uint32_t slots to preserve observed x86 stack width rather than assigning semantic names.",
    "The helper has no RTTI and the flag semantics cannot be recovered from these call sites alone."
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
        "va": "0x0057c2f0"
      },
      {
        "name": null,
        "reconstructed": false,
        "va": "0x005dd610"
      },
      {
        "name": "FUN_005dda30",
        "reconstructed": true,
        "va": "0x005dda30"
      }
    ],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x0057c35e",
        "direction": "in",
        "other": "0x0057c2f0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x005dd6d6",
        "direction": "in",
        "other": "0x005dd610",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x005dd6eb",
        "direction": "in",
        "other": "0x005dd610",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x005ddd00",
        "direction": "in",
        "other": "0x005dda30",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x005dcf2e",
        "direction": "out",
        "other": "0x008105b0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x005dcf3d",
        "direction": "out",
        "other": "0x008105b0",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 3,
    "fan_out": 0,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [
      "0x005dda30"
    ],
    "scc": {
      "id": "scc-0130",
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
    "files": [],
    "handoffs": [],
    "metadata": [
      "reconstruction/metadata/pkg10-editor-dispatch/005dcf20.json"
    ],
    "provenance": []
  },
  "status": "unresolved",
  "subsystem": null,
  "triage": null,
  "types": [
    "Opaque void* lookup results reached by this helper; no concrete owner type is asserted",
    "OpaqueEditorModeManager for ECX",
    "uint32_t",
    "uint32_t for the key and two observed 0/1 flags",
    "void"
  ],
  "unresolved_questions": [
    "Is the third stack value always a boolean-like flag, or can other values occur?",
    "What do flag_a and flag_b mean operationally?",
    "Which opaque target interface owns the 0xc, 0x28, and 0x94 slots?"
  ],
  "va": "0x005dcf20",
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
  "body_end": "005dcf8d",
  "body_span_bytes": 110,
  "body_start": "005dcf20",
  "callees": [
    "FUN_008105b0"
  ],
  "callers": [
    "FUN_005dd610",
    "FUN_0057c2f0",
    "FUN_005dda30"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005dcf20",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005dcf20",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1dcf20",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005dcf20(void)",
  "size_bytes": 110,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005dcf20",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "0057c35e"
    },
    {
      "from": "005ddd00"
    },
    {
      "from": "005dd6d6"
    },
    {
      "from": "005dd6eb"
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
    "reconstruction/metadata/pkg10-editor-dispatch/005dcf20.json"
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
  "Opaque void* lookup results reached by this helper; no concrete owner type is asserted",
  "OpaqueEditorModeManager for ECX",
  "uint32_t",
  "uint32_t for the key and two observed 0/1 flags",
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
