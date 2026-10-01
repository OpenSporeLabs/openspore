# Evidence 0x010537b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7f9be69214207112f8b9e95062e08df6c7b01618ade96d04a358d7eb7ea874d6`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x4",
      "evidence": "0x010537b0 `TEST byte ptr [ESP + 0x4],0x1` is the body's first instruction, executed before the prologue push, so ESP is still at its entry value; the operand width is BYTE, so only the low eight bits of the slot participate. abi_derived.ordinary_stack_arguments[0] agrees: entry_offset entry_ESP+0x4, sizes [1], observed true, read false, written false.",
      "ordinal": 1,
      "width": "1 byte, TESTed, not loaded"
    }
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "saved_registers": [
    "ESI"
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
  "content_sha256": "2064a1654e6d3fc9b78849d788f58a4db4a074fdbf53de62cece86ead062221f",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0010"
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
        "obs-0002"
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
        "obs-0004",
        "obs-0005"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          4
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0010"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0010"
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
        "obs-0010"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0010"
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
      "at": "0x010537b0",
      "count": 1,
      "first_use": 0,
      "first_write_index": 8,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "TEST byte ptr [ESP + 0x4],0x1",
      "reg": "ESP"
    },
    {
      "at": "0x010537b0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "TEST byte ptr [ESP + 0x4],0x1",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x010537b5",
      "count": 5,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x010537b6",
      "count": 1,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x010537b6",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x010537c8",
      "id": "obs-0006",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f47380",
      "target": "0x00f47380"
    },
    {
      "at": "0x010537cd",
      "definite": true,
      "id": "obs-0007",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x4",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x010537d0",
      "definite": true,
      "id": "obs-0008",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ESI",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x010537d2",
      "id": "obs-0009",
      "index": 10,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x010537d3",
      "form": "RET 0x4",
      "id": "obs-0010",
      "imm": 4,
      "index": 11,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 12,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete":
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
  "count": 12,
  "instructions": [
    {
      "address": "010537b0",
      "instruction": "TEST byte ptr [ESP + 0x4],0x1"
    },
    {
      "address": "010537b5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "010537b6",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "010537b8",
      "instruction": "MOV dword ptr [ESI + 0x4],0x13ec458"
    },
    {
      "address": "010537bf",
      "instruction": "MOV dword ptr [ESI],0x13eb938"
    },
    {
      "address": "010537c5",
      "instruction": "JZ 0x010537d0"
    },
    {
      "address": "010537c7",
      "instruction": "PUSH ESI"
    },
    {
      "address": "010537c8",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "010537cd",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "010537d0",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "010537d2",
      "instruction": "POP ESI"
    },
    {
      "address": "010537d3",
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
  "original_bytes": 11701,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"evidence\": \"0x010537b0 `TEST byte ptr [ESP + 0x4],0x1` is the body's first instruction, executed before the prologue push, so ESP is still at its entry value; the operand width is BYTE, so only the low eight bits of the slot participate. abi_derived.ordinary_stack_arguments[0] agrees: entry_offset entry_ESP+0x4, sizes [1], observed true, read false, written false.\",\n        \"ordinal\": 1,\n        \"width\": \"1 byte, TESTed, not loaded\"\n      }\n    ],\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"EVIDENCE COVERAGE WARN, on the pack and not on this reconstruction: 10 of 17 static categories are available; callees_dependencies, callers_dependencies, external_callees, globals, types, contradictions and semantic_hypotheses are all recorded MISSING by the collector.\",\n    \"GLOBALS WARN, set by the evidence and not by the source: the body writes two .rdata addresses (0x013eb938 at 0x010537bf and 0x013ec458 at 0x010537b8) and this target's xref export carries no data-reference edge type at all (dependencies.data_reference_count 0), so the validator has no second machine side to corroborate a mode for them. A source that stated the two immediates truthfully lands here; a source that omitted them would fail CONSTANTS instead. The write mode is read off the two MOV operands.\",\n    \"RETURN SEMANTICS WARN, set by the evidence and not by the source: the canonical ABI token for this VA is the prose 'unclassified_in_EAX', which no C declaration can spell, so the check's string comparison reports 'differs or is semantically renamed'. The machine's own return state is WIDTH_4_IN_EAX and is provable from the complete listing, and the declared type TableWordPair* is that width. Spelling the return type as the prose token to win the comparison would be a validator hack, not a reconstruction, and was not done.\",\n    \"RUNTIME is GATED at 0: no original-process trace exists in this repository, nothing was attempted, and nothing failed.\",\n    \"STATIC PASS is unreachable for this VA while the body writes two data-segment addresses and the canonical return token is prose, so the aggregate is WARN with 6 of 8 structural checks PASS. Both WARNs are stated above and neither is fixable from this package.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-core-systems\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x010537c8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0602\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 2\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"FUN_010537b0\",\n  \"normalized_symbol\": \"FUN_010537b0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n
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
  "body_end": "010537d5",
  "body_span_bytes": 38,
  "body_start": "010537b0",
  "callees": [
    "FUN_00f47380"
  ],
  "callers": [],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "010537b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_010537b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc537b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_010537b0(void)",
  "size_bytes": 38,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x010537b0",
  "vtables": {
    "referenced_by_vtables": [
      "0x0149b4d8",
      "0x0149b8b4",
      "0x0149b498",
      "0x0149b900",
      "0x0149b810",
      "0x0149ba30",
      "0x0148a7c8",
      "0x013f925c",
      "0x0148b040",
      "0x01495400",
      "0x0149b2e0",
      "0x013f7b54",
      "0x0147dba8",
      "0x013f6d6c",
      "0x0140e360",
      "0x0145ab74",
      "0x0145ae10",
      "0x0145aeb4",
      "0x0145af64",
      "0x0145afdc"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 39,
  "xrefs": [
    {
      "from": "013f6d74"
    },
    {
      "from": "0149baf0"
    },
    {
      "from": "0149bb38"
    },
    {
      "from": "013f7b5c"
    },
    {
      "from": "013f9270"
    },
    {
      "from": "013f928c"
    },
    {
      "from": "0145ab94"
    },
    {
      "from": "0145ae30"
    },
    {
      "from": "0145aed8"
    },
    {
      "from": "0145af84"
    },
    {
      "from": "0145affc"
    },
    {
      "from": "0145a6c8"
    },
    {
      "from": "0147dc0c"
    },
    {
      "from": "0148a824"
    },
    {
      "from": "0148b0a0"
    },
    {
      "from": "01495408"
    },
    {
      "from": "0149b510"
    },
    {
      "from": "0149b558"
    },
    {
      "from": "0149b5a0"
    },
    {
      "from": "0149b5e8"
    },
    {
      "from": "0149b630"
    },
    {
      "from": "0149b678"
    },
    {
      "from": "0149b6c0"
    },
    {
      "from": "0149b708"
    },
    {
      "from": "0149b750"
    },
    {
      "from": "0149b798"
    },
    {
      "from": "0149b7e0"
    },
    {
      "from": "0149b830"
    },
    {
      "from": "0149b880"
    },
    {
      "from": "0149b8d0"
    },
    {
      "from": "0149b920"
    },
    {
      "from": "0149b970"
    },
    {
      "from": "0149b9b8"
    },
    {
      "from": "0149ba00"
    },
    {
      "from": "0149ba50"
    },
    {
      "from": "0149ba98"
    },
    {
      "from": "0149b2e8"
    },
    {
      "from": "0149bf28"
    },
    {
      "from": "01053783"
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
    "reconstruction/staging/pkg-swarm-w1-010537b0/sw1_010537b0.cpp",
    "reconstruction/staging/pkg-swarm-w1-010537b0/sw1_010537b0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-010537b0/sw1_010537b0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-010537b0/010537b0.json"
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
    "A trace captures the pointer 0x00f47380 receives and the pointer the body returns in EAX, so the two are shown to be the same address.",
    "A trace captures the two words before and after 0x010537b8 and 0x010537bf, confirming the immediates 0x013eb938 and 0x013ec458 and the order the two stores happen in.",
    "A trace enters through the adjustor 0x01053780, so the -4 bias is observed arriving already applied.",
    "A trace records the value in the entry stack word at 0x010537b0 and the ZF it produces, and which arm 0x010537c5 takes.",
    "The original process is driven to an object whose +0x00 and +0x04 words hold a most-derived table pair, once with the deleting-destructor flag clear and once with it set."
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
  "TableWordPair",
  "TableWordPair* -- a four-byte pointer to the receiver"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f6d6c",
  "vtable:0x013f7b54",
  "vtable:0x013f925c",
  "vtable:0x0140e360",
  "vtable:0x0145ab74",
  "vtable:0x0145ae10",
  "vtable:0x0145aeb4",
  "vtable:0x0145af64",
  "vtable:0x0145afdc",
  "vtable:0x0147dba8",
  "vtable:0x0148a7c8",
  "vtable:0x0148b040",
  "vtable:0x01495400",
  "vtable:0x0149b2e0",
  "vtable:0x0149b498",
  "vtable:0x0149b4d8"
]
```

## Conflicts

```json
[]
```
