# Evidence 0x004c49e0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ec4428d780e87e10dbb4025f0a9c5c7a6174cb85a1d8dc30adb3a760a42003bd`

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
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
  "content_sha256": "9f6d25701788d6f9e7c308b2713522f5d95392c34cfa4eb60ce15b531492a25e",
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
        "obs-0024"
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
        "obs-0006",
        "obs-0007",
        "obs-0014",
        "obs-0015",
        "obs-0016",
        "obs-0021"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          28
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0014",
        "obs-0015",
        "obs-0016",
        "obs-0021",
        "obs-0024"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0024"
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
        "obs-0024"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0024"
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
      "at": "0x004c49e0",
      "count": 13,
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
      "at": "0x004c49e0",
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
      "sub": 16
    },
    {
      "at": "0x004c49e1",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x004c49e1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004c49e3",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x004c49e6",
      "count": 3,
      "first_use": 3,
      "first_write_index": 11,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0xc],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x004c49e6",
      "base": "EBP",
      "disp": -12,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0xc],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x004c49e9",
      "base": "EBP",
      "disp": 8,
      "id": "obs-0008",
      "index": 4,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + 0x8]",
      "res
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
"\nundefined4 __thiscall FUN_004c49e0(int param_1,int param_2)\n\n{\n  undefined4 uVar1;\n  \n  if (param_2 == 0) {\n    uVar1 = *(undefined4 *)(param_1 + 0x18);\n  }\n  else if (param_2 == 1) {\n    uVar1 = *(undefined4 *)(param_1 + 0x1c);\n  }\n  else {\n    uVar1 = 0;\n  }\n  return uVar1;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 25,
  "instructions": [
    {
      "address": "004c49e0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004c49e1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004c49e3",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "004c49e6",
      "instruction": "MOV dword ptr [EBP + -0xc],ECX"
    },
    {
      "address": "004c49e9",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004c49ec",
      "instruction": "MOV dword ptr [EBP + -0x10],EAX"
    },
    {
      "address": "004c49ef",
      "instruction": "CMP dword ptr [EBP + -0x10],0x0"
    },
    {
      "address": "004c49f3",
      "instruction": "JZ 0x004c49fd"
    },
    {
      "address": "004c49f5",
      "instruction": "CMP dword ptr [EBP + -0x10],0x1"
    },
    {
      "address": "004c49f9",
      "instruction": "JZ 0x004c4a0d"
    },
    {
      "address": "004c49fb",
      "instruction": "JMP 0x004c4a1b"
    },
    {
      "address": "004c49fd",
      "instruction": "MOV ECX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "004c4a00",
      "instruction": "MOV EDX,dword ptr [ECX + 0x18]"
    },
    {
      "address": "004c4a03",
      "instruction": "MOV dword ptr [EBP + -0x4],EDX"
    },
    {
      "address": "004c4a06",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004c4a09",
      "instruction": "JMP 0x004c4a1d"
    },
    {
      "address": "004c4a0d",
      "instruction": "MOV EAX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "004c4a10",
      "instruction": "MOV ECX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "004c4a13",
      "instruction": "MOV dword ptr [EBP + -0x8],ECX"
    },
    {
      "address": "004c4a16",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "004c4a19",
      "instruction": "JMP 0x004c4a1d"
    },
    {
      "address": "004c4a1b",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "004c4a1d",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004c4a1f",
      "instruction": "POP EBP"
    },
    {
      "address": "004c4a20",
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
  "body_end": "004c4a22",
  "body_span_bytes": 67,
  "body_start": "004c49e0",
  "callees": [],
  "callers": [
    "FUN_00585330",
    "FUN_00577dd0",
    "Editors::cEditor::Update",
    "FUN_0057e220",
    "Editors::cEditor::AddCreature",
    "FUN_0057f6c0",
    "FUN_0057af00",
    "FUN_0058d1c0",
    "FUN_005aa9c0",
    "FUN_00574a20",
    "FUN_0057e480",
    "FUN_005ab5c0",
    "Editors::cEditor::SetActiveMode",
    "FUN_005aa7a0",
    "Editors::cEditor::HandleMessage",
    "FUN_0057c590",
    "FUN_0058a350",
    "FUN_00591690",
    "FUN_00577620"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "004c49e0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_004c49e0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc49e0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004c49e0(void)",
  "size_bytes": 67,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004c49e0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 33,
  "xrefs": [
    {
      "from": "00577de8"
    },
    {
      "from": "0058757c"
    },
    {
      "from": "005875df"
    },
    {
      "from": "00587638"
    },
    {
      "from": "00587730"
    },
    {
      "from": "00587884"
    },
    {
      "from": "00587967"
    },
    {
      "from": "0058312a"
    },
    {
      "from": "0057e248"
    },
    {
      "from": "0057b75d"
    },
    {
      "from": "0058d2a4"
    },
    {
      "from": "005aa7af"
    },
    {
      "from": "005ab701"
    },
    {
      "from": "005ab712"
    },
    {
      "from": "0057c5c8"
    },
    {
      "from": "0057c70b"
    },
    {
      "from": "00574a3c"
    },
    {
      "from": "0057fdfb"
    },
    {
      "from": "0057ffb1"
    },
    {
      "from": "0058006d"
    },
    {
      "from": "00580093"
    },
    {
      "from": "0058a4b6"
    },
    {
      "from": "0058bfed"
    },
    {
      "from": "0058c57c"
    },
    {
      "from": "0058c596"
    },
    {
      "from": "0058c7aa"
    },
    {
      "from": "0057e4af"
    },
    {
      "from": "00577635"
    },
    {
      "from": "00585457"
    },
    {
      "from": "005930bb"
    },
    {
      "from": "00591a12"
    },
    {
      "from": "005aaa0a"
    },
    {
      "from": "005aa5be"
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
