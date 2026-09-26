# Evidence 0x00c37180

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `706155195333be4a57c8571bc9a2dcc589c1f69de69a9841c8235a48b13888e7`

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
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
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
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "33cc89a4212c9465761af6b61a3cce0e98943d2c20a4889638bc9645a892ba60",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0017"
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
        "obs-0005",
        "obs-0010"
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
        "obs-0001",
        "obs-0002",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0012"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          1812,
          1920,
          1924,
          1928,
          1932,
          1933
        ],
        "register": "ECX",
        "written_through": 5
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0012",
        "obs-0017"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0017"
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
        "obs-0017"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0017"
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
      "at": "0x00c37180",
      "count": 9,
      "first_use": 0,
      "first_write_index": 26,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x780]",
      "reg": "ECX"
    },
    {
      "at": "0x00c37180",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x780]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c37186",
      "count": 8,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c37187",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00c37187",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0005",
      "index": 2,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ESI,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00c37187",
      "definite": true,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,dword
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
"\nvoid __thiscall FUN_00c37180(int param_1,int *param_2,undefined1 param_3)\n\n{\n  int iVar1;\n  IAppSystem *pIVar2;\n  \n  if (((*(int *)(param_1 + 0x780) != *param_2) || (*(int *)(param_1 + 0x784) != param_2[1])) ||\n     (*(int *)(param_1 + 0x788) != param_2[2])) {\n    *(int *)(param_1 + 0x780) = *param_2;\n    *(int *)(param_1 + 0x784) = param_2[1];\n    *(int *)(param_1 + 0x788) = param_2[2];\n    *(undefined1 *)(param_1 + 0x78c) = param_3;\n    *(undefined1 *)(param_1 + 0x78d) = 1;\n    if (*(int *)(param_1 + 0x714) == 0) {\n      iVar1 = FUN_01021300();\n      if (iVar1 != 0) {\n        FUN_00c35740(param_2);\n        pIVar2 = App__IAppSystem__Get();\n        (*pIVar2->_vftable0->InitPlugins)((IAppSystem *)0x5da932e,(CommandLine *)0x0);\n      }\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 39,
  "instructions": [
    {
      "address": "00c37180",
      "instruction": "MOV EAX,dword ptr [ECX + 0x780]"
    },
    {
      "address": "00c37186",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c37187",
      "instruction": "MOV ESI,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c3718b",
      "instruction": "CMP EAX,dword ptr [ESI]"
    },
    {
      "address": "00c3718d",
      "instruction": "JNZ 0x00c371a5"
    },
    {
      "address": "00c3718f",
      "instruction": "MOV EDX,dword ptr [ECX + 0x784]"
    },
    {
      "address": "00c37195",
      "instruction": "CMP EDX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00c37198",
      "instruction": "JNZ 0x00c371a5"
    },
    {
      "address": "00c3719a",
      "instruction": "MOV EAX,dword ptr [ECX + 0x788]"
    },
    {
      "address": "00c371a0",
      "instruction": "CMP EAX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "00c371a3",
      "instruction": "JZ 0x00c37203"
    },
    {
      "address": "00c371a5",
      "instruction": "CMP dword ptr [ECX + 0x714],0x0"
    },
    {
      "address": "00c371ac",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00c371ae",
      "instruction": "MOV dword ptr [ECX + 0x780],EDX"
    },
    {
      "address": "00c371b4",
      "instruction": "MOV EAX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00c371b7",
      "instruction": "MOV dword ptr [ECX + 0x784],EAX"
    },
    {
      "address": "00c371bd",
      "instruction": "MOV EDX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "00c371c0",
      "instruction": "MOV AL,byte ptr [ESP + 0xc]"
    },
    {
      "address": "00c371c4",
      "instruction": "MOV dword ptr [ECX + 0x788],EDX"
    },
    {
      "address": "00c371ca",
      "instruction": "MOV byte ptr [ECX + 0x78c],AL"
    },
    {
      "address": "00c371d0",
      "instruction": "MOV byte ptr [ECX + 0x78d],0x1"
    },
    {
      "address": "00c371d7",
      "instruction": "JNZ 0x00c37203"
    },
    {
      "address": "00c371d9",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00c371de",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c371e0",
      "instruction": "JZ 0x00c37203"
    },
    {
      "address": "00c371e2",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c371e3",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c371e5",
      "instruction": "CALL 0x00c35740"
    },
    {
      "address": "00c371ea",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "00c371ef",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00c371f1",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c371f3",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c371f5",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c371f7",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c371f9",
      "instruction": "MOV EAX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "00c371fc",
      "instruction": "PUSH 0x5da932e"
    },
    {
      "address": "00c37201",
      "instruction": "CALL EAX"
    },
    {
      "address": "00c37203",
      "instruction": "POP ESI"
    },
    {
      "address": "00c37204",
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
  "body_end": "00c37206",
  "body_span_bytes": 135,
  "body_start": "00c37180",
  "callees": [
    "App::IAppSystem::Get",
    "FUN_00c35740",
    "FUN_01021300"
  ],
  "callers": [
    "FUN_00f41bb0",
    "FUN_00c37cc0",
    "FUN_00c35740",
    "FUN_0102acb0",
    "FUN_00d09560",
    "FUN_010095e0",
    "FUN_00c37a90",
    "FUN_00c3e0b0",
    "FUN_01006ef0",
    "FUN_0100b0a0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c37180",
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
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:1",
      "type": "undefined1"
    },
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "pIVar2",
      "storage": "register:00000000:4",
      "type": "IAppSystem *"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_00c37180",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x837180",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c37180(void)",
  "size_bytes": 135,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c37180",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "00c3e0e2"
    },
    {
      "from": "00c357ed"
    },
    {
      "from": "0102ad46"
    },
    {
      "from": "00c37daa"
    },
    {
      "from": "00d09594"
    },
    {
      "from": "00f41c8e"
    },
    {
      "from": "01007358"
    },
    {
      "from": "01009737"
    },
    {
      "from": "0100b183"
    },
    {
      "from": "00c37ba6"
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
