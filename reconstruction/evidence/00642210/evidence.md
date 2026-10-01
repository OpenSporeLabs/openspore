# Evidence 0x00642210

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d0b37290fe61bf35cb5f4e3f6853e810445887c73b210048c741aae281c77fb2`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_this": null,
  "ordinary_stack_argument_slots": 1,
  "receiver_register": null,
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_semantics": "unclassified_in_EAX",
  "return_width_bytes": 4,
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
  "content_sha256": "5e6887f68afc07aa56f1e607e2e1dbe93cf9ce32b2af7fa6035a002510ca8cf4",
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
      "claim": "ECX carries the receiver: 0x00642210 is slot 0 of the vptr-backed vftable at 0x013ff648, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 0,
        "table": "0x013ff648"
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
      "at": "0x00642210",
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
      "at": "0x00642211",
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
      "at": "0x00642211",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00642213",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00642190",
      "target": "0x00642190"
    },
    {
      "at": "0x00642218",
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
      "at": "0x00642218",
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
      "at": "0x00642220",
      "id": "obs-0007",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "sporepedia_asset_destroy_00642190",
    "reconstructed": true,
    "va": "0x00642190"
  }
]
```

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
      "address": "00642210",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00642211",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00642213",
      "instruction": "CALL 0x00642190"
    },
    {
      "address": "00642218",
      "instruction": "TEST byte ptr [ESP + 0x8],0x1"
    },
    {
      "address": "0064221d",
      "instruction": "JZ 0x00642228"
    },
    {
      "address": "0064221f",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00642220",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "00642225",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00642228",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "0064222a",
      "instruction": "POP ESI"
    },
    {
      "address": "0064222b",
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
  "original_bytes": 8685,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": null,\n    \"hidden_this\": null,\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": null,\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013ff648\"\n      ],\n      \"package\": \"pkg-swarm-w1-005c0dd0\",\n      \"score\": 10,\n      \"symbol\": \"re_005c0dd0\",\n      \"va\": \"0x005c0dd0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013ff648\"\n      ],\n      \"package\": \"pkg-swarm-w1-006413d0\",\n      \"score\": 10,\n      \"symbol\": \"re_006413d0\",\n      \"va\": \"0x006413d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013ff648\"\n      ],\n      \"package\": \"pkg-swarm-w1-00641410\",\n      \"score\": 10,\n      \"symbol\": \"re_00641410\",\n      \"va\": \"0x00641410\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013ff648\"\n      ],\n      \"package\": \"pkg-swarm-w1-00641780\",\n      \"score\": 10,\n      \"symbol\": \"re_00641780\",\n      \"va\": \"0x00641780\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013ff648\"\n      ],\n      \"package\": \"pkg-swarm-w1-006417d0\",\n      \"score\": 10,\n      \"symbol\": \"re_006417d0\",\n      \"va\": \"0x006417d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013ff648\"\n      ],\n      \"package\": \"pkg-swarm-w1-00641fa0\",\n      \"score\": 10,\n      \"symbol\": \"sporepedia_predicate_00641fa0\",\n      \"va\": \"0x00641fa0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013ff648\"\n      ],\n      \"package\": \"pkg-swarm-w1-00641fd0\",\n      \"score\": 10,\n      \"symbol\": \"sporepedia_cached_handle_00641fd0\",\n      \"va\": \"0x00641fd0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013ff648\"\n      ],\n      \"package\": \"pkg-swarm-w2-00642700\",\n      \"score\": 10,\n      \"symbol\": \"sporepedia_append_five_lookups_00642700\",\n      \"va\": \"0x00642700\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"sporepedia_asset_destroy_00642190\",\n        \"reconstructed\": true,\n        \"va\": \"0x00642190\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00642213\",\n        \"direction\": \"out\",\n        \"other\": \"0x00642190\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00642220\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00642190\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0170\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"FUN_00642210\",\n  \"normalized_symbol\": \"FUN_00642210\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-w2-00642210/w2_00642210.cpp\",\n      \"reconstruction/staging/pkg-w2-00642210/w2_00642210_model_test.cpp\",\n      \"reconstruction/staging/pkg-w2-00642210/w2_00642210_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-w2-00642210/00642210.json\"\n    ],\n    \"provenance\": [\n      \"GhidraMCP /disassemble_function\",\n      \"GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089\",\n      \"knowledgegraph/triage/xrefs-2540f2ca.tsv\",\n      \"reconstruction/evidence/00642210/context.json\",\n      \"reconstruction/evidence/00642210/evidence.json\",\n      \"tools/reconstruction_tooling/abi_infer.py\"\n    ]\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Sporepedia\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sporepedia-online\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00642210\",\n    \"name\": \"FUN_00642210\",\n    \"priority\": \"P1\",\n    \"provenance\": {
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
  "body_end": "0064222d",
  "body_span_bytes": 30,
  "body_start": "00642210",
  "callees": [
    "FUN_00642190",
    "FUN_00f47380"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00642210",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00642210",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x242210",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00642210(void)",
  "size_bytes": 30,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00642210",
  "vtables": {
    "referenced_by_vtables": [
      "0x013ff648"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "013ff648"
    },
    {
      "from": "01462758"
    },
    {
      "from": "00642173"
    },
    {
      "from": "00642183"
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
  "files": [
    "reconstruction/staging/pkg-w2-00642210/w2_00642210.cpp",
    "reconstruction/staging/pkg-w2-00642210/w2_00642210_model_test.cpp",
    "reconstruction/staging/pkg-w2-00642210/w2_00642210_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00642210/00642210.json"
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
  "gates": [],
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
  "runtime_gated": false,
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
  "openspore::reconstruction::pkg_w2_00642210::OpaqueBoundaryWord",
  "openspore::reconstruction::pkg_w2_00642210::RegisterWord",
  "openspore::reconstruction::pkg_w2_00642210::StackArgument",
  "openspore::reconstruction::pkg_w2_00642210::Word",
  "std::uint32_t",
  "std::uint8_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013ff648"
]
```

## Conflicts

```json
[]
```
