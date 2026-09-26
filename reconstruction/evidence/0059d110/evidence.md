# Evidence 0x0059d110

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `3786a3011fb68f28afac40718cea8c818514676942c0a5542ea58861cea16ca9`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "72391d5096609bcb40360a0f8682ec16bf69bb6ebe0680e41e905c2c2aa27dd8",
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
        "obs-0022",
        "obs-0026"
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
        "obs-0003",
        "obs-0009",
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
        "obs-0001",
        "obs-0007",
        "obs-0010",
        "obs-0013",
        "obs-0018",
        "obs-0021",
        "obs-0025"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          56
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0007",
        "obs-0010",
        "obs-0013",
        "obs-0018",
        "obs-0021",
        "obs-0022",
        "obs-0025",
        "obs-0026"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0022",
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
        "obs-0022",
        "obs-0026"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0022",
        "obs-0026"
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
      "at": "0x0059d110",
      "count": 8,
      "first_use": 0,
      "first_write_index": 13,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0059d111",
      "count": 6,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x0059d111",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x0059d111",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0059d115",
      "count": 4,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0059d116",
      "count": 3,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x0059d117",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,ECX",
      "reg": "EDI",
      "write_kind": "reg"
    },
    {
      "at": "0x0059d11d",
      "count": 9,
      "first_use": 6,
      "first_write_index": 1,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ESP + 0x10],EAX",
      "reg": "EAX"
    },
    {
  
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
"\nuint __thiscall FUN_0059d110(int param_1,int *param_2,undefined4 *param_3)\n\n{\n  int iVar1;\n  undefined4 uVar2;\n  int *piVar3;\n  int local_4;\n  \n  piVar3 = param_2;\n  if (*(int *)(param_1 + 0x38) != 0) {\n    local_4 = param_1;\n    piVar3 = (int *)map_int_whatever_find(&local_4,&param_2);\n    if (*piVar3 != param_1 + 0xc) {\n      piVar3 = (int *)map_int_EditorCreatureControllerPtr__get(&param_2);\n      iVar1 = *(int *)(*piVar3 + 8);\n      piVar3 = (int *)0x0;\n      if (iVar1 != 0) {\n        *param_3 = *(undefined4 *)(iVar1 + 4);\n        param_3[1] = *(undefined4 *)(iVar1 + 8);\n        uVar2 = *(undefined4 *)(iVar1 + 0xc);\n        param_3[2] = uVar2;\n        return CONCAT31((int3)((uint)uVar2 >> 8),1);\n      }\n    }\n  }\n  return (uint)piVar3 & 0xffffff00;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 43,
  "instructions": [
    {
      "address": "0059d110",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0059d111",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0059d115",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0059d116",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0059d117",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "0059d119",
      "instruction": "CMP dword ptr [EDI + 0x38],0x0"
    },
    {
      "address": "0059d11d",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "0059d121",
      "instruction": "JZ 0x0059d170"
    },
    {
      "address": "0059d123",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "0059d127",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0059d128",
      "instruction": "LEA EDX,[ESP + 0xc]"
    },
    {
      "address": "0059d12c",
      "instruction": "LEA ESI,[EDI + 0x8]"
    },
    {
      "address": "0059d12f",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0059d130",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0059d132",
      "instruction": "CALL 0x00e5c780"
    },
    {
      "address": "0059d137",
      "instruction": "ADD EDI,0xc"
    },
    {
      "address": "0059d13a",
      "instruction": "CMP dword ptr [EAX],EDI"
    },
    {
      "address": "0059d13c",
      "instruction": "JZ 0x0059d170"
    },
    {
      "address": "0059d13e",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "0059d142",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0059d143",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0059d145",
      "instruction": "CALL 0x0059c740"
    },
    {
      "address": "0059d14a",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "0059d14c",
      "instruction": "MOV EAX,dword ptr [ECX + 0x8]"
    },
    {
      "address": "0059d14f",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0059d151",
      "instruction": "JZ 0x0059d170"
    },
    {
      "address": "0059d153",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0059d156",
      "instruction": "MOV ECX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "0059d15a",
      "instruction": "MOV dword ptr [ECX],EDX"
    },
    {
      "address": "0059d15c",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "0059d15f",
      "instruction": "MOV dword ptr [ECX + 0x4],EDX"
    },
    {
      "address": "0059d162",
      "instruction": "MOV EAX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "0059d165",
      "instruction": "POP EDI"
    },
    {
      "address": "0059d166",
      "instruction": "MOV dword ptr [ECX + 0x8],EAX"
    },
    {
      "address": "0059d169",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "0059d16b",
      "instruction": "POP ESI"
    },
    {
      "address": "0059d16c",
      "instruction": "POP ECX"
    },
    {
      "address": "0059d16d",
      "instruction": "RET 0x8"
    },
    {
      "address": "0059d170",
      "instruction": "POP EDI"
    },
    {
      "address": "0059d171",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "0059d173",
      "instruction": "POP ESI"
    },
    {
      "address": "0059d174",
      "instruction": "POP ECX"
    },
    {
      "address": "0059d175",
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
  "body_end": "0059d177",
  "body_span_bytes": 104,
  "body_start": "0059d110",
  "callees": [
    "map_int_EditorCreatureControllerPtr__get",
    "map_int_whatever_find"
  ],
  "callers": [
    "FUN_00582d70",
    "Editors::cEditor::Update",
    "Editors::cEditor::AddCreature",
    "FUN_00583900",
    "FUN_00628f10",
    "FUN_00577e10",
    "FUN_00629590",
    "FUN_0062abd0",
    "FUN_00639350"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0059d110",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "undefined4 *"
    },
    {
      "name": "iVar1",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "uVar2",
      "storage": "unique:00017200:4",
      "type": "undefined4"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "int"
    },
    {
      "name": "piVar3",
      "storage": "register:00000000:4",
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
      "type": "int *"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_0059d110",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x19d110",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0059d110(void)",
  "size_bytes": 104,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0059d110",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 18,
  "xrefs": [
    {
      "from": "005833b4"
    },
    {
      "from": "00582df5"
    },
    {
      "from": "00582eb0"
    },
    {
      "from": "00582f22"
    },
    {
      "from": "00628f51"
    },
    {
      "from": "00628f5e"
    },
    {
      "from": "00629655"
    },
    {
      "from": "00629662"
    },
    {
      "from": "0062ac1d"
    },
    {
      "from": "006394ac"
    },
    {
      "from": "005839ce"
    },
    {
      "from": "0058cb89"
    },
    {
      "from": "0058cdf2"
    },
    {
      "from": "00577fce"
    },
    {
      "from": "00578b2d"
    },
    {
      "from": "00578d79"
    },
    {
      "from": "00578d9c"
    },
    {
      "from": "0063a9ec"
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
