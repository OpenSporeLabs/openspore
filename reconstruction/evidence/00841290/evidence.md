# Evidence 0x00841290

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f303c15630ec295d75d1d414c35d3a074df4c5ec143e4e0986d353ae9188d9a9`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with the receiver in ECX and one caller-pushed four-byte stack word",
  "hidden_this_register": "ECX",
  "hidden_this_type": "FormatParser * (SporeApp.exe has no MSVC RTTI; the receiver type is an opaque vtable-owning object)",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    {
      "entry_offset": "EBP+0x08",
      "load_instruction": "0x008412ab: MOV EDX,dword ptr [EBP + 0x8]",
      "name": "argument_08",
      "semantic_type": "unresolved; passed straight through to the +0x3c slot as a raw 32-bit word",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x4",
  "return_note": "(modeled)",
  "return_register": "EAX",
  "return_type": "bool",
  "saved_registers": "EBX, ESI and EDI are pushed and popped unmodified; the fourth push (ECX at 0x008412a8) is dropped by MOV ESP,EBP",
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee"
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
        "ebp_offset": "EBP+0x8",
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
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
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
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "17913e6612e3204bb8500f353540591eb8f1cac9d72854f58f751cd09696c663",
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
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with the receiver in ECX and one caller-pushed four-byte stack word"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0027"
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
        "obs-0010"
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
        "obs-0009",
        "obs-0019",
        "obs-0020",
        "obs-0021"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          60
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0008",
        "obs-0021"
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
        "obs-0009",
        "obs-0019",
        "obs-0020",
        "obs-0021",
        "obs-0027"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0027"
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
        "obs-0027"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0027"
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
      "at": "0x00841290",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00841290",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x00841291",
      "count": 3,
      "first_use": 1,
      "first_write_index": 24,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x00841291",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x0084129a",
      "id": "obs-0005",
      "index": 4,
      "kind": "SEGMENT_TLS",
      "raw": "MOV EAX,FS:[0x0]",
      "segment": "FS",
      "text": "FS:[0x0]"
    },
    {
      "at": "0x0084129a",
      "definite": true,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,FS:[0x0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x008412a0",
      "count": 3,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EA
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
  "count": 27,
  "instructions": [
    {
      "address": "00841290",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00841291",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "00841293",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "00841295",
      "instruction": "PUSH 0x1217640"
    },
    {
      "address": "0084129a",
      "instruction": "MOV EAX,FS:[0x0]"
    },
    {
      "address": "008412a0",
      "instruction": "PUSH EAX"
    },
    {
      "address": "008412a1",
      "instruction": "MOV dword ptr FS:[0x0],ESP"
    },
    {
      "address": "008412a8",
      "instruction": "PUSH ECX"
    },
    {
      "address": "008412a9",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "008412ab",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "008412ae",
      "instruction": "MOV EAX,dword ptr [EAX + 0x3c]"
    },
    {
      "address": "008412b1",
      "instruction": "PUSH EBX"
    },
    {
      "address": "008412b2",
      "instruction": "PUSH ESI"
    },
    {
      "address": "008412b3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "008412b4",
      "instruction": "MOV dword ptr [EBP + -0x10],ESP"
    },
    {
      "address": "008412b7",
      "instruction": "PUSH EDX"
    },
    {
      "address": "008412b8",
      "instruction": "MOV dword ptr [EBP + -0x4],0x0"
    },
    {
      "address": "008412bf",
      "instruction": "CALL EAX"
    },
    {
      "address": "008412c1",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "008412c3",
      "instruction": "MOV ECX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "008412c6",
      "instruction": "MOV dword ptr FS:[0x0],ECX"
    },
    {
      "address": "008412cd",
      "instruction": "POP EDI"
    },
    {
      "address": "008412ce",
      "instruction": "POP ESI"
    },
    {
      "address": "008412cf",
      "instruction": "POP EBX"
    },
    {
      "address": "008412d0",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "008412d2",
      "instruction": "POP EBP"
    },
    {
      "address": "008412d3",
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
    "architecture": "x86-32",
    "calling_convention": "x86-32 thiscall with the receiver in ECX and one caller-pushed four-byte stack word",
    "hidden_this_register": "ECX",
    "hidden_this_type": "FormatParser * (SporeApp.exe has no MSVC RTTI; the receiver type is an opaque vtable-owning object)",
    "ordinary_stack_argument_slots": 1,
    "ordinary_stack_arguments": [
      {
        "entry_offset": "EBP+0x08",
        "load_instruction": "0x008412ab: MOV EDX,dword ptr [EBP + 0x8]",
        "name": "argument_08",
        "semantic_type": "unresolved; passed straight through to the +0x3c slot as a raw 32-bit word",
        "type": "uint32_t",
        "width_bytes": 4
      }
    ],
    "ret_form": "RET 0x4",
    "return_note": "(modeled)",
    "return_register": "EAX",
    "return_type": "bool",
    "saved_registers": "EBX, ESI and EDI are pushed and popped unmodified; the fourth push (ECX at 0x008412a8) is dropped by MOV ESP,EBP",
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee"
  },
  "analogues": [
    {
      "match_basis": [
        "same_subsystem",
        "shared_vtable:vtable:0x0141c930,vtable:0x0141c97c"
      ],
      "package": "PKG-ARGSCRIPT-WAVE9",
      "score": 10,
      "symbol": "pkg_argscript_get_current_scope_00d1dcd0",
      "va": "0x00d1dcd0"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [],
  "body_status": null,
  "class_type": null,
  "cluster": "scripting-content",
  "confidence": null,
  "dependencies": {
    "callees": [],
    "callees_truncated": false,
    "callers": [],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 0,
    "fan_out": 0,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0259",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "CONFIRMED",
  "globals": [],
  "integration_status": null,
  "name": "ArgScript::FormatParser::Release",
  "normalized_symbol": "ArgScript::FormatParser::Release",
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
    "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__Release.c",
    "file": null,
    "files": [
      ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__Release.c",
      "reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290.cpp",
      "reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290.hpp",
      "reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290_model_test.cpp"
    ],
    "handoffs": [],
    "metadata": [
      "reconstruction/metadata/pkg-orchestrate-dogfood-00841290/00841290.json"
    ],
    "provenance": []
  },
  "status": "queued",
  "subsystem": "ArgScript",
  "triage": {
    "category": "ENGINE_INTERFACE",
    "cluster": "scripting-content",
    "db_triage_status": "QUEUED",
    "decomp_path": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__Release.c",
    "dependencies": [
      "resource-io"
    ],
    "evidence": "CONFIRMED",
    "kg_node_id": "fun:00841290",
    "name": "ArgScript::FormatParser::Release",
    "priority": "P0",
    "provenance": {
      "classifier": "triage-v4",
      "generated_at": "2026-09-23T10:12:09Z",
      "generator": "subagent-7-sequential-triage",
      "sdk_name": "ArgScript::FormatParser::Release",
      "snapshot": "2540f2ca",
      "snapshot_sha256": "2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8",
      "vtable_addrs": [
        "0141c930",
        "0141c97c"
      ]
    },
    "queue_state": "queued",
    "rank": 83
  },
  "types": [
    "FormatParser * (SporeApp.exe has no MSVC RTTI; the receiver type is an opaque vtable-owning object)",
    "bool (modeled)",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00841290::FormatParserReleaseSlot3c",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00841290::OpaqueFormatParser",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00841290::OpaqueFormatParserVtable",
    "openspore::reconstruction::pkg_orchestrate_dogfood_00841290::OpaqueReleasePorts",
    "uint32_t"
  ],
  "unresolved_questions": [
    "Is the native return type bool or int, given that only AL is written?",
    "The briefing carried no ABI projection (evidence.missing_sections: ABI); the whole observed_original_abi block above was derived by hand from the disassembly and must be reviewed against a native build.",
    "What does the funclet at 0x01217640 do if the +0x3c callee raises an exception, and is the state word at [EBP-4] ever set by a path not present in this body?",
    "What is the full extent of the vtable beginning at 0x0141c930, and which slots below index 15 belong to base classes?",
    "What is the single stack argument at [EBP+0x8] (type, producer, and meaning)?",
    "Which concrete callee does vtable index 15 resolve to for a live FormatParser receiver, and does the base class at 0x0141c930 or the secondary vtable at 0x0141c97c own that slot?"
  ],
  "va": "0x00841290",
  "vtables": [
    "vtable:0x0141c930",
    "vtable:0x0141c97c"
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
  "body_end": "008412d5",
  "body_span_bytes": 70,
  "body_start": "00841290",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00841290",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "ArgScript::FormatParser::Release",
  "namespace": "ArgScript",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "FormatParser *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "int",
  "return_type_resolved": true,
  "rva": "0x441290",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "int ArgScript::FormatParser::Release(FormatParser * this)",
  "size_bytes": 70,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00841290",
  "vtables": {
    "referenced_by_vtables": [
      "0x0141c930",
      "0x0141c97c"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0141c97c"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__Release.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__Release.c",
    "reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290.hpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-00841290/dogfood_00841290_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-orchestrate-dogfood-00841290/00841290.json"
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "FormatParser * (SporeApp.exe has no MSVC RTTI; the receiver type is an opaque vtable-owning object)",
  "bool (modeled)",
  "openspore::reconstruction::pkg_orchestrate_dogfood_00841290::FormatParserReleaseSlot3c",
  "openspore::reconstruction::pkg_orchestrate_dogfood_00841290::OpaqueFormatParser",
  "openspore::reconstruction::pkg_orchestrate_dogfood_00841290::OpaqueFormatParserVtable",
  "openspore::reconstruction::pkg_orchestrate_dogfood_00841290::OpaqueReleasePorts",
  "uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0141c930",
  "vtable:0x0141c97c"
]
```

## Conflicts

```json
[]
```
