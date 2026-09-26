# Evidence 0x004ad550

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `3387124b3ad5a4383497f9b9338ee3bef81be73ccf6b714ff04910c62af6223e`

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
      },
      {
        "ebp_offset": "EBP+0xc",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
      },
      {
        "ebp_offset": "EBP+0xc",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "792381be6c73f12f846aafc70f53987d3642bdbca46b136c0f5f4de006700454",
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
        "obs-0070"
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
        "obs-0047",
        "obs-0066",
        "obs-0068"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0016",
        "obs-0017",
        "obs-0024",
        "obs-0026",
        "obs-0028",
        "obs-0032",
        "obs-0033",
        "obs-0036",
        "obs-0041",
        "obs-0045",
        "obs-0046",
        "obs-0051",
        "obs-0053",
        "obs-0055",
        "obs-0057",
        "obs-0060",
        "obs-0061",
        "obs-0063",
        "obs-0066"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          24
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0016",
        "obs-0017",
        "obs-0024",
        "obs-0026",
        "obs-0028",
        "obs-0032",
        "obs-0033",
        "obs-0036",
        "obs-0041",
        "obs-0045",
        "obs-0046",
        "obs-0051",
        "obs-0053",
        "obs-0055",
        "obs-0057",
        "obs-0060",
        "obs-0061",
        "obs-0063",
        "obs-0066",
        "obs-0070"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0070"
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
        "obs-0070"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0070"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x004ad550",
      "count": 52,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x004ad550",
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
      "sub": 176
    },
    {
      "at": "0x004ad551",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "reg":
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
"\nundefined4 __thiscall FUN_004ad550(int param_1,undefined4 param_2,char param_3)\n\n{\n  char cVar1;\n  undefined4 *puVar2;\n  undefined4 uVar3;\n  undefined1 local_58 [24];\n  undefined1 local_40 [24];\n  int local_28;\n  int local_24;\n  undefined4 local_20;\n  undefined4 local_1c;\n  undefined4 local_18;\n  undefined4 local_14;\n  undefined4 local_10;\n  undefined4 local_c;\n  int local_8;\n  \n  FUN_00409c00();\n  FUN_00409c00();\n  local_8 = *(int *)(param_1 + 0x1c) - *(int *)(param_1 + 0x18) >> 2;\n  if (local_8 != 0) {\n    puVar2 = (undefined4 *)FUN_0044ae00(local_40,0,0,0);\n    local_14 = puVar2[3];\n    local_10 = puVar2[4];\n    local_c = puVar2[5];\n    local_20 = *puVar2;\n    local_1c = puVar2[1];\n    local_18 = puVar2[2];\n    local_28 = 1;\n    local_24 = *(int *)(param_1 + 0x1c) - *(int *)(param_1 + 0x18) >> 2;\n    for (; local_28 < local_24; local_28 = local_28 + 1) {\n      if ((param_3 == '\\0') || (cVar1 = FUN_00435d40(), cVar1 != '\\0')) {\n        uVar3 = FUN_0044ae00(local_58,0,0,0);\n        FUN_0043f050(uVar3);\n      }\n    }\n  }\n  FUN_00511140(&local_20);\n  return param_2;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 112,
  "instructions": [
    {
      "address": "004ad550",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004ad551",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004ad553",
      "instruction": "SUB ESP,0xb0"
    },
    {
      "address": "004ad559",
      "instruction": "MOV dword ptr [EBP + 0xffffff50],ECX"
    },
    {
      "address": "004ad55f",
      "instruction": "LEA ECX,[EBP + -0x1c]"
    },
    {
      "address": "004ad562",
      "instruction": "CALL 0x00409c00"
    },
    {
      "address": "004ad567",
      "instruction": "LEA ECX,[EBP + -0x1c]"
    },
    {
      "address": "004ad56a",
      "instruction": "CALL 0x00409c00"
    },
    {
      "address": "004ad56f",
      "instruction": "MOV EAX,dword ptr [EBP + 0xffffff50]"
    },
    {
      "address": "004ad575",
      "instruction": "ADD EAX,0x18"
    },
    {
      "address": "004ad578",
      "instruction": "MOV dword ptr [EBP + 0xffffff78],EAX"
    },
    {
      "address": "004ad57e",
      "instruction": "MOV ECX,dword ptr [EBP + 0xffffff78]"
    },
    {
      "address": "004ad584",
      "instruction": "MOV EDX,dword ptr [EBP + 0xffffff78]"
    },
    {
      "address": "004ad58a",
      "instruction": "MOV EAX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "004ad58d",
      "instruction": "SUB EAX,dword ptr [EDX]"
    },
    {
      "address": "004ad58f",
      "instruction": "SAR EAX,0x2"
    },
    {
      "address": "004ad592",
      "instruction": "MOV dword ptr [EBP + -0x4],EAX"
    },
    {
      "address": "004ad595",
      "instruction": "CMP dword ptr [EBP + -0x4],0x0"
    },
    {
      "address": "004ad599",
      "instruction": "JBE 0x004ad6d8"
    },
    {
      "address": "004ad59f",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "004ad5a1",
      "instruction": "SHL ECX,0x2"
    },
    {
      "address": "004ad5a4",
      "instruction": "MOV EDX,dword ptr [EBP + 0xffffff50]"
    },
    {
      "address": "004ad5aa",
      "instruction": "ADD ECX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "004ad5ad",
      "instruction": "MOV dword ptr [EBP + 0xffffff74],ECX"
    },
    {
      "address": "004ad5b3",
      "instruction": "MOV EAX,dword ptr [EBP + 0xffffff74]"
    },
    {
      "address": "004ad5b9",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "004ad5bb",
      "instruction": "MOV dword ptr [EBP + 0xffffff70],ECX"
    },
    {
      "address": "004ad5c1",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "004ad5c3",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "004ad5c5",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "004ad5c7",
      "instruction": "LEA EDX,[EBP + -0x3c]"
    },
    {
      "address": "004ad5ca",
      "instruction": "PUSH EDX"
    },
    {
      "address": "004ad5cb",
      "instruction": "MOV ECX,dword ptr [EBP + 0xffffff70]"
    },
    {
      "address": "004ad5d1",
      "instruction": "CALL 0x0044ae00"
    },
    {
      "address": "004ad5d6",
      "instruction": "MOV dword ptr [EBP + 0xffffff6c],EAX"
    },
    {
      "address": "004ad5dc",
      "instruction": "MOV EAX,dword ptr [EBP + 0xffffff6c]"
    },
    {
      "address": "004ad5e2",
      "instruction": "ADD EAX,0xc"
    },
    {
      "address": "004ad5e5",
      "instruction": "LEA ECX,[EBP + -0x10]"
    },
    {
      "address": "004ad5e8",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "004ad5ea",
      "instruction": "MOV dword ptr [ECX],EDX"
    },
    {
      "address": "004ad5ec",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "004ad5ef",
      "instruction": "MOV dword ptr [ECX + 0x4],EDX"
    },
    {
      "address": "004ad5f2",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "004ad5f5",
      "instruction": "MOV dword ptr [ECX + 0x8],EAX"
    },
    {
      "address": "004ad5f8",
      "instruction": "MOV ECX,dword ptr [EBP + 0xffffff6c]"
    },
    {
      "address": "004ad5fe",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "004ad600",
      "instruction": "MOV dword ptr [EBP + -0x1c],EDX"
    },
    {
      "address": "004ad603",
      "instruction": "MOV EAX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "004ad606",
      "instruction": "MOV dword ptr [EBP + -0x18],EAX"
    },
    {
      "address": "004ad609",
      "instruction": "MOV ECX,dword ptr [ECX + 0x8]"
    },
    {
      "address": "004ad60c",
      "instruction": "MOV dword ptr [EBP + -0x14],ECX"
    },
    {
      "address": "004ad60f",
      "instruction": "MOV dword ptr [EBP + -0x24],0x1"
    },
    {
      "address": "004ad616",
      "instruction": "MOV EDX,dword ptr [EBP + 0xffffff50]"
    },
    {
      "address": "004ad61c",
      "instruction": "ADD EDX,0x18"
    },
    {
      "address": "004ad61f",
      "instruction": "MOV dword ptr [EBP + 0xffffff68],EDX"
    },
    {
      "address": "004ad625",
      "instruction": "MOV EAX,dword ptr [EBP + 0xffffff68]"
    },
    {
      "address": "004ad62b",
      "instruction": "MOV ECX,dword ptr [EBP + 0xffffff68]"
    },
    {
      "address": "004ad631",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "004ad634",
      "instruction": "SUB EDX,dword ptr [ECX]"
    },
    {
      "address": "004ad636",
      "instruction": "SAR EDX,0x2"
    },
    {
      "address": "004ad639",
      "instruction": "MOV dword ptr [EBP + -0x20],EDX"
    },
    {
      "address": "004ad63c",
      "instruction": "JMP 0x004ad647"
    },
    {
      "address": "004ad63e",
      "instruction": "MOV EAX,dword ptr [EBP + -0x24]"
    },
    {
      "address": "004ad641",
      "instruction": "ADD EAX,0x1"
    },
    {
      "address": "004ad644",
      "instruction": "MOV dword ptr [EBP + -0x24],EAX"
    },
    {
      "address": "004ad647",
      "instruction": "MOV ECX,dword pt
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
  "body_end": "004ad6ec",
  "body_span_bytes": 413,
  "body_start": "004ad550",
  "callees": [
    "FUN_00409c00",
    "FUN_0044ae00",
    "FUN_00511140",
    "FUN_00435d40",
    "FUN_0043f050"
  ],
  "callers": [
    "FUN_00583c50",
    "FUN_005ae300",
    "FUN_00580700",
    "Editors::cEditor::SetEditorModel",
    "FUN_00574b40",
    "FUN_005addb0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "004ad550",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_3",
      "storage": "Stack[0x8]:1",
      "type": "char"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "puVar2",
      "storage": "register:00000000:4",
      "type": "undefined4 *"
    },
    {
      "name": "uVar3",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "int"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "int"
    },
    {
      "name": "local_40",
      "storage": "",
      "type": "undefined1[24]"
    },
    {
      "name": "local_58",
      "storage": "",
      "type": "undefined1[24]"
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
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "int"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 17,
  "mode": "live",
  "name": "FUN_004ad550",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xad550",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004ad550(void)",
  "size_bytes": 413,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004ad550",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00574bb4"
    },
    {
      "from": "00583e94"
    },
    {
      "from": "0058072b"
    },
    {
      "from": "00586ee8"
    },
    {
      "from": "005addc6"
    },
    {
      "from": "005ae348"
    },
    {
      "from": "005ae35d"
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
