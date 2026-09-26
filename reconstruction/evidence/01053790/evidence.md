# Evidence 0x01053790

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2bb73b4d98cceb145fcd98b04e84741be546d9e8ac115a4d2509f230e1e25cda`

## abi

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
  "content_sha256": "c7e5f571354c43e8df9428425f2c879aeadf76b94f939613c8b9e8446db72826",
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
          0
        ],
        "register": "ECX",
        "written_through": 1
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
      "at": "0x01053790",
      "count": 1,
      "first_use": 0,
      "first_write_index": 7,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "TEST byte ptr [ESP + 0x4],0x1",
      "reg": "ESP"
    },
    {
      "at": "0x01053790",
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
      "at": "0x01053795",
      "count": 4,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x01053796",
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
      "at": "0x01053796",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x010537a1",
      "id": "obs-0006",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00f47380",
      "target": "0x00f47380"
    },
    {
      "at": "0x010537a6",
      "definite": true,
      "id": "obs-0007",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x4",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x010537a9",
      "definite": true,
      "id": "obs-0008",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ESI",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x010537ab",
      "id": "obs-0009",
      "index": 9,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x010537ac",
      "form": "RET 0x4",
      "id": "obs-0010",
      "imm": 4,
      "index": 10,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 11,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame
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
      "0x01053790",
      "0x01059010",
      "0x01053790",
      "0x01053790",
      "0x01053790",
      "0x01053790",
      "0x01059010",
      "0x01059010",
      "0x01059010",
      "0x00bfc3d0",
      "0x00bfc3d0",
      "0x00bfc7a0",
      "0x00bfc7a0",
      "0x01053790",
      "0x01059010",
      "0x01053790"
    ],
    "conflict_id": "tool_callback_body_mapping",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bfc3d0",
      "0x00bfc7a0",
      "0x01053790",
      "0x01059010",
      "0x01053790",
      "0x00e7a7c0",
      "0x01053790",
      "0x01053790",
      "0x01053790",
      "0x01059010",
      "0x01059010",
      "0x01059010",
      "0x00bfc3d0",
      "0x00bfc3d0",
      "0x00bfc3d0",
      "0x00bfc460"
    ],
    "conflict_id": "tool_projectile_event_path",
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

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\n/* WARNING: Unknown calling convention */\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n\nbool Simulator__cToolStrategy__OnSelect(cToolStrategy *this,cSpaceToolData *pTool)\n\n{\n  undefined4 *in_ECX;\n  \n  *in_ECX = &PTR_Simulator__cToolStrategy__OnSelect_01403934;\n  if (((uint)this & 1) != 0) {\n    FUN_00f47380();\n  }\n  return SUB41(in_ECX,0);\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 11,
  "instructions": [
    {
      "address": "01053790",
      "instruction": "TEST byte ptr [ESP + 0x4],0x1"
    },
    {
      "address": "01053795",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01053796",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "01053798",
      "instruction": "MOV dword ptr [ESI],0x1403934"
    },
    {
      "address": "0105379e",
      "instruction": "JZ 0x010537a9"
    },
    {
      "address": "010537a0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "010537a1",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "010537a6",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "010537a9",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "010537ab",
      "instruction": "POP ESI"
    },
    {
      "address": "010537ac",
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
  "original_bytes": 6300,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-core-systems\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x010537a1\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0530\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"Simulator::cToolStrategy::OnSelect\",\n  \"normalized_symbol\": \"Simulator::cToolStrategy::OnSelect\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cToolStrategy__OnSelect.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cToolStrategy__OnSelect.c\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [],\n    \"provenance\": []\n  },\n  \"status\": \"queued\",\n  \"subsystem\": \"Simulator\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sim-core-systems\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cToolStrategy__OnSelect.c\",\n    \"dependencies\": [\n      \"resource-io\",\n      \"app-lifecycle\",\n      \"utfwin-framework\"\n    ],\n    \"evidence\": \"CONFIRMED\",\n    \"kg_node_id\": \"fun:01053790\",\n    \"name\": \"Simulator::cToolStrategy::OnSelect\",\n    \"priority\": \"P0\",\n    \"provenance\": {\n      \"classifier\": \"triage-v4\",\n      \"generated_at\": \"2026-09-23T10:12:09Z\",\n      \"generator\": \"subagent-7-sequential-triage\",\n      \"sdk_name\": \"Simulator::cToolStrategy::OnSelect\",\n      \"snapshot\": \"2540f2ca\",\n      \"snapshot_sha256\": \"2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8\",\n      \"vtable_addrs\": [\n        \"01416698\",\n        \"014166c4\",\n        \"0141677c\",\n        \"014167a0\",\n        \"014167ec\",\n        \"014168a8\",\n        \"014169bc\",\n        \"014169f0\",\n        \"0141a504\",\n        \"014402c4\",\n        \"01440fbc\",\n        \"0144144c\"\n      ]\n    },\n    \"queue_state\": \"queued\",\n    \"rank\": 20\n  },\n  \"types\": [],\n  \"unresolved_questions\": [],\n  \"va\": \"0x01053790\",\n  \"vtables\": [\n    \"vtable:0x01416698\",\n    \"vtable:0x014166c4\",\n    \"vtable:0x0141677c\",\n    \"vtable:0x014167a0\",\n    \"vtable:0x014167ec\",\n    \"vtable:0x014168a8\",\n    \"vtable:0x014169bc\",\n    \"vtable:0x014169f0\",\n    \"vtable:0x0141a504\",\n    \"vtable:0x014402c4\",\n    \"vtable:0x01440fbc\",\n    \"vtable:0x0144144c\",\n    \"vtable:0x01441a2c\",\n    \"vtable:0x01442324\",\n    \"vtable:0x01442368\",\n    \"vtable:0x01442490\",\n    \"vtable:0x01442678\",\n    \"vtable:0x01442984\",\n    \"vtable:0x01443020\",\n    \"vtable:0x014431c4\",\n    \"vtable:0x01443570\",\n    \"vtable:0x01443694\",\n    \"
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
  "body_end": "010537ae",
  "body_span_bytes": 31,
  "body_start": "01053790",
  "callees": [
    "FUN_00f47380"
  ],
  "callers": [],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "01053790",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "in_ECX",
      "storage": "register:00000004:4",
      "type": "undefined4 *"
    },
    {
      "name": "this",
      "storage": "Stack[0x4]:4",
      "type": "cToolStrategy *"
    },
    {
      "name": "pTool",
      "storage": "Stack[0x8]:4",
      "type": "cSpaceToolData *"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "Simulator::cToolStrategy::OnSelect",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cToolStrategy *"
    },
    {
      "name": "pTool",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "cSpaceToolData *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0xc53790",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool Simulator::cToolStrategy::OnSelect(cToolStrategy * this, cSpaceToolData * pTool)",
  "size_bytes": 31,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01053790",
  "vtables": {
    "referenced_by_vtables": [
      "0x0149b4d8",
      "0x014624d0",
      "0x01462510",
      "0x01462550",
      "0x01462590",
      "0x014625d0",
      "0x0148aba8",
      "0x01495584",
      "0x0149b358",
      "0x0149b398",
      "0x0149b3d8",
      "0x0149b418",
      "0x0149b458",
      "0x0149b498",
      "0x01442324",
      "0x01462610",
      "0x01495654",
      "0x014529fc",
      "0x01442368",
      "0x01441a2c"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "01403934"
    },
    {
      "from": "01452a18"
    },
    {
      "from": "01454fac"
    },
    {
      "from": "0145ea00"
    },
    {
      "from": "0145ea48"
    },
    {
      "from": "0145ea80"
    },
    {
      "from": "0145eac8"
    },
    {
      "from": "0145f948"
    },
    {
      "from": "0145f958"
    },
    {
      "from": "014624d0"
    },
    {
      "from": "014624e0"
    },
    {
      "from": "014624f0"
    },
    {
      "from": "01462500"
    },
    {
      "from": "01462510"
    },
    {
      "from": "01462520"
    },
    {
      "from": "01462530"
    },
    {
      "from": "01462540"
    },
    {
      "from": "01462550"
    },
    {
      "from": "01462560"
    },
    {
      "from": "01462570"
    },
    {
      "from": "01462580"
    },
    {
      "from": "01462590"
    },
    {
      "from": "014625a0"
    },
    {
      "from": "014625b0"
    },
    {
      "from": "014625c0"
    },
    {
      "from": "014625d0"
    },
    {
      "from": "014625e0"
    },
    {
      "from": "014625f0"
    },
    {
      "from": "01462600"
    },
    {
      "from": "01462610"
    },
    {
      "from": "01462620"
    },
    {
      "from": "01465fd0"
    },
    {
      "from": "01465fe0"
    },
    {
      "from": "0147affc"
    },
    {
      "from": "0147b00c"
    },
    {
      "from": "0147b01c"
    },
    {
      "from": "0147b02c"
    },
    {
      "from": "0147b03c"
    },
    {
      "from": "0147b04c"
    },
    {
      "from": "0147b05c"
    },
    {
      "from": "0147b06c"
    },
    {
      "from": "0147b07c"
    },
    {
      "from": "0148aba8"
    },
    {
      "from": "0148abb8"
    },
    {
      "from": "0148c064"
    },
    {
      "from": "01495654"
    },
    {
      "from": "014955b0"
    },
    {
      "from": "014955c0"
    },
    {
      "from": "014955d0"
    },
    {
      "from": "01495590"
    },
    {
      "from": "014955a0"
    },
    {
      "from": "014956dc"
    },
    {
      "from": "014955e0"
    },
    {
      "from": "014955f0"
    },
    {
      "from": "01495600"
    },
    {
      "from": "0149b328"
    },
    {
      "from": "0149b358"
    },
    {
      "from": "0149b368"
    },
    {
      "from": "0149b378"
    },
    {
      "from": "0149b388"
    },
    {
      "from": "0149b398"
    },
    {
      "from": "0149b3a8"
    },
    {
      "from": "0149b3b8"
    },
    {
      "from": "0149b3c8"
    },
    {
      "from": "0149b3d8"
    },
    {
      "from": "0149b3e8"
    },
    {
      "from": "0149b3f8"
    },
    {
      "from": "0149b408"
    },
    {
      "from": "0149b418"
    },
    {
      "from": "0149b428"
    },
    {
      "from": "0149b438"
    },
    {
      "from": "0149b448"
    },
    {
      "from": "0149b458"
    },
    {
      "from": "0149b468"
    },
    {
      "from": "0149b478"
    },
    {
      "from": "0149b488"
    },
    {
      "from": "0149b498"
    },
    {
      "from": "0149b4a8"
    },
    {
      "from": "0149b4b8"
    },
    {
      "from": "0149b4c8"
    },
    {
      "from": "0149b4d8"
    },
    {
      "from": "0149b4e8"
    },
    {
      "from": "0149b4f8"
    },
    {
      "from": "01416a7c"
    },
    {
      "from": "01416624"
    },
    {
      "from": "01416650"
    },
    {
      "from": "01416678"
    },
    {
      "from": "0141669c"
    },
    {
      "from": "014166c8"
    },
    {
      "from": "014166f0"
    },
    {
      "from": "01416714"
    },
    {
      "from": "01416738"
    },
    {
      "from": "0141675c"
    },
    {
      "from": "0141678
[TRUNCATED]
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cToolStrategy__OnSelect.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cToolStrategy__OnSelect.c"
  ],
  "handoffs": [],
  "metadata": []
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01416698",
  "vtable:0x014166c4",
  "vtable:0x0141677c",
  "vtable:0x014167a0",
  "vtable:0x014167ec",
  "vtable:0x014168a8",
  "vtable:0x014169bc",
  "vtable:0x014169f0",
  "vtable:0x0141a504",
  "vtable:0x014402c4",
  "vtable:0x01440fbc",
  "vtable:0x0144144c",
  "vtable:0x01441a2c",
  "vtable:0x01442324",
  "vtable:0x01442368",
  "vtable:0x01442490"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x01053790",
      "0x01059010",
      "0x01053790",
      "0x01053790",
      "0x01053790",
      "0x01053790",
      "0x01059010",
      "0x01059010",
      "0x01059010",
      "0x00bfc3d0",
      "0x00bfc3d0",
      "0x00bfc7a0",
      "0x00bfc7a0",
      "0x01053790",
      "0x01059010",
      "0x01053790"
    ],
    "conflict_id": "tool_callback_body_mapping",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bfc3d0",
      "0x00bfc7a0",
      "0x01053790",
      "0x01059010",
      "0x01053790",
      "0x00e7a7c0",
      "0x01053790",
      "0x01053790",
      "0x01053790",
      "0x01059010",
      "0x01059010",
      "0x01059010",
      "0x00bfc3d0",
      "0x00bfc3d0",
      "0x00bfc3d0",
      "0x00bfc460"
    ],
    "conflict_id": "tool_projectile_event_path",
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
