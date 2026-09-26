# Evidence 0x00d01fb0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1c5343cc54c24abda318fe4eb595a6ac9f20fb618a1ef31d3f6dcb671455d01b`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
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
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "56d8fed3405ddd02a7938baed9b46c129bfd785842e84695c498ea46a6733118",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0013",
        "obs-0014"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0007"
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
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0008"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0008"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0013",
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
        "obs-0013",
        "obs-0014"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0014"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00d01fb0",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00d01fb0",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00d01fb0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00d01fb4",
      "count": 3,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00d01fb5",
      "count": 3,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00d01fb5",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00d01fb7",
 
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
"\nuint FUN_00d01fb0(undefined4 param_1,undefined4 param_2)\n\n{\n  undefined4 uVar1;\n  int iVar2;\n  \n  uVar1 = FUN_00d01ab0(param_1,param_2);\n  iVar2 = FUN_00d01410(uVar1,param_1,param_2);\n  if (iVar2 != 0) {\n    return CONCAT31((uint3)(*(uint *)(iVar2 + 4) >> 9),(char)(*(uint *)(iVar2 + 4) >> 1)) &\n           0xffffff01;\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 22,
  "instructions": [
    {
      "address": "00d01fb0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00d01fb4",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00d01fb5",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00d01fb7",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00d01fbb",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d01fbc",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d01fbd",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d01fbe",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00d01fbf",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00d01fc1",
      "instruction": "CALL 0x00d01ab0"
    },
    {
      "address": "00d01fc6",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00d01fc7",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00d01fc9",
      "instruction": "CALL 0x00d01410"
    },
    {
      "address": "00d01fce",
      "instruction": "POP ESI"
    },
    {
      "address": "00d01fcf",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00d01fd1",
      "instruction": "JZ 0x00d01fdd"
    },
    {
      "address": "00d01fd3",
      "instruction": "MOV EAX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00d01fd6",
      "instruction": "SHR EAX,0x1"
    },
    {
      "address": "00d01fd8",
      "instruction": "AND AL,0x1"
    },
    {
      "address": "00d01fda",
      "instruction": "RET 0x8"
    },
    {
      "address": "00d01fdd",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00d01fdf",
      "instruction": "RET 0x8"
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
  "body_end": "00d01fe1",
  "body_span_bytes": 50,
  "body_start": "00d01fb0",
  "callees": [
    "FUN_00d01410",
    "FUN_00d01ab0"
  ],
  "callers": [
    "FUN_00c5b9c0",
    "FUN_01058020",
    "FUN_00c309e0",
    "FUN_00fdade0",
    "FUN_00c322f0",
    "FUN_0100b430",
    "FUN_00fe8f70",
    "FUN_00fe9580",
    "FUN_01008910"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00d01fb0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00d01fb0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x901fb0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00d01fb0(void)",
  "size_bytes": 50,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00d01fb0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 12,
  "xrefs": [
    {
      "from": "00fe9e37"
    },
    {
      "from": "00fe9f86"
    },
    {
      "from": "00fe90da"
    },
    {
      "from": "00fe91e3"
    },
    {
      "from": "00c325a3"
    },
    {
      "from": "00c5ba68"
    },
    {
      "from": "00c30a4c"
    },
    {
      "from": "00fdb071"
    },
    {
      "from": "0100b51d"
    },
    {
      "from": "01008aa4"
    },
    {
      "from": "010581bd"
    },
    {
      "from": "010582cf"
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
