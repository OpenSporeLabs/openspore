# Evidence 0x0059d110

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `982c182765a23a1e698387cefd8edb34e95e21fedfc72cfd101debeea2b6e1d2`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX, moved to EDI at 0x0059d117 and held for the whole body",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "0x0059d169 MOV AL,0x1 on the success path and 0x0059d171 XOR AL,AL on the failure path. Neither writes the upper bytes of EAX, so bits 8..31 are undefined on exit. Every inspected call site consumes the answer with TEST AL,AL followed by JZ, never as a dword.",
  "return_register": "AL",
  "return_semantics": "a byte-valued predicate: 1 when the position was written, 0 when any of the three guards rejected the query",
  "return_type": "bool",
  "return_width_bytes": 1,
  "saved_registers": [
    "ECX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "proof": "0x0059d111 MOV EAX,[ESP+0x8] reads it after the single PUSH ECX, i.e. the first stack slot; 0x0059d11d re-stores it locally and both map ports receive its address",
      "role": "creature_id",
      "slot": "[ESP_entry+4]"
    },
    {
      "proof": "0x0059d128 LEA EDX,[ESP+0xc] with ESP already lowered by 8 resolves to ESP_entry+8 and is pushed as the second argument to the find port; 0x0059d156 MOV ECX,[ESP+0x14] reloads the same slot on the copy path",
      "role": "out_position",
      "slot": "[ESP_entry+8]"
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "two exits, 0x0059d16d and 0x0059d175, both RET 0x8 and both preceded by POP EDI / POP ESI / POP ECX"
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
        "size_inferred": true,
        "sizes": [
          4
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
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "8ffc80697ea210d2e3e8a31fdef7a5684754a96b3ccf44714d26d7fd3cb2e063",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0022",
        "obs-0026"
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
        "obs-0003",
        "obs-0009",
        "obs-0010"
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
        "obs-0001",
        "obs-0007",
        "obs-0010",
        "obs-0013",
        "obs-0018",
        "obs-0021",
        "obs-0025"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          56
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0007",
        "obs-0010",
        "obs-0013",
        "obs-0018",
        "obs-0021",
        "obs-0022",
        "obs-0025",
        "obs-0026"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0022",
        "obs-0026"
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
        "obs-0022",
        "obs-0026"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0022",
        "obs-0026"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x0059d110",
      "count": 8,
      "first_use": 0,
      "first_write_index": 13,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0059d111",
      "count": 6,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x0059d111",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0059d111",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0059d115",
      "count": 4,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0059d116",
      "count": 3,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x0059d117",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x0059d11d",
      "count": 9,
      "first_use": 6,
      "first_write_index": 1,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ESP + 0x10],EAX",
      "reg": "EAX"
    },
    {
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "map_int_EditorCreatureControllerPtr__get",
    "reconstructed": false,
    "va": "0x0059c740"
  },
  {
    "name": "map_int_whatever_find",
    "reconstructed": true,
    "va": "0x00e5c780"
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
    "va": "0x00577e10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00582d70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00582fe0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00583900"
  },
  {
    "name": "Editors::cEditor::Update",
    "reconstructed": false,
    "va": "0x0058be50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00628f10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00629590"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062abd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00639350"
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
  "count": 43,
  "instructions": [
    {
      "address": "0059d110",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0059d111",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0059d115",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0059d116",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0059d117",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "0059d119",
      "instruction": "CMP dword ptr [EDI + 0x38],0x0"
    },
    {
      "address": "0059d11d",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "0059d121",
      "instruction": "JZ 0x0059d170"
    },
    {
      "address": "0059d123",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "0059d127",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0059d128",
      "instruction": "LEA EDX,[ESP + 0xc]"
    },
    {
      "address": "0059d12c",
      "instruction": "LEA ESI,[EDI + 0x8]"
    },
    {
      "address": "0059d12f",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0059d130",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0059d132",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "0059d137",
      "instruction": "ADD EDI,0xc"
    },
    {
      "address": "0059d13a",
      "instruction": "CMP dword ptr [EAX],EDI"
    },
    {
      "address": "0059d13c",
      "instruction": "JZ 0x0059d170"
    },
    {
      "address": "0059d13e",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "0059d142",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0059d143",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0059d145",
      "instruction": "CALL 0x0059c740"
    },
    {
      "address": "0059d14a",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "0059d14c",
      "instruction": "MOV EAX,dword ptr [ECX + 0x8]"
    },
    {
      "address": "0059d14f",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0059d151",
      "instruction": "JZ 0x0059d170"
    },
    {
      "address": "0059d153",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0059d156",
      "instruction": "MOV ECX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "0059d15a",
      "instruction": "MOV dword ptr [ECX],EDX"
    },
    {
      "address": "0059d15c",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "0059d15f",
      "instruction": "MOV dword ptr [ECX + 0x4],EDX"
    },
    {
      "address": "0059d162",
      "instruction": "MOV EAX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "0059d165",
      "instruction": "POP EDI"
    },
    {
      "address": "0059d166",
      "instruction": "MOV dword ptr [ECX + 0x8],EAX"
    },
    {
      "address": "0059d169",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "0059d16b",
      "instruction": "POP ESI"
    },
    {
      "address": "0059d16c",
      "instruction": "POP ECX"
    },
    {
      "address": "0059d16d",
      "instruction": "RET 0x8"
    },
    {
      "address": "0059d170",
      "instruction": "POP EDI"
    },
    {
      "address": "0059d171",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "0059d173",
      "instruction": "POP ESI"
    },
    {
      "address": "0059d174",
      "instruction": "POP ECX"
    },
    {
      "address": "0059d175",
      "instruction": "RET 0x8"
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
  "original_bytes": 11502,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX, moved to EDI at 0x0059d117 and held for the whole body\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x8\",\n    \"return_observation\": \"0x0059d169 MOV AL,0x1 on the success path and 0x0059d171 XOR AL,AL on the failure path. Neither writes the upper bytes of EAX, so bits 8..31 are undefined on exit. Every inspected call site consumes the answer with TEST AL,AL followed by JZ, never as a dword.\",\n    \"return_register\": \"AL\",\n    \"return_semantics\": \"a byte-valued predicate: 1 when the position was written, 0 when any of the three guards rejected the query\",\n    \"return_type\": \"bool\",\n    \"return_width_bytes\": 1,\n    \"saved_registers\": [\n      \"ECX\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"proof\": \"0x0059d111 MOV EAX,[ESP+0x8] reads it after the single PUSH ECX, i.e. the first stack slot; 0x0059d11d re-stores it locally and both map ports receive its address\",\n        \"role\": \"creature_id\",\n        \"slot\": \"[ESP_entry+4]\"\n      },\n      {\n        \"proof\": \"0x0059d128 LEA EDX,[ESP+0xc] with ESP already lowered by 8 resolves to ESP_entry+8 and is pushed as the second argument to the find port; 0x0059d156 MOV ECX,[ESP+0x14] reloads the same slot on the copy path\",\n        \"role\": \"out_position\",\n        \"slot\": \"[ESP_entry+8]\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"two exits, 0x0059d16d and 0x0059d175, both RET 0x8 and both preceded by POP EDI / POP ESI / POP ECX\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-GAMEGLOBAL\",\n      \"score\": 3,\n      \"symbol\": \"map_int_whatever_find\",\n      \"va\": \"0x00e5c780\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"map_int_EditorCreatureControllerPtr__get\",\n        \"reconstructed\": false,\n        \"va\": \"0x0059c740\"\n      },\n      {\n        \"name\": \"map_int_whatever_find\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5c780\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00577e10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00582d70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00582fe0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00583900\"\n      },\n      {\n        \"name\": \"Editors::cEditor::Update\",\n        \"reconstructed\": false,\n        \"va\": \"0x0058be50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00628f10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00629590\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062abd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00639350\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00577fce\",\n        \"direction\": \"in\",\n        \"other\": \"0x00577e10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00578b2d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00577e10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00578d79\",\n        \"direction\": \"in\",\n        \"other\": \"0x00577e10\",\n        \"reference_type\": \"direct-call\"\n    
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
  "body_end": "0059d177",
  "body_span_bytes": 104,
  "body_start": "0059d110",
  "callees": [
    "map_int_whatever_find",
    "map_int_EditorCreatureControllerPtr__get"
  ],
  "callers": [
    "FUN_00639350",
    "FUN_00577e10",
    "FUN_00582d70",
    "FUN_00583900",
    "Editors::cEditor::Update",
    "FUN_00628f10",
    "FUN_0062abd0",
    "Editors::cEditor::AddCreature",
    "FUN_00629590"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0059d110",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_0059d110",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x19d110",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0059d110(void)",
  "size_bytes": 104,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0059d110",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 18,
  "xrefs": [
    {
      "from": "005833b4"
    },
    {
      "from": "00582df5"
    },
    {
      "from": "00582eb0"
    },
    {
      "from": "00582f22"
    },
    {
      "from": "00628f51"
    },
    {
      "from": "00628f5e"
    },
    {
      "from": "00629655"
    },
    {
      "from": "00629662"
    },
    {
      "from": "0062ac1d"
    },
    {
      "from": "006394ac"
    },
    {
      "from": "005839ce"
    },
    {
      "from": "0058cb89"
    },
    {
      "from": "0058cdf2"
    },
    {
      "from": "00577fce"
    },
    {
      "from": "00578b2d"
    },
    {
      "from": "00578d79"
    },
    {
      "from": "00578d9c"
    },
    {
      "from": "0063a9ec"
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
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_anim_world_get_creature_position.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_anim_world_get_creature_position.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_anim_world_get_creature_position_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b03/0059d110.json"
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
    "A trace must confirm the +0x0c sentinel identity, i.e. that the receiver's +0x0c really is the map's end node in a live instance. This is derived from the find port's source rather than observed at runtime.",
    "A trace with a concrete receiver is required before the creature id space can be characterised, and therefore before the 18 unchecked call sites can be assumed safe.",
    "No original-process trace exists for this function. Static analysis cannot show whether the mpAnimWorld gate is ever false in a live editor session, or how often the key-absent case occurs."
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "bool"
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
