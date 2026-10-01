# Evidence 0x00e7fd00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `38a9875e008e8c90d508a2db5d406af050a3e7a365ba0ff4a358129fc353bfbd`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "stack_cleanup_bytes": 28
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
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_reassigned_before_deref",
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
  "conflicts": [
    {
      "field": "stack_cleanup_bytes",
      "inferred": 0,
      "kind": "inferred_vs_persisted",
      "persisted": 28,
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "b6795861c3f7f28ab47f9b4fb242c6d90298a86cb8924683febb6d0844f5b794",
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
    "indirect_calls": 7,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0150"
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
        "obs-0015",
        "obs-0075",
        "obs-0077",
        "obs-0086",
        "obs-0109",
        "obs-0110",
        "obs-0126",
        "obs-0134",
        "obs-0143",
        "obs-0145"
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
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0150"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "id": "obs-0001"
    },
    {
      "id": "obs-0002"
    },
    {
      "id": "obs-0003"
    },
    {
      "id": "obs-0004"
    },
    {
      "id": "obs-0005"
    },
    {
      "id": "obs-0006"
    },
    {
      "id": "obs-0007"
    },
    {
      "id": "obs-0008"
    },
    {
      "id": "obs-0009"
    },
    {
      "id": "obs-0010"
    },
    {
      "id": "obs-0011"
    },
    {
      "id": "obs-0012"
    },
    {
      "id": "obs-0013"
    },
    {
      "id": "obs-0014"
    },
    {
      "id": "obs-0015"
    },
    {
      "id": "obs-0016"
    },
    {
      "id": "obs-0017"
    },
    {
      "id": "obs-0018"
    },
    {
      "id": "obs-0019"
    },
    {
      "id": "obs-0020"
    },
    {
      "id": "obs-0021"
    },
    {
      "id": "obs-0022"
    },
    {
      "id": "obs-0023"
    },
    {
      "id": "obs-0024"
    },
    {
      "id": "obs-0025"
    },
    {
      "id": "obs-0026"
    },
    {
      "id": "obs-0027"
    },
    {
      "id": "obs-0028"
    },
    {
      "id": "obs-0029"
    },
    {
      "id": "obs-0030"
    },
    {
      "id": "obs-0031"
    },
    {
      "id": "obs-0032"
    },
    {
      "id": "obs-0033"
    },
    {
      "id": "obs-0034"
    },
    {
      "id": "obs-0035"
    },
    {
      "id": "obs-0036"
    },
    {
      "id": "obs-0037"
    },
    {
      "id": "obs-0038"
    },
    {
      "id": "obs-0039"
    },
    {
      "id": "obs-0040"
    },
    {
      "id": "obs-0041"
    },
    {
      "id": "obs-0042"
    },
    {
      "id": "obs-0043"
    },
    {
      "id": "obs-0044"
    },
    {
      "id": "obs-0045"
    },
    {
      "id": "obs-0046"
    },
    {
      "id": "obs-0047"
    },
    {
      "id": "obs-0048"
    },
    {
      "id": "obs-0049"
    },
    {
      "id": "obs-0050"
    },
    {
      "id": "obs-0051"
    },
    {
      "id": "obs-0052"
    },
    {
      "id": "obs-0053"
    },
    {
      "id": "obs-0054"
    },
    {
      "id": "obs-0055"
    },
    {
      "id": "obs-0056"
    },
    {
      "id": "obs-0057"
    },
    {
      "id": "obs-0058"
    },
    {
      "id": "obs-0059"
    },
    {
      "id": "obs-0060"
    },
    {
      "id": "obs-0061"
    },
    {
      "id": "obs-0062"
    },
    {
      "id": "obs-0063"
    },
    {
      "id": "obs-0064"
    },
    {
      "id": "obs-0065"
    },
    {
      "id": "obs-0066"
    },
    {
      "id": "obs-0067"
    },
    {
      "id": "obs-0068"
    },
    {
      "id": "obs-0069"
    },
    {
      "id": "
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "embedded_object_first_word_init_00743b50",
    "reconstructed": true,
    "va": "0x00743b50"
  },
  {
    "name": "FUN_00d018d0",
    "reconstructed": false,
    "va": "0x00d018d0"
  },
  {
    "name": "FUN_00e31100",
    "reconstructed": false,
    "va": "0x00e31100"
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
    "va": "0x00e80660"
  },
  {
    "name": "cell_update_body_00e806b0",
    "reconstructed": true,
    "va": "0x00e806b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e809a0"
  },
  {
    "name": "Simulator::Cell::cCellGame::Initialize",
    "reconstructed": false,
    "va": "0x00e80ba0"
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
      "0x00b72160",
      "0x00b72260",
      "0x00b72270",
      "0x00e665c0",
      "0x00e74a20",
      "0x00e80ba0",
      "0x00e80ba0",
      "0x00e74a20",
      "0x00b72160",
      "0x00b72260",
      "0x00e665c0",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00b72160",
      "0x00b72260",
      "0x00b72270"
    ],
    "conflict_id": "U-001-pool-contract",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The 4096 capacity, 920-byte Cell record, allocation/release path, and first-word free/self-index mechanics are bounded. Original sentinel, index-zero validity, and exact generic entry mapping remain unresolved.",
    "resolution_status": "The 4096 capacity, 920-byte Cell record, allocation/release path, and first-word free/self-index mechanics are bounded. Original sentinel, index-zero validity, and exact generic entry mapping remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e62340",
      "0x00e780a0",
      "0x00e7a7c0",
      "0x00e806b0",
      "0x00e7a7c0",
      "0x00e62340",
      "0x00e780a0",
      "0x00e806b0",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00e780a0",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e5b790",
      "0x00e665c0"
    ],
    "conflict_id": "U-003-cell-respawn-policy",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
    "resolution_status": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bb4af0",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00e74a20",
      "0x00e74a20"
    ],
    "conflict_id": "U-004-star-generation-boundary",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
    "resolution_status": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00eedd40",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e5b790",
      "0x00e80ba0",
      "0x00b72370",
      "0x00b72320",
      "0x00e780a0",
      "0x00b72160",
      "0x00b72260",
      "0x00b72270",
      "0x00b72370",
      "0x00bb4100",
      "0x00bb42a0"
    ],
    "conflict_id": "U-008-scenario-respawner",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e7fd00",
      "0x00e74a20",
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00b237c0",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e5b790",
      "0x00e665c0",
      "0x00e666f0",
      "0x00e80ba0",
      "0x00be34a0",
      "0x00bddef0",
      "0x00bdde70",
      "0x00bb5b50"
    ],
    "conflict_id": "U-009-runtime-validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  },
  {
    "anchors": [
      "0x00e780a0",
      "0x00e780a0",
      "0x000051d8",
      "0x00e7fd00"
    ],
    "conflict_id": "U8",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
   
[TRUNCATED]
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
  "count": 582,
  "instructions": [
    {
      "address": "00e7fd00",
      "instruction": "SUB ESP,0x28"
    },
    {
      "address": "00e7fd03",
      "instruction": "FLDZ"
    },
    {
      "address": "00e7fd05",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e7fd06",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e7fd07",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7fd08",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7fd09",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7fd0c",
      "instruction": "PUSH 0x1e08f6a"
    },
    {
      "address": "00e7fd11",
      "instruction": "CALL 0x00e82690"
    },
    {
      "address": "00e7fd16",
      "instruction": "FLDZ"
    },
    {
      "address": "00e7fd18",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e7fd1b",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7fd1e",
      "instruction": "PUSH 0x8a4d210e"
    },
    {
      "address": "00e7fd23",
      "instruction": "CALL 0x00e82690"
    },
    {
      "address": "00e7fd28",
      "instruction": "MOV EAX,[0x016b3c04]"
    },
    {
      "address": "00e7fd2d",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00e7fd2f",
      "instruction": "MOV byte ptr [EAX + 0x51d8],BL"
    },
    {
      "address": "00e7fd35",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7fd3b",
      "instruction": "MOV dword ptr [ECX + 0x411c],EBX"
    },
    {
      "address": "00e7fd41",
      "instruction": "MOV EDX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7fd47",
      "instruction": "MOV dword ptr [EDX + 0x51d4],EBX"
    },
    {
      "address": "00e7fd4d",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7fd53",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00e7fd56",
      "instruction": "ADD ECX,0x54"
    },
    {
      "address": "00e7fd59",
      "instruction": "CALL 0x00e31100"
    },
    {
      "address": "00e7fd5e",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7fd64",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00e7fd68",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00e7fd6c",
      "instruction": "ADD ECX,0x54"
    },
    {
      "address": "00e7fd6f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7fd70",
      "instruction": "CALL 0x00b72230"
    },
    {
      "address": "00e7fd75",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00e7fd77",
      "instruction": "JZ 0x00e7fdaa"
    },
    {
      "address": "00e7fd79",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "00e7fd80",
      "instruction": "FLDZ"
    },
    {
      "address": "00e7fd82",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00e7fd84",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00e7fd85",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e7fd86",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00e7fd88",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e7fd8b",
      "instruction": "CALL 0x00e7e130"
    },
    {
      "address": "00e7fd90",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7fd96",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00e7fd99",
      "instruction": "LEA EDX,[ESP + 0x10]"
    },
    {
      "address": "00e7fd9d",
      "instruction": "ADD ECX,0x54"
    },
    {
      "address": "00e7fda0",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e7fda1",
      "instruction": "CALL 0x00b72230"
    },
    {
      "address": "00e7fda6",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00e7fda8",
      "instruction": "JNZ 0x00e7fd80"
    },
    {
      "address": "00e7fdaa",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7fdb0",
      "instruction": "ADD ECX,0x54"
    },
    {
      "address": "00e7fdb3",
      "instruction": "CALL 0x00b72110"
    },
    {
      "address": "00e7fdb8",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7fdbe",
      "instruction": "ADD ECX,0x1c"
    },
    {
      "address": "00e7fdc1",
      "instruction": "CALL 0x00e31100"
    },
    {
      "address": "00e7fdc6",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7fdcc",
      "instruction": "MOV dword ptr [ESP + 0xc],EAX"
    },
    {
      "address": "00e7fdd0",
      "instruction": "LEA EAX,[ESP + 0xc]"
    },
    {
      "address": "00e7fdd4",
      "instruction": "ADD ECX,0x1c"
    },
    {
      "address": "00e7fdd7",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e7fdd8",
      "instruction": "CALL 0x00b72230"
    },
    {
      "address": "00e7fddd",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00e7fddf",
      "instruction": "JZ 0x00e7fee9"
    },
    {
      "address": "00e7fde5",
      "instruction": "MOV EDI,dword ptr [EAX]"
    },
    {
      "address": "00e7fde7",
      "instruction": "MOV ECX,dword ptr [0x016b3c04]"
    },
    {
      "address": "00e7fded",
      "instruction": "ADD ECX,0x1c"
    },
    {
      "address": "00e7fdf0",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e7fdf1",
      "instruction": "CALL 0x00b721d0"
    },
    {
      "address": "00e7fdf6",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00e7fdf8",
      "instruction": "JZ 0x00e7fece"
    },
    {
      "address": "00e7fdfe",
      "instruction": "MOV EAX,[0x016b3c04]"
    },
    {
      "address": "00e7fe03",
      "instruction": "CMP EDI,dword ptr [EAX + 0x411c]"
    },
    {
      "address": "00e7fe09
[TRUNCATED]
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
  "original_bytes": 25517,
  "preview": "{\n  \"abi\": {\n    \"stack_cleanup_bytes\": 28\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:CellObjectData,CellResourceRef,ObservedObjectPool,OpaqueResourceScope\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 23,\n      \"symbol\": \"FUN_00e780a0\",\n      \"va\": \"0x00e780a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:CellObjectData,CellResourceRef,OpaqueResourceScope\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 23,\n      \"symbol\": \"FUN_00e7a4a0\",\n      \"va\": \"0x00e7a4a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:CellObjectData,CellResourceRef\"\n      ],\n      \"package\": \"PKG-06-CELL-STATE\",\n      \"score\": 20,\n      \"symbol\": \"FUN_00e7a7c0\",\n      \"va\": \"0x00e7a7c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-06A-CELL-AI-SELECTION\",\n      \"score\": 14,\n      \"symbol\": \"cell_ai_select_profile_00e52910\",\n      \"va\": \"0x00e52910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3f0\",\n      \"va\": \"0x00b3d3f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d430\",\n      \"va\": \"0x00b3d430\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reset order accepted; mode tables, external manager results, global registry ownership, and argument roles remain gated, and Cell identity versus Cell GFX ordering stays separate.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": null,\n  \"confidence\": 0.58,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"embedded_object_first_word_init_00743b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00743b50\"\n      },\n      {\n        \"name\": \"FUN_00d018d0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00d018d0\"\n      },\n      {\n        \"name\": \"FUN_00e31100\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e31100\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e80660\"\n      },\n      {\n        \"name\": \"cell_update_body_00e806b0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e806b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e809a0\"\n      },\n      {\n        \"name\": \"Simulator::Cell::cCellGame::Initialize\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e80ba0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e8067f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e80660\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8069e\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e80660\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8088c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e806b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80b6c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e809a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80f9f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e80ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e80126\",\n        \"direction\": \"out\",\n        \"other\": \"0x00743b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e805fa\",\n        \"direction\": \"out\",\n        \"other\": \"0x00743b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e805d8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00807bb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7ff39\",\n        \"direction\": \"out\",\n        \"other\": \"0x00810590\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e805cb\",\n        \"direction\": \"out\",\n        \"other\": \"0x008105b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7fdb3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72110\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7ffff\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72110\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"cal
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
  "body_end": "00e80653",
  "body_span_bytes": 2388,
  "body_start": "00e7fd00",
  "callees": [
    "FUN_00e31100",
    "FUN_00e82130",
    "FUN_00b72230",
    "FUN_00e7e130",
    "FUN_00b72110",
    "FUN_00b72260",
    "FUN_00807bb0",
    "FUN_00e50810",
    "FUN_00e65180",
    "FUN_00e750c0",
    "FUN_00e78b20",
    "FUN_00e86b60",
    "FUN_00e5f360",
    "thunk_FUN_00e823a0",
    "FUN_00e86980",
    "FUN_00e78c00",
    "FUN_00e82690",
    "FUN_00e7d370",
    "FUN_00e4cce0",
    "FUN_00e66010",
    "FUN_00e6eb60",
    "FUN_00d018d0",
    "FUN_00e4ce40",
    "FUN_00b72210",
    "FUN_00bbb0e0",
    "FUN_00b721d0",
    "FUN_008105b0",
    "FUN_00e6ecb0",
    "FUN_00e78b80",
    "FUN_00810590",
    "thunk_FUN_00bbb210",
    "FUN_00743b50"
  ],
  "callers": [
    "FUN_00e806b0",
    "FUN_00e809a0",
    "FUN_00e80660",
    "Simulator::Cell::cCellGame::Initialize"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e7fd00",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
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
      "name": "local_34",
      "storage": "Stack[-0x34]:1",
      "type": "undefined"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    },
    {
      "name": "local_40",
      "storage": "Stack[-0x40]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_00e7fd00",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xa7fd00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00e7fd00(void)",
  "size_bytes": 2388,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e7fd00",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "00e8088c"
    },
    {
      "from": "00e80b6c"
    },
    {
      "from": "00e80f9f"
    },
    {
      "from": "00e8067f"
    },
    {
      "from": "00e8069e"
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
  "file": "src/reconstruction/pkg06_cell_state/cell_state.cpp",
  "files": [
    "src/reconstruction/pkg06_cell_state/cell_state.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg06-cell-state/00e7fd00.json"
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
    "cell_reset_observation"
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 14358,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": \"SUPPORTED\"\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 36,\n  \"evidence\": [\n    {\n      \"independent_limit\": \"Several argument types and helper names are undefined.\",\n      \"kind\": \"direct_decompilation\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7fd00\",\n      \"supports\": [\n        \"pool drain sequence\",\n        \"serializable progression writes\",\n        \"world-reference branches\",\n        \"population/player creation\",\n        \"hatch selection\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Same binary source; control-flow cross-check only.\",\n      \"kind\": \"disassembly\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@0x00e7fd00\",\n      \"supports\": [\n        \"clear +0x51d8/+0x411c/+0x51d4\",\n        \"pool loops\",\n        \"UI/GFX reset offsets\",\n        \"scale table\",\n        \"serializable offsets +0x1c..+0x28\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Static xrefs do not establish invocation frequency.\",\n      \"kind\": \"callgraph_xrefs\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@xrefs@0x00e7fd00\",\n      \"supports\": [\n        \"4 direct callers\",\n        \"32 direct callees\",\n        \"init/frame reachability\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Some binary fields are generic pointers or padding.\",\n      \"kind\": \"structure_layout\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@structure:cCellGame\",\n      \"supports\": [\n        \"pool +0x01c/+0x054\",\n        \"world +0x4114/+0x4118\",\n        \"avatar +0x411c\",\n        \"serializable +0x5190\",\n        \"reload +0x51d8\"\n      ]\n    },\n    {\n      \"independent_limit\": \"No disk serializer body is part of this target.\",\n      \"kind\": \"structure_layout\",\n      \"source\": \"Ghidra MCP:SporeApp.exe@structure:cCellSerializableData\",\n      \"supports\": [\n        \"progression and kill/death field offsets\",\n        \"separate 236-byte candidate\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Secondary static artifact; exact ABI unresolved.\",\n      \"kind\": \"committed_state_machine_artifact\",\n      \"source\": \"knowledgegraph/research/state-machines/cell-stage.json:301-327\",\n      \"supports\": [\n        \"stage rebuild and parameter groups\"\n      ]\n    },\n    {\n      \"independent_limit\": \"Explicitly static and runtime-unresolved.\",\n      \"kind\": \"committed_transition_artifact\",\n      \"source\": \"docs/analysis/gameplay-transition-map.md:101-107\",\n      \"supports\": [\n        \"reload request to stage rebuild and identity-destructive rebuild\"\n      ]\n    }\n  ],\n  \"family\": \"cell_stage_rebuild_and_world_repopulation\",\n  \"interfaces\": {\n    \"boundaries\": {\n      \"boundary_rule\": \"This is a stage-rebuild coordinator, not a save/load transaction and not proof that the renderer owns stage state.\",\n      \"classification\": \"cross_boundary\",\n      \"inbound\": \"App/mode lifecycle or frame reload request\",\n      \"outbound\": [\n        \"CellGame pool/avatar\",\n        \"serializable progression\",\n        \"world/resource refs\",\n        \"cCellUI\",\n        \"cCellGFX/effects\",\n        \"advect/population\",\n        \"animation/hatch path\"\n      ]\n    },\n    \"direct_callees\": [\n      {\n        \"role\": \"dispatch/drain interaction records\",\n        \"va\": \"0x00e7e130\"\n      },\n      {\n        \"role\": \"release old records\",\n        \"va\": \"0x00b72260\"\n      },\n      {\n        \"role\": \"detach old GFX association\",\n        \"va\": \"0x00e66010\"\n      },\n      {\n        \"role\": \"reconcile/rebuild current player GFX\",\n        \"va\": \"0x00e78c00\"\n      },\n      {\n        \"role\": \"create player Cell and bind presentation\",\n        \"va\": \"0x00e750c0\"\n      },\n      {\n        \"role\": \"egg/autohatch branch\",\n        \"va\": \"0x00e6eb60\"\n      },\n      {\n        \"role\": \"ice-hatch cinematic branch\",\n        \"va\": \"0x00e6ecb0\"\n      },\n      {\n        \"role\": \"populate initial records\",\n        \"va\": \"0x00e7d370\"\n      },\n      {\n        \"role\": \"refresh current/next advect\",\n        \"va\": \"0x00e5f360\"\n      },\n      {\n        \"role\": \"GFX vector/range release\",\n        \"va\": \"0x00e65180\"\n      },\n      {\n        \"role\": \"entry hash/key setup; exact contract unresolved\",\n        \"va\": \"0x00e82690\"\n      },\n      {\n        \"role\": \"world/resource acquisition\",\n        \"va\": \"0x00e4ce40/FUN_00e4cce0\"\n      }\n    ],\n    \"direct_callers\": [\n      {\n        \"name\": \"FUN_00e80660\",\n        \"role\": \"direct rebuild trigger\",\n        \"va\": \"0x00e80660\"\n      },\n      {\n        \"name\": \"FUN_00e806b0\",\n        \"role\": \"frame orchestrator; observes +0x51d8\",\n        \"va\": \"0x00e806b0\"\n      },\n      {\n        \"name\": \"FUN_00e809a0\",\n        \"role\": \"Cell initialization/action entry\",\n        \"va\": \"0x00e809a0\"\n      },\n      {\n        \"role\": \"initial rebuild after setup\",\n        \"va\": \"Simulator::Cell::cCellGame::Initialize@0x00e80ba0\"\n      }\n    ],\n    \"globals\": [],\n    \"structures\": [],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": {\n        \"event_dispatch\": \"Interaction drain uses FUN_00e7e130 and then releases records; dispatcher failures are not surfaced.\",\n        \"missing_service\": \"No explicit null check protects sCellGame, sCellUI, sCellGFX, or serializable data; invalid service state is a fault path rather than a documented failure result.\",\n        \"player_creation\": \"No local result check proves successful allocation/GFX attachment.\",\n        \"pool_lookup\": \"Pool loops can skip invalid records
[TRUNCATED]
```

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
  "CellObjectData",
  "CellResourceRef",
  "None",
  "ObservedAudioConfig",
  "ObservedCallbackVtablePrefix",
  "ObservedObjectPool",
  "ObservedStageRecord",
  "OpaqueResourceScope",
  "std::int32_t",
  "std::uint32_t",
  "std::uint8_t",
  "void"
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
      "0x00b72160",
      "0x00b72260",
      "0x00b72270",
      "0x00e665c0",
      "0x00e74a20",
      "0x00e80ba0",
      "0x00e80ba0",
      "0x00e74a20",
      "0x00b72160",
      "0x00b72260",
      "0x00e665c0",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00b72160",
      "0x00b72260",
      "0x00b72270"
    ],
    "conflict_id": "U-001-pool-contract",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The 4096 capacity, 920-byte Cell record, allocation/release path, and first-word free/self-index mechanics are bounded. Original sentinel, index-zero validity, and exact generic entry mapping remain unresolved.",
    "resolution_status": "The 4096 capacity, 920-byte Cell record, allocation/release path, and first-word free/self-index mechanics are bounded. Original sentinel, index-zero validity, and exact generic entry mapping remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e62340",
      "0x00e780a0",
      "0x00e7a7c0",
      "0x00e806b0",
      "0x00e7a7c0",
      "0x00e62340",
      "0x00e780a0",
      "0x00e806b0",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00e780a0",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e5b790",
      "0x00e665c0"
    ],
    "conflict_id": "U-003-cell-respawn-policy",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
    "resolution_status": "Damage/death branches, despawn cleanup, optional scale replacement, and deferred stage rebuild are concrete. Caller-specific respawn policy and replacement ordering are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bb4af0",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00e74a20",
      "0x00e74a20"
    ],
    "conflict_id": "U-004-star-generation-boundary",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
    "resolution_status": "0x00bb4100 and 0x00bb4ba0 are coherent current bodies; SDK addresses 0x00bb42a0 and 0x00bb4c90 are retained as interior/alias candidates. mPlanetCount creation is visible, but append/materialization order is not.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00eedd40",
      "0x00e7fd00",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e5b790",
      "0x00e80ba0",
      "0x00b72370",
      "0x00b72320",
      "0x00e780a0",
      "0x00b72160",
      "0x00b72260",
      "0x00b72270",
      "0x00b72370",
      "0x00bb4100",
      "0x00bb42a0"
    ],
    "conflict_id": "U-008-scenario-respawner",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e7fd00",
      "0x00e74a20",
      "0x00bb42a0",
      "0x00bb4c90",
      "0x00b237c0",
      "0x00e74a20",
      "0x00e74a20",
      "0x00e4ce20",
      "0x00e5b790",
      "0x00e665c0",
      "0x00e666f0",
      "0x00e80ba0",
      "0x00be34a0",
      "0x00bddef0",
      "0x00bdde70",
      "0x00bb5b50"
    ],
    "conflict_id": "U-009-runtime-validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": 
[TRUNCATED]
```
