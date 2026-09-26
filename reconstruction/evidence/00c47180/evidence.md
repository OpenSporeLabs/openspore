# Evidence 0x00c47180

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `30fb906d60278db615aa4efa3a5bc5756a627c7004a988dee6822686122ce84f`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
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
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "cbc82bab009dff12e96896d09419a18a32ae5a305186802cde79f760b1254c36",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
      "__thiscall"
    ],
    "confidence": "UNKNOWN",
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
        "obs-0002",
        "obs-0003",
        "obs-0004"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
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
      "at": "0x00c47180",
      "count": 5,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c47181",
      "count": 2,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "LEA ESI,[ECX + 0x1e8]",
      "reg": "ECX"
    },
    {
      "at": "0x00c47187",
      "definite": true,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c47193",
      "definite": true,
      "id": "obs-0004",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c47195",
      "count": 3,
      "first_use": 7,
      "first_write_index": 6,
      "id": "obs-0005",
      "index": 7,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0xc0]",
      "reg": "EAX"
    },
    {
      "at": "0x00c47195",
      "definite": true,
      "id": "obs-0006",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0xc0]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c4719b",
      "count": 1,
      "first_use": 8,
      "first_write_index": 7,
      "id": "obs-0007",
      "index": 8,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00c4719b",
      "base": "EDX",
      "disp": null,
      "id": "obs-0008",
      "index": 8,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00c4719d",
      "count": 1,
      "first_use": 9,
      "first_write_index": null,
      "id": "obs-0009",
      "index": 9,
      "kind": "REG_READ",
      "raw":
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
"\nvoid __thiscall FUN_00c47180(int param_1,undefined4 param_2)\n\n{\n  int *piVar1;\n  int *piVar2;\n  \n  piVar2 = (int *)(param_1 + 0x1e8);\n  piVar1 = (int *)*piVar2;\n  if (piVar1 != (int *)0x0) {\n    *piVar2 = 0;\n    (**(code **)(*piVar1 + 0xc0))();\n  }\n  FUN_00b3d2a0(param_2,piVar2);\n  FUN_00bb59b0(param_2,piVar2);\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 17,
  "instructions": [
    {
      "address": "00c47180",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c47181",
      "instruction": "LEA ESI,[ECX + 0x1e8]"
    },
    {
      "address": "00c47187",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "00c47189",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00c4718b",
      "instruction": "JZ 0x00c4719d"
    },
    {
      "address": "00c4718d",
      "instruction": "MOV dword ptr [ESI],0x0"
    },
    {
      "address": "00c47193",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00c47195",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc0]"
    },
    {
      "address": "00c4719b",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c4719d",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c471a1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c471a2",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c471a3",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00c471a8",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c471aa",
      "instruction": "CALL 0x00bb59b0"
    },
    {
      "address": "00c471af",
      "instruction": "POP ESI"
    },
    {
      "address": "00c471b0",
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
  "body_end": "00c471b2",
  "body_span_bytes": 51,
  "body_start": "00c47180",
  "callees": [
    "FUN_00bb59b0",
    "FUN_00b3d2a0"
  ],
  "callers": [
    "FUN_00c63380",
    "FUN_00c4b440",
    "FUN_00c4b7f0",
    "FUN_0101246a",
    "FUN_01012aa0",
    "FUN_010593e0",
    "FUN_00fe9580",
    "FUN_00c51010",
    "FUN_00c4e440",
    "FUN_00c60e90",
    "FUN_010251e0",
    "FUN_00c557c0",
    "FUN_0100e780",
    "FUN_00c4f4e0",
    "FUN_00c62b30",
    "FUN_01014870",
    "FUN_00c5ea60",
    "FUN_0102d0b0",
    "FUN_00c5f770",
    "FUN_00c54380",
    "FUN_01014540",
    "FUN_01012b50"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c47180",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "piVar1",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "piVar2",
      "storage": "Stack[-0x8]:4",
      "type": "int *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00c47180",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x847180",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c47180(void)",
  "size_bytes": 51,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c47180",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 31,
  "xrefs": [
    {
      "from": "00fe9acf"
    },
    {
      "from": "0102d125"
    },
    {
      "from": "00c4b520"
    },
    {
      "from": "00c4b86d"
    },
    {
      "from": "00c4b8c0"
    },
    {
      "from": "00c4e498"
    },
    {
      "from": "00c4e527"
    },
    {
      "from": "00c4f5f8"
    },
    {
      "from": "00c4f6d0"
    },
    {
      "from": "00c511b6"
    },
    {
      "from": "00c511fa"
    },
    {
      "from": "00c5440a"
    },
    {
      "from": "00c54509"
    },
    {
      "from": "00c557db"
    },
    {
      "from": "00c5ea89"
    },
    {
      "from": "00c5eb0e"
    },
    {
      "from": "00c5fae1"
    },
    {
      "from": "00c60ec4"
    },
    {
      "from": "00c60f4e"
    },
    {
      "from": "00c62c63"
    },
    {
      "from": "00c633fb"
    },
    {
      "from": "00c6345d"
    },
    {
      "from": "010124de"
    },
    {
      "from": "01012bae"
    },
    {
      "from": "01014633"
    },
    {
      "from": "01014944"
    },
    {
      "from": "0102544b"
    },
    {
      "from": "0100e7ea"
    },
    {
      "from": "01012b0b"
    },
    {
      "from": "01059e95"
    },
    {
      "from": "00c54e18"
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
