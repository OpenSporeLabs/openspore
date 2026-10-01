# Evidence 0x00901930

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a97d41f8d6528c04bbbc9f87aa2eec5ac21879ea66ce6843f4cf16605bf0f783`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit writer receiver in ECX and caller cleanup",
  "return_semantics": "bool in AL from XML text slot",
  "return_type": "bool",
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
  "content_sha256": "2cc327b5b16e1e772bdf7987a1229d181fe9663a9d155220ad44337c8c9c69cd",
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
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit writer receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0014"
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
        "obs-0003"
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
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          48
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0009",
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
      "at": "0x00901930",
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
      "at": "0x00901931",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00901931",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00901931",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00901935",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ESI",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x00901937",
      "count": 3,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00901938",
      "count": 5,
      "first_use": 4,
      "first_write_index": 2,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "LEA EDI,[EAX + 0x2]",
      "reg": "EAX"
    },
    {
      "at": "0x00901940",
      "definite": true,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV DX,word ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0090194b",
      "count": 1,
      "first_use": 10,
      "first_write_index": null,
      "id": "obs-0009",
      "index": 10,
      "kind": "REG_READ",
      "raw": "MOV EDX,
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
  "count": 20,
  "instructions": [
    {
      "address": "00901930",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00901931",
      "instruction": "MOV ESI,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00901935",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00901937",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00901938",
      "instruction": "LEA EDI,[EAX + 0x2]"
    },
    {
      "address": "0090193b",
      "instruction": "JMP 0x00901940"
    },
    {
      "address": "00901940",
      "instruction": "MOV DX,word ptr [EAX]"
    },
    {
      "address": "00901943",
      "instruction": "ADD EAX,0x2"
    },
    {
      "address": "00901946",
      "instruction": "TEST DX,DX"
    },
    {
      "address": "00901949",
      "instruction": "JNZ 0x00901940"
    },
    {
      "address": "0090194b",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "0090194d",
      "instruction": "SUB EAX,EDI"
    },
    {
      "address": "0090194f",
      "instruction": "SAR EAX,0x1"
    },
    {
      "address": "00901951",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00901952",
      "instruction": "MOV EAX,dword ptr [EDX + 0x30]"
    },
    {
      "address": "00901955",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00901956",
      "instruction": "CALL EAX"
    },
    {
      "address": "00901958",
      "instruction": "POP EDI"
    },
    {
      "address": "00901959",
      "instruction": "POP ESI"
    },
    {
      "address": "0090195a",
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
  "original_bytes": 7412,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit writer receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"bool in AL from XML text slot\",\n    \"return_type\": \"bool\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_file_stream_wave6_file_stream_increment_ref_009317b0\",\n      \"va\": \"0x009317b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_file_stream_wave6_file_stream_set_utf8_path_009317e0\",\n      \"va\": \"0x009317e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_file_stream_wave6_file_stream_set_wide_path_00931810\",\n      \"va\": \"0x00931810\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_file_stream_wave6_stream_buffer_delegate_0093ae60\",\n      \"va\": \"0x0093ae60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_file_stream_wave6::FileStream,openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream,openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer,openspore::reconstruction::pkg_file_stream_wave6::StreamChild\"\n      ],\n      \"package\": \"PKG-FILE-STREAM-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_file_stream_wave6_stream_child_delegate_0093b6d0\",\n      \"va\": \"0x0093b6d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"resource-io\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0277\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"IO::XmlWriter::BeginProcessingInstruction\",\n  \"normalized_symbol\": \"pkg_file_stream_wave6_xml_writer_begin_processing_instruction_00901930\",\n  \"observed_mechanics\": [\n    \"Scans the UTF-16 instruction name through its zero terminator.\",\n    \"Calls writer vtable slot +0x30 with the original pointer and UTF-16 code-unit length and returns its result.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-FILE-STREAM-WAVE6\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-FILE-STREAM-WAVE6\",\n    \"queue_state\": \"queued\"\n  },\n  \"package\": \"PKG-FILE-STREAM-WAVE6\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"XML writer vtable ownership, instruction-name lifetime, and text port behavior remain gated\",\n      \"runtime validation not run\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": \"static_reconstruction_triage_runtime_gated\",\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/IO__XmlWriter__BeginProcessingInstruction.c\",\n    \"file\": \"src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp\",\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/IO__XmlWriter__BeginProcessingInstruction.c\",\n      \"src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp\"\n    ],\n    \"handoffs\": [\n      \"reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json\"\n    ],\n    \"metadata\": [\n      \"reconstruction/m
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
  "body_end": "0090195c",
  "body_span_bytes": 45,
  "body_start": "00901930",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00901930",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "IO::XmlWriter::BeginProcessingInstruction",
  "namespace": "IO",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "XmlWriter *"
    },
    {
      "name": "pInstructionName",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "wchar16 *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x501930",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool IO::XmlWriter::BeginProcessingInstruction(XmlWriter * this, wchar16 * pInstructionName)",
  "size_bytes": 45,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00901930",
  "vtables": {
    "referenced_by_vtables": [
      "0x0143a1c0"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0143a1ec"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/IO__XmlWriter__BeginProcessingInstruction.c",
  "file": "src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/IO__XmlWriter__BeginProcessingInstruction.c",
    "src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-file-stream-wave6/00901930.json"
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
    "XML writer vtable ownership, instruction-name lifetime, and text port behavior remain gated",
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
  "bool",
  "openspore::reconstruction::pkg_file_stream_wave6::FileStream",
  "openspore::reconstruction::pkg_file_stream_wave6::OpaqueStream",
  "openspore::reconstruction::pkg_file_stream_wave6::StreamBuffer",
  "openspore::reconstruction::pkg_file_stream_wave6::StreamChild",
  "openspore::reconstruction::pkg_file_stream_wave6::XmlWriter"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0143a1c0"
]
```

## Conflicts

```json
[]
```
