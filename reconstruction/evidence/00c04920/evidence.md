# Evidence 0x00c04920

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c307fb8ed26512a568c013ec8d17ad56166023e9920f39bfdf9dcba405a19bd8`

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
      }
    ],
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_used_as_counter",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_used_as_counter), and the convention rule that would apply discriminates on receiver absence",
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
  "content_sha256": "c1bfb2212580123e605cafbe513c944e10cfef035ec203e57da5d4e7d365b5d8",
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
        "obs-0021"
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
        "obs-0002",
        "obs-0004",
        "obs-0007",
        "obs-0011",
        "obs-0016",
        "obs-0017",
        "obs-0018"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 4,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0013"
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
        "obs-0013"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_used_as_counter) and every remaining discriminator needs receiver absence",
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
        "obs-0015"
      ],
      "claim": "a bulk string write reaches the return register, which is not a struct-return signature",
      "confidence": "INFERRED",
      "id": "RT4",
      "value": {
        "bulk_write": true
      }
    },
    {
      "based_on": [
        "obs-0021"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0021"
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
      "at": "0x00c04920",
      "count": 7,
      "first_use": 0,
    
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
"\nvoid FUN_00c04920(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)\n\n{\n  int iVar1;\n  undefined4 *puVar2;\n  undefined4 *puVar3;\n  \n  *param_1 = param_4;\n  if (param_2 != param_3) {\n    do {\n      if (param_4 != (undefined4 *)0x0) {\n        puVar2 = param_2;\n        puVar3 = param_4;\n        for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {\n          *puVar3 = *puVar2;\n          puVar2 = puVar2 + 1;\n          puVar3 = puVar3 + 1;\n        }\n      }\n      param_2 = param_2 + 8;\n      param_4 = param_4 + 8;\n    } while (param_2 != param_3);\n    *param_1 = param_4;\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 23,
  "instructions": [
    {
      "address": "00c04920",
      "instruction": "MOV EDX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c04924",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00c04928",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c04929",
      "instruction": "MOV ESI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00c0492d",
      "instruction": "MOV dword ptr [EAX],EDX"
    },
    {
      "address": "00c0492f",
      "instruction": "CMP ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c04933",
      "instruction": "JZ 0x00c0495a"
    },
    {
      "address": "00c04935",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c04936",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "00c04938",
      "instruction": "JZ 0x00c04947"
    },
    {
      "address": "00c0493a",
      "instruction": "MOV ECX,0x8"
    },
    {
      "address": "00c0493f",
      "instruction": "MOV EDI,EDX"
    },
    {
      "address": "00c04941",
      "instruction": "MOVSD.REP ES:EDI,ESI"
    },
    {
      "address": "00c04943",
      "instruction": "MOV ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c04947",
      "instruction": "ADD ESI,0x20"
    },
    {
      "address": "00c0494a",
      "instruction": "ADD EDX,0x20"
    },
    {
      "address": "00c0494d",
      "instruction": "MOV dword ptr [ESP + 0x10],ESI"
    },
    {
      "address": "00c04951",
      "instruction": "CMP ESI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00c04955",
      "instruction": "JNZ 0x00c04936"
    },
    {
      "address": "00c04957",
      "instruction": "MOV dword ptr [EAX],EDX"
    },
    {
      "address": "00c04959",
      "instruction": "POP EDI"
    },
    {
      "address": "00c0495a",
      "instruction": "POP ESI"
    },
    {
      "address": "00c0495b",
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
  "body_end": "00c0495b",
  "body_span_bytes": 60,
  "body_start": "00c04920",
  "callees": [],
  "callers": [
    "FUN_0096e540",
    "FUN_00ec7d00",
    "FUN_0089a370",
    "FUN_00898e10",
    "FUN_00c065a0",
    "FUN_00c06b10",
    "FUN_00899c90",
    "FUN_008991f0",
    "FUN_00dfd080"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00c04920",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "puVar3",
      "storage": "register:0000001c:4",
      "type": "undefined4 *"
    },
    {
      "name": "puVar2",
      "storage": "register:00000018:4",
      "type": "undefined4 *"
    },
    {
      "name": "iVar1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_4",
      "storage": "Stack[0x10]:4",
      "type": "undefined4 *"
    },
    {
      "name": "param_3",
      "storage": "Stack[0xc]:4",
      "type": "undefined4 *"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "undefined4 *"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4 *"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00c04920",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x804920",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c04920(void)",
  "size_bytes": 60,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c04920",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 15,
  "xrefs": [
    {
      "from": "00899ceb"
    },
    {
      "from": "00899d42"
    },
    {
      "from": "0089929a"
    },
    {
      "from": "00898e4a"
    },
    {
      "from": "0089a3c9"
    },
    {
      "from": "0089a41a"
    },
    {
      "from": "0089a43d"
    },
    {
      "from": "0089a4c0"
    },
    {
      "from": "0096e59b"
    },
    {
      "from": "0096e5f2"
    },
    {
      "from": "00c06bb2"
    },
    {
      "from": "00c065e3"
    },
    {
      "from": "00dfd22f"
    },
    {
      "from": "00ec7d5b"
    },
    {
      "from": "00ec7db2"
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
