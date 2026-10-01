# Evidence 0x007c3f70

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `65e3cf8d92f8f547df174e97ac20c851df2fff53b475b5699f46ef77d5419386`

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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "63fd321d08aa03c16d29c06c7374111c435af7b1c705d704c9782cbd1cdca7cf",
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
        "obs-0007"
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
        "obs-0002",
        "obs-0003",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          320,
          324,
          328,
          332,
          336,
          340,
          344,
          348,
          352,
          356,
          360,
          364,
          368
        ],
        "register": "ECX",
        "written_through": 13
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0006",
        "obs-0007"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0007"
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
        "obs-0007"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x007c3f70",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [0x01635db8]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x007c3f78",
      "count": 6,
      "first_use": 1,
      "first_write_index": 10,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x007c3f78",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ECX",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x007c3f7a",
      "count": 13,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [EAX + 0x140],XMM0",
      "reg": "EAX"
    },
    {
      "at": "0x007c3f7a",
      "count": 8,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [EAX + 0x140],XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x007c3fba",
      "definite": true,
      "id": "obs-0006",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "XOR ECX,ECX",
      "reg": "ECX",
      "write_kind": "zero"
    },
    {
      "at": "0x007c3ffb",
      "form": "RET",
      "id": "obs-0007",
      "imm": null,
      "index": 20,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 21,
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
    "confidence": "SUPPORTED",
    "distinct_offsets": 13,
    "max_offset": 368,
    "offsets": [
      320,
      324,
      328,
      332,
      336,
      340,
      344,
      348,
      352,
      356,
      360,
      364,
      368
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-ALIAS",
    "written_through": 13
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "APPROXIMATION",
    "register": "XMM0",
    "register_class": "float_or_x87",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_conf
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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "63fd321d08aa03c16d29c06c7374111c435af7b1c705d704c9782cbd1cdca7cf",
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
        "obs-0007"
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
        "obs-0002",
        "obs-0003",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          320,
          324,
          328,
          332,
          336,
          340,
          344,
          348,
          352,
          356,
          360,
          364,
          368
        ],
        "register": "ECX",
        "written_through": 13
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0006",
        "obs-0007"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0007"
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
        "obs-0007"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x007c3f70",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [0x01635db8]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x007c3f78",
      "count": 6,
      "first_use": 1,
      "first_write_index": 10,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x007c3f78",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,ECX",
      "reg": "EAX",
      "write_kind": "reg"
    },
    {
      "at": "0x007c3f7a",
      "count": 13,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [EAX + 0x140],XMM0",
      "reg": "EAX"
    },
    {
      "at": "0x007c3f7a",
      "count": 8,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [EAX + 0x140],XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x007c3fba",
      "definite": true,
      "id": "obs-0006",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "XOR ECX,ECX",
      "reg": "ECX",
      "write_kind": "zero"
    },
    {
      "at": "0x007c3ffb",
      "form": "RET",
      "id": "obs-0007",
      "imm": null,
      "index": 20,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 21,
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
    "confidence": "SUPPORTED",
    "distinct_offsets": 13,
    "max_offset": 368,
    "offsets": [
      320,
      324,
      328,
      332,
      336,
      340,
      344,
      348,
      352,
      356,
      360,
      364,
      368
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-ALIAS",
    "written_through": 13
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "APPROXIMATION",
    "register": "XMM0",
    "register_class": "float_or_x87",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_conf
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
    "va": "0x00430e70"
  },
  {
    "name": "Editors::cEditor::Initialize",
    "reconstructed": false,
    "va": "0x00584300"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f5260"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006f69c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076acd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076b460"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076b720"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0076d8e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00776f40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0077f040"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b2ab0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b2ca0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b2f40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b31f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b3760"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x007b91f0"
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
"\nvoid __fastcall FUN_007c3f70(int param_1)\n\n{\n  *(undefined4 *)(param_1 + 0x140) = DAT_01635db8;\n  *(undefined4 *)(param_1 + 0x144) = DAT_01635dbc;\n  *(undefined4 *)(param_1 + 0x148) = DAT_01635dc0;\n  *(undefined4 *)(param_1 + 0x14c) = DAT_01635dc4;\n  *(undefined4 *)(param_1 + 0x150) = 0;\n  *(undefined4 *)(param_1 + 0x154) = 0;\n  *(undefined4 *)(param_1 + 0x158) = 0;\n  *(undefined4 *)(param_1 + 0x15c) = 0x461c4000;\n  *(undefined4 *)(param_1 + 0x160) = 0x461c4000;\n  *(undefined4 *)(param_1 + 0x164) = 0x461c4000;\n  *(undefined4 *)(param_1 + 0x168) = 0x461c4000;\n  *(undefined1 *)(param_1 + 0x16c) = 1;\n  *(undefined4 *)(param_1 + 0x170) = 0;\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 21,
  "instructions": [
    {
      "address": "007c3f70",
      "instruction": "MOVSS XMM0,dword ptr [0x01635db8]"
    },
    {
      "address": "007c3f78",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "007c3f7a",
      "instruction": "MOVSS dword ptr [EAX + 0x140],XMM0"
    },
    {
      "address": "007c3f82",
      "instruction": "MOVSS XMM0,dword ptr [0x01635dbc]"
    },
    {
      "address": "007c3f8a",
      "instruction": "MOVSS dword ptr [EAX + 0x144],XMM0"
    },
    {
      "address": "007c3f92",
      "instruction": "MOVSS XMM0,dword ptr [0x01635dc0]"
    },
    {
      "address": "007c3f9a",
      "instruction": "MOVSS dword ptr [EAX + 0x148],XMM0"
    },
    {
      "address": "007c3fa2",
      "instruction": "MOVSS XMM0,dword ptr [0x01635dc4]"
    },
    {
      "address": "007c3faa",
      "instruction": "MOVSS dword ptr [EAX + 0x14c],XMM0"
    },
    {
      "address": "007c3fb2",
      "instruction": "MOVSS XMM0,dword ptr [0x013f0620]"
    },
    {
      "address": "007c3fba",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "007c3fbc",
      "instruction": "MOV dword ptr [EAX + 0x150],ECX"
    },
    {
      "address": "007c3fc2",
      "instruction": "MOV dword ptr [EAX + 0x154],ECX"
    },
    {
      "address": "007c3fc8",
      "instruction": "MOV dword ptr [EAX + 0x158],ECX"
    },
    {
      "address": "007c3fce",
      "instruction": "MOVSS dword ptr [EAX + 0x15c],XMM0"
    },
    {
      "address": "007c3fd6",
      "instruction": "MOVSS dword ptr [EAX + 0x160],XMM0"
    },
    {
      "address": "007c3fde",
      "instruction": "MOVSS dword ptr [EAX + 0x164],XMM0"
    },
    {
      "address": "007c3fe6",
      "instruction": "MOVSS dword ptr [EAX + 0x168],XMM0"
    },
    {
      "address": "007c3fee",
      "instruction": "MOV byte ptr [EAX + 0x16c],0x1"
    },
    {
      "address": "007c3ff5",
      "instruction": "MOV dword ptr [EAX + 0x170],ECX"
    },
    {
      "address": "007c3ffb",
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
  "original_bytes": 9975,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w1-00f9b7f0\",\n      \"score\": 6,\n      \"symbol\": \"re_00f9b7f0\",\n      \"va\": \"0x00f9b7f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00430e70\"\n      },\n      {\n        \"name\": \"Editors::cEditor::Initialize\",\n        \"reconstructed\": false,\n        \"va\": \"0x00584300\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f5260\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006f69c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076acd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076b460\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076b720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0076d8e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00776f40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0077f040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b2ab0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b2ca0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b2f40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b31f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b3760\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b91f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b9420\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b9510\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007b9b00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007be430\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007bea00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x007e7380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0080e850\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0080ebc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ade8b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b35300\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b3ac20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f67e70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f99f20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f9f100\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00feb060\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0043126a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00430e70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058507e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00584300\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005850b1\",\n        \"direction\": \"in\",\n        \"other\": \"0x00584300\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005850e4\",\n        \"direction\": \"in\",\n        \"other\": \"0x00584300\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00585117\",\n        \"direction\": \"in\",\n        \"other\": \"0x00584300\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058514a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00584300\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006f52a9\",\n        \"direction\": \"in\",\n        \"other\": \"0x006f5260\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006f6af0\",\n        \"direction\": \"in\",\n        \"other\": \"0x006f69c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006f6b36\",\n        \"direction\": \"in\",\n        \"other\": \"0x006f69c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006f6b79\",\n        \"direction\": \"in\",\n        \"other\": \"0x006f69c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006f6bbc\",\n        \"direction\": \"in\",
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
  "body_end": "007c3ffb",
  "body_span_bytes": 140,
  "body_start": "007c3f70",
  "callees": [],
  "callers": [
    "INITDISC_0137F8F0",
    "INITDISC_013916F0",
    "FUN_0076b720",
    "FUN_006f69c0",
    "FUN_0080e850",
    "INITDISC_013A58D0",
    "FUN_007b9510",
    "FUN_007b2ab0",
    "FUN_007e7380",
    "FUN_007b9420",
    "Editors::cEditor::Initialize",
    "FUN_0080ebc0",
    "FUN_00f67e70",
    "FUN_007bea00",
    "FUN_00b35300",
    "FUN_0077f040",
    "FUN_00f99f20",
    "INITDISC_013916D0",
    "INITDISC_01391780",
    "FUN_0076b460",
    "FUN_007be430",
    "FUN_007b31f0",
    "FUN_00f9f100",
    "FUN_007b91f0",
    "FUN_00b3ac20",
    "FUN_00776f40",
    "FUN_007b9b00",
    "INITDISC_01391720",
    "FUN_00ade8b0",
    "FUN_006f5260",
    "FUN_0076acd0",
    "FUN_0076d8e0",
    "FUN_00430e70",
    "FUN_007b2ca0",
    "FUN_007b3760",
    "FUN_007b2f40",
    "FUN_00feb060"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "007c3f70",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_007c3f70",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3c3f70",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_007c3f70(void)",
  "size_bytes": 140,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007c3f70",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 65,
  "xrefs": [
    {
      "from": "0043126a"
    },
    {
      "from": "0058507e"
    },
    {
      "from": "005850b1"
    },
    {
      "from": "005850e4"
    },
    {
      "from": "00585117"
    },
    {
      "from": "0058514a"
    },
    {
      "from": "0080ebfc"
    },
    {
      "from": "0080e906"
    },
    {
      "from": "0076d925"
    },
    {
      "from": "0076b4a5"
    },
    {
      "from": "0076b767"
    },
    {
      "from": "006f52a9"
    },
    {
      "from": "006f6af0"
    },
    {
      "from": "006f6b36"
    },
    {
      "from": "006f6b79"
    },
    {
      "from": "006f6bbc"
    },
    {
      "from": "0076ae11"
    },
    {
      "from": "0076ae5f"
    },
    {
      "from": "0076aec8"
    },
    {
      "from": "00776fee"
    },
    {
      "from": "0077f0b5"
    },
    {
      "from": "007b2aff"
    },
    {
      "from": "007b2f8f"
    },
    {
      "from": "007b3056"
    },
    {
      "from": "007b323f"
    },
    {
      "from": "007b9472"
    },
    {
      "from": "007b9562"
    },
    {
      "from": "007be691"
    },
    {
      "from": "007bec2e"
    },
    {
      "from": "007b2d1a"
    },
    {
      "from": "007e758d"
    },
    {
      "from": "00adf2a0"
    },
    {
      "from": "00b357ef"
    },
    {
      "from": "00b3addc"
    },
    {
      "from": "00f67e9d"
    },
    {
      "from": "00f99f95"
    },
    {
      "from": "00f9f106"
    },
    {
      "from": "00feb083"
    },
    {
      "from": "0077f077"
    },
    {
      "from": "006e778e"
    },
    {
      "from": "006e77e3"
    },
    {
      "from": "006e782b"
    },
    {
      "from": "007b37d8"
    },
    {
      "from": "007b9903"
    },
    {
      "from": "007b9a77"
    },
    {
      "from": "007b9266"
    },
    {
      "from": "007c1575"
    },
    {
      "from": "007c15c7"
    },
    {
      "from": "007c1616"
    },
    {
      "from": "007c166b"
    },
    {
      "from": "007c16c0"
    },
    {
      "from": "007c1715"
    },
    {
      "from": "007c177c"
    },
    {
      "from": "007b9b54"
    },
    {
      "from": "007eab82"
    },
    {
      "from": "00e36306"
    },
    {
      "from": "00fa1062"
    },
    {
      "from": "013a58d5"
    },
    {
      "from": "013a58df"
    },
    {
      "from": "013a58e9"
    },
    {
      "from": "0137f8f5"
    },
    {
      "from": "013916d5"
    },
    {
      "from": "013916f5"
    },
    {
      "from": "01391725"
    },
    {
      "from": "01391785"
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
