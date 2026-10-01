# Evidence 0x005e0000

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f0f13db34f7f21645cf9d101b4334888130d8d9b6be755654d05094a73353715`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "return_register": "AL",
  "return_type": "bool",
  "stack_arguments": [
    {
      "entry_offset": "ESP+4",
      "name": "message_id",
      "signed": false,
      "type": "uint32_t",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+8",
      "name": "pMessage",
      "type": "opaque UTFWin::Message*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8
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
      "entry_ESP+0x14",
      "entry_ESP+0x18",
      "entry_ESP+0x1c",
      "entry_ESP+0x20",
      "entry_ESP+0xb4",
      "entry_ESP+0xc8",
      "entry_ESP+0xd0",
      "entry_ESP+0xd4",
      "entry_ESP+0xd8",
      "entry_ESP+0xf0",
      "entry_ESP+0xfc",
      "entry_ESP+0x10c"
    ],
    "ordinary_stack_arguments": [
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
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xb4",
        "observed": true,
        "ordinal": 45,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc8",
        "observed": true,
        "ordinal": 50,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xd0",
        "observed": true,
        "ordinal": 52,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xd4",
        "observed": true,
        "ordinal": 53,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xd8",
        "observed": true,
        "ordinal": 54,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0xf0",
        "observed": true,
        "ordinal": 60,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xfc",
        "observed": true,
        "ordinal": 63,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10c",
        "observed": true,
        "ordinal": 67,
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
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
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
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xb4",
        "observed": true,
        "ordinal": 45,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc8",
        "observed": true,
        "ordinal": 50,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xd0",
        "observed": true,
        "ordinal": 52,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xd4",
        "observed": true,
        "ordinal": 53,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xd8",
        "observed": true,
        "ordinal": 54,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0xf0",
        "observed": true,
        "ordinal": 60,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xfc",
        "observed": true,
        "ordinal": 63,
        "read": false,
        "size_infer
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
    "va": "0x004a88d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573c00"
  },
  {
    "name": "editor_query_service_005ca960",
    "reconstructed": true,
    "va": "0x005ca960"
  },
  {
    "name": "editor_query_reset_005dd750",
    "reconstructed": true,
    "va": "0x005dd750"
  },
  {
    "name": "FUN_005dda30",
    "reconstructed": true,
    "va": "0x005dda30"
  },
  {
    "name": "editor_query_dispatch_005dfd00",
    "reconstructed": true,
    "va": "0x005dfd00"
  },
  {
    "name": "editor_query_clear_flags_0093db80",
    "reconstructed": true,
    "va": "0x0093db80"
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
      "0x005e0000",
      "0x70218642",
      "0xb006ef6e",
      "0xf006efa5",
      "0xf019c2e7",
      "0xf019c2f3",
      "0x005e0000",
      "0x004af260",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x00587270",
      "0x00587270",
      "0x00588570",
      "0x00588570",
      "0x0058ac10"
    ],
    "conflict_id": "editor_ui_command_names",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
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
  "count": 295,
  "instructions": [
    {
      "address": "005e0000",
      "instruction": "SUB ESP,0x14"
    },
    {
      "address": "005e0003",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005e0004",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005e0006",
      "instruction": "LEA ECX,[ESI + 0x10]"
    },
    {
      "address": "005e0009",
      "instruction": "CALL 0x00810070"
    },
    {
      "address": "005e000e",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "005e0010",
      "instruction": "JNZ 0x005e001b"
    },
    {
      "address": "005e0012",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "005e0014",
      "instruction": "POP ESI"
    },
    {
      "address": "005e0015",
      "instruction": "ADD ESP,0x14"
    },
    {
      "address": "005e0018",
      "instruction": "RET 0x8"
    },
    {
      "address": "005e001b",
      "instruction": "CMP byte ptr [ESI + 0x9d],0x0"
    },
    {
      "address": "005e0022",
      "instruction": "JZ 0x005e0012"
    },
    {
      "address": "005e0024",
      "instruction": "CMP byte ptr [ESI + 0x9e],0x0"
    },
    {
      "address": "005e002b",
      "instruction": "JNZ 0x005e0012"
    },
    {
      "address": "005e002d",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005e002e",
      "instruction": "MOV EDI,dword ptr [ESP + 0x24]"
    },
    {
      "address": "005e0032",
      "instruction": "MOV EAX,dword ptr [EDI + 0x8]"
    },
    {
      "address": "005e0035",
      "instruction": "CMP EAX,0x9a1552d3"
    },
    {
      "address": "005e003a",
      "instruction": "JNZ 0x005e008d"
    },
    {
      "address": "005e003c",
      "instruction": "CMP dword ptr [EDI + 0xc],0x503517b0"
    },
    {
      "address": "005e0043",
      "instruction": "JNZ 0x005e0083"
    },
    {
      "address": "005e0045",
      "instruction": "MOV ECX,dword ptr [ESI + 0x70]"
    },
    {
      "address": "005e0048",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "005e004a",
      "instruction": "MOV EAX,dword ptr [EAX + 0xa4]"
    },
    {
      "address": "005e0050",
      "instruction": "LEA EDX,[ESP + 0x24]"
    },
    {
      "address": "005e0054",
      "instruction": "PUSH EDX"
    },
    {
      "address": "005e0055",
      "instruction": "LEA EDX,[ESP + 0x24]"
    },
    {
      "address": "005e0059",
      "instruction": "PUSH EDX"
    },
    {
      "address": "005e005a",
      "instruction": "CALL EAX"
    },
    {
      "address": "005e005c",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "005e005e",
      "instruction": "JZ 0x005e0083"
    },
    {
      "address": "005e0060",
      "instruction": "MOV EAX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "005e0064",
      "instruction": "MOV ECX,dword ptr [ESI + 0x70]"
    },
    {
      "address": "005e0067",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "005e0069",
      "instruction": "MOV EDX,dword ptr [EDX + 0x1c4]"
    },
    {
      "address": "005e006f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005e0070",
      "instruction": "MOV EAX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "005e0074",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005e0075",
      "instruction": "CALL EDX"
    },
    {
      "address": "005e0077",
      "instruction": "MOV ECX,dword ptr [ESI + 0x58]"
    },
    {
      "address": "005e007a",
      "instruction": "MOV EDX,dword ptr [ECX + 0x98]"
    },
    {
      "address": "005e0080",
      "instruction": "MOV dword ptr [EDX + 0x58],EAX"
    },
    {
      "address": "005e0083",
      "instruction": "POP EDI"
    },
    {
      "address": "005e0084",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "005e0086",
      "instruction": "POP ESI"
    },
    {
      "address": "005e0087",
      "instruction": "ADD ESP,0x14"
    },
    {
      "address": "005e008a",
      "instruction": "RET 0x8"
    },
    {
      "address": "005e008d",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005e008e",
      "instruction": "CMP EAX,0x287259f6"
    },
    {
      "address": "005e0093",
      "instruction": "JNZ 0x005e031d"
    },
    {
      "address": "005e0099",
      "instruction": "MOV ECX,dword ptr [EDI]"
    },
    {
      "address": "005e009b",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "005e009d",
      "instruction": "MOV EDX,dword ptr [EAX + 0x20]"
    },
    {
      "address": "005e00a0",
      "instruction": "LEA EBX,[ESI + -0x4]"
    },
    {
      "address": "005e00a3",
      "instruction": "CALL EDX"
    },
    {
      "address": "005e00a5",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005e00a6",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "005e00a8",
      "instruction": "CALL 0x005dfd00"
    },
    {
      "address": "005e00ad",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "005e00af",
      "instruction": "JNZ 0x005e0290"
    },
    {
      "address": "005e00b5",
      "instruction": "MOV EAX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "005e00b8",
      "instruction": "CMP EAX,0x447c4e8"
    },
    {
      "address": "005e00bd",
      "instruction": "JG 0x005e018a"
    },
    {
      "address": "005e00c3",
      "instruction": "JZ 0x005e01b0"
    },
    {
      "address": "005e00c9",
      "instruction": "CMP EAX,0x3f67720"
    },
    {
      "address": "005e00ce",
      "instruction": "JG 0x005e016c"
    },
    {
      "address": "005e00d4",
      "instruction": "JZ 0x005e01b0"
    },
    {
      "address": "005e00da",
      "instruction": "CMP EAX,0xf019c2e7"
    },
    {
      "address": "005e00df",
      "instruction": "JG 0x005e014d"
    },
    {
      "address": "005e00e1",
      "instruction": "JZ 0x005e0139"
    },
    {
      "address": "005e00e3",
      "instruction": "CMP EAX,0xb006ef6e"
    },
 
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
  "original_bytes": 20997,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"return_register\": \"AL\",\n    \"return_type\": \"bool\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+4\",\n        \"name\": \"message_id\",\n        \"signed\": false,\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+8\",\n        \"name\": \"pMessage\",\n        \"type\": \"opaque UTFWin::Message*\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"shared_types:OpaquePreferenceQuery,OpaquePropertyValue\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 17,\n      \"symbol\": \"editor_query_reset_005dd750\",\n      \"va\": \"0x005dd750\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"shared_types:OpaquePreferenceQuery\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 14,\n      \"symbol\": \"editor_query_clear_flags_0093db80\",\n      \"va\": \"0x0093db80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 13,\n      \"symbol\": \"FUN_005dda30\",\n      \"va\": \"0x005dda30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 11,\n      \"symbol\": \"editor_query_service_005ca960\",\n      \"va\": \"0x005ca960\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 11,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 10,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueUiMessage,opaque pointer\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 6,\n      \"symbol\": \"FUN_005bf9d0\",\n      \"va\": \"0x005bf9d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueUiMessage\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0100\",\n      \"va\": \"0x005c0100\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The binary provides no usable RTTI for the subobjects and payload variants.\",\n    \"The first 0x0c bytes and semantics of the preference query remain opaque, while its observed +0x0c/+0x10/+0x12 fields and 0x14-byte extent are recovered.\",\n    \"The mode-2 producer and dead target branch conflict cannot be reconciled without changing the live branch tree, so both facts remain explicit.\",\n    \"The target has no direct code callers; reachability beyond the IMessageListener vtable installation is not established.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueEditorUI\",\n  \"cluster\": null,\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a88d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573c00\"\n      },\n      {\n        \"name\": \"editor_query_service_005ca960\",\n        \"reconstructed\": true,\n        \"va\": \"0x005ca960\"\n      },\n      {\n        \"name\": \"editor_query_reset_005dd750\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dd750\"\n      },\n      {\n        \"name\": \"FUN_005dda30\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dda30\"\n      },\n      {\n        \"name\": \"editor_query_dispatch_005dfd00\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dfd00\"\n      },\n      {\n        \"name\": \"editor_query_clear_flags_0093db80\",\n        \"reconstructed\": true,\n        \"va\": \"0x0093db80\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005e00fa\",\n        \"direction\": \"out\",\n        \"other\": \"0x004a88d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005e011a\",\n        \"direction\": \"out\",\n        \"other\": \"0x004a88d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005e01d4\",\n        \"direction\": \"out\",\n        \"other\": \"0x004a88d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005e033e\",\n        \"direction\": \"out\",\n        \"other\": \"0x005724a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005e0353\",\n        \"direction\": \"out\",\n        \"other\": \"0x00573c00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005e025c\",\n        \"direction\": \"out\",\n        \"other\": \"0x0057c590\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005e0129\",\n        \"direction\": \"out\",\n        \"other\": \"0x0058a5a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\":
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
  "body_end": "005e0362",
  "body_span_bytes": 867,
  "body_start": "005e0000",
  "callees": [
    "FUN_004a88d0",
    "FUN_00810070",
    "FUN_00957f30",
    "FUN_0057c590",
    "Editors::cEditor::Undo",
    "FUN_006035d0",
    "FUN_0093db80",
    "FUN_006b1d50",
    "FUN_005dda30",
    "Editors::cEditor::Redo",
    "FUN_00573c00",
    "FUN_005ca960",
    "FUN_005dfd00",
    "FUN_006b1f90",
    "FUN_008105b0",
    "FUN_005dd750",
    "FUN_005724a0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005e0000",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005e0000",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1e0000",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005e0000(void)",
  "size_bytes": 867,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005e0000",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f925c"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "013f92d8"
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
  "file": "src/reconstruction/pkg10_editor_dispatch/editor_command_dispatch.cpp",
  "files": [
    "src/reconstruction/pkg10_editor_dispatch/editor_command_dispatch.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/005e0000.json"
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
    "gate-editor-ui-command-dispatch"
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
  "original_bytes": 9100,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"events\": \"SUPPORTED_FOR_ANALYTICAL_EVENT_IDS\",\n    \"identity\": \"SUPPORTED\",\n    \"mechanics\": \"CONFIRMED\",\n    \"overall\": \"high_for_static_dispatch_medium_for_payload_and_return_abi\",\n    \"ownership\": \"SUPPORTED_WITH_CAVEAT\",\n    \"persistence\": \"CONFIRMED_AS_NON_PERSISTENT\",\n    \"runtime\": \"UNAVAILABLE\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 17,\n  \"evidence\": [\n    {\n      \"claim\": \"command-hash switch, receiver guards, mode/history callbacks, and result branches\",\n      \"class\": \"direct_body\",\n      \"source\": \"ghidra://SporeApp.exe@0x005e0000\"\n    },\n    {\n      \"claim\": \"the EditorUI candidate pointer run contains the target address\",\n      \"class\": \"raw_vtable_data\",\n      \"source\": \"ghidra_read_memory(0x013f92a0, 128); target word at 0x013f92d8\"\n    },\n    {\n      \"claim\": \"300-byte EditorUI receiver with editor pointer, message references, mode/control fields, and opaque flag at +0x108\",\n      \"class\": \"structure_layout\",\n      \"source\": \"ghidra_get_struct_layout(EditorUI)\"\n    },\n    {\n      \"claim\": \"mode updater suppresses equal modes, calls cEditor::SetActiveMode, and changes UI window state\",\n      \"class\": \"mode_sibling\",\n      \"source\": \"ghidra://SporeApp.exe@0x005dda30\"\n    },\n    {\n      \"claim\": \"Undo and Redo are direct delegated state/history callbacks\",\n      \"class\": \"history_siblings\",\n      \"source\": \"ghidra_get_function_callees(0x005e0000); ghidra://SporeApp.exe@0x0058a5a0 and 0x0058a950\"\n    },\n    {\n      \"claim\": \"the adjacent cEditor message dispatcher is a separate message family with its own hash branches\",\n      \"class\": \"message_sibling\",\n      \"source\": \"ghidra://SporeApp.exe@0x00591fa0\"\n    },\n    {\n      \"claim\": \"known mode/undo/redo command routing and opaque payload limitation\",\n      \"class\": \"committed_artifact\",\n      \"source\": \"knowledgegraph/research/state-machines/editor-workflows.json:928-968; docs/analysis/event-message-map.md:56-60\"\n    }\n  ],\n  \"family\": \"editor-ui-command-dispatch\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": [\n      {\n        \"name\": \"Editors::cEditor::Undo\",\n        \"va\": \"0x0058a5a0\"\n      },\n      {\n        \"name\": \"Editors::cEditor::Redo\",\n        \"va\": \"0x0058a950\"\n      },\n      {\n        \"name\": \"FUN_004a88d0\",\n        \"va\": \"0x004a88d0\"\n      },\n      {\n        \"name\": \"FUN_005724a0\",\n        \"va\": \"0x005724a0\"\n      },\n      {\n        \"name\": \"FUN_00573c00\",\n        \"va\": \"0x00573c00\"\n      },\n      {\n        \"name\": \"FUN_0057c590\",\n        \"va\": \"0x0057c590\"\n      },\n      {\n        \"name\": \"FUN_005ca960\",\n        \"va\": \"0x005ca960\"\n      },\n      {\n        \"name\": \"FUN_005dd750\",\n        \"va\": \"0x005dd750\"\n      },\n      {\n        \"name\": \"FUN_005dda30\",\n        \"va\": \"0x005dda30\"\n      },\n      {\n        \"name\": \"FUN_005dfd00\",\n        \"va\": \"0x005dfd00\"\n      },\n      {\n        \"name\": \"FUN_006035d0\",\n        \"va\": \"0x006035d0\"\n      },\n      {\n        \"name\": \"FUN_006b1d50\",\n        \"va\": \"0x006b1d50\"\n      }\n    ],\n    \"direct_callers\": [],\n    \"globals\": [],\n    \"structures\": {\n      \"name\": \"EditorUI\",\n      \"selected_fields\": [\n        {\n          \"keys\": [\n            \"name\",\n            \"offset\",\n            \"role\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"offset\",\n            \"role\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"offset\",\n            \"role\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"offset\",\n            \"role\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"offset\",\n            \"role\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"offset\",\n            \"role\"\n          ]\n        }\n      ],\n      \"size_bytes\": 300\n    },\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": [\n        \"disabled global, +0x9d set, or +0x9e clear path returns zero\",\n        \"unknown command hashes return zero\",\n        \"some successful branches return one even when the delegated operation is a mode/history request\",\n        \"a service lookup failure in an opaque branch can return zero without a uniform exception/error protocol\"\n      ],\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [],\n      \"ordering\": [\n        \"global and receiver guard\",\n        \"read payload command hash and subtype/value\",\n        \"confirm or prepare the selected command path\",\n        \"invoke mode/history/service callback\",\n        \"return consumed/result code\"\n      ],\n      \"outputs\": [],\n      \"postconditions\": [\n        \"Known PlayMode command 0x70218642 routes to the mode updater and returns a consumed result.\",\n        \"Known Undo command 0xb006ef6e calls Editors::cEditor::Undo and returns a consumed result.\",\n        \"Known Redo command 0xf006efa5 calls Editors::cEditor::Redo and returns a consumed result.\",\n        \"Several opaque control hashes forward to an EditorUI/PlayMode/Editor subobject vtable and return its result.\",\n        \"Unknown or inactive branches return zero without a mode/history mutation.\"\n      ],\n      \"preconditions\": [\n        \"this is an EditorUI-compatible receiver\",\n        \"the global/feature gate returned by 0x00810070 is true\",\n        \"EditorUI+0x9d is false and EditorUI+0x9e is false 
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
  "OpaqueDispatchTarget",
  "OpaqueEditor / Editors::cEditor",
  "OpaqueEditorUI",
  "OpaquePreferenceQuery",
  "OpaquePreferenceQuery*",
  "OpaquePropertyValue",
  "OpaquePropertyValue / Property*",
  "OpaqueUiMessage",
  "OpaqueUiMessage / UTFWin::Message",
  "bool",
  "opaque UTFWin::Message*",
  "opaque command and dispatch targets",
  "opaque pointer",
  "uint32_t",
  "uint8_t",
  "void",
  "void adapter"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f92c0"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x005e0000",
      "0x70218642",
      "0xb006ef6e",
      "0xf006efa5",
      "0xf019c2e7",
      "0xf019c2f3",
      "0x005e0000",
      "0x004af260",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x00587270",
      "0x00587270",
      "0x00588570",
      "0x00588570",
      "0x0058ac10"
    ],
    "conflict_id": "editor_ui_command_names",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
