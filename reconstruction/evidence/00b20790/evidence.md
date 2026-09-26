# Evidence 0x00b20790

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `27baa68ff01e9f8fa10428e69b2a2f4d79d1131b9a831b23ff804c646ad9979f`

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
        "size_inferred": true,
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
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "4e86883b631a3289d69083a469f75bdf4df59f3ce59c23ff94b7cc718d3ed38e",
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
        "obs-0020",
        "obs-0026"
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
        "obs-0005",
        "obs-0009",
        "obs-0011"
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
        "obs-0001",
        "obs-0007",
        "obs-0010",
        "obs-0015",
        "obs-0019",
        "obs-0025"
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
        "obs-0001",
        "obs-0007",
        "obs-0010",
        "obs-0015",
        "obs-0019",
        "obs-0025"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0020",
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
        "obs-0020",
        "obs-0026"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0020",
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
      "at": "0x00b20790",
      "count": 5,
      "first_use": 0,
      "first_write_index": 20,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b20791",
      "count": 4,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b20792",
      "count": 3,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b20793",
      "count": 4,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x00b20793",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0005",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00b20793",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESP + 0x10]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b20797",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b20799",
      "count": 7,
      "first_use": 5,
      "first_write_index": 12,
      "id": "obs-0008",
      "index": 5,
      "kind"
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
"\nuint __thiscall FUN_00b20790(int param_1,undefined4 param_2)\n\n{\n  int *piVar1;\n  uint uVar2;\n  int iVar3;\n  undefined4 uVar4;\n  int local_4;\n  \n  uVar4 = param_2;\n  local_4 = param_1;\n  piVar1 = (int *)map_int_whatever_find(&local_4,&param_2);\n  if ((*piVar1 != param_1 + 0xd4) && (iVar3 = *(int *)(*piVar1 + 0x14), iVar3 != 0)) {\n    uVar2 = FUN_00b1feb0(iVar3);\n    return uVar2;\n  }\n  FUN_00b3d2a0(uVar4);\n  iVar3 = FUN_00ba9370(uVar4);\n  return -(uint)(iVar3 != 0) & 5;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 37,
  "instructions": [
    {
      "address": "00b20790",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00b20791",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b20792",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b20793",
      "instruction": "MOV EDI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00b20797",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b20799",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00b2079d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b2079e",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "00b207a2",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00b207a3",
      "instruction": "LEA ECX,[ESI + 0xd0]"
    },
    {
      "address": "00b207a9",
      "instruction": "MOV dword ptr [ESP + 0x18],EDI"
    },
    {
      "address": "00b207ad",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "00b207b2",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00b207b4",
      "instruction": "LEA EDX,[ESI + 0xd4]"
    },
    {
      "address": "00b207ba",
      "instruction": "CMP EAX,EDX"
    },
    {
      "address": "00b207bc",
      "instruction": "JZ 0x00b207d3"
    },
    {
      "address": "00b207be",
      "instruction": "MOV EAX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00b207c1",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00b207c3",
      "instruction": "JZ 0x00b207d3"
    },
    {
      "address": "00b207c5",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b207c6",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b207c8",
      "instruction": "CALL 0x00b1feb0"
    },
    {
      "address": "00b207cd",
      "instruction": "POP EDI"
    },
    {
      "address": "00b207ce",
      "instruction": "POP ESI"
    },
    {
      "address": "00b207cf",
      "instruction": "POP ECX"
    },
    {
      "address": "00b207d0",
      "instruction": "RET 0x4"
    },
    {
      "address": "00b207d3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b207d4",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00b207d9",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b207db",
      "instruction": "CALL 0x00ba9370"
    },
    {
      "address": "00b207e0",
      "instruction": "NEG EAX"
    },
    {
      "address": "00b207e2",
      "instruction": "SBB EAX,EAX"
    },
    {
      "address": "00b207e4",
      "instruction": "POP EDI"
    },
    {
      "address": "00b207e5",
      "instruction": "AND EAX,0x5"
    },
    {
      "address": "00b207e8",
      "instruction": "POP ESI"
    },
    {
      "address": "00b207e9",
      "instruction": "POP ECX"
    },
    {
      "address": "00b207ea",
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
  "body_end": "00b207ec",
  "body_span_bytes": 93,
  "body_start": "00b20790",
  "callees": [
    "FUN_00b1feb0",
    "FUN_00ba9370",
    "FUN_00b3d2a0",
    "map_int_whatever_find"
  ],
  "callers": [
    "FUN_00b99ed0",
    "FUN_00bf8170",
    "FUN_00c359a0",
    "FUN_00c8e4f0",
    "FUN_00befc40",
    "FUN_00d05d90",
    "FUN_00d01bb0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b20790",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "piVar1",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "uVar4",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "uVar2",
      "storage": "register:00000000:4",
      "type": "uint"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00b20790",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x720790",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b20790(void)",
  "size_bytes": 93,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b20790",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "00c359c2"
    },
    {
      "from": "00d05f2d"
    },
    {
      "from": "00b9a157"
    },
    {
      "from": "00befc71"
    },
    {
      "from": "00bf83c9"
    },
    {
      "from": "00bf8419"
    },
    {
      "from": "00c8e52f"
    },
    {
      "from": "00d01bef"
    },
    {
      "from": "00d01c8f"
    },
    {
      "from": "00d01ca8"
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
