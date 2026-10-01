# Evidence 0x00409c00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `202c87b8674ad3261ab0ef75bcf7083a14a2d15288491bbe6b60aef084eb878f`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (receiver in ECX), no stack arguments",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is read only by the spill at 0x00409c06",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "no value is produced for the caller; the decompiler also gives the function a void return, and no instruction writes a result register",
  "return_register": null,
  "return_semantics": "no value; the constructor communicates entirely through the 24 bytes at the receiver",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single RET at 0x00409cd6"
}
```

## abi_derived

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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "EBP"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "7f6c7694627089b9ee85f66895ff898a0f6c3ab5dff275ecd39477fc5222dba4",
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
    "persisted_calling_convention": "__thiscall (receiver in ECX), no stack arguments"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0042"
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
        "obs-0007",
        "obs-0021",
        "obs-0022",
        "obs-0023",
        "obs-0027",
        "obs-0039"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          4,
          8,
          12,
          16,
          20
        ],
        "register": "ECX",
        "written_through": 6
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0021",
        "obs-0022",
        "obs-0023",
        "obs-0027",
        "obs-0039",
        "obs-0042"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0042"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00409c00",
      "count": 29,
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
      "at": "0x00409c00",
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
      "sub": 52
    },
    {
      "at": "0x00409c01",
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
      "at": "0x00409c01",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x00409c03",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x34",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00409c06",
      "count": 4,
      "first_use": 3,
      "first_write_index": 17,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0x34],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00409c06",
      "base": "EBP",
      "disp": -52,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x34],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00409c09",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM0,dword ptr [0x013eb258]",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00409c11",
      "count": 12,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOVSS dword ptr [EBP + -0x24],XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00409c11",
      "base": "EBP",
      "disp": -36,
      "id": "obs-0010",
      "index": 5,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOVSS dword ptr [EBP + -0x24],XMM0",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00409c1e",
      "base": "EBP",
      "disp": -32,
      "id": "obs-0011",
      "index": 7,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOVSS dword ptr [EBP + -0x20],XMM0",
      "reason": "local",
      "resolved": false,
 
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00407280"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0041aaa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043eef0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00441440"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00449d40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0044a070"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0044aaa0"
  },
  {
    "name": "FUN_0044ae00",
    "reconstructed": false,
    "va": "0x0044ae00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00471000"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00471b50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00471ec0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004ad550"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004aff80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004ba150"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004f01f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00507380"
  }
]
```

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
  "count": 49,
  "instructions": [
    {
      "address": "00409c00",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00409c01",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "00409c03",
      "instruction": "SUB ESP,0x34"
    },
    {
      "address": "00409c06",
      "instruction": "MOV dword ptr [EBP + -0x34],ECX"
    },
    {
      "address": "00409c09",
      "instruction": "MOVSS XMM0,dword ptr [0x013eb258]"
    },
    {
      "address": "00409c11",
      "instruction": "MOVSS dword ptr [EBP + -0x24],XMM0"
    },
    {
      "address": "00409c16",
      "instruction": "MOVSS XMM0,dword ptr [0x013eb258]"
    },
    {
      "address": "00409c1e",
      "instruction": "MOVSS dword ptr [EBP + -0x20],XMM0"
    },
    {
      "address": "00409c23",
      "instruction": "MOVSS XMM0,dword ptr [0x013eb258]"
    },
    {
      "address": "00409c2b",
      "instruction": "MOVSS dword ptr [EBP + -0x1c],XMM0"
    },
    {
      "address": "00409c30",
      "instruction": "MOVSS XMM0,dword ptr [EBP + -0x24]"
    },
    {
      "address": "00409c35",
      "instruction": "MOVSS dword ptr [EBP + -0xc],XMM0"
    },
    {
      "address": "00409c3a",
      "instruction": "MOVSS XMM0,dword ptr [EBP + -0x20]"
    },
    {
      "address": "00409c3f",
      "instruction": "MOVSS dword ptr [EBP + -0x8],XMM0"
    },
    {
      "address": "00409c44",
      "instruction": "MOVSS XMM0,dword ptr [EBP + -0x1c]"
    },
    {
      "address": "00409c49",
      "instruction": "MOVSS dword ptr [EBP + -0x4],XMM0"
    },
    {
      "address": "00409c4e",
      "instruction": "MOV EAX,dword ptr [EBP + -0x34]"
    },
    {
      "address": "00409c51",
      "instruction": "MOV ECX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "00409c54",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "00409c56",
      "instruction": "MOV EDX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "00409c59",
      "instruction": "MOV dword ptr [EAX + 0x4],EDX"
    },
    {
      "address": "00409c5c",
      "instruction": "MOV ECX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "00409c5f",
      "instruction": "MOV dword ptr [EAX + 0x8],ECX"
    },
    {
      "address": "00409c62",
      "instruction": "MOVSS XMM0,dword ptr [0x013eb258]"
    },
    {
      "address": "00409c6a",
      "instruction": "XORPS XMM0,xmmword ptr [0x013eb8b0]"
    },
    {
      "address": "00409c71",
      "instruction": "MOVSS dword ptr [EBP + -0x30],XMM0"
    },
    {
      "address": "00409c76",
      "instruction": "MOVSS XMM0,dword ptr [0x013eb258]"
    },
    {
      "address": "00409c7e",
      "instruction": "XORPS XMM0,xmmword ptr [0x013eb8b0]"
    },
    {
      "address": "00409c85",
      "instruction": "MOVSS dword ptr [EBP + -0x2c],XMM0"
    },
    {
      "address": "00409c8a",
      "instruction": "MOVSS XMM0,dword ptr [0x013eb258]"
    },
    {
      "address": "00409c92",
      "instruction": "XORPS XMM0,xmmword ptr [0x013eb8b0]"
    },
    {
      "address": "00409c99",
      "instruction": "MOVSS dword ptr [EBP + -0x28],XMM0"
    },
    {
      "address": "00409c9e",
      "instruction": "MOVSS XMM0,dword ptr [EBP + -0x30]"
    },
    {
      "address": "00409ca3",
      "instruction": "MOVSS dword ptr [EBP + -0x18],XMM0"
    },
    {
      "address": "00409ca8",
      "instruction": "MOVSS XMM0,dword ptr [EBP + -0x2c]"
    },
    {
      "address": "00409cad",
      "instruction": "MOVSS dword ptr [EBP + -0x14],XMM0"
    },
    {
      "address": "00409cb2",
      "instruction": "MOVSS XMM0,dword ptr [EBP + -0x28]"
    },
    {
      "address": "00409cb7",
      "instruction": "MOVSS dword ptr [EBP + -0x10],XMM0"
    },
    {
      "address": "00409cbc",
      "instruction": "MOV EDX,dword ptr [EBP + -0x34]"
    },
    {
      "address": "00409cbf",
      "instruction": "ADD EDX,0xc"
    },
    {
      "address": "00409cc2",
      "instruction": "MOV EAX,dword ptr [EBP + -0x18]"
    },
    {
      "address": "00409cc5",
      "instruction": "MOV dword ptr [EDX],EAX"
    },
    {
      "address": "00409cc7",
      "instruction": "MOV ECX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "00409cca",
      "instruction": "MOV dword ptr [EDX + 0x4],ECX"
    },
    {
      "address": "00409ccd",
      "instruction": "MOV EAX,dword ptr [EBP + -0x10]"
    },
    {
      "address": "00409cd0",
      "instruction": "MOV dword ptr [EDX + 0x8],EAX"
    },
    {
      "address": "00409cd3",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "00409cd5",
      "instruction": "POP EBP"
    },
    {
      "address": "00409cd6",
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 11013,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall (receiver in ECX), no stack arguments\",\n    \"hidden_receiver\": \"ECX\",\n    \"hidden_this_register\": \"ECX is read only by the spill at 0x00409c06\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"no value is produced for the caller; the decompiler also gives the function a void return, and no instruction writes a result register\",\n    \"return_register\": null,\n    \"return_semantics\": \"no value; the constructor communicates entirely through the 24 bytes at the receiver\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"single RET at 0x00409cd6\"\n  },\n  \"analogues\": [],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00407280\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0041aaa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043eef0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00441440\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00449d40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0044a070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0044aaa0\"\n      },\n      {\n        \"name\": \"FUN_0044ae00\",\n        \"reconstructed\": false,\n        \"va\": \"0x0044ae00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00471000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00471b50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00471ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ad550\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004aff80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ba150\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004f01f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00507380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00507c70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0050c3b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0051e180\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0056a710\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0056a7b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00a05c20\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00407a3e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00407280\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0041ab89\",\n        \"direction\": \"in\",\n        \"other\": \"0x0041aaa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0041affd\",\n        \"direction\": \"in\",\n        \"other\": \"0x0041aaa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0043eeff\",\n        \"direction\": \"in\",\n        \"other\": \"0x0043eef0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00446936\",\n        \"direction\": \"in\",\n        \"other\": \"0x00441440\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00446a86\",\n        \"direction\": \"in\",\n        \"other\": \"0x00441440\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00449d52\",\n        \"direction\": \"in\",\n        \"other\": \"0x00449d40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0044a0a5\",\n        \"direction\": \"in\",\n        \"other\": \"0x0044a070\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0044aab4\",\n        \"direction\": \"in\",\n        \"other\": \"0x0044aaa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0044ae14\",\n        \"direction\": \"in\",\n        \"other\": \"0x0044ae00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00471020\",\n        \"direction\": \"in\",\n        \"other\": \"0x00471000\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00471d54\",\n        \"direction\": \"in\",\n        \"other\": \"0x00471b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00471ed9\",\n        \"di
[TRUNCATED]
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "00409cd6",
  "body_span_bytes": 215,
  "body_start": "00409c00",
  "callees": [],
  "callers": [
    "FUN_00449d40",
    "FUN_00471000",
    "FUN_0050c3b0",
    "FUN_00507380",
    "FUN_004ba150",
    "FUN_004ad550",
    "FUN_0044ae00",
    "FUN_00471ec0",
    "FUN_00a05c20",
    "FUN_0043eef0",
    "FUN_0044aaa0",
    "FUN_004aff80",
    "FUN_00441440",
    "FUN_0044a070",
    "FUN_00407280",
    "FUN_004f01f0",
    "FUN_0056a710",
    "FUN_0056a7b0",
    "FUN_0041aaa0",
    "FUN_00471b50",
    "FUN_0051e180",
    "FUN_00507c70"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00409c00",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined4"
    },
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "undefined4"
    },
    {
      "name": "local_34",
      "storage": "Stack[-0x34]:4",
      "type": "undefined4"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 13,
  "mode": "live",
  "name": "FUN_00409c00",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x9c00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00409c00(void)",
  "size_bytes": 215,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00409c00",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 28,
  "xrefs": [
    {
      "from": "0044ae14"
    },
    {
      "from": "00446936"
    },
    {
      "from": "00446a86"
    },
    {
      "from": "00449d52"
    },
    {
      "from": "0044a0a5"
    },
    {
      "from": "004f0b0c"
    },
    {
      "from": "004f0cb9"
    },
    {
      "from": "0041ab89"
    },
    {
      "from": "0041affd"
    },
    {
      "from": "00507f50"
    },
    {
      "from": "00407a3e"
    },
    {
      "from": "00471020"
    },
    {
      "from": "00471d54"
    },
    {
      "from": "0050751e"
    },
    {
      "from": "0043eeff"
    },
    {
      "from": "0044aab4"
    },
    {
      "from": "0050c3d4"
    },
    {
      "from": "00471ed9"
    },
    {
      "from": "00471f49"
    },
    {
      "from": "004ad562"
    },
    {
      "from": "004ad56a"
    },
    {
      "from": "004affa4"
    },
    {
      "from": "004ba222"
    },
    {
      "from": "0051e230"
    },
    {
      "from": "0056a719"
    },
    {
      "from": "0056a7d2"
    },
    {
      "from": "0056a818"
    },
    {
      "from": "00a05c96"
    }
  ]
}
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b04/00409c00_bounding_box_ctor.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/00409c00_bounding_box_ctor.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b04/00409c00.json"
  ]
}
```

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocking_reason": null,
  "gates": [
    "No original-process trace has been captured. Whether any of the 28 callsites actually passes the constructed object on to a union or intersection without overwriting it first is a runtime fact.",
    "Runtime patching of either global constant cannot be excluded statically; both were read from the on-disk image only."
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "Math::BoundingBox (SDK candidate, exact layout match)",
  "void"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
