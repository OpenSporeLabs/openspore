# Evidence 0x0067dc80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a012288f944a5e8a70fc87652bd088b6fda6709246cd863988fc9ea2a801216b`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall, callee stack cleanup",
  "hidden_receiver": "ECX, dword pointer, callee object",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    {
      "evidence": "RET 0x4 pops exactly one dword; the same slot is the one tested at 0x0067dc88.",
      "index": 0,
      "role": "deleting-destructor flag",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x4",
  "return_note": "MOV EAX,ESI at 0x0067dc98 materialises the receiver into the return register",
  "return_register": "EAX",
  "return_type": "void*",
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    "{'evidence': 'RET 0x4 at 0x0067dc9b pops exactly one dword, and the same slot is the one tested at 0x0067dc88. The test is a BYTE test (encoding f6 44 24 08 01 = TEST r/m8, imm8), so only the low byte of the slot is read and only bit 0 of that byte is examined.', 'index': 0, 'role': 'deleting-destructor flag', 'width_bytes': 4}"
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
  "content_sha256": "60b14790cdbea0eacbd0e12c3da9427e63933625b6a0796b1e2b19b9b10534b0",
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
    "persisted_calling_convention": "__thiscall, callee stack cleanup"
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
      "claim": "ECX carries the receiver: 0x0067dc80 is slot 0 of the vptr-backed vftable at 0x01401798, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 0,
        "table": "0x01401798"
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
      "at": "0x0067dc80",
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
      "at": "0x0067dc81",
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
      "at": "0x0067dc81",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x0067dc83",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0067db10",
      "target": "0x0067db10"
    },
    {
      "at": "0x0067dc88",
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
      "at": "0x0067dc88",
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
      "at": "0x0067dc90",
      "id": "obs-0007",
      "index": 6,
      "kind": "CALL_DI
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
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70"
    ],
    "conflict_id": "Q-DISPATCH-ORDER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70"
    ],
    "conflict_id": "Q-QUEUE-LAYOUT",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The 0x14-byte registration Entry and 0x18-byte ProcessQueue record are distinct observed sizes. Their pointer/reference relation and traversal order are not recovered.",
    "resolution_status": "The 0x14-byte registration Entry and 0x18-byte ProcessQueue record are distinct observed sizes. Their pointer/reference relation and traversal order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70",
      "0x00883970",
      "0x00883970",
      "0x00883a00",
      "0x00883a00",
      "0x00883a90",
      "0x00883a90",
      "0x00883ad0",
      "0x00883ad0",
      "0x00883b20",
      "0x00883b20"
    ],
    "conflict_id": "Q-RTTI-VTABLE-IDENTITY",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70",
      "0x00883970",
      "0x00883970",
      "0x00883a00",
      "0x00883a00",
      "0x00883a90",
      "0x00883a90",
      "0x00883ad0",
      "0x00883ad0",
      "0x00883b20",
      "0x00883b20"
    ],
    "conflict_id": "Q-RUNTIME-COVERAGE",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed corpus contains startup/main-menu observations but no positive original Cell or cross-subsystem event trace. Runtime order remains blocked.",
    "resolution_status": "The committed corpus contains startup/main-menu observations but no positive original Cell or cross-subsystem event trace. Runtime order remains blocked.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  },
  {
    "anchors": [
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70"
    ],
    "conflict_id": "Q-SEND-POST-OWNERSHIP",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "MessageSend, MessagePost, and MessagePostFunction have distinct declared ownership surfaces. Queue insertion, release, lock, and immediate/deferred timing are unresolved.",
    "resolution_status": "MessageSend, MessagePost, and MessagePostFunction have distinct declared ownership surfaces. Queue insertion, release, lock, and immediate/deferred timing are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70",
      "0x00883970",
      "0x00883970",
      "0x00883a00",
      "0x00883a00",
      "0x00883a90",
      "0x00883a90",
      "0x00883ad0",
      "0x00883ad0"
    ],
    "conflict_id": "Q-UTFWIN-UNION",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-
[TRUNCATED]
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
  "count": 11,
  "instructions": [
    {
      "address": "0067dc80",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0067dc81",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0067dc83",
      "instruction": "CALL 0x0067db10"
    },
    {
      "address": "0067dc88",
      "instruction": "TEST byte ptr [ESP + 0x8],0x1"
    },
    {
      "address": "0067dc8d",
      "instruction": "JZ 0x0067dc98"
    },
    {
      "address": "0067dc8f",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0067dc90",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "0067dc95",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0067dc98",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "0067dc9a",
      "instruction": "POP ESI"
    },
    {
      "address": "0067dc9b",
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
  "original_bytes": 8617,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall, callee stack cleanup\",\n    \"hidden_receiver\": \"ECX, dword pointer, callee object\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"ordinary_stack_arguments\": [\n      {\n        \"evidence\": \"RET 0x4 pops exactly one dword; the same slot is the one tested at 0x0067dc88.\",\n        \"index\": 0,\n        \"role\": \"deleting-destructor flag\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 0x4\",\n    \"return_note\": \"MOV EAX,ESI at 0x0067dc98 materialises the receiver into the return register\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void*\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      \"{'evidence': 'RET 0x4 at 0x0067dc9b pops exactly one dword, and the same slot is the one tested at 0x0067dc88. The test is a BYTE test (encoding f6 44 24 08 01 = TEST r/m8, imm8), so only the low byte of the slot is read and only bit 0 of that byte is examined.', 'index': 0, 'role': 'deleting-destructor flag', 'width_bytes': 4}\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-cheat-dispatch-0067e6f0\",\n      \"score\": 6,\n      \"symbol\": \"cCheatManager_func40h_0067e6f0\",\n      \"va\": \"0x0067e6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"cheat-func44h-0067e730\",\n      \"score\": 6,\n      \"symbol\": \"func44h_0067e730\",\n      \"va\": \"0x0067e730\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 6,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-proplist-dispatch-wave14\",\n      \"score\": 6,\n      \"symbol\": \"app_property_list_add_all_properties_from_006a1510\",\n      \"va\": \"0x006a1510\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 6,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 6,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-direct-property-copyfrom-wave14\",\n      \"score\": 6,\n      \"symbol\": \"App_DirectPropertyList_CopyFrom_006a2ad0\",\n      \"va\": \"0x006a2ad0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 6,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0067dc83\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067db10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0067dc90\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f47380\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0180\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"App::IMessageManager::Get\",\n  \"normalized_symbol\": \"App::IMessageManager::Get\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/App__IMessageManager__Get.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/App__IMessageManager__Get.c\",\n      \"reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80.cpp\",\n      \"reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80.hpp\",\n      \"reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-app-imessage-manager-dtor/0067dc80.json\",\n      \"reconstruction/metadata/pkg-dfw-0067dc80/0067dc80.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"queued\",\n  \"subsystem\": \"App\",\n  \"triage\":
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
  "body_end": "0067dc9d",
  "body_span_bytes": 30,
  "body_start": "0067dc80",
  "callees": [
    "FUN_0067db10",
    "FUN_00f47380"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0067dc80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::IMessageManager::Get",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "IMessageManager *",
  "return_type_resolved": true,
  "rva": "0x27dc80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "IMessageManager * App::IMessageManager::Get(void)",
  "size_bytes": 30,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0067dc80",
  "vtables": {
    "referenced_by_vtables": [
      "0x01401798"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "01401798"
    },
    {
      "from": "0067db03"
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
  "global:PASS"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__IMessageManager__Get.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__IMessageManager__Get.c",
    "reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80.cpp",
    "reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80.hpp",
    "reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-imessage-manager-dtor/0067dc80.json",
    "reconstruction/metadata/pkg-dfw-0067dc80/0067dc80.json"
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
  "DATA",
  "void*",
  "void* (dword receiver value) in EAX",
  "void* -- MOV EAX,ESI at 0x0067dc98 materialises the receiver into the return register"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f3a68",
  "vtable:0x01401798"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70"
    ],
    "conflict_id": "Q-DISPATCH-ORDER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70"
    ],
    "conflict_id": "Q-QUEUE-LAYOUT",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The 0x14-byte registration Entry and 0x18-byte ProcessQueue record are distinct observed sizes. Their pointer/reference relation and traversal order are not recovered.",
    "resolution_status": "The 0x14-byte registration Entry and 0x18-byte ProcessQueue record are distinct observed sizes. Their pointer/reference relation and traversal order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70",
      "0x00883970",
      "0x00883970",
      "0x00883a00",
      "0x00883a00",
      "0x00883a90",
      "0x00883a90",
      "0x00883ad0",
      "0x00883ad0",
      "0x00883b20",
      "0x00883b20"
    ],
    "conflict_id": "Q-RTTI-VTABLE-IDENTITY",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70",
      "0x00883970",
      "0x00883970",
      "0x00883a00",
      "0x00883a00",
      "0x00883a90",
      "0x00883a90",
      "0x00883ad0",
      "0x00883ad0",
      "0x00883b20",
      "0x00883b20"
    ],
    "conflict_id": "Q-RUNTIME-COVERAGE",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed corpus contains startup/main-menu observations but no positive original Cell or cross-subsystem event trace. Runtime order remains blocked.",
    "resolution_status": "The committed corpus contains startup/main-menu observations but no positive original Cell or cross-subsystem event trace. Runtime order remains blocked.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  },
  {
    "anchors": [
      "0x000847f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883b20",
      "0x008841f0",
      "0x000847f0",
      "0x0067dc80",
      "0x0067dc80",
      "0x000847f0",
      "0x000847f0",
      "0x0084bd70",
      "0x0084bd70"
    ],
    "conflict_id": "Q-SEND-POST-OWNERSHIP",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "MessageSend, MessagePost, and MessagePostFunction have distinct declared ownership surfaces. Queue insertion, release, lock, and immediate/deferred timing are unresolved.",
    "resolution_status": "MessageSend, MessagePost, and MessagePostFunction have distinct declared ownership surfaces. Queue insertion, release, lock, and immediate/deferred timing are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json
[TRUNCATED]
```
