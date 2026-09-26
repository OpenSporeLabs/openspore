# Evidence 0x01052880

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1bf9af98c8288ad23ad55d0ab44e64d21505f173a086d2858a0af11f9ae3d7f0`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__cdecl",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
      }
    ],
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
      }
    ],
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
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "d67ecaed08198b186f5feebaa76faaf8dfcb672c65d0f860a2aaea7dfaf192be",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__cdecl",
    "candidate_conventions": [
      "__cdecl",
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
        "obs-0012"
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
        "obs-0003",
        "obs-0005"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0012"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0005",
        "obs-0012"
      ],
      "claim": "calling convention is __cdecl: the caller cleans the stack and at least one entry slot is read",
      "confidence": "INFERRED",
      "id": "C9",
      "value": "__cdecl"
    },
    {
      "based_on": [
        "obs-0012"
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
        "obs-0012"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0012"
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
      "at": "0x01052880",
      "count": 2,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x01052881",
      "count": 2,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "reg": "ESP"
    },
    {
      "at": "0x01052881",
      "base": "ESP",
      "disp": 12,
      "id": "obs-0003",
      "index": 1,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x01052881",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword ptr [ESP + 0xc]",
      "reg": "ESI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01052889",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0005",
      "index": 4,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x01052889",
      "definite": true,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0105288d",
      "count": 3,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x0105288e",
      "id": "obs-0008",
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
"\nvoid FUN_01052880(undefined4 param_1,undefined4 *param_2)\n\n{\n  undefined4 uVar1;\n  \n  if (param_2 != (undefined4 *)0x0) {\n    FUN_00b3d390(param_1);\n    uVar1 = FUN_0104c4f0(param_1);\n    *param_2 = uVar1;\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 12,
  "instructions": [
    {
      "address": "01052880",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01052881",
      "instruction": "MOV ESI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "01052885",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "01052887",
      "instruction": "JZ 0x0105289c"
    },
    {
      "address": "01052889",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "0105288d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0105288e",
      "instruction": "CALL 0x00b3d390"
    },
    {
      "address": "01052893",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01052895",
      "instruction": "CALL 0x0104c4f0"
    },
    {
      "address": "0105289a",
      "instruction": "MOV dword ptr [ESI],EAX"
    },
    {
      "address": "0105289c",
      "instruction": "POP ESI"
    },
    {
      "address": "0105289d",
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
  "body_end": "0105289d",
  "body_span_bytes": 30,
  "body_start": "01052880",
  "callees": [
    "FUN_00b3d390",
    "FUN_0104c4f0"
  ],
  "callers": [
    "FUN_01056160",
    "FUN_01056d30",
    "FUN_01057bd0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01052880",
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
      "type": "undefined4 *"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_01052880",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc52880",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01052880(void)",
  "size_bytes": 30,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01052880",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 20,
  "xrefs": [
    {
      "from": "01056eba"
    },
    {
      "from": "01056ef6"
    },
    {
      "from": "010562a9"
    },
    {
      "from": "010562ed"
    },
    {
      "from": "01056347"
    },
    {
      "from": "010563b3"
    },
    {
      "from": "0105647b"
    },
    {
      "from": "010564a3"
    },
    {
      "from": "0105651a"
    },
    {
      "from": "01056575"
    },
    {
      "from": "010565bc"
    },
    {
      "from": "010565e4"
    },
    {
      "from": "0105660c"
    },
    {
      "from": "01056649"
    },
    {
      "from": "010566a0"
    },
    {
      "from": "010566d9"
    },
    {
      "from": "0105671d"
    },
    {
      "from": "010567d4"
    },
    {
      "from": "01056866"
    },
    {
      "from": "01057c8a"
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
