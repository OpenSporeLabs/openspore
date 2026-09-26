# Evidence 0x0043eed0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `33a8ef9f163373bd74c6f5afb92a2abc7a0fe3c23c40437221c8817cbd2a409b`

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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBP"
    ],
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
  "content_sha256": "9f2cf6a9e9edf74823cac9edcf6346892c77bc7ce253f9f445f0d06e81d5368c",
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
        "obs-0012"
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
        "obs-0005",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          468
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0012"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0012"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x0043eed0",
      "count": 4,
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
      "at": "0x0043eed0",
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
      "at": "0x0043eed1",
      "count": 1,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x0043eed1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x0043eed3",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0043eed4",
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
      "at": "0x0043eed7",
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
      "at": "0x0043eed7",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBP + -0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0043eeda",
      "count": 1,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_READ",
      "raw": "FLD float ptr [EAX + 0x1d4]",
      "reg": "EAX"
    },
    {
      "at": "0x0043eee0",
      "definite": true,
      "id": "obs-0010",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ESP,EBP",
      "reg": "ESP",
      "write_kind": "reg"
    },
    {
      "at": "0x0043eee2",
      "id": "obs-0011",
      "index": 7,
      "kind": "REG_RESTORE",
      "raw": "POP EBP",
      "reg": "EBP"
    },
    {
      "at": "0x0043eee3",
      "form": "RET",
      "id": "obs-0012",
      "imm": null,
      "index": 8,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 9,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": true,
      "fp": true,
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 
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
"\nfloat10 __fastcall FUN_0043eed0(int param_1)\n\n{\n  return (float10)*(float *)(param_1 + 0x1d4);\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 9,
  "instructions": [
    {
      "address": "0043eed0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0043eed1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0043eed3",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0043eed4",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "0043eed7",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "0043eeda",
      "instruction": "FLD float ptr [EAX + 0x1d4]"
    },
    {
      "address": "0043eee0",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0043eee2",
      "instruction": "POP EBP"
    },
    {
      "address": "0043eee3",
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
  "body_end": "0043eee3",
  "body_span_bytes": 20,
  "body_start": "0043eed0",
  "callees": [],
  "callers": [
    "FUN_004c73f0",
    "FUN_004a1070",
    "FUN_0048b370",
    "FUN_0044ae00",
    "FUN_0043f3f0",
    "FUN_004a29a0",
    "FUN_0049cfd0",
    "Editors::cEditor::sub_581F70",
    "FUN_004860b0",
    "Editors::cEditor::OnKeyDown",
    "FUN_004a0bf0",
    "FUN_0043f3a0",
    "FUN_0043ecb0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0043eed0",
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
  "name": "FUN_0043eed0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3eed0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0043eed0(void)",
  "size_bytes": 20,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0043eed0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 22,
  "xrefs": [
    {
      "from": "0044afb9"
    },
    {
      "from": "0043f4ba"
    },
    {
      "from": "0043ed5d"
    },
    {
      "from": "0043ed68"
    },
    {
      "from": "0043eda4"
    },
    {
      "from": "004c9086"
    },
    {
      "from": "0043f3be"
    },
    {
      "from": "00486159"
    },
    {
      "from": "00486164"
    },
    {
      "from": "0048b6b8"
    },
    {
      "from": "0048b6c3"
    },
    {
      "from": "0048b77e"
    },
    {
      "from": "0048b819"
    },
    {
      "from": "0048b9c9"
    },
    {
      "from": "0049d1ad"
    },
    {
      "from": "004a15e2"
    },
    {
      "from": "004a2ab0"
    },
    {
      "from": "004a2ec1"
    },
    {
      "from": "004a0fc4"
    },
    {
      "from": "00582b81"
    },
    {
      "from": "00582ba8"
    },
    {
      "from": "0058af90"
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
