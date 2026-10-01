# Evidence 0x00fec3c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `fe5fc2027b46ac41c7909963d09d57313b0ab8cc8ad47465e85815d556468299`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EBX",
      "ESI"
    ],
    "stack_arguments": [
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "slot_width_ambiguous: one entry slot is read at more than one width",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "d49d28f2dd0254fda4c5f7562bda280704dce27b02611e0822a666b13b5140c6",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0027"
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
        "obs-0012",
        "obs-0015",
        "obs-0017",
        "obs-0022",
        "obs-0023"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0012",
        "obs-0015",
        "obs-0017",
        "obs-0022",
        "obs-0023"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0014",
        "obs-0015"
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
        "obs-0009",
        "obs-0014",
        "obs-0015"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
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
      "at": "0x00fec3c0",
      "count": 1,
      "first_use": 0,
      "first_write_index": 19,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00fec3c1",
      "count": 6,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00fec3c2",
      "count": 6,
      "first_use": 2,
      "first_write_index": 22,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00fec3c2",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0004",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00fec3c2",
  
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
      "entry_ESP+0x4",
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EBX",
      "ESI"
    ],
    "stack_arguments": [
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "slot_width_ambiguous: one entry slot is read at more than one width",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "d49d28f2dd0254fda4c5f7562bda280704dce27b02611e0822a666b13b5140c6",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0027"
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
        "obs-0012",
        "obs-0015",
        "obs-0017",
        "obs-0022",
        "obs-0023"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0012",
        "obs-0015",
        "obs-0017",
        "obs-0022",
        "obs-0023"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0014",
        "obs-0015"
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
        "obs-0009",
        "obs-0014",
        "obs-0015"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
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
      "at": "0x00fec3c0",
      "count": 1,
      "first_use": 0,
      "first_write_index": 19,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00fec3c1",
      "count": 6,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00fec3c2",
      "count": 6,
      "first_use": 2,
      "first_write_index": 22,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00fec3c2",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0004",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00fec3c2",
  
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
  "count": 43,
  "instructions": [
    {
      "address": "00fec3c0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00fec3c1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00fec3c2",
      "instruction": "MOV ESI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00fec3c6",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00fec3c8",
      "instruction": "MOV EDX,dword ptr [EAX + 0x20]"
    },
    {
      "address": "00fec3cb",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00fec3cd",
      "instruction": "CALL EDX"
    },
    {
      "address": "00fec3cf",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00fec3d1",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00fec3d3",
      "instruction": "MOV EAX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "00fec3d6",
      "instruction": "MOV dword ptr [ESP + 0xc],0x1"
    },
    {
      "address": "00fec3de",
      "instruction": "CALL EAX"
    },
    {
      "address": "00fec3e0",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00fec3e2",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00fec3e4",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00fec3e8",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00fec3e9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00fec3ea",
      "instruction": "CALL 0x0093aa70"
    },
    {
      "address": "00fec3ef",
      "instruction": "MOV EDX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00fec3f3",
      "instruction": "MOV BL,byte ptr [EDX]"
    },
    {
      "address": "00fec3f5",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00fec3f7",
      "instruction": "MOV EDX,dword ptr [EAX + 0x20]"
    },
    {
      "address": "00fec3fa",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00fec3fd",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00fec3ff",
      "instruction": "AND BL,0x1"
    },
    {
      "address": "00fec402",
      "instruction": "CALL EDX"
    },
    {
      "address": "00fec404",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00fec406",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00fec408",
      "instruction": "MOV EAX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "00fec40b",
      "instruction": "CALL EAX"
    },
    {
      "address": "00fec40d",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00fec40f",
      "instruction": "LEA EDX,[ESP + 0x10]"
    },
    {
      "address": "00fec413",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "00fec415",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00fec416",
      "instruction": "SETNZ CL"
    },
    {
      "address": "00fec419",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00fec41a",
      "instruction": "MOV byte ptr [ESP + 0x18],CL"
    },
    {
      "address": "00fec41e",
      "instruction": "CALL 0x0093a9a0"
    },
    {
      "address": "00fec423",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00fec426",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00fec428",
      "instruction": "POP ESI"
    },
    {
      "address": "00fec429",
      "instruction": "POP EBX"
    },
    {
      "address": "00fec42a",
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
  "original_bytes": 6880,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:MissionManagerWire,Opaque\"\n      ],\n      \"package\": \"PKG-11-A2-PROGRESSION-ALTERNATIVE\",\n      \"score\": 11,\n      \"symbol\": \"mission_track_predicate_00febc90\",\n      \"va\": \"0x00febc90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"achievement_completion_boundary_00676710\",\n      \"va\": \"0x00676710\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"achievement_progress_flag_transition_00676ed0\",\n      \"va\": \"0x00676ed0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:MissionManagerWire\"\n      ],\n      \"package\": \"PKG-11-A2-PROGRESSION-ALTERNATIVE\",\n      \"score\": 8,\n      \"symbol\": \"mission_manager_operation_00fee310\",\n      \"va\": \"0x00fee310\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x00000018\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 4,\n      \"symbol\": \"app_system_service_gate_dispatch_007e5f30\",\n      \"va\": \"0x007e5f30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x00000020\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 4,\n      \"symbol\": \"app_canvas_get_message_server_00c871d0\",\n      \"va\": \"0x00c871d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Opaque\"\n      ],\n      \"package\": \"PKG-18-UI-SPACE\",\n      \"score\": 3,\n      \"symbol\": \"pkg18_text_zoom_rebind_00834fa0\",\n      \"va\": \"0x00834fa0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Opaque\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e80\",\n      \"va\": \"0x00967e80\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"No original-process record write trace was run.\",\n    \"The mission-manager attribution is carried from the wave brief and is not confirmed by any SDK or database symbol.\",\n    \"The record byte read from the second stack word is a single opaque byte; the structure behind that pointer is unresolved.\",\n    \"The virtual table at 0x01396a32 is built at runtime and its owning class is unresolved, so the slot index of 0x00feca60 is unknown.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"MissionManagerWire\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00fec41e\",\n        \"direction\": \"out\",\n        \"other\": \"0x0093a9a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fec3ea\",\n        \"direction\": \"out\",\n        \"other\": \"0x0093aa70\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x0093aa70\",\n      \"0x0093a9a0\"\n    ],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0585\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"mission_manager_record_init_00fec3c0\",\n  \"normalized_symbol\": \"mission_manager_record_init_00fec3c0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\"\n    ],\n    \"manifest\": {\n      \"record\": {\n        \"boundary\": \"No existing body record, staging source, integrated source, or test claims 0x00fec3c0. The forwarding stub at 0x00feca60 has no function in the database and is stored into a runtime-built virtual table at 0x01396a32, so the entry reconstructed here is the implementation body and not the table entry. Nothing in this package claims the stub or the table.\",\n        \"git_status_checked\": true,\n        \"integrated_handoffs_checked\": true,\n        \"manifest_checked\": true,\n        \"metadata_checked\": true,\n        \"staging_and_canonical_source_checked\": true,\n        \"status\": \"unowned_body_reached_only_through_a_vtable_forwarding_stub\"\n      },\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-mission-record-init-00fec3c0\",\n      \"runtime validation not run\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_metadata_exact_runtime_unresolved\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": \"src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.cpp\",\n    \"files\": [\n      \"reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.cpp\",\n      \
[TRUNCATED]
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "00fec42a",
  "body_span_bytes": 107,
  "body_start": "00fec3c0",
  "callees": [
    "FUN_0093aa70",
    "FUN_0093a9a0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00fec3c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00fec3c0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xbec3c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00fec3c0(void)",
  "size_bytes": 107,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00fec3c0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00feca6a"
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
  "file": "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.cpp",
    "reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.hpp",
    "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.cpp",
    "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.hpp",
    "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-a3-achievement-mission-wave2/00fec3c0.json"
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
    "gate-mission-record-init-00fec3c0",
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
  "Opaque",
  "const std::uint8_t*",
  "const void* vftable"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00000018",
  "vtable:0x00000020"
]
```

## Conflicts

```json
[]
```
