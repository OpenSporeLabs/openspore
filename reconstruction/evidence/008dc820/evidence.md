# Evidence 0x008dc820

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9f8bb03faf2f953c324e24eda887b4aed66d20e9b932bd819f11e824eb15e90e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit record receiver in ECX and caller cleanup",
  "return_semantics": "void",
  "return_type": "void",
  "stack_cleanup_bytes": 8,
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
  "content_sha256": "fa6452655d6949df1eb131ce22101360e982facbd60ab70d50feea88bb97065a",
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
    "persisted_calling_convention": "x86-32 thiscall with first explicit record receiver in ECX and caller cleanup"
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
        "obs-0003",
        "obs-0004",
        "obs-0008",
        "obs-0011",
        "obs-0012"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4,
          40
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
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
      "at": "0x008dc820",
      "count": 5,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x008dc821",
      "count": 5,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x008dc822",
      "count": 3,
      "first_use": 2,
      "first_write_index": 6,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x008dc822",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x008dc824",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EDI + 0x28]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x008dc827",
      "count": 3,
      "first_use": 4,
      "first_write_index": 3,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x10]",
      "reg": "EAX"
    },
    {
      "at": "0x008dc827",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_W
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
      "address": "008dc820",
      "instruction": "PUSH ESI"
    },
    {
      "address": "008dc821",
      "instruction": "PUSH EDI"
    },
    {
      "address": "008dc822",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "008dc824",
      "instruction": "MOV EAX,dword ptr [EDI + 0x28]"
    },
    {
      "address": "008dc827",
      "instruction": "MOV EDX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "008dc82a",
      "instruction": "LEA ESI,[EDI + 0x28]"
    },
    {
      "address": "008dc82d",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "008dc82f",
      "instruction": "CALL EDX"
    },
    {
      "address": "008dc831",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "008dc833",
      "instruction": "JZ 0x008dc84d"
    },
    {
      "address": "008dc835",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "008dc839",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "008dc83b",
      "instruction": "MOV EDX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "008dc83f",
      "instruction": "MOV EAX,dword ptr [EAX + 0x28]"
    },
    {
      "address": "008dc842",
      "instruction": "PUSH ECX"
    },
    {
      "address": "008dc843",
      "instruction": "PUSH EDX"
    },
    {
      "address": "008dc844",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "008dc846",
      "instruction": "CALL EAX"
    },
    {
      "address": "008dc848",
      "instruction": "POP EDI"
    },
    {
      "address": "008dc849",
      "instruction": "POP ESI"
    },
    {
      "address": "008dc84a",
      "instruction": "RET 0x8"
    },
    {
      "address": "008dc84d",
      "instruction": "MOV EDX,dword ptr [EDI + 0x4]"
    },
    {
      "address": "008dc850",
      "instruction": "MOV EDX,dword ptr [EDX + 0x28]"
    },
    {
      "address": "008dc853",
      "instruction": "LEA ECX,[EDI + 0x4]"
    },
    {
      "address": "008dc856",
      "instruction": "POP EDI"
    },
    {
      "address": "008dc857",
      "instruction": "POP ESI"
    },
    {
      "address": "008dc858",
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
  "original_bytes": 6680,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit record receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"void\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite\",\n        \"shared_vtable:vtable:0x014368c4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"record_write_seek_008dcab0\",\n      \"va\": \"0x008dcab0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite\",\n        \"shared_vtable:vtable:0x014368c4\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"record_write_read_008dcb70\",\n      \"va\": \"0x008dcb70\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead,openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite\"\n      ],\n      \"package\": \"PKG-RECORD-IO-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"fixed_memory_stream_seek_0093b950\",\n      \"va\": \"0x0093b950\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x0140a328,vtable:0x01436954\"\n      ],\n      \"package\": \"PKG-PROP-RESOURCE-SAFE-WAVE9\",\n      \"score\": 4,\n      \"symbol\": \"record_write_flush_006c0550\",\n      \"va\": \"0x006c0550\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"resource-io\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0273\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"Resource::PFRecordRead::ReadData\",\n  \"normalized_symbol\": \"record_read_data_008dc820\",\n  \"observed_mechanics\": [\n    \"Calls primary stream state at record+0x28 and primary read slot +0x28 when nonzero.\",\n    \"Falls back to stream at record+0x04 and its read slot +0x28 when the primary state is zero.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-RECORD-IO-WAVE6\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-RECORD-IO-WAVE6\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-RECORD-IO-WAVE6\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"runtime validation not run\",\n      \"stream vtable implementations, record initialization, and data ownership remain gated\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_triage_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordRead__ReadData.c\",\n    \"file\": \"src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp\",\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordRead__ReadData.c\",\n      \"src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp\"\n    ],\n    \"handoffs\": [\n      \"reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json\"\n    ],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-record-io-wave6/008dc820.json\"\n    ],\n    \"provenance\": [\n      \"reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json\",\n      \"reconstruction/metadata/pkg-record-io-wave6/008dc820.json\",\n      \"reconstruction/staging/pkg-record-io-wave6/pkg_record_io_wave6.cpp\",\n      \"reconstruction/staging/pkg-record-io-wave6/pkg_record_io_wave6_model_test.cpp\"\n    ]\n  },\n  \"status\": \"reconstructed\",\n  \"subsystem\": \"IO.RecordIO\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"resource-io\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordRead__ReadData.c\",\n    \"dependencies\": [\n      \"runtime-crt-stl\"\n    ],\n    \"evidence\": \"CONFIRMED\",\n    \"k
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
  "body_end": "008dc859",
  "body_span_bytes": 58,
  "body_start": "008dc820",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "008dc820",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Resource::PFRecordRead::ReadData",
  "namespace": "Resource",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "PFRecordRead *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x4dc820",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Resource::PFRecordRead::ReadData(PFRecordRead * this)",
  "size_bytes": 58,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x008dc820",
  "vtables": {
    "referenced_by_vtables": [
      "0x014368c4",
      "0x0140a328",
      "0x01436954"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "0140a350"
    },
    {
      "from": "01436954"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordRead__ReadData.c",
  "file": "src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFRecordRead__ReadData.c",
    "src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-record-io-wave6/008dc820.json"
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
    "runtime validation not run",
    "stream vtable implementations, record initialization, and data ownership remain gated"
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
  "openspore::reconstruction::pkg_record_io_wave6::OpaqueFixedMemoryStream",
  "openspore::reconstruction::pkg_record_io_wave6::OpaqueIStream",
  "openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordRead",
  "openspore::reconstruction::pkg_record_io_wave6::OpaqueRecordWrite",
  "openspore::reconstruction::pkg_record_io_wave6::RecordWritePorts",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0140a328",
  "vtable:0x014368c4",
  "vtable:0x01436954"
]
```

## Conflicts

```json
[]
```
