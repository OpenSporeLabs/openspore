# Evidence 0x006a1600

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `012b53db50b478a4b4056df551d785b4777960f43a383c6b6885e3ad826c1bd9`

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
      "name": "other",
      "type": "PropertyList *",
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
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
  "content_sha256": "e01cca077dfe9d42b3ac7b6faa3721963faf0781a14cce40d7c0d388aaa2f10c",
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
    "indirect_calls": 1,
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
        "obs-0002"
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
        "obs-0005",
        "obs-0006",
        "obs-0014"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          52
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0014",
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
      "at": "0x006a1600",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x006a1600",
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
      "at": "0x006a1600",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a1604",
      "count": 4,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x006a1605",
      "count": 3,
      "first_use": 2,
      "first_write_index": 17,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x006a1605",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x006a160b",
      "count": 1,
      "first_use": 5,
      "first_write_index": 6,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x006a160c",
      "count": 4,
      "first_use": 6,
      "first_write_index": 0,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [EAX + 0x1c]",
      "reg": "EAX"
    },
    {
      "at": "0x006a160c",
      "definite": true,
      "id": "obs-0009",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [EAX + 
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
  "count": 27,
  "instructions": [
    {
      "address": "006a1600",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "006a1604",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a1605",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "006a1607",
      "instruction": "CMP EDI,EAX"
    },
    {
      "address": "006a1609",
      "instruction": "JZ 0x006a1633"
    },
    {
      "address": "006a160b",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a160c",
      "instruction": "MOV EBX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "006a160f",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a1610",
      "instruction": "MOV ESI,dword ptr [EAX + 0x18]"
    },
    {
      "address": "006a1613",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "006a1615",
      "instruction": "JZ 0x006a162e"
    },
    {
      "address": "006a1617",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "006a1619",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "006a161b",
      "instruction": "MOV EAX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "006a161e",
      "instruction": "LEA ECX,[ESI + 0x4]"
    },
    {
      "address": "006a1621",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a1622",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a1623",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "006a1625",
      "instruction": "CALL EAX"
    },
    {
      "address": "006a1627",
      "instruction": "ADD ESI,0x18"
    },
    {
      "address": "006a162a",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "006a162c",
      "instruction": "JNZ 0x006a1617"
    },
    {
      "address": "006a162e",
      "instruction": "INC dword ptr [EDI + 0x34]"
    },
    {
      "address": "006a1631",
      "instruction": "POP ESI"
    },
    {
      "address": "006a1632",
      "instruction": "POP EBX"
    },
    {
      "address": "006a1633",
      "instruction": "POP EDI"
    },
    {
      "address": "006a1634",
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
  "original_bytes": 8339,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"other\",\n        \"type\": \"PropertyList *\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"none\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DirectPropertyList\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 28,\n      \"symbol\": \"direct_property_list_get_property_alt_006a1e50\",\n      \"va\": \"0x006a1e50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:PropertyList *\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 19,\n      \"symbol\": \"property_list_copy_from_006a2a40\",\n      \"va\": \"0x006a2a40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 16,\n      \"symbol\": \"property_list_get_property_ids_006a3070\",\n      \"va\": \"0x006a3070\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:DirectPropertyList\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-PROPERTY-ADAPTER\",\n      \"score\": 10,\n      \"symbol\": \"app_direct_property_list_get_direct_bool_006a25a0\",\n      \"va\": \"0x006a25a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DirectPropertyList\",\n        \"shared_vtable:vtable:0x01408870\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 9,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROP-RESOURCE-SAFE-WAVE9\",\n      \"score\": 8,\n      \"symbol\": \"prop_manager_set_dev_mode_006a3300\",\n      \"va\": \"0x006a3300\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, offsets, constants, strides, and slot indices were read from the live Ghidra disassembly; imported signatures are candidate labels only. Concrete vtable and port owners, runtime values, and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"DirectPropertyList\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.94,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0201\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::DirectPropertyList::AddPropertiesFrom\",\n  \"normalized_symbol\": \"direct_property_list_add_properties_from_006a1600\",\n  \"observed_mechanics\": [\n    \"Read the stack word at ESP+0x04 into EAX and keep ECX in EDI.\",\n    \"Compare EDI with EAX; on equality jump straight to the epilogue and return without touching state.\",\n    \"Read the source end pointer from other+0x1c into EBX and the source begin pointer from other+0x18 into ESI.\",\n    \"If begin equals end, skip the loop.\",\n    \"Per entry: load this->vtable into EAX, load the entry id from [ESI] into EDX, load vtable slot +0x14 into EAX, form &entry->property with LEA ECX,[ESI+0x4], push the property pointer then the id, restore ECX to this, and call slot +0x14.\",\n    \"Advance ESI by 0x18 (the entry stride) and repeat until it equals the source end.\",\n    \"Increment the dword at this+0x34 once after the loop.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-PROPERTY-SAFE-WAVE9\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No original-process invocation or indirect-caller trace was captured.\",\n      \"The concrete vtable target behind slot +0x14 is unresolved; the model keeps it an indirect port.\",\n      \"The source list is a
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
  "body_end": "006a1636",
  "body_span_bytes": 55,
  "body_start": "006a1600",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "006a1600",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::DirectPropertyList::AddPropertiesFrom",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "DirectPropertyList *"
    },
    {
      "name": "pOther",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "PropertyList *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x2a1600",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::DirectPropertyList::AddPropertiesFrom(DirectPropertyList * this, PropertyList * pOther)",
  "size_bytes": 55,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a1600",
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
      "from": "014088a0"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__AddPropertiesFrom.c",
  "file": "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__DirectPropertyList__AddPropertiesFrom.c",
    "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp",
    "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.hpp",
    "src/reconstruction/pkg_property_safe_wave9/property_safe_wave9_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-property-safe-wave9/006a1600.json"
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
    "The concrete vtable target behind slot +0x14 is unresolved; the model keeps it an indirect port.",
    "The source list is assumed to be a stable span between +0x18 and +0x1c; runtime layout is unverified.",
    "gate-property-list-vtable-set-slot-ownership"
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
  "PropertyList *",
  "set_property",
  "void"
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
