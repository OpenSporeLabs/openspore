# Evidence 0x00d00d00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `596c52d22c90900ecf10377d48d8b946f5ea06476ba12d45f3edfdfca417187a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl",
  "hidden_this": null,
  "receiver": "policy returned by 0x00b3d2c0",
  "receiver_register": "ECX",
  "return_type": "float",
  "return_width_bytes": 4,
  "stack_arguments": [
    "source",
    "target",
    "1"
  ],
  "stack_cleanup_bytes": 12,
  "stack_cleanup_owner": "caller"
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
      "entry_ESP+0x8"
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
      }
    ],
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path",
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
  "conflicts": [
    {
      "field": "stack_cleanup_bytes",
      "inferred": 0,
      "kind": "inferred_vs_persisted",
      "persisted": 12,
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "3bcb8accf56b6edf311b41ded86a4f35f3e1ee5d7a1d234f7f7c27e9a3ff1294",
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
    "persisted_calling_convention": "cdecl"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0014",
        "obs-0015"
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
        "obs-0004"
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
        "obs-0005",
        "obs-0007"
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
        "obs-0004",
        "obs-0005",
        "obs-0007"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0014",
        "obs-0015"
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
        "obs-0015"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00d00d00",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00d00d00",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00d00d00",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00d00d04",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00d00d04",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0x4]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00d00d0a",
      "count": 3,
      "first_use": 3,
      "first_write_index": 0,
      
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d2c0",
    "reconstructed": false,
    "va": "0x00b3d2c0"
  },
  {
    "name": "FUN_00d00a70",
    "reconstructed": false,
    "va": "0x00d00a70"
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
    "va": "0x00bd80d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bdde70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e2e6e0"
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
  "count": 21,
  "instructions": [
    {
      "address": "00d00d00",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00d00d04",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00d00d08",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00d00d0a",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d00d0b",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d00d0c",
      "instruction": "CALL 0x00b3d2c0"
    },
    {
      "address": "00d00d11",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00d00d13",
      "instruction": "CALL 0x00d00a70"
    },
    {
      "address": "00d00d18",
      "instruction": "CMP EAX,0x4"
    },
    {
      "address": "00d00d1b",
      "instruction": "JA 0x00d00d40"
    },
    {
      "address": "00d00d1d",
      "instruction": "JMP dword ptr [EAX*0x4 + 0xd00d48]"
    },
    {
      "address": "00d00d24",
      "instruction": "FLD float ptr [0x01478d60]"
    },
    {
      "address": "00d00d2a",
      "instruction": "RET"
    },
    {
      "address": "00d00d2b",
      "instruction": "FLD float ptr [0x014853bc]"
    },
    {
      "address": "00d00d31",
      "instruction": "RET"
    },
    {
      "address": "00d00d32",
      "instruction": "FLD float ptr [0x014763c4]"
    },
    {
      "address": "00d00d38",
      "instruction": "RET"
    },
    {
      "address": "00d00d39",
      "instruction": "FLD float ptr [0x013ec4d0]"
    },
    {
      "address": "00d00d3f",
      "instruction": "RET"
    },
    {
      "address": "00d00d40",
      "instruction": "FLD float ptr [0x013f1cac]"
    },
    {
      "address": "00d00d46",
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
  "original_bytes": 7776,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl\",\n    \"hidden_this\": null,\n    \"receiver\": \"policy returned by 0x00b3d2c0\",\n    \"receiver_register\": \"ECX\",\n    \"return_type\": \"float\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [\n      \"source\",\n      \"target\",\n      \"1\"\n    ],\n    \"stack_cleanup_bytes\": 12,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:OpaqueRelationshipPolicy\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 17,\n      \"symbol\": \"RelationshipScoreObjects_00d00d60\",\n      \"va\": \"0x00d00d60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 10,\n      \"symbol\": \"SpeciesProfileSelector_00c30cc0\",\n      \"va\": \"0x00c30cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 10,\n      \"symbol\": \"ArchetypeRelationshipsID_00c30e20\",\n      \"va\": \"0x00c30e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d430\",\n      \"va\": \"0x00b3d430\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_IsNotStarOrBinaryStar\",\n      \"va\": \"0x00c8b6b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"Concrete policy owner and runtime mode routing remain opaque.\",\n    \"No original-process relationship IDs, policy object, or stage output was observed.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d2c0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b3d2c0\"\n      },\n      {\n        \"name\": \"FUN_00d00a70\",\n        \"reconstructed\": false,\n        \"va\": \"0x00d00a70\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd80d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bdde70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e2e6e0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00bd8104\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bd80d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bde259\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bdde70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e2e748\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e2e6e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d00d0c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d2c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d00d13\",\n        \"direction\": \"out\",\n        \"other\": \"0x00d00a70\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 3,\n    \"fan_out\": 2,\n    \"manifest_callees\": [\n      \"0x00b3d2c0\",\n      \"0x00d00a70\"\n    ],\n    \"manifest_callers\": [\n      \"0x00bd80d0\",\n      \"0x00bdde70\",\n      \"0x00e2e6e0\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0485\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"RelationshipScoreBand_00d00d00\",\n  \"normalized_symbol\": \"RelationshipScoreBand_00d00d00\",\n  \"observed_mechanics\": [\n    \"Push the constant 1, target, and source, call 0x00b3d2c0 for a relationship policy pointer, and use its EAX result as ECX.\",\n    \"Call 0x00d00a70 with the preserved source, target, and constant 1 stack words in that order; that thiscall removes its 12 argument bytes.\",\n    \"Compare the returned relationship stage with 4 using unsigned JA and dispatch a five-entry jump table.\",\n    \"Return immutable x87 constants 10.0, 30.0, 50.0, 80.0, and 100.0 for stages 0, 1, 2, 3, and 4; every unsigned stage above 4 also returns 100.0.\"\n  ],\n  \"ownership\": {\
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
  "body_end": "00d00d46",
  "body_span_bytes": 71,
  "body_start": "00d00d00",
  "callees": [
    "FUN_00b3d2c0",
    "FUN_00d00a70"
  ],
  "callers": [
    "FUN_00e2e6e0",
    "FUN_00bd80d0",
    "FUN_00bdde70"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d00d00",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00d00d00",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x900d00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00d00d00(void)",
  "size_bytes": 71,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d00d00",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00bd8104"
    },
    {
      "from": "00e2e748"
    },
    {
      "from": "00bde259"
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
    "reconstruction/metadata/pkg13-e2-diplomacy-alt/00d00d00.json"
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
    "gate-diplomacy-relationship-score-00d00d00",
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
  "None",
  "OpaqueRelationshipPolicy",
  "float",
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
