# Evidence 0x007e6130

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b4edbad76d6bec1fe4dc61a0c3c5ecf5779355cf8fd96e4e6febd8c55516818b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "interior continuation of the cdecl-shaped 0x007e6100 body; not a standalone call",
  "hidden_receiver": "No public receiver parameter; ECX is comparison state established by 0x007e6100 and is not the SDK this pointer.",
  "ordinary_stack_arguments": [],
  "return_note": "0/1",
  "return_type": "AL"
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
      "entry_ESP+0x10",
      "entry_ESP+0x14"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "fb380b0c56da3d1971f06175d8c21d6fca5327ba50e1061d3796854b73553c06",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__thiscall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "interior continuation of the cdecl-shaped 0x007e6100 body; not a standalone call"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0006",
        "obs-0032",
        "obs-0034"
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
        "obs-0004",
        "obs-0014"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 3,
        "observed_slots": 2,
        "total_bytes": 20
      }
    },
    {
      "based_on": [
        "obs-0007",
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
        "obs-0012"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0032",
        "obs-0034"
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
        "obs-0006",
        "obs-0032",
        "obs-0034"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0032",
        "obs-0034"
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
      "at": "0x007e6130",
      "count": 22,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "SBB EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x007e6130",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SBB EAX,EAX",
      "reg": "EAX",
      "write_kind": "arith"
    },
    {
      "at": "0x007e6139",
      "count": 2,
      "first_use": 4,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x007e6139",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0004",
      "index": 4,
      "key": 16,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x007e6145",
      "id": "obs-0005",
      "index": 7,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x007e6146",
      "form": "RET",
     
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "ui_layer_manager_get_0067ca90",
    "reconstructed": true,
    "va": "0x0067ca90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
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
  "count": 69,
  "instructions": [
    {
      "address": "007e6130",
      "instruction": "SBB EAX,EAX"
    },
    {
      "address": "007e6132",
      "instruction": "SBB EAX,-0x1"
    },
    {
      "address": "007e6135",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "007e6137",
      "instruction": "JNZ 0x007e6147"
    },
    {
      "address": "007e6139",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "007e613d",
      "instruction": "MOV dword ptr [EAX],0x153f864"
    },
    {
      "address": "007e6143",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "007e6145",
      "instruction": "POP ESI"
    },
    {
      "address": "007e6146",
      "instruction": "RET"
    },
    {
      "address": "007e6147",
      "instruction": "MOV ECX,0x1413874"
    },
    {
      "address": "007e614c",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "007e614e",
      "instruction": "MOV EDI,EDI"
    },
    {
      "address": "007e6150",
      "instruction": "MOV DL,byte ptr [EAX]"
    },
    {
      "address": "007e6152",
      "instruction": "CMP DL,byte ptr [ECX]"
    },
    {
      "address": "007e6154",
      "instruction": "JNZ 0x007e6170"
    },
    {
      "address": "007e6156",
      "instruction": "TEST DL,DL"
    },
    {
      "address": "007e6158",
      "instruction": "JZ 0x007e616c"
    },
    {
      "address": "007e615a",
      "instruction": "MOV DL,byte ptr [EAX + 0x1]"
    },
    {
      "address": "007e615d",
      "instruction": "CMP DL,byte ptr [ECX + 0x1]"
    },
    {
      "address": "007e6160",
      "instruction": "JNZ 0x007e6170"
    },
    {
      "address": "007e6162",
      "instruction": "ADD EAX,0x2"
    },
    {
      "address": "007e6165",
      "instruction": "ADD ECX,0x2"
    },
    {
      "address": "007e6168",
      "instruction": "TEST DL,DL"
    },
    {
      "address": "007e616a",
      "instruction": "JNZ 0x007e6150"
    },
    {
      "address": "007e616c",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "007e616e",
      "instruction": "JMP 0x007e6175"
    },
    {
      "address": "007e6170",
      "instruction": "SBB EAX,EAX"
    },
    {
      "address": "007e6172",
      "instruction": "SBB EAX,-0x1"
    },
    {
      "address": "007e6175",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "007e6177",
      "instruction": "JNZ 0x007e6204"
    },
    {
      "address": "007e617d",
      "instruction": "CALL 0x0067ca90"
    },
    {
      "address": "007e6182",
      "instruction": "MOV ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "007e6186",
      "instruction": "MOV dword ptr [ESI],EAX"
    },
    {
      "address": "007e6188",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "007e618d",
      "instruction": "MOV dword ptr [ESI + 0x4],EAX"
    },
    {
      "address": "007e6190",
      "instruction": "CALL 0x0067caa0"
    },
    {
      "address": "007e6195",
      "instruction": "MOV dword ptr [ESI + 0x8],EAX"
    },
    {
      "address": "007e6198",
      "instruction": "CALL 0x0067dd10"
    },
    {
      "address": "007e619d",
      "instruction": "MOV dword ptr [ESI + 0xc],EAX"
    },
    {
      "address": "007e61a0",
      "instruction": "CALL 0x0067dd50"
    },
    {
      "address": "007e61a5",
      "instruction": "MOV dword ptr [ESI + 0x10],EAX"
    },
    {
      "address": "007e61a8",
      "instruction": "CALL 0x0067dd80"
    },
    {
      "address": "007e61ad",
      "instruction": "MOV dword ptr [ESI + 0x14],EAX"
    },
    {
      "address": "007e61b0",
      "instruction": "CALL 0x0067dd90"
    },
    {
      "address": "007e61b5",
      "instruction": "MOV dword ptr [ESI + 0x18],EAX"
    },
    {
      "address": "007e61b8",
      "instruction": "CALL 0x0067ddd0"
    },
    {
      "address": "007e61bd",
      "instruction": "MOV dword ptr [ESI + 0x1c],EAX"
    },
    {
      "address": "007e61c0",
      "instruction": "CALL 0x0067cb20"
    },
    {
      "address": "007e61c5",
      "instruction": "MOV dword ptr [ESI + 0x20],EAX"
    },
    {
      "address": "007e61c8",
      "instruction": "CALL 0x0067cb00"
    },
    {
      "address": "007e61cd",
      "instruction": "MOV dword ptr [ESI + 0x24],EAX"
    },
    {
      "address": "007e61d0",
      "instruction": "CALL 0x0067de30"
    },
    {
      "address": "007e61d5",
      "instruction": "MOV dword ptr [ESI + 0x2c],EAX"
    },
    {
      "address": "007e61d8",
      "instruction": "CALL 0x0067ddb0"
    },
    {
      "address": "007e61dd",
      "instruction": "MOV dword ptr [ESI + 0x30],EAX"
    },
    {
      "address": "007e61e0",
      "instruction": "CALL 0x0067cb50"
    },
    {
      "address": "007e61e5",
      "instruction": "MOV dword ptr [ESI + 0x34],EAX"
    },
    {
      "address": "007e61e8",
      "instruction": "CALL 0x0067cb60"
    },
    {
      "address": "007e61ed",
      "instruction": "MOV dword ptr [ESI + 0x38],EAX"
    },
    {
      "address": "007e61f0",
      "instruction": "CALL 0x0067cb70"
    },
    {
      "address": "007e61f5",
      "instruction": "MOV dword ptr [ESI + 0x28],EAX"
    },
    {
      "address": "007e61f8",
      "instruction": "CALL 0x0067cb80"
    },
    {
      "address": "007e61fd",
      "instruction": "MOV dword ptr [ESI + 0x3c],EAX"
    },
    {
      "address": "007e6200",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "007e6202",
      "instruction": "POP ESI"
    },
    {
      "address": "007e6203",
      "instruction": "RET"
    },
    {
      "address": "007e6204",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "007e6206",
      "instruction": "POP ESI"
    },
    {
      "address": "007e6207",
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
    "calling_convention": "interior continuation of the cdecl-shaped 0x007e6100 body; not a standalone call",
    "hidden_receiver": "No public receiver parameter; ECX is comparison state established by 0x007e6100 and is not the SDK this pointer.",
    "ordinary_stack_arguments": [],
    "return_note": "0/1",
    "return_type": "AL"
  },
  "analogues": [
    {
      "match_basis": [
        "direct_xref_neighbor"
      ],
      "package": "PKG-RUNTIME-SERVICES-WAVE8",
      "score": 3,
      "symbol": "ui_layer_manager_get_0067ca90",
      "va": "0x0067ca90"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [
    "Original-process continuation state and service ownership remain runtime-gated."
  ],
  "body_status": null,
  "class_type": null,
  "cluster": null,
  "confidence": null,
  "dependencies": {
    "callees": [
      {
        "name": "ui_layer_manager_get_0067ca90",
        "reconstructed": true,
        "va": "0x0067ca90"
      },
      {
        "name": null,
        "reconstructed": false,
        "va": "0x0067dcc0"
      }
    ],
    "callees_truncated": false,
    "callers": [],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x007e617d",
        "direction": "out",
        "other": "0x0067ca90",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e6190",
        "direction": "out",
        "other": "0x0067caa0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e61c8",
        "direction": "out",
        "other": "0x0067cb00",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e61c0",
        "direction": "out",
        "other": "0x0067cb20",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e61e0",
        "direction": "out",
        "other": "0x0067cb50",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e61e8",
        "direction": "out",
        "other": "0x0067cb60",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e61f0",
        "direction": "out",
        "other": "0x0067cb70",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e61f8",
        "direction": "out",
        "other": "0x0067cb80",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e6188",
        "direction": "out",
        "other": "0x0067dcc0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e6198",
        "direction": "out",
        "other": "0x0067dd10",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e61a0",
        "direction": "out",
        "other": "0x0067dd50",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e61a8",
        "direction": "out",
        "other": "0x0067dd80",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e61b0",
        "direction": "out",
        "other": "0x0067dd90",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e61d8",
        "direction": "out",
        "other": "0x0067ddb0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e61b8",
        "direction": "out",
        "other": "0x0067ddd0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x007e61d0",
        "direction": "out",
        "other": "0x0067de30",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 0,
    "fan_out": 2,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [
      "0x0067ca90"
    ],
    "scc": {
      "id": "scc-0252",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": null,
  "globals": [
    "global:0x01413874 contains GetAppPluginServices and 0x0153f864 is the first-match output constant."
  ],
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
      "src/reconstruction/pkg_app_lifecycle_wave7",
      "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp",
      "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.hpp",
      "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7_model_test.cpp"
    ],
    "handoffs": [],
    "metadata": [
      "reconstruction/metadata/pkg-app-lifecycle-wave7/007e6130.json"
    ],
    "provenance": []
  },
  "status": "unresolved",
  "subsystem": null,
  "triage": null,
  "types": [
    "AL 0/1",
    "AL 0/1 on the interior exit paths",
    "CONDITIONAL_JUMP"
  ],
  "unresolved_questions": [
    "Concrete caller and receiver state for the inherited continuation",
    "Concrete owners and return values of all 16 service ports",
    "Meaning and lifetime of the output words"
  ],
  "va": "0x007e6130",
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
  "body_end": "007e6207",
  "body_span_bytes": 216,
  "body_start": "007e6130",
  "callees": [
    "Graphics::IRenderer::Get",
    "FUN_0067cb60",
    "FUN_0067cb70",
    "Sporepedia::OTDB::cObjectTemplateDB::Get",
    "Graphics::ILightingManager::Get",
    "FUN_0067ddd0",
    "FUN_0067cb50",
    "Swarm::IEffectsManager::Get",
    "FUN_0067ddb0",
    "FUN_0067caa0",
    "UI::cLayerManager::Get",
    "FUN_0067cb20",
    "FUN_0067cb80",
    "App::IAppSystem::Get",
    "FUN_0067de30",
    "Graphics::IShadowWorld::Get"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "007e6130",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cAppSystem::func7Ch",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cAppSystem *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x3e6130",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::cAppSystem::func7Ch(cAppSystem * this)",
  "size_bytes": 216,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007e6130",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "007e6114"
    },
    {
      "from": "007e6120"
    }
  ]
}
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:0x01413874 contains GetAppPluginServices and 0x0153f864 is the first-match output constant."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp",
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.hpp",
    "src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-lifecycle-wave7/007e6130.json"
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
  "AL 0/1",
  "AL 0/1 on the interior exit paths",
  "CONDITIONAL_JUMP"
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
