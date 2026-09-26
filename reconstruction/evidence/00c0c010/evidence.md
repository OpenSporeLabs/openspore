# Evidence 0x00c0c010

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b563df5686274985eaf24fb6b37b9f7a4ad3db3c116c91b78049fff0b9bfb3d2`

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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule"
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
  "content_sha256": "7b9398985c4994030cb2ff80f0684a1269ac7a361cd9914dae393efde8b1ae64",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0011",
        "obs-0013"
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
        "obs-0001",
        "obs-0002",
        "obs-0010",
        "obs-0012"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          3716,
          4564
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0013"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0013"
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
        "obs-0013"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00c0c010",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c0c011",
      "definite": true,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0xe84]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c0c01b",
      "count": 1,
      "first_use": 4,
      "first_write_index": 1,
      "id": "obs-0003",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOVSS XMM0,dword ptr [EAX + 0x350]",
      "reg": "EAX"
    },
    {
      "at": "0x00c0c01b",
      "definite": true,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [EAX + 0x350]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00c0c023",
      "count": 2,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 5,
      "kind": "REG_READ",
      "raw": "COMISS XMM0,dword ptr [0x01485378]",
      "reg": "XMM0"
    },
    {
      "at": "0x00c0c02a",
      "count": 2,
      "first_use": 6,
      "first_write_index": null,
      "id": "obs-0006",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [ESP],XMM0",
      "reg": "ESP"
    },
    {
      "at": "0x00c0c02a",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0007",
      "index": 6,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOVSS dword ptr [ESP],XMM0",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00c0c02f",
      "id": "obs-0008",
      "index": 7,
      "kind": "UNPARSED",
      "raw": "JC 0x00c0c036",
      "reason": "unknown_mnemonic"
    },
    {
      "at": "0x00c0c031",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0009",
      "index": 8,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "FLD float ptr [ESP]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x00c0c034",
      "id": "obs-0010",
      "index": 9,
      "kind": "REG_RESTORE",
      "raw": "POP ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c0c035",
      "form": "RET",
      "id": "obs-0011",
      "imm": null,
      "index": 10,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00c0c03c",
      "id": "obs-0012",
      "index": 12,
      "kind": "REG_RESTORE",
      "raw": "POP ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00c0c03d",
      "form": "RET",
      "id": "obs-0013",
      "imm": null,
      "index": 13,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 14,
    "degraded": true,
    "esp_
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
"\nfloat10 __fastcall FUN_00c0c010(int param_1)\n\n{\n  float fVar1;\n  \n  if ((*(int *)(param_1 + 0xe84) != 0) &&\n     (fVar1 = *(float *)(*(int *)(param_1 + 0xe84) + 0x350), 0.0 <= fVar1)) {\n    return (float10)fVar1;\n  }\n  return (float10)DAT_0150c8b8;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 14,
  "instructions": [
    {
      "address": "00c0c010",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c0c011",
      "instruction": "MOV EAX,dword ptr [ECX + 0xe84]"
    },
    {
      "address": "00c0c017",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c0c019",
      "instruction": "JZ 0x00c0c036"
    },
    {
      "address": "00c0c01b",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x350]"
    },
    {
      "address": "00c0c023",
      "instruction": "COMISS XMM0,dword ptr [0x01485378]"
    },
    {
      "address": "00c0c02a",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "00c0c02f",
      "instruction": "JC 0x00c0c036"
    },
    {
      "address": "00c0c031",
      "instruction": "FLD float ptr [ESP]"
    },
    {
      "address": "00c0c034",
      "instruction": "POP ECX"
    },
    {
      "address": "00c0c035",
      "instruction": "RET"
    },
    {
      "address": "00c0c036",
      "instruction": "FLD float ptr [0x0150c8b8]"
    },
    {
      "address": "00c0c03c",
      "instruction": "POP ECX"
    },
    {
      "address": "00c0c03d",
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
  "body_end": "00c0c03d",
  "body_span_bytes": 46,
  "body_start": "00c0c010",
  "callees": [],
  "callers": [
    "FUN_00c03950",
    "FUN_00c08350",
    "FUN_00c09410"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00c0c010",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "fVar1",
      "storage": "unique:0000a300:4",
      "type": "float"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00c0c010",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x80c010",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c0c010(void)",
  "size_bytes": 46,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c0c010",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00c03af2"
    },
    {
      "from": "00c086cb"
    },
    {
      "from": "00c090e7"
    },
    {
      "from": "00c09484"
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
