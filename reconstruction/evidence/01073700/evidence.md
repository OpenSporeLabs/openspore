# Evidence 0x01073700

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b8c4bc7eb049b15ea59a7ae0fd03b0aaee45fa6333d3a1d1d3f9c36650f98173`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "receiver": {
    "register": "ECX",
    "type": "SpaceUiState *",
    "width_bytes": 4
  },
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "termination": "RET for the normal path; saved-image non-null path transfers through the saved image vtable +0x04 slot"
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "unparsed_lines_present: 2 line(s) matched no grammar rule",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "c0e5b459ed968683d3f85cfed5c19780d598cec17fd893d13eb9d61a22c2b7d2",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
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
    "indirect_calls": 50,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0240"
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
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0071",
        "obs-0074",
        "obs-0079",
        "obs-0097",
        "obs-0101",
        "obs-0117",
        "obs-0143",
        "obs-0149",
        "obs-0162",
        "obs-0164",
        "obs-0167",
        "obs-0177",
        "obs-0179",
        "obs-0206",
        "obs-0230"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          548,
          552,
          556,
          560,
          564,
          600,
          760,
          796,
          1388,
          1392,
          1396,
          1400,
          1404,
          1408,
          1432,
          1436,
          1440,
          1444,
          1448,
          1476,
          1493,
          1564,
          1680,
          1684
        ],
        "register": "ECX",
        "written_through": 26
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0240"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "id": "obs-0001"
    },
    {
      "id": "obs-0002"
    },
    {
      "id": "obs-0003"
    },
    {
      "id": "obs-0004"
    },
    {
      "id": "obs-0005"
    },
    {
      "id": "obs-0006"
    },
    {
      "id": "obs-0007"
    },
    {
      "id": "obs-0008"
    },
    {
      "id": "obs-0009"
    },
    {
      "id": "obs-0010"
    },
    {
      "id": "obs-0011"
    },
    {
      "id": "obs-0012"
    },
    {
      "id": "obs-0013"
    },
    {
      "id": "obs-0014"
    },
    {
      "id": "obs-0015"
    },
    {
      "id": "obs-0016"
    },
    {
      "id": "obs-0017"
    },
    {
      "id": "obs-0018"
    },
    {
      "id": "obs-0019"
    },
    {
      "id": "obs-0020"
    },
    {
      "id": "obs-0021"
    },
    {
      "id": "obs-0022"
    },
    {
      "id": "obs-0023"
    },
    {
      "id": "obs-0024"
    },
    {
      "id": "obs-0025"
    },
    {
      "id": "obs-0026"
    },
    {
      "id": "obs-0027"
    },
    {
      "id": "obs-0028"
    },
    {
      "id": "obs-0029"
    },
    {
      "id": "obs-0030"
    },
    {
      "id": "obs-0031"
    },
    {
      "id": "obs-0032"
    },
    {
      "id": "obs-0033"
    },
    {
      "id": "obs-0034"
    },
    {
      "id": "obs-0035"
    },
    {
      "id": "obs-0036"
    },
    {
      "id": "obs-0037"
    },
    {
      "id": "obs-0038"
    },
    {
      "id": "obs-0039"
    },
    {
      "id": "obs-0040"
    },
    {
      "id": "obs-0041"
    },
    {
      "id": "obs-0042"
    },
    {
      "id": "obs-0043"
    },
    {
      "id": "obs-0044"
    },
    {
      "id": "obs-0045"
    },
    {
      "id": "obs-0046"
    },
    {
      "id": "obs-0047"
    },
    {
      "id": "obs-0048"
    },
    {
      "id": "obs-0049"
    },
    {
      "id": "obs-0050"
    },
    {
      "id": "obs-0051"
    },
    {
      "id": "obs-0052"
    },
    {
      "id": "obs-0053"
    },
    {
      "id": "obs-0054"
    },
    {
      "id": "obs-0055"
    },
    {
      "id": "obs
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
  },
  {
    "name": "pkg11_sim_core_00b21340",
    "reconstructed": true,
    "va": "0x00b21340"
  },
  {
    "name": "FUN_00b3d230",
    "reconstructed": false,
    "va": "0x00b3d230"
  },
  {
    "name": "FUN_00b3d300",
    "reconstructed": true,
    "va": "0x00b3d300"
  },
  {
    "name": "pkg12_space_01021300",
    "reconstructed": true,
    "va": "0x01021300"
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
    "va": "0x010030c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01003230"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01006ef0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01007430"
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
  "count": 985,
  "instructions": [
    {
      "address": "01073700",
      "instruction": "SUB ESP,0x48"
    },
    {
      "address": "01073703",
      "instruction": "PUSH EBX"
    },
    {
      "address": "01073704",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01073705",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01073706",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "01073708",
      "instruction": "MOV ECX,dword ptr [ESI + 0x580]"
    },
    {
      "address": "0107370e",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0107370f",
      "instruction": "LEA EDI,[ESI + 0x580]"
    },
    {
      "address": "01073715",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01073717",
      "instruction": "JZ 0x01073726"
    },
    {
      "address": "01073719",
      "instruction": "MOV dword ptr [EDI],0x0"
    },
    {
      "address": "0107371f",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01073721",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01073724",
      "instruction": "CALL EDX"
    },
    {
      "address": "01073726",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "01073728",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "0107372a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0107372c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0107372d",
      "instruction": "PUSH 0x149c538"
    },
    {
      "address": "01073732",
      "instruction": "PUSH 0x106c7116"
    },
    {
      "address": "01073737",
      "instruction": "PUSH 0x2f7d0004"
    },
    {
      "address": "0107373c",
      "instruction": "CALL 0x00806320"
    },
    {
      "address": "01073741",
      "instruction": "ADD ESP,0x1c"
    },
    {
      "address": "01073744",
      "instruction": "CMP dword ptr [ESI + 0x224],0x0"
    },
    {
      "address": "0107374b",
      "instruction": "JNZ 0x01073779"
    },
    {
      "address": "0107374d",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0107374f",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "01073751",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "01073753",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "01073755",
      "instruction": "PUSH 0x13f6b3c"
    },
    {
      "address": "0107375a",
      "instruction": "PUSH 0x68"
    },
    {
      "address": "0107375c",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "01073761",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "01073764",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "01073766",
      "instruction": "JZ 0x01073771"
    },
    {
      "address": "01073768",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0107376a",
      "instruction": "CALL 0x00e03ab0"
    },
    {
      "address": "0107376f",
      "instruction": "JMP 0x01073773"
    },
    {
      "address": "01073771",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "01073773",
      "instruction": "MOV dword ptr [ESI + 0x224],EAX"
    },
    {
      "address": "01073779",
      "instruction": "MOV ECX,dword ptr [ESI + 0x224]"
    },
    {
      "address": "0107377f",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01073781",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "01073784",
      "instruction": "PUSH 0x15b9294"
    },
    {
      "address": "01073789",
      "instruction": "CALL EDX"
    },
    {
      "address": "0107378b",
      "instruction": "CMP dword ptr [ESI + 0x22c],0x0"
    },
    {
      "address": "01073792",
      "instruction": "JNZ 0x010737e6"
    },
    {
      "address": "01073794",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "01073796",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "01073798",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0107379a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0107379c",
      "instruction": "PUSH 0x13f6b3c"
    },
    {
      "address": "010737a1",
      "instruction": "PUSH 0x18"
    },
    {
      "address": "010737a3",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "010737a8",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "010737ab",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "010737ad",
      "instruction": "JZ 0x010737ba"
    },
    {
      "address": "010737af",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "010737b1",
      "instruction": "CALL 0x00810000"
    },
    {
      "address": "010737b6",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "010737b8",
      "instruction": "JMP 0x010737bc"
    },
    {
      "address": "010737ba",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "010737bc",
      "instruction": "MOV EBX,dword ptr [ESI + 0x22c]"
    },
    {
      "address": "010737c2",
      "instruction": "CMP EDI,EBX"
    },
    {
      "address": "010737c4",
      "instruction": "JZ 0x010737e6"
    },
    {
      "address": "010737c6",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "010737c8",
      "instruction": "JZ 0x010737d3"
    },
    {
      "address": "010737ca",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "010737cc",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "010737cf",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "010737d1",
      "instruction": "CALL EDX"
    },
    {
      "address": "010737d3",
      "instruction": "MOV dword ptr [ESI + 0x22c],EDI"
    },
    {
      "address": "010737d9",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "010737db",
      "instruction": "JZ 0x010737e6"
    }
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
  "original_bytes": 25990,
  "preview": "{\n  \"abi\": {\n    \"receiver\": {\n      \"register\": \"ECX\",\n      \"type\": \"SpaceUiState *\",\n      \"width_bytes\": 4\n    },\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"RET for the normal path; saved-image non-null path transfers through the saved image vtable +0x04 slot\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-18-UI-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"pkg18_text_zoom_rebind_00834fa0\",\n      \"va\": \"0x00834fa0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 3,\n      \"symbol\": \"pkg11_sim_core_00b21340\",\n      \"va\": \"0x00b21340\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 3,\n      \"symbol\": \"pkg12_space_01021300\",\n      \"va\": \"0x01021300\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"runtime_gated\",\n  \"class_type\": \"SpaceUiState\",\n  \"cluster\": null,\n  \"confidence\": 0.82,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      },\n      {\n        \"name\": \"pkg11_sim_core_00b21340\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b21340\"\n      },\n      {\n        \"name\": \"FUN_00b3d230\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b3d230\"\n      },\n      {\n        \"name\": \"FUN_00b3d300\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d300\"\n      },\n      {\n        \"name\": \"pkg12_space_01021300\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021300\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010030c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01003230\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01006ef0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01007430\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0100311c\",\n        \"direction\": \"in\",\n        \"other\": \"0x010030c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0100335b\",\n        \"direction\": \"in\",\n        \"other\": \"0x01003230\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010072c4\",\n        \"direction\": \"in\",\n        \"other\": \"0x01006ef0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010076d9\",\n        \"direction\": \"in\",\n        \"other\": \"0x01007430\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01073dcb\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01073dd7\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01073e54\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010741ac\",\n        \"direction\": \"out\",\n        \"other\": \"0x00685520\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01073faa\",\n        \"direction\": \"out\",\n        \"other\": \"0x006b5060\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01074080\",\n        \"direction\": \"out\",\n        \"other\": \"0x006b5240\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01073fbe\",\n        \"direction\": \"out\",\n        \"other\": \"0x006b54b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01073fd6\",\n        \"direction\": \"out\",\n        \"other\": \"0x006b55c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010740fc\",\n        \"direction\": \"out\",\n        \"other\": \"0x006b55c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0107412b\",\n        \"direction\": \"out\",\n        \"other\": \"0x006b55c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0107373c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00806320\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01074103\",\n        \"direction\": \"out\",\n        \"other\": \"0x00806de0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01074132\",\n        \"direction\": \"out\",\n        \"other\": \"0x00806de0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01073eec\",\n        \"direction\": \"out\",\n        \"other\": \"0x00807bb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x010737b1\",\n        \"direction\": \"out\",\n    
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
  "body_end": "0107439c",
  "body_span_bytes": 3229,
  "body_start": "01073700",
  "callees": [
    "FUN_00b21340",
    "FUN_01048ce0",
    "FUN_006b54b0",
    "FUN_0106b500",
    "FUN_006b55c0",
    "UTFWin::Image::GetImage",
    "FUN_006b5060",
    "FUN_00e31050",
    "FUN_008120d0",
    "FUN_00810000",
    "App::IAppSystem::Get",
    "FUN_00806de0",
    "FUN_00b3d230",
    "FUN_00e2c920",
    "FUN_00e29c80",
    "FUN_0093b6c0",
    "FUN_0106a280",
    "FUN_01068f70",
    "FUN_010666b0",
    "FUN_00e2f370",
    "FUN_00e012b0",
    "FUN_006b5240",
    "FUN_00e36480",
    "FUN_01002bd0",
    "FUN_00e0fc90",
    "FUN_0106e020",
    "FUN_00f473a0",
    "App::cIDGenerator::Get",
    "FUN_009512d0",
    "FUN_00c326b0",
    "FUN_00807bb0",
    "FUN_01070290",
    "FUN_0083c800",
    "FUN_01072680",
    "FUN_00812160",
    "FUN_00e03ab0",
    "FUN_009512c0",
    "FUN_01021300",
    "FUN_00e25710",
    "FUN_00e0c1f0",
    "FUN_0106a4e0",
    "FUN_01066880",
    "FUN_00b3d300",
    "FUN_01071a00",
    "FUN_01046fc0",
    "FUN_00e28a10",
    "FUN_00fe75d0",
    "FUN_008105b0",
    "FUN_00e36b30",
    "FUN_00810590",
    "FUN_00685520"
  ],
  "callers": [
    "FUN_01003230",
    "FUN_01006ef0",
    "FUN_010030c0",
    "FUN_01007430"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01073700",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_01073700",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc73700",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01073700(void)",
  "size_bytes": 3229,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01073700",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "0100335b"
    },
    {
      "from": "010072c4"
    },
    {
      "from": "0100311c"
    },
    {
      "from": "010076d9"
    },
    {
      "from": "01075143"
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
  "file": "src/reconstruction/pkg18_ui_space/ui_space.cpp",
  "files": [
    "src/reconstruction/pkg18_ui_space/ui_space.cpp",
    "src/reconstruction/pkg18_ui_space/ui_space.hpp",
    "src/reconstruction/pkg18_ui_space/ui_space_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg18-ui-space/01073700.json"
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
    "gate-ui-space-initialization"
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
  "original_bytes": 14463,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"identity\": \"medium-high\",\n    \"mechanics\": \"high\",\n    \"overall\": \"medium-high\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 55,\n  \"evidence\": [\n    {\n      \"claim\": \"The body creates/replaces named space UI resources, writes field_2F8=-1 and field_5D5=1, configures listener data, and invokes the optional Simulator branch.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G01\"\n    },\n    {\n      \"claim\": \"Instruction 0x01073a2e writes [ESI+0x2f8]=0xffffffff; the target has a 0x01074393 jump-table warning and indirect tail.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G02\"\n    },\n    {\n      \"claim\": \"Four named direct callers and 51 direct callee endpoints; three direct root edges are present.\",\n      \"level\": \"OBSERVED\",\n      \"limit\": 100,\n      \"source\": \"G03\"\n    },\n    {\n      \"claim\": \"SpaceGameUI is 1708 bytes, matching the 0x6ac allocation; 0x0149c3ec is a seven-slot IWinProc candidate and 0x0149c1d8 is a helper table/string record.\",\n      \"level\": \"OBSERVED\",\n      \"source\": \"G04\"\n    },\n    {\n      \"claim\": \"0x01070ba0 supplies the 0x6ac object, vptrs, mActivePaletteID=0, and field_2F8=-1; 0x01072d40 is the sibling IWinProc event handler.\",\n      \"level\": \"SUPPORTED\",\n      \"source\": \"G05\"\n    },\n    {\n      \"claim\": \"SDK SpaceGameUI layout identifies the field offsets, MessageListenerData shape, GlobalUI, Minimap, and CivCommCursorAttachment.\",\n      \"level\": \"SUPPORTED\",\n      \"source\": \"C01\"\n    },\n    {\n      \"claim\": \"Canonical xref topology records four inbound direct callers, 51 outbound destinations, and 91 direct reference edges.\",\n      \"level\": \"SUPPORTED\",\n      \"limit\": 100,\n      \"source\": \"C02\"\n    }\n  ],\n  \"family\": null,\n  \"interfaces\": {\n    \"boundaries\": {\n      \"boundary_judgment\": \"UI-to-gameplay service bridge is real, but the function is a UI lifecycle orchestrator rather than a gameplay authority.\",\n      \"gameplay_authority\": \"No direct write to cell state, health, collision, progression, save state, or active game-mode index observed in the assigned body.\",\n      \"gameplay_read_or_bridge\": \"Reads/invokes 0x00b3d300, 0x00b21340, 0x01021300, player inventory/service objects, and optional Simulator objects.\",\n      \"ui_owned_state\": \"layouts, tooltips, minimap, UI windows, callback/listener block, flash-window manager, PosseBar, field_2F8, field_5D5\"\n    },\n    \"direct_callees\": {\n      \"count\": 51,\n      \"direct_reference_edges_canonical\": 91,\n      \"endpoints\": [\n        \"0x0067dcc0\",\n        \"0x0067de20\",\n        \"0x00685520\",\n        \"0x006b5060\",\n        \"0x006b5240\",\n        \"0x006b54b0\",\n        \"0x006b55c0\",\n        \"0x00806de0\",\n        \"0x00807bb0\",\n        \"0x00810000\",\n        \"0x00810590\",\n        \"0x008105b0\"\n      ],\n      \"root_edges\": [\n        \"0x00b3d300\",\n        \"0x00b21340\",\n        \"0x01021300\"\n      ]\n    },\n    \"direct_callers\": {\n      \"additional_unresolved_xref\": \"0x01075143 is an unconditional-call xref with no resolved containing function and is not counted as a direct caller.\",\n      \"caller_evidence\": \"Each named caller is a Simulator setup path that allocates/checks a 0x6ac object through 0x01070ba0 and then invokes the target.\",\n      \"callsites\": [\n        \"0x0100311c\",\n        \"0x0100335b\",\n        \"0x010072c4\",\n        \"0x010076d9\"\n      ],\n      \"count\": 4,\n      \"named_endpoints\": [\n        \"0x010030c0\",\n        \"0x01003230\",\n        \"0x01006ef0\",\n        \"0x01007430\"\n      ]\n    },\n    \"globals\": [],\n    \"structures\": {\n      \"allocation_size_observed\": 1708,\n      \"data_strings\": [\n        {\n          \"keys\": [\n            \"address\",\n            \"value\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"address\",\n            \"value\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"address\",\n            \"value\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"address\",\n            \"value\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"value\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"value\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"value\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"value\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"value\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"value\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"note\",\n            \"value\"\n          ]\n        }\n      ],\n      \"fields\": [\n        {\n          \"keys\": [\n            \"evidence\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"evidence\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"evidence\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"evidence\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"access\",\n            \"name\",\n            \"offset\"\n          ]\n        },\n        {\n          \"keys\": [\n       
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
  "SpaceUiObject",
  "SpaceUiObject *",
  "SpaceUiState",
  "SpaceUiState *",
  "SpaceUiVtable"
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
