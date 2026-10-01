# Evidence 0x00fa5580

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5296af5b263f08d2ea04ecad39f0196c2c1d138e3d7572ff227f327e8b1634e3`

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
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_semantics": "one byte in AL; bits 8..31 of EAX are whatever the last full-register write left there and differ per path (see mechanics.return_word)",
  "return_type": "std::uint8_t",
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "70af322ec93f0a6a3d2a7766772df2f824c372fe22b249b38ef4a9431271c893",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0018",
        "obs-0024"
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
        "obs-0013"
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
        "obs-0003",
        "obs-0004",
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          1944,
          1948
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0009",
        "obs-0018",
        "obs-0024"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0018",
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
        "obs-0018",
        "obs-0024"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018",
        "obs-0024"
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
      "at": "0x00fa5580",
      "count": 1,
      "first_use": 0,
      "first_write_index": 16,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00fa5581",
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
      "at": "0x00fa5582",
      "count": 5,
      "first_use": 2,
      "first_write_index": 11,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00fa5582",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00fa5584",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ESI + 0x79c]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00fa5590",
      "definite": true,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0x2fa0be83",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x00fa5597",
      "count": 6,
      "first_use": 7,
      "first_write_index": 3,
      "id": "obs-0007",
      "index": 7,
      "kind": "REG_READ",
      "raw": "SAR EDX,0x5",
      "reg": "EDX"
    },
    {
      "at": "0x00fa559c",
      "count": 4,
      "first_use": 9,
      "first_write_index": 5,
      "id": "obs-0008",
      "index": 9,
      "kind": "REG_READ",
      "raw": "SHR EAX,0x1f",
      "reg": "EAX"
    },
    {
      "at": "0x00fa55a1",
      "definite": true,
      "id": "obs-0009",
      "index": 11,
      "kind": "REG_WRITE",
      "raw": "XOR ECX,ECX",
   
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
  "count": 46,
  "instructions": [
    {
      "address": "00fa5580",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00fa5581",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00fa5582",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00fa5584",
      "instruction": "MOV EDX,dword ptr [ESI + 0x79c]"
    },
    {
      "address": "00fa558a",
      "instruction": "SUB EDX,dword ptr [ESI + 0x798]"
    },
    {
      "address": "00fa5590",
      "instruction": "MOV EAX,0x2fa0be83"
    },
    {
      "address": "00fa5595",
      "instruction": "IMUL EDX"
    },
    {
      "address": "00fa5597",
      "instruction": "SAR EDX,0x5"
    },
    {
      "address": "00fa559a",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "00fa559c",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "00fa559f",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "00fa55a1",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00fa55a3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00fa55a4",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00fa55a6",
      "instruction": "JLE 0x00fa55c7"
    },
    {
      "address": "00fa55a8",
      "instruction": "MOV EDI,dword ptr [ESI + 0x798]"
    },
    {
      "address": "00fa55ae",
      "instruction": "MOV EBX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00fa55b2",
      "instruction": "LEA EDX,[EDI + 0xa8]"
    },
    {
      "address": "00fa55b8",
      "instruction": "CMP dword ptr [EDX],EBX"
    },
    {
      "address": "00fa55ba",
      "instruction": "JZ 0x00fa55cf"
    },
    {
      "address": "00fa55bc",
      "instruction": "INC ECX"
    },
    {
      "address": "00fa55bd",
      "instruction": "ADD EDX,0xac"
    },
    {
      "address": "00fa55c3",
      "instruction": "CMP ECX,EAX"
    },
    {
      "address": "00fa55c5",
      "instruction": "JL 0x00fa55b8"
    },
    {
      "address": "00fa55c7",
      "instruction": "POP EDI"
    },
    {
      "address": "00fa55c8",
      "instruction": "POP ESI"
    },
    {
      "address": "00fa55c9",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00fa55cb",
      "instruction": "POP EBX"
    },
    {
      "address": "00fa55cc",
      "instruction": "RET 0x4"
    },
    {
      "address": "00fa55cf",
      "instruction": "MOV EDX,dword ptr [ESI + 0x79c]"
    },
    {
      "address": "00fa55d5",
      "instruction": "IMUL ECX,ECX,0xac"
    },
    {
      "address": "00fa55db",
      "instruction": "ADD ECX,EDI"
    },
    {
      "address": "00fa55dd",
      "instruction": "LEA EAX,[ECX + 0xac]"
    },
    {
      "address": "00fa55e3",
      "instruction": "CMP EAX,EDX"
    },
    {
      "address": "00fa55e5",
      "instruction": "JNC 0x00fa55f2"
    },
    {
      "address": "00fa55e7",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00fa55e8",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00fa55e9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00fa55ea",
      "instruction": "CALL 0x00f9f770"
    },
    {
      "address": "00fa55ef",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00fa55f2",
      "instruction": "ADD dword ptr [ESI + 0x79c],0xffffff54"
    },
    {
      "address": "00fa55fc",
      "instruction": "POP EDI"
    },
    {
      "address": "00fa55fd",
      "instruction": "POP ESI"
    },
    {
      "address": "00fa55fe",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00fa5600",
      "instruction": "POP EBX"
    },
    {
      "address": "00fa5601",
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
  "original_bytes": 7881,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"one byte in AL; bits 8..31 of EAX are whatever the last full-register write left there and differ per path (see mechanics.return_word)\",\n    \"return_type\": \"std::uint8_t\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00fa55ea\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f9f770\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0578\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00fa5580\",\n  \"normalized_symbol\": \"FUN_00fa5580\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w1-00fa5580/swarm_w1_00fa5580.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00fa5580/swarm_w1_00fa5580_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00fa5580/swarm_w1_00fa5580_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w1-00fa5580/00fa5580.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Sporepedia\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sporepedia-online\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00fa5580\",\n    \"name\": \"FUN_00fa5580\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\n      \"vtable_addrs\": [\n        \"01490be8\"\n      ]\n    },\n    \"queue_state\": \"candidate\",\n    \"rank\": 284\n  },\n  \"types\": [\n    \"std::uint8_t\"\n  ],\n  \"unresolved_questions\": [\n    \"The only return claim any record carries for this VA is the machine-vocabulary phrase return_semantics 'integral_in_EAX', with return_register EAX and NO return_type field anywhere. That is not a C type, so the va
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
  "body_end": "00fa5603",
  "body_span_bytes": 132,
  "body_start": "00fa5580",
  "callees": [
    "FUN_00f9f770"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00fa5580",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00fa5580",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xba5580",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00fa5580(void)",
  "size_bytes": 132,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00fa5580",
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
      "from": "01490c50"
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
    "reconstruction/staging/pkg-swarm-w1-00fa5580/swarm_w1_00fa5580.cpp",
    "reconstruction/staging/pkg-swarm-w1-00fa5580/swarm_w1_00fa5580_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00fa5580/swarm_w1_00fa5580_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00fa5580/00fa5580.json"
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
