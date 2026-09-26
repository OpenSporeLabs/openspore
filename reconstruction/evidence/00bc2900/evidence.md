# Evidence 0x00bc2900

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b96842405e96ef72574dafebdbc85422d1ec9eaacb42cd53f3ac280e1b47451f`

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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path",
    "receiver_not_determinable: ecx_used_as_counter",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_used_as_counter), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "6ffbbdbe2dc41299432b23b85db6a3b4b985d262253bccf0adea24215f0276ee",
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0042"
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
        "obs-0017"
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
        "obs-0005",
        "obs-0006",
        "obs-0012",
        "obs-0025",
        "obs-0028",
        "obs-0034"
      ],
      "claim": "the register receiver is undetermined: ecx_used_as_counter",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_used_as_counter",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0012",
        "obs-0025",
        "obs-0028",
        "obs-0034"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_used_as_counter) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0042"
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
      "at": "0x00bc2900",
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
      "raw": "SUB ESP,0x5c",
      "sub": 92
    },
    {
      "at": "0x00bc2900",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x5c",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00bc2903",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [0x01485720]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00bc290b",
      "count": 6,
      "first_use": 2,
      "first_write_index": 12,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00bc290c",
      "count": 7,
      "first_use": 3,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "XOR ECX,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00bc290c",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "XOR ECX,ECX",
      "reg": "ECX",
      "write_kind": "zero"
    },
    {
      "at": "0x00bc290e",
      "count": 3,
      "first_use": 4,
      "first_write_index": null,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00bc290f",
      "count": 13,
      "first_use": 5,
      "first_write_index": 5,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_READ",
      "raw": "XOR EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00bc290f",
      "definite": true,
      "id": "obs-0009",
    
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
"\nvoid FUN_00bc2900(undefined4 *param_1,int *param_2)\n\n{\n  undefined4 *puVar1;\n  undefined4 uVar2;\n  int iVar3;\n  undefined4 *puVar4;\n  undefined1 auStack_5c [36];\n  ushort local_38;\n  short local_36;\n  undefined4 uStack_34;\n  undefined4 uStack_30;\n  undefined4 uStack_2c;\n  undefined4 local_28;\n  undefined4 local_24 [9];\n  \n  local_36 = 0;\n  local_38 = 0;\n  local_28 = 0x3f800000;\n  FUN_0041cb40(&DAT_0168aa8c);\n  puVar1 = (undefined4 *)(**(code **)(*param_2 + 0x2c))();\n  uStack_30 = puVar1[1];\n  uStack_34 = *puVar1;\n  uStack_2c = puVar1[2];\n  local_38 = local_38 | 4;\n  local_36 = local_36 + 1;\n  uVar2 = (**(code **)(*param_2 + 0x30))();\n  puVar1 = (undefined4 *)QuaternionToMatrix(auStack_5c,uVar2);\n  puVar4 = local_24;\n  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {\n    *puVar4 = *puVar1;\n    puVar1 = puVar1 + 1;\n    puVar4 = puVar4 + 1;\n  }\n  local_38 = local_38 | 2;\n  local_36 = local_36 + 1;\n  FUN_0040efa0();\n  *param_1 = uStack_34;\n  param_1[1] = uStack_30;\n  param_1[2] = uStack_2c;\n  return;\n}\n\n"
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
      "address": "00bc2900",
      "instruction": "SUB ESP,0x5c"
    },
    {
      "address": "00bc2903",
      "instruction": "MOVSS XMM0,dword ptr [0x01485720]"
    },
    {
      "address": "00bc290b",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bc290c",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00bc290e",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bc290f",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00bc2911",
      "instruction": "MOV word ptr [ESP + 0x2e],CX"
    },
    {
      "address": "00bc2916",
      "instruction": "PUSH 0x168aa8c"
    },
    {
      "address": "00bc291b",
      "instruction": "LEA ECX,[ESP + 0x44]"
    },
    {
      "address": "00bc291f",
      "instruction": "MOV word ptr [ESP + 0x30],AX"
    },
    {
      "address": "00bc2924",
      "instruction": "MOVSS dword ptr [ESP + 0x40],XMM0"
    },
    {
      "address": "00bc292a",
      "instruction": "CALL 0x0041cb40"
    },
    {
      "address": "00bc292f",
      "instruction": "MOV ESI,dword ptr [ESP + 0x6c]"
    },
    {
      "address": "00bc2933",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00bc2935",
      "instruction": "MOV EAX,dword ptr [EDX + 0x2c]"
    },
    {
      "address": "00bc2938",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bc293a",
      "instruction": "CALL EAX"
    },
    {
      "address": "00bc293c",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00bc293f",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "00bc2941",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00bc2944",
      "instruction": "OR word ptr [ESP + 0x2c],0x4"
    },
    {
      "address": "00bc294a",
      "instruction": "INC word ptr [ESP + 0x2e]"
    },
    {
      "address": "00bc294f",
      "instruction": "MOV dword ptr [ESP + 0x34],EDX"
    },
    {
      "address": "00bc2953",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00bc2955",
      "instruction": "MOV dword ptr [ESP + 0x30],ECX"
    },
    {
      "address": "00bc2959",
      "instruction": "MOV dword ptr [ESP + 0x38],EAX"
    },
    {
      "address": "00bc295d",
      "instruction": "MOV EAX,dword ptr [EDX + 0x30]"
    },
    {
      "address": "00bc2960",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00bc2962",
      "instruction": "CALL EAX"
    },
    {
      "address": "00bc2964",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bc2965",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "00bc2969",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bc296a",
      "instruction": "CALL 0x0059c190"
    },
    {
      "address": "00bc296f",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00bc2971",
      "instruction": "MOV ECX,0x9"
    },
    {
      "address": "00bc2976",
      "instruction": "LEA EDI,[ESP + 0x48]"
    },
    {
      "address": "00bc297a",
      "instruction": "MOVSD.REP ES:EDI,ESI"
    },
    {
      "address": "00bc297c",
      "instruction": "OR word ptr [ESP + 0x34],0x2"
    },
    {
      "address": "00bc2982",
      "instruction": "INC word ptr [ESP + 0x36]"
    },
    {
      "address": "00bc2987",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00bc298a",
      "instruction": "LEA ECX,[ESP + 0x2c]"
    },
    {
      "address": "00bc298e",
      "instruction": "CALL 0x0040efa0"
    },
    {
      "address": "00bc2993",
      "instruction": "MOV EAX,dword ptr [ESP + 0x68]"
    },
    {
      "address": "00bc2997",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x30]"
    },
    {
      "address": "00bc299d",
      "instruction": "MOVSS dword ptr [EAX],XMM0"
    },
    {
      "address": "00bc29a1",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x34]"
    },
    {
      "address": "00bc29a7",
      "instruction": "MOVSS dword ptr [EAX + 0x4],XMM0"
    },
    {
      "address": "00bc29ac",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x38]"
    },
    {
      "address": "00bc29b2",
      "instruction": "POP EDI"
    },
    {
      "address": "00bc29b3",
      "instruction": "MOVSS dword ptr [EAX + 0x8],XMM0"
    },
    {
      "address": "00bc29b8",
      "instruction": "POP ESI"
    },
    {
      "address": "00bc29b9",
      "instruction": "ADD ESP,0x5c"
    },
    {
      "address": "00bc29bc",
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
  "body_end": "00bc29bc",
  "body_span_bytes": 189,
  "body_start": "00bc2900",
  "callees": [
    "FUN_0041cb40",
    "FUN_0040efa0",
    "QuaternionToMatrix"
  ],
  "callers": [
    "FUN_00bc29c0",
    "FUN_00bc2c00",
    "FUN_00bc2c50"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bc2900",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "puVar1",
      "storage": "register:00000018:4",
      "type": "undefined4 *"
    },
    {
      "name": "uVar2",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "iVar3",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "puVar4",
      "storage": "register:0000001c:4",
      "type": "undefined4 *"
    },
    {
      "name": "local_24",
      "storage": "",
      "type": "undefined4[9]"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined4"
    },
    {
      "name": "local_36",
      "storage": "Stack[-0x36]:2",
      "type": "short"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4 *"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:2",
      "type": "ushort"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "int *"
    },
    {
      "name": "uStack_30",
      "storage": "Stack[-0x30]:4",
      "type": "undefined4"
    },
    {
      "name": "uStack_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined4"
    },
    {
      "name": "auStack_5c",
      "storage": "",
      "type": "undefined1[36]"
    },
    {
      "name": "uStack_34",
      "storage": "Stack[-0x34]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 14,
  "mode": "live",
  "name": "FUN_00bc2900",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7c2900",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bc2900(void)",
  "size_bytes": 189,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bc2900",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00bc29eb"
    },
    {
      "from": "00bc2d65"
    },
    {
      "from": "00bc2c1b"
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
