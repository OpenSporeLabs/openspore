# Evidence 0x00ac7a40

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a94b6e5ec43bc34b2e6fb5a1bd42aeefa7de098431d7a5bca2bad48e11f2b193`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__stdcall",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
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
      }
    ],
    "receiver": false,
    "ret_form": "RET 0x4",
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
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
  "content_sha256": "1154e46167e05f5b89c85358b090a369e0c258857b564d40a68e55f0aebc8d51",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__stdcall",
    "candidate_conventions": [
      "__stdcall"
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0024"
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
        "obs-0003"
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
        "obs-0024"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0024"
      ],
      "claim": "calling convention is __stdcall: a callee that pops stack arguments with no register receiver",
      "confidence": "INFERRED",
      "id": "C6",
      "value": "__stdcall"
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
      "at": "0x00ac7a40",
      "count": 7,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00ac7a41",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00ac7a41",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00ac7a41",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESP + 0x8]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00ac7a49",
      "definite": true,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EDI",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00ac7a4b",
      "id": "obs-0006",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00cee370",
      "target": "0x00cee370"
    },
    {
      "at": "0x00ac7a54",
      "count": 10,
      "first_use": 8,
      "first_write_index": 11,
      "id": "obs-0007",
      "index": 8,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00ac7a57",
      "id": "obs-0008",
      "index": 10,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00cee330",
      "target": "0x00cee330"
    },
    {
      "at": "0x00ac7a5c",
      "count": 6,
      "first_use": 11,
      "first_write_index": 14,
      "id": "obs-0009",
      "index": 11,
      "kind": "REG_READ",
      "raw": "MOV ESI,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00ac7a5c",
      "definite": true,
      "id": "obs-0010",
      "index": 11,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,EAX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00ac7a62",
      "definite": true,
      "id": "obs-0011",
      "index": 14,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI]",
      "reg": "EAX",
      "write_kind": "me
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
"\nvoid FUN_00ac7a40(int *param_1)\n\n{\n  int iVar1;\n  int *piVar2;\n  int *piVar3;\n  \n  if (param_1 != (int *)0x0) {\n    iVar1 = FUN_00cee370();\n    while (0 < iVar1) {\n      piVar2 = (int *)FUN_00cee330();\n      if (piVar2 != (int *)0x0) {\n        (**(code **)*piVar2)();\n      }\n      (**(code **)(*param_1 + 0xc))(piVar2);\n      FUN_00cee650(piVar2);\n      (**(code **)(*piVar2 + 0x44))();\n      piVar3 = piVar2;\n      FUN_00b3d300(piVar2);\n      FUN_00b225d0(piVar3);\n      (**(code **)(*piVar2 + 4))();\n      iVar1 = FUN_00cee370();\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 45,
  "instructions": [
    {
      "address": "00ac7a40",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ac7a41",
      "instruction": "MOV EDI,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00ac7a45",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00ac7a47",
      "instruction": "JZ 0x00ac7aa7"
    },
    {
      "address": "00ac7a49",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00ac7a4b",
      "instruction": "CALL 0x00cee370"
    },
    {
      "address": "00ac7a50",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00ac7a52",
      "instruction": "JLE 0x00ac7aa7"
    },
    {
      "address": "00ac7a54",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ac7a55",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00ac7a57",
      "instruction": "CALL 0x00cee330"
    },
    {
      "address": "00ac7a5c",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00ac7a5e",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00ac7a60",
      "instruction": "JZ 0x00ac7a6a"
    },
    {
      "address": "00ac7a62",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00ac7a64",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00ac7a66",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ac7a68",
      "instruction": "CALL EDX"
    },
    {
      "address": "00ac7a6a",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00ac7a6c",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00ac7a6f",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ac7a70",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00ac7a72",
      "instruction": "CALL EDX"
    },
    {
      "address": "00ac7a74",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ac7a75",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00ac7a77",
      "instruction": "CALL 0x00cee650"
    },
    {
      "address": "00ac7a7c",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00ac7a7e",
      "instruction": "MOV EDX,dword ptr [EAX + 0x44]"
    },
    {
      "address": "00ac7a81",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ac7a83",
      "instruction": "CALL EDX"
    },
    {
      "address": "00ac7a85",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ac7a86",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00ac7a8b",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ac7a8d",
      "instruction": "CALL 0x00b225d0"
    },
    {
      "address": "00ac7a92",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00ac7a94",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00ac7a97",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00ac7a99",
      "instruction": "CALL EDX"
    },
    {
      "address": "00ac7a9b",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00ac7a9d",
      "instruction": "CALL 0x00cee370"
    },
    {
      "address": "00ac7aa2",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00ac7aa4",
      "instruction": "JG 0x00ac7a55"
    },
    {
      "address": "00ac7aa6",
      "instruction": "POP ESI"
    },
    {
      "address": "00ac7aa7",
      "instruction": "POP EDI"
    },
    {
      "address": "00ac7aa8",
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
  "body_end": "00ac7aaa",
  "body_span_bytes": 107,
  "body_start": "00ac7a40",
  "callees": [
    "FUN_00b3d300",
    "FUN_00cee650",
    "FUN_00cee330",
    "FUN_00b225d0",
    "FUN_00cee370"
  ],
  "callers": [
    "FUN_00b25fe0",
    "FUN_00b32f60",
    "FUN_00cee7e0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ac7a40",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "piVar3",
      "storage": "Stack[-0x10]:4",
      "type": "int *"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "piVar2",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00ac7a40",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6c7a40",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ac7a40(void)",
  "size_bytes": 107,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ac7a40",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00b260b3"
    },
    {
      "from": "00b33009"
    },
    {
      "from": "00cee7eb"
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
