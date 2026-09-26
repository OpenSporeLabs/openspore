# Evidence 0x00bb0d80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f5b66f9a246d583852e3a294d6bf78528f6d9647e62c2c5ae80354620a5ccbd4`

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
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
        "size_inferred": true,
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
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +40, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "3a1623350317c51d7aa5a5e2b693fbe452a258f98245b524d0b427d12b65e001",
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
        "obs-0056"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0010",
        "obs-0018"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0014",
        "obs-0018",
        "obs-0023",
        "obs-0028",
        "obs-0042",
        "obs-0045",
        "obs-0047"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          200
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0014",
        "obs-0018",
        "obs-0023",
        "obs-0028",
        "obs-0042",
        "obs-0045",
        "obs-0047",
        "obs-0056"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0056"
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
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00bb0d80",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 3,
      "raw": "SUB ESP,0x14",
      "sub": 20
    },
    {
      "at": "0x00bb0d80",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x14",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00bb0d83",
      "count": 24,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOVSS XMM2,dword ptr [ESP + 0x1c]",
      "reg": "ESP"
    },
    {
      "at": "0x00bb0d83",
      "base": "ESP",
      "disp": 28,
      "id": "obs-0004",
      "index": 1,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOVSS XMM2,dword ptr [ESP + 0x1c]",
      "resolved": true,
      "size": 4,
      "trust": "untrusted_frame"
    },
    {
      "at": "0x00bb0d83",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
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
"\nvoid __thiscall FUN_00bb0d80(int param_1,float *param_2,float param_3,int param_4)\n\n{\n  float *pfVar1;\n  int iVar2;\n  int iVar3;\n  int iVar4;\n  float fVar5;\n  undefined4 uVar6;\n  int local_14;\n  int local_10;\n  float local_c;\n  float local_8;\n  undefined4 local_4;\n  \n  pfVar1 = param_2;\n  uVar6 = 0;\n  local_c = *param_2 - param_3;\n  local_8 = param_2[1] - param_3;\n  local_4 = 0;\n  fVar5 = param_3;\n  FUN_00ba7100(&local_c,&param_2,&local_14);\n  local_c = *pfVar1 + fVar5;\n  local_8 = pfVar1[1] + fVar5;\n  local_4 = uVar6;\n  FUN_00ba7100(&local_c,&param_3,&local_10);\n  iVar2 = param_4;\n  if ((int)param_2 <= (int)param_3) {\n    do {\n      if (local_14 <= local_10) {\n        iVar3 = (int)(param_2 + local_14 * 0x10) * 0x14;\n        iVar4 = (local_10 - local_14) + 1;\n        do {\n          FUN_01012030(*(undefined4 *)(iVar2 + 4),*(undefined4 *)(*(int *)(param_1 + 200) + iVar3),\n                       *(undefined4 *)(*(int *)(param_1 + 200) + 4 + iVar3),param_2);\n          iVar3 = iVar3 + 0x500;\n          iVar4 = iVar4 + -1;\n        } while (iVar4 != 0);\n      }\n      param_2 = (float *)((int)param_2 + 1);\n    } while ((int)param_2 <= (int)param_3);\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 84,
  "instructions": [
    {
      "address": "00bb0d80",
      "instruction": "SUB ESP,0x14"
    },
    {
      "address": "00bb0d83",
      "instruction": "MOVSS XMM2,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00bb0d89",
      "instruction": "XORPS XMM3,XMM3"
    },
    {
      "address": "00bb0d8c",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00bb0d8d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bb0d8e",
      "instruction": "MOV ESI,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00bb0d92",
      "instruction": "MOVSS XMM0,dword ptr [ESI]"
    },
    {
      "address": "00bb0d96",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00bb0d98",
      "instruction": "LEA EAX,[ESP + 0x8]"
    },
    {
      "address": "00bb0d9c",
      "instruction": "SUBSS XMM0,XMM2"
    },
    {
      "address": "00bb0da0",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb0da1",
      "instruction": "LEA ECX,[ESP + 0x24]"
    },
    {
      "address": "00bb0da5",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM0"
    },
    {
      "address": "00bb0dab",
      "instruction": "MOVSS XMM0,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00bb0db0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bb0db1",
      "instruction": "LEA EDX,[ESP + 0x18]"
    },
    {
      "address": "00bb0db5",
      "instruction": "SUBSS XMM0,XMM2"
    },
    {
      "address": "00bb0db9",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bb0dba",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00bb0dbc",
      "instruction": "MOVSS dword ptr [ESP + 0x20],XMM0"
    },
    {
      "address": "00bb0dc2",
      "instruction": "MOVSS dword ptr [ESP + 0x24],XMM3"
    },
    {
      "address": "00bb0dc8",
      "instruction": "CALL 0x00ba7100"
    },
    {
      "address": "00bb0dcd",
      "instruction": "MOVSS XMM0,dword ptr [ESI]"
    },
    {
      "address": "00bb0dd1",
      "instruction": "LEA EAX,[ESP + 0xc]"
    },
    {
      "address": "00bb0dd5",
      "instruction": "ADDSS XMM0,XMM2"
    },
    {
      "address": "00bb0dd9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb0dda",
      "instruction": "LEA ECX,[ESP + 0x28]"
    },
    {
      "address": "00bb0dde",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM0"
    },
    {
      "address": "00bb0de4",
      "instruction": "MOVSS XMM0,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00bb0de9",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bb0dea",
      "instruction": "LEA EDX,[ESP + 0x18]"
    },
    {
      "address": "00bb0dee",
      "instruction": "ADDSS XMM0,XMM2"
    },
    {
      "address": "00bb0df2",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bb0df3",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00bb0df5",
      "instruction": "MOVSS dword ptr [ESP + 0x20],XMM0"
    },
    {
      "address": "00bb0dfb",
      "instruction": "MOVSS dword ptr [ESP + 0x24],XMM3"
    },
    {
      "address": "00bb0e01",
      "instruction": "CALL 0x00ba7100"
    },
    {
      "address": "00bb0e06",
      "instruction": "MOV EDX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "00bb0e0a",
      "instruction": "CMP EDX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00bb0e0e",
      "instruction": "MOV dword ptr [ESP + 0x20],EDX"
    },
    {
      "address": "00bb0e12",
      "instruction": "JG 0x00bb0e7c"
    },
    {
      "address": "00bb0e14",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bb0e15",
      "instruction": "MOV EBX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00bb0e19",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bb0e1a",
      "instruction": "LEA EBX,[EBX]"
    },
    {
      "address": "00bb0e20",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00bb0e24",
      "instruction": "MOV EDI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00bb0e28",
      "instruction": "CMP ECX,EDI"
    },
    {
      "address": "00bb0e2a",
      "instruction": "JG 0x00bb0e6f"
    },
    {
      "address": "00bb0e2c",
      "instruction": "MOV EAX,ECX"
    },
    {
      "address": "00bb0e2e",
      "instruction": "SHL EAX,0x6"
    },
    {
      "address": "00bb0e31",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "00bb0e33",
      "instruction": "LEA ESI,[EAX + EAX*0x4]"
    },
    {
      "address": "00bb0e36",
      "instruction": "ADD ESI,ESI"
    },
    {
      "address": "00bb0e38",
      "instruction": "SUB EDI,ECX"
    },
    {
      "address": "00bb0e3a",
      "instruction": "ADD ESI,ESI"
    },
    {
      "address": "00bb0e3c",
      "instruction": "INC EDI"
    },
    {
      "address": "00bb0e3d",
      "instruction": "LEA ECX,[ECX]"
    },
    {
      "address": "00bb0e40",
      "instruction": "MOV EAX,dword ptr [EBP + 0xc8]"
    },
    {
      "address": "00bb0e46",
      "instruction": "MOV ECX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00bb0e4a",
      "instruction": "MOV EDX,dword ptr [EAX + ESI*0x1 + 0x4]"
    },
    {
      "address": "00bb0e4e",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bb0e4f",
      "instruction": "MOV ECX,dword ptr [EBX + 0x4]"
    },
    {
      "address": "00bb0e52",
      "instruction": "ADD EAX,ESI"
    },
    {
      "address": "00bb0e54",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00bb0e56",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bb0e57",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bb0e58",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bb0e59",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00bb0e5b",
      "instruction": "CALL 0x01012030"
    },
    {
      "address": "00bb0e60",
      "instruction": "AD
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
  "body_end": "00bb0e83",
  "body_span_bytes": 260,
  "body_start": "00bb0d80",
  "callees": [
    "FUN_01012030",
    "FUN_00ba7100"
  ],
  "callers": [
    "FUN_00bb1080",
    "FUN_00bb0e90",
    "FUN_00bb1200"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bb0d80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "float"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "float"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "int"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "int"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar6",
      "storage": "register:000012c0:4",
      "type": "undefined4"
    },
    {
      "name": "fVar5",
      "storage": "register:00001280:4",
      "type": "float"
    },
    {
      "name": "iVar2",
      "storage": "unique:100000a5:4",
      "type": "int"
    },
    {
      "name": "pfVar1",
      "storage": "unique:100000a1:4",
      "type": "float *"
    },
    {
      "name": "iVar4",
      "storage": "register:0000001c:4",
      "type": "int"
    },
    {
      "name": "iVar3",
      "storage": "register:00000018:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "float *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_4",
      "storage": "Stack[0xc]:4",
      "type": "int"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "float"
    }
  ],
  "locals_count": 15,
  "mode": "live",
  "name": "FUN_00bb0d80",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7b0d80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bb0d80(void)",
  "size_bytes": 260,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bb0d80",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00bb111b"
    },
    {
      "from": "00bb101d"
    },
    {
      "from": "00bb1259"
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
