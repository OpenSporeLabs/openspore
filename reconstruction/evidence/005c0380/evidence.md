# Evidence 0x005c0380

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `644c287f20043bea5e333d9d1587d429941953b921029786297fb1b7aad77c74`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "receiver": {
    "register": "ECX",
    "type": "opaque UI shell",
    "width_bytes": 4
  },
  "return_observation": "void; unchanged state returns through the normal epilogue.",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "enabled",
      "position": 1,
      "type": "uint8",
      "width_bytes": 1
    }
  ],
  "stack_cleanup_bytes": 4,
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
      "EBP",
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
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +292, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "12d571d58c74f7604dc473df4778a061f634d4ac45c37f15504174b3a9f8fc23",
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
    "indirect_calls": 34,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0048",
        "obs-0091"
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
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0058",
        "obs-0063",
        "obs-0065",
        "obs-0073"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          16,
          17,
          24,
          28,
          32
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0048",
        "obs-0058",
        "obs-0063",
        "obs-0065",
        "obs-0073",
        "obs-0091"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0048",
        "obs-0091"
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
        "obs-0048",
        "obs-0091"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0048",
        "obs-0091"
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
      "at": "0x005c0380",
      "count": 9,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "reg": "ESP"
    },
    {
      "at": "0x005c0380",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "resolved": true,
      "size": 1,
      "trust": "untrusted_frame"
    },
    {
      "at": "0x005c0380",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "and_esp": null,
      "at": "0x005c0384",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0004",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 55,
      "sub": 16
    },
    {
      "at": "0x005c0384",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x005c0387",
      "count": 29,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "reg": "ESI"
    },
    {
      "at": "0x005c0388",
      "count": 7,
      "first_use": 3,
      "first_w
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
      "0x00960250",
      "0x00960250",
      "0x005bf9d0",
      "0x005bf9d0",
      "0x005bfd40",
      "0x005bfd40",
      "0x005c0100",
      "0x005c0100",
      "0x005c0380",
      "0x005c0380",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360",
      "0x007d8360"
    ],
    "conflict_id": "U-DIALOG-BEHAVIOR",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x005bf9d0",
      "0x005bf9d0",
      "0x005bfd40",
      "0x005bfd40",
      "0x005c0100",
      "0x005c0100",
      "0x005c0380",
      "0x005c0380",
      "0x0095fcc0",
      "0x0095fcc0",
      "0x00960050",
      "0x00960050",
      "0x00960250",
      "0x00960250"
    ],
    "conflict_id": "U-SCREEN-STATE-BITS",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [],
    "kind": "semantic_decomp_contradiction",
    "path": "vtable_and_structs.vtable_candidate.projection_conflict",
    "source": "knowledgegraph/research/semantic-decomp/worker-05-ui-shell.json",
    "statement": "The live table extends beyond the imported 0x20-byte EditorNamePanel vtable projection.",
    "va": "0x005c0380"
  },
  {
    "anchors": [
      "0x01073a2e",
      "0xffffffff",
      "0x01070ba0",
      "0xffffffff",
      "0x01073700",
      "0x013f7b54",
      "0x005bf9d0",
      "0x005c0380",
      "0x013f7b54",
      "0x005c0380",
      "0x0716d445",
      "0x0716d446",
      "0x00835080",
      "0x00834fa0"
    ],
    "kind": "semantic_decomp_contradiction",
    "path": "evidence_conflicts",
    "source": "knowledgegraph/research/semantic-decomp/worker-05-ui-shell.json",
    "statement": [
      {
        "id": "space_palette_field_offset_conflict",
        "observation": "Live disassembly at 0x01073a2e writes [ESI+0x2f8] = 0xffffffff. The SpaceGameUI structure labels +0x2f8 as field_2F8, not mActivePaletteID. Live constructor 0x01070ba0 writes param_1[0x8f] = 0, which is +0x23c, and param_1[0xbe] = 0xffffffff, which is +0x2f8.",
        "resolution": "Use field_2F8=-1 for the assigned setup body and mActivePaletteID=0 for the constructor-observed state. Do not propagate the historical mActivePaletteID=-1 claim.",
        "scope": "0x01073700 versus historical setup/state-machine claim",
        "sources": [
          "G02",
          "G04",
          "G05",
          "C03",
          "C04"
        ]
      },
      {
        "id": "editor_vtable_projection_mismatch",
        "observation": "The imported EditorNamePanel__vftable projection is 0x20 bytes, but the live table at 0x013f7b54 contains 0x005bf9d0 at +0x30 and 0x005c0380 at +0x58. The live table is therefore longer or begins at a different interface boundary than the imported projection.",
        "resolution": "Use 0x013f7b54 as a live candidate and record exact observed offsets; do not claim exact inherited slot ownership beyond those offsets.",
        "scope": "EditorNamePanel vtable",
        "sources": [
          "G01",
          "G02",
          "G04",
          "C01"
        ]
      },
      {
        "id": "iappsystem_init_event_label_conflict",
        "observation": "The target calls App::IAppSystem::Get()->vtable+0x14 with the literal and a null second argument. The imported IAppSystem layout names +0x14 Init, while committed state-machine prose calls the literals application messages. The target does not call IMessageManager::MessageSend or ProcessQueue.",
        "resolution": "Describe these as IAppSystem +0x14 Init-family dispatch literals with an internal state-change label; queueing, synchronicity, and exact event ABI remain unresolved.",
        "scope": "0x005c0380 literals 0x0716d445/0x0716d446",
        "sources": [
          "G01",
          "G02",
          "G04",
          "C01",
          "C04"
        ]
      },
      {
        "id": "cspuitextzoom_abi_conflict",
        "observation": "The target uses seven stack arguments and RET 0x1c, while the contained SDK Initialize alias at 0x00835080 has six total parameters. The imported cSPUITextZoom structure exposes only 0x78 bytes and no named fields after the early padding region.",
        "resolution": "Keep the mechanics and field offsets, but do not claim the exact SDK ABI or field ownership beyond directly observed offsets.",
        "scope": "0x00834fa0",
        "sources": [
          "G01",
          "G02",
          "G04",
          "C01",
          "C03"
        ]
      }
    ],
    "va": null
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
  "count": 348,
  "instructions": [
    {
      "address": "005c0380",
      "instruction": "MOV AL,byte ptr [ESP + 0x4]"
    },
    {
      "address": "005c0384",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "005c0387",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005c0388",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005c038a",
      "instruction": "CMP byte ptr [ESI + 0x10],AL"
    },
    {
      "address": "005c038d",
      "instruction": "JZ 0x005c0732"
    },
    {
      "address": "005c0393",
      "instruction": "MOV ECX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "005c0396",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005c0397",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005c0399",
      "instruction": "MOV byte ptr [ESI + 0x10],AL"
    },
    {
      "address": "005c039c",
      "instruction": "PUSH 0x272eb68e"
    },
    {
      "address": "005c03a1",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "005c03a3",
      "instruction": "JZ 0x005c0548"
    },
    {
      "address": "005c03a9",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005c03ae",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005c03b0",
      "instruction": "JZ 0x005c03cd"
    },
    {
      "address": "005c03b2",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005c03b4",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005c03b6",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "005c03b9",
      "instruction": "PUSH 0x8ed27e7a"
    },
    {
      "address": "005c03be",
      "instruction": "CALL EAX"
    },
    {
      "address": "005c03c0",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005c03c2",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005c03c4",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005c03c6",
      "instruction": "MOV EAX,dword ptr [EDX + 0x28]"
    },
    {
      "address": "005c03c9",
      "instruction": "PUSH 0x4"
    },
    {
      "address": "005c03cb",
      "instruction": "CALL EAX"
    },
    {
      "address": "005c03cd",
      "instruction": "MOV ECX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "005c03d0",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005c03d2",
      "instruction": "PUSH 0x453ef531"
    },
    {
      "address": "005c03d7",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005c03dc",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005c03de",
      "instruction": "JZ 0x005c03fb"
    },
    {
      "address": "005c03e0",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005c03e2",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005c03e4",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "005c03e7",
      "instruction": "PUSH 0x8ed27e7a"
    },
    {
      "address": "005c03ec",
      "instruction": "CALL EAX"
    },
    {
      "address": "005c03ee",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005c03f0",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005c03f2",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005c03f4",
      "instruction": "MOV EAX,dword ptr [EDX + 0x28]"
    },
    {
      "address": "005c03f7",
      "instruction": "PUSH 0x4"
    },
    {
      "address": "005c03f9",
      "instruction": "CALL EAX"
    },
    {
      "address": "005c03fb",
      "instruction": "CMP byte ptr [ESI + 0x11],0x0"
    },
    {
      "address": "005c03ff",
      "instruction": "JZ 0x005c04a2"
    },
    {
      "address": "005c0405",
      "instruction": "MOV ECX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "005c0408",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005c040a",
      "instruction": "PUSH 0xc7ceb1bd"
    },
    {
      "address": "005c040f",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005c0414",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "005c0416",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "005c0418",
      "instruction": "JZ 0x005c0482"
    },
    {
      "address": "005c041a",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "005c041c",
      "instruction": "MOV EAX,dword ptr [EDX + 0x7c]"
    },
    {
      "address": "005c041f",
      "instruction": "PUSH EBP"
    },
    {
      "address": "005c0420",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005c0422",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005c0424",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "005c0426",
      "instruction": "CALL EAX"
    },
    {
      "address": "005c0428",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "005c042a",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "005c042d",
      "instruction": "PUSH 0xcf428691"
    },
    {
      "address": "005c0432",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "005c0434",
      "instruction": "CALL EAX"
    },
    {
      "address": "005c0436",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "005c0438",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "005c043a",
      "instruction": "MOV EAX,dword ptr [EDX + 0x3c]"
    },
    {
      "address": "005c043d",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "005c043f",
      "instruction": "CALL EAX"
    },
    {
      "address": "005c0441",
      "instruction": "LEA EDX,[EAX + 0x2]"
    },
    {
      "address": "005c0444",
      "instruction": "MOV CX,word ptr [EAX]"
    },
    {
      "address": "005c0447",
      "instruction": "ADD EAX,0x
[TRUNCATED]
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
  "original_bytes": 22673,
  "preview": "{\n  \"abi\": {\n    \"receiver\": {\n      \"register\": \"ECX\",\n      \"type\": \"opaque UI shell\",\n      \"width_bytes\": 4\n    },\n    \"return_observation\": \"void; unchanged state returns through the normal epilogue.\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"enabled\",\n        \"position\": 1,\n        \"type\": \"uint8\",\n        \"width_bytes\": 1\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueUiObject,OpaqueUiShell,UNCONDITIONAL_CALL\",\n        \"shared_vtable:vtable:0x013f7b70\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 32,\n      \"symbol\": \"FUN_005bf9d0\",\n      \"va\": \"0x005bf9d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueUiObject,OpaqueUiShell,UNCONDITIONAL_CALL\",\n        \"shared_vtable:vtable:0x013f7b70\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 32,\n      \"symbol\": \"FUN_005c0100\",\n      \"va\": \"0x005c0100\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 6,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 6,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,uint8\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 6,\n      \"symbol\": \"app_capp_system_func88h_00a6c940\",\n      \"va\": \"0x00a6c940\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 3,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 3,\n      \"symbol\": \"app_system_service_gate_dispatch_007e5f30\",\n      \"va\": \"0x007e5f30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"app_capp_system_hook_windows_007e6080\",\n      \"va\": \"0x007e6080\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueUiShell\",\n  \"cluster\": null,\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005c0521\",\n        \"direction\": \"out\",\n        \"other\": \"0x00435ed0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0712\",\n        \"direction\": \"out\",\n        \"other\": \"0x00435ed0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c05ec\",\n        \"direction\": \"out\",\n        \"other\": \"0x00579a90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c05f5\",\n        \"direction\": \"out\",\n        \"other\": \"0x0057eda0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0619\",\n        \"direction\": \"out\",\n        \"other\": \"0x005bf950\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0623\",\n        \"direction\": \"out\",\n        \"other\": \"0x005bf950\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0470\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067caa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c0529\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c071a\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c03a9\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c03d7\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c040f\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c048c\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c04ac\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005c04cc\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"reference_type\": \"direct-call\"\n      },\n  
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
  "body_end": "005c0738",
  "body_span_bytes": 953,
  "body_start": "005c0380",
  "callees": [
    "FUN_00579a90",
    "FUN_00f47380",
    "FUN_00435ed0",
    "FUN_008105b0",
    "FUN_0067caa0",
    "App::IAppSystem::Get",
    "FUN_005bf950",
    "FUN_0057eda0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005c0380",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005c0380",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1c0380",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005c0380(void)",
  "size_bytes": 953,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005c0380",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f7b54"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "013f7bac"
    },
    {
      "from": "00edb9bd"
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
  "file": "src/reconstruction/pkg18_ui_scripting/ui_shell_functions.cpp",
  "files": [
    "reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.cpp",
    "reconstruction/staging/pkg18-ui-scripting/ui_shell_functions.hpp",
    "reconstruction/staging/pkg18-ui-scripting/ui_shell_functions_model_test.cpp",
    "src/reconstruction/pkg18_ui_scripting/ui_shell_functions.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg18-ui-scripting/005c0380.json"
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
    "gate-ui-scripting-registration-state"
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 12216,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"identity\": \"medium-high\",\n    \"mechanics\": \"high\",\n    \"overall\": \"medium-high\"\n  },\n  \"contradictions\": [\n    {\n      \"path\": \"vtable_and_structs.vtable_candidate.projection_conflict\",\n      \"source\": \"knowledgegraph/research/semantic-decomp/worker-05-ui-shell.json\",\n      \"value\": \"The live table extends beyond the imported 0x20-byte EditorNamePanel vtable projection.\"\n    }\n  ],\n  \"downstream_unlock_count\": 8,\n  \"evidence\": [\n    {\n      \"claim\": \"The exact equality guard, field_10 write, enable/disable branches, service-key lookups, text/child operations, and two +0x14 calls are present.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G01\"\n    },\n    {\n      \"claim\": \"0x013f7bac is the live data reference and 0x00edb9bd is the unresolved live call xref; the vtable calls are at +0x7c/+0x28/+0x4c/+0x94/+0xdc.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G02\"\n    },\n    {\n      \"claim\": \"Eight direct callees, no canonical direct callers, and 17 depth-2 call-graph edges.\",\n      \"level\": \"OBSERVED\",\n      \"limit\": 100,\n      \"source\": \"G03\"\n    },\n    {\n      \"claim\": \"EditorNamePanel is 56 bytes; live table 0x013f7b54 places this target at +0x58 and 005bf9d0 at +0x30.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G04\"\n    },\n    {\n      \"claim\": \"0x005bfd40 initializes the bool and vtable, while 0x005bf950/0x005bfcc0 establish the text/entity path used by the transition.\",\n      \"level\": \"SUPPORTED\",\n      \"source\": \"G05\"\n    },\n    {\n      \"claim\": \"The SDK exports EditorNamePanel::SetExtended, IAppSystem, IWinProc, and the panel field layout; the SDK vtable projection is shorter than the live table.\",\n      \"level\": \"SUPPORTED\",\n      \"source\": \"C01\"\n    },\n    {\n      \"claim\": \"The committed state machine independently records the basic/extended state, guards, and the two state-specific literals; queue semantics remain unverified.\",\n      \"level\": \"SUPPORTED\",\n      \"source\": \"C04\"\n    }\n  ],\n  \"family\": null,\n  \"interfaces\": {\n    \"boundaries\": {\n      \"boundary_judgment\": \"This state machine must not be collapsed into App or gameplay mode state despite sharing an IAppSystem transport surface.\",\n      \"gameplay_authority\": \"No direct write to App game mode, Simulator strategy, SpaceContext, health, progression, or save state observed.\",\n      \"gameplay_read_or_bridge\": \"The panel may be associated with an INameableEntity and random-name type; service callbacks are editor presentation services.\",\n      \"ui_owned_state\": \"EditorNamePanel+0x10, validation/layout/window visibility, text/name presentation, child/editor presentation\"\n    },\n    \"direct_callees\": {\n      \"count\": 8,\n      \"direct_reference_edges_canonical\": 24,\n      \"endpoints\": [\n        \"0x00435ed0\",\n        \"0x00579a90\",\n        \"0x0057eda0\",\n        \"0x005bf950\",\n        \"0x0067caa0\",\n        \"0x008105b0\",\n        \"0x00f47380\",\n        \"0x0067dcc0\"\n      ],\n      \"service_key_fanout\": [\n        \"0x272eb68e\",\n        \"0x453ef531\",\n        \"0xc7ceb1bd\",\n        \"0xd0e6d04b\",\n        \"0xaddc11ef\",\n        \"0x5415e48\",\n        \"0x552c901\"\n      ]\n    },\n    \"direct_callers\": {\n      \"canonical_rule\": \"No direct caller is promoted; the function is vtable-dispatched and the canonical direct-call xref set is empty.\",\n      \"count\": 0,\n      \"named_endpoints\": [],\n      \"xrefs\": [\n        {\n          \"keys\": [\n            \"address\",\n            \"meaning\",\n            \"type\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"address\",\n            \"meaning\",\n            \"type\"\n          ]\n        }\n      ]\n    },\n    \"globals\": [],\n    \"structures\": {\n      \"fields\": [\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        }\n      ],\n      \"interface_context\": \"IWinProc vtable projection places GetPriority at +0x10, GetEventFlags at +0x14, and HandleUIMessage at +0x18; the exact live table boundary for this larger EditorNamePanel table is not proven.\",\n      \"primary_type\": \"EditorNamePanel\",\n      \"type_size_bytes\": 56,\n      \"vtable_candidate\": {\n        \"address\": \"0x013f7b54\",\n        \"data_reference\": \"0x013f7bac\",\n        \"family_relation\": \"0x005bf9d0 is also present in the same live table at +0x30.\",\n        \"projection_conflict\": \"The live table extends beyond the imported 0x20-byte EditorNamePanel vtable projection.\",\n        \"target_slot_offset\": \"+0x58\"\n      }\n    },\n    \"vtables\": {\n      \"fields\": [\n   
[TRUNCATED]
```

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
  "DATA",
  "OpaqueUiObject",
  "OpaqueUiShell",
  "UNCONDITIONAL_CALL",
  "opaque UI shell",
  "uint8"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f7b70"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x005bf9d0",
      "0x005bf9d0",
      "0x005bfd40",
      "0x005bfd40",
      "0x005c0100",
      "0x005c0100",
      "0x005c0380",
      "0x005c0380",
      "0x007d8060",
      "0x007d8060",
      "0x007d8230",
      "0x007d8230",
      "0x007d8360",
      "0x007d8360"
    ],
    "conflict_id": "U-DIALOG-BEHAVIOR",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x005bf9d0",
      "0x005bf9d0",
      "0x005bfd40",
      "0x005bfd40",
      "0x005c0100",
      "0x005c0100",
      "0x005c0380",
      "0x005c0380",
      "0x0095fcc0",
      "0x0095fcc0",
      "0x00960050",
      "0x00960050",
      "0x00960250",
      "0x00960250"
    ],
    "conflict_id": "U-SCREEN-STATE-BITS",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [],
    "kind": "semantic_decomp_contradiction",
    "path": "vtable_and_structs.vtable_candidate.projection_conflict",
    "source": "knowledgegraph/research/semantic-decomp/worker-05-ui-shell.json",
    "statement": "The live table extends beyond the imported 0x20-byte EditorNamePanel vtable projection.",
    "va": "0x005c0380"
  },
  {
    "anchors": [
      "0x01073a2e",
      "0xffffffff",
      "0x01070ba0",
      "0xffffffff",
      "0x01073700",
      "0x013f7b54",
      "0x005bf9d0",
      "0x005c0380",
      "0x013f7b54",
      "0x005c0380",
      "0x0716d445",
      "0x0716d446",
      "0x00835080",
      "0x00834fa0"
    ],
    "kind": "semantic_decomp_contradiction",
    "path": "evidence_conflicts",
    "source": "knowledgegraph/research/semantic-decomp/worker-05-ui-shell.json",
    "statement": [
      {
        "id": "space_palette_field_offset_conflict",
        "observation": "Live disassembly at 0x01073a2e writes [ESI+0x2f8] = 0xffffffff. The SpaceGameUI structure labels +0x2f8 as field_2F8, not mActivePaletteID. Live constructor 0x01070ba0 writes param_1[0x8f] = 0, which is +0x23c, and param_1[0xbe] = 0xffffffff, which is +0x2f8.",
        "resolution": "Use field_2F8=-1 for the assigned setup body and mActivePaletteID=0 for the constructor-observed state. Do not propagate the historical mActivePaletteID=-1 claim.",
        "scope": "0x01073700 versus historical setup/state-machine claim",
        "sources": [
          "G02",
          "G04",
          "G05",
          "C03",
          "C04"
        ]
      },
      {
        "id": "editor_vtable_projection_mismatch",
        "observation": "The imported EditorNamePanel__vftable projection is 0x20 bytes, but the live table at 0x013f7b54 contains 0x005bf9d0 at +0x30 and 0x005c0380 at +0x58. The live table is therefore longer or begins at a different interface boundary than the imported projection.",
        "resolution": "Use 0x013f7b54 as a live candidate and record exact observed offsets; do not claim exact inherited slot ownership beyond those offsets.",
        "scope": "EditorNamePanel vtable",
        "sources": [
          "G01",
          "G02",
          "G04",
          "C01"
        ]
      },
      {
        "id": "iappsystem_init_event_label_conflict",
        "observation": "The target calls App::IAppSystem::Get()->vtable+0x14 with the literal and a null second argument. The imported IAppSystem layout names +0x14 Init, while committed state-machine prose calls the literals application messages. The target does not call IMessageManager::MessageSend or ProcessQueue.",
        "resolution": "Describe these as IAppSystem +0x14 Init-family dispatch literals with an internal state-change label; queueing, synchronicity, and exact event ABI remain unresolved.",
        "scope": "0x005c0380 literals 0x0716d445/0x0716d446",
        "sources": [
          "G01",
          "G02",
          "G04",
          "C01",
          "C04"
        ]
      },
      {
        "id": "cspuitextzoom_abi_conflict",
        "observation": "The target uses seven stack arguments and RET 0x1c, while th
[TRUNCATED]
```
