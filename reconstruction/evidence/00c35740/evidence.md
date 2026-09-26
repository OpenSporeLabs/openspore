# Evidence 0x00c35740

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2e26dfd934cabda5973bdf866ff1f24bd35ba70cc709ad107e05b0328e686c77`

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
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
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
    "flow_not_modelled: the linear ESP walk ends at +36, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "e8554b6f11132ffa50df3a6fa5436a2f6190955b7e6ac4f5f0c6d2dfaf2016bf",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0031"
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
        "obs-0007"
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
        "obs-0009",
        "obs-0022",
        "obs-0023",
        "obs-0025"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          132,
          184,
          188,
          192
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0009",
        "obs-0022",
        "obs-0023",
        "obs-0025",
        "obs-0031"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0031"
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
        "obs-0031"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0031"
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
      "at": "0x00c35740",
      "count": 8,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c35741",
      "count": 4,
      "first_use": 1,
      "first_write_index": 7,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c35741",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,ECX",
      "reg": "EBX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c35743",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBX + 0xb8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c35749",
      "count": 9,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c3574a",
      "count": 3,
      "first_use": 4,
      "first_write_index": null,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x00c3574a",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0007",
      "index": 4,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0xc]",
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
"\nvoid __thiscall FUN_00c35740(int param_1,int *param_2)\n\n{\n  int *piVar1;\n  int iVar2;\n  int iVar3;\n  undefined4 *puVar4;\n  \n  if (((*(int *)(param_1 + 0xb8) != *param_2) || (*(int *)(param_1 + 0xbc) != param_2[1])) ||\n     (*(int *)(param_1 + 0xc0) != param_2[2])) {\n    *(int *)(param_1 + 0xb8) = *param_2;\n    *(int *)(param_1 + 0xbc) = param_2[1];\n    *(int *)(param_1 + 0xc0) = param_2[2];\n    piVar1 = (int *)FUN_0067cb40();\n    (**(code **)(*piVar1 + 0x58))(param_2,1);\n    FUN_00b3d300();\n    iVar2 = FUN_00b21340(&LAB_00cd7d10,&LAB_00d3d420,&LAB_00ad48b0,&LAB_00b1e500,0x18ebadc);\n    puVar4 = *(undefined4 **)(iVar2 + 4);\n    if (puVar4 != *(undefined4 **)(iVar2 + 8)) {\n      do {\n        iVar3 = (**(code **)(*(int *)*puVar4 + 0x4c))();\n        if (iVar3 == *(int *)(param_1 + 0x84)) {\n          FUN_00c37180(param_2,1);\n        }\n        puVar4 = puVar4 + 1;\n      } while (puVar4 != *(undefined4 **)(iVar2 + 8));\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 61,
  "instructions": [
    {
      "address": "00c35740",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c35741",
      "instruction": "MOV EBX,ECX"
    },
    {
      "address": "00c35743",
      "instruction": "MOV EAX,dword ptr [EBX + 0xb8]"
    },
    {
      "address": "00c35749",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c3574a",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00c3574e",
      "instruction": "CMP EAX,dword ptr [EDI]"
    },
    {
      "address": "00c35750",
      "instruction": "JNZ 0x00c3576c"
    },
    {
      "address": "00c35752",
      "instruction": "MOV ECX,dword ptr [EBX + 0xbc]"
    },
    {
      "address": "00c35758",
      "instruction": "CMP ECX,dword ptr [EDI + 0x4]"
    },
    {
      "address": "00c3575b",
      "instruction": "JNZ 0x00c3576c"
    },
    {
      "address": "00c3575d",
      "instruction": "MOV EDX,dword ptr [EBX + 0xc0]"
    },
    {
      "address": "00c35763",
      "instruction": "CMP EDX,dword ptr [EDI + 0x8]"
    },
    {
      "address": "00c35766",
      "instruction": "JZ 0x00c357fc"
    },
    {
      "address": "00c3576c",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00c3576e",
      "instruction": "MOV dword ptr [EBX + 0xb8],EAX"
    },
    {
      "address": "00c35774",
      "instruction": "MOV ECX,dword ptr [EDI + 0x4]"
    },
    {
      "address": "00c35777",
      "instruction": "MOV dword ptr [EBX + 0xbc],ECX"
    },
    {
      "address": "00c3577d",
      "instruction": "MOV EDX,dword ptr [EDI + 0x8]"
    },
    {
      "address": "00c35780",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c35781",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c35782",
      "instruction": "MOV dword ptr [EBX + 0xc0],EDX"
    },
    {
      "address": "00c35788",
      "instruction": "CALL 0x0067cb40"
    },
    {
      "address": "00c3578d",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00c3578f",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00c35791",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c35793",
      "instruction": "MOV EAX,dword ptr [EDX + 0x58]"
    },
    {
      "address": "00c35796",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c35797",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c35799",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00c3579e",
      "instruction": "PUSH 0x18ebadc"
    },
    {
      "address": "00c357a3",
      "instruction": "PUSH 0xb1e500"
    },
    {
      "address": "00c357a8",
      "instruction": "PUSH 0xad48b0"
    },
    {
      "address": "00c357ad",
      "instruction": "PUSH 0xd3d420"
    },
    {
      "address": "00c357b2",
      "instruction": "PUSH 0xcd7d10"
    },
    {
      "address": "00c357b7",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c357b9",
      "instruction": "CALL 0x00b21340"
    },
    {
      "address": "00c357be",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00c357c0",
      "instruction": "MOV EBP,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00c357c3",
      "instruction": "ADD ESI,0x4"
    },
    {
      "address": "00c357c6",
      "instruction": "CMP EBP,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00c357c9",
      "instruction": "JZ 0x00c357fa"
    },
    {
      "address": "00c357cb",
      "instruction": "JMP 0x00c357d0"
    },
    {
      "address": "00c357d0",
      "instruction": "MOV ECX,dword ptr [EBP]"
    },
    {
      "address": "00c357d3",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00c357d5",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4c]"
    },
    {
      "address": "00c357d8",
      "instruction": "MOV dword ptr [ESP + 0x14],ECX"
    },
    {
      "address": "00c357dc",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c357de",
      "instruction": "CMP EAX,dword ptr [EBX + 0x84]"
    },
    {
      "address": "00c357e4",
      "instruction": "JNZ 0x00c357f2"
    },
    {
      "address": "00c357e6",
      "instruction": "MOV ECX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00c357ea",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00c357ec",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c357ed",
      "instruction": "CALL 0x00c37180"
    },
    {
      "address": "00c357f2",
      "instruction": "ADD EBP,0x4"
    },
    {
      "address": "00c357f5",
      "instruction": "CMP EBP,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00c357f8",
      "instruction": "JNZ 0x00c357d0"
    },
    {
      "address": "00c357fa",
      "instruction": "POP ESI"
    },
    {
      "address": "00c357fb",
      "instruction": "POP EBP"
    },
    {
      "address": "00c357fc",
      "instruction": "POP EDI"
    },
    {
      "address": "00c357fd",
      "instruction": "POP EBX"
    },
    {
      "address": "00c357fe",
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
  "body_end": "00c35800",
  "body_span_bytes": 193,
  "body_start": "00c35740",
  "callees": [
    "FUN_00c37180",
    "FUN_00b3d300",
    "FUN_00b21340",
    "FUN_0067cb40"
  ],
  "callers": [
    "FUN_00c37180",
    "FUN_00d09560",
    "FUN_00ffc160"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c35740",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "puVar4",
      "storage": "register:00000014:4",
      "type": "undefined4 *"
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
    },
    {
      "name": "piVar1",
      "storage": "register:00000000:4",
      "type": "int *"
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "FUN_00c35740",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x835740",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c35740(void)",
  "size_bytes": 193,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c35740",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00c371e5"
    },
    {
      "from": "00d0957a"
    },
    {
      "from": "00ffc178"
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
