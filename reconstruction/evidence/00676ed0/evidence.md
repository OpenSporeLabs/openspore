# Evidence 0x00676ed0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `771accbdc795a762add5ddc3490ae532197932d2238c4a333954a9130283fb9a`

## abi

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
      "entry_ESP+0x8"
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
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "72f169bdc808132a543d308032bcba29cb2e30989092231c8ca710cce10b9d7b",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0020"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0009",
        "obs-0010",
        "obs-0013"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0010",
        "obs-0011",
        "obs-0012"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          36
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0020"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0020"
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
        "obs-0020"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020"
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
      "at": "0x00676ed0",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00676ed1",
      "count": 2,
      "first_use": 1,
      "first_write_index": 10,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00676ed1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00676ed9",
      "count": 3,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00676eda",
      "count": 4,
      "first_use": 5,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00676eda",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0006",
      "index": 5,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00676eda",
      "d
[TRUNCATED]
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
      "entry_ESP+0x8"
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
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "72f169bdc808132a543d308032bcba29cb2e30989092231c8ca710cce10b9d7b",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0020"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0009",
        "obs-0010",
        "obs-0013"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0010",
        "obs-0011",
        "obs-0012"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          36
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0020"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0020"
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
        "obs-0020"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020"
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
      "at": "0x00676ed0",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00676ed1",
      "count": 2,
      "first_use": 1,
      "first_write_index": 10,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00676ed1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00676ed9",
      "count": 3,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00676eda",
      "count": 4,
      "first_use": 5,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00676eda",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0006",
      "index": 5,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00676eda",
      "d
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "achievement_completion_boundary_00676710",
    "reconstructed": true,
    "va": "0x00676710"
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
    "va": "0x005a9200"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c07480"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cd4280"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cfbc10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d43e30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e82cf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fda750"
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
  "count": 29,
  "instructions": [
    {
      "address": "00676ed0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00676ed1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00676ed3",
      "instruction": "CMP byte ptr [ESI + 0x24],0x0"
    },
    {
      "address": "00676ed7",
      "instruction": "JNZ 0x00676f17"
    },
    {
      "address": "00676ed9",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00676eda",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00676ede",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00676edf",
      "instruction": "CALL 0x00676660"
    },
    {
      "address": "00676ee4",
      "instruction": "CMP byte ptr [ESP + 0x14],0x0"
    },
    {
      "address": "00676ee9",
      "instruction": "JZ 0x00676ef4"
    },
    {
      "address": "00676eeb",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00676eef",
      "instruction": "OR dword ptr [EAX + 0x4],ECX"
    },
    {
      "address": "00676ef2",
      "instruction": "JMP 0x00676efd"
    },
    {
      "address": "00676ef4",
      "instruction": "MOV EDX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00676ef8",
      "instruction": "NOT EDX"
    },
    {
      "address": "00676efa",
      "instruction": "AND dword ptr [EAX + 0x4],EDX"
    },
    {
      "address": "00676efd",
      "instruction": "TEST byte ptr [EAX],0x1"
    },
    {
      "address": "00676f00",
      "instruction": "JZ 0x00676f16"
    },
    {
      "address": "00676f02",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00676f03",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00676f05",
      "instruction": "CALL 0x006751c0"
    },
    {
      "address": "00676f0a",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00676f0c",
      "instruction": "JZ 0x00676f16"
    },
    {
      "address": "00676f0e",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00676f0f",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00676f11",
      "instruction": "CALL 0x00676710"
    },
    {
      "address": "00676f16",
      "instruction": "POP EDI"
    },
    {
      "address": "00676f17",
      "instruction": "POP ESI"
    },
    {
      "address": "00676f18",
      "instruction": "RET 0xc"
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
  "original_bytes": 8051,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:AchievementManagerWire,std::uint8_t gate\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\",\n      \"score\": 28,\n      \"symbol\": \"achievement_completion_boundary_00676710\",\n      \"va\": \"0x00676710\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:AchievementManagerWire\"\n      ],\n      \"package\": \"PKG-11-A2-PROGRESSION-ALTERNATIVE\",\n      \"score\": 14,\n      \"symbol\": \"achievement_progress_update_00676e90\",\n      \"va\": \"0x00676e90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\",\n      \"score\": 8,\n      \"symbol\": \"mission_manager_record_init_00fec3c0\",\n      \"va\": \"0x00fec3c0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"No original-process flag transition trace was run.\",\n    \"Record creation inside 0x00676660 and the comparator body at 0x006751c0 remain owned by other packages.\",\n    \"The meaning of the individual bits of the mask word is not derivable from this function; only the set and clear mechanics are.\",\n    \"The two call sites with no enclosing function (0x00c3d440, 0x00cfd5d2) are unreconciled.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"AchievementManagerWire\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"achievement_completion_boundary_00676710\",\n        \"reconstructed\": true,\n        \"va\": \"0x00676710\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005a9200\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c07480\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd4280\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cfbc10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d43e30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e82cf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fda750\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005a9452\",\n        \"direction\": \"in\",\n        \"other\": \"0x005a9200\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c07bd6\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c07480\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00cd43a6\",\n        \"direction\": \"in\",\n        \"other\": \"0x00cd4280\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00cfc029\",\n        \"direction\": \"in\",\n        \"other\": \"0x00cfbc10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d440f5\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d43e30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d453d0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d43e30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e82d06\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e82cf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fda92c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00fda750\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00676f05\",\n        \"direction\": \"out\",\n        \"other\": \"0x006751c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00676edf\",\n        \"direction\": \"out\",\n        \"other\": \"0x00676660\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00676f11\",\n        \"direction\": \"out\",\n        \"other\": \"0x00676710\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 7,\n    \"fan_out\": 1,\n    \"manifest_callees\": [\n      \"0x00676660\",\n      \"0x006751c0\",\n      \"0x00676710\"\n    ],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00676710\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0177\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"achievement_progress_flag_transition_00676ed0\",\n  \"normalized_symbol\": \"achievement_progress_flag_transition_00676ed0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\"\n    ],\n    \"manifest\": {\n      \"record\": {\n        \"boundary\": \"No existing body record, staging source, integrated source, or test claims 0x00676ed0. The three callees 0x00676660, 0x006751c0 and 0x00676710 stay opaque ports here: 0x0
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
  "body_end": "00676f1a",
  "body_span_bytes": 75,
  "body_start": "00676ed0",
  "callees": [
    "FUN_00676660",
    "FUN_00676710",
    "FUN_006751c0"
  ],
  "callers": [
    "FUN_00cfbc10",
    "FUN_00cd4280",
    "FUN_00c07480",
    "FUN_00e82cf0",
    "FUN_00d43e30",
    "FUN_005a9200",
    "FUN_00fda750"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00676ed0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00676ed0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x276ed0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00676ed0(void)",
  "size_bytes": 75,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00676ed0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "005a9452"
    },
    {
      "from": "00c07bd6"
    },
    {
      "from": "00cd43a6"
    },
    {
      "from": "00e82d06"
    },
    {
      "from": "00fda92c"
    },
    {
      "from": "00cfc029"
    },
    {
      "from": "00d440f5"
    },
    {
      "from": "00d453d0"
    },
    {
      "from": "00c3d440"
    },
    {
      "from": "00cfd5d2"
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
  "file": "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.cpp",
    "reconstruction/staging/pkg11-a3-achievement-mission-wave2/achievement_mission_wave2.hpp",
    "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.cpp",
    "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2.hpp",
    "src/reconstruction/pkg11_a3_achievement_mission_wave2/achievement_mission_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-a3-achievement-mission-wave2/00676ed0.json"
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
    "gate-achievement-progress-flags-00676ed0",
    "runtime validation not run"
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
  "AchievementManagerWire",
  "std::uint32_t",
  "std::uint32_t flags",
  "std::uint32_t progress flags",
  "std::uint8_t",
  "std::uint8_t gate"
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
