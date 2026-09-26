# Evidence 0x004eb930

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `84bb64f4a39cae7e1b250fa9335a99ca937cdebd72901b29ae4072ff076a2f32`

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
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET",
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
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "66af816f046702fe566689a37a0a1505b4750647f81f48348d088a6d597095bd",
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
        "obs-0006",
        "obs-0008",
        "obs-0012",
        "obs-0013",
        "obs-0014",
        "obs-0015"
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
        "obs-0005",
        "obs-0008",
        "obs-0009",
        "obs-0013",
        "obs-0015"
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
        "obs-0005",
        "obs-0008",
        "obs-0009",
        "obs-0013",
        "obs-0015"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0021"
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
      "at": "0x004eb930",
      "count": 11,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x004eb930",
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
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x004eb931",
      "count": 1,
      "first_use": 1,
      "first_write_index": 22,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x004eb931",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004eb933",
      "count": 4,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PU
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
"\nundefined1 FUN_004eb930(int *param_1,int *param_2)\n\n{\n  undefined1 local_8;\n  \n  if (((*param_1 == *param_2) && (param_1[1] == param_2[1])) && (param_1[2] == param_2[2])) {\n    local_8 = 1;\n  }\n  else {\n    local_8 = 0;\n  }\n  return local_8;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 25,
  "instructions": [
    {
      "address": "004eb930",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004eb931",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004eb933",
      "instruction": "PUSH ECX"
    },
    {
      "address": "004eb934",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004eb937",
      "instruction": "MOV ECX,dword ptr [EBP + 0xc]"
    },
    {
      "address": "004eb93a",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "004eb93c",
      "instruction": "CMP EDX,dword ptr [ECX]"
    },
    {
      "address": "004eb93e",
      "instruction": "JNZ 0x004eb965"
    },
    {
      "address": "004eb940",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004eb943",
      "instruction": "MOV ECX,dword ptr [EBP + 0xc]"
    },
    {
      "address": "004eb946",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "004eb949",
      "instruction": "CMP EDX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "004eb94c",
      "instruction": "JNZ 0x004eb965"
    },
    {
      "address": "004eb94e",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004eb951",
      "instruction": "MOV ECX,dword ptr [EBP + 0xc]"
    },
    {
      "address": "004eb954",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "004eb957",
      "instruction": "CMP EDX,dword ptr [ECX + 0x8]"
    },
    {
      "address": "004eb95a",
      "instruction": "JNZ 0x004eb965"
    },
    {
      "address": "004eb95c",
      "instruction": "MOV dword ptr [EBP + -0x4],0x1"
    },
    {
      "address": "004eb963",
      "instruction": "JMP 0x004eb96c"
    },
    {
      "address": "004eb965",
      "instruction": "MOV dword ptr [EBP + -0x4],0x0"
    },
    {
      "address": "004eb96c",
      "instruction": "MOV AL,byte ptr [EBP + -0x4]"
    },
    {
      "address": "004eb96f",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004eb971",
      "instruction": "POP EBP"
    },
    {
      "address": "004eb972",
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
  "body_end": "004eb972",
  "body_span_bytes": 67,
  "body_start": "004eb930",
  "callees": [],
  "callers": [
    "FUN_00df0830",
    "FUN_01072d40",
    "FUN_0066c490",
    "FUN_01056160",
    "Editors::cEditor::HandleMessage",
    "FUN_010568b0",
    "FUN_010593e0",
    "FUN_0107a6b0",
    "FUN_00e07e70",
    "FUN_00e2b9d0",
    "FUN_01050bb0",
    "FUN_0064c8e0",
    "FUN_00834fa0",
    "FUN_00c80a80",
    "FUN_00c57ad0",
    "FUN_00dd07f0",
    "FUN_004eb270",
    "FUN_005c2bc0",
    "FUN_00cc1c30"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "004eb930",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "int *"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:1",
      "type": "undefined1"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_004eb930",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xeb930",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004eb930(void)",
  "size_bytes": 67,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004eb930",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 53,
  "xrefs": [
    {
      "from": "004eb831"
    },
    {
      "from": "005c2c59"
    },
    {
      "from": "0064d0b6"
    },
    {
      "from": "00834fff"
    },
    {
      "from": "00c57b5c"
    },
    {
      "from": "00c80bcd"
    },
    {
      "from": "00df093a"
    },
    {
      "from": "00e0925f"
    },
    {
      "from": "00e2bedd"
    },
    {
      "from": "00e2c12a"
    },
    {
      "from": "01050e8e"
    },
    {
      "from": "01050ea9"
    },
    {
      "from": "01050ec4"
    },
    {
      "from": "01050f6c"
    },
    {
      "from": "01056a71"
    },
    {
      "from": "01056ac2"
    },
    {
      "from": "01056b19"
    },
    {
      "from": "01056272"
    },
    {
      "from": "0105630c"
    },
    {
      "from": "01056366"
    },
    {
      "from": "010563ef"
    },
    {
      "from": "010564c2"
    },
    {
      "from": "01056669"
    },
    {
      "from": "0105673d"
    },
    {
      "from": "01059d79"
    },
    {
      "from": "01059e2f"
    },
    {
      "from": "0107300d"
    },
    {
      "from": "0107a74b"
    },
    {
      "from": "00dd087f"
    },
    {
      "from": "00592cbf"
    },
    {
      "from": "00593413"
    },
    {
      "from": "0066c50c"
    },
    {
      "from": "00c53214"
    },
    {
      "from": "00c541ca"
    },
    {
      "from": "00c5428b"
    },
    {
      "from": "00c54312"
    },
    {
      "from": "00c547a1"
    },
    {
      "from": "00c548b6"
    },
    {
      "from": "00c54a2e"
    },
    {
      "from": "00c54a7b"
    },
    {
      "from": "00c54b0f"
    },
    {
      "from": "00c54c1f"
    },
    {
      "from": "00c54c5c"
    },
    {
      "from": "00c54cec"
    },
    {
      "from": "00c54d2c"
    },
    {
      "from": "00cc2855"
    },
    {
      "from": "00cc2867"
    },
    {
      "from": "00cc2879"
    },
    {
      "from": "00cc21fa"
    },
    {
      "from": "00ef7123"
    },
    {
      "from": "00f440f1"
    },
    {
      "from": "01033058"
    },
    {
      "from": "01033536"
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
