# Evidence 0x00848100

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c34dcef00883030378e4fabbdc7edd4d16d2850bf033a921ed71faf02f91f353`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit canvas receiver in ECX and caller cleanup",
  "return_semantics": "void",
  "return_type": "void",
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "caller"
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
    "return_semantics": "pointer_like_in_EAX",
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
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "f5c013727454166e2ca70c2be4c2efc86603d768062228c840e4e27191539ef5",
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
    "persisted_calling_convention": "x86-32 thiscall with first explicit canvas receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0009"
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
        "obs-0001",
        "obs-0002",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          52,
          56
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0006",
        "obs-0009"
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
        "obs-0009"
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
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009"
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
      "at": "0x00848100",
      "count": 3,
      "first_use": 0,
      "first_write_index": 2,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [ECX + 0x34]",
      "reg": "ECX"
    },
    {
      "at": "0x00848100",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ECX + 0x34]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00848103",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00848103",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00848103",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00848107",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ECX + 0x38]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0084810a",
      "count": 2,
      "first_use": 3,
      "first_write_index": 1,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr
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
  "count": 6,
  "instructions": [
    {
      "address": "00848100",
      "instruction": "MOV EDX,dword ptr [ECX + 0x34]"
    },
    {
      "address": "00848103",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00848107",
      "instruction": "MOV ECX,dword ptr [ECX + 0x38]"
    },
    {
      "address": "0084810a",
      "instruction": "MOV dword ptr [EAX],EDX"
    },
    {
      "address": "0084810c",
      "instruction": "MOV dword ptr [EAX + 0x4],ECX"
    },
    {
      "address": "0084810f",
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
  "original_bytes": 7432,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit canvas receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"void\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00847a40\",\n      \"va\": \"0x00847a40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00847a90\",\n      \"va\": \"0x00847a90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00847b10\",\n      \"va\": \"0x00847b10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00847b40\",\n      \"va\": \"0x00847b40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord,openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager\",\n        \"shared_vtable:vtable:0x0141ca70\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"app_canvas_00848020\",\n      \"va\": \"0x00848020\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0269\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"App::Canvas::Shutdown\",\n  \"normalized_symbol\": \"app_canvas_00848100\",\n  \"observed_mechanics\": [\n    \"Copies canvas+0x34 then canvas+0x38 to extent first and second words.\",\n    \"Does not mutate the canvas or call external ports.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-APP-CANVAS-WAVE6\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-APP-CANVAS-WAVE6\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-APP-CANVAS-WAVE6\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"extent word semantics and runtime canvas ownership remain gated\",\n      \"runtime validation not run\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_triage_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__Shutdown.c\",\n    \"file\": \"src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp\",\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__Shutdown.c\",\n      \"src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp\"\n    ],\n    \"handoffs\": [\n      \"reconstructi
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
  "body_end": "00848111",
  "body_span_bytes": 18,
  "body_start": "00848100",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00848100",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::Canvas::Shutdown",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "Canvas *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x448100",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::Canvas::Shutdown(Canvas * this)",
  "size_bytes": 18,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00848100",
  "vtables": {
    "referenced_by_vtables": [
      "0x0141ca70"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0141caa4"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__Shutdown.c",
  "file": "src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__Canvas__Shutdown.c",
    "src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-canvas-wave6/00848100.json"
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
    "extent word semantics and runtime canvas ownership remain gated",
    "runtime validation not run"
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
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvas",
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueCanvasSystems",
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueDispatchRecord",
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueMessageManager",
  "openspore::reconstruction::pkg_app_canvas_wave6::OpaqueOwnerManager",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0141ca70"
]
```

## Conflicts

```json
[]
```
