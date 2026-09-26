# Evidence 0x004d3d70

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c6fc45ec742fecb4ba181afeff7b3835d1fd9457cce6211c25e2b8dc0af29521`

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
          1
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
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "2a9bb4c51d557f9d6f2c27f654d17dd87ba7844aff5fbbe1623fb7312480cc2b",
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
        "obs-0016"
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
        "obs-0008"
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
        "obs-0005",
        "obs-0006",
        "obs-0009",
        "obs-0010"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          308
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0009",
        "obs-0010",
        "obs-0016"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0016"
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
      "at": "0x004d3d70",
      "count": 6,
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
      "at": "0x004d3d70",
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
      "at": "0x004d3d71",
      "count": 1,
      "first_use": 1,
      "first_write_index": 12,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x004d3d71",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004d3d73",
      "count": 3,
      "first_use": 2,
      "first_write_index": 7,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x004d3d74",
      "base": "EBP",
      "disp": -4,
      "id": "obs-0006",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x4],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x004d3d77",
      "count": 1,
      "first_use": 4,
      "first_write_index": null,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOVZX EAX,byte ptr [EBP + 0x8]",
      "reg": "EAX"
    },
    {
      "at": "0x004d3d77",
      "base": "EBP",
      "disp": 8,
      "id": "obs-0008",
      "index": 4,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOVZX EAX,byte ptr [EBP + 0x8]",
      "resolved": true,
      "size": 1
    },
    {
      "at": "0x004d3d7f",
      "base": "EBP",
      "disp": -4,
      "id": "obs-0009",
      "index": 7,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [EBP + -0x4]",
   
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
"\nfloat10 __thiscall FUN_004d3d70(int param_1,char param_2)\n\n{\n  float fVar1;\n  \n  if (param_2 == '\\0') {\n    fVar1 = *(float *)(param_1 + 0x134);\n  }\n  else {\n    fVar1 = *(float *)(param_1 + 0x138);\n  }\n  return (float10)fVar1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 15,
  "instructions": [
    {
      "address": "004d3d70",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004d3d71",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004d3d73",
      "instruction": "PUSH ECX"
    },
    {
      "address": "004d3d74",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "004d3d77",
      "instruction": "MOVZX EAX,byte ptr [EBP + 0x8]"
    },
    {
      "address": "004d3d7b",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "004d3d7d",
      "instruction": "JZ 0x004d3d8c"
    },
    {
      "address": "004d3d7f",
      "instruction": "MOV ECX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004d3d82",
      "instruction": "FLD float ptr [ECX + 0x138]"
    },
    {
      "address": "004d3d88",
      "instruction": "JMP 0x004d3d95"
    },
    {
      "address": "004d3d8c",
      "instruction": "MOV EDX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004d3d8f",
      "instruction": "FLD float ptr [EDX + 0x134]"
    },
    {
      "address": "004d3d95",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004d3d97",
      "instruction": "POP EBP"
    },
    {
      "address": "004d3d98",
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
  "body_end": "004d3d9a",
  "body_span_bytes": 43,
  "body_start": "004d3d70",
  "callees": [],
  "callers": [
    "FUN_00d697a0",
    "FUN_00c1de20",
    "FUN_00c08350",
    "FUN_00d1e4b0",
    "FUN_00c09410",
    "FUN_00d7ff20",
    "FUN_00d80a50",
    "FUN_00d1e930",
    "FUN_00c12410"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "004d3d70",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_2",
      "storage": "Stack[0x4]:1",
      "type": "char"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "fVar1",
      "storage": "unique:0000a900:4",
      "type": "float"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_004d3d70",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xd3d70",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004d3d70(void)",
  "size_bytes": 43,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004d3d70",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 16,
  "xrefs": [
    {
      "from": "00c08dff"
    },
    {
      "from": "00c09702"
    },
    {
      "from": "00c12573"
    },
    {
      "from": "00c1e04e"
    },
    {
      "from": "00c1e0a5"
    },
    {
      "from": "00c1e388"
    },
    {
      "from": "00d1e503"
    },
    {
      "from": "00d69fec"
    },
    {
      "from": "00d6a0af"
    },
    {
      "from": "00d6a973"
    },
    {
      "from": "00d8006a"
    },
    {
      "from": "00d80f26"
    },
    {
      "from": "00d1ee27"
    },
    {
      "from": "00d1ee98"
    },
    {
      "from": "00d1eee6"
    },
    {
      "from": "00c1ee62"
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
