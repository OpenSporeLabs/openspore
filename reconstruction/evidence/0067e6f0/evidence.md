# Evidence 0x0067e6f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ffc36453ffba0906da160810be64a4139e3c5e06daebb7a64cce2ffa943f3e71`

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
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x4",
      "ordinal": 1,
      "read": true,
      "read_at": "0x0067e703: MOV EBX,dword ptr [ESP + 0x10] (three register saves already pushed, so +0x10 resolves to entry_ESP+0x4)",
      "size": 4,
      "written": false
    }
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "EDI",
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
      "EBX",
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
  "content_sha256": "2b1a61e79ed6c556ba84ac52ce81d843d86c4ef0befa0c23e146b57119630b30",
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
    "ghidra_parameter_count": 2,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0020"
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
        "obs-0007"
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
        "obs-0001",
        "obs-0003",
        "obs-0009",
        "obs-0010"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          80,
          96,
          100
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0003",
        "obs-0009",
        "obs-0010",
        "obs-0020"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0020"
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
        "obs-0020"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020"
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
      "at": "0x0067e6f0",
      "count": 4,
      "first_use": 0,
      "first_write_index": 10,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "CMP byte ptr [ECX + 0x64],0x0",
      "reg": "ECX"
    },
    {
      "at": "0x0067e6f6",
      "count": 3,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0002",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0067e6f7",
      "definite": true,
      "id": "obs-0003",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ECX + 0x50]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0067e6fa",
      "count": 2,
      "first_use": 4,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x0067e702",
      "count": 2,
      "first_use": 8,
      "first_write_index": 9,
      "id": "obs-0005",
      "index": 8,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x0067e703",
      "count": 1,
      "first_use": 9,
      "first_write_index": 19,
      "id": "obs-0006",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x0067e703",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0007",
      "index": 9,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0067e703",
      "definite": true,
      "id": "obs-0008",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESP + 0x10]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0067e707",
      "definite": true,
      "id": "obs-0009",
   
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
  "count": 26,
  "instructions": [
    {
      "address": "0067e6f0",
      "instruction": "CMP byte ptr [ECX + 0x64],0x0"
    },
    {
      "address": "0067e6f4",
      "instruction": "JZ 0x0067e726"
    },
    {
      "address": "0067e6f6",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0067e6f7",
      "instruction": "MOV ESI,dword ptr [ECX + 0x50]"
    },
    {
      "address": "0067e6fa",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0067e6fb",
      "instruction": "LEA EDI,[ECX + 0x4c]"
    },
    {
      "address": "0067e6fe",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "0067e700",
      "instruction": "JZ 0x0067e724"
    },
    {
      "address": "0067e702",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0067e703",
      "instruction": "MOV EBX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "0067e707",
      "instruction": "MOV ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "0067e70a",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "0067e70c",
      "instruction": "MOV EDX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "0067e70f",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0067e710",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "0067e712",
      "instruction": "CALL EDX"
    },
    {
      "address": "0067e714",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0067e715",
      "instruction": "CALL 0x00921580"
    },
    {
      "address": "0067e71a",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "0067e71c",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0067e71f",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "0067e721",
      "instruction": "JNZ 0x0067e707"
    },
    {
      "address": "0067e723",
      "instruction": "POP EBX"
    },
    {
      "address": "0067e724",
      "instruction": "POP EDI"
    },
    {
      "address": "0067e725",
      "instruction": "POP ESI"
    },
    {
      "address": "0067e726",
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
  "original_bytes": 7136,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x4\",\n        \"ordinal\": 1,\n        \"read\": true,\n        \"read_at\": \"0x0067e703: MOV EBX,dword ptr [ESP + 0x10] (three register saves already pushed, so +0x10 resolves to entry_ESP+0x4)\",\n        \"size\": 4,\n        \"written\": false\n      }\n    ],\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 8,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 8,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 8,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 8,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 8,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0067e715\",\n        \"direction\": \"out\",\n        \"other\": \"0x00921580\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0189\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"App::cCheatManager::func40h\",\n  \"normalized_symbol\": \"App::cCheatManager::func40h\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func40h.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func40h.c\",\n      \"reconstruction/staging/pkg-cheat-dispatch-0067e6f0/cheat_dispatch_0067e6f0.cpp\",\n      \"reconstruction/staging/pkg-cheat-dispatch-0067e6f0/cheat_dispatch_0067e6f0.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-cheat-dispatch-0067e6f0/0067e6f0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"queued\",\n  \"subsystem\": \"App\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"app-lifecycle\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func40h.c\",\n    \"dependencies\": [\n      \"resource-io\"\n    ],\n    \"evidence\": \"CONFIRMED\",\n    \"kg_node_id\": \"fun:0067e6f0\",\n    \"name\": \"App::cCheatManager::func40h\",\n    \"priority\": \"P0\",\n    \"provenance\": {\n      \"classifier\": \"triage-v4\",\n      \"generated_at\": \"2026-09-23T10:12:09Z\",\n      \"gener
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
  "body_end": "0067e728",
  "body_span_bytes": 57,
  "body_start": "0067e6f0",
  "callees": [
    "FUN_00921580"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0067e6f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::cCheatManager::func40h",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCheatManager *"
    },
    {
      "name": "param_2",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x27e6f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::cCheatManager::func40h(cCheatManager * this, int param_2)",
  "size_bytes": 57,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0067e6f0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01401b74"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01401bb4"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func40h.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCheatManager__func40h.c",
    "reconstruction/staging/pkg-cheat-dispatch-0067e6f0/cheat_dispatch_0067e6f0.cpp",
    "reconstruction/staging/pkg-cheat-dispatch-0067e6f0/cheat_dispatch_0067e6f0.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-cheat-dispatch-0067e6f0/0067e6f0.json"
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01401b74"
]
```

## Conflicts

```json
[]
```
