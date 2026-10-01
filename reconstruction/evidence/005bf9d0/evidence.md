# Evidence 0x005bf9d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5ffdf54b8584dffb1dc15d24d7ab138cb831ae97eab6abb7594ab9fa6cd7ddc9`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "receiver": {
    "register": "ECX",
    "type": [
      "opaque UI shell/input state",
      "opaque editor/input state"
    ],
    "width_bytes": 4
  },
  "return_observation": [
    "AL is one for handled ids and zero for unmatched ids or failed shape checks.",
    "AL is one for handled branches and zero for unmatched ids or failed shape checks."
  ],
  "stack_arguments": [
    "{'entry_offset': 'ESP+0x04', 'name': 'message_id', 'position': 1, 'type': 'uint32', 'width_bytes': 4}",
    "{'entry_offset': 'ESP+0x08', 'name': 'message', 'position': 2, 'type': 'opaque UI message pointer', 'width_bytes': 4}",
    "{'entry_offset': 'ESP+0x08', 'name': 'message_payload', 'position': 2, 'type': 'opaque pointer', 'width_bytes': 4}"
  ],
  "stack_cleanup_bytes": 8,
  "termination": "RET 0x8"
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0x14",
      "entry_ESP+0x18"
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
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
      }
    ],
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -28, so the listing is not one path",
    "ret_imm_below_highest_slot: ret 0x8 pops less than the highest read slot 0x18; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x8 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x8 but entry slot 0x18 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "7f4037f0d2bb5320c5787d3b8eee64ff26e412c2ba98cf0cbc651919831987ed",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "UNKNOWN",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0039",
        "obs-0044",
        "obs-0050",
        "obs-0055",
        "obs-0058"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0039",
        "obs-0044",
        "obs-0050",
        "obs-0055",
        "obs-0058"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 8,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0010",
        "obs-0045",
        "obs-0051"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 2,
        "observed_slots": 4,
        "total_bytes": 24
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0014",
        "obs-0031"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          -4,
          12,
          20,
          24
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0058"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0039",
        "obs-0044",
        "obs-0050",
        "obs-0055",
        "obs-0058"
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
        "obs-0004"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION"
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
    "statement": "The imported EditorNamePanel__vftable is 0x20 bytes, so the live table is longer or starts at another interface boundary.",
    "va": "0x005bf9d0"
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
  "count": 130,
  "instructions": [
    {
      "address": "005bf9d0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "005bf9d4",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "005bf9d7",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005bf9d8",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005bf9d9",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005bf9db",
      "instruction": "CMP EAX,0x14418c3f"
    },
    {
      "address": "005bf9e0",
      "instruction": "JA 0x005bfb33"
    },
    {
      "address": "005bf9e6",
      "instruction": "JZ 0x005bfafb"
    },
    {
      "address": "005bf9ec",
      "instruction": "CMP EAX,0x1ee1001"
    },
    {
      "address": "005bf9f1",
      "instruction": "JZ 0x005bfa19"
    },
    {
      "address": "005bf9f3",
      "instruction": "CMP EAX,0x73127e6"
    },
    {
      "address": "005bf9f8",
      "instruction": "JNZ 0x005bfb5b"
    },
    {
      "address": "005bf9fe",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "005bfa02",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "005bfa04",
      "instruction": "CMP ECX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "005bfa07",
      "instruction": "JNZ 0x005bfb5b"
    },
    {
      "address": "005bfa0d",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005bfa0f",
      "instruction": "PUSH 0x5415e48"
    },
    {
      "address": "005bfa14",
      "instruction": "JMP 0x005bfb0d"
    },
    {
      "address": "005bfa19",
      "instruction": "CMP byte ptr [ESI + 0xc],0x0"
    },
    {
      "address": "005bfa1d",
      "instruction": "JZ 0x005bfb5b"
    },
    {
      "address": "005bfa23",
      "instruction": "MOV ECX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "005bfa27",
      "instruction": "MOV EDI,dword ptr [ECX + 0x8]"
    },
    {
      "address": "005bfa2a",
      "instruction": "CMP dword ptr [EDI + 0x8],0x5"
    },
    {
      "address": "005bfa2e",
      "instruction": "JNZ 0x005bfb5b"
    },
    {
      "address": "005bfa34",
      "instruction": "CMP dword ptr [EDI + 0xc],0x3e8"
    },
    {
      "address": "005bfa3b",
      "instruction": "JNZ 0x005bfb5b"
    },
    {
      "address": "005bfa41",
      "instruction": "CMP byte ptr [EDI + 0x10],0x1"
    },
    {
      "address": "005bfa45",
      "instruction": "JNZ 0x005bfb5b"
    },
    {
      "address": "005bfa4b",
      "instruction": "CALL 0x008053b0"
    },
    {
      "address": "005bfa50",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "005bfa52",
      "instruction": "JNZ 0x005bfb5b"
    },
    {
      "address": "005bfa58",
      "instruction": "CVTSI2SS XMM0,dword ptr [EDI + 0x18]"
    },
    {
      "address": "005bfa5d",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005bfa5e",
      "instruction": "LEA EDX,[ESP + 0x18]"
    },
    {
      "address": "005bfa62",
      "instruction": "PUSH EDX"
    },
    {
      "address": "005bfa63",
      "instruction": "LEA EAX,[ESP + 0x20]"
    },
    {
      "address": "005bfa67",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005bfa68",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "005bfa6b",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "005bfa71",
      "instruction": "CVTSI2SS XMM0,dword ptr [EDI + 0x14]"
    },
    {
      "address": "005bfa76",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "005bfa7b",
      "instruction": "CALL 0x00804f80"
    },
    {
      "address": "005bfa80",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "005bfa86",
      "instruction": "MOVSS dword ptr [ESP + 0x1c],XMM0"
    },
    {
      "address": "005bfa8c",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x28]"
    },
    {
      "address": "005bfa92",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "005bfa95",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM0"
    },
    {
      "address": "005bfa9b",
      "instruction": "CALL 0x0067caa0"
    },
    {
      "address": "005bfaa0",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005bfaa2",
      "instruction": "MOV EDX,dword ptr [EDX + 0x44]"
    },
    {
      "address": "005bfaa5",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "005bfaa9",
      "instruction": "PUSH ECX"
    },
    {
      "address": "005bfaaa",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005bfaac",
      "instruction": "CALL EDX"
    },
    {
      "address": "005bfaae",
      "instruction": "MOV ECX,dword ptr [ESI + 0x14]"
    },
    {
      "address": "005bfab1",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005bfab3",
      "instruction": "PUSH 0x272eb68e"
    },
    {
      "address": "005bfab8",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "005bfaba",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005bfabf",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "005bfac1",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "005bfac3",
      "instruction": "CMP EDI,EBX"
    },
    {
      "address": "005bfac5",
      "instruction": "JZ 0x005bfaf0"
    },
    {
      "address": "005bfac7",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005bfac9",
      "instruction": "JZ 0x005bfae3"
    },
    {
      "address": "005bfacb",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005bfacd",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005bfacf",
      "instruction": "MOV EAX,dword ptr [EDX + 0x10]"
    },
    {
      "address": "005bfad2",
      "instruction": "CALL EAX"
    },
    {
      "address": "005bfad4",
      "instruction": "CMP EAX,EB
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
  "original_bytes": 21317,
  "preview": "{\n  \"abi\": {\n    \"receiver\": {\n      \"register\": \"ECX\",\n      \"type\": [\n        \"opaque UI shell/input state\",\n        \"opaque editor/input state\"\n      ],\n      \"width_bytes\": 4\n    },\n    \"return_observation\": [\n      \"AL is one for handled ids and zero for unmatched ids or failed shape checks.\",\n      \"AL is one for handled branches and zero for unmatched ids or failed shape checks.\"\n    ],\n    \"stack_arguments\": [\n      \"{'entry_offset': 'ESP+0x04', 'name': 'message_id', 'position': 1, 'type': 'uint32', 'width_bytes': 4}\",\n      \"{'entry_offset': 'ESP+0x08', 'name': 'message', 'position': 2, 'type': 'opaque UI message pointer', 'width_bytes': 4}\",\n      \"{'entry_offset': 'ESP+0x08', 'name': 'message_payload', 'position': 2, 'type': 'opaque pointer', 'width_bytes': 4}\"\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueUiMessage,OpaqueUiObject,OpaqueUiShell\",\n        \"shared_vtable:vtable:0x013f7b70\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 32,\n      \"symbol\": \"FUN_005c0100\",\n      \"va\": \"0x005c0100\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueUiObject,OpaqueUiShell,UNCONDITIONAL_CALL\",\n        \"shared_vtable:vtable:0x013f7b70\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 32,\n      \"symbol\": \"FUN_005c0380\",\n      \"va\": \"0x005c0380\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueUiMessage,opaque pointer\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 6,\n      \"symbol\": \"Editors_EditorUI_HandleMessage_005e0000\",\n      \"va\": \"0x005e0000\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 6,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 6,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,uint32\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n      \"va\": \"0x00e5c0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,uint32\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_down_00e6c860\",\n      \"va\": \"0x00e6c860\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA,uint32\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n      \"va\": \"0x00e7d660\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueUiShell\",\n  \"cluster\": null,\n  \"confidence\": 0.91,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005bfb4c\",\n        \"direction\": \"out\",\n        \"other\": \"0x005bf950\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005bfa9b\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067caa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005bfa7b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00804f80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005bfa4b\",\n        \"direction\": \"out\",\n        \"other\": \"0x008053b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005bfaba\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005bfb13\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x005bf950\",\n      \"0x0067caa0\",\n      \"0x00804f80\",\n      \"0x008053b0\",\n      \"0x008105b0\"\n    ],\n    \"manifest_callers\": [\n      \"unmodeled_call_0x00edae70\"\n    ],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0108\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"FUN_005bf9d0\",\n  \"normalized_symbol\": \"FUN_005bf9d0\",\n  \"observed_mechanics\": [\n    \"four message ids\",\n    \"payload coordinate conversion\",\n    \"vtable+0x10 linked traversal\",\n    \"parent+0x1c fallback\",\n    \"RET 8\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-18-UI-SCRIPTING\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": \"source-wave3/PKG-18-UI-SCRIPTING\"\n    },\n    \"package\": \"PKG-18-UI-SCRIPTING\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-18-UI-SCRIPTING\",\n  \"reconst
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
  "body_end": "005bfb64",
  "body_span_bytes": 405,
  "body_start": "005bf9d0",
  "callees": [
    "FUN_00804f80",
    "FUN_0067caa0",
    "FUN_008105b0",
    "FUN_008053b0",
    "FUN_005bf950"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005bf9d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_005bf9d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1bf9d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005bf9d0(void)",
  "size_bytes": 405,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005bf9d0",
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
      "from": "013f7b84"
    },
    {
      "from": "00edae70"
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
    "reconstruction/metadata/pkg18-ui-scripting/005bf9d0.json",
    "reconstruction/metadata/pkg18-ui-space/005bf9d0.json"
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
    "gate-ui-scripting-message-routes"
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
  "original_bytes": 12842,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"STRUCTURAL_ONLY\",\n  \"confidence\": {\n    \"identity\": \"medium-high\",\n    \"mechanics\": \"high\",\n    \"overall\": \"medium-high\"\n  },\n  \"contradictions\": [\n    {\n      \"path\": \"vtable_and_structs.vtable_candidate.projection_conflict\",\n      \"source\": \"knowledgegraph/research/semantic-decomp/worker-05-ui-shell.json\",\n      \"value\": \"The imported EditorNamePanel__vftable is 0x20 bytes, so the live table is longer or starts at another interface boundary.\"\n    }\n  ],\n  \"downstream_unlock_count\": 5,\n  \"evidence\": [\n    {\n      \"claim\": \"The body has four message-ID branches, exact payload guards, service +0x80 forwarding, manager +0x44 lookup, list traversal, and 0/1 return behavior.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G01\"\n    },\n    {\n      \"claim\": \"The 0x013f7b84 data xref and 0x00edae70 call xref coexist with no resolved direct caller; the adjusted this-4 vtable +0x1c path is visible in the disassembly.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G02\"\n    },\n    {\n      \"claim\": \"Five direct callees, zero canonical direct callers, and two observed xrefs.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G03\"\n    },\n    {\n      \"claim\": \"EditorNamePanel is 56 bytes with the observed fields; live table 0x013f7b54 places this target at +0x30 and 0x005c0380 at +0x58.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G04\"\n    },\n    {\n      \"claim\": \"0x005bfd40 installs the table and registers IDs; sibling 0x005c0100 handles the adjacent UTFWin message family.\",\n      \"level\": \"SUPPORTED\",\n      \"source\": \"G05\"\n    },\n    {\n      \"claim\": \"SDK exports the EditorNamePanel methods, fields, and IMessageListener/IWinProc interfaces.\",\n      \"level\": \"SUPPORTED\",\n      \"source\": \"C01\"\n    },\n    {\n      \"claim\": \"Canonical xref topology records no inbound direct caller and five direct callees.\",\n      \"level\": \"SUPPORTED\",\n      \"source\": \"C02\"\n    }\n  ],\n  \"family\": null,\n  \"interfaces\": {\n    \"boundaries\": {\n      \"boundary_judgment\": \"This is an editor UI message adapter. It is not a gameplay event consumer merely because it receives a message-shaped record.\",\n      \"gameplay_authority\": \"None observed.\",\n      \"gameplay_read_or_bridge\": \"Service and manager callbacks may reach editor/content services, but no cell state or progression write is present.\",\n      \"ui_owned_state\": \"message dispatch, editor name/display service calls, validation/layout adaptation\"\n    },\n    \"direct_callees\": {\n      \"count\": 5,\n      \"direct_reference_edges_canonical\": 6,\n      \"endpoints\": [\n        \"0x005bf950\",\n        \"0x0067caa0\",\n        \"0x00804f80\",\n        \"0x008053b0\",\n        \"0x008105b0\"\n      ],\n      \"service_and_manager_surface\": [\n        \"0x008105b0\",\n        \"0x0067caa0\",\n        \"0x00804f80\",\n        \"0x008053b0\",\n        \"0x005bf950\"\n      ]\n    },\n    \"direct_callers\": {\n      \"canonical_rule\": \"No direct caller is promoted because the canonical xref snapshot has zero inbound direct callers and the live call xref has no function owner.\",\n      \"count\": 0,\n      \"named_endpoints\": [],\n      \"xrefs\": [\n        {\n          \"keys\": [\n            \"address\",\n            \"meaning\",\n            \"type\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"address\",\n            \"meaning\",\n            \"type\"\n          ]\n        }\n      ]\n    },\n    \"globals\": [],\n    \"structures\": {\n      \"family_construction\": \"0x005bfd40 installs 0x013f7b54 as the primary vptr candidate and registers the listener/service objects.\",\n      \"fields\": [\n        {\n          \"keys\": [\n            \"evidence\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"evidence\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"evidence\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        }\n      ],\n      \"primary_type\": \"EditorNamePanel\",\n      \"type_size_bytes\": 56,\n      \"vtable_candidate\": {\n        \"address\": \"0x013f7b54\",\n        \"projection_conflict\": \"The imported EditorNamePanel__vftable is 0x20 bytes, so the live table is longer or starts at another interface boundary.\",\n        \"sibling_setextended_reference\": \"0x013f7bac\",\n        \"sibling_setextended_slot_offset\": \"+0x58\",\n        \"target_data_reference\": \"0x013f7b84\",\n        \"target_slot_offset\": \"+0x30\"\n 
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
  "OpaqueUiMessage",
  "OpaqueUiObject",
  "OpaqueUiShell",
  "UNCONDITIONAL_CALL",
  "opaque UI message pointer",
  "opaque UI shell/input state",
  "opaque editor/input state",
  "opaque pointer",
  "uint32"
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
    "statement": "The imported EditorNamePanel__vftable is 0x20 bytes, so the live table is longer or starts at another interface boundary.",
    "va": "0x005bf9d0"
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
        "observation": "The target uses seven stac
[TRUNCATED]
```
