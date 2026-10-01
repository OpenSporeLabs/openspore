# Evidence 0x00c30c80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `813bf079e8f18cd580794966a7efe4c3ebe86a53d210426b5f6a06ef66713ad8`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "owner of the record id at +0xb0",
  "hidden_this_register": "ECX, read at 0x00c30c80",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x00c30ca3 XOR EAX,EAX is the only zero return; the other path is 0x00c30c9e JMP 0x00bba500, a tail transfer, so EAX comes straight from that function.",
  "return_register": "EAX",
  "return_semantics": "pointer to the resolved record, or 0 when the id is unset or unresolvable; otherwise the tail callee's result",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller (nothing is pushed at entry)",
  "termination": "0x00c30ca5 RET"
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
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "050cec4c6f09283c2dd2159fc736216da36eaee7509fefb82c109a6d220c705e",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0008"
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
        "obs-0001",
        "obs-0002",
        "obs-0005"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          176
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0005",
        "obs-0008"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0008"
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
        "obs-0007",
        "obs-0008"
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
        "obs-0008"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008"
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
      "at": "0x00c30c80",
      "count": 1,
      "first_use": 0,
      "first_write_index": 5,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0xb0]",
      "reg": "ECX"
    },
    {
      "at": "0x00c30c80",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0xb0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c30c8b",
      "count": 4,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00c30c8c",
      "id": "obs-0004",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d2a0",
      "target": "0x00b3d2a0"
    },
    {
      "at": "0x00c30c91",
      "definite": true,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c30c93",
      "id": "obs-0006",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00ba6d80",
      "target": "0x00ba6d80"
    },
    {
      "at": "0x00c30c9e",
      "id": "obs-0007",
      "index": 10,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x00bba500",
      "target": "0x00bba500"
    },
    {
      "at": "0x00c30ca5",
      "form": "RET",
      "id": "obs-0008",
      "imm": null,
      "index": 12,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 13,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 176,
    "offsets": [
      176
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "integral",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inferen
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
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
    "name": null,
    "reconstructed": false,
    "va": "0x00aebe90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba5bd3"
  },
  {
    "name": "EmpirePoliticalColor_00c32cd0",
    "reconstructed": true,
    "va": "0x00c32cd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c49140"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c49180"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c737a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cbc7f0"
  },
  {
    "name": "DiplomacyTransition_00d065a0",
    "reconstructed": true,
    "va": "0x00d065a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e1bbc0"
  },
  {
    "name": "FUN_00e39ab0",
    "reconstructed": false,
    "va": "0x00e39ab0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fde3e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fe0570"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01005d80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01016070"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0102ce30"
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
  "count": 13,
  "instructions": [
    {
      "address": "00c30c80",
      "instruction": "MOV EAX,dword ptr [ECX + 0xb0]"
    },
    {
      "address": "00c30c86",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "00c30c89",
      "instruction": "JZ 0x00c30ca3"
    },
    {
      "address": "00c30c8b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c30c8c",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00c30c91",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c30c93",
      "instruction": "CALL 0x00ba6d80"
    },
    {
      "address": "00c30c98",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c30c9a",
      "instruction": "JZ 0x00c30ca3"
    },
    {
      "address": "00c30c9c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c30c9e",
      "instruction": "JMP 0x00bba500"
    },
    {
      "address": "00c30ca3",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00c30ca5",
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
  "original_bytes": 10402,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"owner of the record id at +0xb0\",\n    \"hidden_this_register\": \"ECX, read at 0x00c30c80\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x00c30ca3 XOR EAX,EAX is the only zero return; the other path is 0x00c30c9e JMP 0x00bba500, a tail transfer, so EAX comes straight from that function.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer to the resolved record, or 0 when the id is unset or unresolvable; otherwise the tail callee's result\",\n    \"return_type\": \"std::uint32_t\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller (nothing is pushed at entry)\",\n    \"termination\": \"0x00c30ca5 RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 3,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 3,\n      \"symbol\": \"DiplomacyTransition_00d065a0\",\n      \"va\": \"0x00d065a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebe90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5bd3\"\n      },\n      {\n        \"name\": \"EmpirePoliticalColor_00c32cd0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00c32cd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c49140\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c49180\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c737a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cbc7f0\"\n      },\n      {\n        \"name\": \"DiplomacyTransition_00d065a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00d065a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e1bbc0\"\n      },\n      {\n        \"name\": \"FUN_00e39ab0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e39ab0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fde3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe0570\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01005d80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01016070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0102ce30\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00aec21b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00aebe90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba5c59\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba5bd3\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c32f2a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c32cd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c4914e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c49140\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c4918e\",\n        \"direction\": \"in
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
  "body_end": "00c30ca5",
  "body_span_bytes": 38,
  "body_start": "00c30c80",
  "callees": [
    "FUN_00ba6d80",
    "FUN_00bba500",
    "FUN_00b3d2a0"
  ],
  "callers": [
    "FUN_0102ce30",
    "FUN_01005d80",
    "FUN_00e1bbc0",
    "FUN_00ba5bd3",
    "FUN_00c49140",
    "FUN_00e39ab0",
    "FUN_00c737a0",
    "FUN_00aebe90",
    "FUN_00c49180",
    "FUN_01016070",
    "FUN_00c32cd0",
    "FUN_00fde3e0",
    "FUN_00fe0570",
    "FUN_00cbc7f0",
    "FUN_00d065a0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c30c80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00c30c80",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x830c80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c30c80(void)",
  "size_bytes": 38,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c30c80",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 22,
  "xrefs": [
    {
      "from": "00c32f2a"
    },
    {
      "from": "00c738d5"
    },
    {
      "from": "00ba5c59"
    },
    {
      "from": "00d066be"
    },
    {
      "from": "00aec21b"
    },
    {
      "from": "00e39ae4"
    },
    {
      "from": "00e39b43"
    },
    {
      "from": "0102ceb3"
    },
    {
      "from": "00fdea37"
    },
    {
      "from": "01005d92"
    },
    {
      "from": "00c4914e"
    },
    {
      "from": "00c4918e"
    },
    {
      "from": "00cbc8c2"
    },
    {
      "from": "00e1bfeb"
    },
    {
      "from": "010161ac"
    },
    {
      "from": "00fe08e3"
    },
    {
      "from": "00c5c43c"
    },
    {
      "from": "00cfa774"
    },
    {
      "from": "0100c366"
    },
    {
      "from": "0100c413"
    },
    {
      "from": "0104b2b4"
    },
    {
      "from": "0104b2cb"
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
    "reconstruction/staging/wave13-w1-core-b07/00c30c80_resolve_record_by_field.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b07/b07_opaque_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b07/00c30c80.json"
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
    "No original-process trace exists for this address.",
    "The record type, the handle table and the meaning of the +0xb0 id can only be settled with a runtime trace that shows the resolved record in use."
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "std::uint32_t"
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
