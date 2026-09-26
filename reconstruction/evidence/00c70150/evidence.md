# Evidence 0x00c70150

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f83cbf2d0becf9649612354dbcaa356b37e2c658eaa55f3089a34e7a8f80a70b`

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
      "entry_ESP+0xc",
      "entry_ESP+0x10",
      "entry_ESP+0x14"
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
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
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
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -28, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "39a619ae7fa31f832c52ff28b3120c412912a122250718710bffbe2439e37f7c",
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
        "obs-0012",
        "obs-0044",
        "obs-0050"
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
        "obs-0019",
        "obs-0020",
        "obs-0021",
        "obs-0027",
        "obs-0032",
        "obs-0033"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 4,
        "total_bytes": 20
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0006",
        "obs-0011",
        "obs-0021",
        "obs-0022",
        "obs-0030",
        "obs-0043",
        "obs-0049"
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
        "obs-0006",
        "obs-0011",
        "obs-0021",
        "obs-0022",
        "obs-0030",
        "obs-0043",
        "obs-0049"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0012",
        "obs-0044",
        "obs-0050"
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
        "obs-0012",
        "obs-0044",
        "obs-0050"
    
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
"\nundefined4 FUN_00c70150(int param_1,int param_2,char param_3)\n\n{\n  char cVar1;\n  int iVar2;\n  int iVar3;\n  int *piVar4;\n  int iVar5;\n  int iVar6;\n  int local_4;\n  \n  iVar2 = FUN_00b8dab0();\n  if (iVar2 != 5) {\n    return 0;\n  }\n  iVar2 = *(int *)(param_1 + 0x160) - *(int *)(param_1 + 0x15c) >> 2;\n  local_4 = 0;\n  if (0 < iVar2) {\n    do {\n      iVar6 = *(int *)(param_2 + 0x84);\n      iVar3 = FUN_00ff0420();\n      if (iVar3 == iVar6) {\n        piVar4 = (int *)FUN_005c65e0();\n        iVar3 = 0;\n        iVar6 = piVar4[1] - *piVar4 >> 2;\n        if (0 < iVar6) {\n          do {\n            if (param_3 == '\\0') {\n              return 1;\n            }\n            iVar5 = FUN_00ff0870();\n            if (1 < iVar5) {\n              return 1;\n            }\n            iVar3 = iVar3 + 1;\n          } while (iVar3 < iVar6);\n        }\n      }\n      local_4 = local_4 + 1;\n    } while (local_4 < iVar2);\n  }\n  iVar2 = FUN_01021080();\n  if (iVar2 == 0) {\n    if (DAT_0167a60c == 0) {\n      iVar2 = FUN_00f473a0(200,\"Simulator/SimSingleton\",0,0,0,0);\n      if (iVar2 == 0) {\n        DAT_0167a60c = 0;\n      }\n      else {\n        DAT_0167a60c = FUN_00ae5c30();\n      }\n    }\n    cVar1 = FUN_00ae3740();\n    if (cVar1 != '\\0') {\n      return 1;\n    }\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 96,
  "instructions": [
    {
      "address": "00c70150",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c70151",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c70152",
      "instruction": "MOV ESI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00c70156",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c70158",
      "instruction": "CALL 0x00b8dab0"
    },
    {
      "address": "00c7015d",
      "instruction": "CMP EAX,0x5"
    },
    {
      "address": "00c70160",
      "instruction": "JZ 0x00c70167"
    },
    {
      "address": "00c70162",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00c70164",
      "instruction": "POP ESI"
    },
    {
      "address": "00c70165",
      "instruction": "POP ECX"
    },
    {
      "address": "00c70166",
      "instruction": "RET"
    },
    {
      "address": "00c70167",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c70168",
      "instruction": "MOV EBX,dword ptr [ESI + 0x160]"
    },
    {
      "address": "00c7016e",
      "instruction": "SUB EBX,dword ptr [ESI + 0x15c]"
    },
    {
      "address": "00c70174",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c70175",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "00c70177",
      "instruction": "SAR EBX,0x2"
    },
    {
      "address": "00c7017a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c7017b",
      "instruction": "MOV dword ptr [ESP + 0x10],EBP"
    },
    {
      "address": "00c7017f",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00c70181",
      "instruction": "JLE 0x00c701fc"
    },
    {
      "address": "00c70183",
      "instruction": "JMP 0x00c70194"
    },
    {
      "address": "00c70190",
      "instruction": "MOV ESI,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00c70194",
      "instruction": "MOV EAX,dword ptr [ESI + 0x15c]"
    },
    {
      "address": "00c7019a",
      "instruction": "MOV ECX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00c7019e",
      "instruction": "MOV ESI,dword ptr [EAX + EBP*0x4]"
    },
    {
      "address": "00c701a1",
      "instruction": "MOV EDI,dword ptr [ECX + 0x84]"
    },
    {
      "address": "00c701a7",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c701a9",
      "instruction": "CALL 0x00ff0420"
    },
    {
      "address": "00c701ae",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00c701b0",
      "instruction": "JNZ 0x00c701f3"
    },
    {
      "address": "00c701b2",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c701b4",
      "instruction": "CALL 0x005c65e0"
    },
    {
      "address": "00c701b9",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "00c701bb",
      "instruction": "MOV ESI,dword ptr [EBP + 0x4]"
    },
    {
      "address": "00c701be",
      "instruction": "SUB ESI,dword ptr [EBP]"
    },
    {
      "address": "00c701c1",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00c701c3",
      "instruction": "SAR ESI,0x2"
    },
    {
      "address": "00c701c6",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c701c8",
      "instruction": "JLE 0x00c701ef"
    },
    {
      "address": "00c701ca",
      "instruction": "LEA EBX,[EBX]"
    },
    {
      "address": "00c701d0",
      "instruction": "CMP byte ptr [ESP + 0x20],0x0"
    },
    {
      "address": "00c701d5",
      "instruction": "JZ 0x00c70243"
    },
    {
      "address": "00c701d7",
      "instruction": "MOV EDX,dword ptr [EBP]"
    },
    {
      "address": "00c701da",
      "instruction": "MOV ECX,dword ptr [EDX + EDI*0x4]"
    },
    {
      "address": "00c701dd",
      "instruction": "LEA EAX,[EDX + EDI*0x4]"
    },
    {
      "address": "00c701e0",
      "instruction": "CALL 0x00ff0870"
    },
    {
      "address": "00c701e5",
      "instruction": "CMP EAX,0x1"
    },
    {
      "address": "00c701e8",
      "instruction": "JG 0x00c70243"
    },
    {
      "address": "00c701ea",
      "instruction": "INC EDI"
    },
    {
      "address": "00c701eb",
      "instruction": "CMP EDI,ESI"
    },
    {
      "address": "00c701ed",
      "instruction": "JL 0x00c701d0"
    },
    {
      "address": "00c701ef",
      "instruction": "MOV EBP,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c701f3",
      "instruction": "INC EBP"
    },
    {
      "address": "00c701f4",
      "instruction": "CMP EBP,EBX"
    },
    {
      "address": "00c701f6",
      "instruction": "MOV dword ptr [ESP + 0x10],EBP"
    },
    {
      "address": "00c701fa",
      "instruction": "JL 0x00c70190"
    },
    {
      "address": "00c701fc",
      "instruction": "CALL 0x01021080"
    },
    {
      "address": "00c70201",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c70203",
      "instruction": "JNZ 0x00c7024b"
    },
    {
      "address": "00c70205",
      "instruction": "MOV EAX,[0x0167a60c]"
    },
    {
      "address": "00c7020a",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c7020c",
      "instruction": "JNZ 0x00c70238"
    },
    {
      "address": "00c7020e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c7020f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c70210",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c70211",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c70212",
      "instruction": "PUSH 0x145f924"
    },
    {
      "address": "00c70217",
      "instruction": "PUSH 0xc8"
    },
    {
      "address": "00c7021c",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "00c70221",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "00c70224",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c70226",
      "instruction": "JZ 0x00c70231"
    },
    {
      "ad
[TRUNCATED]
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
  "body_end": "00c70252",
  "body_span_bytes": 259,
  "body_start": "00c70150",
  "callees": [
    "FUN_00ae5c30",
    "FUN_00f473a0",
    "FUN_00ae3740",
    "FUN_00ff0420",
    "FUN_01021080",
    "FUN_005c65e0",
    "FUN_00b8dab0",
    "FUN_00ff0870"
  ],
  "callers": [
    "FUN_01068970",
    "FUN_00c34ee0",
    "FUN_00c344f0",
    "FUN_00c308e0",
    "FUN_00c59540",
    "FUN_00c35810",
    "FUN_00c70b20",
    "FUN_00c62ff0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c70150",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar6",
      "storage": "register:00000018:4",
      "type": "int"
    },
    {
      "name": "piVar4",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "iVar5",
      "storage": "register:00000000:4",
      "type": "int"
    },
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
      "name": "param_3",
      "storage": "Stack[0xc]:1",
      "type": "char"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "int"
    }
  ],
  "locals_count": 10,
  "mode": "live",
  "name": "FUN_00c70150",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x870150",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c70150(void)",
  "size_bytes": 259,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c70150",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "00c35887"
    },
    {
      "from": "00c35144"
    },
    {
      "from": "00c70b3a"
    },
    {
      "from": "00c308ec"
    },
    {
      "from": "00c34568"
    },
    {
      "from": "00c59711"
    },
    {
      "from": "01068b6a"
    },
    {
      "from": "00c630b7"
    },
    {
      "from": "00c61a34"
    },
    {
      "from": "00c61b5a"
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
