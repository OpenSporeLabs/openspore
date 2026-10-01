# Evidence 0x0057d6f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d517f88a7bd13c7441a255bfada0c7fdcfd1a971da67c4ee6d6aec42748a62c3`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_observation": "The record classifies the last write to EAX as aggregate_unknown (RT2) and the envelope as unclassified_in_EAX. The listing says more than that and this package reads only the listing: the single write to EAX is MOV EAX,ESI at 0x0057d708, a register-to-register move of the value ESI has held since 0x0057d6f1, so the returned value is the incoming receiver verbatim and 32 bits wide. Both paths to the single reachable RET pass through 0x0057d708, so the must-analysis has no uninitialised path. The C type is Receiver *, which is the width-computable spelling of a 4-byte value that the machine ...",
  "return_register": "EAX",
  "return_semantics": "unclassified_in_EAX",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
  "content_sha256": "ff98013b6b82737331858b23b4ce81fe8f5284ba4d573a570cf1178027007d90",
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
    "persisted_calling_convention": null
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
      "claim": "ECX carries the receiver: 0x0057d6f0 is slot 2 of the vptr-backed vftable at 0x013f57f8, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 2,
        "table": "0x013f57f8"
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
      "at": "0x0057d6f0",
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
      "at": "0x0057d6f1",
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
      "at": "0x0057d6f1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x0057d6f3",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00579e20",
      "target": "0x00579e20"
    },
    {
      "at": "0x0057d6f8",
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
      "at": "0x0057d6f8",
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
      "at": "0x0057d700",
      "id": "obs-0007",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00
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
      "address": "0057d6f0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0057d6f1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0057d6f3",
      "instruction": "CALL 0x00579e20"
    },
    {
      "address": "0057d6f8",
      "instruction": "TEST byte ptr [ESP + 0x8],0x1"
    },
    {
      "address": "0057d6fd",
      "instruction": "JZ 0x0057d708"
    },
    {
      "address": "0057d6ff",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0057d700",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "0057d705",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0057d708",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "0057d70a",
      "instruction": "POP ESI"
    },
    {
      "address": "0057d70b",
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
  "original_bytes": 9594,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_observation\": \"The record classifies the last write to EAX as aggregate_unknown (RT2) and the envelope as unclassified_in_EAX. The listing says more than that and this package reads only the listing: the single write to EAX is MOV EAX,ESI at 0x0057d708, a register-to-register move of the value ESI has held since 0x0057d6f1, so the returned value is the incoming receiver verbatim and 32 bits wide. Both paths to the single reachable RET pass through 0x0057d708, so the must-analysis has no uninitialised path. The C type is Receiver *, which is the width-computable spelling of a 4-byte value that the machine ...\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"pkg-swarm-w2-00586700\",\n      \"score\": 10,\n      \"symbol\": \"re_00586700\",\n      \"va\": \"0x00586700\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"pkg-swarm-w1-005b2490\",\n      \"score\": 10,\n      \"symbol\": \"re_005b2490\",\n      \"va\": \"0x005b2490\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"pkg-swarm-w1-005ba0d0\",\n      \"score\": 10,\n      \"symbol\": \"re_005ba0d0\",\n      \"va\": \"0x005ba0d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"pkg-editor-child-007f30d0\",\n      \"score\": 10,\n      \"symbol\": \"FUN_007f30d0\",\n      \"va\": \"0x007f30d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-vft-preinc-0051e340\",\n      \"score\": 6,\n      \"symbol\": \"vft_preinc_0051e340\",\n      \"va\": \"0x0051e340\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"subobject-forward-0051e380\",\n      \"score\": 6,\n      \"symbol\": \"subobject_forward_0051e380\",\n      \"va\": \"0x0051e380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w1-00a85070\",\n      \"score\": 6,\n      \"symbol\": \"re_00a85070\",\n      \"va\": \"0x00a85070\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w2-00a980b0\",\n      \"score\": 6,\n      \"symbol\": \"re_00a980b0\",\n      \"va\": \"0x00a980b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0057d6f3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00579e20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057d700\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0069\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:0x013f57f8\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_0057d6f0\",\n  \"normalized_symbol\": \"FUN_0057d6f0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"runtime validation not run: no original-process trace exists in this repository, so nothing about the original game has been observed for this VA\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0.cpp\",\n      \"reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0_model_test.cpp\",\n      \"reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-editor-w1-0057d6f0/0057d6f0.json\"\n    ],\n    \"provenance\": [\n      \"GhidraMCP /disassemble_bytes @ 0x0057a590..0x0057a5d3 (the three this-adjusting stubs) and @ 0x00f47380..0x00f473a7\",\n      \"GhidraMCP /disassemble_function @ 0x0057d6f0, @ 0x00579e20 and @ 0x005b2490\",\n      \"GhidraMCP /read_memory @ 0x0057d6f0 (30 bytes) and @ 0x013f57f8 (32 bytes)\",\n      \"reconstruction
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
  "body_end": "0057d70d",
  "body_span_bytes": 30,
  "body_start": "0057d6f0",
  "callees": [
    "FUN_00579e20",
    "FUN_00f47380"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0057d6f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_0057d6f0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x17d6f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0057d6f0(void)",
  "size_bytes": 30,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0057d6f0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f57f8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "013f5800"
    },
    {
      "from": "0057a5a3"
    },
    {
      "from": "0057a5b3"
    },
    {
      "from": "0057a5c3"
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
  "global:0x013f57f8"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0.cpp",
    "reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0_model_test.cpp",
    "reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-editor-w1-0057d6f0/0057d6f0.json"
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
    "runtime validation not run: no original-process trace exists in this repository, so nothing about the original game has been observed for this VA"
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "Receiver *",
  "openspore::reconstruction::pkg_editor_w1_0057d6f0::OptionWord",
  "openspore::reconstruction::pkg_editor_w1_0057d6f0::Receiver"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f57f8"
]
```

## Conflicts

```json
[]
```
