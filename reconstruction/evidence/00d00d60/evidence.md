# Evidence 0x00d00d60

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5d4a30b2dc7dc72d273e30bf8609fb7b847f919e8db6b0b42aab3ea7b577c02f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueRelationshipPolicy*",
  "receiver": "entry policy",
  "receiver_register": "ECX",
  "return_type": "float",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "first",
      "position": 1,
      "type": "OpaqueIdentityObject*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "second",
      "position": 2,
      "type": "OpaqueIdentityObject*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0c",
      "name": "mode",
      "position": 3,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 12,
  "termination": "RET 0x0c on both paths"
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
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0xc",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "abbcbc206efd3a65975a4bd92bc67d5dc3f06870737187569f62c098b1eadd85",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
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
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0023",
        "obs-0026"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0008",
        "obs-0018"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0010",
        "obs-0018"
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
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0010",
        "obs-0018"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
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
        "obs-0026"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00d00d60",
      "count": 2,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00d00d61",
      "count": 3,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00d00d61",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,ECX",
      "reg": "EBX",
      "write_kind": "reg"
    },
    {
      "at": "0x00d00d63",
      "count": 3,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00d00d63",
      "base": "ESP",
      "disp"
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00d00a10",
    "reconstructed": false,
    "va": "0x00d00a10"
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
    "va": "0x00dca100"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ea8c30"
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
  "count": 32,
  "instructions": [
    {
      "address": "00d00d60",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00d00d61",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00d00d63",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00d00d67",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d00d68",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00d00d6a",
      "instruction": "JZ 0x00d00d9b"
    },
    {
      "address": "00d00d6c",
      "instruction": "MOV ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00d00d70",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00d00d72",
      "instruction": "JZ 0x00d00d9b"
    },
    {
      "address": "00d00d74",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00d00d76",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4c]"
    },
    {
      "address": "00d00d79",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d00d7a",
      "instruction": "CALL EDX"
    },
    {
      "address": "00d00d7c",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00d00d7e",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00d00d80",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4c]"
    },
    {
      "address": "00d00d83",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00d00d85",
      "instruction": "CALL EDX"
    },
    {
      "address": "00d00d87",
      "instruction": "MOV ECX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00d00d8b",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d00d8c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d00d8d",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00d00d8e",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00d00d90",
      "instruction": "CALL 0x00d00a10"
    },
    {
      "address": "00d00d95",
      "instruction": "POP EDI"
    },
    {
      "address": "00d00d96",
      "instruction": "POP ESI"
    },
    {
      "address": "00d00d97",
      "instruction": "POP EBX"
    },
    {
      "address": "00d00d98",
      "instruction": "RET 0xc"
    },
    {
      "address": "00d00d9b",
      "instruction": "FLDZ"
    },
    {
      "address": "00d00d9d",
      "instruction": "POP ESI"
    },
    {
      "address": "00d00d9e",
      "instruction": "POP EBX"
    },
    {
      "address": "00d00d9f",
      "instruction": "RET 0xc"
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
  "original_bytes": 7999,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueRelationshipPolicy*\",\n    \"receiver\": \"entry policy\",\n    \"receiver_register\": \"ECX\",\n    \"return_type\": \"float\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"first\",\n        \"position\": 1,\n        \"type\": \"OpaqueIdentityObject*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"second\",\n        \"position\": 2,\n        \"type\": \"OpaqueIdentityObject*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x0c\",\n        \"name\": \"mode\",\n        \"position\": 3,\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 12,\n    \"termination\": \"RET 0x0c on both paths\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:OpaqueRelationshipPolicy\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 17,\n      \"symbol\": \"RelationshipScoreBand_00d00d00\",\n      \"va\": \"0x00d00d00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PRIMITIVES\",\n      \"score\": 8,\n      \"symbol\": \"RelationshipMapSelect_00d01ab0\",\n      \"va\": \"0x00d01ab0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PREDICATE\",\n      \"score\": 8,\n      \"symbol\": \"RelationshipManager_IsAllied2_00d01ff0\",\n      \"va\": \"0x00d01ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-PRIMITIVES\",\n      \"score\": 6,\n      \"symbol\": \"RelationshipLookup_00d01410\",\n      \"va\": \"0x00d01410\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x00000000\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 6,\n      \"symbol\": \"DiplomacyTransition_00d01e30\",\n      \"va\": \"0x00d01e30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x00000000\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-DIPLOMACY-TRANSITIONS\",\n      \"score\": 6,\n      \"symbol\": \"DiplomacyTransition_00d06920\",\n      \"va\": \"0x00d06920\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_Update_0059b4b0\",\n      \"va\": \"0x0059b4b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"Concrete vtable implementations and relationship persistence remain opaque.\",\n    \"No original-process object identities, policy, or relationship score was observed.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueRelationshipPolicy\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00d00a10\",\n        \"reconstructed\": false,\n        \"va\": \"0x00d00a10\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dca100\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ea8c30\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00dca3ef\",\n        \"direction\": \"in\",\n        \"other\": \"0x00dca100\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ea8db8\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ea8c30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d00d90\",\n        \"direction\": \"out\",\n        \"other\": \"0x00d00a10\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 2,\n    \"fan_out\": 1,\n    \"manifest_callees\": [\n      \"0x00d00a10\"\n    ],\n    \"manifest_callers\": [\n      \"0x00dca100\",\n      \"0x00ea8c30\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0486\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"RelationshipScoreObjects_00d00d60\",\n  \"normalized_symbol\": \"RelationshipScoreObjects_00d00d60\",\n  \"observed_mechanics\": [\n    \"Test first and then second for null; either null returns x87 positive zero and skips both virtual identity calls and 0x00d00a10.\",\n    \"Load first vtable, call slot +0x4c with first in ECX, and retain the returned 32-bit identity in EDI.\",\n    \"Load second vtable, call the same +0x4c slot with second in ECX, and retain its identity in EAX.\",\n    \"Call 0x00d00a10 with policy in ECX and stack words first identity, second identity, and mode, then return its x87 float unchanged.\",\n    \"Pop EBX, ESI, and EDI and remove 12 argument bytes on
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
  "body_end": "00d00da1",
  "body_span_bytes": 66,
  "body_start": "00d00d60",
  "callees": [
    "FUN_00d00a10"
  ],
  "callers": [
    "FUN_00dca100",
    "FUN_00ea8c30"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d00d60",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00d00d60",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x900d60",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00d00d60(void)",
  "size_bytes": 66,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d00d60",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00dca3ef"
    },
    {
      "from": "00bdf3a6"
    },
    {
      "from": "00ea8db8"
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
  "file": "src/reconstruction/pkg13_e2_diplomacy_alt/diplomacy_alt.cpp",
  "files": [
    "reconstruction/staging/pkg13-e2-diplomacy-alt/diplomacy_alt.cpp",
    "reconstruction/staging/pkg13-e2-diplomacy-alt/diplomacy_alt.hpp",
    "reconstruction/staging/pkg13-e2-diplomacy-alt/diplomacy_alt_model_test.cpp",
    "src/reconstruction/pkg13_e2_diplomacy_alt/diplomacy_alt.cpp",
    "src/reconstruction/pkg13_e2_diplomacy_alt/diplomacy_alt.hpp",
    "src/reconstruction/pkg13_e2_diplomacy_alt/diplomacy_alt_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave1/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-e2-diplomacy-alt/00d00d60.json"
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
    "gate-diplomacy-relationship-objects-00d00d60",
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
  "OpaqueIdentityObject",
  "OpaqueIdentityObject*",
  "OpaqueRelationshipPolicy",
  "OpaqueRelationshipPolicy*",
  "float",
  "std::uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00000000"
]
```

## Conflicts

```json
[]
```
