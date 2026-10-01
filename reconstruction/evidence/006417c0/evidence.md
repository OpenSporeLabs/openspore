# Evidence 0x006417c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2532324e0cf3815b36e38b4eae9bb99b60cf711e79f2c2086f0068dfd4fe5f01`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "receiver": {
    "observed_use": "none",
    "register": "ECX",
    "type": "Pkg16AssetData *",
    "width_bytes": 4
  },
  "return_observation": "FLD m32 loads the constant 0xbf800000 as a single-precision x87 value; AL and EAX are not written.",
  "return_register": "ST0",
  "stack_arguments": [
    {
      "entry_offset": "ESP+4",
      "observed_use": "none",
      "type": "std::uint64_t *",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 0,
  "termination": "RET"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/vftables.py@25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "receiver": false,
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
  "content_sha256": "3cf85609f9d002ecfddb375952a4699f0fa797cf3ef982cdce1e373cb64d5f5f",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0001"
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
        "obs-0001"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "calling convention is __thiscall: 0x006417c6 is slot 15 of the vptr-backed vftable at 0x013ff648, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 5,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 15,
        "table": "0x013ff648"
      }
    },
    {
      "based_on": [
        "obs-0001"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x006417c6",
      "form": "RET",
      "id": "obs-0001",
      "imm": null,
      "index": 1,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 2,
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
    "confidence": "OBSERVED",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": false,
    "provenance": "vftable_slot",
    "register": "ECX",
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "APPROXIMATION",
    "register": "ST0",
    "register_class": "float_or_x87",
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
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": null,
    "present": false,
    "target": null
  },
  "target": {
    "address_available": true,
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x006417c6"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_INFERRED"
}
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
  "count": 2,
  "instructions": [
    {
      "address": "006417c0",
      "instruction": "FLD float ptr [0x013eb1bc]"
    },
    {
      "address": "006417c6",
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
  "original_bytes": 7938,
  "preview": "{\n  \"abi\": {\n    \"receiver\": {\n      \"observed_use\": \"none\",\n      \"register\": \"ECX\",\n      \"type\": \"Pkg16AssetData *\",\n      \"width_bytes\": 4\n    },\n    \"return_observation\": \"FLD m32 loads the constant 0xbf800000 as a single-precision x87 value; AL and EAX are not written.\",\n    \"return_register\": \"ST0\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+4\",\n        \"observed_use\": \"none\",\n        \"type\": \"std::uint64_t *\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:Pkg16AssetData,Pkg16AssetData *\",\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 29,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:Pkg16AssetData,Pkg16AssetData *\",\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 29,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func3ch_006417b0\",\n      \"va\": \"0x006417b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_name_00641810\",\n      \"va\": \"0x00641810\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_id_00641820\",\n      \"va\": \"0x00641820\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_tags_00641850\",\n      \"va\": \"0x00641850\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_time_created_00641860\",\n      \"va\": \"0x00641860\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"A bool/uint64_t GetAssetID host interface cannot be implemented faithfully at 0x006417c0 without changing its machine behavior.\",\n    \"Reconstructing the adjacent 0x006417d0 body or changing Ghidra names would exceed the assigned three-address reconstruction scope.\",\n    \"The broad 0x013eb1bc global has no asset-specific semantic evidence.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"Pkg16AssetData\",\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": 0.98,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"global_013eb1bc\"\n    ],\n    \"manifest_callers\": [\n      \"data_pointer_xrefs_6\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0158\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [\n    \"global:0x000080bf\",\n    \"global:0x013eb1bc\",\n    \"global:DAT_013eb1bc\"\n  ],\n  \"integration_status\": \"integrated\",\n  \"name\": \"Sporepedia::cSPAssetDataOTDB::GetAssetID\",\n  \"normalized_symbol\": \"Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0\",\n  \"observed_mechanics\": [\n    \"FLD DWORD PTR [0x013eb1bc]\",\n    \"RET\",\n    \"x87 return -1.0\",\n    \"receiver and destination ignored\",\n    \"adjacent 0x006417d0 owns the SDK-shaped contract\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-16-SPOREPEDIA-ONLINE\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"gate-sporepedia-x87-address-mapping\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_x87_minus_one_constant_address_semantics_unresolved\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__GetAssetID.c\",\n    \"file\": \"src/reconstruction/pkg16_sporepedia/sporepedia_access.cpp\",\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/Spore
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
  "body_end": "006417c6",
  "body_span_bytes": 7,
  "body_start": "006417c0",
  "callees": [],
  "callers": [],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "006417c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Sporepedia::cSPAssetDataOTDB::GetAssetID",
  "namespace": "Sporepedia",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cSPAssetDataOTDB *"
    },
    {
      "name": "dst",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint64_t *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x2417c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool Sporepedia::cSPAssetDataOTDB::GetAssetID(cSPAssetDataOTDB * this, uint64_t * dst)",
  "size_bytes": 7,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006417c0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013ff648",
      "0x01462764",
      "0x0147c9e8",
      "0x0147ca30",
      "0x0147ca70",
      "0x0147caf8",
      "0x01489090",
      "0x014893b0"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "013ff684"
    },
    {
      "from": "01462794"
    },
    {
      "from": "0147ca34"
    },
    {
      "from": "0147cafc"
    },
    {
      "from": "014890cc"
    },
    {
      "from": "014893ec"
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
  "global:0x000080bf",
  "global:0x013eb1bc",
  "global:DAT_013eb1bc"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__GetAssetID.c",
  "file": "src/reconstruction/pkg16_sporepedia/sporepedia_access.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Sporepedia__cSPAssetDataOTDB__GetAssetID.c",
    "src/reconstruction/pkg16_sporepedia/sporepedia_access.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg16-sporepedia/006417c0.json"
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
    "gate-sporepedia-x87-address-mapping"
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
  "Pkg16AssetData",
  "Pkg16AssetData *",
  "std::uint64_t *"
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
  "vtable:0x0147ca30",
  "vtable:0x0147ca70",
  "vtable:0x0147caf8",
  "vtable:0x01489090",
  "vtable:0x014893b0"
]
```

## Conflicts

```json
[]
```
