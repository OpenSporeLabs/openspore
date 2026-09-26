# Evidence 0x005772b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `961b497120b851bacccd4d9cd9ade0f650517e58f6afea397abdba4b5018eae8`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBX",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "dd9d75682ce81036c6e7a89f52cab6ac3bf10bb8c7024824c0ae499445faa2fd",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0011",
        "obs-0017"
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
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0007"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          240
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0011",
        "obs-0017"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0011",
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
        "obs-0011",
        "obs-0017"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0011",
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
      "at": "0x005772b0",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005772b1",
      "count": 4,
      "first_use": 1,
      "first_write_index": 5,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005772b1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x005772b3",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI + 0xf0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005772bd",
      "count": 9,
      "first_use": 5,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ECX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x005772bd",
      "definite": true,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EAX]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005772bf",
      "definite": true,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ECX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005772c4",
      "count": 2,
      "first_use": 9,
      "first_write_index": 6,
      "id": "obs-0008",
      "index": 9,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0x16c]",
      "reg": "EDX"
    },
    {
      "at": "0x005772ca",
      "base": "EAX",
      "disp": null,
      "id": "obs-0009",
      "index": 10,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EAX",
      "via": "register"
    },
    {
      "at": "0x005772ec",
      "id": "obs-0010",
      "index": 20,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005772ed",
      "form": "RET",
      "id": "obs-0011",
      "imm": null,
      "index": 21,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x005772f2",
      "count": 2,
      "first_use": 24,
      "first_write_index": 25,
      "id": "obs-0012",
      "index": 24,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x005772f3",
      "definite": true,
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
"\nvoid __fastcall FUN_005772b0(int param_1)\n\n{\n  undefined4 *puVar1;\n  \n  puVar1 = *(undefined4 **)(param_1 + 0xf0);\n  if (puVar1 != (undefined4 *)0x0) {\n    (**(code **)(*(int *)*puVar1 + 0x16c))(puVar1,0);\n    puVar1 = *(undefined4 **)(param_1 + 0xf0);\n    if (puVar1 != (undefined4 *)0x0) {\n      *(undefined4 *)(param_1 + 0xf0) = 0;\n      if (1 < (int)puVar1[0x10]) {\n        puVar1[0x10] = puVar1[0x10] + -1;\n        return;\n      }\n      (**(code **)(*(int *)*puVar1 + 0x170))(puVar1,(uint)puVar1[1] >> 0x1f);\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 36,
  "instructions": [
    {
      "address": "005772b0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005772b1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005772b3",
      "instruction": "MOV EAX,dword ptr [ESI + 0xf0]"
    },
    {
      "address": "005772b9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005772bb",
      "instruction": "JZ 0x0057730a"
    },
    {
      "address": "005772bd",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "005772bf",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "005772c1",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005772c3",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005772c4",
      "instruction": "MOV EAX,dword ptr [EDX + 0x16c]"
    },
    {
      "address": "005772ca",
      "instruction": "CALL EAX"
    },
    {
      "address": "005772cc",
      "instruction": "MOV EAX,dword ptr [ESI + 0xf0]"
    },
    {
      "address": "005772d2",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005772d4",
      "instruction": "JZ 0x0057730a"
    },
    {
      "address": "005772d6",
      "instruction": "MOV dword ptr [ESI + 0xf0],0x0"
    },
    {
      "address": "005772e0",
      "instruction": "MOV ECX,dword ptr [EAX + 0x40]"
    },
    {
      "address": "005772e3",
      "instruction": "CMP ECX,0x1"
    },
    {
      "address": "005772e6",
      "instruction": "JLE 0x005772ee"
    },
    {
      "address": "005772e8",
      "instruction": "DEC ECX"
    },
    {
      "address": "005772e9",
      "instruction": "MOV dword ptr [EAX + 0x40],ECX"
    },
    {
      "address": "005772ec",
      "instruction": "POP ESI"
    },
    {
      "address": "005772ed",
      "instruction": "RET"
    },
    {
      "address": "005772ee",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "005772f0",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "005772f2",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005772f3",
      "instruction": "MOV EBX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "005772f6",
      "instruction": "SHR EBX,0x1f"
    },
    {
      "address": "005772f9",
      "instruction": "AND BL,0x1"
    },
    {
      "address": "005772fc",
      "instruction": "MOVZX ESI,BL"
    },
    {
      "address": "005772ff",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00577300",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00577301",
      "instruction": "MOV EAX,dword ptr [EDX + 0x170]"
    },
    {
      "address": "00577307",
      "instruction": "CALL EAX"
    },
    {
      "address": "00577309",
      "instruction": "POP EBX"
    },
    {
      "address": "0057730a",
      "instruction": "POP ESI"
    },
    {
      "address": "0057730b",
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
  "body_end": "0057730b",
  "body_span_bytes": 92,
  "body_start": "005772b0",
  "callees": [],
  "callers": [
    "Editors::cEditor::SetActiveMode",
    "Editors::cEditor::OnMouseDown",
    "Editors::cEditor::OnMouseUp",
    "FUN_0057a610",
    "FUN_0057e790",
    "Editors::cEditor::OnKeyDown",
    "Editors::cEditor::OnExit",
    "FUN_0057f6c0",
    "FUN_0057e160"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "005772b0",
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
      "name": "puVar1",
      "storage": "unique:00017200:4",
      "type": "undefined4 *"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_005772b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1772b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005772b0(void)",
  "size_bytes": 92,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005772b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "005874da"
    },
    {
      "from": "00587cca"
    },
    {
      "from": "00587d47"
    },
    {
      "from": "0058ba34"
    },
    {
      "from": "0057e1bc"
    },
    {
      "from": "0057a621"
    },
    {
      "from": "0057e7b7"
    },
    {
      "from": "00580225"
    },
    {
      "from": "0058b107"
    },
    {
      "from": "00589be8"
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
