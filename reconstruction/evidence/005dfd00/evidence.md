# Evidence 0x005dfd00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `bb9049639cb700687095d36775b6e49e37437e9afe85122a5d1579417f3b0c74`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall observed",
  "hidden_this_register": "ECX",
  "return_register": "AL",
  "return_type": "std::uint8_t",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Command word selected by the 0x100-based switch table",
      "position": 1,
      "type": "std::uint32_t",
      "width_bytes": 4
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0xe8"
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
        "entry_offset": "entry_ESP+0xe8",
        "observed": true,
        "ordinal": 58,
        "read": false,
        "size_inferred": true,
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
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
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
        "entry_offset": "entry_ESP+0xe8",
        "observed": true,
        "ordinal": 58,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -268, so the listing is not one path",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0xe8; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x4 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0xe8 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "0b2532accf70add22de3b8086e0ecd018b995dc2f66c7325c3b6e7c73b1f30cd",
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
    "persisted_calling_convention": "__thiscall observed"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 5,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0021",
        "obs-0026",
        "obs-0030",
        "obs-0034",
        "obs-0038",
        "obs-0043",
        "obs-0048",
        "obs-0054",
        "obs-0059",
        "obs-0065",
        "obs-0070",
        "obs-0075",
        "obs-0081",
        "obs-0088",
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
        "obs-0021",
        "obs-0026",
        "obs-0030",
        "obs-0034",
        "obs-0038",
        "obs-0043",
        "obs-0048",
        "obs-0054",
        "obs-0059",
        "obs-0065",
        "obs-0070",
        "obs-0075",
        "obs-0081",
        "obs-0088",
        "obs-0091"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 4,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0076"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 56,
        "observed_slots": 2,
        "total_bytes": 232
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0010",
        "obs-0013",
        "obs-0076"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          200,
          208,
          380,
          384,
          452,
          564
        ],
        "register": "ECX",
        "written_through": 12
      }
    },
    {
      "based_on": [
        "obs-0091"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0021",
        "obs-0026",
        "obs-0030",
        "obs-0034",
        "obs-0038",
        "obs-0043",
        "obs-0048",
        "obs-0054",
        "obs-0059",
        "obs-0065",
        "obs-0070",
        "obs-0075",
        "obs-0081",
        "obs-0088",
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
        "obs-0021",
        "obs-0026",
        "obs-0030",
        "obs-0034",
        "obs-0038",
        "obs-0043",
        "obs-0048",
        "obs-0054",
        "obs-0059",
        "obs-0065",
        "obs-0070",
        "obs-0075",
        "obs-0081",
        "obs-0088",
        "obs-0091"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0021",
        "obs-0026",
        "obs-0030",
        "obs-0034",
        "obs-0038",
        "obs-0043",
   
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
    "va": "0x005dc310"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005dd610"
  },
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
    "name": "editor_input_0058ac10",
    "reconstructed": true,
    "va": "0x0058ac10"
  },
  {
    "name": "Editors_EditorUI_HandleMessage_005e0000",
    "reconstructed": true,
    "va": "0x005e0000"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006352d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006352f0"
  }
]
```

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
  "count": 220,
  "instructions": [
    {
      "address": "005dfd00",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "005dfd03",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005dfd04",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005dfd05",
      "instruction": "MOV EDI,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "005dfd09",
      "instruction": "LEA EAX,[EDI + 0xffffff00]"
    },
    {
      "address": "005dfd0f",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005dfd11",
      "instruction": "MOV byte ptr [ESI + 0xd0],0x1"
    },
    {
      "address": "005dfd18",
      "instruction": "CMP EAX,0xd"
    },
    {
      "address": "005dfd1b",
      "instruction": "JA 0x005dffb5"
    },
    {
      "address": "005dfd21",
      "instruction": "JMP dword ptr [EAX*0x4 + 0x5dffc0]"
    },
    {
      "address": "005dfd28",
      "instruction": "MOV EAX,[0x015fd918]"
    },
    {
      "address": "005dfd2d",
      "instruction": "MOV ECX,dword ptr [EAX + 0x3c]"
    },
    {
      "address": "005dfd30",
      "instruction": "CMP dword ptr [ECX + 0x118],0x0"
    },
    {
      "address": "005dfd37",
      "instruction": "JZ 0x005dfd78"
    },
    {
      "address": "005dfd39",
      "instruction": "CALL 0x0067dd30"
    },
    {
      "address": "005dfd3e",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005dfd40",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005dfd42",
      "instruction": "MOV EAX,dword ptr [EDX + 0x30]"
    },
    {
      "address": "005dfd45",
      "instruction": "PUSH 0x604a51a"
    },
    {
      "address": "005dfd4a",
      "instruction": "CALL EAX"
    },
    {
      "address": "005dfd4c",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005dfd4e",
      "instruction": "JZ 0x005dfd78"
    },
    {
      "address": "005dfd50",
      "instruction": "MOV dword ptr [ESI + 0xc8],0x604fa6b"
    },
    {
      "address": "005dfd5a",
      "instruction": "PUSH 0x1519a48"
    },
    {
      "address": "005dfd5f",
      "instruction": "ADD ESI,0xb4"
    },
    {
      "address": "005dfd65",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005dfd66",
      "instruction": "CALL 0x00809db0"
    },
    {
      "address": "005dfd6b",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "005dfd6e",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "005dfd70",
      "instruction": "POP EDI"
    },
    {
      "address": "005dfd71",
      "instruction": "POP ESI"
    },
    {
      "address": "005dfd72",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "005dfd75",
      "instruction": "RET 0x4"
    },
    {
      "address": "005dfd78",
      "instruction": "PUSH 0xa03e74b2"
    },
    {
      "address": "005dfd7d",
      "instruction": "MOV dword ptr [ESI + 0xcc],EDI"
    },
    {
      "address": "005dfd83",
      "instruction": "CALL 0x004a88d0"
    },
    {
      "address": "005dfd88",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "005dfd8b",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005dfd8d",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005dfd8f",
      "instruction": "CALL 0x005dc4d0"
    },
    {
      "address": "005dfd94",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "005dfd96",
      "instruction": "POP EDI"
    },
    {
      "address": "005dfd97",
      "instruction": "POP ESI"
    },
    {
      "address": "005dfd98",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "005dfd9b",
      "instruction": "RET 0x4"
    },
    {
      "address": "005dfd9e",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dfda0",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005dfda1",
      "instruction": "MOV dword ptr [ESI + 0xcc],EDI"
    },
    {
      "address": "005dfda7",
      "instruction": "CALL 0x005df470"
    },
    {
      "address": "005dfdac",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "005dfdae",
      "instruction": "POP EDI"
    },
    {
      "address": "005dfdaf",
      "instruction": "POP ESI"
    },
    {
      "address": "005dfdb0",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "005dfdb3",
      "instruction": "RET 0x4"
    },
    {
      "address": "005dfdb6",
      "instruction": "MOV dword ptr [ESI + 0xcc],EDI"
    },
    {
      "address": "005dfdbc",
      "instruction": "CALL 0x005dfb40"
    },
    {
      "address": "005dfdc1",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "005dfdc3",
      "instruction": "POP EDI"
    },
    {
      "address": "005dfdc4",
      "instruction": "POP ESI"
    },
    {
      "address": "005dfdc5",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "005dfdc8",
      "instruction": "RET 0x4"
    },
    {
      "address": "005dfdcb",
      "instruction": "MOV dword ptr [ESI + 0xcc],EDI"
    },
    {
      "address": "005dfdd1",
      "instruction": "CALL 0x005df8d0"
    },
    {
      "address": "005dfdd6",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "005dfdd8",
      "instruction": "POP EDI"
    },
    {
      "address": "005dfdd9",
      "instruction": "POP ESI"
    },
    {
      "address": "005dfdda",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "005dfddd",
      "instruction": "RET 0x4"
    },
    {
      "address": "005dfde0",
      "instruction": "PUSH 0xa03e74b2"
    },
    {
      "address": "005dfde5",
      "instruction": "MOV dword ptr [ESI + 0xcc],EDI"
    },
    {
      "address": "005dfdeb",
      "instruction": "CALL 0x004a88d0"
    },
    {
      "address": "005dfdf0",
      "instruction": "MOV ECX,dword ptr [ESI + 0xcc]"
    },
    {
      "address": "005dfdf6",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "005dfdf9",
      "instruction": "PUSH 0x1"
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
  "original_bytes": 11978,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall observed\",\n    \"hidden_this_register\": \"ECX\",\n    \"return_register\": \"AL\",\n    \"return_type\": \"std::uint8_t\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"observed_use\": \"Command word selected by the 0x100-based switch table\",\n        \"position\": 1,\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:OpaqueService\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 17,\n      \"symbol\": \"editor_query_service_005ca960\",\n      \"va\": \"0x005ca960\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 16,\n      \"symbol\": \"editor_query_reset_005dd750\",\n      \"va\": \"0x005dd750\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 16,\n      \"symbol\": \"editor_query_clear_flags_0093db80\",\n      \"va\": \"0x0093db80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 11,\n      \"symbol\": \"Editors_EditorUI_HandleMessage_005e0000\",\n      \"va\": \"0x005e0000\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 8,\n      \"symbol\": \"FUN_005dda30\",\n      \"va\": \"0x005dda30\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueService\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"service_005f9230\",\n      \"va\": \"0x005f9230\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No canonical persisted body or typed owner evidence exists for the external callback boundaries.\",\n    \"The function is high fan-in for component dispatch, but payload and runtime transition semantics remain unresolved.\",\n    \"The material and app-system branches dereference live service globals without a source-level null guard.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueEditorQueryContext\",\n  \"cluster\": null,\n  \"confidence\": 0.86,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a88d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dc310\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005dd610\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"editor_input_0058ac10\",\n        \"reconstructed\": true,\n        \"va\": \"0x0058ac10\"\n      },\n      {\n        \"name\": \"Editors_EditorUI_HandleMessage_005e0000\",\n        \"reconstructed\": true,\n        \"va\": \"0x005e0000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006352d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006352f0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0058b0d7\",\n        \"direction\": \"in\",\n        \"other\": \"0x0058ac10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058b2d4\",\n        \"direction\": \"in\",\n        \"other\": \"0x0058ac10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058b411\",\n        \"direction\": \"in\",\n        \"other\": \"0x0058ac10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058b52c\",\n        \"direction\": \"in\",\n        \"other\": \"0x0058ac10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005e00a8\",\n        \"direction\": \"in\",\n        \"other\": \"0x005e0000\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006352db\",\n        \"direction\": \"in\",\n        \"other\": \"0x006352d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006352fb\",\n        \"direction\": \"in\",\n        \"other\": \"0x006352f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dfd83\",\n        \"direction\": \"out\",\n        \"other\": \"0x004a88d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005dfdeb\",\n        \"direction\": \"out\",\n        \"other\": \"0x004a88d0\",\n        \"reference_type\": \"direct-call\"\n      },\
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
  "body_end": "005dffbe",
  "body_span_bytes": 703,
  "body_start": "005dfd00",
  "callees": [
    "FUN_00572260",
    "FUN_004a88d0",
    "FUN_005dd610",
    "FUN_005dc310",
    "FUN_005dd300",
    "FUN_005df8d0",
    "FUN_005dfb40",
    "FUN_008098f0",
    "FUN_005df470",
    "FUN_006035d0",
    "FUN_00809db0",
    "FUN_0064bc50",
    "FUN_00572190",
    "FUN_005dca00",
    "Graphics::IMaterialManager::Get",
    "FUN_005dc4d0",
    "App::IAppSystem::Get"
  ],
  "callers": [
    "Editors::cEditor::OnKeyDown",
    "FUN_006352d0",
    "FUN_006352f0",
    "FUN_005e0000"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005dfd00",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:1",
      "type": "undefined"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
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
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_005dfd00",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1dfd00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005dfd00(void)",
  "size_bytes": 703,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005dfd00",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "005e00a8"
    },
    {
      "from": "0058b0d7"
    },
    {
      "from": "0058b2d4"
    },
    {
      "from": "0058b411"
    },
    {
      "from": "0058b52c"
    },
    {
      "from": "006352db"
    },
    {
      "from": "006352fb"
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
  "global:0x015fd918"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg10_editor_dispatch/editor_query_helpers.cpp",
  "files": [
    "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.cpp",
    "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers.hpp",
    "reconstruction/staging/pkg10-editor-dispatch/editor_query_helpers_model_test.cpp",
    "src/reconstruction/pkg10_editor_dispatch/editor_query_helpers.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/005dfd00.json"
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
    "gate-editor-query-helpers"
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
  "OpaqueAppProperties",
  "OpaqueEditorQueryContext",
  "OpaqueMaterialManager",
  "OpaqueService",
  "std::uint32_t",
  "std::uint8_t"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
