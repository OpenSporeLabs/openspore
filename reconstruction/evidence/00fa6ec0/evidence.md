# Evidence 0x00fa6ec0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `da20f200fcca794b2aa295b7de718e432cc11cfd761a75a176990cf173ecc7d1`

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
  "return_note": "The WIDTH and the bit pattern are machine-fixed: the LAST write to EAX in the whole body is 0x00fa6f13 IMUL EDI, the low 32 bits of the second block's 64-bit signed product, so the value comes back in EAX and is 32 bits wide, and no 64-bit or floating claim is compatible with those bytes. The C SPELLING is a source-side choice: Word is one of several C++ types of that width (std::uint32_t, unsigned int, unsigned long, or a 32-bit typedef of the original source's own vocabulary) and the listing does not choose between them -- which is precisely why abi_derived can classify the register but n...",
  "return_register": "EAX",
  "return_type": "Word",
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "callee",
  "termination": "RET (0x00fa6f37, one byte C3, no immediate)"
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
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "995c430014cc43dd75409816fc73f1c2edad40ace2f91d87440f2d6270b7cc09",
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
        "obs-0018"
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
        "obs-0003",
        "obs-0004",
        "obs-0013"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          1904,
          1908,
          1924,
          1928,
          2068
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0013",
        "obs-0018"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0018"
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
        "obs-0018"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0018"
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
      "at": "0x00fa6ec0",
      "count": 5,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00fa6ec1",
      "count": 8,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00fa6ec2",
      "count": 4,
      "first_use": 2,
      "first_write_index": 29,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00fa6ec2",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00fa6ec4",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESI + 0x770]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00fa6eca",
      "count": 5,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00fa6ecb",
      "definite": true,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESI + 0x774]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00fa6ed4",
      "id": "obs-0008",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f9f770",
      "target": "0x00f9f770"
    },
    {
      "at": "0x00fa6edb",
      "definite": true,
      "id": "obs-0009",
      "index": 11,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0xd05f417d",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x00fa6ee2",
      "count": 6,
      "first_use": 13,
      "first_write_index": null,
      "id": "obs-0010",
      "index": 13,
      "kind": "REG_READ",
      "raw": "SAR EDX,0x5",
      "reg": "EDX"
    },
    {
      "at": "0x00fa6ee7",
      "count": 3,
      "first_use": 15,
      "first_write_index": 11,
      "id": "obs-0011",
      "index": 15,
      "kind": "REG_READ",
      "raw": "SHR EAX,0x1f",
      "reg": "EAX"
    },
    {
      "at": "0x00fa6f07",
      "id": "obs-0012",
      "index": 24,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f9f770",
      "target": "0x00f9f770"
    },
    {
      "at": "0x00fa6f18",
      "definite": true,
      "id": "obs-0013",
      "index": 29,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EDX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00fa6
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
  "count": 40,
  "instructions": [
    {
      "address": "00fa6ec0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00fa6ec1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00fa6ec2",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00fa6ec4",
      "instruction": "MOV EBX,dword ptr [ESI + 0x770]"
    },
    {
      "address": "00fa6eca",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00fa6ecb",
      "instruction": "MOV EDI,dword ptr [ESI + 0x774]"
    },
    {
      "address": "00fa6ed1",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00fa6ed2",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00fa6ed3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00fa6ed4",
      "instruction": "CALL 0x00f9f770"
    },
    {
      "address": "00fa6ed9",
      "instruction": "SUB EDI,EBX"
    },
    {
      "address": "00fa6edb",
      "instruction": "MOV EAX,0xd05f417d"
    },
    {
      "address": "00fa6ee0",
      "instruction": "IMUL EDI"
    },
    {
      "address": "00fa6ee2",
      "instruction": "SAR EDX,0x5"
    },
    {
      "address": "00fa6ee5",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "00fa6ee7",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "00fa6eea",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "00fa6eec",
      "instruction": "IMUL EAX,EAX,0xac"
    },
    {
      "address": "00fa6ef2",
      "instruction": "ADD dword ptr [ESI + 0x774],EAX"
    },
    {
      "address": "00fa6ef8",
      "instruction": "MOV EBX,dword ptr [ESI + 0x784]"
    },
    {
      "address": "00fa6efe",
      "instruction": "MOV EDI,dword ptr [ESI + 0x788]"
    },
    {
      "address": "00fa6f04",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00fa6f05",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00fa6f06",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00fa6f07",
      "instruction": "CALL 0x00f9f770"
    },
    {
      "address": "00fa6f0c",
      "instruction": "SUB EDI,EBX"
    },
    {
      "address": "00fa6f0e",
      "instruction": "MOV EAX,0xd05f417d"
    },
    {
      "address": "00fa6f13",
      "instruction": "IMUL EDI"
    },
    {
      "address": "00fa6f15",
      "instruction": "SAR EDX,0x5"
    },
    {
      "address": "00fa6f18",
      "instruction": "MOV ECX,EDX"
    },
    {
      "address": "00fa6f1a",
      "instruction": "SHR ECX,0x1f"
    },
    {
      "address": "00fa6f1d",
      "instruction": "ADD ECX,EDX"
    },
    {
      "address": "00fa6f1f",
      "instruction": "IMUL ECX,ECX,0xac"
    },
    {
      "address": "00fa6f25",
      "instruction": "ADD dword ptr [ESI + 0x788],ECX"
    },
    {
      "address": "00fa6f2b",
      "instruction": "INC dword ptr [ESI + 0x814]"
    },
    {
      "address": "00fa6f31",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "00fa6f34",
      "instruction": "POP EDI"
    },
    {
      "address": "00fa6f35",
      "instruction": "POP ESI"
    },
    {
      "address": "00fa6f36",
      "instruction": "POP EBX"
    },
    {
      "address": "00fa6f37",
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
  "original_bytes": 10418,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_note\": \"The WIDTH and the bit pattern are machine-fixed: the LAST write to EAX in the whole body is 0x00fa6f13 IMUL EDI, the low 32 bits of the second block's 64-bit signed product, so the value comes back in EAX and is 32 bits wide, and no 64-bit or floating claim is compatible with those bytes. The C SPELLING is a source-side choice: Word is one of several C++ types of that width (std::uint32_t, unsigned int, unsigned long, or a 32-bit typedef of the original source's own vocabulary) and the listing does not choose between them -- which is precisely why abi_derived can classify the register but n...\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"Word\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET (0x00fa6f37, one byte C3, no immediate)\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:Word\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00fa6ed4\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f9f770\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fa6f07\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f9f770\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0579\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00fa6ec0\",\n  \"normalized_symbol\": \"FUN_00fa6ec0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w1-00fa6ec0/00fa6ec0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Sporepedia\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sporepedia-online\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00fa6ec0\",\n    \"name\": \"FUN_00fa6ec0
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
  "body_end": "00fa6f37",
  "body_span_bytes": 120,
  "body_start": "00fa6ec0",
  "callees": [
    "FUN_00f9f770"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00fa6ec0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00fa6ec0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xba6ec0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00fa6ec0(void)",
  "size_bytes": 120,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00fa6ec0",
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
      "from": "01490c48"
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
    "reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00fa6ec0/w22_00fa6ec0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00fa6ec0/00fa6ec0.json"
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
  "Word",
  "Word (uint32_t)",
  "openspore::reconstruction::pkg_swarm_w1_00fa6ec0::Element",
  "openspore::reconstruction::pkg_swarm_w1_00fa6ec0::ElementVector",
  "openspore::reconstruction::pkg_swarm_w1_00fa6ec0::Owner",
  "openspore::reconstruction::pkg_swarm_w1_00fa6ec0::Word"
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
