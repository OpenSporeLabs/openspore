# Evidence 0x004c5200

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `dad0e521f424efcc7eda01009731196f231ca1a1c11f28855ab34a93b67b59f5`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "opaque editor pointer",
  "return_type": "uint8_t",
  "stack_arguments": [
    {
      "entry_offset": "ESP+4",
      "name": "request",
      "observed_fields": [
        "+0x10",
        "+0x58",
        "+0x8c",
        "+0x98",
        "+0xa4"
      ],
      "type": "opaque request pointer",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
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
        "ebp_offset": "EBP+0x8",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
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
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EBP",
      "ESI"
    ],
    "stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "51517dca8f7ed972612e9e6ed7b4bfa0854ccfb472934d85da6197e09c161650",
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
    "indirect_calls": 5,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0249"
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
        "obs-0036",
        "obs-0106",
        "obs-0118",
        "obs-0140",
        "obs-0147",
        "obs-0154",
        "obs-0168",
        "obs-0201",
        "obs-0205"
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
        "obs-0007",
        "obs-0008",
        "obs-0011",
        "obs-0017",
        "obs-0018",
        "obs-0022",
        "obs-0028",
        "obs-0033",
        "obs-0035",
        "obs-0036",
        "obs-0039",
        "obs-0044",
        "obs-0050",
        "obs-0053",
        "obs-0057",
        "obs-0059",
        "obs-0062",
        "obs-0065",
        "obs-0068",
        "obs-0069",
        "obs-0072",
        "obs-0076",
        "obs-0080",
        "obs-0082",
        "obs-0085",
        "obs-0087",
        "obs-0088",
        "obs-0095",
        "obs-0096",
        "obs-0100",
        "obs-0105",
        "obs-0108",
        "obs-0114",
        "obs-0117",
        "obs-0119",
        "obs-0122",
        "obs-0125",
        "obs-0128",
        "obs-0131",
        "obs-0137",
        "obs-0140",
        "obs-0142",
        "obs-0144",
        "obs-0147",
        "obs-0149",
        "obs-0152",
        "obs-0154",
        "obs-0156",
        "obs-0165",
        "obs-0166",
        "obs-0168",
        "obs-0174",
        "obs-0181",
        "obs-0185",
        "obs-0186",
        "obs-0191",
        "obs-0194",
        "obs-0197",
        "obs-0202",
        "obs-0205",
        "obs-0208",
        "obs-0211",
        "obs-0214",
        "obs-0219",
        "obs-0221",
        "obs-0225",
        "obs-0226",
        "obs-0229",
        "obs-0230",
        "obs-0233",
        "obs-0237",
        "obs-0243"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          4,
          8,
          28,
          92,
          100,
          104,
          108,
          132
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0011",
        "obs-0017",
        "obs-0018",
        "obs-0022",
        "obs-0028",
        "obs-0033",
        "obs-0035",
        "obs-0036",
        "obs-0039",
        "obs-0044",
        "obs-0050",
        "obs-0053",
        "obs-0057",
        "obs-0059",
        "obs-0062",
        "obs-0065",
        "obs-0068",
        "obs-0069",
        "obs-0072",
        "obs-0076",
        "obs-0080",
        "obs-0082",
        "obs-0085",
        "obs-0087",
        "obs-0088",
        "obs-0095",
        "obs-0096",
        "obs-0100",
        "obs-0105",
        "obs-0108",
        "obs-0114",
        "obs-0117",
        "obs-0119",
        "obs-0122",
        "obs-0125",
        "obs-0128",
        "obs-0131",
        "obs-0137",
        "obs-0140",
        "obs-0142",
        "obs-0144",
        "obs-0147",
        "obs-0149",
        "obs-0152",
        "obs-0154",
        "obs-0156",
        "obs-0165",
        "obs-0166",
        "obs-0168",
        "obs-0174",
        "obs-0181",
        "obs-0185",
        "obs-0186",
        "obs-0191",
        "obs-0194",
        "obs-0197",
        "obs-0202",
        "obs-0205",
        "obs-0208",
        "obs-0211",
        "obs-0214",
        "obs-0219",
        "obs-0221",
        "obs-0225",
        "obs-0226",
        "obs-0229",
        "obs-0230",
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "app_direct_property_list_get_direct_bool_006a25a0",
    "reconstructed": true,
    "va": "0x006a25a0"
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
    "va": "0x00585d40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00586b00"
  },
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
      "0x004c5200",
      "0x004c5910",
      "0x004c5920",
      "0x004c5200",
      "0x004c5910",
      "0x004c5920",
      "0x004c5920",
      "0x004c5910",
      "0x004c5910",
      "0x004c5920",
      "0x004c5200"
    ],
    "conflict_id": "ceditor_skin_ispainting_alias",
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
  "count": 449,
  "instructions": [
    {
      "address": "004c5200",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004c5201",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004c5203",
      "instruction": "SUB ESP,0x108"
    },
    {
      "address": "004c5209",
      "instruction": "PUSH ESI"
    },
    {
      "address": "004c520a",
      "instruction": "MOV dword ptr [EBP + 0xffffff14],ECX"
    },
    {
      "address": "004c5210",
      "instruction": "MOV EAX,dword ptr [EBP + 0xffffff14]"
    },
    {
      "address": "004c5216",
      "instruction": "MOVZX ECX,byte ptr [EAX + 0x84]"
    },
    {
      "address": "004c521d",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "004c521f",
      "instruction": "JZ 0x004c58a1"
    },
    {
      "address": "004c5225",
      "instruction": "MOV EDX,dword ptr [EBP + 0xffffff14]"
    },
    {
      "address": "004c522b",
      "instruction": "MOV EAX,dword ptr [EDX + 0x5c]"
    },
    {
      "address": "004c522e",
      "instruction": "MOV dword ptr [EBP + -0x48],EAX"
    },
    {
      "address": "004c5231",
      "instruction": "CMP dword ptr [EBP + -0x48],0x0"
    },
    {
      "address": "004c5235",
      "instruction": "JZ 0x004c52bb"
    },
    {
      "address": "004c523b",
      "instruction": "MOV ECX,dword ptr [EBP + 0xffffff14]"
    },
    {
      "address": "004c5241",
      "instruction": "CALL 0x004c58b0"
    },
    {
      "address": "004c5246",
      "instruction": "MOVZX ECX,AL"
    },
    {
      "address": "004c5249",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "004c524b",
      "instruction": "JZ 0x004c52bb"
    },
    {
      "address": "004c524d",
      "instruction": "MOV EDX,dword ptr [EBP + 0xffffff14]"
    },
    {
      "address": "004c5253",
      "instruction": "MOV EAX,dword ptr [EDX + 0x5c]"
    },
    {
      "address": "004c5256",
      "instruction": "MOV dword ptr [EBP + -0x4c],EAX"
    },
    {
      "address": "004c5259",
      "instruction": "MOV ECX,dword ptr [EBP + -0x4c]"
    },
    {
      "address": "004c525c",
      "instruction": "PUSH ECX"
    },
    {
      "address": "004c525d",
      "instruction": "CALL 0x00401080"
    },
    {
      "address": "004c5262",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "004c5264",
      "instruction": "CALL 0x00522a40"
    },
    {
      "address": "004c5269",
      "instruction": "MOV EDX,dword ptr [EBP + 0xffffff14]"
    },
    {
      "address": "004c526f",
      "instruction": "ADD EDX,0x5c"
    },
    {
      "address": "004c5272",
      "instruction": "MOV dword ptr [EBP + -0x54],EDX"
    },
    {
      "address": "004c5275",
      "instruction": "MOV EAX,dword ptr [EBP + -0x54]"
    },
    {
      "address": "004c5278",
      "instruction": "CMP dword ptr [EAX],0x0"
    },
    {
      "address": "004c527b",
      "instruction": "JZ 0x004c52bb"
    },
    {
      "address": "004c527d",
      "instruction": "MOV ECX,dword ptr [EBP + -0x54]"
    },
    {
      "address": "004c5280",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "004c5282",
      "instruction": "MOV dword ptr [EBP + -0x50],EDX"
    },
    {
      "address": "004c5285",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "004c5287",
      "instruction": "JZ 0x004c52a4"
    },
    {
      "address": "004c5289",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "004c528b",
      "instruction": "MOV EDX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "004c528e",
      "instruction": "ADD EDX,0x1"
    },
    {
      "address": "004c5291",
      "instruction": "MOV dword ptr [EBP + 0xffffff10],EDX"
    },
    {
      "address": "004c5297",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "004c5299",
      "instruction": "MOV ECX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "004c529c",
      "instruction": "ADD ECX,0x1"
    },
    {
      "address": "004c529f",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "004c52a1",
      "instruction": "MOV dword ptr [EDX + 0x4],ECX"
    },
    {
      "address": "004c52a4",
      "instruction": "MOV EAX,dword ptr [EBP + -0x54]"
    },
    {
      "address": "004c52a7",
      "instruction": "MOV dword ptr [EAX],0x0"
    },
    {
      "address": "004c52ad",
      "instruction": "CMP dword ptr [EBP + -0x50],0x0"
    },
    {
      "address": "004c52b1",
      "instruction": "JZ 0x004c52bb"
    },
    {
      "address": "004c52b3",
      "instruction": "MOV ECX,dword ptr [EBP + -0x50]"
    },
    {
      "address": "004c52b6",
      "instruction": "CALL 0x00453540"
    },
    {
      "address": "004c52bb",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "004c52bd",
      "instruction": "LEA ECX,[EBP + -0x28]"
    },
    {
      "address": "004c52c0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "004c52c1",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004c52c4",
      "instruction": "CALL 0x004adca0"
    },
    {
      "address": "004c52c9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "004c52ca",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "004c52cc",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "004c52ce",
      "instruction": "MOV EDX,dword ptr [EBP + 0xffffff14]"
    },
    {
      "address": "004c52d4",
      "instruction": "MOV EAX,dword ptr [EDX + 0x6c]"
    },
    {
      "address": "004c52d7",
      "instruction": "PUSH EAX"
    },
    {
      "address": "004c52d8",
      "instruction": "MOV ECX,dword ptr [EBP + 0xffffff14]"
    },
    {
      "address": "004c52de",
      "instruction": "MOV EDX,dword ptr [ECX + 0x64]"
    },
    {
      "address": "004c52e1",
      "instruction": "PUSH EDX"
    },
    {
      "address": "004c52e2",
      "instruction": "CALL 0x004615e0"
    },
    {
      "address": "004c52e7",
      "instruction":
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
  "original_bytes": 21547,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"opaque editor pointer\",\n    \"return_type\": \"uint8_t\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+4\",\n        \"name\": \"request\",\n        \"observed_fields\": [\n          \"+0x10\",\n          \"+0x58\",\n          \"+0x8c\",\n          \"+0x98\",\n          \"+0xa4\"\n        ],\n        \"type\": \"opaque request pointer\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-20-PERSISTENCE-BOUNDARY\",\n      \"score\": 10,\n      \"symbol\": \"ProfilePersistenceBoundary_run_candidate_00b28ec0\",\n      \"va\": \"0x00b28ec0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueEditor\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 5,\n      \"symbol\": \"FUN_005dda30\",\n      \"va\": \"0x005dda30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-PROPERTY-ADAPTER\",\n      \"score\": 5,\n      \"symbol\": \"app_direct_property_list_get_direct_bool_006a25a0\",\n      \"va\": \"0x006a25a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueEditor\",\n  \"cluster\": null,\n  \"confidence\": 0.84,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"app_direct_property_list_get_direct_bool_006a25a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x006a25a0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00585d40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00586b00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00591690\"\n      },\n      {\n        \"name\": \"Editors::cEditor::HandleMessage\",\n        \"reconstructed\": false,\n        \"va\": \"0x00591fa0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00585f4e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00585d40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00586373\",\n        \"direction\": \"in\",\n        \"other\": \"0x00585d40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058715c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00586b00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00587557\",\n        \"direction\": \"in\",\n        \"other\": \"0x00587270\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00591a45\",\n        \"direction\": \"in\",\n        \"other\": \"0x00591690\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00591bea\",\n        \"direction\": \"in\",\n        \"other\": \"0x00591690\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059316e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00591fa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004c57bf\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401010\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004c525d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00401080\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004c53d2\",\n        \"direction\": \"out\",\n        \"other\": \"0x00404f90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004c5670\",\n        \"direction\": \"out\",\n        \"other\": \"0x00432f10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x004c52b6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00453540\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsi
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
  "body_end": "004c58a9",
  "body_span_bytes": 1706,
  "body_start": "004c5200",
  "callees": [
    "FUN_00453540",
    "FUN_00404f90",
    "FUN_004adc80",
    "FUN_006a2660",
    "FUN_00f473a0",
    "Skinner::cPaintSystem::Get",
    "FUN_004adc60",
    "FUN_004615e0",
    "Prop_GetPropValueBool",
    "FUN_00522a40",
    "FUN_00432f10",
    "Editors::IBakeManager::Get",
    "App::Property::GetArrayUInt32",
    "FUN_0051df40",
    "FUN_004c58b0",
    "FUN_004adca0",
    "FUN_0067de30"
  ],
  "callers": [
    "Editors::cEditor::SetActiveMode",
    "FUN_00585d40",
    "FUN_00591690",
    "Editors::cEditor::HandleMessage",
    "Editors::cEditor::SetEditorModel"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "004c5200",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_9",
      "storage": "Stack[-0x9]:1",
      "type": "undefined1"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
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
      "name": "local_2c",
      "storage": "Stack[-0x2c]:1",
      "type": "undefined"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "undefined4"
    },
    {
      "name": "local_34",
      "storage": "Stack[-0x34]:4",
      "type": "undefined4"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    },
    {
      "name": "local_44",
      "storage": "Stack[-0x44]:1",
      "type": "undefined"
    },
    {
      "name": "local_45",
      "storage": "Stack[-0x45]:1",
      "type": "undefined1"
    },
    {
      "name": "local_46",
      "storage": "Stack[-0x46]:1",
      "type": "undefined1"
    },
    {
      "name": "local_4c",
      "storage": "Stack[-0x4c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_50",
      "storage": "Stack[-0x50]:4",
      "type": "undefined4"
    },
    {
      "name": "local_54",
      "storage": "Stack[-0x54]:4",
      "type": "undefined4"
    },
    {
      "name": "local_58",
      "storage": "Stack[-0x58]:4",
      "type": "undefined4"
    },
    {
      "name": "local_5c",
      "storage": "Stack[-0x5c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_60",
      "storage": "Stack[-0x60]:4",
      "type": "undefined4"
    },
    {
      "name": "local_64",
      "storage": "Stack[-0x64]:4",
      "type": "undefined4"
    },
    {
      "name": "local_68",
      "storage": "Stack[-0x68]:4",
      "type": "undefined4"
    },
    {
      "name": "local_6c",
      "storage": "Stack[-0x6c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_70",
      "storage": "Stack[-0x70]:4",
      "type": "undefined4"
    },
    {
      "name": "local_74",
      "storage": "Stack[-0x74]:4",
      "type": "undefined4"
    },
    {
      "name": "local_78",
      "storage": "Stack[-0x78]:4",
      "type": "undefined4"
    },
    {
      "name": "local_7c",
      "storage": "Stack[-0x7c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_80",
      "storage": "Stack[-0x80]:4",
      "type": "undefined4"
    },
    {
      "name": "local_84",
      "storage": "Stack[-0x84]:4",
      "type": "undefined4"
    },
    {
      "name": "local_88",
      "storage": "Stack[-0x88]:4",
      "type": "undefined4"
    },
    {
      "name": "local_8c",
      "storage": "Stack[-0x8c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_90",
      "storage": "Stack[-0x90]:4",
      "type": "undefined4"
    },
    {
      "name": "local_94",
      "storage": "Stack[-0x94]:4",
      "type": "undefined4"
    },
    {
      "name": "local_98",
      "storage": "Stack[-0x98]:4",
      "type": "undefined4"
    },
    {
      "name": "local_9c",
      "storage": "Stack[-0x9c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_a0",
      "storage": "Stack[-0xa0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_a4",
      "storage": "Stack[-0xa4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_a8",
      "storage": "Stack[-0xa8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_ac",
      "storage": "Stack[-0xac]:4",
      "type": "undefined4"
    },
    {
      "name": "local_b0",
      "storage": "Stack[-0xb0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_b4",
      "storage": "Stack[-0xb4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_b8",
      "storage": "Stack[-0xb8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_bc",
      "storage": "Stack[-0xbc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c0",
      "storage": "Stack[-0xc0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c4",
      "storage": "Stack[-0xc4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c8",
      "storage": "Stack[-0xc8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_cc",
      "storage": "Stack[-0xcc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_d0",
      "storage": "Stack[-0xd0]:
[TRUNCATED]
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
  "file": "src/reconstruction/pkg20_persistence_boundary/paint_job_004c5200.cpp",
  "files": [
    "reconstruction/staging/pkg20-persistence-boundary/paint_job_004c5200.cpp",
    "reconstruction/staging/pkg20-persistence-boundary/paint_job_004c5200.hpp",
    "src/reconstruction/pkg20_persistence_boundary/paint_job_004c5200.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave4/handoff.json",
    "reconstruction/integrated/batch-2026-09-25/editor-ui/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg20-persistence-boundary/004c5200.json"
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
    "gate-paint-bake-submission"
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
  "original_bytes": 9825,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"BOUNDED_SEMANTIC\",\n  \"confidence\": {\n    \"events\": \"ANALYTICAL_ONLY\",\n    \"identity\": \"SUPPORTED\",\n    \"mechanics\": \"CONFIRMED\",\n    \"overall\": \"high_for_static_paint_mechanics_medium_for_argument_and_job_types\",\n    \"ownership\": \"SUPPORTED_WITH_CAVEAT\",\n    \"persistence\": \"CONFIRMED_AS_DERIVED_NON_PERSISTENT\",\n    \"runtime\": \"UNAVAILABLE\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 22,\n  \"evidence\": [\n    {\n      \"claim\": \"feature gate, old-job release, 0x84-byte allocation, three-slot population, property fallback, type flags, IBakeManager submission, and boolean-like return\",\n      \"class\": \"direct_body\",\n      \"source\": \"ghidra://SporeApp.exe@0x004c5200\"\n    },\n    {\n      \"claim\": \"136-byte receiver with editor/model/world references, retained job at +0x5c, material/texture fields, and gate at +0x84\",\n      \"class\": \"structure_layout\",\n      \"source\": \"ghidra_get_struct_layout(cEditorSkin)\"\n    },\n    {\n      \"claim\": \"five direct editor callers: cEditor::HandleMessage, cEditor::SetActiveMode, cEditor::SetEditorModel, FUN_00585d40, and FUN_00591690\",\n      \"class\": \"direct_callers\",\n      \"source\": \"ghidra_get_function_callers(0x004c5200)\"\n    },\n    {\n      \"claim\": \"checks the retained job's +0x6b/+0x6c state before allowing the old job to be released\",\n      \"class\": \"sibling_helper\",\n      \"source\": \"ghidra://SporeApp.exe@0x004c58b0\"\n    },\n    {\n      \"claim\": \"nearby rigblock-to-derived-mesh production is a sibling operation, not the same state contract\",\n      \"class\": \"derived_asset_sibling\",\n      \"source\": \"ghidra://SporeApp.exe@0x004c73f0; SDK alias 0x004c7460\"\n    },\n    {\n      \"claim\": \"containing PaintSkin alias, 0x84 job, three colors/effect IDs/seeds, IBakeManager slot, and derived runtime classification\",\n      \"class\": \"committed_artifact\",\n      \"source\": \"knowledgegraph/research/state-machines/editor-workflows.json:3-49; knowledgegraph/research/data-model/07-editor-data.json:510-543\"\n    }\n  ],\n  \"family\": \"editor-skin-paint-pipeline\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": [\n      {\n        \"name\": \"App::Property::GetArrayUInt32\",\n        \"va\": \"0x006a0840\"\n      },\n      {\n        \"name\": \"Editors::IBakeManager::Get\",\n        \"va\": \"0x00401010\"\n      },\n      {\n        \"name\": \"FUN_00404f90\",\n        \"va\": \"0x00404f90\"\n      },\n      {\n        \"name\": \"FUN_00432f10\",\n        \"va\": \"0x00432f10\"\n      },\n      {\n        \"name\": \"FUN_00453540\",\n        \"va\": \"0x00453540\"\n      },\n      {\n        \"name\": \"FUN_004615e0\",\n        \"va\": \"0x004615e0\"\n      },\n      {\n        \"name\": \"FUN_004adc60\",\n        \"va\": \"0x004adc60\"\n      },\n      {\n        \"name\": \"FUN_004adc80\",\n        \"va\": \"0x004adc80\"\n      },\n      {\n        \"name\": \"FUN_004adca0\",\n        \"va\": \"0x004adca0\"\n      },\n      {\n        \"name\": \"FUN_004c58b0\",\n        \"va\": \"0x004c58b0\"\n      },\n      {\n        \"name\": \"FUN_0051df40\",\n        \"va\": \"0x0051df40\"\n      },\n      {\n        \"name\": \"FUN_00522a40\",\n        \"va\": \"0x00522a40\"\n      }\n    ],\n    \"direct_callers\": [\n      {\n        \"callsites\": [\n          \"0x0059316e\"\n        ],\n        \"name\": \"Editors::cEditor::HandleMessage\",\n        \"va\": \"0x00591fa0\"\n      },\n      {\n        \"callsites\": [\n          \"0x00591a45\",\n          \"0x00591bea\"\n        ],\n        \"name\": \"FUN_00591690\",\n        \"va\": \"0x00591690\"\n      },\n      {\n        \"callsites\": [\n          \"0x00585f4e\",\n          \"0x00586373\"\n        ],\n        \"name\": \"FUN_00585d40\",\n        \"va\": \"0x00585d40\"\n      },\n      {\n        \"callsites\": [\n          \"0x00587557\"\n        ],\n        \"name\": \"Editors::cEditor::SetActiveMode\",\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"callsites\": [\n          \"0x0058715c\"\n        ],\n        \"name\": \"Editors::cEditor::SetEditorModel\",\n        \"va\": \"0x00586b00\"\n      }\n    ],\n    \"globals\": [],\n    \"structures\": {\n      \"name\": \"cEditorSkin\",\n      \"selected_fields\": [\n        {\n          \"keys\": [\n            \"name\",\n            \"offset\",\n            \"role\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"offset\",\n            \"role\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"offset\",\n            \"role\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"offset\",\n            \"role\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"offset\",\n            \"role\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"offset\",\n            \"role\"\n          ]\n        },\n        {\n          \"keys\": [\n            \"name\",\n            \"offset\",\n            \"role\"\n          ]\n        }\n      ],\n      \"size_bytes\": 136\n    },\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": [\n        \"this+0x84 equal to zero returns false without submission\",\n        \"IBakeManager slot +0x64 returning false causes job release, property-list release, and false return\",\n        \"successful submission retains the job and returns true\",\n        \"the body does not expose a typed exception, queue position, or asynchronous completion contract\"\n      ],\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [],\n      \"ordering\": [\n        \"check cEditorSkin+0x84\",\n        \"conditio
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
  "OpaqueEditor",
  "OpaquePaintJob",
  "PaintJobServices",
  "PaintRequest",
  "opaque editor pointer",
  "opaque request pointer",
  "uint8_t"
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
      "0x004c5200",
      "0x004c5910",
      "0x004c5920",
      "0x004c5200",
      "0x004c5910",
      "0x004c5920",
      "0x004c5920",
      "0x004c5910",
      "0x004c5910",
      "0x004c5920",
      "0x004c5200"
    ],
    "conflict_id": "ceditor_skin_ispainting_alias",
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
  }
]
```
