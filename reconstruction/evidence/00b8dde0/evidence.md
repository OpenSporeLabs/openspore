# Evidence 0x00b8dde0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `067e842de9d5f9043c53d3fb359fd7215c4aadc372847eaa24e6c8b9b82cdb1f`

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
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "e575115b425fda6b855311d0b9a74ca9ca5ab557e91ea1fd81dca28f1dbb05e4",
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
        "obs-0006",
        "obs-0007"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          420,
          424,
          428
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
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
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008"
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
      "at": "0x00b8dde0",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00b8dde0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00b8dde0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b8dde4",
      "count": 7,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x00b8dde4",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b8dde6",
      "count": 6,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "CMP EDX,dword ptr [ECX + 0x1a4]",
      "reg": "ECX"
    },
    {
      "at": "0x00b8de06",
      "count": 2,
      "first_use": 11,
      "first_write_index": 1,
      "id": "obs-0007",
      "index": 11,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ECX + 0x1a4],EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00b8de1e",
      "form": "RET 0x8",
      "id": "obs-0008",
      "imm": 8,
      "index": 16,
      "kind": "RET",
      "raw": "RET 0x8"
    }
  ],
  "parse": {
    "declared_count": 17,
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
      "sub
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
"\nvoid __thiscall FUN_00b8dde0(int param_1,int *param_2)\n\n{\n  if (((*param_2 != *(int *)(param_1 + 0x1a4)) || (param_2[1] != *(int *)(param_1 + 0x1a8))) ||\n     (param_2[2] != *(int *)(param_1 + 0x1ac))) {\n    *(int *)(param_1 + 0x1a4) = *param_2;\n    *(int *)(param_1 + 0x1a8) = param_2[1];\n    *(int *)(param_1 + 0x1ac) = param_2[2];\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 17,
  "instructions": [
    {
      "address": "00b8dde0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00b8dde4",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00b8dde6",
      "instruction": "CMP EDX,dword ptr [ECX + 0x1a4]"
    },
    {
      "address": "00b8ddec",
      "instruction": "JNZ 0x00b8de04"
    },
    {
      "address": "00b8ddee",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00b8ddf1",
      "instruction": "CMP EDX,dword ptr [ECX + 0x1a8]"
    },
    {
      "address": "00b8ddf7",
      "instruction": "JNZ 0x00b8de04"
    },
    {
      "address": "00b8ddf9",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00b8ddfc",
      "instruction": "CMP EDX,dword ptr [ECX + 0x1ac]"
    },
    {
      "address": "00b8de02",
      "instruction": "JZ 0x00b8de1e"
    },
    {
      "address": "00b8de04",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00b8de06",
      "instruction": "MOV dword ptr [ECX + 0x1a4],EDX"
    },
    {
      "address": "00b8de0c",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00b8de0f",
      "instruction": "MOV dword ptr [ECX + 0x1a8],EDX"
    },
    {
      "address": "00b8de15",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00b8de18",
      "instruction": "MOV dword ptr [ECX + 0x1ac],EAX"
    },
    {
      "address": "00b8de1e",
      "instruction": "RET 0x8"
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
  "body_end": "00b8de20",
  "body_span_bytes": 65,
  "body_start": "00b8dde0",
  "callees": [],
  "callers": [
    "FUN_00bb2a50",
    "FUN_00ba6120",
    "FUN_00ba6310",
    "FUN_00bbac80",
    "FUN_00ba64a0",
    "FUN_00bbaa80",
    "FUN_00ba5fd0",
    "FUN_00f37690",
    "FUN_00ba8830",
    "FUN_00ba7c20",
    "FUN_00c713c0",
    "FUN_00de6f20"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00b8dde0",
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
      "type": "int *"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00b8dde0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x78dde0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b8dde0(void)",
  "size_bytes": 65,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b8dde0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 16,
  "xrefs": [
    {
      "from": "00ba8938"
    },
    {
      "from": "00ba6355"
    },
    {
      "from": "00ba7d36"
    },
    {
      "from": "00bb2cc0"
    },
    {
      "from": "00bb2de3"
    },
    {
      "from": "00bb2f0f"
    },
    {
      "from": "00bb302f"
    },
    {
      "from": "00bb314c"
    },
    {
      "from": "00bbac10"
    },
    {
      "from": "00ba6073"
    },
    {
      "from": "00ba6169"
    },
    {
      "from": "00bbacc8"
    },
    {
      "from": "00c713d1"
    },
    {
      "from": "00de6f94"
    },
    {
      "from": "00f37993"
    },
    {
      "from": "00ba6550"
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
