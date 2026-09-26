# Evidence 0x0062f540

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ac31ece9a141b48ff242ee3ca874e9e560a436cb290a48113f271b3b4ee021fc`

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
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "b27d37d57cbfdd5e4ed3ff1a39eaa1a9ad3cc7c40be0ccd47281df63eb33d73e",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0026"
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
        "obs-0004",
        "obs-0005",
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0014",
        "obs-0019",
        "obs-0022"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          52,
          56,
          60
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0014",
        "obs-0019",
        "obs-0022",
        "obs-0026"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
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
        "obs-0026"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0026"
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
      "and_esp": null,
      "at": "0x0062f540",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x14",
      "sub": 20
    },
    {
      "at": "0x0062f540",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x14",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0062f543",
      "count": 5,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0062f544",
      "count": 6,
      "first_use": 2,
      "first_write_index": 6,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0062f544",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x0062f546",
      "count": 3,
      "first_use": 3,
      "first_write_index": 9,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x0062f547",
      "count": 4,
      "first_use": 4,
      "first_write_index": 0,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "LEA ECX,[ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x0062f547",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0008",
      "index": 4,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA ECX,[ESP + 0x8]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x0062f54b",
      "id": "obs-0009",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x006b5060",
      "target": "0x006b5060"
    },
    {
      "at": "0x0062f550",
      "definite": true,
      "id": "obs-0010",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI + 0x34]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0062f558",
      "id": "obs-0011",
      "index": 8,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00634dc0",
      "target": "0x00634dc0"
    },
    {
      "at": "0x0062f55d",
      "count
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
"\nvoid __fastcall FUN_0062f540(int param_1)\n\n{\n  int iVar1;\n  int *piVar2;\n  undefined4 uVar3;\n  \n  FUN_006b5060();\n  piVar2 = (int *)FUN_00634dc0(0x47ed688);\n  if (piVar2 != (int *)0x0) {\n    FUN_006b54b0(0x7518573e,0x47ed777,L\"*BG Page Count*\");\n    *(int *)(DAT_015f7cf4 + 0x20) = *(int *)(param_1 + 0x38) + 1;\n    *(int *)(DAT_015f7cf4 + 0x24) = *(int *)(param_1 + 0x3c) + 1;\n    iVar1 = *piVar2;\n    uVar3 = FUN_006b55c0();\n    (**(code **)(iVar1 + 0x80))(uVar3);\n  }\n  FUN_006b5240();\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 38,
  "instructions": [
    {
      "address": "0062f540",
      "instruction": "SUB ESP,0x14"
    },
    {
      "address": "0062f543",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0062f544",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0062f546",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0062f547",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "0062f54b",
      "instruction": "CALL 0x006b5060"
    },
    {
      "address": "0062f550",
      "instruction": "MOV ECX,dword ptr [ESI + 0x34]"
    },
    {
      "address": "0062f553",
      "instruction": "PUSH 0x47ed688"
    },
    {
      "address": "0062f558",
      "instruction": "CALL 0x00634dc0"
    },
    {
      "address": "0062f55d",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "0062f55f",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "0062f561",
      "instruction": "JZ 0x0062f5aa"
    },
    {
      "address": "0062f563",
      "instruction": "PUSH 0x13fe404"
    },
    {
      "address": "0062f568",
      "instruction": "PUSH 0x47ed777"
    },
    {
      "address": "0062f56d",
      "instruction": "PUSH 0x7518573e"
    },
    {
      "address": "0062f572",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "0062f576",
      "instruction": "CALL 0x006b54b0"
    },
    {
      "address": "0062f57b",
      "instruction": "MOV EAX,dword ptr [ESI + 0x38]"
    },
    {
      "address": "0062f57e",
      "instruction": "MOV ECX,dword ptr [0x015f7cf4]"
    },
    {
      "address": "0062f584",
      "instruction": "INC EAX"
    },
    {
      "address": "0062f585",
      "instruction": "MOV dword ptr [ECX + 0x20],EAX"
    },
    {
      "address": "0062f588",
      "instruction": "MOV EDX,dword ptr [ESI + 0x3c]"
    },
    {
      "address": "0062f58b",
      "instruction": "MOV EAX,[0x015f7cf4]"
    },
    {
      "address": "0062f590",
      "instruction": "INC EDX"
    },
    {
      "address": "0062f591",
      "instruction": "MOV dword ptr [EAX + 0x24],EDX"
    },
    {
      "address": "0062f594",
      "instruction": "MOV ESI,dword ptr [EDI]"
    },
    {
      "address": "0062f596",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "0062f59a",
      "instruction": "CALL 0x006b55c0"
    },
    {
      "address": "0062f59f",
      "instruction": "MOV EDX,dword ptr [ESI + 0x80]"
    },
    {
      "address": "0062f5a5",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0062f5a6",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0062f5a8",
      "instruction": "CALL EDX"
    },
    {
      "address": "0062f5aa",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "0062f5ae",
      "instruction": "CALL 0x006b5240"
    },
    {
      "address": "0062f5b3",
      "instruction": "POP EDI"
    },
    {
      "address": "0062f5b4",
      "instruction": "POP ESI"
    },
    {
      "address": "0062f5b5",
      "instruction": "ADD ESP,0x14"
    },
    {
      "address": "0062f5b8",
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
  "body_end": "0062f5b8",
  "body_span_bytes": 121,
  "body_start": "0062f540",
  "callees": [
    "FUN_006b5060",
    "FUN_006b55c0",
    "FUN_00634dc0",
    "FUN_006b5240",
    "FUN_006b54b0"
  ],
  "callers": [
    "FUN_0062f7f0",
    "FUN_0062fc90"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0062f540",
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
    },
    {
      "name": "piVar2",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "iVar1",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "uVar3",
      "storage": "register:00000000:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_0062f540",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x22f540",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0062f540(void)",
  "size_bytes": 121,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0062f540",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "0062fd06"
    },
    {
      "from": "0062f88f"
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
