# Evidence 0x0052e640

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `18c11d67b1844222f8536ddec6cf9c95eeb068c14a8cd874a74eb5dfe69d5bf6`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "ret_form": "RET 0xc",
  "return_register": "EAX",
  "saved_registers": [
    "EBP"
  ],
  "stack_cleanup_bytes": 12,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0xc"
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
      "entry_ESP+0xc"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": false,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": false,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBP"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": false,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": false,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "1f1d865043ec3446900a53cb6a0a12ed3fb00c3bb5ea6f94100e9b623fbeb65a",
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
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0011"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0005"
      ],
      "claim": "ECX carries the receiver: 0x0052e640 is slot 8 of the vptr-backed vftable at 0x013f2194, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 25,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 8,
        "table": "0x013f2194"
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
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
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x0052e640",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH
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
    "name": null,
    "reconstructed": false,
    "va": "0x0050a0a0"
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
  "count": 8,
  "instructions": [
    {
      "address": "0052e640",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0052e641",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0052e643",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0052e644",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "0052e647",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "0052e649",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0052e64b",
      "instruction": "POP EBP"
    },
    {
      "address": "0052e64c",
      "instruction": "RET 0xc"
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
  "original_bytes": 8726,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": null,\n    \"ret_form\": \"RET 0xc\",\n    \"return_register\": \"EAX\",\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_cleanup_bytes\": 12,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0xc\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f2194,vtable:0x013f21d8\"\n      ],\n      \"package\": \"pkg-vft-preinc-0051e340\",\n      \"score\": 10,\n      \"symbol\": \"vft_preinc_0051e340\",\n      \"va\": \"0x0051e340\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f2194,vtable:0x013f21d8\"\n      ],\n      \"package\": \"subobject-forward-0051e380\",\n      \"score\": 10,\n      \"symbol\": \"subobject_forward_0051e380\",\n      \"va\": \"0x0051e380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01458024,vtable:0x014599e8\"\n      ],\n      \"package\": \"pkg-swarm-w1-00a85070\",\n      \"score\": 10,\n      \"symbol\": \"re_00a85070\",\n      \"va\": \"0x00a85070\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01458788\"\n      ],\n      \"package\": \"pkg-swarm-w2-00a980b0\",\n      \"score\": 10,\n      \"symbol\": \"re_00a980b0\",\n      \"va\": \"0x00a980b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01458788\"\n      ],\n      \"package\": \"pkg-swarm-w2-00a98200\",\n      \"score\": 10,\n      \"symbol\": \"re_00a98200\",\n      \"va\": \"0x00a98200\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w2-00586700\",\n      \"score\": 6,\n      \"symbol\": \"re_00586700\",\n      \"va\": \"0x00586700\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w1-005b2490\",\n      \"score\": 6,\n      \"symbol\": \"re_005b2490\",\n      \"va\": \"0x005b2490\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w1-005ba0d0\",\n      \"score\": 6,\n      \"symbol\": \"re_005ba0d0\",\n      \"va\": \"0x005ba0d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0050a0a0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0050a468\",\n        \"direction\": \"in\",\n        \"other\": \"0x0050a0a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0050a5d6\",\n        \"direction\": \"in\",\n        \"other\": \"0x0050a0a0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0051\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"FUN_0052e640\",\n  \"normalized_symbol\": \"FUN_0052e640\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No original-process trace exists in this repository for 0x0052e640, so every claim in this record is static. A differential run under Wine must confirm the answer is still 0 in the shipping build and that no runtime patch retargets the address.\",\n      \"One of the .rdata slots that point here must be observed being called with a concrete receiver before any owning class or slot offset can be named.\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero.cpp\",\n      \"reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero.hpp\",\n      \"reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-w2-0052e640/0052e640.json\"\n    ],\n    \"provenance\": [\n      \"/tmp/opencode/briefs/0052e640.json\",\n      \"GhidraMCP /disassemble_function at 0x0050a0a0, 0x0052e620, 0x0052e640, 0x0052e650, 0x0052e680, 0x0050a920\",\n      \"GhidraMCP /read_memory at 0x0052e640, 0x0050a456, 0x013f21a0, 0x0148e720, 0x01458030\",\n      \"knowledgegraph/triage/queue-f0e310e0-v6.json\",\n      \"reconstruction/evidence/0052e640/context.json\",\n      \"reconstruction/evidence/0052e640/evidence.json\"\n    ]\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Editor\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"editor-core\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRE
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
  "body_end": "0052e64e",
  "body_span_bytes": 15,
  "body_start": "0052e640",
  "callees": [],
  "callers": [
    "FUN_0050a0a0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0052e640",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_0052e640",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x12e640",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0052e640(void)",
  "size_bytes": 15,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0052e640",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f2194",
      "0x01458024",
      "0x01458788",
      "0x013f21d8",
      "0x013f276c",
      "0x013f2d68",
      "0x01453998",
      "0x013f2698",
      "0x01412454",
      "0x01414614",
      "0x01453254",
      "0x01459844",
      "0x0145990c",
      "0x014599e8",
      "0x01459a88",
      "0x01413048",
      "0x01414918",
      "0x0148e710"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 27,
  "xrefs": [
    {
      "from": "0050a468"
    },
    {
      "from": "0050a5d6"
    },
    {
      "from": "013f21f0"
    },
    {
      "from": "013f21f4"
    },
    {
      "from": "013f21b4"
    },
    {
      "from": "013f21b8"
    },
    {
      "from": "013f26b8"
    },
    {
      "from": "013f26bc"
    },
    {
      "from": "013f2788"
    },
    {
      "from": "013f278c"
    },
    {
      "from": "013f2d88"
    },
    {
      "from": "013f2d8c"
    },
    {
      "from": "01412478"
    },
    {
      "from": "01413068"
    },
    {
      "from": "0141306c"
    },
    {
      "from": "01414638"
    },
    {
      "from": "01414940"
    },
    {
      "from": "01459930"
    },
    {
      "from": "0148e734"
    },
    {
      "from": "01453274"
    },
    {
      "from": "01459a0c"
    },
    {
      "from": "014539b4"
    },
    {
      "from": "014539b8"
    },
    {
      "from": "01458044"
    },
    {
      "from": "014587a8"
    },
    {
      "from": "01459864"
    },
    {
      "from": "01459aa8"
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
    "reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero.cpp",
    "reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero.hpp",
    "reconstruction/staging/pkg-w2-0052e640/52e640_spill_zero_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-0052e640/0052e640.json"
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
    "No original-process trace exists in this repository for 0x0052e640, so every claim in this record is static. A differential run under Wine must confirm the answer is still 0 in the shipping build and that no runtime patch retargets the address.",
    "One of the .rdata slots that point here must be observed being called with a concrete receiver before any owning class or slot offset can be named."
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f2194",
  "vtable:0x013f21d8",
  "vtable:0x013f2698",
  "vtable:0x013f276c",
  "vtable:0x013f2d68",
  "vtable:0x01412454",
  "vtable:0x01413048",
  "vtable:0x01414614",
  "vtable:0x01414918",
  "vtable:0x01453254",
  "vtable:0x01453998",
  "vtable:0x01458024",
  "vtable:0x01458788",
  "vtable:0x01459844",
  "vtable:0x0145990c",
  "vtable:0x014599e8"
]
```

## Conflicts

```json
[]
```
