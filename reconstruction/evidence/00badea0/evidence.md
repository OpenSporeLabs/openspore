# Evidence 0x00badea0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `14079da9fc87a1b421e79e31e43d6b8edf220b7d827830155bea94580e4c5688`

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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
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
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path",
    "unparsed_lines_present: 2 line(s) matched no grammar rule",
    "slot_width_ambiguous: one entry slot is read at more than one width",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "6296ef3c11cf97a222c96d86b9555920616c801efb9352a5880f241ea8120717",
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
        "obs-0028",
        "obs-0032"
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
        "obs-0009",
        "obs-0018",
        "obs-0019",
        "obs-0021"
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
        "obs-0009",
        "obs-0018",
        "obs-0019",
        "obs-0021"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          12,
          16,
          28
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0028",
        "obs-0032"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0019"
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
        "obs-0028",
        "obs-0032"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
      }
    },
    {
      "based_on": [
        "obs-0028",
        "obs-0032"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0028",
        "obs-0032"
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
      "at": "0x00badea0",
      "count": 3,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0xc]",
      "reg": "ECX"
    },
    {
      "at": "0x00badea0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0xc]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "and_esp": null,
      "at": "0x00badea3",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00badea3",
      "definite": true,
      "id": "obs-0004",
   
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
"\nundefined4 * __thiscall FUN_00badea0(int param_1,uint *param_2)\n\n{\n  undefined4 *puVar1;\n  undefined4 *puVar2;\n  undefined4 *puVar3;\n  undefined4 *puVar4;\n  uint local_8 [2];\n  \n  puVar1 = (undefined4 *)(param_1 + 4);\n  puVar4 = puVar1;\n  if (*(undefined4 **)(param_1 + 0xc) != (undefined4 *)0x0) {\n    puVar2 = *(undefined4 **)(param_1 + 0xc);\n    do {\n      if ((uint)puVar2[4] < *param_2) {\n        puVar3 = (undefined4 *)*puVar2;\n      }\n      else {\n        puVar3 = (undefined4 *)puVar2[1];\n        puVar4 = puVar2;\n      }\n      puVar2 = puVar3;\n    } while (puVar3 != (undefined4 *)0x0);\n  }\n  if ((puVar4 != puVar1) && ((uint)puVar4[4] <= *param_2)) {\n    return puVar4 + 5;\n  }\n  local_8[0] = *param_2;\n  param_2 = (uint *)((uint)param_2 & 0xffffff00);\n  local_8[1] = 0;\n  FUN_00baa660(&param_2,puVar4,local_8,param_2);\n  return (undefined4 *)((int)param_2 + 0x14);\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 51,
  "instructions": [
    {
      "address": "00badea0",
      "instruction": "MOV EAX,dword ptr [ECX + 0xc]"
    },
    {
      "address": "00badea3",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00badea6",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00badea7",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00badea8",
      "instruction": "LEA ESI,[ECX + 0x4]"
    },
    {
      "address": "00badeab",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00badeac",
      "instruction": "MOV EDI,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00badeb0",
      "instruction": "MOV EDX,ESI"
    },
    {
      "address": "00badeb2",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00badeb4",
      "instruction": "JZ 0x00badeca"
    },
    {
      "address": "00badeb6",
      "instruction": "MOV EBP,dword ptr [EDI]"
    },
    {
      "address": "00badeb8",
      "instruction": "CMP dword ptr [EAX + 0x10],EBP"
    },
    {
      "address": "00badebb",
      "instruction": "JC 0x00badec4"
    },
    {
      "address": "00badebd",
      "instruction": "MOV EDX,EAX"
    },
    {
      "address": "00badebf",
      "instruction": "MOV EAX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00badec2",
      "instruction": "JMP 0x00badec6"
    },
    {
      "address": "00badec4",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00badec6",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00badec8",
      "instruction": "JNZ 0x00badeb8"
    },
    {
      "address": "00badeca",
      "instruction": "CMP EDX,ESI"
    },
    {
      "address": "00badecc",
      "instruction": "JZ 0x00baded5"
    },
    {
      "address": "00badece",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00baded0",
      "instruction": "CMP EAX,dword ptr [EDX + 0x10]"
    },
    {
      "address": "00baded3",
      "instruction": "JNC 0x00badf11"
    },
    {
      "address": "00baded5",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00baded7",
      "instruction": "MOV dword ptr [ESP + 0xc],EAX"
    },
    {
      "address": "00badedb",
      "instruction": "MOV byte ptr [ESP + 0x18],0x0"
    },
    {
      "address": "00badee0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00badee4",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00badee5",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00badee9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00badeea",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00badeeb",
      "instruction": "MOV EAX,ESP"
    },
    {
      "address": "00badeed",
      "instruction": "MOV dword ptr [EAX],EDX"
    },
    {
      "address": "00badeef",
      "instruction": "LEA EDX,[ESP + 0x24]"
    },
    {
      "address": "00badef3",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00badef4",
      "instruction": "MOV dword ptr [ESP + 0x20],0x0"
    },
    {
      "address": "00badefc",
      "instruction": "CALL 0x00baa660"
    },
    {
      "address": "00badf01",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00badf05",
      "instruction": "ADD EAX,0x14"
    },
    {
      "address": "00badf08",
      "instruction": "POP EDI"
    },
    {
      "address": "00badf09",
      "instruction": "POP ESI"
    },
    {
      "address": "00badf0a",
      "instruction": "POP EBP"
    },
    {
      "address": "00badf0b",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00badf0e",
      "instruction": "RET 0x4"
    },
    {
      "address": "00badf11",
      "instruction": "POP EDI"
    },
    {
      "address": "00badf12",
      "instruction": "POP ESI"
    },
    {
      "address": "00badf13",
      "instruction": "LEA EAX,[EDX + 0x14]"
    },
    {
      "address": "00badf16",
      "instruction": "POP EBP"
    },
    {
      "address": "00badf17",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00badf1a",
      "instruction": "RET 0x4"
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
  "body_end": "00badf1c",
  "body_span_bytes": 125,
  "body_start": "00badea0",
  "callees": [
    "FUN_00baa660"
  ],
  "callers": [
    "FUN_0102daa0",
    "Simulator::Cell::cCellGFX::PreloadCellResource",
    "FUN_00e063d0",
    "FUN_00e064f0",
    "FUN_00fe5a20",
    "FUN_00bb3750",
    "FUN_00fe5520",
    "FUN_00fe4fa0",
    "FUN_00bb8b20",
    "FUN_00baf590"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00badea0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "puVar4",
      "storage": "register:00000008:4",
      "type": "undefined4 *"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "uint[2]"
    },
    {
      "name": "puVar3",
      "storage": "register:00000000:4",
      "type": "undefined4 *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "uint *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "puVar2",
      "storage": "register:00000000:4",
      "type": "undefined4 *"
    },
    {
      "name": "puVar1",
      "storage": "unique:00006600:4",
      "type": "undefined4 *"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00badea0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7adea0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00badea0(void)",
  "size_bytes": 125,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00badea0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 15,
  "xrefs": [
    {
      "from": "00bb37c8"
    },
    {
      "from": "00bb9602"
    },
    {
      "from": "00e06501"
    },
    {
      "from": "0102dc2d"
    },
    {
      "from": "0102dcd7"
    },
    {
      "from": "00fe553a"
    },
    {
      "from": "00baf59b"
    },
    {
      "from": "00e663ea"
    },
    {
      "from": "00fe51bf"
    },
    {
      "from": "00fe51da"
    },
    {
      "from": "00fe51ec"
    },
    {
      "from": "00fe5a5b"
    },
    {
      "from": "00fe5aec"
    },
    {
      "from": "00fe5bab"
    },
    {
      "from": "00e06419"
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
