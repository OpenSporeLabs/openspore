# Evidence 0x00c035f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `bc4dd019cc990e3f130be2432d7d93645ca1e3f5bdbd1f33475fab47964973f2`

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
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
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
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path",
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
  "content_sha256": "2e352cb5e2aec962463a19cef88553c7c02dc25de46774fc19e57f90b4c0e442",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0057",
        "obs-0061"
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
        "obs-0020",
        "obs-0025",
        "obs-0026",
        "obs-0027",
        "obs-0030",
        "obs-0043"
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
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0018",
        "obs-0041",
        "obs-0048",
        "obs-0049"
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
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0018",
        "obs-0041",
        "obs-0048",
        "obs-0049"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0057",
        "obs-0061"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00c035f0",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x20",
      "sub": 32
    },
    {
      "at": "0x00c035f0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x20",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c035f3",
      "count": 15,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c035f4",
      "count": 31,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x28]",
      "reg": "ESP"
    },
    {
      "at": "0x00c035f4",
      "base": "ESP",
      "disp": 40,
      "id": "obs-0005",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x28]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00c035f4",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0x28]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c0360d",
      "definite": true,
      "id": "obs-0007",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0xb58]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c03613",
      "
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
"\nvoid FUN_00c035f0(int *param_1)\n\n{\n  int iVar1;\n  int *piVar2;\n  undefined4 *puVar3;\n  float10 fVar4;\n  float local_20;\n  float local_1c;\n  undefined4 local_18;\n  undefined4 local_14;\n  undefined4 local_10;\n  undefined1 local_c [12];\n  \n  piVar2 = param_1;\n  if ((param_1 != (int *)0x0) && (param_1[0x2d5] != 0)) {\n    if ((((uint)param_1[0x2d6] >> 9 & 1) == 0) &&\n       ((param_1[0x2cd] == 1 && ((param_1[0x2d6] & 1U) != 0)))) {\n      iVar1 = DAT_01582f4c * 3 + 0x138;\n      local_18 = *(undefined4 *)(param_1[0x2c8] + iVar1 * 4);\n      iVar1 = param_1[0x2c8] + iVar1 * 4;\n      local_14 = *(undefined4 *)(iVar1 + 4);\n      local_10 = *(undefined4 *)(iVar1 + 8);\n      FUN_0067ff30(local_18,local_14,local_10,&param_1,&local_20,&local_1c);\n      param_1 = (int *)(DAT_01583338 * 360.0 + (float)param_1);\n      if (360.0 < (float)param_1) {\n        param_1 = (int *)((float)param_1 - 360.0);\n      }\n      if ((float)param_1 < 0.0) {\n        param_1 = (int *)((float)param_1 + 360.0);\n      }\n      fVar4 = (float10)FUN_005a6e00(DAT_0158333c * local_20);\n      local_20 = (float)fVar4;\n      fVar4 = (float10)FUN_005a6e00(DAT_01583340 * local_1c);\n      local_1c = (float)fVar4;\n      puVar3 = (undefined4 *)FUN_0067fe30(local_c,param_1,local_20,(float)fVar4);\n      local_18 = *puVar3;\n      local_14 = puVar3[1];\n      local_10 = puVar3[2];\n      (**(code **)(*piVar2 + 0xe4))(&local_18);\n      FUN_00c0d950(1);\n      fVar4 = (float10)(**(code **)(*piVar2 + 0x80))(0);\n      (**(code **)(piVar2[0x30] + 0x40))((float)fVar4);\n      return;\n    }\n    (**(code **)(*param_1 + 0xe4))(&DAT_0157126c);\n    FUN_00c0d950(0);\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 116,
  "instructions": [
    {
      "address": "00c035f0",
      "instruction": "SUB ESP,0x20"
    },
    {
      "address": "00c035f3",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c035f4",
      "instruction": "MOV ESI,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00c035f8",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c035fa",
      "instruction": "JZ 0x00c037ae"
    },
    {
      "address": "00c03600",
      "instruction": "CMP dword ptr [ESI + 0xb54],0x0"
    },
    {
      "address": "00c03607",
      "instruction": "JZ 0x00c037ae"
    },
    {
      "address": "00c0360d",
      "instruction": "MOV EAX,dword ptr [ESI + 0xb58]"
    },
    {
      "address": "00c03613",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c03615",
      "instruction": "SHR ECX,0x9"
    },
    {
      "address": "00c03618",
      "instruction": "TEST CL,0x1"
    },
    {
      "address": "00c0361b",
      "instruction": "JNZ 0x00c03794"
    },
    {
      "address": "00c03621",
      "instruction": "CMP dword ptr [ESI + 0xb34],0x1"
    },
    {
      "address": "00c03628",
      "instruction": "JNZ 0x00c03794"
    },
    {
      "address": "00c0362e",
      "instruction": "TEST AL,0x1"
    },
    {
      "address": "00c03630",
      "instruction": "JZ 0x00c03794"
    },
    {
      "address": "00c03636",
      "instruction": "MOV EAX,[0x01582f4c]"
    },
    {
      "address": "00c0363b",
      "instruction": "LEA EDX,[EAX + EAX*0x2 + 0x138]"
    },
    {
      "address": "00c03642",
      "instruction": "MOV EAX,dword ptr [ESI + 0xb20]"
    },
    {
      "address": "00c03648",
      "instruction": "MOVSS XMM0,dword ptr [EAX + EDX*0x4]"
    },
    {
      "address": "00c0364d",
      "instruction": "LEA EAX,[EAX + EDX*0x4]"
    },
    {
      "address": "00c03650",
      "instruction": "MOVSS dword ptr [ESP + 0xc],XMM0"
    },
    {
      "address": "00c03656",
      "instruction": "MOVSS XMM1,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00c0365b",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM1"
    },
    {
      "address": "00c03661",
      "instruction": "MOVSS XMM1,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00c03666",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "00c0366a",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c0366b",
      "instruction": "LEA EDX,[ESP + 0x8]"
    },
    {
      "address": "00c0366f",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c03670",
      "instruction": "LEA EAX,[ESP + 0x30]"
    },
    {
      "address": "00c03674",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c03675",
      "instruction": "MOVSS dword ptr [ESP + 0x20],XMM1"
    },
    {
      "address": "00c0367b",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "00c0367e",
      "instruction": "MOV EAX,ESP"
    },
    {
      "address": "00c03680",
      "instruction": "MOVSS dword ptr [EAX],XMM0"
    },
    {
      "address": "00c03684",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00c0368a",
      "instruction": "MOVSS dword ptr [EAX + 0x4],XMM0"
    },
    {
      "address": "00c0368f",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00c03695",
      "instruction": "MOVSS dword ptr [EAX + 0x8],XMM0"
    },
    {
      "address": "00c0369a",
      "instruction": "CALL 0x0067ff30"
    },
    {
      "address": "00c0369f",
      "instruction": "MOVSS XMM1,dword ptr [0x013ec4d4]"
    },
    {
      "address": "00c036a7",
      "instruction": "MOVSS XMM0,dword ptr [0x01583338]"
    },
    {
      "address": "00c036af",
      "instruction": "MULSS XMM0,XMM1"
    },
    {
      "address": "00c036b3",
      "instruction": "ADDSS XMM0,dword ptr [ESP + 0x40]"
    },
    {
      "address": "00c036b9",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "00c036bc",
      "instruction": "COMISS XMM0,XMM1"
    },
    {
      "address": "00c036bf",
      "instruction": "MOVSS dword ptr [ESP + 0x28],XMM0"
    },
    {
      "address": "00c036c5",
      "instruction": "JBE 0x00c036d1"
    },
    {
      "address": "00c036c7",
      "instruction": "SUBSS XMM0,XMM1"
    },
    {
      "address": "00c036cb",
      "instruction": "MOVSS dword ptr [ESP + 0x28],XMM0"
    },
    {
      "address": "00c036d1",
      "instruction": "XORPS XMM2,XMM2"
    },
    {
      "address": "00c036d4",
      "instruction": "COMISS XMM2,XMM0"
    },
    {
      "address": "00c036d7",
      "instruction": "JBE 0x00c036e3"
    },
    {
      "address": "00c036d9",
      "instruction": "ADDSS XMM0,XMM1"
    },
    {
      "address": "00c036dd",
      "instruction": "MOVSS dword ptr [ESP + 0x28],XMM0"
    },
    {
      "address": "00c036e3",
      "instruction": "MOVSS XMM0,dword ptr [0x0158333c]"
    },
    {
      "address": "00c036eb",
      "instruction": "MULSS XMM0,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00c036f1",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c036f2",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00c036f7",
      "instruction": "CALL 0x005a6e00"
    },
    {
      "address": "00c036fc",
      "instruction": "FSTP float ptr [ESP + 0x8]"
    },
    {
      "address": "00c03700",
      "instruction": "MOVSS XMM0,dword ptr [0x01583340]"
    },
    {
      "address": "00c03708",
      "instruction": "MULSS XMM0,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00c0370e",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00c03713",
      "instruction": "CALL 0x005a6e00"
    },
    {
      "address": "00c03718",
      "instruction": "FST float ptr [ESP + 0xc]"
    },
    {
      "address": "00c0371c",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00c0371f",
      "instruction": "SUB ESP,0x8"
    }
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
  "body_end": "00c037b2",
  "body_span_bytes": 451,
  "body_start": "00c035f0",
  "callees": [
    "FUN_0067ff30",
    "FUN_0067fe30",
    "FUN_00c0d950",
    "FUN_005a6e00"
  ],
  "callers": [
    "FUN_00c099e0",
    "FUN_00c09fa0",
    "FUN_00c04dd0",
    "FUN_00c04e50"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c035f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c",
      "storage": "",
      "type": "undefined1[12]"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "fVar4",
      "storage": "register:00001100:10",
      "type": "float10"
    },
    {
      "name": "puVar3",
      "storage": "register:00000000:4",
      "type": "undefined4 *"
    },
    {
      "name": "piVar2",
      "storage": "unique:100000ef:4",
      "type": "int *"
    },
    {
      "name": "iVar1",
      "storage": "unique:00007a00:4",
      "type": "int"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "float"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "float"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    }
  ],
  "locals_count": 11,
  "mode": "live",
  "name": "FUN_00c035f0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8035f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c035f0(void)",
  "size_bytes": 451,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c035f0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00c0ab80"
    },
    {
      "from": "00c09f89"
    },
    {
      "from": "00c04e36"
    },
    {
      "from": "00c04f76"
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
