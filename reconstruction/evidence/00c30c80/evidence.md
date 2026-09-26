# Evidence 0x00c30c80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c903adb1d67a92a6d09cf09b3791083151d9c09870599f6ea91caaa4c3d81afd`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +4, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "afc35ef12a2fd391af1b67caae027c90163c7c1a2db2e5f211e83855c36b9fd1",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
        "obs-0008"
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
        "obs-0001",
        "obs-0002",
        "obs-0005"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          176
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0005",
        "obs-0008"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0008"
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
        "obs-0007",
        "obs-0008"
      ],
      "claim": "the function can reach a caller by transferring out of the listing, so the path that actually returns was never observed",
      "confidence": "UNKNOWN",
      "id": "T2",
      "value": {
        "form": "epilogue_then_jmp"
      }
    },
    {
      "based_on": [
        "obs-0008"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00c30c80",
      "count": 1,
      "first_use": 0,
      "first_write_index": 5,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0xb0]",
      "reg": "ECX"
    },
    {
      "at": "0x00c30c80",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0xb0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c30c8b",
      "count": 4,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00c30c8c",
      "id": "obs-0004",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d2a0",
      "target": "0x00b3d2a0"
    },
    {
      "at": "0x00c30c91",
      "definite": true,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00c30c93",
      "id": "obs-0006",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00ba6d80",
      "target": "0x00ba6d80"
    },
    {
      "at": "0x00c30c9e",
      "id": "obs-0007",
      "index": 10,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x00bba500",
      "target": "0x00bba500"
    },
    {
      "at": "0x00c30ca5",
      "form": "RET",
      "id": "obs-0008",
      "imm": null,
      "index": 12,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 13,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": false,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "INFERRED",
    "distinct_offsets": 1,
    "max_offset": 176,
    "offsets": [
      176
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "integral",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-
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
"\nundefined4 __fastcall FUN_00c30c80(int param_1)\n\n{\n  int iVar1;\n  undefined4 uVar2;\n  \n  iVar1 = *(int *)(param_1 + 0xb0);\n  if (iVar1 != -1) {\n    FUN_00b3d2a0(iVar1);\n    iVar1 = FUN_00ba6d80(iVar1);\n    if (iVar1 != 0) {\n      uVar2 = FUN_00bba500();\n      return uVar2;\n    }\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 13,
  "instructions": [
    {
      "address": "00c30c80",
      "instruction": "MOV EAX,dword ptr [ECX + 0xb0]"
    },
    {
      "address": "00c30c86",
      "instruction": "CMP EAX,-0x1"
    },
    {
      "address": "00c30c89",
      "instruction": "JZ 0x00c30ca3"
    },
    {
      "address": "00c30c8b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c30c8c",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00c30c91",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c30c93",
      "instruction": "CALL 0x00ba6d80"
    },
    {
      "address": "00c30c98",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c30c9a",
      "instruction": "JZ 0x00c30ca3"
    },
    {
      "address": "00c30c9c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c30c9e",
      "instruction": "JMP 0x00bba500"
    },
    {
      "address": "00c30ca3",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00c30ca5",
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
  "body_end": "00c30ca5",
  "body_span_bytes": 38,
  "body_start": "00c30c80",
  "callees": [
    "FUN_00ba6d80",
    "FUN_00b3d2a0",
    "FUN_00bba500"
  ],
  "callers": [
    "FUN_00e39ab0",
    "FUN_01016070",
    "FUN_00d065a0",
    "FUN_00e1bbc0",
    "FUN_00fde3e0",
    "FUN_00cbc7f0",
    "FUN_00fe0570",
    "FUN_00aebe90",
    "FUN_01005d80",
    "FUN_0102ce30",
    "FUN_00c49140",
    "FUN_00c32cd0",
    "FUN_00c737a0",
    "FUN_00c49180",
    "FUN_00ba5bd3"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c30c80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "uVar2",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00c30c80",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x830c80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c30c80(void)",
  "size_bytes": 38,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c30c80",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 22,
  "xrefs": [
    {
      "from": "00c32f2a"
    },
    {
      "from": "00c738d5"
    },
    {
      "from": "00ba5c59"
    },
    {
      "from": "00d066be"
    },
    {
      "from": "00aec21b"
    },
    {
      "from": "00e39ae4"
    },
    {
      "from": "00e39b43"
    },
    {
      "from": "0102ceb3"
    },
    {
      "from": "00fdea37"
    },
    {
      "from": "01005d92"
    },
    {
      "from": "00c4914e"
    },
    {
      "from": "00c4918e"
    },
    {
      "from": "00cbc8c2"
    },
    {
      "from": "00e1bfeb"
    },
    {
      "from": "010161ac"
    },
    {
      "from": "00fe08e3"
    },
    {
      "from": "00c5c43c"
    },
    {
      "from": "00cfa774"
    },
    {
      "from": "0100c366"
    },
    {
      "from": "0100c413"
    },
    {
      "from": "0104b2b4"
    },
    {
      "from": "0104b2cb"
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
