# Evidence 0x00b25fe0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `09d1460b76e70d56a88d4648e39876c25b81714ffc7690877fe72cf944a16f79`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
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
  "content_sha256": "d835b62d29eee287f3b618e805cedee9cf83ee0ca139d1587502e5e585240cac",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0075"
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
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0016",
        "obs-0035",
        "obs-0036"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          88
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0075"
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
        "obs-0075"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0075"
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
      "and_esp": null,
      "at": "0x00b25fe0",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x1c",
      "sub": 28
    },
    {
      "at": "0x00b25fe0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x1c",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00b25fe3",
      "count": 9,
      "first_use": 1,
      "first_write_index": 79,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00b25fe4",
      "count": 1,
      "first_use": 2,
      "first_write_index": 88,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00b25fe5",
      "count": 30,
      "first_use": 3,
      "first_write_index": 5,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b25fe6",
      "count": 17,
      "first_use": 4,
      "first_write_index": 67,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b25fe7",
      "count": 13,
      "first_use": 5,
      "first_write_index": 8,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b25fe7",
      "definite": true,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b25fe9",
      "id": "obs-0009",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b22960",
      "target": "0x00b22960"
    },
    {
      "at": "0x00b25ff3",
      "definite": true,
      "id": "obs-0010",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,ESI",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00b25ff5",
      "id": "obs-0011",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b22650",
      "target": "0x00b22650"
    },
    {
      "at": "0x00b26001",
      "id": "obs-0012",
      "index": 12,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b22650",
      "target": "0x00b22650"
    },
    {
      "at": "0x00b2600d",
      "id": "obs-0013",
      "index": 15,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b22650",
      "target": "0x00b226
[TRUNCATED]
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
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
  "content_sha256": "d835b62d29eee287f3b618e805cedee9cf83ee0ca139d1587502e5e585240cac",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0075"
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
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0016",
        "obs-0035",
        "obs-0036"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          88
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0075"
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
        "obs-0075"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0075"
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
      "and_esp": null,
      "at": "0x00b25fe0",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x1c",
      "sub": 28
    },
    {
      "at": "0x00b25fe0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x1c",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00b25fe3",
      "count": 9,
      "first_use": 1,
      "first_write_index": 79,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00b25fe4",
      "count": 1,
      "first_use": 2,
      "first_write_index": 88,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00b25fe5",
      "count": 30,
      "first_use": 3,
      "first_write_index": 5,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b25fe6",
      "count": 17,
      "first_use": 4,
      "first_write_index": 67,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b25fe7",
      "count": 13,
      "first_use": 5,
      "first_write_index": 8,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b25fe7",
      "definite": true,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b25fe9",
      "id": "obs-0009",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b22960",
      "target": "0x00b22960"
    },
    {
      "at": "0x00b25ff3",
      "definite": true,
      "id": "obs-0010",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,ESI",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00b25ff5",
      "id": "obs-0011",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b22650",
      "target": "0x00b22650"
    },
    {
      "at": "0x00b26001",
      "id": "obs-0012",
      "index": 12,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b22650",
      "target": "0x00b22650"
    },
    {
      "at": "0x00b2600d",
      "id": "obs-0013",
      "index": 15,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b22650",
      "target": "0x00b226
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 236,
  "instructions": [
    {
      "address": "00b25fe0",
      "instruction": "SUB ESP,0x1c"
    },
    {
      "address": "00b25fe3",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00b25fe4",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00b25fe5",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b25fe6",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00b25fe7",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b25fe9",
      "instruction": "CALL 0x00b22960"
    },
    {
      "address": "00b25fee",
      "instruction": "PUSH 0x18eb45e"
    },
    {
      "address": "00b25ff3",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b25ff5",
      "instruction": "CALL 0x00b22650"
    },
    {
      "address": "00b25ffa",
      "instruction": "PUSH 0x2c9cc91"
    },
    {
      "address": "00b25fff",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b26001",
      "instruction": "CALL 0x00b22650"
    },
    {
      "address": "00b26006",
      "instruction": "PUSH 0x2e96892"
    },
    {
      "address": "00b2600b",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b2600d",
      "instruction": "CALL 0x00b22650"
    },
    {
      "address": "00b26012",
      "instruction": "PUSH 0x18c84a9"
    },
    {
      "address": "00b26017",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b26019",
      "instruction": "CALL 0x00b22650"
    },
    {
      "address": "00b2601e",
      "instruction": "PUSH 0x1be418e"
    },
    {
      "address": "00b26023",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b26025",
      "instruction": "CALL 0x00b22650"
    },
    {
      "address": "00b2602a",
      "instruction": "MOV ECX,dword ptr [ESI + 0x58]"
    },
    {
      "address": "00b2602d",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00b2602f",
      "instruction": "JZ 0x00b2603f"
    },
    {
      "address": "00b26031",
      "instruction": "MOV dword ptr [ESI + 0x58],0x0"
    },
    {
      "address": "00b26038",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00b2603a",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00b2603d",
      "instruction": "CALL EDX"
    },
    {
      "address": "00b2603f",
      "instruction": "PUSH 0x2a8fb3f"
    },
    {
      "address": "00b26044",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b26046",
      "instruction": "CALL 0x00b22650"
    },
    {
      "address": "00b2604b",
      "instruction": "PUSH 0x2a034cd"
    },
    {
      "address": "00b26050",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b26052",
      "instruction": "CALL 0x00b22650"
    },
    {
      "address": "00b26057",
      "instruction": "PUSH 0x18c6de8"
    },
    {
      "address": "00b2605c",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b2605e",
      "instruction": "CALL 0x00b22650"
    },
    {
      "address": "00b26063",
      "instruction": "PUSH 0x18c88e4"
    },
    {
      "address": "00b26068",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b2606a",
      "instruction": "CALL 0x00b22650"
    },
    {
      "address": "00b2606f",
      "instruction": "PUSH 0x3a2511e"
    },
    {
      "address": "00b26074",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b26076",
      "instruction": "CALL 0x00b22650"
    },
    {
      "address": "00b2607b",
      "instruction": "PUSH 0x403df5c"
    },
    {
      "address": "00b26080",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b26082",
      "instruction": "CALL 0x00b22650"
    },
    {
      "address": "00b26087",
      "instruction": "PUSH 0x61494be"
    },
    {
      "address": "00b2608c",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b2608e",
      "instruction": "CALL 0x00b22650"
    },
    {
      "address": "00b26093",
      "instruction": "PUSH 0x629bafe"
    },
    {
      "address": "00b26098",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b2609a",
      "instruction": "CALL 0x00b22650"
    },
    {
      "address": "00b2609f",
      "instruction": "CALL 0x00b3d2b0"
    },
    {
      "address": "00b260a4",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b260a6",
      "instruction": "CALL 0x00ac79d0"
    },
    {
      "address": "00b260ab",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b260ac",
      "instruction": "CALL 0x00b3d2b0"
    },
    {
      "address": "00b260b1",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00b260b3",
      "instruction": "CALL 0x00ac7a40"
    },
    {
      "address": "00b260b8",
      "instruction": "PUSH 0x18ebadc"
    },
    {
      "address": "00b260bd",
      "instruction": "PUSH 0xb1e500"
    },
    {
      "address": "00b260c2",
      "instruction": "PUSH 0xad48b0"
    },
    {
      "address": "00b260c7",
      "instruction": "PUSH 0xd3d420"
    },
    {
      "address": "00b260cc",
      "instruction": "PUSH 0xcd7d10"
    },
    {
      "address": "00b260d1",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00b260d3",
      "instruction": "CALL 0x00b21340"
    },
    {
      "address": "00b260d8",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00b260da",
      "instruction": "MOV ECX,dword ptr [EDI + 0x8]"
    },
    {
      "address": "00b260dd",
      "instruction": "SUB ECX,dword ptr [EDI + 0x4]"
    },
    {
      "address": "00b260e0",
      "instruction": "ADD EDI,0x4"
    },
    {
      "address": "00b260e3",
      "instruction": "LEA EAX,[EDI + 0xc]"
    },
    {
      "address": "00b260e6",
      "instruction": "SAR ECX,0x2"
    },
    {
      "address": "00b260e9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00b260ea",
      "i
[TRUNCATED]
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
  "body_end": "00b262be",
  "body_span_bytes": 735,
  "body_start": "00b25fe0",
  "callees": [
    "FUN_00ac79d0",
    "FUN_00b225d0",
    "FUN_00b22650",
    "FUN_00f47380",
    "FUN_00829110",
    "FUN_00b21340",
    "FUN_00ae6780",
    "FUN_00ac7a40",
    "FUN_00b3d2b0",
    "FUN_00b22960",
    "FUN_00b25ee0",
    "FUN_0102c340",
    "FUN_00f473a0",
    "FUN_00b93c60"
  ],
  "callers": [
    "FUN_00f41300",
    "FUN_00b26320",
    "FUN_00b26600",
    "FUN_00ffa2c0",
    "FUN_00d1c9e0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b25fe0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b25fe0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x725fe0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b25fe0(void)",
  "size_bytes": 735,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b25fe0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 8,
  "xrefs": [
    {
      "from": "00b26369"
    },
    {
      "from": "00b26605"
    },
    {
      "from": "00ffa4be"
    },
    {
      "from": "00d1cac5"
    },
    {
      "from": "00f413fd"
    },
    {
      "from": "00cfa83b"
    },
    {
      "from": "00d19aea"
    },
    {
      "from": "00d19cd1"
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
