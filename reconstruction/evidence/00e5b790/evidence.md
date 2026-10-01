# Evidence 0x00e5b790

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `769190db12e3300be241884097ea8910e2cca3664a9b49460162518c9e1d68bf`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__cdecl",
  "hidden_this_register": "none",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": [
    "float delta_time"
  ],
  "ret_form": "plain RET",
  "return_type": "void",
  "stack_cleanup_bytes": 4
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
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
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
  "conflicts": [
    {
      "field": "stack_cleanup_bytes",
      "inferred": 0,
      "kind": "inferred_vs_persisted",
      "persisted": 4,
      "resolution_status": "unresolved"
    }
  ],
  "content_sha256": "ed768091216fb2b715f26015c8202f37201823f79accc7683e3f5bbe5ed33dc0",
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
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "__cdecl"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0072"
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
        "obs-0016",
        "obs-0021",
        "obs-0024",
        "obs-0028",
        "obs-0059"
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
        "obs-0072"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0072"
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
      "at": "0x00e5b790",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x016b3c04]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "and_esp": null,
      "at": "0x00e5b795",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0002",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x38",
      "sub": 56
    },
    {
      "at": "0x00e5b795",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x38",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00e5b798",
      "count": 21,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "CMP dword ptr [EAX + 0x5158],0x0",
      "reg": "EAX"
    },
    {
      "at": "0x00e5b7a5",
      "definite": true,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x411c]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00e5b7ab",
      "count": 15,
      "first_use": 5,
      "first_write_index": 9,
      "id": "obs-0006",
      "index": 5,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00e5b7ac",
      "count": 11,
      "first_use": 6,
      "first_write_index": 36,
      "id": "obs-0007",
      "index": 6,
      "kind": "REG_READ",
      "raw": "LEA ECX,[EAX + 0x1c]",
      "reg": "ECX"
    },
    {
      "at": "0x00e5b7af",
      "count": 9,
      "first_use": 7,
      "first_write_index": 4,
      "id": "obs-0008",
      "index": 7,
      "kind": "REG_READ",
      "raw": "PUSH EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00e5b7b0",
      "id": "obs-0009",
      "index": 8,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b721d0",
      "target": "0x00b721d0"
    },
    {
      "at": "0x00e5b7b5",
      "definite": true,
      "id": "obs-0010",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,EAX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00e5b7bf",
      "count": 29,
      "first_use": 12,
      "first_write_index": 1,
      "id": "obs-0011",
      "index": 12,
      "kind": "REG_READ",
      "raw": "FLD float ptr [ESP + 0x40]",
      "reg": "ESP"
    },
    {
      "at": "0x00e5b7bf",
      "base": "ESP",
      "disp": 64,
      "id": "obs-0012",
      "index": 12,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "FLD float ptr [ESP + 0x40]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x00e5b7c3",
      "count": 1,
      "first_us
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
    "name": "camera_light_origin_helper_007c4900",
    "reconstructed": true,
    "va": "0x007c4900"
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
    "name": "cell_update_body_00e806b0",
    "reconstructed": true,
    "va": "0x00e806b0"
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
      "0x00e80ba0",
      "0x00e74a20",
      "0x00e5b790",
      "0x00e80ba0",
      "0x00e5b790",
      "0x00000000"
    ],
    "conflict_id": "TB-INH-003",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "separate_entities",
      "preferred_claim": "Use coordination/composition, not inheritance.",
      "preserved_alternatives": true,
      "scope_note": "Current source ownership is non-equivalent and remains a comparison boundary.",
      "status": "preserved_alternatives",
      "taxonomy": "preserved_alternatives"
    },
    "resolution_status": "preserved_alternatives",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "CellGame, CellGFX, and CellUI coordination versus inheritance",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
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
  "count": 155,
  "instructions": [
    {
      "address": "00e5b790",
      "instruction": "MOV EAX,[0x016b3c04]"
    },
    {
      "address": "00e5b795",
      "instruction": "SUB ESP,0x38"
    },
    {
      "address": "00e5b798",
      "instruction": "CMP dword ptr [EAX + 0x5158],0x0"
    },
    {
      "address": "00e5b79f",
      "instruction": "JNZ 0x00e5b9fe"
    },
    {
      "address": "00e5b7a5",
      "instruction": "MOV EDX,dword ptr [EAX + 0x411c]"
    },
    {
      "address": "00e5b7ab",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00e5b7ac",
      "instruction": "LEA ECX,[EAX + 0x1c]"
    },
    {
      "address": "00e5b7af",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e5b7b0",
      "instruction": "CALL 0x00b721d0"
    },
    {
      "address": "00e5b7b5",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00e5b7b7",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00e5b7b9",
      "instruction": "JZ 0x00e5b9fd"
    },
    {
      "address": "00e5b7bf",
      "instruction": "FLD float ptr [ESP + 0x40]"
    },
    {
      "address": "00e5b7c3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00e5b7c4",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e5b7c5",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e5b7c8",
      "instruction": "CALL 0x00e5b2e0"
    },
    {
      "address": "00e5b7cd",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e5b7d0",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "00e5b7d4",
      "instruction": "CALL 0x00743b50"
    },
    {
      "address": "00e5b7d9",
      "instruction": "LEA EAX,[ESP + 0x8]"
    },
    {
      "address": "00e5b7dd",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e5b7de",
      "instruction": "CALL 0x00e4ce40"
    },
    {
      "address": "00e5b7e3",
      "instruction": "MOV EDI,dword ptr [EAX + 0xd4]"
    },
    {
      "address": "00e5b7e9",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00e5b7ec",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "00e5b7f0",
      "instruction": "CALL 0x00e82130"
    },
    {
      "address": "00e5b7f5",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00e5b7f7",
      "instruction": "JL 0x00e5b835"
    },
    {
      "address": "00e5b7f9",
      "instruction": "CMP EDI,0x1"
    },
    {
      "address": "00e5b7fc",
      "instruction": "JLE 0x00e5b817"
    },
    {
      "address": "00e5b7fe",
      "instruction": "CMP EDI,0x2"
    },
    {
      "address": "00e5b801",
      "instruction": "JNZ 0x00e5b835"
    },
    {
      "address": "00e5b803",
      "instruction": "CALL 0x00e50730"
    },
    {
      "address": "00e5b808",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e5b80a",
      "instruction": "JNZ 0x00e5b835"
    },
    {
      "address": "00e5b80c",
      "instruction": "MOV ECX,dword ptr [0x016b3c0c]"
    },
    {
      "address": "00e5b812",
      "instruction": "CMP byte ptr [ECX + 0x26],AL"
    },
    {
      "address": "00e5b815",
      "instruction": "JMP 0x00e5b82f"
    },
    {
      "address": "00e5b817",
      "instruction": "CALL 0x00e50730"
    },
    {
      "address": "00e5b81c",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00e5b81e",
      "instruction": "JNZ 0x00e5b835"
    },
    {
      "address": "00e5b820",
      "instruction": "MOV EAX,[0x016b3c0c]"
    },
    {
      "address": "00e5b825",
      "instruction": "CMP byte ptr [EAX + 0x24],0x0"
    },
    {
      "address": "00e5b829",
      "instruction": "JNZ 0x00e5b835"
    },
    {
      "address": "00e5b82b",
      "instruction": "CMP byte ptr [EAX + 0x26],0x0"
    },
    {
      "address": "00e5b82f",
      "instruction": "JZ 0x00e5b9fc"
    },
    {
      "address": "00e5b835",
      "instruction": "CALL 0x0067dd10"
    },
    {
      "address": "00e5b83a",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00e5b83c",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e5b83e",
      "instruction": "MOV EAX,dword ptr [EDX + 0x58]"
    },
    {
      "address": "00e5b841",
      "instruction": "CALL EAX"
    },
    {
      "address": "00e5b843",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "00e5b847",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e5b848",
      "instruction": "LEA EDX,[ESP + 0x28]"
    },
    {
      "address": "00e5b84c",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e5b84d",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e5b84f",
      "instruction": "CALL 0x007c4900"
    },
    {
      "address": "00e5b854",
      "instruction": "MOVSS XMM2,dword ptr [0x015a7c44]"
    },
    {
      "address": "00e5b85c",
      "instruction": "MOVSS XMM4,dword ptr [0x015a7c48]"
    },
    {
      "address": "00e5b864",
      "instruction": "MOVSS XMM5,dword ptr [0x016b3c2c]"
    },
    {
      "address": "00e5b86c",
      "instruction": "MOVSS XMM0,dword ptr [0x016b3c30]"
    },
    {
      "address": "00e5b874",
      "instruction": "MOVSS XMM6,dword ptr [0x015a7c40]"
    },
    {
      "address": "00e5b87c",
      "instruction": "MOVSS XMM1,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00e5b882",
      "instruction": "MOVSS XMM3,dword ptr [0x013eb8b0]"
    },
    {
      "address": "00e5b88a",
      "instruction": "MULSS XMM0,XMM4"
    },
    {
      "address": "00e5b88e",
      "instruction": "MULSS XMM5,XMM2"
    },
    {
      "address": "00e5b892",
      "instruction": "ADDSS XMM5,XMM0"
    },
    {
      "address": "00e5b896",
      "instruction": "MOVAPS XMM0,XMM6"
    },
    {
      "address": "00e5b899",
      "instruction": "MULSS XMM0,dword ptr [0x016b3c28]"
    },
    {
      "address": "00e5b8a1",
      "instruction": "ADDSS XMM5,XMM0"
    },
  
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
  "original_bytes": 8420,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__cdecl\",\n    \"hidden_this_register\": \"none\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"ordinary_stack_arguments\": [\n      \"float delta_time\"\n    ],\n    \"ret_form\": \"plain RET\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 25,\n      \"symbol\": \"camera_light_origin_helper_007c4900\",\n      \"va\": \"0x007c4900\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"cell_get_globals_data_00e4ce20\",\n      \"va\": \"0x00e4ce20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"camera_manager_set_active_007c64c0\",\n      \"va\": \"0x007c64c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"camera_manager_dispose_007c6e50\",\n      \"va\": \"0x007c6e50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"editor_camera_func24h_005a2050\",\n      \"va\": \"0x005a2050\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"editor_camera_func54h_005a2320\",\n      \"va\": \"0x005a2320\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"editor_camera_on_exit_00c2e640\",\n      \"va\": \"0x00c2e640\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-H3-HELPER-WAVE2\",\n      \"score\": 3,\n      \"symbol\": \"embedded_object_first_word_init_00743b50\",\n      \"va\": \"0x00743b50\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCameraState\",\n  \"cluster\": \"sim-cell\",\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"embedded_object_first_word_init_00743b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00743b50\"\n      },\n      {\n        \"name\": \"camera_light_origin_helper_007c4900\",\n        \"reconstructed\": true,\n        \"va\": \"0x007c4900\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"cell_update_body_00e806b0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e806b0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e8083b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e806b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b835\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b9dd\",\n        \"direction\": \"out\",\n        \"other\": \"0x0069b600\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b7d4\",\n        \"direction\": \"out\",\n        \"other\": \"0x00743b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b84f\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c4900\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b7b0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b721d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b7de\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4ce40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b803\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e50730\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b817\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e50730\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b7c8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e5b2e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5b7f0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e82130\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 2,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00743b50\",\n      \"0x007c4900\",\n      \"0x00e806b0\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0526
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
  "body_end": "00e5ba01",
  "body_span_bytes": 626,
  "body_start": "00e5b790",
  "callees": [
    "FUN_00e4ce40",
    "FUN_0069b600",
    "FUN_00e50730",
    "FUN_00e5b2e0",
    "FUN_00b721d0",
    "FUN_007c4900",
    "FUN_00e82130",
    "Graphics::IRenderer::Get",
    "FUN_00743b50"
  ],
  "callers": [
    "FUN_00e806b0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e5b790",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:1",
      "type": "undefined"
    },
    {
      "name": "local_44",
      "storage": "Stack[-0x44]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "Simulator::Cell::MovePlayerToMousePosition",
  "namespace": "Simulator",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "deltaTime",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "float"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0xa5b790",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Simulator::Cell::MovePlayerToMousePosition(float deltaTime)",
  "size_bytes": 626,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e5b790",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00e8083b"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__MovePlayerToMousePosition.c",
  "file": "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__MovePlayerToMousePosition.c",
    "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
    "src/reconstruction/pkg_camera_wave7/camera_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-camera-wave7/00e5b790.json"
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
    "Original Cell-mode Wine trace and live movement-plane values are not available; no runtime promotion is claimed.",
    "runtime observation required"
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
  "OpaqueCameraState",
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
      "0x00e80ba0",
      "0x00e74a20",
      "0x00e5b790",
      "0x00e80ba0",
      "0x00e5b790",
      "0x00000000"
    ],
    "conflict_id": "TB-INH-003",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": {
      "merge_decision": "separate_entities",
      "preferred_claim": "Use coordination/composition, not inheritance.",
      "preserved_alternatives": true,
      "scope_note": "Current source ownership is non-equivalent and remains a comparison boundary.",
      "status": "preserved_alternatives",
      "taxonomy": "preserved_alternatives"
    },
    "resolution_status": "preserved_alternatives",
    "source": "knowledgegraph/research/conflicts/track-b-vtable-fields.json",
    "subject": "CellGame, CellGFX, and CellUI coordination versus inheritance",
    "unresolved_reason": "The cited static evidence leaves the competing owner, slot, layout, or lifecycle interpretation unresolved; no positive original runtime or MSVC RTTI evidence is available."
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
  }
]
```
