# Evidence 0x00f47930

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d29b00f77d55b8481d9f603204239296d137a79d8d60116ac2efd3cc30048943`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall with no ordinary stack arguments",
  "ordinary_stack_arguments": [],
  "receiver_register": "ECX",
  "ret_form": "plain RET",
  "return_register": "EAX",
  "return_width_bytes": 0,
  "stack_cleanup_bytes": 0
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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
  "content_sha256": "44a0f5d8c2d2f0bb7f712b1d329345d09022142a2a1b1dca94e2a5da8ea6d5e4",
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
    "persisted_calling_convention": "thiscall with no ordinary stack arguments"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 12,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0062"
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
        "obs-0008",
        "obs-0009",
        "obs-0014",
        "obs-0015",
        "obs-0018",
        "obs-0026",
        "obs-0032"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          12,
          16,
          20,
          24,
          28,
          32,
          40,
          44,
          48,
          52,
          56,
          60
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0014",
        "obs-0015",
        "obs-0018",
        "obs-0026",
        "obs-0032",
        "obs-0062"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0062"
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
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00f47930",
      "count": 2,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": 4294967288,
      "at": "0x00f47930",
      "ebp_is_general_register": false,
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
      "sub": 20
    },
    {
      "at": "0x00f47931",
      "count": 18,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x00f47931",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x00f47933",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "AND ESP,0xfffffff8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00f47939",
      "count": 12,
      "first_use": 4,
      "first_write_index": 23,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00f4793a",
      "count": 20,
      "first_use": 5,
      "first_write_index": 6,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00f4793b",
      "count": 15,
      "first_use": 6,
      "first_write_index": 13,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00f4793b",
      "definite": true,
      "id": "obs-0009",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00f47941",
      "count": 7,
      "first_use": 8,
      "first_write_index": 26,
      "id": "obs-0010",
      "index": 8,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00f47948",
      "count": 25,
      "first_use": 10,
      "first_write_index": 24,
      "id": "obs-0011",
      "index": 10,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESP + 0x10]",
      "reg": "EAX"
    },
    {
      "at": "0x00f47948",
      "base": "ESP",
      "disp": 16,
      "id": "obs-00
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f47b10"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00f47410",
      "0x00f47700",
      "0x00f47ed0",
      "0x00f47700",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47410",
      "0x00f47700",
      "0x00f47700",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47b10"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:0",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00f47994",
      "0x00f47a14",
      "0x00f47b10",
      "0x00f47930",
      "0x00f47930",
      "0x00f47994",
      "0x00f47a14",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47994",
      "0x00f47a14",
      "0x00f47994",
      "0x00f47a14"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:1",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00f47969",
      "0x00f47a42",
      "0x00f47930",
      "0x00f47ad9",
      "0x00f47b10",
      "0x00f47700",
      "0x00f47700",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47969",
      "0x00f47a42",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47b10"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:2",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00f47b10",
      "0x00e552f0",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e7fc00",
      "0x00e80980",
      "0x00e80980",
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81f30",
      "0x00f47930"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:4",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Deferred trigger and owner/order semantics are not recovered; no immediate dispatch equivalence is claimed.",
    "resolution_status": "Deferred trigger and owner/order semantics are not recovered; no immediate dispatch equivalence is claimed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00f47930",
      "0x00f47700",
      "0x00f47700",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47ed0",
      "0x00f47ed0",
      "0x00f47930",
      "0x00f47930"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:5",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00f47930",
      "0x00f47930",
      "0x00f47b10",
      "0x00f47b10"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:7",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
  "count": 158,
  "instructions": [
    {
      "address": "00f47930",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00f47931",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "00f47933",
      "instruction": "AND ESP,0xfffffff8"
    },
    {
      "address": "00f47936",
      "instruction": "SUB ESP,0x14"
    },
    {
      "address": "00f47939",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00f4793a",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00f4793b",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00f4793d",
      "instruction": "CMP byte ptr [ESI + 0xc],0x0"
    },
    {
      "address": "00f47941",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00f47942",
      "instruction": "JZ 0x00f47ad3"
    },
    {
      "address": "00f47948",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00f4794c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00f4794d",
      "instruction": "CALL dword ptr [0x013cc2b8]"
    },
    {
      "address": "00f47953",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00f47957",
      "instruction": "SUB ECX,dword ptr [ESI + 0x10]"
    },
    {
      "address": "00f4795a",
      "instruction": "MOV EDX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00f4795e",
      "instruction": "SBB EDX,dword ptr [ESI + 0x14]"
    },
    {
      "address": "00f47961",
      "instruction": "MOV dword ptr [ESP + 0x18],ECX"
    },
    {
      "address": "00f47965",
      "instruction": "MOV dword ptr [ESP + 0x1c],EDX"
    },
    {
      "address": "00f47969",
      "instruction": "FILD qword ptr [ESP + 0x18]"
    },
    {
      "address": "00f4796d",
      "instruction": "FMUL float ptr [ESI + 0x18]"
    },
    {
      "address": "00f47970",
      "instruction": "FSTP float ptr [ESP + 0xc]"
    },
    {
      "address": "00f47974",
      "instruction": "CVTTSS2SI EAX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00f4797a",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00f4797c",
      "instruction": "MOV EAX,[0x015fd918]"
    },
    {
      "address": "00f47981",
      "instruction": "MOV ECX,dword ptr [EAX + 0x3c]"
    },
    {
      "address": "00f47984",
      "instruction": "MOV EDI,dword ptr [ECX + 0xb0]"
    },
    {
      "address": "00f4798a",
      "instruction": "MOV ECX,dword ptr [ESI + 0x20]"
    },
    {
      "address": "00f4798d",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00f4798f",
      "instruction": "MOV EAX,dword ptr [EDX + 0x44]"
    },
    {
      "address": "00f47992",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f47994",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00f47996",
      "instruction": "JZ 0x00f479af"
    },
    {
      "address": "00f47998",
      "instruction": "CMP EDI,0x2d"
    },
    {
      "address": "00f4799b",
      "instruction": "JGE 0x00f479af"
    },
    {
      "address": "00f4799d",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00f4799f",
      "instruction": "JGE 0x00f47ada"
    },
    {
      "address": "00f479a5",
      "instruction": "LEA EAX,[EDI + 0x1]"
    },
    {
      "address": "00f479a8",
      "instruction": "CDQ"
    },
    {
      "address": "00f479a9",
      "instruction": "XOR EAX,EDX"
    },
    {
      "address": "00f479ab",
      "instruction": "SUB EAX,EDX"
    },
    {
      "address": "00f479ad",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00f479af",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00f479b1",
      "instruction": "JLE 0x00f47a16"
    },
    {
      "address": "00f479b3",
      "instruction": "CALL 0x0068f4d0"
    },
    {
      "address": "00f479b8",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00f479ba",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00f479bc",
      "instruction": "MOV EAX,dword ptr [EDX + 0x34]"
    },
    {
      "address": "00f479bf",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "00f479c1",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f479c3",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00f479c5",
      "instruction": "JZ 0x00f479f6"
    },
    {
      "address": "00f479c7",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00f479c9",
      "instruction": "SUB ECX,EBX"
    },
    {
      "address": "00f479cb",
      "instruction": "CMP ECX,0x3"
    },
    {
      "address": "00f479ce",
      "instruction": "JGE 0x00f479d3"
    },
    {
      "address": "00f479d0",
      "instruction": "LEA EDI,[EBX + 0x3]"
    },
    {
      "address": "00f479d3",
      "instruction": "LEA EDX,[EDI + -0x1]"
    },
    {
      "address": "00f479d6",
      "instruction": "CMP EBX,EDX"
    },
    {
      "address": "00f479d8",
      "instruction": "JGE 0x00f479f6"
    },
    {
      "address": "00f479da",
      "instruction": "MOV ECX,dword ptr [ESI + 0x20]"
    },
    {
      "address": "00f479dd",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00f479df",
      "instruction": "MOV EAX,dword ptr [EAX + 0x84]"
    },
    {
      "address": "00f479e5",
      "instruction": "MOV EDX,EDI"
    },
    {
      "address": "00f479e7",
      "instruction": "SUB EDX,EBX"
    },
    {
      "address": "00f479e9",
      "instruction": "DEC EDX"
    },
    {
      "address": "00f479ea",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00f479eb",
      "instruction": "CALL EAX"
    },
    {
      "address": "00f479ed",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00f479ef",
      "instruction": "CALL 0x00f475b0"
    },
    {
      "address": "00f479f4",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00f479f6",
      "instruction": "SUB EDI,EBX
[TRUNCATED]
```

## external_callees

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "EXT:KERNEL32.DLL::QueryPerformanceCounter"
]
```

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 6561,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall with no ordinary stack arguments\",\n    \"ordinary_stack_arguments\": [],\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"plain RET\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 0,\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueFrameRuntime\"\n      ],\n      \"package\": \"PKG-FRAME-RUNTIME-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"cell_mode_update_00e80980\",\n      \"va\": \"0x00e80980\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-FRAME-RUNTIME-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"timing_update_body_00b31cc0\",\n      \"va\": \"0x00b31cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-FRAME-RUNTIME-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"cell_update_body_00e806b0\",\n      \"va\": \"0x00e806b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005bf9d0\",\n      \"va\": \"0x005bf9d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0100\",\n      \"va\": \"0x005c0100\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0380\",\n      \"va\": \"0x005c0380\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 3,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:UNCONDITIONAL_CALL\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 3,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueFrameRuntime\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f47b10\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00f47bb8\",\n        \"direction\": \"in\",\n        \"other\": \"0x00f47b10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f47a45\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f479b3\",\n        \"direction\": \"out\",\n        \"other\": \"0x0068f4d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f47a5b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00812d30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f47a05\",\n        \"direction\": \"out\",\n        \"other\": \"0x00921df0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f479ef\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f475b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f47a0f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f475b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00f4794d\",\n        \"direction\": \"out\",\n        \"other\": \"EXT:KERNEL32.DLL::QueryPerformanceCounter\",\n        \"reference_type\": \"external\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [\n      \"EXT:KERNEL32.DLL::QueryPerformanceCounter\"\n    ],\n    \"fan_in\": 1,\n    \"fan_out\": 1,\n    \"manifest_callees\": [\n      \"0x0067dcc0\",\n      \"0x0068f4d0\",\n      \"0x00812d30\",\n      \"0x00921df0\",\n      \"0x00f475b0\",\n      \"QueryPerformanceCounter\"\n    ],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0567\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"SUPPORTED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"app_frame_update_00f47930\",\n  \"normalized_symbol\": \"app_frame_update_00f47930\",\n  \"observed_mechanics\": [\n    \"{}\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-FRAME-RUNTIME-WAVE7\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": \"PKG-FRAME-RUNTIME-WAVE7\",\n    \"queue_state\": null\n  },\n  \"package\": \"PKG-FRAME-RUNTIME-WAVE7\",\n  \"reconstructed\": true,\n  \"review_status\": \"approved_after_parallel_review\",\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"required\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \
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
  "body_end": "00f47ae3",
  "body_span_bytes": 436,
  "body_start": "00f47930",
  "callees": [
    "QueryPerformanceCounter",
    "FUN_00921df0",
    "FUN_00812d30",
    "FUN_00f475b0",
    "App::IAppSystem::Get",
    "FUN_0068f4d0"
  ],
  "callers": [
    "FUN_00f47b10"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00f47930",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:8",
      "type": "undefined8"
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
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00f47930",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xb47930",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00f47930(void)",
  "size_bytes": 436,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00f47930",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00f47bb8"
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
  "file": "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.cpp",
    "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7.hpp",
    "src/reconstruction/pkg_frame_runtime_wave7/frame_runtime_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-frame-runtime-wave7/00f47930.json"
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
    "required"
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
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueFrameRuntime",
  "OpaqueSporeApp*",
  "UNCONDITIONAL_CALL"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x00f47410",
      "0x00f47700",
      "0x00f47ed0",
      "0x00f47700",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47410",
      "0x00f47700",
      "0x00f47700",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47b10"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:0",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00f47994",
      "0x00f47a14",
      "0x00f47b10",
      "0x00f47930",
      "0x00f47930",
      "0x00f47994",
      "0x00f47a14",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47994",
      "0x00f47a14",
      "0x00f47994",
      "0x00f47a14"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:1",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00f47969",
      "0x00f47a42",
      "0x00f47930",
      "0x00f47ad9",
      "0x00f47b10",
      "0x00f47700",
      "0x00f47700",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47969",
      "0x00f47a42",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47b10"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:2",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00aeb160",
      "0x00aebe90",
      "0x00aeb160",
      "0x00aebe90",
      "0x00f47b10",
      "0x00e552f0",
      "0x00e552f0",
      "0x00e7fc00",
      "0x00e7fc00",
      "0x00e80980",
      "0x00e80980",
      "0x00e81cf0",
      "0x00e81cf0",
      "0x00e81f30",
      "0x00e81f30",
      "0x00f47930"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:4",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Deferred trigger and owner/order semantics are not recovered; no immediate dispatch equivalence is claimed.",
    "resolution_status": "Deferred trigger and owner/order semantics are not recovered; no immediate dispatch equivalence is claimed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00f47930",
      "0x00f47700",
      "0x00f47700",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47930",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47b10",
      "0x00f47ed0",
      "0x00f47ed0",
      "0x00f47930",
      "0x00f47930"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/temporal-semantics.json:5",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "resolution_status": "The cited stream or file boundary is retained, but the complete wire/transaction/round-trip contract is not reconstructed.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    
[TRUNCATED]
```
