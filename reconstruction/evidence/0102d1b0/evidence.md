# Evidence 0x0102d1b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `805fab7debe8838cde35010688fabd02ce94760054850db9aea736242563cde2`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "cdecl observed; no implicit this parameter",
  "return_observation": "The live function ends through ordinary void RET paths; the staged implementation does not add an implicit this parameter.",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "observed_use": "Loaded from the first stack slot and forwarded to helpers; no +0x70 or +0xAC access is attributed to this pointer.",
      "position": 1,
      "type": "Space *",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "observed_use": "Loaded into EDI, used as the explicit ECX operand for FUN_00bba990, and accessed at +0x70 and +0xAC.",
      "position": 2,
      "type": "SpaceContext *",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0C",
      "observed_use": "Loaded into EBP, compared with the result of FUN_0102fa30(4), and used in signed interval and branch selection.",
      "position": 3,
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ]
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
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
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "b45527a8e5557977f0b9c54f8316fc0f38172bf790f354b41999fb3fd3ef6c52",
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
    "persisted_calling_convention": "cdecl observed; no implicit this parameter"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 9,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0185"
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
        "obs-0018"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0025",
        "obs-0038",
        "obs-0041",
        "obs-0074",
        "obs-0076",
        "obs-0112",
        "obs-0115",
        "obs-0130",
        "obs-0136",
        "obs-0139",
        "obs-0155",
        "obs-0157",
        "obs-0158",
        "obs-0163",
        "obs-0176",
        "obs-0188",
        "obs-0200",
        "obs-0206"
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
        "obs-0185"
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
    }
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "achievement_progress_update_00676e90",
    "reconstructed": true,
    "va": "0x00676e90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  },
  {
    "name": "FUN_00aea230",
    "reconstructed": true,
    "va": "0x00aea230"
  },
  {
    "name": "Simulator_cCommManager_CreateAndDispatchEvent_00aeb720",
    "reconstructed": true,
    "va": "0x00aeb720"
  },
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
  },
  {
    "name": "FUN_00b3d2c0",
    "reconstructed": false,
    "va": "0x00b3d2c0"
  },
  {
    "name": "Simulator_cSpaceTrading_Get",
    "reconstructed": true,
    "va": "0x00b3d4d0"
  },
  {
    "name": "FUN_00b8dab0",
    "reconstructed": false,
    "va": "0x00b8dab0"
  },
  {
    "name": "Simulator_LookupEmpireByPoliticalId",
    "reconstructed": true,
    "va": "0x00ba9370"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bbaa60"
  },
  {
    "name": "FUN_00c70e00",
    "reconstructed": false,
    "va": "0x00c70e00"
  },
  {
    "name": "context_word_read_00ce6950",
    "reconstructed": true,
    "va": "0x00ce6950"
  },
  {
    "name": "FUN_00e39ab0",
    "reconstructed": false,
    "va": "0x00e39ab0"
  },
  {
    "name": "FUN_01021080",
    "reconstructed": true,
    "va": "0x01021080"
  },
  {
    "name": "FUN_01021090",
    "reconstructed": false,
    "va": "0x01021090"
  },
  {
    "name": "FUN_01021230",
    "reconstructed": true,
    "va": "0x01021230"
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
    "va": "0x0102df20"
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
      "0x00aeb160",
      "0x00aebe90",
      "0x00aed2c0",
      "0x00c75520",
      "0x00dd5160",
      "0x0102c9e0",
      "0x0102caa0",
      "0x0102cae0",
      "0x0102cc30",
      "0x0102cd90",
      "0x0102ce30",
      "0x0102cf10",
      "0x0102d1b0",
      "0x0102df20",
      "0x01072d40",
      "0x00aeb730"
    ],
    "conflict_id": "LC-006",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_SUPPORTED",
    "resolution_status": "RESOLVED_SUPPORTED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x00AEB720 communication wrapper",
    "unresolved_reason": "The exact private wrapper name and the full parameter types are not recoverable from static naming alone; the create-and-dispatch contract is resolved."
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
  "count": 451,
  "instructions": [
    {
      "address": "0102d1b0",
      "instruction": "SUB ESP,0xb8"
    },
    {
      "address": "0102d1b6",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0102d1b7",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0102d1b8",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0102d1b9",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0102d1ba",
      "instruction": "MOV EDI,dword ptr [ESP + 0xd0]"
    },
    {
      "address": "0102d1c1",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0102d1c3",
      "instruction": "CALL 0x00bba990"
    },
    {
      "address": "0102d1c8",
      "instruction": "PUSH 0x4"
    },
    {
      "address": "0102d1ca",
      "instruction": "MOV dword ptr [ESP + 0x18],EAX"
    },
    {
      "address": "0102d1ce",
      "instruction": "MOV dword ptr [ESP + 0x14],0x92a95b57"
    },
    {
      "address": "0102d1d6",
      "instruction": "XOR BL,BL"
    },
    {
      "address": "0102d1d8",
      "instruction": "CALL 0x0102f810"
    },
    {
      "address": "0102d1dd",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0102d1df",
      "instruction": "CALL 0x0102fa30"
    },
    {
      "address": "0102d1e4",
      "instruction": "MOV EBP,dword ptr [ESP + 0xd4]"
    },
    {
      "address": "0102d1eb",
      "instruction": "CMP EBP,EAX"
    },
    {
      "address": "0102d1ed",
      "instruction": "JNZ 0x0102d1f9"
    },
    {
      "address": "0102d1ef",
      "instruction": "MOV dword ptr [ESP + 0x10],0x57c98667"
    },
    {
      "address": "0102d1f7",
      "instruction": "MOV BL,0x1"
    },
    {
      "address": "0102d1f9",
      "instruction": "MOV ESI,EBP"
    },
    {
      "address": "0102d1fb",
      "instruction": "SUB ESI,dword ptr [ESP + 0x14]"
    },
    {
      "address": "0102d1ff",
      "instruction": "CALL 0x0102f810"
    },
    {
      "address": "0102d204",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0102d206",
      "instruction": "CALL 0x0102ffc0"
    },
    {
      "address": "0102d20b",
      "instruction": "CMP ESI,EAX"
    },
    {
      "address": "0102d20d",
      "instruction": "JLE 0x0102d662"
    },
    {
      "address": "0102d213",
      "instruction": "FLD1"
    },
    {
      "address": "0102d215",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0102d216",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "0102d219",
      "instruction": "PUSH 0x55901b3"
    },
    {
      "address": "0102d21e",
      "instruction": "CALL 0x01021090"
    },
    {
      "address": "0102d223",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0102d224",
      "instruction": "MOV EAX,dword ptr [ESP + 0xd8]"
    },
    {
      "address": "0102d22b",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0102d22c",
      "instruction": "CALL 0x00b3d2c0"
    },
    {
      "address": "0102d231",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0102d233",
      "instruction": "CALL 0x00d06240"
    },
    {
      "address": "0102d238",
      "instruction": "FSTP ST0"
    },
    {
      "address": "0102d23a",
      "instruction": "MOV dword ptr [ESP + 0x10],0xe8a568ec"
    },
    {
      "address": "0102d242",
      "instruction": "MOV EDX,dword ptr [ESP + 0xcc]"
    },
    {
      "address": "0102d249",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0102d24a",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "0102d24f",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0102d251",
      "instruction": "CALL 0x00ba9370"
    },
    {
      "address": "0102d256",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "0102d258",
      "instruction": "LEA ECX,[ESP + 0x18]"
    },
    {
      "address": "0102d25c",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0102d25d",
      "instruction": "MOV ECX,dword ptr [EDI + 0x70]"
    },
    {
      "address": "0102d260",
      "instruction": "LEA EDX,[ESP + 0x2c]"
    },
    {
      "address": "0102d264",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0102d265",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0102d266",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0102d267",
      "instruction": "LEA EDX,[ESP + 0x48]"
    },
    {
      "address": "0102d26b",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0102d26c",
      "instruction": "LEA ECX,[ESP + 0x5c]"
    },
    {
      "address": "0102d270",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0102d271",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0102d272",
      "instruction": "PUSH 0xfdd30461"
    },
    {
      "address": "0102d277",
      "instruction": "MOV dword ptr [ESP + 0x38],ESI"
    },
    {
      "address": "0102d27b",
      "instruction": "MOV dword ptr [ESP + 0x3c],ESI"
    },
    {
      "address": "0102d27f",
      "instruction": "MOV dword ptr [ESP + 0x40],ESI"
    },
    {
      "address": "0102d283",
      "instruction": "MOV dword ptr [ESP + 0x48],ESI"
    },
    {
      "address": "0102d287",
      "instruction": "MOV dword ptr [ESP + 0x4c],ESI"
    },
    {
      "address": "0102d28b",
      "instruction": "MOV dword ptr [ESP + 0x50],ESI"
    },
    {
      "address": "0102d28f",
      "instruction": "MOV dword ptr [ESP + 0x58],ESI"
    },
    {
      "address": "0102d293",
      "instruction": "MOV dword ptr [ESP + 0x5c],ESI"
    },
    {
      "address": "0102d297",
      "instruction": "MOV dword ptr [ESP + 0x60],ESI"
    },
    {
      "address": "0102d29b",
      "instruction": "MOV dword ptr [ESP + 0x68],ESI"
    },
    {
      "address": "0102d29f",
      "instruction": "MOV dword ptr [ESP + 0x6c],ESI"
    },
    {
      "address": "0102d2a3",
      "instruction": "MOV dword ptr [ESP + 0x70],ESI"
    },
    {
      "addre
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
  "original_bytes": 23393,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"cdecl observed; no implicit this parameter\",\n    \"return_observation\": \"The live function ends through ordinary void RET paths; the staged implementation does not add an implicit this parameter.\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"observed_use\": \"Loaded from the first stack slot and forwarded to helpers; no +0x70 or +0xAC access is attributed to this pointer.\",\n        \"position\": 1,\n        \"type\": \"Space *\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"observed_use\": \"Loaded into EDI, used as the explicit ECX operand for FUN_00bba990, and accessed at +0x70 and +0xAC.\",\n        \"position\": 2,\n        \"type\": \"SpaceContext *\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x0C\",\n        \"observed_use\": \"Loaded into EBP, compared with the result of FUN_0102fa30(4), and used in signed interval and branch selection.\",\n        \"position\": 3,\n        \"type\": \"std::uint32_t\",\n        \"width_bytes\": 4\n      }\n    ]\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 11,\n      \"symbol\": \"FUN_00aea230\",\n      \"va\": \"0x00aea230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 11,\n      \"symbol\": \"Simulator_cCommManager_CreateAndDispatchEvent_00aeb720\",\n      \"va\": \"0x00aeb720\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 11,\n      \"symbol\": \"pkg12_space_01021300\",\n      \"va\": \"0x01021300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00aea250\",\n      \"va\": \"0x00aea250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00aea5d0\",\n      \"va\": \"0x00aea5d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00aeb160\",\n      \"va\": \"0x00aeb160\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3b0\",\n      \"va\": \"0x00b3d3b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:None\"\n      ],\n      \"package\": \"PKG-11-H2-ROOT-ACCESSORS\",\n      \"score\": 8,\n      \"symbol\": \"root_accessor_00b3d3e0\",\n      \"va\": \"0x00b3d3e0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Event-carrier separation is preserved; repaired 0x00ce6950 is __fastcall ECX-only and 0x00aeb720 is __thiscall with six ordered stack words; final semantic and ABI re-review is clean, while runtime values remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_repair\",\n  \"blocked\": false,\n  \"blockers\": [\n    \"A linkable runtime model is not provided because the 53 direct callees and service vtables are not reconstructed in this package.\",\n    \"Concrete Space, SpaceContext, and event field layouts require additional direct xrefs, caller analysis, and runtime/differential evidence.\",\n    \"The Ghidra function prototypes remain undefined, so applying named SDK parameter types would exceed the observed evidence.\",\n    \"The vtable EAX targets and runtime ownership of the contiguous service object remain unresolved; only the observed register/stack records are staged.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"None\",\n  \"cluster\": null,\n  \"confidence\": 0.62,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"achievement_progress_update_00676e90\",\n        \"reconstructed\": true,\n        \"va\": \"0x00676e90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      },\n      {\n        \"name\": \"FUN_00aea230\",\n        \"reconstructed\": true,\n        \"va\": \"0x00aea230\"\n      },\n      {\n        \"name\": \"Simulator_cCommManager_CreateAndDispatchEvent_00aeb720\",\n        \"reconstructed\": true,\n        \"va\": \"0x00aeb720\"\n      },\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      },\n      {\n        \"name\": \"FUN_00b3d2c0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b3d2c0\"\n      },\n      {\n        \"name\": \"Simulator_cSpaceTrading_Get\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d4d0\"\n      },\n      {\n        \"name\": \"FUN_00b8dab0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b8dab0\"\n      },\n      {\n        \"name\": \"Simulator_LookupEmpireByPoliticalId\",\n        \"reconstructed\": true,\n        \"va\": \"0x00ba9370\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bbaa60\"\n      },\n      {\n        \"name\": \"FUN_00c70e00\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c70e00\"\n      },\n      {\n        \"name\": \"context_word_read_00ce6950\",\n        \"reconstructed\": true,\n        \"va\": \"0x00ce6950\"\n      },\n      {\n        \"name\": \"FUN_00e39ab0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e39ab0\"\n      },\n      {\n        \"name\":
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
  "body_end": "0102d7d0",
  "body_span_bytes": 1569,
  "body_start": "0102d1b0",
  "callees": [
    "FUN_01021230",
    "FUN_00d06240",
    "FUN_01030600",
    "FUN_01021080",
    "FUN_00bfc5f0",
    "FUN_00aea230",
    "Simulator::cSpaceTrading::Get",
    "FUN_00ad7ad0",
    "j_Sim_cCommManager_CreateSpaceCommEvent",
    "FUN_0102fa30",
    "App::IAppSystem::Get",
    "FUN_00ae09b0",
    "FUN_0102ff40",
    "FUN_00f47380",
    "FUN_010305b0",
    "FUN_01037e40",
    "FUN_00fe5430",
    "FUN_01021260",
    "FUN_0102ffc0",
    "FUN_00b3d2c0",
    "FUN_00bb59b0",
    "FUN_00ae9140",
    "FUN_00c8b770",
    "FUN_00ce6950",
    "memcpy",
    "FUN_00ba6490",
    "FUN_01002bd0",
    "Pollinator::cAchievementsManager::SetProgressFlags",
    "FUN_00f473a0",
    "FUN_01044640",
    "FUN_00a1ad60",
    "FUN_010383a0",
    "FUN_00c70c00",
    "FUN_01021090",
    "FUN_00675250",
    "FUN_00c71e70",
    "FUN_00c705c0",
    "FUN_01030560",
    "FUN_01021300",
    "FUN_00c31a00",
    "FUN_00b8dab0",
    "FUN_00e39ab0",
    "FUN_00bba990",
    "FUN_00b3d2a0",
    "FUN_00c70e00",
    "FUN_00bbaa60",
    "FUN_0102ff80",
    "FUN_00b3d4a0",
    "FUN_00ad79d0",
    "FUN_00ba9370",
    "FUN_0102f810",
    "FUN_00c8ce40",
    "FUN_00ffbe50"
  ],
  "callers": [
    "FUN_0102df20"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0102d1b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_74",
      "storage": "Stack[-0x74]:4",
      "type": "undefined4"
    },
    {
      "name": "local_78",
      "storage": "Stack[-0x78]:4",
      "type": "undefined4"
    },
    {
      "name": "local_7c",
      "storage": "Stack[-0x7c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_80",
      "storage": "Stack[-0x80]:4",
      "type": "undefined4"
    },
    {
      "name": "local_88",
      "storage": "Stack[-0x88]:4",
      "type": "undefined4"
    },
    {
      "name": "local_8c",
      "storage": "Stack[-0x8c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_90",
      "storage": "Stack[-0x90]:4",
      "type": "undefined4"
    },
    {
      "name": "local_98",
      "storage": "Stack[-0x98]:4",
      "type": "undefined4"
    },
    {
      "name": "local_9c",
      "storage": "Stack[-0x9c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_a0",
      "storage": "Stack[-0xa0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_a8",
      "storage": "Stack[-0xa8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_ac",
      "storage": "Stack[-0xac]:4",
      "type": "undefined4"
    },
    {
      "name": "local_b0",
      "storage": "Stack[-0xb0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_b4",
      "storage": "Stack[-0xb4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_b8",
      "storage": "Stack[-0xb8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_cc",
      "storage": "Stack[-0xcc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_d0",
      "storage": "Stack[-0xd0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_d8",
      "storage": "Stack[-0xd8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_e0",
      "storage": "Stack[-0xe0]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 19,
  "mode": "live",
  "name": "FUN_0102d1b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc2d1b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0102d1b0(void)",
  "size_bytes": 1569,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0102d1b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "0102e8e4"
    },
    {
      "from": "0102e95e"
    },
    {
      "from": "0102e996"
    },
    {
      "from": "0102ea0f"
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
  "file": "src/reconstruction/pkg12_space/space_functions.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_functions.cpp",
    "reconstruction/staging/pkg12-space/space_functions.hpp",
    "src/reconstruction/pkg12_space/space_functions.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg12-space/0102d1b0.json"
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
    "space_communication_state_observation"
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
  "original_bytes": 9658,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"overall\": 0.87\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 54,\n  \"evidence\": [\n    {\n      \"finding\": \"Surrender classification, local state updates, achievement call, temporary labels, and final cCommEvent wrapper.\",\n      \"kind\": \"target_decompilation\",\n      \"source\": \"Ghidra 0x0102d1b0\"\n    },\n    {\n      \"finding\": \"Numeric dispatcher calls the target on four selected branches and also creates other local surrender/communication events.\",\n      \"kind\": \"direct_caller_sibling\",\n      \"source\": \"Ghidra 0x0102df20\"\n    },\n    {\n      \"finding\": \"Independent raw key-0x0c/27-slot and key-0x06/24-slot entries under a common owner; no cCommEvent object flow.\",\n      \"kind\": \"anonymous_record_builder\",\n      \"source\": \"Ghidra 0x00e39ab0 and the focused space-pair resolution\"\n    },\n    {\n      \"finding\": \"0xa0 allocation, manager append, refcount-shaped object, and immediate application path.\",\n      \"kind\": \"communication_structure\",\n      \"source\": \"Ghidra 0x00aeb720, 0x00aeb160, 0x00aebe90, and structure:cCommEvent\"\n    },\n    {\n      \"finding\": \"The target is one member of a local surrender/space event family, not a universal event ABI.\",\n      \"kind\": \"state_and_sibling_consumer\",\n      \"source\": \"Ghidra 0x0102df20 and committed event-family artifacts\"\n    },\n    {\n      \"finding\": \"Conditional App/Telemetry encoding is separate from game persistence, resource serialization, and network protocol framing.\",\n      \"kind\": \"persistence_separator\",\n      \"source\": \"focused space-pair resolution and cCommEvent layout\"\n    },\n    {\n      \"finding\": \"No direct network, socket, protocol, or online request edge appears in the target.\",\n      \"kind\": \"negative_network_check\",\n      \"source\": \"Ghidra direct callees and strings\"\n    }\n  ],\n  \"family\": \"scenario_surrender_communication_event\",\n  \"interfaces\": {\n    \"boundaries\": {\n      \"boundary_rule\": \"Keep local cCommEvent, anonymous keyed space records, App transport, resource records, and persistence as separate families.\",\n      \"local\": \"The target operates on local simulator, space-trading, actor, achievement, UI/visibility, and communication-manager services.\",\n      \"network\": {\n        \"evidence\": [\n          \"The direct target body contains no socket, protocol, HTTP, or online request call.\",\n          \"The named cSpaceTrading and Pollinator achievements calls are local service calls in the inspected path.\",\n          \"cCommEvent is allocated and dispatched in-process by 0x00aeb720 -> 0x00aeb160 -> 0x00aebe90.\"\n        ],\n        \"not_claimed\": \"A Pollinator namespace label does not establish an online request/response boundary.\",\n        \"status\": \"no_direct_network_edge\"\n      }\n    },\n    \"direct_callees\": [],\n    \"direct_callers\": [],\n    \"globals\": [],\n    \"structures\": [],\n    \"vtables\": [],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": [],\n      \"identity_boundary\": \"not_reported\",\n      \"inputs\": [\n        \"param_1 local actor/event object\",\n        \"param_2 local space/player context\",\n        \"param_3 numeric state/threshold/event selector\"\n      ],\n      \"ordering\": [],\n      \"outputs\": [\n        \"mutated local surrender/space/communication state\",\n        \"local achievement-progress side effect\",\n        \"one or more cCommEvent create-and-dispatch operations\"\n      ],\n      \"postconditions\": [\n        \"The selected local state/visibility path is updated.\",\n        \"The anonymous space producer may have inserted independent key-0x0c/27-slot and key-0x06/24-slot entries.\",\n        \"A cCommEvent is constructed, appended to the communication manager, and immediately applied through the 0x00aeb720 wrapper.\"\n      ],\n      \"preconditions\": [\n        \"The local simulator, space-trading, and communication services must be available in the exercised mode.\",\n        \"The selected surrender branch is determined by param_3 and helper-returned state values.\"\n      ],\n      \"purpose\": \"LOCAL_SCENARIO_SURRENDER_ORCHESTRATOR\",\n      \"return\": {\n        \"status\": \"not_reported\"\n      },\n      \"side_effects\": [\n        \"Calls Pollinator::cAchievementsManager::SetProgressFlags with achievementID 1 in the decompiled path.\",\n        \"Allocates temporary strings SPG_SystemSurrender_Diplomatic_Planet or SPG_SystemSurrender_Diplomatic_Solar and releases them after local service calls.\",\n        \"May resolve nearest local space objects, mutate local visibility flags, and release borrowed object references.\"\n      ],\n      \"status\": \"partial_static_contract\",\n      \"unresolved\": [\n        \"What exact numeric/state values select diplomatic Planet versus Solar surrender?\",\n        \"What are param_1, param_2, and param_3 semantically?\",\n        \"Which raw keyed entry is consumed by the local space state and what is the key-0x06 sidecar's consumer?\",\n        \"What exact cCommEvent fields are populated for each surrender branch?\",\n        \"Does the achievement progress flag persist to a save or remain runtime-only?\",\n        \"What is the runtime ordering between the keyed space entry, cCommEvent application, and visible UI changes?\",\n        \"Does any indirect path cross a network service in a mode not covered by the direct call graph?\"\n      ]\n    }\n  },\n  \"invariants\": {\n    \"failure_semantics\": [],\n    \"invariants\": [],\n    \"invariants_status\": \"not_reported\"\n  },\n  \"name\": \"LOCAL_SCENARIO_SURRENDER_ORCHESTRATOR\",\n  \"package\": {\n    \"caveat\": \"not_reported\",\n    \"ownership_status\": \"not_reported\",\n    \"primary\": null,\n    \"secondary\": []\n  }
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
  "None",
  "Opaque",
  "Space",
  "Space *",
  "SpaceContext",
  "SpaceContext *",
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
      "0x00aeb160",
      "0x00aebe90",
      "0x00aed2c0",
      "0x00c75520",
      "0x00dd5160",
      "0x0102c9e0",
      "0x0102caa0",
      "0x0102cae0",
      "0x0102cc30",
      "0x0102cd90",
      "0x0102ce30",
      "0x0102cf10",
      "0x0102d1b0",
      "0x0102df20",
      "0x01072d40",
      "0x00aeb730"
    ],
    "conflict_id": "LC-006",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_SUPPORTED",
    "resolution_status": "RESOLVED_SUPPORTED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "0x00AEB720 communication wrapper",
    "unresolved_reason": "The exact private wrapper name and the full parameter types are not recoverable from static naming alone; the create-and-dispatch contract is resolved."
  }
]
```
