# Evidence 0x00f999e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `28680085b963bcd947bc5968062de1c305202bd3e1849a3a553a8d3715799404`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_note": "REPAIR rp10. return_type now states the type the source span declares and the listing proves (std::uint8_t, one byte), and the machine record's register-CLASSIFICATION was moved out of that field into return_semantics, where the phrase is kept verbatim. The phrase is a register class, not a C type, and the listing refutes it: XMM0 is written only by MOVSS, read only by UCOMISS, and left holding nothing on every path, while all three exits write AL only. No typedef named after the phrase exists or may be added. See return_semantics.record_disagreement and unresolved_questions item 1.",
  "return_register": "AL (one byte), a machine fact and not a modelling choice: all three exits write AL only. The machine record's own claim is XMM0; it is kept in return_semantics and its refutation in return_note.",
  "return_semantics": "float_or_x87_in_XMM0",
  "return_type": "std::uint8_t",
  "saved_registers": [
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -8, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "400dddf9fac1fc8a4ea6e77ba3ef633e85106c7bf91494c158460e81954304ef",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0010",
        "obs-0021",
        "obs-0024"
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
        "obs-0005",
        "obs-0006",
        "obs-0017",
        "obs-0018"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          880,
          1076,
          1080,
          1084,
          1088,
          1172,
          1176,
          1180,
          1184,
          1268
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0010",
        "obs-0017",
        "obs-0018",
        "obs-0021",
        "obs-0024"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0021",
        "obs-0024"
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
        "obs-0024"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00f999e0",
      "count": 16,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00f999e1",
      "count": 8,
      "first_use": 1,
      "first_write_index": 3,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00f999e1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00f999e3",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f48a70",
      "target": "0x00f48a70"
    },
    {
      "at": "0x00f999e8",
      "count": 4,
      "first_use": 3,
      "first_write_index": 7,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00f999e8",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00f999ea",
      "id": "obs-0007",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f699b0",
      "target": "0x00f699b0"
    },
    {
      "at": "0x00f999f3",
      "definite": true,
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "XOR AL,AL",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x00f999f5",
      "id": "obs-0009",
      "index": 8,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00f999f6",
      "form": "RET",
      "id": "obs-0010",
      "imm": null,
      "index": 9,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00f999f9",
      "definite": true,
      "id": "obs-0011",
      "index": 11,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x4c]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00f99a00",
      "count": 3,
      "first_use": 14,
      "first_write_index": 11,
      "id": "obs-0012",
      "index": 14,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00f99a00",
      "base": "EDX",
      "disp": null,
      "id": "obs-0013",
      "index": 14,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },

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
  "count": 80,
  "instructions": [
    {
      "address": "00f999e0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00f999e1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00f999e3",
      "instruction": "CALL 0x00f48a70"
    },
    {
      "address": "00f999e8",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00f999ea",
      "instruction": "CALL 0x00f699b0"
    },
    {
      "address": "00f999ef",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00f999f1",
      "instruction": "JNZ 0x00f999f7"
    },
    {
      "address": "00f999f3",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00f999f5",
      "instruction": "POP ESI"
    },
    {
      "address": "00f999f6",
      "instruction": "RET"
    },
    {
      "address": "00f999f7",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00f999f9",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4c]"
    },
    {
      "address": "00f999fc",
      "instruction": "PUSH 0x7"
    },
    {
      "address": "00f999fe",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f99a00",
      "instruction": "CALL EDX"
    },
    {
      "address": "00f99a02",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00f99a04",
      "instruction": "JNZ 0x00f999f3"
    },
    {
      "address": "00f99a06",
      "instruction": "CMP byte ptr [ESI + 0x370],AL"
    },
    {
      "address": "00f99a0c",
      "instruction": "JNZ 0x00f999f3"
    },
    {
      "address": "00f99a0e",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00f99a10",
      "instruction": "MOV EDX,dword ptr [EAX + 0x30]"
    },
    {
      "address": "00f99a13",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f99a15",
      "instruction": "CALL EDX"
    },
    {
      "address": "00f99a17",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00f99a19",
      "instruction": "JZ 0x00f999f3"
    },
    {
      "address": "00f99a1b",
      "instruction": "CMP byte ptr [ESI + 0x4f4],0x0"
    },
    {
      "address": "00f99a22",
      "instruction": "JZ 0x00f999f3"
    },
    {
      "address": "00f99a24",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00f99a25",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00f99a27",
      "instruction": "ADD ESI,0x438"
    },
    {
      "address": "00f99a2d",
      "instruction": "LEA ECX,[ECX]"
    },
    {
      "address": "00f99a30",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00f99a32",
      "instruction": "LEA ECX,[ESI + 0xffffff40]"
    },
    {
      "address": "00f99a38",
      "instruction": "JMP 0x00f99a40"
    },
    {
      "address": "00f99a40",
      "instruction": "MOVSS XMM0,dword ptr [ECX + -0x4]"
    },
    {
      "address": "00f99a45",
      "instruction": "UCOMISS XMM0,dword ptr [ECX + 0x4]"
    },
    {
      "address": "00f99a49",
      "instruction": "LAHF"
    },
    {
      "address": "00f99a4a",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00f99a4d",
      "instruction": "JNP 0x00f99a5d"
    },
    {
      "address": "00f99a4f",
      "instruction": "MOVSS XMM0,dword ptr [ECX]"
    },
    {
      "address": "00f99a53",
      "instruction": "UCOMISS XMM0,dword ptr [ECX + 0x8]"
    },
    {
      "address": "00f99a57",
      "instruction": "LAHF"
    },
    {
      "address": "00f99a58",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00f99a5b",
      "instruction": "JP 0x00f99aaf"
    },
    {
      "address": "00f99a5d",
      "instruction": "INC EDX"
    },
    {
      "address": "00f99a5e",
      "instruction": "ADD ECX,0x60"
    },
    {
      "address": "00f99a61",
      "instruction": "CMP EDX,0x2"
    },
    {
      "address": "00f99a64",
      "instruction": "JL 0x00f99a40"
    },
    {
      "address": "00f99a66",
      "instruction": "MOVSS XMM0,dword ptr [ESI + -0x4]"
    },
    {
      "address": "00f99a6b",
      "instruction": "UCOMISS XMM0,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00f99a6f",
      "instruction": "LAHF"
    },
    {
      "address": "00f99a70",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00f99a73",
      "instruction": "JNP 0x00f99a83"
    },
    {
      "address": "00f99a75",
      "instruction": "MOVSS XMM0,dword ptr [ESI]"
    },
    {
      "address": "00f99a79",
      "instruction": "UCOMISS XMM0,dword ptr [ESI + 0x8]"
    },
    {
      "address": "00f99a7d",
      "instruction": "LAHF"
    },
    {
      "address": "00f99a7e",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00f99a81",
      "instruction": "JP 0x00f99aaf"
    },
    {
      "address": "00f99a83",
      "instruction": "MOVSS XMM0,dword ptr [ESI + 0x5c]"
    },
    {
      "address": "00f99a88",
      "instruction": "UCOMISS XMM0,dword ptr [ESI + 0x64]"
    },
    {
      "address": "00f99a8c",
      "instruction": "LAHF"
    },
    {
      "address": "00f99a8d",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00f99a90",
      "instruction": "JNP 0x00f99aa1"
    },
    {
      "address": "00f99a92",
      "instruction": "MOVSS XMM0,dword ptr [ESI + 0x60]"
    },
    {
      "address": "00f99a97",
      "instruction": "UCOMISS XMM0,dword ptr [ESI + 0x68]"
    },
    {
      "address": "00f99a9b",
      "instruction": "LAHF"
    },
    {
      "address": "00f99a9c",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00f99a9f",
      "instruction": "JP 0x00f99aaf"
    },
    {
      "address": "00f99aa1",
      "instruction": "INC EDI"
    },
    {
      "address": "00f99aa2",
      "instruction": "ADD ESI,0x10"
    },
    {
      "address": "00f99aa5",
      "instruction": "CMP EDI,0x6"
    },
    {
      "address": "00f99aa8",
      "instruction": "JL 0x00f99a30"
    },
    {
      "address": "00f99aaa",
      "instruction": "POP EDI"
    },
 
[TRUNCATED]
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
  "original_bytes": 11742,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_note\": \"REPAIR rp10. return_type now states the type the source span declares and the listing proves (std::uint8_t, one byte), and the machine record's register-CLASSIFICATION was moved out of that field into return_semantics, where the phrase is kept verbatim. The phrase is a register class, not a C type, and the listing refutes it: XMM0 is written only by MOVSS, read only by UCOMISS, and left holding nothing on every path, while all three exits write AL only. No typedef named after the phrase exists or may be added. See return_semantics.record_disagreement and unresolved_questions item 1.\",\n    \"return_register\": \"AL (one byte), a machine fact and not a modelling choice: all three exits write AL only. The machine record's own claim is XMM0; it is kept in return_semantics and its refutation in return_note.\",\n    \"return_semantics\": \"float_or_x87_in_XMM0\",\n    \"return_type\": \"std::uint8_t\",\n    \"saved_registers\": [\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00f999e3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f48a70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f999ea\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f699b0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0572\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:0x016c8eb0\",\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00f999e0\",\n  \"normalized_symbol\": \"FUN_00f999e0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w2-00f999e0/00f999e0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Sporepedia\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sporepedia-online\",\n    \"db_triage_
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
  "body_end": "00f99ab3",
  "body_span_bytes": 212,
  "body_start": "00f999e0",
  "callees": [
    "FUN_00f48a70",
    "FUN_00f699b0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00f999e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00f999e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xb999e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00f999e0(void)",
  "size_bytes": 212,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00f999e0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01490be8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01490c38"
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
  "global:0x016c8eb0",
  "global:PASS"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0.cpp",
    "reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00f999e0/00f999e0.json"
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "Real -- float, binary32, because MOVSS and UCOMISS each read four bytes",
  "Receiver -- an opaque byte run, one unnamed array, no member named anywhere in this package (the machine-derived receiver record is bounds_only)",
  "SlotFirst -- Word (__thiscall *)(Receiver*, std::uint8_t), the shape of the table word at slot +0x4c, the one word it takes being callee-popped",
  "SlotSecond -- Word (__thiscall *)(Receiver*), the shape of the table word at slot +0x30, taking no word",
  "Word -- std::uint32_t, a 32-bit table entry and a 32-bit receiver word",
  "std::uint8_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01490be8"
]
```

## Conflicts

```json
[]
```
