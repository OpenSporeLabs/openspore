# Evidence 0x004adc20

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ba595945e53282206c8d9a82fc2203a7f4b9871d163487cd001e0654d478fa8b`

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
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EBP"
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
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "f7848659a7cf3961b1dae5409a724206c574dab9af7858f4ccb76c650e9ed859",
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
        "obs-0014"
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
        "obs-0009"
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
        "obs-0005",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          79
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0014"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0014"
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
        "obs-0014"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0014"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x004adc20",
      "count": 5,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x004adc20",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x004adc21",
      "count": 1,
      "first_use": 1,
      "first_write_index": 7,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x004adc21",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004adc23",
      "count": 2,
      "first_use": 2,
      "first_write_index": 5,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x004adc24",
      "base": "EBP",
      "disp": -4,
      "id": "obs-0006",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x4],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x004adc27",
      "base": "EBP",
      "disp": -4,
      "id": "obs-0007",
      "index": 4,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + -0x4]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x004adc27",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBP + -0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x004adc2a",
      "base": "EBP",
      "disp": 8,
      "id": 
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nvoid __thiscall FUN_004adc20(int param_1,undefined1 param_2)\n\n{\n  *(undefined1 *)(param_1 + 0x4f) = param_2;\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 10,
  "instructions": [
    {
      "address": "004adc20",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004adc21",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004adc23",
      "instruction": "PUSH ECX"
    },
    {
      "address": "004adc24",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "004adc27",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004adc2a",
      "instruction": "MOV CL,byte ptr [EBP + 0x8]"
    },
    {
      "address": "004adc2d",
      "instruction": "MOV byte ptr [EAX + 0x4f],CL"
    },
    {
      "address": "004adc30",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004adc32",
      "instruction": "POP EBP"
    },
    {
      "address": "004adc33",
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "004adc35",
  "body_span_bytes": 22,
  "body_start": "004adc20",
  "callees": [],
  "callers": [
    "FUN_004a6f10",
    "FUN_0048f790",
    "FUN_005b74f0",
    "FUN_00586960",
    "Editors::cEditor::SetEditorModel",
    "FUN_004a6ca0",
    "Editors::cEditor::sub_581F70",
    "FUN_0043fc20",
    "FUN_0049d6b0",
    "FUN_005b75e0",
    "FUN_004a6d20",
    "FUN_004934d0",
    "FUN_005d07f0",
    "FUN_005d02d0",
    "FUN_005b4bf0",
    "FUN_005b8fb0",
    "FUN_005be500"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "004adc20",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_2",
      "storage": "Stack[0x4]:1",
      "type": "undefined1"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_004adc20",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xadc20",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004adc20(void)",
  "size_bytes": 22,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004adc20",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 45,
  "xrefs": [
    {
      "from": "0049350c"
    },
    {
      "from": "004935db"
    },
    {
      "from": "0043fc88"
    },
    {
      "from": "0043ff6e"
    },
    {
      "from": "0048f96e"
    },
    {
      "from": "0048f9a5"
    },
    {
      "from": "0048fc90"
    },
    {
      "from": "0048fd27"
    },
    {
      "from": "0049d8bd"
    },
    {
      "from": "0049d98e"
    },
    {
      "from": "0049da08"
    },
    {
      "from": "004a6f8d"
    },
    {
      "from": "004a7556"
    },
    {
      "from": "004a7c05"
    },
    {
      "from": "004a6d7f"
    },
    {
      "from": "004a6eeb"
    },
    {
      "from": "004a6cb6"
    },
    {
      "from": "004a6d13"
    },
    {
      "from": "00586a20"
    },
    {
      "from": "00586aa5"
    },
    {
      "from": "00582898"
    },
    {
      "from": "0058290e"
    },
    {
      "from": "005871f0"
    },
    {
      "from": "005b4e72"
    },
    {
      "from": "005b4ec5"
    },
    {
      "from": "005b75cf"
    },
    {
      "from": "005b7606"
    },
    {
      "from": "005b93d5"
    },
    {
      "from": "005b9418"
    },
    {
      "from": "005be886"
    },
    {
      "from": "005bea13"
    },
    {
      "from": "005d030f"
    },
    {
      "from": "005d07e2"
    },
    {
      "from": "005d0c5d"
    },
    {
      "from": "005d0cab"
    },
    {
      "from": "005b48e2"
    },
    {
      "from": "005b4a5b"
    },
    {
      "from": "005b4a68"
    },
    {
      "from": "005b4a97"
    },
    {
      "from": "005b79fa"
    },
    {
      "from": "005b7a2b"
    },
    {
      "from": "005bd661"
    },
    {
      "from": "005bd692"
    },
    {
      "from": "005bd6c8"
    },
    {
      "from": "005beb13"
    }
  ]
}
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
