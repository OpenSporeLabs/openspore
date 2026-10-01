# Evidence 0x00a85790

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5395c2ce654727dd178e8c4cb6a48244933caa2e7299b2d79c6239539ffe4bc7`

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
  "return_note": "unclassified_in_EAX (machine-vocabulary phrase; see return_semantics)",
  "return_register": "EAX",
  "saved_registers": [
    "ESI",
    "EDI (conditionally: only across the 0x00a85815 call)"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "0x00a85839 RET 0x4"
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
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
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
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path"
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
  "content_sha256": "de433887b5a3988336cbc4b5fa357953ecf0bedc4587280fd12e7ff22579248e",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017"
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
        "obs-0017"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          12,
          16,
          20,
          104
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0006",
        "obs-0017"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0017"
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
        "obs-0017"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0017"
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
      "at": "0x00a85790",
      "count": 14,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00a85791",
      "count": 8,
      "first_use": 1,
      "first_write_index": 9,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00a85791",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00a857ab",
      "definite": true,
      "id": "obs-0004",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0xc]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00a857ae",
      "count": 12,
      "first_use": 8,
      "first_write_index": 7,
      "id": "obs-0005",
      "index": 8,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x8]",
      "reg": "EAX"
    },
    {
      "at": "0x00a857b1",
      "definite": true,
      "id": "obs-0006",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00a857bb",
      "definite": true,
      "id": "obs-0007",
      "index": 13,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,EAX",
      "reg": "EDX",
      "write_kind": "reg"
    },
    {
      "at": "0x00a857bd",
      "count": 7,
      "first_use": 14,
      "first_write_index": 13,
      "id": "obs-0008",
      "index": 14,
      "kind": "REG_READ",
      "raw": "SHR EDX,0x5",
      "reg": "EDX"
    },
    {
      "at": "0x00a857cb",
      "id": "obs-0009",
  
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
  "count": 64,
  "instructions": [
    {
      "address": "00a85790",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00a85791",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00a85793",
      "instruction": "CMP byte ptr [ESI + 0x14],0x0"
    },
    {
      "address": "00a85797",
      "instruction": "JZ 0x00a85838"
    },
    {
      "address": "00a8579d",
      "instruction": "CMP dword ptr [ESI + 0x10],0x0"
    },
    {
      "address": "00a857a1",
      "instruction": "MOV byte ptr [ESI + 0x14],0x0"
    },
    {
      "address": "00a857a5",
      "instruction": "JZ 0x00a85838"
    },
    {
      "address": "00a857ab",
      "instruction": "MOV EAX,dword ptr [ESI + 0xc]"
    },
    {
      "address": "00a857ae",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a857b1",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00a857b3",
      "instruction": "SHR ECX,0x3"
    },
    {
      "address": "00a857b6",
      "instruction": "TEST CL,0x1"
    },
    {
      "address": "00a857b9",
      "instruction": "JNZ 0x00a857c5"
    },
    {
      "address": "00a857bb",
      "instruction": "MOV EDX,EAX"
    },
    {
      "address": "00a857bd",
      "instruction": "SHR EDX,0x5"
    },
    {
      "address": "00a857c0",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "00a857c3",
      "instruction": "JZ 0x00a8581f"
    },
    {
      "address": "00a857c5",
      "instruction": "TEST AL,0x1"
    },
    {
      "address": "00a857c7",
      "instruction": "JZ 0x00a857d0"
    },
    {
      "address": "00a857c9",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00a857cb",
      "instruction": "CALL 0x00a85460"
    },
    {
      "address": "00a857d0",
      "instruction": "MOV EAX,dword ptr [ESI + 0xc]"
    },
    {
      "address": "00a857d3",
      "instruction": "MOV ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a857d6",
      "instruction": "SHR ECX,0x3"
    },
    {
      "address": "00a857d9",
      "instruction": "TEST CL,0x1"
    },
    {
      "address": "00a857dc",
      "instruction": "JZ 0x00a857e8"
    },
    {
      "address": "00a857de",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "00a857e1",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00a857e3",
      "instruction": "MOV EAX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "00a857e6",
      "instruction": "CALL EAX"
    },
    {
      "address": "00a857e8",
      "instruction": "MOV EAX,dword ptr [ESI + 0xc]"
    },
    {
      "address": "00a857eb",
      "instruction": "MOV ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a857ee",
      "instruction": "MOV EDX,ECX"
    },
    {
      "address": "00a857f0",
      "instruction": "SHR EDX,0x5"
    },
    {
      "address": "00a857f3",
      "instruction": "TEST DL,0x1"
    },
    {
      "address": "00a857f6",
      "instruction": "JZ 0x00a8581f"
    },
    {
      "address": "00a857f8",
      "instruction": "MOVZX EAX,word ptr [EAX + 0xa8]"
    },
    {
      "address": "00a857ff",
      "instruction": "SHR ECX,0x6"
    },
    {
      "address": "00a85802",
      "instruction": "TEST CL,0x1"
    },
    {
      "address": "00a85805",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "00a85808",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00a8580a",
      "instruction": "MOV EDX,dword ptr [EDX + 0x1c]"
    },
    {
      "address": "00a8580d",
      "instruction": "JZ 0x00a8581a"
    },
    {
      "address": "00a8580f",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00a85810",
      "instruction": "LEA EDI,[ESI + 0x28]"
    },
    {
      "address": "00a85813",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00a85814",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00a85815",
      "instruction": "CALL EDX"
    },
    {
      "address": "00a85817",
      "instruction": "POP EDI"
    },
    {
      "address": "00a85818",
      "instruction": "JMP 0x00a8581f"
    },
    {
      "address": "00a8581a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00a8581c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00a8581d",
      "instruction": "CALL EDX"
    },
    {
      "address": "00a8581f",
      "instruction": "MOV EAX,dword ptr [ESI + 0x68]"
    },
    {
      "address": "00a85822",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00a85824",
      "instruction": "JL 0x00a85838"
    },
    {
      "address": "00a85826",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "00a85829",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00a8582b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00a8582c",
      "instruction": "MOV EAX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00a8582f",
      "instruction": "CALL EAX"
    },
    {
      "address": "00a85831",
      "instruction": "MOV dword ptr [ESI + 0x68],0xffffffff"
    },
    {
      "address": "00a85838",
      "instruction": "POP ESI"
    },
    {
      "address": "00a85839",
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
  "original_bytes": 9330,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_note\": \"unclassified_in_EAX (machine-vocabulary phrase; see return_semantics)\",\n    \"return_register\": \"EAX\",\n    \"saved_registers\": [\n      \"ESI\",\n      \"EDI (conditionally: only across the 0x00a85815 call)\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"0x00a85839 RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01458024\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 6,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01458024\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951230\",\n      \"va\": \"0x00951230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00a857cb\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a85460\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0337\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"FUN_00a85790\",\n  \"normalized_symbol\": \"FUN_00a85790\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w2-00a85790/sw2_00a85790.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00a85790/sw2_00a85790_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00a85790/sw2_00a85790_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w2-00a85790/00a85790.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Editor\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"editor-core\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00a85790\",\n    \"name\": \"FUN_00a85790\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b\",\n      \"vtable_addrs\": [\n        \"01458024\"\n      ]\n    },\n    \"queue_state\": \"candidate\",\n    \"rank\": 268\n  },\n  \"types\": [\n    \"PKG_SW2_00A85790_THISCALL\",\n    \"openspore::reconstruction::pkg_swarm_w2_00a85790::HalfWord\",\n    \"openspore::reconstruction::pkg_swarm_w2_00a85790::Receiver\",\n    \"openspore::reconstruction::pkg_swarm_w2_00a85790::SlotNoArgument\",\n    \"openspore::reconstruction::pkg_swarm_w2_00a85790::SlotOneArgument\",\n    \"openspore::reconstruction::pkg_swarm_w2_00a85790::SlotTwoArgume
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
  "body_end": "00a8583b",
  "body_span_bytes": 172,
  "body_start": "00a85790",
  "callees": [
    "FUN_00a85460"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00a85790",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00a85790",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x685790",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00a85790(void)",
  "size_bytes": 172,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00a85790",
  "vtables": {
    "referenced_by_vtables": [
      "0x01458024"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01458030"
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
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00a85790/sw2_00a85790.cpp",
    "reconstruction/staging/pkg-swarm-w2-00a85790/sw2_00a85790_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00a85790/sw2_00a85790_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00a85790/00a85790.json"
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
  "PKG_SW2_00A85790_THISCALL",
  "openspore::reconstruction::pkg_swarm_w2_00a85790::HalfWord",
  "openspore::reconstruction::pkg_swarm_w2_00a85790::Receiver",
  "openspore::reconstruction::pkg_swarm_w2_00a85790::SlotNoArgument",
  "openspore::reconstruction::pkg_swarm_w2_00a85790::SlotOneArgument",
  "openspore::reconstruction::pkg_swarm_w2_00a85790::SlotTwoArguments",
  "openspore::reconstruction::pkg_swarm_w2_00a85790::Word",
  "unclassified_in_EAX (machine-vocabulary phrase; see return_semantics)",
  "void -- chosen deliberately, and the disagreement with the canonical record is recorded in return_semantics and known_blockers rather than papered over. The single return site 0x00a85838 is reached from four directions and the word in EAX is a DIFFERENT unrelated value on each: the caller's own EAX on both early-exit paths (0x00a85797, 0x00a857a5, neither of which is preceded by an EAX write), the negative word just tested at 0x00a85824, and whatever the 0x00a8582f callee returned on the fallthrough. No path puts a value this function computed into EAX and no single value is consistent across paths, so the body produces no return value. Ghidra's own decompilation agrees in substance: signature `undefined FUN_00a85790(void)`, body ends in a bare `return;`, return_type_resolved false."
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01458024"
]
```

## Conflicts

```json
[]
```
