# Evidence 0x00c446d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `578970ddf98d0abbc426cec98be9212760d9703e10badcae34e25233e47323da`

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
      "entry_ESP+0x8"
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET 0x8",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -16, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "slot_width_ambiguous: one entry slot is read at more than one width",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "eecc034065ed611c8a65b137963d88462a3212c3885a8673eff5f0d259557101",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
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
        "obs-0024",
        "obs-0028",
        "obs-0031"
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
        "obs-0004",
        "obs-0010",
        "obs-0029"
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
        "obs-0004",
        "obs-0010",
        "obs-0029"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0021"
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
        "obs-0013",
        "obs-0021"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0004"
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
      "at": "0x00c446d0",
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
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00c446d0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c446d3",
      "count": 8,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x14]",
      "reg": "ESP"
    },
    {
      "at": "0x00c446d3",
      "base": "ESP",
      "disp": 20,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x14]",
      "resolved": true,
      "size
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
"\nvoid __thiscall FUN_00c446d0(int param_1,undefined4 *param_2,char param_3)\n\n{\n  undefined4 *puVar1;\n  undefined4 local_10;\n  undefined4 local_c;\n  undefined4 local_8;\n  uint local_4;\n  \n  local_10 = *param_2;\n  local_c = param_2[1];\n  local_8 = param_2[2];\n  local_4 = (uint)(param_3 != '\\0');\n  if (param_3 != '\\0') {\n    FUN_00c43f20(*(undefined4 *)(param_1 + 0xf0),&local_10);\n    return;\n  }\n  puVar1 = *(undefined4 **)(param_1 + 0xf4);\n  if (puVar1 < *(undefined4 **)(param_1 + 0xf8)) {\n    *(undefined4 **)(param_1 + 0xf4) = puVar1 + 4;\n    if (puVar1 != (undefined4 *)0x0) {\n      *puVar1 = local_10;\n      puVar1[1] = local_c;\n      puVar1[2] = local_8;\n      puVar1[3] = 0;\n      return;\n    }\n  }\n  else {\n    FUN_00c43cc0(puVar1,&local_10);\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 44,
  "instructions": [
    {
      "address": "00c446d0",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "00c446d3",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00c446d7",
      "instruction": "MOVSS XMM0,dword ptr [EAX]"
    },
    {
      "address": "00c446db",
      "instruction": "MOVSS XMM1,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00c446e0",
      "instruction": "MOVSS XMM2,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00c446e5",
      "instruction": "MOV AL,byte ptr [ESP + 0x18]"
    },
    {
      "address": "00c446e9",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00c446eb",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c446ed",
      "instruction": "SETNZ DL"
    },
    {
      "address": "00c446f0",
      "instruction": "ADD ECX,0xf0"
    },
    {
      "address": "00c446f6",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00c446fb",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM1"
    },
    {
      "address": "00c44701",
      "instruction": "MOVSS dword ptr [ESP + 0x8],XMM2"
    },
    {
      "address": "00c44707",
      "instruction": "MOV dword ptr [ESP + 0xc],EDX"
    },
    {
      "address": "00c4470b",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c4470d",
      "instruction": "JZ 0x00c44721"
    },
    {
      "address": "00c4470f",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00c44711",
      "instruction": "LEA EAX,[ESP]"
    },
    {
      "address": "00c44714",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c44715",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c44716",
      "instruction": "CALL 0x00c43f20"
    },
    {
      "address": "00c4471b",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00c4471e",
      "instruction": "RET 0x8"
    },
    {
      "address": "00c44721",
      "instruction": "MOV EAX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "00c44724",
      "instruction": "CMP EAX,dword ptr [ECX + 0x8]"
    },
    {
      "address": "00c44727",
      "instruction": "JNC 0x00c4474c"
    },
    {
      "address": "00c44729",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c4472a",
      "instruction": "LEA ESI,[EAX + 0x10]"
    },
    {
      "address": "00c4472d",
      "instruction": "MOV dword ptr [ECX + 0x4],ESI"
    },
    {
      "address": "00c44730",
      "instruction": "POP ESI"
    },
    {
      "address": "00c44731",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c44733",
      "instruction": "JZ 0x00c44756"
    },
    {
      "address": "00c44735",
      "instruction": "MOVSS dword ptr [EAX],XMM0"
    },
    {
      "address": "00c44739",
      "instruction": "MOVSS dword ptr [EAX + 0x4],XMM1"
    },
    {
      "address": "00c4473e",
      "instruction": "MOVSS dword ptr [EAX + 0x8],XMM2"
    },
    {
      "address": "00c44743",
      "instruction": "MOV dword ptr [EAX + 0xc],EDX"
    },
    {
      "address": "00c44746",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00c44749",
      "instruction": "RET 0x8"
    },
    {
      "address": "00c4474c",
      "instruction": "LEA EDX,[ESP]"
    },
    {
      "address": "00c4474f",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c44750",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c44751",
      "instruction": "CALL 0x00c43cc0"
    },
    {
      "address": "00c44756",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00c44759",
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
  "body_end": "00c4475b",
  "body_span_bytes": 140,
  "body_start": "00c446d0",
  "callees": [
    "FUN_00c43cc0",
    "FUN_00c43f20"
  ],
  "callers": [
    "FUN_00c13650",
    "FUN_00c13a30",
    "FUN_00c18b40",
    "FUN_00c1b020",
    "FUN_00c20230",
    "FUN_00b452f0",
    "FUN_00c18740",
    "FUN_00f235e0",
    "FUN_00c0eec0",
    "FUN_00c190e0",
    "FUN_00b34380",
    "FUN_00c1a3c0",
    "FUN_00c18370",
    "FUN_00c2a190"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c446d0",
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
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "uint"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4 *"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "puVar1",
      "storage": "unique:00017200:4",
      "type": "undefined4 *"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:1",
      "type": "char"
    }
  ],
  "locals_count": 8,
  "mode": "live",
  "name": "FUN_00c446d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8446d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c446d0(void)",
  "size_bytes": 140,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c446d0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 16,
  "xrefs": [
    {
      "from": "00b345dc"
    },
    {
      "from": "00b45341"
    },
    {
      "from": "00c1a9e6"
    },
    {
      "from": "00c13937"
    },
    {
      "from": "00c13bef"
    },
    {
      "from": "00c18674"
    },
    {
      "from": "00c18ae5"
    },
    {
      "from": "00c195be"
    },
    {
      "from": "00c0f21e"
    },
    {
      "from": "00c20719"
    },
    {
      "from": "00f237fe"
    },
    {
      "from": "00c1b655"
    },
    {
      "from": "00c18f8d"
    },
    {
      "from": "00c1ea76"
    },
    {
      "from": "00c1ede7"
    },
    {
      "from": "00c2a699"
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
