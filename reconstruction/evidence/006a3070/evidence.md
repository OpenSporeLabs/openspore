# Evidence 0x006a3070

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9ebeaa953b0abd3b6d7ea45930fb3640621c5cae0a824c96194a8779eaca1d5f`

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
      "name": "destination",
      "type": "uint32_t * (word vector)",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x4",
  "return_register": "none",
  "return_type": "void",
  "stack_cleanup_bytes": 4
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
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "4b7613df170b618c741967f85a7b2bde1fa357edb75d749611dddb6728c1b485",
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
    "ghidra_parameter_count": 2,
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
        "obs-0019"
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
        "obs-0002",
        "obs-0003",
        "obs-0004"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          24,
          28
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0019"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0019"
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
        "obs-0019"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0019"
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
      "at": "0x006a3070",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x006a3071",
      "count": 3,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x006a3071",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x006a3073",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x1c]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a3079",
      "definite": true,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,0x2aaaaaab",
      "reg": "EAX",
      "write_kind": "imm"
    },
    {
      "at": "0x006a3080",
      "count": 4,
      "first_use": 6,
      "first_write_index": 21,
      "id": "obs-0006",
      "index": 6,
      "kind": "REG_READ",
      "raw": "SAR EDX,0x2",
      "reg": "EDX"
    },
    {
      "at": "0x006a3085",
      "count": 3,
      "first_use": 8,
      "first_write_index": 9,
      "id": "obs-0007",
      "index": 8,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x006a3086",
      "count": 1,
      "first_use": 9,
      "first_write_index": null,
      "id": "obs-0008",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x006a3086",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0009",
      "index": 9,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "resolve
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
  "count": 31,
  "instructions": [
    {
      "address": "006a3070",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a3071",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "006a3073",
      "instruction": "MOV ECX,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "006a3076",
      "instruction": "SUB ECX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "006a3079",
      "instruction": "MOV EAX,0x2aaaaaab"
    },
    {
      "address": "006a307e",
      "instruction": "IMUL ECX"
    },
    {
      "address": "006a3080",
      "instruction": "SAR EDX,0x2"
    },
    {
      "address": "006a3083",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "006a3085",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a3086",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "006a308a",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "006a308d",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "006a308f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a3090",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "006a3092",
      "instruction": "CALL 0x004cd3c0"
    },
    {
      "address": "006a3097",
      "instruction": "MOV EAX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "006a309a",
      "instruction": "CMP EAX,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "006a309d",
      "instruction": "JZ 0x006a30b5"
    },
    {
      "address": "006a309f",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "006a30a1",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a30a2",
      "instruction": "MOV EBX,dword ptr [EAX]"
    },
    {
      "address": "006a30a4",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "006a30a6",
      "instruction": "MOV dword ptr [ECX + EDX*0x1],EBX"
    },
    {
      "address": "006a30a9",
      "instruction": "ADD EAX,0x18"
    },
    {
      "address": "006a30ac",
      "instruction": "ADD ECX,0x4"
    },
    {
      "address": "006a30af",
      "instruction": "CMP EAX,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "006a30b2",
      "instruction": "JNZ 0x006a30a2"
    },
    {
      "address": "006a30b4",
      "instruction": "POP EBX"
    },
    {
      "address": "006a30b5",
      "instruction": "POP EDI"
    },
    {
      "address": "006a30b6",
      "instruction": "POP ESI"
    },
    {
      "address": "006a30b7",
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
  "original_bytes": 8417,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"destination\",\n        \"type\": \"uint32_t * (word vector)\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"none\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:PropertyList\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 28,\n      \"symbol\": \"property_list_copy_from_006a2a40\",\n      \"va\": \"0x006a2a40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 16,\n      \"symbol\": \"direct_property_list_add_properties_from_006a1600\",\n      \"va\": \"0x006a1600\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 16,\n      \"symbol\": \"direct_property_list_get_property_alt_006a1e50\",\n      \"va\": \"0x006a1e50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:PropertyList\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 12,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:PropertyList\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 12,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:PropertyList\",\n        \"shared_vtable:vtable:0x01408820\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 9,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, offsets, constants, strides, and slot indices were read from the live Ghidra disassembly; imported signatures are candidate labels only. Concrete vtable and port owners, runtime values, and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"PropertyList\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.93,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a3092\",\n        \"direction\": \"out\",\n        \"other\": \"0x004cd3c0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x004cd3c0\"\n    ],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0219\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::PropertyList::GetPropertyIDs\",\n  \"normalized_symbol\": \"property_list_get_property_ids_006a3070\",\n  \"observed_mechanics\": [\n    \"Keep this in ESI and read the map end (this+0x1c) minus the map begin (this+0x18) into ECX.\",\n    \"Divide by the entry stride with IMUL by 0x2aaaaaab, SAR EDX by 2, then apply the SHR EAX,0x1f / ADD EAX,EDX rounding: the signed quotient is ((end-begin)/24) computed with sign correction.\",\n    \"Recover the destination vector from the frame and call 0x004cd3c0 with ECX as the destination and the signed quotient as the pushed count.\",\n    \"Reload the map begin; if begin equals the map end, skip the copy loop.\",\n    \"Per entry: read the entry id at [EAX] into EBX, read destination->begin into EDX, store the id at destination->begin + ECX*1, advance the source by 0x18 and the destination cursor by 0x4.\",\n    \"Return with RET 0x4.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-PROPERTY-SAFE-WAVE9\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No original-process invocation or indirect
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
  "body_end": "006a30b9",
  "body_span_bytes": 74,
  "body_start": "006a3070",
  "callees": [
    "FUN_004cd3c0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a3070",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::PropertyList::GetPropertyIDs",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "PropertyList *"
    },
    {
      "name": "dst",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "vector<unsigned int> *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x2a3070",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::PropertyList::GetPropertyIDs(PropertyList * this, vector<unsigned int> * dst)",
  "size_bytes": 74,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a3070",
  "vtables": {
    "referenced_by_vtables": [
      "0x01408820"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01408864"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyIDs.c",
  "file": "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetPropertyIDs.c",
    "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp",
    "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.hpp",
    "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-property-safe-wave9/006a3070.json"
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
    "The raw signed quotient is forwarded without a negative clamp; runtime behavior for a malformed span is unverified.",
    "The resize port's real allocator, capacity policy, and zero-fill are unresolved.",
    "gate-property-list-word-vector-resize-port-behavior"
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
  "PropertyList",
  "uint32_t * (word vector)",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01408820"
]
```

## Conflicts

```json
[]
```
