# Evidence 0x00b5b6f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `21f4f1275141ac3eae6b8c78031b2d96aac3fce75a810591e438deb20a60df1c`

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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
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
  "content_sha256": "d39e2b516cb8f54c95fba49775da6118c4668a3cb7876b661656b7ba314da4cb",
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
        "obs-0008",
        "obs-0011"
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
        "obs-0009"
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
        "obs-0003",
        "obs-0004",
        "obs-0007",
        "obs-0009"
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
        "obs-0003",
        "obs-0004",
        "obs-0007",
        "obs-0009"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0011"
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
        "obs-0008",
        "obs-0011"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0011"
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
      "at": "0x00b5b6f0",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x01686a1c]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b5b6fb",
      "id": "obs-0002",
      "index": 2,
      "kind": "UNPARSED",
      "raw": "JNC 0x00b5b712",
      "reason": "unknown_mnemonic"
    },
    {
      "at": "0x00b5b6fd",
      "count": 4,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00b5b6fd",
      "definite": true,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00b5b70b",
      "count": 2,
      "first_use": 8,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 8,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x00b5b70b",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0006",
      "index": 8,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00b5b70f",
      "count": 3,
      "first_use": 9,
      "first_write_index": 3,
      "id": "obs-0007",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ECX],EAX",
      "reg": "ECX"
    },
    {
      "at": "0x00b5b711",
      "form": "RET",
      "id": "obs-0008",
      "imm": null,
      "index": 10,
      "kind": "RET",
      "raw": "RET"
    },
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
"\nvoid FUN_00b5b6f0(undefined4 param_1)\n\n{\n  undefined4 *puVar1;\n  \n  if (DAT_01686a1c < DAT_01686a20) {\n    puVar1 = DAT_01686a1c + 1;\n    if (DAT_01686a1c != (undefined4 *)0x0) {\n      *DAT_01686a1c = param_1;\n      DAT_01686a1c = puVar1;\n      return;\n    }\n  }\n  else {\n    FUN_00b96600(DAT_01686a1c,&param_1);\n    puVar1 = DAT_01686a1c;\n  }\n  DAT_01686a1c = puVar1;\n  return;\n}\n\n"
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
      "address": "00b5b6f0",
      "instruction": "MOV EAX,[0x01686a1c]"
    },
    {
      "address": "00b5b6f5",
      "instruction": "CMP EAX,dword ptr [0x01686a20]"
    },
    {
      "address": "00b5b6fb",
      "instruction": "JNC 0x00b5b712"
    },
    {
      "address": "00b5b6fd",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b5b6ff",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "00b5b702",
      "instruction": "MOV [0x01686a1c],EAX"
    },
    {
      "address": "00b5b707",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00b5b709",
      "instruction": "JZ 0x00b5b722"
    },
    {
      "address": "00b5b70b",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00b5b70f",
      "instruction": "MOV dword ptr [ECX],EAX"
    },
    {
      "address": "00b5b711",
      "instruction": "RET"
    },
    {
      "address": "00b5b712",
      "instruction": "LEA ECX,[ESP + 0x4]"
    },
    {
      "address": "00b5b716",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00b5b717",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b5b718",
      "instruction": "MOV ECX,0x1686a18"
    },
    {
      "address": "00b5b71d",
      "instruction": "CALL 0x00b96600"
    },
    {
      "address": "00b5b722",
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
  "body_end": "00b5b722",
  "body_span_bytes": 51,
  "body_start": "00b5b6f0",
  "callees": [
    "FUN_00b96600"
  ],
  "callers": [
    "FUN_00f30bc0",
    "FUN_00ae5c30",
    "FUN_00dc7d70",
    "FUN_00ae6a70",
    "FUN_00cc5a70"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b5b6f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "puVar1",
      "storage": "unique:1000001e:4",
      "type": "undefined4 *"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00b5b6f0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x75b6f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b5b6f0(void)",
  "size_bytes": 51,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b5b6f0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "00ae5c4e"
    },
    {
      "from": "00f30bdc"
    },
    {
      "from": "00ae6a8c"
    },
    {
      "from": "00dc7d8c"
    },
    {
      "from": "00cc5a8c"
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
