# Evidence 0x00c0b8a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f6460817c1f1ce2ecb950d25a2bcf3e5b3640308d70236028eeb0999b8faaa43`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
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
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "072000af9d767bb5a02a14dadc1c63e19c7497bc2cb314afcf013517f2fbfb70",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
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
        "obs-0012",
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
        "obs-0006"
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
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0008"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0008"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0012",
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
        "obs-0012",
        "obs-0014"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0012",
        "obs-0014"
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
      "at": "0x00c0b8a0",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c0b8a1",
      "count": 2,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c0b8a1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00c0b8a3",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d4c0",
      "target": "0x00b3d4c0"
    },
    {
      "at": "0x00c0b8ac",
      "count": 1,
      "first_use": 5,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00c0b8ac",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0006",
      "index": 5,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00c0b8ac",
      "definite": true,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESP + 0x8]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c0b8b9",
      "count": 3,
      "first_use": 10,
      "first_write_index": 12,
      "id": "obs-0008",
      "index": 10,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00c0b8bb",
      "id": "obs-0009",
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
"\nbool __thiscall FUN_00c0b8a0(int param_1,undefined4 param_2)\n\n{\n  int iVar1;\n  \n  iVar1 = FUN_00b3d4c0();\n  if (iVar1 != 0) {\n    iVar1 = FUN_00ba3f90(param_1 + 0xb28,param_1,param_2);\n    return iVar1 == 1;\n  }\n  return false;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 21,
  "instructions": [
    {
      "address": "00c0b8a0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c0b8a1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c0b8a3",
      "instruction": "CALL 0x00b3d4c0"
    },
    {
      "address": "00c0b8a8",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c0b8aa",
      "instruction": "JZ 0x00c0b8ca"
    },
    {
      "address": "00c0b8ac",
      "instruction": "MOV ECX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c0b8b0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c0b8b1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c0b8b2",
      "instruction": "ADD ESI,0xb28"
    },
    {
      "address": "00c0b8b8",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c0b8b9",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c0b8bb",
      "instruction": "CALL 0x00ba3f90"
    },
    {
      "address": "00c0b8c0",
      "instruction": "DEC EAX"
    },
    {
      "address": "00c0b8c1",
      "instruction": "NEG EAX"
    },
    {
      "address": "00c0b8c3",
      "instruction": "SBB EAX,EAX"
    },
    {
      "address": "00c0b8c5",
      "instruction": "INC EAX"
    },
    {
      "address": "00c0b8c6",
      "instruction": "POP ESI"
    },
    {
      "address": "00c0b8c7",
      "instruction": "RET 0x4"
    },
    {
      "address": "00c0b8ca",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00c0b8cc",
      "instruction": "POP ESI"
    },
    {
      "address": "00c0b8cd",
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
  "body_end": "00c0b8cf",
  "body_span_bytes": 48,
  "body_start": "00c0b8a0",
  "callees": [
    "FUN_00ba3f90",
    "FUN_00b3d4c0"
  ],
  "callers": [
    "FUN_00d41a70",
    "FUN_00d7b110",
    "FUN_00d8bb70",
    "FUN_00d8c850"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c0b8a0",
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
      "name": "param_2",
      "storage": "Stack[0x4]:4",
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
  "name": "FUN_00c0b8a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x80b8a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c0b8a0(void)",
  "size_bytes": 48,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c0b8a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00d41b7d"
    },
    {
      "from": "00d7b156"
    },
    {
      "from": "00d8bcca"
    },
    {
      "from": "00d8c915"
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
