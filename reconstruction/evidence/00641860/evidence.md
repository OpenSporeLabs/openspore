# Evidence 0x00641860

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9f2ffcb62848182133903558054504c1bd58cab5ce751edd3c66c5f4876cb7c9`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit asset receiver in ECX and callee cleanup",
  "return_semantics": "void",
  "return_type": "void",
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee"
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
    "return_semantics": "unclassified_in_EAX;void_possible",
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
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "3c234ca6f3fd3f384aca7a1f5e432f9b23981e36408331265f87f854ced2d5a9",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit asset receiver in ECX and callee cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0004"
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
        "obs-0004"
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
        "obs-0001",
        "obs-0002"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          28
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0004"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0004"
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
        "obs-0003",
        "obs-0004"
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
        "obs-0004"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0004"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    },
    {
      "based_on": [
        "obs-0004"
      ],
      "claim": "EAX is never written and no call can clobber it, so a void return is possible; this is a flag, never a type",
      "confidence": "APPROXIMATION",
      "id": "RT3",
      "value": {
        "void_possible": true
      }
    }
  ],
  "observations": [
    {
      "at": "0x00641860",
      "count": 1,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ECX + 0x1c]",
      "reg": "ECX"
    },
    {
      "at": "0x00641860",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ECX + 0x1c]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00641867",
      "id": "obs-0003",
      "index": 3,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x00550cf0",
      "target": "0x00550cf0"
    },
    {
      "at": "0x0064186c",
      "form": "RET 0x4",
      "id": "obs-0004",
      "imm": 4,
      "index": 4,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 5,
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
    "confidence": "INFERRED"
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
  "count": 5,
  "instructions": [
    {
      "address": "00641860",
      "instruction": "MOV ECX,dword ptr [ECX + 0x1c]"
    },
    {
      "address": "00641863",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00641865",
      "instruction": "JZ 0x0064186c"
    },
    {
      "address": "00641867",
      "instruction": "JMP 0x00550cf0"
    },
    {
      "address": "0064186c",
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
  "original_bytes": 8197,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit asset receiver in ECX and callee cleanup\",\n    \"return_semantics\": \"void\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:pkg_sporepedia_accessors_wave6::Pkg16AssetData,pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata,pkg_sporepedia_accessors_wave6::Pkg16WideString\",\n        \"shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:pkg_sporepedia_accessors_wave6::Pkg16AssetData,pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata,pkg_sporepedia_accessors_wave6::Pkg16WideString\",\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"sporepedia_func3ch_006417b0\",\n      \"va\": \"0x006417b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:pkg_sporepedia_accessors_wave6::Pkg16AssetData,pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata,pkg_sporepedia_accessors_wave6::Pkg16WideString\",\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"sporepedia_get_author_name_00641810\",\n      \"va\": \"0x00641810\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:pkg_sporepedia_accessors_wave6::Pkg16AssetData,pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata,pkg_sporepedia_accessors_wave6::Pkg16WideString\",\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"sporepedia_get_author_id_00641820\",\n      \"va\": \"0x00641820\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:pkg_sporepedia_accessors_wave6::Pkg16AssetData,pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata,pkg_sporepedia_accessors_wave6::Pkg16WideString\",\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"sporepedia_get_tags_00641850\",\n      \"va\": \"0x00641850\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0\",\n      \"va\": \"0x006417c0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00641867\",\n        \"direction\": \"out\",\n        \"other\": \"0x00550cf0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0163\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"Sporepedia::cSPAssetDataOTDB::GetTimeCreated\",\n  \"normalized_symbol\": \"sporepedia_get_time_created_00641860\",\n  \"observed_mechanics\": [\n    \"Loads metadata pointer from asset+0x1c and returns with RET 4 when null.\",\n    \"Tail-transfers to pkg16_time_helper_00550cf0 with metadata in ECX and destination on the stack otherwise.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"runtime validation not run\",\n      \"time helper, destination lifetime, and null-output behavior remain gated\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated
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
  "body_end": "0064186e",
  "body_span_bytes": 15,
  "body_start": "00641860",
  "callees": [
    "FUN_00550cf0"
  ],
  "callers": [],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00641860",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Sporepedia::cSPAssetDataOTDB::GetTimeCreated",
  "namespace": "Sporepedia",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cSPAssetDataOTDB *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "int64_t",
  "return_type_resolved": true,
  "rva": "0x241860",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "int64_t Sporepedia::cSPAssetDataOTDB::GetTimeCreated(cSPAssetDataOTDB * this)",
  "size_bytes": 15,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00641860",
  "vtables": {
    "referenced_by_vtables": [
      "0x013ff648",
      "0x01462764",
      "0x0147c9e8",
      "0x0147cbbc",
      "0x01489090",
      "0x014893b0"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "013ff668"
    },
    {
      "from": "01462778"
    },
    {
      "from": "0147ca18"
    },
    {
      "from": "0147cbd0"
    },
    {
      "from": "014890b0"
    },
    {
      "from": "014893d0"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__GetTimeCreated.c",
  "file": "src/reconstruction/pkg_sporepedia_accessors_wave6/sporepedia_accessors_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__GetTimeCreated.c",
    "src/reconstruction/pkg_sporepedia_accessors_wave6/sporepedia_accessors_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-sporepedia-accessors-wave6/00641860.json"
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
    "runtime validation not run",
    "time helper, destination lifetime, and null-output behavior remain gated"
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
  "pkg_sporepedia_accessors_wave6::Pkg16AssetData",
  "pkg_sporepedia_accessors_wave6::Pkg16AssetMetadata",
  "pkg_sporepedia_accessors_wave6::Pkg16WideString",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013ff648",
  "vtable:0x01462764",
  "vtable:0x0147c9e8",
  "vtable:0x0147cbbc",
  "vtable:0x01489090",
  "vtable:0x014893b0"
]
```

## Conflicts

```json
[]
```
