# Evidence 0x00aea210

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9bacbef62cd4113191ac2d5a49d5e4e5e4152f68e50281944a2769252478daf9`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path",
    "no_discriminator: no stack-argument read and no positive receiver evidence"
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
  "content_sha256": "11191bb35142494d80dc18f92a566726763af53ff728a4200fde83a91cc18c30",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0009"
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
        "obs-0009"
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
        "obs-0009"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0009"
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
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0009"
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
      "at": "0x00aea210",
      "id": "obs-0001",
      "index": 0,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00ae9f50",
      "target": "0x00ae9f50"
    },
    {
      "at": "0x00aea215",
      "id": "obs-0002",
      "index": 1,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0067dcc0",
      "target": "0x0067dcc0"
    },
    {
      "at": "0x00aea21a",
      "count": 3,
      "first_use": 2,
      "first_write_index": 7,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x00aea21a",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00aea222",
      "definite": true,
      "id": "obs-0005",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00aea224",
      "count": 1,
      "first_use": 7,
      "first_write_index": 2,
      "id": "obs-0006",
      "index": 7,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0x18]",
      "reg": "EDX"
    },
    {
      "at": "0x00aea224",
      "definite": true,
      "id": "obs-0007",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EDX + 0x18]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00aea22c",
      "base": "EAX",
      "disp": null,
      "id": "obs-0008",
      "index": 9,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EAX",
      "via": "register"
    },
    {
      "at": "0x00aea22e",
      "form": "RET",
      "id": "obs-0009",
      "imm": null,
      "index": 10,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 11,
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
    "confidence": "OBSERVED",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": false,
    "register": null,
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confiden
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
"\nvoid FUN_00aea210(void)\n\n{\n  IAppSystem *pIVar1;\n  \n  FUN_00ae9f50();\n  pIVar1 = App__IAppSystem__Get();\n  (*pIVar1->_vftable0->InitPlugins)((IAppSystem *)0x490d429,(CommandLine *)0x0);\n  return;\n}\n\n"
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
      "address": "00aea210",
      "instruction": "CALL 0x00ae9f50"
    },
    {
      "address": "00aea215",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "00aea21a",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00aea21c",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00aea21e",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00aea220",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00aea222",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00aea224",
      "instruction": "MOV EAX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "00aea227",
      "instruction": "PUSH 0x490d429"
    },
    {
      "address": "00aea22c",
      "instruction": "CALL EAX"
    },
    {
      "address": "00aea22e",
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
  "body_end": "00aea22e",
  "body_span_bytes": 31,
  "body_start": "00aea210",
  "callees": [
    "FUN_00ae9f50",
    "App::IAppSystem::Get"
  ],
  "callers": [
    "FUN_00aeb7b0",
    "FUN_00dd5160",
    "FUN_0102df20",
    "FUN_0102d820",
    "FUN_00cfeeb0",
    "FUN_01067b60"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00aea210",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "pIVar1",
      "storage": "register:00000000:4",
      "type": "IAppSystem *"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00aea210",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6ea210",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00aea210(void)",
  "size_bytes": 31,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00aea210",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 18,
  "xrefs": [
    {
      "from": "00aeb872"
    },
    {
      "from": "00cfef28"
    },
    {
      "from": "00cff30c"
    },
    {
      "from": "00cff7a1"
    },
    {
      "from": "00cff8cd"
    },
    {
      "from": "00cffc48"
    },
    {
      "from": "0102e14e"
    },
    {
      "from": "0102e710"
    },
    {
      "from": "0102eb93"
    },
    {
      "from": "0102ec2a"
    },
    {
      "from": "0102ec68"
    },
    {
      "from": "0102ed7d"
    },
    {
      "from": "0102ee32"
    },
    {
      "from": "0102ef0a"
    },
    {
      "from": "0102d84e"
    },
    {
      "from": "00dd51aa"
    },
    {
      "from": "00dd5831"
    },
    {
      "from": "01067c04"
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
