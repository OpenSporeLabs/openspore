# Evidence 0x008414d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2bc780fbf78f4409fe58d24fb238c807d3b66299ad4ac73932675eecbb5377be`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with the receiver in ECX, no stack argument read by the body",
  "hidden_this_register": "ECX",
  "hidden_this_type": "FormatParser * (SporeApp.exe has no MSVC RTTI; the receiver is an opaque vtable-owning object reached only through the vtable slot)",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "ret_form": "plain RET",
  "return_register": "EAX",
  "return_type": "const char*",
  "saved_registers": "ESI is pushed at 0x008414d6 and popped at 0x008414f5 unmodified; no other callee-saved register is touched",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "none for the receiver; the four words pushed for the callee are removed by ADD ESP,0x10 at 0x008414f2"
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
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
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
  "content_sha256": "ccd9a319e3a2716a957c87a5613ed274314e595e920262e5d7e87200c4e95c2a",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with the receiver in ECX, no stack argument read by the body"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0009"
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
        "obs-0004"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          224,
          240
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0004",
        "obs-0009"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0009"
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
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x008414d0",
      "count": 4,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0xf0]",
      "reg": "ECX"
    },
    {
      "at": "0x008414d0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0xf0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x008414d6",
      "count": 4,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x008414dd",
      "definite": true,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ECX + 0xe0]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x008414e3",
      "count": 1,
      "first_use": 4,
      "first_write_index": 0,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x008414eb",
      "id": "obs-0006",
      "index": 8,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00840c20",
      "target": "0x00840c20"
    },
    {
      "at": "0x008414f2",
      "definite": true,
      "id": "obs-0007",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x008414f5",
      "id": "obs-0008",
      "index": 11,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x008414f6",
      "form": "RET",
      "id": "obs-0009",
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
    "max_offset": 240,
    "offsets": [
      224,
      240
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
    "register_class": "pointer_like",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-infe
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
  "count": 13,
  "instructions": [
    {
      "address": "008414d0",
      "instruction": "MOV EAX,dword ptr [ECX + 0xf0]"
    },
    {
      "address": "008414d6",
      "instruction": "PUSH ESI"
    },
    {
      "address": "008414d7",
      "instruction": "LEA ESI,[ECX + 0xf4]"
    },
    {
      "address": "008414dd",
      "instruction": "MOV ECX,dword ptr [ECX + 0xe0]"
    },
    {
      "address": "008414e3",
      "instruction": "PUSH EAX"
    },
    {
      "address": "008414e4",
      "instruction": "PUSH ECX"
    },
    {
      "address": "008414e5",
      "instruction": "PUSH 0x141bcb0"
    },
    {
      "address": "008414ea",
      "instruction": "PUSH ESI"
    },
    {
      "address": "008414eb",
      "instruction": "CALL 0x00840c20"
    },
    {
      "address": "008414f0",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "008414f2",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "008414f5",
      "instruction": "POP ESI"
    },
    {
      "address": "008414f6",
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
  "original_bytes": 8009,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with the receiver in ECX, no stack argument read by the body\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"FormatParser * (SporeApp.exe has no MSVC RTTI; the receiver is an opaque vtable-owning object reached only through the vtable slot)\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"ordinary_stack_arguments\": [],\n    \"ret_form\": \"plain RET\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"const char*\",\n    \"saved_registers\": \"ESI is pushed at 0x008414d6 and popped at 0x008414f5 unmodified; no other callee-saved register is touched\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"none for the receiver; the four words pushed for the callee are removed by ADD ESP,0x10 at 0x008414f2\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x0141c930,vtable:0x0141c97c\"\n      ],\n      \"package\": \"PKG-ARGSCRIPT-WAVE9\",\n      \"score\": 10,\n      \"symbol\": \"pkg_argscript_get_current_scope_00d1dcd0\",\n      \"va\": \"0x00d1dcd0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:const char*\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"app_capp_system_set_effect_collection_ids_007e6100\",\n      \"va\": \"0x007e6100\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"scripting-content\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x008414eb\",\n        \"direction\": \"out\",\n        \"other\": \"0x00840c20\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0262\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"ArgScript::FormatParser::ParseUInt\",\n  \"normalized_symbol\": \"ArgScript::FormatParser::ParseUInt\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseUInt.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseUInt.c\",\n      \"reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0.cpp\",\n      \"reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0.hpp\",\n      \"reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-argscript-format-008414d0/008414d0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"queued\",\n  \"subsystem\": \"ArgScript\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"scripting-content\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseUInt.c\",\n    \"dependencies\": [\n      \"resource-io\"\n    ],\n    \"evidence\": \"CONFIRMED\",\n    \"kg_node_id\": \"fun:008414d0\",\n    \"name\": \"ArgScript::FormatParser::ParseUInt\",\n    \"priority\": \"P0\",\n    \"provenance\": {\n      \"classifier\": \"triage-v4\",\n      \"generated_at\": \"2026-09-23T10:12:09Z\",\n      \"generator\": \"subagent-7-sequential-triage\",\n      \"sdk_name\": \"ArgScript::FormatParser::ParseUInt\",\n      \"snapshot\": \"2540f2ca\",\n      \"snapshot_sha256\": \"2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8\",\n      \"vtable_addrs\": [\n        \"0141c930\",\n        \"0141c97c\"\n      ]\n    },\n    \"queue_state\": \"queued\",\n    \"rank\": 86\n  },\n  \"types\": [\n    \"FormatParser * (SporeApp.exe has no MSVC RTTI; the receiver is an opaque vtable-owning object reached only through the vtable slot)\",\n    \"const char*\",\n    \"openspore::reconstruction::pkg_argscript_format_008414d0::CopyFormattedToString\",\n    \"openspore::reconstruction::pkg_argscript_format_008414d0::FormatParserPorts\",\n    \"openspore::reconstruction::pkg_argscript_format_008414d0::OpaqueFormatParser\",\n    \"openspore::reconstruction::pkg_argscript_format_008414d0::OpaqueString\"\n  ],\n  \"unresolved_questions\": [\n    \"Are there writers of the words at +0xe0 and +0xf0 that would confirm their declared types (a script and a line/index respectively are guesses only)?\",\n    \"Does any real caller push the declared pString stack argument, and if so who cleans it up given the plain RET?\",\n    \"FIELDS/OFFSETS: is the machine-derived receiver record wrong, or is the model wrong? The record is narrower than the body: abi_derived.receiver is shape R-DIRECT with offsets [0xe0, 0xf0] 
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
  "body_end": "008414f6",
  "body_span_bytes": 39,
  "body_start": "008414d0",
  "callees": [
    "FUN_00840c20"
  ],
  "callers": [],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "008414d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "ArgScript::FormatParser::ParseUInt",
  "namespace": "ArgScript",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "FormatParser *"
    },
    {
      "name": "pString",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "char *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "uint",
  "return_type_resolved": true,
  "rva": "0x4414d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "uint ArgScript::FormatParser::ParseUInt(FormatParser * this, char * pString)",
  "size_bytes": 39,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x008414d0",
  "vtables": {
    "referenced_by_vtables": [
      "0x0141c930",
      "0x0141c97c"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0141c98c"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseUInt.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseUInt.c",
    "reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0.cpp",
    "reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0.hpp",
    "reconstruction/staging/pkg-argscript-format-008414d0/parse_uint_008414d0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-argscript-format-008414d0/008414d0.json"
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "FormatParser * (SporeApp.exe has no MSVC RTTI; the receiver is an opaque vtable-owning object reached only through the vtable slot)",
  "const char*",
  "openspore::reconstruction::pkg_argscript_format_008414d0::CopyFormattedToString",
  "openspore::reconstruction::pkg_argscript_format_008414d0::FormatParserPorts",
  "openspore::reconstruction::pkg_argscript_format_008414d0::OpaqueFormatParser",
  "openspore::reconstruction::pkg_argscript_format_008414d0::OpaqueString"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0141c930",
  "vtable:0x0141c97c"
]
```

## Conflicts

```json
[]
```
