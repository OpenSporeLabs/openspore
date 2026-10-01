# Evidence 0x006a1e50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ed9ee13e79578c80ab0532b3a1c03b2b4ce6604f6361984caca62649fd08ba50`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "property_id",
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "result",
      "type": "Property **",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x8",
  "return_register": "EAX",
  "return_type": "bool",
  "stack_cleanup_bytes": 8
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
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "46bf84eae750e4dbb9d0dc02f533571d28d96f840c3e7d76d9fb16bbd1420ae1",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 3,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0011"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0009"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0009",
        "obs-0010"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          40,
          56
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0009",
        "obs-0010",
        "obs-0011"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0009"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0011"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0013"
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
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011"
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
      "at": "0x006a1e50",
      "count": 3,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x006a1e50",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x006a1e50",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a1e54",
      "count": 3,
      "first_use": 1,
      "first_write_index": 7,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "CMP EAX,dword ptr [ECX + 0x38]",
      "reg": "ECX"
    },
    {
      "at": "0x006a1e59",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ECX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
 
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "App::PropertyList::GetPropertyAlt",
    "reconstructed": false,
    "va": "0x006a1de0"
  }
]
```

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
      "address": "006a1e50",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "006a1e54",
      "instruction": "CMP EAX,dword ptr [ECX + 0x38]"
    },
    {
      "address": "006a1e57",
      "instruction": "JNC 0x006a1e6c"
    },
    {
      "address": "006a1e59",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "006a1e5b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a1e5c",
      "instruction": "MOV EAX,dword ptr [EDX + 0x28]"
    },
    {
      "address": "006a1e5f",
      "instruction": "CALL EAX"
    },
    {
      "address": "006a1e61",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "006a1e65",
      "instruction": "MOV dword ptr [ECX],EAX"
    },
    {
      "address": "006a1e67",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "006a1e69",
      "instruction": "RET 0x8"
    },
    {
      "address": "006a1e6c",
      "instruction": "MOV dword ptr [ESP + 0x4],EAX"
    },
    {
      "address": "006a1e70",
      "instruction": "JMP 0x006a1de0"
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
  "original_bytes": 8561,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"property_id\",\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"result\",\n        \"type\": \"Property **\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"bool\",\n    \"stack_cleanup_bytes\": 8\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DirectPropertyList\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 28,\n      \"symbol\": \"direct_property_list_add_properties_from_006a1600\",\n      \"va\": \"0x006a1600\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 16,\n      \"symbol\": \"property_list_copy_from_006a2a40\",\n      \"va\": \"0x006a2a40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 16,\n      \"symbol\": \"property_list_get_property_ids_006a3070\",\n      \"va\": \"0x006a3070\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:DirectPropertyList\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-PROPERTY-ADAPTER\",\n      \"score\": 10,\n      \"symbol\": \"app_direct_property_list_get_direct_bool_006a25a0\",\n      \"va\": \"0x006a25a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DirectPropertyList\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 9,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROP-RESOURCE-SAFE-WAVE9\",\n      \"score\": 8,\n      \"symbol\": \"prop_manager_set_dev_mode_006a3300\",\n      \"va\": \"0x006a3300\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, offsets, constants, strides, and slot indices were read from the live Ghidra disassembly; imported signatures are candidate labels only. Concrete vtable and port owners, runtime values, and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"DirectPropertyList\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.92,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"App::PropertyList::GetPropertyAlt\",\n        \"reconstructed\": false,\n        \"va\": \"0x006a1de0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a1e70\",\n        \"direction\": \"out\",\n        \"other\": \"0x006a1de0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 1,\n    \"manifest_callees\": [\n      \"0x006a1de0\"\n    ],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0203\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::DirectPropertyList::GetPropertyAlt\",\n  \"normalized_symbol\": \"direct_property_list_get_property_alt_006a1e50\",\n  \"observed_mechanics\": [\n    \"Read the id word at ESP+0x04 into EAX.\",\n    \"Compare EAX against the unsigned dword at this+0x38; JNC (unsigned) diverts to the base path.\",\n    \"Fast path: load this->vtable into EDX, push the id, load vtable slot +0x28 into EAX, and call it with ECX still holding this.\",\n    \"Reload the out pointer from the adjusted stack, store the returned property pointer through it, set AL to 0x1, and return with RET 0x8.\",\n    \"Base path: write the id back to the id stack slot so the callee sees the same argument order, then tail-jump to 0x006a1de0.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-PROPERTY-SAFE-WAVE9\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"
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
  "body_end": "006a1e74",
  "body_span_bytes": 37,
  "body_start": "006a1e50",
  "callees": [
    "App::PropertyList::GetPropertyAlt"
  ],
  "callers": [],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "006a1e50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::DirectPropertyList::GetPropertyAlt",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "DirectPropertyList *"
    },
    {
      "name": "propertyID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t"
    },
    {
      "name": "result",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Property * *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x2a1e50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::DirectPropertyList::GetPropertyAlt(DirectPropertyList * this, uint32_t propertyID, Property * * result)",
  "size_bytes": 37,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a1e50",
  "vtables": {
    "referenced_by_vtables": [
      "0x01408870"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01408890"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyAlt.c",
  "file": "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__GetPropertyAlt.c",
    "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp",
    "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.hpp",
    "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-property-safe-wave9/006a1e50.json"
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
    "No original-process invocation or indirect-caller trace was captured.",
    "The base routine's parent-chain termination and inheritance policy are runtime behavior.",
    "The concrete vtable owner behind slots +0x28 and +0x20 is unresolved.",
    "gate-property-list-get-alt-parent-chain-and-vtable-ownership"
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
  "DirectPropertyList",
  "Property **",
  "base_path_defer_to_parent",
  "bool",
  "get_property_object",
  "uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01408870"
]
```

## Conflicts

```json
[]
```
