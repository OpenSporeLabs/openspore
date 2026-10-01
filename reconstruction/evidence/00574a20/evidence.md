# Evidence 0x00574a20

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c0f12f1d04f76297825b4a268052d01fdb6c8da65e73e6db96483bd5339a7d9f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall-like",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueEditor *",
  "return_note": "opaque pointer-like value",
  "stack_arguments": [
    {
      "abi_type": "unclassified 32-bit value",
      "entry_offset": "ESP+4",
      "name": "receiver_candidate_word",
      "nonzero_behavior": "use the incoming value directly as the tail-call ECX receiver candidate; no uint32 selector semantics are established",
      "type": "unclassified 32-bit value",
      "width_bytes": 4,
      "zero_behavior": "load [ECX+0x150] and use that value as the tail-call ECX receiver candidate"
    }
  ],
  "stack_cleanup_bytes": 4
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "cbd6d33c58f00d839ef553c50437af8906c61e627dc8c8be8ef0457e140f929d",
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
    "persisted_calling_convention": "__thiscall-like"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0009"
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
        "obs-0002",
        "obs-0005"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0006",
        "obs-0007"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          336
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0006",
        "obs-0007",
        "obs-0009"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0009"
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
        "obs-0008",
        "obs-0009"
      ],
      "claim": "the function can reach a caller by transferring out of the listing, so the path that actually returns was never observed",
      "confidence": "UNKNOWN",
      "id": "T2",
      "value": {
        "form": "epilogue_then_jmp"
      }
    },
    {
      "based_on": [
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009"
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
      "at": "0x00574a20",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00574a20",
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
      "at": "0x00574a20",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00574a28",
      "count": 1,
      "first_use": 3,
      "first_write_index": 7,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x150]",
      "reg": "ECX"
    },
    {
      "at": "0x00574a32",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0005",
      "index": 6,
      "key": 4,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP + 0x4],0x1",
      "resolved": true,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00574a3a",
      "count": 2,
      "first_use": 7,
      "first_write_index": 0,
      "id": "obs-0006",
      "index": 7,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00574a3a",
      "definite": true,
      "id": "obs-0007",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00574a3c",
      "id": "obs-0008",
      "index": 8,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x004c49e0",
      "target": "0x004c49e0"
   
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
    "va": "0x004c49e0"
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
    "name": "Editor_Save",
    "reconstructed": false,
    "va": "0x00577650"
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
  "count": 11,
  "instructions": [
    {
      "address": "00574a20",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00574a24",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00574a26",
      "instruction": "JNZ 0x00574a32"
    },
    {
      "address": "00574a28",
      "instruction": "MOV EAX,dword ptr [ECX + 0x150]"
    },
    {
      "address": "00574a2e",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00574a30",
      "instruction": "JZ 0x00574a41"
    },
    {
      "address": "00574a32",
      "instruction": "MOV dword ptr [ESP + 0x4],0x1"
    },
    {
      "address": "00574a3a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00574a3c",
      "instruction": "JMP 0x004c49e0"
    },
    {
      "address": "00574a41",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00574a43",
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
  "abi": {
    "calling_convention": "__thiscall-like",
    "hidden_this_register": "ECX",
    "hidden_this_type": "OpaqueEditor *",
    "return_note": "opaque pointer-like value",
    "stack_arguments": [
      {
        "abi_type": "unclassified 32-bit value",
        "entry_offset": "ESP+4",
        "name": "receiver_candidate_word",
        "nonzero_behavior": "use the incoming value directly as the tail-call ECX receiver candidate; no uint32 selector semantics are established",
        "type": "unclassified 32-bit value",
        "width_bytes": 4,
        "zero_behavior": "load [ECX+0x150] and use that value as the tail-call ECX receiver candidate"
      }
    ],
    "stack_cleanup_bytes": 4
  },
  "analogues": [
    {
      "match_basis": [
        "direct_xref_neighbor"
      ],
      "package": "PKG-10-EDITOR-DISPATCH",
      "score": 3,
      "symbol": "FUN_005dda30",
      "va": "0x005dda30"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [
    "The package declaration intentionally uses void* for the pointer-like result; concrete owner and selector semantics remain unresolved.",
    "The pointer-like return is not dereferenced and is not used beyond a null/nonzero check at the target call site."
  ],
  "body_status": null,
  "class_type": null,
  "cluster": null,
  "confidence": null,
  "dependencies": {
    "callees": [
      {
        "name": null,
        "reconstructed": false,
        "va": "0x004c49e0"
      }
    ],
    "callees_truncated": false,
    "callers": [
      {
        "name": "Editor_Save",
        "reconstructed": false,
        "va": "0x00577650"
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
        "callsite": "0x0057775a",
        "direction": "in",
        "other": "0x00577650",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x005dda42",
        "direction": "in",
        "other": "0x005dda30",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00574a3c",
        "direction": "out",
        "other": "0x004c49e0",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 2,
    "fan_out": 1,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [
      "0x005dda30"
    ],
    "scc": {
      "id": "scc-0058",
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
      "reconstruction/metadata/pkg10-editor-dispatch/00574a20.json"
    ],
    "provenance": []
  },
  "status": "unresolved",
  "subsystem": null,
  "triage": null,
  "types": [
    "A nonzero incoming stack word becomes the tail-call ECX receiver candidate directly; no uint32 selector semantics are established",
    "A zero incoming stack word instead loads [ECX+0x150], whose opaque value becomes the tail-call ECX receiver candidate",
    "OpaqueEditor *",
    "OpaqueEditor for ECX; the mode-manager caller passes this+0x5c, while Editor_Save passes its own this",
    "The result retains pointer-like status and is used only through a null/nonzero guard by 0x005dda30; no boolean return is inferred",
    "opaque pointer-like value",
    "unclassified 32-bit value"
  ],
  "unresolved_questions": [
    "Can the receiver candidate at [ECX+0x150] be classified without RTTI?",
    "What concrete pointer-like owner or return semantics, if any, can be recovered for the mode2_guard result?",
    "What concrete type is established for the direct and +0x150-derived tail-call ECX receiver candidates?"
  ],
  "va": "0x00574a20",
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
  "body_end": "00574a45",
  "body_span_bytes": 38,
  "body_start": "00574a20",
  "callees": [
    "FUN_004c49e0"
  ],
  "callers": [
    "Editor_Save",
    "FUN_005dda30"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00574a20",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00574a20",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x174a20",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00574a20(void)",
  "size_bytes": 38,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00574a20",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "0057775a"
    },
    {
      "from": "005dda42"
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
    "reconstruction/metadata/pkg10-editor-dispatch/00574a20.json"
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
  "A nonzero incoming stack word becomes the tail-call ECX receiver candidate directly; no uint32 selector semantics are established",
  "A zero incoming stack word instead loads [ECX+0x150], whose opaque value becomes the tail-call ECX receiver candidate",
  "OpaqueEditor *",
  "OpaqueEditor for ECX; the mode-manager caller passes this+0x5c, while Editor_Save passes its own this",
  "The result retains pointer-like status and is used only through a null/nonzero guard by 0x005dda30; no boolean return is inferred",
  "opaque pointer-like value",
  "unclassified 32-bit value"
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
