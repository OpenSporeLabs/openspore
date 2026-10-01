# Evidence 0x00635700

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0bf85f649bb9c5499d46d15919b0825218111799d0eaee89d3866ac4af5c6951`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall with callee stack cleanup",
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "machine_type": "std::uint32_t",
      "native_reads": [
        "TEST byte ptr [ESP + 0x8],0x1"
      ],
      "normalized_name": "deleting",
      "note": "the slot is one word wide but only its low byte is read; after PUSH ESI it is observed at ESP+0x8",
      "position": 1,
      "width_bytes": 4
    }
  ],
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
  "content_sha256": "3d22fb31f11678d5b1cd762a7437bfe17706c915b1a392d076043ab61de6829c",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall with callee stack cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0018"
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
        "obs-0014"
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
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          4,
          100,
          104
        ],
        "register": "ECX",
        "written_through": 4
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0018"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
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
      "at": "0x00635700",
      "count": 11,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00635701",
      "count": 5,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00635701",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00635710",
      "definite": true,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x68]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00635717",
      "definite": true,
      "id": "obs-0005",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00635719",
      "count": 2,
      "first_use": 8,
      "first_write_index": 7,
      "id": "obs-0006",
      "index": 8,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x4]",
      "reg": "EAX"
    },
    {
      "at": "0x00635719",
      "definite": true,
      "id": "obs-0007",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x4]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0063571c",
      "count": 2,
      "first_use": 9,
      "first_write_index": 8,
      "id": "obs-0008",
      "index": 9,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x0063571c",
      "base": "EDX",
      "disp": null,
      "id": "obs-0009",
      "index": 9,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x0063572a",
 
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
      "address": "00635700",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00635701",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00635703",
      "instruction": "MOV dword ptr [ESI],0x13fe728"
    },
    {
      "address": "00635709",
      "instruction": "MOV dword ptr [ESI + 0x4],0x13fe718"
    },
    {
      "address": "00635710",
      "instruction": "MOV ECX,dword ptr [ESI + 0x68]"
    },
    {
      "address": "00635713",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00635715",
      "instruction": "JZ 0x0063571e"
    },
    {
      "address": "00635717",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00635719",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0063571c",
      "instruction": "CALL EDX"
    },
    {
      "address": "0063571e",
      "instruction": "MOV ECX,dword ptr [ESI + 0x64]"
    },
    {
      "address": "00635721",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00635723",
      "instruction": "JZ 0x0063572c"
    },
    {
      "address": "00635725",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00635727",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0063572a",
      "instruction": "CALL EDX"
    },
    {
      "address": "0063572c",
      "instruction": "LEA ECX,[ESI + 0x2c]"
    },
    {
      "address": "0063572f",
      "instruction": "CALL 0x00811fe0"
    },
    {
      "address": "00635734",
      "instruction": "LEA ECX,[ESI + 0x14]"
    },
    {
      "address": "00635737",
      "instruction": "CALL 0x00811fe0"
    },
    {
      "address": "0063573c",
      "instruction": "TEST byte ptr [ESP + 0x8],0x1"
    },
    {
      "address": "00635741",
      "instruction": "MOV dword ptr [ESI + 0x4],0x13ec458"
    },
    {
      "address": "00635748",
      "instruction": "MOV dword ptr [ESI],0x13eb938"
    },
    {
      "address": "0063574e",
      "instruction": "JZ 0x00635759"
    },
    {
      "address": "00635750",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00635751",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "00635756",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00635759",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "0063575b",
      "instruction": "POP ESI"
    },
    {
      "address": "0063575c",
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
  "original_bytes": 8586,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall with callee stack cleanup\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"machine_type\": \"std::uint32_t\",\n        \"native_reads\": [\n          \"TEST byte ptr [ESP + 0x8],0x1\"\n        ],\n        \"normalized_name\": \"deleting\",\n        \"note\": \"the slot is one word wide but only its low byte is read; after PUSH ESI it is observed at ESP+0x8\",\n        \"position\": 1,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"cursor_buffer_emit_0041e8b0\",\n      \"va\": \"0x0041e8b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"skin_painter_state_setup_00506590\",\n      \"va\": \"0x00506590\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"editor_row_publish_005a2010\",\n      \"va\": \"0x005a2010\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"page_visible_slots_refresh_005c0a60\",\n      \"va\": \"0x005c0a60\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 3,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, field offsets, constants, strides, vtable slot indices and the compiled terminator were read from the live Ghidra disassembly of SporeApp.exe and re-confirmed against the compiled reconstruction at -O0 and -O2 with and without NDEBUG. Imported SDK signatures are candidate labels only. Concrete vtable owners, port semantics, runtime values and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_runtime_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueImageArchive\",\n  \"cluster\": null,\n  \"confidence\": 0.91,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0063572f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00811fe0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00635737\",\n        \"direction\": \"out\",\n        \"other\": \"0x00811fe0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00635751\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x00811fe0\",\n      \"0x00f47380\"\n    ],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0148\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 4\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"image_archive_scalar_deleting_destructor_00635700\",\n  \"normalized_symbol\": \"image_archive_scalar_deleting_destructor_00635700\",\n  \"observed_mechanics\": [\n    \"Write the derived primary vtable 0x013fe728 at +0x00 and the derived secondary 0x013fe718 at +0x04 before any teardown.\",\n    \"Release the handle at +0x68 through its vtable slot +0x04 when it is non null.\",\n    \"Release the handle at +0x64 next through its vtable slot +0x04 when it is non null.\",\n    \"Destroy the service subobject at +0x2c, then the one at +0x14.\",\n    \"Read the low byte of the deleting word only after the whole teardown has run.\",\n    \"Restore the base secondary vtable 0x013ec458 at +0x04 and the base primary 0x013eb938 at +0x00.\",\n    \"Call the deallocation port 0x00f47380 with the receiver when the deleting low bit is set.\",\n    \"Return the receiver unchanged on every gate; no byte outside the two vtable slots is written.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-UI-SAFE-WAVE10\"\n    ],\n    \"manifest\": {\n      \
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
  "body_end": "0063575e",
  "body_span_bytes": 95,
  "body_start": "00635700",
  "callees": [
    "FUN_00f47380",
    "FUN_00811fe0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00635700",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00635700",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x235700",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00635700(void)",
  "size_bytes": 95,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00635700",
  "vtables": {
    "referenced_by_vtables": [
      "0x013fe718"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "013fe730"
    },
    {
      "from": "00634c73"
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
  "file": "src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10.cpp",
    "src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10.hpp",
    "src/reconstruction/pkg_ui_safe_wave10/ui_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-ui-safe-wave10/00635700.json"
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
    "The deallocation port 0x00f47380 is shared with other campaign packages and is not promoted here.",
    "The four vtable words are literal image addresses with no class attribution in the live database.",
    "The handle release slot at +0x04 and the service destructor 0x00811fe0 are opaque seams and are not promoted.",
    "The higher bits of the deleting flag are not interpreted; only its low byte is read.",
    "gate-image-archive-destructor-runtime-vtable-owners",
    "runtime validation not performed; static decompilation and disassembly only",
    "the deallocation port 0x00f47380 is shared with other campaign packages and is not promoted here",
    "the deleting flag is a one word formal whose low byte is the only bit read; the higher bits are not interpreted",
    "the four vtable words 0x013fe728, 0x013fe718, 0x013ec458 and 0x013eb938 are literal image addresses with no class attribution in the live database",
    "the two handle release slots at handle+0x04 and the service destructor 0x00811fe0 are opaque seams and are not promoted"
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
  "ImageArchivePorts",
  "OpaqueImageArchive",
  "OpaqueImageArchive*",
  "OpaqueService24",
  "OpaqueSlot",
  "unsigned int"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
