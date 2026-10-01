# Evidence 0x00febc90

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1a2018faa28fdd4050d79bf09cc5edf66862ef2f0ea99225aeecfa0c9bb66277`

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
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
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
  "content_sha256": "019dacd79d9072a4815d044e10f49ead3485401330d93a671231ea5865b902fb",
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
        "obs-0011"
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
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          52,
          56
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0011"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0011"
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
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011"
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
      "at": "0x00febc90",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00febc91",
      "count": 3,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ECX + 0x38]",
      "reg": "ECX"
    },
    {
      "at": "0x00febc91",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ECX + 0x38]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00febc97",
      "definite": true,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0x92492493",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x00febc9e",
      "count": 1,
      "first_use": 5,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00febc9e",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0006",
      "index": 5,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00febca2",
      "definite": true,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "ADD EDX,ESI",
      "reg": "EDX",
      "write_kind": "arith"
    },
    {
      "at": "0x00febca4",
      "count": 7,
      "first_use": 7,
      "first_write_index": 6,
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_READ",
      "raw": "SAR EDX,0x5",
      "reg": "EDX"
    },
    {
      "at": "0x00febcb2",
      "count": 6,
      "first_use": 13,
      "first_write_index": 3,
      "id": "obs-0009",
      "index": 13,
      "kind": "REG_READ",
      "raw": "XOR AL,AL",
      "reg": "EAX"
    },
    {
      "at": "0
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
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
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
  "content_sha256": "019dacd79d9072a4815d044e10f49ead3485401330d93a671231ea5865b902fb",
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
        "obs-0011"
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
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          52,
          56
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0011"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0011"
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
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011"
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
      "at": "0x00febc90",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00febc91",
      "count": 3,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ECX + 0x38]",
      "reg": "ECX"
    },
    {
      "at": "0x00febc91",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ECX + 0x38]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00febc97",
      "definite": true,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0x92492493",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x00febc9e",
      "count": 1,
      "first_use": 5,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00febc9e",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0006",
      "index": 5,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00febca2",
      "definite": true,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "ADD EDX,ESI",
      "reg": "EDX",
      "write_kind": "arith"
    },
    {
      "at": "0x00febca4",
      "count": 7,
      "first_use": 7,
      "first_write_index": 6,
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_READ",
      "raw": "SAR EDX,0x5",
      "reg": "EDX"
    },
    {
      "at": "0x00febcb2",
      "count": 6,
      "first_use": 13,
      "first_write_index": 3,
      "id": "obs-0009",
      "index": 13,
      "kind": "REG_READ",
      "raw": "XOR AL,AL",
      "reg": "EAX"
    },
    {
      "at": "0
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
    "va": "0x00feed30"
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
      "address": "00febc90",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00febc91",
      "instruction": "MOV ESI,dword ptr [ECX + 0x38]"
    },
    {
      "address": "00febc94",
      "instruction": "SUB ESI,dword ptr [ECX + 0x34]"
    },
    {
      "address": "00febc97",
      "instruction": "MOV EAX,0x92492493"
    },
    {
      "address": "00febc9c",
      "instruction": "IMUL ESI"
    },
    {
      "address": "00febc9e",
      "instruction": "MOV EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00febca2",
      "instruction": "ADD EDX,ESI"
    },
    {
      "address": "00febca4",
      "instruction": "SAR EDX,0x5"
    },
    {
      "address": "00febca7",
      "instruction": "MOV ESI,EDX"
    },
    {
      "address": "00febca9",
      "instruction": "SHR ESI,0x1f"
    },
    {
      "address": "00febcac",
      "instruction": "ADD ESI,EDX"
    },
    {
      "address": "00febcae",
      "instruction": "CMP EAX,ESI"
    },
    {
      "address": "00febcb0",
      "instruction": "JL 0x00febcb8"
    },
    {
      "address": "00febcb2",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00febcb4",
      "instruction": "POP ESI"
    },
    {
      "address": "00febcb5",
      "instruction": "RET 0x8"
    },
    {
      "address": "00febcb8",
      "instruction": "LEA EDX,[EAX*0x8 + 0x0]"
    },
    {
      "address": "00febcbf",
      "instruction": "SUB EDX,EAX"
    },
    {
      "address": "00febcc1",
      "instruction": "MOV EAX,dword ptr [ECX + 0x34]"
    },
    {
      "address": "00febcc4",
      "instruction": "MOV ESI,dword ptr [EAX + EDX*0x8 + 0xc]"
    },
    {
      "address": "00febcc8",
      "instruction": "SUB ESI,dword ptr [EAX + EDX*0x8 + 0x8]"
    },
    {
      "address": "00febccc",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00febccd",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00febcce",
      "instruction": "LEA EDI,[EAX + EDX*0x8]"
    },
    {
      "address": "00febcd1",
      "instruction": "SAR ESI,0x2"
    },
    {
      "address": "00febcd4",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00febcd6",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00febcd8",
      "instruction": "JLE 0x00febd03"
    },
    {
      "address": "00febcda",
      "instruction": "LEA EBX,[EBX]"
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
        "same_package",
        "same_class",
        "shared_types:MissionManagerWire"
      ],
      "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
      "score": 16,
      "symbol": "mission_manager_operation_00fee310",
      "va": "0x00fee310"
    },
    {
      "match_basis": [
        "same_class",
        "shared_types:MissionManagerWire,Opaque"
      ],
      "package": "PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2",
      "score": 11,
      "symbol": "mission_manager_record_init_00fec3c0",
      "va": "0x00fec3c0"
    },
    {
      "match_basis": [
        "same_package"
      ],
      "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
      "score": 8,
      "symbol": "achievement_progress_update_00676e90",
      "va": "0x00676e90"
    },
    {
      "match_basis": [
        "shared_types:Opaque"
      ],
      "package": "PKG-18-UI-SPACE",
      "score": 3,
      "symbol": "pkg18_text_zoom_rebind_00834fa0",
      "va": "0x00834fa0"
    },
    {
      "match_basis": [
        "shared_types:Opaque"
      ],
      "package": "PKG-UTFWIN-LAYOUT-WAVE6",
      "score": 3,
      "symbol": "pkg_utfwin_layout_wave6_00967e80",
      "va": "0x00967e80"
    },
    {
      "match_basis": [
        "shared_types:Opaque"
      ],
      "package": "PKG-UTFWIN-EFFECTS-WAVE6",
      "score": 3,
      "symbol": "utfwin_0096ffc0",
      "va": "0x0096ffc0"
    },
    {
      "match_basis": [
        "shared_types:Opaque"
      ],
      "package": "PKG-UTFWIN-EFFECTS-WAVE6",
      "score": 3,
      "symbol": "utfwin_0097e550",
      "va": "0x0097e550"
    },
    {
      "match_basis": [
        "shared_types:Opaque"
      ],
      "package": "PKG-UTFWIN-EFFECTS-WAVE6",
      "score": 3,
      "symbol": "utfwin_0097e890",
      "va": "0x0097e890"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": "clean",
  "blocked": false,
  "blockers": [
    "No original-process identity/score trace was run.",
    "The identity concrete type and 0x00c317a0 score semantics remain opaque; no release is claimed."
  ],
  "body_status": "integrated",
  "class_type": "MissionManagerWire",
  "cluster": null,
  "confidence": null,
  "dependencies": {
    "callees": [],
    "callees_truncated": false,
    "callers": [
      {
        "name": null,
        "reconstructed": false,
        "va": "0x00feed30"
      }
    ],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x00feefc2",
        "direction": "in",
        "other": "0x00feed30",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 1,
    "fan_out": 0,
    "manifest_callees": [
      "0x01002bd0",
      "0x00bfc5f0",
      "0x00fe4180",
      "0x01021300",
      "0x00c317a0"
    ],
    "manifest_callers": [
      "0x00feed30"
    ],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0584",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "SUPPORTED",
  "globals": [],
  "integration_status": "integrated",
  "name": "mission_track_predicate_00febc90",
  "normalized_symbol": "mission_track_predicate_00febc90",
  "observed_mechanics": [],
  "ownership": {
    "claimability": "do_not_claim",
    "handoff_packages": [
      "PKG-11-A2-PROGRESSION-ALTERNATIVE"
    ],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
    "queue_state": null
  },
  "package": "PKG-11-A2-PROGRESSION-ALTERNATIVE",
  "reconstructed": true,
  "review_status": "approved",
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "gate-mission-track-decision-00febc90",
      "runtime validation not run"
    ],
    "validated": 0
  },
  "runtime_gated": true,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": "static_reconstruction_metadata_only",
  "services": [],
  "source": {
    "decomp": null,
    "file": "src/reconstruction/pkg11_a2_progression_alt/progression_alt.cpp",
    "files": [
      "reconstruction/staging/pkg11-a2-progression-alt/progression_alt.cpp",
      "reconstruction/staging/pkg11-a2-progression-alt/progression_alt.hpp",
      "src/reconstruction/pkg11_a2_progression_alt/progression_alt.cpp",
      "src/reconstruction/pkg11_a2_progression_alt/progression_alt.hpp",
      "src/reconstruction/pkg11_a2_progression_alt/progression_alt_model_test.cpp"
    ],
    "handoffs": [
      "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json"
    ],
    "metadata": [
      "reconstruction/metadata/pkg11-a2-progression-alt/00febc90.json"
    ],
    "provenance": [
      "ghidra_disassemble_bytes",
      "ghidra_disassemble_function",
      "ghidra_disassemble_function:0x00bfc5f0",
      "ghidra_disassemble_function:0x00c317a0",
      "ghidra_disassemble_function:0x00fe4180",
      "ghidra_get_assembly_context",
      "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json",
      "reconstruction/metadata/pkg11-a2-progression-alt/00676e90.json",
      "reconstruction/metadata/pkg11-a2-progression-alt/00febc90.json",
      "reconstruction/metadata/pkg11-a2-progression-alt/00fee310.json"
    ]
  },
  "status": "reconstructed",
  "subsystem": "Simulator.MissionTracking",
  "triage": null,
  "types": [
    "MissionManagerWire",
    "MissionTrackRecordStorage",
    "Opaque",
    "opaque 32-bit identity/borrowed target",
    "std::int32_t"
  ],
  "unresolved_questions": [],
  "va": "0x00febc90",
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
  "body_end": "00febcdf",
  "body_span_bytes": 80,
  "body_start": "00febc90",
  "callees": [],
  "callers": [
    "FUN_00feed30"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00febc90",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00febc90",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xbebc90",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00febc90(void)",
  "size_bytes": 80,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00febc90",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00feefc2"
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
  "file": "src/reconstruction/pkg11_a2_progression_alt/progression_alt.cpp",
  "files": [
    "reconstruction/staging/pkg11-a2-progression-alt/progression_alt.cpp",
    "reconstruction/staging/pkg11-a2-progression-alt/progression_alt.hpp",
    "src/reconstruction/pkg11_a2_progression_alt/progression_alt.cpp",
    "src/reconstruction/pkg11_a2_progression_alt/progression_alt.hpp",
    "src/reconstruction/pkg11_a2_progression_alt/progression_alt_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-a2-progression-alt/00febc90.json"
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
    "gate-mission-track-decision-00febc90",
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
  "MissionManagerWire",
  "MissionTrackRecordStorage",
  "Opaque",
  "opaque 32-bit identity/borrowed target",
  "std::int32_t"
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
