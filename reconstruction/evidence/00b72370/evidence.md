# Evidence 0x00b72370

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `cf82b7c6de125b8efdec09a23114e738439644ca170417e45d82ec4f2ddf43ee`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_receiver": "ECX is the cObjectPool_ receiver; 0x00b72373 MOV ESI,ECX",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "plain RET",
  "return_register": "none",
  "return_semantics": "void; the value returned by the dispatched slot is discarded",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": 0,
  "stack_cleanup_bytes": 0,
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "fb155bf1c65b7b4512a33ae54617d4849e5253d282c2382fe9e8d52d89fbea70",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 2,
    "persisted": "agrees",
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          32,
          36,
          40,
          44,
          48
        ],
        "register": "ECX",
        "written_through": 5
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0009",
        "obs-0017"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
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
      "at": "0x00b72370",
      "count": 4,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00b72371",
      "count": 9,
      "first_use": 1,
      "first_write_index": 3,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b72372",
      "count": 4,
      "first_use": 2,
      "first_write_index": 5,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b72373",
      "count": 2,
      "first_use": 3,
      "first_write_index": 17,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b72373",
      "definite": true,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b72375",
      "id": "obs-0006",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00883860",
      "target": "0x00883860"
    },
    {
      "at": "0x00b7237a",
      "count": 2,
      "first_use": 5,
      "first_write_index": 18,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EDI,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00b7237a",
      "definite": true,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,EAX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b723a4",
      "definite": true,
      "id": "obs-0009",
      "index": 17,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x1465004]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b723aa",
      "definite": true,
      "id": "obs-0010",
      "index": 18,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EDI]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b723ac",
      "definite": true,
      "id": "obs-0011",
      "index": 19,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x24]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b723b3",
      "count": 1,
      "first_use": 23,
      "first_write_index": 19,
      "id": "obs-0012",
      "index": 23,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00b723b3",
      "base": "EDX",
      "disp": null,
      "id": "obs-0013",
      "index"
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

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00eedd40",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e5b790",
      "0x00e80ba0",
      "0x00b72370",
      "0x00b72320",
      "0x00e780a0",
      "0x00b72160",
      "0x00b72260",
      "0x00b72270",
      "0x00b72370",
      "0x00bb4100",
      "0x00bb42a0"
    ],
    "conflict_id": "U-008-scenario-respawner",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
  "count": 31,
  "instructions": [
    {
      "address": "00b72370",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b72371",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b72372",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b72373",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b72375",
      "instruction": "CALL 0x00883860"
    },
    {
      "address": "00b7237a",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00b7237c",
      "instruction": "LEA EBX,[ESI + -0x4]"
    },
    {
      "address": "00b7237f",
      "instruction": "MOV dword ptr [ESI + 0x20],EDI"
    },
    {
      "address": "00b72382",
      "instruction": "MOV dword ptr [ESI + 0x24],EBX"
    },
    {
      "address": "00b72385",
      "instruction": "MOV dword ptr [ESI + 0x28],0x1465004"
    },
    {
      "address": "00b7238c",
      "instruction": "MOV dword ptr [ESI + 0x2c],0x8"
    },
    {
      "address": "00b72393",
      "instruction": "MOV dword ptr [ESI + 0x30],0x0"
    },
    {
      "address": "00b7239a",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00b7239c",
      "instruction": "JZ 0x00b723bd"
    },
    {
      "address": "00b7239e",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00b723a0",
      "instruction": "JZ 0x00b723bd"
    },
    {
      "address": "00b723a2",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00b723a4",
      "instruction": "MOV ECX,dword ptr [ESI + 0x1465004]"
    },
    {
      "address": "00b723aa",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00b723ac",
      "instruction": "MOV EDX,dword ptr [EAX + 0x24]"
    },
    {
      "address": "00b723af",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00b723b0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b723b1",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00b723b3",
      "instruction": "CALL EDX"
    },
    {
      "address": "00b723b5",
      "instruction": "ADD ESI,0x4"
    },
    {
      "address": "00b723b8",
      "instruction": "CMP ESI,0x20"
    },
    {
      "address": "00b723bb",
      "instruction": "JC 0x00b723a4"
    },
    {
      "address": "00b723bd",
      "instruction": "POP EDI"
    },
    {
      "address": "00b723be",
      "instruction": "POP ESI"
    },
    {
      "address": "00b723bf",
      "instruction": "POP EBX"
    },
    {
      "address": "00b723c0",
      "instruction": "RET"
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
  "original_bytes": 8277,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_receiver\": \"ECX is the cObjectPool_ receiver; 0x00b72373 MOV ESI,ECX\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"plain RET\",\n    \"return_register\": \"none\",\n    \"return_semantics\": \"void; the value returned by the dispatched slot is discarded\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": 0,\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"callee\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 8,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-core-systems\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b72375\",\n        \"direction\": \"out\",\n        \"other\": \"0x00883860\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0401\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"Simulator::cObjectPool_::DeleteObject\",\n  \"normalized_symbol\": \"Simulator::cObjectPool_::DeleteObject\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"Observe a real dispatch through the vtable word at 0x014650f0 and record the receiver instance state before and after the five stores.\",\n      \"Observe initialization and write ordering of the global word 0x016514cc through 0x00883870.\",\n      \"Observe whether any later consumer reads the receiver words at +0x28 and +0x2c published here; 0x00b79a60 is the only such consumer found statically.\",\n      \"Record the concrete target of the vtable slot at displacement 0x24 and observe its argument use and return-value handling.\",\n      \"Record the live values of the eight words at 0x01465004 and the concrete class of the object returned by 0x00883860.\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cObjectPool___DeleteObject.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cObjectPool___DeleteObject.c\",\n      \"reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370.cpp\",\n      \"reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370.hpp\",\n      \"reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-orchestrate-dogfood-00b72370/00b72370.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"queued\",\n  \"subsystem\": \"Simulator\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sim-core-systems\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analysis/ghidr
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
  "body_end": "00b723c0",
  "body_span_bytes": 81,
  "body_start": "00b72370",
  "callees": [
    "FUN_00883860"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b72370",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Simulator::cObjectPool_::DeleteObject",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cObjectPool_ *"
    },
    {
      "name": "index",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "cObjectPoolIndex"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x772370",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Simulator::cObjectPool_::DeleteObject(cObjectPool_ * this, cObjectPoolIndex index)",
  "size_bytes": 81,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b72370",
  "vtables": {
    "referenced_by_vtables": [
      "0x014650e8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "014650f0"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cObjectPool___DeleteObject.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cObjectPool___DeleteObject.c",
    "reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370.hpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-orchestrate-dogfood-00b72370/00b72370.json"
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
    "Observe a real dispatch through the vtable word at 0x014650f0 and record the receiver instance state before and after the five stores.",
    "Observe initialization and write ordering of the global word 0x016514cc through 0x00883870.",
    "Observe whether any later consumer reads the receiver words at +0x28 and +0x2c published here; 0x00b79a60 is the only such consumer found statically.",
    "Record the concrete target of the vtable slot at displacement 0x24 and observe its argument use and return-value handling.",
    "Record the live values of the eight words at 0x01465004 and the concrete class of the object returned by 0x00883860."
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "DATA",
  "openspore::reconstruction::pkg_orchestrate_dogfood_00b72370::DeleteObjectGlobals",
  "openspore::reconstruction::pkg_orchestrate_dogfood_00b72370::DeleteObjectPorts",
  "openspore::reconstruction::pkg_orchestrate_dogfood_00b72370::OpaqueDispatchTarget",
  "openspore::reconstruction::pkg_orchestrate_dogfood_00b72370::OpaqueDispatchTargetVtable",
  "openspore::reconstruction::pkg_orchestrate_dogfood_00b72370::OpaqueObjectPoolReceiver",
  "openspore::reconstruction::pkg_orchestrate_dogfood_00b72370::PublishedDeleteRecord",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x014650e8"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00eedd40",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e5b790",
      "0x00e80ba0",
      "0x00b72370",
      "0x00b72320",
      "0x00e780a0",
      "0x00b72160",
      "0x00b72260",
      "0x00b72270",
      "0x00b72370",
      "0x00bb4100",
      "0x00bb42a0"
    ],
    "conflict_id": "U-008-scenario-respawner",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
