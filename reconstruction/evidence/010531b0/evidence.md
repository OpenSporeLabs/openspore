# Evidence 0x010531b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `87351505ed2e6adccf783379cff59e6faa6ea57d5c7dc211afcafb4a92c2987e`

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
    "ret_form": "RET",
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +60, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "dd0cc600ba8e35ba31c1c44a448eb23d68dd3dd4242512016ad492608d6d0249",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
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
        "obs-0010",
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
        "obs-0002"
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
        "obs-0006",
        "obs-0018",
        "obs-0019"
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
        "obs-0006",
        "obs-0018",
        "obs-0019"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0010",
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
        "obs-0010",
        "obs-0026"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0010",
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
      "at": "0x010531b0",
      "count": 4,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x010531b0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x010531b0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x010531bc",
      "count": 11,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x010531c2",
      "id": "obs-0005",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d3e0",
      "target": "0x00b3d3e0"
    },
    {
      "at": "0x010531c7",
      "definite": true,
      "id": "obs-0006",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x010531c9",
      "id": "obs-0007",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00dd5d80",
      "target": "0x00dd5d80"
    },
    {
      "at": "0x010531d3",
      "id": "obs-0008",
      "index": 11,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d3e0",
      "target": "0x00b3d3e0"
    },
    {
      "at": "0x010531da",
      "id": "obs-0009",
      "index": 13,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00dd6a70",
      "target": 
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
"\nvoid FUN_010531b0(int param_1,undefined4 param_2,undefined4 param_3,int param_4,undefined4 param_5)\n\n{\n  int iVar1;\n  undefined4 uVar2;\n  undefined4 uVar3;\n  undefined4 uVar4;\n  undefined4 uVar5;\n  undefined4 uVar6;\n  undefined4 uVar7;\n  \n  if (param_1 != 0) {\n    uVar6 = 0x6e000a7a;\n    iVar1 = param_1;\n    FUN_00b3d3e0(0x6e000a7a,param_1);\n    iVar1 = FUN_00dd5d80(uVar6,iVar1);\n    if (iVar1 != 0) {\n      FUN_00b3d3e0(iVar1);\n      FUN_00dd6a70(iVar1);\n      return;\n    }\n    uVar7 = 0;\n    uVar5 = 1;\n    uVar4 = 0;\n    uVar3 = 0;\n    uVar2 = 0x131a9f54;\n    uVar6 = 0x6e000a7a;\n    FUN_00b3d3e0(0x6e000a7a,0x131a9f54,0,0,1,0);\n    uVar2 = FUN_00dd8640(uVar6,uVar2,uVar3,uVar4,uVar5,uVar7);\n    uVar6 = uVar2;\n    FUN_00b3d3e0(uVar2,param_5);\n    FUN_00dd6df0(uVar6,param_5);\n    uVar6 = uVar2;\n    FUN_00b3d3e0(uVar2,param_1);\n    FUN_00dd6930(uVar6,param_1);\n    if (param_4 != 0) {\n      FUN_00b3d3e0(uVar2,param_4);\n      FUN_00dd6b70(uVar2,param_4);\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 48,
  "instructions": [
    {
      "address": "010531b0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "010531b4",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "010531b6",
      "instruction": "JZ 0x0105323c"
    },
    {
      "address": "010531bc",
      "instruction": "PUSH EAX"
    },
    {
      "address": "010531bd",
      "instruction": "PUSH 0x6e000a7a"
    },
    {
      "address": "010531c2",
      "instruction": "CALL 0x00b3d3e0"
    },
    {
      "address": "010531c7",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "010531c9",
      "instruction": "CALL 0x00dd5d80"
    },
    {
      "address": "010531ce",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "010531d0",
      "instruction": "JZ 0x010531e0"
    },
    {
      "address": "010531d2",
      "instruction": "PUSH EAX"
    },
    {
      "address": "010531d3",
      "instruction": "CALL 0x00b3d3e0"
    },
    {
      "address": "010531d8",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "010531da",
      "instruction": "CALL 0x00dd6a70"
    },
    {
      "address": "010531df",
      "instruction": "RET"
    },
    {
      "address": "010531e0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "010531e1",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "010531e3",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "010531e5",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "010531e7",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "010531e9",
      "instruction": "PUSH 0x131a9f54"
    },
    {
      "address": "010531ee",
      "instruction": "PUSH 0x6e000a7a"
    },
    {
      "address": "010531f3",
      "instruction": "CALL 0x00b3d3e0"
    },
    {
      "address": "010531f8",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "010531fa",
      "instruction": "CALL 0x00dd8640"
    },
    {
      "address": "010531ff",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "01053201",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "01053205",
      "instruction": "PUSH EAX"
    },
    {
      "address": "01053206",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01053207",
      "instruction": "CALL 0x00b3d3e0"
    },
    {
      "address": "0105320c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0105320e",
      "instruction": "CALL 0x00dd6df0"
    },
    {
      "address": "01053213",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "01053217",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01053218",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01053219",
      "instruction": "CALL 0x00b3d3e0"
    },
    {
      "address": "0105321e",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01053220",
      "instruction": "CALL 0x00dd6930"
    },
    {
      "address": "01053225",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "01053229",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0105322b",
      "instruction": "JZ 0x0105323b"
    },
    {
      "address": "0105322d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0105322e",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0105322f",
      "instruction": "CALL 0x00b3d3e0"
    },
    {
      "address": "01053234",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01053236",
      "instruction": "CALL 0x00dd6b70"
    },
    {
      "address": "0105323b",
      "instruction": "POP ESI"
    },
    {
      "address": "0105323c",
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
  "body_end": "0105323c",
  "body_span_bytes": 141,
  "body_start": "010531b0",
  "callees": [
    "FUN_00dd6a70",
    "FUN_00b3d3e0",
    "FUN_00dd6930",
    "FUN_00dd6df0",
    "FUN_00dd6b70",
    "FUN_00dd8640",
    "FUN_00dd5d80"
  ],
  "callers": [
    "FUN_01058680",
    "FUN_01053320",
    "FUN_01053240",
    "FUN_010533d0",
    "FUN_010534c0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "010531b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar5",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar4",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar3",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar2",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar7",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar6",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "param_2",
      "storage": "",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "param_5",
      "storage": "Stack[0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "param_4",
      "storage": "Stack[0x10]:4",
      "type": "int"
    },
    {
      "name": "param_3",
      "storage": "",
      "type": "undefined4"
    }
  ],
  "locals_count": 12,
  "mode": "live",
  "name": "FUN_010531b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc531b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_010531b0(void)",
  "size_bytes": 141,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x010531b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "010532c2"
    },
    {
      "from": "01053305"
    },
    {
      "from": "01053461"
    },
    {
      "from": "010534a2"
    },
    {
      "from": "01053540"
    },
    {
      "from": "01053575"
    },
    {
      "from": "01058729"
    },
    {
      "from": "01058775"
    },
    {
      "from": "01053387"
    },
    {
      "from": "010533c1"
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
