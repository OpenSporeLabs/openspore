# Evidence 0x0052e650

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `75490d58ea76d142019f7e12fbe6d17858c5c78d639f86c598e07b9d948cd16e`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall, callee stack cleanup (one 4-byte word, popped by the callee). The machine-derived ABI record (evidence pack category abi_derived) DETERMINES the convention: conventions.calling_convention = __thiscall, conventions.confidence = INFERRED, conventions.candidate_conventions = [__thiscall], conventions.ambiguities = []. The cleanup is separately OBSERVED and independent of the convention: cleanup.bytes = 4, cleanup.side = callee, cleanup.evidence = \"ret 0x4\". The reconstructed entry is a naked __thiscall member, so the source span carries a __thiscall token and the entry's own `ret $...",
  "ordinary_stack_argument_slots": 1,
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
    }
  ],
  "receiver": "ECX, read twice (PUSH ECX at 0x0052e653, MOV dword ptr [EBP + -0x4],ECX at 0x0052e654) and never dereferenced. The record's receiver sub-record now states present = true, register = ECX, provenance = vftable_slot_dispatch, confidence = INFERRED, bounds_only = true, shape = null, distinct_offsets = 0, written_through = 0. What is proven is that ECX carries the receiver and that the receiver is one 4-byte word wide (the width of PUSH ECX). What is NOT proven, and is not claimed, is the receiver's identity: no class, no receiver type, no shape, no object size, no vtable-pointer offset and no f...",
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_semantics": "unclassified_in_EAX;void_possible",
  "saved_registers": [
    "EBP"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee"
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
        "observed": false,
        "ordinal": 1,
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
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX;void_possible",
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
  "content_sha256": "895373b576b957dab1091dc1c3ce80fadaa756dbf2bb49c8ad8e4fc758916d28",
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
    "persisted_calling_convention": "__thiscall, callee stack cleanup (one 4-byte word, popped by the callee). The machine-derived ABI record (evidence pack category abi_derived) DETERMINES the convention: conventions.calling_convention = __thiscall, conventions.confidence = INFERRED, conventions.candidate_conventions = [__thiscall], conventions.ambiguities = []. The cleanup is separately OBSERVED and independent of the convention: cleanup.bytes = 4, cleanup.side = callee, cleanup.evidence = \"ret 0x4\". The reconstructed entry is a naked __thiscall member, so the source span carries a __thiscall token and the entry's own `ret $..."
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
        "obs-0009"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0005"
      ],
      "claim": "ECX carries the receiver: 0x0052e650 is slot 5 of the vptr-backed vftable at 0x013ef620, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 199,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 5,
        "table": "0x013ef620"
      }
    },
    {
      "based_on": [
        "obs-0005",
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
        "obs-0009"
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
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    },
    {
      "based_on": [
        "obs-0009"
      ],
      "claim": "EAX is never written and no call can clobber it, so a void return is possible; this is a flag, never a type",
      "confidence": "APPROXIMATION",
      "id": "RT3",
      "value": {
        "void_possible": true
      }
    }
  ],
  "observations": [
    {
      "at": "0x0052e650",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x0052e650",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
   
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
    "va": "0x0055bfb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0055c3c0"
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
  "count": 7,
  "instructions": [
    {
      "address": "0052e650",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0052e651",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0052e653",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0052e654",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "0052e657",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0052e659",
      "instruction": "POP EBP"
    },
    {
      "address": "0052e65a",
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
  "original_bytes": 12787,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall, callee stack cleanup (one 4-byte word, popped by the callee). The machine-derived ABI record (evidence pack category abi_derived) DETERMINES the convention: conventions.calling_convention = __thiscall, conventions.confidence = INFERRED, conventions.candidate_conventions = [__thiscall], conventions.ambiguities = []. The cleanup is separately OBSERVED and independent of the convention: cleanup.bytes = 4, cleanup.side = callee, cleanup.evidence = \\\"ret 0x4\\\". The reconstructed entry is a naked __thiscall member, so the source span carries a __thiscall token and the entry's own `ret $...\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"observed\": false,\n        \"ordinal\": 1,\n        \"read\": false,\n        \"size_inferred\": false,\n        \"sizes\": [\n          4\n        ],\n        \"source\": \"ret_immediate\",\n        \"written\": false\n      }\n    ],\n    \"receiver\": \"ECX, read twice (PUSH ECX at 0x0052e653, MOV dword ptr [EBP + -0x4],ECX at 0x0052e654) and never dereferenced. The record's receiver sub-record now states present = true, register = ECX, provenance = vftable_slot_dispatch, confidence = INFERRED, bounds_only = true, shape = null, distinct_offsets = 0, written_through = 0. What is proven is that ECX carries the receiver and that the receiver is one 4-byte word wide (the width of PUSH ECX). What is NOT proven, and is not claimed, is the receiver's identity: no class, no receiver type, no shape, no object size, no vtable-pointer offset and no f...\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"unclassified_in_EAX;void_possible\",\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f2194,vtable:0x013f21d8\"\n      ],\n      \"package\": \"pkg-vft-preinc-0051e340\",\n      \"score\": 10,\n      \"symbol\": \"vft_preinc_0051e340\",\n      \"va\": \"0x0051e340\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x013f2194,vtable:0x013f21d8\"\n      ],\n      \"package\": \"subobject-forward-0051e380\",\n      \"score\": 10,\n      \"symbol\": \"subobject_forward_0051e380\",\n      \"va\": \"0x0051e380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01458024,vtable:0x014599e8\"\n      ],\n      \"package\": \"pkg-swarm-w1-00a85070\",\n      \"score\": 10,\n      \"symbol\": \"re_00a85070\",\n      \"va\": \"0x00a85070\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01458788\"\n      ],\n      \"package\": \"pkg-swarm-w2-00a980b0\",\n      \"score\": 10,\n      \"symbol\": \"re_00a980b0\",\n      \"va\": \"0x00a980b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01458788\"\n      ],\n      \"package\": \"pkg-swarm-w2-00a98200\",\n      \"score\": 10,\n      \"symbol\": \"re_00a98200\",\n      \"va\": \"0x00a98200\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w2-00586700\",\n      \"score\": 6,\n      \"symbol\": \"re_00586700\",\n      \"va\": \"0x00586700\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w1-005b2490\",\n      \"score\": 6,\n      \"symbol\": \"re_005b2490\",\n      \"va\": \"0x005b2490\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w1-005ba0d0\",\n      \"score\": 6,\n      \"symbol\": \"re_005ba0d0\",\n      \"va\": \"0x005ba0d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0055bfb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0055c3c0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0055c2ca\",\n        \"direction\": \"in\",\n        \"other\": \"0x0055bfb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0055c633\",\n        \"direction\": \"in\",\n        \"other\": \"0x0055c3c0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 2,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0052\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"FUN_0052e650\",\n  \"normalized_symbol\": \"FUN_0052e650\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reas
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
  "body_end": "0052e65c",
  "body_span_bytes": 13,
  "body_start": "0052e650",
  "callees": [],
  "callers": [
    "FUN_0055c3c0",
    "FUN_0055bfb0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0052e650",
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
  "name": "FUN_0052e650",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x12e650",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0052e650(void)",
  "size_bytes": 13,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0052e650",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f2194",
      "0x01458024",
      "0x01458788",
      "0x014a4bdc",
      "0x013f21d8",
      "0x013f8be0",
      "0x013f276c",
      "0x013f2d68",
      "0x01453998",
      "0x01469cc0",
      "0x0149c848",
      "0x014a1ce4",
      "0x013ef620",
      "0x013f2698",
      "0x01412454",
      "0x01414614",
      "0x01453254",
      "0x01457e10",
      "0x014582e0",
      "0x01459844"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "0055c2ca"
    },
    {
      "from": "0055c633"
    },
    {
      "from": "013ef64c"
    },
    {
      "from": "013ef634"
    },
    {
      "from": "013f21fc"
    },
    {
      "from": "013f2200"
    },
    {
      "from": "013f2204"
    },
    {
      "from": "013f21c0"
    },
    {
      "from": "013f21c4"
    },
    {
      "from": "013f21c8"
    },
    {
      "from": "013f26c4"
    },
    {
      "from": "013f26c8"
    },
    {
      "from": "013f26cc"
    },
    {
      "from": "013f2794"
    },
    {
      "from": "013f2798"
    },
    {
      "from": "013f279c"
    },
    {
      "from": "013f2d74"
    },
    {
      "from": "013f2d78"
    },
    {
      "from": "013f2d94"
    },
    {
      "from": "013f2d98"
    },
    {
      "from": "013f2d9c"
    },
    {
      "from": "013f8c64"
    },
    {
      "from": "014123e4"
    },
    {
      "from": "014123e8"
    },
    {
      "from": "01412484"
    },
    {
      "from": "01412488"
    },
    {
      "from": "01413074"
    },
    {
      "from": "01413078"
    },
    {
      "from": "0141307c"
    },
    {
      "from": "01414644"
    },
    {
      "from": "01414648"
    },
    {
      "from": "01414948"
    },
    {
      "from": "0141494c"
    },
    {
      "from": "01414950"
    },
    {
      "from": "01457e40"
    },
    {
      "from": "01457e44"
    },
    {
      "from": "0145815c"
    },
    {
      "from": "01458160"
    },
    {
      "from": "01458334"
    },
    {
      "from": "01458338"
    },
    {
      "from": "01458d14"
    },
    {
      "from": "01458d18"
    },
    {
      "from": "0145993c"
    },
    {
      "from": "01459940"
    },
    {
      "from": "01461394"
    },
    {
      "from": "01469cd0"
    },
    {
      "from": "0146939c"
    },
    {
      "from": "0148e73c"
    },
    {
      "from": "0148e740"
    },
    {
      "from": "0148e744"
    },
    {
      "from": "01490334"
    },
    {
      "from": "01490338"
    },
    {
      "from": "0149c898"
    },
    {
      "from": "0149c8a4"
    },
    {
      "from": "0149c8b4"
    },
    {
      "from": "0149c8e0"
    },
    {
      "from": "0149cc4c"
    },
    {
      "from": "0149d278"
    },
    {
      "from": "0149d2a8"
    },
    {
      "from": "0149da98"
    },
    {
      "from": "0149dac0"
    },
    {
      "from": "0149da88"
    },
    {
      "from": "0149dad4"
    },
    {
      "from": "0149db14"
    },
    {
      "from": "0149da44"
    },
    {
      "from": "0149df14"
    },
    {
      "from": "0149df94"
    },
    {
      "from": "0149e074"
    },
    {
      "from": "0149e154"
    },
    {
      "from": "0149e1c4"
    },
    {
      "from": "0149e190"
    },
    {
      "from": "0149e21c"
    },
    {
      "from": "0149e264"
    },
    {
      "from": "0149e1ac"
    },
    {
      "from": "014a180c"
    },
    {
      "from": "014a1820"
    },
    {
      "from": "014a183c"
    },
    {
      "from": "014a1960"
    },
    {
      "from": "014a1994"
    },
    {
      "from": "014a1a10"
    },
    {
      "from": "014a1a2c"
    },
    {
      "from": "014a1a40"
    },
    {
      "from": "014a1a64"
    },
    {
      "from": "014a1aac"
    },
    {
      "from": "0149e2cc"
    },
    {
      "from": "014a1af0"
    },
    {
      "from": "014a1b18"
    },
    {
      "from": "014a1b2c"
    },
    {
      "from": "014a1b68"
    },
    {
      "from": "014a1b94"
    },
    {
      "from": "014a1c0c"
    },
    {
      "from": "014a1d0c"
    },
    {
      "from": "014a1e0c"
    },
    {
      "from": "014a18bc"
    },
    {
      "from": "014a1938"
    },
    {
      "from": "014a1fe4"
    },
    {
      "from": "014a1fa0"
    },
    {
      "from": "014a21c4"
    },
    {
      "from": "014a221c"
    },
    {
      "from": "014a222c"
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
    "reconstruction/staging/pkg-w2-0052e650/reconstruct_0052e650.cpp",
    "reconstruction/staging/pkg-w2-0052e650/reconstruct_0052e650.hpp",
    "reconstruction/staging/pkg-w2-0052e650/reconstruct_0052e650_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-0052e650/0052e650.json"
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
    "count the distinct classes whose vtable slot resolves to this address, and the slot index each uses. The derived record attributes one table and slot (0x013ef620, slot 5) out of 199 and leaves the other 198 unattributed; the binary has no MSVC RTTI. This is the only remaining blocker to naming a class, and it is the one the vftable_slot_dispatch rule works around rather than answers",
    "observe whether the pushed 4-byte word is read by anything at all, which would place this body in a fold group whose remaining members give the argument a type",
    "observe whether the receiver arriving in ECX is always an adjusted base pointer or whether some call site passes a subobject pointer directly, which would bound how many classes are folded onto this one address"
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
  "high - VOID_PROVEN from a complete, fully parsed listing with zero EAX writes, not from a string comparison",
  "openspore::reconstruction::pkg_w2_0052e650::CleanupSide52e650",
  "openspore::reconstruction::pkg_w2_0052e650::ConventionVerdict52e650",
  "openspore::reconstruction::pkg_w2_0052e650::MachineEntry52e650",
  "openspore::reconstruction::pkg_w2_0052e650::MachineExit52e650",
  "openspore::reconstruction::pkg_w2_0052e650::MemoryImage52e650",
  "openspore::reconstruction::pkg_w2_0052e650::ReceiverRegister52e650"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013ef620",
  "vtable:0x013ef7f0",
  "vtable:0x013f2194",
  "vtable:0x013f21d8",
  "vtable:0x013f2698",
  "vtable:0x013f276c",
  "vtable:0x013f2d68",
  "vtable:0x013f8be0",
  "vtable:0x013f8cd4",
  "vtable:0x013f9ab8",
  "vtable:0x014123b4",
  "vtable:0x01412454",
  "vtable:0x01413048",
  "vtable:0x01414614",
  "vtable:0x01414918",
  "vtable:0x01453254"
]
```

## Conflicts

```json
[]
```
