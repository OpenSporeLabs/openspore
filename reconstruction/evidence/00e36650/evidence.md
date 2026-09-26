# Evidence 0x00e36650

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9015908ae270d0018ef66ab05a19321efd362545d797085df3acb9710e6be4a2`

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
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": false,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": false,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
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
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "949c6bc4399f66985d614af56bbf517f10bae6929197a533886f9204c494a3bf",
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
        "obs-0006"
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
        "obs-0006"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 2,
        "total_bytes": 8
      }
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
          12
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0006"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0006"
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
        "obs-0005",
        "obs-0006"
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
        "obs-0006"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0006"
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
      "at": "0x00e36650",
      "count": 1,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ECX + 0xc]",
      "reg": "ECX"
    },
    {
      "at": "0x00e36650",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ECX + 0xc]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e36653",
      "count": 1,
      "first_use": 1,
      "first_write_index": 1,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "XOR EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00e36653",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "XOR EAX,EAX",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x00e36659",
      "id": "obs-0005",
      "index": 4,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x008105b0",
      "target": "0x008105b0"
    },
    {
      "at": "0x00e3665e",
      "form": "RET 0x8",
      "id": "obs-0006",
      "imm": 8,
      "index": 5,
      "ki
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
"\nundefined4 __fastcall FUN_00e36650(int param_1)\n\n{\n  undefined4 uVar1;\n  \n  if (*(int *)(param_1 + 0xc) != 0) {\n    uVar1 = FUN_008105b0();\n    return uVar1;\n  }\n  return 0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 6,
  "instructions": [
    {
      "address": "00e36650",
      "instruction": "MOV ECX,dword ptr [ECX + 0xc]"
    },
    {
      "address": "00e36653",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00e36655",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00e36657",
      "instruction": "JZ 0x00e3665e"
    },
    {
      "address": "00e36659",
      "instruction": "JMP 0x008105b0"
    },
    {
      "address": "00e3665e",
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
  "body_end": "00e36660",
  "body_span_bytes": 17,
  "body_start": "00e36650",
  "callees": [
    "FUN_008105b0"
  ],
  "callers": [
    "FUN_0107ac90",
    "FUN_01063a10",
    "FUN_010759c0",
    "FUN_01067c50",
    "FUN_0107b260",
    "FUN_01077630"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00e36650",
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
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00e36650",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa36650",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e36650(void)",
  "size_bytes": 17,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e36650",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 30,
  "xrefs": [
    {
      "from": "01077689"
    },
    {
      "from": "01067c74"
    },
    {
      "from": "01067c88"
    },
    {
      "from": "01067c9c"
    },
    {
      "from": "01067cb0"
    },
    {
      "from": "01063b00"
    },
    {
      "from": "01063bb2"
    },
    {
      "from": "01063c0e"
    },
    {
      "from": "01063c55"
    },
    {
      "from": "01063c81"
    },
    {
      "from": "01063ca0"
    },
    {
      "from": "01063d69"
    },
    {
      "from": "01075a43"
    },
    {
      "from": "01075b0e"
    },
    {
      "from": "01075b5d"
    },
    {
      "from": "01075b86"
    },
    {
      "from": "01075baf"
    },
    {
      "from": "01075c6c"
    },
    {
      "from": "01075cb7"
    },
    {
      "from": "01075cc7"
    },
    {
      "from": "0107ad26"
    },
    {
      "from": "0107b3cb"
    },
    {
      "from": "0107b494"
    },
    {
      "from": "0107b4e7"
    },
    {
      "from": "0107b50e"
    },
    {
      "from": "0107b535"
    },
    {
      "from": "0107b5a8"
    },
    {
      "from": "0107b5f5"
    },
    {
      "from": "0107b605"
    },
    {
      "from": "010630af"
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
