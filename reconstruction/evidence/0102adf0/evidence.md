# Evidence 0x0102adf0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2fcf7b28e0c33a406f2b82819673854704a872151e3bbd041fc0ea6d3fa2fc21`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__cdecl",
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -16, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "706d2fa81124f48e0fd0cf7a76a405991d2354c7fe18a2ea3dd641f0e3b7ff10",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__cdecl",
    "candidate_conventions": [
      "__cdecl",
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
        "obs-0029"
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
        "obs-0020"
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
        "obs-0034"
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
        "obs-0020",
        "obs-0029"
      ],
      "claim": "calling convention is __cdecl: the caller cleans the stack and at least one entry slot is read",
      "confidence": "INFERRED",
      "id": "C9",
      "value": "__cdecl"
    },
    {
      "based_on": [
        "obs-0029"
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
        "obs-0029",
        "obs-0034"
      ],
      "claim": "the function can reach a caller by transferring out of the listing, so the path that actually returns was never observed",
      "confidence": "UNKNOWN",
      "id": "T2",
      "value": {
        "form": "epilogue_then_jmp"
      }
    },
    {
      "based_on": [
        "obs-0029"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0029"
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
      "at": "0x0102adf0",
      "count": 3,
      "first_use": 0,
      "first_write_index": 10,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x0102adf1",
      "count": 4,
      "first_use": 1,
      "first_write_index": 7,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x0102adf1",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x0102adf2",
      "count": 7,
      "first_use": 2,
      "first_write_index": 15,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x0102adf3",
      "count": 2,
      "first_use": 3,
      "first_write_index": 8,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x0102adf4",
      "id": "obs-0006",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00feb9f0",
      "target": "0x00feb9f0"
    },
    {
      "at": "0x0102adf9",
      "count": 6,
      "first_use": 5,
      "first_write_index": 14,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV E
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
"\nuint FUN_0102adf0(int *param_1)\n\n{\n  int *piVar1;\n  int *piVar2;\n  int *piVar3;\n  int iVar4;\n  uint uVar5;\n  int iVar6;\n  int iVar7;\n  \n  FUN_00feb9f0();\n  piVar2 = (int *)FUN_00fedd50();\n  iVar6 = 0;\n  iVar7 = piVar2[1] - *piVar2 >> 2;\n  piVar3 = piVar2;\n  if (0 < iVar7) {\n    do {\n      piVar1 = *(int **)(*piVar2 + iVar6 * 4);\n      piVar3 = (int *)FUN_00970b30();\n      if (piVar3 == param_1) {\n        iVar4 = (**(code **)(*piVar1 + 0x38))();\n        if (iVar4 == 0x397bff2) {\nLAB_0102ae50:\n          uVar5 = FUN_00c44c80();\n          return uVar5;\n        }\n        piVar3 = (int *)(**(code **)(*piVar1 + 0x38))();\n        if (piVar3 == (int *)0x3960c0a) goto LAB_0102ae50;\n      }\n      iVar6 = iVar6 + 1;\n    } while (iVar6 < iVar7);\n  }\n  return (uint)piVar3 & 0xffffff00;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 47,
  "instructions": [
    {
      "address": "0102adf0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0102adf1",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0102adf2",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0102adf3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0102adf4",
      "instruction": "CALL 0x00feb9f0"
    },
    {
      "address": "0102adf9",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0102adfb",
      "instruction": "CALL 0x00fedd50"
    },
    {
      "address": "0102ae00",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "0102ae02",
      "instruction": "MOV EDI,dword ptr [EBP + 0x4]"
    },
    {
      "address": "0102ae05",
      "instruction": "SUB EDI,dword ptr [EBP]"
    },
    {
      "address": "0102ae08",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "0102ae0a",
      "instruction": "SAR EDI,0x2"
    },
    {
      "address": "0102ae0d",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "0102ae0f",
      "instruction": "JLE 0x0102ae49"
    },
    {
      "address": "0102ae11",
      "instruction": "MOV EAX,dword ptr [EBP]"
    },
    {
      "address": "0102ae14",
      "instruction": "MOV ESI,dword ptr [EAX + EBX*0x4]"
    },
    {
      "address": "0102ae17",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0102ae19",
      "instruction": "CALL 0x00970b30"
    },
    {
      "address": "0102ae1e",
      "instruction": "CMP EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "0102ae22",
      "instruction": "JNZ 0x0102ae44"
    },
    {
      "address": "0102ae24",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "0102ae26",
      "instruction": "MOV EAX,dword ptr [EDX + 0x38]"
    },
    {
      "address": "0102ae29",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0102ae2b",
      "instruction": "CALL EAX"
    },
    {
      "address": "0102ae2d",
      "instruction": "CMP EAX,0x397bff2"
    },
    {
      "address": "0102ae32",
      "instruction": "JZ 0x0102ae50"
    },
    {
      "address": "0102ae34",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "0102ae36",
      "instruction": "MOV EAX,dword ptr [EDX + 0x38]"
    },
    {
      "address": "0102ae39",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0102ae3b",
      "instruction": "CALL EAX"
    },
    {
      "address": "0102ae3d",
      "instruction": "CMP EAX,0x3960c0a"
    },
    {
      "address": "0102ae42",
      "instruction": "JZ 0x0102ae50"
    },
    {
      "address": "0102ae44",
      "instruction": "INC EBX"
    },
    {
      "address": "0102ae45",
      "instruction": "CMP EBX,EDI"
    },
    {
      "address": "0102ae47",
      "instruction": "JL 0x0102ae11"
    },
    {
      "address": "0102ae49",
      "instruction": "POP EDI"
    },
    {
      "address": "0102ae4a",
      "instruction": "POP ESI"
    },
    {
      "address": "0102ae4b",
      "instruction": "POP EBP"
    },
    {
      "address": "0102ae4c",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "0102ae4e",
      "instruction": "POP EBX"
    },
    {
      "address": "0102ae4f",
      "instruction": "RET"
    },
    {
      "address": "0102ae50",
      "instruction": "POP EDI"
    },
    {
      "address": "0102ae51",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0102ae53",
      "instruction": "POP ESI"
    },
    {
      "address": "0102ae54",
      "instruction": "POP EBP"
    },
    {
      "address": "0102ae55",
      "instruction": "POP EBX"
    },
    {
      "address": "0102ae56",
      "instruction": "JMP 0x00c44c80"
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
  "body_end": "0102ae5a",
  "body_span_bytes": 107,
  "body_start": "0102adf0",
  "callees": [
    "FUN_00970b30",
    "FUN_00c44c80",
    "FUN_00fedd50",
    "FUN_00feb9f0"
  ],
  "callers": [
    "FUN_0101d130",
    "FUN_00ffb270",
    "FUN_00c38270",
    "FUN_01000000",
    "FUN_00ffaf20"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0102adf0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "piVar3",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "iVar4",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "piVar1",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "piVar2",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "iVar7",
      "storage": "register:0000001c:4",
      "type": "int"
    },
    {
      "name": "uVar5",
      "storage": "register:00000000:4",
      "type": "uint"
    },
    {
      "name": "iVar6",
      "storage": "register:0000000c:4",
      "type": "int"
    }
  ],
  "locals_count": 8,
  "mode": "live",
  "name": "FUN_0102adf0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc2adf0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0102adf0(void)",
  "size_bytes": 107,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0102adf0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "01000034"
    },
    {
      "from": "00c382c6"
    },
    {
      "from": "00ffaf59"
    },
    {
      "from": "00ffb2d1"
    },
    {
      "from": "0101d375"
    },
    {
      "from": "01066b93"
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
