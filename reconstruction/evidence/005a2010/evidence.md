# Evidence 0x005a2010

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `77ccab6a0fae46120df0227dd11c03fdd29d341de61b18c2229d31b1dd4c6714`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall with callee stack cleanup",
  "receiver_register": "ECX",
  "ret_form": "RET 0x10",
  "stack_arguments": [
    {
      "destination_slot": "+0x80",
      "entry_offset": "ESP+0x04",
      "machine_type": "float",
      "normalized_name": "row_x",
      "position": 1,
      "width_bytes": 4
    },
    {
      "destination_slot": "+0x84",
      "entry_offset": "ESP+0x08",
      "machine_type": "float",
      "normalized_name": "row_y",
      "position": 2,
      "width_bytes": 4
    },
    {
      "destination_slot": "+0x88",
      "entry_offset": "ESP+0x0c",
      "machine_type": "float",
      "normalized_name": "row_z",
      "position": 3,
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x10",
      "gate_width": "low byte only",
      "machine_type": "unsigned int",
      "native_test": "CMP byte ptr [ESP + 0x10],0x0",
      "normalized_name": "also_previous",
      "position": 4,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 16
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
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10"
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
    "ret_form": "RET 0x10",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 16,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x10"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 16,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x10",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "55d9eb02aadf65023eb50c27d94f2e969963d790662a5e71b7890d2962ca07be",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0014"
      ],
      "claim": "the callee pops 16 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 16,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0008"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 4,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0012"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          116,
          120,
          124,
          128,
          132,
          136
        ],
        "register": "ECX",
        "written_through": 6
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0014"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0014"
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
        "obs-0014"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0014"
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
      "at": "0x005a2010",
      "count": 4,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "CMP byte ptr [ESP + 0x10],0x0",
      "reg": "ESP"
    },
    {
      "at": "0x005a2010",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0002",
      "index": 0,
      "key": 16,
      "kind": "STACK_SLOT_READ",
      "raw": "CMP byte ptr [ESP + 0x10],0x0",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x005a2015",
      "
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
    "name": "Editors::cEditor::Update",
    "reconstructed": false,
    "va": "0x0058be50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e34540"
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
  "count": 14,
  "instructions": [
    {
      "address": "005a2010",
      "instruction": "CMP byte ptr [ESP + 0x10],0x0"
    },
    {
      "address": "005a2015",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "005a2019",
      "instruction": "MOV EDX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "005a201d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005a201e",
      "instruction": "MOV ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "005a2022",
      "instruction": "MOV dword ptr [ECX + 0x80],EAX"
    },
    {
      "address": "005a2028",
      "instruction": "MOV dword ptr [ECX + 0x84],EDX"
    },
    {
      "address": "005a202e",
      "instruction": "MOV dword ptr [ECX + 0x88],ESI"
    },
    {
      "address": "005a2034",
      "instruction": "JZ 0x005a203f"
    },
    {
      "address": "005a2036",
      "instruction": "MOV dword ptr [ECX + 0x74],EAX"
    },
    {
      "address": "005a2039",
      "instruction": "MOV dword ptr [ECX + 0x78],EDX"
    },
    {
      "address": "005a203c",
      "instruction": "MOV dword ptr [ECX + 0x7c],ESI"
    },
    {
      "address": "005a203f",
      "instruction": "POP ESI"
    },
    {
      "address": "005a2040",
      "instruction": "RET 0x10"
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
  "original_bytes": 8341,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall with callee stack cleanup\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x10\",\n    \"stack_arguments\": [\n      {\n        \"destination_slot\": \"+0x80\",\n        \"entry_offset\": \"ESP+0x04\",\n        \"machine_type\": \"float\",\n        \"normalized_name\": \"row_x\",\n        \"position\": 1,\n        \"width_bytes\": 4\n      },\n      {\n        \"destination_slot\": \"+0x84\",\n        \"entry_offset\": \"ESP+0x08\",\n        \"machine_type\": \"float\",\n        \"normalized_name\": \"row_y\",\n        \"position\": 2,\n        \"width_bytes\": 4\n      },\n      {\n        \"destination_slot\": \"+0x88\",\n        \"entry_offset\": \"ESP+0x0c\",\n        \"machine_type\": \"float\",\n        \"normalized_name\": \"row_z\",\n        \"position\": 3,\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x10\",\n        \"gate_width\": \"low byte only\",\n        \"machine_type\": \"unsigned int\",\n        \"native_test\": \"CMP byte ptr [ESP + 0x10],0x0\",\n        \"normalized_name\": \"also_previous\",\n        \"position\": 4,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 16\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"cursor_buffer_emit_0041e8b0\",\n      \"va\": \"0x0041e8b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"skin_painter_state_setup_00506590\",\n      \"va\": \"0x00506590\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"page_visible_slots_refresh_005c0a60\",\n      \"va\": \"0x005c0a60\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-UI-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"image_archive_scalar_deleting_destructor_00635700\",\n      \"va\": \"0x00635700\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 3,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, field offsets, constants, strides, vtable slot indices and the compiled terminator were read from the live Ghidra disassembly of SporeApp.exe and re-confirmed against the compiled reconstruction at -O0 and -O2 with and without NDEBUG. Imported SDK signatures are candidate labels only. Concrete vtable owners, port semantics, runtime values and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_runtime_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"Editors::cEditor\",\n  \"cluster\": null,\n  \"confidence\": 0.93,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"Editors::cEditor::Update\",\n        \"reconstructed\": false,\n        \"va\": \"0x0058be50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e34540\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0058cbbf\",\n        \"direction\": \"in\",\n        \"other\": \"0x0058be50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058cbf5\",\n        \"direction\": \"in\",\n        \"other\": \"0x0058be50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e34641\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e34540\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 2,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0099\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"editor_row_publish_005a2010\",\n  \"normalized_symbol\": \"editor_row_publish_005a2010\",\n  \"observed_mechanics\": [\n    \"CMP byte ptr [ESP + 0x10],0x0 first, reading only the low byte of the fourth formal.\",\n    \"MOV EAX,[ESP+0x4] / MOV EDX,[ESP+0x8] / PUSH ESI / MOV ESI,[ESP+0x10] to reach the three row words.\",\n    \"MOV [ECX+0x80],EAX / MOV
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
  "body_end": "005a2042",
  "body_span_bytes": 51,
  "body_start": "005a2010",
  "callees": [],
  "callers": [
    "FUN_00e34540",
    "Editors::cEditor::Update"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "005a2010",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005a2010",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1a2010",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005a2010(void)",
  "size_bytes": 51,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005a2010",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00e34641"
    },
    {
      "from": "0058cbbf"
    },
    {
      "from": "0058cbf5"
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
  "file": "src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10.cpp",
    "src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10.hpp",
    "src/reconstruction/pkg_editor_safe_wave10/editor_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-safe-wave10/005a2010.json"
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
    "A full-word gate test would be observably wrong; the low-byte read is fixed by the CMP at the entry.",
    "No Wine differential run against the original binary was performed.",
    "Receiver class identity unresolved; no vtable label exists for this receiver in the live database.",
    "The semantic role of the +0x74 mirrored row versus the +0x80 row is not established by static evidence.",
    "gate-editor-row-publish-receiver-identity-and-row-semantics"
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
  "Editors::cEditor",
  "OpaqueRowPublisher",
  "OpaqueRowPublisher*",
  "float",
  "unsigned int",
  "void"
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
