# Evidence 0x00c30cc0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9db3d64561a0adee719655765ca9f474d810a9b11849c9b2b42e2b741efda01f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl",
  "hidden_this": null,
  "return_register": "EAX",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "archetype",
      "position": 1,
      "type": "std::uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "difficulty",
      "position": 2,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
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
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
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
      "persisted": 8,
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "72eb549d9599c897186caf3cffdc94be1c83def1b06136b5f779c4dbe11abed8",
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
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0012",
        "obs-0013",
        "obs-0014",
        "obs-0016",
        "obs-0017",
        "obs-0018",
        "obs-0020",
        "obs-0021",
        "obs-0022",
        "obs-0024",
        "obs-0025",
        "obs-0026",
        "obs-0028",
        "obs-0029",
        "obs-0030",
        "obs-0032",
        "obs-0033",
        "obs-0034",
        "obs-0036",
        "obs-0037",
        "obs-0038"
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
        "obs-0007",
        "obs-0011",
        "obs-0015",
        "obs-0019",
        "obs-0023",
        "obs-0027",
        "obs-0031",
        "obs-0035"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0011",
        "obs-0015",
        "obs-0019",
        "obs-0023",
        "obs-0027",
        "obs-0031",
        "obs-0035"
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
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0011",
        "obs-0015",
        "obs-0019",
        "obs-0023",
        "obs-0027",
        "obs-0031",
        "obs-0035"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0012",
        "obs-0013",
        "obs-0014",
        "obs-0016",
        "obs-0017",
        "obs-0018",
        "obs-0020",
        "obs-0021",
        "obs-0022",
        "obs-0024",
        "obs-0025",
        "obs-0026",
        "obs-0028",
        "obs-0029",
        "obs-0030",
        "obs-0032",
        "obs-0033",
        "obs-0034",
        "obs-0036",
        "obs-0037",
        "obs-0038"
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
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0012",
        "obs-0013",
        "obs-0014",
        "obs-0016",
        "obs-0017",
        "obs-0018",
        "obs-0020",
        "obs-0021",
        "obs-0022",
        "obs-0024",
        "obs-0025",
        "obs-0026",
        "obs-0028",
      
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
    "va": "0x00c30e80"
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
  "count": 110,
  "instructions": [
    {
      "address": "00c30cc0",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00c30cc4",
      "instruction": "MOV EAX,0x4e5855b9"
    },
    {
      "address": "00c30cc9",
      "instruction": "CMP ECX,0x12"
    },
    {
      "address": "00c30ccc",
      "instruction": "JA 0x00c30e44"
    },
    {
      "address": "00c30cd2",
      "instruction": "MOVZX ECX,byte ptr [ECX + 0xc30e6c]"
    },
    {
      "address": "00c30cd9",
      "instruction": "JMP dword ptr [ECX*0x4 + 0xc30e48]"
    },
    {
      "address": "00c30ce0",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c30ce4",
      "instruction": "SUB ECX,0x0"
    },
    {
      "address": "00c30ce7",
      "instruction": "JZ 0x00c30d03"
    },
    {
      "address": "00c30ce9",
      "instruction": "SUB ECX,0x1"
    },
    {
      "address": "00c30cec",
      "instruction": "JZ 0x00c30cfd"
    },
    {
      "address": "00c30cee",
      "instruction": "SUB ECX,0x1"
    },
    {
      "address": "00c30cf1",
      "instruction": "JNZ 0x00c30e44"
    },
    {
      "address": "00c30cf7",
      "instruction": "MOV EAX,0xed2bbcc8"
    },
    {
      "address": "00c30cfc",
      "instruction": "RET"
    },
    {
      "address": "00c30cfd",
      "instruction": "MOV EAX,0x4fede4a6"
    },
    {
      "address": "00c30d02",
      "instruction": "RET"
    },
    {
      "address": "00c30d03",
      "instruction": "MOV EAX,0xacb9635d"
    },
    {
      "address": "00c30d08",
      "instruction": "RET"
    },
    {
      "address": "00c30d09",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c30d0d",
      "instruction": "SUB ECX,0x0"
    },
    {
      "address": "00c30d10",
      "instruction": "JZ 0x00c30d2c"
    },
    {
      "address": "00c30d12",
      "instruction": "SUB ECX,0x1"
    },
    {
      "address": "00c30d15",
      "instruction": "JZ 0x00c30d26"
    },
    {
      "address": "00c30d17",
      "instruction": "SUB ECX,0x1"
    },
    {
      "address": "00c30d1a",
      "instruction": "JNZ 0x00c30e44"
    },
    {
      "address": "00c30d20",
      "instruction": "MOV EAX,0x12486202"
    },
    {
      "address": "00c30d25",
      "instruction": "RET"
    },
    {
      "address": "00c30d26",
      "instruction": "MOV EAX,0x250f78b4"
    },
    {
      "address": "00c30d2b",
      "instruction": "RET"
    },
    {
      "address": "00c30d2c",
      "instruction": "MOV EAX,0x4a83b77"
    },
    {
      "address": "00c30d31",
      "instruction": "RET"
    },
    {
      "address": "00c30d32",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c30d36",
      "instruction": "SUB ECX,0x0"
    },
    {
      "address": "00c30d39",
      "instruction": "JZ 0x00c30d55"
    },
    {
      "address": "00c30d3b",
      "instruction": "SUB ECX,0x1"
    },
    {
      "address": "00c30d3e",
      "instruction": "JZ 0x00c30d4f"
    },
    {
      "address": "00c30d40",
      "instruction": "SUB ECX,0x1"
    },
    {
      "address": "00c30d43",
      "instruction": "JNZ 0x00c30e44"
    },
    {
      "address": "00c30d49",
      "instruction": "MOV EAX,0x8aa5a470"
    },
    {
      "address": "00c30d4e",
      "instruction": "RET"
    },
    {
      "address": "00c30d4f",
      "instruction": "MOV EAX,0x76b1a6e"
    },
    {
      "address": "00c30d54",
      "instruction": "RET"
    },
    {
      "address": "00c30d55",
      "instruction": "MOV EAX,0x5d054a25"
    },
    {
      "address": "00c30d5a",
      "instruction": "RET"
    },
    {
      "address": "00c30d5b",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c30d5f",
      "instruction": "SUB ECX,0x0"
    },
    {
      "address": "00c30d62",
      "instruction": "JZ 0x00c30d7e"
    },
    {
      "address": "00c30d64",
      "instruction": "SUB ECX,0x1"
    },
    {
      "address": "00c30d67",
      "instruction": "JZ 0x00c30d78"
    },
    {
      "address": "00c30d69",
      "instruction": "SUB ECX,0x1"
    },
    {
      "address": "00c30d6c",
      "instruction": "JNZ 0x00c30e44"
    },
    {
      "address": "00c30d72",
      "instruction": "MOV EAX,0x21d2a5b8"
    },
    {
      "address": "00c30d77",
      "instruction": "RET"
    },
    {
      "address": "00c30d78",
      "instruction": "MOV EAX,0xb308c5d6"
    },
    {
      "address": "00c30d7d",
      "instruction": "RET"
    },
    {
      "address": "00c30d7e",
      "instruction": "MOV EAX,0xdf83b46d"
    },
    {
      "address": "00c30d83",
      "instruction": "RET"
    },
    {
      "address": "00c30d84",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c30d88",
      "instruction": "SUB ECX,0x0"
    },
    {
      "address": "00c30d8b",
      "instruction": "JZ 0x00c30da7"
    },
    {
      "address": "00c30d8d",
      "instruction": "SUB ECX,0x1"
    },
    {
      "address": "00c30d90",
      "instruction": "JZ 0x00c30da1"
    },
    {
      "address": "00c30d92",
      "instruction": "SUB ECX,0x1"
    },
    {
      "address": "00c30d95",
      "instruction": "JNZ 0x00c30e44"
    },
    {
      "address": "00c30d9b",
      "instruction": "MOV EAX,0xf9b2cbad"
    },
    {
      "address": "00c30da0",
      "instruction": "RET"
    },
    {
      "address": "00c30da1",
      "instruction": "MOV EAX,0xacd3a4cf"
    },
    {
      "address": "00c30da6",
      "instruction": "RET"
    },
    {
      "address": "00c30da7",
      "instruction": "MOV EAX,0x59878688"
    },
    {
      "address": "00c30dac",
      "instruction": "RET"
    },
    {
      "address": "00c30dad",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c30db1",
      "instruction": "SUB ECX,0x0"
    },
    {
      "address": "00c30db4",
      "instruction": "JZ 0x00c30dd0"
    },
    {
      "address": "00c30db6",
      "instruction": "SUB 
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
  "original_bytes": 6581,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl\",\n    \"hidden_this\": null,\n    \"return_register\": \"EAX\",\n    \"return_type\": \"std::uint32_t\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"archetype\",\n        \"position\": 1,\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"difficulty\",\n        \"position\": 2,\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 24,\n      \"symbol\": \"ArchetypeRelationshipsID_00c30e20\",\n      \"va\": \"0x00c30e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 14,\n      \"symbol\": \"ProfileSetter_00c33690\",\n      \"va\": \"0x00c33690\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E2-DIPLOMACY-ALT\",\n      \"score\": 10,\n      \"symbol\": \"RelationshipScoreBand_00d00d00\",\n      \"va\": \"0x00d00d00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d430\",\n      \"va\": \"0x00b3d430\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"HomeWorldMetricLazy_00c31890\",\n      \"va\": \"0x00c31890\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c30e80\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00c30ea4\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c30e80\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [\n      \"0x00c30e80\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0450\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"SpeciesProfileSelector_00c30cc0\",\n  \"normalized_symbol\": \"SpeciesProfileSelector_00c30cc0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-13-E3-EMPIRE-STATE-WAVE2\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-species-profile-selector-00c30cc0\",\n      \"runtime validation not run\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_metadata_exact_runtime_unresolved\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": \"src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp\",\n    \"files\": [\n      \"reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary.S\",\n      \"reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary_test.sh\",\n      \"reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.cpp\",\n      \"reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.hpp\",\n      \"reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2_model_test.cpp\",\n      \"src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary.S\",\n      \"src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary_test.sh\",\n      \"src/reconstruc
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
  "body_end": "00c30e1f",
  "body_span_bytes": 352,
  "body_start": "00c30cc0",
  "callees": [],
  "callers": [
    "FUN_00c30e80"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00c30cc0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00c30cc0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x830cc0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c30cc0(void)",
  "size_bytes": 352,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c30cc0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00c30ea4"
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
  "file": "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary.S",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary_test.sh",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.cpp",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.hpp",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2_model_test.cpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary.S",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary_test.sh",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.hpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-e3-empire-state-wave2/00c30cc0.json"
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
    "gate-species-profile-selector-00c30cc0",
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
