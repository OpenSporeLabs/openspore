# Evidence 0x0059d8b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1957ce3b697821b6ed2b4b9505cf281a31450b9566b1f16df7a8aabd2a940a01`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86:LE:32",
  "calling_convention": "thiscall",
  "hidden_receiver": "ECX = OpaqueEditorAnimEvent*",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "event_id",
      "position": 1,
      "type": "TargetWord"
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "secondary_id",
      "position": 2,
      "type": "TargetWord"
    },
    {
      "entry_offset": "ESP+0x0c",
      "name": "editor_model",
      "position": 3,
      "type": "OpaqueEditorModel*"
    },
    {
      "entry_offset": "ESP+0x10",
      "name": "argument_5",
      "position": 4,
      "type": "TargetWord"
    },
    {
      "entry_offset": "ESP+0x14",
      "name": "flag_6",
      "position": 5,
      "type": "bool"
    },
    {
      "entry_offset": "ESP+0x18",
      "name": "value_7",
      "position": 6,
      "type": "float"
    },
    {
      "entry_offset": "ESP+0x1c",
      "name": "flag_8",
      "position": 7,
      "type": "bool"
    },
    {
      "entry_offset": "ESP+0x20",
      "name": "argument_9",
      "position": 8,
      "type": "TargetWord"
    },
    {
      "entry_offset": "ESP+0x24",
      "name": "value_10",
      "position": 9,
      "type": "float"
    }
  ],
  "return_register": null,
  "return_type": "void",
  "return_width_bytes": 0,
  "stack_cleanup_bytes": 36,
  "termination": "RET 0x24"
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
      "entry_ESP+0xc",
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c",
      "entry_ESP+0x20",
      "entry_ESP+0x24"
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
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
    "ret_form": "RET 0x24",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x24",
        "observed": true,
        "ordinal": 9,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 36,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x24"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 36,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x24",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "7e3380d45520240046a08967f813338bc178d1954d8dc20db77ae62187156d8d",
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
    "ghidra_parameter_count": 10,
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
        "obs-0024"
      ],
      "claim": "the callee pops 36 byte(s) of stack arguments",
      "c
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00587270"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00591690"
  },
  {
    "name": "Editors::cEditor::HandleMessage",
    "reconstructed": false,
    "va": "0x00591fa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005b1e30"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00587270",
      "0x0059d840",
      "0x0059d8b0",
      "0x00587270",
      "0x0059d8b0",
      "0x0059d840",
      "0x00573970",
      "0x00573970",
      "0x00586410",
      "0x00586410",
      "0x00587270",
      "0x00587270",
      "0x0059d840",
      "0x0059d840",
      "0x0059d8b0",
      "0x0059d8b0"
    ],
    "conflict_id": "Q-ANIMATION-DISPATCH",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Editor animation Send/Post surfaces and the editor mode producer are concrete. The final AnimatedCreature/IAnimWorld consumer and pose ordering are unresolved.",
    "resolution_status": "Editor animation Send/Post surfaces and the editor mode producer are concrete. The final AnimatedCreature/IAnimWorld consumer and pose ordering are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00591fa0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883ad0",
      "0x00883a90",
      "0x00591fa0",
      "0x00573970",
      "0x00573970",
      "0x00586410",
      "0x00586410",
      "0x00587270",
      "0x00587270",
      "0x0059d840",
      "0x0059d840",
      "0x0059d8b0",
      "0x0059d8b0"
    ],
    "conflict_id": "Q-EDITOR-MESSAGE-CATALOG",
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
      "0x00587270",
      "0x0059d8b0",
      "0x0062a820",
      "0x0062c550",
      "0x0062c550",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00586b00"
    ],
    "conflict_id": "editor_to_gameplay_boundary",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00587270",
      "0x0059d840",
      "0x0059d8b0",
      "0x00628d50",
      "0x0062a820",
      "0x0062c550",
      "0x00587270",
      "0x0059d8b0",
      "0x0059d840",
      "0x0057f3e0",
      "0x00628d50",
      "0x0062a820",
      "0x0062c550",
      "0x0062a820",
      "0x00628d50",
      "0x0062c550"
    ],
    "conflict_id": "play_mode_module_types",
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
      "0x004c5200",
      "0x00587270",
      "0x0059d840",
      "0x0059d8b0",
      "0x00587270",
      "0x0059d8b0",
      "0x0059d840",
      "0x00591690",
      "0x004c5200",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300"
    ],
    "conflict_id": "skin_paint_lifecycle",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00587270",
      "0x0059d840",
      "0x0059d8b0",
      "0x00587270",
      "0x0059d8b0",
      "0x0059d840",
      "0x0067cae0",
      "0x00b31da0",
      "0x0059ca70",
      "0x0059cac0",
      "0x00b321e0",
      "0x00b32330",
      "0x00b32560",
      "0x0059cea0",
      "0x0059cf00",
      "0x00b63980"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:3",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachabil
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
  "count": 32,
  "instructions": [
    {
      "address": "0059d8b0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0059d8b1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0059d8b3",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "0059d8b8",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0059d8ba",
      "instruction": "JZ 0x0059d914"
    },
    {
      "address": "0059d8bc",
      "instruction": "MOV ECX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "0059d8c0",
      "instruction": "MOV EDX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0059d8c4",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "0059d8ca",
      "instruction": "MOV dword ptr [ESI + 0xc],ECX"
    },
    {
      "address": "0059d8cd",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "0059d8d1",
      "instruction": "MOV dword ptr [ESI + 0x10],ECX"
    },
    {
      "address": "0059d8d4",
      "instruction": "MOV CL,byte ptr [ESP + 0x18]"
    },
    {
      "address": "0059d8d8",
      "instruction": "MOV dword ptr [ESI + 0x18],EDX"
    },
    {
      "address": "0059d8db",
      "instruction": "MOV EDX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "0059d8df",
      "instruction": "MOV byte ptr [ESI + 0x1c],CL"
    },
    {
      "address": "0059d8e2",
      "instruction": "MOV ECX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "0059d8e6",
      "instruction": "MOV dword ptr [ESI + 0x14],EDX"
    },
    {
      "address": "0059d8e9",
      "instruction": "MOV DL,byte ptr [ESP + 0x20]"
    },
    {
      "address": "0059d8ed",
      "instruction": "MOVSS dword ptr [ESI + 0x20],XMM0"
    },
    {
      "address": "0059d8f2",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x28]"
    },
    {
      "address": "0059d8f8",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0059d8fa",
      "instruction": "MOV dword ptr [ESI + 0x28],ECX"
    },
    {
      "address": "0059d8fd",
      "instruction": "MOV byte ptr [ESI + 0x24],DL"
    },
    {
      "address": "0059d900",
      "instruction": "MOVSS dword ptr [ESI + 0x2c],XMM0"
    },
    {
      "address": "0059d905",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "0059d907",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0059d908",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0059d90a",
      "instruction": "MOV EAX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "0059d90d",
      "instruction": "PUSH 0xd1511790"
    },
    {
      "address": "0059d912",
      "instruction": "CALL EAX"
    },
    {
      "address": "0059d914",
      "instruction": "POP ESI"
    },
    {
      "address": "0059d915",
      "instruction": "RET 0x24"
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
  "original_bytes": 9305,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86:LE:32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_receiver\": \"ECX = OpaqueEditorAnimEvent*\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"event_id\",\n        \"position\": 1,\n        \"type\": \"TargetWord\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"secondary_id\",\n        \"position\": 2,\n        \"type\": \"TargetWord\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x0c\",\n        \"name\": \"editor_model\",\n        \"position\": 3,\n        \"type\": \"OpaqueEditorModel*\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x10\",\n        \"name\": \"argument_5\",\n        \"position\": 4,\n        \"type\": \"TargetWord\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x14\",\n        \"name\": \"flag_6\",\n        \"position\": 5,\n        \"type\": \"bool\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x18\",\n        \"name\": \"value_7\",\n        \"position\": 6,\n        \"type\": \"float\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x1c\",\n        \"name\": \"flag_8\",\n        \"position\": 7,\n        \"type\": \"bool\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x20\",\n        \"name\": \"argument_9\",\n        \"position\": 8,\n        \"type\": \"TargetWord\"\n      },\n      {\n        \"entry_offset\": \"ESP+0x24\",\n        \"name\": \"value_10\",\n        \"position\": 9,\n        \"type\": \"float\"\n      }\n    ],\n    \"return_register\": null,\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"stack_cleanup_bytes\": 36,\n    \"termination\": \"RET 0x24\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorModel*,OpaqueRuntimeService,TargetWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 30,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService,TargetWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 27,\n      \"symbol\": \"app_prop_manager_get_global_property_list_006a3310\",\n      \"va\": \"0x006a3310\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"app_prop_manager_get_supported_types_006a3400\",\n      \"va\": \"0x006a3400\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"app_canvas_get_message_server_00c871d0\",\n      \"va\": \"0x00c871d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"app_cheat_manager_get_0067dde0\",\n      \"va\": \"0x0067dde0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"app_id_generator_get_007c79e0\",\n      \"va\": \"0x007c79e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE8\",\n      \"score\": 14,\n      \"symbol\": \"ui_layer_manager_get_0067ca90\",\n      \"va\": \"0x0067ca90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueRuntimeService\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE8\",\n      \"score\": 14,\n      \"symbol\": \"anim_manager_get_0067cae0\",\n      \"va\": \"0x0067cae0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueRuntimeService\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00591690\"\n      },\n      {\n        \"name\": \"Editors::cEditor::HandleMessage\",\n        \"reconstructed\": false,\n        \"va\": \"0x00591fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005b1e30\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00587930\",\n        \"direction\": \"in\",\n        \"other\": \
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
  "body_end": "0059d917",
  "body_span_bytes": 104,
  "body_start": "0059d8b0",
  "callees": [
    "App::IAppSystem::Get"
  ],
  "callers": [
    "Editors::cEditor::SetActiveMode",
    "FUN_005b1e30",
    "FUN_00591690",
    "Editors::cEditor::HandleMessage"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0059d8b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Editors::cEditorAnimEvent::MessageSend",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 10,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cEditorAnimEvent *"
    },
    {
      "name": "eventID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t"
    },
    {
      "name": "param_3",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "int"
    },
    {
      "name": "editorModel",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "EditorModel *"
    },
    {
      "name": "param_5",
      "ordinal": 4,
      "storage": "Stack[0x14]:4",
      "type": "int"
    },
    {
      "name": "param_6",
      "ordinal": 5,
      "storage": "Stack[0x18]:1",
      "type": "bool"
    },
    {
      "name": "param_7",
      "ordinal": 6,
      "storage": "Stack[0x1c]:4",
      "type": "float"
    },
    {
      "name": "param_8",
      "ordinal": 7,
      "storage": "Stack[0x20]:1",
      "type": "bool"
    },
    {
      "name": "param_9",
      "ordinal": 8,
      "storage": "Stack[0x24]:4",
      "type": "int"
    },
    {
      "name": "param_10",
      "ordinal": 9,
      "storage": "Stack[0x28]:4",
      "type": "float"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x19d8b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Editors::cEditorAnimEvent::MessageSend(cEditorAnimEvent * this, uint32_t eventID, int param_3, EditorModel * editorModel, int param_5, bool param_6, float param_7, bool param_8, int param_9, float param_10)",
  "size_bytes": 104,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0059d8b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "00587930"
    },
    {
      "from": "005879cc"
    },
    {
      "from": "005b2111"
    },
    {
      "from": "00592a73"
    },
    {
      "from": "00591cce"
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
  "file": "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp",
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.hpp",
    "src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-runtime-services-wave7/0059d8b0.json"
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
    "required"
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
  "OpaqueEditorModel*",
  "OpaqueRuntimeService",
  "TargetWord",
  "bool",
  "float",
  "void"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x00587270",
      "0x0059d840",
      "0x0059d8b0",
      "0x00587270",
      "0x0059d8b0",
      "0x0059d840",
      "0x00573970",
      "0x00573970",
      "0x00586410",
      "0x00586410",
      "0x00587270",
      "0x00587270",
      "0x0059d840",
      "0x0059d840",
      "0x0059d8b0",
      "0x0059d8b0"
    ],
    "conflict_id": "Q-ANIMATION-DISPATCH",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Editor animation Send/Post surfaces and the editor mode producer are concrete. The final AnimatedCreature/IAnimWorld consumer and pose ordering are unresolved.",
    "resolution_status": "Editor animation Send/Post surfaces and the editor mode producer are concrete. The final AnimatedCreature/IAnimWorld consumer and pose ordering are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00591fa0",
      "0x00883a90",
      "0x00883ad0",
      "0x00883ad0",
      "0x00883a90",
      "0x00591fa0",
      "0x00573970",
      "0x00573970",
      "0x00586410",
      "0x00586410",
      "0x00587270",
      "0x00587270",
      "0x0059d840",
      "0x0059d840",
      "0x0059d8b0",
      "0x0059d8b0"
    ],
    "conflict_id": "Q-EDITOR-MESSAGE-CATALOG",
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
      "0x00587270",
      "0x0059d8b0",
      "0x0062a820",
      "0x0062c550",
      "0x0062c550",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00586b00"
    ],
    "conflict_id": "editor_to_gameplay_boundary",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00587270",
      "0x0059d840",
      "0x0059d8b0",
      "0x00628d50",
      "0x0062a820",
      "0x0062c550",
      "0x00587270",
      "0x0059d8b0",
      "0x0059d840",
      "0x0057f3e0",
      "0x00628d50",
      "0x0062a820",
      "0x0062c550",
      "0x0062a820",
      "0x00628d50",
      "0x0062c550"
    ],
    "conflict_id": "play_mode_module_types",
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
      "0x004c5200",
      "0x00587270",
      "0x0059d840",
      "0x0059d8b0",
      "0x00587270",
      "0x0059d8b0",
      "0x0059d840",
      "0x00591690",
      "0x004c5200",
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300"
    ],
    "conflict_id": "skin_paint_lifecycle",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call p
[TRUNCATED]
```
