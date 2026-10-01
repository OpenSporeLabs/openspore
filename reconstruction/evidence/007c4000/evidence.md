# Evidence 0x007c4000

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `92f66c9ec29a298cdfa0327d51551ac0e355416f9050eee9dcdfc18a2c0ef0fc`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX;void_possible",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "045ad9bb66edabff49995068231a41498433ffeb6c7fe82ce50482bfc5a7d678",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
        "obs-0003"
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
        "obs-0001"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          368
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0003"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0002",
        "obs-0003"
      ],
      "claim": "the function can reach a caller by transferring out of the listing, so the path that actually returns was never observed",
      "confidence": "UNKNOWN",
      "id": "T2",
      "value": {
        "form": "epilogue_then_jmp"
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "EAX is never written and no call can clobber it, so a void return is possible; this is a flag, never a type",
      "confidence": "APPROXIMATION",
      "id": "RT3",
      "value": {
        "void_possible": true
      }
    }
  ],
  "observations": [
    {
      "at": "0x007c4000",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "CMP dword ptr [ECX + 0x170],0x0",
      "reg": "ECX"
    },
    {
      "at": "0x007c4009",
      "id": "obs-0002",
      "index": 2,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x007c3ba0",
      "target": "0x007c3ba0"
    },
    {
      "at": "0x007c400e",
      "form": "RET",
      "id": "obs-0003",
      "imm": null,
      "index": 3,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 4,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 368,
    "offsets": [
      368
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": true
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": "epilogue_then_jmp",
    "present": true,
    "target": "0x007c3ba0"
  },
  "target": {
    "address_available": true,
    "ima
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX;void_possible",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "045ad9bb66edabff49995068231a41498433ffeb6c7fe82ce50482bfc5a7d678",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
        "obs-0003"
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
        "obs-0001"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          368
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0003"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0002",
        "obs-0003"
      ],
      "claim": "the function can reach a caller by transferring out of the listing, so the path that actually returns was never observed",
      "confidence": "UNKNOWN",
      "id": "T2",
      "value": {
        "form": "epilogue_then_jmp"
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "EAX is never written and no call can clobber it, so a void return is possible; this is a flag, never a type",
      "confidence": "APPROXIMATION",
      "id": "RT3",
      "value": {
        "void_possible": true
      }
    }
  ],
  "observations": [
    {
      "at": "0x007c4000",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "CMP dword ptr [ECX + 0x170],0x0",
      "reg": "ECX"
    },
    {
      "at": "0x007c4009",
      "id": "obs-0002",
      "index": 2,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x007c3ba0",
      "target": "0x007c3ba0"
    },
    {
      "at": "0x007c400e",
      "form": "RET",
      "id": "obs-0003",
      "imm": null,
      "index": 3,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 4,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 368,
    "offsets": [
      368
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": true
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": "epilogue_then_jmp",
    "present": true,
    "target": "0x007c3ba0"
  },
  "target": {
    "address_available": true,
    "ima
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_007c3ba0",
    "reconstructed": false,
    "va": "0x007c3ba0"
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
    "va": "0x00430e70"
  },
  {
    "name": "Editors::cEditor::Dispose",
    "reconstructed": false,
    "va": "0x00576c50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f0890"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f5260"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f9cf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076b000"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076b5d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076b840"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00777060"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0077f210"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b29a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b77a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b9620"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b9e80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007bd540"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007bd640"
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
  "count": 4,
  "instructions": [
    {
      "address": "007c4000",
      "instruction": "CMP dword ptr [ECX + 0x170],0x0"
    },
    {
      "address": "007c4007",
      "instruction": "JZ 0x007c400e"
    },
    {
      "address": "007c4009",
      "instruction": "JMP 0x007c3ba0"
    },
    {
      "address": "007c400e",
      "instruction": "RET"
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
  "original_bytes": 10946,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_007c3ba0\",\n        \"reconstructed\": false,\n        \"va\": \"0x007c3ba0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00430e70\"\n      },\n      {\n        \"name\": \"Editors::cEditor::Dispose\",\n        \"reconstructed\": false,\n        \"va\": \"0x00576c50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f0890\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f5260\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f9cf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076b000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076b5d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076b840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00777060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0077f210\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b29a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b77a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b9620\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b9e80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bd540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bd640\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bd6b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bd750\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bdd70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007be430\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bea00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007e7380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0080ead0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0080ec40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0080eca0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00adf690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b35860\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f6b840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f99ff0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f9f1a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00feb0f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010347a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0121390c\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0121395c\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01214ccb\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01216a9b\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x013c7d80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x013c9bf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x013c9c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x013c9c10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x013c9c20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x013ca920\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00432802\",\n        \"direction\": \"in\",\n        \"other\": \"0x00430e70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576f81\",\n        \"direction\": \"in\",\n        \"other\": \"0x00576c50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576fb0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00576c50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00576fdf\",\n        \"direction\": \"in\",\n        \"other\": \"0x00576c50\",\n        \"reference_type\": 
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
  "body_end": "007c400e",
  "body_span_bytes": 15,
  "body_start": "007c4000",
  "callees": [
    "FUN_007c3ba0"
  ],
  "callers": [
    "FUN_007b9620",
    "FUN_007bd6b0",
    "FUN_00777060",
    "Unwind@0121390c",
    "Unwind@01214ccb",
    "FUN_0076b5d0",
    "FUN_007bd640",
    "FUN_006f9cf0",
    "FUN_0080eca0",
    "FUN_0076b000",
    "FUN_007b77a0",
    "FUN_007e7380",
    "FUN_00b35860",
    "FUN_007bd540",
    "FUN_010347a0",
    "FUN_00feb0f0",
    "Unwind@0121395c",
    "FUN_013c9c10",
    "FUN_00430e70",
    "FUN_007bea00",
    "FUN_007b9e80",
    "FUN_013c9c20",
    "FUN_006f5260",
    "FUN_007be430",
    "FUN_013c9c00",
    "FUN_00f6b840",
    "FUN_00f9f1a0",
    "FUN_00f99ff0",
    "FUN_013c7d80",
    "FUN_0076b840",
    "FUN_007b29a0",
    "FUN_007bd750",
    "FUN_007bdd70",
    "FUN_0080ec40",
    "Unwind@01216a9b",
    "FUN_013ca920",
    "FUN_006f0890",
    "FUN_00adf690",
    "FUN_013c9bf0",
    "FUN_0080ead0",
    "Editors::cEditor::Dispose",
    "FUN_0077f210"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "007c4000",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_007c4000",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3c4000",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_007c4000(void)",
  "size_bytes": 15,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007c4000",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 77,
  "xrefs": [
    {
      "from": "01213915"
    },
    {
      "from": "01213965"
    },
    {
      "from": "01214cd1"
    },
    {
      "from": "01216aa1"
    },
    {
      "from": "00432802"
    },
    {
      "from": "0076b609"
    },
    {
      "from": "006f0b0e"
    },
    {
      "from": "006f0b37"
    },
    {
      "from": "006f0b60"
    },
    {
      "from": "0076b141"
    },
    {
      "from": "0076b16a"
    },
    {
      "from": "0076b19b"
    },
    {
      "from": "006f5470"
    },
    {
      "from": "006f9d88"
    },
    {
      "from": "006f9db1"
    },
    {
      "from": "006f9dda"
    },
    {
      "from": "006f9e04"
    },
    {
      "from": "0076b859"
    },
    {
      "from": "007770e1"
    },
    {
      "from": "0077f27c"
    },
    {
      "from": "007b29f1"
    },
    {
      "from": "007b9642"
    },
    {
      "from": "007b9eaa"
    },
    {
      "from": "007bd5b1"
    },
    {
      "from": "007bd691"
    },
    {
      "from": "007bd70a"
    },
    {
      "from": "007bd730"
    },
    {
      "from": "007bdc79"
    },
    {
      "from": "007bddc6"
    },
    {
      "from": "007be8b1"
    },
    {
      "from": "007bec8a"
    },
    {
      "from": "007e75e1"
    },
    {
      "from": "0080eb0c"
    },
    {
      "from": "0080ec5d"
    },
    {
      "from": "0080ed0b"
    },
    {
      "from": "00adf756"
    },
    {
      "from": "00b35a9e"
    },
    {
      "from": "00f9a00f"
    },
    {
      "from": "00f6b935"
    },
    {
      "from": "00feb108"
    },
    {
      "from": "010347a9"
    },
    {
      "from": "010347b4"
    },
    {
      "from": "010347bc"
    },
    {
      "from": "00f9f1ec"
    },
    {
      "from": "00f9f1fb"
    },
    {
      "from": "0077f072"
    },
    {
      "from": "0077f281"
    },
    {
      "from": "01213943"
    },
    {
      "from": "012138f3"
    },
    {
      "from": "00576f81"
    },
    {
      "from": "00576fb0"
    },
    {
      "from": "00576fdf"
    },
    {
      "from": "0057700e"
    },
    {
      "from": "0057703d"
    },
    {
      "from": "0076db27"
    },
    {
      "from": "007b996e"
    },
    {
      "from": "007b9ae2"
    },
    {
      "from": "007bdfe2"
    },
    {
      "from": "007be008"
    },
    {
      "from": "007be034"
    },
    {
      "from": "007be063"
    },
    {
      "from": "007be092"
    },
    {
      "from": "007be0c1"
    },
    {
      "from": "007be12b"
    },
    {
      "from": "007be3e2"
    },
    {
      "from": "007b77c7"
    },
    {
      "from": "007e95d7"
    },
    {
      "from": "00e3644f"
    },
    {
      "from": "00fa48f4"
    },
    {
      "from": "013ca925"
    },
    {
      "from": "013ca92f"
    },
    {
      "from": "013ca939"
    },
    {
      "from": "013c9c15"
    },
    {
      "from": "013c9c05"
    },
    {
      "from": "013c9bf5"
    },
    {
      "from": "013c7d85"
    },
    {
      "from": "013c9c25"
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
  "metadata": []
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
  "status": "candidate"
}
```

## types

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
