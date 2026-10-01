# Evidence 0x00b7e380

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9fb92e02083b9e7d48ca7374d98ceff66fc30353089a04bf59b5ce21d7915b21`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall (V1-VFT: vptr-backed vftable slot 38, callee pops nothing, no stack word read as argument)",
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": "ECX, used as the base of the single computation `LEA EAX,[ECX + 0x2c]` at 0x00b7e380; never saved to another register and never read from",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_semantics": "pointer to a member at offset 0x2c of the receiver",
  "return_type": "void*",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX;void_possible",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_address_taken_without_memory_access",
    "ecx_address_taken_without_memory_access: LEA takes ECX's address without any memory access through it"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "3ddc4ec4733e148d0ef3fcd2c12b7f4f01b66a5f1f6d25c2bbdc0c90c14f8751",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall (V1-VFT: vptr-backed vftable slot 38, callee pops nothing, no stack word read as argument)"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0003"
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
        "obs-0002"
      ],
      "claim": "the register receiver is undetermined: ecx_address_taken_without_memory_access",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_address_taken_without_memory_access",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "calling convention is __thiscall: 0x00b7e380 is slot 38 of the vptr-backed vftable at 0x013ff648, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 6,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 38,
        "table": "0x013ff648"
      }
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
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
      "at": "0x00b7e380",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ECX + 0x2c]",
      "reg": "EAX"
    },
    {
      "at": "0x00b7e380",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ECX + 0x2c]",
      "reg": "ECX"
    },
    {
      "at": "0x00b7e383",
      "form": "RET",
      "id": "obs-0003",
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
    "confidence": "UNKNOWN",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": null,
    "provenance": "vftable_slot",
    "reason": "ecx_address_taken_without_memory_access",
    "register": "ECX",
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": true
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
    "derived_s
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
    "va": "0x005c7500"
  },
  {
    "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
    "reconstructed": true,
    "va": "0x00b28ec0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b5ba30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c82f00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d17250"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fdc710"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fdc800"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fdeac0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fe0160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fe0e10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x010249f0"
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
  "count": 2,
  "instructions": [
    {
      "address": "00b7e380",
      "instruction": "LEA EAX,[ECX + 0x2c]"
    },
    {
      "address": "00b7e383",
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
  "original_bytes": 10010,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall (V1-VFT: vptr-backed vftable slot 38, callee pops nothing, no stack word read as argument)\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"ordinary_stack_arguments\": [],\n    \"receiver\": \"ECX, used as the base of the single computation `LEA EAX,[ECX + 0x2c]` at 0x00b7e380; never saved to another register and never read from\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer to a member at offset 0x2c of the receiver\",\n    \"return_type\": \"void*\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func3ch_006417b0\",\n      \"va\": \"0x006417b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0\",\n      \"va\": \"0x006417c0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_name_00641810\",\n      \"va\": \"0x00641810\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_id_00641820\",\n      \"va\": \"0x00641820\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_tags_00641850\",\n      \"va\": \"0x00641850\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005c7500\"\n      },\n      {\n        \"name\": \"ProfilePersistenceBoundary_run_candidate_00b28ec0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b28ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b5ba30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c82f00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d17250\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdc710\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdc800\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fdeac0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe0160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe0e10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010249f0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005c7653\",\n        \"direction\": \"in\",\n        \"other\": \"0x005c7500\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b291fc\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b28ec0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b5ba64\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b5ba30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c82f27\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c82f00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c82f45\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c82f00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d17263\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d17250\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fdc738\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fdc710\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fdc850\",\n        \"direction\": \"in\",\n  
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
  "body_end": "00b7e383",
  "body_span_bytes": 4,
  "body_start": "00b7e380",
  "callees": [],
  "callers": [
    "FUN_00fdc710",
    "FUN_00fe0160",
    "FUN_00b28ec0",
    "FUN_00fdc800",
    "FUN_010249f0",
    "FUN_00fe0e10",
    "FUN_00d17250",
    "FUN_00fdeac0",
    "FUN_00c82f00",
    "FUN_005c7500",
    "FUN_00b5ba30"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b7e380",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b7e380",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x77e380",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b7e380(void)",
  "size_bytes": 4,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b7e380",
  "vtables": {
    "referenced_by_vtables": [
      "0x013ff648",
      "0x01462764",
      "0x0147ca30",
      "0x0147ca70",
      "0x0147caf8",
      "0x0147cbbc",
      "0x01489090",
      "0x014893b0",
      "0x013ff6ac",
      "0x0147cc14",
      "0x014890f4",
      "0x01489414",
      "0x014627bc"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 21,
  "xrefs": [
    {
      "from": "00b291fc"
    },
    {
      "from": "005c7653"
    },
    {
      "from": "00c82f27"
    },
    {
      "from": "00c82f45"
    },
    {
      "from": "00fe0e52"
    },
    {
      "from": "00d17263"
    },
    {
      "from": "00fdc738"
    },
    {
      "from": "00fdc850"
    },
    {
      "from": "00fdf24c"
    },
    {
      "from": "00fe03a0"
    },
    {
      "from": "01024d1a"
    },
    {
      "from": "013ff6e0"
    },
    {
      "from": "014627f0"
    },
    {
      "from": "0147ca90"
    },
    {
      "from": "0147cb58"
    },
    {
      "from": "0147cc48"
    },
    {
      "from": "01489128"
    },
    {
      "from": "01489448"
    },
    {
      "from": "00b5ba64"
    },
    {
      "from": "00d1d3d7"
    },
    {
      "from": "0100c988"
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
    "reconstruction/staging/pkg-00b7e380-member-ptr-0x2c/member_ptr_0x2c_00b7e380.cpp",
    "reconstruction/staging/pkg-00b7e380-member-ptr-0x2c/member_ptr_0x2c_00b7e380.hpp",
    "reconstruction/staging/pkg-00b7e380-member-ptr-0x2c/member_ptr_0x2c_00b7e380_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-00b7e380-member-ptr-0x2c/00b7e380.json"
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
    "confirm the class identity behind the three vtable images; the binary has no MSVC RTTI",
    "observe one real virtual call through a slot +0x98 word and record whether the caller consumes EAX",
    "record the receiver allocation size at runtime; the 0x30 byte modelled extent is only the prefix through the reached slot",
    "record the value at receiver+0x2c and find its consumer, to establish the member's type"
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
  "medium (machine says void*; the member's type is unverifiable)",
  "openspore::reconstruction::pkg_00b7e380_member_ptr_0x2c::AbiMemberPtr00b7e380",
  "openspore::reconstruction::pkg_00b7e380_member_ptr_0x2c::Opaque",
  "openspore::reconstruction::pkg_00b7e380_member_ptr_0x2c::OpaqueReceiver",
  "openspore::reconstruction::pkg_00b7e380_member_ptr_0x2c::OpaqueReceiverVTable",
  "void*"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013ff648",
  "vtable:0x013ff6ac",
  "vtable:0x01462764",
  "vtable:0x014627bc",
  "vtable:0x0147ca30",
  "vtable:0x0147ca70",
  "vtable:0x0147caf8",
  "vtable:0x0147cbbc",
  "vtable:0x0147cc14",
  "vtable:0x01489090",
  "vtable:0x014890f4",
  "vtable:0x014893b0",
  "vtable:0x01489414"
]
```

## Conflicts

```json
[]
```
