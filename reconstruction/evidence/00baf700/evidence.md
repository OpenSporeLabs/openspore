# Evidence 0x00baf700

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `6a2ad979324de0c3b37d883ee770a48d486de4d5c42dbcc7b88571ea017583f2`

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
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EBX",
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
    "flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path",
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
  "content_sha256": "c523334e40c54641c0d6e63ed41aae2f2566567158a623ff32e3ff4852117c29",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017",
        "obs-0035"
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
        "obs-0003",
        "obs-0009",
        "obs-0011",
        "obs-0022"
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
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0010",
        "obs-0016",
        "obs-0034"
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
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0010",
        "obs-0016",
        "obs-0034"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0017",
        "obs-0035"
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
        "obs-0017",
        "obs-0035"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0017",
        "obs-0035"
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
      "at": "0x00baf700",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00baf701",
      "count": 7,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00baf701",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00baf701",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00baf705",
      "count": 3,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00baf706",
      "id": "obs-0006",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00c30e80",
      "target": "0x00c30e80"
    },
    {
      "at": "0x00baf70b",
      "count": 11,
      "first_use": 4,
      "first_write_index": 12,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EBX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00baf70b",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
     
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
"\nundefined * FUN_00baf700(undefined4 param_1)\n\n{\n  int *piVar1;\n  undefined4 uVar2;\n  int *piVar3;\n  int *piVar4;\n  undefined4 *puVar5;\n  undefined **local_4;\n  \n  uVar2 = FUN_00c30e80();\n  param_1 = uVar2;\n  map_int_whatever_find(&local_4,&param_1);\n  if (local_4 != &PTR_LOOP_0156c620) {\n    return local_4[5];\n  }\n  piVar3 = (int *)FUN_0067de30();\n  piVar4 = (int *)FUN_00dd85c0(&param_1);\n  piVar1 = (int *)*piVar4;\n  if (piVar1 != (int *)0x0) {\n    *piVar4 = 0;\n    (**(code **)(*piVar1 + 4))();\n  }\n  (**(code **)(*piVar3 + 0x2c))(uVar2,0x568de14,piVar4);\n  puVar5 = (undefined4 *)FUN_00dd85c0(&stack0xfffffff8);\n  return (undefined *)*puVar5;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 52,
  "instructions": [
    {
      "address": "00baf700",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00baf701",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00baf705",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00baf706",
      "instruction": "CALL 0x00c30e80"
    },
    {
      "address": "00baf70b",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00baf70d",
      "instruction": "LEA EAX,[ESP + 0xc]"
    },
    {
      "address": "00baf711",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00baf712",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "00baf716",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00baf717",
      "instruction": "MOV ECX,0x156c61c"
    },
    {
      "address": "00baf71c",
      "instruction": "MOV dword ptr [ESP + 0x14],EBX"
    },
    {
      "address": "00baf720",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "00baf725",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00baf729",
      "instruction": "CMP EAX,0x156c620"
    },
    {
      "address": "00baf72e",
      "instruction": "JZ 0x00baf738"
    },
    {
      "address": "00baf730",
      "instruction": "MOV EAX,dword ptr [EAX + 0x14]"
    },
    {
      "address": "00baf733",
      "instruction": "POP EBX"
    },
    {
      "address": "00baf734",
      "instruction": "POP ECX"
    },
    {
      "address": "00baf735",
      "instruction": "RET 0x4"
    },
    {
      "address": "00baf738",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00baf739",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00baf73a",
      "instruction": "CALL 0x0067de30"
    },
    {
      "address": "00baf73f",
      "instruction": "LEA EDX,[ESP + 0x14]"
    },
    {
      "address": "00baf743",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00baf744",
      "instruction": "MOV ECX,0x156c61c"
    },
    {
      "address": "00baf749",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00baf74b",
      "instruction": "CALL 0x00dd85c0"
    },
    {
      "address": "00baf750",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00baf752",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "00baf754",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00baf756",
      "instruction": "JZ 0x00baf765"
    },
    {
      "address": "00baf758",
      "instruction": "MOV dword ptr [ESI],0x0"
    },
    {
      "address": "00baf75e",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00baf760",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00baf763",
      "instruction": "CALL EDX"
    },
    {
      "address": "00baf765",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00baf767",
      "instruction": "MOV EDX,dword ptr [EAX + 0x2c]"
    },
    {
      "address": "00baf76a",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00baf76b",
      "instruction": "PUSH 0x568de14"
    },
    {
      "address": "00baf770",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00baf771",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00baf773",
      "instruction": "CALL EDX"
    },
    {
      "address": "00baf775",
      "instruction": "LEA EAX,[ESP + 0x14]"
    },
    {
      "address": "00baf779",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00baf77a",
      "instruction": "MOV ECX,0x156c61c"
    },
    {
      "address": "00baf77f",
      "instruction": "CALL 0x00dd85c0"
    },
    {
      "address": "00baf784",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00baf786",
      "instruction": "POP EDI"
    },
    {
      "address": "00baf787",
      "instruction": "POP ESI"
    },
    {
      "address": "00baf788",
      "instruction": "POP EBX"
    },
    {
      "address": "00baf789",
      "instruction": "POP ECX"
    },
    {
      "address": "00baf78a",
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
  "body_end": "00baf78c",
  "body_span_bytes": 141,
  "body_start": "00baf700",
  "callees": [
    "FUN_0067de30",
    "map_int_whatever_find",
    "FUN_00dd85c0",
    "FUN_00c30e80"
  ],
  "callers": [
    "FUN_01030930",
    "FUN_00bd9a80",
    "FUN_00c784c0",
    "FUN_01030aa0",
    "FUN_010407d0",
    "FUN_00c322f0",
    "FUN_00c35320",
    "FUN_00fed640",
    "FUN_010309c0",
    "FUN_00ff5930",
    "FUN_00c76800",
    "FUN_00c75d70",
    "FUN_00c75940",
    "FUN_01030a30"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00baf700",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "puVar5",
      "storage": "register:00000000:4",
      "type": "undefined4 *"
    },
    {
      "name": "uVar2",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined * *"
    },
    {
      "name": "piVar1",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "piVar4",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "piVar3",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00baf700",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7af700",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00baf700(void)",
  "size_bytes": 141,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00baf700",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 15,
  "xrefs": [
    {
      "from": "00c356b2"
    },
    {
      "from": "00c78568"
    },
    {
      "from": "00c785cb"
    },
    {
      "from": "00c75d9f"
    },
    {
      "from": "00c7594f"
    },
    {
      "from": "00fed75b"
    },
    {
      "from": "00c323f7"
    },
    {
      "from": "00c76977"
    },
    {
      "from": "01030966"
    },
    {
      "from": "01030a08"
    },
    {
      "from": "01030a78"
    },
    {
      "from": "01030ae8"
    },
    {
      "from": "010407df"
    },
    {
      "from": "00ff5997"
    },
    {
      "from": "00bd9ad9"
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
