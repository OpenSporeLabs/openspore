# Evidence 0x00c17420

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c33efd30787523d8aff8bd9155e7b3665c2eb2f823b76c41f7e15d99e0a07256`

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
      "entry_ESP+0x1c",
      "entry_ESP+0x28"
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x28",
        "observed": true,
        "ordinal": 10,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x28",
        "observed": true,
        "ordinal": 10,
        "read": false,
        "size_inferred": true,
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
    "flow_not_modelled: the linear ESP walk ends at -28, so the listing is not one path",
    "unparsed_lines_present: 3 line(s) matched no grammar rule",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
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
  "content_sha256": "aa1acb542d3e10b161e3cd9bb549f88f38aafa71ed4da7c77755cd23b7ebc303",
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
        "obs-0030",
        "obs-0052",
        "obs-0055"
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
        "obs-0006",
        "obs-0011",
        "obs-0023",
        "obs-0025",
        "obs-0032",
        "obs-0033",
        "obs-0034",
        "obs-0036",
        "obs-0040",
        "obs-0041",
        "obs-0042",
        "obs-0044",
        "obs-0047"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 4,
        "observed_slots": 6,
        "total_bytes": 40
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0013",
        "obs-0017",
        "obs-0018",
        "obs-0020",
        "obs-0024",
        "obs-0033",
        "obs-0034",
        "obs-0041",
        "obs-0042"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",

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
"\nint FUN_00c17420(uint param_1,int param_2,void *param_3,uint param_4)\n\n{\n  int iVar1;\n  int *piVar2;\n  int *piVar3;\n  undefined4 *puVar4;\n  int iVar5;\n  int iVar6;\n  uint local_10;\n  undefined4 local_c;\n  undefined4 local_8;\n  undefined4 local_4;\n  \n  iVar1 = param_1;\n  if (((param_1 != 0) && (iVar6 = *(int *)(param_1 + 0xb54), iVar6 != 0)) &&\n     (*(int *)(iVar6 + 0x17c) != 0)) {\n    iVar5 = param_2;\n    if (0xf < param_2) {\n      iVar5 = 0;\n    }\n    local_10 = (uint)(iVar5 == 0);\n    if (iVar5 == 2) {\n      piVar2 = (int *)FUN_004d9030(iVar6);\n      piVar3 = (int *)&param_4;\n      param_1 = piVar2[1] - *piVar2 >> 2;\n      if (param_1 <= param_4) {\n        piVar3 = (int *)&param_1;\n      }\n      iVar6 = *piVar3;\n      piVar3 = (int *)FUN_004d9030(*(undefined4 *)(iVar1 + 0xb54));\n      iVar5 = *piVar3;\n      puVar4 = (undefined4 *)FUN_004d9030(*(undefined4 *)(iVar1 + 0xb54));\n    }\n    else {\n      if (iVar5 != 0xb) {\n        local_c = *(undefined4 *)(s_rootspinmoutfootbashpokeslshshot_015716e8 + iVar5 * 4);\n        local_8 = 0;\n        local_4 = 0;\n        iVar1 = FUN_009b2340(param_3,param_4,**(undefined4 **)(iVar6 + 0x17c),&local_10,0,0);\n        return iVar1;\n      }\n      piVar2 = (int *)FUN_004d9050(iVar6);\n      piVar3 = (int *)&param_4;\n      param_1 = piVar2[1] - *piVar2 >> 2;\n      if (param_1 <= param_4) {\n        piVar3 = (int *)&param_1;\n      }\n      iVar6 = *piVar3;\n      piVar3 = (int *)FUN_004d9050(*(undefined4 *)(iVar1 + 0xb54));\n      iVar5 = *piVar3;\n      puVar4 = (undefined4 *)FUN_004d9050(*(undefined4 *)(iVar1 + 0xb54));\n    }\n    memcpy(param_3,(void *)*puVar4,(iVar6 * 4 - (int)*puVar4) + iVar5);\n    return iVar6;\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 113,
  "instructions": [
    {
      "address": "00c17420",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "00c17423",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c17424",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c17425",
      "instruction": "MOV ESI,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00c17429",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00c1742b",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "00c1742d",
      "instruction": "JZ 0x00c17576"
    },
    {
      "address": "00c17433",
      "instruction": "MOV EAX,dword ptr [ESI + 0xb54]"
    },
    {
      "address": "00c17439",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00c1743b",
      "instruction": "JZ 0x00c17576"
    },
    {
      "address": "00c17441",
      "instruction": "CMP dword ptr [EAX + 0x17c],EBX"
    },
    {
      "address": "00c17447",
      "instruction": "JZ 0x00c17576"
    },
    {
      "address": "00c1744d",
      "instruction": "MOV ECX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00c17451",
      "instruction": "CMP ECX,0x10"
    },
    {
      "address": "00c17454",
      "instruction": "CMOVGE ECX,EBX"
    },
    {
      "address": "00c17457",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00c17459",
      "instruction": "CMP ECX,EBX"
    },
    {
      "address": "00c1745b",
      "instruction": "JNZ 0x00c17460"
    },
    {
      "address": "00c1745d",
      "instruction": "LEA EDX,[EBX + 0x1]"
    },
    {
      "address": "00c17460",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c17461",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00c17463",
      "instruction": "SUB EDI,0x2"
    },
    {
      "address": "00c17466",
      "instruction": "JZ 0x00c17503"
    },
    {
      "address": "00c1746c",
      "instruction": "SUB EDI,0x9"
    },
    {
      "address": "00c1746f",
      "instruction": "JZ 0x00c174b3"
    },
    {
      "address": "00c17471",
      "instruction": "MOV ECX,dword ptr [ECX*0x4 + 0x15716e8]"
    },
    {
      "address": "00c17478",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c17479",
      "instruction": "MOV dword ptr [ESP + 0x10],EDX"
    },
    {
      "address": "00c1747d",
      "instruction": "MOV dword ptr [ESP + 0x14],ECX"
    },
    {
      "address": "00c17481",
      "instruction": "MOV dword ptr [ESP + 0x18],EBX"
    },
    {
      "address": "00c17485",
      "instruction": "MOV dword ptr [ESP + 0x1c],EBX"
    },
    {
      "address": "00c17489",
      "instruction": "MOV EDX,dword ptr [EAX + 0x17c]"
    },
    {
      "address": "00c1748f",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "00c17491",
      "instruction": "MOV EDX,dword ptr [ESP + 0x30]"
    },
    {
      "address": "00c17495",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c17496",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00c1749a",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c1749b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c1749c",
      "instruction": "MOV EAX,dword ptr [ESP + 0x38]"
    },
    {
      "address": "00c174a0",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c174a1",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c174a2",
      "instruction": "CALL 0x009b2340"
    },
    {
      "address": "00c174a7",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "00c174aa",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00c174ac",
      "instruction": "POP EDI"
    },
    {
      "address": "00c174ad",
      "instruction": "POP ESI"
    },
    {
      "address": "00c174ae",
      "instruction": "POP EBX"
    },
    {
      "address": "00c174af",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00c174b2",
      "instruction": "RET"
    },
    {
      "address": "00c174b3",
      "instruction": "MOV ECX,dword ptr [ESI + 0xb20]"
    },
    {
      "address": "00c174b9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c174ba",
      "instruction": "CALL 0x004d9050"
    },
    {
      "address": "00c174bf",
      "instruction": "MOV ECX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00c174c2",
      "instruction": "SUB ECX,dword ptr [EAX]"
    },
    {
      "address": "00c174c4",
      "instruction": "LEA EAX,[ESP + 0x2c]"
    },
    {
      "address": "00c174c8",
      "instruction": "SAR ECX,0x2"
    },
    {
      "address": "00c174cb",
      "instruction": "MOV dword ptr [ESP + 0x20],ECX"
    },
    {
      "address": "00c174cf",
      "instruction": "CMP dword ptr [ESP + 0x2c],ECX"
    },
    {
      "address": "00c174d3",
      "instruction": "JC 0x00c174d9"
    },
    {
      "address": "00c174d5",
      "instruction": "LEA EAX,[ESP + 0x20]"
    },
    {
      "address": "00c174d9",
      "instruction": "MOV EDI,dword ptr [EAX]"
    },
    {
      "address": "00c174db",
      "instruction": "MOV EAX,dword ptr [ESI + 0xb54]"
    },
    {
      "address": "00c174e1",
      "instruction": "MOV ECX,dword ptr [ESI + 0xb20]"
    },
    {
      "address": "00c174e7",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c174e8",
      "instruction": "CALL 0x004d9050"
    },
    {
      "address": "00c174ed",
      "instruction": "MOV EBX,dword ptr [EAX]"
    },
    {
      "address": "00c174ef",
      "instruction": "MOV EAX,dword ptr [ESI + 0xb54]"
    },
    {
      "address": "00c174f5",
      "instruction": "MOV ECX,dword ptr [ESI + 0xb20]"
    },
    {
      "address": "00c174fb",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c174fc",
      "instruction": "CALL 0x004d9050"
    },
    {
      "address": "00c17501",
      "instruction": "JMP 0x00c17551"
    },
    {
      "address": "00c1750
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
  "body_end": "00c1757d",
  "body_span_bytes": 350,
  "body_start": "00c17420",
  "callees": [
    "FUN_004d9030",
    "FUN_004d9050",
    "FUN_009b2340",
    "memcpy"
  ],
  "callers": [
    "FUN_00c17580",
    "FUN_00c17cc0",
    "FUN_00c1db40",
    "FUN_00c17a30",
    "FUN_00c175d0",
    "FUN_00c17c80",
    "FUN_00c1d640"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c17420",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "uint"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "iVar6",
      "storage": "register:0000001c:4",
      "type": "int"
    },
    {
      "name": "iVar5",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "puVar4",
      "storage": "register:00000000:4",
      "type": "undefined4 *"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "piVar3",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "piVar2",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "param_4",
      "storage": "Stack[0x10]:4",
      "type": "uint"
    },
    {
      "name": "param_3",
      "storage": "Stack[0xc]:4",
      "type": "void *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "uint"
    }
  ],
  "locals_count": 14,
  "mode": "live",
  "name": "FUN_00c17420",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x817420",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c17420(void)",
  "size_bytes": 350,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c17420",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00c1db68"
    },
    {
      "from": "00c17d19"
    },
    {
      "from": "00c1759a"
    },
    {
      "from": "00c17a5a"
    },
    {
      "from": "00c17c90"
    },
    {
      "from": "00c175ed"
    },
    {
      "from": "00c1d66e"
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
