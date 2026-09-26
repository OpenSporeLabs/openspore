# Evidence 0x01021fd0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `29b25456af8a98fd24005a4a9b8eee66d905b966e2a3b1bc1f634f635f897057`

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
      "entry_ESP+0x10"
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
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
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
  "content_sha256": "75694a0da429bfc683b6023606098cccc80ddc3c5f4fd46b3e5dc247d51838ac",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0035"
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
        "obs-0003",
        "obs-0007",
        "obs-0011"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 3,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0018",
        "obs-0020"
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
        "obs-0006"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0035"
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
        "obs-0035"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0035"
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
      "at": "0x01021fd0",
      "count": 8,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x01021fd1",
      "count": 10,
      "first_use": 1,
      "first_write_index": 30,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x01021fd1",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x01021fd1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESP + 0x8]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01021fd5",
      "count": 5,
     
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
"\nvoid FUN_01021fd0(int param_1,int param_2,int param_3,undefined4 param_4)\n\n{\n  uint uVar1;\n  int *piVar2;\n  int iVar3;\n  \n  uVar1 = param_2 - param_1;\n  while ((0x70 < (int)(uVar1 & 0xfffffffc) && (0 < param_3))) {\n    piVar2 = (int *)FUN_01021180(param_1,param_1 + ((param_2 - param_1 >> 2) -\n                                                    (param_2 - param_1 >> 0x1f) >> 1) * 4,\n                                 param_2 + -4,param_4,param_4);\n    piVar2 = (int *)*piVar2;\n    if (piVar2 != (int *)0x0) {\n      (**(code **)(*piVar2 + 0xbc))(piVar2);\n    }\n    iVar3 = FUN_01021e50(param_1,param_2);\n    param_3 = param_3 + -1;\n    FUN_01021fd0(iVar3,param_2,param_3,param_4);\n    uVar1 = iVar3 - param_1;\n    param_2 = iVar3;\n  }\n  if (param_3 == 0) {\n    FUN_01021ed0(param_1,param_2,param_2,param_4);\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 69,
  "instructions": [
    {
      "address": "01021fd0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "01021fd1",
      "instruction": "MOV EBX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "01021fd5",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01021fd6",
      "instruction": "MOV EBP,dword ptr [ESP + 0x18]"
    },
    {
      "address": "01021fda",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01021fdb",
      "instruction": "PUSH EDI"
    },
    {
      "address": "01021fdc",
      "instruction": "MOV EDI,dword ptr [ESP + 0x18]"
    },
    {
      "address": "01021fe0",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "01021fe2",
      "instruction": "SUB EAX,EBX"
    },
    {
      "address": "01021fe4",
      "instruction": "AND EAX,0xfffffffc"
    },
    {
      "address": "01021fe7",
      "instruction": "CMP EAX,0x70"
    },
    {
      "address": "01021fea",
      "instruction": "JLE 0x01022054"
    },
    {
      "address": "01021fec",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "01021ff0",
      "instruction": "CMP dword ptr [ESP + 0x1c],0x0"
    },
    {
      "address": "01021ff5",
      "instruction": "JLE 0x01022059"
    },
    {
      "address": "01021ff7",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "01021ff9",
      "instruction": "SUB EAX,EBX"
    },
    {
      "address": "01021ffb",
      "instruction": "SAR EAX,0x2"
    },
    {
      "address": "01021ffe",
      "instruction": "CDQ"
    },
    {
      "address": "01021fff",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01022000",
      "instruction": "SUB EAX,EDX"
    },
    {
      "address": "01022002",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01022003",
      "instruction": "LEA ECX,[EDI + -0x4]"
    },
    {
      "address": "01022006",
      "instruction": "SAR EAX,0x1"
    },
    {
      "address": "01022008",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01022009",
      "instruction": "LEA EDX,[EBX + EAX*0x4]"
    },
    {
      "address": "0102200c",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0102200d",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0102200e",
      "instruction": "CALL 0x01021180"
    },
    {
      "address": "01022013",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "01022015",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "01022018",
      "instruction": "MOV EDX,ESP"
    },
    {
      "address": "0102201a",
      "instruction": "MOV dword ptr [EDX],ECX"
    },
    {
      "address": "0102201c",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0102201e",
      "instruction": "JZ 0x0102202a"
    },
    {
      "address": "01022020",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "01022022",
      "instruction": "MOV EDX,dword ptr [EAX + 0xbc]"
    },
    {
      "address": "01022028",
      "instruction": "CALL EDX"
    },
    {
      "address": "0102202a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0102202b",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0102202c",
      "instruction": "CALL 0x01021e50"
    },
    {
      "address": "01022031",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "01022033",
      "instruction": "MOV EAX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "01022037",
      "instruction": "DEC EAX"
    },
    {
      "address": "01022038",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01022039",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0102203a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0102203b",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0102203c",
      "instruction": "MOV dword ptr [ESP + 0x3c],EAX"
    },
    {
      "address": "01022040",
      "instruction": "CALL 0x01021fd0"
    },
    {
      "address": "01022045",
      "instruction": "MOV EDI,ESI"
    },
    {
      "address": "01022047",
      "instruction": "SUB ESI,EBX"
    },
    {
      "address": "01022049",
      "instruction": "AND ESI,0xfffffffc"
    },
    {
      "address": "0102204c",
      "instruction": "ADD ESP,0x20"
    },
    {
      "address": "0102204f",
      "instruction": "CMP ESI,0x70"
    },
    {
      "address": "01022052",
      "instruction": "JG 0x01021ff0"
    },
    {
      "address": "01022054",
      "instruction": "CMP dword ptr [ESP + 0x1c],0x0"
    },
    {
      "address": "01022059",
      "instruction": "JNZ 0x01022067"
    },
    {
      "address": "0102205b",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0102205c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0102205d",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0102205e",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0102205f",
      "instruction": "CALL 0x01021ed0"
    },
    {
      "address": "01022064",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "01022067",
      "instruction": "POP EDI"
    },
    {
      "address": "01022068",
      "instruction": "POP ESI"
    },
    {
      "address": "01022069",
      "instruction": "POP EBP"
    },
    {
      "address": "0102206a",
      "instruction": "POP EBX"
    },
    {
      "address": "0102206b",
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
  "body_end": "0102206b",
  "body_span_bytes": 156,
  "body_start": "01021fd0",
  "callees": [
    "FUN_01021fd0",
    "FUN_01021ed0",
    "FUN_01021180",
    "FUN_01021e50"
  ],
  "callers": [
    "FUN_01021fd0",
    "FUN_01022070"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01021fd0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
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
      "type": "int"
    },
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "uint"
    },
    {
      "name": "param_4",
      "storage": "Stack[0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "piVar2",
      "storage": "register:00000000:4",
      "type": "int *"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_01021fd0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc21fd0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01021fd0(void)",
  "size_bytes": 156,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01021fd0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "010220a4"
    },
    {
      "from": "01022040"
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
