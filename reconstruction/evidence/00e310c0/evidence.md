# Evidence 0x00e310c0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ad8f38df76f02321f542b432365608071bf88bbaa6048ac403f245a618fe5f32`

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
      "machine_type": "unsigned char",
      "native_test": "TEST byte ptr [ESP + 0x8],0x1",
      "normalized_name": "state_release_flag",
      "note": "the stack slot is one word wide but only its low byte is read; after PUSH ESI the slot is observed at ESP+0x8",
      "position": 1,
      "width_bytes": 4,
      "width_read_bytes": 1
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
  "content_sha256": "0c30f4b9974bb8553b0adaac270362e74d538b4e6eec4f38f6ad59f5caed8397",
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
      "claim": "ECX carries the receiver: 0x00e310c0 is slot 2 of the vptr-backed vftable at 0x01481940, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 2,
        "table": "0x01481940"
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
      "at": "0x00e310c0",
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
      "at": "0x00e310c1",
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
      "at": "0x00e310c1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00e310c3",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00e30f90",
      "target": "0x00e30f90"
    },
    {
      "at": "0x00e310c8",
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
      "at": "0x00e310c8",
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
      "at": "0x00e310d0",
      "id": "obs-0007",
      "index": 6,
      "kind": "CALL_
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
      "address": "00e310c0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e310c1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00e310c3",
      "instruction": "CALL 0x00e30f90"
    },
    {
      "address": "00e310c8",
      "instruction": "TEST byte ptr [ESP + 0x8],0x1"
    },
    {
      "address": "00e310cd",
      "instruction": "JZ 0x00e310d8"
    },
    {
      "address": "00e310cf",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e310d0",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "00e310d5",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e310d8",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00e310da",
      "instruction": "POP ESI"
    },
    {
      "address": "00e310db",
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
  "original_bytes": 8557,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall with callee stack cleanup\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"machine_type\": \"unsigned char\",\n        \"native_test\": \"TEST byte ptr [ESP + 0x8],0x1\",\n        \"normalized_name\": \"state_release_flag\",\n        \"note\": \"the stack slot is one word wide but only its low byte is read; after PUSH ESI the slot is observed at ESP+0x8\",\n        \"position\": 1,\n        \"width_bytes\": 4,\n        \"width_read_bytes\": 1\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned char\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned char\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"stream_probe_dispatch_004bc540\",\n      \"va\": \"0x004bc540\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned char\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"editor_bake_probe_004bf770\",\n      \"va\": \"0x004bf770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned char\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"editor_bake_select_004c4a30\",\n      \"va\": \"0x004c4a30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned char\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"skin_paint_slot_pass_005183c0\",\n      \"va\": \"0x005183c0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned char\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"skin_tex0_full_region_00518bf0\",\n      \"va\": \"0x00518bf0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned char\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"skin_tex2_uv_region_00518cf0\",\n      \"va\": \"0x00518cf0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned char\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"skin_rig_block_draw_00518f10\",\n      \"va\": \"0x00518f10\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, field offsets, constants, strides, vtable slot indices and the compiled terminator were read from the live Ghidra disassembly of SporeApp.exe and re-confirmed against the compiled reconstruction at -O0 and -O2 with and without NDEBUG. Imported SDK signatures are candidate labels only. Concrete vtable owners, port semantics, runtime values and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_runtime_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"Resource::PFRecordWrite\",\n  \"cluster\": \"resource-io\",\n  \"confidence\": 0.95,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e310c3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e30f90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e310d0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x00e30f90\",\n      \"0x00f47380\"\n    ],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0512\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"Resource::PFRecordWrite::GetState\",\n  \"normalized_symbol\": \"record_write_get_state_00e310c0\",\n  \"observed_mechanics\": [\n    \"PUSH ESI / MOV ESI,ECX: preserve the receiver across both calls.\",\n    \"CALL the destroy port 0x00e30f90 with the untouched ECX receiver, before the flag is read.\",\n    \"TEST byte ptr [ESP + 0x8],0x1: read only the low byte of the stack flag.\",\n    \"JZ skips the untrack dispatch when that low byte is zero.\",\n    \"PUSH ESI / CALL the untrack port 0x00f47380 / ADD ESP,0x4 when the low byte is set.\",\n    \"MOV EAX,ESI: return the receiver unchanged.\",\n    \"POP ESI / RET 0x4 on the single exit.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-RESOURCE-STATE-SAFE-WAVE10\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-RESOURCE-STATE-SAFE-WAVE10\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-RESOURCE-STATE-SAFE-WAVE10\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"0x00e30f90 and 0x00f47380 remain dependency-only, so the release and untrack effects are unverified in this package.\",\n      \"No original-process invocation was captured.\",\n      \"The published entry is reached only through the
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
  "body_end": "00e310dd",
  "body_span_bytes": 30,
  "body_start": "00e310c0",
  "callees": [
    "FUN_00e30f90",
    "FUN_00f47380"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e310c0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Resource::PFRecordWrite::GetState",
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
  "return_type": "FileError",
  "return_type_resolved": true,
  "rva": "0xa310c0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "FileError Resource::PFRecordWrite::GetState(IStream * this)",
  "size_bytes": 30,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e310c0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01481940"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "01481948"
    },
    {
      "from": "00e31023"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetState.c",
  "file": "src/reconstruction/pkg_resource_state_safe_wave10/resource_state_safe_wave10.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordWrite__GetState.c",
    "src/reconstruction/pkg_resource_state_safe_wave10/resource_state_safe_wave10.cpp",
    "src/reconstruction/pkg_resource_state_safe_wave10/resource_state_safe_wave10.hpp",
    "src/reconstruction/pkg_resource_state_safe_wave10/resource_state_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-resource-state-safe-wave10/00e310c0.json"
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
    "0x00e30f90 and 0x00f47380 remain dependency-only, so the release and untrack effects are unverified in this package.",
    "No original-process invocation was captured.",
    "The published entry is reached only through the 0x01481948 vtable slot and the 0x00e31020 thunk that rebases ECX by -0x8.",
    "The receiver class identity is unresolved; the target never dereferences the receiver so no field evidence exists.",
    "gate-record-write-get-state-runtime-receiver-identity"
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
  "OpaqueRecordWrite",
  "OpaqueRecordWrite*",
  "Resource::PFRecordWrite",
  "ResourceStateSafePorts",
  "unsigned char"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01481940"
]
```

## Conflicts

```json
[]
```
