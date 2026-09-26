# Evidence 0x00c70380

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `bfbc4b7f64e82bec3efadf4f1e0ce3909b1ae1bf5d04118f95355326a689c759`

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
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
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
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "5b87e9d14325fc5768157aa9544002403dc9900882bc13e8115c8ff8c0eb26f6",
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
        "obs-0032"
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
        "obs-0016",
        "obs-0022",
        "obs-0024"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0016",
        "obs-0022",
        "obs-0024"
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
        "obs-0003",
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0016",
        "obs-0022",
        "obs-0024"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0016"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0032"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0032"
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
      "at": "0x00c70380",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
   
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
"\nvoid FUN_00c70380(int param_1,int *param_2,int *param_3)\n\n{\n  int iVar1;\n  int *piVar2;\n  int iVar3;\n  int iVar4;\n  int iVar5;\n  int local_8;\n  \n  iVar1 = *(int *)(param_1 + 0x160) - *(int *)(param_1 + 0x15c) >> 2;\n  local_8 = 0;\n  if (0 < iVar1) {\n    do {\n      piVar2 = (int *)FUN_005c65e0();\n      iVar4 = 0;\n      iVar5 = piVar2[1] - *piVar2 >> 2;\n      if (0 < iVar5) {\n        do {\n          iVar3 = FUN_00ff0870();\n          *param_2 = *param_2 + iVar3;\n          iVar3 = FUN_00ff0760();\n          *param_3 = *param_3 + iVar3;\n          iVar4 = iVar4 + 1;\n        } while (iVar4 < iVar5);\n      }\n      local_8 = local_8 + 1;\n    } while (local_8 < iVar1);\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 53,
  "instructions": [
    {
      "address": "00c70380",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00c70383",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00c70387",
      "instruction": "MOV EAX,dword ptr [ECX + 0x160]"
    },
    {
      "address": "00c7038d",
      "instruction": "SUB EAX,dword ptr [ECX + 0x15c]"
    },
    {
      "address": "00c70393",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c70394",
      "instruction": "SAR EAX,0x2"
    },
    {
      "address": "00c70397",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "00c70399",
      "instruction": "MOV dword ptr [ESP + 0x4],EBP"
    },
    {
      "address": "00c7039d",
      "instruction": "MOV dword ptr [ESP + 0x8],EAX"
    },
    {
      "address": "00c703a1",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c703a3",
      "instruction": "JLE 0x00c70414"
    },
    {
      "address": "00c703a5",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c703a6",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c703a7",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c703a8",
      "instruction": "JMP 0x00c703b4"
    },
    {
      "address": "00c703b0",
      "instruction": "MOV ECX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00c703b4",
      "instruction": "MOV EAX,dword ptr [ECX + 0x15c]"
    },
    {
      "address": "00c703ba",
      "instruction": "MOV ECX,dword ptr [EAX + EBP*0x4]"
    },
    {
      "address": "00c703bd",
      "instruction": "CALL 0x005c65e0"
    },
    {
      "address": "00c703c2",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00c703c4",
      "instruction": "MOV EDI,dword ptr [EBX + 0x4]"
    },
    {
      "address": "00c703c7",
      "instruction": "SUB EDI,dword ptr [EBX]"
    },
    {
      "address": "00c703c9",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00c703cb",
      "instruction": "SAR EDI,0x2"
    },
    {
      "address": "00c703ce",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00c703d0",
      "instruction": "JLE 0x00c70406"
    },
    {
      "address": "00c703d2",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "00c703d4",
      "instruction": "LEA EBP,[ESI*0x4 + 0x0]"
    },
    {
      "address": "00c703db",
      "instruction": "MOV ECX,dword ptr [EAX + EBP*0x1]"
    },
    {
      "address": "00c703de",
      "instruction": "ADD EAX,EBP"
    },
    {
      "address": "00c703e0",
      "instruction": "CALL 0x00ff0870"
    },
    {
      "address": "00c703e5",
      "instruction": "MOV ECX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00c703e9",
      "instruction": "ADD dword ptr [ECX],EAX"
    },
    {
      "address": "00c703eb",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "00c703ed",
      "instruction": "MOV ECX,dword ptr [EAX + EBP*0x1]"
    },
    {
      "address": "00c703f0",
      "instruction": "ADD EAX,EBP"
    },
    {
      "address": "00c703f2",
      "instruction": "CALL 0x00ff0760"
    },
    {
      "address": "00c703f7",
      "instruction": "MOV ECX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00c703fb",
      "instruction": "ADD dword ptr [ECX],EAX"
    },
    {
      "address": "00c703fd",
      "instruction": "INC ESI"
    },
    {
      "address": "00c703fe",
      "instruction": "CMP ESI,EDI"
    },
    {
      "address": "00c70400",
      "instruction": "JL 0x00c703d2"
    },
    {
      "address": "00c70402",
      "instruction": "MOV EBP,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c70406",
      "instruction": "INC EBP"
    },
    {
      "address": "00c70407",
      "instruction": "CMP EBP,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00c7040b",
      "instruction": "MOV dword ptr [ESP + 0x10],EBP"
    },
    {
      "address": "00c7040f",
      "instruction": "JL 0x00c703b0"
    },
    {
      "address": "00c70411",
      "instruction": "POP EDI"
    },
    {
      "address": "00c70412",
      "instruction": "POP ESI"
    },
    {
      "address": "00c70413",
      "instruction": "POP EBX"
    },
    {
      "address": "00c70414",
      "instruction": "POP EBP"
    },
    {
      "address": "00c70415",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00c70418",
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
  "body_end": "00c70418",
  "body_span_bytes": 153,
  "body_start": "00c70380",
  "callees": [
    "FUN_005c65e0",
    "FUN_00ff0760",
    "FUN_00ff0870"
  ],
  "callers": [
    "FUN_00bba990",
    "FUN_01030650",
    "FUN_00fde3e0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c70380",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_3",
      "storage": "Stack[0xc]:4",
      "type": "int *"
    },
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "int *"
    },
    {
      "name": "iVar4",
      "storage": "register:00000018:4",
      "type": "int"
    },
    {
      "name": "iVar5",
      "storage": "register:0000001c:4",
      "type": "int"
    },
    {
      "name": "piVar2",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    }
  ],
  "locals_count": 9,
  "mode": "live",
  "name": "FUN_00c70380",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x870380",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c70380(void)",
  "size_bytes": 153,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c70380",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00bbaa06"
    },
    {
      "from": "01030676"
    },
    {
      "from": "00fde9b7"
    },
    {
      "from": "01025af2"
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
