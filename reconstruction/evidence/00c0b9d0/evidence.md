# Evidence 0x00c0b9d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `adbb2df52fe904483032a3ed4bac28ca38221dd2fc9e5a9de3a51ba88c195f2d`

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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
  "content_sha256": "cd840c601d3185437ab2f000376337a5fa6e3317543f176aba57ac26b9468cf0",
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
        "obs-0014"
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
        "obs-0004"
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
        "obs-0013"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          3004
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0014"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0014"
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
      "at": "0x00c0b9d0",
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
      "at": "0x00c0b9d0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c0b9d3",
      "count": 5,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x14]",
      "reg": "ESP"
    },
    {
      "at": "0x00c0b9d3",
      "base": "ESP",
      "disp": 20,
      "id": "obs-0004",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x14]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00c0b9d3",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x14]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00c0b9d9",
      "count": 3,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [ESP],XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00c0b9d9",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0007",
      "index": 2,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOVSS dword ptr [ESP],XMM0",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00c0b9de",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0008",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOVSS XMM0,dword ptr [ESP]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x00c0b9e3",
      "id": "obs-0009",
      "index": 4,
      "kind": "UNPARSED",
      "raw": "MAXSS XMM0,dword ptr [0x01687a04]",
      "reason": "unknown_mnemonic"
    },
    {
      "at": "0x00c0b9eb",
      "id": "obs-0010",
      "index": 5,
      "
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
"\nvoid __thiscall FUN_00c0b9d0(int param_1,float param_2)\n\n{\n  if (param_2 <= DAT_01687a04) {\n    param_2 = DAT_01687a04;\n  }\n  if (DAT_01687a00 <= param_2) {\n    param_2 = DAT_01687a00;\n  }\n  *(float *)(param_1 + 0xbbc) = param_2;\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 11,
  "instructions": [
    {
      "address": "00c0b9d0",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "00c0b9d3",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00c0b9d9",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00c0b9de",
      "instruction": "MOVSS XMM0,dword ptr [ESP]"
    },
    {
      "address": "00c0b9e3",
      "instruction": "MAXSS XMM0,dword ptr [0x01687a04]"
    },
    {
      "address": "00c0b9eb",
      "instruction": "MINSS XMM0,dword ptr [0x01687a00]"
    },
    {
      "address": "00c0b9f3",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00c0b9f8",
      "instruction": "MOVSS XMM0,dword ptr [ESP]"
    },
    {
      "address": "00c0b9fd",
      "instruction": "MOVSS dword ptr [ECX + 0xbbc],XMM0"
    },
    {
      "address": "00c0ba05",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00c0ba08",
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
  "body_end": "00c0ba0a",
  "body_span_bytes": 59,
  "body_start": "00c0b9d0",
  "callees": [],
  "callers": [
    "FUN_00db0b80",
    "FUN_00c0d440",
    "FUN_00dbc7a0",
    "FUN_00bd6eb0",
    "FUN_00d35190",
    "FUN_00d85ad0",
    "FUN_00d54330",
    "FUN_00c09fa0",
    "FUN_00dabdf0",
    "FUN_00c22ae0",
    "FUN_00c8fb50",
    "FUN_00d74060",
    "FUN_00d3fcf0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00c0b9d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "float"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00c0b9d0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x80b9d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c0b9d0(void)",
  "size_bytes": 59,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c0b9d0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 16,
  "xrefs": [
    {
      "from": "00c0ac65"
    },
    {
      "from": "00c0d50c"
    },
    {
      "from": "00c22bf1"
    },
    {
      "from": "00d3fed7"
    },
    {
      "from": "00d5443f"
    },
    {
      "from": "00d85aef"
    },
    {
      "from": "00db0c47"
    },
    {
      "from": "00d3571a"
    },
    {
      "from": "00dac3f9"
    },
    {
      "from": "00dac435"
    },
    {
      "from": "00d75325"
    },
    {
      "from": "00dbcd34"
    },
    {
      "from": "00bd6f55"
    },
    {
      "from": "00bd6fa3"
    },
    {
      "from": "00c8fb74"
    },
    {
      "from": "00d7724b"
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
