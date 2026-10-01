# Evidence 0x006c0550

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f46ca0f5ef2ec74535027e03ebb5b5a978c098511c6768556b70121f5a6d474c`

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
      "name": "data",
      "type": "const void *",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "size",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x8",
  "return_note": "(imported) / observed as the low byte of a 32-bit write result",
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "297ff0e1e817af8a687221efeafcd12595f27dd211098d5d8cb6ae3eaeb02b82",
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
    "ghidra_parameter_count": 1,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017"
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
        "obs-0012",
        "obs-0013"
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
        "obs-0002",
        "obs-0003",
        "obs-0008",
        "obs-0011",
        "obs-0012"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          -4,
          4,
          40
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0008",
        "obs-0011",
        "obs-0012",
        "obs-0017"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0017"
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
        "obs-0017"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0017"
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
      "at": "0x006c0550",
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
      "at": "0x006c0551",
      "count": 3,
      "first_use": 1,
      "first_write_index": 9,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x006c0551",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x006c0553",
      "count": 4,
      "first_use": 2,
      "first_write_index": 2,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "XOR AL,AL",
      "reg": "EAX"
    },
    {
      "at": "0x006c0553",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "XOR AL,AL",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x006c055e",
      "definite": true,
      "id": "obs-0006",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x10]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006c0561",
      "count": 5,
      "first_use": 7,
      "first_write_index": null,
      "id": "obs-0007",
      "index": 7,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
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
  "count": 30,
  "instructions": [
    {
      "address": "006c0550",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006c0551",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "006c0553",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "006c0555",
      "instruction": "CMP dword ptr [ESI + -0x4],0x0"
    },
    {
      "address": "006c0559",
      "instruction": "JZ 0x006c0581"
    },
    {
      "address": "006c055b",
      "instruction": "MOV EAX,dword ptr [ESI + 0x28]"
    },
    {
      "address": "006c055e",
      "instruction": "MOV EDX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "006c0561",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006c0562",
      "instruction": "LEA EDI,[ESI + 0x28]"
    },
    {
      "address": "006c0565",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "006c0567",
      "instruction": "CALL EDX"
    },
    {
      "address": "006c0569",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "006c056b",
      "instruction": "JZ 0x006c0585"
    },
    {
      "address": "006c056d",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "006c0571",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "006c0573",
      "instruction": "MOV EDX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "006c0577",
      "instruction": "MOV EAX,dword ptr [EAX + 0x38]"
    },
    {
      "address": "006c057a",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006c057b",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006c057c",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "006c057e",
      "instruction": "CALL EAX"
    },
    {
      "address": "006c0580",
      "instruction": "POP EDI"
    },
    {
      "address": "006c0581",
      "instruction": "POP ESI"
    },
    {
      "address": "006c0582",
      "instruction": "RET 0x8"
    },
    {
      "address": "006c0585",
      "instruction": "MOV EDX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "006c0588",
      "instruction": "MOV EDX,dword ptr [EDX + 0x38]"
    },
    {
      "address": "006c058b",
      "instruction": "LEA ECX,[ESI + 0x4]"
    },
    {
      "address": "006c058e",
      "instruction": "POP EDI"
    },
    {
      "address": "006c058f",
      "instruction": "POP ESI"
    },
    {
      "address": "006c0590",
      "instruction": "JMP EDX"
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
  "original_bytes": 8271,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"data\",\n        \"type\": \"const void *\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"size\",\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 0x8\",\n    \"return_note\": \"(imported) / observed as the low byte of a 32-bit write result\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"bool\",\n    \"stack_cleanup_bytes\": 8\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PROP-RESOURCE-SAFE-WAVE9\",\n      \"score\": 10,\n      \"symbol\": \"prop_manager_set_dev_mode_006a3300\",\n      \"va\": \"0x006a3300\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0140a328,vtable:0x01436954\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"record_read_data_008dc820\",\n      \"va\": \"0x008dc820\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, offsets, constants, strides, and slot indices were read from the live Ghidra disassembly; imported signatures are candidate labels only. Concrete vtable and port owners, runtime values, and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"PFRecordWrite\",\n  \"cluster\": \"resource-io\",\n  \"confidence\": 0.93,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0226\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"Resource::PFRecordWrite::Flush\",\n  \"normalized_symbol\": \"record_write_flush_006c0550\",\n  \"observed_mechanics\": [\n    \"Keep the stream subobject in ESI and zero AL.\",\n    \"Compare the full dword at ESI-0x4 against zero; on equality jump to the epilogue and return 0 with RET 0x8.\",\n    \"File path: load the file stream vtable word at this+0x28, load its slot +0x10 into EDX, and call it with ECX set to the file stream subobject.\",\n    \"TEST EAX,EAX; on zero divert to the memory path.\",\n    \"File path: recover data from the adjusted frame, load the write slot +0x38 from the file stream vtable, push size then data, set ECX to the file stream, and call it. Return that 32-bit result's low byte with RET 0x8.\",\n    \"Memory path: load the memory stream vtable word at this+0x04, load slot +0x38, form ECX as this+0x04, restore the frame, and tail-jump to the slot so the callee pops the two argument words.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-PROP-RESOURCE-SAFE-WAVE9\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-PROP-RESOURCE-SAFE-WAVE9\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-PROP-RESOURCE-SAFE-WAVE9\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No original-process invocation or indirect-caller trace was captured.\",\n      \"The concrete stream vtable owners behind slots +0x10 and +0x38 are unresolved.\",\n      \"The high three bytes of the 32-bit write result are dropped at runtime; only the low byte is architecturally observable here.\",\n      \"The runtime meaning of the gate word at record+0x1c (owner file-access flag) is unresolved.\",\n      \"gate-record-write-stream-vtable-and-owner-access-gate\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"run
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
  "body_end": "006c0591",
  "body_span_bytes": 66,
  "body_start": "006c0550",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "006c0550",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Resource::PFRecordWrite::Flush",
  "namespace": "Resource",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "IStream *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x2c0550",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool Resource::PFRecordWrite::Flush(IStream * this)",
  "size_bytes": 66,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006c0550",
  "vtables": {
    "referenced_by_vtables": [
      "0x0140a328",
      "0x01436954"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "0140a360"
    },
    {
      "from": "01436964"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__Flush.c",
  "file": "src/reconstruction/pkg_prop_resource_safe_wave9/prop_resource_safe_wave9.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__Flush.c",
    "src/reconstruction/pkg_prop_resource_safe_wave9/prop_resource_safe_wave9.cpp",
    "src/reconstruction/pkg_prop_resource_safe_wave9/prop_resource_safe_wave9.hpp",
    "src/reconstruction/pkg_prop_resource_safe_wave9/prop_resource_safe_wave9_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave9-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-prop-resource-safe-wave9/006c0550.json"
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
    "The concrete stream vtable owners behind slots +0x10 and +0x38 are unresolved.",
    "The high three bytes of the 32-bit write result are dropped at runtime; only the low byte is architecturally observable here.",
    "The runtime meaning of the gate word at record+0x1c (owner file-access flag) is unresolved.",
    "gate-record-write-stream-vtable-and-owner-access-gate"
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
  "PFRecordWrite",
  "bool (imported) / observed as the low byte of a 32-bit write result",
  "const void *",
  "uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0140a328",
  "vtable:0x01436954"
]
```

## Conflicts

```json
[]
```
