# Evidence 0x00ff0350

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ce70d567e773b5f5711d21c091497d65f7b6e5d76970c4ee724154fe3263f8a5`

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
  "content_sha256": "3dfef072181d5d041178381c47a12976cc955e14a49332c4108982db76417503",
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
        "obs-0008"
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
        "obs-0002"
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
        "obs-0004"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          28
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0008"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
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
        "obs-0008"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00ff0350",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00ff0350",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00ff0350",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [ESP + 0x4]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00ff0356",
      "count": 3,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "ADDSS XMM0,dword ptr [ECX + 0x1c]",
      "reg": "ECX"
    },
    {
      "at": "0x00ff035b",
      "count": 3,
      "first_use": 2,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "XORPS XMM1,XMM1",
      "reg": "XMM1"
    },
    {
      "at": "0x00ff035b",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "XORPS XMM1,XMM1",
      "reg": "XMM1",
      "write_kind": "unknown"
    },
    {
      "at": "0x00ff035e",
      "count": 2,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "COMISS XMM1,XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00ff036d",
      "form": "RET 0x4",
      "id": "obs-0008",
      "imm": 4,
      "index": 7,
      "kind": "RET",
      "raw": "RET 0x4"
    }
  ],
  "parse": {
    "declared_count": 8,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
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
    "max_offset": 28,
    "offsets": [
      28
    ],
    "present": true,
    "register": 
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
"\nvoid __thiscall FUN_00ff0350(int param_1,float param_2)\n\n{\n  param_2 = param_2 + *(float *)(param_1 + 0x1c);\n  *(float *)(param_1 + 0x1c) = param_2;\n  if (param_2 < 0.0) {\n    *(undefined4 *)(param_1 + 0x1c) = 0;\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 8,
  "instructions": [
    {
      "address": "00ff0350",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00ff0356",
      "instruction": "ADDSS XMM0,dword ptr [ECX + 0x1c]"
    },
    {
      "address": "00ff035b",
      "instruction": "XORPS XMM1,XMM1"
    },
    {
      "address": "00ff035e",
      "instruction": "COMISS XMM1,XMM0"
    },
    {
      "address": "00ff0361",
      "instruction": "MOVSS dword ptr [ECX + 0x1c],XMM0"
    },
    {
      "address": "00ff0366",
      "instruction": "JBE 0x00ff036d"
    },
    {
      "address": "00ff0368",
      "instruction": "MOVSS dword ptr [ECX + 0x1c],XMM1"
    },
    {
      "address": "00ff036d",
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
  "body_end": "00ff036f",
  "body_span_bytes": 32,
  "body_start": "00ff0350",
  "callees": [],
  "callers": [
    "FUN_00c705c0",
    "FUN_00c72190",
    "FUN_00c704a0",
    "FUN_0103af90",
    "FUN_0103fe90"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00ff0350",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "float"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00ff0350",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xbf0350",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ff0350(void)",
  "size_bytes": 32,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ff0350",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 8,
  "xrefs": [
    {
      "from": "00c7068b"
    },
    {
      "from": "00c7056a"
    },
    {
      "from": "00c7232c"
    },
    {
      "from": "0103b032"
    },
    {
      "from": "0103b07c"
    },
    {
      "from": "01040065"
    },
    {
      "from": "010330ac"
    },
    {
      "from": "0103358a"
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
