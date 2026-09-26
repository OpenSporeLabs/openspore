# Evidence 0x005dc310

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c436e92480bc43932c531501e7c2d14b69b0627e5c247d789753af4180063c0c`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "return_type": "void*",
  "stack_arguments": [
    {
      "entry_offset": "ESP+4",
      "name": "lookup_key",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
}
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
    "name": "Editors::cEditor::Update",
    "reconstructed": false,
    "va": "0x0058be50"
  },
  {
    "name": "Editors::cEditor::HandleMessage",
    "reconstructed": false,
    "va": "0x00591fa0"
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
    "name": null,
    "reconstructed": false,
    "va": "0x00634e40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00634f20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635010"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635390"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635400"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006354c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635520"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635580"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635600"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635680"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00635790"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nvoid FUN_005dc310(undefined4 param_1)\n\n{\n  int iVar1;\n  \n  iVar1 = FUN_008105b0(param_1,1);\n  if (iVar1 == 0) {\n    FUN_008105b0(param_1,1);\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 17,
  "instructions": [
    {
      "address": "005dc310",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005dc311",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005dc312",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "005dc316",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005dc318",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dc31a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005dc31b",
      "instruction": "LEA ECX,[ESI + 0x14]"
    },
    {
      "address": "005dc31e",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005dc323",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005dc325",
      "instruction": "JNZ 0x005dc332"
    },
    {
      "address": "005dc327",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "005dc329",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005dc32a",
      "instruction": "LEA ECX,[ESI + 0x2c]"
    },
    {
      "address": "005dc32d",
      "instruction": "CALL 0x008105b0"
    },
    {
      "address": "005dc332",
      "instruction": "POP EDI"
    },
    {
      "address": "005dc333",
      "instruction": "POP ESI"
    },
    {
      "address": "005dc334",
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
  "original_bytes": 11491,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"return_type\": \"void*\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+4\",\n        \"name\": \"lookup_key\",\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"palette_safe_wave11_fill_node_array_005c7ff0\",\n      \"va\": \"0x005c7ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 5,\n      \"symbol\": \"FUN_005dda30\",\n      \"va\": \"0x005dda30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005fa8d0\",\n      \"va\": \"0x005fa8d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_0060ee90\",\n      \"va\": \"0x0060ee90\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 5,\n      \"symbol\": \"FUN_00aea230\",\n      \"va\": \"0x00aea230\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"editor_query_dispatch_005dfd00\",\n      \"va\": \"0x005dfd00\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"re_00835380\",\n      \"va\": \"0x00835380\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"Ghidra currently records a void return, so a more specific result type is not supported by the recovered prototype.\",\n    \"The result remains void*: no target owner, RTTI identity, lifetime, or ownership is asserted.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"Editors::cEditor::Update\",\n        \"reconstructed\": false,\n        \"va\": \"0x0058be50\"\n      },\n      {\n        \"name\": \"Editors::cEditor::HandleMessage\",\n        \"reconstructed\": false,\n        \"va\": \"0x00591fa0\"\n      },\n      {\n        \"name\": \"FUN_005dda30\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dda30\"\n      },\n      {\n        \"name\": \"editor_query_dispatch_005dfd00\",\n        \"reconstructed\": true,\n        \"va\": \"0x005dfd00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00634e40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00634f20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635010\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635390\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635400\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006354c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635520\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635580\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635600\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635680\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00635790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006358c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00636320\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00636560\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006373e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006377d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00637860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00637c90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00637f80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00638430\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_cou
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
  "body_end": "005dc336",
  "body_span_bytes": 39,
  "body_start": "005dc310",
  "callees": [
    "FUN_008105b0"
  ],
  "callers": [
    "FUN_00638430",
    "FUN_006354c0",
    "FUN_00637c90",
    "FUN_00635600",
    "FUN_00635390",
    "FUN_005dda30",
    "FUN_00636560",
    "FUN_00636320",
    "Editors::cEditor::Update",
    "FUN_00635160",
    "FUN_00637f80",
    "FUN_00635520",
    "FUN_00635010",
    "FUN_006358c0",
    "FUN_00635680",
    "FUN_00635580",
    "FUN_005dfd00",
    "FUN_00635790",
    "FUN_006373e0",
    "FUN_006377d0",
    "Editors::cEditor::HandleMessage",
    "FUN_00634f20",
    "FUN_00635400",
    "FUN_00637860",
    "FUN_00634e40"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005dc310",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_005dc310",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1dc310",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005dc310(void)",
  "size_bytes": 39,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005dc310",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 69,
  "xrefs": [
    {
      "from": "005ddaba"
    },
    {
      "from": "005ddad7"
    },
    {
      "from": "005ddaf4"
    },
    {
      "from": "005ddb11"
    },
    {
      "from": "005ddba8"
    },
    {
      "from": "005ddbc5"
    },
    {
      "from": "005ddbe2"
    },
    {
      "from": "005ddbff"
    },
    {
      "from": "005ddc6a"
    },
    {
      "from": "005ddc87"
    },
    {
      "from": "005ddca4"
    },
    {
      "from": "00635973"
    },
    {
      "from": "0063599e"
    },
    {
      "from": "0063518a"
    },
    {
      "from": "006354fa"
    },
    {
      "from": "00637413"
    },
    {
      "from": "00637442"
    },
    {
      "from": "0063745f"
    },
    {
      "from": "0063552f"
    },
    {
      "from": "0063539c"
    },
    {
      "from": "00634f2b"
    },
    {
      "from": "0063579b"
    },
    {
      "from": "0063501b"
    },
    {
      "from": "0063540f"
    },
    {
      "from": "0063542f"
    },
    {
      "from": "00636fda"
    },
    {
      "from": "00637045"
    },
    {
      "from": "0063788e"
    },
    {
      "from": "006378ec"
    },
    {
      "from": "00637916"
    },
    {
      "from": "0063795a"
    },
    {
      "from": "0063799e"
    },
    {
      "from": "006379e2"
    },
    {
      "from": "00637a26"
    },
    {
      "from": "00637a46"
    },
    {
      "from": "00637a66"
    },
    {
      "from": "00637a86"
    },
    {
      "from": "00637aa6"
    },
    {
      "from": "00637ac6"
    },
    {
      "from": "00637ae6"
    },
    {
      "from": "00637b06"
    },
    {
      "from": "00637b27"
    },
    {
      "from": "00637b88"
    },
    {
      "from": "00637bc4"
    },
    {
      "from": "00637c1a"
    },
    {
      "from": "00637ceb"
    },
    {
      "from": "00637d3c"
    },
    {
      "from": "00637d59"
    },
    {
      "from": "00637db9"
    },
    {
      "from": "00637e12"
    },
    {
      "from": "00637e2f"
    },
    {
      "from": "00637e8f"
    },
    {
      "from": "0063560c"
    },
    {
      "from": "0063568c"
    },
    {
      "from": "006363cd"
    },
    {
      "from": "006363ee"
    },
    {
      "from": "00638455"
    },
    {
      "from": "00638027"
    },
    {
      "from": "00638039"
    },
    {
      "from": "00638259"
    },
    {
      "from": "0063558c"
    },
    {
      "from": "006377db"
    },
    {
      "from": "00634e46"
    },
    {
      "from": "005dff89"
    },
    {
      "from": "0058c7e3"
    },
    {
      "from": "0058ca9a"
    },
    {
      "from": "0059230f"
    },
    {
      "from": "00592377"
    },
    {
      "from": "005925ae"
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
  "files": [],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg10-editor-dispatch/005dc310.json"
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "Opaque void* for the lookup result; no concrete target owner or ownership contract is asserted",
  "OpaqueEditorModeManager for ECX",
  "uint32_t",
  "uint32_t for the lookup key",
  "void*"
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
