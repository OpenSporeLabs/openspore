# Evidence 0x005c5ee0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a50c758fe8c544353e6ac7f6daad2b209c0e0a2ba806aa21923b0684ed18f565`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_receiver": "ECX is the receiver word, copied to ESI at 0x005c5ee1 and returned in EAX at 0x005c5ef8",
  "ordinary_stack_argument_slots": 1,
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_semantics": "returns the receiver word itself; MOV EAX,ESI at 0x005c5ef8 runs on both the release and the skip path, and the EAX result of the 0x005c5e90 call is discarded",
  "return_type": "OpaquePaletteMain*",
  "return_width_bytes": 4,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04, read as ESP+0x08 after the PUSH ESI at 0x005c5ee0",
      "machine_type": "opaque_dword",
      "native_use": "only the low byte is read, by TEST byte ptr [ESP+0x8],0x1 at 0x005c5ee8",
      "normalized_name": "stack_word",
      "position": 1,
      "width_bytes": 4
    }
  ],
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
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
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
          1
        ],
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
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "dfb3468010da2dd937090fd2dd96120aa7fa8e623d5ebcffd5f7980c180fd15e",
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
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0011"
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
        "obs-0006"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "ECX carries the receiver: 0x005c5ee0 is slot 4 of the vptr-backed vftable at 0x013f7fc4, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 4,
        "table": "0x013f7fc4"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0011"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0011"
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
      "at": "0x005c5ee0",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005c5ee1",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005c5ee1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x005c5ee3",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x005c5e90",
      "target": "0x005c5e90"
    },
    {
      "at": "0x005c5ee8",
      "count": 1,
      "first_use": 3,
      "first_write_index": 7,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "TEST byte ptr [ESP + 0x8],0x1",
      "reg": "ESP"
    },
    {
      "at": "0x005c5ee8",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0006",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "TEST byte ptr [ESP + 0x8],0x1",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x005c5ef0",
      "id": "obs-0007",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0
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
  "count": 11,
  "instructions": [
    {
      "address": "005c5ee0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005c5ee1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005c5ee3",
      "instruction": "CALL 0x005c5e90"
    },
    {
      "address": "005c5ee8",
      "instruction": "TEST byte ptr [ESP + 0x8],0x1"
    },
    {
      "address": "005c5eed",
      "instruction": "JZ 0x005c5ef8"
    },
    {
      "address": "005c5eef",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005c5ef0",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "005c5ef5",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "005c5ef8",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "005c5efa",
      "instruction": "POP ESI"
    },
    {
      "address": "005c5efb",
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
  "original_bytes": 9867,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_receiver\": \"ECX is the receiver word, copied to ESI at 0x005c5ee1 and returned in EAX at 0x005c5ef8\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"returns the receiver word itself; MOV EAX,ESI at 0x005c5ef8 runs on both the release and the skip path, and the EAX result of the 0x005c5e90 call is discarded\",\n    \"return_type\": \"OpaquePaletteMain*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04, read as ESP+0x08 after the PUSH ESI at 0x005c5ee0\",\n        \"machine_type\": \"opaque_dword\",\n        \"native_use\": \"only the low byte is read, by TEST byte ptr [ESP+0x8],0x1 at 0x005c5ee8\",\n        \"normalized_name\": \"stack_word\",\n        \"position\": 1,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 6,\n      \"symbol\": \"FUN_005bf9d0\",\n      \"va\": \"0x005bf9d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 6,\n      \"symbol\": \"FUN_005c0100\",\n      \"va\": \"0x005c0100\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 6,\n      \"symbol\": \"FUN_005c0380\",\n      \"va\": \"0x005c0380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-15-EDITOR-SUPPORT\",\n      \"score\": 6,\n      \"symbol\": \"palette_application_setup_005c53c0\",\n      \"va\": \"0x005c53c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-15-EDITOR-SUPPORT\",\n      \"score\": 6,\n      \"symbol\": \"palette_page_construct_005c9230\",\n      \"va\": \"0x005c9230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-15-EDITOR-SUPPORT\",\n      \"score\": 6,\n      \"symbol\": \"palette_select_category_005cb240\",\n      \"va\": \"0x005cb240\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-15-EDITOR-SUPPORT\",\n      \"score\": 6,\n      \"symbol\": \"palette_editor_construct_loop_005cb5a0\",\n      \"va\": \"0x005cb5a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 6,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-support\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005c5ee3\",\n        \"direction\": \"out\",\n        \"other\": \"0x005c5e90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c5ef0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0117\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:high\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"Palettes::PaletteMain::GetCategory\",\n  \"normalized_symbol\": \"Palettes::PaletteMain::GetCategory\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"Capture both stack-word polarities at a real call site and confirm that only bit 0 decides the release.\",\n      \"Confirm the returned EAX is the receiver word on the release path, where the receiver has just been handed to the release wrapper.\",\n      \"Determine the class and base-subobject binding of the vtables at 0x013f7fd4 and 0x013f7fc4, and the role of the word at 0x013f7fd8.\",\n      \"Observe 0x005c5e90 live: its loop, the callees it invokes, and the values of the words it reads at receiver+0x04 and receiver+0x0c.\",\n      \"Observe a real virtual dispatch through the word at 0x013f7fd4 and through the subobject slot at 0x013f7fcc, and record which of the two produced the entry call and with which receiver word.\",\n      \"Record the receiver words at +0x00, +0x04 and +0x08 before and after the call and confirm that the entry itself leaves all three unchanged.\",\n      \"Resolve whether the original source identifier, argument name, and return type match the imported SDK label or the destructor-shaped reading of the body.\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"
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
  "body_end": "005c5efd",
  "body_span_bytes": 30,
  "body_start": "005c5ee0",
  "callees": [
    "FUN_005c5e90",
    "FUN_00f47380"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005c5ee0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Palettes::PaletteMain::GetCategory",
  "namespace": "Palettes",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "PaletteMain *"
    },
    {
      "name": "categoryID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "PaletteCategory *",
  "return_type_resolved": true,
  "rva": "0x1c5ee0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "PaletteCategory * Palettes::PaletteMain::GetCategory(PaletteMain * this, uint32_t categoryID)",
  "size_bytes": 30,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005c5ee0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f7fc4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "013f7fd4"
    },
    {
      "from": "005c5e83"
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
  "global:high"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Palettes__PaletteMain__GetCategory.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Palettes__PaletteMain__GetCategory.c",
    "reconstruction/staging/pkg-orchestrate-dogfood-005c5ee0/dogfood_005c5ee0.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-005c5ee0/dogfood_005c5ee0.hpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-005c5ee0/dogfood_005c5ee0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-orchestrate-dogfood-005c5ee0/005c5ee0.json"
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
    "Capture both stack-word polarities at a real call site and confirm that only bit 0 decides the release.",
    "Confirm the returned EAX is the receiver word on the release path, where the receiver has just been handed to the release wrapper.",
    "Determine the class and base-subobject binding of the vtables at 0x013f7fd4 and 0x013f7fc4, and the role of the word at 0x013f7fd8.",
    "Observe 0x005c5e90 live: its loop, the callees it invokes, and the values of the words it reads at receiver+0x04 and receiver+0x0c.",
    "Observe a real virtual dispatch through the word at 0x013f7fd4 and through the subobject slot at 0x013f7fcc, and record which of the two produced the entry call and with which receiver word.",
    "Record the receiver words at +0x00, +0x04 and +0x08 before and after the call and confirm that the entry itself leaves all three unchanged.",
    "Resolve whether the original source identifier, argument name, and return type match the imported SDK label or the destructor-shaped reading of the body."
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "DATA",
  "OpaquePaletteMain*",
  "UNCONDITIONAL_CALL",
  "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::GetCategoryPorts",
  "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::OpaquePaletteMain",
  "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::OpaquePaletteMainGetCategory005c5ee0",
  "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::OpaquePaletteMainRelease00f47380",
  "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::OpaquePaletteMainSubobjectVtable",
  "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::OpaquePaletteMainTeardown005c5e90",
  "openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0::OpaquePaletteMainVtable"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f7fc4",
  "vtable:0x013f7fd4"
]
```

## Conflicts

```json
[]
```
