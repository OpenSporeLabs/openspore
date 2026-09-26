# Evidence 0x00438700

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d103f9171ea5b37e9a07d5607f06fc8d16826879c2a049148a10fc631cee0a8a`

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
        "ebp_offset": "EBP+0x8",
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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBP"
    ],
    "stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
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
    "unparsed_lines_present: 2 line(s) matched no grammar rule"
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
  "content_sha256": "6c69b038fc80dce93ccb6e55191b8670f3ab278d0181cb82b2f3d49822ec512f",
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
        "obs-0066"
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
        "obs-0008",
        "obs-0020",
        "obs-0029",
        "obs-0032",
        "obs-0039",
        "obs-0055",
        "obs-0060"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0011",
        "obs-0012",
        "obs-0014",
        "obs-0017",
        "obs-0021",
        "obs-0025",
        "obs-0029",
        "obs-0033",
        "obs-0036",
        "obs-0037",
        "obs-0042",
        "obs-0050",
        "obs-0051",
        "obs-0057",
        "obs-0058",
        "obs-0062",
        "obs-0063"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          40,
          992
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0011",
        "obs-0012",
        "obs-0014",
        "obs-0017",
        "obs-0021",
        "obs-0025",
        "obs-0029",
        "obs-0033",
        "obs-0036",
        "obs-0037",
        "obs-0042",
        "obs-0050",
        "obs-0051",
        "obs-0057",
        "obs-0058",
        "obs-0062",
        "obs-0063",
        "obs-0066"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0066"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00438700",
      "count": 46,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00438700",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 0,
      "sub": 52
    },
    {
      "at": "0x00438701",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "reg": "ESP"
    },
    {
      "at": "0x00438701",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x00438703",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00438706",
      "count": 17,
      "first_use": 3,
      "first_write_index": 6,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "reg": "ECX"
    },
    {
      "at": "0x00438706",
      "base": "EBP",
      "disp": -48,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "re
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
"\n/* WARNING: Removing unreachable block (ram,0x0043877c) */\n/* WARNING: Removing unreachable block (ram,0x0043884a) */\n\nvoid __thiscall FUN_00438700(int param_1,int param_2)\n\n{\n  char cVar1;\n  int iVar2;\n  \n  FUN_004388b0(param_2);\n  if (((*(int *)(param_1 + 0x28) != 0) && (cVar1 = FUN_004adc40(), cVar1 != '\\0')) &&\n     ((*(uint *)(param_2 + 0xdc8) & 0x80) == 0)) {\n    if (*(int *)(param_1 + 0x3e0) == 0) {\n      if ((*(int *)(param_2 + 0x3e0) != 0) && (cVar1 = FUN_004a7e60(param_1), cVar1 != '\\0')) {\n        if ((*(uint *)(param_1 + 0xdc8) & 0x800) == 0) {\n          FUN_004388b0(*(undefined4 *)(param_2 + 0x3e0));\n        }\n        else {\n          iVar2 = FUN_0044f220();\n          if ((float10)iVar2 == (float10)0) {\n            FUN_004388b0(*(undefined4 *)(param_2 + 0x3e0));\n          }\n        }\n      }\n    }\n    else if (*(int *)(param_2 + 0x3e0) != 0) {\n      FUN_004388b0(*(undefined4 *)(param_2 + 0x3e0));\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 128,
  "instructions": [
    {
      "address": "00438700",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00438701",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "00438703",
      "instruction": "SUB ESP,0x34"
    },
    {
      "address": "00438706",
      "instruction": "MOV dword ptr [EBP + -0x30],ECX"
    },
    {
      "address": "00438709",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0043870c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0043870d",
      "instruction": "MOV ECX,dword ptr [EBP + -0x30]"
    },
    {
      "address": "00438710",
      "instruction": "CALL 0x004388b0"
    },
    {
      "address": "00438715",
      "instruction": "MOV ECX,dword ptr [EBP + -0x30]"
    },
    {
      "address": "00438718",
      "instruction": "CMP dword ptr [ECX + 0x28],0x0"
    },
    {
      "address": "0043871c",
      "instruction": "JZ 0x004388a2"
    },
    {
      "address": "00438722",
      "instruction": "MOV EDX,dword ptr [EBP + -0x30]"
    },
    {
      "address": "00438725",
      "instruction": "MOV ECX,dword ptr [EDX + 0x28]"
    },
    {
      "address": "00438728",
      "instruction": "CALL 0x004adc40"
    },
    {
      "address": "0043872d",
      "instruction": "MOVZX EAX,AL"
    },
    {
      "address": "00438730",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00438732",
      "instruction": "JZ 0x004388a2"
    },
    {
      "address": "00438738",
      "instruction": "MOV ECX,0x7"
    },
    {
      "address": "0043873d",
      "instruction": "CMP ECX,0x3c"
    },
    {
      "address": "00438740",
      "instruction": "JNC 0x0043877c"
    },
    {
      "address": "00438742",
      "instruction": "MOV EDX,0x7"
    },
    {
      "address": "00438747",
      "instruction": "SHR EDX,0x5"
    },
    {
      "address": "0043874a",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0043874d",
      "instruction": "MOV ECX,dword ptr [EAX + EDX*0x4 + 0xdc8]"
    },
    {
      "address": "00438754",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "00438757",
      "instruction": "MOV EAX,0x7"
    },
    {
      "address": "0043875c",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "0043875e",
      "instruction": "MOV ECX,0x20"
    },
    {
      "address": "00438763",
      "instruction": "DIV ECX"
    },
    {
      "address": "00438765",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "0043876a",
      "instruction": "MOV ECX,EDX"
    },
    {
      "address": "0043876c",
      "instruction": "SHL EAX,CL"
    },
    {
      "address": "0043876e",
      "instruction": "AND EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "00438771",
      "instruction": "NEG EAX"
    },
    {
      "address": "00438773",
      "instruction": "SBB EAX,EAX"
    },
    {
      "address": "00438775",
      "instruction": "NEG EAX"
    },
    {
      "address": "00438777",
      "instruction": "MOV byte ptr [EBP + -0x5],AL"
    },
    {
      "address": "0043877a",
      "instruction": "JMP 0x00438780"
    },
    {
      "address": "0043877c",
      "instruction": "MOV byte ptr [EBP + -0x5],0x0"
    },
    {
      "address": "00438780",
      "instruction": "MOVZX ECX,byte ptr [EBP + -0x5]"
    },
    {
      "address": "00438784",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00438786",
      "instruction": "JNZ 0x004388a2"
    },
    {
      "address": "0043878c",
      "instruction": "MOV EDX,dword ptr [EBP + -0x30]"
    },
    {
      "address": "0043878f",
      "instruction": "MOV EAX,dword ptr [EDX + 0x3e0]"
    },
    {
      "address": "00438795",
      "instruction": "MOV dword ptr [EBP + -0xc],EAX"
    },
    {
      "address": "00438798",
      "instruction": "CMP dword ptr [EBP + -0xc],0x0"
    },
    {
      "address": "0043879c",
      "instruction": "JZ 0x004387d9"
    },
    {
      "address": "0043879e",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004387a1",
      "instruction": "MOV EDX,dword ptr [ECX + 0x3e0]"
    },
    {
      "address": "004387a7",
      "instruction": "MOV dword ptr [EBP + -0x10],EDX"
    },
    {
      "address": "004387aa",
      "instruction": "CMP dword ptr [EBP + -0x10],0x0"
    },
    {
      "address": "004387ae",
      "instruction": "JZ 0x004387d4"
    },
    {
      "address": "004387b0",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004387b3",
      "instruction": "MOV ECX,dword ptr [EAX + 0x3e0]"
    },
    {
      "address": "004387b9",
      "instruction": "MOV dword ptr [EBP + -0x14],ECX"
    },
    {
      "address": "004387bc",
      "instruction": "MOV EDX,dword ptr [EBP + -0x30]"
    },
    {
      "address": "004387bf",
      "instruction": "MOV EAX,dword ptr [EDX + 0x3e0]"
    },
    {
      "address": "004387c5",
      "instruction": "MOV dword ptr [EBP + -0x18],EAX"
    },
    {
      "address": "004387c8",
      "instruction": "MOV ECX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "004387cb",
      "instruction": "PUSH ECX"
    },
    {
      "address": "004387cc",
      "instruction": "MOV ECX,dword ptr [EBP + -0x18]"
    },
    {
      "address": "004387cf",
      "instruction": "CALL 0x004388b0"
    },
    {
      "address": "004387d4",
      "instruction": "JMP 0x004388a2"
    },
    {
      "address": "004387d9",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004387dc",
      "instruction": "MOV EAX,dword ptr [EDX + 0x3e0]"
    },
    {
      "address": "004387e2",
      "instruction": "MOV dword ptr [EBP + -0x1c],EAX"
    },
    {
      "address": "004387e5",
      "instruction": "CMP dword ptr [EBP + -0x1c],0x0"
    },
    {
      "address": "004387e9",
      "instruction": "JZ 0x004388a2"
    },
    {
      "address": "004387ef",
    
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
  "body_end": "004388a7",
  "body_span_bytes": 424,
  "body_start": "00438700",
  "callees": [
    "FUN_004388b0",
    "FUN_004adc40",
    "FUN_004a7e60",
    "FUN_0044f220"
  ],
  "callers": [
    "FUN_004a29a0",
    "FUN_004a6f10",
    "FUN_004a2350",
    "FUN_0048fde0",
    "FUN_005d36e0",
    "FUN_0048f790",
    "FUN_005ad5d0",
    "FUN_005d3300",
    "FUN_00487040",
    "FUN_0049cfd0",
    "FUN_005d27e0",
    "FUN_004a1070",
    "FUN_0049cb90",
    "FUN_0049d6b0",
    "FUN_004a0bf0",
    "FUN_005b7cf0",
    "FUN_005bb5a0",
    "Editors::cEditor::OnKeyDown",
    "FUN_005b8da0",
    "FUN_00437b00",
    "FUN_0049a2a0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00438700",
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
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00438700",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x38700",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00438700(void)",
  "size_bytes": 424,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00438700",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 26,
  "xrefs": [
    {
      "from": "00437e08"
    },
    {
      "from": "0049cd27"
    },
    {
      "from": "0048707b"
    },
    {
      "from": "0048f98c"
    },
    {
      "from": "0048fd0c"
    },
    {
      "from": "0048fe81"
    },
    {
      "from": "0049b095"
    },
    {
      "from": "0049d144"
    },
    {
      "from": "0049dc83"
    },
    {
      "from": "004a15b8"
    },
    {
      "from": "004a2ea5"
    },
    {
      "from": "004a0f88"
    },
    {
      "from": "004a73e4"
    },
    {
      "from": "004a23ef"
    },
    {
      "from": "005d3cdb"
    },
    {
      "from": "005ad8ce"
    },
    {
      "from": "005b7f47"
    },
    {
      "from": "005b8edc"
    },
    {
      "from": "005d2f1e"
    },
    {
      "from": "005d2f6b"
    },
    {
      "from": "005d34d5"
    },
    {
      "from": "005bbf9c"
    },
    {
      "from": "0058af6f"
    },
    {
      "from": "005abab7"
    },
    {
      "from": "005ac3f5"
    },
    {
      "from": "005b3b09"
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
