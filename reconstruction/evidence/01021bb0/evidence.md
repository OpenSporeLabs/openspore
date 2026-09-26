# Evidence 0x01021bb0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `49a3343320d4ee0f709df3483e73fb92fb6937d954aff57012d4ba4f20ecd41c`

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
      "entry_ESP+0xc",
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x18"
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
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
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
    "return_semantics": "pointer_like_in_EAX",
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
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x18",
        "observed": true,
        "ordinal": 6,
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
  "content_sha256": "74832e690c9b7a7e9a5f4bbdbe367cab096d6320728d7081a282bb8110e73729",
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
    "indirect_calls": 7,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0049"
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
        "obs-0005",
        "obs-0009",
        "obs-0011",
        "obs-0017",
        "obs-0022",
        "obs-0026",
        "obs-0028",
        "obs-0029",
        "obs-0031",
        "obs-0033",
        "obs-0034",
        "obs-0035",
        "obs-0037",
        "obs-0039"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 6,
        "total_bytes": 24
      }
    },
    {
      "based_on": [
        "obs-0014",
        "obs-0016",
        "obs-0022",
        "obs-0026",
        "obs-0029",
        "obs-0031",
        "obs-0034",
     
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
"\nvoid FUN_01021bb0(int param_1,undefined4 param_2,int param_3,int param_4,int *param_5,code *param_6)\n\n{\n  int *piVar1;\n  int *piVar2;\n  int iVar3;\n  int iVar4;\n  int iVar5;\n  \n  while( true ) {\n    iVar5 = param_4;\n    iVar3 = iVar5 * 2;\n    param_4 = iVar3 + 2;\n    if (param_3 <= param_4) break;\n    iVar4 = (*param_6)(*(undefined4 *)(param_1 + param_4 * 4),\n                       *(undefined4 *)(param_1 + -4 + param_4 * 4));\n    if (iVar4 != 0) {\n      param_4 = iVar3 + 1;\n    }\n    piVar1 = *(int **)(param_1 + iVar5 * 4);\n    piVar2 = *(int **)(param_1 + param_4 * 4);\n    if (piVar2 != piVar1) {\n      if (piVar2 != (int *)0x0) {\n        (**(code **)(*piVar2 + 0xbc))();\n      }\n      *(int **)(param_1 + iVar5 * 4) = piVar2;\n      if (piVar1 != (int *)0x0) {\n        (**(code **)(*piVar1 + 0xc0))();\n      }\n    }\n  }\n  if (param_4 == param_3) {\n    piVar1 = *(int **)(param_1 + iVar5 * 4);\n    piVar2 = *(int **)(param_1 + -4 + param_4 * 4);\n    if (piVar2 != piVar1) {\n      if (piVar2 != (int *)0x0) {\n        (**(code **)(*piVar2 + 0xbc))();\n      }\n      *(int **)(param_1 + iVar5 * 4) = piVar2;\n      if (piVar1 != (int *)0x0) {\n        (**(code **)(*piVar1 + 0xc0))();\n      }\n    }\n    iVar5 = iVar3 + 1;\n  }\n  if (param_5 != (int *)0x0) {\n    (**(code **)(*param_5 + 0xbc))(param_5,param_6);\n  }\n  FUN_010215e0(param_1,param_2,iVar5);\n  if (param_5 != (int *)0x0) {\n                    /* WARNING: Could not recover jumptable at 0x01021c96. Too many branches */\n                    /* WARNING: Treating indirect jump as call */\n    (**(code **)(*param_5 + 0xc0))();\n    return;\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 93,
  "instructions": [
    {
      "address": "01021bb0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "01021bb1",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01021bb2",
      "instruction": "MOV EBP,dword ptr [ESP + 0x18]"
    },
    {
      "address": "01021bb6",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01021bb7",
      "instruction": "LEA ESI,[EBP + EBP*0x1 + 0x2]"
    },
    {
      "address": "01021bbb",
      "instruction": "CMP ESI,dword ptr [ESP + 0x18]"
    },
    {
      "address": "01021bbf",
      "instruction": "PUSH EDI"
    },
    {
      "address": "01021bc0",
      "instruction": "MOV EDI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "01021bc4",
      "instruction": "JGE 0x01021c1a"
    },
    {
      "address": "01021bc6",
      "instruction": "MOV EAX,dword ptr [EDI + ESI*0x4 + -0x4]"
    },
    {
      "address": "01021bca",
      "instruction": "MOV ECX,dword ptr [EDI + ESI*0x4]"
    },
    {
      "address": "01021bcd",
      "instruction": "PUSH EAX"
    },
    {
      "address": "01021bce",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01021bcf",
      "instruction": "CALL dword ptr [ESP + 0x30]"
    },
    {
      "address": "01021bd3",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "01021bd6",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "01021bd8",
      "instruction": "JZ 0x01021bdb"
    },
    {
      "address": "01021bda",
      "instruction": "DEC ESI"
    },
    {
      "address": "01021bdb",
      "instruction": "MOV ECX,dword ptr [EDI + EBP*0x4]"
    },
    {
      "address": "01021bde",
      "instruction": "MOV EBX,dword ptr [EDI + ESI*0x4]"
    },
    {
      "address": "01021be1",
      "instruction": "MOV dword ptr [ESP + 0x20],ECX"
    },
    {
      "address": "01021be5",
      "instruction": "CMP EBX,ECX"
    },
    {
      "address": "01021be7",
      "instruction": "JZ 0x01021c0e"
    },
    {
      "address": "01021be9",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "01021beb",
      "instruction": "JZ 0x01021bfd"
    },
    {
      "address": "01021bed",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "01021bef",
      "instruction": "MOV EDX,dword ptr [EAX + 0xbc]"
    },
    {
      "address": "01021bf5",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "01021bf7",
      "instruction": "CALL EDX"
    },
    {
      "address": "01021bf9",
      "instruction": "MOV ECX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "01021bfd",
      "instruction": "MOV dword ptr [EDI + EBP*0x4],EBX"
    },
    {
      "address": "01021c00",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01021c02",
      "instruction": "JZ 0x01021c0e"
    },
    {
      "address": "01021c04",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01021c06",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc0]"
    },
    {
      "address": "01021c0c",
      "instruction": "CALL EDX"
    },
    {
      "address": "01021c0e",
      "instruction": "MOV EBP,ESI"
    },
    {
      "address": "01021c10",
      "instruction": "LEA ESI,[ESI + ESI*0x1 + 0x2]"
    },
    {
      "address": "01021c14",
      "instruction": "CMP ESI,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "01021c18",
      "instruction": "JL 0x01021bc6"
    },
    {
      "address": "01021c1a",
      "instruction": "JNZ 0x01021c53"
    },
    {
      "address": "01021c1c",
      "instruction": "MOV ECX,dword ptr [EDI + EBP*0x4]"
    },
    {
      "address": "01021c1f",
      "instruction": "MOV EBX,dword ptr [EDI + ESI*0x4 + -0x4]"
    },
    {
      "address": "01021c23",
      "instruction": "MOV dword ptr [ESP + 0x1c],ECX"
    },
    {
      "address": "01021c27",
      "instruction": "CMP EBX,ECX"
    },
    {
      "address": "01021c29",
      "instruction": "JZ 0x01021c50"
    },
    {
      "address": "01021c2b",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "01021c2d",
      "instruction": "JZ 0x01021c3f"
    },
    {
      "address": "01021c2f",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "01021c31",
      "instruction": "MOV EDX,dword ptr [EAX + 0xbc]"
    },
    {
      "address": "01021c37",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "01021c39",
      "instruction": "CALL EDX"
    },
    {
      "address": "01021c3b",
      "instruction": "MOV ECX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "01021c3f",
      "instruction": "MOV dword ptr [EDI + EBP*0x4],EBX"
    },
    {
      "address": "01021c42",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01021c44",
      "instruction": "JZ 0x01021c50"
    },
    {
      "address": "01021c46",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01021c48",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc0]"
    },
    {
      "address": "01021c4e",
      "instruction": "CALL EDX"
    },
    {
      "address": "01021c50",
      "instruction": "LEA EBP,[ESI + -0x1]"
    },
    {
      "address": "01021c53",
      "instruction": "MOV EAX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "01021c57",
      "instruction": "PUSH EAX"
    },
    {
      "address": "01021c58",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01021c59",
      "instruction": "MOV ECX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "01021c5d",
      "instruction": "MOV EAX,ESP"
    },
    {
      "address": "01021c5f",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "01021c61",
      "instruction": "MOV ECX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "01021c65",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "01021c67",
      "instruction": "JZ 0x01021c73"
    },
    {
      "address": "01021c69",
      "instruction": "MOV EDX
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
  "body_end": "01021c9c",
  "body_span_bytes": 237,
  "body_start": "01021bb0",
  "callees": [
    "FUN_010215e0"
  ],
  "callers": [
    "FUN_01021ed0",
    "FUN_01021ca0",
    "FUN_01021e00"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01021bb0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_5",
      "storage": "Stack[0x14]:4",
      "type": "int *"
    },
    {
      "name": "param_4",
      "storage": "Stack[0x10]:4",
      "type": "int"
    },
    {
      "name": "piVar1",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "param_6",
      "storage": "Stack[0x18]:4",
      "type": "undefined *"
    },
    {
      "name": "iVar3",
      "storage": "unique:100000a0:4",
      "type": "int"
    },
    {
      "name": "piVar2",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "iVar5",
      "storage": "register:00000014:4",
      "type": "int"
    },
    {
      "name": "iVar4",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "param_3",
      "storage": "Stack[0xc]:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 11,
  "mode": "live",
  "name": "FUN_01021bb0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc21bb0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01021bb0(void)",
  "size_bytes": 237,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01021bb0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "01021f74"
    },
    {
      "from": "01021d16"
    },
    {
      "from": "01021e3c"
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
