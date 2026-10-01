# Evidence 0x00ec3be0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `bcc8383bcf8c83b980d9d12f12245f2962c3ff322cbee4a2dbd9c399efde207d`

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
  "return_note": "the machine ABI envelope (abi_derived.return) names EAX as the return register, classifies its register_class as aggregate_unknown and sets void_possible false, and evidence_returns therefore reports UNCLASSIFIED for this body rather than a void; the declared void here rests on the listing instead -- no path writes EAX immediately before a terminator for the purpose of returning it, and Ghidra's decompilation is `void __thiscall FUN_00ec3be0(int,uint *)` with five bare `return;` statements. What the machine does leave in EAX is incidental and path-dependent: the callee's return where no arm...",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "EDI",
    "ESI"
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
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
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
    "flow_not_modelled: the linear ESP walk ends at -28, so the listing is not one path"
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
  "content_sha256": "79126110f56e342932b948e2dcaa6494908dd6f120f7fac0dfd24835aa5c2d2c",
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
        "obs-0012",
        "obs-0016",
        "obs-0020",
        "obs-0023",
        "obs-0026"
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
        "obs-0007"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          120,
          121,
          122,
          123,
          124
        ],
        "register": "ECX",
        "written_through": 5
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0012",
        "obs-0016",
        "obs-0020",
        "obs-0023",
        "obs-0026"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0012",
        "obs-0016",
        "obs-0020",
        "obs-0023",
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
        "obs-0012",
        "obs-0016",
        "obs-0020",
        "obs-0023",
        "obs-0026"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0012",
        "obs-0016",
        "obs-0020",
        "obs-0023",
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
      "at": "0x00ec3be0",
      "count": 13,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00ec3be1",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00ec3be1",
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
      "at": "0x00ec3be1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00ec3be5",
      "count": 6,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00ec3be7",
      "count": 1,
      "first_use": 4,
      "first_write_index": 23,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00ec3be7",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
    
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
  "count": 58,
  "instructions": [
    {
      "address": "00ec3be0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ec3be1",
      "instruction": "MOV ESI,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00ec3be5",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ec3be6",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ec3be7",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00ec3be9",
      "instruction": "CALL 0x00642530"
    },
    {
      "address": "00ec3bee",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00ec3bf0",
      "instruction": "CMP EAX,0x5a3584a7"
    },
    {
      "address": "00ec3bf5",
      "instruction": "JA 0x00ec3c34"
    },
    {
      "address": "00ec3bf7",
      "instruction": "JZ 0x00ec3c1c"
    },
    {
      "address": "00ec3bf9",
      "instruction": "CMP EAX,0x15e8afc8"
    },
    {
      "address": "00ec3bfe",
      "instruction": "JNZ 0x00ec3c8c"
    },
    {
      "address": "00ec3c04",
      "instruction": "CMP dword ptr [ESI + 0x4],0x2e1a75d"
    },
    {
      "address": "00ec3c0b",
      "instruction": "JNZ 0x00ec3c8c"
    },
    {
      "address": "00ec3c0d",
      "instruction": "CMP dword ptr [ESI + 0x8],0x1"
    },
    {
      "address": "00ec3c11",
      "instruction": "SETZ AL"
    },
    {
      "address": "00ec3c14",
      "instruction": "MOV byte ptr [EDI + 0x78],AL"
    },
    {
      "address": "00ec3c17",
      "instruction": "POP EDI"
    },
    {
      "address": "00ec3c18",
      "instruction": "POP ESI"
    },
    {
      "address": "00ec3c19",
      "instruction": "RET 0x4"
    },
    {
      "address": "00ec3c1c",
      "instruction": "CMP dword ptr [ESI + 0x4],0x2e1a75d"
    },
    {
      "address": "00ec3c23",
      "instruction": "JNZ 0x00ec3c8c"
    },
    {
      "address": "00ec3c25",
      "instruction": "CMP dword ptr [ESI + 0x8],0x1"
    },
    {
      "address": "00ec3c29",
      "instruction": "SETZ CL"
    },
    {
      "address": "00ec3c2c",
      "instruction": "MOV byte ptr [EDI + 0x79],CL"
    },
    {
      "address": "00ec3c2f",
      "instruction": "POP EDI"
    },
    {
      "address": "00ec3c30",
      "instruction": "POP ESI"
    },
    {
      "address": "00ec3c31",
      "instruction": "RET 0x4"
    },
    {
      "address": "00ec3c34",
      "instruction": "CMP EAX,0xb91fba14"
    },
    {
      "address": "00ec3c39",
      "instruction": "JZ 0x00ec3c79"
    },
    {
      "address": "00ec3c3b",
      "instruction": "CMP EAX,0xd22f5e35"
    },
    {
      "address": "00ec3c40",
      "instruction": "JZ 0x00ec3c61"
    },
    {
      "address": "00ec3c42",
      "instruction": "CMP EAX,0xdb4675dd"
    },
    {
      "address": "00ec3c47",
      "instruction": "JNZ 0x00ec3c8c"
    },
    {
      "address": "00ec3c49",
      "instruction": "CMP dword ptr [ESI + 0x4],0x2e1a75d"
    },
    {
      "address": "00ec3c50",
      "instruction": "JNZ 0x00ec3c8c"
    },
    {
      "address": "00ec3c52",
      "instruction": "CMP dword ptr [ESI + 0x8],0x1"
    },
    {
      "address": "00ec3c56",
      "instruction": "SETZ DL"
    },
    {
      "address": "00ec3c59",
      "instruction": "MOV byte ptr [EDI + 0x7c],DL"
    },
    {
      "address": "00ec3c5c",
      "instruction": "POP EDI"
    },
    {
      "address": "00ec3c5d",
      "instruction": "POP ESI"
    },
    {
      "address": "00ec3c5e",
      "instruction": "RET 0x4"
    },
    {
      "address": "00ec3c61",
      "instruction": "CMP dword ptr [ESI + 0x4],0x2e1a75d"
    },
    {
      "address": "00ec3c68",
      "instruction": "JNZ 0x00ec3c8c"
    },
    {
      "address": "00ec3c6a",
      "instruction": "CMP dword ptr [ESI + 0x8],0x1"
    },
    {
      "address": "00ec3c6e",
      "instruction": "SETZ AL"
    },
    {
      "address": "00ec3c71",
      "instruction": "MOV byte ptr [EDI + 0x7b],AL"
    },
    {
      "address": "00ec3c74",
      "instruction": "POP EDI"
    },
    {
      "address": "00ec3c75",
      "instruction": "POP ESI"
    },
    {
      "address": "00ec3c76",
      "instruction": "RET 0x4"
    },
    {
      "address": "00ec3c79",
      "instruction": "CMP dword ptr [ESI + 0x4],0x2e1a75d"
    },
    {
      "address": "00ec3c80",
      "instruction": "JNZ 0x00ec3c8c"
    },
    {
      "address": "00ec3c82",
      "instruction": "CMP dword ptr [ESI + 0x8],0x1"
    },
    {
      "address": "00ec3c86",
      "instruction": "SETZ CL"
    },
    {
      "address": "00ec3c89",
      "instruction": "MOV byte ptr [EDI + 0x7a],CL"
    },
    {
      "address": "00ec3c8c",
      "instruction": "POP EDI"
    },
    {
      "address": "00ec3c8d",
      "instruction": "POP ESI"
    },
    {
      "address": "00ec3c8e",
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
  "original_bytes": 9514,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_note\": \"the machine ABI envelope (abi_derived.return) names EAX as the return register, classifies its register_class as aggregate_unknown and sets void_possible false, and evidence_returns therefore reports UNCLASSIFIED for this body rather than a void; the declared void here rests on the listing instead -- no path writes EAX immediately before a terminator for the purpose of returning it, and Ghidra's decompilation is `void __thiscall FUN_00ec3be0(int,uint *)` with five bare `return;` statements. What the machine does leave in EAX is incidental and path-dependent: the callee's return where no arm...\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014890f4\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014890f4\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00ec3be9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00642530\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0564\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00ec3be0\",\n  \"normalized_symbol\": \"FUN_00ec3be0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w1-00ec3be0/00ec3be0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Sporepedia\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sporepedia-online\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00ec3be0\",\n    \"name\": \"FUN_00ec3be0\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\
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
  "body_end": "00ec3c90",
  "body_span_bytes": 177,
  "body_start": "00ec3be0",
  "callees": [
    "FUN_00642530"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ec3be0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00ec3be0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xac3be0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ec3be0(void)",
  "size_bytes": 177,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ec3be0",
  "vtables": {
    "referenced_by_vtables": [
      "0x014890f4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01489144"
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
    "reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00ec3be0/sw1_00ec3be0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00ec3be0/00ec3be0.json"
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
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x014890f4"
]
```

## Conflicts

```json
[]
```
