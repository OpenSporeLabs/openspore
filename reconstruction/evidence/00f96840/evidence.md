# Evidence 0x00f96840

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `22f645cff2fb04be49872c285007442e190e21591aa48add35db52ddda8815ea`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "receiver": "ECX carries the receiver, and this is an INFERRED determination with a real dereference history rather than a guess. The record states receiver {present true, register ECX, confidence INFERRED, shape R-ALIAS, bounds_only true, distinct_offsets 2, offsets [0, 2068], max_offset 2068, written_through 1} on inference R1, from observations obs-0002, obs-0003 and obs-0009: ECX is copied into ESI at 0x00f96841 and is dereferenced through that alias before any definite write to it. The listing corroborates it instruction by instruction: 0x00f96841 is the only read of ECX, and ECX is not written aga...",
  "ret_form": null,
  "return_register": "EAX",
  "return_semantics": "pointer_like_in_EAX",
  "return_width_bytes": null,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": "none. stack_arguments {observed_slots 0, derived_slots 0, total_bytes 0, gaps 0, not_complete false, widths_ambiguous false, confidence APPROXIMATION}, and the fifteen instructions contain no memory operand on ESP at all: nothing is pushed for a callee and no stack word is read.",
  "stack_cleanup_bytes": null,
  "stack_cleanup_owner": null,
  "termination": "JMP EDX at 0x00f96868 (ff e2) -- a tail transfer, not a return"
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "ESI"
    ]
  },
  "abstained_because": [
    "no_terminal_ret: function has no RET instruction"
  ],
  "cleanup": {
    "bytes": null,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": null,
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "121ce454e1fb5f79b0e12ca42479d716e068c9fb0d7c5b01c34192414b23b8a8",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
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
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0012"
      ],
      "claim": "no terminal return is present in the listing",
      "confidence": "UNKNOWN",
      "id": "C2"
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          2068
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0012"
      ],
      "claim": "entry slot 0 is not written through a pointer",
      "confidence": "APPROXIMATION",
      "id": "S2",
      "value": {
        "present": false
      }
    }
  ],
  "observations": [
    {
      "at": "0x00f96840",
      "count": 7,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00f96841",
      "count": 1,
      "first_use": 1,
      "first_write_index": 7,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00f96841",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00f96843",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00f96845",
      "count": 3,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x70]",
      "reg": "EAX"
    },
    {
      "at": "0x00f96845",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x70]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00f96848",
      "count": 3,
      "first_use": 4,
      "first_write_index": 3,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00f96848",
      "base": "EDX",
      "disp": null,
      "id": "obs-0008",
      "index": 4,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00f9684f",
      "definite": true,
      "id": "obs-0009",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,ESI",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00f96851",
      "base": "EDX",
      "disp": null,
      "id": "obs-0010",
      "index": 8,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00f96867",
      "id": "obs-0011",
      "index": 13,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00f96868",
      "base": "EDX",
      "disp": null,
      "id": "obs-0012",
      "index": 14,
      "kind": "JMP_INDIRECT",
      "raw": "JMP EDX",
      "via": "register"
    }
  ],
  "parse": {
    "declared_count": 15,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
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
    "distinct_offsets": 2,
    "max_offset": 2068,
    "offsets": [
      0,
      2068
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-ALIAS",
    "written_through": 1
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "pointer_like",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "s
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

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nvoid __fastcall FUN_00f96840(int *param_1)\n\n{\n  code *UNRECOVERED_JUMPTABLE;\n  \n  (**(code **)(*param_1 + 0x70))();\n  (**(code **)(*param_1 + 0x60))();\n  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x84);\n  param_1[0x205] = 0;\n                    /* WARNING: Could not recover jumptable at 0x00f96868. Too many branches */\n                    /* WARNING: Treating indirect jump as call */\n  (*UNRECOVERED_JUMPTABLE)();\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 15,
  "instructions": [
    {
      "address": "00f96840",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00f96841",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00f96843",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00f96845",
      "instruction": "MOV EDX,dword ptr [EAX + 0x70]"
    },
    {
      "address": "00f96848",
      "instruction": "CALL EDX"
    },
    {
      "address": "00f9684a",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00f9684c",
      "instruction": "MOV EDX,dword ptr [EAX + 0x60]"
    },
    {
      "address": "00f9684f",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f96851",
      "instruction": "CALL EDX"
    },
    {
      "address": "00f96853",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00f96855",
      "instruction": "MOV EDX,dword ptr [EAX + 0x84]"
    },
    {
      "address": "00f9685b",
      "instruction": "MOV dword ptr [ESI + 0x814],0x0"
    },
    {
      "address": "00f96865",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f96867",
      "instruction": "POP ESI"
    },
    {
      "address": "00f96868",
      "instruction": "JMP EDX"
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
  "original_bytes": 10058,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": null,\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": \"ECX carries the receiver, and this is an INFERRED determination with a real dereference history rather than a guess. The record states receiver {present true, register ECX, confidence INFERRED, shape R-ALIAS, bounds_only true, distinct_offsets 2, offsets [0, 2068], max_offset 2068, written_through 1} on inference R1, from observations obs-0002, obs-0003 and obs-0009: ECX is copied into ESI at 0x00f96841 and is dereferenced through that alias before any definite write to it. The listing corroborates it instruction by instruction: 0x00f96841 is the only read of ECX, and ECX is not written aga...\",\n    \"ret_form\": null,\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"return_width_bytes\": null,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": \"none. stack_arguments {observed_slots 0, derived_slots 0, total_bytes 0, gaps 0, not_complete false, widths_ambiguous false, confidence APPROXIMATION}, and the fifteen instructions contain no memory operand on ESP at all: nothing is pushed for a callee and no stack word is read.\",\n    \"stack_cleanup_bytes\": null,\n    \"stack_cleanup_owner\": null,\n    \"termination\": \"JMP EDX at 0x00f96868 (ff e2) -- a tail transfer, not a return\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"pkg-swarm-w2-00f999e0\",\n      \"score\": 10,\n      \"symbol\": \"re_00f999e0\",\n      \"va\": \"0x00f999e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"pkg-fa0d50-atomic-inc\",\n      \"score\": 10,\n      \"symbol\": \"FUN_00fa0d50\",\n      \"va\": \"0x00fa0d50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"pkg-swarm-w1-00fa5580\",\n      \"score\": 10,\n      \"symbol\": \"re_00fa5580\",\n      \"va\": \"0x00fa5580\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"pkg-swarm-w1-00fa6ec0\",\n      \"score\": 10,\n      \"symbol\": \"re_00fa6ec0\",\n      \"va\": \"0x00fa6ec0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"pkg-swarm-w1-00fa73c0\",\n      \"score\": 10,\n      \"symbol\": \"sw1_snap_and_dispatch_00fa73c0\",\n      \"va\": \"0x00fa73c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"pkg-swarm-w1-0104c110\",\n      \"score\": 10,\n      \"symbol\": \"re_0104c110\",\n      \"va\": \"0x0104c110\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w1-005c0dd0\",\n      \"score\": 6,\n      \"symbol\": \"re_005c0dd0\",\n      \"va\": \"0x005c0dd0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w1-006413d0\",\n      \"score\": 6,\n      \"symbol\": \"re_006413d0\",\n      \"va\": \"0x006413d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"STATIC AGGREGATE IS NOT PASS, and cannot be without asserting a fact the machine record states it cannot determine. Seven of the eight structural checks PASS. ABI is a WARN: the derived record's verdict is ABI_UNKNOWN with confidence UNKNOWN and abstained_because \\\"no_terminal_ret: function has no RET instruction\\\", and the validator's ABI arm reports that abstention verbatim. RETURN SEMANTICS is NOT_AVAILABLE: the machine return state is UNCLASSIFIED on a body whose only exit is a tail jump, so there is no state to compare a declaration against and the validator invents none. The promotion gate therefore reports a static_not_pass blocker for this package. Neither is repairable from the source: the only two ways to clear them are to claim a convention the record abstains on, or to claim a return type belonging to a routine outside the body.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0570\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"FUN_00f96840\",\n  \"normalized_symbol\": \"FUN_00f96840\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"no original-process trace exists in this repository; the runtime gate is open, nothing was attempted, and nothing failed\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\"
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
  "body_end": "00f96869",
  "body_span_bytes": 42,
  "body_start": "00f96840",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00f96840",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "UNRECOVERED_JUMPTABLE",
      "storage": "unique:00017200:4",
      "type": "undefined *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int *"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00f96840",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xb96840",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00f96840(void)",
  "size_bytes": 42,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00f96840",
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
      "from": "01490c70"
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
    "reconstruction/staging/pkg-w2-00f96840/w2_00f96840.cpp",
    "reconstruction/staging/pkg-w2-00f96840/w2_00f96840_model_test.cpp",
    "reconstruction/staging/pkg-w2-00f96840/w2_00f96840_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00f96840/00f96840.json"
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
    "no original-process trace exists in this repository; the runtime gate is open, nothing was attempted, and nothing failed"
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "openspore::reconstruction::pkg_w2_00f96840::CandidateConvention00f96840",
  "openspore::reconstruction::pkg_w2_00f96840::CleanupSide00f96840",
  "openspore::reconstruction::pkg_w2_00f96840::ConventionVerdict00f96840",
  "openspore::reconstruction::pkg_w2_00f96840::Receiver",
  "openspore::reconstruction::pkg_w2_00f96840::ReceiverRegister00f96840",
  "openspore::reconstruction::pkg_w2_00f96840::ReceiverShape00f96840",
  "openspore::reconstruction::pkg_w2_00f96840::ReturnRegisterClass00f96840"
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
