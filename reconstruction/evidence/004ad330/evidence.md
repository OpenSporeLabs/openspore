# Evidence 0x004ad330

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `6229f3d7cfaaf5ef6b8e86bbb361fc2650c47f79082ef675c841533906b08315`

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
    "return_semantics": "unclassified_in_EAX",
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
  "content_sha256": "2df63a7bfcd5a8c7e299480e8dd7cf8dd53770705267e0145572e612097eae41",
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
        "obs-0024"
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
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0013",
        "obs-0014",
        "obs-0020",
        "obs-0021"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          48
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0013",
        "obs-0014",
        "obs-0020",
        "obs-0021",
        "obs-0024"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0024"
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
        "obs-0024"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0024"
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
      "at": "0x004ad330",
      "count": 11,
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
      "at": "0x004ad330",
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
      "sub": 12
    },
    {
      "at": "0x004ad331",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x004ad331",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004ad333",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0xc",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x004ad336",
      "count": 3,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0xc],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x004ad336",
      "base": "EBP",
      "disp": -12,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0xc],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x004ad339",
      "base": "EBP",
      "disp": -12,
      "id": "obs-0008",
      "index": 4,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [EBP + -0xc]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x004ad339",
      "definite": true,
      "id": "obs-0009",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EBP + -0xc]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x004ad33c",
      "id": "obs-0010",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x004ad280",
      "target": "0x004ad280"
    },
    {
      "at": "0x004ad341",
      "base": "EBP",
      "disp": -12,
      "id": "obs-0011",
      "index": 6,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + -0xc]",
      "reason": "local",
      "reso
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
"\nvoid __fastcall FUN_004ad330(int param_1)\n\n{\n  FUN_004ad280();\n  if (*(int *)(param_1 + 0x30) != 0) {\n    FUN_004b9570(param_1);\n  }\n  return;\n}\n\n"
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
      "address": "004ad330",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004ad331",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004ad333",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "004ad336",
      "instruction": "MOV dword ptr [EBP + -0xc],ECX"
    },
    {
      "address": "004ad339",
      "instruction": "MOV ECX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "004ad33c",
      "instruction": "CALL 0x004ad280"
    },
    {
      "address": "004ad341",
      "instruction": "MOV EAX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "004ad344",
      "instruction": "MOV ECX,dword ptr [EAX + 0x30]"
    },
    {
      "address": "004ad347",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "004ad34a",
      "instruction": "CMP dword ptr [EBP + -0x4],0x0"
    },
    {
      "address": "004ad34e",
      "instruction": "JZ 0x004ad365"
    },
    {
      "address": "004ad350",
      "instruction": "MOV EDX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "004ad353",
      "instruction": "MOV EAX,dword ptr [EDX + 0x30]"
    },
    {
      "address": "004ad356",
      "instruction": "MOV dword ptr [EBP + -0x8],EAX"
    },
    {
      "address": "004ad359",
      "instruction": "MOV ECX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "004ad35c",
      "instruction": "PUSH ECX"
    },
    {
      "address": "004ad35d",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "004ad360",
      "instruction": "CALL 0x004b9570"
    },
    {
      "address": "004ad365",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004ad367",
      "instruction": "POP EBP"
    },
    {
      "address": "004ad368",
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
  "body_end": "004ad368",
  "body_span_bytes": 57,
  "body_start": "004ad330",
  "callees": [
    "FUN_004ad280",
    "FUN_004b9570"
  ],
  "callers": [
    "FUN_0040d2d0",
    "FUN_004aba00",
    "FUN_0046d840",
    "Editors::cEditor::OnExit",
    "FUN_0057f6c0",
    "FUN_0057d710",
    "Editors::cEditor::SetEditorModel",
    "Editors::cEditor::Dispose",
    "FUN_005f40b0",
    "FUN_00585c10"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "004ad330",
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
  "name": "FUN_004ad330",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xad330",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004ad330(void)",
  "size_bytes": 57,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004ad330",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 13,
  "xrefs": [
    {
      "from": "0046da80"
    },
    {
      "from": "0040d3b5"
    },
    {
      "from": "0040e58e"
    },
    {
      "from": "004aba1f"
    },
    {
      "from": "00585c40"
    },
    {
      "from": "00586bf7"
    },
    {
      "from": "00587e15"
    },
    {
      "from": "00587e57"
    },
    {
      "from": "005f422e"
    },
    {
      "from": "0057f6dd"
    },
    {
      "from": "00576d38"
    },
    {
      "from": "00576d74"
    },
    {
      "from": "0057df35"
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
