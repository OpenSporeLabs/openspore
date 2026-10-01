# Evidence 0x00834fa0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `922c00fd037b45f64f30465a70c546ac2bed84e26cc7757ad6aa673c3b1438a1`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "receiver": {
    "register": "ECX",
    "type": "ZoomOwner *",
    "width_bytes": 4
  },
  "return_observation": "AL is zero on the null-source and zero-selected-value paths and one on the normal completion path.",
  "return_register": "EAX",
  "return_type": "bool",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "source",
      "position": 1,
      "type": "Opaque",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "target",
      "position": 2,
      "type": "Opaque",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0c",
      "name": "mode",
      "position": 3,
      "type": "Opaque",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x10",
      "name": "state",
      "position": 4,
      "type": "Opaque",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x14",
      "name": "resource_key_0",
      "position": 5,
      "type": "Opaque",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x18",
      "name": "resource_key_1",
      "position": 6,
      "type": "Opaque",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x1c",
      "name": "resource_key_2",
      "position": 7,
      "type": "Opaque",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 28,
  "termination": "RET 0x1c"
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
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c"
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
        "size_inferred": true,
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
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
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
    "ret_form": "RET 0x1c",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBP",
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
        "size_inferred": true,
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
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 28,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x1c"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +56, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched"
  ],
  "cleanup": {
    "bytes": 28,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x1c",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "f711cad84466d425cfa687a9f91be3669e4dee9207ee6670e5856443a7a51344",
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
    "indirect_calls": 19,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0078",
        "obs-0081"
      ],
      "claim": "the callee pops 28 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 28,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0017",
        "obs-0018",
        "obs-0019",
        "obs-0020",
        "obs-0022",
        "obs-0037",
        "obs-0039"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 2,
        "observed_slots": 5,
        "total_bytes": 28
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0013",
        "obs-0017",
        "obs-0037",
        "obs-0039",
        "obs-0040",
        "obs-0046",
        "obs-0054",
        "obs-0057",
        "obs-0060",
        "obs-0062",
        "obs-0065",
        "obs-0069"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          72,
          76,
          80,
          84,
          100,
          104,
          108,
          112,
          116
        ],
        "register": "ECX",
        "written_through": 10
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0013",
        "obs-0017",
        "obs-0037",
        "obs-0039",
        "obs-0040",
        "obs-0046",
        "obs-0054",
        "obs-0057",
        "obs-0060",
        "obs-
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
    "va": "0x00658440"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0066daf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e15780"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ecf320"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ef50a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f149d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0106f3d0"
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
  "count": 259,
  "instructions": [
    {
      "address": "00834fa0",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "00834fa3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00834fa4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00834fa5",
      "instruction": "MOV EDI,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00834fa9",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00834fab",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00834fad",
      "instruction": "JZ 0x00835273"
    },
    {
      "address": "00834fb3",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00834fb5",
      "instruction": "MOV EDX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "00834fb8",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00834fba",
      "instruction": "CALL EDX"
    },
    {
      "address": "00834fbc",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00834fbe",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00834fc0",
      "instruction": "MOV EAX,dword ptr [EDX + 0x10]"
    },
    {
      "address": "00834fc3",
      "instruction": "CALL EAX"
    },
    {
      "address": "00834fc5",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00834fc7",
      "instruction": "JZ 0x00835273"
    },
    {
      "address": "00834fcd",
      "instruction": "CMP dword ptr [ESI + 0x68],EDI"
    },
    {
      "address": "00834fd0",
      "instruction": "JNZ 0x00835018"
    },
    {
      "address": "00834fd2",
      "instruction": "MOV ECX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00834fd6",
      "instruction": "CMP ECX,dword ptr [0x0164f240]"
    },
    {
      "address": "00834fdc",
      "instruction": "JNZ 0x00834ff6"
    },
    {
      "address": "00834fde",
      "instruction": "MOV EDX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00834fe2",
      "instruction": "CMP EDX,dword ptr [0x0164f244]"
    },
    {
      "address": "00834fe8",
      "instruction": "JNZ 0x00834ff6"
    },
    {
      "address": "00834fea",
      "instruction": "MOV EAX,dword ptr [ESP + 0x30]"
    },
    {
      "address": "00834fee",
      "instruction": "CMP EAX,dword ptr [0x0164f248]"
    },
    {
      "address": "00834ff4",
      "instruction": "JZ 0x00835018"
    },
    {
      "address": "00834ff6",
      "instruction": "LEA ECX,[ESI + 0x48]"
    },
    {
      "address": "00834ff9",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00834ffa",
      "instruction": "LEA EDX,[ESP + 0x2c]"
    },
    {
      "address": "00834ffe",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00834fff",
      "instruction": "CALL 0x004eb930"
    },
    {
      "address": "00835004",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00835007",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00835009",
      "instruction": "JZ 0x00835018"
    },
    {
      "address": "0083500b",
      "instruction": "MOV EAX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "0083500f",
      "instruction": "CMP dword ptr [ESI + 0x6c],EAX"
    },
    {
      "address": "00835012",
      "instruction": "JZ 0x00835269"
    },
    {
      "address": "00835018",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00835019",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0083501a",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0083501c",
      "instruction": "CALL 0x00834e30"
    },
    {
      "address": "00835021",
      "instruction": "MOV EBX,dword ptr [ESI + 0x68]"
    },
    {
      "address": "00835024",
      "instruction": "CMP EDI,EBX"
    },
    {
      "address": "00835026",
      "instruction": "JZ 0x00835040"
    },
    {
      "address": "00835028",
      "instruction": "MOV EDX,dword ptr [EDI]"
    },
    {
      "address": "0083502a",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "0083502c",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0083502e",
      "instruction": "CALL EAX"
    },
    {
      "address": "00835030",
      "instruction": "MOV dword ptr [ESI + 0x68],EDI"
    },
    {
      "address": "00835033",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00835035",
      "instruction": "JZ 0x00835040"
    },
    {
      "address": "00835037",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "00835039",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "0083503c",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "0083503e",
      "instruction": "CALL EAX"
    },
    {
      "address": "00835040",
      "instruction": "MOV ECX,dword ptr [ESI + 0x68]"
    },
    {
      "address": "00835043",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00835045",
      "instruction": "MOV EAX,dword ptr [EDX + 0x10]"
    },
    {
      "address": "00835048",
      "instruction": "CALL EAX"
    },
    {
      "address": "0083504a",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "0083504c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0083504e",
      "instruction": "MOV EAX,dword ptr [EDX + 0x30]"
    },
    {
      "address": "00835051",
      "instruction": "CALL EAX"
    },
    {
      "address": "00835053",
      "instruction": "MOV dword ptr [ESI + 0x74],EAX"
    },
    {
      "address": "00835056",
      "instruction": "CALL 0x009512c0"
    },
    {
      "address": "0083505b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0083505c",
      "instruction": "PUSH 0x14007f8"
    },
    {
      "address": "00835061",
      "instruction": "PUSH 0x4"
    },
    {
      "address": "00835063",
      "instruction": "PUSH 0x834"
    },
    {
      "address": "00835068",
 
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
  "original_bytes": 24054,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"receiver\": {\n      \"register\": \"ECX\",\n      \"type\": \"ZoomOwner *\",\n      \"width_bytes\": 4\n    },\n    \"return_observation\": \"AL is zero on the null-source and zero-selected-value paths and one on the normal completion path.\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"bool\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"source\",\n        \"position\": 1,\n        \"type\": \"Opaque\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"target\",\n        \"position\": 2,\n        \"type\": \"Opaque\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x0c\",\n        \"name\": \"mode\",\n        \"position\": 3,\n        \"type\": \"Opaque\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x10\",\n        \"name\": \"state\",\n        \"position\": 4,\n        \"type\": \"Opaque\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x14\",\n        \"name\": \"resource_key_0\",\n        \"position\": 5,\n        \"type\": \"Opaque\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x18\",\n        \"name\": \"resource_key_1\",\n        \"position\": 6,\n        \"type\": \"Opaque\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x1c\",\n        \"name\": \"resource_key_2\",\n        \"position\": 7,\n        \"type\": \"Opaque\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 28,\n    \"termination\": \"RET 0x1c\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-18-UI-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"pkg18_space_ui_initialize_01073700\",\n      \"va\": \"0x01073700\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Opaque\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e80\",\n      \"va\": \"0x00967e80\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Opaque\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"utfwin_0096ffc0\",\n      \"va\": \"0x0096ffc0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Opaque\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"utfwin_0097e550\",\n      \"va\": \"0x0097e550\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Opaque\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"utfwin_0097e890\",\n      \"va\": \"0x0097e890\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Opaque\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"utfwin_00980200\",\n      \"va\": \"0x00980200\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Opaque\"\n      ],\n      \"package\": \"PKG-UTFWIN-EFFECTS-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"utfwin_00980470\",\n      \"va\": \"0x00980470\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Opaque\"\n      ],\n      \"package\": \"PKG-11-A2-PROGRESSION-ALTERNATIVE\",\n      \"score\": 3,\n      \"symbol\": \"mission_track_predicate_00febc90\",\n      \"va\": \"0x00febc90\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"ZoomOwner\",\n  \"cluster\": null,\n  \"confidence\": 0.86,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00658440\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0066daf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e15780\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ecf320\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ef50a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f149d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0106f3d0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00658734\",\n        \"direction\": \"in\",\n        \"other\": \"0x00658440\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0066e116\",\n        \"direction\": \"in\",\n        \"other\": \"0x0066daf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e15902\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e15780\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ecf3f3\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ecf320\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ef582c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ef50a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ef5d4f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ef50a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f14ad5\",\n        \"direction\": \"in\",\n        \"oth
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
  "body_end": "0083527c",
  "body_span_bytes": 733,
  "body_start": "00834fa0",
  "callees": [
    "FUN_008120d0",
    "FUN_009512c0",
    "FUN_008121b0",
    "FUN_009512d0",
    "FUN_00b5f950",
    "FUN_008105b0",
    "FUN_00810620",
    "FUN_00989000",
    "FUN_004eb930",
    "FUN_00834e30",
    "FUN_0080fee0"
  ],
  "callers": [
    "FUN_0106f3d0",
    "FUN_00ecf320",
    "FUN_00e15780",
    "FUN_00ef50a0",
    "FUN_00658440",
    "FUN_0066daf0",
    "FUN_00f149d0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00834fa0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00834fa0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x434fa0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00834fa0(void)",
  "size_bytes": 733,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00834fa0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 12,
  "xrefs": [
    {
      "from": "0066e116"
    },
    {
      "from": "00f14ad5"
    },
    {
      "from": "00658734"
    },
    {
      "from": "00e15902"
    },
    {
      "from": "00ef582c"
    },
    {
      "from": "00ef5d4f"
    },
    {
      "from": "0106f51c"
    },
    {
      "from": "00eb99a8"
    },
    {
      "from": "00eb9fca"
    },
    {
      "from": "00eb9903"
    },
    {
      "from": "00eb9a65"
    },
    {
      "from": "00ecf3f3"
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
  "file": "src/reconstruction/pkg18_ui_space/zoom_boundary_00834fa0.cpp",
  "files": [
    "reconstruction/staging/pkg18-ui-space/zoom_boundary_00834fa0.cpp",
    "reconstruction/staging/pkg18-ui-space/zoom_boundary_00834fa0.hpp",
    "reconstruction/staging/pkg18-ui-space/zoom_boundary_00834fa0_model_test.cpp",
    "src/reconstruction/pkg18_ui_space/zoom_boundary_00834fa0.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json",
    "reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg18-ui-space/00834fa0.json"
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
    "gate-ui-space-text-zoom-rebind"
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
  "original_bytes": 12645,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"STRUCTURAL_ONLY\",\n  \"confidence\": {\n    \"identity\": \"medium\",\n    \"mechanics\": \"high\",\n    \"overall\": \"medium-high\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 18,\n  \"evidence\": [\n    {\n      \"claim\": \"The target validates nested virtuals, has a same-binding fast path, replaces four associated objects, updates key/state fields, calls service 0x626e3b8, and returns 0/1.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G01\"\n    },\n    {\n      \"claim\": \"RET 0x1c confirms seven stack arguments; the UI/cSPUITextZoom literal and service callback are instruction-level facts.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G02\"\n    },\n    {\n      \"claim\": \"Seven named direct callers, eleven direct callees, and 26 depth-2 call-graph edges.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G03\"\n    },\n    {\n      \"claim\": \"cSPUITextZoom is 120 bytes; 0x008345c0 installs three vptrs and default sentinels; 0x00989000 returns a UTFWin Window-like object with relevant +0x20c state.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G04\"\n    },\n    {\n      \"claim\": \"Constructor, teardown, layout update, and SpaceGameUI sibling paths all operate on the same +0x64..+0x74 slots.\",\n      \"level\": \"SUPPORTED\",\n      \"source\": \"G05\"\n    },\n    {\n      \"claim\": \"The SDK exports cSPUITextZoom::Initialize and a 120-byte structure, but does not recover the target ABI.\",\n      \"level\": \"SUPPORTED\",\n      \"source\": \"C01\"\n    },\n    {\n      \"claim\": \"Canonical topology records seven direct callers, eleven direct callees, and nineteen direct reference edges.\",\n      \"level\": \"SUPPORTED\",\n      \"source\": \"C02\"\n    }\n  ],\n  \"family\": null,\n  \"interfaces\": {\n    \"boundaries\": {\n      \"boundary_judgment\": \"The object is a reusable presentation adapter. Gameplay-to-UI data association is upstream and must remain a separate seam.\",\n      \"gameplay_authority\": \"No direct health, collision, progression, save, or mode-state write observed.\",\n      \"gameplay_read_or_bridge\": \"Callers can provide entity, scenario, editor, or SpaceGameUI names/contexts; the target does not mutate the providers.\",\n      \"ui_owned_state\": \"text/source object, context/window object, layout/drawable object, resource key, dimensions, zoom/style state\"\n    },\n    \"direct_callees\": {\n      \"count\": 11,\n      \"direct_reference_edges_canonical\": 19,\n      \"endpoints\": [\n        \"0x004eb930\",\n        \"0x0080fee0\",\n        \"0x008105b0\",\n        \"0x00810620\",\n        \"0x008120d0\",\n        \"0x008121b0\",\n        \"0x00834e30\",\n        \"0x009512c0\",\n        \"0x009512d0\",\n        \"0x00989000\",\n        \"0x00b5f950\"\n      ],\n      \"root_edges\": []\n    },\n    \"direct_callers\": {\n      \"caller_boundary_evidence\": [\n        {\n          \"keys\": [\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"role\",\n            \"va\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"role\",\n            \"va\"\n          ]\n        }\n      ],\n      \"callsites\": [\n        \"0x00658734\",\n        \"0x0066e116\",\n        \"0x00e15902\",\n        \"0x00ecf3f3\",\n        \"0x00ef582c\",\n        \"0x00ef5d4f\",\n        \"0x0106f51c\"\n      ],\n      \"count\": 7,\n      \"named_endpoints\": [\n        \"0x00658440\",\n        \"0x0066daf0\",\n        \"0x00e15780\",\n        \"0x00ecf320\",\n        \"0x00ef50a0\",\n        \"0x00f149d0\",\n        \"0x0106f3d0\"\n      ],\n      \"unresolved_xrefs\": [\n        \"0x00eb9903\",\n        \"0x00eb99a8\",\n        \"0x00eb9a65\",\n        \"0x00eb9fca\"\n      ]\n    },\n    \"globals\": [],\n    \"structures\": {\n      \"constructor\": \"0x008345c0 writes three vptrs, a zero reference-count/derived state, and default resource sentinels.\",\n      \"constructor_vptrs\": [\n        \"0x0141ada8\",\n        \"0x0141ad98\",\n        \"0x0141ad7c\"\n      ],\n      \"factory\": {\n        \"role\": \"UTFWin Window-like factory; target uses the returned +0x20c subobject\",\n        \"va\": \"0x00989000\"\n      },\n      \"family_teardown\": {\n        \"role\": \"releases +0x68/+0x64/+0x70/+0x6c and clears related state\",\n        \"va\": \"0x00834e30\"\n      },\n      \"fields\": [\n        {\n          \"keys\": [\n            \"evidence\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"evidence\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"evidence\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"evidence\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n    
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
  "Opaque",
  "ZoomObject",
  "ZoomOwner",
  "ZoomOwner *",
  "ZoomVtable",
  "bool"
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
